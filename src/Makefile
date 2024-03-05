default: run

run: lang
	./lang

lex.o: lexer/lex.c
	gcc -c lexer/lex.c 

driver.o: driver.c
	gcc -c driver.c

lang: driver.o lex.o
	gcc -o lang lex.o driver.o
