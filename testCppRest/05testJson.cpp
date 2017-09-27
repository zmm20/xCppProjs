#define MAIN
#ifdef MAIN

//#include <cpprest/containerstream.h>
#include <cpprest/json.h>
#include <iostream>
#include <sstream>
#include <my/TextHelper.h>

using namespace std;
using namespace web;

int wmain()
{
    cout << "test 1" << endl;
    {
        // Create a JSON object.
        json::value obj;
        obj[L"key1"] = json::value::boolean(false);
        obj[L"key2"] = json::value::number(44);
        obj[L"key3"] = json::value::number(43.6);
        obj[L"key4"] = json::value::string(U("str"));

        std::vector<json::value> arr;
        json::value subObj;
        subObj[L"subKey"] = json::value::number(1);
        arr.push_back(subObj);

        subObj[L"subKey"] = json::value::number(2);
        arr.push_back(subObj);

        subObj[L"subKey"] = json::value::number(2);
        arr.push_back(subObj);

        obj[L"key5"] = json::value::array(arr);

        std::wcout << obj << endl;

        std::wcout << "key1 = " << obj[L"key1"].as_bool() << endl;
        std::wcout << "key2 = " << obj[L"key2"].as_integer() << endl;
        std::wcout << "key3 = " << obj[L"key3"].as_double() << endl;
        std::wcout << "key4 = " << obj[L"key4"].as_string() << endl;
    }
    cout << endl;

    cout << "test 2" << endl;
    {
        json::value obj = json::value::parse(U(R"({"result":1, "errmsg":"用户名或密码错误"})"));

        wcout.imbue(std::locale("chs"));
        wcout << obj << endl;

        wstring str = obj.serialize();
        wcout << "serialize = " << str << endl;
        try
        {
            cout << "result = " << obj.at(U("result")).as_integer() << endl;
            wcout << "errmsg = " << obj.at(U("errmsg")).as_string() << endl;
        }
        catch (const std::exception& e)
        {
            cerr << "error : " << e.what() << endl;
        }
        
    }
    cout << endl;

    cout << "test 3" << endl;
    {
        // 可见, json 解析之后, 自动把utf-8 转化为本地字符集(gbk)
        const string u8str = u8R"({"result":1, "errmsg":"用户名或密码错误"})";
        json::value obj = json::value::parse(std::stringstream(u8str));

        wcout.imbue(std::locale("chs"));
        wcout << obj << endl;
        try
        {
            cout << "result = " << obj.at(U("result")).as_integer() << endl;
            wcout << "errmsg = " << obj.at(U("errmsg")).as_string() << endl;
        }
        catch (const std::exception& e)
        {
            cerr << "error : " << e.what() << endl;
        }
    }
    cout << endl;
    
    // 以下几个例子来自 https://github.com/Microsoft/cpprestsdk/wiki/JSON
    cout << "test 4 Construction" << endl;
    {
        json::value v0 = json::value::null();
        json::value v1 = json::value::number(17);
        json::value v2 = json::value::number(3.1415);
        json::value v3 = json::value::boolean(true);
        json::value v4 = json::value::string(U("Hello Again!"));
        json::value v5 = json::value::object();
        json::value v6 = json::value::array();

        wcout << "v0 = " << v0.serialize() << endl;
        wcout << "v1 = " << v1.serialize() << endl;
        wcout << "v2 = " << v2.serialize() << endl;
        wcout << "v3 = " << v3.serialize() << endl;
        wcout << "v4 = " << v4.serialize() << endl;
        wcout << "v5 = " << v5.serialize() << endl;
        wcout << "v6 = " << v6.serialize() << endl;
    }
    cout << endl;

    cout << "test 5 Parsing and Serializing" << endl;
    {
        utility::stringstream_t ss1;
        ss1 << U("17");//U(R"({"country":"中国"})");
        json::value v1 = json::value::parse(ss1);
        wcout << "v1 serialize: " << v1.serialize() << endl;

        utility::stringstream_t stream;
        json::value v2 = json::value::string(U("Hi"));
        v2.serialize(stream);
        wcout << "v2 serialize: " << stream.str() << endl;
    }
    cout << endl;

    cout << "test 6 Accessing Data" << endl;
    {
        json::value v1 = json::value::number(17);
        json::value v2 = json::value::number(3.1415);
        json::value v3 = json::value::boolean(true);
        json::value v4 = json::value::string(U("Hello Again!"));

        int i = v1.as_integer();
        double d = v2.as_double();
        bool b = v3.as_bool();
        utility::string_t s = v4.as_string();

        json::value obj = json::value::parse(U("{ \"a\" : 10 }"));
        obj[U("a")] = json::value(12);
        obj[U("b")] = json::value(13);
        auto nullValue = obj[U("c")];
        wcout << obj.serialize() << endl;

        try
        {
            json::value obj = json::value::parse(U("{ \"a\" : 10 }"));
            auto aValue = obj.at(U("a"));
            auto bValue = obj.at(U("b"));
        }
        catch (json::json_exception& e)
        {
            wcout << "error : " << e.what() << endl;
        }
    }
    cout << endl;

    // 以下是我自己测试
    cout << "test 7" << endl;
    {
        std::string replyStr = u8"";
        std::ifstream initFile("C:\\Users\\zmm\\Documents\\Visual Studio 2015\\Projects\\xCppProjs\\ISecExamPaperAddIn\\initAll.json", std::ios::in);
        char buf[1024];
        while (initFile.getline(buf, 1024))
            replyStr += buf;
        //cout << "response content(show in gbk): " << XAB:: TextHelper::UTF2GBK(replyStr) << endl;

        try
        {
            json::value root = json::value::parse(stringstream(replyStr));
            cout << "parse ok" << endl;

            json::array kenoledges = root.at(L"knowledgePoints").as_array();
            for (auto obj : kenoledges)
            {
                if (!obj.has_field(U("subjectId")))
                    continue;

                cout << "---------obj begin------------" << endl;
                wcout << "id =" << obj.at(U("id")).as_string() << endl;
                wcout << "pId =" << obj.at(U("pId")).as_string() << endl;
                wcout << "name =" << obj.at(U("name")).as_string() << endl;
                wcout << "subjectId =" << obj.at(U("subjectId")).as_string() << endl;
                wcout << "stage =" << obj.at(U("stage")).as_string() << endl;
                cout << "---------obj end------------" << endl;
            }
        }
        catch (const exception& e)
        {
            cerr << "error: " << e.what() << endl;
        }
    }

}
#endif