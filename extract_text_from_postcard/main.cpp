#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int main(int argc, char * argv[])
{
	string filename = "../images/postcard_1.jpg";
	Mat srcImage = imread(filename);

	// step1, 利用金字塔函数进行下采样  
	Mat pyrImage;
	pyrDown(srcImage, pyrImage);

	// setp2, 图像灰度化
	Mat grayImage;
	cvtColor(pyrImage, grayImage, CV_BGR2GRAY);

	// step3, 滤波
	Mat blurImage;
	GaussianBlur(grayImage, blurImage, Size(3, 3), 0, 0);

	// step4, 形态学梯度
	Mat gradImage;
	Mat morphKernel = getStructuringElement(MORPH_ELLIPSE, Size(3, 3));
	morphologyEx(blurImage, gradImage, MORPH_GRADIENT, morphKernel);

#ifdef _DEBUG
	imshow("grad", gradImage);
#endif

	// step5, 二值化
	Mat binImage;
	threshold(gradImage, binImage, 0.0, 255.0, THRESH_BINARY | THRESH_OTSU);

	// step6, 水平膨胀
	Mat dilateImage;
	morphKernel = getStructuringElement(MORPH_RECT, Size(9, 1));
	morphologyEx(binImage, dilateImage, MORPH_CLOSE, morphKernel);
#ifdef _DEBUG
	imshow("connected", dilateImage);
#endif

	// step7, 轮廓
	Mat mask = Mat::zeros(binImage.size(), CV_8UC1);
	vector<vector<Point>> contours;
	vector<Vec4i> hierarchy;
	findContours(dilateImage, contours, hierarchy, CV_RETR_CCOMP, CV_CHAIN_APPROX_SIMPLE, Point(0, 0));

	// step8, 过滤非字符所在轮廓
	for (int idx = 0; idx >= 0; idx = hierarchy[idx][0])
	{
		Rect rect = boundingRect(contours[idx]);
		Mat maskROI(mask, rect); 
		maskROI = Scalar(0, 0, 0);

		drawContours(mask, contours, idx, Scalar(255, 255, 255), FILLED);
		// 计算非零区域的比例
		double r = (double)countNonZero(maskROI) / (rect.width * rect.height);

		if (r > .45 /* assume at least 45% of the area is filled if it contains text */
			&&
			(rect.height > 8 && rect.width > 8) /* constraints on region size */
			/* these two conditions alone are not very robust. better to use something
			like the number of significant peaks in a horizontal projection as a third condition */
			)
		{
			rectangle(pyrImage, rect, Scalar(0, 255, 0), 2);
		}
	}
	imshow("result", pyrImage);
	waitKey(0);
	return 0;
}