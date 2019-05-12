// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#pragma once
#include <cassert>
#include <cmath>
#include <iostream>
#include <type_traits>
#include "SDL_stdinc.h"

typedef unsigned char byte;

/**
 * \brief The Vector2D class that manages all vectors in the game.
 * \tparam T The value type this instance will hold and use.
 */
template <typename T,
          typename =
              typename std::enable_if<std::is_arithmetic<T>::value, T>::type>
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
   * \brief Create a Vector2D instance with an x and y coordinates.
   * \param x The value for the x coordinate.
   * \param y The value for the y coordinate.
   */
  Vector2D(T x, T y) : x_(x), y_(y) {}
  /**
   * \brief The Vector2D destructor.
   */
  ~Vector2D() = default;
  /**
   * \brief Get the x coordinate value for this instance.
   * \return The value for the x coordinate.
   */
  T getX() const { return x_; }
  /**
   * \brief Get the y coordinate value for this instance.
   * \return The value for the y coordinate.
   */
  T getY() const { return y_; }
  /**
   * \brief Set the x coordinate value for this instance.
   * \param x The new value for the x coordinate.
   */
  void setX(T x) { x_ = x; }
  /**
   * \brief Set the y coordinate value for this instance.
   * \param y The new value for the y coordinate.
   */
  void setY(T y) { y_ = y; }
  /**
   * \brief Set the (x, y) coordinates.
   * \param x The new value for the x coordinate.
   * \param y The new value for the y coordinate.
   */
  void set(T x, T y) {
    x_ = x;
    y_ = y;
  }
  /**
   * \brief Set the (x, y) coordinates from another Vector2D instance.
   * \param v A vector with the (x, y) coordinates to set to this instance.
   */
  void set(const Vector2D<T>& v) {
    x_ = v.getX();
    y_ = v.getY();
  }

  template <typename Q, typename = typename std::enable_if<
                            std::is_arithmetic<Q>::value, Q>::type>
  Vector2D<Q> to() const {
    return {static_cast<Q>(getX()), static_cast<Q>(getY())};
  }

  /**
   * \brief Gets the magnitude of this vector.
   * \return The magnitude of this vector.
   */
  T magnitude() const { return sqrt(pow(x_, 2) + pow(y_, 2)); }

  Vector2D<T> operator-(const Vector2D<T>& v) const {
    return Vector2D(x_ - v.getX(), y_ - v.getY());
  }

  Vector2D<T> operator+(const Vector2D<T>& v) const {
    return Vector2D(x_ + v.getX(), y_ + v.getY());
  }

  Vector2D<T> operator*(const Vector2D<T>& d) const {
    return Vector2D(x_ * d.getX(), y_ * d.getY());
  }

  Vector2D<T> operator*(T d) const { return Vector2D(x_ * d, y_ * d); }

  Vector2D<T> operator/(T d) const { return Vector2D(x_ / d, y_ / d); }

  friend std::ostream& operator<<(std::ostream& os, const Vector2D<T>& v) {
    os << "(" << v.getX() << ", " << v.getY() << ")";
    return os;
  }
};
