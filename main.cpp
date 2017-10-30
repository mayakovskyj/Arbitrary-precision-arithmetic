#include "long_number.h"
#include <iostream>

using namespace std;

int main() {
	long_number myNumber;
	long_number myNumber1;
	long_number b1("194305406543241241242131231249");
	long_number lom("991948532142142131231094755497");
	myNumber = b1.toom3wayMultiplication(lom);
	myNumber1 = lom.karatsuba(b1);
	myNumber.theNumber();
	myNumber1.theNumber();
	system("pause");
	return 0;
}
