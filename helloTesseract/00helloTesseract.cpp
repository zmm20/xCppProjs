// helloTesseract.cpp : 定义控制台应用程序的入口点。
//
//#define MAIN
#ifdef MAIN

#include "stdafx.h"
#include <iostream>
#include <tesseract/api/baseapi.h>
#include <leptonica/allheaders.h>

int main()
{
    try
    {
        char *outText;

        std::string imgPath(R"(.\image\test.pdf)"); // test_chi2.png

        tesseract::TessBaseAPI api;
        // Initialize tesseract-ocr with English, without specifying tessdata path
        if (api.Init(NULL, "eng")) {
            fprintf(stderr, "Could not initialize tesseract.\n");
            exit(1);
        }

        // Open input image with leptonica library
        Pix *image = pixRead(imgPath.c_str());

        api.SetImage(image);
        
        // Get OCR result
        outText = api.GetUTF8Text();
        printf("OCR output:\n%s", outText);

        // Destroy used object and release memory
        api.End();
        delete[] outText;

        pixDestroy(&image);
    }
    catch (std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}


#endif