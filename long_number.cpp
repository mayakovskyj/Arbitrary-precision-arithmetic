#include "long_number.h"
#include <iostream>

using namespace std;

typedef complex<long_number> base;

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

long_number::long_number(const long long & x)
{
	int i = 0;
	long long x1 = x;
	while (x1 != 0) {
		number.push_back(x1 % 10);
		x1 /= 10;
		i++;
	}
}


void long_number::theNumber()const
{
	for (int i = number.size() - 1; i >= 0; i--)
		cout << number[i];
	cout << endl;
}


long_number::~long_number()
{
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

	for (int i = 0; i <= m + n + 1; ++i)
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

const long_number long_number::operator/(const long long & x) const
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

const long_number long_number::operator/(const long_number & other) const
{
	if (other == long_number("0"))
		throw ("hi");
	long_number x = (*this);
	long_number y = (*&other);

	if (x.number[x.number.size() - 1] < 0) {
		if (y.number[y.number.size() - 1] < 0) {
			x.number[x.number.size() - 1] *= -1;
			y.number[y.number.size() - 1] *= -1;
			return x / y;
		}
		x.number[x.number.size() - 1] *= -1;
		x = x / y;
		x.number[x.number.size() - 1] *= -1;
		return x;
	}
	if (y.number[y.number.size() - 1] < 0) {
		y.number[y.number.size() - 1] *= -1;
		x = x / y;
		x.number[x.number.size() - 1] *= -1;
		return x;
	}

	long_number res("0"), z("1");
	int k = 0;

	while (!(y > x))
	{
		y = y + y;
		z = z + z;
		++k;
	}
	while (k)
	{
		y = y / 2;
		z = z / 2;
		--k;
		while (!(y > x))
		{
			x = x - y;
			res = res + z;
		}
	}
	return res;
}

const long_number long_number::operator%(const long long & x) const
{
	return (*this) - ((*this / x)*long_number(x));
}

const long_number long_number::operator%(const long_number & other) const
{
	return (*this) - ((*this / other)*other);
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
			int t = x.number[i] + y.number[i] + k;
			(*result).number[i] = t % 10;
			k = t / 10;
		}
		(*result).number[n] += k;
		int i = n + 1;
		while ((*result).number[i] == 0 && i != 0) {
			(*result).number.pop_back();
			i--;
		}

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

	//If subtrahend > minuend, the result with sign "-"
	if (isPositive == false) (*result).number[(*result).number.size() - 1] *= -1;
	return (*result);
}

