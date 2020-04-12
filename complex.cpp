#define debugMode 0
#if debugMode==1
#define Log(x) std::cout<<x<<std::endl
#else
#define Log(x)
#endif
#include <iostream>
#include<math.h>
class Complex
{
private:
	float real_;
	float imag_;
public:
	Complex():real_(0),imag_(0){}
	Complex(float,float);
	Complex(const Complex&);
	Complex(Complex&&); 
	~Complex();
	Complex operator +(Complex const&)const;
	Complex operator -(Complex const&)const;
	Complex& operator +=(const Complex &);
	Complex& operator -=(const Complex&);
	Complex operator *(const Complex &)const;
	bool operator ==(const Complex&)const;
	bool operator !=(const Complex&)const;
	friend std::ostream& operator<<(std::ostream &,const Complex&);
	friend std::istream& operator >>(std::istream&,Complex&);
	float Modul()const;
	float GetReal()const;
	float GetImage()const;
};
Complex::Complex(float r,float i):real_(r),imag_(i)
{
	Log("Called parametrized ctor");
}
Complex::Complex(const Complex&other):real_(other.real_),imag_(other.imag_)
{
	Log("Called copy ctor");
}
Complex::Complex(Complex&&other):real_(other.real_),imag_(other.imag_)
{
	Log("Called move ctor");
}
Complex::~Complex()
{
	Log("Called dtor");
}
Complex Complex::operator +(Complex const& other)const
{
	Log("Called operator +");
	Complex result;
	result.real_=real_+other.real_;
	result.imag_=imag_+other.imag_;
	return result;
}
Complex Complex::operator -(Complex const& other)const
{
	Log("Called operator -");
	Complex result;
	result.real_=real_-other.real_;
	result.imag_=imag_-other.imag_;
	return result;
}
Complex& Complex::operator +=(const Complex& other)
{
	Log("Called operator +=");
	real_+=other.real_;
	imag_+=other.imag_;
	return(*this);
}
Complex& Complex::operator -=(const Complex& other)
{
	Log("Called operator-=");
	real_-=other.real_;
	imag_-=other.imag_;
	return(*this);
} 
Complex Complex::operator *(const Complex&other)const
{
	Log("Complex operator *");
	Complex result;
	result.real_=(real_*other.real_)-(imag_*other.imag_);
	result.imag_=(imag_*other.real_)+(real_*other.imag_);
	return result;
}
bool Complex::operator==(const Complex&other)const
{
	Log("Called operator ==");
	if(real_!=other.real_)
	{
		return 0;
	}
	if(imag_!=other.imag_)
	{
		return 0;
	}
	return 1;
}
bool Complex::operator!=(const Complex&other)const
{
	Log("Called operator !=");
   return !(other==*this);
}
float Complex::Modul()const
{
	Log("Called Modul");
	float modul;
	modul=sqrt(pow(real_,2)+pow(imag_,2));
	return modul;
}
float Complex::GetReal()const
{
	Log("Called GetReal");
	return real_;
}
float Complex::GetImage()const
{
	Log("Called GetImage");
	return imag_;
}
 std::ostream& operator<<(std::ostream &out ,const Complex&current)
 {
 	Log("Called friend function  ostream operator <<");
  	if(current.imag_==0)
 	{
 		out<<current.real_;
 		return out;
 	}
 	if(current.real_!=0)
 	{
 		out<<current.real_;
 		if(current.imag_>0)
 		{
 			out<<"+";
 		}
 	}
 	if(current.imag_!=1 && current.imag_!=-1)
 	{
 		out<<current.imag_<<"*";
 	}
 	if(current.imag_==-1)
 	{
 		out<<"-";
 	}
 	out<<"i";
 	return out;
 }

std::istream& operator >>(std::istream&in,Complex&current)
{
	Log("Called friend function istream& operator  >>");
	in>>current.real_;
	in>>current.imag_;
	return in;
}
main()
{
	Complex a(3,-4);
	Complex b(2,-5);
	std::cout<<a-b<<std::endl;
	return 0;
}
