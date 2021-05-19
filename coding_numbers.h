#ifndef CODING_NUMBERS_H
#define CODING_NUMBERS_H

#include <vector>
#include <list>
#include <bitset>

static constexpr int start_stop = 99;

static std::vector<std::pair<int, std::string>> coding_table = {
    {start_stop , "01010010010"  },
    {0          , "0101010100"   },
    {1          , "00101010100"  },
    {2          , "01001010100"  },
    {3          , "001001010100" },
    {4          , "01010010100"  },
    {5          , "00101001010"  },
    {6          , "01001001010"  },
    {7          , "01010100100"  },
    {8          , "00101010010"  },
    {9          , "0010101010"   },
    {10         , "0101001010"   },
    {start_stop , "01010010010"  },
};

class barcode
{
    std::vector<int> m_data;
    std::vector<int> m_result;
public:
    void DecryptBarcode();
    void operator<<(int data);
private:
    std::vector<int>::iterator FindStartStop();
    bool ParseData(std::vector<int> array, const std::string &byte);
    bool CalculateCheckSum();
    void PrintResult();
};

#endif // CODING_NUMBERS_H
