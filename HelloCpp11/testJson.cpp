#define MAIN
#ifdef MAIN

#include <iostream>
#include <memory>
#include <json/json.h>

using namespace std;


int main()
{
    cout << "----------testJson.cpp----------" << endl;

    cout << "test 1" << endl;
    {
        Json::Value root;
        root["type"] = 0;
        root["cmd"] = 0;
        root["state"] = 0;
        root["errMsg"] = "test";

        Json::Value arr;
        Json::Value subItem;
        subItem["freeRule"] = 1;
        subItem["ip"] = "192.1681.100";
        subItem["mask"] = "255.255.255.255";
        arr.append(subItem);

        subItem["freeRule"] = 2;
        subItem["ip"] = "192.1681.101";
        subItem["mask"] = "255.255.255.255";
        arr.append(subItem);

        subItem["freeRule"] = 3;
        subItem["ip"] = "192.1681.102";
        subItem["mask"] = "255.255.255.255";
        arr.append(subItem);

        root["resultSet"] = arr;

        float aa = 0.1f;
        root["float"] = aa;

        cout << "style format: " << endl
            << root.toStyledString() << endl << endl;

        // ÎÞ¸ñÊ½json×Ö·û´® 
        Json::FastWriter writer;
        std::string strTmp = writer.write(root);
        cout << "no format: " << endl
            << strTmp.c_str() << endl;
    }
    cout << endl;
    
    cout << "test 2" << endl;
    {
        Json::Value arr;
        arr.append("aaa1");

        Json::Value arr2;
        arr2.append(arr[0].asString());

        Json::Value root;
        root["images"] = arr2;
        cout << root << endl;

    }
    cout << endl;
}
#endif