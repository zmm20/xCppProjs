// MyWebService.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <fstream>
#include <locale>
#include <codecvt>
#include <string>
using namespace std;

struct MyStruct
{
    void hello(cinatra::Request& req, cinatra::Response& res)
    {
        //res.end("hello world!");
        res.redirect("index.html");
    }
};


std::string GBK2UTF(const std::string& src) noexcept;
std::string UTF2GBK(const std::string& src) noexcept;


int main()
{
    cinatra::Cinatra<> app;
    // method 1:
    MyStruct t;
    app.route("/", &MyStruct::hello, &t);

    // method 2:
    app.route("/knowledge/add", [](cinatra::Request& req, cinatra::Response& res)
    {
        cout << "request data: " << UTF2GBK(req.body()) << endl;

        std::string strRes = "{ "
            "  \"error\" : false "
            ", \"errMsg\" : \"\" "
            ", \"cmd\" : \"add\" "
            "}";
        res.end(strRes);
    }
    );
    app.route("/knowledge/delete", [](cinatra::Request& req, cinatra::Response& res)
    {
        cout << "request data: " << UTF2GBK(req.body()) << endl;

        std::string strRes = "{ "
            "  \"error\" : false "
            ", \"errMsg\" : \"\" "
            ", \"cmd\" : \"delete\" "
            "}";
        res.end(strRes);
    }
    );
    app.route("/knowledge/modify", [](cinatra::Request& req, cinatra::Response& res)
    {
        cout << "request data: " << UTF2GBK(req.body()) << endl;

        std::string strRes = "{ "
            "  \"error\" : false "
            ", \"errMsg\" : \"\" "
            ", \"cmd\" : \"modify\" "
            "}";
        res.end(strRes);
    }
    );
    app.route("/knowledge/select", [](cinatra::Request& req, cinatra::Response& res)
    {
        cout << "request data: " << UTF2GBK(req.body()) << endl;

        // 该数据应该从数据库读取, 这里暂时从文件读取模仿一下
        std::string replyStr = u8"";
        std::ifstream initFile("C:\\Users\\zmm\\Documents\\Visual Studio 2015\\Projects\\xTestCpp11\\ISecExamPaperAddIn\\initTree.json", std::ios::in);
        char buf[1024];
        while (initFile.getline(buf, 1024))
            replyStr += buf;

        res.end(replyStr);
    }
    );

    app.route("/topic/add", [](cinatra::Request& req, cinatra::Response& res)
    {
        cout << "request data: " << UTF2GBK(req.body()) << endl;

        std::string strRes = "{ "
            "  \"error\" : false "
            ", \"errMsg\" : \"\" "
            ", \"cmd\" : \"modify\" "
            "}";
        res.end(strRes);
    }
    );

    app.route("/topic/init", [](cinatra::Request& req, cinatra::Response& res)
    {
        cout << "request data: " << UTF2GBK(req.body()) << endl;

        // 该数据应该从数据库读取, 这里暂时从文件读取模仿一下
        std::string replyStr = u8"";
        std::ifstream initFile("C:\\Users\\zmm\\Documents\\Visual Studio 2015\\Projects\\xTestCpp11\\ISecExamPaperAddIn\\initForm.json", std::ios::in);
        char buf[1024];
        while (initFile.getline(buf, 1024))
            replyStr += buf;
        res.end(replyStr);
    }
    );

    app.route("/anwerSheet/gen", [](cinatra::Request& req, cinatra::Response& res) {
        cout << "request data: " << UTF2GBK(req.body()) << endl;

        std::string strRes = u8R"({"error" : false , "errMsg" : ""})";
        res.end(strRes);
    }
    );


    app.static_dir("./static");
    app.listen("0.0.0.0", "8080"); //"http"
    app.run();

    return 0;
}




/// 由gbk编码, 转换为utf8编码
///
/// @author zhoumanman888@126.com
std::string GBK2UTF(const std::string& src) noexcept
{
#ifdef _MSC_VER
    const string localeName = "CHS"; // ".936";
#else
    const string localeName = "zh_CN.GBK";
#endif
    try
    {
        //std::wstring ws = to_wstring(src, std::locale(localeName));
        wstring_convert<codecvt_byname<wchar_t, char, mbstate_t>> cv1(new codecvt_byname<wchar_t, char, mbstate_t>(localeName));
        const std::wstring ws = cv1.from_bytes(src);

        std::wstring_convert<std::codecvt_utf8<wchar_t>> myconv;
        return myconv.to_bytes(ws);
    }
    catch (std::exception& e)
    {
        fprintf(stderr, "GBK2UTF %s\n", e.what());
        return src;
    }
}

/// 由utf8编码, 转换为gbk编码
///
/// @author zhoumanman888@126.com
std::string UTF2GBK(const std::string& src) noexcept
{
#ifdef _MSC_VER
    const string localeName = "CHS"; //".936";
#else
    const string localeName = "zh_CN.GBK";
#endif
    try
    {
        std::wstring_convert<std::codecvt_utf8<wchar_t>> myconv;
        const std::wstring ws = myconv.from_bytes(src);

        wstring_convert<codecvt_byname<wchar_t, char, mbstate_t>> cv(new codecvt_byname<wchar_t, char, mbstate_t>(localeName));
        return cv.to_bytes(ws);
    }
    catch (std::exception& e)
    {
        fprintf(stderr, "UTF2GBK %s\n", e.what());
        return src;
    }
}