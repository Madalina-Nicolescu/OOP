#include "matrix.h"
#include<iostream>
#include <stdio.h>

//------EXCEPTIONS------

class addNotPossible: public exception
{

    const char* what() const throw()
    {
        return "Nu se poate realiza adunarea. Dimensiunile matricilor nu se potrivesc.";
    }
};

class difNotPossible: public exception
{

    const char* what() const throw()
    {
        return "Nu se poate realiza diferenta. Dimenisunile matricilor nu se potrivesc.";
    }
};

class mulNotPossible: public exception
{

    const char* what() const throw()
    {
        return "Nu se poate realiza inmultirea. Dimenisunile matricilor nu se potrivesc.";
    }
};

class powNotPossible: public exception
{

    const char* what() const throw()
    {
        return "Nu se poate realiza ridicarea la putere. Matricea nu este patratica.";
    }
};

//------CREATION------


matrix::matrix(){

    this->rows = 0;
    this->cols = 0;
    this->noOfElements = 0;
    this->elemente = NULL;

} // constructor fara parametri

matrix::matrix(int n, int m, int noOfElements, int **elemente) // constructor cu parametri
{
    this->rows = n;
    this->cols = m;
    this->noOfElements = noOfElements;
    this->elemente = elemente;



}
matrix::matrix(const matrix& m1) // constructor de copiere
{
    this->rows = m1.rows;
    this->cols = m1.cols;
    this->noOfElements = m1.noOfElements;
    elemente = new int*[m1.noOfElements];
    for( int i = 0; i < m1.noOfElements; i++)
    {
        elemente[i] = new int[3];
    }
    for(int i = 0; i < m1.noOfElements; i++)
    {
        this->elemente[i][0] = m1.elemente[i][0];
        this->elemente[i][1] = m1.elemente[i][1];
        this->elemente[i][2] = m1.elemente[i][2];
    }
}


matrix::~matrix() // destructor
{
    rows = 0;
    cols = 0;
    for(int i = 0; i < noOfElements; i++)
        delete []elemente[i];
    delete []elemente;
    noOfElements = 0;
}




//--------HELPERS--------

int matrix::commonElements(const matrix& m2) const // elemente care se suprapun
{
    int noOfCommonEl = 0;
    for(int i = 0; i < noOfElements; i++)
    {
        for(int j = 0; j < m2.noOfElements; j++)
        {
            if(elemente[i][0]==m2.elemente[j][0] && elemente[i][1] == m2.elemente[j][1])
                noOfCommonEl++;
        }
    }

    return noOfCommonEl;
}

int matrix::zeroSum(const matrix& m2) const // elementele care se suprapun si a caror suma este nula
{
    int nrElem = 0;
    for(int i = 0; i < noOfElements; i++)
    {
        for(int j = 0; j < m2.noOfElements; j++)
        {
            if((elemente[i][0]==m2.elemente[j][0] && elemente[i][1] == m2.elemente[j][1]) && (elemente[i][2]+ m2.elemente[j][2] == 0))
                nrElem++;
        }
    }
    return nrElem;
}
int matrix::zeroDif(const matrix& m2) const // elementele care se suprapun si a caror diferenta este nula
{
    int nrElem = 0;
    for(int i = 0; i < noOfElements; i++)
    {
        for(int j = 0; j < m2.noOfElements; j++)
        {
            if((elemente[i][0] == m2.elemente[j][0] && elemente[i][1] == m2.elemente[j][1]) && (elemente[i][2] - m2.elemente[j][2] == 0))
                nrElem++;
        }
    }
    return nrElem;
}

matrix matrix::trans() // transpusa matricei
{
    int **t = new int*[noOfElements];
    for(int i = 0; i < noOfElements; i++)
        t[i] = new int[3];
    int k = 0;
    for(int i = 0; i < cols; i++)
        for(int j = 0; j < noOfElements; j++)
            if(i == elemente[j][1])
            {
                t[k][0] = i;
                t[k][1] = elemente[j][0];
                t[k][2] = elemente[j][2];
                k++;

            }
    matrix m(cols, rows, noOfElements, t);
    return m;
}



//-------GETTERS-------


int matrix::getCols() // obtinerea numarului de coloane
{
    return this->cols;
}

int matrix::getRows() // obtinerea numarului de linii
{
    return this->rows;
}


//-------OVERLOADING OPERATORS-------

istream& operator>>(istream& f, matrix& m) // citirea unei matrice
{
    f>>m.rows;
    f>>m.cols;
    f>>m.noOfElements;
    m.elemente = new int*[m.noOfElements];
    for( int i = 0; i < m.noOfElements; i++)
    {
        m.elemente[i] = new int[3];
        f>>m.elemente[i][0]>>m.elemente[i][1]>>m.elemente[i][2];
    }
    return f;
}


