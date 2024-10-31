#ifndef __T_MATRIX_H___
#define __T_MATRIX_H___

#include <assert.h>
#include <iostream>
#include <vector>
#include <cstdlib>


//YOUR CODE GOES HERE!
template<typename T>
class Matrix {
 private:
  int numRows;
  int numColumns;
  std::vector<T> ** rows;
 public:
  Matrix(){
    numColumns = 0;
    numRows = 0;
    rows = NULL;
  }
  Matrix(int r, int c){
    rows = new std::vector<T>*[r];
    for(int i =0;i<r;i++){
        rows[i] = new std::vector<T>(c);
    }
    numColumns = c;
    numRows = r;
  }
  Matrix(const Matrix<T> & rhs){
    int r = rhs.getRows();
    int c = rhs.getColumns();
    rows = new std::vector<T>*[r];
    for(int i = 0;i<r;i++){
        rows[i] = new std::vector<T>(rhs[i]);    
    }
    numColumns = c;
    numRows = r;
  }
  ~Matrix(){
    for(int i = 0;i<numRows;i++){
        delete rows[i];
    }
    delete[] rows;
  }
  Matrix<T> & operator=(const Matrix<T> & rhs){
    //free current content
    for(int i = 0;i<numRows;i++){
        delete rows[i];
    }
    delete[] rows;

    //copy rhs
    int r = rhs.getRows();
    int c = rhs.getColumns();
    rows = new std::vector<T>*[r];
    for(int i = 0;i<r;i++){
        rows[i] = new std::vector<T>(rhs[i]);    
    }
    numColumns = c;
    numRows = r;
    return *this;
  }
  int getRows() const{
    return numRows;
  }
  int getColumns() const{
    return numColumns;
  }
  const std::vector<T> & operator[](int index) const{
    assert(index>=0 && index <numRows);
    return *(rows[index]);
  }
  std::vector<T> & operator[](int index){
    assert(index>=0 && index <numRows);
    return *(rows[index]);
  }
  bool operator==(const Matrix<T> & rhs) const{
    int r = rhs.getRows();
    int c = rhs.getColumns();
    if(r!=numRows || c!=numColumns){
        return false;
    }
    for(int i = 0;i<numRows;i++){
        if(*(rows[i])!=rhs[i]){
            return false;
        }
    }
    return true;
  }
  Matrix<T> operator+(const Matrix<T> & rhs) const{
    assert(rhs.getColumns() == numColumns && rhs.getRows() == numRows);
    Matrix<T> ans(numRows,numColumns);
    for(int i = 0;i<numRows;i++){
        for(int j = 0;j<numColumns;j++){
            ans[i][j]=rhs[i][j]+(*this)[i][j];
        }
    }
    return ans;
  }
};

template <typename T>
std::ostream & operator<<(std::ostream & s, const Matrix<T> & rhs){
     s<<"[ ";
    for(int i = 0;i<rhs.getRows()-1;i++){
        s<<"{";
        for(long unsigned int j = 0;j<rhs[i].size()-1;j++){
            s<<rhs[i][j]<<",";
        } 
        s<<rhs[i][rhs[i].size()-1]<<"},\n";
    }
    if(rhs.getRows() == 0){
        s<<" ]";
    }else{
        s<<"{";
        int i = rhs.getRows()-1;
         for(long unsigned int j = 0;j<rhs[i].size()-1;j++){
            s<<rhs[i][j]<<",";
        } 
        s<<rhs[i][rhs[i].size()-1]<<"}"<<" ]";
    }
    return s;
}


#endif
