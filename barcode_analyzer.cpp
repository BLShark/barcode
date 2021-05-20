#include "barcode_analyzer.h"
#include <iostream>
#include <sstream> //stringstream
#include <math.h> //fabs
#include <algorithm> //for_each

void barcode::DecryptBarcode()
{
    auto decrypt = [this](){
        for(auto index = 0; index < m_data.size(); index++)
        {
            for(auto number = 0; number < coding_table2.size(); number++)
            {
                table_number tmp = coding_table2.at(number);
                if (ParseData({m_data.begin() + index, m_data.end()}, tmp.second))
                {
                    //we found the number
                    m_result.push_back(tmp.first);
                    index += tmp.second.size();
                    break;
                }
            }
        }
    };

    decrypt();
    if (m_result.empty() || m_result.at(0) != start_stop)
    {
        //we should reverse numbers from the coding table to cover flipped barcode!
        for(auto& number : coding_table2)
        {
            std::reverse(number.second.begin(), number.second.end());
        }

        //again start decrypt with reverse numbers
        m_result.clear();
        decrypt();
        std::reverse(m_result.begin(), m_result.end());
    }

    if (m_result.front() == start_stop && m_result.back() == start_stop)
    {
        //the barcode was read correctly. remove start/stop symbol and analyze result!
        m_result.pop_back();
        m_result.pop_front();

        if (AnalyzeResult())
        {
            PrintResult();
        }
        else
        {
            std::cout<<"Wrong barcode!!! The checksum is not correct"<<std::endl;
        }
    }
    else if (m_result.front() == start_stop)
    {
        std::cout<<"Barcode truncated. Move the scanner to the right." <<std::endl;
    }
    else if (m_result.back() == start_stop)
    {
        std::cout<<"Barcode truncated. Move the scanner to the left." <<std::endl;
    }
}

void barcode::operator <<(float data)
{
    m_data.push_back(data);
}

bool barcode::ParseData(std::vector<float> array, const std::vector<float> &number)
{
    bool result = true;
    for (int var = 0; var < number.size() && var < array.size() ; ++var) {
        if (ApproximatelyEqual(array.at(var), number.at(var), 0.65f))
        {
            result &= true;
        }
        else
        {
            result &= false;
        }
    }
    return result;
}


bool barcode::AnalyzeResult()
{
    int C = 0;
    int K = 0;

    // we substract 2 becase at the m_result we have C and K
    const auto barcode_size = m_result.size() - 2;
    {
        //calculate C
        for (auto index = 1; index <= barcode_size; index++)
        {
            C += ((barcode_size - index) % 10 + 1) * m_result.at(index - 1);
        }
        C = C % 11;
    }

    {
        //calculate K
        for (auto index = 1; index <= barcode_size + 1; index++)
        {
            K += ((barcode_size - index + 1) % 9 + 1) * m_result.at(index - 1);
        }
        K = K % 11;
    }

    return m_result.at(barcode_size) == C && m_result.back() == K;
}

void barcode::PrintResult()
{
    {
        //remove C & K
        m_result.erase(m_result.end()-2, m_result.end());
    }

    for(const auto& x: m_result )
    {
        if (x == 10) std::cout<<"-";
        else std::cout<<x;
    }
    std::cout<<std::endl;
}

bool barcode::ApproximatelyEqual(float a, float b, float epsilon)
{
    if (fabs(a - b) < epsilon)
    {
        return true; // they are same
    }
    return false; // they are not same
}
