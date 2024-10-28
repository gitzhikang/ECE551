#include "IntMatrix.h"

IntMatrix::IntMatrix():numRows(0),numColumns(0),rows(NULL){
}
IntMatrix::IntMatrix(int r, int c) {

    rows = new IntArray*[r];
    for(int i = 0;i<r;i++){
        rows[i] = new IntArray(c);    
    }
    numColumns = c;
    numRows = r;

}
IntMatrix::IntMatrix(const IntMatrix & rhs)  {
    int r = rhs.getRows();
    int c = rhs.getColumns();
    rows = new IntArray*[r];
    for(int i = 0;i<r;i++){
        rows[i] = new IntArray(rhs[i]);    
    }
    numColumns = c;
    numRows = r;
}
IntMatrix::~IntMatrix() {
    for(int i = 0;i<numRows;i++){
        delete rows[i];
    }
    delete[] rows;
}
IntMatrix &IntMatrix::operator=(const IntMatrix & rhs) {
    //free current content
    for(int i = 0;i<numRows;i++){
        delete rows[i];
    }
    delete[] rows;

    //copy rhs
    int r = rhs.getRows();
    int c = rhs.getColumns();
    rows = new IntArray*[r];
    for(int i = 0;i<r;i++){
        rows[i] = new IntArray(rhs[i]);    
    }
    numColumns = c;
    numRows = r;
    return *this;
}
int IntMatrix::getRows() const {
    return numRows;
}
int IntMatrix::getColumns() const {
    return numColumns;
}
const IntArray & IntMatrix::operator[](int index) const {
    assert(index>=0 && index <numRows);
    return *(rows[index]);
}
IntArray & IntMatrix::operator[](int index){
    assert(index>=0 && index <numRows);
    return *(rows[index]);
}

bool IntMatrix::operator==(const IntMatrix & rhs) const {
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

IntMatrix IntMatrix::operator+(const IntMatrix & rhs) const {
    assert(rhs.getColumns() == numColumns && rhs.getRows() == numRows);
    IntMatrix ans(numRows,numColumns);
    for(int i = 0;i<numRows;i++){
        for(int j = 0;j<numColumns;j++){
            ans[i][j]=rhs[i][j]+(*this)[i][j];
        }
    }
    return ans;
}

std::ostream & operator<<(std::ostream & s, const IntMatrix & rhs) {
    s<<"[ ";
    for(int i = 0;i<rhs.getRows()-1;i++){
        s<<rhs[i]<<",\n";
    }
    if(rhs.getRows() == 0){
        s<<" ]";
    }else{
        s<<rhs[rhs.getRows()-1]<<" ]";
    }
    return s;
}
