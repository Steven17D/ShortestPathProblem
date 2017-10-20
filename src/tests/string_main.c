//
// Created by StevenD on 10/20/2017.
//

#include <assert.h>
#include "../String.h"

int main() {
    String* stringA = String_Create();
    String* stringB = String_CreateCopy("");

    assert(String_Size(stringA) == 0);
    assert(String_Size(stringB) == 0);
    assert(String_Compare(stringB, stringB) == 0);

    char c; for (c = 'a'; c <= 'z'; ++c) {
        String_AppendChar(stringA, c);
        String_AppendChar(stringB, c);
    }

    assert(strcmp(String_CStr(stringA), "abcdefghijklmnopqrstuvwxyz") == 0);
    assert(strcmp(String_CStr(stringB), "abcdefghijklmnopqrstuvwxyz") == 0);

    assert(String_Size(stringB) == strlen("abcdefghijklmnopqrstuvwxyz"));
    String_Reserve(stringB, 50);
    String_ShrinkToFit(stringB);
    assert(String_Size(stringB) == strlen("abcdefghijklmnopqrstuvwxyz"));

    UINT i; for (i = 0; i < String_Size(stringA); ++i) {
        assert(String_At(stringA, i) == ('a' + i));
    }

    String_AppendString(stringA, stringB);

    String* stringC = String_CreateCopy("abcdefghijklmnopqrstuvwxyz" "abcdefghijklmnopqrstuvwxyz");
    assert(String_Compare(stringA, stringC) == 0);
    assert(String_Size(stringA) == (('z' - 'a' + 1) * 2));
    String_Destroy(stringC);

    String_Destroy(stringA);
    String_Destroy(stringB);
    return 0;
}