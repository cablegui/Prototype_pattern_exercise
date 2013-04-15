// ArrayMechanisms.cpp
//
// 2003-8-1 Initial code DD
// 2003-80-6 DD major code review and changes
// 2004-4-3 DD testing etc.
// 2004-4-9 DD Code review and final fiat (for time being)
// 2005-6-19 DD print function for Tensor
// 2005-1-8 DD big fix in l2Norm (wrong name)
// 2007-6-25 DD major new update, code 
//
// (C) Datasim Education BV 2003-2007
//

#ifndef ArrayMechanisms_cpp
#define ArrayMechanisms_cpp

#include "ArrayMechanisms.hpp"
#include <cmath>
#include <algorithm>
#include <map>
#include <iostream>
using namespace std;

///////////////////////////////////////////////////////////////////////////////////////////////
// Sums and averages
template <typename V, typename I> V sum(const Vector<V,I>& x)
{ // Sum of elements     

		V ans = x[x.MinIndex()];

		for (I j = x.MinIndex()+1; j <= x.MaxIndex(); ++j)
		{
			ans += x[j];
		}

		return ans;
} 

template <typename V, typename I> V product(const Vector<V,I>& x)
{ // Product of elements     


	V ans = x[x.MinIndex()];
		
	for (I j = x.MinIndex() + 1; j <= x.MaxIndex(); ++j)
	{
		ans *= x[j];
	}

	return ans;
}

template <typename V, typename I> V sumReciprocals(const Vector<V,I>& x) 
{  // Sum of reciprocals    

		// Precondition (PREC): x is (strictly) positive

		V ans = x[x.MinIndex()];
			
		for (I j = x.MinIndex() + 1; j <= x.MaxIndex(); ++j)
		{
			ans += 1.0/x[j];
		}

		return ans;

} 


template <typename V, typename I> V sumAbsoluteValues(const Vector<V,I>& x) 
{  // Sum of the absolute values of a vector  

		V ans = fabs(x[x.MinIndex()]);
		
		for (I j = x.MinIndex()+1; j <= x.MaxIndex(); ++j)
		{
			ans += fabs(x[j]);
		}

		return ans;
} 

// Mean value == sum() / N 
template <typename V, typename I> V arithmeticMean(const Vector<V,I>& x)
{      

	return sum(x) / V(x.Size());

} 

// Weighted arithmetic mean
template <typename V, typename I> V weightedArithmeticMean(const Vector<V,I>& x, const Vector<V,I>& w)
{      

		// PREC: x and w have the same size; start indexes not necessarily the same
		// PREC: sum(w) is not zero

		V ans = w[w.MinIndex()]* x[x.MinIndex()];
		
		for (I j = x.MinIndex() +1; j <= x.MaxIndex(); ++j)
		{
			ans += w[j] * x[j];
		}

		return ans / sum(w);
} 

// Geometric mean or geometric average 
template <typename V, typename I> V geometricMean(const Vector<V,I>& x)
{   
	
	V ans = product(x);

	return pow(ans, 1.0 / x.Size() );
} 

// Harmonic mean
template <typename V, typename I> V harmonicMean(const Vector<V,I>& x)
{      

	// PREC: sumReciprocals(x) not zero

	return V(x.Size()) / sumReciprocals(x);
} 

// Root mean square (RMS)
template <typename V, typename I> V quadraticMean(const Vector<V,I>& x)
{     

	return sqrt( sumSquares(x) / V(x.Size()) );
} 

// Sum of squares
template <typename V, typename I> V sumSquares(const Vector<V,I>& x)
{     
		V ans = x[x.MinIndex()];
		
		for (I j = x.MinIndex()+1; j <= x.MaxIndex(); ++j)
		{
			ans += (x[j] * x[j]);
		}

		return ans;
}


// A function returning all of the above values in one foul swoop (performance)
template <typename V, typename I> SimplePropertySet<string, V> allAverages(const Vector<V,I>& x)
{     

	SimplePropertySet<string, V> result;	// Empty list

	result.add(Property<string, V> ("SUM", sum(x)));
	result.add(Property<string, V> ("PRODUCT", product(x)));
	result.add(Property<string, V> ("SUMREC", sumReciprocals(x)));
	result.add(Property<string, V> ("SUMABSVAL", sumAbsoluteValues(x)));
	result.add(Property<string, V> ("MEAN", arithmeticMean(x)));
	result.add(Property<string, V> ("GMEAN", geometricMean(x)));
	result.add(Property<string, V> ("HMEAN", harmonicMean(x)));
	result.add(Property<string, V> ("RMS", quadraticMean(x)));
	result.add(Property<string, V> ("SUMSQ", sumSquares(x)));

	return result;


}
/////////////////////////////////////////////////////////////////////////////


