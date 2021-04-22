// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#pragma once

#ifdef _DEBUG
#ifndef _CRTDBG_MAP_ALLOC
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#include <cstdlib>
#ifndef DBG_NEW
#define DBG_NEW new (_NORMAL_BLOCK, __FILE__, __LINE__)
#define new DBG_NEW
#endif  // DBG_NEW
#endif  // _CRTDBG_MAP_ALLOC
#endif  // _DEBUG
