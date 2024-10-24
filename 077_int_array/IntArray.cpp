#include "IntArray.h"
#include <assert.h>
#include <ostream>

IntArray::IntArray():data(NULL),numElements(0){

}
IntArray::IntArray(int n){
    if(n == 0){
        this->data=NULL;
        this->numElements=0;
    }else{
        this->data = (int *) malloc(n*sizeof(*data));
        this->numElements=n;
    }
}

IntArray::IntArray(const IntArray & rhs)  {
    this->numElements = rhs.numElements;
    if(rhs.size() == 0){
        this->data = NULL;
    }else{
        this->data = (int *) malloc(this->numElements*sizeof(*data));
        for(int i =0;i<rhs.numElements;i++){
            this->data[i] = rhs.data[i];
        }
    }
    
}
IntArray::~IntArray() {
    free(this->data);
}

IntArray & IntArray::operator=(const IntArray & rhs) {
    if(&rhs == this){
        return *this;
    }
    if(rhs.size()==0){
        this->numElements=0;
        free(this->data);
        this->data = NULL;
    }else{
        this->numElements = rhs.numElements;
        free(this->data);
        this->data = (int *) malloc(this->numElements*sizeof(*data));
        for(int i =0;i<rhs.numElements;i++){
            this->data[i] = rhs.data[i];
        }
    }
    return *this;
}
const int & IntArray::operator[](int index) const {
    assert(index>=0 && index<this->numElements);
    return this->data[index];
}
int & IntArray::operator[](int index) {
    assert(index>=0 && index<this->numElements);
    return this->data[index];
}

int IntArray::size() const {
    return this->numElements;
}

bool IntArray::operator==(const IntArray & rhs) const {
    if(this->numElements!=rhs.numElements){
        return false;
    }
    if(this->numElements==0&&rhs.numElements==0){
        return true;
    }
    for(int i =0;i<rhs.numElements;i++){
        if(this->data[i] != rhs.data[i]){
            return false;
        }
    }
    return true;
}

bool IntArray::operator!=(const IntArray & rhs) const {

    if(this->numElements!=rhs.numElements){
        return true;
    }
    if(this->numElements==0&&rhs.numElements==0){
        return false;
    }
    for(int i =0;i<rhs.numElements;i++){
        if(this->data[i] != rhs.data[i]){
            return true;
        }
    }
    return false;
}

std::ostream & operator<<(std::ostream & s, const IntArray & rhs) {
    if(rhs.size() == 0){
        s<<"{}";
        return s;
    }
    s<<"{";
    for(int i =0;i<rhs.size()-1;i++){
       s<<rhs[i]<<", ";
    }
    s<<rhs[rhs.size()-1]<<"}";
    return s;
}
