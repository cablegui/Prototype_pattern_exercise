// UniformGenerator.cpp
//
// A class hierarchy for generating random numbers, 
// vectors and matrices.
// 
// This hierarchy uses the Template Method Pattern and it
// delegates to a Strategy pattern for generating uniform
// random numbers.
//
// The solution is object-oriented and uses run-time polymorphic
// functions. In another chapter we use policy classes and templates.
//
// Last modifucation dates:
//
//	2008-3-6 DD kick off
//  2008-10-16 DD new functionality
//
// (C) Datasim Education BV 2008
//

// Remembering to define _CRT_RAND_S prior to inclusion statement.


#include "UniformGenerator.hpp"

UniformGenerator::UniformGenerator()
{
}

	

// Getting random structures (Template Method pattern)
Vector<double, long> UniformGenerator::getUniformVector(long N, double A, double B)
{ // Invariant part

	Vector<double, long> vec(N);

//#pragma omp parallel for shared(A, B)
	for(long i=vec.MinIndex(); i<=vec.MaxIndex();  ++i)
	{
		vec[i] = A + (B-A)* getUniform(); // Variant part
	}
	
	return vec;
}

Vector<pair<double,double>, long> UniformGenerator::getUniformVectorPairs(long N, double A, double B)	// (Pairs of U(0,1))*
{ // Generate N pairs of uniform numbers

	Vector<double, long> basisArray = getUniformVector(2 * N, A, B);

	Vector<pair <double, double>, long > result (N);
	
	long i =  basisArray.MinIndex();
	//#pragma omp parallel for private(i)does not work with var i
	for (long j = result.MinIndex(); j < result.MaxIndex(); ++j)
	{

		result[j].first = basisArray[i];
		result[j].second = basisArray[i + 1];
		i+= 2;

	}

	return result;
}

TerribleRandGenerator::TerribleRandGenerator()
{
		factor = 1.0 + double(RAND_MAX); //RAND_MAX = 32767
}


void TerribleRandGenerator::init(long Seed_)
{
	// Call this function ONCE ONCE ONCE before calling the other 'generator' functions

	srand((unsigned) time (0));

}



// Implement (variant) hook function
double TerribleRandGenerator::getUniform() 
{

	return  double(rand())/factor;
}

CRandGenerator::CRandGenerator()
{
		factor = 1.0 + double(RAND_MAX);
}


void CRandGenerator::init(long Seed_)
{
	// Call this function ONCE ONCE ONCE before calling the other 'generator' functions

	srand((unsigned) time (0));

}



// Implement (variant) hook function
double CRandGenerator::getUniform() 
{

	return  double(rand())/factor;
}

MSSecureRandGenerator::MSSecureRandGenerator()
{
	max = 1.0;
}


void MSSecureRandGenerator::init(long Seed_)
{
	
}

#define _CRT_RAND_S		

// Implement (variant) hook function
double MSSecureRandGenerator::getUniform()
{
	
			// does not compile
			/*errno_t err = rand_s( &number );
			if (err != 0) // failed
			{
				U1 = .9999999; // error
			}*/
        
			U1 = (double)number / (double)UINT_MAX * max;

			return U1;
}
