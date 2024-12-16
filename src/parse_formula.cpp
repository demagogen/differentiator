#include <ctype.h>

#include "parse_formula.h"

int read_formula (TREE* tree, FORMULA* formula)
{
    assert (formula);

    TOKEN* tokensArray = (TOKEN* ) calloc (MAX_TOKEN_QUANTITY, sizeof(TOKEN));

    lexer (&tokensArray, formula);

    if (tokensArray)
    {
        CONTEXT context     = {};
        context.tokensArray = tokensArray;
        context.token_index = 0;

        tree->root = get_g(&context);
    }

    return 0;
}

#define DEBUG_LEXER_TOKEN(message) \
    printf(message);              \
    printf(" %d\n", token_index);

int lexer (TOKEN** tokensArray, FORMULA* formula)
{
    assert (tokensArray);
    assert (formula);

    size_t token_index = 0;

    size_t open_brackets_quantity  = 0;
    size_t close_brackets_quantity = 0;

    while (CURRENT_FORMULA_SYMBOL != '$' && CURRENT_FORMULA_SYMBOL != '\0')
    {
        int symbol = read_next_symbol(formula);

        if (CURRENT_FORMULA_SYMBOL == '(')
        {
            TOKEN_PTR[token_index].type = OPERATION;
            TOKEN_PTR[token_index].data = OPEN_BRACKET;

            open_brackets_quantity++;

            F_INDEX += 1;
        }
        else if (CURRENT_FORMULA_SYMBOL == ')')
        {
            TOKEN_PTR[token_index].type = OPERATION;
            TOKEN_PTR[token_index].data = CLOSE_BRACKET;

            close_brackets_quantity++;

            F_INDEX += 1;
        }
        else if ('0' <= CURRENT_FORMULA_SYMBOL && CURRENT_FORMULA_SYMBOL <= '9')
        {
            NodeData_t value  = 0;
            int        offset = 0;

            sscanf (F_BUFFER + F_INDEX, " %lf%n", &value, &offset);

            TOKEN_PTR[token_index].type = OBJECT;
            TOKEN_PTR[token_index].data = value;

            F_INDEX += offset;
        }
        else if (CURRENT_FORMULA_SYMBOL == 'x')
        {
            TOKEN_PTR[token_index].type = VARIABLE;
            TOKEN_PTR[token_index].data = 404;

            F_INDEX += 1;
        }
        else if (CURRENT_FORMULA_SYMBOL == '\0' && CURRENT_FORMULA_SYMBOL == '$')
        {
            TOKEN_PTR[token_index].type = OPERATION;
            TOKEN_PTR[token_index].data = END;
        }
        else
        {
            parse_operations_in_lexer (tokensArray, token_index, formula);
        }

        token_index++;
    }

    TOKEN_PTR[token_index].type = OPERATION;
    TOKEN_PTR[token_index].data = END;

    if (open_brackets_quantity != close_brackets_quantity)
    {
        syntax_error ("brackets error"); // TODO print error
        TOKEN_PTR = NULL;
    }
    else
    {
        TOKEN_PTR[token_index].type = OPERATION;
        TOKEN_PTR[token_index].data = END;
    }

    dump_tokens (tokensArray);

    return 0;
}

#define PARSE_TOKEN(op, op_length)            \
    TOKEN_PTR[token_index].type = OPERATION; \
    TOKEN_PTR[token_index].data = op;        \
    F_INDEX += op_length;

#define DEBUG_PRINT_TOKEN(operation)                            \
    printf(operation);                                         \
    printf("\n");                                              \
    printf("token index: %d\n", TOKEN_PTR[token_index].number);

int parse_operations_in_lexer (TOKEN** tokensArray, size_t token_index, FORMULA* formula)
{
    assert (formula);
    int symbol = read_next_symbol (formula);

    TOKEN_PTR[token_index].number = token_index;

    if (strncmp ("sin", F_BUFFER + F_INDEX, 3) == 0)
    {
        TOKEN_PTR[token_index].type = OPERATION;
        TOKEN_PTR[token_index].data = SIN;

        F_INDEX += 3;
    }
    else if (strncmp ("cos", F_BUFFER + F_INDEX, 3) == 0)
    {
        TOKEN_PTR[token_index].type = OPERATION;
        TOKEN_PTR[token_index].data = COS;

        F_INDEX += 3;
    }
    else if (strncmp ("ln", F_BUFFER + F_INDEX, 2) == 0)
    {
        TOKEN_PTR[token_index].type = OPERATION;
        TOKEN_PTR[token_index].data = LN;

        F_INDEX += 2;
    }
    else if (F_BUFFER[F_INDEX] == '+')
    {
        TOKEN_PTR[token_index].type = OPERATION;
        TOKEN_PTR[token_index].data = ADD;

        F_INDEX += 1;
    }
    else if (F_BUFFER[F_INDEX] == '-')
    {
        TOKEN_PTR[token_index].type = OPERATION;
        TOKEN_PTR[token_index].data = SUB;

        F_INDEX += 1;
    }
    else if (F_BUFFER[F_INDEX] == '*')
    {
        TOKEN_PTR[token_index].type = OPERATION;
        TOKEN_PTR[token_index].data = MUL;

        F_INDEX += 1;
    }
    else if (F_BUFFER[F_INDEX] == '/')
    {
        TOKEN_PTR[token_index].type = OPERATION;
        TOKEN_PTR[token_index].data = DIV;

        F_INDEX += 1;
    }
    else if (F_BUFFER[F_INDEX] == '^')
    {
        TOKEN_PTR[token_index].type = OPERATION;
        TOKEN_PTR[token_index].data = POW;

        F_INDEX += 1;
    }
    else if (F_BUFFER[F_INDEX] == '\0' || F_BUFFER[F_INDEX] == '$')
    {
        TOKEN_PTR[token_index].type = OPERATION;
        TOKEN_PTR[token_index].data = END;
    }

    return 0;
}

