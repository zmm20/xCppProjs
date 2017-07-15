//#define MAIN
#ifdef MAIN

#include <iostream>
#include <string>
#include <regex>
#include <algorithm>

using namespace std;

void out(bool b)
{
    cout << (b ? "found" : "not found") << endl;
}

template <typename T>
std::string regexCode(T code)
{
    switch (code) 
    {
    case std::regex_constants::error_collate:
        return "error_collate: "
            "regex has invalid collating element name";
    case std::regex_constants::error_ctype:
        return "error_ctype: "
            "regex has invalid character class name";
    case std::regex_constants::error_escape:
        return "error_escape: "
            "regex has invalid escaped char. or trailing escape";
    case std::regex_constants::error_backref:
        return "error_backref: "
            "regex has invalid back reference";
    case std::regex_constants::error_brack:
        return "error_brack: "
            "regex has mismatched ’[’ and ’]’";
    case std::regex_constants::error_paren:
        return "error_paren: "
            "regex has mismatched ’(’ and ’)’";
    case std::regex_constants::error_brace:
        return "error_brace: "
            "regex has mismatched ’{’ and ’}’";
    case std::regex_constants::error_badbrace:
        return "error_badbrace: "
            "regex has invalid range in {} expression";
    case std::regex_constants::error_range:
        return "error_range: "
            "regex has invalid character range, such as ’[b-a]’";
    case std::regex_constants::error_space:
        return "error_space: "
            "insufficient memory to convert regex into finite state";
    case std::regex_constants::error_badrepeat:
        return "error_badrepeat: "
            "one of *?+{ not preceded by valid regex";
    case std::regex_constants::error_complexity:
        return "error_complexity: "
            "complexity of match against regex over pre-set level";
    case std::regex_constants::error_stack:
        return "error_stack: "
            "insufficient memory to determine regex match";
    }
    return "unknown/non-standard regex error code";
}
int main()
{
    cout << "test 1: " << endl;
    {
        // find XML/HTML-tagged value (using default syntax):
        regex reg1("<.*>.*</.*>");
        bool found = regex_match("<tag>value</tag>", // data
            reg1); // regular expression
        out(found);
        // find XML/HTML-tagged value (tags before and after the value must match):
        // method 1:
        //regex reg2("<(.*)>.*</\\1>");
        // method 2:
        const string strPattern = R"(<(.*)>.*</\1>)";// raw string: R"delim(....)delim";
        regex reg2(strPattern); 
        found = regex_match("<tag>value</tag>", // data
            reg2); // regular expression
        out(found);
        // find XML/HTML-tagged value (using grep syntax):
        regex reg3("<\\(.*\\)>.*</\\1>", regex_constants::grep);
        found = regex_match("<tag>value</tag>", // data
            reg3); // regular expression
        out(found);
        // use C-string as regular expression (needs explicit cast to regex):
        found = regex_match("<tag>value</tag>", // data
            regex("<(.*)>.*</\\1>")); // regular expression
        out(found);
        cout << endl;
        // regex_match() versus regex_search():
        // regex_match 检测是否整个字符序列匹配某个正则表达式
        // regex_search 检测是否部分字符序列匹配某个正则表达式
        found = regex_match("XML tag: <tag>value</tag>",
            regex("<(.*)>.*</\\1>")); // fails to match
        out(found);
        found = regex_match("XML tag: <tag>value</tag>",
            regex(".*<(.*)>.*</\\1>.*")); // matches
        out(found);
        found = regex_search("XML tag: <tag>value</tag>",
            regex("<(.*)>.*</\\1>")); // matches
        out(found);
        found = regex_search("XML tag: <tag>value</tag>",
            regex(".*<(.*)>.*</\\1>.*")); // matches
        out(found);
    }
    cout << endl;

    cout << "test 2" << endl;
    {
        string data = "XML tag: <tag-name>the value</tag-name>.";
        cout << "data: " << data << "\n\n";
        smatch m; // for returned details of the match
        bool found = regex_search(data, m, regex("<(.*)>(.*)</(\\1)>"));
        // print match details:
        cout << "m.empty(): " << boolalpha << m.empty() << endl;
        cout << "m.size(): " << m.size() << endl;
        if (found) {
            cout << "m.str(): " << m.str() << endl;
            cout << "m.length(): " << m.length() << endl;
            cout << "m.position(): " << m.position() << endl;
            cout << "m.prefix().str(): " << m.prefix().str() << endl;
            cout << "m.suffix().str(): " << m.suffix().str() << endl;
            cout << endl;
            // iterating over all matches (using the match index):
            for (int i = 0; i<m.size(); ++i) {
                cout << "m[" << i << "].str(): " << m[i].str() << endl;
                cout << "m.str(" << i << "): " << m.str(i) << endl;
                cout << "m.position(" << i << "): " << m.position(i)
                    << endl;
            }
            cout << endl;
            // iterating over all matches (using iterators):
            cout << "matches:" << endl;
            for (auto pos = m.begin(); pos != m.end(); ++pos) {
                cout << " " << *pos << " ";
                cout << "(length: " << pos->length() << ")" << endl;
            }
        }
    }
    cout << endl;

    cout << "test 3" << endl;
    {
        string data = "XML tag: <tag-name>the value</tag-name>.";
        cout << "data: " << data << "\n\n";
        smatch m; // for returned details of the match
        bool found = regex_search(data,
            m,
            regex("<(.*)>(.*)</(\\1)>"));
        // print match details:
        cout << "m.empty(): " << boolalpha << m.empty() << endl;
        cout << "m.size(): " << m.size() << endl;
        if (found) {
            cout << "m.str(): " << m.str() << endl;
            cout << "m.length(): " << m.length() << endl;
            cout << "m.position(): " << m.position() << endl;
            cout << "m.prefix().str(): " << m.prefix().str() << endl;
            cout << "m.suffix().str(): " << m.suffix().str() << endl;
            cout << endl;
            // iterating over all matches (using the match index):
            for (int i = 0; i<m.size(); ++i) {
                cout << "m[" << i << "].str(): " << m[i].str() << endl;
                cout << "m.str(" << i << "): " << m.str(i) << endl;
                cout << "m.position(" << i << "): " << m.position(i)
                    << endl;
            }
            cout << endl;
            // iterating over all matches (using iterators):
            cout << "matches:" << endl;
            for (auto pos = m.begin(); pos != m.end(); ++pos) {
                cout << " " << *pos << " ";
                cout << "(length: " << pos->length() << ")" << endl;
            }
        }
    }
    cout << endl;

    cout << "test 4: " << endl;
    {
        string data = "<person>\n"
            " <first>Nico</first>\n"
            " <last>Josuttis</last>\n"
            "</person>\n";
        regex reg("<(.*)>(.*)</(\\1)>"); // . 表示除了换行符的任意字符
        // iterate over all matches
        auto pos = data.cbegin();
        auto end = data.cend();
        smatch m;
        for (; regex_search(pos, end, m, reg); pos = m.suffix().first) {
            cout << "match: " << m.str() << endl;
            cout << " tag: " << m.str(1) << endl;
            cout << " value: " << m.str(2) << endl;
        }
    }
    cout << endl;

    cout << "test 5: " << endl;
    {
        string data = "<person>\n"
            " <first>Nico</first>\n"
            " <last>Josuttis</last>\n"
            "</person>\n";
        regex reg("<(.*)>(.*)</(\\1)>");
        // iterate over all matches (using a regex_iterator):
        sregex_iterator pos(data.cbegin(), data.cend(), reg);
        sregex_iterator end; // 默认构造函数定义出一个指向"末尾之下一个位置"(past-the-end)
        for (; pos != end; ++pos) {
            cout << "match: " << pos->str() << endl;
            cout << " tag: " << pos->str(1) << endl;
            cout << " value: " << pos->str(2) << endl;
        }
        // use a regex_iterator to process each matched substring as element in an algorithm:
        sregex_iterator beg(data.cbegin(), data.cend(), reg);
        for_each(beg, end, [](const smatch& m) {
            cout << "match: " << m.str() << endl;
            cout << " tag: " << m.str(1) << endl;
            cout << " value: " << m.str(2) << endl;
        });
    }
    cout << endl;

    cout << "test 5: " << endl;
    {
        string data = "<person>\n"
            " <first>Nico</first>\n"
            " <last>Josuttis</last>\n"
            "</person>\n";
        regex reg("<(.*)>(.*)</(\\1)>");
        // iterate over all matches (using a regex_token_iterator):
        sregex_token_iterator pos(data.cbegin(), data.cend(), // sequence
            reg, // token separator
            { 0,2 }); // 0: full match, 2: second substring
        sregex_token_iterator end;
        for (; pos != end; ++pos) {
            cout << "match: " << pos->str() << endl;
        }
        cout << endl;
        string names = "nico, jim, helmut, paul, tim, john paul, rita";
        regex sep("[ \t\n]*[,;.][ \t\n]*"); // separated by , ; or . and spaces
        sregex_token_iterator p(names.cbegin(), names.cend(), // sequence
            sep, // separator
            -1); // -1: values between separators
        sregex_token_iterator e;
        for (; p != e; ++p) {
            cout << "name: " << *p << endl;
        }
    }
    cout << endl;

    cout << "test 6: " << endl;
    {
        string data = "<person>\n"
            " <first>Nico</first>\n"
            " <last>Josuttis</last>\n"
            "</person>\n";
        regex reg("<(.*)>(.*)</(\\1)>");
        // print data with replacement for matched patterns
        cout << regex_replace(data, // data
            reg, // regular expression
            "<$1 value=\"$2\"/>") // replacement // 匹配之次表达式(matched subexpression)
            << endl;
        // same using sed syntax
        cout << regex_replace(data, // data
            reg, // regular expression
            "<\\1 value=\"\\2\"/>", // replacement
            regex_constants::format_sed) // format flag
            << endl;
        // use iterator interface, and
        // - format_no_copy: don’t copy characters that don’t match
        // - format_first_only: replace only the first match found
        string res2;
        regex_replace(back_inserter(res2), // destination
            data.begin(), data.end(), // source range
            reg, // regular expression
            "<$1 value=\"$2\"/>", // replacement
            regex_constants::format_no_copy // format flags
            | regex_constants::format_first_only);
        cout << res2 << endl;
    }
    cout << endl;

    cout << "test 7: " << endl;
    {
        // case-insensitive find LaTeX index entries
        //string pat1 = R"(\\.*index\{([^}]*)\})"; // first capture group
        //string pat2 = R"(\\.*index\{(.*)\}\{(.*)\})"; // 2nd and 3rd capture group
        //regex pat(pat1 + "\n" + pat2,
        //    regex_constants::egrep | regex_constants::icase); // 使用UNIX 工具egrep文法, 且忽略大小写
        //// initialize string with characters from standard input:
        //string data((istreambuf_iterator<char>(cin)),
        //    istreambuf_iterator<char>());
        //// search and print matching index entries:
        //smatch m;
        //auto pos = data.cbegin();
        //auto end = data.cend();
        //for (; regex_search(pos, end, m, pat); pos = m.suffix().first) {
        //    cout << "match: " << m.str() << endl;
        //    cout << " val: " << m.str(1) + m.str(2) << endl;
        //    cout << " see: " << m.str(3) << endl;
        //}
    }
    cout << endl;

    cout << "test 8: " << endl;
    {
        try {
            // initialize regular expression with invalid syntax:
            regex pat("\\\\.*index\\{([^}]*)\\}",
                regex_constants::grep | regex_constants::icase);
            //...
        }
        catch (const regex_error& e) {
            cerr << "regex_error: \n"
                << " what(): " << e.what() << "\n"
                << " code(): " << regexCode(e.code()) << endl;
        }
    }
    cout << endl;
}
#endif