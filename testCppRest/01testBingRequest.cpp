//#define MAIN
#ifdef MAIN

#include <cpprest/http_client.h>
#include <cpprest/filestream.h>
#include <iostream>

using namespace utility;                    // Common utilities like string conversions
using namespace web;                        // Common features like URIs.
using namespace web::http;                  // Common HTTP functionality
using namespace web::http::client;          // HTTP client features
using namespace concurrency::streams;       // Asynchronous streams
using std::wcout;
using std::endl;
void TestRequest()
{// �����汾: 
    auto fileStream = std::make_shared<concurrency::streams::ostream>();
    concurrency::streams::ostream outFile = concurrency::streams::fstream::open_ostream(U("result11.html")).get();
    *fileStream = outFile;

    http_client client(L"http://www.bing.com/");
    uri_builder builder(L"/search");
    builder.append_query(L"q", L"Casablanca CodePlex");
    wcout << builder.to_string() << endl;

    http_response response = client.request(methods::GET, builder.to_string()).get();
    response.body().read_to_end(fileStream->streambuf()).get();
    fileStream->close().get();
}


#ifdef _WIN32
int wmain(int argc, wchar_t *args[])
#else
int main(int argc, char *args[])
#endif
{
    /*
        https://github.com/Microsoft/cpprestsdk/wiki/Getting-Started-Tutorial
        http://www.cnblogs.com/qicosmos/archive/2014/11/14/4098094.html
    ��   ������ӰѴ�bing.com�ϲ�ѯ��Casablanca CodePlex�������ݱ��浽һ�������ļ�result.html�У��õ���ppl�Ĵ�������
        �������ĸ��첽���񣬵�һ�������Ǵ�һ���ļ��������ţ������˵ڶ����������ڷ���һ����ѯ����
        Ȼ�󣬵���������ȴ��������Ӧ��������Ӧ�Ľ�����뵽�ļ���ȥ��
        ���ĸ������ǹر��ļ�����Ҫע��rest sdk���ַ���ص�����ǿ��ַ���wchr_t��
    */
    auto fileStream = std::make_shared<concurrency::streams::ostream>();
    // Open stream to output file.
    // ��һ������, ���ļ���
    pplx::task<void> requestTask = concurrency::streams::fstream::open_ostream(U("result.html"))
        .then([=](concurrency::streams::ostream outFile) 
    {
        // ��һ��������ɺ����
        *fileStream = outFile;

        // Create http_client to send the request.
        http_client client(U("http://www.bing.com/"));

        // Build request URI and start the request.
        uri_builder builder(U("/search"));
        builder.append_query(U("q"), U("Casablanca CodePlex"));
        wcout << builder.to_string() << endl;
        return client.request(methods::GET, builder.to_string()); // ����ڶ�������, ����һ����ѯ����
    })
        .then([=](http_response response)
    {
        // �ڶ���������ɺ����
        // Handle response headers arriving.
        printf("Received response status code:%u\n", response.status_code());

        // Write response body into the file.
        return response.body().read_to_end(fileStream->streambuf()); // �������������, ����Ӧ������뵽�ļ���ȥ
    }).then([=](size_t len) {
        return fileStream->close(); // ������ĸ�����, �ر��ļ���
    });

    try
    {
        requestTask.wait();
    }
    catch (const std::exception& e)
    {
        std::cout << e.what() << std::endl;
    }
   
    return 0;
}

#endif