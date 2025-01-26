#include "DataProcessor.h"

double DataProcessor::applyEMA(const std::vector<double>& data, double alpha) {
    if (data.empty()) return 0.0;
    if (data.size() == 1) return data[0] * DEG_TO_RAD;

    double y_prev = data[data.size() - 2] * DEG_TO_RAD; // Penúltimo valor processado
    double x_curr = data.back() * DEG_TO_RAD;          // Último dado bruto
    return y_prev * (1 - alpha) + x_curr * alpha;
}

double DataProcessor::calculateAccumulatedAngle(const std::vector<double>& filteredData, double tsample) {
    if (filteredData.empty()) return 0.0;

    double angle = 0.0;
    size_t lastIndex = filteredData.size() - 1;
    if (lastIndex > 0) {
        angle = filteredData[lastIndex - 1] * tsample; // Ângulo acumulado anterior
    }

    angle += filteredData[lastIndex] * tsample; // Integração

    // Ajusta para o intervalo [-pi, pi]
    if (angle > M_PI) angle -= 2 * M_PI;
    if (angle < -M_PI) angle += 2 * M_PI;

    return angle;
}
