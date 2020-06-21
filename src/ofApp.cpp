#include "../barrier.h"
#include "ofApp.h"

const int THREADS_COUNT = 11;
const int N = 50;
const int M = 350;
const float dx = 4;
const float dy = 4;
const float r = 2;

float mouse_radius = 20;


Barrier b1(THREADS_COUNT);
Barrier b2(THREADS_COUNT);
Barrier b3(THREADS_COUNT);


//--------------------------------------------------------------
void ofApp::setup(){
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			auto obj = new Obj();
			obj->setCoord(ofVec2f(100 + dx * j, 100 + dy * i));
			obj->setAnchored(i == 0);
			obj->setRadius(r);
			objects.push_back(obj);
		}
	}

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M - 1; j++) {
			auto spring = new Spring();
			spring->setLength(dx);
			spring->setObjects(objects[i * M + j], objects[i * M + j + 1]);
			springs.push_back(spring);
		}
	}

	for (int i = 0; i < N - 1; i++) {
		for (int j = 0; j < M; j++) {
			auto spring = new Spring();
			spring->setLength(dy);
			spring->setObjects(objects[i * M + j], objects[(i + 1) * M + j]);
			springs.push_back(spring);
		}
	}

	int per_thread_o = objects.size() / THREADS_COUNT;
	int some_more_obj = objects.size() % THREADS_COUNT;
	std::vector<int> objs_per_thread;
	
	for (int i = 0; i < THREADS_COUNT; i++)
		if ( i < some_more_obj)
			objs_per_thread.push_back(per_thread_o + 1);
		else
			objs_per_thread.push_back(per_thread_o);
	
	//for (int i = 0; i < some_more_obj; i++)
	//	objs_per_thread[i] += 1;
	

	int per_thread_s = springs.size() / THREADS_COUNT;
	int some_more_s = springs.size() % THREADS_COUNT;
	std::vector<int> springs_per_thread;

	for (int i = 0; i < THREADS_COUNT; i++)
		springs_per_thread.push_back(per_thread_s);

	for (int i = 0; i < some_more_s; i++)
		springs_per_thread[i] += 1;

	int oc = 0, sc = 0;
	for (int i = 0; i < THREADS_COUNT; i++) {

		Thread* thread = new Thread(objects, springs, oc, oc + objs_per_thread[i], sc, sc + springs_per_thread[i]);
		oc += objs_per_thread[i];
		sc += springs_per_thread[i];
		threads.push_back(thread);
	}
	


	for (Thread* thread : threads)
		thread->setBarriers(b1, b2, b3);

	for (Thread* thread : threads)
		thread->startThread();
}

//--------------------------------------------------------------
void ofApp::update(){
	//for (auto obj : objects)
	//	obj->resetForce();

	//for (auto spring : springs)
	//	spring->step();

	//for (auto obj : objects)
	//	obj->step();
}

//--------------------------------------------------------------
void ofApp::draw(){


	//for (auto spring : springs)
	//	spring->draw();

	for (auto obj : objects)
		obj->draw();

	ofNoFill();
	ofSetColor(255);
	ofDrawCircle(ofGetMouseX(), ofGetMouseY(), mouse_radius);
	std::ostringstream fr_str;
	fr_str << ofGetFrameRate();
	ofDrawBitmapString(fr_str.str(), 10, 10);
	
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
	if (button == 0)
		for (Obj* obj : dragged_objects)
			obj->moveTo(ofVec2f(x, y));

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
	if (button == 0)
		for (auto obj : objects) {
			ofVec2f offset = obj->getCoord() - ofVec2f(x, y);

			if (offset.length() < mouse_radius)
			{
				obj->startDragging(offset);
				dragged_objects.push_back(obj);
			}
		}
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
	if (button == 0) {
		for (Obj* obj : dragged_objects)
			obj->endDragging();
		dragged_objects.clear();
	}

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}

void ofApp::mouseScrolled(int x, int y, float scrollX, float scrollY){
	if (scrollY > 0)
		mouse_radius += 1;
	else
		mouse_radius -= 1;
}

void ofApp::exit() {
	for (Thread* thread : threads)
		thread->stopThread();

	for (Thread* thread : threads)
		thread->waitForThread();
}