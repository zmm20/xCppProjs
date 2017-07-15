//#define MAIN
#ifdef MAIN

#include <iostream>
#include <cstdlib>
#include <codecvt>
#include <locale>
#include <exception>
#include <vector>
#include <iomanip>
#include <chrono>
#include <ctime>
using namespace std;

// output operator for pos_format() and neg_format():
ostream& operator<< (ostream& strm, moneypunct<char>::pattern p)
{
    for (int i = 0; i<4; ++i) {
        auto f = p.field[i];
        strm << (f == money_base::none ? "none" :
            f == money_base::space ? "space" :
            f == money_base::symbol ? "symbol" :
            f == money_base::sign ? "sign" :
            f == money_base::value ? "value" :
            "???") << " ";
    }
    return strm;
}
template <bool intl>
void printMoneyPunct(const string& localeName)
{
    locale loc(localeName);
    const moneypunct<char, intl>& mp
        = use_facet<moneypunct<char, intl>>(loc);
    cout << "moneypunct in locale \"" << loc.name() << "\":" << endl;
    cout << " decimal_point: " << (mp.decimal_point() != '\0' ? mp.decimal_point() : ' ') << endl;
    cout << " thousands_sep: " << (mp.thousands_sep() != '\0' ? mp.thousands_sep() : ' ') << endl;
    cout << " grouping: ";
    for (int i = 0; i<mp.grouping().size(); ++i) {
        cout << static_cast<int>(mp.grouping()[i]) << ' ';
    }
    cout << endl;
    cout << " curr_symbol: " << mp.curr_symbol() << endl;
    cout << " positive_sign: " << mp.positive_sign() << endl;
    cout << " negative_sign: " << mp.negative_sign() << endl;
    cout << " frac_digits: " << mp.frac_digits() << endl;
    cout << " pos_format: " << mp.pos_format() << endl;
    cout << " neg_format: " << mp.neg_format() << endl;
}

