#include "diff_tree.h"
#include "diff_tree_utils.h"
#include "diff.h"

NODE* differentiate(NODE* node)
{
    if (node->type == OBJECT)
    {
        return NUM_(0.0);
    }
    else if (node->type == VARIABLE)
    {
        return NUM_(1.0);
    }

    NODE* resultNode = {};

    #define DIFF_LEFT  differentiate ( node->left  )
    #define DIFF_RIGHT differentiate ( node->right )
    #define COPY_LEFT  copy_node     ( node->left  )
    #define COPY_RIGHT copy_node     ( node->right )

    switch (return_operation_code(node))
    {
        case (ADD):
        {
            resultNode = ADD_(DIFF_LEFT, DIFF_RIGHT);
            break;
        }
        case (SUB):
        {
            resultNode = SUB_(DIFF_LEFT, DIFF_RIGHT);
            break;
        }
        case (MUL):
        {
            resultNode = ADD_(MUL_(DIFF_LEFT, COPY_RIGHT), MUL_(DIFF_RIGHT, COPY_LEFT)); //printf in LaTeX after every operation
            break;
//TODO cos sin log pow reader
            //TODO frazes
            //TODO graphics
            //TODO Taylor
        }
        case (DIV):
        {
            resultNode = DIV_(SUB_(MUL_(DIFF_LEFT, COPY_RIGHT), MUL_(DIFF_RIGHT, COPY_LEFT)), MUL_(COPY_RIGHT, COPY_RIGHT));
            break;
        }
    }

    #undef DIFF_LEFT
    #undef DIFF_RIGHT
    #undef COPY_LEFT
    #undef COPY_RIGHT

    return resultNode;
}

//TODO constant propagation
//TODO * useless element (huynya + 0)
//TODO LaTeX after every derivative

void optimization(TREE* tree)
{
    while (true)
    {
        bool indicator = true;

        recursive_constant_propagation(tree->root, &indicator);

        // recursive_remove_trivials(tree->root, &indicator);

        if (indicator)
        {
            break;
        }
    }
}

#define CUT_CHILDS(value) \
    node->left  = NULL;   \
    node->right = NULL;   \
                          \
    node->type = OBJECT;  \
    node->data = value;

void recursive_constant_propagation(NODE* node, bool* indicator)
{
    if (!node || !node->left || !node->right)
    {
        return;
    }

    if (node->type == OPERATION)
    {
        if (check_div_numerator_is_zero(node))
        {printf("rcp 1\n");
            node = div_numerator_is_zero(node);
            *indicator = false;
        }
        if (check_div_denominator_is_one(node))
        {printf("rcp 2\n");
            node = div_denominator_is_one(node);
            *indicator = false;
        }
        if (check_mul_factor_is_zero(node))
        {printf("rcp 3\n");
            node = mul_factor_is_zero(node);
            *indicator = false;
        }
        if (check_mul_factor_is_one(node))
        {printf("rcp 4\n");
            node = mul_factor_is_one(node);
            *indicator = false;
        }
        if (check_add_term_is_zero(node))
        {printf("rcp 5\n");
            node = add_term_is_zero(node);
            *indicator = false;
        }
        // if (check_two_neighboring_objects(node))
        // {
//
        // }
    }

    if (node->right)
    {
        recursive_constant_propagation(node->right, indicator);
    }
    if (node->left)
    {
        recursive_constant_propagation(node->left, indicator);
    }

    return;
}

//=============================================================================================================================
//!                                                 OPTIMIZATION UTILS
//=============================================================================================================================
//-----------------------------------------------------------------------------------------------------------------------------
//!                                                CONSTANTS PROPAGATION
//-----------------------------------------------------------------------------------------------------------------------------

//TODO сделать так, чтобы это была свертка констант, а не лобого выражения.
#define CHECK_DIV_PARAMS(node, value)              \
    return_operation_code(node) == DIV          && \
    node->type == OBJECT                        && \
    compare_values(node->data, value) == EQUAL;    \

bool check_div_numerator_is_zero(NODE* node)
{
    return CHECK_DIV_PARAMS(node->left, 0);
}

bool check_div_denominator_is_one(NODE* node)
{
    return CHECK_DIV_PARAMS(node->right, 1);
}

#define CHECK_MUL_PARAMS(value)                                                              \
    return_operation_code(node) == MUL                                                    && \
    ((node->right->type == OBJECT && compare_values(node->right->data, value) == EQUAL)   || \
     (node->left->type  == OBJECT && compare_values(node->left->data,  value) == EQUAL));    \

bool check_mul_factor_is_zero(NODE* node)
{
    return CHECK_MUL_PARAMS(0);
}

