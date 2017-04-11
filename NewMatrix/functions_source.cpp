#include "functions_headers.h"

using namespace STD_NAMESPACE;

void print(char simbol, int quantity)
{
    while(quantity--)
        STD_OUT_STREAM << simbol;
}
