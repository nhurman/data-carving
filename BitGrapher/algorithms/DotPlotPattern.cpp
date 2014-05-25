#include "DotPlotPattern.h"

//Return a list with all the diagonals, without doubles
std::list<Diagonal> BitString::dotPlotPattern(const BitString *dump, unsigned int minDiagSize) const {
    std::list<Diagonal> listDiag;
    unsigned int z = 0;

    for (unsigned int y = 0; y <= dump->m_size - minDiagSize ; y++){
        for (unsigned int x = 0; x <= this->m_size - minDiagSize; x++ ){
            if (( x!= 0 && y != 0) ? (((dump->m_bytes[(y-1) / 8] & (1 << ((y-1) % 8))) >> ((y+z) % 8)) != ((this->m_bytes[(x-1) / 8] & (1 << ((x-1) % 8))) >> ((x+z) % 8))) : true) {
                for( z = 0; x+z < this->m_size && y+z < dump->m_size ; z++){
                    //std::cout << z << " " << (dump->m_bytes[(y+z) / 8] & (1 << ((y+z) % 8))) << " " << (this->m_bytes[(x+z) / 8] & (1 << ((x+z) % 8))) << std::endl;
                    if (((dump->m_bytes[(y+z) / 8] & (1 << ((y+z) % 8))) >> ((y+z) % 8)) != (((this->m_bytes[(x+z) / 8] & (1 << ((x+z) % 8))) >> ((x+z) % 8)))) {
                       break;
                    }
                }
                if (z >= minDiagSize) {
                    //std::cout << "hello" << std::endl;
                    listDiag.push_back(Diagonal(x, y, z));
                }
            }
        }
    }
    return listDiag;
}

std::list<Diagonal> BitString::dotPlotPattern(unsigned int minDiagSize) const {
    std::list<Diagonal> listDiag;
    unsigned int z;

    listDiag.push_back(Diagonal(0, 0, m_size));

    for (unsigned int y = 0; y <= m_size - minDiagSize ; y++){
        for (unsigned int x = 0; x < y; x++ ){
            if (( x!= 0) ? ((m_bytes[(y-1) / 8] & (1 << ((y-1) % 8))) != (m_bytes[(x-1) / 8] & (1 << ((x-1) % 8)))) : 1) {
                for( z = 0; x+z < m_size && y+z < m_size ; z++){
                    if (!((m_bytes[(y+z) / 8] & (1 << ((y+z) % 8))) == (m_bytes[(x+z) / 8] & (1 << ((x+z) % 8))))) {
                       break;
                    }
                }
                if (z >= minDiagSize) {
                    listDiag.push_back(Diagonal(x, y, z));
                    listDiag.push_back(Diagonal(y, x, z));
                }
            }
        }
    }
    return listDiag;
}
