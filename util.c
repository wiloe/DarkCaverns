/*
 * util.c - Miscellaneous utility fns
 */


/* Determine the endianness of the system we're running on. */
bool system_is_little_endian() {
    unsigned int x = 0x76543210;
    char *c = (char*) &x; 
    if (*c == 0x10) { return true; }
    return false;
}



/* Convert a character string representing a hex value to an int */
int xtoi(char *hexstring) {
	int	i = 0;
	
	if ((*hexstring == '0') && (*(hexstring+1) == 'x')) {
		  hexstring += 2;
	}

	while (*hexstring) {
		char c = toupper(*hexstring++);
		if ((c < '0') || (c > 'F') || ((c > '9') && (c < 'A'))) {
			break;
		}
		c -= '0';
		if (c > 9) {
			c -= 7;
		}
		i = (i << 4) + c;
	}

	return i;
}


/* String Manipulation Helpers *******************************************************************/

#ifndef HAVE_ASPRINTF
#include <stdio.h>  //vsnprintf
#include <stdlib.h> //malloc
#include <stdarg.h> //va_start et al

int asprintf(char **str, char* fmt, ...){
    va_list argp;
    va_start(argp, fmt);
    char one_char[1];
    int len = vsnprintf(one_char, 1, fmt, argp);
    if (len < 1){
        fprintf(stderr, "An encoding error occurred. Setting the input pointer to NULL.\n");
        *str = NULL;
        return len;
    }
    va_end(argp);

    *str = malloc(len+1);
    if (!str) {
        fprintf(stderr, "Couldn't allocate %i bytes.\n", len+1);
        return -1;
    }
    va_start(argp, fmt);
    vsnprintf(*str, len+1, fmt, argp);
    va_end(argp);
    return len;
}
#endif

/* Macro for clean string extending with formatting */
#define sasprintf(write_to, ...) {		\
	char *temp = (write_to);			\
	asprintf(&(write_to), __VA_ARGS__);	\
	free(temp);							\
}
