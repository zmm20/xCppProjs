#define MAIN
#ifdef MAIN

#include "TextExtractor.h"
#include "ImageExtractor.h"
#include <iostream>
#include <podofo/podofo.h>
#include <string>
#include <vector>
#include <string>
#include <cstdlib>
#include <boost/filesystem/path.hpp>

using namespace std;
using namespace PoDoFo;

int count_pages(const char* pszFilename, const bool & bShortFormat)
{
    PdfMemDocument document;
    document.Load(pszFilename);
    int nPages = document.GetPageCount();

    if (bShortFormat)
        printf("%i\n", nPages);
    else
        printf("%s:\t%i\n", pszFilename, nPages);

    return nPages;
}


int main()
{
    cout << "-----00test------------" << endl;

    PdfError::EnableDebug(false);
    const std::string pdfPath(R"(.\test\test.pdf)");

    cout << "test 0" << endl;
    {
        const std::string tmpPath = std::getenv("temp");
        boost::filesystem::path ph(tmpPath);

        cout << tmpPath << endl;
        //return 0;
    }
    cout << endl;

    cout << "test 1" << endl;
    {        
        try {

            PdfMemDocument document;
            document.Load(pdfPath.c_str());
            int nPages = document.GetPageCount();

            cout << "pdf页数:" << nPages << endl;
        }
        catch (PdfError & e) {
            fprintf(stderr, "Error: An error %i ocurred during counting pages in the pdf file.\n", e.GetError());
            e.PrintErrorMsg();
            return e.GetError();
        }
    }
    cout << endl;


    cout << "test 2" << endl;
    {// 文本抓取
        CTextExtractor extractor;

        try {
            extractor.Init(pdfPath.c_str());
            auto  pagesTxtList = extractor.getPageTxtList();

            int nPage = 0;
            for (const auto& item : pagesTxtList)
            {
                ++nPage;
                cout << "页码: " << nPage << ", 内容: " << endl;
                cout << item << endl;
            }
        }
        catch (PdfError & e) {
            fprintf(stderr, "Error: An error %i ocurred during processing the pdf file.\n", e.GetError());
            e.PrintErrorMsg();
            return e.GetError();
        }
    }
    cout << endl;

    cout << "test 3" << endl;
    {// 图片抓取
        CImageExtractor extractor;

        try {
            extractor.Init(pdfPath.c_str());
            const auto& imgList = extractor.getImages();
            for (const auto item : imgList)
                cout << item << endl;
        }
        catch (PdfError & e) {
            fprintf(stderr, "Error: An error %i ocurred during processing the pdf file.\n", e.GetError());
            e.PrintErrorMsg();
            return e.GetError();
        }
    }
    cout << endl;

    return EXIT_SUCCESS;
}

#endif