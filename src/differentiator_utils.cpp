#include "differentiator.h"
#include "differentiator_utils.h"
#include "compose_tex.h"

bool have_variable (NODE* node)
{
    bool indicator = false;

    bool right_node_have_variable = false;
    bool left_node_have_variable  = false;

    if (node->type == VARIABLE)
    {
        return true;
    }

    if (node->left)
    {
        left_node_have_variable = have_variable (node->left);
    }
    if (node->right)
    {
        right_node_have_variable = have_variable (node->right);
    }

    return left_node_have_variable || right_node_have_variable;
}

bool two_childs_are_objects (NODE* parentNode) // TODO children
{
    assert (parentNode);

    return (parentNode->left->type == OBJECT && parentNode->right->type == OBJECT);
}

bool check_one_object_is_zero (NODE* parentNode)
{
    assert (parentNode);

    return (parentNode->right->type == OBJECT && compare_values (parentNode->right->data, 0) == EQUAL) ||
           (parentNode->left->type  == OBJECT && compare_values (parentNode->left->type, 0)  == EQUAL);
}

bool check_for_basic_trivials_statement (NODE* node)
{
    assert (node);

    return (node->type == OPERATION                                      && // TODO formatting
           (node->left->type == OBJECT && node->right->type != OBJECT    ||
            node->left->type != OBJECT && node->right->type == OBJECT));
}

bool trivials_add_zero (NODE* operationNode, NODE* objectNode)
{
    assert (operationNode);
    assert (objectNode);

    return (return_operation_code (operationNode) == ADD &&
            compare_values (objectNode->data, 0)  == EQUAL);
}

bool trivials_mul_one(NODE* operationNode, NODE* objectNode)
{
    assert (operationNode);
    assert (objectNode);

    return (return_operation_code (operationNode) == MUL &&
            compare_values (objectNode->data, 1)  == EQUAL);
}


    #define DESCRIPTION_(_error)    \
        case _error: return #_error

const char* return_tree_error_enum_name_string (TREE_ERROR enum_param)
{
    switch (enum_param)
    {
        DESCRIPTION_ ( TREE_NODE_DED_INSIDE              );
        DESCRIPTION_ ( TREE_DED_INSIDE                   );
        DESCRIPTION_ ( TREE_POISON                       );
        DESCRIPTION_ ( TREE_NONE                         );
        DESCRIPTION_ ( TREE_STRUCT_ALLOCATION_ERROR      );
        DESCRIPTION_ ( TREE_NODE_ALLOCATION_ERROR        );
        DESCRIPTION_ ( TREE_INVALID_CAPACITY             );
        DESCRIPTION_ ( TREE_OVERSIZE                     );
        DESCRIPTION_ ( TREE_MISSING_IP                   );
        DESCRIPTION_ ( TREE_ROOT_ALLOCATION_ERROR        );
        DESCRIPTION_ ( TREE_LEFT_CHILD_ALLOCATION_ERROR  );
        DESCRIPTION_ ( TREE_RIGHT_CHILD_ALLOCATION_ERROR );
        DESCRIPTION_ ( TREE_PARENT_ALLOCATION_ERROR      );
        DESCRIPTION_ ( TREE_NODE_NOT_LEAF                );
        DESCRIPTION_ ( TREE_ERROR_SIDE                   );
        DESCRIPTION_ ( TREE_NULL_NODE                    );
        DESCRIPTION_ ( TREE_NODE_TYPE_ERROR              );

        default:
            return "error print error";
    }
}

const char* return_node_rule_enum_name_string (NODE_RULE enum_param)
{
    switch(enum_param)
    {
        DESCRIPTION_ ( RULE_POISON );
        DESCRIPTION_ ( ROOT        );
        DESCRIPTION_ ( RIGHT       );
        DESCRIPTION_ ( LEFT        );

        default:
            return "error print error";
    }
}

const char* return_type_string (NODE_ELEMENT_TYPE enum_param)
{
    switch (enum_param)
    {
        DESCRIPTION_ ( TYPE_POISON );
        DESCRIPTION_ ( OBJECT      );
        DESCRIPTION_ ( OPERATION   );
        DESCRIPTION_ ( VARIABLE    );

        default:
            printf("i don know what is it %d\n", enum_param);
            return "error print error";
    }
}

const char* return_operation_string (NodeData_t data)
{
    OPERATIONS operation = (OPERATIONS) data;

    switch (operation)
    {
        case ( ADD           ): return "+"    ; break;
        case ( SUB           ): return "-"    ; break;
        case ( MUL           ): return "*"    ; break;
        case ( DIV           ): return "/"    ; break;
        case ( POW           ): return "^"    ; break;
        case ( COS           ): return "cos"  ; break;
        case ( SIN           ): return "sin"  ; break;
        case ( LN            ): return "ln"   ; break;
        case ( OPEN_BRACKET  ): return "("    ; break;
        case ( CLOSE_BRACKET ): return ")"    ; break;
        case ( END           ): return "ruble"; break;

        default:
            printf("unknown %d\n", OPERATIONS(data));
            return "error print error";
            break;
    }
}

OPERATIONS return_operation_code (NODE* node)
{
    if (node->type == OPERATION)
    {
        return (OPERATIONS) node->data;
    }
    else
    {
        return POISON;
    }
}

COMPARE compare_values (NodeData_t value1, NodeData_t value2)
{
    if (value1 < value2)
    {
        return LESS;
    }
    else if (value1 > value2)
    {
        return MORE;
    }
    else
    {
        return EQUAL;
    }
}

int read_line (char** line, char** base_ip)
{
    if (!base_ip)
    {
        return -1;
    }

    *line = *base_ip;
    size_t offset = 0;
    while (*(*base_ip + 1) != '{' && *(*base_ip + 1) != '}')
    {
        (*line)[offset] = **base_ip;
        (*base_ip)++;
        offset++;
    }
    *(*line + offset) = '\0';

    return 0;
}

const char* random_phrase ()
{
    int cringe_descriptor = rand() % PhrasesQuantity;

    return phrases[cringe_descriptor];
}