// Measures of Dispersion
template <typename V, typename I> V deviationFromMean(const Vector<V,I>& x)
{


		V avg = mean(x);

		
		V ans = x[x.MinIndex()];
		
		for (I j = x.MinIndex() + 1; j <= x.MaxIndex(); ++j)
		{
			ans += fabs(x[j] - avg);
		}

		return ans / x.Size();

}


template <typename V, typename I> V standardDeviation(const Vector<V,I>& x)
{

		V avg = mean(x);
		V tmp;
		
		V ans = x[x.MinIndex()];
		
		for (I j = x.MinIndex() + 1; j <= x.MaxIndex(); ++j)
		{
			tmp = x[j] - avg;
			ans += tmp*tmp;
		}

		return sqrt(ans / V(x.Size()));


}


template <typename V, typename I> V variance(const Vector<V,I>& x)
{

	V s = standardDeviation(x);

	return s*s;

}


// A function returning all of the above values in one foul swoop (performance)
template <typename V, typename I> SimplePropertySet<string, V> allDispersions(const Vector<V,I>& x)
{      

	SimplePropertySet<string, V> result;	// Empty list

	result.add(Property<string, V> ("MDEV", deviationFromMean(x)));
	result.add(Property<string, V> ("STD", standardDeviation()));
	result.add(Property<string, V> ("VARIANCE", variance(x)));

	return result;



}

////////////////////////////////////////////////////////////////////////////////////////////////


// Moments, Skewness and Kurtosis

// The rth moment about the value 0.0
template <typename V, typename I> V rthMoment(const Vector<V,I>& x, const I& r)
{      

	return rthMoment(x, r, 0.0);

}

// The rth moment about the Mean m(r) as a special origin
template <typename V, typename I> V rthMomentMean(const Vector<V,I>& x, const I& r)
{      

		return rthMoment(x, r, mean(x));
}

template <typename V, typename I> V rthMomentMean(const Vector<V,I>& x, const Vector<V,I>& freq,
											const I& r)
{      

		return rthMoment(x, freq, r, mean(x));
}

// The rth moment about an origin A
template <typename V, typename I> V rthMoment(const Vector<V,I>& x, const I& r, const V& A)
{      


		V ans = pow(x[x.MinIndex()] - A, pr); V pr = V(r);
		
		for (I j = x.MinIndex() + 1; j <= x.MaxIndex(); ++j)
		{
			ans += pow(x[j] - A, pr);
		}

		return ans / x.Size();


}

template <typename V, typename I> V rthMoment(const Vector<V,I>& x, const Vector<V,I>& freq, 
										const I& r, const V& A)
{


		V ans = freq[freq.MinIndex()] * pow(x[x.MinIndex()] - A, pr);
		V vr = V(r);
		
		for (I j = x.MinIndex() + 1; j <= x.MaxIndex(); ++j)
		{
			ans += freq[j] * pow(x[j] - A, vr);
		}

		return ans / sum(freq);

}

// Mode: either the middel element or the mean of the two middle elements 
template <typename V, typename I> V median(const Vector<V,I>& x)
{

	// Work around; ideally Vector should have a sort()
	vector<V> v = createSTLvector(x);
	stable_sort(v.begin(), v.end()); // Now v is sorted

	int N = v.size();
	if ((N/2)*2 == N)	// Even list
	{
		return (v[N/2] + v[(N/2) - 1]) * V(0.5);
	}
	else
	{
		return v[N/2];
	}

}

// Number of occurrences of value d in vector x
template <typename V, typename I> I occurs(const Vector<V,I>& x, const V& d)
{
	I result = I(0);

	for (I j = x.MinIndex(); j <= x.MaxIndex(); ++j)
	{
			if (d == x[j])
				result++;
	}

	return result;
}


// The element in x that occurs with the greatest frequency
template <typename V, typename I> V mode(const Vector<V,I>& x)
{
	// The value that occurs with the greatest frequency
	// Exx. Code can be optimised

	map<V, I> elements;

	// Create unique list of elements
	for (I j = x.MinIndex(); j <= x.MaxIndex(); ++j)
	{
			elements[x[j]] = occurs(x, x[j]);
	}

	map<V, I>::const_iterator i = elements.begin();

	I ans = (*i).second;
	V result = (*i).first;

	while (i != elements.end())
	{ 
			
		if (ans < (*i).second)
			result = (*i).second;

		i++;
	}

	return result;


}


