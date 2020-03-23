#ifndef MATRIX_H
#define MATRIX_H
#include<iostream>
#include <stdio.h>
using namespace std;

class matrix
{

    int rows, cols, noOfElements;
    int **elemente;

    //--------HELPERS--------
    matrix trans();
    int commonElements(const matrix&) const;
    int zeroSum(const matrix&) const;
    int zeroDif(const matrix&) const;



    public:

        //------CREATION------

        matrix(); //constructor
        matrix(int, int, int, int**); //
        matrix(const matrix&);  //copy constructor
        ~matrix();  //destructor


        //-------GETTERS-------

        int getRows();
        int getCols();



        //-------OVERLOADING OPERATORS-------

        friend ostream& operator <<(ostream&, const matrix&);
        friend istream& operator >>(istream&, matrix&);
        matrix& operator=(const matrix&);
        friend matrix operator+(const matrix&, const matrix&);
        friend matrix operator-(const matrix&, const matrix&);
        friend matrix operator*(const matrix&, matrix&);
        friend matrix operator*(const int&, const matrix&);
        int* operator[](const int&) const ;
        friend matrix operator^(matrix&, const int&);
        bool operator==(const matrix&) const;

};

#endif // MATRIX_H
