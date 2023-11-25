#include <cstdio>
#include <MiLang/lib.h>

const int bufferSize = 4096;
char t[bufferSize];

int main() {
    getLocale(t, bufferSize);
    printf("%s", t);
    return 0;
}