#define TRY(x, y)   (x == y ? perror(NULL), exit(-1) : 0)
#define eprintf(…)  (fprintf (stderr, __VA_ARGS__))
