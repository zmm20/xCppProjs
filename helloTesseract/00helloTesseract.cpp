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

        std::string imgPath(R"(.\image\test_chi2.png)"); // test_chi2.png

        tesseract::TessBaseAPI api;
        // Initialize tesseract-ocr with English, without specifying tessdata path
        if (api.Init(NULL, "chi_sim")) {
            fprintf(stderr, "Could not initialize tesseract.\n");
            exit(1);
        }

        api.InitForAnalysePage();
        api.SetPageSegMode(tesseract::PSM_AUTO_ONLY);
        // Open input image with leptonica library
        Pix *image = pixRead(imgPath.c_str());
        api.SetImage(image);

        // Get OCR result
        outText = api.GetUTF8Text();
        printf("OCR output:\n%s", outText);
        delete[] outText;

        //double avgDeskew = 0.;
        //int nDeskew = 0;
        //QList<QRectF> rects;
        //tesseract::PageIterator* it = api.AnalyseLayout();
        //if (it && !it->Empty(tesseract::RIL_BLOCK)) {
        //    do {
        //        int x1, y1, x2, y2;
        //        tesseract::Orientation orient;
        //        tesseract::WritingDirection wdir;
        //        tesseract::TextlineOrder tlo;
        //        float deskew;
        //        it->BoundingBox(tesseract::RIL_BLOCK, &x1, &y1, &x2, &y2);
        //        it->Orientation(&orient, &wdir, &tlo, &deskew);
        //        avgDeskew += deskew;
        //        ++nDeskew;
        //        float width = x2 - x1, height = y2 - y1;
        //        if (width > 10 && height > 10) {
        //            //rects.append(QRectF(x1 - 0.5 * img.width(), y1 - 0.5 * img.height(), width, height));
        //        }
        //    } while (it->Next(tesseract::RIL_BLOCK));
        //}
        //delete it;

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