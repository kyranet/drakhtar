// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#pragma once
#include <iostream>

template <typename T>
class Vector2D {
  T x_;  // first coordinate
  T y_;  // second coordinate

 public:
  Vector2D<T>() : x_(), y_() {}
  Vector2D<T>(const Vector2D<T> &v) : x_(v.getX()), y_(v.getY()) {}
  Vector2D<T>(T x, T y) : x_(x), y_(y) {}
  virtual ~Vector2D() {}
  T getX() const { return x_; }
  T getY() const { return y_; }
  void setX(T x) { x_ = x; }
  void setY(T y) { y_ = y; }
  void set(const Vector2D<T> &v) { x_ = v.getX(), y_ = v.getY() }
  void set(T x, T y) {
    x_ = x;
    y_ = y;
  }
  T magnitude() const;
  Vector2D<T> rotate(double degrees);
  T angle(const Vector2D<T> &v) const;
  Vector2D<T> normalize();

  Vector2D<T> operator-(const Vector2D<T> &v) const;
  Vector2D<T> operator+(const Vector2D<T> &v) const;
  Vector2D<T> operator*(T d) const;
  double operator*(const Vector2D<T> &d) const;
  Vector2D<T> operator/(T d) const;
  friend std::ostream &operator<<(std::ostream &os, const Vector2D<T> &v);
};
