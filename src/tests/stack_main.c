//
// Created by Steven on 10/7/2017.
//

#include <stdio.h>
#include <malloc.h>
#include <assert.h>
#include <SDL2/SDL_quit.h>
#include "../stack.h"

define_Stack(Uint16)

BOOL predicate_Uint16(Uint16 a, Uint16 b) { return a == b;}

int formatter(String* str, Uint16 item) {
    String_Reserve(str, 32);
    int size = sprintf(String_CStr(str), "%u", item);
    String_ShrinkToFit(str);
    return size;
}

int main() {
    Stack_Uint16 *s = Stack_Create_Uint16();
    Uint16 stack_items = 32000;

    assert(Stack_Size_Uint16(s) == 0);
    assert(Stack_IsEmpty_Uint16(s) == TRUE);

    Uint16 i; for (i = 0; i < stack_items; ++i) {
        Stack_Push_Uint16(s, i);
    }

    assert(Stack_Size_Uint16(s) == stack_items);
    assert(Stack_IsEmpty_Uint16(s) == FALSE);

    assert(Stack_Peek_Uint16(s) == stack_items - 1);
    assert(Stack_PeekAt_Uint16(s, (UINT) (stack_items / 2)) == (stack_items / 2));

    assert(Stack_Find_Uint16(s, (Uint16) (stack_items / 2), predicate_Uint16) == (stack_items / 2));
    assert(Stack_Find_Uint16(s, (Uint16) (stack_items + 100), predicate_Uint16) == -1);

    for (i = 0; i < stack_items; ++i) {
        Stack_Pop_Uint16(s);
    }

    assert(Stack_Size_Uint16(s) == 0);
    assert(Stack_IsEmpty_Uint16(s) == TRUE);
    assert(s->allocated_size == 10);

    Uint16 stack_items_print = 16;
    String *str = String_Create();
    String *delimiter = String_CreateCopy(", ");
    String *expected_str = String_CreateCopy("0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15");

    for (i = 0; i < stack_items_print; ++i) {
        Stack_Push_Uint16(s, i);
    }

    assert(Stack_format_Uint16(s, str, formatter, delimiter) == String_Size(str));
    assert(String_Size(str) == String_Size(expected_str));
    assert(String_Compare(str, expected_str) == 0);

    String_Destroy(expected_str);
    String_Destroy(delimiter);
    Stack_Destroy_Uint16(s);
    return 0;
}