// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле

#include "tbitfield.h"

TBitField::TBitField(int len)
{
    if (len < 0)
    {
        throw 0;
    }
    else
    {
        size = sizeof(int) * 8;
        MemLen = ((len + size - 1) / size);
        BitLen = len;
        pMem = new TELEM[MemLen];
        for (int i = 0; i < MemLen; ++i)
        {
            pMem[i] = 0;
        }
    }
}

TBitField::TBitField(const TBitField &bf):MemLen(bf.MemLen),BitLen(bf.BitLen),size(bf.size) // конструктор копирования
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
    int ind = n / size;
    return ind;
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
    TELEM mask = (1 << (BitLen - n -1));//32 - длина маски в битах
    return mask;
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
  return BitLen;
}

void TBitField::SetBit(const int n) // установить бит
{

    if (n < 0 || n > BitLen)
    {
        throw 0;
    }
    else
    {
        pMem[GetMemIndex(n)] = (pMem[GetMemIndex(n)] | GetMemMask(n));
    }
}

void TBitField::ClrBit(const int n) // очистить бит
{
    if (n < 0|| n>BitLen)
    {
        throw 0;
    }
    else
    {
        TELEM mask = TBitField::GetMemMask(n);
        pMem[GetMemIndex(n)] = pMem[GetMemIndex(n)] ^ mask;
    }
}

int TBitField::GetBit(const int n) const // получить значение бита
{
    if (n < 0 || n>BitLen)
    {
        throw 0;
    }
    else
    {
        TELEM mask = (1 << (BitLen - n -1));//32 - длина маски в битах
        if ((pMem[GetMemIndex(n)] | mask) == pMem[GetMemIndex(n)])
            return 1;
        else
            return 0;
    }
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
    bool fl = 0;
    for (int i = 0; i < MemLen; i++)
    {
        if (pMem[i] != bf.pMem[i])
        {
            fl = 1;
            break;
        }
    }
    if (fl == 0)
        return 1;
    else
        return 0;
  }

int TBitField::operator!=(const TBitField &bf) const // сравнение
{
    if (operator==(bf) == 1)
        return 0;
    else
        return 1;
}

TBitField TBitField::operator|(const TBitField &bf) // операция "или"
{
    if (bf.BitLen == BitLen)
    {
        TBitField new_field(BitLen);
        for (int i = 0; i < MemLen; i++)
        {
            new_field.pMem[i] = pMem[i] | bf.pMem[i];
        }
        return new_field;
    }
    else
    {
        int max_len = max({ BitLen,bf.BitLen });
        int min_len = min({ BitLen,bf.BitLen });
        TBitField new_field(max_len);
        for (int i = 0; i < min_len; i++)
        {
            if (GetBit(i)==1 || bf.GetBit(i) == 1)
                new_field.SetBit(i);
        }
        if (BitLen > min_len)
        {
            for (int i = min_len; i < max_len; i++)
            {
                if (GetBit(i) == 1)
                    new_field.SetBit(i);
            }
        }
        if (bf.BitLen > min_len)
        {
            for (int i = min_len; i < max_len; i++)
            {
                if (bf.GetBit(i) == 1)
                    new_field.SetBit(i);
            }
        }
        return new_field;
    }
}

TBitField TBitField::operator&(const TBitField &bf) // операция "и"
{
    int max_len = max({ BitLen,bf.BitLen });
    int min_len = min({ BitLen,bf.BitLen });
    TBitField op_1(max_len);
    for (int i = 0; i < min_len; i++)
    {
        if (GetBit(i)==1 && bf.GetBit(i) == 1)
            op_1.SetBit(i);
    }
    return op_1;
}

TBitField TBitField::operator~(void) // отрицание
{   
    TBitField op_1(BitLen);
    for (int i = 0; i < BitLen; i++)
    {
        if (GetBit(i) == 0)
            op_1.SetBit(i);
    }
    return op_1;
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
