#include "stdafx.h"
#include "leaplistener.h"


#include <opencv2/core/core.hpp>

#include <opencv\cv.h>
#include <opencv2\highgui\highgui.hpp>
#include <opencv2\imgproc\imgproc.hpp>
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <stdio.h>
#include <iostream>
using namespace cv;
using namespace Leap;

void leapListener::onInit( const Leap::Controller &controller)
{
    std::cout << "Initialized" << std::endl;
}

void leapListener::onConnect( const Leap::Controller &controller)
{
    std::cout << "Connected" << std::endl;
    controller.enableGesture(Leap::Gesture::TYPE_CIRCLE);
    controller.enableGesture(Leap::Gesture::TYPE_KEY_TAP);
    controller.enableGesture(Leap::Gesture::TYPE_SCREEN_TAP);
    controller.enableGesture(Leap::Gesture::TYPE_SWIPE);
}

void leapListener::onDisconnect( const Leap::Controller &controller)
{
    std::cout << "Disconnected" << std::endl;
}

void leapListener::onExit( const Leap::Controller &controller)
{
    std::cout << "Exited" << std::endl;
}

void skeleton_fingerDetection(Mat bwImg){

	Mat edges;
	Canny(bwImg, edges, 0, 30, 3);
	//dilate(edges,edges,NULL);
	cv::dilate(edges, edges, cv::Mat(), cv::Point(-1,-1));
	imshow("Edges" , edges);

	Mat skel(bwImg.size(), CV_8UC1, cv::Scalar(0));
	Mat temp(bwImg.size(), CV_8UC1);
	Mat element = cv::getStructuringElement(cv::MORPH_CROSS, cv::Size(3, 3));
	bool done;
	do
	{
		morphologyEx(bwImg, temp, cv::MORPH_OPEN, element);
		bitwise_not(temp, temp);
		bitwise_and(bwImg, temp, temp);
		bitwise_or(skel, temp, skel);
		erode(bwImg, bwImg, element);

		double max;
		cv::minMaxLoc(bwImg, 0, &max);
		done = (max == 0);
	} while (!done);
	//cv::dilate(skel, skel, cv::Mat(), cv::Point(-1,-1));
	imshow("skeleton", skel);


	//bitwise_and(skel,edges,skel);
	//imshow(" Finger tips using bitwise And", skel);
	bitwise_or(skel,edges,edges);
	imshow("bitwise or", edges);


}

void convexDefects_fingerDetection(Mat bufferImg){
	RNG rng(12345);
	vector<vector<Point> > contours;
	vector<Vec4i> hierarchy;

	findContours(bufferImg, contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);
	cvtColor( bufferImg, bufferImg, CV_GRAY2BGR );
	
	for (int i = 0; i < contours.size(); i++){
		if(contours.size() != NULL){
			Scalar color = Scalar( rng.uniform(0, 255), rng.uniform(0,255), rng.uniform(0,255) );
			drawContours(bufferImg, contours, i, color, 1, 8, hierarchy);
		}
	}
  
	imshow("Contours" , bufferImg);


	if( contours.size() > 0 ){
		
		Mat drawing = Mat::zeros( bufferImg.size(), CV_8UC3 );
		vector<vector<int> >hull( contours.size() );
        vector<vector<Vec4i>> convDef(contours.size() );
        vector<vector<Point>> hull_points(contours.size());
        vector<vector<Point>> defect_points(contours.size());

		for( int i = 0; i < contours.size(); i++ )
        {
            if(contourArea(contours[i])>5000)
            {
                convexHull( contours[i], hull[i], false );
                convexityDefects( contours[i],hull[i], convDef[i]);

                // start_index, end_index, farthest_pt_index, fixpt_depth

                for(int k=0;k<hull[i].size();k++)
                {           
                    int ind=hull[i][k];
                    hull_points[i].push_back(contours[i][ind]);
                }

                for(int k=0;k<convDef[i].size();k++)
                {           
                    if(convDef[i][k][3]>20*256)
                    {
                        int ind_0=convDef[i][k][0];
                        int ind_1=convDef[i][k][1];
                        int ind_2=convDef[i][k][2];
                        defect_points[i].push_back(contours[i][ind_2]);
                        circle(drawing,contours[i][ind_0],5,Scalar(0,255,0),-1);
                        circle(drawing,contours[i][ind_1],5,Scalar(0,255,0),-1);
                        circle(drawing,contours[i][ind_2],5,Scalar(0,0,255),-1);
                        line(drawing,contours[i][ind_2],contours[i][ind_0],Scalar(0,0,255),1);
                        line(drawing,contours[i][ind_2],contours[i][ind_1],Scalar(0,0,255),1);
                    }
                }

                drawContours( drawing, contours, i, Scalar(0,255,0), 1, 8, vector<Vec4i>(), 0, Point() );
                drawContours( drawing, hull_points, i, Scalar(255,0,0), 1, 8, vector<Vec4i>(), 0, Point() );
            }
        }
		namedWindow( "Hull Finger Detection",cv::WINDOW_AUTOSIZE );
		imshow( "Hull Finger Detection", drawing );
	}
	
	
}

void distanceTransform(Mat bwImg){ // for optimizing skeleton method TBD
	Mat dist;
    distanceTransform(bwImg, dist, CV_DIST_L2, 3);
	normalize(dist, dist, 0.0, 1.0, NORM_MINMAX);
	//inRange(dist,.7,.8,dist);
    imshow("Distance Transform", dist);
}


void leapListener::onFrame( const Leap::Controller &controller)
{
	
    Frame frame = controller.frame();
    ImageList images = frame.images();
	
	Image image = images[1];
	const unsigned char* image_buffer = image.data();
	
	//std::cout << " height = " << image.height() << " width = " << image.width() << std::endl;
    
	Mat opencvImg = Mat( image.height(), image.width(), CV_8UC1 );
    opencvImg.data = (unsigned char*)image.data();

    Mat bwImg = cv::Mat( image.height(), image.width(), CV_8UC1 );
    threshold(opencvImg, bwImg, 0, 255, CV_THRESH_BINARY | CV_THRESH_OTSU);

	imshow("binary Image" , bwImg);
	imshow("opencv Image" , opencvImg);


	Mat bufferImg = Mat::zeros(opencvImg.size(), CV_8UC3);
	
	bufferImg = bwImg;
	
	//skeleton_fingerDetection(bwImg);
	
	convexDefects_fingerDetection(bufferImg);
	//distanceTransform(bwImg);
	

    waitKey(1);

	//std::cout <<"Image Information this is how big it is "<<image.width()<<std::endl;
}

void leapListener::onFocusGained( const Leap::Controller &controller)
{
    std::cout << "Focus Gained" << std::endl;
}

void leapListener::onFocusLost( const Leap::Controller &controller)
{
    std::cout << "Focus Lost" << std::endl;
}

void leapListener::onDeviceChange( const Leap::Controller &controller)
{
    std::cout << "Device Changed" << std::endl;
    const Leap::DeviceList devices = controller.devices();

    for (int i = 0; i < devices.count(); ++i) {
        std::cout << "id: " << devices[i].toString() << std::endl;
        std::cout << "  isStreaming: " << (devices[i].isStreaming() ? "true" : "false") << std::endl;
    }
}

void leapListener::onServiceConnect( const Leap::Controller &controller)
{
    std::cout << "Service Connected" << std::endl;
}

void leapListener::onServiceDisconnect( const Leap::Controller &controller)
{
    std::cout << "Service Disconnected" << std::endl;
}