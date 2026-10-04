#include "tset.h"

TSet::TSet(int mp) : MaxPower(mp), BitField(mp) {}
TSet::TSet(const TSet &s) : MaxPower(s.MaxPower), BitField(s.BitField) {}
TSet::TSet(const TBitField &bf) : MaxPower(bf.GetLength()), BitField(bf) {}

TSet::operator TBitField() {
    return this->BitField;
}

int TSet::GetMaxPower(void) const {
    return this->MaxPower;
}

int TSet::IsMember(const int Elem) const {
    if (Elem < 0 || Elem >= this->MaxPower) {
        throw std::out_of_range("Такого элемента в множестве нет!");
    }

    return this->BitField.GetBit(Elem);
}

void TSet::InsElem(const int Elem) {
    if (Elem < 0 || Elem >= this->MaxPower) {
        throw std::out_of_range("Такого элемента в множестве нет!");
    }

    this->BitField.SetBit(Elem);
}

void TSet::DelElem(const int Elem) {
    if (Elem < 0 || Elem >= this->MaxPower) {
        throw std::out_of_range("Такого элемента в множестве нет!");
    }

    this->BitField.ClrBit(Elem);
}

const TSet& TSet::operator=(const TSet &s) {
    if (this == &s) return *this;

    this->BitField = s.BitField;
    this->MaxPower = s.MaxPower;

    return *this;
}

int TSet::operator==(const TSet &s) const {
    return this->BitField == s.BitField;
}

int TSet::operator!=(const TSet &s) const {
    return this->BitField != s.BitField;
}

TSet TSet::operator+(const TSet &s) const {
    return TSet(this->BitField | s.BitField);
}

TSet TSet::operator+(const int Elem) const {
    if (Elem < 0 || Elem >= this->MaxPower) {
        throw std::out_of_range("Такого элемента в множестве нет!");
    }

    TBitField newBitField(this->BitField);
    newBitField.SetBit(Elem);

    return TSet(newBitField);
}

TSet TSet::operator-(const int Elem) const {
    if (Elem < 0 || Elem >= this->MaxPower) {
        throw std::out_of_range("Такого элемента в множестве нет!");
    }

    TBitField newBitField(this->BitField);
    newBitField.ClrBit(Elem);

    return TSet(newBitField);
}

TSet TSet::operator*(const TSet &s) const {
    return TSet(this->BitField & s.BitField);
}

TSet TSet::operator~(void) const {
    return TSet(~this->BitField);
}

istream& operator>>(istream& istr, TSet& s) {
    return istr >> s.BitField;
}

ostream& operator<<(ostream &ostr, const TSet &s) {
    return ostr << s.BitField;
}
