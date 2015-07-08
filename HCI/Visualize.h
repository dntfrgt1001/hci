//
//  Visualize.h
//  HCI
//
//  Created by masakazu nakazawa on 2015/07/08.
//  Copyright (c) 2015年 masakazu. All rights reserved.
//

#ifndef __HCI__Visualize__
#define __HCI__Visualize__

#include <stdio.h>
#include <opencv2/core/core.hpp>
#include "Particle.h"
#include "Enclosure.h"

class Visualize
{
public:
    Visualize(){};
    Visualize(b2World& world, int pid, int number,
              int x, int y, int radius);
    ~Visualize();
    void draw(cv::Mat& img);
    
private:
    int pid;
    int number;
    int x;
    int y;
    int radius;
    Enclosure* enc;
    std::vector<Particle*> parts;
};

#endif /* defined(__HCI__Visualize__) */
