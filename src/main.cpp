#include "diff_typedefs.h"
#include "diff_tree.h"

#define ADD_(node1, node2) new_node(OPERATION, ADD, node1, node2)
#define SUB_(node1, node2) new_node(OPERATION, SUB, node1, node2)
#define MUL_(node1, node2) new_node(OPERATION, MUL, node1, node2)
#define DIV_(node1, node2) new_node(OPERATION, DIV, node1, node2)
#define NUM_(value)        new_node(OBJECT,    value, NULL, NULL)
#define X_                 new_node(VARIABLE,  0,     NULL, NULL)

int main()
{
    TREE tree = {};
    tree_ctor(&tree);

    // tree.root = new_node(OPERATION, DIV, NULL, NULL);

    // tree.root = new_node(OPERATION, DIV, (new_node(OPERATION, ADD, new_node(VARIABLE, 1, NULL, NULL),
                        // new_node(OBJECT, 3, NULL, NULL)), new_node(OPERATION, SUB, new_node(OBJECT, 1000, NULL, NULL),
                        // new_node(OBJECT, 7, NULL, NULL))));

    tree.root = DIV_(ADD_(X_, NUM_(3)), SUB_(NUM_(1000), NUM_(7)));

    tree_graphic_dump(&tree);

    return 0;
}

/*
    examples
        root = new_node(OP, DIV, (new_node(OP, ADD, new_node(VAR, 1, NULL, NULL), new_node(NUM, 3, NULL, NULL)),
                        new_node(OP, SUB, new_node(OBJECT, 1000, NULL, NULL), new_node(NUM, 7, NULL, NULL))));

        root = DIV_(ADD_(X_, NUM_(3)), SUB_(NUM_(1000), NUM_(7)));

    prefix
        (/(+(X)(3))(-(1000)(7)))

    infix
        (((x) + (3)) / ((1000) - (7)))

    We make new tree while taking derivative
    diff(3) -> 0
    diff(x) -> 1
    diff(root) -> diff(root->right) and diff(root->left)
    copy(subtree)
*/

/*
#define DIV_(node1, node2)    \
    NODE newNode = NULL;      \
    new_node(newNode);  \
    newNode->operation = DIV; \
    newNode->left  = node1;   \
    newNode->right = node2;   \

#define ADD_(node1, node2)    \
    NODE newNode = NULL;      \
    new_node(newNode);  \
    newNode->operation = ADD; \
    newNode->left  = node1    \
    newNode->right = node2    \

#define SUB_(node1, node2)    \
    NODE newNode = NULL;      \
    new_node(newNode);  \
    newNode->operation = SUB; \
    newNode->left  = node1;   \
    newNode->right = node2;   \

#define MUL_(node1, node2)    \
    NODE newNode = NULL;      \
    new_node(newNode);  \
    newNode->operation = MUL; \
    newNode->left  = node1    \
    newNode->right = node2    \

#define NUM_(value)      \
    NODE node = NULL;    \
    new_node(node) \
*/

/*
    tree.root = new_node(OPERATION, DIV, new_node(OPERATION, ADD, new_node(VARIABLE, 1, NULL, NULL),
                                         new_node(OBJECT, 3, NULL, NULL)),
                                         new_node(OPERATION, SUB, new_node(OBJECT, 1000, NULL, NULL),
                                         new_node(OBJECT, 7, NULL, NULL)));
*/
