//
//  InfoExtract.h
//  HCI
//
//  Created by masakazu nakazawa on 2015/07/07.
//  Copyright (c) 2015年 masakazu. All rights reserved.
//

#ifndef __HCI__InfoExtract__
#define __HCI__InfoExtract__

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

class InfoExtract
{
public:
    InfoExtract(){};
    InfoExtract(std::string filePath);
    ~InfoExtract();
    void getLine(std::string& line);
    void split(std::string& line, std::vector<std::string>& splitted,
               char sep);
    void extPidThr(std::vector<std::string>& procDetail);
    void excSlash(std::string& threadLine);
private:
    std::string filePath;
    std::ifstream* ifs;
};


#endif /* defined(__HCI__InfoExtract__) */
