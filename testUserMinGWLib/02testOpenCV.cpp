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
        namedWindow("��1������ͼ"); //����һ����Ϊ "��1������ͼ"�Ĵ���  
        imshow("��1������ͼ", girl);//��ʾ��Ϊ "��1������ͼ"�Ĵ���  
    }
    cout << endl;

    waitKey();
}

#endif