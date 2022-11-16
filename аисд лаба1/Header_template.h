#include <iostream>
#include <string>
#include <complex>
#include <math.h>
#include <iomanip>
using namespace std;

template<typename T>
class _matrix {
private:
	T** data;
	int row, column;
	double Eps=0.01;

	static T determenant_(const _matrix<T>& matrix, int N) {
		if (matrix.column != matrix.row) {
			return NULL;
		}
		else if (N == 1) {
			return matrix.data[0][0];
		}
		else if (N == 2) {
			return matrix.data[0][0] * matrix.data[1][1] - matrix.data[0][1] * matrix.data[1][0];
		}
		else {
			T determ = 0;

			for (size_t k = 0; k < N; k++) {

				T** temp = new T* [N - 1];
				for (size_t i = 0; i < N - 1; i++) {
					temp[i] = new T[N - 1];
				}

				for (size_t i = 1; i < N; i++) {
					for (size_t j = 0; j < N; j++) {

						if (j == k) {
							continue;
						}
						else if (j < k) {
							temp[i - 1][j] = matrix.data[i][j];
						}
						else {
							temp[i - 1][j - 1] = matrix.data[i][j];
						}
					}
				}
				determ += pow(-1, k + 2) * matrix.data[0][k] * determenant_(_matrix<T>(temp, N - 1, N - 1), N - 1);

				for (size_t i = 0; i < static_cast<unsigned long long>(N) - 1; i++)
				{
					delete[] temp[i];
				}
				delete[] temp;
			}
			return determ;
		}
	}
public:
	_matrix() {
		row = 2;
		column = row;
		data = new T* [row];
		Eps = 0;
		for (size_t i = 0; i < row; ++i)
		{
			data[i] = new T[column];
		}

		for (size_t i = 0; i < row; ++i)
		{
			for (size_t j = 0; j < column; j++)
			{
				data[i][j] = static_cast<T>(0);
			}
		}
	}

	_matrix(int _rows, int _columns) {
		if (_rows < 1 or _columns < 1) throw "Invalid matrix size";

		row = _rows;
		column = _columns;
		Eps = 0;

		data = new T* [row];
		for (size_t i = 0; i < row; ++i)
		{
			data[i] = new T[column];
		}

		cout << "Enter values" << endl << endl;
		for (size_t i = 0; i < row; i++)
		{
			for (size_t j = 0; j < column; j++)
			{
				cout << "[" << i << "][" << j << "]: ";
				T temp_value;
				cin >> temp_value;
				data[i][j] = temp_value;
			}
		}
	}

	_matrix(const _matrix<T>& matrix) {
		data = new T* [matrix.row];
		for (size_t i = 0; i < matrix.row; ++i)
		{
			data[i] = new T [matrix.column];
		}

		row = matrix.row;
		column = matrix.column;
		Eps = 0;

		for (size_t i = 0; i < row; i++)
		{
			for (size_t j = 0; j < column; j++)
			{
				data[i][j] = matrix.data[i][j];
			}
		}
	}

	_matrix(T** matrix, int _row, int _column) {
		if (_row < 1 or _column < 1) throw "Invalid matrix size";

		row = _row;
		column = _column;
		Eps = 0;

		data = new T* [row];
		for (size_t i = 0; i < row; ++i)
		{
			data[i] = new T [column];
		}

		for (size_t i = 0; i < row; i++)
		{
			for (size_t j = 0; j < column; j++)
			{
				data[i][j] = matrix[i][j];
			}
		}
	}

	~_matrix() {
		for (size_t i = 0; i < row; i++)
		{
			delete[] data[i];
		}
		delete[] data;
	}

	int get_row() const {
		return row;
	}

	int get_column() const {
		return column;
	}

	const T& operator()(int i, int j) const {
		if ((i<0 or i>row) and (j<0 or j>column)) throw "Invalid index";
		return data[i][j];
	}

	T& operator()(int i, int j) {
		if ((i<0 or i>row) and (j<0 or j>column)) throw "Invalid index";
		return data[i][j];
	}

