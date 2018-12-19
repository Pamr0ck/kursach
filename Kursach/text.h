#ifndef KURSACH_TEXT_H
#define KURSACH_TEXT_H

#include "iotext.h"
#include "structs_and_memory.h"

#define NONE   "\033[0m"
#define GREEN   "\033[0;32m"

static size_t third_word_len(const struct Sentence *sent);
int cmp_third_word(const void *a, const void *b);
void sort(struct Text *txt);

void green(struct Text *txt);
void print_green(struct Text *txt);

void del_repeat(struct Text *txt);

int xchange (struct Text *txt);
#endif
