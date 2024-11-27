#ifndef SORT_TEXT_H_
#define SORT_TEXT_H_

#include <cstdio>

#include "text_data.h"

typedef int (*compare_func_t)(const void*, const void*);

int is_letter              (const char symbol);
int is_apostrophe          (const char symbol);
int custom_qsort           (void* array, size_t el_count, size_t el_size, compare_func_t compare_func);
int partition              (void* array, size_t el_count, size_t el_size, compare_func_t compare_func);
int compare_strings_starts (const void* line1, const void* line2);
int compare_strings_ends   (const void* line_struct1, const void* line_struct2);
int compare_pointers       (const void* line_struct1, const void* line_struct2);

#endif
