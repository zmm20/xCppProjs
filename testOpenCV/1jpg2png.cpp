//#define MAIN
#ifdef MAIN

#include <opencv2/opencv.hpp>
#include <iostream>
#include <string>

using namespace cv;
using namespace std;



void createAlphaMat(Mat &dst, const Mat& src);

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        cout << "格式: 原图片1 原图片2..";
        return -1;
    }

    for (int i = 1; i < argc; ++i)
    {
        const string jpgImg(argv[i]);
        const int pos = jpgImg.find_last_of('.');
        const string pngImg(jpgImg.substr(0, pos) + ".png");

        const Mat pic1 = imread(jpgImg); //ajust.png

        //创建带alpha通道的Mat
        Mat outPic;
        createAlphaMat(outPic, pic1);
        vector<int>compression_params;
        compression_params.push_back(CV_IMWRITE_PNG_COMPRESSION);
        compression_params.push_back(9);
        //显示图片
        try {
            imwrite(pngImg, outPic, compression_params);
        }
        catch (runtime_error& ex) {
            cout << "图像转换成PNG格式发生错误：" << ex.what();
            return 1;
        }
    }
        
}


//利用imwrite函数生成带透明通道的png图像
//--------------------------------【createAlphaMat( )函数】--------------------------------
// 描述：创建带alpha通道的Mat, src 中的白色像素将被设置成全透明
//-------------------------------------------------------------------------------------------------
void createAlphaMat(Mat &dst, const Mat& src)
{
    dst.create(src.size(), CV_8UC4);

    for (int i = 0; i < dst.rows; ++i) {
        for (int j = 0; j < dst.cols; ++j) {
            Vec4b& rgba_dst = dst.at<Vec4b>(i, j);
            const Vec3b& rgba_src = src.at<Vec3b>(i, j);
            rgba_dst[0] = rgba_src[0];
            rgba_dst[1] = rgba_src[1];
            rgba_dst[2] = rgba_src[2];

            if (rgba_dst[0] == 255
                && rgba_dst[1] == 255
                && rgba_dst[2] == 255
                )
            {
                rgba_dst[3] = 0;  // 0 表示透明
            }
            else
            {
                rgba_dst[3] = saturate_cast<uchar>(255);
            }
        }
    }
}

#endif