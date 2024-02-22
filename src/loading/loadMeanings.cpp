#include "loading.h"
#include "config.h"
#include "stringUtil.h"
#include "hashMaps.h"
#include <fstream>
#include <vector>
#include <string>
#include <iostream>

namespace loading {

void loadMeanings() {
    std::ifstream readingsFile;
    readingsFile.open(READINGS_PATH);
    std::string line;
    if(!readingsFile) {
        readingsFile.open(std::string("../") + READINGS_PATH); // if executable is in build directory
    }
    if(readingsFile) {
        #ifdef VERBOSE
            std::cout << "Loading meanings from " << READINGS_PATH << std::endl;
            int numSuccess = 0;
        #endif
        while(std::getline(readingsFile, line)) {
            if(line.empty() || line[0] == '#') {
                continue;
            }
            std::vector<std::string> columns = util::split<char>(line, "\t");
            std::string character = columns[0];
            std::string datatype = columns[1];
            if(datatype == "kDefinition") {
                std::string meanings = columns[2];
                #ifdef VERBOSE
                    numSuccess +=
                #endif
                crafting::registerMeanings(util::unicodeToChar(character), meanings);
            }
        }
        #ifdef VERBOSE
            std::cout << "Successfully loaded meanings for " << numSuccess << " characters." << std::endl;
        #endif
    }
    else {
        throw std::runtime_error("Could not open readings file.");
    }
}

} // namespace loading