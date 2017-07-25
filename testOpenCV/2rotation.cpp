#define MAIN
#ifdef MAIN

#include <opencv2/opencv.hpp>
#include <iostream>


using namespace cv;
using namespace std;


void myRotate(Mat& srcImage, double degree);
void myRotateAndDeskewing(cv::Mat& img, double angle);


#define ERROR 1234
//度数转换
double DegreeTrans(double theta)
{
    double res = theta / CV_PI * 180;
    return res;
}

double CalcDegree(const Mat &srcImage);

int main()
{
    std::string imgPath(R"(test\p16.jpg)");
    Mat srcImage = imread(imgPath);
    if (srcImage.empty())
    {
        cerr << "打开图片失败!" << endl;
        return EXIT_FAILURE;
    }
    imshow("原始图", srcImage);

    // gray image
    Mat dstImage;
    cv::cvtColor(srcImage, dstImage, CV_BGR2GRAY);

    Mat dst;

    //倾斜角度矫正
    double degree = CalcDegree(dstImage);
    if (degree == ERROR)
    {
        cout << "矫正失败！" << endl;
        return -1;
    }

    //rotateImage(srcImage, dst, degree);
    myRotateAndDeskewing(dstImage, -degree);
    imshow("旋转后图像2", dstImage);
    cout << "angle:" << degree << endl;

    //Mat m_ResImg(srcImage);
    //myRotate(m_ResImg, 98);
    //imshow("旋转后图像1", m_ResImg);    

    waitKey(0);
}

// degree 为正, 表示顺时针旋转
void myRotate(Mat& srcImage, double degree)
{
    degree = -degree;
    const double angle = degree  * CV_PI / 180.; // 弧度
    const double a = sin(angle), b = cos(angle);
    const int width = srcImage.cols;
    const int height = srcImage.rows;
    const int width_rotate = int(height * fabs(a) + width * fabs(b));
    const int height_rotate = int(width * fabs(a) + height * fabs(b));
    //旋转数组map
    // [ m0  m1  m2 ] ===>  [ A11  A12   b1 ]
    // [ m3  m4  m5 ] ===>  [ A21  A22   b2 ]

    cv::Mat rotMat(2, 3, CV_32F);
    cv::Point center = cv::Point(srcImage.cols / 2, srcImage.rows / 2);
    const double scale = 1;
    // 通过上面的旋转细节信息求得旋转矩阵
    rotMat = getRotationMatrix2D(center, degree, scale);

    // 平移到矩形区中心中心
    rotMat.ptr<double>(0)[2] += (width_rotate - width) / 2;
    rotMat.ptr<double>(1)[2] += (height_rotate - height) / 2;

    cv::Mat img_rotate;
    //对图像做仿射变换
    warpAffine(srcImage, img_rotate, rotMat, cv::Size(width_rotate, height_rotate));
    srcImage = img_rotate;
}

// degree 为正, 表示顺时针旋转
void myRotateAndDeskewing(cv::Mat& img, double angle)
{
    // 1> 先旋转90度倍数
    const double angle_less90 = std::fmod(angle, 90);
    const double angle_large = angle - angle_less90;
    if (std::abs(angle_large) - 0.0001 > 0)
        myRotate(img, angle_large);

    if (std::abs(angle_less90) - 0.0001 <= 0)
        return;

    // 2> 旋转小角度
    cv::bitwise_not(img, img);
    std::vector<cv::Point> points;
    cv::Mat_<uchar>::iterator it = img.begin<uchar>();
    cv::Mat_<uchar>::iterator end = img.end<uchar>();
    for (; it != end; ++it)
        if (*it)
            points.push_back(it.pos());

    cv::RotatedRect box = cv::minAreaRect(cv::Mat(points));
    cv::Mat rot_mat = cv::getRotationMatrix2D(box.center, -angle_less90, 1); // 

    cv::Mat rotated;
    cv::warpAffine(img, rotated, rot_mat, img.size(), cv::INTER_CUBIC);

    cv::bitwise_not(rotated, rotated);


    // 裁剪图片
    //cv::Size box_size = box.size;
    //// RotatedRect中返回的角度angle:
    //// http://blog.csdn.net/fadefaraway/article/details/54932378
    //cout << "box.angle = " << box.angle << endl;
    //cout << "box size: width = " << box_size.width << ", height = " << box_size.height << endl;
    //if (box.angle < -45.) // 根据y 正方向
    //    std::swap(box_size.width, box_size.height);
    //cv::Mat cropped;
    //cv::getRectSubPix(rotated, box_size, box.center, cropped);
    //cropped.copyTo(img);

    rotated.copyTo(img);
}

//通过霍夫变换计算角度, 返回顺时针角度
double CalcDegree(const Mat &srcImage)
{// http://www.cnblogs.com/skyfsm/p/6902524.html
    Mat dstImage;
    Canny(srcImage, dstImage, 50, 200, 3);

    //通过霍夫变换检测直线
    vector<Vec2f> lines;
    HoughLines(dstImage, lines, 1, CV_PI / 180, 300, 0, 0);//第5个参数就是阈值，阈值越大，检测精度越高
    
    //由于图像不同，阈值不好设定，因为阈值设定过高导致无法检测直线，阈值过低直线太多，速度很慢
    //所以根据阈值由大到小设置了三个阈值，如果经过大量试验后，可以固定一个适合的阈值。
    if (!lines.size())
    {
        HoughLines(dstImage, lines, 1, CV_PI / 180, 200, 0, 0);
    }
    
    if (!lines.size())
    {
        HoughLines(dstImage, lines, 1, CV_PI / 180, 150, 0, 0);
    }
    if (!lines.size())
    {
        cout << "没有检测到直线！" << endl;
        return 0;
    }

    float sum = 0;
    //依次画出每条线段
    for (size_t i = 0; i < lines.size(); i++)
    {
        const float theta = lines[i][1];
        //只选角度最小的作为旋转角度
        sum += theta;
#ifdef MY_DEBUG
        const float rho = lines[i][0];
        Point pt1, pt2;
        const double a = cos(theta), b = sin(theta);
        const double x0 = a*rho, y0 = b*rho;
        pt1.x = cvRound(x0 + 1000 * (-b));
        pt1.y = cvRound(y0 + 1000 * (a));
        pt2.x = cvRound(x0 - 1000 * (-b));
        pt2.y = cvRound(y0 - 1000 * (a));
        line(dstImage, pt1, pt2, Scalar(55, 100, 195), 1, LINE_AA); //Scalar函数用于调节线段颜色
        imshow("直线探测效果图", dstImage);
#endif
    }
    float average = sum / lines.size(); //对所有角度求平均，这样做旋转效果会更好

    cout << "average theta:" << average << endl;
    const double angle = DegreeTrans(average) - 90;
    return angle;
}

#endif