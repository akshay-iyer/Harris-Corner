//
// Created by akshay on 3/23/19.
//

#ifndef UNTITLED_HARRISCORNER_H
#define UNTITLED_HARRISCORNER_H

#endif //UNTITLED_HARRISCORNER_H
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <opencv2/opencv.hpp>
//#include "opencv2/calib3d.hpp"
//#include "features2d.hpp"
//#include "opencv2/features2d.hpp"
//#include "opencv2/xfeatures2d.hpp"

using namespace cv;
using namespace std;
//using namespace cv::xfeatures2d;

class Harris{
    Mat gray, Ix, Iy, Ixx, Iyy, Ixy, trace, determinant,temp1, temp2, response, response_norm, trace_squared;
    int alpha = 0.005;
public:
    Mat findCorners(Mat& src);
    void stitchImages(Mat&img1, Mat&img2);
    map<pair<int, int>, vector<pair<int, int>>> findDescriptor(Mat& gray, Mat& response_norm);
    float findEucDist(vector<pair<int, int>> des1, vector<pair<int, int>> des2);
    void harrisVideo(string& video_name);
};
