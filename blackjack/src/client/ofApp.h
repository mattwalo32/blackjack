#pragma once

#include "ofMain.h"
#include "game/GameManager.h"
#include "game/GameConstants.h"
#include <thread>

class ofApp : public ofBaseApp {

	public:
		~ofApp();
		// Implemented OF Functions
		void setup();
		void update();
		void keyPressed(int key);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
		void draw();

		// Drawing helper functions
		void drawBackground();
		void drawCards();
		void drawPlayerNames();
		void drawPlayers();

		GameManager* getGameManager();

		// Unimplemented OF Functions
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);

	private:
		const std::string cardbackPath = "cards/gray_back.png";
		GameManager manager;
		std::thread* gameThread;
		ofImage tableImage;
		ofTrueTypeFont font;
};
