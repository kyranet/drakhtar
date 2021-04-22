// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#pragma once
#include <array>
#include "SDL.h"
#include "Utils/Constants.h"
#include "Utils/Vector2D.h"

class Scene;
class GameObject;

/**
 * \brief The Input manager that handles keyboard and mouse input. It's the
 * interface between direct SDL2 calls.
 *
 * \note This class is a Singleton, and must have the clear() method called
 * before starting to handling events, and the update() method on every received
 * event.
 *
 * This class also collects all input events and saves them on internal
 * structures.
 */
class Input final {
  /**
   * \brief The current instance of this singleton.
   */
  static Input* instance_;
  Input();
  ~Input();

  /**
   * \brief Internal SDL keyboard state.
   */
  const Uint8* keyboard_{};

  /**
   * \brief Internal SDL mouse state.
   */
  Uint32 mouse_{};

  /**
   * \brief The current mouse position.
   */
  Vector2D<int> mousePosition_;

  /**
   * \brief The keys that are currently down.
   */
  std::array<bool, static_cast<size_t>(KeyboardKey::kKeyLimit)> keyDown_{};

  /**
   * \brief The keys that are currently up.
   */
  std::array<bool, static_cast<size_t>(KeyboardKey::kKeyLimit)> keyUp_{};

  /**
   * \brief The mouse buttons that are currently down.
   */
  std::array<bool, static_cast<size_t>(MouseKey::kKeyLimit)> mouseDown_{};

  /**
   * \brief The mouse buttons that are currently up.
   */
  std::array<bool, static_cast<size_t>(MouseKey::kKeyLimit)> mouseUp_{};

  /**
   * \brief The GameObject that was raycasted in the current mouse position.
   * This is used only to optimize repetitive calls to
   * Input::screenMouseToRay(), and is assigned to nullptr when the cursor
   * moves.
   */
  GameObject* casted_ = nullptr;

 public:
  static Input* instance();

  Input(const Input&) = delete;              // Copy Constructor
  Input(const Input&&) = delete;             // Move Constructor
  Input& operator=(const Input&) = delete;   // Assignment Operator
  Input& operator=(const Input&&) = delete;  // Move Operator

  /**
   * \brief Cleans up the states, must be called before the event loop.
   */
  void clear();

  /**
   * \brief Update this instance from the event loop.
   * \param event The event to handle.
   */
  void update(SDL_Event event);

  /**
   * \brief Gets the current mouse's position.
   * \return The current mouse's position.
   */
  static Vector2D<int> getMousePosition();

  /**
   * \brief Checks if a key if currently pressed.
   * \param key The keyboard key to check if it is currently pressed.
   * \return Whether or not the specified key is currently pressed.
   */
  static bool isKeyPressed(KeyboardKey key);

  /**
   * \brief Checks if a key was pressed in this tick cycle.
   * \param key The keyboard key to check if it got pressed in this tick cycle.
   * \return Whether or not the specified keyboard key was pressed in this tick
   * cycle.
   */
  static bool isKeyDown(KeyboardKey key);

  /**
   * \brief Checks if a key was released in this tick cycle.
   * \param key The keyboard key to check if it got released in this tick cycle.
   * \return Whether or not the specified keyboard key was released in this tick
   * cycle.
   */
  static bool isKeyUp(KeyboardKey key);

  /**
   * \brief Checks if a mouse button was pressed in this tick cycle.
   * \param button The mouse button to check if it got pressed in this tick
   * cycle.
   * \return Whether or not the specified mouse key was pressed in this
   * tick cycle.
   */
  static bool isMouseButtonDown(MouseKey button);

  /**
   * \brief Checks if a mouse button was released in this tick cycle.
   * \param button The mouse button to check if it got released in this tick
   * cycle.
   * \return Whether or not the specified mouse key was released in this
   * tick cycle.
   */
  static bool isMouseButtonUp(MouseKey button);

  /**
   * \brief Checks if the mouse is inside a rectangle.
   * \param rectangle The area to check against.
   * \return Whether or not the mouse is inside the specified rectangle.
   */
  static bool isMouseInside(const SDL_Rect* rectangle);

  /**
   * \brief Checks if either the right or left shift keys are being pressed.
   * \return Whether or not any shift key is being pressed.
   */
  static bool getShift();

  /**
   * \brief Checks if either the right or left control keys are being pressed.
   * \return Whether or not any control key is being pressed.
   */
  static bool getCtrl();

  /**
   * \brief Checks if either the right or left alt keys are being pressed.
   * \return Whether or not any alt key is being pressed.
   */
  static bool getAlt();

  static GameObject* screenMouseToRay();

  /**
   * \brief Destroys this Input instance, freeing memory.
   */
  static void destroy();
};
