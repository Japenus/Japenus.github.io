#include "pch.h"
#include "CImgProcessing.h"

Mat CImgProcessing::RGB_to_Gray(Mat src)
{
	Mat dst;
	cvtColor(src, dst, COLOR_BGR2GRAY);
	return dst;
}

void CImgProcessing::ShowHistogram(Mat src)
{
	Mat gray_img,hist;
	cvtColor(src, gray_img, COLOR_RGB2GRAY);
	int val = 256;
	float ranges[] = { 0,256 };
	const float* histRanges = { ranges };
	calcHist(&gray_img, 1, 0, Mat(), hist, 1, &val, &histRanges, true, false);
	//����ֱ��ͼ��ʾͼ��
	int hist_h = 300;//ֱ��ͼ��ͼ��ĸ�
	int hist_w = 512;//ֱ��ͼ��ͼ��Ŀ�
	int bin_w = hist_w / val;//ֱ��ͼ�ĵȼ�
	Mat histImage(hist_h, hist_w, CV_8UC3, Scalar(0, 0, 0));//����ֱ��ͼ��ʾ��ͼ��
	//���Ʋ���ʾֱ��ͼ
	normalize(hist, hist, 0, hist_h, NORM_MINMAX, -1, Mat());//��һ��ֱ��ͼ
	for (int i = 1; i < val; i++)
	{
		line(histImage, Point((i - 1) * bin_w, hist_h - cvRound(hist.at<float>(i - 1))),
		Point((i)*bin_w, hist_h - cvRound(hist.at<float>(i))), Scalar(255, 0, 0), 2, 8, 0);
	}
	imshow("�Ҷ�ֱ��ͼ", histImage);
	waitKey(0);
}

Mat CImgProcessing::HistEqual(Mat src)
{
	Mat gray_img, enhanced;//���⻯֮ǰ��Ҫ�ҶȻ�����
	cvtColor(src, gray_img, COLOR_BGR2GRAY);
	equalizeHist(gray_img, enhanced);//ֱ��ͼ���⻯
	return enhanced;
}

Mat CImgProcessing::linearTransform(Mat image)
{
	// �������ͼ���Ƿ�Ϊ3ͨ����RGBͼ��
	assert(image.channels() == 3);

	// ����һ��������ͼ���С��ͬ�ĻҶ�ͼ��
	Mat grayImage(image.size(), CV_8UC1);

	// ���Ա任��ʽ��Gray = 0.299 * R + 0.587 * G + 0.114 * B
	for (int i = 0; i < image.rows; i++) {
		for (int j = 0; j < image.cols; j++) {
			Vec3b pixel = image.at<Vec3b>(i, j);
			int grayValue = 0.299 * pixel[2] + 0.587 * pixel[1] + 0.114 * pixel[0];
			grayImage.at<uchar>(i, j) = grayValue;
		}
	}
	return grayImage;
}

Mat CImgProcessing::logTransform(Mat image,double para)
{
	// �������ͼ���Ƿ�Ϊ3ͨ����RGBͼ��
	assert(image.channels() == 3);

	// ����һ��������ͼ���С��ͬ�ĻҶ�ͼ��
	Mat grayImage(image.size(), CV_8UC1);

	// �����任��ʽ��Gray = c * log(1 + R)
	//double c = 255 / log(256);  // ���Ų���c
	for (int i = 0; i < image.rows; i++) {
		for (int j = 0; j < image.cols; j++) {
			Vec3b pixel = image.at<Vec3b>(i, j);
			int grayValue = para * log(1 + pixel[2]);
			grayImage.at<uchar>(i, j) = grayValue;
		}
	}
	return grayImage;
}

Mat CImgProcessing::gammaTransform(Mat image, float gamma)
{
	assert(image.channels() == 3);

	// ����һ��������ͼ���С��ͬ�ĻҶ�ͼ��
	Mat grayImage(image.size(), CV_8UC1);

	// ٤��任��ʽ��Gray = 255 * (R/255)^gamma
	for (int i = 0; i < image.rows; i++) {
		for (int j = 0; j < image.cols; j++) {
			cv::Vec3b pixel = image.at<cv::Vec3b>(i, j);
			int grayValue = 255 * pow(pixel[2] / 255.0, gamma);
			grayImage.at<uchar>(i, j) = grayValue;
		}
	}
	return grayImage;
}