	friend ostream& operator<<(ostream& os, const _matrix<T>& rhs)
	{
		for (int i = 0; i < rhs.row; ++i)
		{
			for (int j = 0; j < rhs.column; ++j)
			{
				cout.width(10);
				os << left << rhs.data[i][j] << '\t';
			}
			os << endl;
		}
		return os;
	}

	bool operator==(const _matrix<T>& matrix) {
		if (row != matrix.row or column != matrix.column) {
			return false;
		}
		else {
			cout << "Enter the accuracy of the comparison: ";
			cin >> Eps;
			for (size_t i = 0; i < row; i++)
			{
				for (size_t j = 0; j < column; j++)
				{
					if (fabs(data[i][j] - matrix.data[i][j]) > Eps) {
						return false;
					}
				}
			}
			return true;
		}
	}

	bool operator!=(const _matrix<T>& matrix) {
		return !(*this == matrix);
	}

	_matrix<T>& operator+=(const _matrix<T>& matrix) {
		if (row != matrix.row or column != matrix.column) throw "Dimensions do not match!";
		T** temp = new T* [matrix.row];

		for (size_t i = 0; i < matrix.row; ++i)
		{
			temp[i] = new T [matrix.column];
		}

		for (size_t i = 0; i < row; ++i)
		{
			for (size_t j = 0; j < column; ++j)
			{
				temp[i][j] = data[i][j] + matrix.data[i][j];
			}
		}

		for (size_t i = 0; i < row; i++)
		{
			delete[] data[i];
		}
		delete[] data;

		data = temp;
		return *this;
	}

	_matrix<T> operator+(const _matrix<T>& matrix) const {
		_matrix temp(*this);
		temp += matrix;
		return temp;
	}

	_matrix<T>& operator-=(const _matrix<T>& matrix) {
		if (row != matrix.row or column != matrix.column) throw "Dimensions do not match!";

		T** temp = new T* [matrix.row];
		for (size_t i = 0; i < matrix.row; ++i)
		{
			temp[i] = new T [matrix.column];
		}

		for (size_t i = 0; i < row; ++i)
		{
			for (size_t j = 0; j < column; ++j)
			{
				temp[i][j] = data[i][j] - matrix.data[i][j];
			}
		}

		for (size_t i = 0; i < row; i++)
		{
			delete[] data[i];
		}
		delete[] data;

		data = temp;
		return *this;
	}

	_matrix<T> operator-(const _matrix<T>& matrix) const {
		_matrix temp(*this);
		temp -= matrix;
		return temp;
	}

	_matrix<T>& operator*=(const _matrix<T>& matrix) {
		if (column != matrix.row) throw "Dimensions do not match!";

		T** temp = new T* [row];
		for (size_t i = 0; i < row; ++i)
		{
			temp[i] = new T [matrix.column];
		}

		for (size_t rows = 0; rows < row; rows++)
		{
			for (size_t col = 0; col < matrix.column; col++)
			{
				temp[rows][col] = 0;
				for (size_t inner = 0; inner < column; inner++)
				{
					temp[rows][col] += data[rows][inner] * matrix.data[inner][col];
				}
			}
		}

		column = matrix.column;

		for (size_t i = 0; i < row; i++)
		{
			delete[] data[i];
		}
		delete[] data;

		data = temp;
		return *this;
	}

	_matrix<T> operator*(const _matrix<T>& matrix) const {
		_matrix temp(*this);
		temp *= matrix;
		return temp;
	}

	_matrix<T>& operator*=(T value) {        //??????
		for (size_t i = 0; i < row; i++)
		{
			for (size_t j = 0; j < column; j++)
			{
				data[i][j] = data[i][j]*value;
			}
		}
		return *this;
	}

	_matrix<T> operator*(T value) const {
		_matrix temp(*this);
		temp *= value;
		return temp;
	}

	friend _matrix<T> operator*(T value, const _matrix<T>& matrix) {
		_matrix temp(matrix);
		temp *= value;
		return temp;
	}

