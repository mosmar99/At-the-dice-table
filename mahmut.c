#include "mahmutHeaders.h"

/* NPCs play is inspired by:
1. http://www.durangobill.com/Pig.html

2. https://citeseerx.ist.psu.edu/viewdoc/download?doi=10.1.1.841.1345&rep=rep1&type=pdf
*/

void menu(void);
void pig(void);

int main(void) {
    clock_t begin = clock();
    // --------- S T A R T  T O  C O D E  H E R E ---------
    
    //menu();
    pig();

    // --------- E N D  O F  C O D E ---------
    clock_t end = clock();
    double res = (double) (end - begin) / CLOCKS_PER_SEC;
    printf("\nExecution time: %f", res);
    return 0;
}