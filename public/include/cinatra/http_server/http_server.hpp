
#pragma once

#ifdef _MSC_VER
#pragma warning(disable:4819)
#endif // _MSC_VER

#include <cinatra/http_server/io_service_pool.hpp>
#include <cinatra/http_server/connection.hpp>
#include <cinatra/utils/logging.hpp>

#include <boost/noncopyable.hpp>
#include <boost/asio.hpp>
#include <boost/asio/spawn.hpp>

#include <unordered_map>
#include <functional>
#include <memory>
#include <string>


namespace cinatra
{
	struct HttpsConfig 
	{
		using pwd_callback_t = std::function < std::string(std::size_t, int) > ;
		enum verify_mode_t
		{
			none,
			optional,
			required,
		};

		HttpsConfig(bool ssl_enable_v3,
			verify_mode_t verify_mode,
			pwd_callback_t pwd_callback,
			const std::string& certificate_chain_file,
			const std::string& private_key_file,
			const std::string& tmp_dh_file,
			const std::string& verify_file)
			:ssl_enable_v3(ssl_enable_v3),
			verify_mode(verify_mode),
			pwd_callback(pwd_callback),
			certificate_chain_file(certificate_chain_file),
			private_key_file(private_key_file),
			tmp_dh_file(tmp_dh_file),
			verify_file(verify_file)
		{}
		HttpsConfig()
		{}
		bool ssl_enable_v3;
		verify_mode_t verify_mode;

		pwd_callback_t pwd_callback;
		std::string certificate_chain_file;
		std::string private_key_file;
		std::string tmp_dh_file;
		std::string verify_file;
	};

	class HTTPServer : boost::noncopyable
	{
	public:
#ifndef CINATRA_SINGLE_THREAD
		HTTPServer(std::size_t io_service_pool_size)
			:io_service_pool_(io_service_pool_size)
#else
		HTTPServer()
			: io_service_pool_(1)
#endif // CINATRA_SINGLE_THREAD
		{

		}

		~HTTPServer()
		{}

		HTTPServer& set_request_handler(request_handler_t request_handler)
		{
			request_handler_ = request_handler;
			return *this;
		}

		HTTPServer& set_error_handler(error_handler_t error_handler)
		{
			error_handler_ = error_handler;
			return *this;
		}

		HTTPServer& listen(const std::string& address, const std::string& port)
		{
			boost::asio::spawn(
				io_service_pool_.get_io_service(),
				[this, address, port](boost::asio::yield_context yield)
			{
				do_accept(address, port, yield);
			});

			return *this;
		}

#ifdef CINATRA_ENABLE_HTTPS
		HTTPServer& listen(const std::string& address, const std::string& port, HttpsConfig cfg)
		{
			boost::asio::spawn(
				io_service_pool_.get_io_service(),
				[this, address, port, cfg](boost::asio::yield_context yield)
			{
				do_accept(address, port, cfg, yield);
			});

			return *this;
		}
#endif //CINATRA_ENABLE_HTTPS

		HTTPServer& listen(const std::string& address, unsigned short port)
		{
			return listen(address, boost::lexical_cast<std::string>(port));
		}

		HTTPServer& static_dir(const std::string& dir)
		{
			static_dir_ = dir;
			return *this;
		}

		void run()
		{
			LOG_DBG << "Starting HTTP Server";
			io_service_pool_.run();
		}

	private:
		void do_accept(
			const std::string address,
			const std::string port,
			const boost::asio::yield_context& yield)
		{
			LOG_DBG << "Listen on " << address << ":" << port;
			boost::asio::ip::tcp::acceptor acceptor(io_service_pool_.get_io_service());
			boost::asio::ip::tcp::resolver resolver(acceptor.get_io_service());
			boost::asio::ip::tcp::resolver::query query(address, port);
			boost::asio::ip::tcp::endpoint endpoint = *resolver.resolve(query);
			acceptor.open(endpoint.protocol());
			acceptor.set_option(boost::asio::ip::tcp::acceptor::reuse_address(true));
			acceptor.bind(endpoint);
			acceptor.listen();

			for (;;)
			{
				auto conn(
					std::make_shared<Connection<tcp_socket>>(
					io_service_pool_.get_io_service(),
					request_handler_, error_handler_, static_dir_));

				boost::system::error_code ec;
				acceptor.async_accept(conn->raw_socket(), yield[ec]);
				if (ec)
				{
					LOG_DBG << "Accept new connection failed: " << ec.message();
					continue;
				}

				conn->start();
			}
		}

#ifdef CINATRA_ENABLE_HTTPS
		void do_accept(
			const std::string address,
			const std::string port,
			HttpsConfig config,
			const boost::asio::yield_context& yield)
		{
			LOG_DBG << "Listen on " << address << ":" << port;
			boost::asio::ip::tcp::acceptor acceptor(io_service_pool_.get_io_service());
			boost::asio::ip::tcp::resolver resolver(acceptor.get_io_service());
			boost::asio::ip::tcp::resolver::query query(address, port);
			boost::asio::ip::tcp::endpoint endpoint = *resolver.resolve(query);
			acceptor.open(endpoint.protocol());
			acceptor.set_option(boost::asio::ip::tcp::acceptor::reuse_address(true));
			acceptor.bind(endpoint);
			acceptor.listen();

			std::unique_ptr<boost::asio::ssl::context> ctx;

			ctx.reset(new boost::asio::ssl::context(boost::asio::ssl::context::sslv23));
			unsigned long ssl_options = boost::asio::ssl::context::default_workarounds
				| boost::asio::ssl::context::no_sslv2
				| boost::asio::ssl::context::single_dh_use;

			if (!config.ssl_enable_v3)
				ssl_options |= boost::asio::ssl::context::no_sslv3;
			ctx->set_options(ssl_options);

			if (config.pwd_callback)
			{
				ctx->set_password_callback(config.pwd_callback);
			}

			if (config.verify_mode == HttpsConfig::none)
			{
				ctx->set_verify_mode(boost::asio::ssl::context::verify_none);
			}
			else if (config.verify_mode == HttpsConfig::optional)
			{
				ctx->set_verify_mode(boost::asio::ssl::context::verify_peer);
				ctx->load_verify_file(config.verify_file);
			}
			else
			{
				// required
				ctx->set_verify_mode(boost::asio::ssl::context::verify_peer |
					boost::asio::ssl::context::verify_fail_if_no_peer_cert);
				ctx->load_verify_file(config.verify_file);
			}

			ctx->use_certificate_chain_file(config.certificate_chain_file);
			ctx->use_private_key_file(config.private_key_file,
				boost::asio::ssl::context::pem);
			ctx->use_tmp_dh_file(config.tmp_dh_file);

			for (;;)
			{

				auto conn(
					std::make_shared<Connection<ssl_socket>>(
					io_service_pool_.get_io_service(),
					*ctx, request_handler_, error_handler_, static_dir_));
				boost::system::error_code ec;
				acceptor.async_accept(conn->raw_socket(), yield[ec]);
				if (ec)
				{
					LOG_DBG << "Accept new connection failed: " << ec.message();
					continue;
				}

				conn->start();
			}
		}
#endif // CINATRA_ENABLE_HTTPS
	private:
		IOServicePool io_service_pool_;

		request_handler_t request_handler_;
		error_handler_t error_handler_;

		std::string static_dir_;
	};
}
