// demo_joshua.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Leap.h"
#include "LeapMath.h"

#include <opencv2/core/core.hpp>

#include <opencv\cv.h>
#include <opencv2\highgui\highgui.hpp>
#include <opencv2\imgproc\imgproc.hpp>
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <stdio.h>
#include <iostream>


//#include <QApplication>
//#include <QQmlApplicationEngine>
#include "leaplistener.h"


using namespace Leap;
using namespace std;
using namespace cv;


class SampleListener : public Listener {
    public:
    virtual void onConnect(const Controller&);
    virtual void onFrame(const Controller&);
};

void SampleListener::onConnect(const Controller& controller) {
    std::cout << "Connected" << std::endl;
	controller.enableGesture(Gesture::TYPE_SWIPE);
}

void SampleListener::onFrame(const Controller& controller) {
	const Frame frame = controller.frame();
	ImageList images = frame.images();
	Image image = images[0];
	cout << "width = " << image.width() << "height == " << image.height() << endl;
    /*std::cout << "Frame id: " << frame.id()
          << ", timestamp: " << frame.timestamp()
		  << ", hands: " << frame.hands().count()
          << ", fingers: " << frame.fingers().count()
          << ", tools: " << frame.tools().count()
          << ", gestures: " << frame.gestures().count() << std::endl;
	  */
}

int main(int argc, char *argv[])
{
    
    leapListener listener;
    Leap::Controller controller;

    controller.addListener( listener );

    Leap::Controller::PolicyFlag addImagePolicy;
    addImagePolicy = ( Leap::Controller::PolicyFlag )
            ( Leap::Controller::PolicyFlag::POLICY_IMAGES |
             controller.policyFlags());

    controller.setPolicyFlags( addImagePolicy );
    std::cout << "Press Enter to quit..." << std::endl;
    std::cin.get();

    controller.removeListener( listener );

    return 0;
}


