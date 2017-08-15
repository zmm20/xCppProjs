// helloTesseract.cpp : 定义控制台应用程序的入口点。
//
#define MAIN
#ifdef MAIN

#include "stdafx.h"
#include <iostream>
#include <tesseract/api/baseapi.h>
#include <tesseract/api/renderer.h>

#include <leptonica/allheaders.h>
#include <my/TextHelper.h>
#include <vector>

using namespace std;
using namespace tesseract;
int main()
{
    cout << "---------testCTextDetector.cpp-------------" << endl;

    try
    {
        std::string imgPath(R"(C:\Users\zmm\AppData\Local\Temp\pdfimage_0000_001.jpg)"); // test_chi2.png
        //std::string imgPath(R"(.\image\test_chi2.png)"); // 该tif 中含有2 副图片, 默认只识别第一幅图片

        tesseract::TessBaseAPI api;
        // Initialize tesseract-ocr with English, without specifying tessdata path
        if (api.Init(NULL, "chi_sim")) {
            fprintf(stderr, "Could not initialize tesseract.\n");
            exit(1);
        }        
        
        cout << "开始识别..." << endl;
        cout << "test 1" << endl;
        {
            // Open input image with leptonica library
            Pix *image = pixRead(imgPath.c_str());
            api.SetImage(image);
            pixDestroy(&image);

            // test
            api.SetSourceResolution(72);
            cout << "image y resolution: " << api.GetSourceYResolution() << endl;
            
            api.InitForAnalysePage();
            api.SetPageSegMode(tesseract::PSM_AUTO_ONLY);

            // Get OCR result
            char *outText = api.GetUTF8Text();
            const std::string strResult(outText);
            delete[] outText;
            cout << "OCR output: \n" << XAB::CTextHelper::UTF2GBK(strResult) << endl;
        }
        cout << endl;

        cout << "test 2" << endl;
        {
            //api.InitForAnalysePage();
            //api.SetPageSegMode(tesseract::PSM_AUTO_ONLY);

            ////tesseract::TessResultRenderer;
            //tesseract::TessTextRenderer render("stdout");
            //bool succeed = api.ProcessPages(imgPath.c_str(), NULL, 0, &render);
            //if (!succeed) {
            //    fprintf(stderr, "Error during processing.\n");
            //    return EXIT_FAILURE;
            //}
            
        }
        cout << endl;

        cout << "test 3" << endl;
        {
            //// Open input image with leptonica library
            //Pix *image = pixRead(imgPath.c_str());
            //api.SetImage(image);
            //pixDestroy(&image);

            //api.InitForAnalysePage();
            //api.SetPageSegMode(tesseract::PSM_AUTO_ONLY);

        }


        api.End();
        
    }
    catch (std::exception& e)
    {
        std::cerr << "error: " << e.what() << std::endl;
    }

    return 0;
}


#endif