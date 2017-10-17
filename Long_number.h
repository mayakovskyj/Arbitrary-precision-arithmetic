#pragma once
//#include <iostream>
//#include <vector>
#include "help_functions.h"
#define Const 10
#define Const_1 Power1(Const,10)
	
using namespace std;

class Long_number
{
private:
	int k;
	vector<long long int> b;

public:
	Long_number Sum(Long_number other);
	Long_number Difference(Long_number other);
	Long_number Multiplication(Long_number other);
	Long_number Mult_on_int(int a);
	Long_number Division_on_int(int a);
	Long_number Max(Long_number other);
	Long_number Division(Long_number this1, Long_number other);
	Long_number Karatsuba(Long_number this1, Long_number other);
	Long_number Toom_Cook_3(Long_number this1, Long_number other); 
	Long_number Schonhage(Long_number this1, Long_number other);
	Long_number operator+ (Long_number n) { return Sum(n); };
	Long_number operator- (Long_number n) { return Difference(n); };
	Long_number operator* (Long_number n) { return Multiplication(n); };
	bool operator==(Long_number n);
	bool operator>(Long_number other);
	Long_number div(int m);
	void Number(string a);
	void get_string(string a) { Number(a); };
	void number_out();
};