int main()
{
    cout << "test 1" << endl;
    {
        cout << "你好 u8: " << u8"你好" << endl;
        string uStr = u8"你好";

        
        // 将UTF-8编码的原始字符串转换为Unicode，然后再转换为中文GBK编码。
        std::wstring_convert<std::codecvt_utf8<wchar_t>> cvt_utf8; //UTF-8<->Unicode转换器
        std::wstring_convert<std::codecvt<wchar_t, char, std::mbstate_t>> cvt_ansi(new std::codecvt<wchar_t, char, std::mbstate_t>("CHS"));//GBK<->Unicode转换器
        std::wstring ws = cvt_utf8.from_bytes(uStr);//UTF-8转换为Unicode
        std::string myansistr = cvt_ansi.to_bytes(ws);//Unicode转换为GBK
        cout << myansistr << endl;

        // https://www.zhihu.com/question/39186934
        string gbkStr = "你好";

#ifdef _MSC_VER
        const string GBK_LOCALE_NAME = ".936";
#else
        const string GBK_LOCALE_NAME = "zh_CN.GBK";
#endif
        //构造GBK与wstring间的转码器（wstring_convert在析构时会负责销毁codecvt_byname，所以不用自己delete）
        wstring_convert<codecvt_byname<wchar_t, char, mbstate_t>> cv1(new codecvt_byname<wchar_t, char, mbstate_t>(GBK_LOCALE_NAME));
        wstring tmp_wstr = cv1.from_bytes(gbkStr);
        wstring_convert<codecvt_utf8<wchar_t>> cv2;
        string utf8_str = cv2.to_bytes(tmp_wstr);

        cout << utf8_str << endl;
    }
    cout << endl;

    cout << "test 2" << endl;
    {
//        try {
//            // use classic C locale to read data from standard input
//            cin.imbue(locale::classic()); // 同: std::locale("C");
//            // use a German locale to write data to standard output
//            // - use different locale names for Windows and POSIX
//#ifdef _MSC_VER
//            cout.imbue(locale("deu_deu.1252"));
//#else
//            cout.imbue(locale("de_DE"));
//#endif
//            // read and output floating-point values in a loop
//            cout << "input floating-point values (classic notation): " << endl;
//            double value;
//            while (cin >> value) {
//                cout << value << endl;
//            }
//        }
//        catch (const std::exception& e) {
//            cerr << "Exception: " << e.what() << endl;
//            return EXIT_FAILURE;
//        }
    }
    cout << endl;

    cout << "test 3" << endl;
    {
        //try {
        //    // create the default locale from the user’s environment
        //    locale langLocale("");
        //    // and assign it to the standard output channel
        //    cout.imbue(langLocale);
        //    // process the name of the locale to find out whether German is used
        //    cout << langLocale.name() << endl;
        //    const string strLocaleName = langLocale.name();
        //    bool isGerman = (strLocaleName.substr(0, 2) == "de" ||
        //        strLocaleName.substr(0, 3) == "ger" ||
        //        strLocaleName.substr(0, 3) == "Ger");
        //    // read locale for the input
        //    cout << (isGerman ? "Sprachumgebung fuer Eingaben: "
        //        : "Locale for input: ") << endl;
        //    string s;
        //    cin >> s;
        //    if (!cin) {
        //        if (isGerman) {
        //            cerr << "FEHLER beim Einlesen der Sprachumgebung"
        //                << endl;
        //        }
        //        else {
        //            cerr << "ERROR while reading the locale" << endl;
        //        }
        //        return EXIT_FAILURE;
        //    }
        //    locale cinLocale(s); // create locale by string (since C++11)
        //                         // and assign it to the standard input channel
        //    cin.imbue(cinLocale);
        //    // read and output floating-point values in a loop
        //    cout << (isGerman ? "Gleitkommawerte: "
        //        : "Floating-point values: ") << endl;
        //    double value;
        //    while (cin >> value) {
        //        cout << value << endl;
        //    }
        //}
        //catch (const std::exception& e) {
        //    cerr << "Exception: " << e.what() << endl;
        //    return EXIT_FAILURE;
        //}
    }
    cout << endl;

    cout << "test 4" << endl;
    {
//        try {
//            // print floating-point value with the global classic locale:
//            locale locC;
//            cout.imbue(locC);
//            use_facet<num_put<char>>(locC).put(cout, cout, ' ', 1234.5678);// 将1234.5678 以第二个参数指定的格式 写到第一个参数, 并以' '填充
//            cout << endl;
//
//            
//            // print floating-point value with German locale:
//#ifdef _MSC_VER
//            locale locG("deu_deu.1252");
//#else
//            locale locG("de_DE");
//#endif
//            cout.imbue(locG);
//            use_facet<num_put<char>>(locG).put(cout, cout, ' ', 1234.5678);
//            cout << endl;
//        }
//        catch (const std::exception& e) {
//            cerr << "Exception: " << e.what() << endl;
//            return EXIT_FAILURE;
//        }
    }
    cout << endl;

    cout << "test 5" << endl;
    {
        //try {
        //    printMoneyPunct<false>("C");
        //    cout << endl;
        //    printMoneyPunct<false>("german");
        //    cout << endl;
        //    printMoneyPunct<true>("german");
        //}
        //catch (const std::exception& e) {
        //    cerr << "Exception: " << e.what() << endl;
        //    return EXIT_FAILURE;
        //}
    }
    cout << endl;

    cout << "test 6" << endl;
    {
//        try {
//            // use German locale:
//#ifdef _MSC_VER
//            locale locG("deu_deu.1252");
//#else
//            locale locG("de_DE");
//#endif
//            const money_put<char>& mpG = use_facet<money_put<char> >(locG);
//            // ensure that the money_put<> facet impacts the output and currency is written:
//            cout.imbue(locG);
//            cout << showbase;
//            // use double as monetary value (use local symbol)
//            mpG.put(cout, false, cout, ' ', 12345.678);
//            cout << endl;
//            // use string as monetary value (use international symbol)
//            mpG.put(cout, true, cout, ' ', "12345.678");
//            cout << endl;
//        }
//        catch (const std::exception& e) {
//            cerr << "EXCEPTION: " << e.what() << endl;
//            return EXIT_FAILURE;
//        }
    }
    cout << endl;

    cout << "test 7" << endl;
    {
//        try {
//            // use German locale:
//#ifdef _MSC_VER
//            locale locG("deu_deu.1252");
//#else
//            locale locG("de_DE");
//#endif
//            // use German locale and ensure that the currency is written:
//            cin.imbue(locG);
//            cout.imbue(locG);
//            cout << showbase;
//            // read monetary value into long double (use international symbol)
//            long double val;
//            cout << "monetary value: ";
//            cin >> get_money(val, true);
//            if (cin) {
//                // write monetary value (use local symbol)
//                cout << put_money(val, false) << endl;
//            }
//            else {
//                cerr << "invalid format" << endl;
//            }
//        }
//        catch (const std::exception& e) {
//            cerr << "Exception: " << e.what() << endl;
//            return EXIT_FAILURE;
//        }
    }
    cout << endl;

    cout << "test 8" << endl;
    {
        try {
            // query local time:
            auto now = chrono::system_clock::now();
            std::time_t t = chrono::system_clock::to_time_t(now);
            tm* nowTM = std::localtime(&t);
            // print local time with the global classic locale:
            locale locC;
            const time_put<char>& tpC = use_facet<time_put<char>>(locC);
            // use single conversion specifier
            tpC.put(cout, cout, ' ', nowTM, 'x');
            cout << endl;
            cout << put_time(nowTM, "%X") << endl; // time manipulator
            // use format string:
            string format = "%A %x %I%p\n"; // format: weekday date hour
            tpC.put(cout, cout, ' ', nowTM, format.c_str(), format.c_str() + format.size());
            // print local time with German locale:
#ifdef _MSC_VER
            locale locG("deu_deu.1252");
#else
            locale locG("de_DE");
#endif
            const time_put<char>& tpG = use_facet<time_put<char>>(locG);
            tpG.put(cout, cout, ' ', nowTM, 'x');
            cout << endl;
            tpG.put(cout, cout, ' ', nowTM, format.c_str(), format.c_str() + format.size());
        }
        catch (const std::exception& e) {
            cerr << "Exception: " << e.what() << endl;
            return EXIT_FAILURE;
        }
    }
    cout << endl;

    cout << "test 9 " << endl;
    {
        try {
            // use German locale:
#ifdef _MSC_VER
            locale locG("deu_deu.1252");
#else
            locale locG("de_DE.ISO-8859-1");
#endif
            const time_get<char>& tgG = use_facet<time_get<char>>(locG);
            // print date order of German locale:
            typedef time_base TB;
            time_get<char>::dateorder d = tgG.date_order();
            cout << "dateorder: "
                << (d == TB::no_order || d == TB::mdy ? "mdy" :
                    d == TB::dmy ? "dmy" :
                    d == TB::ymd ? "ymd" :
                    d == TB::ydm ? "ydm" : "unknown") << endl;
            // read weekday (in German) and time (hh::mm))
            cout << "<wochentag> <hh>:<mm>: ";
            string format = "%A %H:%M";
            struct tm val;
            ios_base::iostate err = ios_base::goodbit;
            tgG.get(istreambuf_iterator<char>(cin),
                istreambuf_iterator<char>(),
                cin, err, &val,
                format.c_str(), format.c_str() + format.size());
            if (err != ios_base::goodbit) 
                cerr << "invalid format" << endl;

            if (!cin)
            {
                cin.sync(); // 清除缓冲区
                cin.clear(); // 清除错误状态, 不知道有没有效果
            }
            //cin.ignore(100, '\n'); // 忽略100 个字符, 或遇到回车时候停止等待
            cout << "<wochentag> <hh>:<mm>: ";
            cin >> get_time(&val, format.c_str()); // time manipulator
            if (!cin)
                cerr << "invalid format" << endl;
        }
        catch (const std::exception& e) {
            cerr << "Exception: " << e.what() << endl;
            return EXIT_FAILURE;
        }

    }
    cout << endl;

    return EXIT_SUCCESS;
}


#endif