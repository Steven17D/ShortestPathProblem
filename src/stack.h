//
// Created by Steven on 10/7/2017.
//

#include <windef.h>
#include "String.h"

#define define_Stack(type) \
typedef struct Stack_##type { \
    type* stack; \
\
    UINT used_size; \
    UINT allocated_size; \
    UINT allocation_coefficient; \
} Stack_##type; \
\
Stack_##type* Stack_Create_##type() { \
    Stack_##type* stack = (Stack_##type*)malloc(sizeof(Stack_##type)); \
    stack->stack = NULL; \
    stack->used_size = 0; \
    stack->allocated_size = 0; \
    stack->allocation_coefficient = 10; \
    return stack; \
} \
void Stack_Destroy_##type(Stack_##type *stack){ \
    free(stack->stack); \
    free(stack); \
} \
\
void Stack_Push_##type(Stack_##type* stack, type value) { \
    if (stack->allocated_size < stack->used_size + 1) { \
        if (stack->stack == NULL) { \
            stack->stack = (type*)malloc(sizeof(Stack_##type) * stack->allocation_coefficient); \
            stack->allocated_size = stack->allocation_coefficient; \
        } else { \
            stack->stack = (type*)realloc(stack->stack, sizeof(type) * (stack->allocated_size + stack->allocation_coefficient)); \
            stack->allocated_size += stack->allocation_coefficient; \
        } \
    } \
    *(stack->stack + stack->used_size) = value; \
    ++stack->used_size; \
} \
type Stack_Pop_##type(Stack_##type* stack) { \
    --stack->used_size; \
    type value = *(stack->stack + stack->used_size); \
    if (stack->allocated_size - stack->allocation_coefficient > stack->used_size) { \
        stack->stack = (type*)realloc(stack->stack, sizeof(type) * (stack->allocated_size - stack->allocation_coefficient)); \
        stack->allocated_size -= stack->allocation_coefficient; \
    } \
    return value; \
} \
\
type Stack_Peek_##type(Stack_##type* stack) { \
    type value = *(stack->stack + (stack->used_size - 1)); \
    return value; \
} \
type Stack_PeekAt_##type(Stack_##type* stack, UINT index) { \
    type value = *(stack->stack + index); \
    return value; \
} \
int Stack_Find_##type(Stack_##type* stack, type value, BOOL (*predicate)(type, type)) { \
    int index; \
    for (index = 0; index < stack->used_size ; ++index) { \
        if (predicate != NULL && predicate(*(stack->stack + index), value)) { \
            return index; \
        }\
    } \
    return -1; \
} \
\
BOOL Stack_IsEmpty_##type(Stack_##type *stack) { \
    return stack->used_size == 0 ? TRUE : FALSE; \
} \
UINT Stack_Size_##type(Stack_##type *stack) { \
    return stack->used_size; \
} \
int Stack_format_##type(Stack_##type *stack, String *str, int (*formatter)(String*, type), String* delimiter) { \
    String* item_str = String_Create(); \
    int total_char_writen = 0; \
    int delimiter_len = String_Size(delimiter); \
    UINT i; for (i = 0; (i + 1) < stack->used_size; ++i) { \
        int char_writen = formatter(item_str, Stack_PeekAt_##type(stack, i));\
        if (char_writen < 0) return char_writen; \
        String_AppendString(str, item_str); \
        total_char_writen += char_writen; \
        String_AppendString(str, delimiter); \
        total_char_writen += delimiter_len; \
    } \
    if (stack->used_size > 0) { \
        int char_writen = formatter(item_str, Stack_PeekAt_##type(stack, stack->used_size - 1));\
        if (char_writen < 0) return char_writen; \
        String_AppendString(str, item_str); \
        total_char_writen += char_writen; \
    } \
    String_Destroy(item_str); \
    return total_char_writen; \
}
