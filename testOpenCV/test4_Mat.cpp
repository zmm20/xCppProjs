//#define MAIN
#ifdef MAIN


#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int main()
{
    Mat m(2, 3, CV_8UC3, Scalar(0, 0, 255));
    cout << "m = " << endl << " " << m << endl << endl;

    int arg[]{ 2, 2, 2 };
    Mat m2(2, arg, CV_8UC3, Scalar::all(0));
    cout << "m2 = " << endl << " " << format(m2, Formatter::FMT_PYTHON) << endl << endl;

    Mat m3 = (Mat_<double>(3, 3) << 0, -1, 0, -1, 5, -1, 0, -1, 0);
    cout << "m3 = " << endl << " " << m3 << endl << endl;
    
    Mat m4 = Mat(10, 3, CV_8UC3);
    randu(m4, Scalar::all(0), Scalar::all(255));
    cout << "m4 = " << endl << " " << format(m4, Formatter::FMT_PYTHON) << endl << endl;


    // 点
    Point2f p2f(6.5, 2);
    cout << "p2f = " << p2f << ";" << endl;

    Point3f p3f(8.1, 2, 0);
    cout << "p3f = " << p3f << ";" << endl;

    // 基于Mat 的vector
    vector<float> v;
    v.push_back(3);
    v.push_back(5);
    v.push_back(7);
    cout << "v = " << Mat(v) << endl;

    
    waitKey(0);
}
#endif