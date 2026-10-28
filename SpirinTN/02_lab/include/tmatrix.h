#ifndef __TDynamicMatrix_H__
#define __TDynamicMatrix_H__

#include <iostream>
#include <algorithm>
#include <iomanip>
#include <stdexcept>
#include <cassert> 

using namespace std;

const int MAX_VECTOR_SIZE = 100000000;
const int MAX_MATRIX_SIZE = 10000;

template<typename T>
class TDynamicVector {
protected:
    size_t sz;
    T* pMem;
public:
    TDynamicVector(size_t size = 1) : sz(size) {
        if (sz == 0 || sz > MAX_VECTOR_SIZE) {
            throw out_of_range("Incorrect vector size");
        }
        pMem = new T[sz]();
    }
    TDynamicVector(T* arr, size_t s) : sz(s) {
        if (sz == 0 || sz > MAX_VECTOR_SIZE) {
            throw out_of_range("Incorrect vector size");
        }
        assert(arr != nullptr && "TDynamicVector ctor requires non-nullptr arg");
        pMem = new T[sz];
        copy(arr, arr + sz, pMem);
    }
    TDynamicVector(const TDynamicVector& v) : sz(v.sz), pMem(new T[sz]) {
        copy(v.pMem, v.pMem + v.sz, pMem);
    }
    TDynamicVector(TDynamicVector&& v) noexcept : sz(v.sz), pMem(v.pMem) {
        v.sz = 0;
        v.pMem = nullptr;
    }
    ~TDynamicVector() {
        delete[] pMem;
    }

    TDynamicVector& operator=(const TDynamicVector& v) {
        if (this == &v) return *this;
        
        if (sz != v.sz) {
            T* newPMem = new T[v.sz];
            sz = v.sz;
            delete[] pMem;
            pMem = newPMem;
        }

        copy(v.pMem, v.pMem + v.sz, pMem);

        return *this;
    }
    TDynamicVector& operator=(TDynamicVector&& v) noexcept {
        if (this == &v) return *this;

        sz = v.sz;
        delete[] pMem;
        pMem = v.pMem;

        v.sz = 0;
        v.pMem = nullptr;

        return *this;
    }

    size_t size() const noexcept { 
        return sz; 
    }

    T& operator[](size_t ind) {
        return pMem[ind];
    }
    const T& operator[](size_t ind) const {
        return pMem[ind];
    }
    T& at(size_t ind) {
        if (ind >= sz) {
            throw out_of_range("There is no element with that index");
        }
        return pMem[ind];
    } 
    const T& at(size_t ind) const {
        if (ind >= sz) {
            throw out_of_range("There is no element with that index");
        }
        return pMem[ind];
    }

    bool operator==(const TDynamicVector& v) const noexcept {
        if (sz != v.sz) {
            return false;
        }
        for (size_t i = 0; i < sz; i++) {
            if (pMem[i] != v.pMem[i]) {
                return false;
            }
        }
        return true;
    }
    bool operator!=(const TDynamicVector& v) const noexcept {
        return !(*this == v);
    }

    TDynamicVector operator+(T val) const {
        TDynamicVector resultVector(*this);

        for (size_t i = 0; i < sz; i++) {
            resultVector.pMem[i] += val;
        }

        return resultVector;
    }
    TDynamicVector operator-(T val) const {
        TDynamicVector resultVector(*this);

        for (size_t i = 0; i < sz; i++) {
            resultVector.pMem[i] -= val;
        }

        return resultVector;
    }
    TDynamicVector operator*(T val) const {
      TDynamicVector resultVector(*this);

      for (size_t i = 0; i < sz; i++) {
          resultVector.pMem[i] *= val;
      }

      return resultVector;
    }

    TDynamicVector operator+(const TDynamicVector& v) const {
        if (sz != v.sz) {
            throw invalid_argument("The vector sizes do not match");
        }

        TDynamicVector resultVector(*this);

        for (size_t i = 0; i < sz; i++) {
            resultVector.pMem[i] += v.pMem[i];
        }

        return resultVector;
    }
    TDynamicVector operator-(const TDynamicVector& v) const  {
        if (sz != v.sz) {
            throw invalid_argument("The vector sizes do not match");
        }

        TDynamicVector resultVector(*this);

        for (size_t i = 0; i < sz; i++) {
            resultVector.pMem[i] -= v.pMem[i];
        }

        return resultVector;
    }
    //T operator*(const TDynamicVector& v) const noexcept(noexcept(T()))
    T operator*(const TDynamicVector& v) const {
        if (sz != v.sz) {
            throw invalid_argument("The vector sizes do not match");
        }

        T result{};

        for (size_t i = 0; i < sz; i++) {
            result += pMem[i] * v.pMem[i];
        }

        return result;
    }

    friend void swap(TDynamicVector& lhs, TDynamicVector& rhs) noexcept {
        swap(lhs.sz, rhs.sz);
        swap(lhs.pMem, rhs.pMem);
    }

