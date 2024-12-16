#include "differentiator_tree.h"
#include "differentiator.h"
#include "compose_tex.h"
#include "parse_formula.h"

int main (int argc, const char* argv[])
{
    // char input_formula[52] = {};
    FILE* file = NULL;
/*
    if (argc == 1)
    {
        file = fopen("default_tex_dump.tex", "w+");

        printf("Enter function:\n");

        scanf("%s[^\n]", input_formula);
        printf("my sentence %s\n", input_formula);
    }
    else if (argc == 2)
    {
        file = fopen(argv[1], "w+");

        printf("Enter function:\n");

        scanf("%s[^\n]", input_formula);
    }
*/

    file = fopen ("dump.tex", "w+");
    char input_formula[] = "(5 + 3) * 39 * x * cos(x* sin(x^2)) * ln(98)";

/*
    printf("Enter function:\n");
    char input[30] = {};
    scanf("%s", input);

    FILE* input = stdin;

    TEXT_DATA textData = {};
    fill_text(input, &textData);

*/
    TREE tree = {};
    tree_ctor (&tree);
    tree.latex_dump_file = file;

    TREE readTree = {};
    tree_ctor (&readTree);

    FORMULA formula = {};
    formula.buffer   = input_formula;
    formula.index   = 0;

    read_formula (&tree, &formula);

    latex_dump (&tree, tree.root, TEX_START);

    TREE diffTree = {};
    diffTree.latex_dump_file = tree.latex_dump_file;
    tree_ctor (&diffTree);

    dump_tree (&tree);
    diffTree.root = differentiate (&tree, tree.root);

    latex_dump (&diffTree, tree.root, TEX_ANSWER);
    latex_dump (&tree, tree.root, TEX_END);

    // dump_tree (&tree);
    dump_tree (&diffTree);

    return 0;
}
