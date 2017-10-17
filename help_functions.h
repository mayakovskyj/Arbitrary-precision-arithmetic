#include <vector>
#include "math.h"

#ifndef HELP_FUNCTIONS_H_INCLUDED
#define HELP_FUNCTIONS_H_INCLUDED

using namespace std;

int Power1(int a,int b){
	int m = 0;
	while (a > 1) {
		a /= b;
		m++;
	}
    return m;
}

int Get_digit(int a) {
	//кількість розрядів
    int k=0;
	if (a == 0)
        k++;
	while (a > 0) {
		a /= 10;
        k++;
    }
    return k;
}

int Parse(string s) {
	int k = 0;
	for (int i = 1; i < s.size(); i++) {
		int m = s[i] - '0';
		k += m*pow(10, s.size() - 1 - i);
	}

	if (s[0] == '-')
		k *= (-1);
    else
		k += (s[0] - '0')*pow(10, s.size() - 1);

	return k;
}

#endif // HELP_FUNCTIONS_H_INCLUDED

