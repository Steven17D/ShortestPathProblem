//
// Created by StevenD on 10/20/2017.
//

#include <malloc.h>
#include "String.h"

String *String_Create() {
    String* string = (String*) malloc(sizeof(String));
    string->string = calloc(1, sizeof(char));
    string->length = 0;
    string->allocated_size = 1;
    return string;
}

String *String_CreateCopy(const char *str) {
    String* string = (String*) malloc(sizeof(String));
    string->length = (UINT) strlen(str);
    string->allocated_size = string->length + 1;
    string->string = calloc(string->allocated_size, sizeof(char));
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
    this->allocated_size += size;
    this->string = realloc(this->string, this->allocated_size);
}

void String_ShrinkToFit(String *this) {
    this->length = (UINT) strlen(this->string);
    this->allocated_size = this->length + 1;
    this->string = realloc(this->string, this->allocated_size);
}

void String_AppendChar(String *this, const char c) {
    ++this->length;
    ++this->allocated_size;
    this->string = realloc(this->string, this->allocated_size);
    this->string[this->length - 1] = c;
    this->string[this->length] = '\0';
}

void String_AppendChars(String *this, const char *str) {
    UINT str_length = (UINT) strlen(str);
    this->allocated_size += str_length;
    this->string = realloc(this->string, this->allocated_size);
    strcpy(this->string + this->length, str);
    this->length += str_length;
}

void String_AppendString(String *this, const String *str) {
    String_AppendChars(this, str->string);
}

UINT String_Size(String *this) {
    return this->length;
}

int String_Compare(const String *str1, const String *str2) {
    return strcmp(str1->string, str2->string);
}
