// helloTesseract.cpp : 定义控制台应用程序的入口点。
//
//#define MAIN
#ifdef MAIN

#include "stdafx.h"
#include <iostream>
#include <tesseract/api/baseapi.h>
#include <leptonica/allheaders.h>
#include <my/TextHelper.h>
#include <vector>

using namespace std;
int main()
{
    try
    {
        // std::string imgPath(R"(.\image\test_chi2.png)"); // test_chi2.png
         std::string imgPath(R"(.\image\mix.tif)"); // 该tif 中含有2 副图片, 默认只识别第一幅图片

        tesseract::TessBaseAPI api;
        // Initialize tesseract-ocr with English, without specifying tessdata path
        if (api.Init(NULL, "eng")) {
            fprintf(stderr, "Could not initialize tesseract.\n");
            exit(1);
        }        
        // Open input image with leptonica library
        Pix *image = pixRead(imgPath.c_str());
        api.SetImage(image);

        cout << "开始识别..." << endl;
        cout << "test 1" << endl;
        {
            api.InitForAnalysePage();
            api.SetPageSegMode(tesseract::PSM_AUTO_ONLY);

            // Get OCR result
            char *outText = api.GetUTF8Text();
            const std::string strResult(outText);
            delete[] outText;
            cout << "OCR output: \n" << XAB::CTextHelper::UTF2GBK(strResult) << endl;
        }
        cout << endl;



        api.End();
        pixDestroy(&image);
    }
    catch (std::exception& e)
    {
        std::cerr << "error: " << e.what() << std::endl;
    }

    return 0;
}


#endif