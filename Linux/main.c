// debag green
// one func left
// main c возможностью выхода
// cmake
//otchet
#include <wctype.h>
#include <wchar.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <locale.h>
#include <ctype.h>

#define NONE   "\033[0m"
#define GREEN   "\033[0;32m"


#define SENT 32
#define SIZE 64
#define WORD 16

struct Sentence{
    size_t len;
    wchar_t *sent;
    size_t len_third_word;
    wchar_t flag;
    wchar_t* sum;           //delete       3d word
    wchar_t * second_word;
    size_t len_without_first_word;
};
struct Text{
    struct Sentence *sentences;
    size_t count_sent;
};

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

// увеличение памяти +
// ноль символ +

// символ конца файла если из файла
// ввод из файла

//delete
size_t get_text(struct Text *txt){
    setlocale(LC_CTYPE, "");
    size_t count=0;
    size_t i;
    char flag;
    wchar_t sym;
    txt->sentences=malloc(SIZE*sizeof(struct Sentence));
    size_t struct_size=SENT;
    do{
        i=0;
        flag=0;
        txt->sentences[count].sent=(wchar_t*)malloc(SIZE*sizeof(wchar_t));
        txt->sentences[count].sum=(wchar_t*)malloc(SIZE*sizeof(wchar_t));              // delete
        size_t size= SIZE;
        do{
            sym=getwchar();
        }while(iswblank(sym));
        if (sym==L'.'){
            txt->sentences[count].sent[i]=sym;
            i++;
            txt->sentences[count].sent[i]=L'\0';
            txt->sentences[count].len=i;
            //i=0;

            for (size_t j=0;j<count;j++){
                if (txt->sentences[j].len==txt->sentences[count].len) {
                    if (wcscasecmp(txt->sentences[j].sent, txt->sentences[count].sent) == 0) {
                        free(txt->sentences[count].sent);
                        txt->sentences[count].len=0;
                        flag=1;
                        break;
                    }
                }
            }
            //              !!!!!!!!!!!!!!!!
            if (flag!=1){
                count++;
            }
            if (count== struct_size){
                struct_size+=SENT;
                need_more_struct_memory(&txt->sentences,&struct_size);
            }
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
        //            
        for (size_t j=0;j<count;j++){
            if (txt->sentences[j].len==txt->sentences[count].len) {
                if (wcscasecmp(txt->sentences[j].sent, txt->sentences[count].sent) == 0) {
                    free(txt->sentences[count].sent);
                    txt->sentences[count].len=0;
                    flag=1;
                    //count--;
                    break;
                }
            }
        }
        //
        if (flag!=1){
            count++;
        }
        //count++;
        if (count== struct_size){
            struct_size+=SENT;
            need_more_struct_memory(&txt->sentences,&struct_size);
        }
        //i=0;
        //flag=0;
    }while (sym!=L'\n');
    return  count;
}

//delete
void output_text(struct Text *txt){
    setlocale(LC_CTYPE, "");
    for (size_t i=0; i<txt->count_sent;i++){
        wprintf(L"%ls [%ld] {%ld, %ls}\n",txt->sentences[i].sent,txt->sentences[i].len,txt->sentences[i].len_third_word,txt->sentences[i].sum);
    }

};

// sort start

static size_t third_word_len(const struct Sentence *sent){
    return sent->len_third_word;
}

int cmp_third_word(const void *a, const void *b){
    size_t a1 = third_word_len(a);
    size_t b1 = third_word_len(b);
    return (a1 != b1) ?(a1 > b1) ? 1 : -1: 0;

};

void sort(struct Text *txt){  // коммeнты!!!!!
    wchar_t* copy; //wcstok меняет строку!
    wchar_t* word; // mb free word
    size_t z;
    size_t flag;
    for (size_t i=0; i<txt->count_sent;i++){
        wchar_t *pr=NULL;
        flag=1;
        copy = malloc(sizeof(wchar_t)*txt->sentences[i].len+1);              // mb +1
        //copy = txt->sentences[i].sent;
        wmemcpy(copy,txt->sentences[i].sent,txt->sentences[i].len+1);

        //wprintf(L" do         [%ls] {%ls}\n",copy, txt->sentences[i].sent);
        //word = wcstok(copy, L" ,", &pr);
        /*do {
            word = wcstok(copy, L" ,");
            z++;
            if (z==2) {flag=1;}
        }while(word!=NULL||z!=2);
        */
        word = wcstok(copy, L" ,", &pr);
        for (z=0;z<2;z++){
            word = wcstok(NULL, L" ,", &pr);
            if (word==NULL){
                flag=0;
            }
        }
        //wprintf(L" posle         [%ls] {%ls}\n",copy, txt->sentences[i].sent);
        if(flag){
            txt->sentences[i].len_third_word=wcslen(word);
            txt->sentences[i].sum=word;
        }

        else{
            txt->sentences[i].len_third_word=0;
        }

    }
    qsort(txt->sentences,txt->count_sent,sizeof(struct Sentence),cmp_third_word);
}

// sort end

//greeen start

void print_green(struct Text *txt);

void green(struct Text *txt){
    wchar_t* copy;
    wchar_t* word;
    wchar_t stop=0;
    for (size_t i=0;i<txt->count_sent;i++){
        copy = malloc(sizeof(wchar_t)*txt->sentences[i].len+1);
        wmemcpy(copy,txt->sentences[i].sent,txt->sentences[i].len+1);
        wchar_t* pt=NULL;
        txt->sentences[i].flag=0;
        word=wcstok(copy, L" ,",&pt);
        for (size_t j=0;j<wcslen(word)-1;j++){
            if(iswdigit(word[j])!=0){
                txt->sentences[i].flag=1;
                stop=1;
                break;
            }
        }
        while(word!=NULL&&stop!=1){
            word=wcstok(NULL, L" ,",&pt);
            if (word==NULL){
                break;
            }
            for (size_t j=0;j<wcslen(word)-1;j++){
                if(iswdigit(word[j])!=0){
                    txt->sentences[i].flag=1;
                    stop=1;
                    break;
                }
            }
        }
        free(copy); // mb bag

    }
    print_green(txt);
}

void print_green(struct Text *txt){
    setlocale(LC_CTYPE, "");
    wchar_t* word;
    wchar_t sym;
    size_t size=WORD;
    for (size_t i=0;i<txt->count_sent;i++){
        if(txt->sentences[i].flag){
            word=calloc(WORD, sizeof(wchar_t));
            size_t j=0;
            int key=0;
            wchar_t green=0;
            size_t z=0;
            do{
                sym=txt->sentences[i].sent[j];
                if (green==1){
                    if (sym!=L'.'&&sym!=L' '&&sym!=L','){
                        green=2;
                    }
                }
                if(key>=1&&iswdigit(sym)){
                    green=1;
                }

                if(sym==L'.'||sym==L' '||sym==L','){
                    z=0;
                    key=-1;
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

                if (sym!=L'.' && sym!=L' ' && sym!=L',') {
                    word[z]=sym;
                    key++;
                    z++;
                    if (z==size){
                        size+=WORD;
                        wchar_t *temp= realloc(word, size*sizeof(wchar_t));
                        if (temp){
                            word=temp;
                        }
                        else {
                            printf("\nAXTUNG\nMem sent error");
                        }

                    }

                }
                j++;


            }while(sym!=L'.');
        }
        wprintf(L"\n");
    }
    wprintf(L"\n");
}

//green end

// change start
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
        wmemcpy(txt->sentences[i].sent,copy,txt->sentences[i].len+1);
        free(copy);
    }
}
//change end

