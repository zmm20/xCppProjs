//#define MAIN
#ifdef MAIN

#include <opencv2/opencv.hpp>
#include <iostream>


using namespace cv;
using namespace std;


Mat rotateImage1(Mat img, int degree);
int main()
{
    Mat srcImage = imread("test1.jpg");
    imshow("原始图", srcImage);
    Mat m_ResImg = rotateImage1(srcImage, 90);

    //imwrite("test_out.jpg", m_ResImg);
    //namedWindow("旋转后图像", 1);
    imshow("旋转后图像", m_ResImg);

    waitKey(0);
}

Mat rotateImage1(Mat img, int degree)
{
    degree = -degree;
    double angle = degree  * CV_PI / 180.; // 弧度  
    double a = sin(angle), b = cos(angle);
    int width = img.cols;
    int height = img.rows;
    int width_rotate = int(height * fabs(a) + width * fabs(b));
    int height_rotate = int(width * fabs(a) + height * fabs(b));
    //旋转数组map
    // [ m0  m1  m2 ] ===>  [ A11  A12   b1 ]
    // [ m3  m4  m5 ] ===>  [ A21  A22   b2 ]
    float map[6];
    Mat map_matrix = Mat(2, 3, CV_32F, map);
    // 旋转中心

    Mat rotMat(2, 3, CV_32FC1);
    Point center = Point(img.cols / 2, img.rows / 2);
    double scale = 1;

    // 通过上面的旋转细节信息求得旋转矩阵
    rotMat = getRotationMatrix2D(center, degree, scale);
    // 平移变换
    rotMat.ptr<double>(0)[2] += (width_rotate - width) / 2;
    rotMat.ptr<double>(1)[2] += (height_rotate - height) / 2;

    Mat img_rotate;
    //对图像做仿射变换
    warpAffine(img, img_rotate, rotMat, Size(width_rotate, height_rotate), INTER_CUBIC);//INTER_AREA, INTER_CUBIC, INTER_LANCZOS4

    return img_rotate;
}

#endif