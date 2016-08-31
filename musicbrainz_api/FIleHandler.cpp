//
// Created by Elenore on 2016. 8. 30..
//

#include "FIleHandler.h"
#include <fstream>
#include <sstream>


FIleHandler::FIleHandler() {

}
FIleHandler::~FIleHandler() {

}

void FIleHandler::readFileFromPath(std::string path) {

    std::ifstream inFile(path);
    std::string line;

    while(getline(inFile, line)) {
        std::istringstream ss(line);

        std::string name;
        int var1, var2, var3;

        ss >> name >> var1 >> var2 >> var3;
    }

    inFile.close();

}