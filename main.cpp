#include <iostream>
#include <stdio.h>
#include "matrix.h"
#include<cassert>
using namespace std;


int main()
{
    matrix m1;
    matrix m2, m_suma, m_dif, m_mul, m_pow,m3;

    cin>>m1;
    cin>>m2;
    cin>>m_suma;
    cin>>m_dif;
    cin>>m_mul;
    cin>>m_pow;

    assert(m1+m2 == m_suma);
    assert(m1-m2 == m_dif);
    assert(m1*m2 == m_mul);
    assert((m1^2) == m_pow);
    assert(m1.getCols()==3);
    assert(m1.getRows()==3);
    assert((m3=m1)== m1);




    return 0;
}
