#define MAIN
#ifdef MAIN

#include <iostream>
#include <boost/asio.hpp>

using namespace std;
using boost::asio::ip::tcp;


int ParseUrl(const std::string& url, std::string& out_server, std::string& out_port, std::string& out_path) noexcept;
int HttpPost(const std::string& host, const std::string& port, const std::string& page, const std::string& data, std::string& reponse_data) noexcept;

int main()
{
    cout << "test 1" << endl;
    {
        int ret;

        std::string strHost = "192.168.4.162";
        std::string strPort = "80";
        std::string strPath;
        //ret = ParseUrl("http://192.168.4.162/login", strHost, strPort, strPath);
        //assert(ret == 0);

        string strRespone;
        ret = HttpPost(strHost, strPort, "/login", "user=zmm&password=e10adc3949ba59abbe56e057f20f883e", strRespone);
        assert(ret == 0);
        cout << "login respone content: " << strRespone << endl;

        // 从服务器端可以发现, 每次 HttpPost 之后连接都会中断, session 也就丢失了
        ret = HttpPost(strHost, strPort, "/api", "", strRespone);
        assert(ret == 0);
        cout << "api respone content: " << strRespone << endl;

    }
    cout << endl;


    return EXIT_SUCCESS;
}

int HttpPost(const std::string& host, const std::string& port, const std::string& page, const std::string& data, std::string& reponse_data) noexcept
{
    try
    {
        boost::asio::io_service io_service;
        //如果io_service存在复用的情况
        if (io_service.stopped())
            io_service.reset();

        // 从dns取得域名下的所有ip
        tcp::resolver resolver(io_service);
        tcp::resolver::query query(host, port);
        tcp::resolver::iterator endpoint_iterator = resolver.resolve(query);

        // 尝试连接到其中的某个ip直到成功 
        tcp::socket socket(io_service);
        boost::asio::connect(socket, endpoint_iterator);

        // Form the request. We specify the "Connection: close" header so that the
        // server will close the socket after transmitting the response. This will
        // allow us to treat all data up until the EOF as the content.
        boost::asio::streambuf request;
        std::ostream request_stream(&request);
        request_stream << "POST " << page << " HTTP/1.0\r\n";
        request_stream << "Host: " << host << ":" << port << "\r\n";
        request_stream << "Accept: */*\r\n";
        request_stream << "Content-Length: " << data.length() << "\r\n";
        request_stream << "Content-Type: application/x-www-form-urlencoded\r\n";
        request_stream << "Connection: close\r\n\r\n"; //close / Keep-alive
        request_stream << data;

        // Send the request.
        boost::asio::write(socket, request);

        // Read the response status line. The response streambuf will automatically
        // grow to accommodate the entire line. The growth may be limited by passing
        // a maximum size to the streambuf constructor.
        boost::asio::streambuf response;
        boost::asio::read_until(socket, response, "\r\n");

        // Check that response is OK.
        std::istream response_stream(&response);
        std::string http_version;
        response_stream >> http_version;
        unsigned int status_code;
        response_stream >> status_code;
        std::string status_message;
        std::getline(response_stream, status_message);
        if (!response_stream || http_version.substr(0, 5) != "HTTP/")
        {
            reponse_data = "Invalid response";
            return -2;
        }
        // 如果服务器返回非200都认为有错,不支持301/302等跳转
        if (status_code != 200)
        {
            reponse_data = "Response returned with status code != 200 ";
            return status_code;
        }

        // 传说中的包头可以读下来了
        std::string header;
        std::vector<std::string> headers;
        while (std::getline(response_stream, header) && header != "\r")
            headers.push_back(header);

        // 读取所有剩下的数据作为包体
        boost::system::error_code error;
        while (boost::asio::read(socket, response,
            boost::asio::transfer_at_least(1), error))
        {
        }

        //响应有数据
        if (response.size())
        {
            std::istream response_stream(&response);
            std::istreambuf_iterator<char> eos;
            reponse_data = std::string(std::istreambuf_iterator<char>(response_stream), eos);
        }

        if (error != boost::asio::error::eof)
        {
            // 这里的编码为gbk, 需要转成utf-8
            reponse_data = error.message();
            //reponse_data = GBK2UTF(reponse_data);
            return -3;
        }
    }
    catch (std::exception& e)
    {
        // 这里的编码为gbk, 需要转成utf-8
        reponse_data = e.what();
        //reponse_data = GBK2UTF(reponse_data);
        return -4;
    }
    return 0;
}

int ParseUrl(const std::string& url, std::string& out_server, std::string& out_port, std::string& out_path) noexcept
{
    const std::string http___ = "http://";
    const std::string https___ = "https://";
    std::string temp_data = url;

    if (temp_data.find(http___) == 0)
        temp_data = temp_data.substr(http___.length());
    else if (temp_data.find(https___) == 0)
        temp_data = temp_data.substr(https___.length());
    else
        return -1;

    std::size_t idx = temp_data.find('/');
    if (std::string::npos == idx)
    {
        out_path = "/";
        idx = temp_data.size();
    }
    else
    {
        out_path = temp_data.substr(idx);
    }

    out_server = temp_data.substr(0, idx);
    idx = out_server.find(':');
    if (std::string::npos == idx)
    {
        out_port = "http";
        out_port = "80";
    }
    else
    {
        out_port = out_server.substr(idx + 1);
        out_server = out_server.substr(0, idx);
    }

    return 0;
}
#endif