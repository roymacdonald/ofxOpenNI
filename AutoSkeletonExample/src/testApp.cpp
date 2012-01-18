#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup() {

	isMasking		= true;

	nearThreshold = 500;
	farThreshold  = 10000;

	filterFactor = 0.1f;

	ofBackground(0, 0, 0);
#if defined (TARGET_OSX) //|| defined(TARGET_LINUX) // only working on Mac/Linux at the moment (but on Linux you need to run as sudo...)
	hardware.setup();				// libusb direct control of motor, LED and accelerometers
	hardware.setLedOption(LED_OFF);
#endif	
	mContext.setup();
	
	mDepth.setup(&mContext);
	mImage.setup(&mContext);

	mUser.setup(&mContext,true);
	mUser.setSmoothing(filterFactor);				// built in openni skeleton smoothing...
	mUser.setUseMaskPixels(isMasking);

	//mHandTracker.setup(&mContext, 4);
	//mHandTracker.setSmoothing(filterFactor);			// built in openni hand track smoothing...
	//mHandTracker.setFilterFactors(filterFactor);		// custom smoothing/filtering (can also set per hand with setFilterFactor)...set them all to 0.1f to begin with

	mContext.toggleRegisterViewport();
	mContext.toggleMirror();

}

//--------------------------------------------------------------
void testApp::update(){
	#if defined (TARGET_OSX) //|| defined(TARGET_LINUX) // only working on Mac/Linux at the moment (but on Linux you need to run as sudo...)

	hardware.update();
#endif
	

	mContext.update();
	mDepth.update();
	mImage.update();

		// demo getting depth pixels directly from depth gen
	depthRangeMask.setFromPixels(mDepth.getDepthPixels(nearThreshold, farThreshold), mDepth.getWidth(), mDepth.getHeight(), OF_IMAGE_GRAYSCALE);

		// update tracking/ming nodes
		mUser.update();
	
		if (isMasking) {
			allUserMasks.setFromPixels(mUser.getUserPixels(), mUser.getWidth(), mUser.getHeight(), OF_IMAGE_GRAYSCALE);
			user1Mask.setFromPixels(mUser.getUserPixels(1), mUser.getWidth(), mUser.getHeight(), OF_IMAGE_GRAYSCALE);
			user2Mask.setFromPixels(mUser.getUserPixels(2), mUser.getWidth(), mUser.getHeight(), OF_IMAGE_GRAYSCALE);
		}

	
}

//--------------------------------------------------------------
void testApp::draw(){

	ofSetColor(255, 255, 255);

	glPushMatrix();
	glScalef(0.75, 0.75, 0.75);


		mDepth.draw(0,0,640,480);
		mImage.draw(640, 0, 640, 480);

		depthRangeMask.draw(0, 480, 640, 480);	// can use this with openCV to make masks, find contours etc when not dealing with openNI 'User' like object
		mUser.draw();
		drawMasks();
		//mHandTracker.drawHands();

	glPopMatrix();

	ofSetColor(255, 255, 0);

}
//--------------------------------------------------------------
void testApp:: drawMasks() {
	glPushMatrix();
	glEnable(GL_BLEND);
	glBlendFunc(GL_DST_COLOR, GL_ZERO);
	allUserMasks.draw(640, 0);
	glDisable(GL_BLEND);
	//user1Mask.draw(320, 480, 320, 240);
	//user2Mask.draw(640, 480, 320, 240);
	glPopMatrix();
}
//--------------------------------------------------------------
void testApp::keyPressed(int key){

	float smooth;

	switch (key) {
#if defined (TARGET_OSX) //|| defined(TARGET_LINUX) // only working on Mac/Linux at the moment (but on Linux you need to run as sudo...)
		case 357: // up key
			hardware.setTiltAngle(hardware.tilt_angle++);
			break;
		case 359: // down key
			hardware.setTiltAngle(hardware.tilt_angle--);
			break;
#endif
		
		
	
		case 'r':
	//		mContext.toggleRegisterViewport();
			break;
		default:
			break;
	}
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){}
//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){}
//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){}
//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){}
//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){}
//--------------------------------------------------------------
void testApp::windowResized(int w, int h){}