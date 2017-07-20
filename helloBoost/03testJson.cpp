//#define MAIN
#ifdef MAIN

#include <iostream>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/date_time.hpp>
#include <string>
#include <my/Texthelper.h>
using namespace std;

using namespace boost::property_tree;
using namespace boost;

int main()
{
    // jsoncpp �� boost ptree �Ա�
    // http://www.cnblogs.com/lidabo/archive/2012/10/31/2748026.html
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
        string strJson = R"({ "people": ["firstName", "lastName", "email"]})";

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
        boost::property_tree::ptree pt_root;
        boost::property_tree::ptree children;
        
        boost::property_tree::ptree child;
        child.put("1", "hello");
        child.put("2", "world");
        children.push_back(std::make_pair("", child));

        // ������д��ʱ, ������ת��utf-8����, ����ᵼ���ڽ����쳣�ж�
        //child.put("1", "���"); // error
        //child.put("2", "����"); // error
        child.put("1", XAB::CTextHelper::GBK2UTF("���")); // ok
        child.put("2", XAB::CTextHelper::GBK2UTF("����")); // ok
        children.push_back(std::make_pair("", child));

        pt_root.add_child("arr", children);

        std::stringstream ss;
        boost::property_tree::write_json(ss, pt_root);
        std::string str = ss.str();
        cout << str << endl;


        ptree pt, p1, p2;
        stringstream stream;
        stream << str;
        read_json<ptree>(stream, pt); // �������Ļ�������, ��ʱ����
        p1 = pt.get_child("arr");
        cout << "array size: " << p1.size() << endl;
        for (boost::property_tree::ptree::iterator it = p1.begin(); it != p1.end(); ++it)
        {
            p2 = it->second; //firstΪ��

            const string s1 = p2.get<string>("1");
            const string s2 = p2.get<string>("2");

            cout << "1 = " << XAB::CTextHelper::UTF2GBK(s1)
                << ", 2 = " << XAB::CTextHelper::UTF2GBK(s2) << endl;
        }
        return 0;
    }
    cout << endl;

   
    return EXIT_SUCCESS;
}

#endif