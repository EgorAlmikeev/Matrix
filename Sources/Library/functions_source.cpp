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
