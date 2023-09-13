#include <stdio.h>
#include "e3.h"

int score, trials;

void test(const char *s, char ok) {
    trials++;
    char res = charfreq(s);
    printf("Test %d: %c (ASCII %d) [corretto: %c (ASCII) %d]\n", trials, res, res, ok, ok);
    score += res == ok;
}

int main() {

    test("This.is.by.far.the.dumbest.test-ever", 46);
    test("Seventh son of a seventh son seems so soorth", 32);
    test("ab bb cb daaa", 97);
    test("ccc", 99);
    printf("Risultato: %d/%d\n", score, trials);

    return 0;
}
