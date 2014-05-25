#include "DotPlotResult.h"

DotPlotResult::DotPlotResult(Dump dump1, Dump dump2, int diagSize) :
    m_dump1(dump1), m_dump2(dump2), m_diagSize(diagSize)
{

}

Dump DotPlotResult::getDump1()
{
    return m_dump1;
}

Dump DotPlotResult::getDump2()
{
    return m_dump2;
}

int DotPlotResult::getDiagSize()
{
    return m_diagSize;
}

bool DotPlotResult::sameDump()
{
    return m_dump1.bitString() == m_dump2.bitString();
}
