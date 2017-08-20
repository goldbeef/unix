/*************************************************************************
    > File Name: pop.cpp
    > Author: goldbeef
    > Mail: goldbeef@163.com 
    > Created Time: 2017年08月04日 星期五 13时01分50秒
 ************************************************************************/

#include <iostream>
using namespace std;

#define MAX_ELEMENT_NUM 100

class CPop
{
public:
    void show();
    void sort();
    void input();
private:
    int m_data[MAX_ELEMENT_NUM];
    int m_iElemNum;
};


void CPop::show()
{
    for (int i = 0; i < m_iElemNum && i < MAX_ELEMENT_NUM; i++)
    {
        cout << "\t" << m_data[i] << endl;
    }
}


void CPop::input()
{
    m_iElemNum = 0;
    int iVal;
    while (cin >> iVal && m_iElemNum < MAX_ELEMENT_NUM)
    {
        m_data[m_iElemNum++] = iVal;
    }
}

void CPop::sort()
{
    int i, j;
    int iTmp;
    for (i = 0; i < m_iElemNum - 1; i++)
    {
        for (j = i + 1; j < m_iElemNum; j++)
        {
            if (m_data[j] < m_data[j-1])
            {
                iTmp = m_data[j - 1];
                m_data[j - 1] = m_data[j];
                m_data[j] = iTmp;
            }
        }
    }
}

int main()
{
    CPop oPop;
    oPop.input();
    oPop.show();
    oPop.sort();
    oPop.show();
    return 0;
}
