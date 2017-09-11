// MyWebService.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <fstream>
#include <locale>
#include <codecvt>
#include <string>
#include <fstream>

using namespace std;

struct MyStruct
{
    void hello(cinatra::Request& req, cinatra::Response& res)
    {
        cout << "/, request data: " << req.body() << endl;
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
        cout << "/knowledge/add, request data: " << UTF2GBK(req.body()) << endl;

        std::string strRes = "{ "
            "  \"error\" : false "
            ", \"errMsg\" : \"\" "
            ", \"cmd\" : \"add\" "
            "}";
        cout << "response content: " << strRes << endl;
        res.end(strRes);
    }
    );
    app.route("/knowledge/delete", [](cinatra::Request& req, cinatra::Response& res)
    {
        cout << "/knowledge/delete, request data: " << UTF2GBK(req.body()) << endl;

        std::string strRes = "{ "
            "  \"error\" : false "
            ", \"errMsg\" : \"\" "
            ", \"cmd\" : \"delete\" "
            "}";
        cout << "response content: " << strRes << endl;
        res.end(strRes);
    }
    );
    app.route("/knowledge/modify", [](cinatra::Request& req, cinatra::Response& res)
    {
        cout << "/knowledge/modify, request data: " << UTF2GBK(req.body()) << endl;

        std::string strRes = "{ "
            "  \"error\" : false "
            ", \"errMsg\" : \"\" "
            ", \"cmd\" : \"modify\" "
            "}";
        cout << "response content: " << strRes << endl;
        res.end(strRes);
    }
    );
    app.route("/knowledge/select", [](cinatra::Request& req, cinatra::Response& res)
    {
        cout << "/knowledge/select, request data: " << UTF2GBK(req.body()) << endl;

        // 该数据应该从数据库读取, 这里暂时从文件读取模仿一下
        std::string replyStr = u8"";
        std::ifstream initFile(R"(C:\Users\zmm\Documents\Visual Studio 2015\Projects\xCppProjs\ISecExamPaperAddIn\initTree.json)", std::ios::in);
        char buf[1024];
        while (initFile.getline(buf, 1024))
            replyStr += buf;

        cout << "response content: " << replyStr << endl;
        res.end(replyStr);

        
    }
    );

    app.route("/test", [](cinatra::Request& req, cinatra::Response& res)
    {
        cout << "/test, request data: " << UTF2GBK(req.body()) << endl;

        
        const std::string name = req.query().get_val("name");
        cout << "name = " << name << endl;

        res.write(u8"<html><head><title>test</title >");
        res.write(u8R"(<meta http-equiv="content-Type" content="text/plain; charset=utf-8" />)");
        res.write(u8"</head><body>");
        res.write(u8R"({"msg":"success"})");
        res.end(u8"</body></html>");
    });

    app.route("/topic/add", [](cinatra::Request& req, cinatra::Response& res)
    {
        cout << "/topic/add, request data: " << UTF2GBK(req.body()) << endl;

        std::string strRes = "{ "
            "  \"error\" : false "
            ", \"errMsg\" : \"\" "
            ", \"cmd\" : \"modify\" "
            "}";
        cout << "response content: " << strRes << endl;
        res.end(strRes);
    }
    );

    app.route("/topic/init", [](cinatra::Request& req, cinatra::Response& res)
    {
        cout << "/topic/init, request data: " << UTF2GBK(req.body()) << endl;

        // 该数据应该从数据库读取, 这里暂时从文件读取模仿一下
        std::string replyStr = u8"";
        std::ifstream initFile("C:\\Users\\zmm\\Documents\\Visual Studio 2015\\Projects\\xTestCpp11\\ISecExamPaperAddIn\\initForm.json", std::ios::in);
        char buf[1024];
        while (initFile.getline(buf, 1024))
            replyStr += buf;
        cout << "response content: " << replyStr << endl;
        res.end(replyStr);
    }
    );

    app.route("/anwerSheet/gen", [](cinatra::Request& req, cinatra::Response& res) {
        cout << "/anwerSheet/gen, request data: " << UTF2GBK(req.body()) << endl;

        std::string strRes = u8R"({"error" : false , "errMsg" : ""})";
        cout << "response content: " << strRes << endl;
        res.end(strRes);
    }
    );

    app.route("/office/load", [](cinatra::Request& req, cinatra::Response& res) {
        cout << "/office/load, request data: " << UTF2GBK(req.body()) << endl;
        const std::string fileName = req.query().get_val("filename");
        cout << "file name = " << fileName << endl;

        ifstream fs("./static/" + fileName, ios::binary);
        if (!fs)
        {
            res.end("not find file" + fileName);
            return;
        }

        std::string str((std::istreambuf_iterator<char>(fs)), std::istreambuf_iterator<char>());
        res.end(str);
    }
    );

    app.route("/office/save", [](cinatra::Request& req, cinatra::Response& res) {        
        // 保存word 文档
        cout << "/office/save..." << endl;

        std::string strTmp;

        if (req.method() != cinatra::Request::method_t::POST)
        {
            strTmp = "upload failed: method is not POST";
            cout << strTmp << endl;
            return;
        }

        std::vector<cinatra::item_t> items;
        if (!cinatra::data_body_parser(req, items))
        {
            strTmp = "upload failed: data_body_parser";
            cout << strTmp << endl;
            res.end(strTmp);
            return;
        }

        for (auto& item : items)
        {
            if (!item.is_file)
            {
                std::cout << "field name: " << item.content_disposition.get_val("name") << ", value: " << item.data << std::endl;
                continue;
            }
            std::ofstream out("./static/test2.docx", std::ios::binary | std::ios::trunc);
            if (!out || !out.write(item.data.data(), item.data.size()))
            {
                strTmp = "upload failed: ofstream";
                cout << strTmp << endl;
                res.end(strTmp);
                return;
            }
        }
        strTmp = "upload succeed";
        res.end(strTmp);
    }
    );

    cout << "web server is running..." << endl;
    app.static_dir("./static");
    app.listen("0.0.0.0", "8080");
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