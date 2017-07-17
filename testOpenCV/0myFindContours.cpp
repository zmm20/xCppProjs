//#define MAIN
#ifdef MAIN

#include <opencv2/opencv.hpp>
#include <iostream>


using namespace cv;
using namespace std;

#define WINDOW_NAME "原始图"
void on_MouseHandle(int event, int x, int y, int flags, void* param);

int main(int argc, char** argv)
{
    // 【1】载入原始图，且必须以二值图模式载入
    Mat srcImage = imread("test1.jpg", IMREAD_COLOR);//IMREAD_COLOR, IMREAD_GRAYSCALE
    //namedWindow(WINDOW_NAME, WINDOW_NORMAL);
    imshow(WINDOW_NAME, srcImage);
    
    cout << "原图大小: " << srcImage.size() << endl;
    cout << "first pix: " << srcImage(Rect(0, 0, 1, 1)) << endl;
    cout << "矩阵行像素, step: " << srcImage.step << endl;
    setMouseCallback(WINDOW_NAME, on_MouseHandle, (void*)&srcImage);

    waitKey(0);

}

void on_MouseHandle(int event, int x, int y, int flags, void* param)
{

    Mat& srcImage = *(cv::Mat*) param;
    if (event != EVENT_LBUTTONDOWN)
        return;
    int minX = x - 50;
    int minY = y - 50;
    if (minX < 0)
        minX = 0;
    if (minY < 0)
        minY = 0;

    int maxX = x + 50;
    int maxY = y + 50;
    if (maxX > srcImage.cols)
        maxX = srcImage.cols;
    if (maxY > srcImage.rows)
        maxY = srcImage.rows;
    Rect roiRect = Rect(minX, minY, maxX - minX, maxY - minY);
    Mat roiImage = srcImage(roiRect);
    cout << "感兴趣区域大小: " << roiImage.size() << endl;
    
    // 转成灰度
    cvtColor(roiImage, roiImage, COLOR_BGR2GRAY);
    // 平滑
    //blur(g_grayImage, g_grayImage, Size(3, 3));

    //【3】srcImage取大于阈值119的那部分
    //roiImage = roiImage > 119;
    //filtering out pixels with too small or too large values.
    // http://blog.sina.com.cn/s/blog_154bd48ae0102wboc.html
    threshold(roiImage, roiImage, 145, 255, THRESH_BINARY);
    imshow("二值化后", roiImage);

    //【4】定义轮廓和层次结构
    vector<vector<Point> > contours;
    vector<Vec4i> hierarchy;

    Mat dstImage(100, 100, srcImage.type());
    //【5】查找轮廓
    findContours(roiImage, contours, hierarchy, RETR_LIST, CHAIN_APPROX_SIMPLE);
    for (int i = 0; i < contours.size(); ++i)
    {
        if (contours[i].size() < 4)
            continue;

        // 对给定的 2D 点集，寻找最小包围矩形
        Rect box = boundingRect(contours[i]); // minAreaRect
        
        // 找到在感兴趣区域中心点位置的轮廓
        if (!box.contains(Point(50, 50)))
            continue;

        // 一般的原点区域宽高只有10~20 像素
        if (box.width >= roiRect.width / 2 || box.height >= roiRect.height / 2)
            continue;
        cout << contours[i] << endl;
        rectangle(dstImage,
            box,
            Scalar(0, 255, 255),
            1,
            8);

        break;
    }
    imshow("test", dstImage);//srcImage
}

#endif