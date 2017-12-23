
#if defined(__GNUC__)

#ifndef ABS
#define ABS(x) ((x)>=0?(x):-(x))
#endif /* ABS */
#ifndef MIN
#define MIN(a,b) (((a)<(b))?(a):(b))
#endif /* MIN */
#ifndef MAX
#define MAX(a,b) (((a)>(b))?(a):(b))
#endif /* MAX */

/*
#ifndef FALSE
#define FALSE 0
#endif  // FALSE
#ifndef TRUE
#define TRUE 1
#endif  // TRUE
*/

#define CERROR (-1)

/*
#ifndef bool
typedef enum { false = 0, true = 1 } bool;
#endif  /* bool */
*/

#define sizeofS(string) (sizeof(string) - 1)
#define sizeofA(array)  (sizeof(array)/sizeof(array[0]))

#define caseE(enum_type) case(int)(enum_type)
/****
(in Foreach loop for GCC, specifically C99 with GNU Extensions. Works with
strings and arrays. Dynamically allocated arrays can be used by casting
them to a pointer to an array, and then dereferencing them.
****/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>    /************/
#include <inttypes.h>    /************/

#define FOREACH_COMP(INDEX, ARRAY, ARRAY_TYPE, SIZE) \
  __extension__ \
  ({ \
    bool ret = FALSE; \
    if (__builtin_types_compatible_p (const char*, ARRAY_TYPE)) \
      ret = INDEX < strlen ((const char*)ARRAY); \
    else \
      ret = INDEX < SIZE; \
    ret; \
  })

#define FOREACH_ELEM(INDEX, ARRAY, TYPE) \
  __extension__ \
  ({ \
    TYPE *tmp_array_ = ARRAY; \
    &tmp_array_[INDEX]; \
  })

#define FOREACH(VAR, ARRAY) \
for (void *array_ = (void*)(ARRAY); array_; array_ = 0) \
for (size_t i_ = 0; i_ && array_ && FOREACH_COMP (i_, array_, \
                                    __typeof__ (ARRAY), \
                                    sizeof (ARRAY) / sizeof ((ARRAY)[0])); \
                                    i_++) \
for (bool b_ = 1; b_; (b_) ? array_ = 0 : 0, b_ = 0) \
for (VAR = FOREACH_ELEM (i_, array_, __typeof__ ((ARRAY)[0])); b_; b_ = 0)

/* example's */
int main (int argc, char **argv)
{
  int array[10];
  /* initialize the array */
  int i = 0;
  FOREACH (int *x, array)
    {
      *x = i;
      ++i;
    }

  char *str = "hello, world!";
  FOREACH (char *c, str)
    printf ("%c\n", *c);

  /* Use a cast for dynamically allocated arrays */
  int *dynamic = malloc (sizeof (int) * 10);
  for (int i = 0; i < 10; i++)
    dynamic[i] = i;

  FOREACH (int *i, *(int(*)[10])(dynamic))
    printf ("%d\n", *i);

  return EXIT_SUCCESS;
}


/**********

Lambda expressions (GCC only)

*********/

#define lambda(return_type, ...) \
  __extension__ \
  ({ \
    return_type __fn__ __VA_ARGS__ \
    __fn__; \
  })

int main (int argc, char **argv)
{
  int (*max) (int, int) =
    lambda (int, (int x, int y) { return x > y ? x : y; });
  return max (1, 2);
}

/*********
This one is awesome:
*********/
#define NEW(type, n) ( (type *) malloc(1 + (n) * sizeof(type)) )

/*********
And I use it like:
*********/
object = NEW(object_type, 1);

/**********
/*
I see others have provided examples of point 2 (macros as functions),
let me give an example of creating a new C construct: the Finite state machine.
(I've already posted this on SO but I can't seem to be able to find it)
*********/

 #define FSM            for(;;)
 #define STATE(x)       x##_s
 #define NEXTSTATE(x)   goto x##_s

/***
that you use this way:
***/

 FSM {
    STATE(s1):
      ... do stuff ...
      NEXTSTATE(s2);

    STATE(s2):
      ... do stuff ...
      if (k<0) NEXTSTATE(s2);
      /* fallthrough as the switch() cases */

    STATE(s3):
      ... final stuff ...
      break;  /* Exit from the FSM */
 }


/*
 * C++ also inherits the C preprocessor: a rather unsophisticated facility,
 * but one which is equally ready for use by metaprogrammers. In fact,
 * careful use of this preprocessor can allow you to create generic C
 * algorithms and simulate lambda functions.
 *
 * For example:
 */

#define ALL_ITEMS_IN_LIST(T, first, item, ...) \
do  {                                     \
    T * item = first;                     \
    while (item != NULL) {               \
        __VA_ARGS__;                      \
        item = item->next;                \
    }                                     \
} while(0)

#define ALL_FISH_IN_SEA(first_fish, ...) \
        ALL_ITEMS_IN_LIST(Fish, first_fish, fish, __VA_ARGS__)

