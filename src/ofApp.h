#pragma once
#include <vector>
#include "ofMain.h"
#include "../Spring.h"
#include "../Obj.h"
#include "../Thread.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void mouseScrolled(int x, int y, float scrollX, float scrollY);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
		void exit();
		
private:
	std::vector<Obj*> objects;
	std::vector<Spring*> springs;
	std::vector<Obj*> dragged_objects;
	std::vector<Thread*> threads;
};
