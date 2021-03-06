#define MAIN
#ifdef MAIN

#include <stdio.h>
#include <opencv2/opencv.hpp>
#include <fstream>

using namespace std;
using namespace cv;

int main()
{
    //-----------------------------------【一、图像的载入和显示】---------------------------------
    //	描述：以下三行代码用于完成图像的载入和显示
    //--------------------------------------------------------------------------------------------------

    cout << "test 1" << endl;
    {
        Mat girl = imread(".\\test\\phototest.tif");// girl.jpg
        namedWindow("【1】动漫图"); //创建一个名为 "【1】动漫图"的窗口  
        imshow("【1】动漫图", girl);//显示名为 "【1】动漫图"的窗口  

        // 保存成内存流
        //(1) jpeg compression 
        vector<uchar> buff;//buffer for coding 
        vector<int> param = vector<int>(2);
        param[0] = CV_IMWRITE_JPEG_QUALITY;
        param[1] = 95;//default(95) 0-100 

        imencode(".jpg", girl, buff, param);
        cout << "coded file size(jpg)" << buff.size() << endl;//fit buff size automatically. 
        Mat jpegimage = imdecode(Mat(buff), CV_LOAD_IMAGE_COLOR);
        imshow("memory image", jpegimage);

        ofstream ofs(".\\test\\out.jpg", ios::trunc | ios::binary);
        ofs.write((char*)buff.data(), buff.size());
    }
    cout << endl;

    cout << "test 2" << endl;
    {
        // 从内存中加载图片
        //ifstream is("girl.jpg", ios::binary);
        //if (!is)
        //{
        //    cerr << "图片打开失败!" << endl;
        //}

        //is.seekg(0, is.end);
        //const int fileSize = is.tellg();
        //is.seekg(0, is.beg);

        //std::string str;
        //str.resize(fileSize, ' '); // reserve space
        //char* begin = &*str.begin();

        //is.read(begin, fileSize);
        //is.close();

        //std::vector<uchar> data(str.begin(), str.end());
        //Mat girl = imdecode(data, CV_LOAD_IMAGE_COLOR);
        //namedWindow("从内存中加载图片"); 
        //imshow("从内存中加载图片", girl);
    }
    cout << endl;

    cout << "test 3" << endl;
    {
        //Mat mix = imread(".\\test\\mix.tif"); // 尝试加载多页的tif 文件
        //namedWindow("多页图"); //创建一个名为 "【1】动漫图"的窗口  
        //imshow("多页图", mix);//显示名为 "【1】动漫图"的窗口  
    }
    cout << endl;

    waitKey();
    return 0;

    //-----------------------------------【二、初级图像混合】--------------------------------------
    //	描述：二、初级图像混合
    //--------------------------------------------------------------------------------------------------
    //载入图片
    Mat image = imread("dota.jpg");//, 199  // 如果按书本中的版本, 199是错误的.
    Mat logo = imread("dota_logo.jpg");
    if (!image.data || !logo.data)
    {
        printf("载入失败\n");
        return -1;
    }

    //载入后先显示
    namedWindow("【2】原画图");
    imshow("【2】原画图", image);

    namedWindow("【3】logo图");
    imshow("【3】logo图", logo);


    // 定义一个Mat类型，用于存放，图像的ROI
    Mat imageROI;
    //方法一
    imageROI = image(Rect(800, 350, logo.cols, logo.rows));
    //方法二
    //imageROI= image(Range(350,350+logo.rows),Range(800,800+logo.cols));

    // 将logo加到原图上
    addWeighted(imageROI, 0.5, logo, 0.3, 0., imageROI);

    //显示结果
    namedWindow("【4】原画+logo图");
    imshow("【4】原画+logo图", image);

    //-----------------------------------【三、图像的输出】--------------------------------------
    //	描述：将一个Mat图像输出到图像文件
    //-----------------------------------------------------------------------------------------------
    //输出一张jpg图片到工程目录下
    imwrite("由imwrite生成的图片.jpg", image);
    

    waitKey();

}
#endif