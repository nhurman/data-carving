#ifndef DOTPLOTRESULT_H
#define DOTPLOTRESULT_H


#include "core/Dump.h"

class DotPlotResult
{
public:
    DotPlotResult(Dump dump1, Dump dump2);
    Dump getDump1();
    Dump getDump2();
    bool sameDump();

private:
    Dump m_dump1;
    Dump m_dump2;
};

#endif // DOTPLOTRESULT_H
