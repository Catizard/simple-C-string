#include <string.h>
#include <malloc.h>
#include "lemon_string.h"

string_dict_t *DICT;

int _basic_cstring_compare(const char *LHS, size_t LSZ, const char *RHS, size_t RSZ) {
    if (LSZ != RSZ) {
        return 0;
    }

    for (int i = 0; i < LSZ; ++i) {
        if (LHS[i] != RHS[i]) {
            return 0;
        }
    }
    return 1;
}

string_t *_search_string_in_dict(const char *rawstring) {
    //TODO change dict's structure in order to get faster search prog
    for (int i = 0; i < DICT->_size; i++) {
        if (_basic_cstring_compare(DICT->dict[i]->data, DICT->dict[i]->len,
                                   rawstring, strlen(rawstring))) {
            return DICT->dict[i];
        }
    }
    return NULL;
}

void _dict_append(string_t *str) {
    DICT->dict[DICT->_size] = str;
    DICT->_size++;
}

string_t *string_create(char *rawstring) {
    //TODO This setup progress should write in a function like prehandle()
    //In order to control them easily, like if the user want to disable sharing memory
    //prehandle()

    if (DICT == NULL) {
        DICT = (string_dict_t *) malloc(sizeof(string_dict_t));
        DICT->_size = 0;
        //TODO FOR TEST ARRAY
        DICT->dict = malloc(sizeof(string_t *) * 100);
    }

    string_t *fs = _search_string_in_dict(rawstring);
    if (fs != NULL) {
        return fs;
    }
    string_t *new_s = (string_t *) malloc(sizeof(string_t));
    new_s->len = strlen(rawstring);
    char *alloc_string = (char *) malloc(new_s->len);
    memcpy(alloc_string, rawstring, new_s->len);
    new_s->data = alloc_string;
    _dict_append(new_s);
    return new_s;
}

int string_compare(string_t *LHS, string_t *RHS) {
    return _basic_cstring_compare(LHS->data, LHS->len, RHS->data, RHS->len);
}

int string_compare_fn(string_t *LHS, string_t *RHS, int(*fn)(char *, size_t, char *, size_t)) {
    return fn(LHS->data, LHS->len, RHS->data, RHS->len);
}

int string_delete(string_t *str) {
    free(str->data);
    free(str);
    return 1;
}

