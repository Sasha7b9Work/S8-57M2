#pragma once


    typedef char *va_list; //-V677
    #define va_start(x, y) x = (char *)y;
    int vsprintf(void *, const void *, void *);
    #define va_end(x)
