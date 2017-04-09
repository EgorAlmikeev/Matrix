#ifndef GET_FROM_STD_ISTRAM_H
#define GET_FROM_STD_ISTRAM_H

#include "stream_defines.h"

template <class GetableType>
class GetFormStdIstream
{
public :
    static GetableType get();
};

#endif // GET_FROM_STD_ISTRAM_H
