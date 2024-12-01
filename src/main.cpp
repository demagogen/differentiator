#include "diff_tree.h"

int main()
{
    TREE tree = {};
    tree_ctor(&tree);

    // tree.root = new_node(OPERATION, DIV, NULL, NULL);

    tree.root = DIV_(ADD_(MUL_(NUM_(7), X_), NUM_(3)), SUB_(NUM_(1000), NUM_(7)));

    // prefix_print(stdout, tree.root);
    // printf("\n\n");
    // infix_print(stdout, tree.root);
    // printf("\n\n");
    // bad_tex_print(stdout, tree.root);
    // printf("\n\n");

    // tree.root = get_g();
    // NodeData_t result = tree.root->data;


    tree.root = get_g();

    tree_graphic_dump(&tree);

    return 0;
}

/*
    examples
        root = new_node(OP, DIV, (new_node(OP, ADD, new_node(VAR, 1, NULL, NULL), new_node(NUM, 3, NULL, NULL)),
                        new_node(OP, SUB, new_node(OBJECT, 1000, NULL, NULL), new_node(NUM, 7, NULL, NULL))));

        root = DIV_(ADD_(X_, NUM_(3)), SUB_(NUM_(1000), NUM_(7)));

    prefix
        (/(+(x)(3))(-(1000)(7)))

    infix
        (((x) + (3)) / ((1000) - (7)))

    We make new tree while taking derivative
    diff(3) -> 0
    diff(x) -> 1
    diff(root) -> diff(root->right) and diff(root->left)
    copy(subtree)
*/

    // tree.root = new_node(OPERATION, DIV, (new_node(OPERATION, ADD, new_node(VARIABLE, 1, NULL, NULL),
                        // new_node(OBJECT, 3, NULL, NULL)), new_node(OPERATION, SUB, new_node(OBJECT, 1000, NULL, NULL),
                        // new_node(OBJECT, 7, NULL, NULL))));
