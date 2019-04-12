#include "ofApp.h"
#include "FastNoiseSIMD.h"

int particleLife = 360;
int evolutions = 128; // Best at around 128. Should be multiple of 8.
int dancerRadius = 35*35;

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
    fractal = new float**[ofGetWidth()/2];
    for (int i = 0; i < ofGetWidth()/2; i++){
        fractal[i] = new float*[ofGetHeight()/2];
        for (int j = 0; j < ofGetHeight()/2; j++)
            fractal[i][j] = new float[evolutions];
    }
    
    // Fractal settings/generation
    cout << "This run will need calculate at least " << ofGetWidth()/2*ofGetHeight()/2*evolutions*4*0.000001 << "MB of noise." << endl;
    FastNoiseSIMD* fractalNoise = FastNoiseSIMD::NewFastNoiseSIMD();
    fractalNoise->SetFrequency(0.02);
    float* noiseSet = fractalNoise->GetSimplexFractalSet(0, 0, 0, ofGetWidth()/2, ofGetHeight()/2, evolutions);
    int index = 0;
    for (int x = 0; x < ofGetWidth()/2; x++){
        for (int y = 0; y < ofGetHeight()/2; y++){
            for (int z = 0; z < evolutions; z++){
                fractal[x][y][z] = noiseSet[index++];
            }
        }
    }
    FastNoiseSIMD::FreeNoiseSet(noiseSet);
}

//--------------------------------------------------------------
void ofApp::update(){
    // Update particles
    for (particle &p : particles)
        p.update(fractal, mouseX, mouseY);
    
    // Update light
    mouseLight.setPosition(mouseX, mouseY, 25);
}

//--------------------------------------------------------------
void ofApp::draw(){
    if (ofGetFrameRate() < 55){ cout << "Frame rate is below 55: " << ofGetFrameRate() << endl;}
    ofEnableDepthTest();
    ofEnableLighting();
    ofSetGlobalAmbientColor(ofFloatColor(0.f,0.f,0.f));
    mouseLight.enable();
    
    // Draw particles
    ofFill();
    for (particle &p : particles)
        p.draw();
    
    mouseLight.disable();
    ofDisableLighting();
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
