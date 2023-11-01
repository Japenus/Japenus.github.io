#include "pch.h"
#include "ShapeProcess.h"

Mat ShapeProcess::Imgerosion(Mat image)
{
    Mat erodedImage(image.size(), image.type());

    // 定义腐蚀操作的内核
    Mat kernel = getStructuringElement(MORPH_RECT, Size(3, 3));

    // 对每个通道进行腐蚀操作
    erode(image, erodedImage, kernel);

    return erodedImage;
}

Mat ShapeProcess::dilation(Mat image)
{
    Mat dilatedImage(image.size(), image.type());
    // 定义膨胀操作的内核
    Mat kernel =getStructuringElement(MORPH_RECT, Size(3, 3));
    // 对每个通道进行膨胀操作
    dilate(image, dilatedImage, kernel);
    return dilatedImage;
}
