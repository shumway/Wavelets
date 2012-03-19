#include <gtest/gtest.h>
#include "Wavelet.h"
#include <cmath>

namespace {

class WaveletTest : public ::testing::Test {
protected:
    virtual void SetUp() {
        data = new double[DATA_COUNT];
        double amplitude = 1.0;
        double offset = 42.0;
        initializeData(amplitude, offset);
        wavelet = new Wavelet(DATA_COUNT, data);
        wavelet->decompose();
    }

    virtual void TearDown() {
        delete wavelet;
        delete [] data;
    }

    void initializeData(double amplitude, double offset) {
        this->amplitude = amplitude;
        this->offset = offset;
        for (int i = 0; i < DATA_COUNT; ++i) {
            data[i] = amplitude*sin(i*PI/16.0) + offset;
        }
    }

    static const int DATA_COUNT;
    double *data;
    double amplitude;
    double offset;
    Wavelet *wavelet;
    static const double PI;
};

const int WaveletTest::DATA_COUNT = 128;
const double WaveletTest::PI = 3.141592653589793;

TEST_F(WaveletTest, testDataCount) {
    ASSERT_EQ(DATA_COUNT, wavelet->getDataCount());
}

TEST_F(WaveletTest, testLevelCount) {
    ASSERT_EQ(7, wavelet->getLevelCount());
}

TEST_F(WaveletTest, testOffset) {
    double offset = wavelet->getOffset();
    ASSERT_NEAR(this->offset, offset, 1e-14);
}

TEST_F(WaveletTest, testLowestCoefficientAtStart) {
    int level = 0;
    int index = 0;
    double coefficient = wavelet->getCoefficient(level, index);
    ASSERT_NEAR(0.19509032201612825, coefficient, 1e-14);
}

TEST_F(WaveletTest, testLowestCoefficientAtEnd) {
    int level = 0;
    int index = 127;
    double coefficient = wavelet->getCoefficient(level, index);
    ASSERT_NEAR(0.1875931103489609, coefficient, 1e-14);
}

TEST_F(WaveletTest, testArbitraryCoefficient) {
    int level = 3;
    int index = 42;
    double coefficient = wavelet->getCoefficient(level, index);
    ASSERT_NEAR(0.125, coefficient, 1e-14);
}

TEST_F(WaveletTest, testHighestCoefficient) {
    int level = wavelet->getLevelCount();
    int index = 42;
    double coefficient = wavelet->getCoefficient(level, index);
    ASSERT_NEAR(0.0, coefficient, 1e-14);
}

}
