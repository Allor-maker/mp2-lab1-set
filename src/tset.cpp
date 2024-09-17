// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tset.cpp - Copyright (c) Гергель В.П. 04.10.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Множество - реализация через битовые поля

#include "tset.h"

TSet::TSet(int mp): MaxPower(mp), BitField(TBitField(mp))
{
}

// конструктор копирования
TSet::TSet(const TSet &s) : MaxPower(s.MaxPower),BitField(s.BitField)
{
}

// конструктор преобразования типа
TSet::TSet(const TBitField &bf) : MaxPower(bf.GetLength()),BitField(bf)
{
}

TSet::operator TBitField()
{
    return BitField;
}

int TSet::GetMaxPower(void) const // получить макс. к-во эл-тов
{
    return MaxPower;
}

int TSet::IsMember(const int Elem) const // элемент множества?
{
    return BitField.GetBit(Elem);
}

void TSet::InsElem(const int Elem) // включение элемента множества
{
    if (Elem >= MaxPower)
    { }
    else
        BitField.SetBit(Elem);
}

void TSet::DelElem(const int Elem) // исключение элемента множества
{
    if (IsMember(Elem) == 0)
    {}
    else
        BitField.ClrBit(Elem);
}

// теоретико-множественные операции

TSet& TSet::operator=(const TSet &s) // присваивание
{
    if (&s == this)
        return *this;
    this->MaxPower = s.MaxPower;
    BitField = s.BitField;
    return *this;
}

int TSet::operator==(const TSet &s) const // сравнение
{
    if (BitField == s.BitField && MaxPower == s.MaxPower)
        return 1;
    else
        return 0;
        
}

int TSet::operator!=(const TSet &s) const // сравнение
{
    if (BitField != s.BitField || MaxPower != s.MaxPower)
        return 1;
    else
        return 0;
}

TSet TSet::operator+(const TSet &s) // объединение
{
    int len = max({ MaxPower,s.MaxPower });
    TSet new_s = BitField | s.BitField;
    return new_s;
}

TSet TSet::operator+(const int Elem) // объединение с элементом
{
    if (Elem >= MaxPower)
        throw 0;
    else
    {
        TSet new_s(Elem + 1);
        new_s.BitField.SetBit(Elem);
        return BitField | new_s.BitField;
    }
    
}

TSet TSet::operator-(const int Elem) // разность с элементом
{
    BitField.ClrBit(Elem);
    return *this;
}

TSet TSet::operator*(const TSet &s) // пересечение
{

    return BitField & s.BitField;
}

TSet TSet::operator~(void) // дополнение
{
    return ~BitField;
}

// перегрузка ввода/вывода

istream &operator>>(istream &istr, TSet &s) // ввод
{
    return istr;
}

ostream& operator<<(ostream &ostr, const TSet &s) // вывод
{
    return ostr;
}
