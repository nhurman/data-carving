#include "Sixbit.h"
#include <sstream>
#include <iomanip>
#include <QDebug>

Sixbit::Sixbit() : Encoding()
{

}

Sixbit::Sixbit(BitString const* bs) : Encoding(bs)
{

}

Sixbit::~Sixbit()
{

}


size_t Sixbit::BytesPerLine() const
{
    return 16;
}

size_t Sixbit::LineHeight() const
{
    return 17;
}

size_t Sixbit::LineWidth() const
{
    return 150;
}

size_t Sixbit::lines() const
{
    if (!m_bitString) {
        return 0;
    }

    return ceil((float)m_bitString->size() / (BitPerChar() * BytesPerLine()));
}

size_t Sixbit::BitPerChar() const
{
    return 6;
}

std::string Sixbit::toHTML() const
{
    if (!m_bitString) {
        return std::string();
    }

    std::stringstream os;
    os << "<style>i{font-style: normal;color: #7F7F7F}";
    os << "b{font-weight:normal}";
    os << "i,b{font-size:14px}</style>";

    for (size_t i = 0; i < m_bitString->size(); i += 8) {
        unsigned char byte = 0;
        for (char j = 0; j < 8; ++j) {
            byte += ((*m_bitString)[i + j] ? 1 : 0) << (7 - j);
            // magic for sixbit, should not be here
            byte+=32;
        }

        int mod = (i/8) % BytesPerLine();
        if (i == 0 || mod == 0) {
            if (i != 0) {
                os.seekp(-1, std::ios_base::cur);
                os << "</b>" << std::endl;
            }

            os << "<b>";
        }

        if (byte < 32 || byte > 126) {
            byte = '.';
            os << "<i>.</i>";
        }
        else {
            os << byte;
        }
    }

    if (m_bitString->size() > 0) {
        os.seekp(-1, std::ios_base::cur);
        os << "</b>";
    }

    return os.str();
}