	_matrix<T>& operator/=(T value) {
		if (value == 0) throw "Division by zero";
		for (size_t i = 0; i < row; i++)
		{
			for (size_t j = 0; j < column; j++)
			{
				data[i][j] =static_cast<T>(data[i][j]/value);
			}
		}
		return *this;
	}

	_matrix<T> operator/(T value) const {
		_matrix temp(*this);
		temp /= value;
		return temp;
	}

	T matrix_trace() const {
		T temp = 0;
		if (row != column) throw "The matrix is not square";
		else {
			for (size_t i = 0; i < row; i++)
			{
				temp += data[i][i];
			}
		}
		return temp;
	}

	_matrix<T> inversion() {
		if (row != column) { throw "The matrix is not square"; }

		if (determenant_(*this, column) == 0) { throw "The determinant of the matrix is 0"; }

		T temp;
		int N = row;								//размерность
		_matrix<T> inversion_matrix(*this);

		T** E = new T* [N];							//единичная матрица
		for (size_t i = 0; i < N; i++) {
			E[i] = new T [N];
		}

		for (size_t i = 0; i < N; i++) {
			for (size_t j = 0; j < N; j++)
			{
				E[i][j] = 0;

				if (i == j)
					E[i][j] = 1;
			}
		}

		for (size_t k = 0; k < N; k++)
		{
			temp = inversion_matrix.data[k][k];

			for (size_t j = 0; j < N; j++)
			{
				inversion_matrix.data[k][j] = inversion_matrix.data[k][j]/temp;
				E[k][j] = E[k][j]/temp;
			}

			for (size_t i = k + 1; i < N; i++)
			{
				temp = inversion_matrix.data[i][k];

				for (size_t j = 0; j < N; j++)
				{
					inversion_matrix.data[i][j] -= inversion_matrix.data[k][j] * temp;
					E[i][j] -= E[k][j] * temp;
				}
			}

		}

		for (int k = N - 1; k > 0; k--)
		{
			for (int i = k - 1; i >= 0; i--)
			{
				temp = inversion_matrix.data[i][k];

				for (size_t j = 0; j < N; j++)
				{
					inversion_matrix.data[i][j] -= inversion_matrix.data[k][j] * temp;
					E[i][j] -= E[k][j] * temp;
				}

			}
		}

		for (size_t i = 0; i < N; i++) {
			for (size_t j = 0; j < N; j++) {
				inversion_matrix.data[i][j] = E[i][j];
			}
		}

		for (size_t i = 0; i < N; i++)
		{
			delete[] E[i];
		}
		delete[] E;

		return inversion_matrix;
	}

	T determenant() const {
		return determenant_(*this, row);
	}

};

template<typename T>
class _matrix<complex<T>> {
private:
	complex<T>** data;
	int row, column;
	double Eps=0.01;

	static complex<T> determenant_(const _matrix<complex<T>>& matrix, int N) {
		if (matrix.column != matrix.row) {
			throw "The matrix is not square";
		}
		else if (N == 1) {
			return matrix.data[0][0];
		}
		else if (N == 2) {
			return matrix.data[0][0] * matrix.data[1][1] - matrix.data[0][1] * matrix.data[1][0];
		}
		else {
			complex<T> determ(0,0);

			for (size_t k = 0; k < N; k++) {

				complex<T>** temp = new complex<T> * [N - 1];
				for (size_t i = 0; i < N - 1; i++) {
					temp[i] = new complex<T>[N - 1];
				}

				for (size_t i = 1; i < N; i++) {
					for (size_t j = 0; j < N; j++) {

						if (j == k) {
							continue;
						}
						else if (j < k) {
							temp[i - 1][j] = matrix.data[i][j];
						}
						else {
							temp[i - 1][j - 1] = matrix.data[i][j];
						}
					}
				}
				determ += pow(-1, k + 2) * matrix.data[0][k] * determenant_(_matrix<complex<T>>(temp, N - 1, N - 1), N - 1);

				for (size_t i = 0; i < static_cast<unsigned long long>(N) - 1; i++)
				{
					delete[] temp[i];
				}
				delete[] temp;
			}
			return determ;
		}
	}
public:
	_matrix() {
		row = 2;
		column = row;
		data = new complex<T> * [row];
		for (size_t i = 0; i < row; ++i)
		{
			data[i] = new complex<T>[column];
		}

		for (size_t i = 0; i < row; ++i)
		{
			for (size_t j = 0; j < column; j++)
			{
				data[i][j] = 0;
			}
		}
	}

