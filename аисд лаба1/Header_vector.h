#include <iostream>
#include <string>
#include <complex>
#include <math.h>
#include <algorithm>
#include <vector>
#include <iterator>
#include <iomanip>
using namespace std;

template<typename T>
class _matrix {
private:
	vector<vector<T>> data;
	int row, column;
	double Eps = 0.01;

	static T determenant_(const vector<vector<T>>& matrix, int N) {
		if (matrix.size() != matrix[0].size()) {
			return NULL;
		}
		else if (N == 1) {
			return matrix[0][0];
		}
		else if (N == 2) {
			return matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0];
		}
		else {
			T determ = 0;

			for (size_t k = 0; k < N; k++) {

				vector<vector<T>> temp(N - 1, vector<T>(N - 1));
	
				for (size_t i = 1; i < N; i++) {
					for (size_t j = 0; j < N; j++) {

						if (j == k) {
							continue;
						}
						else if (j < k) {
							temp[i - 1][j] = matrix[i][j];
						}
						else {
							temp[i - 1][j - 1] = matrix[i][j];
						}
					}
				}

				vector<vector<T>> new_temp(N - 1, vector<T>(N - 1));

				for (size_t i = 0; i < N-1; ++i)
				{
					for (size_t j = 0; j < N-1; ++j)
					{
						new_temp[i][j] = temp[i][j];
					}
				}
				determ += pow(-1, k + 2) * matrix[0][k] * determenant_(new_temp, N - 1);

			}
			return determ;
		}
	}
