#ifndef _TEST_APP
#define _TEST_APP

//#define USE_IR // Uncomment this to use infra red instead of RGB cam...

#include "ofxOpenNI.h"
#include "ofMain.h"
#include "DSLRRemoteLib.h"

//#define CALIBRATION_MODE
#define Y_THRESHOLD -450

/* App States */

#define TRACK_USERS_STATE 1
#define DISPLAY_COUNTER_STATE 2
#define TAKE_PHOTO_STATE 3
#define DISPLAY_PHOTO_STATE 4
#define ERROR_STATE 5

/* Counters */
#define END_OF_THE_WORLD 10 /* seconds */
#define PHOTO_DISPLAY_TIME 10 /*seconds*/

/* Define the max no of users MAX_NUMBER_USERS 8 */
#define NO_OF_USERS 1

typedef struct{
	bool UsersTracked;
	bool AllUsersInsideHotSpot;
} UsersStatus;

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

	void	setupRecording(string _filename = "");
	void	setupPlayback(string _filename);
	string	generateFileName();

	void StateMachineUpdate(void);
	void StateMachineDraw(void);
	void ChangeToDisplayCounter(void);
	void ChangeToDisplayPhoto(void);
	void ChangeToTakePhoto(void);
	UsersStatus UpdateUsersStatus(void);

	bool				isLive, isTracking, isRecording, isCloud, isCPBkgnd, isMasking,takePhoto;
	bool				isTrackingHands, isFiltering;
	int globalCounter;
	ofxOpenNIContext	recordContext, playContext;
	ofxDepthGenerator	recordDepth, playDepth;

#ifdef USE_IR
	ofxIRGenerator		recordImage, playImage;
#else
	ofxImageGenerator	recordImage, playImage;
#endif

	ofxHandGenerator	recordHandTracker, playHandTracker;

	ofxUserGenerator	recordUser, playUser;
	ofxOpenNIRecorder	oniRecorder;

#if defined (TARGET_OSX) //|| defined(TARGET_LINUX) // only working on Mac/Linux at the moment (but on Linux you need to run as sudo...)
	ofxHardwareDriver	hardware;
#endif

	void				drawMasks();
	void				drawPointCloud(ofxUserGenerator * user_generator, int userID);

	int					nearThreshold, farThreshold;
	int					pointCloudRotationY;

	ofImage				allUserMasks, user1Mask, user2Mask, depthRangeMask, photo;

	float				filterFactor;
	
	int 				CurrentState;

	float				DisplayCounterInitTime, DisplayPhotoInitTime;

	char PhotoFilename[1024];

	ofVideoPlayer 		getReadyMovie;
};

#endif
