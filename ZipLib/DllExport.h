#pragma once

#pragma warning( disable : 4251 )

#ifdef ZIPLIB_EXPORTS
#define ZIPLIB_IMPEXP  __declspec(dllexport)
#else
#define ZIPLIB_IMPEXP  __declspec(dllimport)
#endif