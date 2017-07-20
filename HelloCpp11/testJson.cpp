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

        // �޸�ʽjson�ַ��� 
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
        string src = R"({"images":["Abcdefghijklmnopqrstuvwxyz �й���� 123456  Abcedfghijklmnopqrstuvwxyz 123456789           ","       ��ӡ���������� ����, ��ѧ, Ӣ��, ����, ��ѧ  ","��л���ӹ�ҵ����Ų����ӵ�ĳ����ͺͶ�һ��༭Ϊ����ĳ��������Ĵ�\n���Ĺ����� ���ǶԳ������רҵ���Ͻ���̬�ȸ�����������̵�ӡ��\n\n���, ��Ҫ��л�Ҳ����ϵ��ڶ�����ǣ� �����Ƕ��Ȿ����ڴ����������\n��������������Ȿ��Ķ�����������\n\n�����뿱��\n\n���ڱ���ˮƽ���ޡ� �鼮��ʹ�����˶�ε�У�ԣ� Ҳ���������©֮���� ϣ\n���鱾ǰ���㣬 �ܹ����ĵ�ָ���鱾�д��� �Ա����Ȿ����һ��ӡˢ��ʱ��y\n����]�����������Ͻ�������' �����ڴ�ҵ���ǰ�� ���⡿ ��Ҫ�����㲻��]��\n����ս��' �����ߵĲ����У� �����ҵ����Լ�־ͬ���ϵ��ڶ�ϲ��������Ӿ���\n�̼����İ������ǡ� ���ǿ���һͬ����, ��ͬѧϰ�Ų���\n\nVII\n\n"]})";
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