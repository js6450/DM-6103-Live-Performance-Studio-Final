//
//  particle.cpp
//  DM6013 Final
//
//  Created by Alexander Wing on 4/9/19.
//

#include "ofApp.h"

void particle::setup(){
    radius = ofRandom(0.5,2);
    
    pos.x = ofRandom(0,ofGetWidth());
    pos.y = ofRandom(0,ofGetHeight());
    vel.x = ofRandom(-2,2);
    vel.y = ofRandom(-2,2);
    
    color.r = 255;
    color.g = 255;
    color.b = 255;
    
    age = 0;
}

//--------------------------------------------------------------
void particle::update(float** turbX, float** turbY, int x, int y){
    // reset if particle dies
    if (age > particleLife)
        setup();
    
    // attract to x, y
    float force = 500/((x - pos.x)*(x - pos.x) + (y - pos.y)*(y - pos.y) - 2500);
    if (force > 1) force = 1;
    if (force < 0) {
        vel.x = 0;
        vel.y = 0;
        force = -0.5;
        color.r = 255;
        color.g = 247;
        color.b = 226;
    }
    float angle = atan( (y-pos.y)/(x-pos.x) );
    if (x < pos.x) angle += M_PI;
    vel.x += cos(angle)*force;
    vel.y += sin(angle)*force;
    
    // update position using vel times air resistance
    if (pos.x > 0 && pos.x < ofGetWidth() && pos.y > 0 && pos.y < ofGetHeight()){
        int posx = pos.x;
        int posy = pos.y;
        pos.x += vel.x * (turbX[posx][posy]*2+1);
        pos.y += vel.y * (turbY[posx][posy]*2+1);
    }
    age++;
    
    // air resistance
    vel -= vel * 0.01;
}

//--------------------------------------------------------------
void particle::draw(){
    float life = age/particleLife;
    if (life < 0.25){
        life = life*4*255;
    } else if (life > 0.75){
        life = (1-life)*4*255;
    } else{
        life = 255;
    }
    ofSetColor(color.r, color.g, color.b, life);
    ofDrawCircle(pos, radius);
}
