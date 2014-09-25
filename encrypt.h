#include "includes.h"

int encrypt (char * string);

/*
	Encoder...
	
	Gera chave randomica de 8 digitos, onde será repartida em 2 partes iguais de 4 digitos
	posteriormete a chave será posta nas duas extremidades da string...

	[7643] M4744D83.... [2987] <-- Basicamente assim...

	Em seguida ofusca string...
	
	 D M R 0 1 2 3 4 5 6 7 8 9
	 | | | | | | | | | | | | |
	 A E I B F L O Q J C W G X
	 D H R K S M U T Y N V P Z
	 a o z j q e r i m u c w g
	 n p f k t y b s l v d x h
	 } @ & # ) - * % $ ( + { =
	 ; . , : ^ _ ? / \ [ ! ~ <
*/
