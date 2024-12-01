#include "diff_tree.h"
#include "diff_tree_utils.h"
#include "../lib/kalatushkin/text_data.h"

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
    }
    if (left)
    {
        left->parent = newNode;
    }

    newNode->left  = left;
    newNode->right = right;

    newNode->type = type;

    return newNode;
}


TREE_ERROR tree_node_dtor(NODE* node)
{
    assert(node);

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
#define PRINT_DATA_BY_TYPE(type, data)                    \
    if (type == OPERATION)                                \
    {                                                     \
        fprintf(file, "%s", return_operation_enum(data)); \
    }                                                     \
    else if (type == VARIABLE)                            \
    {                                                     \
        fprintf(file, "x");                               \
    }                                                     \
    else if (type == OBJECT)                              \
    {                                                     \
        fprintf(file, "%.0lf", data);                     \
    }                                                     \
    else                                                  \
    {                                                     \
        return TREE_NODE_TYPE_ERROR;                      \
    }                                                     \

TREE_ERROR prefix_print(FILE* file, NODE* node)
{
    assert(file);

    if (!node)
    {
        return TREE_NODE_ALLOCATION_ERROR;
    }

    fprintf(file, "(");

    PRINT_DATA_BY_TYPE(node->type, node->data);

    if (node->left)
    {
        prefix_print(file, node->left);
    }
    if (node->right)
    {
        prefix_print(file, node->right);
    }

    fprintf(file, ")");

    return TREE_NONE;
}

TREE_ERROR infix_print(FILE* file, NODE* node)
{
    assert(file);

    if (!node)
    {
        return TREE_NODE_ALLOCATION_ERROR;
    }

    fprintf(file, "(");

    if (node->left)
    {
        infix_print(file, node->left);
    }

    PRINT_DATA_BY_TYPE(node->type, node->data);

    if (node->right)
    {
        infix_print(file, node->right);
    }

    fprintf(file, ")");

    return TREE_NONE;
}

TREE_ERROR bad_tex_print(FILE* file, NODE* node)
{
    assert(file);

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
                fprintf(file, "(");
            }
            else if (div_brackets_counter % 2 == 1)
            {
                fprintf(file, ")");
            }

            div_brackets_counter++;
        }
    }

    if (node->left)
    {
        bad_tex_print(file, node->left);
    }

    PRINT_DATA_BY_TYPE(node->type, node->data);

    if (node->right)
    {
        bad_tex_print(file, node->right);
    }

    return TREE_NONE;
}

const char* s = "24*2+30*4+(23-21)*1000$";
int         p = 0;

NODE* get_g()
{
    NODE* val = get_e();

    if (s[p] != '$')
    {
        syntax_error();
    }

    return val;
}

NODE* get_n()
{
    int val = 0;

    int old_p = p;
    while ('0' <= s[p] && s[p] <= '9')
    {
        val = val * 10 + s[p] - '0';
        p++;
    }

    if (old_p != p)
    {
        syntax_error();
    }

    return NUM_(val);
}

NODE* get_e()
{
    NODE* val = get_t();

    while (s[p] == '+' || s[p] == '-')
    {
        int op = s[p];
        p++;
        NODE* val2 = get_t();

        if (op == '+')
        {
            val->data += val2->data;
        }
        else
        {
            val->data -= val2->data;
        }
    }

    return val;
}

NODE* get_t()
{
    NODE* val = get_p();

    while (s[p] == '*' || s[p] == '/')
    {
        int op = s[p];
        p++;
        NODE* val2 = get_p();

        if (op == '*')
        {
            val->data *= val2->data;
        }
        else
        {
            val->data /= val2->data;
        }
    }

    return val;
}

NODE* get_p()
{
    if (s[p] == '(')
    {
        p++;
        NODE* val = get_e();

        if (s[p] != ')')
        {
            syntax_error();
        }
        p++;

        return val;
    }
    else
    {
        return get_n();
    }

    return syntax_error();
}

NODE* syntax_error()
{
    return NULL;
}

void tree_graphic_dump(TREE* tree)
{
    assert(tree);

    FILE* dotfile = fopen("dotfile.gv", "wb");

    fprintf(dotfile, "digraph {bgcolor=\"#696969\" rankdir = TB\n");

    fprintf(dotfile, "Info[shape=Mrecord, "
                     "style=filled, "
                     "fillcolor=\"grey\", "
                     "label=\"capacity: %d\", "
                     "fontcolor = \"black\", "
                     "fontsize = 14];\n\n ",
                      tree->capacity);

    size_t index = 0;
    node_graphic_dump(dotfile, &index, tree->root);

    fprintf(dotfile, "\n}");

    fclose(dotfile);
}

void node_graphic_dump (FILE* dotfile, size_t* index, NODE* node)
{
    assert(dotfile);

    if (!node) return;

    node_print_node(dotfile, index, node);

    size_t current_node_index = *index;

    if (node->left)
    {
        node_print_edge(dotfile, current_node_index, ++(*index), node->left);
        node_graphic_dump(dotfile, index, node->left);
    }
    if (node->right)
    {
        node_print_edge(dotfile, current_node_index, ++(*index), node->right);
        node_graphic_dump(dotfile, index, node->right);
    }
    else
    {
        return;
    }
}

void node_print_node (FILE* dotfile, size_t* index, NODE* node)
{
    assert(node);
    assert(dotfile);

    char node_color[12] = {};
    switch(node->type)
    {
        case(OBJECT   ):
        {
            strcpy(node_color, "firebrick1");
            break;
        }
        case(OPERATION):
        {
            strcpy(node_color, "deepskyblue");
            break;
        }
        case(VARIABLE ):
        {
            strcpy(node_color, "grey");
            break;
        }

        default:
        {
            return;
        }
    }

    fprintf(dotfile, "node%d[shape=Mrecord, "
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
                     node->side,
                     node->parent,
                     node->left,
                     node->right);

    switch(node->type)
    {
        case(OBJECT   ):
        {
            fprintf(dotfile, "| data: %lf}\"];\n\n", node->data);
            break;
        }
        case(OPERATION):
        {
            fprintf(dotfile, "| data: %s}\"];\n\n", return_operation_enum(node->data));
            break;
        }
        case(VARIABLE ):
        {
            fprintf(dotfile, "| data: %s}\"];\n\n", "x");
            break;
        }

        default: { return; }
    }
}

void node_print_edge(FILE* dotfile, size_t first_node_index, size_t second_node_index, NODE* node)
{
    assert(dotfile);
    assert(node);

    fprintf(dotfile, "node%d->node%d "
                     "[color = \"grey\"];\n ",
                      first_node_index,
                      second_node_index);
}
