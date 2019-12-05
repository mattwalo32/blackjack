#pragma once

#include "ofMain.h"
#include "game/GameManager.h"
#include "game/GameConstants.h"
#include <thread>

class ofApp : public ofBaseApp {

	public:
		~ofApp();
		void setup();
		void update();
		void draw();

		void drawBackground();
		void drawCards();
		void drawPlayerNames();
		void drawPlayers();

		GameManager* getGameManager();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);

	private:
		const std::string cardbackPath = "cards/gray_back.png";
		GameManager manager;
		std::thread* gameThread;
		ofImage tableImage;
		ofTrueTypeFont font;
};
