//#define MAIN
#ifdef MAIN

#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include <cctype> // for toupper
#include <regex>
#include <iterator>
#include "util/icstring.hpp"
using namespace std;
using namespace std;

std::wstring to_lower(const std::wstring& src)
{
    try
    {
        std::wstring strDst;
        std::transform(src.cbegin(), src.cend(), std::back_inserter<std::wstring>(strDst), [](wchar_t c) {return std::tolower(c, std::locale()); });
        
        return strDst;
    }
    catch (exception e)
    {
        cerr << e.what() << endl;
        return L"error";
    }
}


std::string to_lower(const std::string& src)
{
    try
    {
        std::string strDst;
        std::transform(src.cbegin(), src.cend(), std::back_inserter<std::string>(strDst), [](char c) {return std::tolower(c, std::locale()); });

        return strDst;
    }
    catch (exception e)
    {
        cerr << e.what() << endl;
        return "error";
    }
}

int main()
{
    cout << "test 1" << endl;
    {
        //const string delims(" \t,.;");
        //string line;
        //// for every line read successfully
        //while (getline(cin, line)) 
        //{
        //    string::size_type begIdx, endIdx;
        //    // search beginning of the first word
        //    begIdx = line.find_first_not_of(delims);
        //    // while beginning of a word found
        //    while (begIdx != string::npos) {
        //        // search end of the actual word
        //        endIdx = line.find_first_of(delims, begIdx);
        //        if (endIdx == string::npos) {
        //            // end of word is end of line
        //            endIdx = line.length();
        //        }
        //        // print characters in reverse order
        //        for (int i = endIdx - 1; i >= static_cast<int>(begIdx); --i) {
        //            cout << line[i];
        //        }
        //        cout << ' ';
        //        // search beginning of the next word
        //        begIdx = line.find_first_not_of(delims, endIdx);
        //    }
        //    cout << endl;
        //}
    }
    cout << endl;


    cout << "test 2" << endl;
    {
        std::string s1("nico"); // initializes s1 with: ��n�� ��i�� ��c�� ��o��
        std::string s2("nico", 5); // initializes s2 with: ��n�� ��i�� ��c�� ��o�� ��\0��
        std::string s3(5, '\0'); // initializes s3 with: ��\0�� ��\0�� ��\0�� ��\0�� ��\0��
        cout << s1 << " length = " << s1.length() << endl; // yields 4
        cout << s2 << " length = " << s2.length() << endl; // yields 5
        cout << s3 << " length = " << s3.length() << endl; // yields 5
        
    }
    cout << endl;

    cout << "test 3" << endl;
    {
        std::string s("12345");
        cout << s << " = " << atoi(s.c_str()) << endl; // convert string into integer
        
        char buffer[100] = "";
        // copy at most 100 characters of s into buffer
        s.copy(buffer, 100);
        cout << "buffer = " << buffer << endl;

        // copy at most 100 characters of s into buffer
        // starting with the third character of s
        s.copy(buffer, 100, 2);
        cout << "buffer = " << buffer << endl;
    }
    cout << endl;

    cout << "test 4" << endl;
    {
        std::string s = "hello world";
        const char* p = s.c_str(); // p refers to the contents of s as a C-string
        cout << p << endl;// foo(p);  OK (p is still valid)
        s += " hello zmm"; // invalidates p
        cout << p << endl;  //foo(p); ERROR: argument p is not valid
    }
    cout << endl;

    cout << "test 5" << endl;
    {
        std::string s("abcd");
        s.compare("abcd"); // returns 0
        s.compare("dcba"); // returns a value < 0 (s is less)
        s.compare("ab"); // returns a value > 0 (s is greater)
        s.compare(s); // returns 0 (s is equal to s)
        s.compare(0, 2, s, 2, 2); // returns a value < 0 ("ab" is less than "cd")
        s.compare(1, 2, "bcx", 2); // returns 0 ("bc" is equal to "bc")
    }
    cout << endl;

    cout << "test 6" << endl;
    {
        const std::string aString("othello");
        std::string s;
        s = aString; // assign "othello"
        s = "two\nlines"; // assign a C-string
        s = ' '; // assign a single character
        s.assign(aString); // assign "othello" (equivalent to operator =)
        s.assign(aString, 1, 3); // assign "the"
        s.assign(aString, 2, std::string::npos); // assign "hello"
        s.assign("two\nlines"); // assign a C-string (equivalent to operator =)
        s.assign("nico", 5); // assign the character array: ��n�� ��i�� ��c�� ��o�� ��\0��
        s.assign(5, 'x'); // assign five characters: ��x�� ��x�� ��x�� ��x�� ��x��
    }
    cout << endl;

    cout << "test 7" << endl;
    {
        const std::string aString("othello");
        std::string s;
        s += aString; // append "othello"
        s += "two\nlines"; // append C-string
        s += '\n'; // append single character
        s += { 'o', 'k' }; // append an initializer list of characters (since C++11)
        s.append(aString); // append "othello" (equivalent to operator +=)
        s.append(aString, 1, 3); // append "the"
        s.append(aString, 2, std::string::npos); // append "hello"
        s.append("two\nlines"); // append C-string (equivalent to operator +=)
        s.append("nico", 5); // append character array: ��n�� ��i�� ��c�� ��o�� ��\0��
        s.append(5, 'x'); // append five characters: ��x�� ��x�� ��x�� ��x�� ��x��
        s.push_back('\n'); // append single character (equivalent to operator +=)
    }
    cout << endl;

    cout << "test 8" << endl;
    {
        std::string s = "i18n"; // s: i18n
        s.replace(1, 2, "nternationalizatio"); // s: internationalization
        s.erase(13); // s: international
        s.erase(7, 5); // s: internal
        s.pop_back(); // s: interna (since C++11)
        s.replace(0, 2, "ex"); // s: externa
    }
    cout << endl;

    cout << "test 9" << endl;
    {
        std::string s("interchangeability");
        s.substr(); // returns a copy of s
        s.substr(11); // returns string("ability")
        s.substr(5, 6); // returns string("change")
        s.substr(s.find('c')); // returns string("changeability")

        std::string s1("international");
        std::string s2("ization");
        s = std::move(s1) + std::move(s2); // OK, s1 and s2 have valid state with unspecified value
    }
    cout << endl;

    cout << "test 10" << endl;
    {
        const string filecontents = "hello world; hello zmm";
        // process first line of passed string:
        std::string firstLine;
        std::getline(std::stringstream(filecontents), // OK since C++11, ��c++11 ��ʼ, ������ʱ��
            firstLine, ';');
        cout << "read line: " << firstLine << endl;
    }
    cout << endl;

    cout << "test 11" << endl;
    {
        std::string s("Hi Bill, I��m ill, so please pay the bill");
        s.find("il"); // returns 4 (first substring "il")
        s.find("il", 10); // returns 13 (first substring "il" starting from s[10])
        s.rfind("il"); // returns 37 (last substring "il")
        s.find_first_of("il"); // returns 1 (first char ��i�� or ��l��)
        s.find_last_of("il"); // returns 39 (last char ��i�� or ��l��)
        s.find_first_not_of("il"); // returns 0 (first char neither ��i�� nor ��l��)
        s.find_last_not_of("il"); // returns 36 (last char neither ��i�� nor ��l��)
        s.find("hi"); // returns npos
    }
    cout << endl;

    cout << "test 12" << endl;
    {
        std::string s("hello world");
        std::string::size_type idx; // be careful: don��t use any other type! // ������ int �� unsigned ��Ϊ����ֵ, ���򷵻�ֵ�� string::npos ֮��ıȽϿ����޷���ȷִ��
        idx = s.find("substring");
        if (idx == std::string::npos) {
            cout << "cannot find 'substring'" << endl;
        }

        // ������÷�:
        unsigned short errUse = s.find("sss");
        if (errUse == std::string::npos) {
            cout << "cannot find 'sss'" << endl;
        }
        else
        {
            cout << "find out 'sss'" << endl;

        }
    }
    cout << endl;

    cout << "test 13" << endl;
    {
        try 
        {
            // convert to numeric type
            std::cout << std::stoi(" 77") << std::endl;
            std::cout << std::stod(" 77.7") << std::endl;
            std::cout << std::stoi("-0x77") << std::endl;
            // use index of characters not processed
            std::size_t idx;
            std::cout << std::stoi(" 42 is the truth", &idx) << std::endl;
            std::cout << " idx of first unprocessed char: " << idx << std::endl;
            // use bases 16 and 8
            std::cout << std::stoi(" 42", nullptr, 16) << std::endl;
            std::cout << std::stol("789", &idx, 8) << std::endl;
            std::cout << " idx of first unprocessed char: " << idx << std::endl;
            // convert numeric value to string
            long long ll = std::numeric_limits<long long>::max();
            std::string s = std::to_string(ll); // converts maximum long long to string
            std::cout << s << std::endl;
            // try to convert back
            std::cout << std::stoi(s) << std::endl; // throws out_of_range
        }
        catch (const std::exception& e) 
        {
            std::cout << e.what() << std::endl;
        }
    }
    cout << endl;

    cout << "test 14" << endl;
    {
        // create a string
        string s("The zip code of Braunschweig in Germany is 38100");
        cout << "original: " << s << endl;
        // lowercase all characters
        transform(s.cbegin(), s.cend(), // source
            s.begin(), // destination
            [](char c) { // operation
            return tolower(c);
        });
        cout << "lowered: " << s << endl;
        // uppercase all characters
        transform(s.cbegin(), s.cend(), // source
            s.begin(), // destination
            [](char c) { // operation
            return toupper(c);
        });
        cout << "uppered: " << s << endl;
        // search case-insensitive for Germany
        string g("Germany");
        string::const_iterator pos;
        pos = search(s.cbegin(), s.cend(), // source string in which to search
            g.cbegin(), g.cend(), // substring to search
            [](char c1, char c2) { // comparison criterion
            return toupper(c1) == toupper(c2);
        });
        if (pos != s.cend()) 
        {
            cout << "substring \"" << g << "\" found at index "
                << pos - s.cbegin() << endl;
        }
    }
    cout << endl;

    cout << "test 15" << endl;
    {
        // create constant string
        const string hello("Hello, how are you?");
        // initialize string s with all characters of string hello
        string s(hello.cbegin(), hello.cend());
        // ranged-based for loop that iterates through all the characters
        for (char c : s) 
        {
            cout << c;
        }
        cout << endl;
        // reverse the order of all characters inside the string
        reverse(s.begin(), s.end());
        cout << "reverse: " << s << endl;
        // sort all characters inside the string
        sort(s.begin(), s.end());
        cout << "ordered: " << s << endl;

        // remove adjacent duplicates
        // - unique() reorders and returns new end
        auto iend = unique(s.begin(), s.end());
        cout << "unique(begin, end): " << s << endl;
        // - erase() shrinks accordingly
        s.erase(iend, s.end());
        cout << "no duplicates: " << s << endl;
    }
    cout << endl;

    cout << "test 16" << endl;
    {
        //string input;
        //// don��t skip leading whitespaces
        //cin.unsetf(ios::skipws);
        //// read all characters while compressing whitespaces
        //const locale& loc(cin.getloc()); // locale
        //unique_copy(istream_iterator<char>(cin), // beginning of source
        //    istream_iterator<char>(), // end of source
        //    back_inserter(input), // destination
        //    [=](char c1, char c2) { // criterion for adj. duplicates
        //    return isspace(c1, loc) && isspace(c2, loc);
        //});
        //// process input
        //// - here: write it to the standard output
        //cout << input;
    }
    cout << endl;

    cout << "test 17" << endl;
    {
        wstring s1 = L"Hello World";
        wcout << "wstring: " << to_lower(s1) << endl;

        string s2 = "Hello World";
        cout << "string: " << to_lower(s2) << endl;
    }
    cout << endl;

    cout << "test 18" << endl;
    {
        using std::cout;
        using std::endl;
        icstring s1("hallo");
        icstring s2("otto");
        icstring s3("hALLo");
        cout << std::boolalpha;
        cout << s1 << " == " << s2 << " : " << (s1 == s2) << endl;
        cout << s1 << " == " << s3 << " : " << (s1 == s3) << endl;
        icstring::size_type idx = s1.find("All");
        if (idx != icstring::npos) {
            cout << "index of \"All\" in \"" << s1 << "\": "
                << idx << endl;
        }
        else {
            cout << "\"All\" not found in \"" << s1 << endl;
        }
    }
    cout << endl;

    
    return EXIT_SUCCESS;
}

#endif