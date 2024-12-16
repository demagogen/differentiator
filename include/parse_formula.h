#ifndef PARSE_FORMULA_H_
#define PARSE_FORMULA_H_

#include "differentiator_tree.h"
#include "differentiator.h"

//-----------------------------------------------------------------------------------------------------------------------------
//!                                                          FORMULA FUNCTIONS
//-----------------------------------------------------------------------------------------------------------------------------

struct FORMULA
{
    char*  buffer;
    size_t index;
};

//-----------------------------------------------------------------------------------------------------------------------------
//!                                                              LEXER
//-----------------------------------------------------------------------------------------------------------------------------

const size_t MAX_TOKEN_QUANTITY = 52;

#define F_BUFFER formula->buffer
#define F_INDEX formula->index

#define T_ARRAY context->tokensArray
#define T_INDEX context->token_index

#define CURRENT_TOKEN context->tokensArray[context->token_index]

#define TOKEN_PTR (*tokensArray)

#define CURRENT_FORMULA_SYMBOL formula->buffer[formula->index]
#define PREVIOUS_FORMULA_SYMBOL formula->buffer[formula->index - 1]
#define NEXT_FORMULA_SYMBOL formula->buffer[formula->index + 1]

struct TOKEN
{
    size_t            number;
    NODE_ELEMENT_TYPE type;
    NodeData_t        data;
};

struct CONTEXT
{
    size_t token_index;
    TOKEN* tokensArray;
};

int read_formula              (TREE* tree, FORMULA* formula);
int lexer                     (TOKEN** tokensArray, FORMULA* formula);
int parse_operations_in_lexer (TOKEN** tokensArray, size_t token_index, FORMULA* formula);
int dump_tokens         (TOKEN** tokensArray);

//-----------------------------------------------------------------------------------------------------------------------------
//!                                                     RECURSIVE PARSING FUNCTIONS
//-----------------------------------------------------------------------------------------------------------------------------

NODE* get_n (CONTEXT* context);
NODE* get_p (CONTEXT* context);
NODE* get_g (CONTEXT* context);
NODE* get_e (CONTEXT* context);
NODE* get_t (CONTEXT* context);
NODE* get_v (CONTEXT* context);
NODE* get_f (CONTEXT* context);

NODE* syntax_error (const char* string);

//-----------------------------------------------------------------------------------------------------------------------------
//!                                                             UTILS
//-----------------------------------------------------------------------------------------------------------------------------
char read_next_symbol (FORMULA* formula);

#endif
