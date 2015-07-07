//
//  main.cpp
//  HCI
//
//  Created by masakazu nakazawa on 2015/07/07.
//  Copyright (c) 2015年 masakazu. All rights reserved.
//

#include <iostream>
#include "InfoExtract.h"

int main(int argc, const char * argv[])
{
    std::string filePath = "/Users/masakazu/Desktop/HCI/HCI/working/log.txt";
    
    InfoExtract ie(filePath);
    
    std::string procLine;
    std::vector<std::string> procDetail;
    
    char seperator = ' ';
    
    int infoNum = 10;
    
    for(int j=0; j<infoNum; j++){
        ie.getLine(procLine);
        ie.split(procLine, procDetail, seperator);

        ie.extPidThr(procDetail);
        for(int i=0; i<procDetail.size(); i++)
            std::cout << procDetail[i] << "  ";
        std::cout << std::endl;
    }
    
    
    
    return 0;
}
