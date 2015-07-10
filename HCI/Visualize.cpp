//
//  Visualize.cpp
//  HCI
//
//  Created by masakazu nakazawa on 2015/07/08.
//  Copyright (c) 2015年 masakazu. All rights reserved.
//

#include "Visualize.h"

Visualize::Visualize(b2World& world, int pid, int number,
                     int x, int y, int partRadius, int partV,
                     cv::Scalar color)
: pid(pid), number(number), x(x), y(y), partV(partV), color(color)
{
    radius = partRadius * sqrt(number / 0.25f);
    
    enc = new Enclosure(world, x, y, radius);
    
    for(int i=0; i<number; i++){
        parts.push_back(new Particle(world, partRadius, x+i-number/2,
                                     y+i-number/2, partV, &(this->color)));
    }
    
    dt = new DisplayText(x, y, std::to_string(pid));
}

Visualize::~Visualize()
{
    delete enc;
    std::vector<Particle*>::iterator iter;
    for(iter=parts.begin(); iter!=parts.end(); iter++){
        delete *iter;
    }
    delete dt;
}

void Visualize::velocityCorrection()
{
    Particle::velocityCorrection(parts, partV);
}

void Visualize::draw(cv::Mat& img)
{
   //enc->draw(img);
    
    std::vector<Particle*>::iterator iter;
    for(iter=parts.begin(); iter!=parts.end(); iter++){
        (*iter)->draw(img);
    }
    
    dt->draw(img);
}