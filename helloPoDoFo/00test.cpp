#define MAIN
#ifdef MAIN

#include <iostream>
#include <podofo/podofo.h>
#include <string>
#include <vector>
#include <string>
#include <cstdlib>
#include <boost/filesystem/path.hpp>
#include "TextAndImgExtractor.h"
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

            cout << "pdfÒ³Êý:" << nPages << endl;
        }
        catch (PdfError & e) {
            fprintf(stderr, "Error: An error %i ocurred during counting pages in the pdf file.\n", e.GetError());
            e.PrintErrorMsg();
            return e.GetError();
        }
    }
    cout << endl;

    cout << "test 2, my class's usage" << endl;
    {
        CTextAndImgExtractor extractor;
        try 
        {
            extractor.Init(pdfPath.c_str());

            int pgCnt = extractor.getPagesCount();
            for (int i = 0; i < pgCnt; ++i)
            {
                 auto page = extractor.getPage(i + 1);
                 cout << "Ò³Âë: " << i + 1 << ": " << endl;
                 cout << "    text content: " << page.strText << endl;
                 cout << "    image path: " << endl;
                 for (auto e : page.imgURIs)
                     cout << "        " << e << endl;
            }
        }
        catch (PdfError & e) {
            fprintf(stderr, "Error: An error %i ocurred during processing the pdf file.\n", e.GetError());
            e.PrintErrorMsg();
            return e.GetError();
        }
    }

    return EXIT_SUCCESS;
}

#endif