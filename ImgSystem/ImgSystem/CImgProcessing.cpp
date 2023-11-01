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
	//创建直方图显示图像
	int hist_h = 300;//直方图的图像的高
	int hist_w = 512;//直方图的图像的宽
	int bin_w = hist_w / val;//直方图的等级
	Mat histImage(hist_h, hist_w, CV_8UC3, Scalar(0, 0, 0));//绘制直方图显示的图像
	//绘制并显示直方图
	normalize(hist, hist, 0, hist_h, NORM_MINMAX, -1, Mat());//归一化直方图
	for (int i = 1; i < val; i++)
	{
		line(histImage, Point((i - 1) * bin_w, hist_h - cvRound(hist.at<float>(i - 1))),
		Point((i)*bin_w, hist_h - cvRound(hist.at<float>(i))), Scalar(255, 0, 0), 2, 8, 0);
	}
	imshow("灰度直方图", histImage);
	waitKey(0);
}

Mat CImgProcessing::HistEqual(Mat src)
{
	Mat gray_img, enhanced;//均衡化之前先要灰度化处理
	cvtColor(src, gray_img, COLOR_BGR2GRAY);
	equalizeHist(gray_img, enhanced);//直方图均衡化
	return enhanced;
}

Mat CImgProcessing::linearTransform(Mat image)
{
	// 检查输入图像是否为3通道的RGB图像
	assert(image.channels() == 3);

	// 创建一个与输入图像大小相同的灰度图像
	Mat grayImage(image.size(), CV_8UC1);

	// 线性变换公式：Gray = 0.299 * R + 0.587 * G + 0.114 * B
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
	// 检查输入图像是否为3通道的RGB图像
	assert(image.channels() == 3);

	// 创建一个与输入图像大小相同的灰度图像
	Mat grayImage(image.size(), CV_8UC1);

	// 对数变换公式：Gray = c * log(1 + R)
	//double c = 255 / log(256);  // 缩放参数c
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

	// 创建一个与输入图像大小相同的灰度图像
	Mat grayImage(image.size(), CV_8UC1);

	// 伽马变换公式：Gray = 255 * (R/255)^gamma
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

	// 对每个通道进行阈值分割操作
	for (int i = 0; i < image.rows; i++) {
		for (int j = 0; j < image.cols; j++) {
			Vec3b pixel = image.at<Vec3b>(i, j);
			int grayValue = (pixel[0] + pixel[1] + pixel[2]) / 3;  // 计算灰度值
			if (grayValue >= threshold) {
				thresholdedImage.at<uchar>(i, j) = 255;  // 超过阈值的像素设置为白色
			}
			else {
				thresholdedImage.at<uchar>(i, j) = 0;  // 低于阈值的像素设置为黑色
			}
		}
	}
	return thresholdedImage;
}

Mat CImgProcessing::adaptiveThresholding(Mat image, int blockSize, double C)
{
	Mat grayImage;
	cvtColor(image, grayImage, COLOR_BGR2GRAY);

	// 创建一个与输入图像大小相同的输出图像
	Mat thresholdedImage(image.size(), CV_8UC1);

	// 使用自适应阈值分割进行图像处理
	adaptiveThreshold(grayImage, thresholdedImage, 255, ADAPTIVE_THRESH_MEAN_C, THRESH_BINARY, blockSize, C);
	return thresholdedImage;
}

