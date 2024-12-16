#include "differentiator_utils.h"
#include "differentiator_tree.h"
#include "differentiator.h"
#include "compose_tex.h"

//-----------------------------------------------------------------------------------------------------------------------------
//!                                                       DIFFERENTIATE FUNCTIONS
//-----------------------------------------------------------------------------------------------------------------------------

NODE* differentiate (TREE* tree, NODE* node)
{
    assert (node);

    if (node->type == OBJECT)
    {
        return NUM_(0);
    }
    else if (node->type == VARIABLE)
    {
        return NUM_(1);
    }

    NODE* resultNode = take_node_derivative (tree, node);

    bool detector = true;
    optimization (node, &detector);

    assert (resultNode);
    assert (node);

    return resultNode;
}

NODE* take_node_derivative (TREE* tree, NODE* node)
{
    assert (node);

    switch (return_operation_code (node))
        {
            // TODO remove brackets
            case (ADD):
                // LATEX_PRINT ("$$\\left(");
                latex_dump  (tree, node, TEX_NODE);
                // LATEX_PRINT ("\\right)^\\prime");

                node = ADD_ (DIFF_LEFT, DIFF_RIGHT);

                // latex_dump  (tree, node, TEX_NODE_SECOND);
                // LATEX_PRINT ("$$\n");
                break;

            case (SUB):
                // LATEX_PRINT ("$$\\left(");
                latex_dump  (tree, node, TEX_NODE);
                // LATEX_PRINT ("\\right)^\\prime");

                node = SUB_ (DIFF_LEFT, DIFF_RIGHT);

                // latex_dump  (tree, node, TEX_NODE_SECOND);
                // LATEX_PRINT ("$$\n");
                break;

            case (MUL):
                // LATEX_PRINT ("$$\\left(");
                latex_dump  (tree, node, TEX_NODE);
                // LATEX_PRINT ("\\right)^\\prime");

                node = ADD_ (MUL_ (DIFF_LEFT, COPY_RIGHT), MUL_ (DIFF_RIGHT, COPY_LEFT));

                // latex_dump  (tree, node, TEX_NODE_SECOND);
                // LATEX_PRINT ("$$\n");
                break;

            case (DIV):
                // LATEX_PRINT ("$$\\left(");
                latex_dump  (tree, node, TEX_NODE);
                // LATEX_PRINT ("\\right)^\\prime");

                node = DIV_ (SUB_ (MUL_ (DIFF_LEFT, COPY_RIGHT), MUL_ (DIFF_RIGHT, COPY_LEFT)), MUL_ (COPY_RIGHT, COPY_RIGHT));

                // latex_dump  (tree, node, TEX_NODE_SECOND);
                // LATEX_PRINT ("$$\n");
                break;

            case (SIN):
                // LATEX_PRINT ("$$\\left(");
                latex_dump  (tree, node, TEX_NODE);
                // LATEX_PRINT ("\\right)^\\prime");

                node = MUL_ (COS_ (COPY_LEFT), DIFF_LEFT);

                // latex_dump  (tree, node, TEX_NODE_SECOND);
                // LATEX_PRINT ("$$\n");
                break;

            case (COS):
                // LATEX_PRINT ("$$\\left(");
                latex_dump  (tree, node, TEX_NODE);
                // LATEX_PRINT ("\\right)^\\prime");

                node = MUL_ (NUM_ (-1), MUL_ (SIN_ (COPY_LEFT), DIFF_LEFT));

                // latex_dump  (tree, node, TEX_NODE_SECOND);
                // LATEX_PRINT ("$$\n");
                break;

            case (LN):
                // LATEX_PRINT ("$$\\left(");
                latex_dump  (tree, node, TEX_NODE);
                // LATEX_PRINT ("\\right)^\\prime");

                node = MUL_ (DIV_ (NUM_ (1), COPY_LEFT), DIFF_LEFT);

                // latex_dump  (tree, node, TEX_NODE_SECOND);
                // LATEX_PRINT ("$$\n");
                break;

            case (POW):
                // LATEX_PRINT ("$$\\left(");
                latex_dump  (tree, node, TEX_NODE);
                // LATEX_PRINT ("\\right)^\\prime");

                if (!have_variable(node->left))
                {
                    node = MUL_ (MUL_ (POW_ (COPY_LEFT, COPY_RIGHT), NUM_ (log (node->left->data))), DIFF_RIGHT);
                }
                else if (!have_variable (node->right))
                {
                    node = MUL_ (MUL_ (COPY_RIGHT, POW_ (COPY_LEFT, NUM_ (node->right->data - 1))), DIFF_LEFT);
                }
                else
                {
                    node = MUL_ (POW_ (COPY_LEFT, COPY_RIGHT), ADD_ (MUL_ (LN_ (COPY_LEFT), DIFF_RIGHT),
                                      MUL_ (DIV_ (DIFF_LEFT, COPY_LEFT), COPY_RIGHT)));
                }

                // latex_dump (tree, node, TEX_NODE_SECOND);
                // LATEX_PRINT ("$$\n");
                break;

            default:
                printf ("nothing\n");
                break;
        }

        assert (node);

        bool detector = true;
        optimization (node, &detector);

        return node;
}

