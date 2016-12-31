#include "staticfunctions.h"

StaticFunctions::StaticFunctions()
{

}


QString StaticFunctions::timeFormat(int seconds)
{
    if(seconds>3599)
    {
        return QString("h:m:ss");
    }
    else
    {
        return QString("m:ss");
    }
}
