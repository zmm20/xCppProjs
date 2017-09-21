//#define MAIN
#ifdef MAIN

#include <cpprest/http_client.h> 
#include <cpprest/filestream.h> 
#include <sstream>

using namespace std;
using namespace web::http;
using namespace web::http::client;
using namespace concurrency;
using namespace utility;

pplx::task<void> HTTPGetAsync()
{
    // 参考: http://blog.jobbole.com/53642/
    // I want to make the following HTTP GET: http://api.flickr.com/services/rest/?method=flickr.test.echo&name=value
    /*
        http_client client(U("http://api.flickr.com/services/rest/"));
        uri_builder builder;
        builder.append_query(U("method"), U("flickr.test.echo"));
        builder.append_query(U("name"), U("value"));
    */

    http_client client(U("http://192.168.4.162:8080"));

    uri_builder builder;
    // test 1
    //builder.append_path(U("/index.html"));

    builder.append_path(U("/test"));
    builder.append_query(U("name"), U("zhou"));
    auto path_query_fragment = builder.to_string();
    wcout << path_query_fragment << endl;


    // Make an HTTP GET request and asynchronously process the response
    return client.request(methods::GET, path_query_fragment).then([](http_response response)
    {
        // Display the status code that the server returned
        std::wostringstream stream;
        stream << L"Server returned returned status code " << response.status_code() << L'.' << std::endl;
        std::wcout << stream.str();

        stream.str(std::wstring());
        stream << L"Content type: " << response.headers().content_type() << std::endl;
        stream << L"Content length: " << response.headers().content_length() << L"bytes" << std::endl;
        std::wcout << stream.str();

        try
        {
            web::json::value v = response.extract_json(false).get();
            // Perform actions here to process the JSON value...
            wcout << "json data: " << v.to_string() << endl;
        }
        catch (const http_exception& e)
        {
            // Print error.
            wostringstream ss;
            ss << e.what() << endl;
            wcout << ss.str();
        }


        auto bodyStream = response.body();
        streams::stringstreambuf sbuffer;
        auto& target = sbuffer.collection();

        bodyStream.read_to_end(sbuffer).get();

        stream.str(std::wstring());
        stream << L"Response body: " << target.c_str();
        std::wcout << stream.str();
    });
}

int main()
{
    cout << "test 1 " << endl;
    {
        http_client cli(U("http://www.baidu.com"));

        //uri_builder builder(U("/s"));
        //builder.append_query(U("wd"), U("meinv"));
        //wcout << builder.to_string() << endl;
        //auto response = cli.request(methods::GET, builder.to_string());

        // get方式请求服务  
        auto response = cli.request(methods::GET, U("s?wd=123"));
        
        // 指定一个回调函数，也就是匿名函数（lambda）  
        auto task = response.then([](http_response hr)
        {
            cout << "status code: " << hr.status_code() << endl;

            std::wcout << L"Content type: " << hr.headers().content_type() << std::endl;
            std::wcout << L"Content length: " << hr.headers().content_length() << L"bytes" << std::endl;
        });

        cout << "begin wait..." << endl;
        // 阻塞，等待请求完成  
        task.wait();
    }
    cout << endl;

    cout << "test 2" << endl;
    {
        std::wcout << L"Calling HTTPGetAsync..." << std::endl;
        // In this case, I call wait. However, you won’t usually want to wait for the asynchronous operations
        HTTPGetAsync().wait();
    }
    cout << endl;

    return 0;
}


#endif