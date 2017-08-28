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
{// 阻塞版本: 
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
    　   这个例子把从bing.com上查询“Casablanca CodePlex”的内容保存到一个本地文件result.html中，用到了ppl的串行任务。
        启用了四个异步任务，第一个任务是打开一个文件流，接着，发起了第二个任务，用于发起一个查询请求，
        然后，第三个任务等待请求的响应，并将响应的结果输入到文件中去，
        第四个任务是关闭文件流。要注意rest sdk的字符相关的入参是宽字符（wchr_t）
    */
    auto fileStream = std::make_shared<concurrency::streams::ostream>();
    // Open stream to output file.
    // 第一个任务, 打开文件流
    pplx::task<void> requestTask = concurrency::streams::fstream::open_ostream(U("result.html"))
        .then([=](concurrency::streams::ostream outFile) 
    {
        // 第一个任务完成后进入
        *fileStream = outFile;

        // Create http_client to send the request.
        http_client client(U("http://www.bing.com/"));

        // Build request URI and start the request.
        uri_builder builder(U("/search"));
        builder.append_query(U("q"), U("Casablanca CodePlex"));
        wcout << builder.to_string() << endl;
        return client.request(methods::GET, builder.to_string()); // 发起第二个任务, 发起一个查询请求
    })
        .then([=](http_response response)
    {
        // 第二个任务完成后进入
        // Handle response headers arriving.
        printf("Received response status code:%u\n", response.status_code());

        // Write response body into the file.
        return response.body().read_to_end(fileStream->streambuf()); // 发起第三个任务, 将响应结果输入到文件中去
    }).then([=](size_t len) {
        return fileStream->close(); // 发起第四个任务, 关闭文件流
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