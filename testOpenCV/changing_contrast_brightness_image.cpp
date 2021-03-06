//#define MAIN
#ifdef MAIN


#include <iostream>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
/*
    本例子来源: http://docs.opencv.org/master/d3/dc1/tutorial_basic_linear_transform.html
*/
using namespace std;
using namespace cv;

// C++ 新的标准中提倡使用匿名命名空间, 而不推荐使用static,因为static用在不同的地方,涵义不同,容易造成混淆. 另外, static不能修饰class
namespace
{
    /** Global Variables */
    int alpha = 100;
    int beta = 100;
    int gamma_cor = 100;
    Mat img_original, img_corrected, img_gamma_corrected;

    void basicLinearTransform(const Mat &img, const double alpha_, const int beta_)
    {
        Mat res;
        img.convertTo(res, -1, alpha_, beta_);

        hconcat(img, res, img_corrected);
    }

    void gammaCorrection(const Mat &img, const double gamma_)
    {
        CV_Assert(gamma_ >= 0);
        //![changing-contrast-brightness-gamma-correction]
        Mat lookUpTable(1, 256, CV_8U);
        uchar* p = lookUpTable.ptr();
        for (int i = 0; i < 256; ++i)
            p[i] = saturate_cast<uchar>(pow(i / 255.0, gamma_) * 255.0);

        Mat res = img.clone();
        LUT(img, lookUpTable, res); // http://docs.opencv.org/master/d2/de8/group__core__array.html#gab55b8d062b7f5587720ede032d34156f
        //![changing-contrast-brightness-gamma-correction]

        hconcat(img, res, img_gamma_corrected);
    }

    void on_linear_transform_alpha_trackbar(int, void *)
    {
        double alpha_value = alpha / 100.0;
        int beta_value = beta - 100;
        basicLinearTransform(img_original, alpha_value, beta_value);
    }

    void on_linear_transform_beta_trackbar(int, void *)
    {
        double alpha_value = alpha / 100.0;
        int beta_value = beta - 100;
        basicLinearTransform(img_original, alpha_value, beta_value);
    }

    void on_gamma_correction_trackbar(int, void *)
    {
        double gamma_value = gamma_cor / 100.0;
        gammaCorrection(img_original, gamma_value);
    }
}
int main()
{
    // dota.jpg, p16.jpg, test_chi2_dpi.png
    String imageName(R"(test\test1.jpg)"); // by default

    img_original = imread(imageName);
    if (img_original.empty())
    {
        cerr << "image path is invalid!" << endl;
        return -1;
    }

    img_corrected = Mat(img_original.rows, img_original.cols * 2, img_original.type());
    img_gamma_corrected = Mat(img_original.rows, img_original.cols * 2, img_original.type());

    hconcat(img_original, img_original, img_corrected);
    hconcat(img_original, img_original, img_gamma_corrected);

    namedWindow("Brightness and contrast adjustments", WINDOW_AUTOSIZE);
    namedWindow("Gamma correction", WINDOW_AUTOSIZE);

    createTrackbar("Alpha gain (contrast)", "Brightness and contrast adjustments", &alpha, 500, on_linear_transform_alpha_trackbar);
    createTrackbar("Beta bias (brightness)", "Brightness and contrast adjustments", &beta, 200, on_linear_transform_beta_trackbar);
    createTrackbar("Gamma correction", "Gamma correction", &gamma_cor, 200, on_gamma_correction_trackbar);

    while (true)
    {
        imshow("Brightness and contrast adjustments", img_corrected);
        imshow("Gamma correction", img_gamma_corrected);

        int c = waitKey(30);
        if (c == 27)
            break;
    }

    //imwrite("linear_transform_correction.png", img_corrected);
    //imwrite("gamma_correction.png", img_gamma_corrected);

    return 0;
}

#endif