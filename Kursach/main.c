// символ конца файла если из файла
// ввод из файла        если будет скучно


// FIX xchange
// cmake
//otchet

//wprintf(L"%ls [%ld] {%ld}\n",txt->sentences[i].sent,txt->sentences[i].len,txt->sentences[i].len_third_word);
//#include <ctype.h>
//#include <stdlib.h>
//#include <string.h>
//#include <wctype.h>



#include <wchar.h>
#include <stdio.h>
#include <locale.h>

#include "text.h"
#include "iotext.h"
#include "structs_and_memory.h"


int main(){
    struct Text txt;
    setlocale(LC_CTYPE, "");
    size_t count;
    int command;
    count=get_text(&txt);
    txt.count_sent=count;
    do {
        command = menu();
        switch (command){
            case 1:
                if(xchange(&txt)==0) return 0;                  //FIX!!!!!!!!!!!!!!
                break;
            case 2:
                sort(&txt);
                break;
            case 3 :
                green(&txt);
                break;
            case 4:
                del_repeat(&txt);
                break;
            case 5:
                output_text(&txt);
                break;
            case 0:
                wprintf(L"%ls",GOODBUE);
                break;
            case 10:
                wprintf(L"%ls",UPS);
                break;
        }
    }while(command!=0);
    goodbuy_world(&txt);
    return 0;
}