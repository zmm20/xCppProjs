//#define MAIN
#ifdef MAIN

#include <opencv2/opencv.hpp>
#include <iostream>


using namespace cv;
using namespace std;

#define WINDOW_NAME "ԭʼͼ"
void on_MouseHandle(int event, int x, int y, int flags, void* param);

int main(int argc, char** argv)
{
    // ��1������ԭʼͼ���ұ����Զ�ֵͼģʽ����
    Mat srcImage = imread("test1.jpg", IMREAD_COLOR);//IMREAD_COLOR, IMREAD_GRAYSCALE
    //namedWindow(WINDOW_NAME, WINDOW_NORMAL);
    imshow(WINDOW_NAME, srcImage);
    
    cout << "ԭͼ��С: " << srcImage.size() << endl;
    cout << "first pix: " << srcImage(Rect(0, 0, 1, 1)) << endl;
    cout << "����������, step: " << srcImage.step << endl;
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
    cout << "����Ȥ�����С: " << roiImage.size() << endl;
    
    // ת�ɻҶ�
    cvtColor(roiImage, roiImage, COLOR_BGR2GRAY);
    // ƽ��
    //blur(g_grayImage, g_grayImage, Size(3, 3));

    //��3��srcImageȡ������ֵ119���ǲ���
    //roiImage = roiImage > 119;
    //filtering out pixels with too small or too large values.
    // http://blog.sina.com.cn/s/blog_154bd48ae0102wboc.html
    threshold(roiImage, roiImage, 145, 255, THRESH_BINARY);
    imshow("��ֵ����", roiImage);

    //��4�����������Ͳ�νṹ
    vector<vector<Point> > contours;
    vector<Vec4i> hierarchy;

    Mat dstImage(100, 100, srcImage.type());
    //��5����������
    findContours(roiImage, contours, hierarchy, RETR_LIST, CHAIN_APPROX_SIMPLE);
    for (int i = 0; i < contours.size(); ++i)
    {
        if (contours[i].size() < 4)
            continue;

        // �Ը����� 2D �㼯��Ѱ����С��Χ����
        Rect box = boundingRect(contours[i]); // minAreaRect
        
        // �ҵ��ڸ���Ȥ�������ĵ�λ�õ�����
        if (!box.contains(Point(50, 50)))
            continue;

        // һ���ԭ��������ֻ��10~20 ����
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