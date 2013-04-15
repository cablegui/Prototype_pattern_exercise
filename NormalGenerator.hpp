// NormalGenerator.hpp
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
// (C) Datasim Education BV 2008
//

#ifndef NormalGenerator_HPP
#define NormalGenerator_HPP

#include "UniformGenerator.hpp"
#include "UtilitiesDJD/VectorsAndMatrices/Vector.cpp"
#include "UtilitiesDJD/VectorsAndMatrices/NumericMatrix.cpp"
#include "UtilitiesDJD/CompileTimeVectorsAndMatrices/VectorSpace.cpp"

// boost
#include <boost/random.hpp>
#include <boost/random/mersenne_twister.hpp>
#include <boost/random/normal_distribution.hpp>
#include <boost/random/variate_generator.hpp>

class NormalGenerator
{
protected:

	UniformGenerator* ug;	// This is a strategy object

public:
	NormalGenerator();
	NormalGenerator(UniformGenerator& uniformGen);

	// Getting random structures (Template Method pattern)
	virtual double getNormal() = 0;										// Get a number in (0,1) variant
	Vector<double, long> getNormalVector(long N);						// Invariant part
	template <long N>
	VectorSpace<double, N> getNormalVectorSpace();						// Invariant part
	NumericMatrix<double, long> getNormalMatrix(long N, long M);		// Invariant part

};
class PolarMarsaglia : public NormalGenerator
{
private:

	double U1, U2;	// Uniform numbers
	double N1, N2;	// 2 Normal numbers as product of BM

	double V1, V2;
	double W, W_function;

public:
	PolarMarsaglia(UniformGenerator& uniformGen);

	// Implement (variant) hook function
	double getNormal();
};

class BoxMuller : public NormalGenerator
{
private:
	double U1, U2;	// Uniform numbers
	double N1, N2;	// 2 Normal numbers as product of BM

	double W;
	const double tpi;
public:
	BoxMuller(UniformGenerator& uniformGen);

	// Implement (variant) hook function
	double getNormal();
};

class BoostNormal : public NormalGenerator
{
private:

	boost::lagged_fibonacci607 rng;
	boost::normal_distribution<> nor;
//
	boost::variate_generator<boost::lagged_fibonacci607&, boost::normal_distribution<> >* myRandom;


public:
	BoostNormal();	// NB no uniform parameters

	// Implement (variant) hook function
	double getNormal();

	~BoostNormal();
};

class Tocher : public NormalGenerator
{ // 
private:
	double U1, U2;
	double X, Z;
	const double magicNumber;
public:
	Tocher(UniformGenerator& uniformGen);

	// Implement (variant) hook function
	double getNormal();
};

class NormalFromUniform12 : public NormalGenerator
{ // Generate a N(0,1)r.v. based on an array of U(0,1)
  // Consequence of the Central Limit Theorem
private:
	double Z;
public:
	NormalFromUniform12(UniformGenerator& uniformGen);

	// Implement (variant) hook function
	double getNormal();
};

#endif
