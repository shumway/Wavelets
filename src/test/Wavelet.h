#ifndef WAVELET_H_
#define WAVELET_H_

/**
 * Class to perform a Haar wavelet transformation.
 * Pass in a const pointer to a data array and the size of the array.
 * See unit tests for expected behavior.
 */
class Wavelet {
public:
    Wavelet(int dataCount, const double *data);
    virtual ~Wavelet();

    int getDataCount() const;
    int getLevelCount() const;

    void decompose();
    double getOffset() const;
    double getCoefficient(int level, int index) const;

private:
    const int dataCount;
    const double *data;
    double *coefficients;
    void decomposeOneLevel(int level);
    void copyDataToCoeficientArray();

};

#endif
