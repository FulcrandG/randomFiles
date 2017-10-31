#define TRY(x, y)   x == y ? perror(NULL), exit(-1) : 0
