#include "mahmutHeaders.h"

void menu(void);
void abyss(void);

int main(void) {
    clock_t begin = clock();
    // --------- S T A R T  T O  C O D E  H E R E ---------

    menu();

    // --------- E N D  O F  C O D E ---------
    clock_t end = clock();
    double res = (double) (end - begin) / CLOCKS_PER_SEC;
    printf("\nExecution time: %f", res);
    return 0;
}