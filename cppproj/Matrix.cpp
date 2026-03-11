//
// Created by shell on 11/06/2025.
//
#include <utility>
#include <iostream>
#include <cmath>


#include "Matrix.h"
Matrix:: Matrix(int rows, int cols): _rows(rows), _cols(cols) {
    if (rows <= 0 || cols <= 0)
    {
        throw std::invalid_argument("Matrix dimensions must be positive.");
    }
    float* m = new float[rows*cols];
    for (int i =0; i<rows*cols; i++) {
        m[i]=0;
    }

    _matrix= m;
};

Matrix:: Matrix(){
    _rows= 1;
    _cols=1;
    _matrix= new float[1];
    _matrix[0] = 0.0f;
}

Matrix:: Matrix(const Matrix& m){
    _rows= m._rows;
    _cols= m._cols;
    _matrix = new float[_rows * _cols];
    for (int i=0; i<_rows*_cols; i++) {
        _matrix[i] = m._matrix[i];
    }
}

Matrix::~Matrix() {
    delete[](_matrix);
}

int Matrix:: get_rows() const {
    return _rows;
}

int Matrix:: get_cols() const {
    return _cols;
}

Matrix & Matrix:: transpose() {
    Matrix trans_mat(_cols, _rows);
    for (int i=0; i<_rows; i++) {
        for (int j =0; j<_cols; j++) {
           trans_mat._matrix[j*_rows+i]= _matrix[i*_cols+j];
        }
    }
    std::swap(_rows, trans_mat._rows);
    std::swap(_cols, trans_mat._cols);
    std::swap(_matrix, trans_mat._matrix);
    //*this= trans_mat;
    return *this;
}

Matrix& Matrix:: vectorize() {
    _rows= _rows*_cols;
    _cols=1;
    return *this;
}

void Matrix:: plain_print() const {
    for (int i = 0; i < _rows; ++i) {
        for (int j = 0; j < _cols; ++j) {
            std::cout << _matrix[i * _cols + j] << " ";
        }
        std::cout << "\n";
    }

}

Matrix Matrix:: dot(Matrix m) {
    if ((_rows!= m._rows)||(_cols!=m._cols)){
        throw std::invalid_argument("Invalid matrix dimension");
    }
    Matrix new_mat(_rows, _cols);
    for (int i=0; i<_cols*_rows; i++) {
        new_mat._matrix[i] = _matrix[i]*m._matrix[i];
    }
    return new_mat;
}

float Matrix:: norm() const {
    float sum = 0.0f;
    for (int i = 0; i < _rows * _cols; ++i) {
        sum += _matrix[i] * _matrix[i];
    }
    return std::sqrt(sum);
}


Matrix Matrix::rref() const {
    Matrix result(*this);

    int lead = 0;
    for (int r = 0; r < result._rows; ++r) {
        if (lead >= result._cols)
            break;

        int i = r;
        while (result._matrix[i * _cols + lead] == 0) {
            ++i;
            if (i == result._rows) {
                i = r;
                ++lead;
                if (lead == result._cols)
                    return result;
            }
        }


        for (int k = 0; k < result._cols; ++k)
            std::swap(result._matrix[r * _cols + k], result._matrix[i * _cols + k]);


        float pivot = result._matrix[r * _cols + lead];
        if (pivot != 0) {
            for (int k = 0; k < result._cols; ++k)
                result._matrix[r * _cols + k] /= pivot;
        }


        for (int j = 0; j < result._rows; ++j) {
            if (j != r) {
                float factor = result._matrix[j * _cols + lead];
                for (int k = 0; k < result._cols; ++k) {
                    result._matrix[j * _cols + k] -= factor * result._matrix[r * _cols + k];
                }
            }
        }

        ++lead;
    }

    return result;
}

int Matrix:: argmax() const {
    int max_index = 0;
    float max_val = _matrix[0];
    for (int i =1; i<_rows*_cols; i++) {
        if (max_val< _matrix[i]) {
            max_index = i;
            max_val= _matrix[i];
        }//if
    }//for
    return max_index;
}

