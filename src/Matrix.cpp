#include "Matrix.h"
#include <iostream>
void Matrix::print(double d) const{
   printf("%-0.17f ",d);
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
   gsl_matrix_memcpy(copy._matrix,_matrix);
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
   Row row(_matrix->data+j,_matrix->tda);
   // std::cout<<row.size()<<"\n";
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
      throw("zle wymiary");
   for(int y=0;y<size().y;y++)
      for(int x=0;x<size().x;x++)
   (*this)[y][x]=c[y][x];
}
Matrix Matrix::operator*(Matrix &O){
   if(size().x!=O.size().y)
      throw("zle wymiary");
   Matrix res(O.size().x,size().y);
   for(int y=0;y<res.size().y;y++)
      for(int x=0;x<res.size().x;x++)
         for(int i=0;i<size().x;i++)
            res[y][x]+=(*this)[y][i]*O[i][x];
   return res;
}
Matrix Matrix::transpose(){
   Matrix res(size().y,size().x);
   for(int y=0;y<size().y;y++)
      for(int x=0;x<size().x;x++)
         res[y][x]=(*this)[x][y];
   return res;
}