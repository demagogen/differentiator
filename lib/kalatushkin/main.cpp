#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>

#include "parsing_flags.h"
#include "flags.h"
#include "text_data.h"
#include "utils.h"
#include "sort_text.h"
#include "color_scheme.h"

int main(int argc, const char *argv[]) {
    register_flag("-h", "--help",            help_flag,          "help, I need somebody");
    register_flag("-V", "--version",         version_flag,       "version, or just anybody");
    register_flag("-a", "--sort_alphabet",   sort_text_alphabet, "alphabetly sorty texty");
    register_flag("-r", "--sort_rhyme",      sort_text_rhyme,    "rhyme sort, brother");
    register_flag("-d", "--special_for_ded", special_for_ded,    "dont ask me");

    if (argc > 1) {
        parse_flags(argc, argv);
    }
    else {
        help_flag(argc, argv);
    }

    return 0;
}