public:
	_matrix() {
		row = 2; column = row;
		data.resize(row);

		for (size_t i = 0; i < row; i++)
		{
			data[i].resize(column);
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
		if (_rows < 1 or _columns < 1) { throw "Invalid matrix size"; }

		row = _rows;
		column = _columns;

		data.resize(row);
		for (size_t i = 0; i < row; ++i)
		{
			data[i].resize(column);
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

	_matrix(const _matrix<T>& matrix) = default;

	~_matrix() = default;

	/*class vv_iterator : public iterator<bidirectional_iterator_tag, T> {		
		vv_iterator(_matrix<T>& _vv, size_t _idxOuter, size_t _idxInner): vv(&(_vv.data)), idxOuter(_idxOuter), idxInner(_idxInner) {}
		vector<vector<T>>* vv = nullptr;
		size_t idxOuter = 0;
		size_t idxInner = 0;
		friend class _matrix;
	public:
		
		static vv_iterator begin(_matrix<T>& vv) {
			return vv_iterator(vv, 0, 0);
		}
		static vv_iterator end(_matrix<T>& vv) {
			return vv_iterator(vv, vv.get_row(), 0);
		}
		vv_iterator() = default;
	
		vv_iterator& operator++()
		{
			
			if (idxInner + 1 < (*vv)[idxOuter].size())
			{
				
				++idxInner;
			}
			else
			{
				
				do
				{
					++idxOuter;
				} while (idxOuter < (*vv).size() && (*vv)[idxOuter].empty());
				
				idxInner = 0;
			}
			return *this;
		}
		
		vv_iterator& operator--()
		{
			
			if (idxInner > 0)
			{
				
				--idxInner;
			}
			else
			{
				
				do
				{
					--idxOuter;
				} while ((*vv)[idxOuter].empty());
				
				idxInner = (*vv)[idxOuter].size() - 1;
			}
			return *this;
		}
		
		vv_iterator operator++(int)
		{
			T retval = *this;
			++(*this);
			return retval;
		}
		
		vv_iterator operator--(int)
		{
			T retval = *this;
			--(*this);
			return retval;
		}
		bool operator==(const vv_iterator& other) const
		{
			return other.vv == vv && other.idxOuter == idxOuter && other.idxInner == idxInner;
		}
		bool operator!=(const vv_iterator& other) const
		{
			return !(*this == other);
		}
		const T& operator*() const
		{
			return *this;
		}
		T& operator*()
		{
			return (*vv)[idxOuter][idxInner];
		}
		const T& operator->() const
		{
			return *this;
		}
		T& operator->()
		{
			return *this;
		}
	};

	vv_iterator begin() {
		return vv_iterator(*this, 0, 0);
	}
	vv_iterator end() {
		return vv_iterator(*this, row, 0);
	}*/

	auto begin() {
		return data.begin();

	}

	auto end() {
		return data.end();
	}

	int get_row() const {
		if (data.size() != row) { throw "Dimensions of the matrix do not match"; }
		return data.size();
	}

	int get_column() const {
		if (data[0].size() != column) { throw "Dimensions of the matrix do not match"; }
		return data[0].size();
	}

	const T& operator()(int i, int j) const {
		if ((i<0 or i>row) and (j<0 or j>column)) { throw "Invalid index"; }
		return data[i][j];
	}

	T& operator()(int i, int j) {
		if ((i<0 or i>row) and (j<0 or j>column)) { throw "Invalid index"; }
		return data[i][j];
	}

	friend ostream& operator<<(ostream& os, const _matrix<T>& rhs)
	{
		for (const auto i : rhs.data) {
			for (const auto j : i) {
				cout.width(10);
				os << left << j<<'\t';
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
		if (row != matrix.row or column != matrix.column) { throw "Dimensions do not match!"; }
		vector<vector<T>> temp (row, vector<T>(column));

		for (size_t i = 0; i < row; ++i)
		{
			for (size_t j = 0; j < column; ++j)
			{
				temp[i][j] = data[i][j] + matrix.data[i][j];
			}
		}

		data = temp;
		return *this;
	}

	_matrix<T> operator+(const _matrix<T>& matrix) const {
		_matrix temp(*this);
		temp += matrix;
		return temp;
	}

	_matrix<T>& operator-=(const _matrix<T>& matrix) {
		if (row != matrix.row or column != matrix.column) { throw "Dimensions do not match!"; }
		vector<vector<T>> temp(row, vector<T>(column));

		for (size_t i = 0; i < row; ++i)
		{
			for (size_t j = 0; j < column; ++j)
			{
				temp[i][j] = data[i][j] - matrix.data[i][j];
			}
		}

		data = temp;
		return *this;
	}

	_matrix<T> operator-(const _matrix<T>& matrix) const {
		_matrix temp(*this);
		temp -= matrix;
		return temp;
	}

	_matrix<T>& operator*=(const _matrix<T>& matrix) {
		if (column != matrix.row) { throw "Dimensions do not match!"; }
		vector<vector<T>> temp(row, vector<T>(matrix.column));

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

		data = temp;
		return *this;
	}

	_matrix<T> operator*(const _matrix<T>& matrix) const {
		_matrix temp(*this);
		temp *= matrix;
		return temp;
	}

	_matrix<T>& operator*=(T value) {       
		for (size_t i = 0; i < row; i++)
		{
			for (size_t j = 0; j < column; j++)
			{
				data[i][j] = data[i][j] * value;
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
		if (value == 0) { throw "Division by zero"; }
		for (size_t i = 0; i < row; i++)
		{
			for (size_t j = 0; j < column; j++)
			{
				data[i][j] = static_cast<T>(data[i][j] / value);
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
		if (row != column) { throw "The matrix is not square"; }
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

		if (determenant_(data, column) == 0) { throw "The determinant of the matrix is 0"; }

		T temp;
		int N = row;								//размерность
		_matrix<T> inversion_matrix(*this);

		vector<vector<T>> E(N, vector<T>(N));						//единичная матрица
	
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

		return inversion_matrix;
	}

	T determenant() const {
		return determenant_(data, row);
	}

};

template<typename T>
class _matrix<complex<T>> {
private:
	vector<vector<complex<T>>> data;
	int row, column;
	double Eps = 0.01;

	static complex<T> determenant_(const vector<vector<complex<T>>>& matrix, int N) {
		if (matrix.size() != matrix[0].size()) {
			return NULL;
		}
		else if (N == 1) {
			return matrix[0][0];
		}
		else if (N == 2) {
			return matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0];
		}
		else {
			complex<T> determ(0, 0);

			for (size_t k = 0; k < N; k++) {

				vector<vector<complex<T>>> temp(N - 1, vector<complex<T>>(N - 1));

				for (size_t i = 1; i < N; i++) {
					for (size_t j = 0; j < N; j++) {

						if (j == k) {
							continue;
						}
						else if (j < k) {
							temp[i - 1][j] = matrix[i][j];
						}
						else {
							temp[i - 1][j - 1] = matrix[i][j];
						}
					}
				}
				vector<vector<complex<T>>> new_temp(N - 1, vector<complex<T>>(N - 1));

				for (size_t i = 0; i < N - 1; ++i)
				{
					for (size_t j = 0; j < N - 1; ++j)
					{
						new_temp[i][j] = temp[i][j];
					}
				}
				determ += pow(-1, k + 2) * matrix[0][k] * determenant_(new_temp, N - 1);

			}
			return determ;
		}
	}
public:
	_matrix() {
		row = 2; column = row;
		data.resize(row);

		for (size_t i = 0; i < row; i++)
		{
			data[i].resize(column);
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
		if (_rows < 1 or _columns < 1) { throw "Invalid matrix size"; }

		row = _rows;
		column = _columns;

		data.resize(row);

		for (size_t i = 0; i < row; i++)
		{
			data[i].resize(column);
		}

		cout << "Enter values" << endl << endl;
		for (size_t i = 0; i < row; i++)
		{
			for (size_t j = 0; j < column; j++)
			{
				cout << "[" << i << "][" << j << "]: ";
				T temp_real, temp_imag;
				cout << "Real:";
				cin >> temp_real;
				cout << "Imaginary:";
				cin >> temp_imag;
				data[i][j] = complex<T>(temp_real, temp_imag);
				cout << endl;
			}

		}
	}

	_matrix(const _matrix<complex<T>>& matrix) = default;

	~_matrix() = default;

	/*class vv_iterator : public iterator<bidirectional_iterator_tag, complex<T>> {		
		vv_iterator(_matrix<complex<T>>& _vv, size_t _idxOuter, size_t _idxInner): vv(&(_vv.data)), idxOuter(_idxOuter), idxInner(_idxInner) {}
		vector<vector<complex<T>>>* vv = nullptr;
		size_t idxOuter = 0;
		size_t idxInner = 0;
		friend class _matrix;
	public:
		
		static vv_iterator begin(_matrix<complex<T>>& vv) {
			return vv_iterator(vv, 0, 0);
		}
		static vv_iterator end(_matrix<complex<T>>& vv) {
			return vv_iterator(vv, vv.get_row(), 0);
		}
		vv_iterator() = default;
	
		vv_iterator& operator++()
		{
			
			if (idxInner + 1 < (*vv)[idxOuter].size())
			{
				
				++idxInner;
			}
			else
			{
				
				do
				{
					++idxOuter;
				} while (idxOuter < (*vv).size() && (*vv)[idxOuter].empty());
				
				idxInner = 0;
			}
			return *this;
		}
		
		vv_iterator& operator--()
		{
			
			if (idxInner > 0)
			{
				
				--idxInner;
			}
			else
			{
				
				do
				{
					--idxOuter;
				} while ((*vv)[idxOuter].empty());
				
				idxInner = (*vv)[idxOuter].size() - 1;
			}
			return *this;
		}
		
		vv_iterator operator++(int)
		{
			complex<T> retval = *this;
			++(*this);
			return retval;
		}
		
		vv_iterator operator--(int)
		{
			complex<T> retval = *this;
			--(*this);
			return retval;
		}
		bool operator==(const vv_iterator& other) const
		{
			return other.vv == vv && other.idxOuter == idxOuter && other.idxInner == idxInner;
		}
		bool operator!=(const vv_iterator& other) const
		{
			return !(*this == other);
		}
		const complex<T>& operator*() const
		{
			return *this;
		}
		complex<T>& operator*()
		{
			return (*vv)[idxOuter][idxInner];
		}
		const complex<T>& operator->() const
		{
			return *this;
		}
		complex<T>& operator->()
		{
			return *this;
		}
	};

	vv_iterator begin() {
		return vv_iterator(*this, 0, 0);
	}
	vv_iterator end() {
		return vv_iterator(*this, row, 0);
	}*/


	auto begin() {
		return data.begin();

	}

	auto end() {
		return data.end();
	}

	int get_row() const {
		if (data.size() != row) { throw "Dimensions of the matrix do not match"; }
		return data.size();
	}

	int get_column() const {
		if (data[0].size() != column) { throw "Dimensions of the matrix do not match"; }
		return data[0].size();
	}

	const complex<T>& operator()(int i, int j) const {
		if ((i<0 or i>row) and (j<0 or j>column)) { throw "Invalid index"; }
		return data[i][j];
	}

	complex<T>& operator()(int i, int j) {
		if ((i<0 or i>row) and (j<0 or j>column)) { throw "Invalid index"; }
		return data[i][j];
	}

	friend ostream& operator<<(ostream& os, const _matrix<complex<T>>& rhs)
	{
		for (const auto& i : rhs.data) {
			for (const auto& j : i) {
				cout.width(15);
				os << left << setprecision(4) << j << '\t';
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
		if (row != matrix.row or column != matrix.column) { throw "Dimensions do not match!"; }
		vector<vector<complex<T>>> temp(row, vector<complex<T>>(column));

		for (size_t i = 0; i < row; ++i)
		{
			for (size_t j = 0; j < column; ++j)
			{
				temp[i][j] = data[i][j] + matrix.data[i][j];
			}
		}

		data = temp;
		return *this;
	}

	_matrix<complex<T>> operator+(const _matrix<complex<T>>& matrix) const {
		_matrix temp(*this);
		temp += matrix;
		return temp;
	}

	_matrix<complex<T>>& operator-=(const _matrix<complex<T>>& matrix) {
		if (row != matrix.row or column != matrix.column) { throw "Dimensions do not match!"; }

		vector<vector<complex<T>>> temp(row, vector<complex<T>>(column));

		for (size_t i = 0; i < row; ++i)
		{
			for (size_t j = 0; j < column; ++j)
			{
				temp[i][j] = data[i][j] - matrix.data[i][j];
			}
		}

		data = temp;
		return *this;
	}

	_matrix<complex<T>> operator-(const _matrix<complex<T>>& matrix) const {
		_matrix temp(*this);
		temp -= matrix;
		return temp;
	}

	_matrix<complex<T>>& operator*=(const _matrix<complex<T>>& matrix) {
		if (column != matrix.row) { throw "The sizes of the matrices do not match! "; }

		vector<vector<complex<T>>> temp(row, vector<complex<T>>(matrix.column));

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

		data = temp;
		return *this;
	}

	_matrix<complex<T>> operator*(const _matrix<complex<T>>& matrix) const {
		_matrix temp(*this);
		temp *= matrix;
		return temp;
	}

	_matrix<complex<T>>& operator*=(complex<T> value) {        //??????
		for (size_t i = 0; i < row; i++)
		{
			for (size_t j = 0; j < column; j++)
			{
				data[i][j] = data[i][j] * value;
			}
		}
		return *this;
	}

	_matrix<complex<T>> operator*(complex<T> value) const {
		_matrix temp(*this);
		temp *= value;
		return temp;
	}

	friend _matrix<complex<T>> operator*(complex<T> value, const _matrix<complex<T>>& matrix) {
		_matrix temp(matrix);
		temp *= value;
		return temp;
	}

	_matrix<complex<T>>& operator*=(T value) {        //??????
		for (size_t i = 0; i < row; i++)
		{
			for (size_t j = 0; j < column; j++)
			{
				data[i][j] = data[i][j] * value;
			}
		}
		return *this;
	}

	_matrix<complex<T>> operator*(T value) const {
		_matrix temp(*this);
		temp *= value;
		return temp;
	}

	friend _matrix<complex<T>> operator*(T value, const _matrix<complex<T>>& matrix) {
		_matrix temp(matrix);
		temp *= value;
		return temp;
	}

	_matrix<complex<T>>& operator/=(complex<T> value) {
		if (value.real() == 0 or value.imag()) { throw "Division by zero"; }
		for (size_t i = 0; i < row; i++)
		{
			for (size_t j = 0; j < column; j++)
			{
				data[i][j] = data[i][j] / value;
			}
		}
		return *this;
	}

	_matrix<complex<T>> operator/(complex<T> value) const {
		_matrix temp(*this);
		temp /= value;
		return temp;
	}

	_matrix<complex<T>>& operator/=(T value) {
		if (value == 0) { throw "Division by zero"; }
		for (size_t i = 0; i < row; i++)
		{
			for (size_t j = 0; j < column; j++)
			{
				data[i][j] = data[i][j] / value;
			}
		}
		return *this;
	}

	_matrix<complex<T>> operator/(T value) const {
		_matrix temp(*this);
		temp /= value;
		return temp;
	}

	complex<T> matrix_trace() const {
		complex<T> temp(0, 0);
		if (row != column) { throw "The matrix is not square"; }
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

		if (determenant_(data, column) == complex<T>(0, 0)) { throw "The determinant of the matrix is 0"; }

		complex<T> temp;
		int N = row;								//размерность
		_matrix<complex<T>> inversion_matrix(*this);

		vector<vector<complex<T>>> E(N, vector<complex<T>>(N));						//единичная матрица

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

		return inversion_matrix;
	}

	complex<T> determenant() const {
		return determenant_(data, row);
	}
};