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
            p2 = it->second; //firstΪ��

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
        string strJson = R"({ "people": ["firstName", "lastName", "email�й�"]})";

        ptree pt, p1, p2;
        stringstream stream;

        stream << strJson;
        read_json<ptree>(stream, pt);
        p1 = pt.get_child("people");
        cout << "array size: " << p1.size() << endl;
        for (boost::property_tree::ptree::iterator it = p1.begin(); it != p1.end(); ++it)
        {
            p2 = it->second; //firstΪ��
            cout << p2.get_value<string>() << endl;
        }
    }
    cout << endl;


    cout << "test 3" << endl;
    {
        // ���� JsonCpp ��������boost ����
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

        // �޸�ʽjson�ַ��� 
        Json::FastWriter writer;
        std::string strTmp = writer.write(root);
        cout << "no format: " << endl
            << strTmp.c_str() << endl;


        // ��boost ����
        ptree pt, p1, p2;
        stringstream stream;

        stream << strTmp;
        read_json<ptree>(stream, pt);
        p1 = pt.get_child("resultSet");
        cout << "array size: " << p1.size() << endl;
        for (boost::property_tree::ptree::iterator it = p1.begin(); it != p1.end(); ++it)
        {
            p2 = it->second; //firstΪ��
            cout << p2.get<string>("ip") << endl;
        }
    }
    cout << endl;

    cout << "test 4" << endl;
    {
        //std::string src = R"({"images":["Abcdefghijklmnopqrstuvwxyz �й���� 123456  Abcedfghijklmnopqrstuvwxyz 123456789           ","       ��ӡ���������� ����, ��ѧ, Ӣ��, ����, ��ѧ  ","��л���ӹ�ҵ����Ų����ӵ�ĳ����ͺͶ�һ��༭Ϊ����ĳ��������Ĵ�\n���Ĺ����� ���ǶԳ������רҵ���Ͻ���̬�ȸ�����������̵�ӡ��\n\n���, ��Ҫ��л�Ҳ����ϵ��ڶ�����ǣ� �����Ƕ��Ȿ����ڴ����������\n��������������Ȿ��Ķ�����������\n\n�����뿱��\n\n���ڱ���ˮƽ���ޡ� �鼮��ʹ�����˶�ε�У�ԣ� Ҳ���������©֮���� ϣ\n���鱾ǰ���㣬 �ܹ����ĵ�ָ���鱾�д��� �Ա����Ȿ����һ��ӡˢ��ʱ��y\n����]�����������Ͻ�������' �����ڴ�ҵ���ǰ�� ���⡿ ��Ҫ�����㲻��]��\n����ս��' �����ߵĲ����У� �����ҵ����Լ�־ͬ���ϵ��ڶ�ϲ��������Ӿ���\n�̼����İ������ǡ� ���ǿ���һͬ����, ��ͬѧϰ�Ų���\n\nVII\n\n"]})";
        std::string src = R"({"images":["Abcdefghijklmnopqrstuvwxyz �й���� 123456  Abcedfghijklmnopqrstuvwxyz 123456789           ","       ��ӡ���������� ����, ��ѧ, Ӣ��, ����, ��ѧ  ","��л���ӹ�ҵ����Ų����ӵ�ĳ����ͺͶ�һ��༭Ϊ����ĳ��������Ĵ�\n���Ĺ����� ���ǶԳ������רҵ���Ͻ���̬�ȸ�����������̵�ӡ��\n\n���, ��Ҫ��л�Ҳ����ϵ��ڶ�����ǣ� �����Ƕ��Ȿ����ڴ����������\n��������������Ȿ��Ķ�����������\n\n�����뿱��\n\n���ڱ���ˮƽ���ޡ� �鼮��ʹ�����˶�ε�У�ԣ� Ҳ���������©֮���� ϣ\n���鱾ǰ���㣬 �ܹ����ĵ�ָ���鱾�д��� �Ա����Ȿ����һ��ӡˢ��ʱ��y\n����]�����������Ͻ�������' �����ڴ�ҵ���ǰ�� ���⡿ ��Ҫ�����㲻��]��\n����ս��' �����ߵĲ����У� �����ҵ����Լ�־ͬ���ϵ��ڶ�ϲ��������Ӿ���\n�̼����İ������ǡ� ���ǿ���һͬ����, ��ͬѧϰ�Ų���"]})";
        // ��boost ����
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
            p2 = it->second; //firstΪ��
            cout << p2.get_value<string>() << endl;
        }

    }
    cout << endl;

    return EXIT_SUCCESS;
}

#endif