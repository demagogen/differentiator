#include "differentiator_tree.h"
#include "differentiator_utils.h"

// TODO tree verfification`m

TREE_ERROR tree_ctor(TREE* tree)
{
    assert(tree);

    tree->capacity = StartTreeCapacity;
    tree->root     = NULL;
    tree->error    = TREE_NONE;

    return tree->error;
}

TREE_ERROR tree_dtor(TREE* tree)
{
    assert(tree);

    tree->capacity = TREE_POISON;

    tree->root->left   = NULL;
    tree->root->right  = NULL;
    tree->root->parent = NULL;

    tree->error = TREE_DED_INSIDE;

    return tree->error;
}

NODE* new_node(NODE_ELEMENT_TYPE type, NodeData_t data, NODE* left, NODE* right)
{
    NODE* newNode = (NODE* ) calloc(1, sizeof(NODE));

    newNode->data     = data;

    newNode->parent   = NULL;

    if (right)
    {
        right->parent = newNode;
        right->rule   = RIGHT;
    }
    if (left)
    {
        left->parent  = newNode;
        left->rule    = LEFT;
    }

    newNode->left  = left;
    newNode->right = right;

    newNode->type = type;

    return newNode;
}

TREE_ERROR relink_node(NODE* oldNode, NODE* newNode)
{
    assert(oldNode);
    assert(newNode);

    newNode->parent = oldNode->parent;

    oldNode->parent = NULL;
    oldNode->left   = NULL;
    oldNode->right  = NULL;
    oldNode->type   = TYPE_POISON;
    oldNode->data   = POISON;

    return TREE_NONE;
}

NODE* copy_node(NODE* node)
{
    assert(node);

    if (!node)
    {
        return NULL;
    }

    NODE* copyNode = new_node(node->type, node->data, node->left, node->right);

    if (node->left)
    {
        copy_node(node->left);
    }
    if (node->right)
    {
        copy_node(node->right);
    }

    return copyNode;
}

TREE_ERROR node_dtor (NODE* node)
{
    assert (node);

    if (!node)
    {
        return TREE_NODE_ALLOCATION_ERROR;
    }

    node->right   = NULL;
    node->left    = NULL;
    node->parent  = NULL;
    node->data    = TREE_POISON;

    return TREE_NONE;
}
// need (((x)+(3))/((1000)-(7)))

// TODO debug variation with .2 in fprintf
#define PRINT_DATA_BY_TYPE(type, data)                      \
    if (type == OPERATION)                                 \
    {                                                      \
        fprintf (file, "%s", return_operation_string (data)); \
    }                                                      \
    else if (type == VARIABLE)                             \
    {                                                      \
        fprintf (file, "x");                                \
    }                                                      \
    else if (type == OBJECT)                               \
    {                                                      \
        fprintf (file, "%.0lf", data);                      \
    }                                                      \
    else                                                   \
    {                                                      \
        return TREE_NODE_TYPE_ERROR;                       \
    }

TREE_ERROR prefix_print (FILE* file, NODE* node)
{
    assert (file);
    assert (node);

    if (!node)
    {
        return TREE_NODE_ALLOCATION_ERROR;
    }

    fprintf (file, "(");

    PRINT_DATA_BY_TYPE (node->type, node->data);

    if (node->left)
    {
        prefix_print (file, node->left);
    }
    if (node->right)
    {
        prefix_print (file, node->right);
    }

    fprintf (file, ")");

    return TREE_NONE;
}

TREE_ERROR infix_print (FILE* file, NODE* node)
{
    assert (file);
    assert (node);

    if (!node)
    {
        return TREE_NODE_ALLOCATION_ERROR;
    }

    fprintf (file, "(");

    if (node->left)
    {
        infix_print (file, node->left);
    }

    PRINT_DATA_BY_TYPE (node->type, node->data);

    if (node->right)
    {
        infix_print (file, node->right);
    }

    fprintf (file, ")");

    return TREE_NONE;
}

