//#define MAIN
#ifdef MAIN

//#include <cpprest/containerstream.h>
#include <cpprest/json.h>
#include <iostream>
#include <sstream>

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
            wcout << "errmsg = " << obj.at(U("errmsg")).as_string();
        }
        catch (const std::exception& e)
        {
            cerr << "error : " << e.what() << endl;
        }
    }
    cout << endl;
    
}
#endif