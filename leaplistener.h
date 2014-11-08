#ifndef LEAPLISTENER_H
#define LEAPLISTENER_H
#include "stdafx.h"
#include "Leap.h"
#include <opencv2/opencv.hpp>

class leapListener : public Leap::Listener
{
public:
    virtual void onInit( const Leap::Controller& );
    virtual void onConnect( const Leap::Controller& );
    virtual void onDisconnect( const Leap::Controller& );
    virtual void onExit( const Leap::Controller& );
    virtual void onFrame( const Leap::Controller& );
    virtual void onFocusGained( const Leap::Controller& );
    virtual void onFocusLost( const Leap::Controller& );
    virtual void onDeviceChange( const Leap::Controller& );
    virtual void onServiceConnect( const Leap::Controller& );
    virtual void onServiceDisconnect( const Leap::Controller& );

private:
};

#endif // LEAPLISTENER_H