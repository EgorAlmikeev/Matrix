#include "functions_headers.h"
#include "stream_defines.h"
#include <iostream>

using namespace STD_NAMESPACE;

void print(char simbol, int quantity)
{
    while(quantity--)
        STD_OUT_STRAM << simbol;
}
