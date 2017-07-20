// helloTesseract.cpp : 定义控制台应用程序的入口点。
//
#define MAIN
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

        api.InitForAnalysePage();
        api.SetPageSegMode(tesseract::PSM_AUTO_ONLY);
        
        // Open input image with leptonica library
        Pix *image = pixRead(imgPath.c_str());
        api.SetImage(image);

        cout << "开始识别..." << endl;
        // Get OCR result
        //char *outText = api.GetUTF8Text();
        //const std::string strResult(outText);
        //delete[] outText;
        //cout << "OCR output: \n" << XAB::CTextHelper::UTF2GBK(strResult) << endl;


        vector<Box> boxList;
        double avgDeskew = 0.;
        int nDeskew = 0;
        tesseract::PageIterator* it = api.AnalyseLayout();
        if (it && !it->Empty(tesseract::RIL_BLOCK)) 
        {
            do {
                int x1, y1, x2, y2;
                tesseract::Orientation orient;
                tesseract::WritingDirection wdir;
                tesseract::TextlineOrder tlo;
                float deskew;
                it->BoundingBox(tesseract::RIL_BLOCK, &x1, &y1, &x2, &y2);
                it->Orientation(&orient, &wdir, &tlo, &deskew);

                avgDeskew += deskew;
                ++nDeskew;

                float width = x2 - x1, height = y2 - y1;
                if (width > 10 && height > 10) 
                {
                    Box b;
                    b.x = x1;
                    b.y = y1;
                    b.w = width;
                    b.h = height;
                    boxList.push_back(std::move(b));
                }
            } while (it->Next(tesseract::RIL_BLOCK));
        }
        delete it;
        cout << "nDeskew = " << nDeskew << ", avgDeskew = " << avgDeskew << ", boxList size = " << boxList.size() << endl;
        for (const auto& item : boxList)
        {
            cout << "box : x = " << item.x << ", y = " << item.y << ", w = " << item.w << ", h = " << item.h << endl;
        }


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