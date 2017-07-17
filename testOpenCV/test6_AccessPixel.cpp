//#define MAIN
#ifdef MAIN

#include <opencv2/opencv.hpp>


using namespace cv;
using namespace std;

//-----------------------------------【全局函数声明部分】-----------------------------------
//          描述：全局函数声明
//-----------------------------------------------------------------------------------------------
void colorReduce(Mat& inputImage, Mat& outputImage, int div);
void colorReduce2(Mat& inputImage, Mat& outputImage, int div);
void colorReduce3(Mat& inputImage, Mat& outputImage, int div);
void ShowHelpText();



//--------------------------------------【main( )函数】---------------------------------------
//          描述：控制台应用程序的入口函数，我们的程序从这里开始执行
//-----------------------------------------------------------------------------------------------
int main()
{
    //【1】创建原始图并显示
    Mat srcImage = imread("1.jpg");
    imshow("原始图像", srcImage);

    //【2】按原始图的参数规格来创建创建效果图
    Mat dstImage;
    // create 会开拓内存空间, 而在colorReduce函数中使用clone 已经开拓了内存空间
    //dstImage.create(srcImage.rows, srcImage.cols, srcImage.type());//效果图的大小、类型与原图片相同 

    ShowHelpText();
    
    //【4】调用颜色空间缩减函数
    colorReduce(srcImage, dstImage, 32);

    colorReduce2(srcImage, dstImage, 32);

    colorReduce3(srcImage, dstImage, 32);

    
    //【6】显示效果图
    imshow("效果图", dstImage);
    waitKey(0);
}


//---------------------------------【colorReduce( )函数】---------------------------------
//          描述：使用【指针访问：C操作符[ ]】方法版的颜色空间缩减函数
//----------------------------------------------------------------------------------------------
void colorReduce(Mat& inputImage, Mat& outputImage, int div)
{
    //【3】记录起始时间
    double time0 = static_cast<double>(getTickCount());

    //参数准备
    outputImage = inputImage.clone();  //拷贝实参到临时变量
    int rowNumber = outputImage.rows;  //行数
    int colNumber = outputImage.cols*outputImage.channels();  //列数 x 通道数=每一行元素的个数

                                                              //双重循环，遍历所有的像素值
    for (int i = 0; i < rowNumber; i++)  //行循环
    {
        uchar* data = outputImage.ptr<uchar>(i);  //获取第i行的首地址
        for (int j = 0; j < colNumber; j++)   //列循环
        {
            // ---------【开始处理每个像素】-------------     
            data[j] = data[j] / div*div + div / 2;
            // ----------【处理结束】---------------------
        }  //行处理结束
    }

    //【5】计算运行时间并输出
    time0 = ((double)getTickCount() - time0) / getTickFrequency();
    cout << "\t此方法运行时间为： " << time0 << "秒" << endl;  //输出运行时间
}



//-------------------------------------【colorReduce( )函数】-----------------------------
//		描述：使用【迭代器】方法版的颜色空间缩减函数
//----------------------------------------------------------------------------------------------
void colorReduce2(Mat& inputImage, Mat& outputImage, int div)
{
    //【3】记录起始时间
    double time0 = static_cast<double>(getTickCount());

    //参数准备
    outputImage = inputImage.clone();  //拷贝实参到临时变量
                                       //获取迭代器
    Mat_<Vec3b>::iterator it = outputImage.begin<Vec3b>();  //初始位置的迭代器
    Mat_<Vec3b>::iterator itend = outputImage.end<Vec3b>();  //终止位置的迭代器

                                                             //存取彩色图像像素
    for (; it != itend; ++it)
    {
        // ------------------------【开始处理每个像素】--------------------
        (*it)[0] = (*it)[0] / div*div + div / 2;
        (*it)[1] = (*it)[1] / div*div + div / 2;
        (*it)[2] = (*it)[2] / div*div + div / 2;
        // ------------------------【处理结束】----------------------------
    }

    //【5】计算运行时间并输出
    time0 = ((double)getTickCount() - time0) / getTickFrequency();
    cout << "\t此方法运行时间为： " << time0 << "秒" << endl;  //输出运行时间
}

//----------------------------------【colorReduce( )函数】-------------------------------
//          描述：使用【动态地址运算配合at】方法版本的颜色空间缩减函数
//----------------------------------------------------------------------------------------------
void colorReduce3(Mat& inputImage, Mat& outputImage, int div)
{
    //【3】记录起始时间
    double time0 = static_cast<double>(getTickCount());

    //参数准备
    outputImage = inputImage.clone();  //拷贝实参到临时变量
    int rowNumber = outputImage.rows;  //行数
    int colNumber = outputImage.cols;  //列数

    //存取彩色图像像素
    for (int i = 0; i < rowNumber; i++)
    {
        for (int j = 0; j < colNumber; j++)
        {
            // ------------------------【开始处理每个像素】--------------------
            outputImage.at<Vec3b>(i, j)[0] = outputImage.at<Vec3b>(i, j)[0] / div*div + div / 2;  //蓝色通道
            outputImage.at<Vec3b>(i, j)[1] = outputImage.at<Vec3b>(i, j)[1] / div*div + div / 2;  //绿色通道
            outputImage.at<Vec3b>(i, j)[2] = outputImage.at<Vec3b>(i, j)[2] / div*div + div / 2;  //红是通道
            // -------------------------【处理结束】----------------------------
        }  // 行处理结束     
    }

    //【5】计算运行时间并输出
    time0 = ((double)getTickCount() - time0) / getTickFrequency();
    cout << "\t此方法运行时间为： " << time0 << "秒" << endl;  //输出运行时间
}


//-----------------------------------【ShowHelpText( )函数】----------------------------------
//          描述：输出一些帮助信息
//----------------------------------------------------------------------------------------------
void ShowHelpText()
{
    //输出欢迎信息和OpenCV版本
    printf("\n\n\t\t\t非常感谢购买《OpenCV3编程入门》一书！\n");
    printf("\n\n\t\t\t此为本书OpenCV3版的第21个配套示例程序\n");
    printf("\n\n\t\t\t   当前使用的OpenCV版本为：" CV_VERSION);
    printf("\n\n  ----------------------------------------------------------------------------\n");
}

#endif