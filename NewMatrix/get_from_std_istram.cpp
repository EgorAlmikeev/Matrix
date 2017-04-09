#include <iostream>
#include "get_from_std_istram.h"

using namespace STD_NAMESPACE;

template <class GetableType>
GetableType GetFormStdIstream<GetableType>::get()
{
    GetableType getable_data;

    while(true)
    {
        STD_INPUT_STRAM >> getable_data;
        if(STD_INPUT_STRAM.good())
            break;
        STD_INPUT_STRAM.clear();
        STD_INPUT_STRAM.ignore(10, '\n');
        ERROR_STREAM << "\n#error : STD INPUT ERROR\n";
    }

    return getable_data;
}
