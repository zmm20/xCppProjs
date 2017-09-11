// 本文件的编码是UTF8
#include "stdafx.h"
#include "Login.h"
#include <iostream>
#include <json/json.h>
#include <unordered_map>

using namespace std;

unordered_map<std::string, int> g_fileIndexMap;

int main()
{
    
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
		if (!session.has(SessionData::loginin_)) { //第一次登陆.
			if (body.get_val(SessionData::uid_).compare(SessionData::username_) != 0
				|| body.get_val(SessionData::pwd_).compare(SessionData::password_) != 0)
			{
				//登陆失败.
				res.end(R"({"errcode":-3, "errmsg":"用户名或密码错误"})");
				return;
			}
		}

		session.set(SessionData::uid_, body.get_val(SessionData::uid_));
		session.set<bool>(SessionData::loginin_, true);
		session.set(SessionData::pwd_, SessionData::password_);

		std::string json = R"({"errcode":0,"uid":")";
		json += SessionData::username_ + R"(", "errmsg":""})";
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
    app.route("/workOrdersSelect", [](cinatra::Request& req, cinatra::Response& res, cinatra::ContextContainer& ctx)
    {
        //auto body = cinatra::urlencoded_body_parser(req.body());
        //auto& session = ctx.get_req_ctx<cinatra::Session>();

        //if (!session.has(SessionData::loginin_)
        //    || body.get_val(SessionData::uid_).compare(session.get<std::string>(SessionData::uid_)) != 0
        //    || !session.get<bool>(SessionData::loginin_))
        //{
        //    res.end(u8R"({"result":-2, "msg":"用户没有登录"})");
        //    return;
        //}

        // 该数据应该从数据库读取, 这里暂时从文件读取模仿一下
        std::string replyStr = u8"";
        std::ifstream initFile(R"(C:\Users\zmm\Documents\Visual Studio 2015\Projects\xCppProjs\session_control\my_test\workOrders.json)", std::ios::in);
        char buf[1024];
        while (initFile.getline(buf, 1024))
            replyStr += buf;

        cout << "response content: " << replyStr << endl;
        res.end(replyStr);

        return;
    });
    app.route("/workOrderUpdate", [](cinatra::Request& req, cinatra::Response& res, cinatra::ContextContainer& ctx)
    {
        //auto body = cinatra::urlencoded_body_parser(req.body());
        //auto& session = ctx.get_req_ctx<cinatra::Session>();

        //if (!session.has(SessionData::loginin_)
        //    || body.get_val(SessionData::uid_).compare(session.get<std::string>(SessionData::uid_)) != 0
        //    || !session.get<bool>(SessionData::loginin_))
        //{
        //    res.end(u8R"({"result":-2, "msg":"用户没有登录"})");
        //    return;
        //}

        
        cout << "request data: " << req.body() << endl;;
        Json::Value recvJson;
        Json::Reader reader;
        if (!reader.parse(req.body(), recvJson))
        {
            std::string json = R"({"errcode":1, "errmsg":"json 解析失败!"})";
            cout << "response data: " << json << endl;
            res.end(json);

            return;
        }
        const std::string orderNo = recvJson["number"].asString();


        Json::Value jRoot;
        jRoot["number"] = orderNo;
        jRoot["errcode"] = 0;
        jRoot["errmsg"] = "";

            
        Json::FastWriter writer;
        const std::string str = writer.write(jRoot);
        cout << "respone data: " << str << endl;
        res.end(str);

        return;
    });
    
    //app.route("/filesInOrder", [](cinatra::Request& req, cinatra::Response& res, cinatra::ContextContainer& ctx)
    //{
    //    const std::string no = req.query().get_val("workOrderNo");
    //    cout << "order no = " << no << endl;

    //    Json::Value jRoot;
    //    jRoot["number"] = no;

    //    Json::Value jFileList;
    //    Json::Value jFileNote;

    //    std::string json = R"({"errcode":0, "errmsg":""})";
    //    if ("00001" == no)
    //    {// 模拟未处理的工单
    //        jRoot["fileList"] = "[]";
    //        jRoot["errcode"] = 0;
    //        jRoot["errmsg"] = "";
    //    }
    //    else if ("00002" == no)
    //    {// 模拟已处理的工单
    //        jFileNote["fileName"] = "文件1.doc";
    //        jFileNote["size"] = 1200;
    //        jFileNote["lastDate"] = "2017/01/01 08:01";
    //        jFileList.append(jFileNote);

    //        jFileNote["fileName"] = "文件2.doc";
    //        jFileNote["size"] = 1000;
    //        jFileNote["lastDate"] = "2017/01/02 08:01";
    //        jFileList.append(jFileNote);

    //        jRoot["fileList"] = jFileList;
    //        jRoot["errcode"] = 0;
    //        jRoot["errmsg"] = "";
    //    }
    //    else
    //    {
    //        jRoot["errcode"] = -1;
    //        jRoot["errmsg"] = "没有找到工单号: " + no;
    //        jRoot["fileList"] = "[]";
    //    }

    //    cout << "respone data: " << jRoot.toStyledString() << endl;
    //    res.end(jRoot.toStyledString());

    //    return;
    //});
    
    app.route("/fileUploadBefore", [](cinatra::Request& req, cinatra::Response& res, cinatra::ContextContainer& ctx)
    {
        cout << "request body: " << req.body() << endl;

        Json::Value recvJson;
        Json::Reader reader;
        if (!reader.parse(req.body(), recvJson))
        {
            std::string json = R"({"errcode":1, "errmsg":"json 解析失败!"})";
            cout << "response data: " << json << endl;
            res.end(json);

            return;
        }

        const std::string filenameRule = recvJson["filenameRule"].asString();
        const std::string orderNo = recvJson["number"].asString();

        int index = g_fileIndexMap[filenameRule];
        ++index;
        g_fileIndexMap[filenameRule] = index;


        // 响应客户端:

        Json::Value jRoot;
        jRoot["errcode"] = 0;
        jRoot["errmsg"] = "";
        jRoot["number"] = orderNo;
        jRoot["fileIndex"] = index;

        Json::FastWriter writer;
        const std::string str = writer.write(jRoot);
        cout << "respone data: " << str << endl;
        res.end(str);

        return;
    });
    app.route("/fileUploadEnd", [](cinatra::Request& req, cinatra::Response& res, cinatra::ContextContainer& ctx)
    {
        cout << "request body: " << req.body() << endl;

        Json::Value recvJson;
        Json::Reader reader;
        if (!reader.parse(req.body(), recvJson))
        {
            std::string json = R"({"errcode":1, "errmsg":"json 解析失败!"})";
            cout << "response data: " << json << endl;
            res.end(json);

            return;
        }

        try
        {
            const std::string orderNo = recvJson["number"].asString();
            const int uploadState = recvJson["uploadState"].asInt();
            const std::string fileName = recvJson["fileName"].asString();
            const Json::UInt64 size = recvJson["size"].asUInt64();
            const std::string lastDate = recvJson["lastDate"].asString();
            const std::string filenameRule = recvJson["filenameRule"].asString();
            const std::string fileIndex = recvJson["fileIndex"].asString();

            if (uploadState != 0)
            {
                int index = g_fileIndexMap[filenameRule];
                --index;
                g_fileIndexMap[filenameRule] = index;
            }

            // 响应客户端:

            Json::Value jRoot;
            jRoot["errcode"] = 0;
            jRoot["errmsg"] = "";
            jRoot["number"] = orderNo;

            Json::FastWriter writer;
            const std::string str = writer.write(jRoot);
            cout << "respone data: " << str << endl;
            res.end(str);

        }
        catch (const Json::Exception& e)
        {
            cout << "json 解析失败: " << e.what() << endl;
        }

        return;
    });


	app.static_dir("./static").listen("http").run();
	return 0;
}
