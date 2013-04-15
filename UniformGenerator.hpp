// UniformGenerator.hpp
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

#ifndef UniformGenerator_HPP
#define UniformGenerator_HPP


#include "UtilitiesDJD/VectorsAndMatrices/Vector.cpp"
#include "UtilitiesDJD/VectorsAndMatrices/NumericMatrix.cpp"

//#define _CRT_RAND_S		


#include <time.h> // For seeds
#include <stdlib.h>
#include <stdio.h>
#include <limits.h>

using namespace std;

class UniformGenerator
{
protected:
	double a, b;	// The interval
public:
	UniformGenerator();
	UniformGenerator(double A, double B);

	// Initialisation and setting the seed
	virtual void init(long Seed_) = 0;

	// Getting random structures (Template Method pattern)
	virtual double getUniform() = 0;	// Get a number in range (0,1), variant
	Vector<double, long> getUniformVector(long N, double A=0.0, double B = 1.0);	// Invariant part
	Vector<pair<double,double>, long> getUniformVectorPairs(long N, double A, double B);	// (Pairs of U(0,1))*

};

class TerribleRandGenerator : public UniformGenerator
{ // Based on the infamous rand()

private:
	double factor;

public:
	TerribleRandGenerator();
	TerribleRandGenerator(double A, double B);

	// Initialise the seed, among others
	void init(long Seed_);

	// Implement (variant) hook function
	double getUniform();

};

class CRandGenerator : public UniformGenerator
{ // Based on the infamous rand()

private:
	double factor;

public:
	CRandGenerator();
	CRandGenerator(double A, double B);

	// Initialise the seed, among others
	void init(long Seed_);

	// Implement (variant) hook function
	double getUniform();

};

class MSSecureRandGenerator : public UniformGenerator
{ // Based on the Microsoft .NET rand_s() function

private:
		//errno_t err;
		unsigned int number; 
		double max; // ==> in U(0, max)
		double U1;
public:
	MSSecureRandGenerator();
	MSSecureRandGenerator(double A, double B);

	// Initialise the seed, among others
	void init(long Seed_);

	// Implement (variant) hook function
	double getUniform();

};

#endif
