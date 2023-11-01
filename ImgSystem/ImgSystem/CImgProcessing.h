#pragma once
class CImgProcessing
{
public:
	//声明RGB转灰度的函数，实现转到CImgProcessing中
	//RGB 转灰度
	Mat RGB_to_Gray(Mat src);
	//显示直方图
	void ShowHistogram(Mat src);
	//直方图均衡化
	Mat HistEqual(Mat src);
	//灰度变换-线性变换
	Mat linearTransform(Mat image);
	//对数变换
	Mat logTransform(Mat image, double para);
	//伽马变换
	Mat gammaTransform(Mat image, float gamma);
	//图像分割
	//~~
	// 固定阈值分割~~~~~~~~~~~~~
	Mat thresholding(Mat image, int threshold);
	//自适应阈值分割
	Mat adaptiveThresholding(Mat image, int blockSize, double C);
	//图像区域生长
	void regionGrowing(Mat src, Mat dst, int seedX, int seedY, int threshold);
	//图像边缘检测sobel算子
	Mat EdgeDetectSobel(Mat src);
	//边缘检测canny算子
	Mat EdgeDetectCanny(Mat src);

	//滤波处理
	//**********************
	//均值滤波
	Mat MeanFiltering(Mat src);
	//中值滤波
	Mat MediumFilter(Mat src);
	//高斯滤波
	Mat GaussFilter(Mat src);
	//人脸检测
	void DetectFace();
};