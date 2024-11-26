#include "diff_typedefs.h"
#include "diff_tree.h"

int main()
{
    TREE tree = {};
    tree_ctor(&tree);
    tree_add(&tree, tree.root, ROOT, OBJECT, 59);
    tree_add(&tree, tree.root, RIGHT, OPERATION, ADD);
    tree_add(&tree, tree.root, LEFT, VARIABLE, 2);

    tree_graphic_dump(&tree);

    return 0;
}
