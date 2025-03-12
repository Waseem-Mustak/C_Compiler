yacc -d -y 2005091.y
g++ -w -c -o y.o y.tab.c
flex 2005091.l
g++ -w -c -o l.o lex.yy.c
g++ y.o l.o -lfl -o a
./a input.c