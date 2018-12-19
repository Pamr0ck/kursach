#include "structs_and_memory.h"

void need_more_sent_memory(wchar_t **buf  , const size_t* len){
    wchar_t *temp= realloc(*buf, *len*sizeof(wchar_t));
    if (temp){
        *buf=temp;
    }
    else {
        printf("\nAXTUNG\nMem sent error");
    }
}

void need_more_struct_memory(struct Sentence **sent , const size_t* len){
    struct Sentence *temp= realloc(*sent, *len*sizeof(struct Sentence));
    if (temp){
        *sent=temp;
    }
    else {
        printf("\nAXTUNG\nMem error");
    }
}

void goodbuy_world(struct Text *txt){
    for (size_t i=0; i<txt->count_sent;i++){
        free(txt->sentences[i].sent);
    }
    free(txt->sentences);
}