	_matrix(int _rows, int _columns) {
		if (_rows < 1 or _columns < 1) throw "Invalid matrix size";

		row = _rows;
		column = _columns;

		data = new complex<T> * [row];
		for (size_t i = 0; i < row; ++i)
		{
			data[i] = new complex<T>[column];
		}

		cout << "Enter values" << endl << endl;
		for (size_t i = 0; i < row; i++)
		{
			for (size_t j = 0; j < column; j++)
			{
				cout << "[" << i << "][" << j << "]: ";
				T temp_real,temp_imag;
				cout << "Real:";
				cin >> temp_real;
				cout << "Imaginary:";
				cin >> temp_imag;
				data[i][j] = complex<T>(temp_real,temp_imag);
				cout << endl;	
			}
			
		}
	}

	_matrix(const _matrix<complex<T>>& matrix) {
		data = new complex<T> * [matrix.row];
		for (size_t i = 0; i < matrix.row; ++i)
		{
			data[i] = new complex<T>[matrix.column];
		}

		row = matrix.row;
		column = matrix.column;

		for (size_t i = 0; i < row; i++)
		{
			for (size_t j = 0; j < column; j++)
			{
				data[i][j] = matrix.data[i][j];
			}
		}
	}

	_matrix(complex<T>** matrix, int _row, int _column) {
		if (_row < 1 or _column < 1) throw "Invalid matrix size";

		row = _row;
		column = _column;

		data = new complex<T> * [row];
		for (size_t i = 0; i < row; ++i)
		{
			data[i] = new complex<T>[column];
		}

		for (size_t i = 0; i < row; i++)
		{
			for (size_t j = 0; j < column; j++)
			{
				data[i][j] = matrix[i][j];
			}
		}
	}

	~_matrix() {
		for (size_t i = 0; i < row; i++)
		{
			delete[] data[i];
		}
		delete[] data;
	}

	int get_row() const {
		return row;
	}

	int get_column() const {
		return column;
	}

	const complex<T>& operator()(int i, int j) const {
		if ((i<0 or i>row) and (j<0 or j>column)) throw "Invalid index";
		return data[i][j];
	}

	complex<T>& operator()(int i, int j) {
		if ((i<0 or i>row) and (j<0 or j>column)) throw "Invalid index";
		return data[i][j];
	}

	friend ostream& operator<<(ostream& os, const _matrix<complex<T>>& rhs)
	{
		for (int i = 0; i < rhs.row; ++i)
		{
			for (int j = 0; j < rhs.column; ++j)
			{
				cout.width(15);
				os << left << setprecision(4) << rhs.data[i][j] << '\t';
			}
			os << endl;
		}
		return os;
	}

	bool operator==(const _matrix<complex<T>>& matrix) {
		if (row != matrix.row or column != matrix.column) {
			return false;
		}
		else {
			cout << "Enter the accuracy of the comparison: ";
			cin >> Eps;
			for (size_t i = 0; i < row; i++)
			{
				for (size_t j = 0; j < column; j++)
				{
					if (fabs(data[i][j].real() - matrix.data[i][j].real()) > Eps or fabs(data[i][j].imag() - matrix.data[i][j].imag()) > Eps) {
						return false;
					}
				}
			}
			return true;
		}
	}

	bool operator!=(const _matrix<complex<T>>& matrix) {
		return !(*this == matrix);
	}

	_matrix<complex<T>>& operator+=(const _matrix<complex<T>>& matrix) {
		if (row != matrix.row or column != matrix.column) throw "Dimensions do not match!";
		complex<T>** temp = new complex<T> * [matrix.row];

		for (size_t i = 0; i < matrix.row; ++i)
		{
			temp[i] = new complex<T>[matrix.column];
		}

		for (size_t i = 0; i < row; ++i)
		{
			for (size_t j = 0; j < column; ++j)
			{
				temp[i][j] = data[i][j] + matrix.data[i][j];
			}
		}

		for (size_t i = 0; i < row; i++)
		{
			delete[] data[i];
		}
		delete[] data;

		data = temp;
		return *this;
	}

