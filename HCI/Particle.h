//
//  Particle.h
//  HCI
//
//  Created by masakazu nakazawa on 2015/07/07.
//  Copyright (c) 2015年 masakazu. All rights reserved.
//

#ifndef __HCI__Particle__
#define __HCI__Particle__

#include <stdio.h>
#include <iostream>
#include <Box2D/Box2D.h>
#include <opencv2/core/core.hpp>

extern int pixel;

class Particle
{
public:
    Particle(){};
    Particle(b2World& world, int initX, int initY, int radius, int initV);
    ~Particle();
    void setVelocity(int velocityX, int velocityY);
    b2Vec2 getPosition();
    int getRadius();
    b2Vec2 getVelocity();
    void draw(cv::Mat& img);
    static void velocityCorrection(std::vector<Particle*>& parts, int partVelocity);
private:
    cv::Scalar color;
    b2Body* body;
    b2Fixture* fixture;
};

#endif /* defined(__HCI__Particle__) */
