#include <assert.h>
#include <stdlib.h>
#include <cstdio>

#include "flags.h"
#include "parsing_flags.h"
#include "color_scheme.h"
#include "text_data.h"
#include "sort_text.h"
#include "utils.h"

int version_flag(int argc, const char* argv[]) {
    graphic_printf(BLACK, BOLD, "Version 1.0.0 not muted edition\n");
    exit(0);
}

int help_flag(int argc, const char* argv[]){
    graphic_printf(BLACK, BOLD, "Using: ./kalatushkin [file] [options] [file]\n");
    print_help(argc, argv);
    exit(0);
}

int sort_text_alphabet(int argc, const char* argv[]) {
    ERROR_DATA error_inf = PROGRAM_ERROR;
    TEXT_DATA TextData = {};
    FILE* input_file_handle  = NULL;
    FILE* output_file_handle = stdout;

    if (argc == 3) {
        input_file_handle = fopen(argv[2], "rb");
        if (!input_file_handle) {
            graphic_printf(RED, BOLD, "null pointer input_file_handle in main\n");
            return FILE_ERROR;
        }
    }
    else if (argc == 4) {
        input_file_handle = fopen(argv[2], "rb");
        if (!input_file_handle) {
            graphic_printf(RED, BOLD, "null pointer input_file_handle in main\n");
            return FILE_ERROR;
        }
        output_file_handle = fopen(argv[3], "a");
        if (!output_file_handle) {
            graphic_printf(RED, BOLD, "null pointer output_file in main\n");
            return FILE_ERROR;
        }
        fprintf(stderr, "out file: %p\n", output_file_handle);
    }
    else {
        graphic_printf(RED, BOLD, "error\nfile name was not entered\n");
        return INPUT_ERROR;
    }

    count_symbols  (input_file_handle, &TextData);
    fill_text      (input_file_handle, &TextData);
    custom_qsort   (TextData.LineData, TextData.lines, sizeof(LINE_DATA), compare_strings_starts);
    print_text     (output_file_handle, &TextData);
    free_text_data (&TextData);

    fclose(input_file_handle);
    fclose(output_file_handle);

    return 0;
}

int sort_text_rhyme(int argc, const char* argv[]) {
    ERROR_DATA error_inf = PROGRAM_ERROR;
    TEXT_DATA TextData   = {};
    FILE* input_file_handle  = NULL;
    FILE* output_file_handle = stdout;

    if (argc == 3) {
        input_file_handle = fopen(argv[2], "rb");
        if (!input_file_handle) {
            graphic_printf(RED, BOLD, "null pointer input_file_handle in main\n");
            return FILE_ERROR;
        }
    }
    else if (argc == 4) {
        input_file_handle = fopen(argv[2], "rb");
        if (!input_file_handle) {
            graphic_printf(RED, BOLD, "null pointer input_file_handle in main\n");
            return FILE_ERROR;
        }
        output_file_handle = fopen(argv[3], "a");
        if (!output_file_handle) {
            graphic_printf(RED, BOLD, "null pointer output_file in main\n");
            return FILE_ERROR;
        }
        fprintf(stderr, "out file: %p\n", output_file_handle);
    }
    else {
        graphic_printf(RED, BOLD, "error\nfile name was not entered\n");
        return INPUT_ERROR;
    }

    count_symbols  (input_file_handle, &TextData);
    fill_text      (input_file_handle, &TextData);
    custom_qsort   (TextData.LineData, TextData.lines, sizeof(LINE_DATA), compare_strings_ends);
    print_text     (output_file_handle, &TextData);
    free_text_data (&TextData);

    fclose(input_file_handle);
    fclose(output_file_handle);

    return 0;
}

int special_for_ded(int argc, const char* argv[]) {
    ERROR_DATA error_inf = PROGRAM_ERROR;
    TEXT_DATA TextData = {};
    FILE* input_file_handle  = NULL;
    FILE* output_file_handle = stdout;

    if (argc == 3) {
        input_file_handle  = fopen(argv[2], "rb");
        output_file_handle = fopen(argv[2], "a");
        if (!input_file_handle) {
            graphic_printf(RED, BOLD, "null pointer input_file_handle in main\n");
            return FILE_ERROR;
        }
    }

    count_symbols  (input_file_handle,  &TextData);
    fill_text      (input_file_handle,  &TextData);
    custom_qsort   (TextData.LineData,   TextData.lines, sizeof(LINE_DATA), compare_strings_starts);
    print_text     (output_file_handle, &TextData);
    custom_qsort   (TextData.LineData,   TextData.lines, sizeof(LINE_DATA), compare_strings_ends);
    print_text     (output_file_handle, &TextData);
    custom_qsort   (TextData.LineData,   TextData.lines, sizeof(LINE_DATA), compare_pointers);
    print_text     (output_file_handle, &TextData);
    free_text_data (&TextData);

    fclose(input_file_handle);
    fclose(output_file_handle);

    return 0;
}
