#ifndef _TEST_APP
#define _TEST_APP

#include "ofMain.h"
#include "ofxOpenNI.h"

class testApp : public ofBaseApp{

public:
	void setup();
	void update();
	void draw();

	void keyPressed  (int key);
	void keyReleased(int key);
	void mouseMoved(int x, int y );
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void windowResized(int w, int h);

	
	bool				isMasking;
	
	ofxOpenNIContext	mContext;
	ofxDepthGenerator	mDepth;
	
	ofxImageGenerator	mImage;

	
	ofxUserGenerator	mUser;

#if defined (TARGET_OSX) //|| defined(TARGET_LINUX) // only working on Mac/Linux at the moment (but on Linux you need to run as sudo...)
	ofxHardwareDriver	hardware;
#endif
	
	void				drawMasks();
	
	int					nearThreshold, farThreshold;
	
	ofImage				allUserMasks, user1Mask, user2Mask, depthRangeMask;
	
	float				filterFactor;
	

};

#endif


