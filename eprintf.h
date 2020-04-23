#include <stdlib.h>

/* eprintf.h: error wrapper functions */
extern void eprintf(char *, ...);
extern void weprintf(char *, ...);
extern char *estrdup(char *);
extern void *emalloc(size_t);
extern void *erealloc(void *, size_t);