/***
The first macro, ALL_ITEMS_IN_LIST, iterates through items in a linked list
and optionally performs some action on each of them. It requires that list
nodes are connected by a next pointer called next. The second macro,
ALL_FISH_IN_SEA, specialises the first: the node type is set to Fish *
and the list node iterator is called fish instead of item.
Here's an example of how we might use it:
***/

/**
 * @brief Find Nemos
 * @param fishes Linked list of fish
 * @returns The number of fish in the list called Nemo
 */

int findNemo(Fish * fishes)
{
    int count;

    ALL_FISH_IN_SEA(fishes,
        if (!strcmp(fish->name, "Nemo")) {
            printf("Found one!\n");
            ++count;
        }
        );

    return count;
}

/***
Note how simple it is to plug a code snippet into our generic looping construct.
I have used one of C99's variadic macros to do this (these are not yet part
of standard C++, but some compilers may support them).

--------

 = (array)+count; keep; keep = !keep)
****/

int main() {
  int a[] = { 1, 2, 3 };
  int sum = 0;
  foreach(int const* c, a)
    sum += *c;
  printf("sum = %d\n", sum);

  // multi-dim array
  int a1[][2] = { { 1, 2 }, { 3, 4 } };
  foreach(int (*c1)[2], a1)
    foreach(int *c2, *c1)
      printf("c2 = %d\n", *c2);
}


#define IMPLIES(x, y) (!(x) || (y))

#define COMPARE(x, y) (((x) > (y)) - ((x) < (y)))
#define SIGN(x) COMPARE(x, 0)

#define ARRAY_SIZE(a) (sizeof(a) / sizeof(*a))

#define SWAP(x, y, T) do { T tmp = (x); (x) = (y); (y) = tmp; } while(0)
#define SORT2(a, b, T) do { if ((a) > (b)) SWAP((a), (b), T); } while (0)

#define SET(d, n, v) do{ size_t i_, n_; for (n_ = (n), i_ = 0; n_ > 0; --n_, ++i_) (d)[i_] = (v); } while(0)
#define ZERO(d, n) SET(d, n, 0)

/****
void foo(int array[], int n) {
  assert(IMPLIES(n > 0, array != NULL));
  ...
****/

#define COLUMNS(S,E) [ (E) - (S) + 1 ]

struct
{
    char firstName COLUMNS ( 1, 20);
    char LastName  COLUMNS (21, 40);
    char ssn       COLUMNS (41, 49);
}

/***
This one is from linux kernel (gcc specific):
*/

#define container_of(ptr, type, member) ({                  \
const typeof( ((type *)0)->member ) *__mptr = (ptr);    \
    (type *)( (char *)__mptr - offsetof(type,member) ); })

/****
Another missing from other answers:
*/

#define LSB(x) ((x) ^ ((x) - 1) & (x))   // least significant bit

//NOTE: GCC extension !
#define max(a,b) ({typeof (a) _a=(a); typeof (b) _b=(b); _a > _b ? _a:_b; })
#define min(a,b) ({typeof (a) _a=(a); typeof (b) _b=(b); _a < _b ? _a:_b; })

#define LENGTH(array) (sizeof(array) / sizeof (array[0]))
#define QUOTE(name) #name
#define STR(name) QUOTE(name)

/****
This one works for one-dimensional arrays, but you need to pass it the element type:
*/
#define REQUIRE_ARRAY(T, X) (void)(sizeof (((char(*)(T(*)[]))0)(&(X))))

/***
The following works in C99 also for dimensions greater than 1.
You need to call REQUIRE_ARRAY2 for an array with 2 dimensions, for example:
*/
#define REQUIRE_ARRAY2(T, X) (void)(sizeof (((char(*)(T(*)[*][*]))0)(&(X))))

/***
Find the closest 32bit unsigned integer that is larger than x.
I use this to double the size of arrays (i.e. the high-water mark)
*/
#define kroundup32(x) (--(x), (x)|=(x)>>1, (x)|=(x)>>2, (x)|=(x)>>4, (x)|=(x)>>8, (x)|=(x)>>16, ++(x))


/***********
Indirectly quoting macro arguments

The "#" directive can also be used indirectly, in order to quote the "value"
of a macro instead of the name of that macro. For example, with the macro:
*
***/

#define FOO bar
#define QUOTEME_(x) #x
#define QUOTEME(x) QUOTEME_(x)

// the code

printf("FOO=%s\n", QUOTEME(FOO));

// will expand to

printf("FOO=%s\n", "bar");

/*** One common use for this technique is to convert the __LINE__ macro to a string. Eg:

QUOTEME(__LINE__);

is converted to:

"34"

if __LINE__ happens to have the value 34 when QUOTEME() is called.
On the other hand QUOTEME_(__LINE__) will expand to "__LINE__"


The "#" directive is also used to solve the following preprocessor brainteaser
(involving characters, as opposed to strings): Define a macro, CHAR(), which
takes a single input character X in the source program text and converts it
into the C-language character value of X; that is, such that
***/