    friend istream& operator>>(istream& istr, TDynamicVector& v) {
        for (size_t i = 0; i < v.sz; i++) {
            istr >> v.pMem[i];
        }

        return istr;
    }
    friend ostream& operator<<(ostream& ostr, const TDynamicVector& v) {
        ostr << "[ ";
        for (size_t i = 0; i < v.sz; i++) {
            ostr << v.pMem[i];
            if (i < v.sz - 1) ostr << ' ';
        }
        ostr << "]";
        return ostr;
    }
};

template<typename T>
class TDynamicMatrix : private TDynamicVector<TDynamicVector<T>> {
private:
    using TDynamicVector<TDynamicVector<T>>::pMem;
    using TDynamicVector<TDynamicVector<T>>::sz;
public:
    TDynamicMatrix(size_t s = 1) : TDynamicVector<TDynamicVector<T>>(s) {
        if (sz == 0 || sz > MAX_MATRIX_SIZE) {
            throw out_of_range("Incorrect matrix size");
        }
        for (size_t i = 0; i < sz; i++) {
            pMem[i] = TDynamicVector<T>(sz - i);
        }
    }
    
    size_t getDimension() const { 
        return sz; 
    }

    T& operator()(size_t row, size_t column) {
        if (row >= sz || column >= sz) {
            throw out_of_range("Matrix indices out of bounds");
        }
        if (column < row) {
            throw out_of_range("Elements below the diagonal are not stored (always 0)");
        }
        return pMem[row][column - row];
    }

    const T& operator()(size_t row, size_t column) const {
        if (row >= sz || column >= sz) {
            throw out_of_range("Matrix indices out of bounds");
        }
        if (column < row) {
            throw out_of_range("Elements below the diagonal are not stored (always 0)");
        }
        return pMem[row][column - row];
    }

    bool operator==(const TDynamicMatrix& m) const noexcept {
        return TDynamicVector<TDynamicVector<T>>::operator==(m);
    }

    bool operator!=(const TDynamicMatrix& m) const noexcept {
        return !(*this == m);
    }

    TDynamicMatrix operator*(const T& val) const {
        TDynamicMatrix resultMatrix(*this);

        for (size_t i = 0; i < sz; i++) {
            resultMatrix.pMem[i] = resultMatrix.pMem[i] * val;
        }

        return resultMatrix;
    }

    TDynamicVector<T> operator*(const TDynamicVector<T>& v) const {
        if (sz != v.sz) {
            throw invalid_argument("The sizes do not match");
        }

        TDynamicVector<T> resultVector(sz);

        for (size_t i = 0; i < sz; i++) {
            T sum = pMem[i][0] * v[i];

            for (size_t j = i + 1; j < sz; j++) {
                sum += pMem[i][j - i] * v[j];
            }

            resultVector[i] = sum;
        }

        return resultVector;
    }

    TDynamicMatrix operator+(const TDynamicMatrix& m) const {
        if (sz != m.sz) {
            throw invalid_argument("The sizes do not match");
        }

        TDynamicMatrix resultMatrix(*this);
        for (size_t i = 0; i < sz; i++) {
            resultMatrix.pMem[i] = resultMatrix.pMem[i] + m.pMem[i];
        }

        return resultMatrix;
    }
    TDynamicMatrix operator-(const TDynamicMatrix& m) const {
        if (sz != m.sz) {
            throw invalid_argument("The sizes do not match");
        }

        TDynamicMatrix resultMatrix(*this);
        for (size_t i = 0; i < sz; i++) {
            resultMatrix.pMem[i] = resultMatrix.pMem[i] - m.pMem[i];
        }

        return resultMatrix;
    }
    TDynamicMatrix operator*(const TDynamicMatrix& m) const {
        if (sz != m.sz) {
            throw invalid_argument("The sizes do not match");
        }

        TDynamicMatrix resultMatrix(*this);
        for (size_t i = 0; i < sz; i++) {
            for (size_t j = i; j < sz; j++) {
                T sum = pMem[i][0] * m.pMem[i][j - i];

                for (size_t k = 1; k <= j - i; k++) {
                    sum += pMem[i][k] * m.pMem[i + k][j - i - k];
                }

                resultMatrix.pMem[i][j - i] = sum;
            }
        }

        return resultMatrix;
    }
    friend istream& operator>>(istream& istr, TDynamicMatrix& v) {
        for (size_t i = 0; i < v.sz; i++) {
            istr >> v.pMem[i];
        }

        return istr;
    }
    friend ostream& operator<<(ostream& ostr, const TDynamicMatrix& v) {
        for (size_t i = 0; i < v.sz; i++) {
            ostr << '[ ';
            for (size_t j = 0; j < v.sz; j++) {
                if (j < i) {
                    ostr << setw(6) << 0;
                }
                else {
                    ostr << setw(6) << v.pMem[i][j - i];
                }
            }
            ostr << ' ]\n';
        }

        return ostr;
    }
};

#endif
