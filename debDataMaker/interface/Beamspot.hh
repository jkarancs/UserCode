#ifndef SusyAnalysis_debDataMaker_Beamspot_hh_
#define SusyAnalysis_debDataMaker_Beamspot_hh_
// -*- C++ -*-
//
// Package:    debDataMaker
// Class:      Beamspot
// 
/**\class Beamspot Beamspot.hh SusyAnalysis/debDataMaker/interface/Beamspot.hh

 Description: 

        Provided by Anita or Attila:
	"The beam spot is the luminous region produced by the collisions of 
	proton beams. The algorithm used to calculated the transverse beam 
	position is the so called d0-phi algorithm. This is a robust and fast 
	fit which just needs 1000 good tracks to reach micron precision. 
	Using a Log-Likelihood fit, the beam width can be extracted using 
	20000 good tracks. A more detail description can be found in the CMS 
	Note 2007/021. 

	Luminosity:     L = (f*n*N1*N2) / A

		f : 	the revolution frequency
		n : 	the number of bunches in one beam in the storage ring
	   N1 & N2: 	the number of particles in each bunch
		A : 	the cross section of the beam"

 Implementation:

   !!!! See usage of inherited functions in Container.hh source code !!!!

   The following fuctions should be overloaded here according to the exact 
   definition of D in Container<D> :

      int passed(std::string selection,unsigned int i) (virtual):
         returns the result of selection. The selections are implemented in 
	 this function.

      void calculate(?) (virtual):
         calculates values that depend on other data models

*/
//
// Original Author:  Viktor VESZPREMI
//         Created:  Tue Aug 3 12:21:11 CET 2010
// $Id$
//
//
//-----------------------------------------------------------------------------

#include "SusyAnalysis/debDataMaker/interface/VContainer.hh"
#include "SusyAnalysis/debDataMaker/interface/BeamspotData.hh"

namespace deb {

//----------------------------- Class Definition ------------------------------

class Beamspot : public VContainer<BeamspotData> { 
 public:
  Beamspot(std::string name="") : VContainer<BeamspotData>(name, 1) { }
  ~Beamspot() { }

  inline BeamspotData& beamspot(size_t i) { return *(*this)(i); } 

  void calculate () { }

  // This is an event level quantity, should be no passed or select functions
 private:
  using VContainer<BeamspotData>::passed;
  using VContainer<BeamspotData>::select;

};

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

}
#endif
