// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#pragma once

template <typename T>
class Matrix {
 private:
  int cols_;
  int rows_;
  T **matrix_;

 public:
  Matrix<T>(int cols, int rows) : cols_(cols), rows_(rows) {
    matrix_ = new T *[cols];
    for (int x = 0; x < cols; x++) {
      matrix_[x] = new T[rows];
    }
  };

  ~Matrix<T>() {
    for (int x = 0; x < cols_; x++) {
      delete matrix_[x];
    }
    delete[] matrix_;
  };

  int cols() const { return cols_; }
  int rows() const { return rows_; }
  T getElement(int x, int y) { return matrix_[x][y]; }
  void setElement(int x, int y, T element) { matrix_[x][y] = element; }
};