ostream& operator<<(ostream& g, const matrix& m) // scrierea unei matrice
{
    for(int i = 0; i < m.rows; i++)
    {
        for( int j = 0; j < m.cols; j++)
        {
            int ok = 0;
            for(int k = 0; k < m.noOfElements; k++)
            {
                if( (i == m.elemente[k][0]) && (j == m.elemente[k][1]))
                {
                    g<<m.elemente[k][2]<<" ";
                    ok = 1;
                }

            }
            if(ok == 0)
            {
                g<<"0 ";
            }

        }
        g<<endl;
    }
    return g;
}

matrix& matrix::operator=(const matrix& m2) // atribuire
{
   this->rows = m2.rows;
    this->cols = m2.cols;
    this->noOfElements = m2.noOfElements;
    this->elemente = new int*[m2.noOfElements];
    for( int i = 0; i < m2.noOfElements; i++)
    {
        elemente[i] = new int[3];
    }
    for(int i = 0; i < m2.noOfElements; i++)
    {
        this->elemente[i][0] = m2.elemente[i][0];
        this->elemente[i][1] = m2.elemente[i][1];
        this->elemente[i][2] = m2.elemente[i][2];
    }

    return *this;

}

matrix operator+(const matrix& m1, const matrix& m2) // suma intre doua matrice
{

    int i = 0, j = 0;
    int newSize = m1.noOfElements + m2.noOfElements - m1.commonElements(m2) - m1.zeroSum(m2) ;
    int **m3_elemente = new int*[newSize];
    for(int i = 0; i < newSize; i++)
        m3_elemente[i] = new int[3];

    if ((m1.rows != m2.rows)||(m1.cols != m2.cols))
    {
        throw addNotPossible();
    }

    int k = 0;
    while(i < m1.noOfElements && j < m2.noOfElements)
    {
        if((m1.elemente[i][0] < m2.elemente[j][0]) || ((m1.elemente[i][0] == m2.elemente[j][0]) && (m1.elemente[i][1] < m2.elemente[j][1])))
        {
            m3_elemente[k][0] = m1.elemente[i][0];
            m3_elemente[k][1] = m1.elemente[i][1];
            m3_elemente[k][2] = m1.elemente[i][2];
            k++;
            i++;

        }
        else if((m1.elemente[i][0] > m2.elemente[j][0]) || ((m1.elemente[i][0] == m2.elemente[j][0]) && (m1.elemente[i][1] > m2.elemente[j][1])))
        {
            m3_elemente[k][0] = m2.elemente[j][0];
            m3_elemente[k][1] = m2.elemente[j][1];
            m3_elemente[k][2] = m2.elemente[j][2];
            k++;
            j++;
        }
        else if((m1.elemente[i][0] == m2.elemente[j][0]) && (m1.elemente[i][1] == m2.elemente[j][1]) && (m1.elemente[i][2] + m2.elemente[j][2] != 0)) // daca suma e 0?
        {
            m3_elemente[k][0] = m2.elemente[j][0];
            m3_elemente[k][1] = m2.elemente[j][1];
            m3_elemente[k][2] = m1.elemente[i][2] + m2.elemente[j][2];
            k++;
            i++;
            j++;
        }


    }

    while(i < m1.noOfElements)
    {
        m3_elemente[k][0] = m1.elemente[i][0];
        m3_elemente[k][1] = m1.elemente[i][1];
        m3_elemente[k][2] = m1.elemente[i][2];
        k++;
        i++;
    }
    while(j < m2.noOfElements)
    {
        m3_elemente[k][0] = m2.elemente[j][0];
        m3_elemente[k][1] = m2.elemente[j][1];
        m3_elemente[k][2] = m2.elemente[j][2];
        k++;
        j++;
    }

    matrix m3(m1.rows, m1.cols, newSize, m3_elemente);
    return m3;
}


