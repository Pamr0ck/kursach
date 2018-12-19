#ifndef KURSACH_STRUCTS_AND_MEMORY_H
#define KURSACH_STRUCTS_AND_MEMORY_H

#include <wchar.h>
#include <stdio.h>
#include <stdlib.h>

#define GOODBUE   L"Пока...\n"
#define UPS  L"Упс, неверная команда\n"
#define WHAT_U_WANT                                                                                    \
L" ===============================================================================================\n"\
L"|    1 --- Заменить в каждом предложении первое слово на второе из предыдущего предложения      |\n"\
L"|    2 --- Отсортировать предложения по длине третьего слова                                    |\n"\
L"|    3 --- Вывести на экран предложения, в которых в середине слова встречаются цифры           |\n"\
L"|    4 --- Убрать повторы в словах                                                              |\n"\
L"|    5 --- Вывести текст                                                                        |\n"\
L"|    0 --- Закончить работу                                                                     |\n"\
L" ===============================================================================================\n"

#define SENT 32
#define SIZE 64
#define WORD 48




struct Sentence{
    size_t len;
    wchar_t *sent;
    size_t len_third_word;
    wchar_t flag_color;
    wchar_t * second_word;
    size_t len_without_first_word;
};
struct Text{
    struct Sentence *sentences;
    size_t count_sent;
};


void need_more_struct_memory(struct Sentence **sent , const size_t* len);
void need_more_sent_memory(wchar_t **buf  , const size_t* len);
void goodbuy_world(struct Text *txt);

#endif //KURSACH_STRUCTS_AND_MEMORY_H
