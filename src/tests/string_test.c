//
// Created by StevenD on 10/20/2017.
//

#include <assert.h>
#include <stdio.h>
#include "../String.h"

int main() {
    String* stringA = String_Create();
    String* stringB = String_CreateCopy("");
    char* expected_str = "abcdefghijklmnopqrstuvwxyz";
    assert(String_Size(stringA) == 0);
    assert(String_Size(stringB) == 0);
    assert(String_Compare(stringB, stringB) == 0);

    char c; for (c = 'a'; c <= 'z'; ++c) {
        String_AppendChar(stringA, c);
        String_AppendChar(stringB, c);
    }

    assert(strcmp(String_CStr(stringA), expected_str) == 0);
    assert(strcmp(String_CStr(stringB), expected_str) == 0);

    assert(String_Size(stringB) == strlen(expected_str));
    String_Reserve(stringB, 50);
    assert(String_Size(stringB) == strlen(expected_str));
    assert(String_Compare(stringA, stringB) == 0);
    assert(String_Size(stringB) == strlen(expected_str));

    UINT i; for (i = 0; i < String_Size(stringA); ++i) {
        assert(String_At(stringA, i) == ('a' + i));
    }

    String_AppendString(stringA, stringB);

    String* stringC = String_CreateCopy("abcdefghijklmnopqrstuvwxyz""abcdefghijklmnopqrstuvwxyz");
    assert(String_Compare(stringA, stringC) == 0);
    assert(String_Size(stringA) == (('z' - 'a' + 1) * 2));
    String_Destroy(stringC);

    String_ShrinkToFit(stringB);
    assert(strcmp(String_CStr(stringB), expected_str) == 0);

    String_Reserve(stringA, 32);
    sprintf(String_CStr(stringA), "[%s]", "Test");
    String_ShrinkToFit(stringA);
    assert(strcmp(String_CStr(stringA), "[Test]") == 0);
    assert(String_Size(stringA) == strlen("[Test]"));

    String_Destroy(stringA);
    String_Destroy(stringB);
    return 0;
}