/*
    ( { __Return_Type __Anonymous_Functions_Name (__Arguments) { __Body } __Anonymous_Functions_Name; } )
 */

/* The following example works only with GCC. Because of how macros are
 * expanded, the __Body cannot contain any commas outside of parentheses;
 * GCC treats the comma as a delimiter between macro arguments. The
 * argument __Return_Type can be removed if __typeof__ is available;
 * in the example below using __typeof__ on array would return testtype_t *,
 * which can be dereferenced for the actual value if needed.
 */

#include <stdio.h>

/* this is the definition of the anonymous function */
#define lambda(__Return_Type, __Arguments, __Body)       \
  ({                                                     \
   __Return_Type __Anonymous_Functions_Name __Arguments  \
   __Body                                                \
   &__Anonymous_Functions_Name;                          \
   })

#define forEachInArray(fe_arrType, fe_arr, fe_fn_body)   \
{                                                        \
  int i=0;                                               \
  for(;i<sizeof(fe_arr)/sizeof(fe_arrType);i++)          \
    {  fe_arr[i] = fe_fn_body(&fe_arr[i]); }             \
}

typedef struct __test
{
    int a;
    int b;
} testtype_t;

void printout(const testtype_t * array)
{
    int i;
    for ( i = 0; i < 3; ++ i )
        printf("%d %d\n", array[i].a, array[i].b);
    printf("\n");
}

int main(void)
{
    testtype_t array[] = { {0,1}, {2,3}, {4,5} };

    printout(array);
    /* the anonymous function is given as function for the foreach */
    forEachInArray(testtype_t,
                   array,
                   lambda (testtype_t, (void *item),
    {
        int temp = (*( testtype_t *) item).a;
        (*( testtype_t *) item).a = (*( testtype_t *) item).b;
        (*( testtype_t *) item).b = temp;
        /* SWAP((*( testtype_t *) item).a, (*( testtype_t *) item).b); */
        return (*( testtype_t *) item);
    }));
    printout(array);
    return 0;
}
