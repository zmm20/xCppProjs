//#define MAIN
#ifdef MAIN

#include <iostream>
#include <cstdlib>
#include <codecvt>
#include <locale>
#include <exception>
#include <vector>
#include <cctype>
using namespace std;


/*
ע��: �뿴<<c++ ��׼�� (�ڶ���)>>924ҳ
codecvt �� ctype facet �ĳ�Ա����widen() ��narrow() �ܲ�ͬ.

codecvt ����ʹ�ö��char ����һ��wchar_t (��֮),
ctype �������ǽ�ĳ�ֱ����µ�ĳ���ַ�ת��Ϊ��һ�ֱ����µĶ�Ӧ�ַ�(������ܵĻ�).
*/

// convert string to wstring
std::wstring to_wstring(const std::string& str, const std::locale& loc = std::locale());
// convert wstring to string with ��?�� as default character
std::string to_string(const std::wstring& str, const std::locale& loc = std::locale());
// convert UTF-8 string to wstring
std::wstring utf8_to_wstring(const std::string& str);
// convert wstring to UTF-8 string
std::string wstring_to_utf8(const std::wstring& str);


/// ��gbk����, ת��Ϊutf8����
///
/// @author zhoumanman888@126.com
std::string GBK2UTF(const std::string& src) noexcept
{
#ifdef _MSC_VER
    const string localeName = "CHS"; // ".936";
#else
    const string localeName = "zh_CN.GBK";
#endif
    try
    {
        //std::wstring ws = to_wstring(src, std::locale(localeName));
        wstring_convert<codecvt_byname<wchar_t, char, mbstate_t>> cv1(new codecvt_byname<wchar_t, char, mbstate_t>(localeName));
        const std::wstring ws = cv1.from_bytes(src);

        std::wstring_convert<std::codecvt_utf8<wchar_t>> myconv;
        return myconv.to_bytes(ws);
    }
    catch (std::exception& e)
    {
        fprintf(stderr, "GBK2UTF %s\n", e.what());
        return src;
    }
}

/// ��utf8����, ת��Ϊgbk����
///
/// @author zhoumanman888@126.com
std::string UTF2GBK(const std::string& src) noexcept
{
#ifdef _MSC_VER
    const string localeName = "CHS"; //".936";
#else
    const string localeName = "zh_CN.GBK";
#endif
    try
    {
        std::wstring_convert<std::codecvt_utf8<wchar_t>> myconv;
        const std::wstring ws = myconv.from_bytes(src);

        wstring_convert<codecvt_byname<wchar_t, char, mbstate_t>> cv(new codecvt_byname<wchar_t, char, mbstate_t>(localeName));
        return cv.to_bytes(ws);
    }
    catch (std::exception& e)
    {
        fprintf(stderr, "UTF2GBK %s\n", e.what());
        return src;
    }
}
int main()
{
    cout << "test 1" << endl;
    {
        std::locale loc;
        std::string s = "hello world";
        for (char& c : s)
            c = std::use_facet<std::ctype<char>>(loc).toupper(c);
        cout << s << endl;
    }
    cout << endl;

    cout << "test 2" << endl;
    {
        std::string s = "���\n";
        std::wstring ws = to_wstring(s);
        std::wcout << ws;
        std::cout << to_string(ws);
    }
    cout << endl;

    cout << "test 3" << endl;
    {
        std::locale loc;
        char c = 'a';
        if (std::isalpha(c, loc) && std::islower(c, loc))
        {
            const char C = std::toupper(c, loc);
            cout << c << " => " << C << endl;
        }

        // cctype �ж���ĺ���ֻ��һ������
        // ������c �����еĺ���, ����c���԰汾ֻ���ж�ֵ�� 0~255, �����ֽ�(�纺��)������255
        c = 'A';
        if (std::isalpha(c) && std::isupper(c))
        {
            const char lower = std::tolower(c, loc);
            cout << c << " => " << lower << endl;
        }
    }
    cout << endl;

    cout << "test 4" << endl;
    {
        try {
#ifdef _MSC_VER
            // string with German umlaut and euro symbol (in Windows encoding):
            std::string s = "nj: ��a + \x80 1";
            // convert to wide-character string (using Windows encoding):
            std::wstring ws = to_wstring(s, std::locale("deu_DEU.1252"));
#else
            // string with German umlaut and euro symbol (in ISO Latin-15 encoding):
            std::string s = "nj: ��a + \xA4 1";
            // convert to wide-character string (using ISO Latin-15 encoding):
            std::wstring ws = to_wstring(s, std::locale("de_DE.ISO-8859-15"));
#endif
            // print string as UTF-8 sequence:
            std::cout << wstring_to_utf8(ws) << std::endl;

            cout << endl;
            string str_gbk = "���";
            string str_utf8 = u8"���";
            cout << "gbk: " << str_gbk << ", utf8:" << str_utf8 << endl;
            cout << "gbk=>utf8: " << GBK2UTF(str_gbk) << endl;
            cout << "utf8=>gbk: " << UTF2GBK(str_utf8) << endl;

            ws = to_wstring(str_gbk, std::locale(".936"));
            if (ws == L"���")
                wcout << L"ok" << endl;
            else
                wcout << L"false" << endl;
        }
        catch (const std::exception& e) {
            std::cerr << "Exception: " << e.what() << std::endl;
            return EXIT_FAILURE;
        }
    }
    cout << endl;

    cout << "test 5" << endl;
    {
        string str = "һ�������";
        wstring wstr1 = L"һ�������";
        wstring wstr2 = to_wstring(str);
        cout << "sizeof str = " << sizeof str << ", .size = " << str.size() << endl;
        cout << "sizeof wstr1 = " << sizeof wstr1 << ", .size = " << wstr1.size() << endl;
        cout << "sizeof wstr2 = " << sizeof wstr2 << ", .size = " << wstr2.size() << endl;

        locale loc("CHS");
        wcout.imbue(loc); // ע��, ���û�и�װ�ض���, ���޷���ʾ
        wcout << L"old string: " << wstr1 << endl << L"new string: ";
        for (const auto c : wstr1)
        {
            if (std::isalpha(c, loc))
                wcout << c << L"";
        }
        cout << endl;
    }
    cout << endl;

    return EXIT_SUCCESS;
}

// convert string to wstring
std::wstring to_wstring(const std::string& str, const std::locale& loc)
{
    std::vector<wchar_t> buf(str.size());
    std::use_facet<std::ctype<wchar_t>>(loc).widen(str.data(), str.data() + str.size(), buf.data());
    return std::wstring(buf.data(), buf.size());
}
// convert wstring to string with ��?�� as default character
std::string to_string(const std::wstring& str, const std::locale& loc)
{
    std::vector<char> buf(str.size());
    std::use_facet<std::ctype<wchar_t>>(loc).narrow(str.data(), str.data() + str.size(), '?', buf.data());
    return std::string(buf.data(), buf.size());
}

// convert UTF-8 string to wstring
std::wstring utf8_to_wstring(const std::string& str)
{
    std::wstring_convert<std::codecvt_utf8<wchar_t>> myconv;
    return myconv.from_bytes(str);
}

// convert wstring to UTF-8 string
std::string wstring_to_utf8(const std::wstring& str)
{
    std::wstring_convert<std::codecvt_utf8<wchar_t>> myconv;
    return myconv.to_bytes(str);
}
#endif