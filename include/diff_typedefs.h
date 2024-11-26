#ifndef DIFF_TYPEDEFS_H_
#define DIFF_TYPEDEFS_H_

#include <cstddef>
#include <cstdlib>
#include <assert.h>
#include <cstdio>
#include <cstring>

/// @brief differentiator errors codes

enum DIFF_ERROR
{
    DIFF_NONE       = 0, /// <no error
    DIFF_TREE_ERROR = 1, /// <differentiator tree error
};

#endif
