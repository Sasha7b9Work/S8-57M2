#include "defines.h"
#include "Hardware/HAL/HAL.h"


void HAL::ErrorHandler(const char *, int)
{
    while (true) {};
}
