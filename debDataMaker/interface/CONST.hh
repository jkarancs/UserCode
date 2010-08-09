#ifndef SusyAnalysis_debDataMaker_CONST_hh_
#define SusyAnalysis_debDataMaker_CONST_hh_

//
// PROJECT OF THIS VERSION USED BY THE PREPROCESSOR !!!
//
#define DEB_CMSSW_VERSION 20209

// ----------------------------------------------------
//

#define DEB_CMSSW_VERSION_31X 31000
#define DEB_CMSSW_VERSION_2XX 20000

//#define DEB_DEBUG

  namespace deb{
  
    double const NOVAL_D=-9999.0;
    Double_t const NOVAL_D_t=-9999.0;
    float const NOVAL_F=-9999.0;
    int const NOVAL_I=-9999;
    unsigned int const NOVAL_i=9999;
    long const NOVAL_L=-9999;
    unsigned long const NOVAL_l=9999;
    const char* const NOVAL_S="N/A";


    template<class T> inline T        NOVAL() { return T();     }
    template<> inline double          NOVAL() { return NOVAL_D; }
    template<> inline float           NOVAL() { return NOVAL_F; }
    template<> inline int             NOVAL() { return NOVAL_I; }
    template<> inline unsigned int    NOVAL() { return NOVAL_i; }
    template<> inline long            NOVAL() { return NOVAL_L; }
    template<> inline unsigned long   NOVAL() { return NOVAL_l; }
    template<> inline const char*     NOVAL() { return NOVAL_S; }


    template<class T> inline T      NOVAL(T& t)             { return T();     }
    template<> inline double        NOVAL(double& t)        { return NOVAL_D; }
    template<> inline float         NOVAL(float& t)         { return NOVAL_F; }
    template<> inline int           NOVAL(int& t)           { return NOVAL_I; }
    template<> inline unsigned int  NOVAL(unsigned int& t)  { return NOVAL_i; }
    template<> inline long          NOVAL(long& t)          { return NOVAL_L; }
    template<> inline unsigned long NOVAL(unsigned long& t) { return NOVAL_l; }
    template<> inline const char*   NOVAL(const char*& t)   { return NOVAL_S; }


    int const PASS_VALIDITY=0;

    int const FROM_PAT=0;
    int const FROM_RECO=1;
    int const FROM_SIM=2;

    std::pair<char,std::pair<std::string,size_t> > _ROOTVariableTypes_[] = {
      std::pair<char,std::pair<std::string,size_t> >(
	 'F', std::pair<std::string,size_t>("Float_t", sizeof(Float_t))),
      std::pair<char,std::pair<std::string,size_t> >(
	 'D', std::pair<std::string,size_t>("Double_t", sizeof(Double_t))),
      std::pair<char,std::pair<std::string,size_t> >(
	 'I', std::pair<std::string,size_t>("Int_t", sizeof(Int_t))),
      std::pair<char,std::pair<std::string,size_t> >(
	 'L', std::pair<std::string,size_t>("Long_t", sizeof(Long_t))),
      std::pair<char,std::pair<std::string,size_t> >(
	 'i', std::pair<std::string,size_t>("UInt_t", sizeof(UInt_t))),
      std::pair<char,std::pair<std::string,size_t> >(
	 'l', std::pair<std::string,size_t>("ULong_t", sizeof(ULong_t)))
    };
    
   std::map<char,std::pair<std::string,size_t> > 
   ROOTVariableTypeMap(_ROOTVariableTypes_,
		       _ROOTVariableTypes_+
		       sizeof(_ROOTVariableTypes_)/
		       sizeof(_ROOTVariableTypes_[0]));


  }

#endif
