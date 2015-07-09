//
//  Particle.cpp
//  HCI
//
//  Created by masakazu nakazawa on 2015/07/07.
//  Copyright (c) 2015年 masakazu. All rights reserved.
//

#include "Particle.h"


Particle::Particle(b2World& world, int initX, int initY, int radius,
                   int initV)
{
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set((float)initX / pixel, (float)initY / pixel);
    body = world.CreateBody(&bodyDef);
    b2CircleShape circleShape;
    circleShape.m_radius = (float)radius / pixel;
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &circleShape;
    fixtureDef.density =  1.0f;
    fixtureDef.friction = 0.0f;
    fixtureDef.restitution = 1.0f;
    fixture = body->CreateFixture(&fixtureDef);
    
    int axisV = initV / sqrt(2);
    std::cout << "axisV = " << axisV << std::endl;
    setVelocity(axisV, axisV);
    color = cv::Scalar(255, 0, 0);
}

Particle::~Particle()
{
    b2World* world = body->GetWorld();
    world->DestroyBody(body);
}

void Particle::setVelocity(int velocityX, int velocityY)
{
    b2Vec2 newV((float)velocityX / pixel, (float)velocityY / pixel);
    body->SetLinearVelocity(newV);
}

int Particle::getRadius()
{
    return (int)(fixture->GetShape()->m_radius * pixel);
}

b2Vec2 Particle::getPosition()
{
    b2Vec2 position = body->GetWorldCenter();
    position *= (float)pixel;
    return position;
}

b2Vec2 Particle::getVelocity()
{
    b2Vec2 velocity = body->GetLinearVelocity();
    velocity *= pixel;
    return velocity;
}

void Particle::draw(cv::Mat& img)
{
    b2Vec2 position = getPosition();
    cv::circle(img, cv::Point(position.x, position.y),
               getRadius(), color, -1, 8, 0);
    cv::circle(img, cv::Point(position.x, position.y),
               getRadius(), cv::Scalar(0, 0, 0), 3, 8, 0);
}

void Particle::velocityCorrection(std::vector<Particle*>& parts, int partVelocity)
{
    float energy = 0.0f;
    
    std::vector<Particle*>::iterator iter;
    for(iter=parts.begin(); iter!=parts.end(); iter++){
        Particle* tmpPart = *iter;
        
        energy += tmpPart->getVelocity().LengthSquared();
    }
    
    float curEnergy = energy / parts.size();
    float iniEnergy = partVelocity*partVelocity*2;
    float ratio = sqrt(iniEnergy / curEnergy);
    
    std::cout << "current = " << curEnergy;
    std::cout << ", initial = " << iniEnergy;
    std::cout << ", ratio = " << ratio << std::endl;
    
    for(iter=parts.begin(); iter!=parts.end(); iter++){
        Particle* tmpPart = *iter;
        
        tmpPart->setVelocity(tmpPart->getVelocity().x * ratio,
                             tmpPart->getVelocity().y * ratio);
    }
}