matrix operator-(const matrix& m1, const matrix& m2) // diferenta intre doua matrice
{

    int i = 0, j = 0;
    int newSize = m1.noOfElements + m2.noOfElements - m1.commonElements(m2) - m1.zeroDif(m2);
    int **m3_elemente = new int*[newSize];
    for(int i = 0; i < newSize; i++)
        m3_elemente[i] = new int[3];

    if ((m1.rows != m2.rows)||(m1.cols != m2.cols))
    {
        throw difNotPossible();
    }

    int k = 0;
    while(i < m1.noOfElements && j < m2.noOfElements)
    {
        if((m1.elemente[i][0] < m2.elemente[j][0]) || ((m1.elemente[i][0] == m2.elemente[j][0]) && (m1.elemente[i][1] < m2.elemente[j][1])))
        {
            m3_elemente[k][0] = m1.elemente[i][0];
            m3_elemente[k][1] = m1.elemente[i][1];
            m3_elemente[k][2] = m1.elemente[i][2];
            k++;
            i++;

        }
        else if((m1.elemente[i][0] > m2.elemente[j][0]) || ((m1.elemente[i][0] == m2.elemente[j][0]) && (m1.elemente[i][1] > m2.elemente[j][1])))
        {
            m3_elemente[k][0] = m2.elemente[j][0];
            m3_elemente[k][1] = m2.elemente[j][1];
            m3_elemente[k][2] = -m2.elemente[j][2];
            k++;
            j++;
        }
        else if((m1.elemente[i][0] == m2.elemente[j][0]) && (m1.elemente[i][1] == m2.elemente[j][1])&& (m1.elemente[i][2] - m2.elemente[j][2] != 0)) // daca suma e 0?
        {
            m3_elemente[k][0] = m2.elemente[j][0];
            m3_elemente[k][1] = m2.elemente[j][1];
            m3_elemente[k][2] = m1.elemente[i][2] - m2.elemente[j][2];
            k++;
            i++;
            j++;
        }


    }

    while(i < m1.noOfElements)
    {
        m3_elemente[k][0] = m1.elemente[i][0];
        m3_elemente[k][1] = m1.elemente[i][1];
        m3_elemente[k][2] = m1.elemente[i][2];
        k++;
        i++;
    }
    while(j < m2.noOfElements)
    {
        m3_elemente[k][0] = m2.elemente[j][0];
        m3_elemente[k][1] = m2.elemente[j][1];
        m3_elemente[k][2] = -m2.elemente[j][2];
        k++;
        j++;
    }

    matrix m3(m1.rows, m1.cols, newSize, m3_elemente);
    return m3;
}

int* matrix::operator[](const int& index) const // obtinerea unei linii
{
    int* linie = new int[cols];
    for(int i = 0; i < cols; i++)
    {
        int ok = 0;
        for(int j = 0; j < noOfElements; j++)
        {
            if(elemente[j][0] == index && elemente[j][1] == i)
            {
                linie[i] = elemente[j][2];
                ok = 1;
            }
        }
        if(ok == 0)
            linie[i] = 0;
    }
    return linie;
}

matrix operator*(const matrix& m1, matrix& m2) // inmultire intre doua matrice
{
    if(m1.cols != m2.rows)
        throw mulNotPossible();


    int *v = NULL;
    int *p = NULL;
    matrix t;
    t = m2.trans();
    int nr_elem = 0;

    for(int i = 0; i < m1.rows; i++)
    {
        v = m1[i];
        for(int j = 0; j < t.rows; j++)
        {
            p = t[j];
            int sum = 0;
            for(int k = 0; k < m1.cols; k++)
            {
                sum += v[k] * p[k];
            }
            if(sum != 0)
            {
                nr_elem++;

            }
        }
    }
    int **r = new int*[nr_elem];
    for(int i = 0; i < nr_elem; i++)
        r[i] = new int[3];
    int c = 0;
    for(int i = 0; i < m1.rows; i++)
    {
        v = m1[i];

        for(int j = 0; j < t.rows; j++)
        {
            p = t[j];
            int sum = 0;
            for(int k = 0; k < m1.cols; k++)
                sum += v[k] * p[k];
            if(sum != 0)
            {
                r[c][0] = i;
                r[c][1] = j;
                r[c][2] = sum;
                c++;
            }
        }
    }
    delete []v;
    delete[]p;

    matrix m3(m1.rows, m2.cols, nr_elem, r);
    return m3;

}

matrix operator^(matrix& m1, const int& x) // ridicare la putere
{
    matrix m;
    m = m1;

    if(m1.rows != m1.cols)
        throw powNotPossible();

    for(int i = 1; i < x; i++)
    {
        m = m*m1;
    }

    return m;
}

bool matrix::operator==(const matrix& m1) const
{
    if(rows != m1.rows || cols != m1.cols || noOfElements!= m1.noOfElements)
        return false;
    for(int i = 0; i < noOfElements; i++)
    {
        if(elemente[i][0] != m1.elemente[i][0] || elemente[i][1] != m1.elemente[i][1] || elemente[i][2] != m1.elemente[i][2])
            return false;
    }
    return true;

}
