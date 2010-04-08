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
// $Id: Histogram.hh,v 1.5 2010/03/28 16:21:43 veszpv Exp $
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
  // Copy constructor - creates "this" histo in the current TDirectory
  //
  //Histogram(const Histogram<H> &h) : H(h) { *this=h; }
  Histogram(const Histogram<H> &h) { init(); *this=h; }

  //
  // TH1 constructors
  //
  Histogram(const char* name, const char* title, Int_t nbinsx, Double_t xlow, 
	    Double_t xup) : H(name, title, nbinsx, xlow, xup) { init(); };

  Histogram(const char *name, const char *title, Int_t nbins, 
	    const Float_t *xbins) : H(name, title, nbins, xbins) { init(); };

  Histogram(const char *name, const char *title, Int_t nbins, 
	    const Double_t *xbins) : H(name, title, nbins, xbins) { init(); };

  // New types for TH1:
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

  // New types of TH2:
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
  H* num_;                              // the numerator if efficiency is set
  H* den_;                              // the denominator if efficiency is set
  std::string legend_;                  // legend of this histogram when drawn
  std::string legendHead_;              // head on the legend (category)
  void init() {
    num_=NULL;
    den_=NULL;
    legend_="";
    legendHead_="";
  }
  std::map<std::string,int> auxIndex_;
  std::vector<H> auxVector_;


  // Creates the clones in the current TDirectory
  inline H* makeCloneInGDirectory(H* target, std::string newname="") {
    H* duplicate=NULL;
    if (target!=NULL) duplicate = new H(*target);
    if (duplicate!=NULL && newname!="") duplicate->SetName(newname.c_str());
    return duplicate;
  }

 protected:
  std::vector<std::string> getNameTitle(char *nameTitle) {
  // In format: name[!legend[!legend head]][;title[;Xlabel[;Ylabel[;Zlabel]]]]
  // Returns strings: name, title (containing axis labels in ROOT format)
  // Set variables: legend_, legendHead_
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
  Histogram<H>& operator= (const Histogram<H> &h) {
    * dynamic_cast<H*>(this) = dynamic_cast<const H&>(h);
    if (num_!=NULL) {
      if (h.num()!=NULL) {
	*num_ = *h.num();
      } else {
	delete num_;
	num_=NULL;
      }
    } else {
      num_ = makeCloneInGDirectory(h.num());
    }
    if (den_!=NULL) {
      if (h.den()!=NULL) {
	*den_ = *h.den();
      } else {
	delete den_;
	den_=NULL;
      }
    } else {
      den_ = makeCloneInGDirectory(h.den());
    }
    legend_ = h.legend_;
    legendHead_ = h.legendHead_;
    auxIndex_ = h.auxIndex_;
    auxVector_ = h.auxVector_;
    return *this; 
  }

  void        setLabel(std::string, std::string, ...);  
  std::string getLabel(std::string, std::string, ...);
  void        efficiency();

  H*          num() const { return num_; }
  H*          den() const { return den_; }
  H*          ptr(std::string ext) {
    if (ext==".num") return num();
    else if (ext==".den") return den();
    return this;
  }

  // Transient auxiliary copies of this histo, alway stored in memory
  //
  H* addAux(std::string key) {
    H* h=aux(key);
    if (h!=NULL) return h;
    auxVector_.push_back(dynamic_cast<H&>(*this));
    int i=auxVector_.size()-1;
    auxIndex_[key]=i;
    auxVector_[i].SetDirectory(0);
    key.insert(0, "_");
    auxVector_[i].SetName(key.insert(0, auxVector_[i].GetName()).c_str());
    return &(auxVector_[i]);
  }
  //std::map<std::string,H>& auxIndex() { return auxIndex_; }
  int auxIndex(std::string key) {
    typename std::map<std::string,int>::const_iterator it=auxIndex_.find(key);
    return (it!=auxIndex_.end()) ? it->second : -1;
  }
  //std::vector<H>& auxVector() { return auxVector_; }
  H* aux(int i) {
    return (i>=0 && i<int(auxVector_.size())) ? &(auxVector_[i]) : NULL; 
  }
  H* aux(std::string key) { return aux(auxIndex(key)); }
  //
  //


  std::string getExtensions() { return std::string(".num .den"); }
  int         getExtLen() { return 4; }

  void        setLegend(std::string legend, std::string legendHead="") { 
    legend_=legend; 
    legendHead_=legendHead;
  }
  std::string getLegend() { return legend_; }
  void        setLegendHead(std::string legendHead) { legendHead_=legendHead; }
  std::string getLegendHead() { return legendHead_; }
  void        setDirectory(TDirectory *dir=0);
  Int_t       Write(const char*, Int_t, Int_t);
  int         load(std::string name="", TDirectory *dir=NULL);
  void        print();
  void        setStyle(std::string style) { };
  void        SetName(const char* name);
  void        setName(std::string name) { this->SetName(name.c_str()); }

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

  if (num_!=NULL && den_!=NULL ) { // && den_->Integral()!=0.) {
    this->Divide(num_, den_, 1., 1., "B");
    return;
  }

  this->Sumw2();

  if (num_==NULL) {
    std::ostringstream name_num;
    name_num << this->GetName() << "_num";
    num_ = makeCloneInGDirectory(this, name_num.str()); 
    // Move the new histo into the same directory as "this" is located
    if (num_!=NULL) num_->SetDirectory(this->GetDirectory());
  }

  if (den_==NULL) {
    std::ostringstream name_den;
    name_den << this->GetName() << "_den";
    den_ = makeCloneInGDirectory(this, name_den.str());
    // Move the new histo into the same directory as "this" is located
    if (den_!=NULL) den_->SetDirectory(this->GetDirectory());
  }

}


