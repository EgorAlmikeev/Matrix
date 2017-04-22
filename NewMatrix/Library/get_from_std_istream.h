#include <iostream>
#include "stream_defines.h"

using namespace STD_NAMESPACE;

#ifndef GET_FROM_STD_ISTREAM_H
#define GET_FROM_STD_ISTREAM_H

template <class GetableType>
class GetFormStdIstream
{
public :
    static GetableType get();

    class GetFromStdIstreamException
    {};
};

template <class GetableType>
GetableType GetFormStdIstream<GetableType>::get()
{
    GetableType getable_data;

    while(true)
    {
        STD_INPUT_STREAM.unsetf(ios::skipws);
        STD_INPUT_STREAM >> getable_data;
        STD_INPUT_STREAM.ignore(1);
        if(STD_INPUT_STREAM.good())
            break;
        STD_INPUT_STREAM.clear();
        STD_INPUT_STREAM.ignore(10, '\n');
        throw GetFromStdIstreamException();
    }

    STD_INPUT_STREAM.setf(ios::skipws);

    return getable_data;
}

#endif // GET_FROM_STD_ISTREAM_H
