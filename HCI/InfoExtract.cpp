//
//  InfoExtract.cpp
//  HCI
//
//  Created by masakazu nakazawa on 2015/07/07.
//  Copyright (c) 2015年 masakazu. All rights reserved.
//

#include "InfoExtract.h"

InfoExtract::InfoExtract(std::string filePath)
: filePath(filePath)
{
    ifs = new std::ifstream(filePath);
 
    if(ifs == NULL)
        std::cout << "file not found" << std::endl;
    
    int rest = 12;
    std::string str;
    for(int i=0; i<rest; i++){
        getLine(str);
    }
}

InfoExtract::~InfoExtract()
{
    delete ifs;
}

void InfoExtract::getLine(std::string& line)
{
    std::getline(*ifs, line);
}

void InfoExtract::split(std::string& line,
                        std::vector<std::string>& splitted, char sep)
{
    std::istringstream iss(line);
    std::string tmp;
    
    splitted.clear();
    
    while(std::getline(iss, tmp, sep)){
        if(tmp != "")
            splitted.push_back(tmp);
    }
}

void InfoExtract::extPidThr(std::vector<std::string>& procDetail)
{
    procDetail.erase(procDetail.begin()+1, procDetail.end()-1);
}