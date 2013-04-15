// NormalGenerator.cpp
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
//  2009-5-16 DD generate fixed arrays of normal variates
//	2009-6-29 DD Boost Normal generator
//
// (C) Datasim Education BV 2008-2009
//

#include "NormalGenerator.hpp"
#include <cmath>

NormalGenerator::NormalGenerator()
{
	ug = 0;
}

NormalGenerator::NormalGenerator(UniformGenerator& uniformGen)
{
	ug = &uniformGen;
}

// Getting random structures (Template Method Pattern)
Vector<double, long> NormalGenerator::getNormalVector(long N)
{ // Invariant part

	Vector<double, long> vec(N);

	for(long i=vec.MinIndex(); i<=vec.MaxIndex();  ++i)
	{
			// OLD WAY
			//BoxMuller(N1, N2);
			//PolarMarsaglia(N1, N2);


			vec[i] = getNormal();
	}
	
	return vec;
}

template <long N>
		VectorSpace<double, N> NormalGenerator::getNormalVectorSpace()	
{ // Invariant part

	VectorSpace<double, N> vec;

	for(long i=vec.MinIndex(); i<=vec.MaxIndex();  ++i)
	{
		vec[i] = getNormal();
	}
	
	return vec;
}

NumericMatrix<double, long> NormalGenerator::getNormalMatrix(long N, long M) 
{ // Invariant part

		NumericMatrix<double, long> result(N, M);

		for(long i=result.MinRowIndex(); i<= result.MaxRowIndex(); ++i)
		{
			for(long j=result.MinColumnIndex(); j<= result.MaxColumnIndex(); ++j)
			{
				result(i,j) = getNormal();
			}
		}
		return result;
}

PolarMarsaglia::PolarMarsaglia(UniformGenerator& uniformGen):  NormalGenerator(uniformGen)
{

		
}



// Implement (variant) hook function
double PolarMarsaglia::getNormal() 
{
		do
		{
			        
			U1 = ug->getUniform();
			U2 = ug->getUniform();

			V1 = 2.0 * U1 - 1;	// Uniform (-1,1) random variables
			V2 = 2.0 * U2 - 1;
		
			W = V1*V1 + V2*V2;
			
		}while( W > 1.0 );
		
		double W_function = sqrt( - 2.0 * log(W) / W );
		
		N1 = V1 * W_function;
		N2 = V2 * W_function;

		return N1;
}


BoxMuller::BoxMuller(UniformGenerator& uniformGen) :  NormalGenerator(uniformGen), tpi(2.0 * 3.1415)
{
}


// Implement (variant) hook function
double BoxMuller::getNormal() 
{

	/*	U1 = ug->getUniform();
		U2 = ug->getUniform();
		W = sqrt( -2.0 * log(U1));
		
		N1 = W * cos(tpi * U2);
		N2 = W * sin(tpi * U2);

		return N1;*/
		
	// Temp
		double U1, U2, V1, V2;
		do
		{
			        
			U1 = ug->getUniform();
			U2 = ug->getUniform();

			V1 = 2.0 * U1 - 1;	// Uniform (-1,1) random variables
			V2 = 2.0 * U2 - 1;
		
			W = V1*V1 + V2*V2;
			
		}while( W > 1.0 );
		
		double W_function = sqrt( - 2.0 * log(W) / W );
		
		N1 = V1 * W_function;
		N2 = V2 * W_function;

		return N1;

}

BoostNormal::BoostNormal() : NormalGenerator ()
{
	rng = boost::lagged_fibonacci607();
	nor = boost::normal_distribution<>(0,1);
	myRandom = new boost::variate_generator<boost::lagged_fibonacci607&, boost::normal_distribution<> >
			(rng, nor);

}


// Implement (variant) hook function
double BoostNormal::getNormal() 
{
	return (*myRandom)();
}


BoostNormal::~BoostNormal() 
{

	delete myRandom;
}



Tocher::Tocher(UniformGenerator& uniformGen):  NormalGenerator(uniformGen), magicNumber(sqrt(3.1415/8.0))
{

}


// Implement (variant) hook function
double Tocher::getNormal() 
{
        
		U1 = ug->getUniform();
		U2 = ug->getUniform();

		X = magicNumber * log((1.0 + U1)/ (1.0 - U2));

		if (U2 <= 0.5)
		{
			Z = - X;
		}
		else
		{	Z = X;
		}

		return Z;

}


NormalFromUniform12::NormalFromUniform12(UniformGenerator& uniformGen) :  NormalGenerator(uniformGen)
{

}

// Implement (variant) hook function
double NormalFromUniform12::getNormal() 
{
	// Generate a N(0,1)r.v. based on an array of U(0,1)
	// Consequence of the Central Limit Theorem

	Vector<double, long> UArr = ug->getUniformVector(12, 0,1);
	
	for (long j = UArr.MinIndex(); j <= UArr.MaxIndex(); ++j)
	{
		Z += UArr[j];
	}
	
	Z -= 6.0;

	return Z;

}

