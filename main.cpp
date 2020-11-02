#include <iostream>
#include <fstream>
#include <cmath>
#include <sstream>
#include <cstdlib>
#include <iomanip>

#define tab "\t\t"

using namespace std;


/*

        Yunus Dilber
        yunusdilber99@gmail.com


        Last Change Date: 11.12.2019
*/

//struct
struct rgb
{
  unsigned char red;
  unsigned char blue;
  unsigned char green;
};

//Matrix Class 
template < class P > class Matrix
{
protected:
  P ** matrix;
  int rows;
  int columns;
  double **temp;
public:
  Matrix ();
  void print ();		//print this->matrix
  Matrix (int, int, P);		//cons
  Matrix (int, int, char);	//cons
  void init_matrix (P ** &, int, int, P) const;	//initiate this->matrix with given value
  void resize (int, int);	//resize this->matrix
  void print (string);		//print this->matrix to file
  void T ();			//transpoze
  void emul (Matrix < P > const &);	//emul
  P det (P **, int);		//det for class function
  P det ();
  void adjoint (P **);		//adjoint finding
  void getCofactor (P **, P **, int p, int q, int n);
  void inv ();			//inverse of this->matrix
  template < class P1 > friend Matrix < P1 > operator+ (Matrix < P1 >
							const &m1,
							Matrix < P1 >
							const &m2);
  template < class P1 > friend Matrix < P1 > operator- (Matrix < P1 >
							const &m1,
							Matrix < P1 >
							const &m2);
  template < class P1 > friend Matrix < P1 > operator* (Matrix < P1 >
							const &m1,
							Matrix < P1 >
							const &m2);
  template < class P1 > friend Matrix < P1 > operator+ (Matrix < P1 >
							const &m1, P1 num);
  template < class P1 > friend Matrix < P1 > operator- (Matrix < P1 >
							const &m1, P1 num);
  template < class P1 > friend Matrix < P1 > operator/ (Matrix < P1 >
							const &m1, P1 num);
  template < class P1 > friend Matrix < P1 > operator* (Matrix < P1 >
							const &m1, P1 num);
  template < class P1 > friend Matrix < P1 > operator% (Matrix < P1 >
							const &m1, P1 num);
  template < class P1 > friend Matrix < P1 > operator^ (Matrix < P1 >
							const &m1, P1 num);

};


//for old compilers ; g++ -std=c++0x 365324.cpp 

//constructer
template < class P > Matrix < P >::Matrix ()
{
  rows = 10;
  columns = 10;
  init_matrix (this->matrix, rows, columns, 0);
}

template <> Matrix < rgb >::Matrix ()
{
}

//print this->matrix
template < class s > void Matrix < s >::print ()
{

  if (this->matrix[0][0] < 0.01 && this->matrix[0][0] > -0.05)
    {
      cout << setprecision (4);
    }
  for (int i = 0; i < this->rows; i++)
    {
      for (int j = 0; j < this->columns; j++)
	{
	  cout << this->matrix[i][j] << tab;
	}
      cout << endl;
    }
  cout << endl;
}

template <> void Matrix < rgb >::print ()
{

  for (int i = 0; i < this->rows; i++)
    {
      for (int j = 0; j < this->columns; j++)
	{
	  cout << (int) this->matrix[i][j].green << tab;
	}
      cout << endl;
    }
  cout << endl;
}

//constructer
template < class P > Matrix < P >::Matrix (int row, int col, P value)
{
  rows = row;
  columns = col;
  init_matrix (this->matrix, rows, columns, value);
}

template < class P > Matrix < P >::Matrix (int row, int col, char key)
{
  rows = row;
  columns = col;
  init_matrix (this->matrix, rows, columns, 0);
  if (key == 'e')
    {
      if (rows != columns)
	{
	  cout << "Need n x n this->matrix" << endl;
	  return;
	}

      for (int i = 0; i < rows; i++)
	{
	  this->matrix[i][i] = 1;
	}
    }
  else if (key == 'r')
    {

      for (int i = 0; i < rows; i++)
	{
	  for (int j = 0; j < columns; j++)
	    {
	      this->matrix[i][j] = rand () % 255;
	    }

	}

    }
}

