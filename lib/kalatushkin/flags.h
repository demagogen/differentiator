#ifndef FLAGS_H_
#define FLAGS_H_

#include "parsing_flags.h"

int version_flag       (int argc, const char* argv[]);
int help_flag          (int argc, const char* argv[]);
int sort_text_alphabet (int argc, const char* argv[]);
int sort_text_rhyme    (int argc, const char* argv[]);
int special_for_ded    (int argc, const char* argv[]);
int print_help         (int argc, const char* argv[]);

#endif
