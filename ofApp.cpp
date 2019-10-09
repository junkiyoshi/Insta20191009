#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("openframeworks");

	ofBackground(239);
	ofSetColor(39);
	ofNoFill();
	ofSetLineWidth(2);

	this->font.loadFont("fonts/Kazesawa-Bold.ttf", 120, true, true, true);
}

//--------------------------------------------------------------
void ofApp::update() {

}

//--------------------------------------------------------------
void ofApp::draw() {

	auto x = ofGetWidth() * 0.5;

	for (int y = 60; y < ofGetHeight(); y += 120) {

		string word = "CENTER";
		auto path_list = font.getStringAsPoints(word, true, false);
		for (auto path : path_list) {

			auto outline = path.getOutline();

			ofBeginShape();
			for (int outline_index = 0; outline_index < outline.size(); outline_index++) {

				if (outline_index != 0) { ofNextContour(true); }

				outline[outline_index] = outline[outline_index].getResampledByCount(300);
				auto vertices = outline[outline_index].getVertices();
				for (int vertices_index = 0; vertices_index < vertices.size(); vertices_index++) {

					auto location = glm::vec2(x + vertices[vertices_index].x - this->font.stringWidth(word) * 0.5, y + vertices[vertices_index].y + this->font.stringHeight(word) * 0.5);
					auto noise_value_1 = ofMap(ofNoise(y, location.x * 0.005 + ofGetFrameNum() * 0.01), 0, 1, y, y + 70);
					auto noise_value_2 = ofMap(ofNoise(y, location.x * 0.005 + ofGetFrameNum() * 0.01), 0, 1, y - 70, y);

					if (location.y > noise_value_1) { location.y = noise_value_1; }
					if (location.y < noise_value_2) { location.y = noise_value_2; }

					ofVertex(location);
				}
			}
			ofEndShape(true);
		}
	}
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}