Mat CImgProcessing::thresholding(Mat image, int threshold)
{
	Mat thresholdedImage(image.size(), CV_8UC1);

	// ��ÿ��ͨ��������ֵ�ָ����
	for (int i = 0; i < image.rows; i++) {
		for (int j = 0; j < image.cols; j++) {
			Vec3b pixel = image.at<Vec3b>(i, j);
			int grayValue = (pixel[0] + pixel[1] + pixel[2]) / 3;  // ����Ҷ�ֵ
			if (grayValue >= threshold) {
				thresholdedImage.at<uchar>(i, j) = 255;  // ������ֵ����������Ϊ��ɫ
			}
			else {
				thresholdedImage.at<uchar>(i, j) = 0;  // ������ֵ����������Ϊ��ɫ
			}
		}
	}
	return thresholdedImage;
}

Mat CImgProcessing::adaptiveThresholding(Mat image, int blockSize, double C)
{
	Mat grayImage;
	cvtColor(image, grayImage, COLOR_BGR2GRAY);

	// ����һ��������ͼ���С��ͬ�����ͼ��
	Mat thresholdedImage(image.size(), CV_8UC1);

	// ʹ������Ӧ��ֵ�ָ����ͼ����
	adaptiveThreshold(grayImage, thresholdedImage, 255, ADAPTIVE_THRESH_MEAN_C, THRESH_BINARY, blockSize, C);
	return thresholdedImage;
}

void CImgProcessing::regionGrowing(Mat src,Mat dst, int seedX, int seedY, int threshold)
{
	// ����һ����ԭʼͼ����ͬ��С�ı��ͼ�����ڼ�¼�Ѿ�����������
	Mat visited = Mat::zeros(src.size(), CV_8UC1);
	// ��ȡԭʼͼ��Ŀ�Ⱥ͸߶�
	int width = src.cols;
	int height = src.rows;

	// ��ȡ���ӵ����ɫ
	Vec3b seedColor = src.at<Vec3b>(seedX, seedY);

	// ����һ�����У����ڴ洢�����������ص�
	queue<Point> q;

	// �����ӵ�������
	q.push(Point(seedX, seedY));

	// �����в�Ϊ��ʱ��������������
	while (!q.empty())
	{
		// �Ӷ�����ȡ��һ�����ص�
		Point p = q.front();
		q.pop();

		// ��ȡ���ص������
		int x = p.x;
		int y = p.y;

		// ��鵱ǰ���ص��Ƿ��Ѿ������ʹ�
		if (visited.at<uchar>(y, x) == 1)
		{
			continue;
		}

		// ����ǰ���ص���Ϊ�ѷ���
		visited.at<uchar>(y, x) = 1;

		// ��ȡ��ǰ���ص����ɫ
		Vec3b color = src.at<Vec3b>(y, x);

		// ���㵱ǰ���ص������ӵ����ɫ��
		int diff = abs(seedColor[0] - color[0]) + abs(seedColor[1] - color[1]) + abs(seedColor[2] - color[2]);

		// �����ɫ��С����ֵ���򽫵�ǰ���ص������������
		if (diff < threshold)
		{
			dst.at<uchar>(y, x) = 255;

			// ����ǰ���ص���������ص�������
			if (x > 0)
			{
				q.push(Point(x - 1, y));
			}
			if (x < width - 1)
			{
				q.push(Point(x + 1, y));
			}
			if (y > 0)
			{
				q.push(Point(x, y - 1));
			}
			if (y < height - 1)
			{
				q.push(Point(x, y + 1));
			}
		}
	}
}

Mat CImgProcessing::EdgeDetectSobel(Mat src)
{
	Mat grayImage;
	cvtColor(src, grayImage, COLOR_BGR2GRAY);

	// �ԻҶ�ͼ�����Sobel��Ե���
	Mat sobelX, sobelY;
	Sobel(grayImage, sobelX, CV_16S, 1, 0);
	Sobel(grayImage, sobelY, CV_16S, 0, 1);

	// ��Sobel���ת�����޷�����������
	Mat sobelXAbs, sobelYAbs;
	convertScaleAbs(sobelX, sobelXAbs);
	convertScaleAbs(sobelY, sobelYAbs);

	// �ϲ�ˮƽ�ʹ�ֱSobel���
	Mat sobelImage;
	addWeighted(sobelXAbs, 0.5, sobelYAbs, 0.5, 0, sobelImage);
	return sobelImage;
}