bool long_number::operator>(const long_number & other) const
{
	if ((*this).number[(*this).number.size() - 1] < 0 && (other.number[other.number.size() - 1] >= 0)) return false;
	if ((*this).number[(*this).number.size() - 1] >= 0 && (other.number[other.number.size() - 1] < 0)) return true;
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

bool long_number::operator==(const long_number & other) const
{
		return (*this).number == other.number;
}

long_number long_number::karatsuba(long_number & other)
{
	int length = max(number.size(), other.number.size());
	if (length <= 14) 
		return (*this)*other;

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
	if (length <= 14)
		return (*this)*other;

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
	W1 = (x2 + x1 + x0) * (y2 + y1 + y0);
	W2 = (x_in_2*x_in_2*x2 + x_in_2*x1 + x0)*(x_in_2*x_in_2*y2 + x_in_2*y1 + y0);
	W3 = (x_in_3*x_in_3*x2 + x_in_3*x1 + x0)*(x_in_3*x_in_3*y2 + x_in_3*y1 + y0);
	W4 = (x_in_4*x_in_4*x2 + x_in_4*x1 + x0)*(x_in_4*x_in_4*y2 + x_in_4*y1 + y0);

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

	W2 = W2 - x_in_2*W1;
	W3 = W3 - x_in_3*W1;
	W4 = W4 - x_in_4*W1;

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

	W3 = W3 - (W4 * long_number("6"));
	W2 = W2 - (W4 * long_number("7"));
	W1 = W1 - W4;

	// 1  0  0   0   0	  W0
	// 0  1  1   1   0    W1
	// 0  0  1   3   0    W2
	// 0  0  0   1   0    W3
	// 0  0  0   0   1    W4

	W2 = W2 - (W3 * x_in_3);
	W1 = W1 - W3;

	W1 = W1 - W2;

	//The Final product is obtained by adding the numbers by shifting
	//So shifting
	W4.number.insert(W4.number.begin(), 4 * k, 0);
	W3.number.insert(W3.number.begin(), 3 * k, 0);
	W2.number.insert(W2.number.begin(), 2 * k, 0);
	W1.number.insert(W1.number.begin(), k, 0);

	long_number result;
	result = W4 + W3 + W2 + W1 + W0;
	return result;
}

int long_number::bits_in_number()const
{
	long_number n = *this;
	if (n == long_number("0"))
		return 1;
	int result = 0;
	while (!(n == long_number("0")))
	{
		n = n / 2;
		++result;
	}
	return result;
}

long_number long_number::shoenhage(long_number & other)
{
	int length = max(number.size(), other.number.size());
	if (length <= 14)
		return (*this)*other;

	long_number x = (*this);
	long_number y = other;

	//calculating k0
	int k = max(x.bits_in_number(), y.bits_in_number());
	int n = k;
	if (k <= 26) k = 1;
	if (k % 18 == 0) k /= 18;
	else k = (k / 18) + 1;

	vector<long long> q = {k};
	vector<long long> p = {};
	for (int i = 0; i < 10; ++i)
		q.push_back(q.back() * 3 - 1);
	for (int i = 0; i < q.size(); ++i)
		p.push_back(q[i] * 18 + 8);
	
	int i = 0;
	while (n > p[i])
		++i;

	// add zeros
	while (number.size() < p[i])
		number.push_back(0);
	while (other.number.size() < p[i])
		other.number.push_back(0);

	vector<long_number> m(6);
	m[0] = pow(2, (6 * q[i] - 1)) - 1;
	m[1] = pow(2, (6 * q[i] + 1)) - 1;
	m[2] = pow(2, (6 * q[i] + 2)) - 1;
	m[3] = pow(2, (6 * q[i] + 3)) - 1;
	m[4] = pow(2, (6 * q[i] + 5)) - 1;
	m[5] = pow(2, (6 * q[i] + 7)) - 1;

	vector<long_number> v(6), u(6);
	for (i = 0; i < 6; i++) {
		v[i] = x % m[i];
		u[i] = y % m[i];
	}
	
	vector<long_number> r(6);
	for (i = 0; i < 6; i++)
		r[i] = (v[i] * u[i]) % m[i];
	
	// calculating w, using Chinese remainder theorem
		long_number mult_product(1);
		long_number sum("0"), mi;

		for (int i = 0; i < 6; i++) mult_product = mult_product * m[i];
		for (int i = 0; i < 6; i++) {
			mi = mult_product / m[i];
			long_number mi1 = mi.find_inverse_by_mod(m[i]);
			sum = sum + (mi1 * mi * r[i]);
		}
		return sum % mult_product;
}

// returns mi^-1 where (mi * mi^-1)  == 1 (mod m)
long_number long_number::find_inverse_by_mod(long_number& m) const
{
	long_number b0 = m, t, q, one("1"), null("0"), a = *this;
	long_number x0("0"), x1("1");
	if (m == one) return one;
	while (a > one) {
		q = a / m;
		t = m;
		m = a % m;
		a = t;
		t = x0;
		x0 = x1 - (q * x0);
		x1 = t;
	}
	if (null > x1)
		x1 = b0 + x1;
	return x1;
}

long_number long_number::strassen(long_number & other)
{
	int length = max(number.size(), other.number.size());
	if (length <= 14)
		return (*this)*other;

	long_number a = *this;
	long_number b = other;
	vector<int> res;
	vector<complex<double>> fa(a.number.begin(), a.number.end()), fb(b.number.begin(), b.number.end());
	size_t n = 1;
	while (n < max(a.number.size(), b.number.size()))  n <<= 1;
	n <<= 1;
	fa.resize(n), fb.resize(n);

	FFT(fa, false), FFT(fb, false);
	for (size_t i = 0; i<n; ++i)
		fa[i] *= fb[i];
	FFT(fa, true);

	res.resize(n);

	for (size_t i = 0; i < n; ++i)
		res[i] = int(fa[i].real() + 0.5);

	int carry = 0;
	for (size_t i = 0; i<n; ++i) {
		res[i] += carry;
		carry = res[i] / 10;
		res[i] %= 10;
	}
	int i = n - 1;
	while (res[i] == 0 && i != 0) {
		res.pop_back();
		i--;
	}
	return long_number(res);
}


void long_number::FFT(vector<complex<double>>& a, bool invert)
{
		int n = (int)a.size();
		if (n == 1)  return;

		vector<complex<double>> a0(n / 2), a1(n / 2);
		for (int i = 0, j = 0; i<n; i += 2, ++j) {
			a0[j] = a[i];
			a1[j] = a[i + 1];
		}
		FFT(a0, invert);
		FFT(a1, invert);

		double ang = 2 * PI / n * (invert ? -1 : 1);
		complex<double> w(1), wn(cos(ang), sin(ang));
		for (int i = 0; i<n / 2; ++i) {
			a[i] = a0[i] + w * a1[i];
			a[i + n / 2] = a0[i] - w * a1[i];
			if (invert)
				a[i] /= 2, a[i + n / 2] /= 2;
			w *= wn;
		}
}
