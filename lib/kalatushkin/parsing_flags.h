#ifndef FLAGS_H_
#define FLAGS_H_

#include "flags.h"

typedef int (*FlagCallback)(int argc, const char* argv[]);

struct FLAG {
    const char *flag_short                        = NULL;
    const char *flag_long                         = NULL;
    int (*callback)(int argc, const char* argv[]) = 0;
    const char *description                       = NULL;
};

int version_flag       (int argc, const char* argv[]);
int help_flag          (int argc, const char* argv[]);
int sort_text_alphabet (int argc, const char* argv[]);
int sort_text_rhyme    (int argc, const char* argv[]);
int special_for_ded    (int argc, const char* argv[]);

bool register_flag     (const char *flag_short, const char *flag_long, FlagCallback callback, const char *description);
int  parse_flags       (int argc, const char* argv[]);

#endif
