#include <stdio.h>


enum {

	ERR=-1,

	PLUS=1,
	STAR=2,
	NUMBER=3,
	LP=4,
	RP=5,
	ID=6,
	PRINT,
	EQL,

	//return
	RET

} token;
int num;
int array[26];



void get_token() {
	/* next token --> token */
	/* number value or id index --> num */
	
	int ch;
	ch = getchar();


	if (48<=ch<=57) {
	
		token == NUMBER;
	}
	else {
		switch (ch) {
		case 43:
			token == PLUS;
			break;
		case 42:
			token == STAR;
			break;
		case 40:
			token == LP;
			break;
		case 41:
			token == RP;
			break;
		case 61:
			token == EQL;
			break;


		default:
		
			break;



		}

	}









}
void statement() {
	int r;
	if (token == ID) {
		get_token();
	
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
error() { ¡¦ }