#include<opencv2/opencv.hpp>
#include<opencv2/highgui.hpp>
using namespace cv;

int main()
{
    Mat img = imread("C:/users/14537/desktop/4K.jpg");
    Mat resize_img(img);
    resize(img, resize_img, Size(img.cols/7, img.rows/7));
    imshow("4K", resize_img);
    waitKey(0);
    return 0;
}
