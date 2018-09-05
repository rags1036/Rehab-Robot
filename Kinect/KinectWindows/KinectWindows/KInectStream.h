#pragma once
#include <OpenNI.h>
#include <NiTE.h>
#include <vector>
#include <memory>
#include "gestureInterface.h"
#include <FTGL/FTGLPixmapFont.h>
#include "Window.h"

struct QuadData
{
	int topLeftX, topLeftY;
	int topRightX, topRightY;
	int bottomLeftX, bottomLeftY;
	int bottomRightX, bottomRightY;
	int width, height;

	QuadData(int topLeftX, int topLeftY, int height, int width) : topLeftX(topLeftX), topLeftY(topLeftY), width(width), height(height)
	{
		topRightX = topLeftX + width;
		topRightY = topLeftY;

		bottomLeftX = topLeftX;
		bottomLeftY = topLeftY + height;

		bottomRightX = topLeftX + width;
		bottomRightY = topLeftY + height;
	}
};

class KinectStream
{
private:
	Window *window;

	openni::VideoFrameRef depthFrame;
	openni::VideoFrameRef colourFrame;
	openni::VideoStream colourStream;
	openni::VideoStream depthStream;
	openni::Device kinect;

	openni::VideoStream** streams;

	int colorTextureMapX;
	int colorTextureMapY;
	openni::RGB888Pixel* colorTextureMap;
	openni::RGB888Pixel* depthTextureMap;

	int streamWidth;
	int streamHeight;

	nite::UserTracker tracker;
	nite::UserTrackerFrameRef trackerFrame;
	nite::UserData PrimeUser;
	std::vector<nite::UserData> users;
	nite::SkeletonState userSkeltonState = nite::SKELETON_NONE;


	FTGLPixmapFont font;

	void DrawLimb(nite::UserTracker* pUserTracker, const nite::SkeletonJoint& joint1, const nite::SkeletonJoint& joint2, const nite::UserData& user, const QuadData&);
	void DrawSkeleton(nite::UserTracker* pUserTracker, const nite::UserData& userData, const QuadData&);
	void updateUserState(const nite::UserData& user, uint64_t delta);
	void runTracker(const QuadData&);
	void drawDepthFrame(const QuadData&);
	void drawColorFrame(const QuadData&);
	void initOPGL(int width, int height);


public:
	KinectStream();
	~KinectStream();

	//inits openni, nite, window, creates connection with kinect.
	//returns false if anything fails, prints error to console
	bool init();
	
	//Runs tracker, draws depth, colour stream to window
	void run();

	/**
	* draws string to screen, with 0,0 being the bottom left of the screen.
	* colours doesn't work consistently but here is some examples
	* Cyan: 0xff0000 Pink: 0x00ff00 yellow: 0x0000ff red: 0x00ffff green: 0xff00ff blue: 0xffff00 white: 0x0
	**/
	void drawString(std::string, float x, float y, float z, int size, int colour);

	//Return primeuser skeleton, the user that is currently being tracked. 
	nite::Skeleton* getUserSkeleton();
	
	//Returns true is prime user is no longer on screen
	bool isPrimeUserLost();
	
	Window* getWindow();
	
	//flips buffer on window and updates its width height 
	void BufferSwap();

};

