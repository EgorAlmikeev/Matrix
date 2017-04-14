#include "functions_headers.h"

using namespace STD_NAMESPACE;

void print(char simbol, int quantity)
{
    while(quantity--)
        STD_OUT_STREAM << simbol;
}

template <class Type>
void swap(Type** a, Type** b)
{
    Type* temp = a;
    a = b;
    b = temp;
}

template <class Type>
void swap(Type* a, Type* b)
{
    Type* temp = a;
    a = b;
    b = temp;
}
