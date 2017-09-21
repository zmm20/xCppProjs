#define MAIN
#ifdef MAIN

#include <cpprest/http_client.h> 
#include <cpprest/json.h>
#include <sstream>
#include <codecvt>
#include <my/TextHelper.h>


using namespace std;
using namespace web::http;
using namespace web::http::client;
using namespace concurrency;
using namespace utility;

int main()
{
    http_client_config config;


    http_client cli(U("http://192.168.4.162:80"));
    wcout.imbue(std::locale("CHS"));
    wcout << L"�й�" << endl;
    auto onResponse = [](http_response hr)
    {
        wcout << "content: (" << hr.to_string() << ")" << endl;
        wcout << "status code: " << hr.status_code() << endl;
        wcout << L"Content type: " << hr.headers().content_type() << std::endl;
        wcout << L"Content length: " << hr.headers().content_length() << L"bytes" << std::endl;

        if (hr.status_code() != status_codes::OK)
            return;
        // �����Է���, http ͷ���ȴ�������, Ȼ��body �Żᴫ��, ��������� extract_string ����ȴ���дһ���첽����
        //  method 1:
        //std::wstring wU8Str = hr.extract_string().get();
        //std::string u8Str = ::to_string(wU8Str);

        // method 2:
        concurrency::streams::stringstreambuf buffer;
        hr.body().read_to_end(buffer).get();
        std::string& u8Str = buffer.collection();

        
        std::string gbkStr = XAB::CTextHelper::UTF2GBK(u8Str);
        cout << "body: " << gbkStr << endl;
        try
        {
            //wcout << "wbody: " << conversions::to_utf16string(wU8Str) << endl;
        }
        catch (std::exception& e)
        {
            cout << "error : " << e.what() << endl;
        }
        
        //std::wcout << "body: " << conversions::to_string_t(u8Str) << endl;
    };

    cout << "test 1" << endl;
    {
        uri_builder builder;
        builder.append_path(U("/login"));
        wcout << builder.to_string() << endl;

        // http://www.cnblogs.com/qicosmos/p/4098094.html
        // ������������
        auto response = cli.request(methods::POST, builder.to_string(), U("user=zmm&password=e10adc3949ba59abbe56e057f20f883e"), U("application/x-www-form-urlencoded"));
        // ָ��һ���ص�������Ҳ��������������lambda��  
        auto task = response.then(onResponse);

        cout << "begin wait..." << endl;
        // �������ȴ��������  
        task.wait();

    }
    cout << endl;

    cout << "test 2" << endl;
    {
        // ������������
        auto response = cli.request(methods::POST, U("/test"), L"�й�", U("application/x-www-form-urlencoded"));
        // ָ��һ���ص�������Ҳ��������������lambda��  
        auto task = response.then(onResponse); // �����Է���: ��Ȼpost data ����ʱgbk ����, ���Ƿ������յ���ȴ��utf-8 ����

        cout << "begin wait..." << endl;
        // �������ȴ��������  
        task.wait();
    }
    cout << endl;
    

    return EXIT_SUCCESS;

}


#endif

