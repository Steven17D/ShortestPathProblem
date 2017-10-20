//
// Created by StevenD on 10/20/2017.
//

#include "String.h"

String *String_Create() {
    String* string = (String*) malloc(sizeof(String));
    string->string = calloc(1, sizeof(char));

    string->size = 1;
    return string;
}

String *String_CreateCopy(const char *str) {
    String* string = (String*) malloc(sizeof(String));
    string->size = (UINT) strlen(str) + 1;
    string->string = calloc(string->size, sizeof(char));
    strcpy(string->string, str);
    return string;
}

void String_Destroy(String *this) {
    free(this->string);
    free(this);
}

char *String_CStr(String *this) {
    return this->string;
}

char String_At(String *this, UINT index) {
    return this->string[index];
}

void String_Reserve(String *this, const UINT size) {
    this->size += size;
    this->string = realloc(this->string, this->size);
}

void String_ShrinkToFit(String *this) {
    this->size = (UINT) (strlen(this->string) + 1);
    this->string = realloc(this->string, this->size);
}

void String_AppendChar(String *this, const char c) {
    char s[2] = { c, '\0'};
    String_AppendChars(this, s);
}

void String_AppendChars(String *this, const char *str) {
    this->size += (UINT) strlen(str);
    this->string = realloc(this->string, this->size);
    strcat(this->string, str);
}

void String_AppendString(String *this, const String *str) {
    String_AppendChars(this, str->string);
}

UINT String_Size(String *this) {
    return this->size - 1;
}

int String_Compare(const String *str1, const String *str2) {
    return strcmp(str1->string, str2->string);
}
