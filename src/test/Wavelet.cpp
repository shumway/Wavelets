#include "Wavelet.h"
#include <iostream>

Wavelet::Wavelet(int dataCount, const double *data)
    :   dataCount(dataCount), data(data),
        coefficients(new double[dataCount]) {
}

Wavelet::~Wavelet() {
    delete [] coefficients;
}


void Wavelet::decompose() {
    copyDataToCoeficientArray();
    for (int level = 0; level < getLevelCount(); ++level) {
        decomposeOneLevel(level);
    }
}

void Wavelet::copyDataToCoeficientArray() {
    for(int i = 0;i < dataCount;++i){
        coefficients[i] = data[i];
    }
}

void Wavelet::decomposeOneLevel(int level) {
    int halfStride = 1 << level;
    for (int i = halfStride; i < dataCount; i += 2 * halfStride){
        double difference = coefficients[i] - coefficients[i - halfStride];
        double mean = 0.5 * (coefficients[i] + coefficients[i - halfStride]);
        coefficients[i - halfStride] = mean;
        coefficients[i] = difference;
    }
}


double Wavelet::getCoefficient(int level, int index) const {
    int offset = (1 << level);
    int stride = (offset << 1);
    int scaledIndex = index / stride;
    return coefficients[offset + scaledIndex * stride];
}

int Wavelet::getDataCount() const {
    return dataCount;
}

int Wavelet::getLevelCount() const {
    int count = dataCount;
    int level = 0;
    while (count >>= 1) ++level;
    return level;
}

double Wavelet::getOffset() const {
    return coefficients[0];
}