template <class H> 
void Histogram<H>::setDirectory(TDirectory *dir) {
  this->SetDirectory(dir);
  if (num_!=NULL) num_->SetDirectory(dir);
  if (den_!=NULL) den_->SetDirectory(dir);
}
 

template <class H> 
Int_t Histogram<H>::Write(const char* name = 0, Int_t option = 0, 
			  Int_t bufsize = 0) {
  if (num_!=NULL) {
    std::string name_num=num_->GetName();
    if (name!=NULL) {
      name_num=name;
      name_num+="_num";
    }
    num_->Write(name_num.c_str(), option, bufsize);
  }
  if (den_!=NULL) {
    std::string name_den=den_->GetName();
    if (name!=NULL) {
      name_den=name;
      name_den+="_den";
    }
    den_->Write(name_den.c_str(), option, bufsize);
  }
  return H::Write(name, option, bufsize);
}


template <class H>
int Histogram<H>::load(std::string namecycle, TDirectory* dir) {

  if (namecycle=="") namecycle=this->GetName();
  if (dir==NULL) dir=gDirectory;
  H* h=NULL;

  h = (H*) dir->GetObjectChecked(namecycle.c_str(), this->IsA());
  if (h!=NULL) {
    (*(H*)this)=*h;
    delete h;
    std::cout<<"Loaded "<<this->GetName()<<std::endl;
  }

  std::string num=namecycle;
  size_t pos=num.find_first_of(";"); // the cyclenumber part
  num.insert((pos!=std::string::npos) ? pos : num.length(), "_num");
  h=NULL;

  h = (H*) dir->GetObjectChecked(num.c_str(), this->IsA());
  if (h!=NULL) {
    if (num_==NULL) {
      num_ = h;
    } else {
      *num_=*h;
      delete h;
    }
    num_->SetDirectory(this->GetDirectory());
    std::cout<<"Loaded "<<num_->GetName()<<std::endl;
  }

  std::string den=namecycle;
  pos=den.find_first_of(";"); // the cyclenumber part
  den.insert((pos!=std::string::npos) ? pos : den.length(), "_den");
  h=NULL;

  h = (H*) dir->GetObjectChecked(den.c_str(), this->IsA());
  if (h!=NULL) {
    if (den_==NULL) {
      den_ = h;
    } else {
      *den_=*h;
      delete h;
    }
    den_->SetDirectory(this->GetDirectory());
    std::cout<<"Loaded "<<den_->GetName()<<std::endl;
  }
  return 0;
}


template <class H>
void Histogram<H>::print() {
  std::cout<<"Histogram: "<<this->GetName()<<" in ";
  if (this->GetDirectory()!=0) {
    this->GetDirectory()->pwd();
  } else {
    std::cout<<"memory\n";
  }
  if (num_!=NULL) {
    std::cout<<"\t"<<num_->GetName()<<" in ";
    if (num_->GetDirectory()!=0) {
      num_->GetDirectory()->pwd();
    } else {
      std::cout<<"memory\n";
    }
  }
  if (den_!=NULL) {
    std::cout<<"\t"<<den_->GetName()<<" in ";
    if (den_->GetDirectory()!=0) {
      den_->GetDirectory()->pwd();
    } else {
      std::cout<<"memory\n";
    }
  }
}


template <class H>
void Histogram<H>::SetName(const char* name) {
  //std::cout<<"Naming "<<this->GetName()<<" to "<<name<<std::endl;
  H::SetName(name);
  if (num_!=NULL) {
    std::string name_num=this->GetName();
    name_num+="_num";
    //std::cout<<"Naming "<<num_->GetName()<<" to "<<name_num<<std::endl;
    num_->SetName(name_num.c_str());
  }
  if (den_!=NULL) {
    std::string name_den=this->GetName();
    name_den+="_den";
    //std::cout<<"Naming "<<den_->GetName()<<" to "<<name_den<<std::endl;
    den_->SetName(name_den.c_str());
  }
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
