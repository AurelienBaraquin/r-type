#pragma once

extern "C"
{
#include <incbin.h>
}

#ifdef __cplusplus
extern "C"
{
#endif

#define IMPORT_ASSETS(name, path) INCBIN(name, path)
#define IMPORT_TEXT(name, path) INCTXT(name, path)

#ifdef __cplusplus
}
#endif