	_matrix<complex<T>> operator+(const _matrix<complex<T>>& matrix) const {
		_matrix temp(*this);
		temp += matrix;
		return temp;
	}

	_matrix<complex<T>>& operator-=(const _matrix<complex<T>>& matrix) {
		if (row != matrix.row or column != matrix.column) throw "Dimensions do not match!";

		complex<T>** temp = new complex<T> * [matrix.row];
		for (size_t i = 0; i < matrix.row; ++i)
		{
			temp[i] = new complex<T>[matrix.column];
		}

		for (size_t i = 0; i < row; ++i)
		{
			for (size_t j = 0; j < column; ++j)
			{
				temp[i][j] = data[i][j] - matrix.data[i][j];
			}
		}

		for (size_t i = 0; i < row; i++)
		{
			delete[] data[i];
		}
		delete[] data;

		data = temp;
		return *this;
	}

	_matrix<complex<T>> operator-(const _matrix<complex<T>>& matrix) const {
		_matrix temp(*this);
		temp -= matrix;
		return temp;
	}

	_matrix<complex<T>>& operator*=(const _matrix<complex<T>>& matrix) {
		if (column != matrix.row) throw "The sizes of the matrices do not match! ";

		complex<T>** temp = new complex<T> * [row];
		for (size_t i = 0; i < row; ++i)
		{
			temp[i] = new complex<T>[matrix.column];
		}

		for (size_t rows = 0; rows < row; rows++)
		{
			for (size_t col = 0; col < matrix.column; col++)
			{
				temp[rows][col] = 0;
				for (size_t inner = 0; inner < column; inner++)
				{
					temp[rows][col] += data[rows][inner] * matrix.data[inner][col];
				}
			}
		}

		column = matrix.column;

		for (size_t i = 0; i < row; i++)
		{
			delete[] data[i];
		}
		delete[] data;

		data = temp;
		return *this;
	}

	_matrix<complex<T>> operator*(const _matrix<complex<T>>& matrix) const {
		_matrix temp(*this);
		temp *= matrix;
		return temp;
	}

	_matrix<complex<T>>& operator*=(double value) {        //??????
		for (size_t i = 0; i < row; i++)
		{
			for (size_t j = 0; j < column; j++)
			{
				data[i][j] = data[i][j] * value;
			}
		}
		return *this;
	}

	_matrix<complex<T>> operator*(double value) const {
		_matrix temp(*this);
		temp *= value;
		return temp;
	}

	friend _matrix<complex<T>> operator*(double value, const _matrix<complex<T>>& matrix) {
		_matrix temp(matrix);
		temp *= value;
		return temp;
	}

	_matrix<complex<T>>& operator/=(double value) {
		if (value == 0) throw "Division by zero";
		for (size_t i = 0; i < row; i++)
		{
			for (size_t j = 0; j < column; j++)
			{
				data[i][j] = data[i][j] / value;
			}
		}
		return *this;
	}

	_matrix<complex<T>> operator/(double value) const {
		_matrix temp(*this);
		temp /= value;
		return temp;
	}

	complex<T> matrix_trace() const {
		complex<T> temp(0,0);
		if (row != column) throw "The matrix is not square";
		else {
			for (size_t i = 0; i < row; i++)
			{
				temp += data[i][i];
			}
		}
		return temp;
	}

