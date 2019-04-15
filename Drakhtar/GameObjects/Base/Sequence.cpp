// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#include "Sequence.h"

Sequence::Sequence(Scene *scene, Texture *texture) : GameObject(scene,
                                                                texture) {}

Sequence::Sequence(Scene *scene,
                   Texture *texture,
                   const Vector2D<int> &position,
                   const Vector2D<int> &size) : GameObject(scene,
                                                           texture,
                                                           position,
                                                           size) {}
