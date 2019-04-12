#include "ofApp.h"

int particleLife = 360;

//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(0);
    ofSetFrameRate(60);
    ofSetVerticalSync(true);
    
    // Create particles
    particleCount = ofGetWidth() * ofGetHeight() * particleLife / 12000;
    particles.reserve(particleCount);
    for (int i = 0; i < particleCount; i++){
        particle p;
        p.setup();
        p.age = ofRandom(0, particleLife);
        particles.push_back(p);
    }
    
    // Mouselight settings
    ofSetSmoothLighting(true);
    mouseLight.setPointLight();
    mouseLight.setAttenuation(0.f,0.f,0.0001);
    mouseLight.setAmbientColor(ofFloatColor(0.f,0.f,0.f));
    mouseLight.setDiffuseColor(ofFloatColor(1.f,1.f,1.f));
    
    // Create fractal noise map arrays
    turbulenceMap1 = new float*[ofGetWidth()];
    for (int i = 0; i < ofGetWidth(); i++) turbulenceMap1[i] = new float[ofGetHeight()];
    turbulenceMap2 = new float*[ofGetWidth()];
    for (int i = 0; i < ofGetWidth(); i++) turbulenceMap2[i] = new float[ofGetHeight()];
    
    // Fractal settings/generation
    FastNoise fractalNoise;
    fractalNoise.SetNoiseType(FastNoise::SimplexFractal);
    fractalNoise.SetFrequency(0.007);
    
    for (int x = 0; x < ofGetWidth(); x++){
        for (int y = 0; y < ofGetHeight(); y++){
            turbulenceMap1[x][y] = fractalNoise.GetNoise(x,y);
        }
    }
    
    fractalNoise.SetSeed(2000);
    
    for (int x = 0; x < ofGetWidth(); x++){
        for (int y = 0; y < ofGetHeight(); y++){
            turbulenceMap2[x][y] = fractalNoise.GetNoise(x,y);
        }
    }
}

//--------------------------------------------------------------
void ofApp::update(){
    // Update particles
    for (particle &p : particles)
        p.update(turbulenceMap1, turbulenceMap2, mouseX, mouseY);
    
    // Update light
    mouseLight.setPosition(mouseX, mouseY, 25);
}

//--------------------------------------------------------------
void ofApp::draw(){
    cout << ofGetFrameRate() << endl;
    ofEnableDepthTest();
//    ofEnableLighting();
    ofSetGlobalAmbientColor(ofFloatColor(0.f,0.f,0.f));
//    mouseLight.enable();
    
    // Draw particles
    ofFill();
    for (particle &p : particles)
        p.draw();
    
//    mouseLight.disable();
//    ofDisableLighting();
    ofDisableDepthTest();
    
    // Draw border rectangle
    ofSetColor(255,255,255);
    ofNoFill();
    ofSetLineWidth(100);
    ofDrawRectangle(0,0,ofGetWidth(),ofGetHeight());
    ofSetLineWidth(0);
}


//--------------------------------------------------------------
void ofApp::keyPressed(int key){

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
void ofApp::windowResized(int w, int h){
    
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
