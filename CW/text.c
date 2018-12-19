#include "text.h"

// sort start
static size_t third_word_len(const struct Sentence *sent){
    return sent->len_third_word;
}

int cmp_third_word(const void *a, const void *b){
    size_t a1 = third_word_len(a);
    size_t b1 = third_word_len(b);
    return (a1 != b1) ?(a1 > b1) ? 1 : -1: 0;

};

void sort(struct Text *txt){
    wchar_t* copy;
    wchar_t* word;
    size_t z;
    size_t flag;
    for (size_t i=0; i<txt->count_sent;i++){
        wchar_t *pr=NULL;
        flag=1;
        copy = malloc(sizeof(wchar_t)*txt->sentences[i].len+1);
        wmemcpy(copy,txt->sentences[i].sent,txt->sentences[i].len+1);
        word = wcstok(copy, L" ,", &pr);
        for (z=0;z<2;z++){
            word = wcstok(NULL, L" ,", &pr);
            if (word==NULL){
                flag=0;
            }
        }

        if(flag){
            txt->sentences[i].len_third_word=wcslen(word);
        }

        else{
            txt->sentences[i].len_third_word=0;
        }

    }
    qsort(txt->sentences,txt->count_sent,sizeof(struct Sentence),cmp_third_word);
}

// sort end

//greeen start

void print_green(struct Text *txt){
    setlocale(LC_CTYPE, "");
    wchar_t* word;
    wchar_t sym;
    size_t size=WORD;
    size_t j; // номер символа в строке
    wchar_t green;
    size_t z; // номер символа в слове
    int key;
    for (size_t i=0;i<txt->count_sent;i++){
        if(txt->sentences[i].flag_color){
            word=calloc(WORD, sizeof(wchar_t));
            j=0;
            key=0;
            green=0;
            z=0;
            do{
                sym=txt->sentences[i].sent[j];
                if (green==1){
                    if (sym!=L'.' && sym!=L' ' && sym!=L','){   // не последняя
                        green=2;
                    }
                }
                if(key>=1&&iswdigit(sym)&&green!=2){
                    green=1;
                }

                if(sym==L'.'||sym==L' '||sym==L','){
                    z=0;
                    key=0;
                    if (green==2){
                        wprintf(L"%s%ls%s", GREEN, word, NONE);
                    }
                    else{
                        wprintf(L"%ls",word);
                    }
                    free(word);
                    word=calloc(size, sizeof(wchar_t));
                    green=0;
                    wprintf(L"%c",sym);
                    j++;
                    continue;
                }

                else {
                    if (sym != L'.' && sym != L' ' && sym != L',') {
                        word[z] = sym;
                        key++;
                        z++;
                        if (z == size) {
                            size += WORD;
                            wchar_t *temp = realloc(word, size * sizeof(wchar_t));
                            if (temp) {
                                word = temp;
                            }
                            else {
                                printf("\nAXTUNG\nMem sent error");
                            }

                        }

                    }
                }
                j++;


            }while(sym!=L'.');
            wprintf(L"\n");
        }

    }
}


void green(struct Text *txt){
    wchar_t* copy;
    wchar_t* word;
    wchar_t stop;
    wchar_t* pt;
    for (size_t i=0;i<txt->count_sent;i++){
        copy = malloc(sizeof(wchar_t)*txt->sentences[i].len+1);
        wmemcpy(copy,txt->sentences[i].sent,txt->sentences[i].len+1);
        pt=NULL;
        txt->sentences[i].flag_color=0;
        word=wcstok(copy, L" ,.",&pt);
        stop=0;
        if (word == NULL) {
            continue;
        }
        if (wcslen(word)>=3){
            for (size_t j=1;j<wcslen(word)-1;j++) {
                if (iswdigit(word[j]) != 0) {
                    txt->sentences[i].flag_color = 1;
                    stop = 1;
                    break;
                }
            }
        }
        while(word!=NULL&&stop!=1){
            word=wcstok(NULL, L" ,.",&pt);
            if (word == NULL) {
                break;
            }
            if(wcslen(word)>=3) {
                for (size_t j = 1; j < wcslen(word) - 1; j++) {
                    if (iswdigit(word[j]) != 0) {
                        txt->sentences[i].flag_color = 1;
                        stop = 1;
                        break;
                    }
                }
            }
        }
        free(copy); // mb bag

    }
    print_green(txt);
}

//green end

void del_repeat(struct Text *txt){
    wchar_t* copy;
    size_t len;
    wchar_t sym;
    size_t k;
    for (size_t i=0; i<txt->count_sent;i++){
        k=0;
        copy = malloc(sizeof(wchar_t)*txt->sentences[i].len+1);
        len=wcslen(txt->sentences[i].sent);
        sym=txt->sentences[i].sent[0];
        copy[0]=sym;
        for (size_t j=1; j<len;j++){
            sym=txt->sentences[i].sent[j];
            if (sym!=copy[k]){
                k++;
                copy[k]=sym;
            }

        }
        k++;
        copy[k]=L'\0';
        txt->sentences[i].len=k;
        wmemcpy(txt->sentences[i].sent,copy,txt->sentences[i].len+1);
        free(copy);
    }
}

int xchange (struct Text *txt){
    size_t last=txt->count_sent;
    wchar_t* copy_sent;
    wchar_t* word;
    wchar_t* copy;
    wchar_t* tmp;
    size_t len;
    size_t len_first_word;
    wchar_t* pr;
    size_t tmp_size;
    for (size_t i=0;i<last;i++){
        copy_sent = malloc(sizeof(wchar_t)*(txt->sentences[i].len+1));
        wcscpy(copy_sent,txt->sentences[i].sent);
        pr=NULL;

        word = wcstok(copy_sent, L" ,", &pr);
        len=wcslen(word);
        txt->sentences[i].len_without_first_word=txt->sentences[i].len-len;
        word = wcstok(NULL, L" ,.", &pr);
        if (word==NULL){
            wprintf(L"BAD, SENT #%zu HAS LESS THEN 2 WORDS. TRY AGAIN!\n", i+1);
            free(copy_sent);
            return 0;
        }
        len=wcslen(word);
        txt->sentences[i].second_word=malloc((len+1)*sizeof(wchar_t));
        wcscpy(txt->sentences[i].second_word,word);
        free(copy_sent);

    }
    size_t pred;
    for (size_t i=0;i<last;i++){
        if(i>0) pred=i-1;
        else pred= last-1;
        len_first_word=wcslen(txt->sentences[pred].second_word);
        copy=malloc((len_first_word+txt->sentences[i].len_without_first_word+1)*sizeof(wchar_t));
        wcscpy(copy,txt->sentences[pred].second_word);
        wcscpy(copy+len_first_word,txt->sentences[i].sent+txt->sentences[i].len-txt->sentences[i].len_without_first_word);
        copy[wcslen(copy)]=L'\0';//
        free(txt->sentences[i].sent);
        txt->sentences[i].sent=calloc(wcslen(copy)+1,sizeof(wchar_t));
        wcscpy(txt->sentences[i].sent,copy);
        txt->sentences[i].len=wcslen(copy);
        txt->sentences[i].sent[wcslen(txt->sentences[i].sent)]=L'\0';
        free(copy);
    }
    for (size_t i=0;i<last;i++){
        free(txt->sentences[i].second_word);
    }
    return 1;
}
