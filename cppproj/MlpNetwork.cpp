//
// Created by shell on 16/06/2025.
//

#include "MlpNetwork.h"
#include "Activation.h"
#include "Dense.h"

#include <iostream>

MlpNetwork::MlpNetwork(Matrix weights[4], Matrix biases[4])
    : _layers{
        Dense(weights[0], biases[0], activation::relu),
        Dense(weights[1], biases[1], activation::relu),
        Dense(weights[2], biases[2], activation::relu),
        Dense(weights[3], biases[3], activation::softmax)
    }
{}

digit MlpNetwork::operator()(const Matrix& input) const {
    Matrix output = input;


    for (int i = 0; i < MLP_SIZE; ++i) {

        output = _layers[i](output);
    }

    digit result;
    result.value = output.argmax();


    if (result.value >= static_cast<unsigned int>(output.get_rows() * output.get_cols()))
        {
        throw std::runtime_error("Invalid argmax result – matrix size mismatch.");
    }

    result.probability = output[result.value];

    return result;
}
