#ifndef SusyAnalysis_debDataMaker_CONST_hh_
#define SusyAnalysis_debDataMaker_CONST_hh_

  namespace deb{
  
    double const NOVAL_D=-9999.0;
    float const NOVAL_F=-9999.0;
    int const NOVAL_I=-9999;
    const char* const NOVAL_S="N/A";

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
