//
//  Enclosure.h
//  HCI
//
//  Created by masakazu nakazawa on 2015/07/07.
//  Copyright (c) 2015年 masakazu. All rights reserved.
//

#ifndef __HCI__Enclosure__
#define __HCI__Enclosure__

#include <stdio.h>
#include <Box2D/Box2D.h>
#include <opencv2/core/core.hpp>

extern int pixel;

class Enclosure
{
public:
    Enclosure(){};
    Enclosure(b2World& world, int x, int y, int radius);
    ~Enclosure();
    int getRadius();
    b2Vec2 getPosition();
    void draw(cv::Mat& img);
private:
    int x;
    int y;
    int radius;
    b2Body* body;
    b2Fixture* fixture;
};


#endif /* defined(__HCI__Enclosure__) */
