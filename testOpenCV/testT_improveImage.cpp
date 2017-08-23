//#define MAIN
#ifdef MAIN

#include <opencv2/opencv.hpp>
#include <iostream>
#include <string>
#include "putText.h"

using namespace cv;
using namespace std;

const std::string WindowName = "���ͼƬ";
// ������Դ: http://blog.csdn.net/dcrmg/article/details/53677739

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
        std::cout << "��ͼƬʧ��,����" << std::endl;
        return -1;
    }
    imshow("ԭͼ��", image);

    //��������
    namedWindow("���ͼƬ", 1);
    /*
    0: ֱ��ͼ
    1: ������˹
    2: ����LOG �任
    3: ٤��任
    4: �Զ���
    */

    
    // ������, ͼƬ���д������ֵĲ��ʺϽ���ģ������
    //Mat midianImage;
    //cv::medianBlur(image, midianImage, 3);
    //imshow("��ֵ�˲�", midianImage);

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
            ֱ��ͼ���⻯��ͨ������ͼ��Ļҽ׷ֲ���ʹ����0~255�ҽ��ϵķֲ����Ӿ��⣬
            �����ͼ��ĶԱȶȣ��ﵽ����ͼ�������Ӿ�Ч����Ŀ�ġ�
            �ԱȶȽϵ͵�ͼ���ʺ�ʹ��ֱ��ͼ���⻯��������ǿͼ��ϸ�ڡ�
        */
        Mat imageRGB[3];
        split(srcImage, imageRGB);
        for (int i = 0; i < 3; i++)
        {
            equalizeHist(imageRGB[i], imageRGB[i]);
        }

        merge(imageRGB, 3, dstImage);
        strTip = "����ֱ��ͼ";
        break;
    }
    case 1:
    {
        /*
            ʹ������Ϊ5��8����������˹������ͼ�������Դﵽ����ǿͼ���Ŀ��.
            ������˹���ӿ�����ǿ�ֲ���ͼ��Աȶ�
        */
        Mat kernel = (Mat_<float>(3, 3) << 0, -1, 0, 0, 5, 0, 0, -1, 0);
        filter2D(srcImage, dstImage, CV_8UC3, kernel);
        strTip = "������˹";
        break;
    }
    case 2:
    {
        /*
            �����任���Խ�ͼ��ĵͻҶ�ֵ������չ����ʾ���ͻҶȲ��ָ����ϸ�ڣ�
            ����߻Ҷ�ֵ����ѹ�������ٸ߻Ҷ�ֵ���ֵ�ϸ�ڣ��Ӷ��ﵽǿ��ͼ��ͻҶȲ��ֵ�Ŀ�ġ�
            �����任��������Աȶ�ƫ�Ͳ��һҶ�ֵƫ�͵�ͼ����ǿЧ���Ϻ�
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
        //��һ����0~255    
        normalize(imageLog, imageLog, 0, 255, CV_MINMAX);
        //ת����8bitͼ����ʾ    
        convertScaleAbs(imageLog, dstImage);
        strTip = "���ڶ����任";
        break;
    }
    case 3:
    {
        /*
            ٤��任��Ҫ����ͼ���У�������Ҷȹ��߻��߻Ҷȹ��͵�ͼƬ������������ǿ�Աȶȡ�
            �任��ʽ���Ƕ�ԭͼ����ÿһ������ֵ���˻�����
            ٤��任��ͼ�������������ʵ����ͨ����ǿ�ͻҶȻ�߻Ҷȵ�ϸ��ʵ�ֵ�
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
        ////��һ����0~255
        //normalize(imageGamma, imageGamma, 0, 255, CV_MINMAX);
        ////ת����8bitͼ����ʾ
        //convertScaleAbs(imageGamma, dstImage);

        gammaCorrection(srcImage, dstImage);

        strTip = "����٤��任";
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
        // convertTo �ڲ�ʵ��ִ�еĴ������������ʾ
        // http://docs.opencv.org/master/d3/dc1/tutorial_basic_linear_transform.html
        //srcImage.convertTo(dstImage, -1, 2.2, 50);

        srcImage.copyTo(dstImage);
        strTip = "ԭͼ";
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

    // opencv �����������
    // putText(dstImage, strTip, Point(0, 100), cv::FONT_HERSHEY_PLAIN, 1, Scalar(0, 0, 255));
    putTextZH(dstImage, strTip.data(), Point(0, 100), Scalar(0, 0, 255), 30, "΢���ź�");
    imshow(WindowName, dstImage);

    // 
    imshow("�Ҷ�ͼ", grayImage);

    // ��ֵͼ
    Mat thdImage;
    threshold(grayImage, thdImage, 0, 255, cv::THRESH_OTSU);
    imshow("��ֵ��", thdImage);

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