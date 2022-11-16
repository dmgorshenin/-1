#pragma once
#include <iostream>
#include <string>
#include <random>
#include <ctime>
using namespace std;

class _matrix {
private:
	double** data;
	int row, column;

	static double determenant_(const _matrix& matrix, int N) {
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
			double determ = 0;

			for (int k = 0; k < N; k++) {

				double** temp = new double* [N - 1];
				for (int i = 0; i < N - 1; i++) {
					temp[i] = new double[N - 1];
				}

				for (int i = 1; i < N; i++) {
					for (int j = 0; j < N; j++) {

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
				determ += pow(-1, k + 2) * matrix.data[0][k] * determenant_(_matrix(temp, N - 1, N - 1), N - 1);

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
		srand(time(0));
		row = rand() % 3 + 2;
		column = row;
		data = new double* [row];
		for (size_t i = 0; i < row; ++i)
		{
			data[i] = new double[column];
		}
		for (size_t i = 0; i < row; i++)
		{
			for (size_t j = 0; j < column; j++)
			{
				data[i][j] = (rand() % 300) / 10.0;
			}
		}
	}

	_matrix(int _rows, int _columns) {
		if (_rows < 1 or _columns < 1) throw "Invalid matrix size";

		row = _rows;
		column = _columns;

		data = new double* [row];
		for (size_t i = 0; i < row; ++i)
		{
			data[i] = new double[column];
		}

		cout << "Enter values" << endl;
		for (size_t i = 0; i < row; i++)
		{
			for (size_t j = 0; j < column; j++)
			{
				cout << "[" << i  << "][" << j  << "]: ";
				double temp_value;
				cin >> temp_value;
				data[i][j] = temp_value;
			}
		}
	}

	_matrix(const _matrix& matrix) {
		data = new double* [matrix.row];
		for (size_t i = 0; i < matrix.row; ++i)
		{
			data[i] = new double[matrix.column];
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

	_matrix(double** matrix, int _row,int _column) {
		if (_row < 1 or _column < 1) throw "Invalid matrix size";

		row = _row;
		column = _column;

		data = new double* [row];
		for (size_t i = 0; i < row; ++i)
		{
			data[i] = new double[column];
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

	double operator()(int i, int j) const {
		if ((i<0 or i>row) and (j<0 or j>column)) throw "Invalid index";
		return data[i][j];
	}

	double& operator()(int i, int j) {
		if ((i<0 or i>row) and (j<0 or j>column)) throw "Invalid index";
		return data[i][j];
	}

	friend ostream& operator<<(ostream& os, const _matrix& rhs)
	{
		for (int i = 0; i < rhs.row; ++i)
		{
			for (int j = 0; j < rhs.column; ++j)
			{
				cout.width(10);
				os <<left<< rhs.data[i][j] << '\t';
			}
			os << endl;
		}
		return os;
	}

	bool operator==(const _matrix& matrix) {
		if (row != matrix.row or column != matrix.column) {
			return false;
		}
		else {
			for (size_t i = 0; i < row; i++)
			{
				for (size_t j = 0; j < column; j++)
				{
					if (fabs(data[i][j] - matrix.data[i][j]) > 0.000001) {
						return false;
					}
				}
			}
			return true;
		}
	}
	
	bool operator!=(const _matrix& matrix) {
		return !(*this == matrix);
	}

	_matrix& operator+=(const _matrix& matrix) {
		if (row != matrix.row or column != matrix.column) throw "Dimensions do not match!";
		double** temp;

		temp = new double* [matrix.row];
		for (size_t i = 0; i < matrix.row; ++i)
		{
			temp[i] = new double[matrix.column];
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

	_matrix operator+(const _matrix& matrix) const {
		_matrix temp(*this);
		temp += matrix;
		return temp;
	}

	_matrix& operator-=(const _matrix& matrix) {
		if (row != matrix.row or column != matrix.column) throw "Dimensions do not match!";

		double** temp;

		temp = new double* [matrix.row];
		for (size_t i = 0; i < matrix.row; ++i)
		{
			temp[i] = new double[matrix.column];
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

	_matrix operator-(const _matrix& matrix) const {
		_matrix temp(*this);
		temp -= matrix;
		return temp;
	}

	_matrix& operator*=(const _matrix& matrix) {
		if (column != matrix.row) throw "Dimensions do not match!";
		
		double** temp;

		temp = new double* [row];
		for (size_t i = 0; i < row; ++i)
		{
			temp[i] = new double[matrix.column];
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

	_matrix operator*(const _matrix& matrix) const {
		_matrix temp(*this);
		temp *= matrix;
		return temp;
	}

	_matrix& operator*=(double value) {
		for (size_t i = 0; i < row; i++)
		{
			for (size_t j = 0; j < column; j++)
			{
				data[i][j] *= value;
			}
		}
		return *this;
	}
	
	_matrix operator*(double value) const {
		_matrix temp(*this);
		temp *= value;
		return temp;
	}

	friend _matrix operator*(double value, const _matrix& matrix) {
		_matrix temp(matrix);
		temp *= value;
		return temp;
	}

	_matrix& operator/=(double value) {
		if (value == 0) throw "Division by zero";
		for (size_t i = 0; i < row; i++)
		{
			for (size_t j = 0; j < column; j++)
			{
				data[i][j] /= value;
			}
		}
		return *this;
	}

	_matrix operator/(double value) const {
		_matrix temp(*this);
		temp /= value;
		return temp;
	}

	double matrix_trace() const {
		double temp=0;
		if (row != column) throw "The matrix is not square";
		else {
			for (size_t i = 0; i < row; i++)
			{
				temp += data[i][i];
			}
		}
		return temp;
	}

	_matrix inversion() {
		if (row != column) { throw "The matrix is not square"; }

		if (determenant() == 0) { throw "The determinant of the matrix is 0"; }

		double temp;								
		int N = row;								//размерность
		_matrix inversion_matrix(*this);	

		double** E = new double* [N];				//единичная матрица
		for (int i = 0; i < N; i++) {
			E[i] = new double[N];
		}

		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++)
			{
				E[i][j] = 0.0;

				if (i == j)
					E[i][j] = 1.0;
			}
		}

		for (int k = 0; k < N; k++)
		{
			temp = inversion_matrix.data[k][k];

			for (int j = 0; j < N; j++)
			{
				inversion_matrix.data[k][j] /= temp;
				E[k][j] /= temp;
			}

			for (int i = k + 1; i < N; i++)
			{
				temp = inversion_matrix.data[i][k];

				for (int j = 0; j < N; j++)
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

				for (int j = 0; j < N; j++)
				{
					inversion_matrix.data[i][j] -= inversion_matrix.data[k][j] * temp;
					E[i][j] -= E[k][j] * temp;
				}
				
			}
		}

		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
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

	double determenant() const {
		return determenant_(*this, row);
	}
	
	/*friend double determenant(const _matrix& matrix, int N) {
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
			double determ = 0;

			for (int k = 0; k < N; k++) {

				double** temp = new double* [N - 1];
				for (int i = 0; i < N - 1; i++) {
					temp[i] = new double[N - 1];
				}

				for (int i = 1; i < N; i++) {
					for (int j = 0; j < N; j++) {

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
				determ += pow(-1, k + 2) * matrix.data[0][k] * determenant(_matrix(temp, N - 1, N - 1), N - 1);

				for (size_t i = 0; i < static_cast<unsigned long long>(N) - 1; i++)
				{
					delete[] temp[i];
				}
				delete[] temp;
			}
			return determ;
		}
	}*/

};