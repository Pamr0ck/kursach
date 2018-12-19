#include "iotext.h"

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

                    break;
                }
            }
        }

        if (flag!=1){
            count++;
        }

        if (count== struct_size){
            struct_size+=SENT;
            need_more_struct_memory(&txt->sentences,&struct_size);
        }

    }while (sym!=L'\n');
    return  count;
}

void output_text(struct Text *txt){
    setlocale(LC_CTYPE, "");
    for (size_t i=0; i<txt->count_sent;i++){
        wprintf(L"%ls [%ld]\n",txt->sentences[i].sent,txt->sentences[i].len);
    }

};

int menu(){
    setlocale(LC_CTYPE, "");
    wprintf(L"%ls", WHAT_U_WANT);
    wchar_t* buff=malloc(SIZE* sizeof(wchar_t));
    wprintf(L"Ваша команда : ");
    wchar_t* res=fgetws(buff,40,stdin);
    if(wcslen(buff)!=2) return 10;
    wchar_t command= res[0];
    switch (command) {
        case (L'0'):
            free(buff);
            return 0;
        case (L'1'):
            free(buff);
            return 1;
        case (L'2'):
            free(buff);
            return 2;
        case (L'3'):
            free(buff);
            return 3;
        case (L'4'):
            free(buff);
            return 4;
        case (L'5'):
            free(buff);
            return 5;
        default:
            free(buff);
            return 10;
    }
}
