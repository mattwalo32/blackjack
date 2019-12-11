#include "ofApp.h"
#include <math.h>

ofApp::~ofApp() {
	manager.stopGame();
}

//--------------------------------------------------------------
void ofApp::setup(){
	manager.init();
	tableImage.load("table_background.jpg");
	font.loadFont("ArterioNonCommercial.otf", GameConstants::FONT_SIZE);
}


//--------------------------------------------------------------
void ofApp::draw(){
	drawBackground();
	if (!manager.isGameRunning()) {
		drawPlayerNames();
	} else {
		drawCards();
		drawPlayers();
	}
}

/*
 * Draws the names of all the players that joined the game and are in the lobby.
 */
void ofApp::drawPlayerNames() {
	float centerX = ofGetWindowWidth() / 2;
	float centerY = ofGetWindowHeight() / 2;
	float currentY = GameConstants::JOINED_PLAYERS_Y * ofGetWindowHeight();
	float w = GameConstants::JOINED_PLAYERS_BOX_WIDTH * ofGetWindowWidth();
	float h = GameConstants::JOINED_PLAYERS_BOX_HEIGHT * ofGetWindowHeight();

	float height = font.getLineHeight();
	float offset = height * 1.5;

	ofSetColor(100, 20, 10, 200);
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

/*
 * Draws the background image and any instruction prompts
 */
void ofApp::drawBackground() {
	ofSetColor(255, 255, 255);
	tableImage.draw(0, 0, ofGetWindowWidth(), ofGetWindowHeight());

	std::string message = manager.isGameRunning() ? "Press space to exit to lobby." : "Press space to start";
	float height = font.getLineHeight() * 0.4;
	float width = font.getStringBoundingBox(message, 0, 0).getWidth() * 0.4;

	ofPushMatrix();
	ofTranslate((ofGetWindowWidth() - width) / 2, height, 0);
	ofScale(0.4, 0.4, 1);
	font.drawString(message, 0, 0);
	ofPopMatrix();
}

/*
 * Draws the cards of each player. The cards are drawn in such a way that they will be 
 * slightly overlapping, but not completly.
 */
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

			if (cardNum == paths.size()) {
				std::string scoreInfo = "Score: " + std::to_string(strategy->getHandValue());
				float scoreWidth = font.getStringBoundingBox(scoreInfo, 0, 0).getWidth();

				ofPushMatrix();
				ofTranslate(x, y);
				ofRotate(rotation);
				ofScale(0.55, 0.55, 1);
				font.drawString(scoreInfo, -scoreWidth / 2, ofGetWindowHeight() * GameConstants::SCORE_OFFSET[1]);
				ofPopMatrix();
			}

			x += ofGetWindowWidth() * GameConstants::CARD_STACK_OFFSET[0] * sin(rotation);
			y += ofGetWindowHeight() * GameConstants::CARD_STACK_OFFSET[1] * cos(rotation);
			cardNum++;
		}
	}
}

/*
 * Draws all the info about the players on the screen such as their names and
 * total wins.
 */
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
	if (key == 32) {
		if (!manager.isGameRunning())
			gameThread = new std::thread(&GameManager::startGame, &manager);
		else
			manager.stopGame();
	}
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h) {
	float height = h;
	float width = height * GameConstants::WINDOW_ASPECT_RATIO;

	ofSetWindowShape(width, height);
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y){

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
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}

GameManager* ofApp::getGameManager() {
	return &manager;
}
