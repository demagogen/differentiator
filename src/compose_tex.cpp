#include "differentiator_utils.h"
#include "compose_tex.h"

// TODO rename file

#define NUMBER_FORMAT "%.2lf"
#define NUMBER_FORMAT_WITH_BRACKETS "(%.2lf)"
#define NUMBER_INTEGER_FORMAT "%d"

#define LATEX_PRINT(...) fprintf (tree->latex_dump_file, __VA_ARGS__)

void latex_dump (TREE* tree, NODE* node, TEX_DUMP_PARAM param)
{
    assert (node);

    if (param == TEX_START)
    {
        latex_dump_header (tree);
        LATEX_PRINT       ("$$f(x) = ");
        latex_dump_node   (tree, tree->root);
        LATEX_PRINT       ("$$\\newline\n");

        bool detector = true;
        optimization(tree->root, &detector);

        if (!detector)
        {
            LATEX_PRINT     ("\n\\text{Ебало проще делай}\n");
            LATEX_PRINT     ("$$f(x) = ");
            latex_dump_node (tree, tree->root);
            LATEX_PRINT     ("$$\\newline\n");
        }
    }
    else if (param == TEX_END)
    {
        latex_dump_end (tree);

        fclose (tree->latex_dump_file);
        tree->latex_dump_file = NULL;
    }
    else if (param == TEX_NODE)
    {
        LATEX_PRINT ("\\section{%s}", "Работаем");
        LATEX_PRINT ("\\begin{center}");
        LATEX_PRINT ("\\text{%s}", random_phrase());
        LATEX_PRINT ("\n$$");

        latex_dump_node (tree, node);

        LATEX_PRINT ("$$ \\end{center}\\  \\newline \n");
        LATEX_PRINT ("\\subsection{Порешение}\\ \\newline");
    }
    else if (param == TEX_NODE_FIRST)
    {
        LATEX_PRINT ("\\section{%s}", "Работаем");
        LATEX_PRINT ("\\begin{center}");
        LATEX_PRINT ("\\text{%s}", random_phrase());
        LATEX_PRINT ("\n$$\\left(");

        latex_dump_node (tree, node);

        LATEX_PRINT ("\\right)^\\prime = ");
    }
    else if (param == TEX_NODE_SECOND)
    {
        latex_dump_node (tree, node);
        LATEX_PRINT     ("$$ \\end{center} \\newline \n");
        LATEX_PRINT     ("\\subsection{Порешение}\\ \\newline");
    }
    else if (param == TEX_ANSWER)
    {
        LATEX_PRINT ("\\subsection{Ответус}");
        LATEX_PRINT ("%s\n", "Сюдаааа"
                     "\\begin{center}"
                     "\n$$f(x)^\\prime =",
                     "ГООООООООЛ");

        latex_dump_node (tree, tree->root);

        LATEX_PRINT ("$$\\end{center}\\ \n");
    }
}

void latex_dump_header(TREE* tree)
{
    LATEX_PRINT ( "\\documentclass[a4paper 12pt]{article}\n"
                  "\\usepackage{wrapfig}\n"
                  "\\usepackage{mathtext}\n"
                  "\\usepackage{amsmath}\n"
                  "\\usepackage{rotating}\n"
                  "\\usepackage{float}\n"
                  "\\usepackage[T1,T2A]{fontenc}\n"
                  "\\usepackage[russian]{babel}\n"
                  "\\usepackage{amsfonts}\n"
                  "\\usepackage[a4paper,left=20mm,right=15mm,top=15mm,bottom=15mm]{geometry} % устанавливает поля документа\n"
                  "\\title{\n"
                  "\\begin{center}\n"
                  "\\underline{Отчет о выполнении бабки лабки 52}\n"
                  "\\end{center}}\n"
                  "\\author{Коренной Роман \\(о боже, как он хорош\\). Б01-411}\n"
                  "\\date{хз какого декабря 2024 года}\n"
                  "\\begin{document}\n"
                  "\\pagenumbering{gobble}\n"
                  "\\maketitle\n"
                  "\\pagenumbering{arabic}\n"
                  "\\textbf{Цель работы:} исследовать явление производненского диссонанса в тонком мозгу учащегося;\n"
                  "измерить скорость распространения матерных слов в кабинете во время контрольной\n"
                  "из различных материалов и различных размеров; измерить скорость охмеления при различных примерах.\\\\\n"
                  "\\hfill\n"
                  "\\textbf{В работе используются:}\n"
                  "генератор кринжокода (Рома), профессиональный пидорас (Максим Тимошкин), примеросочинитель (Дед),\n"
                  "лучший друг студоса, мрущего от энергоса (тазик) и идол, символ веры в лучшее и любительница молочка (Полторашка)"
                  ", набор рюмок и водка \"Птичка Синичка\"\n"
                  "\\subsection{Выражение}\n");
}

void latex_dump_end (TREE* tree)
{
    assert (tree->latex_dump_file);

    fprintf (tree->latex_dump_file, "\n\\end{document}\n");
}