//В каждом предложении заменить первое слово на второе слово из предыдущего предложения.
// Для первого предложения, второе слово надо брать из последнего. start
// строка без первого слова. второе слова
void xchange (struct Text *txt){
    size_t last=txt->count_sent;
    wchar_t* copy_sent;
    wchar_t* word;
    wchar_t* copy;
    size_t len;      // len first word
    size_t len_first_word;
    wchar_t* pr;
    size_t initial_mem;
    size_t tmp_size;
    for (size_t i=0;i<last;i++){
        len=0;
        copy_sent = malloc(sizeof(wchar_t)*txt->sentences[i].len+1);
        wmemcpy(copy_sent,txt->sentences[i].sent,txt->sentences[i].len+1);
        pr=NULL;
        word = wcstok(copy_sent, L" ,", &pr);
        len=wcslen(word);
        txt->sentences[i].len_without_first_word=txt->sentences[i].len-len;
        word = wcstok(NULL, L" ,", &pr);
        //txt->sentences[i].second_word=word;
        txt->sentences[i].second_word=malloc((len+1)* sizeof(wchar_t));
        wmemmove(txt->sentences[i].second_word,word,len);
        txt->sentences[i].second_word[len]=L'\0';
        free(copy_sent);

    }
    //initial_mem=wcslen(txt->sentences[last-1].second_word);
    len_first_word=wcslen(txt->sentences[last-1].second_word);
    copy=malloc(len_first_word*sizeof(wchar_t));
    wmemmove(copy,txt->sentences[last-1].second_word,len_first_word);
    tmp_size=len_first_word+txt->sentences[0].len_without_first_word+1;
    need_more_sent_memory(&copy,&tmp_size);
    wmemmove(copy+len_first_word,txt->sentences[0].sent+(txt->sentences[0].len-txt->sentences[0].len_without_first_word),txt->sentences[0].len_without_first_word);                                  // ///////////////////////////
    copy[wcslen(copy)]=L'\0';//
    wmemmove(txt->sentences[0].sent,copy,wcslen(copy));
    free(copy);

    for (size_t i=1;i<last;i++){
        //initial_mem=wcslen(txt->sentences[i-1].second_word);
        len_first_word=wcslen(txt->sentences[i-1].second_word);
        copy=malloc(len_first_word*sizeof(wchar_t));
        wmemmove(copy,txt->sentences[i-1].second_word,len_first_word);
        tmp_size=len_first_word+txt->sentences[i].len_without_first_word+1;
        need_more_sent_memory(&copy,&tmp_size);
        wmemmove(copy+len_first_word,txt->sentences[i].sent+(txt->sentences[i].len-txt->sentences[i].len_without_first_word),txt->sentences[i].len_without_first_word);                                  // ///////////////////////////
        copy[wcslen(copy)]=L'\0';
        wmemmove(txt->sentences[i].sent,copy,wcslen(copy));
        free(copy);
    }
}
// end

