#ifndef ENGINE_HPP
#define ENGINE_HPP

#include "Core.hpp"

#ifdef BUILD_GRAPHIC
#include "Graphic.hpp"
#endif

#ifdef BUILD_PHYSICS
#include "Physics.hpp"
#endif

#ifdef BUILD_AUDIO
#include "Audio.hpp"
#endif

#ifdef BUILD_INPUTS
#include "Inputs.hpp"
#endif

#endif  // ENGINE_HPP
