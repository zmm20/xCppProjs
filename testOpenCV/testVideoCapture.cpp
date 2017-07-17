//#define MAIN
#ifdef MAIN

#include <opencv2/opencv.hpp>

using namespace cv;

int main()
{
    VideoCapture capture;
    capture.open("1.avi"); // 如果参数是0, 表示从摄像头读入视频

    // 循环显示每一帧
    while (1)
    {
        Mat frame; // 用于存储每一帧的图像
        capture >> frame;
        imshow("读取视频", frame);

        waitKey(30);
    }
}
#endif