#include "ofApp.h"

ofApp::~ofApp() {
	delete gameThread;
}

//--------------------------------------------------------------
void ofApp::setup(){
	manager.init();
	tableImage.load("table_background.jpg");
	testCard.load("cards/2C.png");
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
	drawBackground();
	drawPlayers();
}

void ofApp::drawBackground() {
	tableImage.draw(0, 0, ofGetWindowWidth(), ofGetWindowHeight());
}

void ofApp::drawPlayers() {
	if (!manager.getRunningGame())
		return;

	for (Strategy* strategy : manager.getRunningGame()->getPlayers()) {
		float x = strategy->tableLocationX * ofGetWindowWidth();
		float y = strategy->tableLocationY * ofGetWindowHeight();
		float rotation = strategy->angle;

		float w = GameConstants::PERCENT_CARD_WIDTH * ofGetWindowWidth();
		float h = GameConstants::CARD_ASPECT_RATIO * w;

		ofPushMatrix();
		ofTranslate(x, y, 0);
		testCard.setAnchorPercent(0.5f, 0.5f);
		ofRotateRad(rotation);
		testCard.draw(0, 0, w, h);
		ofPopMatrix();
	}
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
	float height = h;
	float width = height * GameConstants::WINDOW_ASPECT_RATIO;

	ofSetWindowShape(width, height);
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
