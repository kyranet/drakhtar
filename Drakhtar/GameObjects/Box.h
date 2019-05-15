// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#pragma once
#include "GameObject.h"

class Unit;

/**
 * \brief Assigns a name to each index of the box texture array.
 */
enum class TextureInd {
  BASE = 0,
  HOVER = 1,
  MOVABLE = 2,
  ENEMY = 3,
  ACTIVE = 4,
  HOVER_MOVABLE = 5,
  HOVER_ENEMY = 6
};

class Box final : public GameObject {
 protected:
  /**
   * \brief The row and column this box occupies in the board matrix.
   */
  Vector2D<byte> boardIndex_;

  /**
   * \brief The index of current texture in the box texture array.
   */
  TextureInd cellTexture_;

  /**
   * \brief Whether or not the mouse is over the box.
   */
  bool hovered_ = false;

  /**
   * \brief Array of all textures de box may render.
   */
  Texture* cellTextures_[7]{};

  /**
   * \brief Vector2D of the width and height of the box.
   */
  const Vector2D<int> size_;

 public:
  Box(Scene* scene, const Vector2D<int>& pos, const Vector2D<int>& size,
      const Vector2D<byte>& boardIndex);

  /**
   * \return The SDL_Rect of the box, being its position, width and height.
   */
  SDL_Rect getRect() const override;

  /**
   * \brief Renders the appropriated texture for the box and its content.
   */
  void render() const override;

  /**
   * \brief Is called every frame to check if the mouse is over the box.
   */
  void update() override;

  /**
   * \brief Checks if there is any unit placed in this box.
   * \return Whether or not the box contains a unit.
   */
  bool isEmpty() const;

  /**
   * \return A vector2D of the row and column this box occupies in the board.
   */
  Vector2D<byte> getIndex() const;

  /**
   * \return An enum of the current texture being rendered by this box.
   */
  TextureInd getCurrentTexture() const;

  /**
   * \return A pointer to the unit placed on this box.
   */
  Unit* getContent() const;

  /**
   * \brief Changes the texture the box renders.
   * \param cellTexture: An enum of the index of the new texture in the box
   * textures array.
   */
  void setCurrentTexture(TextureInd cellTexture);

  /**
   * \brief Queues its contents to destroy.
   */
  void destroyContent();
};
