#ifndef COLORS_H
#define COLORS_H

#include <iostream>

/* FOREGROUND */

#define DEFAULT  "\x1B[0m"
#define RED  "\x1B[31m"
#define GREEN  "\x1B[32m"
#define YELLOW  "\x1B[33m"
#define BLUE  "\x1B[34m"
#define MAGENTA  "\x1B[35m"
#define CYAN  "\x1B[36m"
#define WHITE  "\x1B[37m"

#define FRED(x) RED x DEFAULT
#define FGRN(x) GREEN x DEFAULT
#define FYEL(x) YELLOW x DEFAULT
#define FBLU(x) BLUE x DEFAULT
#define FMAG(x) MAGENTA x DEFAULT
#define FCYN(x) CYAN x DEFAULT
#define FWHT(x) WHITE x DEFAULT

#define BOLD(x) "\x1B[1m" x DEFAULT

#define UNDL(x) "\x1B[4m" x DEFAULT


#endif  /* _COLORS_ */