template < class P >
  void Matrix < P >::init_matrix (P ** &mat, int row, int column,
				  P value) const
{
  mat = new P *[row];
  for (int i = 0; i < row; i++)
    {
      mat[i] = new P[column];
      fill_n (mat[i], column, value);	//initialaze values to given avlue
    }
}

template <> void Matrix < rgb >::resize (int r, int c)
{
  rows = r;
  columns = c;
  matrix = new rgb *[r];
  for (int i = 0; i < r; i++)
    {
      matrix[i] = new rgb[c];
    }


}

template < class P > void Matrix < P >::resize (int row, int column)
{

  int row_len, col_len;
  row_len = rows > row ? row : rows;	//is row number grows?
  col_len = columns > column ? column : columns;	//is column number grows?
  P **temp;
  init_matrix (temp, row, column, 0);
  for (int i = 0; i < row_len; i++)
    {
      for (int j = 0; j < col_len; j++)
	{
	  temp[i][j] = this->matrix[i][j];
	}
    }
  for (int i = 0; i < rows; i++)
    {
      delete[] * (this->matrix + i);
    }
  delete[]this->matrix;
  this->rows = row;
  this->columns = column;

  this->matrix = temp;
}

template <> void Matrix < rgb >::print (string file_name)
{
  ofstream file;

  file.open (file_name);

  for (int i = 0; i < this->rows; i++)
    {
      for (int j = 0; j < this->columns; j++)
	{
	  file << (int) this->matrix[i][j].green << " ";
	}
      file << "\n";
    }
  file.close ();
}

template < class P > void Matrix < P >::print (string file_name)
{
  ofstream file;
  file << fixed << setprecision (2);
  if (sizeof (P) == sizeof (int))
    file << setprecision (0);
  file.open (file_name);
  if (this->matrix[0][0] < 0.01 && this->matrix[0][0] > -0.05)
    {
      file << setprecision (4);
    }
  for (int i = 0; i < this->rows; i++)
    {
      for (int j = 0; j < this->columns; j++)
	{
	  file << this->matrix[i][j] << tab;
	}
      file << "\n";
    }
  file.close ();
}

template < class P > void Matrix < P >::T ()
{
  P **trans;
  init_matrix (trans, rows, columns, 0);
  for (int i = 0; i < rows; ++i)
    for (int j = 0; j < columns; ++j)
      {
	trans[j][i] = this->matrix[i][j];
      }
  for (int i = 0; i < rows; i++)
    {
      delete[] * (this->matrix + i);
    }
  delete[]this->matrix;
  this->matrix = trans;
}

template < class P > void Matrix < P >::emul (Matrix < P > const &m2)
{

  if (((this->columns) != (m2.columns)) || ((this->rows) != (m2.rows)))
    {
      cout << "can't emul (m x n != m x n)" << endl;
      return;
    }
  for (int i = 0; i < m2.rows; i++)
    {
      for (int j = 0; j < m2.columns; j++)
	{
	  this->matrix[i][j] = this->matrix[i][j] * m2.matrix[i][j];
	}

    }
}

template < class P >
  Matrix < P > operator+ (Matrix < P > const &m1, Matrix < P > const &m2)
{
  Matrix < P > *C = new Matrix < P > (m1.rows, m1.columns, (P) 0);
  if (m1.columns != m2.columns || m1.columns != m2.columns)
    {
      cout << "can't sub (m x n != m x n)" << endl;
      return m1;
    }

  for (int i = 0; i < m1.rows; i++)
    {
      for (int j = 0; j < m2.columns; j++)
	{
	  C->matrix[i][j] = m1.matrix[i][j] + m2.matrix[i][j];
	}

    }

  return *C;
}

