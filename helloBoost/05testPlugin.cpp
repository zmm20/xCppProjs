//#define MAIN
#ifdef MAIN

#include <iostream>
#include <boost/dll.hpp>
#include <boost/function.hpp>
#include "my_plugin_api.hpp"
#include "../my_plugin_static/static_plugin.hpp"
#include <string>
#include <vector>
#include <Windows.h>

namespace dll = boost::dll;
using namespace std;

std::size_t search_for_symbols(const std::vector<boost::filesystem::path>& plugins);

int main()
{
#ifdef _DEBUG
    string dllPath = R"(C:\Users\zmm\Documents\Visual Studio 2015\Projects\xCppProjs\Debug)";
#else
    string dllPath = R"(C:\Users\zmm\Documents\Visual Studio 2015\Projects\xCppProjs\Release)";
#endif
    cout << "test 1 " << endl;
    {
        boost::filesystem::path lib_path(dllPath);          // argv[1] contains path to directory with our plugin library
        boost::shared_ptr<my_plugin_api> plugin;            // variable to hold a pointer to plugin variable
        std::cout << "Loading the plugin" << std::endl;

        plugin = dll::import<my_plugin_api>(          // type of imported symbol is located between `<` and `>`
            lib_path / "my_plugin_sum.dll",                     // path to the library and library name
            "plugin",                                       // name of the symbol to import
            dll::load_mode::append_decorations              // makes `libmy_plugin_sum.so` or `my_plugin_sum.dll` from `my_plugin_sum`
            );

        std::cout << "plugin->calculate(1.5, 1.5) call:  " << plugin->calculate(1.5, 1.5) << std::endl;
    }
    cout << endl;

    cout << "test 2" << endl;
    {
        boost::filesystem::path shared_library_path(dllPath);               // argv[1] contains path to directory with our plugin library
        shared_library_path /= "my_plugin_aggregator";
        typedef boost::shared_ptr<my_plugin_api>(pluginapi_create_t)(); // 定义一个返回类型为只能指针的函数指针
        std::function<pluginapi_create_t> creator;

        creator = boost::dll::import_alias<pluginapi_create_t>(             // type of imported symbol must be explicitly specified
            shared_library_path,                                            // path to library
            "create_plugin",                                                // symbol to import
            dll::load_mode::append_decorations                              // do append extensions and prefixes
            );

        boost::shared_ptr<my_plugin_api> plugin = creator();
        std::cout << "plugin->calculate(1.5, 1.5) call:  " << plugin->calculate(1.5, 1.5) << std::endl;
        std::cout << "plugin->calculate(1.5, 1.5) second call:  " << plugin->calculate(1.5, 1.5) << std::endl;
        std::cout << "Plugin Name:  " << plugin->name() << std::endl;
    }
    cout << endl;

    cout << "test 3, 遍历多插件符号" << endl;
    {
        boost::filesystem::path lib_path(dllPath);
        std::vector<boost::filesystem::path> dllPathVec;
        dllPathVec.push_back(lib_path / "my_plugin_sum.dll");
        dllPathVec.push_back(lib_path / "my_plugin_aggregator.dll");

        search_for_symbols(dllPathVec);
    }
    cout << endl;

    cout << "test 4, 测试静态库" << endl;
    {// 注意, 使用这种方式时, 必须包含静态库的头, 否则会报错
        try
        {
            dll::shared_library self(dll::program_location());
            cout << "program_location = " << dll::program_location() << endl;

            std::cout << "Call function" << std::endl;
            std::function<boost::shared_ptr<my_plugin_api>()> creator
                = self.get_alias<boost::shared_ptr<my_plugin_api>()>("create_plugin");

            std::cout << "Computed Value: " << creator()->calculate(2, 2) << std::endl;
            {
                // This block is invisible for Quickbook documentation
                float res = creator()->calculate(10, 10);
                if (!(res > -0.0001 && res < 0.00001)) {
                    throw std::runtime_error("Failed check: res > -0.0001 && res < 0.00001");
                }
            }
        }
        catch (const std::exception& e)
        {
            cout << e.what() << endl;
        }
        
    }
    cout << endl;

    cout << "test 5" << endl;
    {
        // function signature with calling convention
        typedef HANDLE(__stdcall GetStdHandle_t)(DWORD);

        // OPTION #0, requires C++11 compatible compiler that understands GetStdHandle_t signature.
        auto get_std_handle = dll::import<GetStdHandle_t>(
            "Kernel32.dll",
            "GetStdHandle",
            boost::dll::load_mode::search_system_folders
            );
        std::cout << "0.0 GetStdHandle() returned " << get_std_handle(STD_OUTPUT_HANDLE) << std::endl;

        // You may put the `get_std_handle` into boost::function<>. But boost::function<Signature> can not compile with
        // Signature template parameter that contains calling conventions, so you'll have to remove the calling convention.
        boost::function<HANDLE(DWORD)> get_std_handle2 = get_std_handle;
        std::cout << "0.1 GetStdHandle() returned " << get_std_handle2(STD_OUTPUT_HANDLE) << std::endl;


        // OPTION #1, does not require C++11. But without C++11 dll::import<> can not handle calling conventions,
        // so you'll need to hand write the import.
        dll::shared_library lib("Kernel32.dll", dll::load_mode::search_system_folders);
        GetStdHandle_t& func = lib.get<GetStdHandle_t>("GetStdHandle");

        // Here `func` does not keep a reference to `lib`, you'll have to deal with that on your own.
        std::cout << "1.0 GetStdHandle() returned " << func(STD_OUTPUT_HANDLE) << std::endl;

    }
    cout << endl;

    return 0;
}

std::size_t search_for_symbols(const std::vector<boost::filesystem::path>& plugins) {
    std::size_t plugins_found = 0;

    for (std::size_t i = 0; i < plugins.size(); ++i) {
        std::cout << "Loading plugin: " << plugins[i] << '\n';
        dll::shared_library lib(plugins[i], dll::load_mode::append_decorations);
        if (!lib.has("create_plugin")) {
            // no such symbol
            continue;
        }

        // library has symbol, importing...
        typedef boost::shared_ptr<my_plugin_api>(pluginapi_create_t)();
        std::function<pluginapi_create_t> creator = dll::import_alias<pluginapi_create_t>(boost::move(lib), "create_plugin");

        std::cout << "Matching plugin name: " << creator()->name() << std::endl;
        ++plugins_found;
    }

    return plugins_found;
}

#endif