mini_sql: parser.tab.c lexer.yy.c main.c csv_utils.c
	gcc -o mini_sql parser.tab.c lexer.yy.c main.c csv_utils.c -lfl

parser.tab.c: parser.y
	bison -d parser.y

lexer.yy.c: lexer.l
	flex -o lexer.yy.c lexer.l

clean:
	rm -f mini_sql parser.tab.* lexer.yy.c