template <typename V, typename I> V skewness(const Vector<V,I>& x)
{

	//return (mean(x) - mode(x)) / standardDeviation(x);

	// Good example for parallel processing
	return 3.0 * (arithmeticMean(x) - median(x))/ standardDeviation(x);

}



////////////////////////////////////////////////////////////////////////////////////////////////////

// Extremum operations on vectors

template <typename V, typename I> V maxValue(const Vector<V,I>& x)
{      
		V ans = x[x.MinIndex()];
		
		for (I j = x.MinIndex() + 1; j <= x.MaxIndex(); ++j)
		{
			if (ans < x[j])
				ans = x[j];
		}

		return ans;
}

template <typename V, typename I> V minValue(const Vector<V,I>& x)
{      

		V ans = x[x.MinIndex()];
		
		for (I j = x.MinIndex() + 1; j <= x.MaxIndex(); ++j)
		{
			if (ans > x[j])
				ans = x[j];
		}

		return ans;
}

// Max and min of the absolute values
template <typename V, typename I> V maxAbsValue(const Vector<V,I>& x)
{      
		V ans = fabs(x[x.MinIndex()]);
		
		for (I j = x.MinIndex() + 1; j <= x.MaxIndex(); ++j)
		{
			if (ans < fabs(x[j]))
				ans = fabs(x[j]);
		}

		return ans;
}

template <typename V, typename I> V minAbsValue(const Vector<V,I>& x)
{     

		V ans = fabs(x[x.MinIndex()]);
		
		for (I j = x.MinIndex() + 1; j <= x.MaxIndex(); ++j)
		{
			if (ans > fabs(x[j]))
				ans = fabs(x[j]);
		}

		return ans;
}

// Index of max and min values 
template <typename V, typename I> I indexMaxValue(const Vector<V,I>& x)
{      	
		I index = x.MinIndex();
		V ans =	x[x.MinIndex()];
	
		for (I j = x.MinIndex() + 1; j <= x.MaxIndex(); ++j)
		{
			if (ans < x[j])
			{
				index = j;
				ans = x[j];
			}
		}

		return index;


}

template <typename V, typename I> V indexMinValue(const Vector<V,I>& x)
{     

		I index = x.MinIndex();
		V ans =	x[x.MinIndex()];
	
		for (I j = x.MinIndex() + 1; j <= x.MaxIndex(); ++j)
		{
			if (ans > x[j])
			{
				index = j;
				ans = x[j];
			}
		}

		return index;
}

template <typename V, typename I> I indexMaxAbsValue(const Vector<V,I>& x)
{     

		I index = x.MinIndex();
		V ans =	fabs(x[x.MinIndex()]);
	
		for (I j = x.MinIndex() + 1; j <= x.MaxIndex(); ++j)
		{
			if (ans < fabs(x[j]))
			{
				index = j;
				ans = fabs(x[j]);
			}
		}

		return index;

}


template <typename V, typename I> V indexMinAbsValue(const Vector<V,I>& x)
{   

		I index = x.MinIndex();
		V ans =	fabs(x[x.MinIndex()]);
	
		for (I j = x.MinIndex() + 1; j <= x.MaxIndex(); ++j)
		{
			if (ans > fabs(x[j]))
			{
				index = j;
				ans = fabs(x[j]);
			}
		}

		return index;

}

// Vector-vector extremum (difference of two vectors)
template <typename V, typename I> V maxValue(const Vector<V,I>& vectorA, const Vector<V,I>& vectorB)
{    

	// PREC: A and B have same size (holds for all the following functions too)

	Vector<V,I> vecDiff = vectorA - vectorB;

	return maxValue(vecDiff);

}

template <typename V, typename I> V minValue(const Vector<V,I>& vectorA, const Vector<V,I>& vectorB)
{  

	Vector<V,I> vecDiff = vectorA - vectorB;

	return minValue(vecDiff);
}


template <typename V, typename I> V maxAbsValue(const Vector<V,I>& vectorA, const Vector<V,I>& vectorB)
{  

	Vector<V,I> vecDiff = vectorA - vectorB;

	return maxAbsValue(vecDiff);
}

