#pragma
#include <vector>
#include <deque>

static constexpr int start_stop = 99;
using table_number = std::pair<int, std::vector<float>>;
using container = std::vector<table_number>;

static container coding_table2 = {
    {start_stop,    {0, 1, 0, 1, 0, 0, 1, 0, 0, 1, 0    }},
    {0,             {0, 1, 0, 1, 0, 1, 0, 1, 0, 0       }},
    {1,             {0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0    }},
    {2,             {0, 1, 0, 0, 1, 0, 1, 0, 1, 0, 0    }},
    {3,             {0, 0, 1, 0, 0, 1, 0, 1, 0, 1, 0, 0 }},
    {4,             {0, 1, 0, 1, 0, 0, 1, 0, 1, 0, 0    }},
    {5,             {0, 0, 1, 0, 1, 0, 0, 1, 0, 1, 0    }},
    {6,             {0, 1, 0, 0, 1, 0, 0, 1, 0, 1, 0    }},
    {7,             {0, 1, 0, 1, 0, 1, 0, 0, 1, 0, 0    }},
    {8,             {0, 0, 1, 0, 1, 0, 1, 0, 0, 1, 0    }},
    {9,             {0, 0, 1, 0, 1, 0, 1, 0, 1, 0       }},
    {10,            {0, 1, 0, 1, 0, 0, 1, 0, 1, 0       }},
    {start_stop,    {0, 1, 0, 1, 0, 0, 1, 0, 0, 1, 0    }},
};

class barcode
{
    std::vector<float> m_data;
    std::deque<int> m_result;
public:
    void DecryptBarcode();
    void operator<<(float data);
private:
    bool ParseData(std::vector<float> array, const std::vector<float>& number);
    bool AnalyzeResult();
    void PrintResult();
    bool ApproximatelyEqual(float a, float b, float epsilon);

};
