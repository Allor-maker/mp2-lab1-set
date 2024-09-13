// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле

#include "tbitfield.h"

TBitField::TBitField(int len)
{
    MemLen = ((len + sizeof(int) * 8 - 1) / (sizeof(int) * 8));
    BitLen = MemLen * 8;
    pMem = new TELEM[MemLen];
    for (int i = 0; i < MemLen; ++i)
    {
        pMem[i] = 0;
    }
}

TBitField::TBitField(const TBitField &bf):MemLen(bf.MemLen),BitLen(bf.BitLen) // конструктор копирования
{
    this->pMem = new TELEM[MemLen];

    for (int i = 0; i < MemLen; ++i)
    {
        pMem[i] = bf.pMem[i];
    }
}

TBitField::~TBitField()
{
    delete[] pMem;
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
    int ind = n / (sizeof(int) * 8);
    return ind;
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{

    TELEM mask = (1 << (32 - (n%(sizeof(int)*8)) - 1));//32 - длина маски в битах
    return mask;
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
  return BitLen;
}

void TBitField::SetBit(const int n) // установить бит
{
    pMem[n / (sizeof(int) * 8)] = (pMem[n / (sizeof(int) * 8)] | GetMemMask(n));
}

void TBitField::ClrBit(const int n) // очистить бит
{

    int inv_mask = pMem[n / (sizeof(int) * 8)] ^ 255;
    pMem[n / (sizeof(int) * 8)] = pMem[n / (sizeof(int) * 8)] & inv_mask;
}

int TBitField::GetBit(const int n) const // получить значение бита
{
  TELEM mask = (1 << (32 - (n % (sizeof(int) * 8)) - 1));//32 - длина маски в битах
  if ((pMem[n / (sizeof(int) * 8)] | mask) == pMem[n / (sizeof(int) * 8)])
      return 1;
  else
      return 0;
 
}

// битовые операции

TBitField& TBitField::operator=(const TBitField &bf) // присваивание
{
    if (&bf == this)
        return *this;
    this->MemLen = bf.MemLen;
    this->BitLen = bf.BitLen;
    delete[] pMem;
    pMem = new TELEM[MemLen];
    for (int i = 0; i < MemLen; i++)
    {
        pMem[i] = bf.pMem[i];
    }
    return *this;
}

int TBitField::operator==(const TBitField &bf) const // сравнение
{

  return 0;
}

int TBitField::operator!=(const TBitField &bf) const // сравнение
{
  return 0;
}

TBitField TBitField::operator|(const TBitField &bf) // операция "или"
{
    return TBitField(0);
}

TBitField TBitField::operator&(const TBitField &bf) // операция "и"
{
    return TBitField(0);
}

TBitField TBitField::operator~(void) // отрицание
{
    return TBitField(0);
}

// ввод/вывод

istream &operator>>(istream &istr, TBitField &bf) // ввод
{
    return istr;
}

ostream &operator<<(ostream &ostr, const TBitField &bf) // вывод
{
    return ostr;
}
