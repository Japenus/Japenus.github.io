#include "pch.h"
#include "ShapeProcess.h"

Mat ShapeProcess::Imgerosion(Mat image)
{
    Mat erodedImage(image.size(), image.type());

    // ���帯ʴ�������ں�
    Mat kernel = getStructuringElement(MORPH_RECT, Size(3, 3));

    // ��ÿ��ͨ�����и�ʴ����
    erode(image, erodedImage, kernel);

    return erodedImage;
}

Mat ShapeProcess::dilation(Mat image)
{
    Mat dilatedImage(image.size(), image.type());
    // �������Ͳ������ں�
    Mat kernel =getStructuringElement(MORPH_RECT, Size(3, 3));
    // ��ÿ��ͨ���������Ͳ���
    dilate(image, dilatedImage, kernel);
    return dilatedImage;
}