	_matrix<complex<T>> inversion() {
		if (row != column) { throw "The matrix is not square"; }

		if (determenant_(*this, column) == complex<T>(0,0)) { throw "The determinant of the matrix is 0"; }

		complex<T> temp;
		int N = row;								//размерность
		_matrix<complex<T>> inversion_matrix(*this);

		complex<T>** E = new complex<T> * [N];							//единичная матрица
		for (size_t i = 0; i < N; i++) {
			E[i] = new complex<T>[N];
		}

		for (size_t i = 0; i < N; i++) {
			for (size_t j = 0; j < N; j++)
			{
				E[i][j] = 0;

				if (i == j)
					E[i][j] = 1;
			}
		}

		for (size_t k = 0; k < N; k++)
		{
			temp = inversion_matrix.data[k][k];

			for (size_t j = 0; j < N; j++)
			{
				inversion_matrix.data[k][j] = inversion_matrix.data[k][j] / temp;
				E[k][j] = E[k][j] / temp;
			}

			for (size_t i = k + 1; i < N; i++)
			{
				temp = inversion_matrix.data[i][k];

				for (size_t j = 0; j < N; j++)
				{
					inversion_matrix.data[i][j] -= inversion_matrix.data[k][j] * temp;
					E[i][j] -= E[k][j] * temp;
				}
			}

		}

		for (int k = N - 1; k > 0; k--)
		{
			for (int i = k - 1; i >= 0; i--)
			{
				temp = inversion_matrix.data[i][k];

				for (size_t j = 0; j < N; j++)
				{
					inversion_matrix.data[i][j] -= inversion_matrix.data[k][j] * temp;
					E[i][j] -= E[k][j] * temp;
				}

			}
		}

		for (size_t i = 0; i < N; i++) {
			for (size_t j = 0; j < N; j++) {
				inversion_matrix.data[i][j] = E[i][j];
			}
		}

		for (size_t i = 0; i < N; i++)
		{
			delete[] E[i];
		}
		delete[] E;

		return inversion_matrix;
	}

	complex<T> determenant() const {
		return determenant_(*this, row);
	}

};

template<>
bool _matrix<int>::operator==(const _matrix<int>& matrix) {
	if (row != matrix.row or column != matrix.column) {
		return false;
	}
	else {
		for (size_t i = 0; i < row; i++)
		{
			for (size_t j = 0; j < column; j++)
			{
				if (data[i][j] != matrix.data[i][j]) {
					return false;
				}
			}
		}
		return true;
	}
}

_matrix<int> _matrix<int>::inversion() {
	if (row != column) { throw "The matrix is not square"; }

	if (determenant_(*this, column) == 0) { throw "The determinant of the matrix is 0"; }

	int temp;
	int N = row;								//размерность
	_matrix<int> inversion_matrix(*this);

	int** E = new int * [N];							//единичная матрица
	for (size_t i = 0; i < N; i++) {
		E[i] = new int[N];
	}

	for (size_t i = 0; i < N; i++) {
		for (size_t j = 0; j < N; j++)
		{
			E[i][j] = 0;

			if (i == j)
				E[i][j] = 1;
		}
	}

	for (size_t k = 0; k < N; k++)
	{
		temp = inversion_matrix.data[k][k];

		for (size_t j = 0; j < N; j++)
		{
			inversion_matrix.data[k][j] = static_cast<int>(inversion_matrix.data[k][j] / temp);
			E[k][j] = static_cast<int>(E[k][j] / temp);
		}

		for (size_t i = k + 1; i < N; i++)
		{
			temp = inversion_matrix.data[i][k];

			for (size_t j = 0; j < N; j++)
			{
				inversion_matrix.data[i][j] -= static_cast<int>(inversion_matrix.data[k][j] * temp);
				E[i][j] -= static_cast<int>(E[k][j] * temp);
			}
		}

	}

	for (int k = N - 1; k > 0; k--)
	{
		for (int i = k - 1; i >= 0; i--)
		{
			temp = inversion_matrix.data[i][k];

			for (size_t j = 0; j < N; j++)
			{
				inversion_matrix.data[i][j] -= static_cast<int>(inversion_matrix.data[k][j] * temp);
				E[i][j] -= static_cast<int>(E[k][j] * temp);
			}

		}
	}

	for (size_t i = 0; i < N; i++) {
		for (size_t j = 0; j < N; j++) {
			inversion_matrix.data[i][j] = E[i][j];
		}
	}

	for (size_t i = 0; i < N; i++)
	{
		delete[] E[i];
	}
	delete[] E;

	return inversion_matrix;
}