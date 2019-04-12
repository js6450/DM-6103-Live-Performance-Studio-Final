//
//  particle.h
//  DM6013 Final
//
//  Created by Alexander Wing on 4/9/19.
//

#pragma once

extern int particleLife;

class particle : public ofBaseApp{
    
public:
    void setup();
    void update(float** turbX, float** turbY, int x, int y);
    void draw();
    
    ofVec2f pos;
    ofVec2f vel;
    
    ofColor color;
    float radius;
    float age;
};
