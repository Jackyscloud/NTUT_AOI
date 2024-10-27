<<<<<<< HEAD
// Purpose of using cpp instead of python
// Try to practice using the linkded list to construct the image process functions
#include <iostream>
#include <vector>
#include <opencv2/opencv.hpp>
#include <string>

using namespace std;

class RGB {
    public:
        vector<vector<int>> R;
        vector<vector<int>> G;
        vector<vector<int>> B;
};

struct Interval_Node{
    int interval_Max;
    int count[3]; // R_count, G_count, B_count in RGB
    Interval_Node* prev;
    Interval_Node* next;
};

typedef Interval_Node* Interval_NodePtr;

class split_interval_count{
    public:
        Interval_NodePtr head;
        int split = 0;
        int Max_Pixel = 255;
        int nodeNum = 0;

        void Build(){

            head = NULL;
            head = new Interval_Node;
            head -> interval_Max = 0;
            head -> prev = NULL;
            head -> next = NULL;
            nodeNum++;

        }

        void add_node(Interval_NodePtr cur, int interval_value){

            if (cur == head) {
                Interval_NodePtr promoted = new Interval_Node;
                head -> next = promoted;
                head -> interval_Max = interval_value;
                promoted -> prev = cur;
                promoted -> next = NULL;
                nodeNum++;

            }
            else {

                Interval_NodePtr promoted = new Interval_Node;
                cur -> next = promoted;
                cur -> interval_Max = interval_value;
                promoted -> prev = cur;
                promoted -> next = NULL;
                nodeNum++;

            }

        }

        void Calculate_interval_Max(){
            int temp = 0;
            Interval_NodePtr cur = head;
            int interval = Max_Pixel / split;

            for (int i = 0; i < split; i++){
                
                temp = interval * (i + 1) + i;

                if (temp > Max_Pixel) temp = Max_Pixel;

                add_node(cur, temp);
                cur = cur -> next;

            }
        }

        void verify(){

            cout << "Verify:" << endl;

            Interval_NodePtr cur = head;

            for (int i = 0 ;i < split; i++){
                cout << cur -> interval_Max << " ";
                cur = cur -> next;
            } cout << endl; cur = head;
            for (int i = 0 ;i < split; i++){
                cout << cur -> count[0] << " ";
                cur = cur -> next;
            } cout << endl; cur = head;
            for (int i = 0 ;i < split; i++){
                cout << cur -> count[1] << " ";
                cur = cur -> next;
            } cout << endl; cur = head;
            for (int i = 0 ;i < split; i++){
                cout << cur -> count[2] << " ";
                cur = cur -> next;
            } cout << endl;

        }

        void count(RGB image_in){

            Interval_NodePtr cur = head;

            int rows = image_in.R.size();
            int columns = image_in.R[0].size();
            

            while (cur != NULL){
                int count_temp[3] = {0,0,0};


                for (int i = 0; i < columns; i++){
                    for (int j = 0; j < rows; j++){
                        
                        if (image_in.R[j][i] <= cur -> interval_Max && image_in.R[j][i] >= cur -> interval_Max - head -> interval_Max){
                            count_temp[0]++;

                        }
                        if (image_in.G[j][i] <= cur -> interval_Max && image_in.G[j][i] >= cur -> interval_Max - head -> interval_Max){
                            count_temp[1]++;
                        }
                        if (image_in.B[j][i] <= cur -> interval_Max && image_in.B[j][i] >= cur -> interval_Max - head -> interval_Max){
                            count_temp[2]++;
                        }

                    }
                }

                cur -> count[0] = count_temp[0];
                cur -> count[1] = count_temp[1];
                cur -> count[2] = count_temp[2];
                cur = cur -> next;

            }
            
        }

