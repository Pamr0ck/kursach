//otchet
// dell len
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
                if(xchange(&txt)==0) return 0;
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