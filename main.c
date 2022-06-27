#include <stdio.h>
#include <malloc.h>
#include "lemon_string.h"

int main() {
    string_t *s = string_create("HELLO");
    printf("s data is %s\n", s->data);
    string_t *exactlysame = string_create("HELLO");
    printf("exactlysame data is %s\n", exactlysame->data);
    printf("s with s compare :%d\n", string_compare(s, s));
    printf("s with exactlysame compare :%d\n", string_compare(s, exactlysame));
    printf("s address: %o, exactlysame address: %o\n", s->data, exactlysame->data);
    return 0;
}
