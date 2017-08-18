//#define MAIN
#ifdef MAIN

#include <opencv2/opencv.hpp>
#include <iostream>
#include <string>
#include "putText.h"

using namespace cv;
using namespace std;

const std::string WindowName = "结果图片";
// 例子来源: http://blog.csdn.net/dcrmg/article/details/53677739

void gammaCorrection(const Mat &img, Mat& dst);
void on_Trackbar(int, void* userData);
int main()
{
    cout << "----testT_improveImage.cpp-------------" << endl;

    // dota.jpg, test_chi2_dpi.png, m20.jpg, test1.jpg, color2.png
    std::string imgPath(R"(test\eng1.jpg)");

    Mat image = imread(imgPath.data(), 1);
    if (image.empty())
    {
        std::cout << "打开图片失败,请检查" << std::endl;
        return -1;
    }
    imshow("原图像", image);

    //创建窗体
    namedWindow("结果图片", 1);
    /*
    0: 直方图
    1: 拉普拉斯
    2: 对数LOG 变换
    3: 伽马变换
    4: 自定义
    */

    
    // 经测试, 图片中有大量文字的不适合进行模糊操作
    //Mat midianImage;
    //cv::medianBlur(image, midianImage, 3);
    //imshow("中值滤波", midianImage);

    //Mat closeImage;
    //Mat kernel = getStructuringElement(cv::MorphShapes::MORPH_CROSS, Size(3, 3));
    //morphologyEx(image, closeImage, MORPH_CLOSE, kernel);

    int typeId = 3;
    createTrackbar("trackba", WindowName, &typeId, 4, on_Trackbar, &image);
    on_Trackbar(typeId, &image);


    cout << "test 1" << endl;
    {
        
    }
    cout << endl;


    waitKey();
}

void on_Trackbar(int typeId, void* userData)
{
    const Mat& srcImage = *((Mat*)userData);
    Mat dstImage, grayImage;

    std::string strTip;
    switch (typeId)
    {
    case 0:
    {
        /*
            直方图均衡化是通过调整图像的灰阶分布，使得在0~255灰阶上的分布更加均衡，
            提高了图像的对比度，达到改善图像主观视觉效果的目的。
            对比度较低的图像适合使用直方图均衡化方法来增强图像细节。
        */
        Mat imageRGB[3];
        split(srcImage, imageRGB);
        for (int i = 0; i < 3; i++)
        {
            equalizeHist(imageRGB[i], imageRGB[i]);
        }

        merge(imageRGB, 3, dstImage);
        strTip = "基于直方图";
        break;
    }
    case 1:
    {
        /*
            使用中心为5的8邻域拉普拉斯算子与图像卷积可以达到锐化增强图像的目的.
            拉普拉斯算子可以增强局部的图像对比度
        */
        Mat kernel = (Mat_<float>(3, 3) << 0, -1, 0, 0, 5, 0, 0, -1, 0);
        filter2D(srcImage, dstImage, CV_8UC3, kernel);
        strTip = "拉普拉斯";
        break;
    }
    case 2:
    {
        /*
            对数变换可以将图像的低灰度值部分扩展，显示出低灰度部分更多的细节，
            将其高灰度值部分压缩，减少高灰度值部分的细节，从而达到强调图像低灰度部分的目的。
            对数变换对于整体对比度偏低并且灰度值偏低的图像增强效果较好
        */
        Mat imageLog(srcImage.size(), CV_32FC3);
        for (int i = 0; i < srcImage.rows; i++)
        {
            for (int j = 0; j < srcImage.cols; j++)
            {
                imageLog.at<Vec3f>(i, j)[0] = log(1 + srcImage.at<Vec3b>(i, j)[0]);
                imageLog.at<Vec3f>(i, j)[1] = log(1 + srcImage.at<Vec3b>(i, j)[1]);
                imageLog.at<Vec3f>(i, j)[2] = log(1 + srcImage.at<Vec3b>(i, j)[2]);
            }
        }
        //归一化到0~255    
        normalize(imageLog, imageLog, 0, 255, CV_MINMAX);
        //转换成8bit图像显示    
        convertScaleAbs(imageLog, dstImage);
        strTip = "基于对数变换";
        break;
    }
    case 3:
    {
        /*
            伽马变换主要用于图像的校正，将灰度过高或者灰度过低的图片进行修正，增强对比度。
            变换公式就是对原图像上每一个像素值做乘积运算
            伽马变换对图像的修正作用其实就是通过增强低灰度或高灰度的细节实现的
        */        
        //Mat imageGamma(srcImage.size(), CV_32FC3);        
        //for (int i = 0; i < srcImage.rows; i++)
        //{
        //    for (int j = 0; j < srcImage.cols; j++)
        //    {
        //        imageGamma.at<Vec3f>(i, j)[0] = (srcImage.at<Vec3b>(i, j)[0])*(srcImage.at<Vec3b>(i, j)[0])*(srcImage.at<Vec3b>(i, j)[0]);
        //        imageGamma.at<Vec3f>(i, j)[1] = (srcImage.at<Vec3b>(i, j)[1])*(srcImage.at<Vec3b>(i, j)[1])*(srcImage.at<Vec3b>(i, j)[1]);
        //        imageGamma.at<Vec3f>(i, j)[2] = (srcImage.at<Vec3b>(i, j)[2])*(srcImage.at<Vec3b>(i, j)[2])*(srcImage.at<Vec3b>(i, j)[2]);
        //    }
        //}
        ////归一化到0~255
        //normalize(imageGamma, imageGamma, 0, 255, CV_MINMAX);
        ////转换成8bit图像显示
        //convertScaleAbs(imageGamma, dstImage);

        gammaCorrection(srcImage, dstImage);

        strTip = "基于伽马变换";
        break;
    }
    default:
    {
        /*
            for( int y = 0; y < image.rows; y++ ) {
                for( int x = 0; x < image.cols; x++ ) {
                        for( int c = 0; c < 3; c++ ) {
                            new_image.at<Vec3b>(y,x)[c] =
                              saturate_cast<uchar>( alpha*( image.at<Vec3b>(y,x)[c] ) + beta );
                        }
                    }
                }
        */
        // convertTo 内部实际执行的代码就是如上所示
        // http://docs.opencv.org/master/d3/dc1/tutorial_basic_linear_transform.html
        //srcImage.convertTo(dstImage, -1, 2.2, 50);

        srcImage.copyTo(dstImage);
        strTip = "原图";
    }
    }
    cvtColor(dstImage, grayImage, CV_BGR2GRAY);

    //cv::HersheyFonts;
    //int fontFace = FONT_HERSHEY_SCRIPT_SIMPLEX;
    //double fontScale = 1;
    //int thickness = 1;
    //int baseline = 0;
    //Size textSize = getTextSize(strTip, fontFace, fontScale, thickness, &baseline);
    //baseline += thickness;
    //putText(dstImage, strTip, Point(0, 100), fontFace, fontScale, Scalar(0, 0, 255), thickness, 8);

    // opencv 不能输出中文
    // putText(dstImage, strTip, Point(0, 100), cv::FONT_HERSHEY_PLAIN, 1, Scalar(0, 0, 255));
    putTextZH(dstImage, strTip.data(), Point(0, 100), Scalar(0, 0, 255), 30, "微软雅黑");
    imshow(WindowName, dstImage);

    // 
    imshow("灰度图", grayImage);

    // 二值图
    Mat thdImage;
    threshold(grayImage, thdImage, 0, 255, cv::THRESH_OTSU);
    imshow("二值化", thdImage);

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