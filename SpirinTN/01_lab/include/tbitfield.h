#ifndef __BITFIELD_H__
#define __BITFIELD_H__

#include <iostream>

using namespace std;

typedef unsigned int TELEM;
#define BIT_IN_BYTE 8
#define BIT_SHIFTING 3

class TBitField {
private:
  int  BitLen;
  TELEM *pMem;
  int  MemLen;

  int   GetMemIndex(const int n) const;
  TELEM GetMemMask (const int n) const;
public:
  TBitField(int len);
  TBitField(const TBitField &bf);
  ~TBitField();

  int GetLength(void) const;
  void SetBit(const int n);
  void ClrBit(const int n);
  int  GetBit(const int n) const;         

  int operator==(const TBitField &bf) const;
  int operator!=(const TBitField &bf) const;
  const TBitField& operator=(const TBitField &bf);
  TBitField  operator|(const TBitField &bf) const;
  TBitField  operator&(const TBitField &bf) const;
  TBitField  operator~(void) const;

  friend istream &operator>>(istream &istr, TBitField &bf);
  friend ostream &operator<<(ostream &ostr, const TBitField &bf);
};

#endif
