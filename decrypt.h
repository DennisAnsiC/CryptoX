#include "includes.h"

int decrypt(char * string);

/*
	Decoder...
	
	Faz reverso da ofuscação...

	D M R 0 1 2 3 4 5 6 7 8 9
	| | | | | | | | | | | | |
	A E I B F L O Q J C W G X
	D H R K S M U T Y N V P Z
	a o z j q e r i m u c w g
	n p f k t y b s l v d x h
	} @ & # ) - * % $ ( + { =
	; . , : ^ _ ? / \ [ ! ~ <

	Parseia string pegando sempre os 4 primeiros e 4 ultimos digitos e monta chae pra decodar a string...

	[7643] M4744D83.... [2987] <-- Basicamente assim...

	Decoda a string....
*/
