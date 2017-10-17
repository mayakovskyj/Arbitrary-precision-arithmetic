#include "Long_number.h"

void Long_number::Number(string a) {

	if (a.size() % Const_1 == 0)
		k = a.size() / Const_1;
	else
		k = a.size() / Const_1 + 1;
	int p = a.size();
	int n = 0;
	if (a.size() >= Const_1) {
		p = Const_1;
		n = a.size() - p;
	}
	string m;
	for (int i = 0; i<k; i++) {
		b.push_back(Parse(m.assign(a, n, p)));
		if (n - Const_1<0) {
			p = n;
			n = 0;
		}
		else
			n -= p;
	}
	if (a[0] == '-') {
		k--;
		b[k - 1] *= (-1);
	}
}
Long_number Long_number::Sum(Long_number other) {
	Long_number c;
	if (k >= other.k) {
		c.k = k;
		for (int i = other.k; i<c.k; i++)
			other.b.push_back(0);
	}
	else {
		c.k = other.k;
		for (int i = k; i<c.k; i++)
			b.push_back(0);
	}

	int p = 0;
	for (int i = 0; i<c.k; i++) {
		c.b.push_back(p + b[i] + other.b[i]);
		p = 0;
		if (c.b[i] / Const>0) {
			p = c.b[i] / Const;
			c.b[i] %= Const;
		}
	}
	if (p != 0) {
		c.k++;
		c.b.push_back(p);
	}

	return c;
}

Long_number Long_number::Difference(Long_number other) {
	Long_number result;
	Long_number a = (*this);
	Long_number d = other;
	bool n = true;

	if (a.b[a.k - 1]<0 && d.b[d.k - 1]>0)
		return (a.Mult_on_int(-1) + d).Mult_on_int(-1);
	else if (a.b[a.k - 1]>0 && d.b[d.k - 1]<0)
		return (a + d.Mult_on_int(-1));
	else {
		if (d>a) {
			a.b.swap(d.b);
			int l = a.k;
			a.k = d.k;
			d.k = l;
			n = false;
		}

		int m = 0;
		result.k = k;
		for (int i = d.k; i<result.k; i++)
			d.b.push_back(0);
		for (int i = d.k; i<result.k; i++)
			d.b.push_back(0);
		for (int i = 0; i<result.k; i++) {
			if (a.b[i]<d.b[i]) {
				a.b[i] += Const;
				if (i + 1<result.k)
					d.b[i + 1]++;
			}
			result.b.push_back(a.b[i] - d.b[i]);
		}
	}
	int l = result.k;
	if (l != 1)
		for (int i = 0; i<l - 1; i++) {
			if (result.b[l - 1 - i] == 0)
				result.k--;
			else
				break;
		}
	if (n == false)
		result.b[result.k - 1] *= (-1);
	return result;
}

Long_number Long_number::Multiplication(Long_number other) {//звичайне множення в стовпчик
	Long_number c;
	Long_number a;
	c.k = k + other.k;
	a.k = c.k;
	for (int i = 0; i<c.k; i++)
		c.b.push_back(0);
	for (int i = other.k; i<c.k; i++)
		other.b.push_back(0);
	for (int i = k; i<c.k; i++)
		b.push_back(0);

	int p = 0;
	for (int i = 0; i<other.k; i++) {
		for (int j = 0; j<c.k; j++) {
			a.b.push_back((b[j] * other.b[i] % Const + p) % Const);
			p = b[j] * other.b[i] / Const + (b[j] * other.b[i] % Const + p) / Const;
		}
		if (i >= 1)
			for (int m = a.k - 1; m >= i; m--)
				a.b[m] = a.b[m - i];
		for (int m = 0; m<i; m++)
			a.b[m] = 0;

		c = c.Sum(a);
		a.b.clear();
	}
	c.k = k + other.k;
	int m = c.k;
	for (int i = 0; i<m - 1; i++) {
		if (c.b[m - 1 - i] == 0)
			c.k--;
		else
			break;
	}

	return c;
}
Long_number Long_number::Mult_on_int(int a) {
	//множення на число
	Long_number result;
	result.k = k + 1;
	b[k] = 0;
	int m;
	if (a<0)
		m = (-1)*a;
	else
		m = a;
	for (int i = 0; i<result.k; i++) {
		result.b.push_back(b[i] * m);
		result.b[i + 1] += result.b[i] / Const;
		result.b[i] %= Const;
	}
	if (result.b[k] == 0)
		result.k--;
	if (a<0)
		result.b[k - 1] *= (-1);
	return result;
}

