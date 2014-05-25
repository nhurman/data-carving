#ifndef DOTPLOTRESULT_H
#define DOTPLOTRESULT_H


#include "core/Dump.h"

class DotPlotResult
{
public:
    DotPlotResult(Dump dump1, Dump dump2, int diagSize);
    Dump getDump1();
    Dump getDump2();
    int getDiagSize();
    bool sameDump();

private:
    Dump m_dump1;
    Dump m_dump2;
    int m_diagSize;
};

#endif // DOTPLOTRESULT_H