template < class P >
  Matrix < P > operator- (Matrix < P > const &m1, Matrix < P > const &m2)
{

  Matrix < P > *C = new Matrix < P > (m1.rows, m1.columns, (P) 0);
  if (m1.columns != m2.columns || m1.columns != m2.columns)
    {
      cout << "can't sub (m x n != m x n)" << endl;
      return m1;
    }

  for (int i = 0; i < m1.rows; i++)
    {
      for (int j = 0; j < m2.columns; j++)
	{
	  C->matrix[i][j] = m1.matrix[i][j] - m2.matrix[i][j];
	}

    }

  return *C;
}

template < class P >
  Matrix < P > operator* (Matrix < P > const &m1, Matrix < P > const &m2)
{

  if (m1.rows != m2.columns)
    {
      cout << "can't multiply (row1 != column2)" << endl;
      return m1;
    }

  Matrix < P > *C = new Matrix < P > (m1.rows, m1.columns, (P) 0);

  for (int i = 0; i < m1.rows; ++i)
    for (int j = 0; j < m2.columns; ++j)
      for (int k = 0; k < m1.columns; ++k)
	{
	  C->matrix[i][j] += m1.matrix[i][k] * m2.matrix[k][j];
	}

  return *C;
}

template < class P > Matrix < P > operator+ (Matrix < P > const &m1, P num)
{

  Matrix < P > *C = new Matrix < P > (m1.rows, m1.columns, (P) 0);

  for (int i = 0; i < m1.rows; i++)
    {
      for (int j = 0; j < m1.columns; j++)
	{
	  C->matrix[i][j] = m1.matrix[i][j] + num;
	}

    }

  return *C;
}

template < class P > Matrix < P > operator- (Matrix < P > const &m1, P num)
{

  Matrix < P > *C = new Matrix < P > (m1.rows, m1.columns, (P) 0);

  for (int i = 0; i < m1.rows; i++)
    {
      for (int j = 0; j < m1.columns; j++)
	{
	  C->matrix[i][j] = m1.matrix[i][j] - num;
	}

    }

  return *C;
}

template < class P > Matrix < P > operator/ (Matrix < P > const &m1, P num)
{

  Matrix < P > *C = new Matrix < P > (m1.rows, m1.columns, (P) 0);

  for (int i = 0; i < m1.rows; i++)
    {
      for (int j = 0; j < m1.columns; j++)
	{
	  C->matrix[i][j] = m1.matrix[i][j] / num;
	}

    }

  return *C;
}

template < class P > Matrix < P > operator* (Matrix < P > const &m1, P num)
{

  Matrix < P > *C = new Matrix < P > (m1.rows, m1.columns, (P) 0);

  for (int i = 0; i < m1.rows; i++)
    {
      for (int j = 0; j < m1.columns; j++)
	{
	  C->matrix[i][j] = m1.matrix[i][j] * num;
	}

    }

  return *C;
}

template < class P > Matrix < P > operator% (Matrix < P > const &m1, P num)
{

  Matrix < P > *C = new Matrix < P > (m1.rows, m1.columns, (P) 0);

  for (int i = 0; i < m1.rows; i++)
    {
      for (int j = 0; j < m1.columns; j++)
	{
	  if (sizeof (P) == sizeof (int))
	    {
	      C->matrix[i][j] = (int) m1.matrix[i][j] % (int) num;
	    }
	  else
	    {
	      C->matrix[i][j] = fmod (m1.matrix[i][j], num);	// for P numbers
	    }
	}

    }

  return *C;

}

template < class P > Matrix < P > operator^ (Matrix < P > const &m1, P num)
{

  Matrix < P > *C = new Matrix < P > (m1.rows, m1.columns, (P) 0);

  for (int i = 0; i < m1.rows; i++)
    {
      for (int j = 0; j < m1.columns; j++)
	{
	  C->matrix[i][j] = (P) pow (m1.matrix[i][j], num);
	}

    }

  return *C;
}


//find cof
template < class P >
  void Matrix < P >::getCofactor (P ** A, P ** t, int p, int q, int n)
{
  int i = 0, j = 0;

  for (int row = 0; row < n; row++)
    {
      for (int col = 0; col < n; col++)
	{
	  if (row != p && col != q)
	    {
	      t[i][j++] = A[row][col];

	      if (j == n - 1)
		{
		  j = 0;
		  i++;
		}
	    }
	}
    }
}

