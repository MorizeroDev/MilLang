#include <cstdio>
#include "lib.h"

int main() {
    char t[4096];
    getLocale(t);
    printf("%s",t);
}