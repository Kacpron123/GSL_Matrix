#ifndef MATRIX_H_
#define MATRIX_H_

#include "gsl_math.h"
#include "gsl_linalg.h"

#include <vector>
#include <functional>
class Matrix{
private:
gsl_matrix* _matrix;
void print(double) const;
class Row{
    private:
        double* m_data;
        int m_width;
    public:
        Row(double* data,int width);
        ~Row();
        size_t size() const;
        double& operator[](int j);
    };
    struct _size{
       size_t x;
       size_t y;
    };
    public:
    /// @brief deconstructor
    ~Matrix();
    /// @brief create Matrix rows x cols and fill with fill value
    /// @param rows number of rows
    /// @param col number of cols
    Matrix(int rows,int col,int fill=0);
    //copy constructor
    Matrix(const Matrix &copy);
    //copy constructor
    Matrix(const Matrix &&copy);
    /// @brief constructor from vector
    Matrix(std::vector<std::vector<double>> vector);
    //copy constructor
    Matrix(gsl_matrix *copy);
    /// @brief filling Matrix from vector
    void fill(std::vector<std::vector<double>> c);
    /// @brief filling Matrix from function
    void fill(std::function<double(int,int)> func);
    /// @brief printing content of Matricx
    void print() const;
    /// @brief printing content of Matricx
    static void print(gsl_matrix *matrix);
    /// @brief transpose Matrix
    Matrix transpose();
    /// @brief inverse Matrix 
    Matrix inverse();
    /// @brief size of Matrix
    /// @return size{x,y}
    _size size() const;
    /// @brief copy operator
    Matrix& operator=(const Matrix& other);
    /// @brief pointer opetor
    /// @return pointer to gsl_matrix
    gsl_matrix* operator*();
    /// @brief double convertion operator
    operator double();
    /// @operator accesing maitrix[y][x]
    Row operator[](int j);
    /// @brief multiplication of Matrixies
    Matrix operator*(Matrix O);
    /// @brief addition of Matrixies
    Matrix operator+(Matrix O);
    /// @brief substraction of Matrixies
    Matrix operator-(Matrix O);
    /// @brief multiplication of Matrix and scalar
    Matrix operator*(double scalar);
    friend Matrix operator*(double scalar,Matrix O);
    /// @brief division of Matrix and scalar
    Matrix operator/(double scalar);
};
#endif