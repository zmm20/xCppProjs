//#define MAIN
#ifdef MAIN

#include <opencv2/opencv.hpp>

using namespace cv;

int main()
{
    VideoCapture capture;
    capture.open("1.avi"); // ���������0, ��ʾ������ͷ������Ƶ

    // ѭ����ʾÿһ֡
    while (1)
    {
        Mat frame; // ���ڴ洢ÿһ֡��ͼ��
        capture >> frame;
        imshow("��ȡ��Ƶ", frame);

        waitKey(30);
    }
}
#endif