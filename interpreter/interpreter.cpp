#include <stdio.h>

enum {

    ERR = -1,

    PLUS = 1,
    STAR = 2,
    NUMBER = 3,
    LP = 4,
    RP = 5,
    ID = 6,
    PRINT = 7,
    EQL = 8,
    ENT = 9,

    //return
    RET = 10

} token;
int num;
int array[26];


int term();
int expr();
int error();
int factor();

//이 array 정체는 알파벳 id 저장하는 칸이어씀 
// 주어진 문법이 맞는지 아닌지.!!!!!!!!!!!!!!!!!!11 목적!!!!!!!!!11


void get_token() {
    /* next token --> token */
    /* number value or id index --> num */

    int ch;
    ch = getchar();

    //확인용
    //printf("\ncheck:%c",ch);



    // 공백 재낌.
    if (ch == ' ') {
        ch = getchar();

    }

    //PRINT
    if (ch == 'p') {
        ch = getchar();

        if (ch == 'r')
            ch = getchar();

        if (ch == 'i')
            ch = getchar();

        if (ch == 'n')
            ch = getchar();

        if (ch == 't')
            token = PRINT;
        ch = getchar();
        return;

    }



    else {


        //NUMBER 0~9
        if (48 <= ch && ch <= 57) {

            token = NUMBER;


            num = ch - 48;


            return;
        }

        //ID
        else if ('a' <= ch && ch <= 'z') {

            token = ID;


            // num 에 알파벳 저장
            num = ch - 97;
            return;

        }

        else {
            switch (ch) {
            case '+':
                token = PLUS;
                break;
            case '*':
                token = STAR;
                break;
            case '(':
                token = LP;
                break;
            case ')':
                token = RP;

                break;
            case '=':
                token = EQL;
                break;

            case '\n':
                token = ENT;
                break;


            default:

                error();
                break;

            }

            return;

        }

    }


}
void statement() {

    int r;


    // ID=> =-> EXPR => /N 
    if (token == ID) {


        r = num;
        get_token();
        if (token == EQL) {


            get_token();


            //????????
            array[r] = num;

            //확인용
            //printf("r: %d\n",r);
            //printf("array[r]:%d",array[r]);



            //ID 다음 토큰이 EXR 인지
            expr();


        }

        else
        {
            error();
        }



    }

    ///////////////////////////////////////////////


 // PRINT=> EXPR=> /N
    else if (token == PRINT) {
        get_token();
        r = expr();
        //printf("> %d\n", r);
    }

    else {
        error();
    }


}
int expr() {
    int r;
    r = term();
    while (token == PLUS) {
        get_token();
        r = r + term();
    }
    return (r);
}
int term() {
    int r;
    r = factor();
    while (token == STAR) {
        get_token();
        r = r * factor();
    }
    return (r);
}


int factor() {


// 아 LP 갔다가EXPR 다시 와서 
    int r =0;
    int tmp=0;

    if (token == NUMBER) {
        r = num;
        //확인용
        //printf("rrrrrrrrrrrrr: %d\n", r);

        get_token();
    }
    else if (token == ID) {
        r = array[num];
        get_token();
    }
    else if (token == LP) {
        get_token();
        tmp = num;
        expr();
        if (token == RP)

            get_token();
        else
            error();
    }
    else
        error();

    return r;
}
void main() {

    while (1) {
        get_token();
        statement();
    }
}
int error() {

    printf("SYNTAX error!\n");
    return -1;
}