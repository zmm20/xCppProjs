#define MAIN
#ifdef MAIN

#include <stdio.h>
#include <opencv2/opencv.hpp>
#include <fstream>

using namespace std;
using namespace cv;

int main()
{
    //-----------------------------------��һ��ͼ����������ʾ��---------------------------------
    //	�������������д����������ͼ����������ʾ
    //--------------------------------------------------------------------------------------------------

    cout << "test 1" << endl;
    {
        Mat girl = imread("girl.jpg"); //����ͼ��Mat
        namedWindow("��1������ͼ"); //����һ����Ϊ "��1������ͼ"�Ĵ���  
        imshow("��1������ͼ", girl);//��ʾ��Ϊ "��1������ͼ"�Ĵ���  
    }
    cout << endl;

    cout << "test 2" << endl;
    {
        ifstream is("girl.jpg", ios::binary);
        if (!is)
        {
            cerr << "ͼƬ��ʧ��!" << endl;
        }

        is.seekg(0, is.end);
        const int fileSize = is.tellg();
        is.seekg(0, is.beg);

        std::string str;
        str.resize(fileSize, ' '); // reserve space
        char* begin = &*str.begin();

        is.read(begin, fileSize);
        is.close();

        //std::stringstream sstr;
        //while (is >> sstr.rdbuf());
        //is.close();

        std::vector<uchar> data(str.begin(), str.end());
        Mat girl = imdecode(data, CV_LOAD_IMAGE_COLOR);
        namedWindow("���ڴ��м���ͼƬ"); 
        imshow("���ڴ��м���ͼƬ", girl);
    }
    cout << endl;

    waitKey();
    return 0;

    //-----------------------------------����������ͼ���ϡ�--------------------------------------
    //	��������������ͼ����
    //--------------------------------------------------------------------------------------------------
    //����ͼƬ
    Mat image = imread("dota.jpg");//, 199  // ������鱾�еİ汾, 199�Ǵ����.
    Mat logo = imread("dota_logo.jpg");
    if (!image.data || !logo.data)
    {
        printf("����ʧ��\n");
        return -1;
    }

    //���������ʾ
    namedWindow("��2��ԭ��ͼ");
    imshow("��2��ԭ��ͼ", image);

    namedWindow("��3��logoͼ");
    imshow("��3��logoͼ", logo);


    // ����һ��Mat���ͣ����ڴ�ţ�ͼ���ROI
    Mat imageROI;
    //����һ
    imageROI = image(Rect(800, 350, logo.cols, logo.rows));
    //������
    //imageROI= image(Range(350,350+logo.rows),Range(800,800+logo.cols));

    // ��logo�ӵ�ԭͼ��
    addWeighted(imageROI, 0.5, logo, 0.3, 0., imageROI);

    //��ʾ���
    namedWindow("��4��ԭ��+logoͼ");
    imshow("��4��ԭ��+logoͼ", image);

    //-----------------------------------������ͼ��������--------------------------------------
    //	��������һ��Matͼ�������ͼ���ļ�
    //-----------------------------------------------------------------------------------------------
    //���һ��jpgͼƬ������Ŀ¼��
    imwrite("��imwrite���ɵ�ͼƬ.jpg", image);
    

    waitKey();

}
#endif