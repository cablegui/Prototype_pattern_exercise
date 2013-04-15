// ArrayMechanisms.hpp
//
// Sets of functions for common vector and matrix manipulation. These
// are useful utility functions.
//
// Categories:
//
//			Sums and averages of vectors
//			Mean, median, std, variance
//			Maximum/minimum values associated with vectors
//			Inner products, norms of vectors and matrices
//			Comparing vectors
//			Converting between STL vector and (Datasim) Vector
//			Simple (but useful) print functions
//
// (C) Datasim Education BV 2003-2007

#ifndef ArrayMechanisms_hpp
#define ArrayMechanisms_hpp

#include "UtilitiesDJD/PropertySet/SimplePropertySet.cpp"
#include "UtilitiesDJD/Geometry/Range.cpp"
#include "UtilitiesDJD/Geometry/Tensor.cpp"

///////////////////////////////////////////////////////////////////////////////////////////////
// Sums and averages
template <typename V, typename I> V sum(const Vector<V,I>& x); // Sum of elements
template <typename V, typename I> V product(const Vector<V,I>& x); // Product of elements
template <typename V, typename I> V sumReciprocals(const Vector<V,I>& x); // Sum of reciprocals
template <typename V, typename I> V sumAbsoluteValues(const Vector<V,I>& x); // Sum of absolute values


// Mean value == sum() / N , arithmetic
template <typename V, typename I> V arithmeticMean(const Vector<V,I>& x); 

// Weighted arithmetic mean
template <typename V, typename I> V weightedArithmeticMean(const Vector<V,I>& x, const Vector<V,I>& w); 

// Geometric mean or geometric average 
template <typename V, typename I> V geometricMean(const Vector<V,I>& x); 

// Harmonic mean
template <typename V, typename I> V harmonicMean(const Vector<V,I>& x); 

// Root mean square (RMS)
template <typename V, typename I> V quadraticMean(const Vector<V,I>& x); 

// Sum of squares
template <typename V, typename I> V sumSquares(const Vector<V,I>& x);

// A function returning all of the above values in one foul swoop (performance)
template <typename V, typename I> SimplePropertySet<string, V> allAverages(const Vector<V,I>& x);


////////////////////////////////////////////////////////////////////////////////////////////////


// Measures of Dispersion

template <typename V, typename I> V deviationFromMean(const Vector<V,I>& x);
template <typename V, typename I> V standardDeviation(const Vector<V,I>& x);
template <typename V, typename I> V variance(const Vector<V,I>& x);

// A function returning all of the above values in one foul swoop (performance)
template <typename V, typename I> SimplePropertySet<string, V> allDispersions(const Vector<V,I>& x);

////////////////////////////////////////////////////////////////////////////////////////////////


// Moments, Skewness and Kurtosis

// The rth moment
template <typename V, typename I> V rthMoment(const Vector<V,I>& x, const I& r);

// The rth moment about the Mean m(r)
template <typename V, typename I> V rthMomentMean(const Vector<V,I>& x, const I& r);
template <typename V, typename I> V rthMomentMean(const Vector<V,I>& x, const Vector<V,I>& freq,
											const I& r);

// The rth moment about an origin A
template <typename V, typename I> V rthMoment(const Vector<V,I>& x, const I& r, const V& A);

// The rth moment about an origin A and with frequencies of each element in vector
template <typename V, typename I> V rthMoment(const Vector<V,I>& x, const Vector<V,I>& freq, 
										const I& r, const V& A);

// Mode: either the middle element or the mean of the two middle elements 
template <typename V, typename I> V median(const Vector<V,I>& x);

// Number of occurrences of value d in vector x
template <typename V, typename I> I occurs(const Vector<V,I>& x, const V& d);

// The element in x that occurs with the greatest frequency
template <typename V, typename I> V mode(const Vector<V,I>& x);

template <typename V, typename I> V skewness(const Vector<V,I>& x);


////////////////////////////////////////////////////////////////////////////////////////////////////

// Extremum operations on vectors

template <typename V, typename I> V maxValue(const Vector<V,I>& x);
template <typename V, typename I> V minValue(const Vector<V,I>& x);

// Max and min of the absolute values
template <typename V, typename I> V maxAbsValue(const Vector<V,I>& x);
template <typename V, typename I> V minAbsValue(const Vector<V,I>& x);

