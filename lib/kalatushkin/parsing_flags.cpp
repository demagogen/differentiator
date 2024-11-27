#include <stdio.h>
#include <string.h>
#include <math.h>
#include <assert.h>

#include "parsing_flags.h"
#include "flags.h"
#include "color_scheme.h"
#include "utils.h"

static const size_t flags_array_max_size = 5;
static int          flags_array_counter  = 0;

static FLAG flags_array[flags_array_max_size] = {};

bool register_flag(const char *flag_short, const char *flag_long, FlagCallback callback, const char *description) {
    assert(flag_short);
    assert(flag_long);
    assert(callback);

    if (flags_array_counter >= flags_array_max_size) {
        return false;
    }
    // TODO blank line
    flags_array[flags_array_counter].flag_short  = flag_short;
    flags_array[flags_array_counter].flag_long   = flag_long;
    flags_array[flags_array_counter].callback    = callback;
    flags_array[flags_array_counter].description = description;

    flags_array_counter++;

    return true;
}

int parse_flags(int argc, const char *argv[]) {
    assert(argv);

    for (int enter_flags_counter = 1; enter_flags_counter < argc; enter_flags_counter++) {
        for (int check_flag_counter = 0; check_flag_counter < flags_array_counter; check_flag_counter++) {
            if (strcmp(flags_array[check_flag_counter].flag_short, argv[enter_flags_counter]) == 0 ||
                strcmp(flags_array[check_flag_counter].flag_long,  argv[enter_flags_counter]) == 0) {

                flags_array[check_flag_counter].callback(argc, argv);
                return 0;
            }
        }
    }
    graphic_printf(RED, BOLD, "ААА, неверный флаг!!! АШЫПКА!!!\n");

    return -1;
}

int print_help(int argc, const char* argv[]) {
    int print_help_counter = -1;

    while (++print_help_counter < flags_array_counter) {
        graphic_printf(BLACK, BOLD,"             %s %s %s\n", flags_array[print_help_counter].flag_short,
                                                              flags_array[print_help_counter].flag_long,
                                                              flags_array[print_help_counter].description);
    }

    return 0;
}
