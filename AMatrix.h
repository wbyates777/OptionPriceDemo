/* Matrix Template Class
 
 $$$$$$$$$$$$$$$$$$$$$$$
 $   Matrix.h - defs   $
 $$$$$$$$$$$$$$$$$$$$$$$
 
 Copyright (C) 2011  W.B. Yates
 
 This program is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 
 You should have received a copy of the GNU General Public License
 along with this program.  If not, see http://www.gnu.org/licenses/

 
 History:
 
*/

#ifndef __MATRIX_H__
#define __MATRIX_H__


#include <iostream>
#include <vector>


template <typename T>
class Matrix 
{

public:
	
	
	Matrix( void ): m_rows(0), m_cols(0), m_rawData() {}	
    Matrix( int r, int c, const T &x = T() ): m_rows(r), m_cols(c), m_rawData(r, std::vector<T>(c, x)) {}
    
	explicit Matrix( const std::vector<std::vector<T>>& values ): m_rows(0), m_cols(0), m_rawData() 
	{
		setMatrix( values );
	}
	

	~Matrix( void ) { m_rows = 0; m_cols = 0; m_rawData.clear(); }
	
    void 
    clear( void ) { m_rows = 0; m_cols = 0; m_rawData.clear(); } 
	
	Matrix<T>& 
	operator=( const T &a );		// assign a to every element
	
	void
	setMatrix( int r, int c )
	{
		m_rows = r;
		m_cols = c;
		m_rawData.resize( r, std::vector<T>(c, T()) );	
	}
	
	void
	setMatrix( const std::vector< std::vector<T> >& values ) 
	{
		m_rows = values.size();
        m_cols = (m_rows) ? values[0].size() : 0;
		m_rawData = values;
	}
	
	std::vector<T>& 
    operator[]( int i ) { return m_rawData[i]; }	// return row i
    
	const std::vector<T>& 
    operator[]( int i ) const { return m_rawData[i]; }
	
	std::vector<T> 
    column( int colIdx ) const; // extract column copy c as a (row) vector
    
    void
    column( int colIdx, const std::vector<T>& c );
	
	int rows( void ) const { return m_rows; }
	int cols( void ) const { return m_cols; }

	void 
	resize( int r, int c, const T& = T() ); // will preserve/truncate existing data accordingly

	const std::vector< std::vector<T> >&
	data( void ) const { return m_rawData; }
	
	std::vector< std::vector<T> >&
	data( void ) { return m_rawData; }
	
private:
		
	int m_rows;
	int m_cols;
	std::vector< std::vector<T> > m_rawData;
	
};

template <class T>
std::ostream&
operator<<( std::ostream& ostr, const Matrix<T>& m );

template <class T>
std::istream&
operator>>( std::istream& istr, Matrix<T>& m );


template <class T>
std::ostream&
operator<<( std::ostream& ostr, const Matrix<T>& m ) 
{
    ostr << m.rows() << ' ' << m.cols() << '\n';
    for (int i = 0; i < m.rows(); ++i)
    {
        for (int j = 0; j < m.cols(); ++j)
        {
            ostr << m[i][j] << ' ';
        }
        ostr << '\n';
    }
    ostr << '\n';
    return ostr;
}

template <class T>
std::istream&
operator>>( std::istream& istr, Matrix<T>& m )
{
    int r = 0, c = 0;
    istr >> r;
    istr >> c;
    
    m.resize(r,c);	
    for (int i = 0; i < m.rows(); ++i)
    {
        for (int j = 0; j < m.cols(); ++j)
        {
            istr >> m[i][j];
        }
    }
    return istr;
}



template <class T>
void 
Matrix<T>::resize( int r, int c, const T& v ) 
{		
	if (r == m_rows && c == m_cols)
		return; // no resize needed
	
	if (c != m_cols) // resize cols of existing rows
	{
		typename std::vector< std::vector<T> >::iterator end = m_rawData.end();
		for (typename std::vector< std::vector<T> >::iterator i = m_rawData.begin(); i != end; ++i)
		{
			i->resize(c, v);
		}
	}
	
	m_rows = r;
	m_cols = c;
	
	// add in extra rows
	m_rawData.resize( r, std::vector<T>(c, v) );
}

template <class T>
Matrix<T>& 
Matrix<T>::operator=( const T &a )	
// assign a to every element
{
	for (int i = 0; i< m_rows; ++i)
	{
		for (int j = 0; j < m_cols; ++j)
		{
			m_rawData[i][j] = a;
		}
	}
	return *this;
}

// extract a copy of column c from matrix as a vector; use transpose(v) to construct a column vector (see below)
template <class T>
std::vector<T> 
Matrix<T>::column( int colIdx ) const
{
	assert(colIdx < m_cols);
	
	std::vector<T> retVal(m_rows); 
	for (int j = 0; j < m_rows; ++j)
	{
		retVal[j] = m_rawData[j][colIdx];
	}
	return retVal;
}

template <class T>
void
Matrix<T>::column( int colIdx, const std::vector<T>& col )
{
    assert(col.size() == m_rows && colIdx < m_cols);
    for (int j = 0; j < m_rows; ++j)
    {
        m_rawData[j][colIdx] = col[j];
    }
}


template <class T>
bool 
operator!=( const Matrix<T> &m1, const Matrix<T> &m2 ); 

template <class T>
bool 
operator==( const Matrix<T> &m1, const Matrix<T> &m2 ); 

template <class T>
bool 
operator!=( const Matrix<T> &m1, const Matrix<T> &m2 ) 
{
	assert((m1.rows() == m2.rows()) && (m1.cols() == m2.cols()));
	
    for (int i = 0; i < m1.rows(); ++i)
	{
		for (int j = 0; j < m1.cols(); ++j)
		{
			if (m1[i][j] != m2[i][j])
				return true;
		}
	}
	return false;
}

template <class T>
bool 
operator==( const Matrix<T> &m1, const Matrix<T> &m2 ) 
{
	assert((m1.rows() == m2.rows()) && (m1.cols() == m2.cols()));
	
    for (int i = 0; i < m1.rows(); ++i)
	{
		for (int j = 0; j < m1.cols(); ++j)
		{
			if (m1[i][j] != m2[i][j])
				return false;
		}
	}
	return true;
}



template <class T>
Matrix<T> 
transpose( const Matrix<T>& m );

 
template <class T>
Matrix<T> 
transpose( const Matrix<T>& m ) 
{
	Matrix<T> retVal(m.cols(), m.rows());
    for (int i = 0; i < retVal.rows(); ++i)
	{
		for (int j = 0; j < retVal.cols(); ++j)
		{
			retVal[i][j] = m[j][i];
		}
	}
	
	return retVal;
}





#endif // __MATRIX_H__ 


