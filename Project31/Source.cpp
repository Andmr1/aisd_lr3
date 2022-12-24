#include <iostream>
#include <vector>
#include <iterator>
#include<complex>
template <typename T>
class matrix
{
	std::vector<std::vector<T>> _data;
	size_t _columns;
public:
	template<typename T1>friend std::ostream& operator<<(std::ostream& s, matrix<T1> a);
	matrix(size_t rows=0,size_t columns=0, bool ask = false)
	{
		if (ask == true)
		{
			std::cout << "Rows: ";
			std::cin >> rows;
			std::cout << std::endl;
			std::cout << "Columns: ";
			std::cin >> columns;
			std::cout << std::endl;
		}
		std::vector<std::vector<T>> data;		
		for (size_t i = 0; i < rows; ++i)
		{
			std::vector<T> dt;
			for (size_t j = 0; j < columns; ++j)
			{
				T val = 0;
				std::cout << "val[" << i << "][" << j << "]:= ";
				std::cin >> val;
				dt.push_back(val);
			}
			data.push_back(dt);
		}
		_data = data;
		_columns = columns;
	}
	int begin()
	{
		return _data.begin();
	}
	int end()
	{
		return _data.end;
	}
	T& operator()(size_t row, size_t column)
	{
		if (row < _data.size())
		{
			if (column < _data[row].size())
			{
				return _data[row][column];
			}
		}
		throw("Invalid index");
	}
	matrix operator +(const matrix& a)const
	{
		if (_data.size() != a._data.size() || _data[0].size() != a._data[0].size())
		{
			throw("Invalid sizes");
		}
		matrix b = *this;
		for (size_t i = 0; i < b._data.size(); ++i)
		{
			for (size_t j = 0; j < b._columns; ++j)
			{
				b._data[i][j] += a._data[i][j];
			}
		}
		return b;
	}
	matrix& operator +=(const matrix b)
	{
		if (_data.size != b._data.size() || _columns != b._columns)
		{
			throw("Invalid sizes");
		}
		for (size_t i = 0; i < _data.size(); ++i)
		{
			for (size_t j = 0; j < _columns; ++j)
			{
				this->_data[i][j] += b._data[i][j];
			}
		}
		return *this;
	}
	matrix operator - (const matrix& a)const
	{
		if (_data.size() != a._data.size() || _columns != a._columns)
		{
			throw("Invalid sizes");
		}
		matrix b = *this;
		for (size_t i = 0; i < a._data.size(); ++i)
		{
			for (size_t j = 0; j < b._columns; ++j)
			{
				b._data[i][j] -= a._data[i][j];
			}
		}
		return b;
	}
	matrix operator / (T val)const
	{
		if (val == 0)
		{
			throw("Division by zero");
		}
		matrix b = *this;
		for (size_t i = 0; i < b._data.size(); ++i)
		{
			for (size_t j = 0; j < b._columns; ++j)
			{
				b._data[i][j] /= val;
			}
		}
		return b;
	}
	matrix operator * (T val)const
	{
		matrix b = *this;
		for (size_t i = 0; i < b._data.size(); ++i)
		{
			for (size_t j = 0; j < b._columns; ++j)
			{
				b._data[i][j] *= val;
			}
		}
		return b;
	}
	matrix operator*(const matrix& a)const
	{
		if (_data[0].size() != a._data.size())
		{
			throw("Invalid sizes");
		}
		matrix b = *this;
		matrix c(b._data.size(), a._columns, 0);
		for (size_t i = 0; i < b._data.size(); ++i)
		{
			for (size_t j = 0; j < a._columns; ++j)
			{
				for (size_t k = 0; k < b._columns; ++k)
				{
					c._data[i][j] += b._data[i][k] * a._data[k][j];
				}
			}
		}
		return c;
	}
	T trail()const
	{
		if (_data.size() != _columns)
		{
			throw("This matrix is not square");
		}
		T tr = 0;
		for (size_t i = 0; i < _data.size(); ++i)
		{
			tr += _data[i][i];
		}
		return tr;
	}
	matrix inversion()const
	{
		if (_data.size() != _columns)
		{
			throw("Only for square matrix");
		}
		T tmp;
		matrix a = *this;
		matrix b = a;
		for (size_t i = 0; i < a._data.size(); ++i)
		{
			for (size_t j = 0; j < a._columns; ++j)
			{
				b._data[i][j] = 0;
				if (i == j)b._data[i][j] = 1;
			}
		}
		for (int k = 0; k < a._data.size();++k)
		{
			tmp = a._data[k][k];
			for (int j = 0; j < a._data.size(); ++j)
			{
				a._data[k][j] /= tmp;
				b._data[k][j] /= tmp;
			}
			for (int i = k + 1; i < a._data.size(); ++i)
			{
				tmp = a._data[i][k];
				for (int j = 0; j < a._data.size(); ++j)
				{
					a._data[i][j] -= a._data[k][j] * tmp;
					b._data[i][j] -= b._data[k][j] * tmp;
				}
			}
		}
		for (int k = a._data.size() - 1; k > 0; --k)
		{
			for (int i = k - 1; i >= 0; --i)
			{
				tmp = a._data[i][k];
				for (int j = 0; j < a._data.size(); ++j)
				{
					a._data[i][j] -= a._data[k][j] * tmp;
					b._data[i][j] -= b._data[k][j] * tmp;
				}
			}
		}
		return b;
	}
	bool operator ==(const matrix& b)const
	{
		if (_data.size() != b._data.size() || _columns != b._columns)
		{
			return false;
		}
		for (size_t i = 0; i < _data.size(); ++i)
		{
			for (size_t j = 0; j < _columns; ++j)
			{
				if (_data[i][j] != b._data[i][j])
				{
					return false;
				}
			}
		}
		return true;
	}
};
template <typename T>
std::ostream& operator <<(std::ostream& s, matrix<T> a)
{
	for (auto&& c : a._data)
	{
		for (auto&& b : c)
		{
			s << b<<" ";
		}
		s << std::endl;
	}
	return s;
}
template<typename T>
matrix<T> operator*(T val, const matrix<T>& a)
{
	return a * val;
}
template<> matrix<std::complex<double>> matrix<std::complex<double>>::operator/(std::complex<double> val)const
{
	if (val.real() == 0 || val.imag() == 0)
	{
		throw("Division by zero");
	}
	matrix<std::complex<double>> b = *this;
	for (size_t i = 0; i < b._data.size(); ++i)
	{
		for (size_t j = 0; j < b._columns; ++j)
		{
			b._data[i][j] /= val;
		}
	}
	return b;
}
template<> matrix<std::complex<float>> matrix<std::complex<float>>::operator/(std::complex<float> val)const
{
	if (val.real() == 0 || val.imag() == 0)
	{
		throw("Division by zero");
	}
	matrix<std::complex<float>> b = *this;
	for (size_t i = 0; i < b._data.size(); ++i)
	{
		for (size_t j = 0; j < b._columns; ++j)
		{
			b._data[i][j] /= val;
		}
	}
	return b;
}
template<> matrix<int> matrix<int>::inversion()const
{
	throw("Unavalible for integer");
	return *this;
}
void menu()
{
	std::cout << "create matrix:1 \n";
	std::cout << "trail:2 \n";
	std::cout << "matrix inversion:3 \n";
	std::cout << "matrix sum:4 \n";
	std::cout << "matrix difference:5 \n";
	std::cout << "matrix multiplication:6 \n";
	std::cout << "matrix multiplication 2:7 \n";
	std::cout << "matrix division:8 \n";
	std::cout << "call element:9 \n";
	std::cout << "matrix compirision:10 \n";
	std::cout << "back:11 \n";	
}
void menu2()
{
	std::cout << "Choose type:" << std::endl;
	std::cout << "int:1" << std::endl;;
	std::cout << "float:2" << std::endl;;
	std::cout << "double:3" << std::endl;;
	std::cout << "std::complex<float>:4" << std::endl;;
	std::cout << "std::complex<double>:5" << std::endl;;
	std::cout << "quit:6" << std::endl;;
}
int main()
{
	matrix<int> a1(0, 0);
	matrix<float> a2(0,0);
	matrix<double> a3(0,0);
	matrix<std::complex<float>> a4(0,0);
	matrix<std::complex<double>> a5(0,0);
	bool main_loop = 0, loop_int = 0, loop_float = 0, loop_double = 0, loop_cdouble = 0, loop_cfloat = 0;
	while (!main_loop)
	{
		menu2();
		size_t choice;
		std::cin >> choice;
		switch (choice)
		{
			case 1:
				loop_int = 0;
				while (!loop_int)
				{
					menu();
					size_t choice_int;
					std::cin >> choice_int;
					switch (choice_int)
					{
					case 1:
					{
						matrix<int>a12(0, 0, true);
						std::cout << a12;
						a1 = a12;
					}
					break;
					case 2:
					{
						std::cout << a1.trail();
					}
					break;
					case 3:
					{
						try
						{
							matrix<int> c = a1.inversion();
							std::cout << c;
						}
						catch (const char* err)
						{
							std::cout << err << std::endl;
						}
					}
					break;
					case 4:
					{
						matrix<int>b(0, 0, true);
						try
						{
							matrix<int>c = a1 + b;
							std::cout << c;
						}
						catch (const char* err)
						{
							std::cout << err << std::endl;
						}
					}
					break;
					case 5:
					{
						try
						{
							matrix<int> b(0, 0, true);
							std::cout << a1 - b;
						}
						catch (const char* err)
						{
							std::cout << err << std::endl;
						}
					}
					break;
					case 6:
					{
						try
						{
							matrix<int> b(0, 0, true);
							std::cout << a1 * b;
						}
						catch (const char* err)
						{
							std::cout << err << std::endl;
						}
					}
					break;
					case 7:
					{
						int val1 = 0;
						std::cout << "Input integer: ";
						std::cin >> val1;
						std::cout << std::endl;
						std::cout << a1 * val1 << std::endl;
					}
					break;
					case 8:
					{
						int val1 = 0;
						std::cout << "Input integer: ";
						std::cin >> val1;
						std::cout << std::endl;
						try
						{
							std::cout << a1 / val1;
						}
						catch (const char* err)
						{
							std::cout << err << std::endl;
						}
					}
					break;
					case 9:
					{
						bool call = false;
						std::cout << "call: 1" << std::endl << "change: 2" << std::endl;
						std::cout << "choise: ";
						std::cin >> call;
						std::cout << std::endl;
						switch (call)
						{
						case 1:
						{
							size_t row, column;
							std::cout << "Row; ";
							std::cin >> row;
							std::cout << std::endl << "Column: ";
							std::cin >> column;
							try
							{
								std::cout << std::endl << a1(row, column) << std::endl;
							}
							catch (const char* err)
							{
								std::cout << err;
							}
						}
						break;
						case 2:
						{
							size_t row, column;
							std::cout << "Row; ";
							std::cin >> row;
							std::cout << std::endl << "Column: ";
							std::cin >> column;
							std::cout << std::endl << "Value: ";
							int val1;
							std::cin >> val1;
							try
							{
								a1(row, column) = val1;
								std::cout << a1;
							}
							catch (const char* err)
							{
								std::cout << err;
							}
						}
						}
						break;
					}
					break;
					case 10:
					{
						matrix<int>b1(0, 0, true);
						bool c = a1 == b1;
						std::cout << c << std::endl;
					}
					break;
					break;
					case 11:
						loop_int = 1;
						break;
					}
				}
				break;
			case 2:
				loop_float = 0;
				while (!loop_float)
				{
					menu();
					size_t choice_fl;
					std::cin >> choice_fl;
					switch (choice_fl)
					{
					case 1:
					{
						matrix<float>a12(0, 0, true);
						std::cout << a12;
						a2 = a12;
					}
					break;
					case 2:
					{
						std::cout << a2.trail();
					}
					break;
					case 3:
					{
						try
						{
							matrix<float> c = a2.inversion();
							std::cout << c;
						}
						catch (const char* err)
						{
							std::cout << err << std::endl;
						}
					}
					break;
					case 4:
					{
						matrix<float>b(0, 0, true);
						try
						{
							matrix<float>c = a2 + b;
							std::cout << c;
						}
						catch (const char* err)
						{
							std::cout << err << std::endl;
						}
					}
					break;
					case 5:
					{
						try
						{
							matrix<float> b(0, 0, true);
							std::cout << a2 - b;
						}
						catch (const char* err)
						{
							std::cout << err << std::endl;
						}
					}
					break;
					case 6:
					{
						try
						{
							matrix<float> b(0, 0, true);
							std::cout << a2 * b;
						}
						catch (const char* err)
						{
							std::cout << err << std::endl;
						}
					}
					break;
					case 7:
					{
						float val1 = 0;
						std::cout << "Input integer: ";
						std::cin >> val1;
						std::cout << std::endl;
						std::cout << a2 * val1 << std::endl;
					}
					break;
					case 8:
					{
						float val1 = 0;
						std::cout << "Input integer: ";
						std::cin >> val1;
						std::cout << std::endl;
						try
						{
							std::cout << a2 / val1;
						}
						catch (const char* err)
						{
							std::cout << err << std::endl;
						}
					}
					break;
					case 9:
					{
						bool call = false;
						std::cout << "call: 1" << std::endl << "change: 2" << std::endl;
						std::cout << "choise: ";
						std::cin >> call;
						std::cout << std::endl;
						switch (call)
						{
						case 1:
						{
							size_t row, column;
							std::cout << "Row; ";
							std::cin >> row;
							std::cout << std::endl << "Column: ";
							std::cin >> column;
							try
							{
								std::cout << std::endl << a2(row, column) << std::endl;
							}
							catch (const char* err)
							{
								std::cout << err;
							}
						}
						break;
						case 2:
						{
							size_t row, column;
							std::cout << "Row; ";
							std::cin >> row;
							std::cout << std::endl << "Column: ";
							std::cin >> column;
							std::cout << std::endl << "Value: ";
							float val1;
							std::cin >> val1;
							try
							{
								a2(row, column) = val1;
								std::cout << a2;
							}
							catch (const char* err)
							{
								std::cout << err;
							}
						}
						}
						break;
					}
					break;
					case 10:
					{
						matrix<float>b1(0, 0, true);
						bool c = a2 == b1;
						std::cout << c << std::endl;
					}
					break;
					break;
					case 11:
						loop_float = 1;
						break;
					}
				}
				break;
			case 3:
				loop_double = 0;
				while (!loop_double)
				{
					menu();
					size_t choice_db;
					std::cin >> choice_db;
					switch (choice_db)
					{
					case 1:
					{
						matrix<double>a12(0, 0, true);
						std::cout << a12;
						a3 = a12;
					}
					break;
					case 2:
					{
						std::cout << a3.trail();
					}
					break;
					case 3:
					{
						try
						{
							matrix<double> c = a3.inversion();
							std::cout << c;
						}
						catch (const char* err)
						{
							std::cout << err << std::endl;
						}
					}
					break;
					case 4:
					{
						matrix<double>b(0, 0, true);
						try
						{
							matrix<double>c = a3 + b;
							std::cout << c;
						}
						catch (const char* err)
						{
							std::cout << err << std::endl;
						}
					}
					break;
					case 5:
					{
						try
						{
							matrix<double> b(0, 0, true);
							std::cout << a3 - b;
						}
						catch (const char* err)
						{
							std::cout << err << std::endl;
						}
					}
					break;
					case 6:
					{
						try
						{
							matrix<double> b(0, 0, true);
							std::cout << a3 * b;
						}
						catch (const char* err)
						{
							std::cout << err << std::endl;
						}
					}
					break;
					case 7:
					{
						double val1 = 0;
						std::cout << "Input integer: ";
						std::cin >> val1;
						std::cout << std::endl;
						std::cout << a3 * val1 << std::endl;
					}
					break;
					case 8:
					{
						double val1 = 0;
						std::cout << "Input integer: ";
						std::cin >> val1;
						std::cout << std::endl;
						try
						{
							std::cout << a3 / val1;
						}
						catch (const char* err)
						{
							std::cout << err << std::endl;
						}
					}
					break;
					case 9:
					{
						bool call = false;
						std::cout << "call: 1" << std::endl << "change: 2" << std::endl;
						std::cout << "choise: ";
						std::cin >> call;
						std::cout << std::endl;
						switch (call)
						{
						case 1:
						{
							size_t row, column;
							std::cout << "Row; ";
							std::cin >> row;
							std::cout << std::endl << "Column: ";
							std::cin >> column;
							try
							{
								std::cout << std::endl << a3(row, column) << std::endl;
							}
							catch (const char* err)
							{
								std::cout << err;
							}
						}
						break;
						case 2:
						{
							size_t row, column;
							std::cout << "Row; ";
							std::cin >> row;
							std::cout << std::endl << "Column: ";
							std::cin >> column;
							std::cout << std::endl << "Value: ";
							double val1;
							std::cin >> val1;
							try
							{
								a3(row, column) = val1;
								std::cout << a3;
							}
							catch (const char* err)
							{
								std::cout << err;
							}
						}
						}
						break;
					}
					break;
					case 10:
					{
						matrix<double>b1(0, 0, true);
						bool c = a3 == b1;
						std::cout << c << std::endl;
					}
					break;
					break;
					case 11:
						loop_double = 1;
						break;
					}
				}
				break;
			case 4:
				loop_cfloat = 0;
				while (!loop_cfloat)
				{
					menu();
					size_t choice_cfl;
					std::cin >> choice_cfl;
					switch (choice_cfl)
					{
					case 1:
					{
						matrix<std::complex<float>>a12(0, 0, true);
						std::cout << a12;
						a4 = a12;
					}
					break;
					case 2:
					{
						std::cout << a4.trail();
					}
					break;
					case 3:
					{
						try
						{
							matrix<std::complex<float>> c = a4.inversion();
							std::cout << c;
						}
						catch (const char* err)
						{
							std::cout << err << std::endl;
						}
					}
					break;
					case 4:
					{
						matrix<std::complex<float>>b(0, 0, true);
						try
						{
							matrix<std::complex<float>>c = a4 + b;
							std::cout << c;
						}
						catch (const char* err)
						{
							std::cout << err << std::endl;
						}
					}
					break;
					case 5:
					{
						try
						{
							matrix<std::complex<float>> b(0, 0, true);
							std::cout << a4 - b;
						}
						catch (const char* err)
						{
							std::cout << err << std::endl;
						}
					}
					break;
					case 6:
					{
						try
						{
							matrix<std::complex<float>> b(0, 0, true);
							std::cout << a4 * b;
						}
						catch (const char* err)
						{
							std::cout << err << std::endl;
						}
					}
					break;
					case 7:
					{
						std::complex<float> val1 = (0,0);
						std::cout << "Input integer: ";
						std::cin >> val1;
						std::cout << std::endl;
						std::cout << a4 * val1 << std::endl;
					}
					break;
					case 8:
					{
						std::complex<float> val1 = (0,0);
						std::cout << "Input integer: ";
						std::cin >> val1;
						std::cout << std::endl;
						try
						{
							std::cout << a4 / val1;
						}
						catch (const char* err)
						{
							std::cout << err << std::endl;
						}
					}
					break;
					case 9:
					{
						bool call = false;
						std::cout << "call: 1" << std::endl << "change: 2" << std::endl;
						std::cout << "choise: ";
						std::cin >> call;
						std::cout << std::endl;
						switch (call)
						{
						case 1:
						{
							size_t row, column;
							std::cout << "Row; ";
							std::cin >> row;
							std::cout << std::endl << "Column: ";
							std::cin >> column;
							try
							{
								std::cout << std::endl << a4(row, column) << std::endl;
							}
							catch (const char* err)
							{
								std::cout << err;
							}
						}
						break;
						case 2:
						{
							size_t row, column;
							std::cout << "Row; ";
							std::cin >> row;
							std::cout << std::endl << "Column: ";
							std::cin >> column;
							std::cout << std::endl << "Value: ";
							std::complex<float> val1;
							std::cin >> val1;
							try
							{
								a4(row, column) = val1;
								std::cout << a4;
							}
							catch (const char* err)
							{
								std::cout << err;
							}
						}
						}
						break;
					}
					break;
					case 10:
					{
						matrix<std::complex<float>>b1(0, 0, true);
						bool c = a4 == b1;
						std::cout << c << std::endl;
					}
					break;
					break;
					case 11:
						loop_cfloat = 1;
						break;
					}
				}
				break;
			case 5:
				loop_cdouble = 0;
				while (!loop_cdouble)
				{
					menu();
					size_t choice_cdb;
					std::cin >> choice_cdb;
					switch (choice_cdb)
					{
					case 1:
					{
						matrix<std::complex<double>>a12(0, 0, true);
						std::cout << a12;
						a5 = a12;
					}
					break;
					case 2:
					{
						std::cout << a5.trail();
					}
					break;
					case 3:
					{
						try
						{
							matrix<std::complex<double>> c = a5.inversion();
							std::cout << c;
						}
						catch (const char* err)
						{
							std::cout << err << std::endl;
						}
					}
					break;
					case 4:
					{
						matrix<std::complex<double>>b(0, 0, true);
						try
						{
							matrix<std::complex<double>>c = a5 + b;
							std::cout << c;
						}
						catch (const char* err)
						{
							std::cout << err << std::endl;
						}
					}
					break;
					case 5:
					{
						try
						{
							matrix<std::complex<double>> b(0, 0, true);
							std::cout << a5 - b;
						}
						catch (const char* err)
						{
							std::cout << err << std::endl;
						}
					}
					break;
					case 6:
					{
						try
						{
							matrix<std::complex<double>> b(0, 0, true);
							std::cout << a5 * b;
						}
						catch (const char* err)
						{
							std::cout << err << std::endl;
						}
					}
					break;
					case 7:
					{
						std::complex<double> val1 = (0,0);
						std::cout << "Input integer: ";
						std::cin >> val1;
						std::cout << std::endl;
						std::cout << a5 * val1 << std::endl;
					}
					break;
					case 8:
					{
						std::complex<double> val1 = 0;
						std::cout << "Input integer: ";
						std::cin >> val1;
						std::cout << std::endl;
						try
						{
							std::cout << a5 / val1;
						}
						catch (const char* err)
						{
							std::cout << err << std::endl;
						}
					}
					break;
					case 9:
					{
						bool call = false;
						std::cout << "call: 1" << std::endl << "change: 2" << std::endl;
						std::cout << "choise: ";
						std::cin >> call;
						std::cout << std::endl;
						switch (call)
						{
						case 1:
						{
							size_t row, column;
							std::cout << "Row; ";
							std::cin >> row;
							std::cout << std::endl << "Column: ";
							std::cin >> column;
							try
							{
								std::cout << std::endl << a5(row, column) << std::endl;
							}
							catch (const char* err)
							{
								std::cout << err;
							}
						}
						break;
						case 2:
						{
							size_t row, column;
							std::cout << "Row; ";
							std::cin >> row;
							std::cout << std::endl << "Column: ";
							std::cin >> column;
							std::cout << std::endl << "Value: ";
							std::complex<double> val1;
							std::cin >> val1;
							try
							{
								a5(row, column) = val1;
								std::cout << a5;
							}
							catch (const char* err)
							{
								std::cout << err;
							}
						}
						}
						break;
					}
					break;
					case 10:
					{
						matrix<std::complex<double>>b1(0, 0, true);
						bool c = a5 == b1;
						std::cout << c << std::endl;
					}
					break;
					break;
					case 11:
						loop_cdouble = 1;
						break;
					}
				}
				break;
			case 6:
				main_loop = 1;
		}
	}
	return 0;
}