template < class P > P Matrix < P >::det ()
{
  init_matrix (temp, rows, columns, 0);
  return det (this->matrix, rows);
}

template < class P > P Matrix < P >::det (P ** A, int n)
{
  P D = 0;
  if (rows != columns)
    {
      cout << "\nrow!=columns\n";
      return -1;
    }

  //if this->matrix has 1 elem
  if (n == 1)
    return A[0][0];



  int sign = 1;

  for (int f = 0; f < n; f++)
    {

      getCofactor (A, temp, 0, f, n);
      D += sign * A[0][f] * det (temp, n - 1);

      sign = -sign;
    }

  return D;
}

template < class P > void Matrix < P >::adjoint (P ** adj)
{
  P **t = new P *[rows];
  for (int i = 0; i < rows; i++)
    {
      t[i] = new P[columns];
    }

  for (int i = 0; i < rows; i++)
    {
      for (int j = 0; j < columns; j++)
	{
	  t[i][j] = this->matrix[i][j];
	}

    }

  //find adjoint
  if (rows == 1)
    {
      adj[0][0] = 1;
      return;
    }

  P sign = 1;
  init_matrix (temp, rows, rows, 0);

  for (int i = 0; i < rows; i++)
    {
      for (int j = 0; j < rows; j++)
	{

	  getCofactor (t, temp, i, j, rows);

	  sign = ((i + j) % 2 == 0) ? 1 : -1;

	  adj[j][i] = (sign) * (det (temp, rows - 1));
	}
    }
}

template < class P > void Matrix < P >::inv ()
{
  if (sizeof (P) != sizeof (double))
    {
      cout << "Need double data type for inverse.\n";
      return;
    }
  else
    {

      // Find determinant  
      P determinant = this->det ();
      if (determinant == 0)
	{
	  cout << "\nSingular this->matrix, can't find its inverse\n";
	  return;
	}

      //call ad
      adjoint (this->matrix);
      for (int i = 0; i < rows; i++)
	for (int j = 0; j < rows; j++)
	  this->matrix[i][j] = (P) ((P) this->matrix[i][j] / determinant);
    }

}

template < class t > class Table:public Matrix < t >
{
private:
  string rowNames[25];
  string colNames[25];
public:
Table ():Matrix < t > ()
  {
    initiateRowNames ();
  }				//constructers
  Table (int a, int b, int c):Matrix < t > (a, b, c)
  {
    initiateRowNames ();
  }
  Table (int a, int b, char key);
  //return item with indexes
  int itemAt (int r, int c)
  {
    return this->matrix[r][c];
  }
  //retrun item with string
  int itemAt (string str);
  //retrun item from given values
  int itemAt (string rs, string cs);

  //set rown names
  void setRowNames (string s[], int n);
  //set column names
  void setColNames (string s[], int n);

  //initiate row and column names
  void initiateRowNames ();

  //print table
  void print ();
};

template < class t > Table < t >::Table (int a, int b, char key):
  Matrix < t > (a, b, key)
{
  if (key != 'r')
    {
      cout << "invalid command key..." << endl;
      this->resize (0, 0);
    }
  initiateRowNames ();
}

template < class t > int Table < t >::itemAt (string str)
{
  string r = str.substr (1);	//get second char
  string c = str.substr (0, 1);	//get first
  int i, j;
  for (i = 0; i < 25; i++)
    {
      if (rowNames[i] == r)
	{
	  break;
	}
    }
  for (j = 0; j < 25; j++)
    {
      if (colNames[j] == c)
	{
	  break;
	}
    }
  return this->matrix[i][j];
}


template < class t > int Table < t >::itemAt (string rs, string cs)
{
  string r = rs;
  string c = cs;
  int i, j;
  for (i = 0; i < 25; i++)
    {
      if (rowNames[i] == r)
	{
	  break;
	}
    }
  for (j = 0; j < 25; j++)
    {
      if (colNames[j] == c)
	{
	  break;
	}
    }
  return this->matrix[i][j];
}