void CImgProcessing::regionGrowing(Mat src,Mat dst, int seedX, int seedY, int threshold)
{
	// 创建一个与原始图像相同大小的标记图像，用于记录已经生长的区域
	Mat visited = Mat::zeros(src.size(), CV_8UC1);
	// 获取原始图像的宽度和高度
	int width = src.cols;
	int height = src.rows;

	// 获取种子点的颜色
	Vec3b seedColor = src.at<Vec3b>(seedX, seedY);

	// 创建一个队列，用于存储待生长的像素点
	queue<Point> q;

	// 将种子点加入队列
	q.push(Point(seedX, seedY));

	// 当队列不为空时，进行区域生长
	while (!q.empty())
	{
		// 从队列中取出一个像素点
		Point p = q.front();
		q.pop();

		// 获取像素点的坐标
		int x = p.x;
		int y = p.y;

		// 检查当前像素点是否已经被访问过
		if (visited.at<uchar>(y, x) == 1)
		{
			continue;
		}

		// 将当前像素点标记为已访问
		visited.at<uchar>(y, x) = 1;

		// 获取当前像素点的颜色
		Vec3b color = src.at<Vec3b>(y, x);

		// 计算当前像素点与种子点的颜色差
		int diff = abs(seedColor[0] - color[0]) + abs(seedColor[1] - color[1]) + abs(seedColor[2] - color[2]);

		// 如果颜色差小于阈值，则将当前像素点加入生长区域
		if (diff < threshold)
		{
			dst.at<uchar>(y, x) = 255;

			// 将当前像素点的邻域像素点加入队列
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

	// 对灰度图像进行Sobel边缘检测
	Mat sobelX, sobelY;
	Sobel(grayImage, sobelX, CV_16S, 1, 0);
	Sobel(grayImage, sobelY, CV_16S, 0, 1);

	// 将Sobel结果转换回无符号整数类型
	Mat sobelXAbs, sobelYAbs;
	convertScaleAbs(sobelX, sobelXAbs);
	convertScaleAbs(sobelY, sobelYAbs);

	// 合并水平和垂直Sobel结果
	Mat sobelImage;
	addWeighted(sobelXAbs, 0.5, sobelYAbs, 0.5, 0, sobelImage);
	return sobelImage;
}

Mat CImgProcessing::EdgeDetectCanny(Mat src)
{
	// 将图像转换为灰度图像
	Mat grayImage;
	cvtColor(src, grayImage,COLOR_BGR2GRAY);
	// 使用Canny算子进行边缘检测
	Mat edges;
	Canny(grayImage, edges, 150, 200);
	return edges;
}

Mat CImgProcessing::MeanFiltering(Mat src)
{
	// 创建与原始图像相同大小的空白图像用于存储均值滤波结果
	Mat result = Mat::zeros(src.size(),src.type());

	// 遍历每个像素
	for (int y = 1; y < src.rows - 1; y++) {
		for (int x = 1; x < src.cols - 1; x++) {
			// 计算周围像素的均值
			int sumR = 0, sumG = 0, sumB = 0;
			for (int i = -1; i <= 1; i++) {
				for (int j = -1; j <= 1; j++) {
					Vec3b pixel = src.at<Vec3b>(y + i, x + j);
					sumR += pixel[2];
					sumG += pixel[1];
					sumB += pixel[0];
				}
			}
			// 将均值作为当前像素的值
			result.at<Vec3b>(y, x)[2] = sumR / 9;
			result.at<Vec3b>(y, x)[1] = sumG / 9;
			result.at<Vec3b>(y, x)[0] = sumB / 9;
		}
	}
	return result;
}

Mat CImgProcessing::MediumFilter(Mat src)
{
	// 创建输出图像
	Mat filteredImage = src.clone();

	// 遍历图像的每个像素
	for (int y = 1; y < src.rows - 1; y++)
	{
		for (int x = 1; x < src.cols - 1; x++)
		{
			// 获取当前像素周围的9个像素
			Vec3b pixels[9];
			int index = 0;
			for (int i = -1; i <= 1; i++)
			{
				for (int j = -1; j <= 1; j++)
				{
					pixels[index++] = src.at<Vec3b>(y + i, x + j);
				}
			}
			// 对9个像素进行排序，取中值作为当前像素的值
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
	// 创建存储结果的Mat对象
	Mat result;
	// 使用高斯滤波对图像进行模糊处理
	GaussianBlur(src, result, cv::Size(15, 15), 0); // 调整卷积核大小和标准差以控制滤波效果

	return result;
}

void CImgProcessing::DetectFace()
{
	CascadeClassifier faceCascade;
	if (!faceCascade.load("haarcascade_frontalface_alt.xml")) {
		cout << "无法加载人脸检测器！" << endl;
	}

	// 打开摄像头
	VideoCapture capture(0);
	if (!capture.isOpened()) {
		cout << "无法打开摄像头！" << endl;
	}

	// 创建窗口
	namedWindow("人脸检测", WINDOW_NORMAL);

	while (true) {
		// 读取图像帧
		Mat frame;
		capture.read(frame);

		// 转换为灰度图像
		Mat gray;
		cvtColor(frame, gray, COLOR_BGR2GRAY);

		// 目标人脸矩形区域
		vector<Rect> faces;

		// 运行人脸检测器
		faceCascade.detectMultiScale(gray, faces, 1.1, 3, 0, Size(30, 30));

		// 在图像中绘制人脸矩形框
		for (size_t i = 0; i < faces.size(); i++) {
			rectangle(frame, faces[i], Scalar(0, 255, 0), 2);
		}

		// 显示图像
		imshow("人脸检测", frame);

		// 按下ESC键退出
		if (waitKey(10) == 27) {
			break;
		}
	}
	// 释放摄像头并关闭窗口
	capture.release();
	destroyAllWindows();
}
