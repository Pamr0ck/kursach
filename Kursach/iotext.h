#ifndef KURSACH_IOTEXT_H
#define KURSACH_IOTEXT_H

#include "structs_and_memory.h"
#include <locale.h>
#include <wctype.h>

size_t get_text(struct Text *txt);
void output_text(struct Text *txt);
int menu();

#endif
