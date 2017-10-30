#include "long_number.h"
#include <iostream>

using namespace std;

long_number::long_number() {}

long_number::long_number(const string s)
{
	//if (!stoi(s)) throw ("Your value is not a number!");
//	if (s.size() == 2) 
	int i = s.size() - 1;
	while (i > 1) {
		number.push_back(int(s[i]) - 48);
		i--;
	}
	if (s[0] == '-') number.push_back(-1 * (int(s[1]) - 48));
	else {
		if (s[1] != '\0')
			number.push_back(int(s[1]) - 48);
		number.push_back(int(s[0]) - 48);
	}
}

long_number::long_number(vector<int> theNumber)
{
	number = theNumber;
}


const long_number long_number::operator*(const long_number& other)const
{
	long_number x = *this;
	long_number y = other;
	int n = other.number.size();
	int m = (*this).number.size();
	string s;
	int k = 0, i = 0, j = 0;

	if (number[number.size() - 1] < 0) {
		if (other.number[other.number.size() - 1] < 0) {
			x.number[x.number.size() - 1] *= -1;
			y.number[y.number.size() - 1] *= -1;
			return x*y;
		}
		x.number[x.number.size() - 1] *= -1;
		x = x*y;
		x.number[x.number.size() - 1] *= -1;
		return x;
	}
	if (y.number[y.number.size() - 1] < 0) {
		y.number[y.number.size() - 1] *= -1;
		x = x*y;
		x.number[x.number.size() - 1] *= -1;
		return x;
	}
	
	for (int i = 0; i <= m+n+1; ++i)
		s += '0';
	long_number *result = new long_number(s);
	
	for (j = 0; j < n; j++) {
		k = 0;
		if (other.number[j] == 0) {
			(*result).number[j + m] = 0;
			continue;
		}
		for (i = 0; i < m; i++) {
			int t = (*this).number[i] * other.number[j] + (*result).number[i + j] + k;
			(*result).number[i + j] = t % 10;
			k = t / 10;
		}
		(*result).number[j + m] = k;
	}
	i = m + n + 1;
	while ((*result).number[i] == 0 && i != 0) {
		(*result).number.pop_back();
		i--;
	}
	return (*result);
}


const long_number long_number::operator/(const int & x) const
{
	if (x == 0) throw ("Division by zero!");
	int n = (*this).number.size();
	string s;
	int k = 0;
	for (int i = 0; i <= n; ++i)
		s += '0';
	long_number *result = new long_number(s);

	for (int i = n - 1; i >= 0; i--)
	{
		int cur = 10 * k + (*this).number[i];
		(*result).number[i] = cur / x;
		k = cur % x;
	}
	int i = n;
	while ((*result).number[i] == 0 && i != 0) {
		(*result).number.pop_back();
		i--;
	}
	return (*result);
}


const long_number long_number::operator+(const long_number & other) const
{
	long_number x = (*this);
	long_number y = (*&other);
	if (number[number.size() - 1] < 0) {
		if (other.number[other.number.size() - 1] < 0) {
			x.number[x.number.size() - 1] *= -1;
			y.number[y.number.size() - 1] *= -1;
			x = x + y;
			x.number[x.number.size() - 1] *= -1;
			return x;
		}
		x.number[x.number.size() - 1] *= -1;
		return y - x;
	}
	if (y.number[y.number.size() - 1] < 0) {
		y.number[y.number.size() - 1] *= -1;
		return x - y;
	}

	int n = max((*this).number.size(), other.number.size());
	string s;
	int k = 0;
	for (int i = 0; i <= n+1; ++i)
		s += '0';
	long_number *result = new long_number(s);
	if (x.number.size() < y.number.size()) 
		while (x.number.size() != y.number.size())
			x.number.push_back(0);
	if (x.number.size() > y.number.size())
		while (y.number.size() != x.number.size())
			y.number.push_back(0);

		for (int i = 0; i < n; i++) {
			int t = (x).number[i] + y.number[i] + k;
			(*result).number[i] = t % 10;
			k = t / 10;
		}
		int i = n + 1;
		while ((*result).number[i] == 0 && i != 0) {
			(*result).number.pop_back();
			i--;
		}
	//if ((*result).number[n] == 0) (*result).number.pop_back();
	return (*result);
}

