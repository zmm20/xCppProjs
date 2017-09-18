#include "stdafx.h"
#include "ZISecArchivingSys.h"
#include <json/json.h>
#include <iostream>
#include <unordered_map>
#include <fstream>
using namespace std;

unordered_map<std::string, int> g_fileIndexMap;

ZISecArchivingSys::ZISecArchivingSys()
{
}


ZISecArchivingSys::~ZISecArchivingSys()
{
}

std::string ZISecArchivingSys::login(const std::string& jsonData, cinatra::ContextContainer& ctx)
{
    string strResult;

    Json::Value recvJson;
    Json::Reader reader;
    if (!reader.parse(jsonData, recvJson))
    {
        strResult = R"({"errcode":1, "errmsg":"json 解析失败!"})";
        return strResult;
    }
    const std::string user = recvJson["user"].asString();
    const std::string password = recvJson["password"].asString();
    cout << "user: " << user << ", password: " << password << endl;

    auto& session = ctx.get_req_ctx<cinatra::Session>();
    if (!session.has("loginin")) { //第一次登陆.
        if (user != "zmm" || password != "e10adc3949ba59abbe56e057f20f883e")
        {
            //登陆失败.
            strResult = R"({"errcode":-3, "errmsg":"用户名或密码错误"})";
            return strResult;
        }
    }

    // 登录成功
    session.set("user", "zmm");
    session.set<bool>("loginin", true);
    session.set("password", "e10adc3949ba59abbe56e057f20f883e");

    strResult = R"({"errcode":0,"uid":")";
    strResult += R"(zmm", "errmsg":""})";

    return strResult;
}

std::string ZISecArchivingSys::workOrdersSelect(const std::string& jsonData)
{
    string strResult;

    strResult = u8"";
    std::ifstream initFile(R"(C:\Users\zmm\Documents\Visual Studio 2015\Projects\xCppProjs\session_control\my_test\workOrders.json)", std::ios::in);
    char buf[1024];
    while (initFile.getline(buf, 1024))
        strResult += buf;

    return strResult;
}

std::string ZISecArchivingSys::fileUploadBefore(const std::string& jsonData)
{
    string strResult;

    Json::Value recvJson;
    Json::Reader reader;
    if (!reader.parse(jsonData, recvJson))
    {
        strResult = R"({"errcode":1, "errmsg":"json 解析失败!"})";

        return strResult;
    }

    const std::string filenameRule = recvJson["filenameRule"].asString();
    const std::string orderNo = recvJson["number"].asString();

    int index = g_fileIndexMap[filenameRule];
    ++index;
    g_fileIndexMap[filenameRule] = index;



    Json::Value jRoot;
    jRoot["errcode"] = 0;
    jRoot["errmsg"] = "";
    jRoot["number"] = orderNo;
    jRoot["fileIndex"] = index;

    Json::FastWriter writer;
    strResult = writer.write(jRoot);
    cout << "respone data: " << strResult << endl;
    
    return strResult;
}

std::string ZISecArchivingSys::fileUploadEnd(const std::string& jsonData)
{
    string strResult;

    Json::Value recvJson;
    Json::Reader reader;
    if (!reader.parse(jsonData, recvJson))
    {
        strResult = R"({"errcode":1, "errmsg":"json 解析失败!"})";
        cout << "response data: " << strResult << endl;

        return strResult;
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

        Json::Value jRoot;
        jRoot["errcode"] = 0;
        jRoot["errmsg"] = "";
        jRoot["number"] = orderNo;

        Json::FastWriter writer;
        strResult = writer.write(jRoot);
    }
    catch (const Json::Exception& e)
    {
        cout << "json 异常: " << e.what() << endl;
    }


    return strResult;
}

std::string ZISecArchivingSys::workOrderUpdate(const std::string& jsonData)
{
    string strResult;

    Json::Value recvJson;
    Json::Reader reader;
    if (!reader.parse(jsonData, recvJson))
    {
        strResult = R"({"errcode":1, "errmsg":"json 解析失败!"})";
        cout << "response data: " << strResult << endl;

        return strResult;
    }
    const std::string orderNo = recvJson["number"].asString();
    const int state = recvJson["state"].asInt();


    Json::Value jRoot;
    jRoot["number"] = orderNo;
    jRoot["errcode"] = 0;
    jRoot["errmsg"] = "";
    jRoot["state"] = state;


    Json::FastWriter writer;
    strResult = writer.write(jRoot);
    
    return strResult;
}