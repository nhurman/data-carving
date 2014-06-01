#include "DotPlotResult.h"

DotPlotResult::DotPlotResult(const Dump* dump1, const Dump* dump2, int diagSize) :
    m_dump1(dump1), m_dump2(dump2), m_diagSize(diagSize)
{

}

const Dump* DotPlotResult::getDump1() const
{
    return m_dump1;
}

const Dump* DotPlotResult::getDump2() const
{
    return m_dump2;
}

int DotPlotResult::getDiagSize() const
{
    return m_diagSize;
}

bool DotPlotResult::sameDump() const
{
    return *(m_dump1->bitString()) == *(m_dump2->bitString());
}
