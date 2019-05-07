#include "harrisCorner.h"


using namespace cv;


int main() {
    std::cout << "Hello, World!" << std::endl;
    Mat img1,img2,img3,img4;
    //src = imread("/home/akshay/Mask_RCNN/src/apple.jpg", CV_LOAD_IMAGE_COLOR);
    img1 = imread("/home/akshay/Downloads/img1.jpg", CV_LOAD_IMAGE_COLOR);
    img2 = imread("/home/akshay/Downloads/img2.jpg", CV_LOAD_IMAGE_COLOR);
    img3 = imread("/home/akshay/Downloads/img3.jpg", CV_LOAD_IMAGE_COLOR);
    img4 = imread("/home/akshay/Downloads/img4.jpg", CV_LOAD_IMAGE_COLOR);
    resize(img2, img2, Size(640,480), 0,0,INTER_LANCZOS4);
    resize(img3, img3, Size(640,480), 0,0,INTER_LANCZOS4);

    Harris h;
    h.stitchImages(img2,img3);
    //h.harrisVideo();
    //h.findCorners(img1);
    return 0;
}