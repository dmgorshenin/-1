#include <iostream>
#include <string>
#include "Header.h"
using namespace std;

int main()
{
	setlocale(LC_ALL, "rus");
	_matrix a(3, 3);

	try {
		_matrix obr = a.inversion();
		cout << obr;
		_matrix E = obr*a;
		cout << E;
	}
	catch (const char* err) {
		cout << err << endl;
	}

	
}
