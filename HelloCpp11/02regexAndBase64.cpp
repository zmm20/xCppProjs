//#define MAIN
#ifdef MAIN

#include <iostream>
#include <string>
#include <regex>
#include <objbase.h>
#include <fstream>
#include "Base64.h"

using namespace std;

std::string src="<html>\n"
                "<body>\n"
                "<p>FdsffdsDD<img src = \"file:///C:\\Users\\zmm\\AppData\\Local\\Temp\\msohtmlclip1\\01\\clip_image002.gif\" width = \"77\" height = \"48\" / > < / p>\n"
                "<table border = \"1\" cellspacing = \"0\" cellpadding = \"0\">\n"
                "<tr>\n"
                "<td width = \"189\" >\n"
                "<p >COLUM1 < / p>< / td>\n"
                "<td width = \"189\" >\n"
                "<p >COLUM2 < / p>< / td>\n"
                "<td width = \"189\" >\n"
                "<p >COLUM3 < / p>< / td>< / tr>\n"
                "<tr>\n"
                "<td >\n"
                "<p><img src = \"file:///C:\\Users\\zmm\\AppData\\Local\\Temp\\msohtmlclip1\\01\\clip_image004.gif\" width = \"31\" height = \"23\" / > < / p>< / td>\n"
                "<td >\n"
                "<p >2 < / p>< / td>\n"
                "<td>\n"
                "<p >3 < / p>< / td>< / tr>< / table>\n"
                "<p >X<span style = \" vertical-align:super;\">2< / span> < / p>\n"
                "< / body>\n"
                "< / html>\n";

std::string genGUID();

// Ŀǰֻ֧��һ~ʮ��ת��, ��ΪĿǰֻ�õ���ô��
int cvtNum(const wchar_t c) 
{
    switch (c)
    {
    case L'һ':
        return 1;
        break;
    case L'��':
        return 1;
        break;
    case L'��':
        return 1;
        break;
    case L'��':
        return 1;
        break;
    case L'��':
        return 1;
        break;
    case L'��':
        return 1;
        break;
    case L'��':
        return 1;
        break;
    case L'��':
        return 1;
        break;
    case L'��':
        return 1;
        break;
    case L'ʮ':
        return 10;
        break;
    default:
        return 0;
    }
}

