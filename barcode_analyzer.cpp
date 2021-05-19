#include "barcode_analyzer.h"
#include <iostream>
#include <sstream> //stringstream
#include <math.h> //fabs

void barcode::DecryptBarcode()
{

    //Find Start/Stop msg
    auto index_pos = FindStartStop();
    if ( index_pos != m_data.end())
    {
        //remove front bytes +1 for the empty sector
        m_data.erase(m_data.begin(), index_pos + 1);

        //now we can find the real data for every number
        for(auto index = 0; index < m_data.size(); index++)
        {
            for(auto number = 1; number < coding_table.size(); number++)
            {
                std::pair<int, std::string> tmp = coding_table.at(number);
                if (ParseData({m_data.begin(), m_data.begin() + tmp.second.size()} , tmp.second))
                {
                    //we found the number
                    m_data.erase(m_data.begin(), m_data.begin() + tmp.second.size() + 1 );
                    m_result.push_back(tmp.first);
                    break;
                }
            }
        }

        //barcode decryption finished
        if (m_result.back() == start_stop)
        {
            //remove last start_stop symbol
            m_result.pop_back();
            if (AnalyzeResult())
            {
                PrintResult();
            }
            else
            {
                //try to revert data array
                //AnalyzeResult();
            }
        }
        else
        {
            std::cout<<"Barcode truncated. Move the scanner to the left."<<std::endl;
        }
    }
    else
    {
        std::cout<<"Barcode truncated. Move the scanner to the right."<<std::endl;
    }
}

void barcode::operator <<(int data)
{
    m_data.push_back(data);
}

std::vector<double>::iterator barcode::FindStartStop()
{
    std::string start_stop("01010010010");
    for (auto index = m_data.begin(); index + start_stop.size() < m_data.end(); ++index)
    {
        std::stringstream ss;
        for (auto i = 0; i < start_stop.size(); i++)
        {
            ss << *(index + i);
        }
        if (start_stop == ss.str())
        {
            //we should pop the bytes we found!!!
            return index + start_stop.size();
        }
    }
    return {};
}

bool barcode::ParseData(std::vector<double> array, const std::string &byte)
{
    std::stringstream bit_sequence;
    for (size_t index = 0; index < array.size(); index ++)
    {
        bit_sequence<< array.at(index);
    }

    return byte == bit_sequence.str();
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

bool barcode::approximatelyEqual(float a, float b, float epsilon)
{
    //approximatelyEqual(0.19f, 0.55, 0.65)<<endl;
    return fabs(a - b) <= ( (fabs(a) < fabs(b) ? fabs(b) : fabs(a)) * epsilon);
}
