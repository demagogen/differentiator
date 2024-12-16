#ifndef COMPARE_TEX_H_
#define COMPARE_TEX_H_

#include "differentiator.h"

#define LATEX_PRINT(...) fprintf (tree->latex_dump_file, __VA_ARGS__)

const size_t PhrasesQuantity = 20;

const char* const phrases[]
{
    "По-моему, это очев",
    "Сходу видно",
    "Что ни делай, а производную взять надо",
    "Спи моя радость, усни, в доме погасли огни, на улицу вышли они, курево -- матанутые из МФТИ",
    "--БЛять, ебаные производные -- сказал Пекус Пекусович. --Брать, пес! -- сказал лежащий на столе первый том Кудрявцева",
    "Нетрудное следствие, с трудным последствием",
    "Приветствуйте меня и мою производную",
    "По теореме Больцано-Вейерштрасса -- ай, блять стоять! -- по Лейбницу, по Лейбницу!!!",
    "Воспользуемся 52 методом Эдварда Эдвардсона Султанова",
    "Не бери производную, не совершай ошибку",
    "дэ икс по дэ игрек, а дальше сами...",
    "Не смешно, но брать тебе придется вот такое",
    "Человек с хорошим воспитанием обязан знать эту штуку",
    "Советский воробей ловко ручку и фиганет вот такое",
    "Какой будет следующий мув, загадка от кафедры вЫШмата, на размышление дается 5i секунд",
    "Аааааааа, когда уже кончится этот пиздец. Я все выучил, я все выучил. Смотрите, и такое знаю",
    "Че то длинная производная, меня ни к чему длиннее тик-тока со скибидишкой в жизни не готовили",
    "Древние Русы не брали по иксу, они брали по херу",
    "Ща околашматим ящера вышматовского, водой вычислений православной, глянь какая формула",
    "Фантазии больше нет, дальше производные возьмете сами. Свой сборник анекдотов я забыл в НМУ"
};

enum TEX_DUMP_PARAM
{
    TEX_POISON      = -1,
    TEX_NONE        =  0,
    TEX_START       =  1,
    TEX_NODE        =  2,
    TEX_END         =  3,
    TEX_ANSWER      =  4,
    TEX_NODE_FIRST  =  5,
    TEX_NODE_SECOND =  6,
};

// @brief tex dump
// @param name of a file

void latex_dump(TREE* tree, NODE* node, TEX_DUMP_PARAM param);

/// @brief tex dump header print
/// @param pointer on output file

void latex_dump_header(TREE* tree);

/// @brief tex dump end print
/// @param pointer on output file

void latex_dump_end(TREE* tree);

/// @brief print operation in latex file
/// @param pointer on file
/// @param pointer on node

void latex_dump_operation(TREE* tree, NODE* node);

/// @brief tex dump node print
/// @param pointer on output file
/// @param pointer on node

void latex_dump_node(TREE* tree, NODE* node);

/// @brief print number in tex
/// @param pointer on file
/// @param number for print

void latex_dump_object(TREE* tree, NODE* node);

#endif
