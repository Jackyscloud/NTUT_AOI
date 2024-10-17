// HW2.cpp : 此檔案包含 'main' 函式。程式會於該處開始執行及結束執行。
//
#include <iostream>
#include <vector>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace std;
using namespace cv;

int r_array[4][5] = {
	{247,67,32,187,240},
	{122,41,21,16,154},
	{52,35,79,21,93},
	{27,22,35,154,75}
};
int g_array[4][5] = {
	{14,145,132,25,40},
	{212,221,121,54,14},
	{132,235,178,19,14},
	{122,122,133,54,47},
};
int b_array[4][5] = {
	{17,44,32,127,240},
	{22,231,21,156,124},
	{32,35,78,21,194},
	{127,22,33,54,45},
};
int col = 4;
int row = 5;


int main()
{
	int r1,g1,b1;
	int sum = 0;
	int total = row * col;

	Mat img_source(col, row, CV_8UC3, Scalar(0, 0, 0));//製作影像
	for (int i = 0; i < col; i++) {//i為水平像素點
		for (int j = 0; j < row; j++) {//j為垂直像素點
			img_source.at<Vec3b>(i, j)[2] = r_array[i][j];//Vec3b---表示每一個Vec3b物件中,可以存儲3個char(字元型)資料.
			img_source.at<Vec3b>(i, j)[1] = g_array[i][j];
			img_source.at<Vec3b>(i, j)[0] = b_array[i][j];
		}
	}

	for (int i = 0; i < col; i++) {//i為水平像素點
		for (int j = 0; j < row; j++) {//j為垂直像素點
			sum += b_array[i][j];
		}
	}
	double mean = sum / total;
	cout << "mean=" << endl << mean << endl;

	double variance = 0;
	for (int i = 0; i < row; ++i) {
		for (int j = 0; j < col; ++j) {
			variance += (b_array[i][j] - mean) * (b_array[i][j] - mean);
		}
	}
	variance /= total;

	double std_dev = std::sqrt(variance);
	cout << "std_dev=" << endl << std_dev << endl;

	Mat target(col, row, CV_8UC3, Scalar(0, 0, 0));//製作影像
	for (int i = 0; i < col; i++) {//i為水平像素點
		for (int j = 0; j < row; j++) {//j為垂直像素點
			r1 = r_array[i][j] + 30;
			g1 = g_array[i][j] - 20;
			b1 = b_array[i][j];
			if (r1 > 255)
			{
				r1 = 255;
			}
			else if (r1 < 0)
			{
				r1 = 0;
			}
			if (g1 > 255)
			{
				g1 = 255;
			}
			else if (g1 < 0)
			{
				g1 = 0;
			}
			if (b1 > mean+std_dev)
			{
				b1 = 255;
			}
			else if (b1 < mean - std_dev)
			{
				b1 = 0;
			}
			
			target.at<Vec3b>(i, j)[2] = r1;//Vec3b---表示每一個Vec3b物件中,可以存儲3個char(字元型)資料.
			target.at<Vec3b>(i, j)[1] = g1;
			target.at<Vec3b>(i, j)[0] = b1;
		}
	}
	
	cout << "img=" << endl << img_source << endl;
	cout << "target=" << endl << target << endl;

	namedWindow("原圖", WINDOW_NORMAL);
	namedWindow("target", WINDOW_NORMAL);

	imshow("原圖", img_source);
	imshow("target", target);
	waitKey(0);
	return 0;
}


