//
//  main.cpp
//  HCI
//
//  Created by masakazu nakazawa on 2015/07/07.
//  Copyright (c) 2015年 masakazu. All rights reserved.
//

#include <iostream>
#include <time.h>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "InfoExtract.h"
#include "Particle.h"
#include "Enclosure.h"

int pixel = 100;

int main(int argc, const char * argv[])
{
    srand((unsigned int) time(NULL));
    
    std::string filePath = "/Users/masakazu/Desktop/HCI/HCI/working/log.txt";
    
    InfoExtract ie(filePath);
    
    std::vector<std::vector<std::string>> procInfo;
    
    char seperator = ' ';
    
    int infoNum = 10;
    
    for(int i=0; i<infoNum; i++){
        std::string procLine;
        std::vector<std::string> procDetail;
        
        ie.getLine(procLine);
        ie.split(procLine, procDetail, seperator);
        ie.extPidThr(procDetail);
        
        procInfo.push_back(procDetail);
    }
    
    
    for(int i=0; i<infoNum; i++){
        ie.excSlash(procInfo[i][1]);
        
        for(int j=0; j<2; j++){
            std::cout << procInfo[i][j] << "  ";
        }
        std::cout << std::endl;
    }
    
    float32 timeStep = 1.0f/60.0f;
    int32 velocityIterations = 10;
    int32 positionIterations = 3;
    
    b2Vec2 gravity(0.0f, 0.0f);
    b2World world(gravity);
    
    const int width = 640;
    const int height = 480;
    
    cv::Mat img;
    cv::namedWindow("window", CV_WINDOW_AUTOSIZE|CV_WINDOW_FREERATIO);
    
    int encX = width / 2;
    int encY = height / 2;
    int encRadius = 60;
    Enclosure enc(world, encX, encY, encRadius);
    
    const int partNum = 10;
    const int partRadius = 10;
    const int partVelocity = 200;
    std::vector<Particle*> parts;
    for(int i=0; i<partNum; i++){
        Particle* tmpPart =
            new Particle(world,
                         encX + encRadius*i/partNum - encRadius/2,
                         encY + encRadius*i/partNum - encRadius/2,
                         partRadius);
        tmpPart->setVelocity(partVelocity, partVelocity);
        parts.push_back(tmpPart);
    }
    
    
    int loopCount = 0;
    while(true){
        world.Step(timeStep, velocityIterations, positionIterations);
        
        cv::Mat img(cv::Size(width, height), CV_8UC3, cv::Scalar(255, 255, 255));
        
        std::vector<Particle*>::iterator iter;
        
        for(iter=parts.begin(); iter!=parts.end(); iter++){
            Particle* tmpPart = *iter;
            
            tmpPart->draw(img);
        }
        
        if(loopCount%100 == 0){
            Particle::velocityCollection(parts, partVelocity);
        }
        
//        std::cout << "energy = " << energy << std::endl;
        
//        if(loopCount % 1000 == 0)
            
/*
        b2Vec2 vec1 = parts[0]->getVelocity();
        b2Vec2 vec2 = vec1;
        vec2 *= pixel;
        
        std::cout << "vec1 length = " << vec1.Length() << "  ";
        std::cout << "vec2 length = " << vec2.Length() << "  ";
        std::cout << std::endl;
*/
 //        std::cout << "vec1 = (" << vec1.x << ", " << vec1.y << "),  ";
//        std::cout << "vec2 = (" << vec2.x << ", " << vec2.y << ")" << std::endl;

        
        enc.draw(img);
        
        cv::imshow("windows", img);
        
        loopCount++;
        if(loopCount >= 10000)
            loopCount = 0;
        
        if(cv::waitKey(10) > 0)
            break;
    }
    
    for(int i=0; i<partNum; i++){
        delete parts[i];
    }
    
    return 0;
}
