#define MAIN
#ifdef MAIN

#include <iostream>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/date_time.hpp>
#include <string>
#include <json/json.h>
using namespace std;

using namespace boost::property_tree;
using namespace boost::gregorian;
using namespace boost;

int main()
{
    cout << "test 1" << endl;
    {
        string strJson = 
            R"({ "people": [
                    { "firstName": "Brett", "lastName" : "McLaughlin", "email" : "aaaa" }, 
                    { "firstName": "Jason", "lastName" : "Hunter", "email" : "bbbb" },
                    { "firstName": "Elliotte", "lastName" : "Harold", "email" : "cccc" }
                  ] 
               })";

        ptree pt, p1, p2;
        stringstream stream;

        stream << strJson;
        read_json<ptree>(stream, pt);
        p1 = pt.get_child("people");
        cout << "array size: " << p1.size() << endl;
        for (boost::property_tree::ptree::iterator it = p1.begin(); it != p1.end(); ++it)
        {
            p2 = it->second; //first为空

            try
            {
                p2.get<string>("fi");
            }
            catch (const std::exception& e)
            {
                cout << "error: "<< e.what() << endl;
            }
            
            cout << "firstName: " << p2.get<string>("firstName")
                << ", lastName: " << p2.get<string>("lastName")
                << ", email: " << p2.get<string>("email") << endl;
        }
    }
    cout << endl;

    cout << "test 2" << endl;
    {
        string strJson = R"({ "people": ["firstName", "lastName", "email中国"]})";

        ptree pt, p1, p2;
        stringstream stream;

        stream << strJson;
        read_json<ptree>(stream, pt);
        p1 = pt.get_child("people");
        cout << "array size: " << p1.size() << endl;
        for (boost::property_tree::ptree::iterator it = p1.begin(); it != p1.end(); ++it)
        {
            p2 = it->second; //first为空
            cout << p2.get_value<string>() << endl;
        }
    }
    cout << endl;


    cout << "test 3" << endl;
    {
        // 测试 JsonCpp 的数据用boost 解析
        Json::Value root;
        root["type"] = 0;
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

        // 无格式json字符串 
        Json::FastWriter writer;
        std::string strTmp = writer.write(root);
        cout << "no format: " << endl
            << strTmp.c_str() << endl;


        // 用boost 解析
        ptree pt, p1, p2;
        stringstream stream;

        stream << strTmp;
        read_json<ptree>(stream, pt);
        p1 = pt.get_child("resultSet");
        cout << "array size: " << p1.size() << endl;
        for (boost::property_tree::ptree::iterator it = p1.begin(); it != p1.end(); ++it)
        {
            p2 = it->second; //first为空
            cout << p2.get<string>("ip") << endl;
        }
    }
    cout << endl;

    cout << "test 4" << endl;
    {
        //std::string src = R"({"images":["Abcdefghijklmnopqrstuvwxyz 中国你好 123456  Abcedfghijklmnopqrstuvwxyz 123456789           ","       打印服务器管理 语文, 数学, 英语, 生物, 化学  ","感谢电子工业出版杜博文视点的陈晓猛和丁一琼编辑为本书的出版所做的大\n量的工作】 他们对出版物的专业和严谨的态度给我留下了深刻的印象。\n\n最后, 需要感谢我博客上的众多读者们， 是你们对这本书的期待和热情的留\n言让我有了完成这本书的动力和勇气。\n\n交流与勘误\n\n由于编者水平有限′ 书籍即使经过了多次的校对， 也难免会有疏漏之处。 希\n望书本前的你， 能够热心地指出书本中错误， 以便在这本书下一版印刷的时候y\n能以]个更完美更严谨的样子' 呈现在大家的面前。 另外】 你要相信你不是]个\n人在战斗' 在作者的博客中， 可以找到与自己志同道合的众多喜欢计算机视觉编\n程技术的爱好者们。 我们可以一同交流, 共同学习迸步。\n\nVII\n\n"]})";
        std::string src = R"({"images":["Abcdefghijklmnopqrstuvwxyz 中国你好 123456  Abcedfghijklmnopqrstuvwxyz 123456789           ","       打印服务器管理 语文, 数学, 英语, 生物, 化学  ","感谢电子工业出版杜博文视点的陈晓猛和丁一琼编辑为本书的出版所做的大\n量的工作】 他们对出版物的专业和严谨的态度给我留下了深刻的印象。\n\n最后, 需要感谢我博客上的众多读者们， 是你们对这本书的期待和热情的留\n言让我有了完成这本书的动力和勇气。\n\n交流与勘误\n\n由于编者水平有限′ 书籍即使经过了多次的校对， 也难免会有疏漏之处。 希\n望书本前的你， 能够热心地指出书本中错误， 以便在这本书下一版印刷的时候y\n能以]个更完美更严谨的样子' 呈现在大家的面前。 另外】 你要相信你不是]个\n人在战斗' 在作者的博客中， 可以找到与自己志同道合的众多喜欢计算机视觉编\n程技术的爱好者们。 我们可以一同交流, 共同学习迸步。"]})";
        // 用boost 解析
        ptree pt, p1, p2;
        stringstream stream;

        stream << src;
        try
        {
            read_json<ptree>(stream, pt);
        }
        catch (const std::exception& e)
        {
            cerr << e.what() << endl;
            return 1;
        }
        
        p1 = pt.get_child("images");
        cout << "array size: " << p1.size() << endl;
        for (boost::property_tree::ptree::iterator it = p1.begin(); it != p1.end(); ++it)
        {
            p2 = it->second; //first为空
            cout << p2.get_value<string>() << endl;
        }

    }
    cout << endl;

    return EXIT_SUCCESS;
}

#endif