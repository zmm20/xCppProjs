//#define MAIN
#ifdef MAIN

#include <opencv2/opencv.hpp>
#include <iostream>
#include <string>
#include "putText.h"

using namespace cv;
using namespace std;

void on_trackbar(int, void*);
void gammaCorrection(const Mat &img, Mat& dst);
int main()
{
    // dota.jpg, test_chi2_dpi.png, m20.jpg, test1.jpg, color2.png
    // test_chi2_dpi.png
    std::string imgPath(R"(test\dota.jpg)");

    Mat image = imread(imgPath.data(), 1);
    if (image.empty())
    {
        std::cout << "��ͼƬʧ��,����" << std::endl;
        return -1;
    }
    imshow("ԭͼ��", image);

    //��������
    namedWindow("���ͼƬ", 1);

    int iMorphTypes = 0;
    createTrackbar("trackbar", "���ͼƬ", &iMorphTypes, 6, on_trackbar, &image);
    on_trackbar(0, &image);

    waitKey();
}

void on_trackbar(int iMorphTypes, void* userData)
{
    Mat dstImage;
    /*
        http://blog.csdn.net/poem_qianmo/article/details/24599073
        MORPH_OPEN �C �����㣨Opening operation��
        MORPH_CLOSE �C �����㣨Closing operation��
        MORPH_GRADIENT -��̬ѧ�ݶȣ�Morphological gradient��
        MORPH_TOPHAT - ����ñ������Top hat����
        MORPH_BLACKHAT - ����ñ������Black hat����
    */
    MORPH_OPEN;

    Mat kernel = getStructuringElement(cv::MorphShapes::MORPH_CROSS, Size(3, 3));
    morphologyEx(*(Mat*)userData, dstImage, iMorphTypes, kernel);
    
    String text;
    switch (iMorphTypes)
    {
    case MORPH_ERODE:
        text = "MORPH_ERODE";
        break;
    case MORPH_DILATE:
        text = "MORPH_DILATE";
        break;
    case MORPH_OPEN:
        text = "MORPH_OPEN";
        break;
    case MORPH_CLOSE:
        text = "MORPH_CLOSE";
        break;
    case MORPH_GRADIENT:
        text = "MORPH_GRADIENT";
        break;
    case MORPH_TOPHAT:
        text = "MORPH_TOPHAT";
        break;
    case MORPH_BLACKHAT:
        text = "MORPH_BLACKHAT";
        break;
    }
    putText(dstImage, text, Point(0, 100), HersheyFonts::FONT_HERSHEY_SIMPLEX, 1, Scalar(0, 0, 255));


    imshow("���ͼƬ", dstImage);

    //Mat gammaImage;
    //gammaCorrection(dstImage, gammaImage);
    //imshow("����٤��任", gammaImage);
}

void gammaCorrection(const Mat &img, Mat& dst)
{
    //![changing-contrast-brightness-gamma-correction]
    double gamma_ = 3;

    Mat lookUpTable(1, 256, CV_8U);
    uchar* p = lookUpTable.ptr();
    for (int i = 0; i < 256; ++i)
        p[i] = saturate_cast<uchar>(pow(i / 255.0, gamma_) * 255.0);

    dst = img.clone();
    LUT(img, lookUpTable, dst); // http://docs.opencv.org/master/d2/de8/group__core__array.html#gab55b8d062b7f5587720ede032d34156f
}
#endif