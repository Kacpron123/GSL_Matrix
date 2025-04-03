#include "Matrix.h"
#include <iostream>
#include <exception>

//Row
Matrix::Row::Row(double* data,int sizex,int width):m_data(data),m_sizex(sizex),m_width(width){}
Matrix::Row::~Row(){
   m_data=nullptr;
   m_width=0;
}
size_t Matrix::Row::size() const{
   return m_width;}
double& Matrix::Row::operator[](int j){
   if(j<0 || j>=m_sizex)
       throw std::out_of_range("Row index.x out of range");
   return m_data[j*m_width];}
//Matrix
void Matrix::print(double d) const{
   printf("%+.4e ",d);
}
Matrix::Matrix(int rows,int col,int fill){
   _matrix=gsl_matrix_calloc(rows,col);
   if(fill==0)
      return;
   int n=rows*col;
   for(int i=0;i<n;i++){
      _matrix->data[i]=fill;
   }
}
Matrix::Matrix(const Matrix& copy){
   _matrix=gsl_matrix_calloc(copy.size().x,copy.size().y);
   gsl_matrix_memcpy(_matrix,copy._matrix);
}
Matrix::Matrix(const Matrix&& copy){
   _matrix=gsl_matrix_calloc(copy.size().x,copy.size().y);
   gsl_matrix_memcpy(_matrix,copy._matrix);
}
Matrix::Matrix(std::vector<std::vector<double>> vector): Matrix(vector[0].size(),vector.size()){
   fill(vector);
}
Matrix::Matrix(gsl_matrix *copy){
   gsl_matrix_memcpy(copy,_matrix);
}
Matrix::~Matrix(){
   delete _matrix;
   _matrix=nullptr;
}
void Matrix::print() const{
   for(int y=0;y<size().y;y++){
      for(int x=0;x<size().x;x++)
         print(gsl_matrix_get(_matrix,x,y));
         // print(_matrix[y][x]);
      printf("\n");
   }
}
void Matrix::print(gsl_matrix *matrix){
   Matrix m(matrix);
   m.print();
}
Matrix::_size Matrix::size() const{
   _size s{_matrix->size1,_matrix->size2};
   return s;
}
Matrix::Row Matrix::operator[](int j){
   if(j<0 || j>=size().y)
      throw std::out_of_range("Row index.y out of range");
   Row row(_matrix->data+j,size().x,_matrix->tda);
   return row;
}
Matrix& Matrix::operator=(const Matrix& other){
   if(this == &other)
      return *this;
   _matrix = gsl_matrix_calloc(other.size().x,other.size().y);
   gsl_matrix_memcpy(_matrix,other._matrix);
   return *this;
}
void Matrix::fill(std::vector<std::vector<double>> c){
   if(size().y!=c.size() || size().x!=c[0].size())
      throw std::invalid_argument("wrong dimensions");
   for(int y=0;y<size().y;y++)
      for(int x=0;x<size().x;x++)
   (*this)[y][x]=c[y][x];
}
void Matrix::fill(std::function<double(int,int)> func){
   for(int y=0;y<size().y;y++)
      for(int x=0;x<size().x;x++)
   (*this)[y][x]=func(x,y);
}
Matrix Matrix::operator*(Matrix O){
   if(size().x!=O.size().y)
      throw std::invalid_argument("wrong dimensions");
   Matrix res(O.size().x,size().y);
   for(int y=0;y<res.size().y;y++)
      for(int x=0;x<res.size().x;x++)
         for(int i=0;i<size().x;i++)
            res[y][x]+=(*this)[y][i]*O[i][x];
   return res;
}
Matrix::operator double(){
   if (size().x != 1 || size().x != 1) {
      throw std::runtime_error("Matrix is not 1x1, cannot convert to double.");
   }
   return (*this)[0][0];
}
Matrix Matrix::transpose(){
   Matrix res(size().y,size().x);
   for(int y=0;y<size().y;y++)
      for(int x=0;x<size().x;x++)
         res[x][y]=(*this)[y][x];
   return res;
}
Matrix Matrix::inverse(){
   if(size().x!=size().y)  
      throw std::invalid_argument("wrong dimensions");
   // TODO: implement inverse
   throw std::invalid_argument("not implemented");
}
Matrix Matrix::operator+(Matrix O){
   if(size().x!=O.size().x || size().y!=O.size().y)
      throw std::invalid_argument("wrong dimensions");
   Matrix res(size().x,size().y);
   for(int y=0;y<size().y;y++)
      for(int x=0;x<size().x;x++)
         res[y][x]=(*this)[y][x]+O[y][x];
   return res;
}
Matrix Matrix::operator-(Matrix O){
   if(size().x!=O.size().x || size().y!=O.size().y)
      throw std::invalid_argument("wrong dimensions");
   Matrix res(size().x,size().y);
   for(int y=0;y<size().y;y++)
      for(int x=0;x<size().x;x++)
         res[y][x]=(*this)[y][x]-O[y][x];
   return res;
}
Matrix Matrix::operator*(double scalar){
   Matrix res(*this);
   for(int y=0;y<size().y;y++)
      for(int x=0;x<size().x;x++)
         res[y][x]*=scalar;
   return res;
}
Matrix Matrix::operator/(double scalar){
   Matrix res(*this);
   for(int y=0;y<size().y;y++)
      for(int x=0;x<size().x;x++)
         res[y][x]/=scalar;
   return res;
}
Matrix operator*(double scalar,Matrix O){
   return O*scalar;
}
gsl_matrix* Matrix::operator*(){
   return _matrix;
}