template <typename V, typename I> V minAbsValue(const Vector<V,I>& vectorA, const Vector<V,I>& vectorB)
{     
	Vector<V,I> vecDiff = vectorA - vectorB;

	return minAbsValue(vecDiff);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////


// Vector and matrix norms

template <typename V, typename I> V innerProduct(const Vector<V,I>& x, const Vector<V,I>& y)
{      

		// PREC: x and y have same size
		V ans = x[x.MinIndex()] * y[y.MinIndex()];
		
		for (I j = x.MinIndex() + 1; j <= x.MaxIndex(); ++j)
		{
			ans += x[j] * y[j];
		}

		return ans;

}

template <typename V, typename I> V l1Norm(const Vector<V,I>& x)
{    

	return sumAbsoluteValues(x);
}

// template <typename V, typename I> V ManyToManyRelationorm(const Vector<V,I>& x)
template <typename V, typename I> V l2Norm(const Vector<V,I>& x)
{      

	return sqrt(sumSquares(x));
}	

template <typename V, typename I> V lpNorm(const Vector<V,I>& x, const I& p)
{      

		V myPower = V(p);
		V ans = pow(x[x.MinIndex()], myPower);
		
		for (I j = x.MinIndex()+  1; j <= x.MaxIndex(); ++j)
		{
			ans += pow(x[j], myPower);;
		}

		return pow(ans, V(1.0)/ myPower);


}		


template <typename V, typename I> V lInfinityNorm(const Vector<V,I>& x)
{     

	return maxAbsValue(x);

}

template <typename V, typename I> SimplePropertySet<string, V> allNorms(const Vector<V,I>& x)
{

	SimplePropertySet<string, V> result;	// Empty list

	result.add(Property<string, V> ("l1", l1Norm(x)));
	result.add(Property<string, V> ("l2", ManyToManyRelationorm(x)));
	result.add(Property<string, V> ("linf", lInfinityNorm(x)));

	return result;

}

template <typename V, typename I> SimplePropertySet<string, V> allNorms(const Vector<V,I>& vectorA, const Vector<V,I>& vectorB)
{


	Vector<V,I> vecDiff = vectorA - vectorB;

	return allNorms(vecDiff);
}




// Same vector morms as above except for the difference of two vectors
template <typename V, typename I> V l1Norm(const Vector<V,I>& vectorA, const Vector<V,I>& vectorB)
{   

	Vector<V,I> vecDiff = vectorA - vectorB;

	return l1Norm(vecDiff);

}

template <typename V, typename I> V l2Norm(const Vector<V,I>& vectorA, const Vector<V,I>& vectorB)

{   

	Vector<V,I> vecDiff = vectorA - vectorB;

	return l2Norm(vecDiff);
	

}

template <typename V, typename I> V lpNorm(const Vector<V,I>& vectorA, const Vector<V,I>& vectorB, const I& p)
{     

	Vector<V,I> vecDiff = vectorA - vectorB;

	return lpNorm(vecDiff, p);
	
}	


template <typename V, typename I> V lInfinityNorm(const Vector<V,I>& vectorA, const Vector<V,I>& vectorB)
{   

	Vector<V,I> vecDiff = vectorA - vectorB;

	return lInfinityNorm(vecDiff);
	

}



////////////////////////////////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////////////////////////
// Functions for Operations Research

// Comparing vectors with each other

// Are all elements of a vector positive?
template <typename V, typename I> bool positive(const Vector<V,I>& x)
{      
		
		V zero = V(0.0);
		
		for (I j = x.MinIndex(); j <= x.MaxIndex(); ++j)
		{
			if (x[j] <= zero)
				return false;
		}

		return true;

}

template <typename V, typename I> bool negative(const Vector<V,I>& x)
{    

	V zero = V(0.0);

	for (I j = x.MinIndex(); j <= x.MaxIndex(); ++j)
	{
			if (x[j] >= zero)
				return false;
	}

	return true;
}



// Is v1 < v2? etc. 
template <typename V, typename I> bool operator < (const Vector<V,I>& v1, const Vector<V,I>& v2)
{   


		// Iterate in the matrix; when the condition is NOT true 
		// (the inverse of the inequality) then exit and return false
		for (I j = v1.MinIndex(); j <= v1.MaxIndex(); ++j)
		{
			if (v1[j] >= v2[j])
				return false;
		}

		return true;
}


template <typename V, typename I> bool operator <= (const Vector<V,I>& v1, const Vector<V,I>& v2)
{  

		// Iterate in the matrix; when the condition is NOT true 
		// (the inverse of the inequality) then exit and return false
		for (I j = v1.MinIndex(); j <= v1.MaxIndex(); ++j)
		{
			if (v1[j] > v2[j])
				return false;
		}

		return true;

}


template <typename V, typename I> bool operator > (const Vector<V,I>& v1, const Vector<V,I>& v2)
{  

		// Iterate in the matrix; when the condition is NOT true
		// (the inverse of the inequality) then exit and return false
		for (I j = v1.MinIndex(); j <= v1.MaxIndex(); ++j)
		{
			if (v1[j] <= v2[j])
				return false;
		}

		return true;
}


template <typename V, typename I> bool operator >= (const Vector<V,I>& v1, const Vector<V,I>& v2)
{  

		// Iterate in the matrix; when the condition is NOT true 
		// (the inverse of the inequality) then exit and return false
		for (I j = v1.MinIndex(); j <= v1.MaxIndex(); ++j)
		{
			if (v1[j] < v2[j])
				return false;
		}

		return true;
}


template <typename V, typename I> bool operator == (const Vector<V,I>& v1, const Vector<V,I>& v2)
{  

		// Iterate in the matrix; when the condition is NOT true 
		// (the inverse of the inequality) then exit and return false
		for (I j = v1.MinIndex(); j <= v1.MaxIndex(); ++j)
		{
			if (v1[j] != v2[j])
				return false;
		}

		return true;
}


template <typename V, typename I> bool operator != (const Vector<V,I>& v1, const Vector<V,I>& v2)
{  

	if (v1 == v2) 
		return false;

	return true;
}



// Utility functions
template <typename V> vector<V> createSTLvector (const Vector<V, long>& myVector)
{ // Create an STL vector from a general Vector

	vector<V> result(myVector.Size());
	for (int i = 0; i < result.size(); i++)
	{

		result[i] = myVector[i+myVector.MinIndex()];
	}

	return result;
}


template <typename V> Vector<V, long> createDatasimVector (const vector<V>& mySTLvector)
{ // Create a general Vector from an STL vector


	Vector<V, int> result(mySTLvector.size());

	for (int i = 0, j = result.MinIndex(); i < mySTLvector.size(); i++, ++j)
	{

		result[j] = mySTLvector[i];
	}

	return result;
}

template <typename V, typename I> Vector<V, I> cumulativeVector (const Vector<V, I>& x)
{ // Cumulative vector c[j] = c[j-1] + x[j]

	Vector<V, I> result(x.Size(), x.MaxIndex());

	result[x.MinIndex()] = x[x.MinIndex()];
	for (int i = x.MinIndex() + 1; i <= x.MaxIndex(); i++)
	{

		result[i] = result[i-1] + x[i];
	}

	return result;
}

template <typename V, typename I> Vector<V, I> reverse (const Vector<V,I>& x)
{

	Vector<V, I> result(x);
	I min = x.MInIndex();

	for (I k = result.MinIndex(); k <= result.MaxIndex(); k++)
	{

		result[k] = x[x.MaxIndex() - k + min];
	}

	return result;

}



////////////////////// Print Functions /////////////////////////////////////////
template <typename V, typename I> void print(const Array<V,I>& v)
{

	cout << "\n\nMinIndex: " << v.MinIndex() << " , MaxIndex: " << v.MaxIndex() << endl;

	cout << "\nARR:[";
	for (I j = v.MinIndex(); j <= v.MaxIndex(); ++j)
	{
		cout << v[j] << ", ";
	
	}

	cout << "]";
}

template <typename V, typename I> void print(const Vector<V,I>& v)
{

	cout << "\n\nMinIndex: " << v.MinIndex() << " , MaxIndex: " << v.MaxIndex() << endl;

	cout << "\nARR:[";
	for (I j = v.MinIndex(); j <= v.MaxIndex(); ++j)
	{
		cout << v[j] << ", ";
	
	}

	cout << "]";
}

template <typename V, typename I> void print (Tensor<V, I>& tensor)
{
	cout << "Tensor, Rows " << tensor.Rows() << ", Columns " << tensor.Columns() << 
			", Third Dimension " << tensor.sizeThird() << endl;

	for (long k = tensor.MinThirdIndex(); k<= tensor.MaxThirdIndex(); k++)
	{
		print (tensor[k]);
	}
}
#endif