template < class t > void Table < t >::setRowNames (string s[], int n)
{
  for (int i = 0; i < n; i++)
    {
      rowNames[i] = s[i];
    }

}

template < class t > void Table < t >::setColNames (string s[], int n)
{
  for (int i = 0; i < n; i++)
    {
      colNames[i] = s[i];
    }

}

template < class t > void Table < t >::initiateRowNames ()
{
  int i;
  for (i = 0; i < 25; i++)
    {
      stringstream s;
      s << i;
      s >> rowNames[i];
    }
  for (i = 0; i < 25; i++)
    {
      colNames[i] = ((char) i + 65);	//assign from ascii value
    }

}

template < class t > void Table < t >::print ()
{
  cout << setprecision (2) << tab;
  if (sizeof (t) == sizeof (int))
    cout << setprecision (0);
  if (this->matrix[0][0] < 0.01 && this->matrix[0][0] > -0.05)
    {
      cout << setprecision (4);
    }

  for (int i = 0; i < this->columns; i++)
    {
      cout << colNames[i] << tab;
    }
  cout << "\n\n";
  for (int i = 0; i < this->rows; i++)
    {
      cout << rowNames[i] << tab;
      for (int j = 0; j < this->columns; j++)
	{
	  cout << this->matrix[i][j] << tab;
	}
      cout << "\n";
    }
  cout << endl;
}

template < class E > class Image:public Matrix < rgb >
{
private:
  int width;
  int height;
  int filesize;
  bool bin_flag;
  unsigned char *headerInfo;
  unsigned char w, h, pixel;
  unsigned char TheaderInfo[54] =
    { 'B', 'M', 0, 0, 0, 0, 0, 0, 0, 0, 54, 0, 0, 0,
    40, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    1, 0, 8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0
  };
  //init list
  unsigned char Color_table[1024];
public:
  Image ()
  {
    bmp_header (255, 255);
    resize (255, 255);
  }
  Image (int w, int h)
  {
    bmp_header (w, h);
    resize (height, width);
  }
  Image (string fn, string f)
  {
    imread (fn, f);		//call image read
  }


  void matrix_to_binary ();

  void imread (string filename, string mode);

  void imwrite (string name, string format);

  void bmp_header (int w, int h);

  //color image becomes gray
  void color2gray ();

  //gray image becomes binary
  void gray2binary (int the);

  void erosion ();
  void dilation ();

  void opening ();
  void closing ();

};

template < class A > void Image < A >::color2gray ()
{
  int k = 0;
  for (int i = 0; i < height; i++)
    {
      for (int j = 0; j < width; j++)
	{
	  this->matrix[i][j].green =
	    (unsigned char) (0.3 * this->matrix[i][j].green);
	}

    }

}

template < class A > void Image < A >::gray2binary (int the)
{
  bin_flag = true;
  for (int i = 0; i < height; i++)
    {
      for (int j = 0; j < width; j++)
	{
	  this->matrix[i][j].green =
	    (unsigned char) ((int) this->matrix[i][j].green) > the ? 255 : 0;
	}

    }

}

template < class A > void Image < A >::opening ()
{
  if (!bin_flag)
    {
      cout << "Image is not Binary" << endl;
      return;
    }
  this->erosion ();
  this->dilation ();
}

template < class A > void Image < A >::closing ()
{
  if (!bin_flag)
    {
      cout << "Image is not Binary" << endl;
      return;
    }
  this->dilation ();
  this->erosion ();
}

