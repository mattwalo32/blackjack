#include "ofApp.h"
#include <math.h>

ofApp::~ofApp() {
	delete gameThread;
}

//--------------------------------------------------------------
void ofApp::setup(){
	manager.init();
	tableImage.load("table_background.jpg");
	font.loadFont("ArterioNonCommercial.otf", GameConstants::FONT_SIZE);
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
	drawBackground();
	if (!manager.getRunningGame()) {
		drawPlayerNames();
	} else {
		drawCards();
		drawPlayers();
	}
}

void ofApp::drawPlayerNames() {
	float centerX = ofGetWindowWidth() / 2;
	float centerY = ofGetWindowHeight() / 2;
	float currentY = GameConstants::JOINED_PLAYERS_Y * ofGetWindowHeight();
	float w = GameConstants::JOINED_PLAYERS_BOX_WIDTH * ofGetWindowWidth();
	float h = GameConstants::JOINED_PLAYERS_BOX_HEIGHT * ofGetWindowHeight();

	float height = font.getLineHeight();
	float offset = height * 1.5;

	ofSetColor(100, 20, 10);
	ofRect(centerX - w/2, centerY - h/2, w, h);
	ofSetColor(255, 255, 255);

	std::string msg = "Players Joined";
	ofRectangle rect = font.getStringBoundingBox(msg, 0,0);
	font.drawString(msg, centerX - rect.width / 2, currentY);

	for (Strategy* strategy : manager.getPlayers()) {
		currentY += offset;
		std::string msg = strategy->getName();
		ofRectangle rect = font.getStringBoundingBox(msg, 0, 0);
		font.drawString(msg, centerX - rect.width / 2, currentY);
	}
}

void ofApp::drawBackground() {
	ofSetColor(255, 255, 255);
	tableImage.draw(0, 0, ofGetWindowWidth(), ofGetWindowHeight());
}

void ofApp::drawCards() {
	for (Strategy* strategy : manager.getRunningGame()->getPlayers()) {
		float x = strategy->tableLocationX * ofGetWindowWidth();
		float y = strategy->tableLocationY * ofGetWindowHeight();
		float rotation = strategy->angle;

		float w = GameConstants::PERCENT_CARD_WIDTH * ofGetWindowWidth();
		float h = GameConstants::CARD_ASPECT_RATIO * w;

		std::vector<std::string> paths = strategy->getHandImgPaths();
		ofImage image;

		int cardNum = 1;

		for (std::string path : paths) {
			if (strategy->playerIsDealer() && paths.size() == 2 && cardNum == 2)
				path = cardbackPath;
			image.load(path);
			ofPushMatrix();

			ofTranslate(x, y, 0);
			image.setAnchorPercent(0.5f, 0.5f);
			ofRotateRad(rotation);
			image.draw(0, 0, w, h);
			ofPopMatrix();

			x += ofGetWindowWidth() * GameConstants::CARD_STACK_OFFSET[0] * sin(rotation);
			y += ofGetWindowHeight() * GameConstants::CARD_STACK_OFFSET[1] * cos(rotation);
			cardNum++;
		}
	}
}

void ofApp::drawPlayers() {
	for (Strategy* strategy : manager.getRunningGame()->getPlayers()) {
		float x = strategy->tableLocationX * ofGetWindowWidth();
		float y = strategy->tableLocationY * ofGetWindowHeight();
		float angle = strategy->angle;

		std::string userInfo = strategy->getName();

		if (!strategy->playerIsDealer())
			userInfo += "\nWins: " + std::to_string(strategy->getNumWins());

		float textWidth = font.getStringBoundingBox(userInfo, 0, 0).getWidth();

		ofPushMatrix();
		ofTranslate(x, y);
		ofRotate(angle);
		ofScale(0.4, 0.4, 1);
		font.drawString(userInfo, -textWidth/2, ofGetWindowHeight() * GameConstants::INFO_OFFSET[1]);
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
