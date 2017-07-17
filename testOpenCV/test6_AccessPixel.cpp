//#define MAIN
#ifdef MAIN

#include <opencv2/opencv.hpp>


using namespace cv;
using namespace std;

//-----------------------------------��ȫ�ֺ����������֡�-----------------------------------
//          ������ȫ�ֺ�������
//-----------------------------------------------------------------------------------------------
void colorReduce(Mat& inputImage, Mat& outputImage, int div);
void colorReduce2(Mat& inputImage, Mat& outputImage, int div);
void colorReduce3(Mat& inputImage, Mat& outputImage, int div);
void ShowHelpText();



//--------------------------------------��main( )������---------------------------------------
//          ����������̨Ӧ�ó������ں��������ǵĳ�������￪ʼִ��
//-----------------------------------------------------------------------------------------------
int main()
{
    //��1������ԭʼͼ����ʾ
    Mat srcImage = imread("1.jpg");
    imshow("ԭʼͼ��", srcImage);

    //��2����ԭʼͼ�Ĳ����������������Ч��ͼ
    Mat dstImage;
    // create �Ὺ���ڴ�ռ�, ����colorReduce������ʹ��clone �Ѿ��������ڴ�ռ�
    //dstImage.create(srcImage.rows, srcImage.cols, srcImage.type());//Ч��ͼ�Ĵ�С��������ԭͼƬ��ͬ 

    ShowHelpText();
    
    //��4��������ɫ�ռ���������
    colorReduce(srcImage, dstImage, 32);

    colorReduce2(srcImage, dstImage, 32);

    colorReduce3(srcImage, dstImage, 32);

    
    //��6����ʾЧ��ͼ
    imshow("Ч��ͼ", dstImage);
    waitKey(0);
}


//---------------------------------��colorReduce( )������---------------------------------
//          ������ʹ�á�ָ����ʣ�C������[ ]�����������ɫ�ռ���������
//----------------------------------------------------------------------------------------------
void colorReduce(Mat& inputImage, Mat& outputImage, int div)
{
    //��3����¼��ʼʱ��
    double time0 = static_cast<double>(getTickCount());

    //����׼��
    outputImage = inputImage.clone();  //����ʵ�ε���ʱ����
    int rowNumber = outputImage.rows;  //����
    int colNumber = outputImage.cols*outputImage.channels();  //���� x ͨ����=ÿһ��Ԫ�صĸ���

                                                              //˫��ѭ�����������е�����ֵ
    for (int i = 0; i < rowNumber; i++)  //��ѭ��
    {
        uchar* data = outputImage.ptr<uchar>(i);  //��ȡ��i�е��׵�ַ
        for (int j = 0; j < colNumber; j++)   //��ѭ��
        {
            // ---------����ʼ����ÿ�����ء�-------------     
            data[j] = data[j] / div*div + div / 2;
            // ----------�����������---------------------
        }  //�д������
    }

    //��5����������ʱ�䲢���
    time0 = ((double)getTickCount() - time0) / getTickFrequency();
    cout << "\t�˷�������ʱ��Ϊ�� " << time0 << "��" << endl;  //�������ʱ��
}



//-------------------------------------��colorReduce( )������-----------------------------
//		������ʹ�á������������������ɫ�ռ���������
//----------------------------------------------------------------------------------------------
void colorReduce2(Mat& inputImage, Mat& outputImage, int div)
{
    //��3����¼��ʼʱ��
    double time0 = static_cast<double>(getTickCount());

    //����׼��
    outputImage = inputImage.clone();  //����ʵ�ε���ʱ����
                                       //��ȡ������
    Mat_<Vec3b>::iterator it = outputImage.begin<Vec3b>();  //��ʼλ�õĵ�����
    Mat_<Vec3b>::iterator itend = outputImage.end<Vec3b>();  //��ֹλ�õĵ�����

                                                             //��ȡ��ɫͼ������
    for (; it != itend; ++it)
    {
        // ------------------------����ʼ����ÿ�����ء�--------------------
        (*it)[0] = (*it)[0] / div*div + div / 2;
        (*it)[1] = (*it)[1] / div*div + div / 2;
        (*it)[2] = (*it)[2] / div*div + div / 2;
        // ------------------------�����������----------------------------
    }

    //��5����������ʱ�䲢���
    time0 = ((double)getTickCount() - time0) / getTickFrequency();
    cout << "\t�˷�������ʱ��Ϊ�� " << time0 << "��" << endl;  //�������ʱ��
}

//----------------------------------��colorReduce( )������-------------------------------
//          ������ʹ�á���̬��ַ�������at�������汾����ɫ�ռ���������
//----------------------------------------------------------------------------------------------
void colorReduce3(Mat& inputImage, Mat& outputImage, int div)
{
    //��3����¼��ʼʱ��
    double time0 = static_cast<double>(getTickCount());

    //����׼��
    outputImage = inputImage.clone();  //����ʵ�ε���ʱ����
    int rowNumber = outputImage.rows;  //����
    int colNumber = outputImage.cols;  //����

    //��ȡ��ɫͼ������
    for (int i = 0; i < rowNumber; i++)
    {
        for (int j = 0; j < colNumber; j++)
        {
            // ------------------------����ʼ����ÿ�����ء�--------------------
            outputImage.at<Vec3b>(i, j)[0] = outputImage.at<Vec3b>(i, j)[0] / div*div + div / 2;  //��ɫͨ��
            outputImage.at<Vec3b>(i, j)[1] = outputImage.at<Vec3b>(i, j)[1] / div*div + div / 2;  //��ɫͨ��
            outputImage.at<Vec3b>(i, j)[2] = outputImage.at<Vec3b>(i, j)[2] / div*div + div / 2;  //����ͨ��
            // -------------------------�����������----------------------------
        }  // �д������     
    }

    //��5����������ʱ�䲢���
    time0 = ((double)getTickCount() - time0) / getTickFrequency();
    cout << "\t�˷�������ʱ��Ϊ�� " << time0 << "��" << endl;  //�������ʱ��
}


//-----------------------------------��ShowHelpText( )������----------------------------------
//          ���������һЩ������Ϣ
//----------------------------------------------------------------------------------------------
void ShowHelpText()
{
    //�����ӭ��Ϣ��OpenCV�汾
    printf("\n\n\t\t\t�ǳ���л����OpenCV3������š�һ�飡\n");
    printf("\n\n\t\t\t��Ϊ����OpenCV3��ĵ�21������ʾ������\n");
    printf("\n\n\t\t\t   ��ǰʹ�õ�OpenCV�汾Ϊ��" CV_VERSION);
    printf("\n\n  ----------------------------------------------------------------------------\n");
}

#endif