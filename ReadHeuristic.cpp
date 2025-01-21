#include "ReadHeuristic.h"

#include <fstream>
#include <sstream>

std::map<std::string, int> readHeuristic(const std::string &path) {
    std::ifstream file(path);

    if (!file.is_open()) {
        std::cerr << "Cannot open file" << std::endl;
        return {};
    }

    std::map<std::string, int> heuristicMap;

    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string nodeIdentifier;
        int heuristicValue;

        if (!(iss >> nodeIdentifier >> heuristicValue)) {
            std::cerr << "Cannot parse line `" << line << "'" << std::endl;
            return {};
        }

        if (!heuristicMap.insert({nodeIdentifier, heuristicValue}).second) {
            std::cerr << "Multiple heuristic values found for " << nodeIdentifier << std::endl;
            return {};
        }
    }

    file.close();

    return heuristicMap;
}
