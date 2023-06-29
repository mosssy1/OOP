#pragma once
#include <utility>
#include <iostream>
#include <string>
#include <numeric>

class CRational
{
public:
	// ������������ ������������ �����, ������ ���� (0/1)
	CRational();
	CRational(int value);// ������������ ������������ �����, ������ value (value/1)
	CRational(int numerator, int denominator);// ������������ ������������ �����, ������ numerator/denominator
	int GetNumerator() const;// ���������� ���������
	int GetDenominator() const;// ���������� ����������� (����������� �����)
	double ToDouble() const;// ���������� ��������� ��������� � ����������� � ���� ����� double
	std::pair<int, CRational> ToCompoundFraction() const; //// ���������� ������������� ������������� ����� � ���� ��������� �����
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

