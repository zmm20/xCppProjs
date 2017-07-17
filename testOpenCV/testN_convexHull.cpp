//#define MAIN
#ifdef MAIN

#include <opencv2/opencv.hpp>


using namespace cv;
using namespace std;



//-----------------------------------��ShowHelpText( )������----------------------------------
//          ���������һЩ������Ϣ
//----------------------------------------------------------------------------------------------
static void ShowHelpText()
{
    //�����ӭ��Ϣ��OpenCV�汾
    printf("\n\n\t\t\t�ǳ���л����OpenCV3������š�һ�飡\n");
    printf("\n\n\t\t\t��Ϊ����OpenCV3��ĵ�71������ʾ������\n");
    printf("\n\n\t\t\t   ��ǰʹ�õ�OpenCV�汾Ϊ��" CV_VERSION);
    printf("\n\n  ----------------------------------------------------------------------------\n");
    //���һЩ������Ϣ
    printf("\n\t��ӭ������͹����⡿ʾ������~\n\n");
    printf("\n\t��������˵��: \n\n"
        "\t\t���̰�����ESC������Q������q��- �˳�����\n\n"
        "\t\t���̰�������� - ������������㣬������͹�����\n");

}


//--------------------------------------��main( )������-----------------------------------------
//          ����������̨Ӧ�ó������ں��������ǵĳ�������￪ʼִ��
//-----------------------------------------------------------------------------------------------
int main()
{
    //�ı�console������ɫ
    system("color 1F");

    //��ʾ��������
    ShowHelpText();

    //��ʼ�����������ֵ
    Mat image(600, 600, CV_8UC3);
    RNG& rng = theRNG();

    //ѭ��������ESC,Q,q�������˳��������м����±�һֱ����
    while (1)
    {
        //������ʼ��
        char key;//��ֵ
        int count = (unsigned)rng % 100 + 3;//������ɵ������
        vector<Point> points; //��ֵ

                              //������ɵ�����
        for (int i = 0; i < count; i++)
        {
            Point point;
            point.x = rng.uniform(image.cols / 4, image.cols * 3 / 4);
            point.y = rng.uniform(image.rows / 4, image.rows * 3 / 4);

            points.push_back(point);
        }

        //���͹��
        vector<int> hull;
        convexHull(Mat(points), hull, true);

        //���Ƴ������ɫ�ĵ�
        image = Scalar::all(0);
        for (int i = 0; i < count; i++)
            circle(image, points[i], 3, Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255)), FILLED, LINE_AA);

        //׼������
        int hullcount = (int)hull.size();//͹���ı���
        Point point0 = points[hull[hullcount - 1]];//����͹���ߵ������

                                                   //����͹���ı�
        for (int i = 0; i < hullcount; i++)
        {
            Point point = points[hull[i]];
            line(image, point0, point, Scalar(255, 255, 255), 2, LINE_AA);
            point0 = point;
        }

        //��ʾЧ��ͼ
        imshow("͹�����ʾ��", image);

        //����ESC,Q,����q�������˳�
        key = (char)waitKey();
        if (key == 27 || key == 'q' || key == 'Q')
            break;
    }

    return 0;
}

#endif