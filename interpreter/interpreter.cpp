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

//�� array ��ü�� ���ĺ� id �����ϴ� ĭ�̾ 
// �־��� ������ �´��� �ƴ���.!!!!!!!!!!!!!!!!!!11 ����!!!!!!!!!11


void get_token() {
    /* next token --> token */
    /* number value or id index --> num */

    int ch;
    ch = getchar();

    //Ȯ�ο�
    //printf("\ncheck:%c",ch);



    // ���� �糦.
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


            // num �� ���ĺ� ����
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

            array[r] = num;

            //Ȯ�ο�
            //printf("r: %d\n",r);
            //printf("array[r]:%d",array[r]);


            //ID ���� ��ū�� EXR ����
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
        //Ȯ�ο�
        //printf("rrrrrrrrrrrrr: %d\n", r);

        get_token();
    }
    else if (token == ID) {
        r = array[num];
        get_token();
    }
    else if (token == LP) {
        get_token();
        r = expr();
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
    return -1;
}