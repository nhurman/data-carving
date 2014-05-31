#include "ASCII.h"


ASCII::ASCII() : Encoding()
{

}

ASCII::ASCII(BitString const* bs) : Encoding(bs)
{

}

ASCII::~ASCII()
{

}

size_t ASCII::BytesPerLine() const
{
    return 16;
}

size_t ASCII::LineHeight() const
{
    return 17;
}

size_t ASCII::LineWidth() const
{
    return 135;
}

size_t ASCII::BitPerChar() const
{
    return 8;
}

size_t ASCII::lines() const
{
    if (!m_bitString) {
        return 0;
    }

    return ceil((float)m_bitString->size() / (BitPerChar() * BytesPerLine()));
}

std::string ASCII::toHTML() const
{
    if (!m_bitString) {
        return std::string();
    }

    std::stringstream os;
    os << "<style>i{font-style: normal;color: #7F7F7F}";
    os << "b{font-weight:normal}";
    os << "i,b{font-size:14px}</style>";
    os << "<b>";

    for (size_t i = 0; i < m_bitString->size(); i += BitPerChar()) {
        unsigned char byte = 0;
        for (uchar j = 0; j < BitPerChar(); ++j) {
            byte += ((*m_bitString)[i + j] ? 1 : 0) << (7 - j);
        }

        if (byte < 32 || byte > 126) {
            byte = '.';
            os << "<i>.</i>";
        }
        else {
            if (byte == '<') os << "&lt;";
            else if (byte == '&') os << "&amp;";
            else os << byte;
        }

        if (0 != i && (i / BitPerChar() + 1) % BytesPerLine() == 0)
            os << "</b>" << std::endl << "<b>";

    }

    os << "</b>";
    return os.str();
}