Mat CImgProcessing::EdgeDetectCanny(Mat src)
{
	// ��ͼ��ת��Ϊ�Ҷ�ͼ��
	Mat grayImage;
	cvtColor(src, grayImage,COLOR_BGR2GRAY);
	// ʹ��Canny���ӽ��б�Ե���
	Mat edges;
	Canny(grayImage, edges, 150, 200);
	return edges;
}

Mat CImgProcessing::MeanFiltering(Mat src)
{
	// ������ԭʼͼ����ͬ��С�Ŀհ�ͼ�����ڴ洢��ֵ�˲����
	Mat result = Mat::zeros(src.size(),src.type());

	// ����ÿ������
	for (int y = 1; y < src.rows - 1; y++) {
		for (int x = 1; x < src.cols - 1; x++) {
			// ������Χ���صľ�ֵ
			int sumR = 0, sumG = 0, sumB = 0;
			for (int i = -1; i <= 1; i++) {
				for (int j = -1; j <= 1; j++) {
					Vec3b pixel = src.at<Vec3b>(y + i, x + j);
					sumR += pixel[2];
					sumG += pixel[1];
					sumB += pixel[0];
				}
			}
			// ����ֵ��Ϊ��ǰ���ص�ֵ
			result.at<Vec3b>(y, x)[2] = sumR / 9;
			result.at<Vec3b>(y, x)[1] = sumG / 9;
			result.at<Vec3b>(y, x)[0] = sumB / 9;
		}
	}
	return result;
}

Mat CImgProcessing::MediumFilter(Mat src)
{
	// �������ͼ��
	Mat filteredImage = src.clone();

	// ����ͼ���ÿ������
	for (int y = 1; y < src.rows - 1; y++)
	{
		for (int x = 1; x < src.cols - 1; x++)
		{
			// ��ȡ��ǰ������Χ��9������
			Vec3b pixels[9];
			int index = 0;
			for (int i = -1; i <= 1; i++)
			{
				for (int j = -1; j <= 1; j++)
				{
					pixels[index++] = src.at<Vec3b>(y + i, x + j);
				}
			}
			// ��9�����ؽ�������ȡ��ֵ��Ϊ��ǰ���ص�ֵ
			sort(pixels, pixels + 9, [](const Vec3b& a, const Vec3b& b) {
				return (a[0] + a[1] + a[2]) < (b[0] + b[1] + b[2]);
				});
			filteredImage.at<Vec3b>(y, x) = pixels[4];
		}
	}
	return filteredImage;
}

Mat CImgProcessing::GaussFilter(Mat src)
{
	// �����洢�����Mat����
	Mat result;
	// ʹ�ø�˹�˲���ͼ�����ģ������
	GaussianBlur(src, result, cv::Size(15, 15), 0); // ��������˴�С�ͱ�׼���Կ����˲�Ч��

	return result;
}

void CImgProcessing::DetectFace()
{
	CascadeClassifier faceCascade;
	if (!faceCascade.load("haarcascade_frontalface_alt.xml")) {
		cout << "�޷����������������" << endl;
	}

	// ������ͷ
	VideoCapture capture(0);
	if (!capture.isOpened()) {
		cout << "�޷�������ͷ��" << endl;
	}

	// ��������
	namedWindow("�������", WINDOW_NORMAL);

	while (true) {
		// ��ȡͼ��֡
		Mat frame;
		capture.read(frame);

		// ת��Ϊ�Ҷ�ͼ��
		Mat gray;
		cvtColor(frame, gray, COLOR_BGR2GRAY);

		// Ŀ��������������
		vector<Rect> faces;

		// �������������
		faceCascade.detectMultiScale(gray, faces, 1.1, 3, 0, Size(30, 30));

		// ��ͼ���л����������ο�
		for (size_t i = 0; i < faces.size(); i++) {
			rectangle(frame, faces[i], Scalar(0, 255, 0), 2);
		}

		// ��ʾͼ��
		imshow("�������", frame);

		// ����ESC���˳�
		if (waitKey(10) == 27) {
			break;
		}
	}
	// �ͷ�����ͷ���رմ���
	capture.release();
	destroyAllWindows();
}
