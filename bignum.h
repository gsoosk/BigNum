#ifndef BIGNUM_H
#define BIGNUM_H
#include <iostream>
#include <string>
#include <vector>
#define POSITIVE +1
#define NEGATIVE -1
class Bad_Exception
{
public:
	Bad_Exception(std::string fn, int n):LineNum(n),FileName(fn){};
private:
	int LineNum;
	std:: string FileName;
};
	
class Digit
{
	
public:
	Digit(int *ptd):PointerToDigit(ptd){};
	Digit():PointerToDigit(0){};
	void set_val(int x){*PointerToDigit=x;}
	int get_val (){return *PointerToDigit;}
	int* get_pointer(){return PointerToDigit;}
	Digit operator= (const int a)
        {
            if (a < 0 || a > 9)
                throw Bad_Exception("bignum.h",28);
            (*PointerToDigit) = a;
            return (*this);
        }
   operator int() { return get_val(); }   	
private:
	int* PointerToDigit;
};

class BigNum
{
public:
	BigNum(std:: string Num);
	BigNum(double Num);
	BigNum();
	std:: vector<int>get_round_part(){return RoundPart;}
	std:: vector<int>get_decimal_part(){return DecimalPart;}
 	int get_sign(){return Sign;}
 	BigNum operator+(BigNum B);
 	BigNum operator+(double B);
 	BigNum& operator+=(BigNum B);
 	BigNum& operator++();
 	BigNum operator++(int x);
 	BigNum& operator=(BigNum B);
 	BigNum& operator-();
 	Digit operator[](int i);
 	bool operator==(BigNum& B);
 	bool operator<(const BigNum& B) const;


 	
 	void print();


private:
	std:: vector<int> RoundPart;
	std:: vector<int> DecimalPart;
	int Sign;
};

std:: vector<int> MakeRoundPartFromString(std:: string Num,bool does_it_have_decimal_point,int DecimalPointLocation,int Sign);
std:: vector<int> MakeDecimalPartFromString(std:: string Num,bool does_it_have_decimal_point,int DecimalPointLocation,int Sign);
void BadExceptionForConsrtuctor(std:: string Num);
void RemoveExtraZerosFromDecimalPart(std::vector<int> &DecimalPart);
void ExtraZerosToDecimalPart(int NumOfZeros,std:: vector<int> &DecimalPart);
void RemoveExtraZerosFromRoundPart(std::vector<int> &RoundPart);
void ExtraZerosToRoundPart(int NumOfZeros,std:: vector<int> &RoundPart);
std:: string MakeStringOfNum(std:: vector<int> RoundPart, std:: vector<int> DecimalPart, int Sign);
BigNum Add(BigNum A, BigNum B);
BigNum Reduce(BigNum A, BigNum B);
BigNum operator+(double	B,BigNum A);
std::ostream& operator<<(std::ostream& out,BigNum C);
std::istream& operator>>(std::istream& in,BigNum& C);
std::ostream& operator<<(std::ostream& out,Digit C);
std::istream& operator>>(std::istream& in,Digit C);

#endif