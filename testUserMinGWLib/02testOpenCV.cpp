//#define MAIN
#ifdef MAIN

#include <opencv2/opencv.hpp>
#include <iostream>
#include <string>

using namespace std;
using namespace cv;
int main()
{
    cout << "test 1" << endl;
    {
        Mat girl = imread(".\\test\\girl.jpg"); // mix.tif
        namedWindow("【1】动漫图"); //创建一个名为 "【1】动漫图"的窗口  
        imshow("【1】动漫图", girl);//显示名为 "【1】动漫图"的窗口  
    }
    cout << endl;

    waitKey();
}

#endif