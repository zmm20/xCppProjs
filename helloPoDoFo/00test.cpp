#define MAIN
#ifdef MAIN

#include <iostream>
#include <podofo/podofo.h>
#include <string>

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

    //PdfError::EnableDebug(false);
    const std::string pdfPath(R"(.\test\test.pdf)");

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


    return EXIT_SUCCESS;
}

#endif