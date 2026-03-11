//
// Created by shell on 15/06/2025.
//

#include "Activation.h"
#include "Matrix.h"
#include <cmath>

namespace activation {
    Matrix relu(const Matrix& m) {
        Matrix result(m.get_rows(), m.get_cols());
        for (int i=0; i<m.get_rows()*m.get_cols(); i++ ) {
            if (m[i]<0) {
                result[i] = 0;
            }
            else {
                result[i] = m[i];
            }//else

        }//for
        return result;
    }

    Matrix softmax(const Matrix& m) {
        int size = m.get_rows() * m.get_cols();
        if (size == 0) {
            throw std::invalid_argument("Cannot apply softmax on empty matrix.");
        }

        Matrix result(m.get_rows(), m.get_cols());
        float max_val = m[m.argmax()];  // to avoid overflow
        float sum = 0.0f;
        for (int i = 0; i < size; ++i) {
            result[i] = std::exp(m[i] - max_val);
            sum += result[i];
        }
        if (sum == 0) {
            throw std::runtime_error("Softmax sum is zero – numerical issue.");
        }
        for (int i = 0; i < size; ++i) {
            result[i] /= sum;
        }
        return result;
    }

}