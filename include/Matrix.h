#ifndef MATRIX_H_
#define MATRIX_H_

#include "gsl_math.h"
#include "gsl_linalg.h"

#include <vector>
class Matrix{
private:
gsl_matrix* _matrix;
void print(double) const;
class Row{
    private:
        double* _data;
        int _width;
    public:
        Row(double* data,int width):_data(data),_width(width){};
        ~Row(){_data=nullptr;}
        size_t size() const{return _width;}
        double& operator[](int j){return _data[j*_width];}
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
    /// @brief constructor from vector
    Matrix(std::vector<std::vector<double>> vector);
    //copy constructor
    Matrix(gsl_matrix *copy);
    /// @brief filling Matrix from vector
    void fill(std::vector<std::vector<double>> c);
    /// @brief printing content of Matricx
    void print() const;
    static void print(gsl_matrix *matrix);
    Matrix transpose();
    /// @brief size of Matrix
    /// @return size{x,y}
    _size size() const;
    /// @brief copy operator
    Matrix& operator=(const Matrix& other);
    /// @brief pointer opetor
    /// @return pointer to gsl_matrix
    gsl_matrix* operator*(){return _matrix;}
    /// @operator accesing maitrix[y][x]
    Row operator[](int j);
    /// @brief multiplication of Matrixies
    Matrix operator*(Matrix &O);
};
#endif