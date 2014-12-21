#include <sys.h>
#include <lib.h>
#include <const.h>

typedef char *va_list;
/* integer to array 
 * modify from
 * http://blog.csdn.net/wesley1991/article/details/5430350 */

char* itoa(int value, char *str, int radix){
    char reverse[36];   
    char *p = reverse;
    bool sign = (value > 0)?TRUE:FALSE;
    value = (value > 0)?value:-value;
    *p++ = '\0';
    while (value > 0){
        *p++ = "0123456789abcdef"[value%radix];
        value /= radix;
    }
    if (!sign) *p = '-';
    else p--;
    while (p >= reverse){
        *str++ = *p--;
    }
    return str;
}

int vsprintf(char *buf, const char *fmt, va_list args){
    char *p;
    va_list p_next_arg = args;
    for (p = buf; *fmt; fmt++){
        if (*fmt != '%'){
            *p++ = *fmt;
            continue;
        }
        fmt++;  // *fmt = '%'
        switch (*fmt){
            case 'd':
                itoa(p_next_arg,p,10);
                p_next_arg += 4;
                p += strlen(p);
                break;
            default:
                break;
        }
    }
    return 0;
}
int printf(const char *fmt, ...){
    char buf[256];
    va_list arg = (va_list)((char *)(&fmt) + 4);
    vsprintf(buf, fmt, arg);
    puts(buf);
    return 0;
}

