#include <iostream>
#include "SensorReader.h"
#include "DataProcessor.h"
#include "Constants.h"

#define MPU_SDA PB_9  // Pino SDA
#define MPU_SCL PB_8  // Pino SCL

using namespace std;

int main() {
    SensorReader sensor(MPU_SDA, MPU_SCL);
    if (!sensor.initialize()) {
        cerr << "Erro: Falha na inicialização do MPU6050.\n";
        return -1;
    }
    cout << "MPU6050 inicializado com sucesso.\n";

    vector<double> rawAngularSpeeds; // Dados brutos em graus/s
    vector<double> filteredData;    // Dados filtrados
    vector<double> angles;          // Ângulos acumulados
    double alpha = 0.2;             // Parâmetro do filtro EMA

    cout << "Lendo dados do sensor...\n";
    while (true) {
        double local_w = sensor.readAngularSpeedZ();
        rawAngularSpeeds.push_back(local_w);

        // Processamento
        double filteredValue = DataProcessor::applyEMA(rawAngularSpeeds, alpha);
        filteredData.push_back(filteredValue);

        double angle = DataProcessor::calculateAccumulatedAngle(filteredData, TSAMPLE);
        angles.push_back(angle);

        // Exibição
        size_t lastIndex = rawAngularSpeeds.size() - 1;
        printf("Amostra %zu | Vel. Angular Bruta: %.4f graus/s | Filtrada: %.4f rad/s | Ângulo: %.4f rad\n",
               lastIndex, rawAngularSpeeds[lastIndex], filteredData[lastIndex], angles[lastIndex]);

        // Aguarda próximo ciclo (5 ms)
        ThisThread::sleep_for(5ms);
    }

    return 0;
}
