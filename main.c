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


    //slice test
    string_slice_t *slice = string_slice_create(s, 0, -1);
    printf("slice address is %o\n", slice);
    printf("slice data is %s\n", slice_to_string(slice)->data);
    string_slice_t *slice2 = string_slice_create(s, 0, 1);
    slice = string_slice_merge(slice, slice2);
    printf("merged slice data is %s\n", slice_to_string(slice)->data);
    string_slice_t *slice3 = string_slice_create(s, -1, -1);
    slice = string_slice_merge(slice, slice3);
    printf("merged slice data is %s\n", slice_to_string(slice)->data);
    return 0;
}
