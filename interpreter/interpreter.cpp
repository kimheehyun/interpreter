#include <stdio.h>

enum {

	ERR=-1,

	PLUS=1,
	STAR=2,
	NUMBER=3,
	LP=4,
	RP=5,
	ID=6,
	PRINT=7,
	EQL=8,

	//return
	RET
	
} token;
int num;
int array[26];


int term();
int expr();
int error();
int factor();


//이 array 정체는 알파벳 id 저장하는 칸이어씀 
// 



void get_token() {
	/* next token --> token */
	/* number value or id index --> num */
	
	int ch;
	ch = getchar();

	//확인용
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

		//NUMBER
		if (48 <= ch && ch <= 57) {

			token = NUMBER;
			num = ch;
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


			default:

				error();
				break;


			}
			
			return;

		}

	}






}
void statement() {

	
	if (token == ID) {
		get_token();
		if (token == EQL)
			expr();
	}

	
		///////////////////////////////////////////////

	//print 를 친게 검출되면 expr 호출 


	if (token == PRINT) {
		expr();
		printf("\n");

	}

	if (token == EQL) {
		expr();

	}



	get_token();

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
	int r;
	if (token == NUMBER) {
		r = num;
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

	
		get_token();
		statement();
	
}
int error() {

	printf("error!");
	return -1;

	
}