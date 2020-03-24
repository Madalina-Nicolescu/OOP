#include <iostream>
#include <stdio.h>
#include "matrix.h"
#include<cassert>
#include<fstream>
using namespace std;

ifstream f("input.txt");

void Test()
{
     matrix m1;
    matrix m2, m_suma, m_dif, m_mul, m_pow,m3;

    f>>m1;
    f>>m2;
    f>>m_suma;
    f>>m_dif;
    f>>m_mul;
    f>>m_pow;

    assert(m1+m2 == m_suma);
    assert(m1-m2 == m_dif);
    assert(m1*m2 == m_mul);
    assert((m1^2) == m_pow);
    assert(m1.getCols()==3);
    assert(m1.getRows()==3);
    assert((m3=m1)== m1);
    int *v = new int[3]{0, 0, 3};
    int *p = m1[1];
    for(int i = 0; i < 3; i++)
    {
        assert(v[i]==p[i]);
    }
    cout<<"Testele au trecut";

}


int main()
{
    Test();

    return 0;
}
