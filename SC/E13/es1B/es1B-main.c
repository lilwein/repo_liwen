#include <stdio.h>

void interleave(const char* a, const char* b, char* c);

int main() {
    // test 1
    char* a1 = "kenobi";
    char* b1 = "anakin";
    char  c1[11];
    interleave(a1, b1, c1);
    printf("\"%s\" [corretto: \"kaennaokbiin\"]\n", c1);

    // test 2
    char* a2 = "obi-wan";
    char* b2 = "kenobi";
    char  c2[14];
    interleave(a2, b2, c2);
    printf("\"%s\" [corretto: \"okbein-owbain\"]\n", c2);

    // test 3
    char* a3 = "lila";
    char* b3 = "e";
    char  c3[6];
    interleave(a3, b3, c3);
    printf("\"%s\" [corretto: \"leila\"]\n", c3);

    // test 4
    char* a4 = "R";
    char* b4 = "2D2";
    char  c4[5];
    interleave(a4, b4, c4);
    printf("\"%s\" [corretto: \"R2D2\"]\n", c4);

    return 0;
}
