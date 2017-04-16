#include "functions_headers.h"

using namespace STD_NAMESPACE;

void print(char simbol, int quantity)
{
    while(quantity--)
        STD_OUT_STREAM << simbol;
}

void swap(void** a, void** b)
{
    void** temp = a;
    a = b;
    b = temp;
}

void swap(void* a, void* b)
{
    void* temp = a;
    a = b;
    b = temp;
}

