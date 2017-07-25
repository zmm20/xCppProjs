#define MAIN
#ifdef MAIN

#include <opencv2/opencv.hpp>
#include <iostream>


using namespace cv;
using namespace std;


void myRotate(Mat& srcImage, double degree);
void myRotateAndDeskewing(cv::Mat& img, double angle);


#define ERROR 1234
//����ת��
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
        cerr << "��ͼƬʧ��!" << endl;
        return EXIT_FAILURE;
    }
    imshow("ԭʼͼ", srcImage);

    // gray image
    Mat dstImage;
    cv::cvtColor(srcImage, dstImage, CV_BGR2GRAY);

    Mat dst;

    //��б�ǶȽ���
    double degree = CalcDegree(dstImage);
    if (degree == ERROR)
    {
        cout << "����ʧ�ܣ�" << endl;
        return -1;
    }

    //rotateImage(srcImage, dst, degree);
    myRotateAndDeskewing(dstImage, -degree);
    imshow("��ת��ͼ��2", dstImage);
    cout << "angle:" << degree << endl;

    //Mat m_ResImg(srcImage);
    //myRotate(m_ResImg, 98);
    //imshow("��ת��ͼ��1", m_ResImg);    

    waitKey(0);
}

// degree Ϊ��, ��ʾ˳ʱ����ת
void myRotate(Mat& srcImage, double degree)
{
    degree = -degree;
    const double angle = degree  * CV_PI / 180.; // ����
    const double a = sin(angle), b = cos(angle);
    const int width = srcImage.cols;
    const int height = srcImage.rows;
    const int width_rotate = int(height * fabs(a) + width * fabs(b));
    const int height_rotate = int(width * fabs(a) + height * fabs(b));
    //��ת����map
    // [ m0  m1  m2 ] ===>  [ A11  A12   b1 ]
    // [ m3  m4  m5 ] ===>  [ A21  A22   b2 ]

    cv::Mat rotMat(2, 3, CV_32F);
    cv::Point center = cv::Point(srcImage.cols / 2, srcImage.rows / 2);
    const double scale = 1;
    // ͨ���������תϸ����Ϣ�����ת����
    rotMat = getRotationMatrix2D(center, degree, scale);

    // ƽ�Ƶ���������������
    rotMat.ptr<double>(0)[2] += (width_rotate - width) / 2;
    rotMat.ptr<double>(1)[2] += (height_rotate - height) / 2;

    cv::Mat img_rotate;
    //��ͼ��������任
    warpAffine(srcImage, img_rotate, rotMat, cv::Size(width_rotate, height_rotate));
    srcImage = img_rotate;
}

// degree Ϊ��, ��ʾ˳ʱ����ת
void myRotateAndDeskewing(cv::Mat& img, double angle)
{
    // 1> ����ת90�ȱ���
    const double angle_less90 = std::fmod(angle, 90);
    const double angle_large = angle - angle_less90;
    if (std::abs(angle_large) - 0.0001 > 0)
        myRotate(img, angle_large);

    if (std::abs(angle_less90) - 0.0001 <= 0)
        return;

    // 2> ��תС�Ƕ�
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


    // �ü�ͼƬ
    //cv::Size box_size = box.size;
    //// RotatedRect�з��صĽǶ�angle:
    //// http://blog.csdn.net/fadefaraway/article/details/54932378
    //cout << "box.angle = " << box.angle << endl;
    //cout << "box size: width = " << box_size.width << ", height = " << box_size.height << endl;
    //if (box.angle < -45.) // ����y ������
    //    std::swap(box_size.width, box_size.height);
    //cv::Mat cropped;
    //cv::getRectSubPix(rotated, box_size, box.center, cropped);
    //cropped.copyTo(img);

    rotated.copyTo(img);
}

//ͨ������任����Ƕ�, ����˳ʱ��Ƕ�
double CalcDegree(const Mat &srcImage)
{// http://www.cnblogs.com/skyfsm/p/6902524.html
    Mat dstImage;
    Canny(srcImage, dstImage, 50, 200, 3);

    //ͨ������任���ֱ��
    vector<Vec2f> lines;
    HoughLines(dstImage, lines, 1, CV_PI / 180, 300, 0, 0);//��5������������ֵ����ֵԽ�󣬼�⾫��Խ��
    
    //����ͼ��ͬ����ֵ�����趨����Ϊ��ֵ�趨���ߵ����޷����ֱ�ߣ���ֵ����ֱ��̫�࣬�ٶȺ���
    //���Ը�����ֵ�ɴ�С������������ֵ�����������������󣬿��Թ̶�һ���ʺϵ���ֵ��
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
        cout << "û�м�⵽ֱ�ߣ�" << endl;
        return 0;
    }

    float sum = 0;
    //���λ���ÿ���߶�
    for (size_t i = 0; i < lines.size(); i++)
    {
        const float theta = lines[i][1];
        //ֻѡ�Ƕ���С����Ϊ��ת�Ƕ�
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
        line(dstImage, pt1, pt2, Scalar(55, 100, 195), 1, LINE_AA); //Scalar�������ڵ����߶���ɫ
        imshow("ֱ��̽��Ч��ͼ", dstImage);
#endif
    }
    float average = sum / lines.size(); //�����нǶ���ƽ������������תЧ�������

    cout << "average theta:" << average << endl;
    const double angle = DegreeTrans(average) - 90;
    return angle;
}

#endif