        void plot_counting_result(){

            Interval_NodePtr cur = head;

            int scaler = 9;
            int histHeight = 100;
            int binWidth = 50;
            int width = binWidth * split;

            //cout << "The Hight and Width is " << histHeight << " " << width << endl;

            cv::Mat histImageR(histHeight, width, CV_8UC3, cv::Scalar(255, 255, 255));
            cv::Mat histImageG(histHeight, width, CV_8UC3, cv::Scalar(255, 255, 255));
            cv::Mat histImageB(histHeight, width, CV_8UC3, cv::Scalar(255, 255, 255));

            for (int i = 0; i < split; i++){
                
                cv::rectangle(histImageR, cv::Point(i * binWidth, histHeight - (cur -> count[0]) * scaler), cv::Point((i + 1) * binWidth - 10, histHeight), cv::Scalar(0, 0, 255), cv::FILLED);
                cv::rectangle(histImageG, cv::Point(i * binWidth, histHeight - (cur -> count[1]) * scaler), cv::Point((i + 1) * binWidth - 10, histHeight), cv::Scalar(255, 0, 0), cv::FILLED);
                cv::rectangle(histImageB, cv::Point(i * binWidth, histHeight - (cur -> count[2]) * scaler), cv::Point((i + 1) * binWidth - 10, histHeight), cv::Scalar(0, 255, 0), cv::FILLED);

                int mid = binWidth / 4 + i * binWidth;

                cv::putText(histImageR, to_string(cur -> count[0]), cv::Point(mid, 15), cv::FONT_HERSHEY_SIMPLEX, 0.6, cv::Scalar(0, 0, 0), 1);
                cv::putText(histImageG, to_string(cur -> count[1]), cv::Point(mid, 15), cv::FONT_HERSHEY_SIMPLEX, 0.6, cv::Scalar(0, 0, 0), 1);
                cv::putText(histImageB, to_string(cur -> count[2]), cv::Point(mid, 15), cv::FONT_HERSHEY_SIMPLEX, 0.6, cv::Scalar(0, 0, 0), 1);
                
                cur = cur -> next;
            }

            //cv::putText(histImageR, "Red Channel Histogram", cv::Point(40, 15), cv::FONT_HERSHEY_SIMPLEX, 0.6, cv::Scalar(0, 0, 0), 1);

            cv::imshow("Histogram - Red Channel", histImageR);
            cv::imshow("Histogram - Green Channel", histImageG);
            cv::imshow("Histogram - Blue Channel", histImageB);
            cv::waitKey(0);

        }

};

class image_process{
    public:
        RGB image_orignal;

        void create_images(){
            
            image_orignal.R = {
                {247,67,32,187,240},
                {122,41,21,16,154},
                {52,35,79,21,93},
                {27,22,35,154,75}
            };
            image_orignal.G = {
                {14,145,132,25,40},
                {212,221,121,54,14},
                {132,235,178,19,14},
                {122,122,133,54,47},
            };
            image_orignal.B = {
                {17,44,32,127,240},
                {22,231,21,156,124},
                {32,35,78,21,194},
                {127,22,33,54,45},
            };

        }

        int clip(int number){

            if (number > 255) number = 255;
            if (number < 0) number = 0;

            return number;

        }

        RGB image_calc(int shiftR, int shiftG, int shiftB){

            RGB image_calc = image_orignal;

            for (int i = 0; i < 4; i++){

                for (int j = 0; j < 5; j++){
                    image_calc.R[i][j] = clip(image_orignal.R[i][j] + shiftR);
                    image_calc.G[i][j] = clip(image_orignal.G[i][j] + shiftG);
                    image_calc.B[i][j] = clip(image_orignal.B[i][j] + shiftB);
                }

            }
            return image_calc;

        }

        void print_image(RGB image_in){

            int rows = image_in.R.size();
            int columns = image_in.R[0].size();

            for (int i = 0; i < rows; i++){

                for (int j = 0; j < columns; j++){

                    cout << image_in.R[i][j] << " ";

                }

                cout << endl;

            }

        }

};

int main(){
    split_interval_count SIC;
    cout << "Please input the number of split: ";
    cin >> SIC.split;
    SIC.Build();
    SIC.Calculate_interval_Max();

    image_process IP;
    IP.create_images();
    RGB image_new = IP.image_calc(28, -30, 0);
    IP.print_image(image_new);
    SIC.count(image_new);
    SIC.verify();
    SIC.plot_counting_result();
}
=======
﻿#include <iostream>
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
>>>>>>> 2413d3293a51038b626ffb1419c2a189e1d7e345