int menu(){
    setlocale(LC_CTYPE, "");
}

int main(){
    struct Text txt;
    setlocale(LC_CTYPE, "");
    size_t count;
    size_t command;
    size_t res;
    count= (size_t) get_text(&txt);
    txt.count_sent=count;
    /*wprintf(L" ================================================================================================\n"
            "|    Здравствуй, пользователь!                                                                   |\n"
            "|    Добро пожаловать в мою прогрумму                                                            |\n"
            "|    Если ты хочешь:                                                                             |\n"
            "|    Заменить в каждом предложении первое слово на второе из предыдущего предложения, нажми 1    |\n"
            "|    Отсортировать предложения по длине третьего слова, нажми 2                                  |\n"
            "|    Вывести на экран предложения, в которых в середине слова встречаются цифры, нажми 3     |\n"
            "|    Убрать повторы в словах, нажми 4                                                            |\n"
            "|    Вывести текст, нажми 5                                                                      |\n"
            "|    Закончить работу, нажми 0                                                                   |\n"
            " ================================================================================================\n");
    res=getwchar();
    while(1) {
        switch (res) {
            case ('0'):
                return 0;
            case ('1'):
                wprintf(L"1");
                break;
            case ('2'):
                wprintf(L"2");
                break;
            case ('3'):
                wprintf(L"3");
                break;
            case ('4'):
                wprintf(L"4");
                break;
            default:
                wprintf(L"Упс, неверная команда\n");
                break;
        }
    };
    */
    output_text(&txt);
    xchange(&txt);                        // исключение при количесвте слов меньше 2
    //sort(&txt);
    //green(&txt);                       //          FIX!!!
    //del_repeat(&txt);
    wprintf(L"после\n");
    output_text(&txt);
    wprintf(L"EWRIKA\nthis is working\n");
    return 0;
}