float Matrix:: sum() const {
    float sum = 0;
    for (int i=0; i<_cols*_rows; i++) {
        sum+= _matrix[i];
    }
    return sum;
}


Matrix& Matrix:: operator+=(const Matrix& other) {
    if ((_rows!= other._rows)||(_cols!=other._cols)){
        throw std::invalid_argument("Invalid matrix dimension");
    }
    for (int i=0; i<_cols*_rows; i++) {
        _matrix[i]+= other._matrix[i];
    }
    return *this;
}

Matrix Matrix:: operator+(const Matrix& other) const {
    if ((_rows!= other._rows)||(_cols!=other._cols)){
        throw std::invalid_argument("Invalid matrix dimension");
    }
    Matrix sum(_rows, _cols);
    for (int i=0; i<_cols*_rows; i++) {
        sum._matrix[i]= _matrix[i]+ other._matrix[i];
    }
   return sum;
}

Matrix& Matrix:: operator=(const Matrix& other) {
     delete[] _matrix;
    _rows= other._rows;
    _cols= other._cols;
    _matrix = new float[_rows * _cols];
    for (int i=0; i<_rows*_cols; i++) {
        _matrix[i] = other._matrix[i];
    }
    return *this;

}

Matrix Matrix::operator*(const Matrix& other) const {
    if (_cols != other._rows) {
        throw std::invalid_argument("Matrix dimensions do not allow multiplication");
    }

    Matrix result(_rows, other._cols);

    for (int i = 0; i < _rows; ++i) {
        for (int j = 0; j < other._cols; ++j) {
            float sum = 0;
            for (int k = 0; k < _cols; ++k) {
                sum += (*this)(i, k) * other(k, j);
            }
            result(i, j) = sum;
        }
    }

    return result;
}



Matrix Matrix:: operator*(float c) const {
    Matrix mult_by_c(_rows, _cols);

    for (int i=0; i<_cols*_rows; i++) {
        mult_by_c._matrix[i]= _matrix[i]*c;
    }
    return mult_by_c;
}

Matrix operator*(float c, const Matrix& m) {
    return m * c;
}

Matrix  operator*(double c, const Matrix& m) {
    return m * static_cast<float>(c);
}

Matrix operator*(int c, const Matrix& m) {
    return m * static_cast<float>(c);
}

float& Matrix:: operator()(int i, int j)  {
    if (i<0||j<0||i>=_rows||j>=_cols) {
        throw std::invalid_argument("Invalid matrix dimension");
    }
    return _matrix[i*_cols+j];
}

float Matrix::operator()(int i, int j) const {
    if (i < 0 || j < 0 || i >= _rows || j >= _cols) {
        throw std::invalid_argument("Invalid matrix dimension");
    }
    return _matrix[i * _cols + j];
}


float& Matrix:: operator[](int k)  {
    if (k<0||k>=_rows*_cols) {
        throw std::invalid_argument("Invalid matrix dimension");
    }
    return _matrix[k];
}

float Matrix:: operator[](int k) const {
    if (k<0||k>=_rows*_cols) {
        throw std::invalid_argument("Invalid matrix dimension");
    }
    return _matrix[k];
}

std::ostream& operator<<(std::ostream& os, const Matrix& m) {
    for (int i = 0; i < m._rows; ++i) {
        for (int j = 0; j < m._cols; ++j) {
            if (m._matrix[i * m._cols + j] > 0.1f) {
                os << "**";
            } else {
                os << "  ";
            }
        }
        os << "\n";
    }
    return os;
}


std::istream& operator>>(std::istream& in, Matrix& m) {
    in.read(reinterpret_cast<char*>(m._matrix), sizeof(float) * m._rows * m._cols);
    if (!in) {
        throw std::runtime_error("Input stream too short for matrix size");
    }
    return in;
}

