//#define MAIN
#ifdef MAIN

#include <opencv2/opencv.hpp>


using namespace cv;
using namespace std;


//-----------------------------------【ShowHelpText( )函数】----------------------------------
//		 描述：输出一些帮助信息
//----------------------------------------------------------------------------------------------
void ShowHelpText()
{
    //输出欢迎信息和OpenCV版本
    printf("\n\n\t\t\t非常感谢购买《OpenCV3编程入门》一书！\n");
    printf("\n\n\t\t\t此为本书OpenCV3版的第30个配套示例程序\n");
    printf("\n\n\t\t\t   当前使用的OpenCV版本为：" CV_VERSION);
    printf("\n\n  ----------------------------------------------------------------------------\n\n");
}




int main()
{
    //改变console字体颜色
    system("color 6F");

    ShowHelpText();

    //初始化
    FileStorage fs2("test.yaml", FileStorage::READ);

    // 第一种方法，对FileNode操作
    int frameCount = (int)fs2["frameCount"];

    std::string date;
    // 第二种方法，使用FileNode运算符> > 
    fs2["calibrationDate"] >> date;

    Mat cameraMatrix2, distCoeffs2;
    fs2["cameraMatrix"] >> cameraMatrix2;
    fs2["distCoeffs"] >> distCoeffs2;

    cout << "frameCount: " << frameCount << endl
        << "calibration date: " << date << endl
        << "camera matrix: " << cameraMatrix2 << endl
        << "distortion coeffs: " << distCoeffs2 << endl;

    FileNode features = fs2["features"];
    FileNodeIterator it = features.begin(), it_end = features.end();
    int idx = 0;
    std::vector<uchar> lbpval;

    //使用FileNodeIterator遍历序列
    for (; it != it_end; ++it, idx++)
    {
        cout << "feature #" << idx << ": ";
        cout << "x=" << (int)(*it)["x"] << ", y=" << (int)(*it)["y"] << ", lbp: (";
        // 我们也可以使用使用filenode > > std::vector操作符很容易的读数值阵列
        (*it)["lbp"] >> lbpval;
        for (int i = 0; i < (int)lbpval.size(); i++)
            cout << " " << (int)lbpval[i];
        cout << ")" << endl;
    }
    fs2.release();

    //程序结束，输出一些帮助文字
    printf("\n文件读取完毕，请输入任意键结束程序~");
    getchar();

    return 0;
}

#endif