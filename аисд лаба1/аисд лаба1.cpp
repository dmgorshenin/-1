#include "Header_vector.h"
using namespace std;

int main()
{
	//_matrix<int> a;
	//_matrix<int> b(2, 3);
	//_matrix<int> c(3, 2);
	//cout << b << endl << c << endl << a << endl;

	//try {
	//	int det = a.determenant();
	//	cout << det << endl;
	//}
	//catch (const char* err) {
	//	cout << err << endl;
	//}

	//try {
	//	_matrix<int> d = b + c;
	//	cout << d << endl;
	//}
	//catch (const char* err) {
	//	cout << err << endl;
	//}

	//try {
	//	_matrix<int> e = b * c; cout << e << endl;
	//}
	//catch (const char* err) {
	//	cout << err << endl;
	//}

	//try {
	//	_matrix<int> f = b - 3 * b; cout << f << endl;
	//}
	//catch (const char* err) {
	//	cout << err << endl;
	//}
	//_matrix<int> g = b * 3; cout << g << endl;
	//_matrix<int> t = 3 * b; cout << t << endl;
	//_matrix<int> x = c / 7; cout << x << endl;

	//if (g == t)
	//	cout << "G==T" << endl;
	//else
	//	cout << "G!=T" << endl;

	//int trace = a.matrix_trace(); cout << trace << endl;

	//cout << b(0, 0) << endl;
	//b(0, 0) = 7824;
	//cout << b(0, 0) << endl;

	//try {
	//	_matrix<int> A(3, 3);
	//	_matrix<int> _b(3, 1);
	//	_matrix<int> A_inv = A.inversion();
	//	cout << A_inv << endl;
	//	_matrix<int> _x = A_inv * _b;
	//	cout << _x;
	//}
	//catch (const char* err) {
	//	cout << err << endl;
	//}




	_matrix<complex<double>> test(2, 2);
	for (const auto i : test) {
		for (const auto j : i) {
			cout << j;
		}
		cout << endl;
	}
	cout << test;





	//_matrix<complex<double>> a;
	//_matrix<complex<double>> b(3, 2);
	//_matrix<complex<double>> c(2, 3);
	//cout << b << endl << c << endl << a << endl;

	//try {
	//	complex<double> det = a.determenant();
	//	cout << det<<endl;
	//}
	//catch (const char* err) {
	//	cout << err << endl;
	//}

	//try {
	//	_matrix<complex<double>> d = b + c;
	//	cout << d << endl;
	//}
	//catch (const char* err) {
	//	cout << err << endl;
	//}

	//try {
	//	_matrix<complex<double>> e = b * c; cout << e << endl;
	//}
	//catch (const char* err) {
	//	cout << err << endl;
	//}
	//
	//try {
	//	_matrix<complex<double>> f = b - 3*b; cout << f << endl;
	//}
	//catch (const char* err) {
	//	cout << err << endl;
	//}
	//try {
	//	_matrix<complex<double>> g = b * complex<double>(3.5, 6.7); cout << g << endl;
	//	_matrix<complex<double>> t = 3.5 * b; cout << t << endl;
	//	_matrix<complex<double>> x = c / 7; cout << x << endl;
	//}
	//catch (const char* err) {
	//	cout << err << endl;
	//}

	///*if (g == t)
	//	cout << "G==T" << endl;
	//else
	//	cout << "G!=T" << endl;*/

	//complex<double> trace =(b*c).matrix_trace(); cout << trace << endl;

	//cout << b(0, 0)<<endl;
	//b(0, 0) = complex<double>(7824,12);
	//cout << b(0, 0)<<endl;

	//try {
	//	_matrix<complex<double>> A(3, 3);
	//	_matrix<complex<double>> _b(3, 1);
	//	_matrix<complex<double>> A_inv = A.inversion();
	//	cout << A_inv<<endl;
	//	_matrix<complex<double>> _x = A_inv * _b;
	//	cout << _x;
	//}
	//catch (const char* err) {
	//	cout << err << endl;
	//}







	_matrix<float> a;
	_matrix<float> b(3, 2);
	_matrix<float> c(2, 3);
	cout << b << endl << c << endl << a << endl;
	
	try {
		float det = b.determenant();
		cout << det << endl;
	}
	catch (const char* err) {
		cout << err << endl;
	}
	
	try {
		_matrix<float> d = b + c;
		cout << d << endl;
	}
	catch (const char* err) {
		cout << err << endl;
	}
	
	try {
		_matrix<float> e = b * c; cout << e << endl;
	}
	catch (const char* err) {
		cout << err << endl;
	}
	
	try {
		_matrix<float> f = b - 3 * b; cout << f << endl;
	}
	catch (const char* err) {
		cout << err << endl;
	}
	_matrix<float> g = b * 3.5; cout << g << endl;
	_matrix<float> t = 3.5 * b; cout << t << endl;
	_matrix<float> x = c / 7; cout << x << endl;
	
	if (g == t)
	cout << "G==T" << endl;
	else
	cout << "G!=T" << endl;
	
	float trace = a.matrix_trace(); cout << trace << endl;
	
	cout << b(0, 0) << endl;
	b(0, 0) = 7824;
	cout << b(0, 0) << endl;
	
	try {
		_matrix<float> A(3, 3);
		_matrix<float> _b(3, 1);
		_matrix<float> A_inv = A.inversion();
		cout << A_inv << endl;
		_matrix<float> _x = A_inv * _b;
		cout << _x;
	}
	catch (const char* err) {
		cout << err << endl;
	}




	//_matrix<double> a;
	//_matrix<double> b(3, 2);
	//_matrix<double> c(2, 3);
	//cout << b << endl << c << endl << a << endl;
	//
	//try {
	//	double det = a.determenant();
	//	cout << det << endl;
	//}
	//catch (const char* err) {
	//	cout << err << endl;
	//}
	//
	//try {
	//	_matrix<double> d = b + c;
	//	cout << d << endl;
	//}
	//catch (const char* err) {
	//	cout << err << endl;
	//}
	//
	//try {
	//	_matrix<double> e = b * c; cout << e << endl;
	//}
	//catch (const char* err) {
	//	cout << err << endl;
	//}
	//
	//try {
	//	_matrix<double> f = b - 3 * b; cout << f << endl;
	//}
	//catch (const char* err) {
	//	cout << err << endl;
	//}
	//_matrix<double> g = b * 3.5; cout << g << endl;
	//_matrix<double> t = 3.5 * b; cout << t << endl;
	//_matrix<double> x = c / 7; cout << x << endl;
	//
	//if (g == t)
	//cout << "G==T" << endl;
	//else
	//cout << "G!=T" << endl;
	//
	//double trace = a.matrix_trace(); cout << trace << endl;
	//
	//cout << b(0, 0) << endl;
	//b(0, 0) = 7824;
	//cout << b(0, 0) << endl;
	//
	//try {
	//	_matrix<double> A(3, 3);
	//	_matrix<double> _b(3, 1);
	//	_matrix<double> A_inv = A.inversion();
	//	cout << A_inv << endl;
	//	_matrix<double> _x = A_inv * _b;
	//	cout << _x;
	//}
	//catch (const char* err) {
	//	cout << err << endl;
	//}
}