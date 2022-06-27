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

void _refix_interval(size_t *l, size_t *r, size_t minv, size_t maxv) {
    if ((*l) == -1 || (*l) < minv) {
        (*l) = minv;
    }
    if ((*r) == -1 || (*r) > maxv) {
        (*r) = maxv;
    }
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

string_slice_t *string_slice_create(string_t *str, size_t l, size_t r) {
    _refix_interval(&l, &r, 0, str->len);
    if (l >= r) {
        return NULL;
    }

    string_slice_t *new_s = (string_slice_t *) malloc(sizeof(string_slice_t));
    new_s->len = r - l;
    new_s->data = str->data + l;
    new_s->l = l;
    new_s->r = r;
    new_s->succ = NULL;
    new_s->succ_len = 0;
    return new_s;
}

int string_slice_delete(string_slice_t *str) {
    free(str->data);
    free(str);
    return 1;
}

//TODO current method complex is O(n), can we speed it up?
string_slice_t *string_slice_merge(string_slice_t *LHS, string_slice_t *RHS) {
    LHS->succ_len += RHS->succ_len;
    string_slice_t *fs = LHS;
    while ((fs->succ) != NULL) {
        fs = fs->succ;
    }
    fs->succ = RHS;
    return LHS;
}

string_t *slice_to_string(string_slice_t *slice) {
    char *merge_info = malloc(sizeof(char) * ((slice->len) + (slice->succ_len) + 1));

    size_t new_len = 0;
    while (slice != NULL) {
        memcpy(merge_info + new_len, slice->data, slice->len);
        new_len += slice->len;
        slice = slice->succ;
    }
    merge_info[new_len] = '\0';
    return string_create(merge_info);
}