const long_number long_number::operator-(const long_number & other) const
{
	long_number x = (*this);
	long_number y = other;
	/* if subtrahend is negative, use addition: x-(-y) = x + y;
	if minuend is negative, use addition with adding "-" after: -x-y = -(x+y);
	if both of numbers are negative, use (-other) - (*this): -x-(-y) = y-x */
	if (y.number[y.number.size() - 1] < 0) {
		if (x.number[x.number.size() - 1] > 0) {
			y.number[y.number.size() - 1] *= -1;
			return x + y;
		}
		y.number[y.number.size() - 1] *= -1;
		x.number[x.number.size() - 1] *= -1;
		return y - x;
	}
	if (x.number[x.number.size() - 1] < 0) {
		x.number[x.number.size() - 1] *= -1;
		x = y + x;
		x.number[x.number.size() - 1] *= -1;
		return x;
	}
	bool isPositive = true;
	if (other > (*this)) {
		y = (*this);
		x = other;
		isPositive = false;
	}

	int n = max((*this).number.size(), other.number.size());
	string s;
	int k = 0;
	for (int i = 0; i <= n+1; ++i)
		s += '0';
	long_number *result = new long_number(s);
	/*long_number x = (*this);
	long_number y = (*&other);*/
	if (x.number.size() < y.number.size())
		while (x.number.size() != y.number.size())
			x.number.push_back(0);
	if (x.number.size() > y.number.size())
		while (y.number.size() != x.number.size())
			y.number.push_back(0);
	for (int i = 0; i < y.number.size(); i++) {
		if (x.number[i] < y.number[i]) {
			x.number[i + 1]--;
			x.number[i] += 10;
		}
		(*result).number[i] = x.number[i] - y.number[i];
	}
	int i = n + 1;
	while ((*result).number[i] == 0 && i != 0) {
		(*result).number.pop_back();
		i--;
	}

	//При віднімання більшого числа з меншого, знак першої цифри відповіді(останнього числа вектору) змінюється на "-"
	if (isPositive == false) (*result).number[(*result).number.size() - 1] *= -1;
	return (*result);
}

bool long_number::operator>(const long_number & other) const
{
	if ((*this).number.size() > other.number.size()) return true;
	if ((*this).number.size() < other.number.size()) return false;
	int i = (*this).number.size()-1;
	bool isGreater = false;
	while (i >= 0 && !isGreater) {
		if ((*this).number[i] > other.number[i]) 
			isGreater = true;
		if ((*this).number[i] < other.number[i]) i = -1;
		i--;
	}
	return isGreater;
}

long_number & long_number::operator=(const long_number & right)
{
	if (this == &right) 
		return *this;
	number = right.number;
	return *this;
}

long_number long_number::karatsuba(long_number & other)
{
	int length = max(number.size(), other.number.size());
	if (length <= 14) {
		(*this).theNumber();
		other.theNumber();
		long_number res = (*this)*other;
		res.theNumber();
		return res;
	}

	int m = other.number.size();
	int n = (*this).number.size();

	long_number x = (*this);
	long_number y = (*&other);
	if (n < m) //Adds 0 to make numbers with equal sizes
		while (x.number.size() != y.number.size())
			x.number.push_back(0);
	if (m < n)
		while (y.number.size() != x.number.size())
			y.number.push_back(0);

	int k = (length / 2) + (length % 2);
	vector <int> a0 = { x.number.begin() + k, x.number.end() }; //First k figures from x
	vector <int> a1 = { x.number.begin(), x.number.begin() + k }; //Second k figures from x
	vector <int> b0 = { y.number.begin() + k, y.number.end() };
	vector <int> b1 = { y.number.begin(), y.number.begin() + k };

	long_number a_0(a0), a_1(a1), b_0(b0), b_1(b1);

	long_number a0b0, a0_a1, b0_b1, a1b1, a, b,c, result;  // _ -- "+"
	a0b0 = a_0.karatsuba(b_0);
	a0_a1 = a_0 + a_1;
	b0_b1 = b_0 + b_1;
	a = a0_a1.karatsuba(b0_b1);  // (A0 + A1) * (B0 + B1) 
	a1b1 = a_1.karatsuba(b_1); //(A1*B1)
	c = a - a0b0 - a1b1; //(A0 + A1) * (B0 + B1) - (A0*B0) - (A1*B1)
	a0b0.number.insert(a0b0.number.begin(), 2 * k, 0); // Add zeroes 
	c.number.insert(c.number.begin(), k, 0);
	result = a0b0 + c + a1b1;
	int i = result.number.size() - 1;
	while (result.number[i] == 0 && i != 0) {
		result.number.pop_back();
		i--;
	}
	return result;
}