/// ת�����ֵ���ֵ, ֻ֧��ת����ֵС��100��
///
/// @isChinese �Ƿ�Ϊ������ֵ
/// end ָ�� wsrc ����ֵ��һ��λ��
int cvtStr2Num(const std::wstring& wsrc, bool& isChinese, int& end)
{
    std::wregex pattern_digit(L"([\\d]+)");
    std::wregex pattern_ch(L"([һ|��|��|��|��|��|��|��|��|ʮ]{1,3})");
    std::wsmatch res;
    if (std::regex_search(wsrc, res, pattern_ch))
    {
        isChinese = true;

        const std::wstring strDigit = res.str(1);
        end = std::distance(wsrc.cbegin(), res.suffix().first);

        int total = 0;
        const int len = strDigit.size();
        if (1 == len)
            total = cvtNum(strDigit.at(0));
        else if (2 == len)
        {
            const int first = cvtNum(strDigit.at(0));
            const int second = cvtNum(strDigit.at(1));
            if (first == 10)
                total = first + second;
            else if (second == 10)
                total = first * 10;
        }
        else if (3 == len)
        {
            const int first = cvtNum(strDigit.at(0));
            const int second = cvtNum(strDigit.at(1));
            const int third = cvtNum(strDigit.at(2));
            if (second != 10 || third == 10)
                total = 0;
            else
                total = first * 10 + third;
        }
        else
        {
            total = 0;
        }

        return total;
    }
    else if (std::regex_search(wsrc, res, pattern_digit))
    {
        isChinese = false;
        const int total = std::stoi(res.str(1));
        end = std::distance(wsrc.cbegin(), res.suffix().first);
        return total;
    }

    isChinese = false;
    end = 0;
    return 0;
}
int main()
{
    cout << "test 0:" << endl;
    {
        bool isChinese = false;
        int n;
        wstring wdata = L"1.	Fdsfdsfd";
        const int num= cvtStr2Num(wdata, isChinese, n);
        cout << num << (isChinese ? "�Ǻ���" : "�Ǻ���") << ", posEnd: " << n << endl;

        return 0;
    }
    cout << endl;

    cout << "test 1:" << endl;
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
                cout << "m.position(" << i << "): " << m.position(i)<< endl;
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

    cout << "test 2: base64" << endl;
    {
        const string imgPath = "C:\\Users\\zmm\\AppData\\Local\\Temp\\msohtmlclip1\\01\\clip_image002.gif";
        ifstream imgFile(imgPath, std::ios::binary);
        if (!imgFile)
        {
            cerr << "open file failed" << endl;
            return EXIT_FAILURE;
        }
        string strBuf("");
        char buf[1024]{0};
        int readCount = -1;
        while (readCount != 0)
        {
            imgFile.read(buf, sizeof buf);
            readCount = imgFile.gcount();
            strBuf += string(buf, readCount);
        }
        
        int enDstLen;
        CBase64 base;
        // ��ȡ��Ŀ���С
        base.EncodeBase64((unsigned char*)&strBuf[0], strBuf.size(), nullptr, &enDstLen);
        // �ٱ���
        char* pEnDstBuf = new char[enDstLen];
        int rt = base.EncodeBase64((unsigned char*)&strBuf[0], strBuf.size(), (unsigned char*)pEnDstBuf, &enDstLen);
        if (rt < 0)
        {
            cerr << "encode base64 error" << endl;
            return EXIT_FAILURE;
        }
        cout << "����ɹ�" << endl;
        ofstream oEnfile("C:\\Users\\zmm\\AppData\\Local\\Temp\\imgEncode.txt", ios::binary | ios::trunc);
        oEnfile.write(pEnDstBuf, enDstLen);


        // ����
        int deDstLen;
        base.DecodeBase64((unsigned char*)pEnDstBuf, enDstLen, nullptr, &deDstLen);
        char* pDeDstBuf = new char[deDstLen];
        base.DecodeBase64((unsigned char*)pEnDstBuf, enDstLen, (unsigned char*)pDeDstBuf, &deDstLen);

        ofstream of("C:\\Users\\zmm\\AppData\\Local\\Temp\\test.gif", ios::binary | ios::trunc);
        of.write(pDeDstBuf, deDstLen);

    }
    cout << endl;
    
    return EXIT_SUCCESS;

    cout << "test 3: " << endl;
    {
        // �������е�img������ǩ
        //std::regex img_pattern("<img [^>]+>");
        std::regex img_pattern("<img [^\"]+\"(file:///([^\"]+))\"[^>]+>");

        // ʹ�� std::regex_search ��ѯ��һ��ƥ����ַ���.
        std::smatch matchResult;
        std::cout << "regex_search ====" << std::endl;
        if (std::regex_search(src, matchResult, img_pattern))
        {
            cout << "match[0]= " << matchResult[0] << endl
                << "match[1] = " << matchResult[1] << endl;
        }
        cout << endl;

        // ʹ���� std::regex_iterator �����ж������.
        std::cout << "sregex_iterator ====" << std::endl;
        std::vector<smatch> matchList;
        auto words_begin = std::sregex_iterator(src.begin(), src.end(), img_pattern);
        auto words_end = std::sregex_iterator();
        for (std::sregex_iterator i = words_begin; i != words_end; ++i)
        {
            matchList.push_back(*i);

            const string fileURI = i->str(2);
            std::cout << "image path: " << fileURI << endl;

            //const std::ifstream imgFile(fileURI, std::ios::binary);
        }
        cout << endl;

        // �滻ͼƬ��·��
        int i = 0; // �����i ������guid ����
        for (auto rIt = matchList.crbegin(); rIt != matchList.crend(); ++rIt)
        {
            ++i;
            const int dotPos = rIt->str(1).find_last_of('.');
            const string imageSuffix = rIt->str(1).substr(dotPos, -1);
            const string newImage = genGUID() + imageSuffix;

            auto itStart = src.cbegin() + rIt->position(1);
            auto itEnd = itStart + rIt->length(1);
            src.replace(itStart, itEnd, newImage);
        }
        cout << "src = \n" << src << endl;
    }
    cout << endl;

    
    cout << "test 4: " << endl;
    {
        
    }
    cout << endl;
}

std::string genGUID()
{
    char buffer[64] = { 0 };
    GUID guid;

    if (CoCreateGuid(&guid))
    {
        std::cerr << "create guid error" << endl;
        return "";
    }
    _snprintf(buffer, sizeof(buffer),
        "%08X-%04X-%04x-%02X%02X-%02X%02X%02X%02X%02X%02X",
        guid.Data1, guid.Data2, guid.Data3,
        guid.Data4[0], guid.Data4[1], guid.Data4[2],
        guid.Data4[3], guid.Data4[4], guid.Data4[5],
        guid.Data4[6], guid.Data4[7]);
    return std::move(std::string(buffer));
}

#endif