template < class A > void Image < A >::imread (string filename, string mode)
{
  if (mode == "bmp")
    {
      //read bmp formated file and set values to struct
      headerInfo = TheaderInfo;
      ifstream myFile;
      unsigned char hc, r;
      myFile.open (filename, ios::binary);
      for (int i = 0; i < 54; ++i)
	{
	  if (i == 2)
	    {
	      myFile.read (reinterpret_cast < char *>(&this->filesize),
			   sizeof (int));
	      i = 5;
	    }
	  else if (i == 18)
	    {
	      myFile.read (reinterpret_cast < char *>(&this->width),
			   sizeof (int));
	      i = 21;
	    }
	  else if (i == 22)
	    {
	      myFile.read (reinterpret_cast < char *>(&this->height),
			   sizeof (int));
	      i = 25;
	    }
	  else
	    myFile >> r;
	}
      myFile.seekg (0, ios::beg);
      for (int i = 0; i < 54; i++)
	{
	  myFile >> headerInfo[i];
	}


      for (int i = 0; i < 1024; i++)
	{
	  myFile >> noskipws >> Color_table[i];
	}
      resize (height, width);

      for (int i = 0, k = 0; i < height; i++)
	{
	  for (int j = 0; j < width; j++, k++)
	    {
	      myFile >> noskipws >> pixel;
	      this->matrix[i][j].green = pixel;
	    }

	}

      myFile.close ();
    }
  else if (mode == "bin")
    {
      //read bin formated file and set values to struct
      unsigned char r;
      ifstream myFile;
      myFile.open (filename, ios::binary);
      myFile >> this->h >> this->w;

      this->height = (int) h;
      this->width = (int) w;
      resize (height, width);
      for (int i = 0, k = 0; i < height; i++)
	{
	  for (int j = 0; j < width; j++, k++)
	    {
	      myFile >> noskipws >> pixel;

	      this->matrix[i][j].green = pixel;
	    }

	}
      myFile.close ();
      bmp_header (width, height);
    }
}

template < class A > void Image < A >::imwrite (string name, string format)
{
  if (format == "bmp")
    {
      //write bmp formatted file 
      ofstream myFile;
      myFile.open (name, ios::binary);

      for (int i = 0; i < 54; i++)
	{
	  myFile << headerInfo[i];
	}
      for (int i = 0; i < 1024; i++)
	{
	  myFile << Color_table[i];
	}
      for (int i = 0; i < height; i++)
	{
	  for (int j = 0; j < width; j++)
	    {
	      myFile << this->matrix[i][j].green;
	    }

	}

      myFile.close ();
    }
  else if (format == "bin")
    {
      //write bin formatted file 
      ofstream myFile;
      myFile.open (name, ios::binary);

      h = (unsigned char) this->height;
      w = (unsigned char) this->width;
      myFile << h << w;

      for (int i = 0; i < height; i++)
	{
	  for (int j = 0; j < width; j++)
	    {
	      myFile << this->matrix[i][j].green;
	    }

	}
      myFile.close ();
    }
}

template < class A > void Image < A >::bmp_header (int w, int h)
{
  // assign values with w and h
  this->width = w;
  this->height = h;
  this->filesize = (54 + w * h);
  while (this->filesize % 4 != 0)
    filesize++;			//filesize must be multiple of 4
  TheaderInfo[2] = (unsigned char) (filesize);
  TheaderInfo[3] = (unsigned char) (filesize >> 8);
  TheaderInfo[4] = (unsigned char) (filesize >> 16);
  TheaderInfo[5] = (unsigned char) (filesize >> 24);
  TheaderInfo[14 + 4] = (unsigned char) (width);
  TheaderInfo[14 + 5] = (unsigned char) (width >> 8);
  TheaderInfo[14 + 6] = (unsigned char) (width >> 16);
  TheaderInfo[14 + 7] = (unsigned char) (width >> 24);
  TheaderInfo[14 + 8] = (unsigned char) (height);
  TheaderInfo[14 + 9] = (unsigned char) (height >> 8);
  TheaderInfo[14 + 10] = (unsigned char) (height >> 16);
  TheaderInfo[14 + 11] = (unsigned char) (height >> 24);
  headerInfo = TheaderInfo;
}

template < class A > void Image < A >::matrix_to_binary ()
{
  for (int i = 0; i < height; i++)
    {
      for (int j = 0; j < width; j++)
	{
	  this->matrix[i][j].green =
	    (unsigned char) ((int) this->matrix[i][j].green) > 0 ? 1 : 0;

	}
    }
}