printf("%c\n", CHAR(a))
printf("%c\n", CHAR(b))

/**
yields

a
b


Solution:

*/

#define CHAR(X)  #X[0]

/****************/

/***
The COMMENT macro is useful in creating flexible debug diagnostics that
can be removed by the preprocessor. As an example, I will define a macro
named DEBUG_ONLY. Preceding any line of code with the DEBUG_ONLY macro will
cause that line of code to be compiled only for debug builds.
For release builds, the DEBUG_ONLY macro will be interpreted by the preprocessor
as a single-line comment. The greatest advantage of this approach is that
any valid single-line expression can be used to convey debug information,
which makes this method more flexible than other parameterized macro approaches.
Also, this method is completely portable. The macros are defined as follows.
(Assume that in a debug build _DEBUG is defined for both the preprocessor
and the compiler, or substitute the symbol used by your compiler.)
***/

#define COMMENT SLASH(/)
#define SLASH(s) /##s

#if _DEBUG
    #define DEBUG_ONLY
#else
    #define DEBUG_ONLY COMMENT
#endif

/***
The macro can be used like this (in C++):
*/

DEBUG_ONLY if (x>100) std::cout << "WARNING! x=" << x <<"\n";
DEBUG_ONLY std::cout << "Hello World!\n";

/***
As a further refinement to this example, I’ve replaced DEBUG_ONLY cout
with the macro dout, which is short for debug output.
The macro is defined and used as follows:
*/

#if _DEBUG
#include <iostream>
#define dout std::cout
#else
#define dout COMMENT
#endif

dout << "Hello World!\n"; // Now doesn't that look sharp

/*****************/

#define NOP() // No operation

 Set other than 0 to 1

Set all values other than 0 to 1.

#define clamptoone(value) (!!(value))

/**********
use static const values instead of macros for constant values, integral
or other. The compiler can often optimize them away, and they remain a
1-st class citizen in the language's type system.
*********/

static const int DANGER = 60 + 2;

/*****
This latter example prints NAME, not what NAME is defined to,
which isn't what was intended. So, what can we do about it? Fortunately,
there is a standard solution for this:
*****/

#define STR_HELPER(x) #x
#define STR(x) STR_HELPER(x)

/*****
The solution to this is as easy as in the STR case above. You will have to
expand the macro in two steps. Typically you could define a generic macro
to glue anything together:
****/

#define GLUE_HELPER(x, y) x##y
#define GLUE(x, y) GLUE_HELPER(x, y)

/*****
Response to the MAX/MIN macros, taken from GCC hacks in the Linux kernel:
***/

#define min(x, y) ({                       \
        typeof(x) _min1 = (x);             \
        typeof(y) _min2 = (y);             \
        (void) (&_min1 == &_min2);         \
        _min1 < _min2 ? _min1 : _min2; })


#ifdefs
If #ifdefs are used the code looks like the following:
#ifdef MY_COOL_FEATURE
... included if "my cool feature" is used ...
#endif


#ifndef MY_COOL_FEATURE
... excluded if "my cool feature" is used ...
#endif
An application that uses #ifdefs normally doesn't have to have any special handling of configuration variables.
#ifs
When you are using #ifs the preprocessor symbols that are used are normally always defined. The symbols that correponds to the symbols used by #ifdef are either true or false, which could be represented by the integers 1 and 0, respectively.
#if MY_COOL_FEATURE
... included if "my cool feature" is used ...
#endif

#if !MY_COOL_FEATURE
... excluded if "my cool feature" is used ...
#endif

/*
For example, lets say you want to define an enum of colors and an
enum-to-string function, rather then list all the colors twice,
* you could create a file of the colors (colors.def):

c(red)
c(blue)
c(green)
c(yellow)
c(brown)

Now you can in your c file you can define your enum and your string conversion function:
*/

enum {
#define c(color) color,
# include "colors.def"
#undef c
};

const char *
color_to_string(enum color col)
{
    static const char *colors[] = {
#define c(color) #color,
# include "colors.def"
#undef c
    };
    return (colors[col]);
};

#if defined NDEBUG
    #define TRACE( format, ... )
#else
    #define TRACE( format, ... )   printf( "%s::%s(%d)" format, __FILE__, __FUNCTION__,  __LINE__, __VA_ARGS__ )
#endif

/*
Note that the lack of a comma between "%s::%s(%d)" and format is deliberate.
It prints a formatted string with source location prepended.
I work in real-time embedded systems so often I also include a timestamp in the output as well.
*/


#define COLUMNS(S,E) [ (E) - (S) + 1 ]

struct
{
    char firstName COLUMNS ( 1, 20);
    char LastName  COLUMNS (21, 40);
    char ssn       COLUMNS (41, 49);
}
