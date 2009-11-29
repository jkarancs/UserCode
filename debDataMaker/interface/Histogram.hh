#ifndef debDataMaker_Histogram_hh_
#define debDataMaker_Histogram_hh_
// -*- C++ -*-
//
// Package:    debDataMaker
// Class:      Histogram
// 
/**\class Histogram Histogram.hh debDataMaker/interface/Histogram.hh

 Description: Extension to root TH1 and derived classes

 Implementation:
  - TH1 constructors are available to ensure backward compatibility

  - New constructor format: same as TH1 constructors, but name/title/etc
  string is the last parameter instead of being the first, which makes it
  possible to use variable number of parameters following the format of  
  printf("format string", variables...)
  
  Format defines names and lables in the histogram such as:

   <name>[!<legend>[!<legend head>]][;<title>[;<Xlabel>[;<Ylabel>[;<Zlabel>]]]]

  Note: - name and legend define individual objects linked to each other, these
          are separated by "!"
	- title, axis labels are parameters of the histogram defined by name,
          these are separated by ";"
   

*/
//
// Original Author:  Viktor VESZPREMI
//         Created:  Wed Oct 25 20:57:26 CET 2009
// $Id: Histogram.hh,v 1.1 2009/11/18 14:10:51 veszpv Exp $
//
//
//-----------------------------------------------------------------------------

#include <iostream>
#include <fstream>

