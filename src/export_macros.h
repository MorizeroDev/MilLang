#ifndef MILIZE_EXPORT_MACROS_H
#define MILIZE_EXPORT_MACROS_H

// https://github.com/AOMediaCodec/libavif/blob/397f74c8e289386eb7d309b2f8041d8a190db29a/include/avif/avif.h#L15
// ---------------------------------------------------------------------------
// Export macros

// Here's what MILIZE_API will be defined as in shared build:
// |       |        Windows        |                  Unix                  |
// | Build | __declspec(dllexport) | __attribute__((visibility("default"))) |
// |  Use  | __declspec(dllimport) |                                        |
//
// For static build, MILIZE_API is always defined as nothing.

#if defined(_WIN32)
#define MILIZE_HELPER_EXPORT __declspec(dllexport)
#define MILIZE_HELPER_IMPORT __declspec(dllimport)
#elif defined(__GNUC__) && __GNUC__ >= 4
#define MILIZE_HELPER_EXPORT __attribute__((visibility("default")))
#define MILIZE_HELPER_IMPORT
#else
#define MILIZE_HELPER_EXPORT
#define MILIZE_HELPER_IMPORT
#endif

#endif //MILIZE_EXPORT_MACROS_H
