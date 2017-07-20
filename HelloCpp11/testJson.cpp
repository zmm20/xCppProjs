//#define MAIN
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

        // 无格式json字符串 
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

    cout << "test 3" << endl;
    {
        string src = R"({"images":["Abcdefghijklmnopqrstuvwxyz 中国你好 123456  Abcedfghijklmnopqrstuvwxyz 123456789           ","       打印服务器管理 语文, 数学, 英语, 生物, 化学  ","感谢电子工业出版杜博文视点的陈晓猛和丁一琼编辑为本书的出版所做的大\n量的工作】 他们对出版物的专业和严谨的态度给我留下了深刻的印象。\n\n最后, 需要感谢我博客上的众多读者们， 是你们对这本书的期待和热情的留\n言让我有了完成这本书的动力和勇气。\n\n交流与勘误\n\n由于编者水平有限′ 书籍即使经过了多次的校对， 也难免会有疏漏之处。 希\n望书本前的你， 能够热心地指出书本中错误， 以便在这本书下一版印刷的时候y\n能以]个更完美更严谨的样子' 呈现在大家的面前。 另外】 你要相信你不是]个\n人在战斗' 在作者的博客中， 可以找到与自己志同道合的众多喜欢计算机视觉编\n程技术的爱好者们。 我们可以一同交流, 共同学习迸步。\n\nVII\n\n"]})";
        Json::Value root;
        Json::Reader reader;
        bool ok = reader.parse(src, root);
        if (ok)
        {
            if (!root.isMember("images"))
                return -1;

            Json::Value imgs = root["images"];
            for (int i = 0; i < imgs.size(); ++i)
            {
                cout << imgs[i].asString() << endl;
            }
        }
    }
    cout << endl;
}
#endif