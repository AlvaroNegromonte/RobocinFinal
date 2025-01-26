#ifndef DATA_PROCESSOR_H
#define DATA_PROCESSOR_H

#include <vector>
#include <cmath>
#include "Constants.h"

class DataProcessor {
public:
    static double applyEMA(const std::vector<double>& data, double alpha);
    static double calculateAccumulatedAngle(const std::vector<double>& filteredData, double tsample);
};

#endif
