#include <stdio.h>
#include <stdlib.h>
int term();
int expr();
int error();
int factor();


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
int idx;
int array[26];


void get_token() {
    /* next token --> token */
    /* number value or id index --> num */

    int tmp;

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

        if ((ch = getchar()) == 'r' &&
            (ch = getchar()) == 'i' &&
            (ch = getchar()) == 'n' &&
            (ch = getchar()) == 't') {

            token = PRINT;
            ch = getchar();
            return;
        }
        error();
    }

    else {

        //NUMBER 0~9
        if (48 <= ch && ch <= 57) {

            token = NUMBER;


            num = ch - '0';
            while ((ch = getchar()) >= '0' && ch <= '9') {
                num = num * 10 + (ch - '0');
            }
            ungetc(ch, stdin);

            return;
        }

        //ID
        else if ('a' <= ch && ch <= 'z') {


            token = ID;



            // 아 저장을 해야됨.!!!!!!11
            // num 에 알파벳 저장

            // 여기 지나니까 num 값이 변하는 거임. 


            idx = ch - 97;

            return;

        }

        else {
            switch (ch) {
            case '+': token = PLUS; break;
            case '*': token = STAR;  break;
            case '(':token = LP;  break;
            case ')': token = RP;  break;
            case '=': token = EQL;   array[idx] = num;   break;
            case '\n': token = ENT;  break;
            default:  error();

            }
        }
    }


}
void statement() {

    int r;


    // ID=> =-> EXPR => /N 
    if (token == ID) {

        // id 의 인덱스
        r = idx;

        get_token();


        if (token == EQL) {


            get_token();


            //저장.
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
        printf("> %d\n", r);
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
    int r = 0;

    if (token == NUMBER) {

        r = num;


        //확인용
        //printf("rrrrrrrrrrrrr: %d\n", r);

        get_token();
    }
    else if (token == ID) {

        r = array[idx];
        get_token();
    }
    else if (token == LP) {
        get_token();


        r = expr();
        //printf("%d", r);
        if (token == RP)
            get_token();
        else
            error();
    }
    else
        error();
    return (r);
}
void main() {

    while (1) {
        get_token();
        statement();
    }
}
int error() {

    printf("SYNTAX error!\n");
    exit(1);
}