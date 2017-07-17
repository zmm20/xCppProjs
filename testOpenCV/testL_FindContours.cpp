//#define MAIN
#ifdef MAIN

#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;


int main(int argc, char** argv)
{
    // ��1������ԭʼͼ���ұ����Զ�ֵͼģʽ����
    Mat srcImage = imread("test1.jpg", 0);
    imshow("ԭʼͼ", srcImage);

    //��2����ʼ�����ͼ
    Mat dstImage = Mat::zeros(srcImage.rows, srcImage.cols, CV_8UC3);

    //��3��srcImageȡ������ֵ119���ǲ���
    srcImage = srcImage > 119;
    imshow("ȡ��ֵ���ԭʼͼ", srcImage);

    //��4�����������Ͳ�νṹ
    vector<vector<Point> > contours;
    vector<Vec4i> hierarchy;

    //��5����������
    //�˾�����OpenCV2��Ϊ��
    //findContours( srcImage, contours, hierarchy,CV_RETR_CCOMP, CV_CHAIN_APPROX_SIMPLE );
    //�˾�����OpenCV3��Ϊ��
    findContours(srcImage, contours, hierarchy, RETR_CCOMP, CHAIN_APPROX_SIMPLE);

    // ��6���������ж���������� �������ɫ���Ƴ�ÿ�����������ɫ
    int index = 0;
    for (; index >= 0; index = hierarchy[index][0])
    {
    Scalar color(rand() & 255, rand() & 255, rand() & 255);
    //�˾�����OpenCV2��Ϊ��
    //drawContours( dstImage, contours, index, color, CV_FILLED, 8, hierarchy );
    //�˾�����OpenCV3��Ϊ��
    drawContours(dstImage, contours, index, color, FILLED, 8, hierarchy);
    }

    //��7����ʾ��������ͼ
    imshow("����ͼ", dstImage);

    waitKey(0);

}

#endif