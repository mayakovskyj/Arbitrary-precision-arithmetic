#pragma once
#include <vector>
#include <string>
#include <algorithm>

using std::string;
using std::vector;

class long_number
{
private:
	vector<int> number;
public:
	long_number();
	long_number(const string s);
	long_number(vector<int> theNumber);

	//Ha-ha, classic algorithms
	const long_number operator*(const long_number& other)const;
	const long_number operator+(const long_number& other)const;
	const long_number operator-(const long_number& other)const;
	bool operator>(const long_number& other)const;
	const long_number operator / (const int &x)const;
	long_number& operator=(const long_number& right);
	//Ha-ha, no ha-ha :|
	long_number karatsuba(long_number& other);
	long_number toom3wayMultiplication(long_number& other);
	long_number toomInverse(long_number& other);
	void theNumber()const;
	~long_number();
};