//-----------------------------------------------------------------------------------------------------------------------------
//!                                                     OPTIMIZATION FUNCTIONS
//-----------------------------------------------------------------------------------------------------------------------------

void optimization (NODE* node, bool* detector)
{
    assert (node);

    while (true)
    {
        bool indicator = true;

        recursive_constant_propagation ( node, &indicator);
        recursive_remove_trivials      (&node, &indicator);

        if (indicator)
        {
            break;
        }
        else
        {
            *detector = false;
        }
    }

    assert (node);
}

void recursive_constant_propagation (NODE* node, bool* indicator)
{
    assert (node);
    assert (indicator);

    if (!node || !node->left || !node->right)
    {
        return;
    }

    if (node->type        == OPERATION &&
        node->right->type == OBJECT    &&
        node->left->type  == OBJECT)
    {
        NodeData_t left_value  = node->left->data;
        NodeData_t right_value = node->right->data;

        switch (return_operation_code (node))
        {
            case (ADD):
                CUT_CHILDS_AND_SAVE_VALUE(left_value + right_value);
                *indicator = false;
                break;

            case (MUL):
                if (two_childs_are_objects (node))
                {
                    CUT_CHILDS_AND_SAVE_VALUE(left_value * right_value);
                }
                else if (check_one_object_is_zero (node))
                {
                    CUT_CHILDS_AND_SAVE_VALUE(0);
                }

                *indicator = false;
                break;

            case (DIV):
                CUT_CHILDS_AND_SAVE_VALUE(left_value / right_value);
                *indicator = false;
                break;

            default:
                break;
        }
    }

    if (node->right)
    {
        recursive_constant_propagation (node->right, indicator);
    }
    if (node->left)
    {
        recursive_constant_propagation (node->left, indicator);
    }

    return;
}

// TODO make defines later
// TODO add recursive deletion of subtrees

void recursive_remove_trivials (NODE** node, bool* indicator)
{
    assert (node);
    assert (indicator);

    VERIFY_SEGMENT_STATEMENT (node);

    if (!check_for_basic_trivials_statement (NODE_PTR))
    {
        if (NODE_PTR->right)
        {
            recursive_remove_trivials (&(NODE_PTR->right), indicator);
        }
        if (NODE_PTR->left)
        {
            recursive_remove_trivials (&(NODE_PTR->left), indicator);
        }

        return;
    }
    else
    {
        NODE* operationNode = NODE_PTR;
        NODE* objectNode    = NULL;
        NODE* otherNode     = NULL;

        if (NODE_PTR->right->type == OBJECT)
        {
            PARSE_NODES (NODE_PTR->right, NODE_PTR->left);
        }
        else if (NODE_PTR->left->type == OBJECT)
        {
            PARSE_NODES (NODE_PTR->left, NODE_PTR->right);
        }
        else
        {
            return;
        }

        if (trivials_add_zero (operationNode, objectNode))
        {
            NODE_PTR   = otherNode;
            *indicator = false;

            return;
        }
        if (trivials_mul_one (operationNode, objectNode))
        {
            NODE_PTR   = otherNode;
            *indicator = false;

            return;
        }
    }

    return;
}
