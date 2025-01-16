#pragma once

#include "Log.hpp"
#if defined(_WIN32)
extern "C" {
#define CloseWindow RaylibCloseWindow
#define ShowCursor RaylibShowCursor
#endif
#include <raylib.h>
#if defined(_WIN32)
#undef CloseWindow
#undef ShowCursor
}
#endif
