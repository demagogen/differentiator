#include <cstddef>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <ctype.h>

#include "sort_text.h"
#include "text_data.h"
#include "utils.h"
#include "color_scheme.h"

int compare_strings_starts(const void *line_struct1, const void *line_struct2) {
	assert(line_struct1 && "compare strings assert fucked up");
	assert(line_struct2);

    char* letter1_ptr = (*((LINE_DATA* )line_struct1)).lines_pointers;
    char* letter2_ptr = (*((LINE_DATA* )line_struct2)).lines_pointers;

    size_t line1_length = (*((LINE_DATA* )line_struct1)).lines_lengths;
    size_t line2_length = (*((LINE_DATA* )line_struct2)).lines_lengths;

    size_t letter1_index = 0;
    size_t letter2_index = 0;

    while (letter1_index < line1_length && letter2_index < line2_length) {
        while (!isalpha(letter1_ptr[letter1_index]) && !is_apostrophe(letter1_ptr[letter1_index])) {
            letter1_index++;
        }
        while (!isalpha(letter2_ptr[letter2_index]) && !is_apostrophe(letter2_ptr[letter2_index])) {
            letter2_index++;
        }
        if (letter1_ptr[letter1_index] != letter2_ptr[letter2_index]) {
            return (int) (letter1_ptr[letter1_index] - letter2_ptr[letter2_index]);
        }
        else {
            letter1_index++;
            letter2_index++;
            continue;
        }
    }
    return 0;
}

int compare_strings_ends(const void* line_struct1, const void* line_struct2) {
	assert(line_struct1);
	assert(line_struct2);

    char* letter1_ptr = (*((LINE_DATA* )line_struct1)).lines_pointers;
    char* letter2_ptr = (*((LINE_DATA* )line_struct2)).lines_pointers;

    size_t line1_length = (*((LINE_DATA* )line_struct1)).lines_lengths;
    size_t line2_length = (*((LINE_DATA* )line_struct2)).lines_lengths;

    size_t letter1_index = 0;
    size_t letter2_index = 0;

    while (letter1_index < line1_length && letter2_index < line2_length) {
        while (!isalpha(letter1_ptr[line1_length - letter1_index])) {
            letter1_index++;
        }
        while (!isalpha(letter2_ptr[line2_length - letter2_index])) {
            letter2_index++;
        }
        if (letter1_ptr[line1_length - letter1_index] != letter2_ptr[line2_length - letter2_index]) {
            return (int) (letter1_ptr[line1_length - letter1_index] - letter2_ptr[line2_length - letter2_index]);
        }
        else {
            letter1_index++;
            letter2_index++;
            continue;
        }
    }
    return 0;
}

int compare_pointers(const void* line_struct1, const void* line_struct2) {
    assert(line_struct1);
	assert(line_struct2);

    char* line1_ptr = (*((LINE_DATA* )line_struct1)).lines_pointers;
    char* line2_ptr = (*((LINE_DATA* )line_struct2)).lines_pointers;

    return (int) (line1_ptr - line2_ptr);
}

int is_letter(const char symbol) {
    return (symbol >= 'A' && symbol <= 'Z' || symbol >= 'a' && symbol <= 'z');
}

int is_apostrophe(const char symbol) {
    return (symbol == '\'');
}

int custom_qsort(void* array, size_t el_count, size_t el_size, compare_func_t compare_func) {
    assert(array);
    assert(compare_func);

    partition(array, el_count, el_size, compare_func);

    return 0;
}


int partition(void* array, size_t el_count, size_t el_size, compare_func_t compare_func) {
    assert(array        && "array assert in partition");
    assert(compare_func && "compare_func assert in partition");

    if (el_count == 1) {
        return 0;
    }

    size_t left_side  = 0;
    size_t right_side = el_count - 1;
    size_t separator = rand() % (el_count - 1) + 1;

    while (left_side < right_side) {
        while (compare_func((char* )array + left_side * el_size, (char* )array + separator * el_size) < 0 && left_side < el_count) {
            left_side++;
        }
        while (compare_func((char* )array + separator * el_size, (char* )array + right_side * el_size) < 0 && right_side > 0) {
            right_side--;
        }

        if (left_side <= right_side) {
            swap((char* )array + left_side * el_size, (char* )array + right_side * el_size, el_size);

            if (separator == left_side) {
                separator = right_side;
            }
            else if (separator == right_side) {
                separator = left_side;
            }
            left_side++;
            right_side--;
        }
    }

    if (right_side > 0) {
        custom_qsort(array, right_side + 1, el_size, compare_func);
    }
    if (left_side < el_count - 1) {
        custom_qsort((char* )array + left_side * el_size, el_count - left_side, el_size, compare_func);
    }

    return 0;
}
