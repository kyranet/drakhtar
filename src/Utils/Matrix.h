// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#pragma once

/**
 * \brief A Matrix class that simulates a dynamic 2D array.
 * \tparam T The value type this Matrix will hold.
 */
template <typename T>
class Matrix {
  /**
   * \brief The amount of columns this matrix has.
   */
  int columns_;
  /**
   * \brief The amount of rows this matrix has.
   */
  int rows_;
  /**
   * \brief The internal dynamic 2D array.
   */
  T** matrix_;

 public:
  /**
   * \brief Create a new matrix with n columns and m rows.
   * \param columns The amount of columns for this matrix.
   * \param rows The amount of rows for this matrix.
   */
  Matrix<T>(const int columns, const int rows)
      : columns_(columns), rows_(rows) {
    matrix_ = new T*[columns];
    for (auto x = 0; x < columns; x++) {
      matrix_[x] = new T[rows];
    }
  }

  /**
   * \brief Free all the internal memory for this instance.
   */
  ~Matrix<T>() {
    for (auto x = 0; x < columns_; x++) {
      delete matrix_[x];
    }
    delete[] matrix_;
  }

  /**
   * \brief Get the amount of columns for this matrix.
   * \return The amount of columns this matrix has.
   */
  int cols() const { return columns_; }
  /**
   * \brief Get the amount of rows for this matrix.
   * \return The amount of rows this matrix has.
   */
  int rows() const { return rows_; }
  /**
   * \brief Get an element from this matrix given a position (x, y).
   * \param x The position in x for this matrix.
   * \param y The position in y for this matrix.
   * \return The value in the position (x, y) of this matrix.
   */
  T getElement(int x, int y) { return matrix_[x][y]; }
  /**
   * \brief Set an element to this matrix given a position (x, y).
   * \param x The position in x for this matrix.
   * \param y The position in y for this matrix.
   * \param element The element to insert to the position (x, y) of this matrix
   */
  void setElement(int x, int y, T element) { matrix_[x][y] = element; }
};
