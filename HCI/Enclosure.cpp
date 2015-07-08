//
//  Enclosure.cpp
//  HCI
//
//  Created by masakazu nakazawa on 2015/07/07.
//  Copyright (c) 2015年 masakazu. All rights reserved.
//

#include "Enclosure.h"



Enclosure::Enclosure(b2World& world, int x, int y, int radius)
: x(x), y(y), radius(radius)
{
    const int vertNum = 10;
    b2Vec2 vertices[vertNum];
    
    for(int i=0; i<vertNum; i++){
        vertices[i].Set
            (radius*cos(2.0f*M_PI*(float)i/(float)vertNum) / pixel,
             radius*sin(2.0f*M_PI*(float)i/(float)vertNum) / pixel);
    }
                      
    b2ChainShape chainShape;
    chainShape.CreateLoop(vertices, vertNum);
    
    b2BodyDef bodyDef;
    bodyDef.type = b2_staticBody;
    bodyDef.position.Set((float)x / (float)pixel,
                         (float)y / (float)pixel);
    body = world.CreateBody(&bodyDef);
    
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &chainShape;
    fixtureDef.density = 1.0f;
    fixtureDef.friction = 0.0f;
    fixtureDef.restitution = 0.0f;
    fixture = body->CreateFixture(&fixtureDef);
}

Enclosure::~Enclosure()
{
    b2World* world = body->GetWorld();
    world->DestroyBody(body);
}

int Enclosure::getRadius()
{
    return radius;
}

b2Vec2 Enclosure::getPosition()
{
    b2Vec2 position = body->GetWorldCenter();
    position *= (float)pixel;
    return position;
}

void Enclosure::draw(cv::Mat& img)
{
    cv::circle(img, cv::Point(x, y), radius, cv::Scalar(0, 0, 0), 3, 8, 0);
}