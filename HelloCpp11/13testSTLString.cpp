#define MAIN
#ifdef MAIN

#include <iostream>
#include <string>
#include <sstream>

using namespace std;

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
        std::string s1("nico"); // initializes s1 with: ’n’ ’i’ ’c’ ’o’
        std::string s2("nico", 5); // initializes s2 with: ’n’ ’i’ ’c’ ’o’ ’\0’
        std::string s3(5, '\0'); // initializes s3 with: ’\0’ ’\0’ ’\0’ ’\0’ ’\0’
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
        s.assign("nico", 5); // assign the character array: ’n’ ’i’ ’c’ ’o’ ’\0’
        s.assign(5, 'x'); // assign five characters: ’x’ ’x’ ’x’ ’x’ ’x’
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
        s.append("nico", 5); // append character array: ’n’ ’i’ ’c’ ’o’ ’\0’
        s.append(5, 'x'); // append five characters: ’x’ ’x’ ’x’ ’x’ ’x’
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
        std::getline(std::stringstream(filecontents), // OK since C++11, 自c++11 开始, 允许临时流
            firstLine, ';');
        cout << "read line: " << firstLine << endl;
    }
    cout << endl;

    cout << "test 11" << endl;
    {
        std::string s("Hi Bill, I’m ill, so please pay the bill");
        s.find("il"); // returns 4 (first substring "il")
        s.find("il", 10); // returns 13 (first substring "il" starting from s[10])
        s.rfind("il"); // returns 37 (last substring "il")
        s.find_first_of("il"); // returns 1 (first char ’i’ or ’l’)
        s.find_last_of("il"); // returns 39 (last char ’i’ or ’l’)
        s.find_first_not_of("il"); // returns 0 (first char neither ’i’ nor ’l’)
        s.find_last_not_of("il"); // returns 36 (last char neither ’i’ nor ’l’)
        s.find("hi"); // returns npos
    }
    cout << endl;

    cout << "test 12" << endl;
    {
        std::string s("hello world");
        std::string::size_type idx; // be careful: don’t use any other type! // 不能以 int 或 unsigned 作为返回值, 否则返回值与 string::npos 之间的比较可能无法正确执行
        idx = s.find("substring");
        if (idx == std::string::npos) {
            cout << "cannot find 'substring'" << endl;
        }

        // 错误的用法:
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


    return EXIT_SUCCESS;
}

#endif