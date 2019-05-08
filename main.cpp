#include "harrisCorner.h"


using namespace cv;
using namespace std;

int main(int argc, char* argv[]) {
    
    Mat img1,img2,img3,img4;
    
    if(argc == 1)
    	{
    		cerr<<"No image or video path found. Run the program as\n 1 <path_to_image> OR\n 2 <path_to_video>\n";
    		return 0;
    	}

    Harris h;

    if (*argv[1] == '1')
    {
  		cout<<"Detecting corners in the image\n";
  		img1 = imread(argv[2]);	
    	h.findCorners(img1);
    }	
    else if (*argv[1] == '2')
    {
    	cout<<"Detecting corners in the video\n";
    	string video_name = argv[2];
    	h.harrisVideo(video_name);	
    }
    else{
		cerr<<"No correct image or video path found. Run the program as\n 1 <path_to_image> OR\n 2 <path_to_video>\n";
    }
    //uncomment to find harris corners from a video
    
    
	// untested code to create panaroma from images
    // resize(img2, img2, Size(640,480), 0,0,INTER_LANCZOS4);
    // resize(img3, img3, Size(640,480), 0,0,INTER_LANCZOS4);
    // h.stitchImages(img2,img3);
   
    
    return 0;
}