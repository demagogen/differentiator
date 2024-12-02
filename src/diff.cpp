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

        recursive_remove_trivials(tree->root, &indicator);

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

// TODO make define later
void recursive_constant_propagation(NODE* node, bool* indicator)
{
    if (!node || !node->left || !node->right)
    {
        return;
    }

    if (node->type == OPERATION     &&
        node->right->type == OBJECT &&
        node->left->type  == OBJECT)
    {
        NodeData_t left_value  = node->left->data;
        NodeData_t right_value = node->right->data;

        switch (return_operation_code(node))
        {
            case (ADD):
                CUT_CHILDS(left_value + right_value);
                *indicator = false;
                break;


            case (MUL):
                CUT_CHILDS(left_value * right_value);
                *indicator = false;
                break;

            case (DIV):
                CUT_CHILDS(left_value / right_value);
                *indicator = false;
                break;

            default:
                break;
        }
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

//TODO сделать так, чтобы это была свертка констант, а не любого выражения.

//-----------------------------------------------------------------------------------------------------------------------------
//!                                                  REMOVE TRIVIALS
//-----------------------------------------------------------------------------------------------------------------------------

/*
    trivials function structure
    if-statement (make function)
        return new node (make function or macros)
        indicator false
*/

// TODO make defines later

void recursive_remove_trivials(NODE* node, bool* indicator)
{
    if (!node || !node->right || !node->left)
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
    {
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
    {
        CUT_CHILDS(0);
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
