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
    matrix_ = new T *[rows];
    for (int i = 0; i < rows; i++) {
      matrix_[i] = new T[cols];
    }
  };

  ~Matrix<T>() {
    for (int r = 0; r < rows_; r++) {
      delete matrix_[r];
    }
    delete[] matrix_;
  };

  int cols() const { return cols_; }
  int rows() const { return rows_; }
  T getElement(int x, int y) { return matrix_[x][y]; }
  void setElement(int x, int y, T element) { matrix_[x][y] = element; }
};
