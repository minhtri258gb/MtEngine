#define __MT_STRING_UTILS_CPP__

#include <stdarg.h>
#include <sstream>

#include "common.h"
#include "StringUtils.h"

using namespace std;
using namespace mt::engine;

int StringUtils::parseInt(std::string str)
{
	int num;
	stringstream ss;
	ss << str;
	ss >> num;
	return num;
}


// string StringUtils::format(char *fmt, ...)
// {
//     va_list ap;
//     va_start(ap, fmt);

// 	char str[80];

//    sprintf(str, "Gia tri cua Pi = %f", M_PI);
//    puts(str);
   
//    return(0);

// 	sprintf()

// 	vsprintf (buf, fmt, va);


//     int max = va_arg(ap, int);
//     for(int i = 2; i <= n_args; i++) {
//         int a = va_arg(ap, int);
//         if(a > max) max = a;
//     }
//     va_end(ap);
//     return max;
// }