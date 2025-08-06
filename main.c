#include <stdio.h>
int yyparse(void);

int main() {
    printf("Mini SQL for CSV\n");
    printf("Enter SQL Query:\n");
    yyparse();
    return 0;
}
