#pragma once
class CImgProcessing
{
public:
	//����RGBת�Ҷȵĺ�����ʵ��ת��CImgProcessing��
	//RGB ת�Ҷ�
	Mat RGB_to_Gray(Mat src);
	//��ʾֱ��ͼ
	void ShowHistogram(Mat src);
	//ֱ��ͼ���⻯
	Mat HistEqual(Mat src);
	//�Ҷȱ任-���Ա任
	Mat linearTransform(Mat image);
	//�����任
	Mat logTransform(Mat image, double para);
	//٤��任
	Mat gammaTransform(Mat image, float gamma);
	//ͼ��ָ�
	//~~
	// �̶���ֵ�ָ�~~~~~~~~~~~~~
	Mat thresholding(Mat image, int threshold);
	//����Ӧ��ֵ�ָ�
	Mat adaptiveThresholding(Mat image, int blockSize, double C);
	//ͼ����������
	void regionGrowing(Mat src, Mat dst, int seedX, int seedY, int threshold);
	//ͼ���Ե���sobel����
	Mat EdgeDetectSobel(Mat src);
	//��Ե���canny����
	Mat EdgeDetectCanny(Mat src);

	//�˲�����
	//**********************
	//��ֵ�˲�
	Mat MeanFiltering(Mat src);
	//��ֵ�˲�
	Mat MediumFilter(Mat src);
	//��˹�˲�
	Mat GaussFilter(Mat src);
	//�������
	void DetectFace();
};