Long_number Long_number::Division_on_int(int a) {
	Long_number result;
	Long_number c;
	c.k = k;
	c.b = b;
	result.k = k;
	for (int i = k - 1; i >= 0; i--) {
		while (c.b[i]<a&&i>0) {
			c.b[i] = c.b[i] * Const + c.b[i - 1];
			c.b[i - 1] = c.b[i] - a*(c.b[i] / a);
		}
		result.b.push_back(c.b[i] / a);
	}
	return result;
}

Long_number Long_number::div(int m) {
	//ділення на 10 в степені m
	Long_number result;
	result.k = k - m;
	for (int i = 0; i<result.k; i++)
		result.b.push_back(b[i + m]);
	return result;
}
Long_number Long_number::Division(Long_number this1, Long_number other) {
	//ділення алгоритмом Кука
	Long_number result;
	Long_number remainder;
	Long_number integer_part;
	Long_number a;
	a.k = this1.k + 1;
	for (int i = 0; i<a.k; i++) {
		if (i == (a.k - 1))
			a.b.push_back(1);
		else
			a.b.push_back(0);
	}

	Long_number m;
	m.k = this1.k - other.k + 1;
	for (int i = 0; i<m.k; i++) {
		if (i == (m.k - 1))
			m.b.push_back(1);
		else
			m.b.push_back(0);
	}

	Long_number c = m;
	while (true) {
		m = m + (m*(a - other*m)).div(a.k - 1);
		if (c == m)
			break;
		else
			c = m;
	}
	integer_part = (this1*m).div(a.k - 1);
	remainder = this1 - other*integer_part;

	Long_number addition;
	addition.k = 1;
	addition.b.push_back(1);

	while (remainder>other) {
		integer_part = integer_part + addition;
		remainder = remainder - other;
	}

	/* result.k=integer_part.k+remainder.k;
	for(int i=0;i<remainder.k;i++)
	result.b.push_back(remainder.b[i]);

	for(int i=remainder.k;i<result.k;i++)
	result.b.push_back(integer_part.b[i-remainder.k]);*/

	return result;
}

bool Long_number::operator==(Long_number n) {
	if (k != n.k)
		return false;
	else
		for (int i = 0; i<k; i++) {
			if (b[i] == n.b[i])
				continue;
			else
				return false;
		}
	return true;
}
bool Long_number::operator>(Long_number other) {
	if ((*this).Max(other) == (*this))
		return true;
	else
		return false;

}
Long_number Long_number::Karatsuba(Long_number this1, Long_number other) {

	Long_number result;
	result.k = this1.k + other.k;

	if (this1.k == 1 || other.k == 1) {
		result = this1*other;
		return result;
	}

	Long_number this_part1;
	this_part1.k = (this1.k + 1) / 2;
	for (int i = 0; i<this_part1.k; i++)
		this_part1.b.push_back(this1.b[i]);

	Long_number this_part2;
	this_part2.k = this1.k / 2;
	for (int i = 0; i<this_part2.k; i++)
		this_part2.b.push_back(this1.b[this_part1.k + i]);

	Long_number other_part1;
	other_part1.k = (this1.k + 1) / 2;
	for (int i = 0; i<other_part1.k; i++)
		other_part1.b.push_back(other.b[i]);

	Long_number other_part2;
	other_part2.k = other.k - other_part1.k;
	for (int i = 0; i<other_part2.k; i++)
		other_part2.b.push_back(other.b[other_part1.k + i]);


	Long_number a = Karatsuba(this_part1, other_part1);
	Long_number c = Karatsuba(this_part2, other_part2);
	Long_number ac = Karatsuba((this_part1 + this_part2), (other_part1 + other_part2)) - a - c;

	for (int i = c.k; i<c.k + this_part1.k * 2; i++)
		c.b.push_back(0);
	c.k += this_part1.k * 2;
	for (int i = c.k - 1; i >= c.k - this_part1.k * 2; i--)
		c.b[i] = c.b[i - this_part1.k * 2];
	for (int i = 0; i<this_part1.k * 2; i++)
		c.b[i] = 0;

	for (int i = ac.k; i<ac.k + this_part1.k; i++)
		ac.b.push_back(0);
	ac.k += this_part1.k;
	for (int i = ac.k - 1; i>0; i--)
		ac.b[i] = ac.b[i - this_part1.k];
	for (int i = 0; i<this_part1.k; i++)
		ac.b[i] = 0;

	result = c + a + ac;

	return result;
}
