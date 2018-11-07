#include "bignum.h"
using namespace std;
BigNum:: BigNum(string Num)
{
	int StringSize = Num.size();
	BadExceptionForConsrtuctor(Num);
	if(Num[0]=='-')
		Sign=NEGATIVE;
	else 
		Sign=POSITIVE;
	bool does_it_have_decimal_point=false;
	int DecimalPointLocation;
	for(int i=0; i<StringSize; i++)
	{
		if(Num[i]=='.')
		{
			does_it_have_decimal_point=true;
			DecimalPointLocation=i;
			break;
		}
	}
	if(does_it_have_decimal_point==false)
		DecimalPointLocation=StringSize;
	RoundPart=MakeRoundPartFromString(Num,does_it_have_decimal_point,DecimalPointLocation,Sign);
	DecimalPart=MakeDecimalPartFromString(Num,does_it_have_decimal_point,DecimalPointLocation,Sign);
	RemoveExtraZerosFromDecimalPart(DecimalPart);

} 
vector<int> MakeRoundPartFromString(string Num,bool does_it_have_decimal_point,int DecimalPointLocation,int Sign)
{
	int tmp;
	vector<int> RoundPart;
	if(Sign==POSITIVE)
		tmp=0;
	else
		tmp=+1;
	for(int i=0+tmp; i<DecimalPointLocation; i++)
	{
		int number=(int) Num[i]-48;
		RoundPart.push_back(number);
	}
	return RoundPart;
}
vector<int> MakeDecimalPartFromString(string Num,bool does_it_have_decimal_point,int DecimalPointLocation,int Sign)
{
	vector<int> DecimalPart;
	for(int i=DecimalPointLocation+1; i<Num.size(); i++)
	{
		int number=(int) Num[i]-48;
		DecimalPart.push_back(number);
	}
	return DecimalPart;
}
void BadExceptionForConsrtuctor(string Num)
{
	int StringSize = Num.size();
	if (StringSize==0)
		throw Bad_Exception("bignum.cpp",5);
	for(int i=0; i<StringSize; i++)
	{
		if(Num[i]!='-' && Num[i]!='.')
			if(Num[i]<48 || Num[i]>57)
				throw Bad_Exception("bignum.cpp",5);
	}
}

BigNum:: BigNum(double Num)
{
	string tmpString=to_string(Num);
	BigNum tmpNum(tmpString);
	RoundPart=tmpNum.get_round_part();
	DecimalPart=tmpNum.get_decimal_part();
	Sign=tmpNum.get_sign();
}
void RemoveExtraZerosFromDecimalPart(std::vector<int> &DecimalPart)
{
	for(int i=DecimalPart.size()-1; i>=0; i--)
	{
		if (DecimalPart[i]==0)
			DecimalPart.erase(DecimalPart.begin()+i);
		else 
			break;
	}
}
BigNum:: BigNum()
{
	BigNum tmpNum("0");
	RoundPart=tmpNum.get_round_part();
	DecimalPart=tmpNum.get_decimal_part();
	Sign=tmpNum.get_sign();
}

std:: string MakeStringOfNum(vector<int> RoundPart, vector<int> DecimalPart, int Sign)
{
	RemoveExtraZerosFromDecimalPart(DecimalPart);
	RemoveExtraZerosFromRoundPart(RoundPart);
	string ReturnStr="";
	if(Sign==NEGATIVE)
		ReturnStr.push_back('-');
	for(int i=0; i<RoundPart.size(); i++)
		ReturnStr.push_back(RoundPart[i]+48);
	if(DecimalPart.size()!=0)
	{
		ReturnStr.push_back('.');
		for(int i=0; i<DecimalPart.size(); i++)
			ReturnStr.push_back(DecimalPart[i]+48);
	}
	return ReturnStr;

}
void BigNum:: print()
{
	string strForPrint=MakeStringOfNum(RoundPart, DecimalPart, Sign);
	cout<<strForPrint<<endl;
}

