#pragma once
#include <utility>
#include <iostream>
#include <string>
#include <numeric>

class CRational
{
public:
	// Конструирует рациональное число, равное нулю (0/1)
	CRational();
	CRational(int value);// Конструирует рациональное число, равное value (value/1)
	CRational(int numerator, int denominator);// Конструирует рациональное число, равное numerator/denominator
	int GetNumerator() const;// Возвращает числитель
	int GetDenominator() const;// Возвращает знаменатель (натуральное число)
	double ToDouble() const;// Возвращает отношение числителя и знаменателя в виде числа double
	std::pair<int, CRational> ToCompoundFraction() const; //// Возвращает представление рационального числа в виде смешанной дроби
	CRational operator+() const;
	CRational operator-() const;

	CRational& operator+=(const CRational& number);
	CRational& operator-=(const CRational& number);
	CRational& operator*=(const CRational& number);
	CRational& operator/=(const CRational& number);

	~CRational() = default;

private:

	void NormalizeRational();

	int m_numerator;
	int m_denominator;
};
CRational operator+(const CRational& number1, const CRational& number2);
CRational operator-(const CRational& number1, const CRational& number2);

CRational operator*(const CRational& number1, const CRational& number2);
CRational operator/(const CRational& number1, const CRational& number2);

bool operator==(const CRational& number1, const CRational& number2);
bool operator!=(const CRational& number1, const CRational& number2);
bool operator<(const CRational& number1, const CRational& number2);
bool operator>(const CRational& number1, const CRational& number2);
bool operator<=(const CRational& number1, const CRational& number2);
bool operator>=(const CRational& number1, const CRational& number2);

std::istream& operator>>(std::istream& is, CRational& number);
std::ostream& operator<<(std::ostream& os, const CRational& number);

