#pragma once
#include <vector>
#include <string>
#include <algorithm>
#include <iterator>
#include <cmath>
#include <complex> //using for FFT

using std::complex;
using std::string;
using std::vector;
using std::iterator;

#define PI           3.14159265358979323846

class long_number
{
private:
	vector<int> number;
public:
	long_number();
	long_number(const string s);
	long_number(vector<int> theNumber);
	long_number(const long long &x);

	//operators
	const long_number operator+(const long_number& other)const;
	const long_number operator-(const long_number& other)const;
	const long_number operator*(const long_number& other)const;
	const long_number operator / (const long long &x)const;
	const long_number operator / (const long_number& other)const;
	const long_number operator%(const long long &x)const;
	const long_number operator%(const long_number &other)const;

	long_number& operator=(const long_number& right);
	bool operator>(const long_number& other)const;
	bool operator==(const long_number& other)const;
	long_number operator - () const;
	long_number operator + () const;
	
	//Multiplication algorithms 
	long_number karatsuba(long_number& other);
	long_number toom3wayMultiplication(long_number& other);
	long_number shoenhage(long_number& other);
		int bits_in_number()const;
		long_number find_inverse_by_mod(long_number& m) const;
	long_number strassen(long_number& other);
		void FFT(vector<complex<double>> &a, bool invert);

	//Algorithms for prime numbers
	bool is_prime_Solovey_Strassen();
		long_number gcd(const long_number &other)const;
		long_number random_number();
		long_number power(const long_number &number, const long_number p);
		long_number jacobi(long_number &other)const;
	
	void theNumber()const;
	~long_number();
};
