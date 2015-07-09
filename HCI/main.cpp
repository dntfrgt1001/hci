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
#include "Visualize.h"

int pixel = 100;

int main(int argc, const char * argv[])
{
    srand((unsigned int) time(NULL));
    
    std::string filePath = "/Users/masakazu/Desktop/HCI/HCI/working/log.txt";
    
    InfoExtract ie(filePath);
    
    std::vector<std::vector<int>> info;
    
    char seperator = ' ';
    
    int infoNum = 10;
    
    for(int i=0; i<infoNum; i++){
        std::string procLine;
        std::vector<std::string> procExtStr;
        std::vector<int> procExtInt;
        
        ie.getLine(procLine);
        ie.split(procLine, procExtStr, seperator);
        ie.extPidTh(procExtStr);
        ie.excSlash(procExtStr[1]);
        ie.strToInt(procExtStr, procExtInt);
        
        info.push_back(procExtInt);
    }
    
    
    for(int i=0; i<infoNum; i++){
        for(int j=0; j<2; j++){
            std::cout << info[i][j] << "  ";
        }
        std::cout << std::endl;
    }
    
    
    float32 timeStep = 1.0f/60.0f;
    int32 velocityIterations = 8;
    int32 positionIterations = 3;
    
    b2Vec2 gravity(0.0f, 0.0f);
    b2World world(gravity);
    
    const int width = 1280;
    const int height = 720;
    
    cv::Mat img;
    cv::namedWindow("window", CV_WINDOW_AUTOSIZE|CV_WINDOW_FREERATIO);
    
    
    std::vector<Visualize*> vis;
    int number = 4;
    for(int i=0; i<number; i++){
        vis.push_back(new Visualize(world, info[i][0], info[i][1],
                                   width*i/number+width/number/2,
                                    height/2, 5, 150));
        //Visualize vi(world, info[0][0], info[0][1], width/2, height/2, 10, 150);
    }
    
    for(int i=0; i<10; i++)
        world.Step(timeStep, velocityIterations, positionIterations);
    for(int i=0; i<vis.size(); i++)
        vis[i]->velocityCorrection();
    
    int loopCount = 1;
    while(true){
        world.Step(timeStep, velocityIterations, positionIterations);
        
        img = cv::Mat(cv::Size(width, height), CV_8UC3,
                      cv::Scalar(255, 255, 255));
        
        for(int i=0; i<vis.size(); i++){
            vis[i]->draw(img);
        
            if(loopCount%100 == 0){
                vis[i]->velocityCorrection();
            }
        }
        if(loopCount >= 10000)
            loopCount = 0;
        
        loopCount++;
        
        cv::imshow("window", img);
        if(cv::waitKey(10)>0)
            break;
    }
    
    for(int i=0; i<vis.size(); i++)
        delete vis[i];
    
/*
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
*/
    
    return 0;
}
