// Dense.h
#ifndef DENSE_H
#define DENSE_H

#include "Activation.h"
#include "Matrix.h"

// Insert Dense class here...

class Dense {
private:
    Matrix _bias;
    Matrix _weights;
    ActivationFunction _active_func;

public:
    Dense(Matrix weights, Matrix bias, ActivationFunction func): _bias(bias), _weights(weights),
                                                                    _active_func(func){}

    Matrix get_bias() const;
    Matrix get_weights() const;
    ActivationFunction get_activation() const;
    Matrix operator()(const Matrix& input) const;
};








#endif //DENSE_H