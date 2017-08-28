#define MAIN
#ifdef MAIN

//#include <cpprest/containerstream.h>
#include <cpprest/json.h>
#include <iostream>
#include <sstream>

using namespace std;
using namespace web;

int wmain()
{
    // Create a JSON object.
    json::value obj;
    obj[L"key1"] = json::value::boolean(false);
    obj[L"key2"] = json::value::number(44);
    obj[L"key3"] = json::value::number(43.6);
    obj[L"key4"] = json::value::string(U("str"));

    std::wcout << obj << endl;

    //// Loop over each element in the object.
    //for (auto iter = obj.cbegin(); iter != obj.cend(); ++iter)
    //{
    //    // Make sure to get the value as const reference otherwise you will end up copying
    //    // the whole JSON value recursively which can be expensive if it is a nested object.
    //    const json::value &str = iter->first;
    //    const json::value &v = iter->second;

    //    // Perform actions here to process each string and value in the JSON object...
    //    std::wcout << L"String: " << str.as_string() << L", Value: " << v.to_string() << endl;
    //}
}
#endif