long_number long_number::toom3wayMultiplication(long_number & other)
{
	int length = max(number.size(), other.number.size());
	/*	if (length <= 9)
	return (*this)*other;*/

	long_number x = (*this);
	long_number y = (*&other);
	int n = x.number.size();
	int m = y.number.size();
	//Adds 0 to make numbers with equal sizes and sizes wich give 0 by mod 3
	if (n < m)
		if (m % 3 != 0)
			while (y.number.size() % 3 != 0)
				y.number.push_back(0);
	while (x.number.size() != y.number.size())
		x.number.push_back(0);
	if (m < n)
		if (n % 3 != 0)
			while (x.number.size() % 3 != 0)
				x.number.push_back(0);
	while (y.number.size() != x.number.size())
		y.number.push_back(0);
	if (m == n)
		if (n % 3 != 0)
			while (x.number.size() % 3 != 0) {
				x.number.push_back(0);
				y.number.push_back(0);
			}

	(*this).theNumber();
	other.theNumber();
	length = x.number.size();
	int k = length / 3;

	// a0*x_2^2 + b0*x_1 + x_0 
	// a1*y_2^2 + b1*y_1 + y_0
	vector<int> x_2 = { x.number.begin() + 2 * k, x.number.end() };
	vector<int> x_1 = { x.number.begin() + k, x.number.begin() + 2 * k };
	vector<int> x_0 = { x.number.begin(), x.number.begin() + k };
	vector<int> y_2 = { y.number.begin() + 2 * k, y.number.end() };
	vector<int> y_1 = { y.number.begin() + k, y.number.begin() + 2 * k };
	vector<int> y_0 = { y.number.begin(), y.number.begin() + k };
	long_number x2(x_2), x1(x_1), x0(x_0), y2(y_2), y1(y_1), y0(y_0);

	// W(0) , W(1), W(2), W(3), W(4)
	long_number W0, W1, W2, W3, W4;
	long_number x_in_2("2");
	long_number x_in_3("3");
	long_number x_in_4("4");
	W0 = x0*y0;
	W1 = (x2 + x1 + x0)*(y2 + y1 + y0);
	W2 = (x_in_2*x_in_2*x2 + x_in_2*x1 + x0)*(x_in_2*x_in_2*y2 + x_in_2*y2 + y0);
	W3 = (x_in_3*x_in_3*x2 + x_in_3*x1 + x0)*(x_in_3*x_in_3*y2 + x_in_3*y2 + y0);
	W4 = (x_in_4*x_in_4*x2 + x_in_4*x1 + x0)*(x_in_4*x_in_4*y2 + x_in_4*y2 + y0);

	// Interpolation
	// 1  0  0   0   0    W0
	// 1  1  1   1   1    W1
	// 1  2  4   8   16   W2
	// 1  3  9   27  81   W3
	// 1  4  16  64  256  W4 

	W1 = W1 - W0;
	W2 = W2 - W0;
	W3 = W3 - W0;
	W4 = W4 - W0;
	/*
	W2 = W2 - x_in_2*W1;
	W3 = W3 - x_in_3*W1;
	W4 = W4 - x_in_4*W4;

	// 1  0  0   0   0    W0
	// 0  1  1   1   1    W1
	// 0  0  2   6   14   W2
	// 0  0  6   24  78   W3
	// 0  0  12  60  252  W4

	W3 = W3 - x_in_3*W2;
	W4 = W4 - x_in_2*x_in_3*W2;

	W4 = W4 - x_in_2*x_in_2*W3;

	// 1  0  0   0   0    W0
	// 0  1  1   1   1    W1
	// 0  0  2   6   14   W2
	// 0  0  0   6   36   W3
	// 0  0  0   0   24   W4

	W4 = W4 / 24;
	W3 = W3 / 6;
	W2 = W2 / 2;

	// 1  0  0   0   0    W0
	// 0  1  1   1   1    W1
	// 0  0  1   3   7    W2
	// 0  0  0   1   6    W3
	// 0  0  0   0   1    W4

	W3 = W3 - W4 * long_number("6");
	W2 = W2 - W4 * long_number("7");
	W1 = W1 - W4;

	// 1  0  0   0   0	  W0
	// 0  1  1   1   0    W1
	// 0  0  1   3   0    W2
	// 0  0  0   1   0    W3
	// 0  0  0   0   1    W4

	W2 = W2 - W3 * x_in_3;
	W1 = W1 - W3;

	W1 = W1 - W2;

	//The Final product is obtained by adding the numbers by shifting
	//So shifting
	W4.number.insert(W4.number.begin(), 4 * k, 0);
	W3.number.insert(W3.number.begin(), 3 * k, 0);
	W2.number.insert(W2.number.begin(), 2 * k, 0);
	W1.number.insert(W1.number.begin(), k, 0);
	*/
	long_number result;
	result = W4 + W3 + W2 + W1 + W0;
	return result;
}

void long_number::theNumber()const
{
	for (int i = number.size() - 1; i >= 0; i--)
		cout << number[i];
	cout << endl;
	/*	s += i + 48;
	reverse(s.begin(), s.end());
	return s;*/
}



long_number::~long_number()
{
}
