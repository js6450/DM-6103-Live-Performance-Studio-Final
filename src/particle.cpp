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
//    vel.x = vel.y = 0; // intrerestring effect
    
    color.r = 255;
    color.g = 255;
    color.b = 255;
    
    age = 0;
}

//--------------------------------------------------------------
void particle::update(float*** fractal, int x, int y){
    // reset if particle dies
    if (age > particleLife)
        setup();
    
    // attract to x, y
    float force = 500/((x - pos.x)*(x - pos.x) + (y - pos.y)*(y - pos.y) - dancerRadius);
    if (force > 1) force = 1;
    if (force < 0) {
        vel.x = 0;
        vel.y = 0;
        force = -0.5;
//        force = 0 // interesting effect
//        color.r = 255; color.g = 247; color.b = 226; // interesting effect
    }
    float angle = atan( (y-pos.y)/(x-pos.x) );
    if (x < pos.x) angle += M_PI;
    vel.x += cos(angle)*force;
    vel.y += sin(angle)*force;
    
    // update position using vel times fractal
    if (pos.x > 0 && pos.x < ofGetWidth() && pos.y > 0 && pos.y < ofGetHeight()){
        int posx = pos.x/2;
        int posy = pos.y/2;
        int time = ofGetFrameNum()/8 % (evolutions*2);
        if (time >= evolutions) time = evolutions*2 - time;
        pos.x += vel.x * (fractal[posx][posy][time]*2+1);
        pos.y += vel.y * (fractal[posx][posy][evolutions-time]*2+1);
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
