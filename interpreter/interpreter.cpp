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


int term();
int expr();
int error();
int factor();


//ÀÌ array Á¤Ã¼´Â ¾ËÆÄºª id ÀúÀåÇÏ´Â Ä­ÀÌ¾î¾¸ 
// 



//ÀÌ array Á¤Ã¼´Â ¾ËÆÄºª id ÀúÀåÇÏ´Â Ä­ÀÌ¾î¾¸ 
// 



//ÀÌ array Á¤Ã¼´Â ¾ËÆÄºª id ÀúÀåÇÏ´Â Ä­ÀÌ¾î¾¸ 
// 



//ÀÌ array Á¤Ã¼´Â ¾ËÆÄºª id ÀúÀåÇÏ´Â Ä­ÀÌ¾î¾¸ 
// 



void get_token() {
    /* next token --> token */
    /* number value or id index --> num */

    int tmp;

    int ch;
    ch = getchar();

    //È®ÀÎ¿ë
    //printf("\ncheck:%c",ch);


	//PRINT
	if (ch == 'p') {
		get_token();
		if(ch=='r')
			get_token();
		if (ch == 'i')
			get_token();
		if (ch == 'n')
			get_token();
		if (ch == 't')
			token = PRINT;
			return;
			
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

			num = ch - 97;
			token = ID;
			get_token();


		}

		else {
			switch (ch) {
			case '+':
				token = PLUS;
				get_token();
				break;
			case '*':
				token = STAR;
				get_token();
				break;
			case '(':
				token = LP;
				get_token();
				break;
			case ')':
				token = RP;
				
				break;
			case '=':
				token = EQL;
				expr();
				break;


            return;

        }


            }
        }
    }


}
void statement() {

    int r;


    // ID=> =-> EXPR => /N 
    if (token == ID) {

        // id ÀÇ ÀÎµ¦½º
        r = idx;

        get_token();


        if (token == EQL) {

	
	if (token == ID) {
		get_token();
		if (token == EQL)
			expr();
	}


            //ÀúÀå.
            array[r] = num;

            //È®ÀÎ¿ë
            //printf("r: %d\n",r);
            //printf("array[r]:%d",array[r]);


            //ID ´ÙÀ½ ÅäÅ«ÀÌ EXR ÀÎÁö
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


        //È®ÀÎ¿ë
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