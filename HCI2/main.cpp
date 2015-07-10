//
//  main.cpp
//  HCI2
//
//  Created by masakazu nakazawa on 2015/07/10.
//  Copyright (c) 2015年 masakazu. All rights reserved.
//

#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>


int main(int argc, const char * argv[])
{
    cv::Mat img(cv::Size(640, 480), CV_8UC3);
    
    cv::Scalar color;
    int i = 4;
    switch(i){
        case 0:
            color = cv::Scalar(255, 0, 0);
            break;
        case 1:
            color = cv::Scalar(0, 255, 0);
            break;
        case 2:
            color = cv::Scalar(0, 0, 255);
            break;
        default:
            color = cv::Scalar(255, 255, 255);
            break;
    }
    
    cv::circle(img, cv::Point(320, 240), 100, color, 3, 8, 0);
    
    cv::namedWindow("window", CV_WINDOW_AUTOSIZE|CV_WINDOW_FREERATIO);
    cv::imshow("window", img);
    
    cv::waitKey(-1);
    
    return 0;
}
