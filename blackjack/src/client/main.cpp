#include "ofMain.h"
#include "ofApp.h"
#include "game/GameConstants.h"

using namespace GameConstants;

//========================================================================
int main( ){
	ofSetupOpenGL(DEFAULT_WINDOW_WIDTH, DEFAULT_WINDOW_HEIGHT, OF_WINDOW);			// <-------- setup the GL context
	ofSetFrameRate(60);
	ofRunApp(new ofApp());

}
