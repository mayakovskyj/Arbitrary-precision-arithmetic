#include "long_number.h"
#include <iostream>

using namespace std;

int main() {
	long_number myNumber = long_number("12345678911234567891");
	long_number myNumber1 = long_number("148999879879997979797799");
	long_number n1 = long_number("146979677678");
	long_number n2 = long_number("911246913569");
	n1 = n1 * n2;
	//n1.theNumber();
	myNumber = myNumber.karatsuba(myNumber1);
	//myNumber = myNumber.toom3wayMultiplication(myNumber1);
//	myNumber = myNumber1 - myNumber;
//	cout << result.theNumber() << endl;
//	myNumber.theNumber();
//	myNumber1.theNumber();
	myNumber.theNumber();
	system("pause");
	return 0;
}