void ExtraZerosToDecimalPart(int NumOfZeros,vector<int> &DecimalPart)
{
	for(int i=0; i<NumOfZeros; i++)
		DecimalPart.push_back(0);
}
void RemoveExtraZerosFromRoundPart(vector<int> &RoundPart)
{
	for(int i=0; i<RoundPart.size(); i++)
	{
		if(RoundPart[i]==0)
		{
			RoundPart.erase(RoundPart.begin()+i);
		} 
		else 
			break;
	}
}
void ExtraZerosToRoundPart(int NumOfZeros,vector<int> &RoundPart)
{
	vector<int> tmp;
	for(int i=0; i<NumOfZeros; i++)
		tmp.push_back(0);
	for(int i=0; i<RoundPart.size(); i++)
		tmp.push_back(RoundPart[i]);
	RoundPart=tmp;
}
BigNum BigNum::operator+(BigNum B)
{
	string Astring=MakeStringOfNum(RoundPart,DecimalPart,Sign);
	BigNum A(Astring);
	BigNum FirstArg,SecondArg;
	if(A<B)
	{
		FirstArg=A;
		SecondArg=B;
		return SecondArg+FirstArg;
	} else
	{
		if(Sign*B.Sign==POSITIVE)
		{
			return Add(A,B);
		} else
		{
			return Reduce(A,B);
		}
	}
}
bool BigNum::operator<(const BigNum& B) const
{
	if(RoundPart.size()>B.RoundPart.size())
		return false;
	else if(RoundPart.size()<B.RoundPart.size())
		return true;
	else 
	{
		for(int i=0; i<RoundPart.size(); i++)
		{
			if(RoundPart[i]>B.RoundPart[i])
				return false;
			else if(RoundPart[i]<B.RoundPart[i])
				return true;
		}
	}
	if(DecimalPart.size()>B.DecimalPart.size())
		return false;
	else if(DecimalPart.size()<B.DecimalPart.size())
		return true;
	else 
	{
		for(int i=0; i<DecimalPart.size(); i++)
		{
			if(DecimalPart[i]>B.DecimalPart[i])
				return false;
			else if(DecimalPart[i]<B.DecimalPart[i])
				return true;
		}
	}
	return false;
}
BigNum Add(BigNum A, BigNum B)
{
	int Carry=0;
	vector<int> ADecimalPart=A.get_decimal_part() , BDecimalPart=B.get_decimal_part();
	vector<int> ARoundPart=A.get_round_part(), BRoundPart=B.get_round_part();
	int Sign=A.get_sign();
	if(ADecimalPart.size()<BDecimalPart.size())
		ExtraZerosToDecimalPart(BDecimalPart.size()-ADecimalPart.size(),ADecimalPart);
	else 
		ExtraZerosToDecimalPart(ADecimalPart.size()-BDecimalPart.size(),BDecimalPart);
	vector<int> newDecimalPart(ADecimalPart.size());
	for(int i=ADecimalPart.size()-1; i>=0; i--)
	{
		newDecimalPart[i]=(ADecimalPart[i]+BDecimalPart[i]+Carry)%10;
		Carry=(ADecimalPart[i]+BDecimalPart[i]+Carry)/10;
	}
	ExtraZerosToRoundPart(ARoundPart.size()-BRoundPart.size(),BRoundPart);
	vector<int> newRoundPart(ARoundPart.size()+1);
	for(int i=BRoundPart.size()-1; i>=0; i--)
	{
		newRoundPart[i+1]=(ARoundPart[i]+BRoundPart[i]+Carry)%10;
		Carry=(ARoundPart[i]+BRoundPart[i]+Carry)/10;
	}
	newRoundPart[0]=Carry;
	int newSign=Sign;
	RemoveExtraZerosFromDecimalPart(newDecimalPart);
	RemoveExtraZerosFromRoundPart(newRoundPart);
	string tmp=MakeStringOfNum(newRoundPart,newDecimalPart,newSign);
	BigNum C(tmp);
	return C;
}
BigNum Reduce(BigNum A, BigNum B)
{
	vector<int> ADecimalPart=A.get_decimal_part() , BDecimalPart=B.get_decimal_part();
	vector<int> ARoundPart=A.get_round_part(), BRoundPart=B.get_round_part();
	int newSign=A.get_sign();
	if(ADecimalPart.size()<BDecimalPart.size())
		ExtraZerosToDecimalPart(BDecimalPart.size()-ADecimalPart.size(),ADecimalPart);
	else 
		ExtraZerosToDecimalPart(ADecimalPart.size()-BDecimalPart.size(),BDecimalPart);
	vector<int> newDecimalPart(ADecimalPart.size());
	for(int i=ADecimalPart.size()-1; i>=0; i--)
	{
		if(ADecimalPart[i]>=BDecimalPart[i])
			newDecimalPart[i]=ADecimalPart[i]-BDecimalPart[i];
		else
		{
			if(i!=0)
			{
				ADecimalPart[i-1]--;
				ADecimalPart[i]+=10;
				newDecimalPart[i]=ADecimalPart[i]-BDecimalPart[i];
			}
			else
			{
				ARoundPart[ARoundPart.size()-1]--;
				ADecimalPart[i]+=10;
				newDecimalPart[i]=ADecimalPart[i]-BDecimalPart[i];
			}
		}
	}
	ExtraZerosToRoundPart(ARoundPart.size()-BRoundPart.size(),BRoundPart);
	vector<int> newRoundPart(ARoundPart.size());
	for(int i=BRoundPart.size()-1; i>=0; i--)
	{
		if(ARoundPart[i]>=BRoundPart[i])
			newRoundPart[i]=ARoundPart[i]-BRoundPart[i];
		else
		{
			ARoundPart[i-1]--;
			ARoundPart[i]+=10;
			newRoundPart[i]=ARoundPart[i]-BRoundPart[i];
		}
	}
	RemoveExtraZerosFromRoundPart(newRoundPart);
	RemoveExtraZerosFromDecimalPart(newDecimalPart);
	string tmp=MakeStringOfNum(newRoundPart,newDecimalPart,newSign);
	BigNum C(tmp);
	return C;
}