//erosion
template < class A > void Image < A >::erosion ()
{
  if (!bin_flag)
    {
      cout << "Image is not Binary" << endl;
      return;
    }
  rgb **temp = new rgb *[rows];
  for (int i = 0; i < rows; i++)
    {
      temp[i] = new rgb[columns];
    }

  matrix_to_binary ();
  unsigned char B = (unsigned char) 1;
  for (int i = 0, k = 0; i < height; i++)
    {
      for (int j = 0; j < width; j++, k++)
	{
	  if (i > 0 && j != 0 && i != height - 1 && j != width - 1)
	    {
	      if (this->matrix[i][j].green == B
		  && this->matrix[i][j - 1].green == B
		  && this->matrix[i][j + 1].green == B
		  && this->matrix[i + 1][j].green == B
		  && this->matrix[i - 1][j].green == B
		  && this->matrix[i + 1][j + 1].green == B
		  && this->matrix[i + 1][j - 1].green == B
		  && this->matrix[i - 1][j - 1].green == B
		  && this->matrix[i - 1][j + 1].green == B)
		{
		  temp[i][j].green = (unsigned char) 255;
		}
	      else
		{
		  temp[i][j].green = (unsigned char) 0;
		}
	    }
	  else
	    {
	      temp[i][j].green = (unsigned char) 0;
	    }
	}
    }
  matrix = temp;

}

//dilatoin
template < class A > void Image < A >::dilation ()
{
  if (!bin_flag)
    {
      cout << "Image is not Binary" << endl;
      return;
    }
  matrix_to_binary ();
  rgb **temp = new rgb *[rows];
  for (int i = 0; i < rows; i++)
    {
      temp[i] = new rgb[columns];
    }
  unsigned char B = (unsigned char) 1;
  for (int i = 0; i < height; i++)
    {
      for (int j = 0; j < width; j++)
	{
	  if (i > 0 && j != 0 && i != height - 1 && j != width - 1)
	    {
	      if (this->matrix[i][j].green == B
		  || this->matrix[i][j - 1].green == B
		  || this->matrix[i][j + 1].green == B
		  || this->matrix[i + 1][j].green == B
		  || this->matrix[i - 1][j].green == B
		  || this->matrix[i + 1][j + 1].green == B
		  || this->matrix[i + 1][j - 1].green == B
		  || this->matrix[i - 1][j - 1].green == B
		  || this->matrix[i - 1][j + 1].green == B)
		{
		  temp[i][j].green = (unsigned char) 255;
		}
	      else
		{
		  temp[i][j].green = (unsigned char) 0;
		}
	    }
	  else
	    {
	      temp[i][j].green = (unsigned char) 0;
	    }
	}
    }
  matrix = temp;
}


int
main ()
{
  srand (time (NULL));
  cout << fixed << setprecision (2);
  Matrix < double >*m1 = new Matrix < double >(2, 2, 'r');
  Matrix < double >*m2 = new Matrix < double >(2, 2, 'r');
  m1->inv ();
  m1->print ();
  m1->emul (*m2);
  m1->print ();
  (*m1) = (*m2) - (*m1);
  (*m1) = (*m2) + (*m1);
  (*m1) = (*m2) * (*m1);
  (*m1) = (*m2) + 5.0;
  (*m1) = (*m2) - 3.0;
  (*m1) = (*m2) * 4.0;
  (*m1) = (*m2) % 5.0;
  (*m1) = (*m2) ^ 1.;
  m1->T ();
  m1->print ();

  Image < rgb > I (10, 10);
  I.imread ("image_file2.bmp", "bmp");
  I.color2gray ();
  I.gray2binary (41);
  I.erosion ();
  I.dilation ();
  I.closing ();
  I.opening ();
  I.imwrite ("myf.bmp", "bmp");

  I.imread ("image1.bin", "bin");
  I.color2gray ();
  I.gray2binary (25);
  I.erosion ();
  I.dilation ();
  I.closing ();
  I.opening ();
  I.imwrite ("myo.bin", "bin");

  I.print ("a.txt");

  Table < float >*table = new Table < float >(5, 5, 'r');
  cout << table->itemAt (2, 2);
  string rownames[5] = {"A","B","C","D","E"};
  table->setRowNames(rownames,5);
  table->print ();
  return 0;




}
