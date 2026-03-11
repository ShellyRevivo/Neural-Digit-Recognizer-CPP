//
// Created by shell on 16/06/2025.
//

#include "Matrix.h"
#include "Activation.h"
#include "Dense.h"

#include <iostream>



Matrix Dense:: get_bias() const{
    return _bias;
}

Matrix Dense:: get_weights() const{
    return _weights;
}

ActivationFunction Dense:: get_activation() const {
    return _active_func;
}

Matrix Dense:: operator()(const Matrix& input) const {
    return _active_func(_weights*input + _bias);
}