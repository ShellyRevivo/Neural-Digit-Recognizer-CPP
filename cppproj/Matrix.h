// Matrix.h
#ifndef MATRIX_H
#define MATRIX_H
#include "Activation.h"
#include <istream>
#include <ostream>


// You don't have to use the struct. Can help you with MlpNetwork.h
struct matrix_dims {
    int rows, cols;
};




// Insert Matrix class here...
class Matrix{
    friend std::istream& operator>>(std::istream& in, Matrix& m);
    friend std::ostream& operator<<(std::ostream& out, const Matrix& m);
    //friend Matrix activation::relu(const Matrix& m);

  private:
    int _rows;
    int _cols;
    float* _matrix;
  public:
    Matrix(int rows, int cols);

    Matrix();

    Matrix(const Matrix& m);

    ~Matrix();

    int get_rows() const;

    int get_cols() const;

    Matrix& transpose();

    Matrix& vectorize();

    void plain_print() const;

    Matrix dot(Matrix m);

    float norm() const;

    float sum() const;

    int argmax() const;

    Matrix rref() const;


    Matrix& operator=(const Matrix& other);
    Matrix& operator+=(const Matrix& other);
    Matrix operator+(const Matrix& other) const;
    Matrix operator*(const Matrix& other) const;
    Matrix operator*(float c) const;
    float& operator()(int i, int j);
    float operator()(int i, int j) const;
    float& operator[](int k);
    float operator[](int k) const;




};

#endif //MATRIX_H

Matrix operator*(int c, const Matrix& m);
Matrix operator*(float c, const Matrix& m);
Matrix operator*(double c, const Matrix& m);
