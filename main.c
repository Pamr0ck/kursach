#include <stdio.h>
#include <wchar.h>
#include <string.h>
#include <stdlib.h>
#include <wctype.h>
#include <locale.h>
#include <ctype.h>
#define SENT 32
#define SIZE 64


struct Sentence{
    size_t len;
    wchar_t *sent;
};
struct Text{
    struct Sentence *sentences;
    size_t count_sent;
};

void need_more_sent_memory(wchar_t **buf  , size_t* len){
    wchar_t *temp= realloc(*buf, *len*sizeof(wchar_t));
    if (temp){
        *buf=temp;
    }
    else {
        printf("\nAXTUNG\nMem sent error");
    }
}

void need_more_struct_memory(struct Sentence **sent , size_t* len){
    struct Sentence *temp= realloc(*sent, *len*sizeof(struct Sentence));
    if (temp){
        *sent=temp;
    }
    else {
        printf("\nAXTUNG\nMem error");
    }
}

// ввод из файла
// увеличение памяти +
// ноль символ +
// символ конца файла если из файла
int get_text(struct Text *txt){
    setlocale(LC_CTYPE, "");
    size_t count=0;
    size_t i=0;
    wchar_t sym;
    txt->sentences=malloc(SIZE*sizeof(struct Sentence));
    size_t struct_size=SENT;
    do{
        txt->sentences[count].sent=(wchar_t*)malloc(SIZE*sizeof(wchar_t));
        size_t size= SIZE;
        do{
            sym=getwchar();
        }while(iswblank(sym));
        if (sym==L'.'){
            txt->sentences[count].sent[i]=sym;
            i++;
            txt->sentences[count].sent[i]=L'\0';
            txt->sentences[count].len=i;
            count++;
            if (count== struct_size){
                struct_size+=SENT;
                need_more_struct_memory(&txt->sentences,&struct_size);
            }
            i=0;
            continue;
        }
        if(sym==L'\n'){
            break;
        }
        do{
            txt->sentences[count].sent[i]=sym;
            i++;
            if (i==size){
                size+=SIZE;
                need_more_sent_memory(&txt->sentences[count].sent,&size);
            }
            sym=getwchar();
        }while(sym!=L'.');
        size+=5;
        txt->sentences[count].sent = realloc(txt->sentences[count].sent, size * sizeof(wchar_t));
        txt->sentences[count].sent[i]=sym;
        i++;
        txt->sentences[count].sent[i]=L'\0';
        txt->sentences[count].len=i;
        count++;
        if (count== struct_size){
            struct_size+=SENT;
            need_more_struct_memory(&txt->sentences,&struct_size);
        }
        i=0;
    }while (sym!=L'\n');
    return count;
}

void output_text(struct Text *txt){
    setlocale(LC_CTYPE, "");
    for (size_t i=0; i<txt->count_sent;i++){
        wprintf(L"%ls [%ld]\n",txt->sentences[i].sent,txt->sentences[i].len);
    }

};

// GOVNO PROGRAMA!!!!!!!!!!!!
// если null -free
//сначала перезапись
// realloc предыдущего
void del_same_sent(struct Text *txt){
    size_t count=txt->count_sent;
    for (size_t i=0;i<txt->count_sent;i++){
        for (size_t j=i+1; j<txt->count_sent;j++){// mb bag
            if (txt->sentences[i].len==txt->sentences[j].len) {
                if (wcscmp(txt->sentences[i].sent, txt->sentences[j].sent) == 0) {
                    //free(txt->sentences[j].sent);
                    txt->sentences[j].sent = NULL;
                    txt->sentences[j].len = 0;
                    txt->count_sent--;

                }
            }
        }
    }
    for(size_t i=0;i<count;){
        if (txt->sentences[count].sent != NULL){
            memmove(txt->sentences+i,txt->sentences+i+1,(count-i) * sizeof(struct Sentence));
            txt->count_sent--;
            i--;
        }
        i++;
    }
    struct Sentence *temp = realloc(txt->sentences, txt->count_sent * sizeof(struct Sentence));
    if (temp!=NULL){
        txt->sentences = temp;
    }
    else{
        printf("\nAbating\nMem error");
    }

};

int main(){
    struct Text txt;
    setlocale(LC_CTYPE, "");
    size_t count;
    count=get_text(&txt);
    if (count == -1){
        return 1;
    }
    txt.count_sent=count;
    //del_same_sent(&txt);
    output_text(&txt);
    wprintf(L"EWRIKA\nthis is working\n");
    return 0;
}