// Index of max and min values 
template <typename V, typename I> I indexMaxValue(const Vector<V,I>& x);
template <typename V, typename I> V indexMinValue(const Vector<V,I>& x);

template <typename V, typename I> I indexMaxAbsValue(const Vector<V,I>& x);
template <typename V, typename I> V indexMinAbsValue(const Vector<V,I>& x);

// Vector-vector extremum (difference of two vectors)
template <typename V, typename I> V maxValue(const Vector<V,I>& vectorA, const Vector<V,I>& vectorB);
template <typename V, typename I> V minValue(const Vector<V,I>& vectorA, const Vector<V,I>& vectorB);

template <typename V, typename I> V maxAbsValue(const Vector<V,I>& vectorA, const Vector<V,I>& vectorB);
template <typename V, typename I> V minAbsValue(const Vector<V,I>& vectorA, const Vector<V,I>& vectorB);

///////////////////////////////////////////////////////////////////////////////////////////////////////

// Vector and matrix norms

template <typename V, typename I> V innerProduct(const Vector<V,I>& vectorA, const Vector<V,I>& vectorB);
template <typename V, typename I> V l1Norm(const Vector<V,I>& x);
template <typename V, typename I> V l2Norm(const Vector<V,I>& x);		// Euclidean norm
template <typename V, typename I> V lpNorm(const Vector<V,I>& x, const I& p);		
template <typename V, typename I> V lInfinityNorm(const Vector<V,I>& x);	// L infinity norm

template <typename V, typename I> SimplePropertySet<string, V> allNorms(const Vector<V,I>& x);

// Same vector morms as above except for the difference of two vectors
template <typename V, typename I> V l1Norm(const Vector<V,I>& vectorA, const Vector<V,I>& vectorB);
template <typename V, typename I> V l2Norm(const Vector<V,I>& vectorA, const Vector<V,I>& vectorB);		// Euclidean norm
template <typename V, typename I> V lpNorm(const Vector<V,I>& vectorA, const Vector<V,I>& vectorB, const I& p);		
template <typename V, typename I> V lInfinityNorm(const Vector<V,I>& vectorA, const Vector<V,I>& vectorB);	// L infinity norm

template <typename V, typename I> SimplePropertySet<string, V> allNorms(const Vector<V,I>& vectorA, const Vector<V,I>& vectorB);


////////////////////////////////////////////////////////////////////////////////////////////////////////



///////////////////////////////////////////////////////////////////////////////////////////////////
// Functions for Operations Research and Numerical Linear Algebra

// Comparing vectors with each other

// Are all elements of a vector positive?
template <typename V, typename I> bool positive(const Vector<V,I>& x);
template <typename V, typename I> bool negative(const Vector<V,I>& x);


// Is v1 < v2? etc. 
template <typename V, typename I> bool operator < (const Vector<V,I>& v1, const Vector<V,I>& v2);
template <typename V, typename I> bool operator <= (const Vector<V,I>& v1, const Vector<V,I>& v2);
template <typename V, typename I> bool operator > (const Vector<V,I>& v1, const Vector<V,I>& v2);
template <typename V, typename I> bool operator >= (const Vector<V,I>& v1, const Vector<V,I>& v2);
template <typename V, typename I> bool operator == (const Vector<V,I>& v1, const Vector<V,I>& v2);
template <typename V, typename I> bool operator != (const Vector<V,I>& v1, const Vector<V,I>& v2);




// Utility functions

// Create an STL vector from a general Vector
template <typename V> vector<V> createSTLvector (const Vector<V,long>& myVector);
// Create a general Vector from an STL vector
template <typename V> Vector<V, long> createDatasimVector (const vector<V>& mySTLvector);

// Cumulative vector c[j] = c[j-1] + x[j]
template <typename V, typename I> Vector<V, I> cumulativeVector (const Vector<V, I>& x);

// First shall be last
template <typename V, typename I> Vector<V, I> reverse (const Vector<V,I>& x);


////////////// Useful and Basic Print Functions ////////////////////////////////////////////////////
template <typename V, typename I> void print(const Array<V,I>& v);
template <typename V, typename I> void print(const Vector<V,I>& v);
template <typename V, typename I> void print (Tensor<V, I>& tensor);

#endif