int dump_tokens (TOKEN** tokensArray)
{
    assert (tokensArray);

    printf ("TOKENS ARRAY DUMP\n");
    printf ("_________________\n");

    for (size_t token_index = 0; token_index < MAX_TOKEN_QUANTITY; token_index++)
    {
        printf ("token[%3d] type: %s\n", token_index, return_type_string (TOKEN_PTR[token_index].type));

        if (TOKEN_PTR[token_index].type == OPERATION)
        {
            printf ("token[%3d] data: %s\n", token_index, return_operation_string (TOKEN_PTR[token_index].data));

            if ((OPERATIONS) TOKEN_PTR[token_index].data == END)
            {
                break;
            }
        }
        else if (TOKEN_PTR[token_index].type == VARIABLE)
        {
            printf ("token[%3d] data: %s\n", token_index, "x");
        }
        else if (TOKEN_PTR[token_index].type == OBJECT)
        {
            printf ("token[%3d] data: %lf\n", token_index, TOKEN_PTR[token_index].data);
        }
        else
        {
            printf ("token[%3d] data: %c\n", token_index, TOKEN_PTR[token_index].data);
        }
    }

    printf ("_________________\n");

    return 0;
}

#define DEBUG_PRINT_GET(get_function)                      \
    printf(get_function);                                 \
    printf("\n");                                         \
    printf("get token number %d\n", CURRENT_TOKEN.number);

NODE* get_g (CONTEXT* context)
{
    assert (context);

    NODE* node = get_e (context);

    if ((OPERATIONS)CURRENT_TOKEN.data != END)
    {
        syntax_error ("get_g END lost");
        printf       ("token index failure %d\n", context->token_index);
        printf       ("operation number %d\n", (OPERATIONS) node->data);
        printf       ("token index %d\n", context->token_index); exit(0);
    }

    return node;
}

NODE* get_n (CONTEXT* context)
{
    assert (context);

    NODE* node = new_node (OBJECT, CURRENT_TOKEN.data, NULL, NULL);
    context->token_index++;

    return node;
}

#define ADD_OR_SUB \
    CURRENT_TOKEN.type == OPERATION && ((OPERATIONS)CURRENT_TOKEN.data == ADD || (OPERATIONS)CURRENT_TOKEN.data == SUB)

NODE* get_e (CONTEXT* context)
{
    assert (context);

    NODE* node = get_t (context);

    while (ADD_OR_SUB)
    {
        size_t old_index = context->token_index;
        context->token_index++;
        NODE* node2 = get_t (context);
        node = new_node (OPERATION, (OPERATIONS)context->tokensArray[old_index].data, node, node2);
    }

    return node;
}

NODE* get_d (CONTEXT* context)
{
    NODE* node = get_p (context);

    if ((OPERATIONS)context->tokensArray[context->token_index].data == POW)
    {
        context->token_index++;
        NODE* node2 = get_d (context);
        node = new_node (OPERATION, POW, node, node2);
    }

    return node;
}

#define MUL_OR_DIV \
    CURRENT_TOKEN.type == OPERATION && ((OPERATIONS)CURRENT_TOKEN.data == MUL || (OPERATIONS)CURRENT_TOKEN.data == DIV)

NODE* get_t (CONTEXT* context)
{
    NODE* node = get_d (context);

    while (MUL_OR_DIV)
    {
        size_t old_index = context->token_index;
        context->token_index++;
        NODE* node2 = get_d (context);
        node = new_node (OPERATION, (OPERATIONS)context->tokensArray[old_index].data, node, node2);
    }

    return node;
}

NODE* get_p (CONTEXT* context)
{
    if (context->tokensArray[context->token_index].type == OPERATION)
    {
        if ((OPERATIONS)context->tokensArray[context->token_index].data == OPEN_BRACKET)
        {
            context->token_index++;
            NODE* node = get_e (context);
            context->token_index++;

            return node;
        }
        else
        {
            return get_f (context);
        }
    }
    else
    {
        return get_f (context);
    }
}

NODE* get_f (CONTEXT* context)
{
    assert (context);

    if (context->tokensArray[context->token_index].type == OPERATION)
    {
        size_t old_index = context->token_index;
        context->token_index++;
        NODE* node = get_p (context);

        return new_node (OPERATION, (OPERATIONS)context->tokensArray[old_index].data, node, NULL);
    }
    else
    {
        return get_v (context);
    }
}

NODE* get_v (CONTEXT* context)
{
    assert (context);

    if (context->tokensArray[context->token_index].type == VARIABLE)
    {
        size_t old_index = context->token_index;
        context->token_index++;

        return new_node (VARIABLE, CURRENT_TOKEN.data, NULL, NULL);
    }
    else
    {
        return get_n (context);
    }
}

NODE* syntax_error (const char* string)
{
    printf ("PIZDEC\n%s\n", string);

    return 0;
}

char read_next_symbol (FORMULA* formula)
{
    assert (formula);

    while (isspace (formula->buffer[formula->index]))
    {
        formula->index++;
    }

    return formula->buffer[formula->index];
}