void latex_dump_node (TREE* tree, NODE* node)
{
    assert (tree->latex_dump_file);
    assert (node);

    if (!node)
    {
        return;
    }

    switch (node->type)
    {
        case (VARIABLE):
        {
            LATEX_PRINT ("x");
            break;
        }
        case (OBJECT):
        {
            latex_dump_object (tree, node);
            break;
        }
        case (OPERATION):
        {
            latex_dump_operation (tree, node);
            break;
        }
        default:
        {
            printf ("erroren pidorasen\n");
            break;
        }
    }
}

#define CHECK_SON_ON_OPERATION(check_node, bracket)                                                   \
    if (check_node)                                                                                  \
    {                                                                                                \
        if (check_node->type == OPERATION &&                                                         \
           (return_operation_code (check_node) == ADD || return_operation_code (check_node) == SUB)) \
        {                                                                                            \
            fprintf(tree->latex_dump_file, bracket);                                                        \
        }                                                                                            \
    }

void latex_dump_operation (TREE* tree, NODE* node)
{
    assert (tree->latex_dump_file);
    assert (node);

    switch (return_operation_code (node))
    {
        case (ADD):
            latex_dump_node (tree, node->left);
            fprintf         (tree->latex_dump_file, " + ");
            latex_dump_node (tree, node->right);
            break;

        case (MUL):
            if (node->left->type == OBJECT && node->right->type == OBJECT)
            {
                latex_dump_node (tree, node->left);
                fprintf         (tree->latex_dump_file, " \\cdot ");
                latex_dump_node (tree, node->right);
            }
            else
            {
                CHECK_SON_ON_OPERATION (node->left, "(");
                latex_dump_node        (tree, node->left);
                CHECK_SON_ON_OPERATION (node->left, ")");

                CHECK_SON_ON_OPERATION (node->right, "(");
                latex_dump_node        (tree, node->right);
                CHECK_SON_ON_OPERATION (node->right, ")");
            }
            break;

        case (DIV):
            fprintf         (tree->latex_dump_file, "\\cfrac{");
            latex_dump_node (tree, node->left);
            fprintf         (tree->latex_dump_file, "}{");
            latex_dump_node (tree, node->right);
            fprintf         (tree->latex_dump_file, "}");
            break;

        case (SIN):
            fprintf         (tree->latex_dump_file, "\\sin\\left(");
            latex_dump_node (tree, node->left);
            fprintf         (tree->latex_dump_file, "\\right)");
            break;

        case (COS):
            fprintf         (tree->latex_dump_file, "\\cos\\left(");
            latex_dump_node (tree, node->left);
            fprintf         (tree->latex_dump_file, "\\right)");
            break;

        case (POW):
            if (node->left->type == OPERATION)
            {
                fprintf         (tree->latex_dump_file, "\\left(");
                latex_dump_node (tree, node->left);
                fprintf         (tree->latex_dump_file, "\\right)^{");
                latex_dump_node (tree, node->right);
                fprintf         (tree->latex_dump_file, "}");
                break;
            }
            else if (node->left->type == VARIABLE)
            {
                fprintf         (tree->latex_dump_file, "x^{");
                latex_dump_node (tree, node->right);
                fprintf         (tree->latex_dump_file, "}");
                break;
            }
            else
            {
                fprintf         (tree->latex_dump_file, "^{");
                latex_dump_node (tree, node->right);
                fprintf         (tree->latex_dump_file, "}");
                break;
            }
        case (LN):
            fprintf         (tree->latex_dump_file, "\\ln\\left(");
            latex_dump_node (tree, node->left);
            fprintf         (tree->latex_dump_file, "\\right)");
            break;

        default:
            printf ("default in operations: %d\n", return_operation_code(node));
            break;
    }
}

#define IF_NEGATIVE_START if (compare_values (node->data, 0) == LESS) fprintf (tree->latex_dump_file, "(");
#define IF_NEGATIVE_END if (compare_values (node->data, 0) == LESS) fprintf (tree->latex_dump_file, ")");

#define NEED_BRACKETS_CHECK(bracket)                                                       \
    if (PARENT)                                                                           \
    {                                                                                     \
        if (DED)                                                                          \
        {                                                                                 \
            if (DED->type == OPERATION &&                                                 \
               (return_operation_code (DED) == MUL || return_operation_code (DED) == DIV) \
            {                                                                             \
                fprintf(file, bracket);                                                    \
            }                                                                             \
        }                                                                                 \
    }


void latex_dump_object (TREE* tree, NODE* node)
{
    IF_NEGATIVE_START;

    if (node->parent)
    {
        if (node->parent->type == OPERATION && compare_values (node->data, (int)node->data) == EQUAL)
        {
            fprintf (tree->latex_dump_file, NUMBER_INTEGER_FORMAT, (int)node->data);
        }
        else
        {
            fprintf (tree->latex_dump_file, NUMBER_FORMAT, node->data);
        }
    }
    else
    {
        if (compare_values (node->data, (int)node->data) == EQUAL)
        {
            fprintf (tree->latex_dump_file, NUMBER_INTEGER_FORMAT, (int)node->data);
        }
        else
        {
            fprintf (tree->latex_dump_file, NUMBER_FORMAT, node->data);
        }
    }

    IF_NEGATIVE_END;
}
