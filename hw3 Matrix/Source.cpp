#include<iostream>
#include<conio.h>
#include<fstream>
#include<ctime>
#include <cstdlib>
using namespace std;
class Matrix
{
	int **mat;
	int r;  // number of rows
	int c;  // number of columns
public:
	friend Matrix operator*(int, Matrix &);
	friend ostream& operator<<(ostream &, Matrix &);
	Matrix()
	{
		mat = nullptr;
		r = c = 0;
	}
	~Matrix()        // destructor
	{
		if (mat != nullptr)
		{
			for (int i = 0; i < r; i++)
				delete[] mat[i];
			delete[] mat;
		}
	}
	Matrix(int rows, int cols, int val)
	{
		r = rows;
		c = cols;
		mat = new int*[r];
		for (int i = 0; i < r; i++)
			mat[i] = new int[c];

		for (int i = 0; i < r; i++)
		{
			for (int j = 0; j < c; j++)
			{
				mat[i][j] = val;
			}
		}
	}
	Matrix(char* file)
	{
		int val = 0;
		ifstream fin(file);  
		if (fin.fail())
		{
			cout << "File not opened";
		}
		else
		{
			fin>>val;
			r = val;
			fin >> val;
			c = val;
			mat = new int*[r];
			for (int i = 0; i < r; i++)
				mat[i] = new int[c];

			for (int i = 0; i < r; i++)
			{
				for (int j = 0; j < c; j++)
				{
					fin >> val;
					mat[i][j] = val;
				}
			}
		}
		fin.close();
	}
	Matrix(const Matrix &obj)   //deep copy constructor  w=t=v
	{
		r = obj.r;
		c = obj.c;
		mat = new int*[r];
		for (int i = 0; i < r; i++)
			mat[i] = new int[c];
		for (int i = 0; i < r; i++)
		{
			for (int j = 0; j < c; j++)
			{
				mat[i][j] = obj.mat[i][j];
			}
		}
	}
	Matrix operator+(int val)  
	{
		Matrix ans;
		ans.r = r;
		ans.c = c;
		ans.mat = new int*[ans.r];
		for (int i = 0; i < ans.r; i++)
			ans.mat[i] = new int[ans.c];
		for (int i = 0; i < ans.r; i++)
		{
			for (int j = 0; j < ans.c; j++)
			{
				ans.mat[i][j] =mat[i][j]+ val;
			}
		}
		return ans;
	}
	Matrix operator+ (const Matrix &obj)
	{
		if (obj.r == r && obj.c == c)
		{
			Matrix ans;
			ans.r = r;
			ans.c = c;
			ans.mat = new int*[r];
			for (int i = 0; i < r; i++)
				ans.mat[i] = new int[c];
			for (int i = 0; i < r; i++)
			{
				for (int j = 0; j < c; j++)
				{
					ans.mat[i][j] = mat[i][j] + obj.mat[i][j];
				}
			}
			return ans;
		}
		else
			cout << "Addition not possible" << endl;
	}
	void operator=(const Matrix &obj)   // deep copy 
	{
		if (mat != nullptr)   
		{ 
			for (int i = 0; i < r;i++)
				delete[] mat[i];
			delete [] mat;
		}
		r = obj.r;
		c = obj.c;
		mat = new int*[r];
		for (int i = 0; i < r; i++)
			mat[i] = new int[c];
		for (int i = 0; i < r; i++)
		{
			for (int j = 0; j < c; j++)
			{
				mat[i][j] = obj.mat[i][j];
			}
		}
	}
	bool operator== (const Matrix &obj)
	{

		if (r != obj.r || c != obj.c)
			return false;
		else if (r == obj.r && c == obj.c)
		{
			for (int i = 0; i < r; i++)
			{
				for (int j = 0; j < c; j++)
				{
					if (mat[i][j] != obj.mat[i][j])
					{
						return false;
						break;
					}
				}
			}
		}
		return true;
	}
	bool operator!=(const Matrix &obj)
	{
		if (r != obj.r || c != obj.c)
			return true;
		else if (r == obj.r && c == obj.c)
		{
			for (int i = 0; i < r; i++)
			{
				for (int j = 0; j < c; j++)
				{
					if (mat[i][j] != obj.mat[i][j])
					{
						return true;
						break;
					}
				}
			}
		}
		return false;
	}
	Matrix operator*(const Matrix &obj)
	{
		if (c == obj.r)
		{
			Matrix ans;
			ans.r = r;
			ans.c = obj.c;
			ans.mat = new int*[ans.r];
			for (int i = 0; i < ans.r; i++)
				ans.mat[i] = new int[ans.c];
			for (int i = 0; i < r; i++)
			{
				for (int j = 0; j < obj.c; j++)     
				{
					ans.mat[i][j] = 0;
					for (int k = 0; k < obj.r; k++)
					{	
						ans.mat[i][j] += mat[i][k] * obj.mat[k][j];
					}
				}
			}
			return ans;
		}
		else
			cout << "Multiplication not possible" << endl;
	}
	void operator*(int num)
	{
		for (int i = 0; i < r; i++)
		{
			for (int j = 0; j < c; j++)
			{
				mat[i][j] = num*mat[i][j];
			}
		}
	}
	Matrix operator++(int)			// post increment
	{
		Matrix temp;
		temp = *this;
		for (int i = 0; i < r; i++)
		{
			for (int j = 0; j < c; j++)
				mat[i][j] = mat[i][j] + 1;
		}
		return temp;
	}
	Matrix operator++()			// pre increment
	{
		for (int i = 0; i < r; i++)
		{
			for (int j = 0; j < c; j++)
				mat[i][j] = mat[i][j] + 1;
		}
		return *this;
	}
	Matrix Transpose()
	{
		Matrix ans;
		ans.r = c;
		ans.c = r;
		ans.mat = new int*[ans.r];
		for (int i = 0; i < ans.r; i++)
			ans.mat[i] = new int[ans.c];
		for (int i = 0; i < r; i++)
		{
			for (int j = 0; j < c; j++)
			{
				ans.mat[j][i] = mat[i][j];
			}
		}
		return ans;
	}
	int row()
	{
		return r;
	}
	int col()
	{
		return c;
	}
	int*& operator [] (const int i)   // operator overload
	{
		return mat[i];
	}
	static Matrix Identity(int row, int col)
	{
		Matrix iden;
		iden.r = row;
		iden.c = col;
		iden.mat = new int *[iden.r];
		for (int i = 0; i < iden.r; i++)
			iden.mat[i] = new int[iden.c];
		for (int i = 0; i < iden.r; i++)
		{
			for (int j = 0; j < iden.c; j++)
			{
				if (i == j)
					iden.mat[i][j] = 1;
				else
					iden.mat[i][j] = 0;
			}
		}
		return iden;
	}
	static Matrix Random(int row, int col, int lim)
	{
		Matrix ans;
		ans.r = row;
		ans.c = col;
		ans.mat = new int *[ans.r];
		for (int i = 0; i < ans.r; i++)
			ans.mat[i] = new int[ans.c];
		srand(0);
		for (int i = 0; i < ans.r; i++)
		{
			for (int j = 0; j < ans.c; j++)
			{
				ans.mat[i][j] = (rand() % (lim - 1 + 1) + 1);
			}
		}
		return ans;
	}
	Matrix operator*=(Matrix &obj)
	{
		if (c == obj.r)
		{
			*this = *this * obj;
			return *this;
		}
		else
			cout << "Multiplication not possible" << endl;
	}
};
Matrix operator*( int val, Matrix &obj)
{
	for (int i = 0; i < obj.r; i++)
	{
		for (int j = 0; j < obj.c; j++)
		{
			obj.mat[i][j] = obj.mat[i][j] * val;
		}
	}
	return obj;
}
ostream& operator<<(ostream &out, Matrix &obj)
{
	if (obj.mat != nullptr)
	{
		for (int i = 0; i < obj.r; i++)
		{
			for (int j = 0; j < obj.c; j++)
			{
				if(obj.mat[i][j]>=100)
					out << obj.mat[i][j] << " ";
				else if (obj.mat[i][j]<10)
					out <<"  "<< obj.mat[i][j] << " ";
				else
					out<< " " << obj.mat[i][j] << " ";
			}
			out << endl;
		}
	}
	return out;
}

