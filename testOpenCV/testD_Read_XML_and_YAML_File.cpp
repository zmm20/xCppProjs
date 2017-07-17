//#define MAIN
#ifdef MAIN

#include <opencv2/opencv.hpp>


using namespace cv;
using namespace std;


//-----------------------------------��ShowHelpText( )������----------------------------------
//		 ���������һЩ������Ϣ
//----------------------------------------------------------------------------------------------
void ShowHelpText()
{
    //�����ӭ��Ϣ��OpenCV�汾
    printf("\n\n\t\t\t�ǳ���л����OpenCV3������š�һ�飡\n");
    printf("\n\n\t\t\t��Ϊ����OpenCV3��ĵ�30������ʾ������\n");
    printf("\n\n\t\t\t   ��ǰʹ�õ�OpenCV�汾Ϊ��" CV_VERSION);
    printf("\n\n  ----------------------------------------------------------------------------\n\n");
}




int main()
{
    //�ı�console������ɫ
    system("color 6F");

    ShowHelpText();

    //��ʼ��
    FileStorage fs2("test.yaml", FileStorage::READ);

    // ��һ�ַ�������FileNode����
    int frameCount = (int)fs2["frameCount"];

    std::string date;
    // �ڶ��ַ�����ʹ��FileNode�����> > 
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

    //ʹ��FileNodeIterator��������
    for (; it != it_end; ++it, idx++)
    {
        cout << "feature #" << idx << ": ";
        cout << "x=" << (int)(*it)["x"] << ", y=" << (int)(*it)["y"] << ", lbp: (";
        // ����Ҳ����ʹ��ʹ��filenode > > std::vector�����������׵Ķ���ֵ����
        (*it)["lbp"] >> lbpval;
        for (int i = 0; i < (int)lbpval.size(); i++)
            cout << " " << (int)lbpval[i];
        cout << ")" << endl;
    }
    fs2.release();

    //������������һЩ��������
    printf("\n�ļ���ȡ��ϣ��������������������~");
    getchar();

    return 0;
}

#endif