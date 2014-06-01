#ifndef DOTPLOTRESULT_H
#define DOTPLOTRESULT_H

#include "core/Dump.h"

/// \class DotPlotResult
///
/// \brief Class that stores the result after closing a DotPlotDialog
///
/// \author Alexandre Audinot
///
/// \date 23/05/2014
///
class DotPlotResult
{
public:
    DotPlotResult(const Dump* dump1, const Dump* dump2, int diagSize);

    /// \brief Getter for m_dump1
    /// \return The dump chosen with the first combo box
    const Dump* getDump1() const;

    /// \brief Getter for m_dump2
    /// \return The dump chosen with the second combo box
    const Dump* getDump2() const;

    /// \brief Getter for m_diagSize
    /// \return The chosen minimum diagonal size for the DotPlot operation
    int getDiagSize() const;

    /// \brief Tests if the 2 dumps are the same
    /// \return True if the 2 dumps have the same bitstring
    bool sameDump() const;

private:
    const Dump* m_dump1;
    const Dump* m_dump2;
    int m_diagSize;
};

#endif // DOTPLOTRESULT_H
