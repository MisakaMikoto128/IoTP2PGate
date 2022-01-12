#include <stdbool.h>
#include <stdio.h>
#include <stdarg.h>
static bool debug_on = false;

void debug_print(const char *fmt, ...)
{
    if (debug_on)
    {
        va_list ap;
        va_start(ap, fmt);
        vprintf(fmt, ap);
        va_end(ap);
    }
}

void set_debug_on()
{
    debug_on = true;
}

void set_debug_off()
{
    debug_on = false;
}
