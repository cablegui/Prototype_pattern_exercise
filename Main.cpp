/*****************************************************************

Author:			Neville Andrade

Date:			3 Dec 2012

Description:	(Factory Method Pattern)
				This exercise has to do 
				with section 9.8.1 of the MC Book (and in particular Figure 9.9)
				where we model a class hierarchy for interest rate models 
				as well as factory classes for instantiation. 
				To this end, we direct you to Exercise 3 in section 9.10. There we
				describe the exercise in full.

				Here we need to implement the prototype pattern. 
				
******************************************************************/

// TestIrSde.cpp
//
// Testing 1-factor IR SDEs
//
// 2008-3-28 DD kick off
//
// (C) Datasim Education BV 2008

#include "UtilitiesDJD\IRModels\IrSdeFactory.hpp"
#include "UtilitiesDJD\Vectorsandmatrices\Vector.cpp"
#include "UtilitiesDJD\RNG\NormalGenerator.hpp"
#include "UtilitiesDJD\Vectorsandmatrices\ArrayMechanisms.cpp"
#include <iostream>

using namespace std;


Vector<double, long> Simulation(const IrSde& irsde, Vector<double, long> mesh)
{ // Simulate a short-rate using explicit Euler method

	long N = mesh.Size();

	Vector<double, long> result(N, mesh.MinIndex());

	// Step size
	double k = irsde.Interval().spread()/double(N - 1);
	double sk = sqrt(k);

	double rOld;

	// Generate array of normal random numbers
	TerribleRandGenerator myTerrible; // rand()
	NormalGenerator* myNormal = new BoxMuller(myTerrible);
	Vector<double, long> arr2 = myNormal->getNormalVector(N);
	
	//cout << endl << "Printing normal random numbers" << endl;

	//print(arr2);

	// Initial condition
	result[result.MinIndex()] = irsde.InitialCondition();

	for (long n = result.MinIndex()+1; n <= result.MaxIndex(); ++n)
	{
		rOld = result[n-1];
		result[n] = rOld + (irsde.calculateDrift(mesh[n], rOld) * k)
						+ (irsde.calculateDiffusion(mesh[n], rOld) * sk * arr2[n]);
	}

	delete myNormal;

	return result;
}


int main()
{
	// Choose your factory
	cout << "1. CIR, 2. Merton: "; int choice; cin >> choice;
	IrSdeFactory* myFactory = ChooseFactory(choice);

	double kappa = 0;


	IrSde* mySde = myFactory->CreateIrSde();
	IrSde* mySde2 = mySde->Clone();//->CreateIrSde();

	

	
	//mySde2->setkappa(cin >> kappa);

	//Here I need to create another SDE which clones mySde
	//IrSde* mySde2(mySde);

	// Now simulate a path using Euler method
	cout << "Number of sub-intervals: "; long N; cin >> N;
	Vector<double, long> myMesh = mySde->Interval().mesh(N);


	CIRSde *derivedPtr = dynamic_cast<CIRSde *> (mySde2);

	//Change kappa setting
	if (derivedPtr != 0)
	{
		double oldKappa = derivedPtr->getKappa();
		cout << "Old Kappa setting : " << oldKappa << endl;
		derivedPtr->setKappa();
		cout << "New Kappa setting : " << derivedPtr->getKappa() << endl;
	}

	// Do an Euler simulation with the current SDE
	Vector<double, long> result = Simulation(*mySde, myMesh);
	
	cout << endl << "Prining simulation 1 results" << endl;
	print(result);
	
	result = Simulation(*mySde2, myMesh);

	cout << endl << "Prining simulation 2 results" << endl;
	print(result);

	// Clean up
	delete mySde;
	delete mySde2;
	delete myFactory;

	return 0;
}