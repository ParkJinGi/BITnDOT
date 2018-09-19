#include "opencv2/opencv.hpp"
#include "opencv2/core.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"

using namespace cv;
using namespace std;

int main(int a, char *arr[]){

	int offset, width, margin;
	offset = 50;
	width = 50;
	margin = 5;

	Mat img;
	img = imread(arr[1],1);

	
	int line_1,line_2,line_3;
	line_1 = img.at<Vec3b>(10, img.cols/2)[0];
	line_2 = img.at<Vec3b>(10, img.cols/2)[1];
	line_3 = img.at<Vec3b>(10, img.cols/2)[2];
	
	
	int val =0;
	if( line_1>200 && line_2<150 && line_3<150){
		val = 1;
	}
/*
	if(val == 0){
		puts("이미지 한 장...");
		imwrite("tmp.jpg", img);
		exit(1);
	}
*/	
	Mat img1 = img(Range(0, img.rows), Range(0, img.cols/2));
	Mat img2 = img(Range(0, img.rows), Range(img.cols/2, img.cols));
	Mat img_result;
	vconcat(img1, img2,img_result);
	
	Mat gray;
	cvtColor(img_result, gray, COLOR_BGR2GRAY);

	Mat img_binary;
	//threshold(gray, img_binary, 0,255, THRESH_BINARY);
	//GaussianBlur(gray, gray, Size(3,3),0);
	/*
	adaptiveThreshold(gray, img_binary, 255, 
			ADAPTIVE_THRESH_MEAN_C, THRESH_BINARY, 
			7, 5);
			imshow("result",img_result);
	
	imshow("2", img_binary);
	waitKey();
*/	
//	imshow("result" ,img_result);
//	waitKey();
	imwrite("Croped_Picture.jpg", img_result);
	return 2;
}
