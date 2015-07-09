//
//  DisplayText.cpp
//  HCI
//
//  Created by masakazu nakazawa on 2015/07/09.
//  Copyright (c) 2015年 masakazu. All rights reserved.
//

#include "DisplayText.h"

DisplayText::DisplayText(int x, int y, std::string str)
: x(x), y(y), str(str)
{
    //
}

void DisplayText::draw(cv::Mat& img)
{
    cv::putText(img, str, cv::Point(x, y), cv::FONT_HERSHEY_SIMPLEX,
                2.0, cv::Scalar(128, 128, 128), 3, CV_AA);
}