bool check_mul_factor_is_one(NODE* node)
{
    return CHECK_MUL_PARAMS(1);
}

bool check_add_term_is_zero(NODE* node)
{
    return return_operation_code(node) == ADD            &&
         ((node->left->type  == OBJECT                   &&
           compare_values(node->left->data,  0) == EQUAL &&
           node->right->type == OBJECT)                  ||
          (node->right->type == OBJECT                   &&
           compare_values(node->right->data, 0) == EQUAL &&
           node->left->type == OBJECT));
}

bool check_two_neighboring_objects(NODE* node)
{
    return node->type == OPERATION && node->right->type == OBJECT && node->left->type == OBJECT;
}

NODE* div_numerator_is_zero(NODE* node)
{
    CUT_CHILDS(0);

    return node;
}

NODE* div_denominator_is_one(NODE* node)
{
    NodeData_t value = node->left->data;

    CUT_CHILDS(value);

    return node;
}

NODE* mul_factor_is_zero(NODE* node)
{
    CUT_CHILDS(0);

    return node;
}

NODE* mul_factor_is_one(NODE* node)
{
    NodeData_t value = 0;

    if (node->left->data != 1)
    {
        value = node->left->data;
    }
    else
    {
        value = node->right->data;
    }

    CUT_CHILDS(value);

    return node;
}

NODE* add_term_is_zero(NODE* node)
{
    NodeData_t value = 0;

    if (node->left->data != 0)
    {
        value = node->left->data;
    }
    else
    {
        value = node->right->data;
    }

    CUT_CHILDS(value);

    return node;
}

NODE* add_two_terms(NODE* node)
{
    NodeData_t value = node->left->data + node->right->data;

    CUT_CHILDS(value);

    return node;
}

NODE* mul_two_factors(NODE* node)
{
    NodeData_t value = node->left->data * node->right->data;

    CUT_CHILDS(value);

    return node;
}

//-----------------------------------------------------------------------------------------------------------------------------
//!                                                  REMOVE TRIVIALS
//-----------------------------------------------------------------------------------------------------------------------------

/*
    trivials function structure
    if-statement (make function)
        return new node (make function or macros)
        indicator false
*/

void recursive_remove_trivials(NODE* node, bool* indicator)
{
    if (!node)
    {
        return;
    }

    struct THREE_NODE_DATA
    {
        OPERATIONS operation;

        NodeData_t object_value;
        NODE_RULE object_node_rule;

        NODE* tmpNode;
        NODE_RULE tmpNode_rule;
    };

    THREE_NODE_DATA threeNodeData = {};

    NodeData_t object_value = 0;
    NODE*      tmpNode      = NULL;

    if (node->type == OPERATION)
    {
        threeNodeData.operation = return_operation_code(node);
    }

    if (node->right->type == OBJECT && node->left->type != OBJECT)
    {
        threeNodeData.object_value     = node->right->data;
        threeNodeData.object_node_rule = RIGHT;

        threeNodeData.tmpNode      = node->left;
        threeNodeData.tmpNode_rule = LEFT;
    }
    else if (node->left->type == OBJECT && node->right->type != OBJECT)
    {
        threeNodeData.object_value     = node->left->data;
        threeNodeData.object_node_rule = LEFT;

        threeNodeData.tmpNode      = node->right;
        threeNodeData.tmpNode_rule = RIGHT;
    }
    else
    {printf("return in ==\n");
        return;
    }

    if (threeNodeData.operation == ADD && compare_values(threeNodeData.object_value, 0) == EQUAL)
    {
        node = threeNodeData.tmpNode;
        *indicator = false;
    }
    if (threeNodeData.operation == MUL && compare_values(threeNodeData.object_value, 1) == EQUAL)
    {
        node = threeNodeData.tmpNode;
        *indicator = false;
    }
    if (threeNodeData.operation == DIV && threeNodeData.object_node_rule == LEFT && compare_values(threeNodeData.object_value, 0))
    {
        node = threeNodeData.tmpNode;
        *indicator = false;
    }
    if (threeNodeData.operation == DIV && threeNodeData.object_node_rule == RIGHT && compare_values(threeNodeData.object_value, 1))
    {
        node = threeNodeData.tmpNode;
        *indicator = false;
    }

    if (threeNodeData.operation == MUL && compare_values(threeNodeData.object_value, 0) == EQUAL)
    {printf("in null trivials\n");
        node = NUM_(0);
        *indicator = false;
    }

    if (node->left)
    {
        recursive_remove_trivials(node->left, indicator);
    }
    if (node->right)
    {
        recursive_remove_trivials(node->right, indicator);
    }
}
