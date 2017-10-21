//
// Created by StevenD on 10/20/2017.
//

#ifndef SHORTESTPATHPROBLEM_STRING_H
#define SHORTESTPATHPROBLEM_STRING_H
#include <windef.h>

typedef struct String {
    char *string;
    UINT length;
    UINT allocated_size;
} String;

String* String_Create();
String* String_CreateCopy(const char*);
void String_Destroy(String *);

char* String_CStr(String*);
char String_At(String*, UINT);

void String_Reserve(String*, UINT);
void String_ShrinkToFit(String *this);

void String_AppendChar(String*, char);
void String_AppendChars(String*, const char*);
void String_AppendString(String*, const String*);

UINT String_Size(String*);
int String_Compare(const String*, const String*);

#endif //SHORTESTPATHPROBLEM_STRING_H