BigNum BigNum:: operator+(double B)
{
	BigNum BBigNum(B);
	string tmp=MakeStringOfNum(RoundPart,DecimalPart,Sign);
	BigNum A(tmp);
	return A + BBigNum;
}
BigNum operator+(double	B,BigNum A)
{
	BigNum BBigNum(B);
	return A+BBigNum;
}
BigNum& BigNum:: operator+=(BigNum B)
{
	string tmp=MakeStringOfNum(RoundPart,DecimalPart,Sign);
	BigNum A(tmp);
	BigNum C=A+B;
	RoundPart=C.get_round_part();
	DecimalPart=C.get_decimal_part();
	Sign=C.get_sign();
	return *this;
}
BigNum& BigNum:: operator++()
{
	string tmp=MakeStringOfNum(RoundPart,DecimalPart,Sign);
	BigNum A(tmp);
	BigNum C=A+1;
	RoundPart=C.get_round_part();
	DecimalPart=C.get_decimal_part();
	Sign=C.get_sign();
	return *this;
}
BigNum BigNum:: operator++(int x)
{
	string tmp=MakeStringOfNum(RoundPart,DecimalPart,Sign);
	BigNum A(tmp);
	BigNum C=A+1;
	RoundPart=C.get_round_part();
	DecimalPart=C.get_decimal_part();
	Sign=C.get_sign();
	return A;
}
BigNum& BigNum:: operator=(BigNum B)
{
	RoundPart=B.get_round_part();
	DecimalPart=B.get_decimal_part();
	Sign=B.get_sign();
	return *this;
}
BigNum& BigNum:: operator-()
{
	Sign*=NEGATIVE;
	return *this;
}
Digit BigNum:: operator[](int i)
{
	if(i>=0)
	{
		if(i>=RoundPart.size())
		{
			ExtraZerosToRoundPart(i-RoundPart.size()+1,RoundPart);
			Digit Dig(&RoundPart[RoundPart.size()-1-i]);
			return Dig;
		}
		else
		{
			Digit Dig(&RoundPart[RoundPart.size()-1-i]);
			return Dig;
		}
	}
	else 
	{
		i*=-1;
		if(i>=DecimalPart.size())
		{
			ExtraZerosToDecimalPart(i-DecimalPart.size()+1,DecimalPart);
			Digit Dig(&DecimalPart[i]);
			return Dig;
		}
		else
		{
			Digit Dig(&DecimalPart[i]);
			return Dig;
		}
	}
}
bool BigNum:: operator==(BigNum& B)
{
	RemoveExtraZerosFromDecimalPart(DecimalPart);
	RemoveExtraZerosFromRoundPart(RoundPart);
	RemoveExtraZerosFromDecimalPart(B.DecimalPart);
	RemoveExtraZerosFromRoundPart(B.RoundPart);
	if(Sign!=B.Sign)
		return false;
	if(RoundPart.size()!=B.RoundPart.size())
		return false;
	if(DecimalPart.size()!=B.DecimalPart.size())
		return false;
	for(int i=0; i<RoundPart.size(); i++)
		if(RoundPart[i]!=B.RoundPart[i])
			return false;
	for(int i=0; i<DecimalPart.size(); i++)
		if(DecimalPart[i]!=B.DecimalPart[i])
			return false;
	return true;
}
ostream& operator<<(ostream& out, BigNum C)
{
	string str=MakeStringOfNum(C.get_round_part(),C.get_decimal_part(),C.get_sign());
	out<<str<<endl;
	return out;
}
istream& operator>>(istream& in,BigNum& C)
{
	string str;
	in>> str;
	BigNum tmp(str);
	C=tmp;
	return in;
}
ostream& operator<<(ostream& out,Digit C)
{
	int* PointerToDigit=C.get_pointer();
	out<<*PointerToDigit<<endl;
	return out;
}
std::istream& operator>>(std::istream& in,Digit C)
{
	int x;
	in>>x;
	if(x>9 || x<0)
		throw Bad_Exception("bignum.cpp",406);
	C.set_val(x);
	return in;
}