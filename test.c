#include <stdio.h>
#include <string.h>
int main() {
    char s1[10] = "123";
    char s2[6] = "12";
    strncat(s1,s2, 3);
    printf("%s", s1);
    return 0;
}