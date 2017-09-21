// 本文件的编码是UTF8
#include "stdafx.h"
#include "Login.h"
#include <iostream>
#include <json/json.h>
#include "ZISecArchivingSys.h"
#include <my/TextHelper.h>

using namespace std;


int main()
{
    cout << "server running..." << endl;

	cinatra::Cinatra<
		cinatra::RequestCookie,
		cinatra::ResponseCookie,
		cinatra::Session,
		LoginControl
	> app;
	app.route("/", [](cinatra::Request& /* req */, cinatra::Response& res)
	{
		res.redirect("index.html");
		return;
	});
	app.route("/login", [](cinatra::Request& req, cinatra::Response& res, cinatra::ContextContainer& ctx)
	{
		auto body = cinatra::urlencoded_body_parser(req.body());
		auto& session = ctx.get_req_ctx<cinatra::Session>();

        cout << "request body: " << req.body() << endl;

		if (!session.has(SessionData::loginin_)) { //第一次登陆.
			if (body.get_val(SessionData::uid_).compare(SessionData::username_) != 0
				|| body.get_val(SessionData::pwd_).compare(SessionData::password_) != 0)
			{
				//登陆失败.
				res.end(R"({"result":-3, "errmsg":"用户名或密码错误"})");
				return;
			}
		}

		session.set(SessionData::uid_, body.get_val(SessionData::uid_));
		session.set<bool>(SessionData::loginin_, true);
		session.set(SessionData::pwd_, SessionData::password_);

		std::string json = R"({"result":0,"uid":")";
		json += SessionData::username_ + R"(", "errmsg":""})";
        cout << "respone str: " << json << endl;
		res.end(json);
	});
	app.route("/loginOut", [](cinatra::Response& res, cinatra::ContextContainer& ctx)
	{
		auto& session = ctx.get_req_ctx<cinatra::Session>();
		if (session.has(SessionData::loginin_))
		{
			session.del(SessionData::loginin_);
		}
		res.redirect("/index.html");
	});
	app.route("/change", [](cinatra::Request& req, cinatra::Response& res, cinatra::ContextContainer& ctx)
	{
		auto body = cinatra::urlencoded_body_parser(req.body());
		auto& session = ctx.get_req_ctx<cinatra::Session>();

		if (!session.has(SessionData::loginin_)
			|| body.get_val(SessionData::uid_).compare(session.get<std::string>(SessionData::uid_)) != 0
			|| !session.get<bool>(SessionData::loginin_))
		{
			res.end("{\"result\":-2}");
			return;
		}
		session.set(SessionData::nick_, body.get_val(SessionData::nick_));
		session.set(SessionData::pwd_, body.get_val(SessionData::pwd_));
		res.end("{\"result\":0}");
	});
	app.route("/queryInfo", [](cinatra::Request& req, cinatra::Response& res, cinatra::ContextContainer& ctx)
	{
		auto body = cinatra::urlencoded_body_parser(req.body());
		auto& session = ctx.get_req_ctx<cinatra::Session>();

		if (!session.has(SessionData::loginin_)
			|| body.get_val(SessionData::uid_).compare(session.get<std::string>(SessionData::uid_)) != 0
			|| !session.get<bool>(SessionData::loginin_))
		{
			res.end("{\"result\":-2}");
			return;
		}
		std::string json = "{\"result\":0,\"uid\":\"";
		json += SessionData::username_ + "\",\"nick\":\"" 
			+ (session.has(SessionData::nick_) ? session.get<std::string>(SessionData::nick_) : "not set")
			+ "\",\"pwd\":\"" 
			+ session.get<std::string>(SessionData::pwd_)
			+ "\"}";
		res.end(json);
		return;
	});

    ZISecArchivingSys arc;
    app.route("/api", [&arc](cinatra::Request& req, cinatra::Response& res, cinatra::ContextContainer& ctx)
    {
        auto body = cinatra::urlencoded_body_parser(req.body());
        auto& session = ctx.get_req_ctx<cinatra::Session>();

        cout << "----------------/api begin---------" << endl;
        cout << "request body: " << req.body() << endl;
        if (!session.has("loginin")
            //|| body.get_val(SessionData::uid_).compare(session.get<std::string>(SessionData::uid_)) != 0
            || !session.get<bool>("loginin"))
            cout << "none login" << endl;
        else
            //cout << "has login, and user = " << session.get<std::string>("user") << endl;
            cout << "has login" << endl;
        const string strFunType = body.get_val("funType");
        const string jsonData = body.get_val("jsonData");

        std::string strReq;
        if ("login" == strFunType)
            strReq = arc.login(jsonData, ctx);
        else if ("workOrdersSelect" == strFunType)
            strReq = arc.workOrdersSelect(jsonData);
        else if ("fileUploadBefore" == strFunType)
            strReq = arc.fileUploadBefore(jsonData);
        else if ("fileUploadEnd" == strFunType)
            strReq = arc.fileUploadEnd(jsonData);
        else if ("workOrderUpdate" == strFunType)
            strReq = arc.workOrderUpdate(jsonData);
        else
            strReq = R"({"errcode":-4, "errmsg":"错误的函数方法"})";

        cout << "respone data: " << strReq << endl;
        res.end(strReq);
        cout << "----------------/api end---------" << endl << endl << endl;
    });

    app.route("/test", [&arc](cinatra::Request& req, cinatra::Response& res, cinatra::ContextContainer& ctx)
    {
        auto body = cinatra::urlencoded_body_parser(req.body());
        auto& session = ctx.get_req_ctx<cinatra::Session>();

        cout << "----------------/test begin---------" << endl;
        const std::string strBody = req.body();
        cout << "request body(show in origin): " << strBody << endl;
        cout << "request body(show in gbk): " << XAB::CTextHelper::UTF2GBK(strBody) << endl;
        if (!session.has("loginin")
            //|| body.get_val(SessionData::uid_).compare(session.get<std::string>(SessionData::uid_)) != 0
            || !session.get<bool>("loginin"))
            cout << "none login" << endl;
        else
            //cout << "has login, and user = " << session.get<std::string>("user") << endl;
            cout << "has login" << endl;
        

        std::string strReq = R"({"errcode":0, "errmsg":"测试成功!"})";
        cout << "respone data(show in origin): " << strReq << endl;
        cout << "respone data(show in gbk): " << XAB::CTextHelper::UTF2GBK(strReq) << endl;
        res.end(strReq);

        cout << "----------------/test end---------" << endl;

    });

	app.static_dir("./static").listen("http").run();
	return 0;
}
