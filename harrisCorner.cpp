//
// Created by akshay on 3/23/19.
//

#include "harrisCorner.h"

void Harris::stitchImages(Mat& gray1, Mat& gray2){
    Mat rn1, rn2;
//    cvtColor( img1, gray1, CV_BGR2GRAY );
//    cvtColor( img2, gray2, CV_BGR2GRAY );

    rn1 = findCorners(gray1);
    map<pair<int, int>, vector<pair<int, int>>> map1 = findDescriptor(gray1, rn1);
    rn2 = findCorners(gray2);
    map<pair<int, int>, vector<pair<int, int>>> map2 = findDescriptor(gray2, rn2);
    cout<<endl<<"map sizes "<<map1.size()<<" "<<map2.size();
    map<pair<int,int>, pair<int,int>> matches;

    pair<int,int> matching_pair;
    for (auto& itr1: map1){
        int counter = 0;
        float min_dist = 100000;
        cout<<"point from first map: "<<itr1.first.first<<","<<itr1.first.second<<endl;
        for(auto& itr2: map2) {
            counter++;
            float euc_dist = findEucDist(itr1.second, itr2.second);
            cout<<itr2.first.first<<","<<itr2.first.second<<"==="<<euc_dist<<endl;
            if(euc_dist<min_dist) {
                min_dist = euc_dist;
                matching_pair = itr2.first;
            }
        }
        matches[itr1.first] = matching_pair;
    }
    cout<<endl;
    for (auto& itr: matches)
        cout<<itr.first.first<<","<<itr.first.second<<"-->"<<itr.second.first<<","<<itr.second.second<<endl;
    vector<Point2f> src, dst, src1, dst1;
    //for(auto& itr:matches)
    for (auto itr = matches.begin(); itr != matches.end();){

        src.emplace_back(Point2f(itr->first.first, itr->first.second));
        dst.emplace_back(Point2f(itr->second.first, itr->second.second));
        //itr++;itr++;itr++;itr++;itr++;
        //itr+=7;
        std::advance(itr,7);
    }
    cout<<"size!!!: "<<src.size()<<endl;
//    circle(img1, Point(src[12].y, src[12].x), 3, Scalar(255));
//    circle(img2, Point(dst[12].y, dst[12].x), 3, Scalar(255));
//    imshow( "Image 1", img1);
//    imshow( "Image 2", img2);
//    waitKey(0);
    src1.emplace_back(src[2]);src1.emplace_back(src[3]);src1.emplace_back(src[4]);src1.emplace_back(src[7]);src1.emplace_back(src[8]);
    dst1.emplace_back(dst[2]);dst1.emplace_back(dst[3]);dst1.emplace_back(dst[4]);dst1.emplace_back(dst[7]);dst1.emplace_back(dst[8]);

    for(int i=0;i<src.size();i++)
        cout<<src[i].x<<" "<<src[i].y<<endl;
    cout<<endl<<"size: "<<src.size();
    Mat hom = findHomography(src1,dst1,RANSAC);
    cout<<"printing hom\n";
    for(int i =0;i<hom.rows;i++) {
        cout<<endl;
        for (int j = 0; j < hom.cols; j++)
            cout << hom.at<float>(i,j) << " ";
    }
    cout<<endl<<"type: "<<hom.type()<<endl;
    //hom.convertTo(hom, CV_32FC1);
    cout<<endl<<"type: "<<hom.type()<<endl;
    Mat offset(3,3,CV_32FC1,Scalar(0));
    offset.at<float>(0,0)=1;
    offset.at<float>(0,1)=0;
    offset.at<float>(0,2)=100;
    offset.at<float>(1,0)=0;
    offset.at<float>(1,1)=1;
    offset.at<float>(1,2)=100;
    offset.at<float>(2,0)=0;
    offset.at<float>(2,1)=0;
    offset.at<float>(2,2)=1;
    cout<<"test";
    Mat output, homography;
    //homography = offset*hom;
//    hom.at<float> (0,2) = 200;
//    hom.at<float> (1,2) = 200;
    //warpPerspective(gray2, output, hom, Size(gray2.cols, gray2.rows), INTER_CUBIC, BORDER_TRANSPARENT);
    warpPerspective(gray2, output, hom, Size(gray1.cols+gray2.cols, gray2.rows), INTER_CUBIC, BORDER_TRANSPARENT);

    imshow("warped img", output );


    Mat final(Size(gray2.cols*2 + gray1.cols, gray2.rows*2), CV_8UC3);
    Mat roi1(final, Rect(0, 0,  gray1.cols, gray1.rows));
    cout<<"\nimg1 dims: "<<gray1.cols<<" "<<gray1.rows<<endl;
    cout<<"\noutput dims: "<<output.cols<<" "<<output.rows<<endl;
    cout<<"\noutput dims: "<<final.cols<<" "<<final.rows<<endl;
    Mat roi2(final, Rect(0,0, output.cols, output.rows));
    //Mat roi2(final, Rect(0,0, 640, 480));
    output.copyTo(roi2);
    gray1.copyTo(roi1);
    imshow("final", final);

    imshow( "Image 1", gray1);
    imshow( "Image 2", gray2);
//    imshow( "Warped image", output);
    waitKey(0);
}


