#include "Hexadecimal.h"

Hexadecimal::Hexadecimal() : Encoding()
{

}

Hexadecimal::Hexadecimal(BitString const* bs) : Encoding(bs)
{

}

Hexadecimal::~Hexadecimal()
{

}

size_t Hexadecimal::BytesPerLine() const
{
    return 16;
}

size_t Hexadecimal::LineHeight() const
{
    return 17;
}

size_t Hexadecimal::LineWidth() const
{
    return 450;
}

size_t Hexadecimal::lines() const
{
    if (!m_bitString) {
        return 0;
    }

    return ceil((float)m_bitString->size() / (8 * BytesPerLine()));
}

std::string Hexadecimal::toHTML() const
{
    if (!m_bitString) {
        return std::string();
    }

    std::stringstream os;
    os << "<style>i{font-style: normal;color: #008ec3}";
    os << "b{font-weight:normal}";
    os << "i,b{font-size:14px}</style>";

    os << std::hex << std::setfill('0');

    for (size_t i = 0; i < m_bitString->size(); i += 8) {
        unsigned char byte = 0;
        for (char j = 0; j < 8; ++j) {
            byte += ((*m_bitString)[i + j] ? 1 : 0) << (7 - j);
        }

        char str[3];
        itoa(byte, str, 16);
        if (str[1] == '\0') {
            str[1] = str[0];
            str[0] = '0';
            str[2] = '\0';
        }

        str[0] = toupper(str[0]);
        str[1] = toupper(str[1]);

        int mod = (i/8) % BytesPerLine();
        if (i == 0 || mod == 0) {
            if (i != 0) {
                os.seekp(-1, std::ios_base::cur);
                os << "</b>" << std::endl;
            }
            os << "<i>" << std::setw(8) << i/8 << "</i> <b>" << std::setw(2);
        }

        os << str << ' ';
    }

    if (m_bitString->size() > 0) {
        os.seekp(-1, std::ios_base::cur);
        os << "</b>";
    }

    return os.str();
}
