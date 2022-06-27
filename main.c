#include <stdio.h>
#include <malloc.h>
#include "lemon_string.h"

int main() {
    string_t* s = string_create("HELLO");
    printf("data is %s\n", s->data);
    string_t* OTH = string_create("HELLO111");
    printf("s with s compare :%d\n", string_compare(s, s));
    printf("s with OTH compare :%d\n", string_compare(s, OTH));
    return 0;
}
