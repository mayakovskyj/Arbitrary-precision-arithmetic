#include "long_number.h"
#include "factorizations.h"
#include <iostream>

using namespace std;

int main() {
	long_number b("2171894412424173123213127828242344");
	long_number a("214121313189419248312343");
	long_number karats, toom, shoen, strass;

	karats = a.karatsuba(b);
	toom = a.toom3wayMultiplication(b);
	shoen = a.shoenhage(b);
	strass = a.strassen(b);

	karats.theNumber();
	toom.theNumber();
	shoen.theNumber();
	strass.theNumber();

	system("pause");
	return 0;
}
