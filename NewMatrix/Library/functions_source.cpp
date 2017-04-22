#include "functions_headers.h"

using namespace STD_NAMESPACE;

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

int pow(int a, int b)
{
    return (b == 0) ? 1 : (b == 1) ? a : a * pow(a, b - 1);
}
