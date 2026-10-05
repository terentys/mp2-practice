#include <stdexcept>
#include <cstring>
#include <string>

#include "tbitfield.h"

TBitField::TBitField(int len) {
    if (len < 0) {
        throw runtime_error("Некорректное значение длины битового поля!");
    }

    const int bitsPerElem = sizeof(TELEM) << BIT_SHIFTING;
    this->BitLen = len;
    this->MemLen = (len + bitsPerElem - 1) / bitsPerElem;
    this->pMem = new TELEM[this->MemLen];
    memset(this->pMem, 0, this->MemLen * sizeof(TELEM));
}

TBitField::TBitField(const TBitField &bf) {
    this->BitLen = bf.BitLen;
    this->MemLen = bf.MemLen;
    this->pMem = new TELEM[this->MemLen];
    for (int i = 0; i < this->MemLen; i++) {
        pMem[i] = bf.pMem[i];
    }
}

TBitField::~TBitField() {
    delete[] this->pMem;
}

int TBitField::GetMemIndex(const int n) const {
    return n / (BIT_IN_BYTE * sizeof(TELEM));
}

TELEM TBitField::GetMemMask(const int n) const {
    return TELEM(1) << (n & ((sizeof(TELEM) << BIT_SHIFTING) - 1));
}

int TBitField::GetLength(void) const {
    return this->BitLen;
}

void TBitField::SetBit(const int n) {
    if (n < 0 || n >= this->BitLen) {
        throw std::out_of_range("Такого бита в поле нет!");
    }

    this->pMem[GetMemIndex(n)] |= GetMemMask(n);
}

void TBitField::ClrBit(const int n) {
    if (n < 0 || n >= this->BitLen) {
        throw std::out_of_range("Такого бита в поле нет!");
    }

    int MemIndex = GetMemIndex(n);
    this->pMem[MemIndex] &= ~GetMemMask(n);


    if (MemIndex == this->MemLen - 1) {
        int lenMaskForResetZero = this->BitLen & ((sizeof(TELEM) << BIT_SHIFTING) - 1);
        if (lenMaskForResetZero != 0) {
            TELEM maskForResetZero = (TELEM(1) << lenMaskForResetZero) - 1;
            this->pMem[MemIndex] &= maskForResetZero;
        }
    }
}

int TBitField::GetBit(const int n) const {
  if (n < 0 || n >= this->BitLen) {
      throw std::out_of_range("Такого бита в поле нет!");
  }

  return (this->pMem[GetMemIndex(n)] & GetMemMask(n)) >> (n & ((sizeof(TELEM) << BIT_SHIFTING) - 1));
}

const TBitField& TBitField::operator=(const TBitField &bf) {
    if (this == &bf) return *this;

    TELEM* temp = new TELEM[bf.MemLen];
    for (int i = 0; i < bf.MemLen; i++) {
        temp[i] = bf.pMem[i];
    }
    delete[] this->pMem;
    this->pMem = temp;
    this->MemLen = bf.MemLen;
    this->BitLen = bf.BitLen;

    //создавать только в случае разного размера

    return *this;
}

int TBitField::operator==(const TBitField &bf) const {
    if (this->BitLen != bf.BitLen) {
        return 0;
    }
    for (int i = 0; i < this->MemLen; i++) {
        if (this->pMem[i] != bf.pMem[i]) {
            return 0;
        }
    }
    return 1;
}

int TBitField::operator!=(const TBitField &bf) const {
    return !(*this == bf);
}

TBitField TBitField::operator|(const TBitField &bf) const {
    const TBitField& bfWithMoreLen = this->BitLen > bf.BitLen ? *this : bf;
    const TBitField& bfWithLessLen = this->BitLen <= bf.BitLen ? *this : bf;
    
    TBitField bfResult(bfWithMoreLen);
    for (int i = 0; i < bfWithLessLen.MemLen; i++) {
        bfResult.pMem[i] |= bfWithLessLen.pMem[i];
    }

    return bfResult;
}

TBitField TBitField::operator&(const TBitField &bf) const {
    const TBitField& bfWithMoreLen = this->BitLen > bf.BitLen ? *this : bf;
    const TBitField& bfWithLessLen = this->BitLen <= bf.BitLen ? *this : bf;

    TBitField bfResult(bfWithMoreLen);
    for (int i = 0; i < bfWithLessLen.MemLen; i++) {
        bfResult.pMem[i] &= bfWithLessLen.pMem[i];
    }

    for (int i = bfWithLessLen.MemLen; i < bfWithMoreLen.MemLen; i++) {
        bfResult.pMem[i] = 0;
    }

    return bfResult;
}

TBitField TBitField::operator~(void) const {
    TBitField bfResult(*this);
    for (int i = 0; i < bfResult.MemLen; i++) {
        bfResult.pMem[i] = ~bfResult.pMem[i];
    }

    int lenMaskForResetZero = bfResult.BitLen & ((sizeof(TELEM) << BIT_SHIFTING) - 1);
    if (lenMaskForResetZero != 0) {
        TELEM maskForResetZero = (TELEM(1) << lenMaskForResetZero) - 1;
        bfResult.pMem[bfResult.MemLen - 1] &= maskForResetZero;
    }

    return bfResult;
}

istream &operator>>(istream &istr, TBitField &bf) {
    string sField;
    istr >> sField;

    if (sField.size() != bf.BitLen) {
        istr.setstate(ios::failbit);
        return istr;
    }

    TBitField bfTemp(bf.BitLen);
    for (int i = 0; i < bf.BitLen; i++) {
        if (sField[i] == '1') {
            bfTemp.SetBit(bf.BitLen - 1 - i);
        }
        else if (sField[i] != '0') {
            istr.setstate(ios::failbit);
            return istr;
        }
    }
    bf = bfTemp;

    return istr;
}

ostream &operator<<(ostream &ostr, const TBitField &bf) {
    std::string sField;
    sField.reserve(bf.BitLen);
    for (int i = bf.BitLen - 1; i >= 0; i--) {
        sField += bf.GetBit(i) ? '1' : '0';
    }

    ostr << sField;
    return ostr;
}
