// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#pragma once
#include <cassert>
#include <iostream>
#include "SDL_stdinc.h"

/**
 * \brief The Vector2D class that manages all vectors in the game.
 * \tparam T The value type this instance will hold and use.
 */
template <typename T>
class Vector2D final {
  /**
   * \brief The x coordinate.
   */
  T x_;
  /**
   * \brief The y coordinate.
   */
  T y_;

 public:
  /**
   * \brief Create a new instance of Vector2D with the type's default values.
   */
  Vector2D<T>();
  /**
   * \brief Clone a Vector2D instance.
   * \param v The Vector2D instance to clone.
   */
  Vector2D<T>(const Vector2D<T> &v);
  /**
   * \brief Create a Vector2D instance with an x and y coordinates.
   * \param x The value for the x coordinate.
   * \param y The value for the y coordinate.
   */
  Vector2D<T>(T x, T y);
  /**
   * \brief The Vector2D destructor.
   */
  ~Vector2D();
  /**
   * \brief Get the x coordinate value for this instance.
   * \return The value for the x coordinate.
   */
  T getX() const;
  /**
   * \brief Get the y coordinate value for this instance.
   * \return The value for the y coordinate.
   */
  T getY() const;
  /**
   * \brief Set the x coordinate value for this instance.
   * \param x The new value for the x coordinate.
   */
  void setX(T x);
  /**
   * \brief Set the y coordinate value for this instance.
   * \param y The new value for the y coordinate.
   */
  void setY(T y);
  /**
   * \brief Set the (x, y) coordinates.
   * \param x The new value for the x coordinate.
   * \param y The new value for the y coordinate.
   */
  void set(T x, T y);
  /**
   * \brief Set the (x, y) coordinates from another Vector2D instance.
   * \param v A vector with the (x, y) coordinates to set to this instance.
   */
  void set(const Vector2D<T> &v);
  /**
   * \brief Gets the magnitude of this vector.
   * \return The magnitude of this vector.
   */
  T magnitude() const;
  /**
   * \brief Creates a clone of this instance and rotates it by n degrees from (0, 0).
   * \param degrees Rotate a vector by n degrees from (0, 0).
   * \return The rotated Vector2D instance.
   */
  Vector2D<T> rotate(double degrees) const;
  /**
   * \brief Gets the angle between two vectors, or (0, 0) if omitted.
   * \param v The angle between this vector and another.
   * \return The angle of this vector.
   */
  T angle(const Vector2D<T> &v) const;
  /**
   * \brief Creates a clone of tis instance and normalizes it.
   * \return The normalized vector.
   */
  Vector2D<T> normalize() const;

  Vector2D<T> operator-(const Vector2D<T> &v) const;
  Vector2D<T> operator+(const Vector2D<T> &v) const;
  Vector2D<T> operator*(const Vector2D<T> &d) const;
  Vector2D<T> operator*(T d) const;
  Vector2D<T> operator/(T d) const;
  friend std::ostream &operator<<(std::ostream &os, const Vector2D<T> &v);
};

template <typename T>
Vector2D<T>::Vector2D() : x_(), y_() {}

template <typename T>
Vector2D<T>::Vector2D(const Vector2D<T> &v) : x_(v.getX()), y_(v.getY()) {}

template <typename T>
Vector2D<T>::Vector2D(T x, T y) : x_(x), y_(y) {}

template <typename T>
Vector2D<T>::~Vector2D() {
  if (std::is_destructible<T>()) {
    delete x_;
    delete y_;
  }
}

template <typename T>
T Vector2D<T>::getX() const {
  return x_;
}

template <typename T>
T Vector2D<T>::getY() const {
  return y_;
}

template <typename T>
void Vector2D<T>::setX(T x) {
  x_ = x;
}

template <typename T>
void Vector2D<T>::setY(T y) {
  y_ = y;
}

template <typename T>
void Vector2D<T>::set(const Vector2D<T> &v) {
  x_ = v.getX();
  y_ = v.getY();
}

template <typename T>
void Vector2D<T>::set(T x, T y) {
  x_ = x;
  y_ = y;
}

template <typename T>
T Vector2D<T>::magnitude() const {
  return sqrt(pow(x_, 2) + pow(y_, 2));
}

template <typename T>
Vector2D<T> Vector2D<T>::rotate(double degrees) const {
  Vector2D r;

  degrees = fmod(degrees, 360.0);
  if (degrees > 180.0) {
    degrees = degrees - 360.0;
  } else if (degrees <= -180.0) {
    degrees = 360.0 + degrees;
  }

  assert(degrees >= -180.0 && degrees <= 180.0);

  const auto angle = degrees * M_PI / 180.0;
  const auto sine = sin(angle);
  const auto cosine = cos(angle);

  // Rotation matrix
  double matrix[2][2] = {{cosine, -sine}, {sine, cosine}};

  const auto x = x_;
  const auto y = y_;

  r.x_ = matrix[0][0] * x + matrix[0][1] * y;
  r.y_ = matrix[1][0] * x + matrix[1][1] * y;

  return r;
}

template <typename T>
T Vector2D<T>::angle(const Vector2D<T> &v) const {
  const double a2 = atan2(v.getX(), v.getY());
  const double a1 = atan2(x_, y_);
  const double sign = a1 > a2 ? 1 : -1;
  const auto k = -sign * M_PI * 2;
  auto angle = a1 - a2;
  angle = (abs(k + angle) < abs(angle)) ? k + angle : angle;
  return angle * 180. / M_PI;
}

template <typename T>
Vector2D<T> Vector2D<T>::normalize() const {
  Vector2D r(x_, y_);
  double mag = magnitude();
  if (mag > 0.0) {
    r.x_ = r.x_ / mag;
    r.y_ = r.y_ / mag;
  }
  return r;
}

template <typename T>
Vector2D<T> Vector2D<T>::operator-(const Vector2D<T> &v) const {
  return Vector2D(x_ - v.getX(), y_ - v.getY());
}

template <typename T>
Vector2D<T> Vector2D<T>::operator+(const Vector2D<T> &v) const {
  return Vector2D(x_ + v.getX(), y_ + v.getY());
}

template <typename T>
Vector2D<T> Vector2D<T>::operator*(T d) const {
  return Vector2D(x_ * d, y_ * d);
}

template <typename T>
double Vector2D<T>::operator*(const Vector2D<T> &d) const {
  return x_ * d.getX() + y_ * d.getY();
}

template <typename T>
Vector2D<T> Vector2D<T>::operator/(T d) const {
  return Vector2D(x_ / d, y_ / d);
}

template <typename T>
std::ostream &operator<<(std::ostream &os, const Vector2D<T> &v) {
  os << "(" << v.getX() << ", " << v.getY() << ")";
  return os;
}
