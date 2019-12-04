#include "ofApp.h"

ofApp::~ofApp() {
	delete gameThread;
}

//--------------------------------------------------------------
void ofApp::setup(){
	manager.init();
	tableImage.load("table_background.jpg");
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
	drawBackground();

}

void ofApp::drawBackground() {
	tableImage.draw(0, 0, ofGetWindowWidth(), ofGetWindowHeight());
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
	if(!gameThread)
		gameThread = new std::thread(&GameManager::startGame, &manager);
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){
	float width = w;
	float height = width / GameConstants::ASPECT_RATIO;

	//ofSetWindowShape(width, height);
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}

GameManager* ofApp::getGameManager() {
	return &manager;
}