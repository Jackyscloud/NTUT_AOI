#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace std;
using namespace cv;

const int bin_size = 64;  // 每級距大小 (0-63, 64-127, 128-191, 192-255)
const int num_bins = 4;   // 4 級距

// 計算每個通道的級距直方圖
vector<int> calculate_histogram(const Mat& channel) {
    vector<int> bins(num_bins, 0);  // 初始化 4 個級距的計數
    for (int i = 0; i < channel.rows; ++i) {
        for (int j = 0; j < channel.cols; ++j) {
            int pixel_value = channel.at<uchar>(i, j);
            int bin = pixel_value / bin_size;  // 根據像素值分類到對應級距
            bins[bin]++;
        }
    }
    return bins;
}

// 畫出級距直方圖
void draw_histogram(const vector<int>& histogram, const string& window_name, const Scalar& color) {
    int hist_w = 400;  // 直方圖寬度
    int hist_h = 300;  // 直方圖高度
    int bin_w = cvRound((double)hist_w / num_bins);  // 每個 bin 的寬度

    Mat hist_image(hist_h, hist_w, CV_8UC3, Scalar(0, 0, 0));  // 黑色背景
    int max_value = *max_element(histogram.begin(), histogram.end());  // 最大值縮放高度

    for (int i = 0; i < num_bins; i++) {
        int bin_height = cvRound((double)histogram[i] / max_value * hist_h);
        rectangle(hist_image,
            Point(i * bin_w, hist_h - bin_height),
            Point((i + 1) * bin_w - 1, hist_h),
            color, FILLED);
    }

    namedWindow(window_name, WINDOW_NORMAL);
    imshow(window_name, hist_image);
}

// 建立影像副函式
Mat create_image(int r_array[4][5], int g_array[4][5], int b_array[4][5], int col, int row) {
    Mat img(col, row, CV_8UC3, Scalar(0, 0, 0));
    for (int i = 0; i < col; i++) {
        for (int j = 0; j < row; j++) {
            img.at<Vec3b>(i, j)[2] = r_array[i][j];  // Red
            img.at<Vec3b>(i, j)[1] = g_array[i][j];  // Green
            img.at<Vec3b>(i, j)[0] = b_array[i][j];  // Blue
        }
    }
    return img;
}

// 單通道調整副函式
void adjust_channel(Mat& channel, int adjustment) {
    for (int i = 0; i < channel.rows; ++i) {
        for (int j = 0; j < channel.cols; ++j) {
            int new_value = min(max(channel.at<uchar>(i, j) + adjustment, 0), 255);
            channel.at<uchar>(i, j) = static_cast<uchar>(new_value);
        }
    }
}

// 調整影像副函式（使用單通道）
Mat adjust_image(const Mat& img, int r_adjust, int g_adjust, int b_adjust) {
    vector<Mat> bgr_planes;
    split(img, bgr_planes);  // 分離 R、G、B 通道

    adjust_channel(bgr_planes[2], r_adjust);  // 調整 R 通道
    adjust_channel(bgr_planes[1], g_adjust);  // 調整 G 通道
    adjust_channel(bgr_planes[0], b_adjust);  // 調整 B 通道

    Mat adjusted_img;
    merge(bgr_planes, adjusted_img);  // 合併通道
    return adjusted_img;
}

// 顯示影像副函式
void display_image(const Mat& img, const string& window_name) {
    namedWindow(window_name, WINDOW_NORMAL);
    imshow(window_name, img);
}

int main() {
    // 原始影像的資料
    int r_array[4][5] = {
        {247, 67, 32, 187, 240},
        {122, 41, 21, 16, 154},
        {52, 35, 79, 21, 93},
        {27, 22, 35, 154, 75}
    };
    int g_array[4][5] = {
        {14, 145, 132, 25, 40},
        {212, 221, 121, 54, 14},
        {132, 235, 178, 19, 14},
        {122, 122, 133, 54, 47}
    };
    int b_array[4][5] = {
        {17, 44, 32, 127, 240},
        {22, 231, 21, 156, 124},
        {32, 35, 78, 21, 194},
        {127, 22, 33, 54, 45}
    };

    const int col = 4;
    const int row = 5;

    // 建立原始影像
    Mat img_source = create_image(r_array, g_array, b_array, col, row);

    // 調整影像
    Mat img_adjusted = adjust_image(img_source, 28, -30, 0);  // R+28, G-30, B不變

    // 分離 R、G、B 通道
    vector<Mat> bgr_planes;
    split(img_adjusted, bgr_planes);

    // 計算並繪製每個通道的級距直方圖
    draw_histogram(calculate_histogram(bgr_planes[2]), "Red Channel Histogram", Scalar(0, 0, 255));
    draw_histogram(calculate_histogram(bgr_planes[1]), "Green Channel Histogram", Scalar(0, 255, 0));
    draw_histogram(calculate_histogram(bgr_planes[0]), "Blue Channel Histogram", Scalar(255, 0, 0));

    // 顯示影像
    display_image(img_source, "Original Image");
    display_image(img_adjusted, "Adjusted Image");

    waitKey(0);
    return 0;
}