namespace deb {

//----------------------------- Class Definition ------------------------------

template<class H> class Histogram : public H {
 public:
  Histogram() : H() { init(); };

  //
  // Copy constructor
  //
  Histogram(const Histogram<H> &h) : H(h) {
    num_ = (h.num()!=NULL) ? (H*)h.num()->Clone() : NULL;
    den_ = (h.den()!=NULL) ? (H*)h.den()->Clone() : NULL;
    legend_ = h.legend_;
    legendHead_ = h.legendHead_;
  };

  //
  // TH1 constructors
  //
  Histogram(const char* name, const char* title, Int_t nbinsx, Double_t xlow, 
	    Double_t xup) : H(name, title, nbinsx, xlow, xup) { init(); };

  Histogram(const char *name, const char *title, Int_t nbins, 
	    const Float_t *xbins) : H(name, title, nbins, xbins) { init(); };

  Histogram(const char *name, const char *title, Int_t nbins, 
	    const Double_t *xbins) : H(name, title, nbins, xbins) { init(); };

  // New types:
  // In format: name[!legend[!legend head]][;title[;Xlabel[;Ylabel[;Zlabel]]]]
  Histogram(Int_t nbinsx, Double_t xlow, Double_t xup, std::string format,...);
  Histogram(Int_t nbins, const Float_t *xbins, std::string format,...);
  Histogram(Int_t nbins, const Double_t *xbins, std::string format,...);


  //
  // TH2 constructors
  //
  Histogram(const char *name, const char *title, Int_t nbinsx, Double_t xlow,
	    Double_t xup, Int_t nbinsy, Double_t ylow, Double_t yup) :
    H(name, title, nbinsx, xlow, xup, nbinsy, ylow, yup) { init(); };

  Histogram(const char *name, const char *title, Int_t nbinsx, 
	    const Double_t *xbins, Int_t nbinsy, Double_t ylow, Double_t yup) :
    H(name, title, nbinsx, xbins, nbinsy, ylow, yup) { init(); };

  Histogram(const char *name, const char *title, Int_t nbinsx, Double_t xlow,
	    Double_t xup, Int_t nbinsy, const Double_t *ybins) :
    H(name, title, nbinsx, xlow, xup, nbinsy, ybins) { init(); };

  Histogram(const char *name, const char *title, Int_t nbinsx, 
	    const Double_t *xbins, Int_t nbinsy, const Double_t *ybins) : 
    H(name, title, nbinsx, xbins, nbinsy, ybins) { init(); };

  Histogram(const char *name, const char *title, Int_t nbinsx, 
	    const Float_t *xbins , Int_t nbinsy, const Float_t *ybins) :
    H(name, title, nbinsx, xbins, nbinsy, ybins) { init(); };

  // New types:
  // In format: name[!legend[!legend head]][;title[;Xlabel[;Ylabel[;Zlabel]]]]
  Histogram(Int_t nbinsx, Double_t xlow, Double_t xup, 
	    Int_t nbinsy, Double_t ylow, Double_t yup, std::string format,...);

  Histogram(Int_t nbinsx, const Double_t *xbins, 
	    Int_t nbinsy, Double_t ylow, Double_t yup, std::string format,...);

  Histogram(Int_t nbinsx, Double_t xlow, Double_t xup, 
	    Int_t nbinsy, const Double_t *ybins, std::string format,...);

  Histogram(Int_t nbinsx, const Double_t *xbins, 
	    Int_t nbinsy, const Double_t *ybins, std::string format,...);

  Histogram(Int_t nbinsx, const Float_t *xbins, 
	    Int_t nbinsy, const Float_t *ybins, std::string format,...);

  ~Histogram() {
    if (num_!=NULL) delete num_;
    if (den_!=NULL) delete den_;
  }

 private:
  H* num_;
  H* den_;
  std::string legend_;
  std::string legendHead_;
  void init() {
    num_=NULL;
    den_=NULL;
    legend_="";
    legendHead_="";
  }


 protected:
  std::vector<std::string> getNameTitle(char *nameTitle) {
    std::cout<<"getNameTitle(\""<<nameTitle<<"\"\n";
    std::string name=nameTitle;
    std::string title="";
    size_t posTitle=name.find_first_of(";");
    if (posTitle!=std::string::npos) {
      title=name.substr(posTitle+1);
      name.erase(posTitle);
    }
    size_t posLegends=name.find_first_of("!");
    if (posLegends!=std::string::npos) {
      legend_=name.substr(posLegends+1);
      name.erase(posLegends);
      posLegends=legend_.find_first_of("!");
      if (posLegends!=std::string::npos) {
	legendHead_=legend_.substr(posLegends+1);
	legend_.erase(posLegends);
      }
    }
    std::cout<<"name "<<name<<" title "<<title<<std::endl;
    std::cout<<"legend "<<legend_<<" head "<<legendHead_<<std::endl;
    std::vector<std::string> ret;
    ret.push_back(name);
    ret.push_back(title);
    return ret;
  }

  void fillX(H* h, Double_t x, Double_t w);
  void fillY(H* h, Double_t y, Double_t w);


 public:
  void        setLabel(std::string, std::string, ...);  
  std::string getLabel(std::string, std::string, ...);
  void        efficiency();
  H*          num() const { return num_; }
  H*          den() const { return den_; }
  void        setLegend(std::string legend, std::string legendHead="") { 
    legend_=legend; 
    legendHead_=legendHead;
  }
  std::string getLegend() { return legend_; }
  void        setLegendHead(std::string legendHead) { legendHead_=legendHead; }
  std::string getLegendHead() { return legendHead_; }
  Int_t       Write(const char*, Int_t, Int_t);
  void        setStyle(std::string style) { };

  // Only for 2-D histograms
  // No safeguard when compiling with 1-D histograms. It just won't compile.
  void        fillX(Double_t x, Double_t w=1.)    { this->fillX(this, x, w); }
  void        fillY(Double_t y, Double_t w=1.)    { this->fillY(this, y, w); }
  void        fillNumX(Double_t x, Double_t w=1.) { this->fillX(num_, x, w); }
  void        fillNumY(Double_t y, Double_t w=1.) { this->fillY(num_, y, w); }
  void        fillDenX(Double_t x, Double_t w=1.) { this->fillX(den_, x, w); }
  void        fillDenY(Double_t y, Double_t w=1.) { this->fillY(den_, y, w); }

};

//----------------------------- TH1 Constructors ------------------------------

template<class H>
Histogram<H>::Histogram(Int_t nbinsx, Double_t xlow, Double_t xup, 
			std::string format,...) :
  H("", "", nbinsx, xlow, xup) {

  va_list argList;
  va_start(argList, format);
  char s[10000];
  vsprintf(s, format.data(), argList);
  va_end(argList);
  
  std::vector<std::string> nameTitle=getNameTitle(s);
  this->SetNameTitle(nameTitle[0].data(), nameTitle[1].data());
  init();
}


template<class H>
Histogram<H>::Histogram(Int_t nbins, const Float_t *xbins, 
			std::string format,...) :
  H("", "", nbins, xbins) {

  va_list argList;
  va_start(argList, format);
  char s[10000];
  vsprintf(s, format.data(), argList);
  va_end(argList);
  
  std::vector<std::string> nameTitle=getNameTitle(s);
  this->SetNameTitle(nameTitle[0].data(), nameTitle[1].data());
  init();
}


template<class H>
Histogram<H>::Histogram(Int_t nbins, const Double_t *xbins, 
			std::string format,...) : 
  H("", "", nbins, xbins) {

  va_list argList;
  va_start(argList, format);
  char s[10000];
  vsprintf(s, format.data(), argList);
  va_end(argList);
  
  std::vector<std::string> nameTitle=getNameTitle(s);
  this->SetNameTitle(nameTitle[0].data(), nameTitle[1].data());
  init();
}


//----------------------------- TH2 Constructors ------------------------------

template<class H>
Histogram<H>::Histogram(Int_t nbinsx, Double_t xlow, Double_t xup, 
			Int_t nbinsy, Double_t ylow, Double_t yup, 
			std::string format,...) :
  H("", "", nbinsx, xlow, xup, nbinsy, ylow, yup) {

  va_list argList;
  va_start(argList, format);
  char s[10000];
  vsprintf(s, format.data(), argList);
  va_end(argList);
  
  std::vector<std::string> nameTitle=getNameTitle(s);
  this->SetNameTitle(nameTitle[0].data(), nameTitle[1].data());
  init();
}


template<class H>
Histogram<H>::Histogram(Int_t nbinsx, const Double_t *xbins, 
			Int_t nbinsy, Double_t ylow, Double_t yup, 
			std::string format,...) :
  H("", "", nbinsx, xbins, nbinsy, ylow, yup) {

  va_list argList;
  va_start(argList, format);
  char s[10000];
  vsprintf(s, format.data(), argList);
  va_end(argList);
  
  std::vector<std::string> nameTitle=getNameTitle(s);
  this->SetNameTitle(nameTitle[0].data(), nameTitle[1].data());
  init(); 
}


template<class H>
Histogram<H>::Histogram(Int_t nbinsx, Double_t xlow, Double_t xup, 
			Int_t nbinsy, const Double_t *ybins, 
			std::string format,...) :
  H("", "", nbinsx, xlow, xup, nbinsy, ybins) {

  va_list argList;
  va_start(argList, format);
  char s[10000];
  vsprintf(s, format.data(), argList);
  va_end(argList);
  
  std::vector<std::string> nameTitle=getNameTitle(s);
  this->SetNameTitle(nameTitle[0].data(), nameTitle[1].data());
  init(); 
}


template<class H>
Histogram<H>::Histogram(Int_t nbinsx, const Double_t *xbins, 
			Int_t nbinsy, const Double_t *ybins, 
			std::string format,...) :
  H("", "", nbinsx, xbins, nbinsy, ybins) {

  va_list argList;
  va_start(argList, format);
  char s[10000];
  vsprintf(s, format.data(), argList);
  va_end(argList);
  
  std::vector<std::string> nameTitle=getNameTitle(s);
  this->SetNameTitle(nameTitle[0].data(), nameTitle[1].data());
  init(); 
}


template<class H>
Histogram<H>::Histogram(Int_t nbinsx, const Float_t *xbins, 
			Int_t nbinsy, const Float_t *ybins, 
			std::string format,...) :
  H("", "", nbinsx, xbins, nbinsy, ybins) {

  va_list argList;
  va_start(argList, format);
  char s[10000];
  vsprintf(s, format.data(), argList);
  va_end(argList);
  
  std::vector<std::string> nameTitle=getNameTitle(s);
  this->SetNameTitle(nameTitle[0].data(), nameTitle[1].data());
  init();
}


//-----------------------------------------------------------------------------

template <class H> 
void Histogram<H>::setLabel(std::string param, std::string value, ...) {
  va_list argList;
  va_start(argList, value);
  char s[10000];
  vsprintf(s, value.data(), argList);
  va_end(argList);
  value=s;
  
  if (param=="Name") this->SetName(value.data());
  if (param=="Title") this->SetTitle(value.data());
  if (param=="XTitle") this->SetXTitle(value.data());
  if (param=="YTitle") this->SetYTitle(value.data());
  if (param=="ZTitle") this->SetZTitle(value.data());
}


template <class H> 
std::string Histogram<H>::getLabel(std::string param, 
				   std::string value="", ...) {

  std::string ret="";
  if (param=="Name") ret=this->GetName();
  if (param=="Title") ret=this->GetTitle();
  if (param=="XTitle") ret=this->GetXaxis()->GetTitle();
  if (param=="YTitle") ret=this->GetYaxis()->GetTitle();
  if (param=="ZTitle") ret=this->GetZaxis()->GetTitle();
  if (ret=="" || value=="") return ret;

  size_t dollar=value.find("$");
  if (dollar!=std::string::npos) {
    value.replace(dollar, 1, ret);
  } else {
    return ret;
  }

  va_list argList;
  va_start(argList, value);
  char s[10000];
  vsprintf(s, value.data(), argList);
  va_end(argList);
  value=s;
  
  return value;
}


template <class H> 
void Histogram<H>::efficiency() {

  if (num_!=NULL && den_!=NULL && den_->Integral()!=0.) {
    std::string name=this->GetName();
    *(H*)this=*num_;
    this->SetName(name.data());
    this->Divide(den_);
    return;
  }

  if (num_==NULL) {
    std::ostringstream name_num;
    name_num << this->GetName() << "_num";
    num_=(H*)this->Clone(name_num.str().data());
    num_->Sumw2();
  }

  if (den_==NULL) {
    std::ostringstream name_den;
    name_den << this->GetName() << "_den";
    den_=(H*)this->Clone(name_den.str().data());
    den_->Sumw2();
  }

  this->Sumw2();

}


template <class H> 
Int_t Histogram<H>::Write(const char* name = 0, Int_t option = 0, 
			  Int_t bufsize = 0) {
  if (num_!=NULL) num_->Write();
  if (den_!=NULL) den_->Write();
  return H::Write(name, option, bufsize);
}


template <class H> 
void Histogram<H>::fillX(H* h, Double_t x, Double_t w=1.) {
  for (Int_t i=1; i<=h->GetNbinsY(); i++) {
    h->Fill(x, h->GetYaxis()->GetBinCenter(i), w);
  }
  h->Fill(x, h->GetYaxis()->GetBinLowEdge(1)*0.9999, w);
  h->Fill(x, h->GetYaxis()->GetBinUpEdge(h->GetNbinsY())*1.0001, w);
}


template <class H> 
void Histogram<H>::fillY(H* h, Double_t y, Double_t w=1.) {
  for (Int_t i=1; i<=h->GetNbinsX(); i++) {
    h->Fill(h->GetXaxis()->GetBinCenter(i), y, w);
  }
  h->Fill(h->GetXaxis()->GetBinLowEdge(1)*0.9999, y, w);
  h->Fill(h->GetXaxis()->GetBinUpEdge(h->GetNBinsX())*1.0001, y, w);  
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

}
#endif
