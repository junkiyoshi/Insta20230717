#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(30);
	ofSetWindowTitle("openframeworks");

	ofBackground(239);
	ofSetLineWidth(1.5);
	//ofEnableBlendMode(ofBlendMode::OF_BLENDMODE_ADD);

	this->len = 30;
	for (float x = 0; x < ofGetWidth(); x += this->len) {

		for (float y = 0; y < ofGetHeight(); y += this->len) {

			this->start_location_list.push_back(glm::vec3(x, y, 0));
		}
	}

	for (int i = 0; i < 16; i++) {

		int r = ofRandom(this->start_location_list.size());

		auto log_list = vector<glm::vec2>();
		log_list.push_back(this->start_location_list[r]);
		this->location_list.push_back(log_list);
	}
}

//--------------------------------------------------------------
void ofApp::update() {

	if (ofGetFrameNum() % 2 == 0) {

		for (auto& log_list : this->location_list) {

			int r = ofRandom(4);
			int deg_start = r * 90;
			for (int deg = deg_start; deg < deg_start + 360; deg += 90) {

				auto tmp_location = log_list.back() + glm::vec2(this->len * cos(deg * DEG_TO_RAD), this->len * sin(deg * DEG_TO_RAD));
				if (tmp_location.x < 0 || tmp_location.x > ofGetWidth() - this->len || tmp_location.y < 0 || tmp_location.y > ofGetHeight() - this->len) {

					continue;
				}

				bool flag = false;
				for (int i = 0; i < log_list.size(); i++) {

					if (tmp_location == log_list[i] && deg_start != deg && deg_start % 360 == deg % 360){

						flag = true;
						break;
					}
				}
				if (flag) { continue; }

				log_list.push_back(tmp_location);
				break;
			}

			while (log_list.size() > 5) {

				log_list.erase(log_list.begin());
			}
		}
	}
}

//--------------------------------------------------------------
void ofApp::draw() {

	int color_index = 0;
	for (auto& log_list : this->location_list) {

		for (int i = 0; i < log_list.size(); i++) {

			ofFill();
			ofSetColor(ofColor(0, ofMap(i, 0, log_list.size(), 32, 200)));
			ofDrawRectangle(log_list[i], this->len, this->len);

			ofNoFill();
			ofSetColor(0);
			ofDrawRectangle(log_list[i], this->len, this->len);
		}
	}

	ofSetColor(0, 32);
	ofNoFill();
	for (float x = 0; x < ofGetWidth(); x += this->len) {

		for (float y = 0; y < ofGetHeight(); y += this->len) {

			ofDrawRectangle(glm::vec3(x, y, 0), this->len, this->len);
		}
	}
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}