int main()
{
	Matrix m1("mat1.txt"), m2("mat2.txt"), m3(2, 3, 0), m4;
	if (m1 != m3)
	{
		m3 = m3 + m1;
	}
	cout << "Result of addition M3 is:" << endl << m3;
	m4 = m3*m2; 
	cout << "Result of multiplication:" << endl << m4;
	Matrix m5 = (3 * (m3++)) + 2;
	cout << "Result of m5=(3*(m3++))+2:" << endl << m5;
	cout << "Updated m3:" << endl << m3;
	for (int i = 0; i<m5.row(); i++) //following code replaces all odd numbers in m4 by zeroes
	{
		for (int j = 0; j<m5.col(); j++)
		{
			if (m5[i][j] % 2 != 0)
			{
				m5[i][j] = 0;
			}
		}
	}
	cout << "m5 after odds are zeroed:" << endl << m5;  
	Matrix m6 = Matrix::Identity(5, 5);		//a 5x5 identity matrix
	cout << "m6 is the identity matrix:" << endl << m6;
	Matrix m7 = m6.Transpose();
	cout << "m7 is the transpose of m6:" << endl << m7;
	Matrix m8 = Matrix::Random(5, 5, 100);	//a 5x5 matrix of random values below 100
	cout << "m8 is a 5x5 random matrix:" << endl << m8;
	m7 *= (++m8);
	cout << "Updated m8:" << endl << m8;
	cout << "Result of m7*=(++m8)" << endl << m7;
	
	_getch();
}