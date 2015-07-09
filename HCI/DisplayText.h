//
//  DisplayText.h
//  HCI
//
//  Created by masakazu nakazawa on 2015/07/09.
//  Copyright (c) 2015年 masakazu. All rights reserved.
//

#ifndef __HCI__DisplayText__
#define __HCI__DisplayText__

#include <stdio.h>
#include <string>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

class DisplayText
{
public:
    DisplayText(){};
    DisplayText(int x, int y, std::string);
    ~DisplayText(){};
    void draw(cv::Mat& img);
private:
    int x;
    int y;
    std::string str;
};

#endif /* defined(__HCI__DisplayText__) */