TREE_ERROR bad_tex_print(FILE* file, NODE* node)
{
    assert (file);
    assert (node);

    if (!node)
    {
        return TREE_NODE_ALLOCATION_ERROR;
    }

    static size_t div_brackets_counter = 0;

/*
Here I think about how to make TeX like formula format
*/

    if (node->parent)
    {
        if (node->parent->type == OPERATION && (OPERATIONS) node->parent->data == DIV)
        {
            if (div_brackets_counter % 2 == 0)
            {
                fprintf (file, "(");
            }
            else if (div_brackets_counter % 2 == 1)
            {
                fprintf (file, ")");
            }

            div_brackets_counter++;
        }
    }

    if (node->left)
    {
        bad_tex_print (file, node->left);
    }

    PRINT_DATA_BY_TYPE (node->type, node->data);

    if (node->right)
    {
        bad_tex_print (file, node->right);
    }

    return TREE_NONE;
}

void dump_tree (TREE* tree)
{
    assert (tree);

    FILE* dotfile = fopen ("dotfile.gv", "wb");

    fprintf (dotfile, "digraph {bgcolor=\"#696969\" rankdir = TB\n");

    fprintf (dotfile, "Info[shape=Mrecord, "
                      "style=filled, "
                      "fillcolor=\"grey\", "
                      "label=\"capacity: %d\", "
                      "fontcolor = \"black\", "
                      "fontsize = 14];\n\n ",
                       tree->capacity);

    size_t index = 0;
    dump_all_nodes (dotfile, &index, tree->root);

    fprintf (dotfile, "\n}");

    fclose (dotfile);
}

void dump_all_nodes (FILE* dotfile, size_t* index, NODE* node)
{
    assert (dotfile);

    if (!node) return;

    dump_node_vertex (dotfile, index, node);

    size_t current_node_index = *index;

    if (node->left)
    {
        dump_node_edge (dotfile, current_node_index, ++(*index), node->left);
        dump_all_nodes (dotfile, index, node->left);
    }
    if (node->right)
    {
        dump_node_edge (dotfile, current_node_index, ++(*index), node->right);
        dump_all_nodes (dotfile, index, node->right);
    }
    else
    {
        return;
    }
}

void dump_node_vertex (FILE* dotfile, size_t* index, NODE* node)
{
    assert (node);
    assert (dotfile);

    char node_color[12] = {};
    switch (node->type)
    {
        case (OBJECT):
            strcpy (node_color, "firebrick1");
            break;

        case (OPERATION):
            strcpy (node_color, "deepskyblue");
            break;

        case (VARIABLE):
            strcpy (node_color, "grey");
            break;

        default:
            return;
    }

    fprintf (dotfile, "node%d[shape=Mrecord, "
                     "style=filled, "
                     "fillcolor=\"%s\", "
                     "label=\" "
                     "{address: %p "
                     "| type:   %d "
                     "| parent: %p "
                     "| left:   %p "
                     "| right:  %p ",
                     *index,
                     node_color,
                     node,
                     node->rule,
                     node->parent,
                     node->left,
                     node->right);

    switch (node->type)
    {
        case (OBJECT):
            fprintf (dotfile, "| data: %lf}\"];\n\n", node->data);
            break;

        case (OPERATION):
            fprintf (dotfile, "| data: %s}\"];\n\n", return_operation_string(node->data));
            break;

        case (VARIABLE):
            fprintf (dotfile, "| data: %s}\"];\n\n", "x");
            break;

        default: return;
    }
}

void dump_node_edge (FILE* dotfile, size_t first_node_index, size_t second_node_index, NODE* node)
{
    assert (dotfile);
    assert (node);

    char edge_color[EdgeColorStringSize] = {};

    switch (node->rule)
    {
        case (LEFT):
            strcpy (edge_color, "olivedrab1");
            break;

        case (RIGHT):
            strcpy (edge_color, "orchid1");
            break;

        default:
            strcpy (edge_color, "black");
            break;
    }

    fprintf (dotfile, "node%d->node%d "
                     "[color = \"%s\"];\n ",
                      first_node_index,
                      second_node_index,
                      edge_color);
}