float Harris::findEucDist(vector<pair<int, int>> des1, vector<pair<int, int>> des2){
    int size = min(des1.size(), des2.size());
    float euc_dist=0;
    for(int i=0; i<size; i++){
        euc_dist += (des1[i].first - des2[i].first)*(des1[i].first - des2[i].first) + (des1[i].first - des2[i].first)*(des1[i].second - des2[i].second);
    }
    return sqrt(euc_dist);
}

Mat Harris::findCorners(Mat& img){
    //namedWindow( "Display window", WINDOW_NORMAL );
    cvtColor( img, gray, CV_BGR2GRAY );

    Sobel(gray, Ix, CV_32FC1 , 1, 0, 7, BORDER_DEFAULT);
    Sobel(gray, Iy, CV_32FC1 , 0, 1, 7, BORDER_DEFAULT);

    pow(Ix,2,Ixx);
    pow(Iy,2,Iyy);
    multiply(Ix,Iy,Ixy);

    GaussianBlur(Ixx, Ixx, Size(3,3), 0, 0);
    GaussianBlur(Iyy, Iyy, Size(3,3), 0, 0);
    GaussianBlur(Ixy, Ixy, Size(3,3), 0, 0);
    multiply(Ixx, Iyy, temp1);
    pow(Ixy,2,temp2);
    determinant = temp1 - temp2;

    trace = Ixx+Iyy;
    pow(trace,2,trace_squared);
    //Mat temp = trace*trace;

    response = determinant - alpha*trace_squared;

    normalize( response, response_norm, 0, 255, NORM_MINMAX);
    //convertScaleAbs(response_norm, response_norm);
    int count = 0;
    for (int i = 0; i < gray.rows; i++) {
        for (int j = 0; j < gray.cols; j++) {
            if (response_norm.at<float>(i, j) > 75) {
                count++;
                circle(img, Point(j, i), 3, Scalar(0,0,255));
            }
        }
    }
    cout<<"Number of corners detected: "<<count<<endl;
    imshow("Harris",img);
    waitKey(0);
    return response_norm;
}

map<pair<int, int>, vector<pair<int, int>>> Harris::findDescriptor(Mat& gray, Mat& response_norm) {
    vector < pair<int, int>> descriptor;
    vector < pair<int, int>> deviations{make_pair(-1, -1), make_pair(-1, 0), make_pair(-1, 1), make_pair(0, -1), make_pair(0, 0),
               make_pair(0, 1), make_pair(1, -1), make_pair(1, 0), make_pair(1, 1)};
    map<pair<int, int>, vector<pair<int, int>>> point_descriptor_pair;

    int count = 0;
    bool pixel_is_in;
    for (int i = 0; i < gray.rows; i++) {
        for (int j = 0; j < gray.cols; j++) {
            if (response_norm.at<float>(i, j) > 75) {
                circle(gray, Point(j, i), 3, Scalar(255));
                for (auto &itr: deviations) {
                    if ((itr.first + i) < gray.rows && (itr.first + i) > 0 && (itr.second + j) < gray.cols &&
                        (itr.second + j) > 0)
                        pixel_is_in = true;
                    else
                        pixel_is_in = false;
                }
                if (pixel_is_in) {
                    cout << "center pixel: " << i << " " << j << endl;
                    for (auto &itr: deviations) {
                        //cout << i + itr.first << " " << j + itr.second << endl;
                        descriptor.emplace_back(make_pair(i + itr.first, j + itr.second));
                    }
                    //cout << descriptor.size() << endl;
                }
                pair<int, int> point = make_pair(i, j);
                //cout << "inserting in map\n";
                point_descriptor_pair[point] = descriptor;
                descriptor.clear();
                count++;
            }
        }
    }

    cout<<"Number of corners detected: "<<count<<endl;
    return point_descriptor_pair;
}

void Harris::harrisVideo() {
    VideoCapture cap("/home/akshay/Downloads/Video1.mp4");
    VideoWriter video("/home/akshay/Downloads/harrisVideo.avi",CV_FOURCC('M','J','P','G'),10, Size(1920,1080));
    cap.set(CV_CAP_PROP_FPS, 10);
    Mat frame, frame_gray;

    if(!video.isOpened())
        return;

    while (1) {
        cap >> frame;

        if (frame.empty())
            break;
        cvtColor( frame, frame_gray, CV_BGR2GRAY );
        findCorners(frame);
        imshow("harris corners", frame);
        waitKey(10);
        video.write(frame);

    }
}