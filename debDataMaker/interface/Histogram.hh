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
// $Id: Histogram.hh,v 1.7 2010/04/09 10:35:30 veszpv Exp $
//
//
//-----------------------------------------------------------------------------

#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <vector>
#include <algorithm>
#include <math.h>

#include "TKey.h"
#include "TFormula.h"

#include "cxxabi.h"
#include <boost/regex.hpp>

#ifndef HISTOGRAM_DEBUG
#define HISTOGRAM_DEBUG 0
#endif

namespace deb {

template<class U, class V>
class rmap : public std::map<std::pair<U,U>,V> {
 public:
  typedef typename std::pair<U,U>                         Range;
  typedef typename std::map<std::pair<U,U>,V>             RmapBase;
  typedef typename std::map<std::pair<U,U>,V>::iterator   iterator;

  rmap(V default_value) : default_value_(default_value) { }
  rmap(const rmap& m) { *this=m; }
  ~rmap() { }

 private:
  std::string name;
  V default_value_;
  
  void order(U& u1, U& u2) { if (u1>u2) { U u(u2); u2=u1; u1=u; } }

 public:

  void set_default(V default_value) { default_value_=default_value; }

  rmap& operator=(const rmap& m){
    * dynamic_cast<RmapBase*>(this) = dynamic_cast<const RmapBase&>(m);
    default_value_=m.default_value_;
    return *this;
  }

  // The Range means (u1,u2], but if u1==u2, it means {u1}
  void insert(U u1, U u2, V v) {
    order(u1, u2);
    Range r(u1,u2);
    if (this->size()==0) RmapBase::insert(std::pair<Range,V>(r, v));
    iterator it=lower_bound(r);

    if (it->first.first==u1) return;
    if (it==this->end()) {
      if (u1>=this->rbegin()->first.second) {
	RmapBase::insert(std::pair<Range,V>(r, v));
	this->regularize();
      }
      return;
    }
    if (it==this->begin()) {
      if (u2<=it->first.first) {
	RmapBase::insert(std::pair<Range,V>(r, v));
	this->regularize();
      }
      return;
    }
    if (u2<=it->first.first) {
      it--;
      if (u1>=it->first.second) {
	RmapBase::insert(std::pair<Range,V>(r, v));
	this->regularize();
      }
    }
  }

  void insertn(int n,...) {
    va_list argList;
    va_start(argList, n);
    for (int i=0; i<n; i++) {
      U u1=va_arg(argList, U);
      U u2=va_arg(argList, U);
      V v=va_arg(argList, V);
      insert(u1, u2, v);
    }
    va_end(argList);
  }
  
  bool regularize() {
    bool changed=false;
    iterator it_end=this->end();
    it_end--;
    for (iterator it=this->begin(); it!=it_end; it++) {
      iterator it2=it;
      it2++;
      if (it->second==it2->second && it->first.second==it2->first.first) {
	Range rnew(it->first.first, it2->first.second);
	V v=it->second;
	this->erase(it2);
	this->erase(it);
	RmapBase::insert(std::pair<Range,V>(rnew, v));
	changed=true;
	break;
      }
    }
    if (changed) regularize();
    return changed;
  }
  
  V operator()(U u){
    iterator it=lower_bound(Range(u, 0));
    if (it->first.first==u) return it->second;
    if (it==this->begin()) return default_value_;
    it--;
    if (u<it->first.second) return it->second;
    return default_value_;
  }

  void print() {
    std::cout<<std::endl;
    if (this->size()==0) {
      std::cout<<" Default value: "<<default_value_<<"\n\n";
      return;
    }
    size_t count=0;
    iterator it=this->begin();
    for (; it!=this->end(); it++, count++) {
      std::cout << " " << count << ": ";
      if (it->first.first==it->first.second) {
	std::cout << "{" << it->first.first << "}";
      } else {
	std::cout << "[" << it->first.first << ", " << it->first.second << ")";
      }
      std::cout<< " -> " << it->second<<std::endl;
    }
    std::cout<<" Out-of-range value: "<<default_value_<<"\n\n";
  }


  std::vector<V> image();
  
  // This version of image() will collect the final image of an rmap-nested
  // rmap: for rmap<X,rmap<Y,T> >, image<T>() will yield the image of (X,Y)-> T
  // The result will contain every element only once except for the last, which
  // is repeated such that image<T>().size() = image(X) * image(Y)
  template<class T> std::vector<T> image();

};


template<class U,class V>
template<class T>
std::vector<T> rmap<U,V>::image() {
  std::vector<T> img;

  for (iterator it=this->begin(); it!=this->end(); it++) {
      std::vector<T> img_part=it->second.image();
      img.insert(img.end(), img_part.begin(), img_part.end());
  }
  std::sort(img.begin(), img.end());
  std::unique(img.begin(), img.end());
  return img;
}  


template<class U,class V>
std::vector<V> rmap<U,V>::image() {
  std::vector<V> img;
  
  for (iterator it=this->begin(); it!=this->end(); it++) {
    img.push_back(it->second);
  }
  std::sort(img.begin(), img.end());
  std::unique(img.begin(), img.end());
  return img;
} 


// template<class U,class V>
// template<class T> std::vector<T> rmap<U,V>::image() {

//   std::vector<T> img;
 
//   std::string ret_type = abi::__cxa_demangle(typeid(T).name(), NULL,NULL,NULL);
//   std::string V_type = abi::__cxa_demangle(typeid(V).name(), NULL, NULL, NULL);
//   std::string V_img_type="";

//   boost::regex e(".*rmap<.*, (.*)>");
//   boost::match_results<std::string::const_iterator> m;
//   if (boost::regex_match(V_type, m, e, boost::match_default)) {
//     if (m.size()==2) {
//       V_img_type=V_type.substr(m.position(), m.length());
//       std::cout<<"V_img_type: "<<V_img_type<<std::endl;
//     }
//   }

//   for (iterator it=this->begin(); it!=this->end(); it++) {
 
//     std::vector<T> img_part;

//     if (ret_type==V_img_type) {         // rmap<X, rmap<Y, T> > :
//       img_part=it->second.image();
//     } else {                            // rmap<X, rmap<Y, rmap<Z, T> > > :
//       img_part=it->second.image<T>();  
//     }

//     img.insert(img_part.end(), img_part.begin(), img_part.end());
//   }
//   std::sort(img.begin(), img.end());
//   std::unique(img.begin(), img.end());
//   return img;
// }


// template<class U,class V>
// std::vector<V> rmap<U,V>::image() {     // rmap<U, V> :
//   std::vector<V> img;
  
//   for (iterator it=this->begin(); it!=this->end(); it++) {
//     img.push_back(it->second);
//   }
//   std::sort(img.begin(), img.end());
//   std::unique(img.begin(), img.end());
//   return img;
// } 


//----------------------------- Class Definition ------------------------------

template<class H> class Histogram : public H {
 public:

  Histogram() : H() { init(); }

  //
  // Copy constructor - creates "this" histo in the current TDirectory
  //
  Histogram(const Histogram<H> &h) : H() { init(); *this=h; }

  //
  // Base class only copy constructor
  //
  Histogram(const H& h) : H(h) { init(); };

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
    if (HISTOGRAM_DEBUG) {
      std::cout<<"\nDtor: "<<this->GetName()<<" "<<this<<std::endl;
    }
  }

 private:
  std::map<std::string,int> auxIndex_;
  std::vector<Histogram<H> > auxVector_;
  int iNum_;                            // the numerator if efficiency is set
  int iDen_;                            // the denominator if efficiency is set
  std::map<std::string,int>::iterator lastIndex_;
  std::string legend_;                  // legend of this histogram when drawn
  std::string legendHead_;              // head on the legend (category)

  void init() {
    iNum_=-1;
    iDen_=-1;
    legend_="";
    legendHead_="";
    setDirectory(0); // set this histo and aux histos to TDirectory==0
    if (HISTOGRAM_DEBUG) {
      std::cout<<"\nCtor: "<<this->GetName()<<" "<<this<<std::endl;
    }
  }


 protected:
  std::vector<std::string> getNameTitle(char *nameTitle) {
  // In format: name[!legend[!legend head]][;title[;Xlabel[;Ylabel[;Zlabel]]]]
  // Returns strings: name, title (containing axis labels in ROOT format)
  // Set variables: legend_, legendHead_
    if (HISTOGRAM_DEBUG) std::cout<<"\ngetNameTitle(\""<<nameTitle<<"\")\n";
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
    if (HISTOGRAM_DEBUG) {
      std::cout<<"  name: "<<name<<"\n  title: "<<title;
      std::cout<<"\n  legend: "<<legend_<<"\n  head: "<<legendHead_<<std::endl;
    }
    std::vector<std::string> ret;
    ret.push_back(name);
    ret.push_back(title);
    return ret;
  }

  void fillX(H* h, Double_t x, Double_t w);
  void fillY(H* h, Double_t y, Double_t w);


 public:
  Histogram<H>& operator= (const Histogram<H> &h) { // moved to gDirectory
    if (HISTOGRAM_DEBUG) {
      std::cout<<"\noperator=: "<<this->GetName()<<" "<<this;
      std::cout<<" on "<<h.GetName()<<" "<<&h<<std::endl;
    }
    * dynamic_cast<H*>(this) = dynamic_cast<const H&>(h);
    legend_ = h.legend_;
    legendHead_ = h.legendHead_;
    auxIndex_ = h.auxIndex_;
    auxVector_ = h.auxVector_;
    iNum_=h.iNum_;
    iDen_=h.iDen_;

    setDirectory(0);
    return *this; 
  }

  

  void        setLabel(std::string, std::string, ...);  
  std::string getLabel(std::string, std::string, ...);
  void        efficiency();

  Histogram<H>*  num() { return (iNum_>=0) ? aux(iNum_) : NULL; }
  Histogram<H>*  den() { return (iDen_>=0) ? aux(iDen_) : NULL; }
  H&             getBase() { return dynamic_cast<H&>(*this); }

  void        copyContentFrom(H& h) {
    std::string oldname=this->GetName();
    this->getBase()=h;
    this->getBase().SetName(oldname.c_str());
  }

  void        copyContentFrom(Histogram<H>& h) { copyContentFrom(h.getBase());}

  void        copyContentTo(H& h) {
    std::string oldname=h.GetName();
    h=this->getBase();
    h.SetName(oldname.c_str());
  }

  void        copyContentTo(Histogram<H>& h) { copyContentTo(h.getBase()); }

  // Transient auxiliary copies of this histo, alway stored in memory
  //

  int addAux(std::string key,...) {
    va_list argList;
    va_start(argList, key);
    char s[10000];
    vsprintf(s, key.data(), argList);
    va_end(argList);
    key=s;

    if (aux(key)!=NULL) return -1;
    //auxVector_.push_back(dynamic_cast<H&>(*this));
    auxVector_.push_back(this->getBase());
    // IMPORTANT!!! a setDirectory must always follow a push_back
    setDirectoryAux(0);
    int i=getNAux()-1;
    auxIndex_[key]=i;
    key.insert(0, ".");
    auxVector_[i].SetName(key.insert(0, auxVector_[i].GetName()).c_str());
    return i;
  }

  int addAux(std::string key, H& h) {
    int i=addAux(key);
    if (i>=0) {
      std::string aname=aux(i)->GetName();
      (*aux(i))=h; 
      aux(i)->SetName(aname.c_str());
    }
    return i;
  }

  int addAux(std::string key, std::string formula,...) {
    va_list argList;
    va_start(argList, formula);
    char s[10000];
    vsprintf(s, formula.data(), argList);
    va_end(argList);
    formula=s;
    Histogram<H> h(*this);
    if (h.setContent(formula)==0) return addAux(key, h.getBase());
    return -1;
  }

  int addAux(std::string key, Histogram<H>& h, std::string formula,...) {
    va_list argList;
    va_start(argList, formula);
    char s[10000];
    vsprintf(s, formula.data(), argList);
    va_end(argList);
    formula=s;
    Histogram<H> h2=h;
    if (h2.setContent(formula)==0) return addAux(key, h2.getBase());
    return -1;
  }

  void eraseAux(std::string key,...) {
    va_list argList;
    va_start(argList, key);
    char s[10000];
    vsprintf(s, key.data(), argList);
    va_end(argList);
    int i=auxIndex(s);
    if (i>=0) eraseAux(i);
  }

  void eraseAux(int i) {
    typename std::map<std::string,int>::iterator rm=auxIndex_.end();
    typename std::map<std::string,int>::iterator it=auxIndex_.begin();
    for (; it!=auxIndex_.end(); it++) {
      if (it->second==i) rm=it; // this must come before the next line!!!
      if (it->second>i) it->second-=1;;
    }
    if (rm==auxIndex_.end()) return;
    auxVector_.erase(auxVector_.begin()+i);
    auxIndex_.erase(rm);
  }

  int auxIndex(std::string key) {
    typename std::map<std::string,int>::const_iterator it=auxIndex_.find(key);
    return (it!=auxIndex_.end()) ? it->second : -1;
  }

  int auxKey(int i) { // Very slow function, do not use it if possible
    typename std::map<std::string,int>::const_iterator it=auxIndex_.begin();
    for (; it!=auxIndex_.end(); it++) if (it->second==i) return i;
    return -1;
  }

  inline int getNAux() { return auxVector_.size(); }

  Histogram<H>* aux(int i=0) {
    return (i>=0 && i<int(auxVector_.size())) ? &(auxVector_[i]) : NULL; 
  }

  // Use aux() with no parameter when possible if only one aux histo exists
  Histogram<H>* aux(std::string key) { 
    if (auxVector_.size()==1) {
      return (key==auxIndex_.begin()->first) ? aux() : NULL;
    }
    return aux(auxIndex(key)); 
  }

  void setDirectoryAux(TDirectory* dir, std::string list="") {
    for (int i=0; i<getNAux(); i++) {
      if (list=="" || list.find(auxVector_[i].GetName())!=std::string::npos) {
	auxVector_[i].setDirectory(dir);
      }
    }
  }
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

  // Always applies to "this" histo, aux hists in "list" are set to TDirectory:
  void        setDirectory(TDirectory *dir=0, std::string list="");
  Int_t       Write(const char*, Int_t, Int_t);
  int         load(std::string name="", TDirectory *dir=NULL);
  void        print(std::string prefix="");
  void        setStyle(std::string style) { };
  void        SetName(const char* name);
  void        setName(std::string name,...) { 
    va_list argList;
    va_start(argList, name);
    char s[10000];
    vsprintf(s, name.data(), argList);
    va_end(argList);
    name=s;
    SetName(name.c_str()); 
  }
  void        reset(Option_t* option="");

  // Only for 2-D histograms
  // No safeguard when compiling with 1-D histograms. It just won't compile.
  void        fillX(Double_t x, Double_t w=1.)    { this->fillX(this, x, w); }
  void        fillY(Double_t y, Double_t w=1.)    { this->fillY(this, y, w); }

  int         setContent(int type, std::string formula, ...);
  int         setContent(std::string formula, ...);
  int         setError(std::string formula, ...);

  // For now it works only for uniform binning:
  void        shiftBinContent(float shift=0) {
    int dbin=int(floor(shift/this->GetBinWidth(1)))*-1;
    shift=(shift+dbin*this->GetBinWidth(1))/this->GetBinWidth(1);
    int i=this->addAux("__aux_for_shifting_", *this);
    if (i<0) return;
    this->setContent("$__aux_for_shifting_{%d}*%f+$__aux_for_shifting_{%d}*%f",
		     dbin-1, shift, dbin, 1.-shift);
    eraseAux("__aux_for_shifting_");
  }

  

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

  if (iNum_>=0 && iDen_>=0) {

    this->setContent("$num{}/$den{}");

    this->setError("1.96*sqrt( (($num{}+2)/($den{}+4)) " //sqrt(p' [= (X+2)/n']
		   "* (1-(($num{}+2)/($den{}+4))) " // * (1-p')
		   "/ ($den{}+4) ) * ($den{}!=0)"); // /n' [=N+4]) * (N!=0)
    // Last part *(N=0) assures no error in bin with no denominator in eff.

    return;
  }

  if (iNum_<0 && aux("num")!=NULL) iNum_=auxIndex("num");
  if (iDen_<0 && aux("den")!=NULL) iDen_=auxIndex("den");

  this->Sumw2();

  if (iNum_<0) iNum_ = addAux("num");
  if (iDen_<0) iDen_ = addAux("den");

}


template <class H> 
void Histogram<H>::setDirectory(TDirectory *dir, std::string list) {
  this->SetDirectory(dir);
  this->setDirectoryAux(dir, list);
}
 

template <class H> 
Int_t Histogram<H>::Write(const char* name = 0, Int_t option = 0, 
			  Int_t bufsize = 0) {

  for (int i=0; i<getNAux(); i++) {
    aux(i)->Write(aux(i)->GetName(), option, bufsize);
  }
  return H::Write(name, option, bufsize);
}


template <class H>
int Histogram<H>::load(std::string name, TDirectory* dir) {

  if (HISTOGRAM_DEBUG) std::cout<<"\nLoading histogram "<<name<<std::endl;

  // Load this histo:

  std::string oldname=this->GetName();

  if (name=="") name=this->GetName();
  if (dir==NULL) dir=gDirectory;
  H* h=NULL;

  h = (H*) dir->GetObjectChecked(name.c_str(), this->IsA());
  if (h!=NULL) {
    (*(H*)this)=*h;
    delete h;
    if (HISTOGRAM_DEBUG) std::cout<<"Loaded "<<this->GetName()<<std::endl;
  } else {
    return 1;
  }

  // Load the auxiliary histos, but destroy the ones we have currently first:

  auxIndex_.clear();
  auxVector_.clear();
  iNum_=iDen_=-1;

  TIter next(dir->GetListOfKeys());
  TKey *key;
  while (key=(TKey*)next()) {
    std::string hname=key->GetName();
    if (HISTOGRAM_DEBUG) std::cout<<"Key "<<hname<<std::endl;

    if (hname==name) continue;  // this is the main histo not an aux
    if (hname.find(name)!=0) continue; // this does not belong to this histo
    if (hname[name.size()]!='.') continue; // has no extension, it isn't an aux
    std::string aname=hname.substr(0, hname.find_first_of(".", name.size()+1));
    if (hname!=aname) continue; // this is not a direct aux of this hist

    std::string ext=aname.substr(aname.find_last_of(".")+1);

    int i=addAux(ext);

    // Special cases for known extensions:
    if (ext=="num") iNum_ = i;
    if (ext=="den") iDen_ = i; 

    aux(i)->load(aname, dir);
    if (HISTOGRAM_DEBUG) aux(i)->print();
  }

  setDirectory(0);
  if (name!=oldname) setName(oldname);
  return 0;
}


template <class H>
void Histogram<H>::print(std::string prefix) {

  if (prefix=="") {
    std::cout<<"\nHistogram: "<<this->GetName()<<" - in ";
  } else {
    std::cout<< prefix <<this->GetName()<<" - in ";
  }

  if (this->GetDirectory()!=0) {
    this->GetDirectory()->pwd();
  } else {
    std::cout<<"memory\n";
  }
  if (HISTOGRAM_DEBUG) std::cout<< prefix << "   at " << this << std::endl;

  prefix+="   ";
  for (int i=0; i<getNAux(); i++) {
    aux(i)->print(prefix);
  }
}


template <class H>
void Histogram<H>::SetName(const char* name) {

  for (int i=0; i<getNAux(); i++) {
    std::string name_aux=aux(i)->GetName();
    name_aux.erase(0, strlen(this->GetName()));
    name_aux.insert(0, name);
    aux(i)->SetName(name_aux.c_str());
  }
  // This has to be the last step, otherwise we lose the original name:
  H::SetName(name);
}


template <class H>
void Histogram<H>::reset(Option_t* option) {

  for (int i=0; i<getNAux(); i++) aux(i)->Reset(option);
  H::Reset(option);
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


template <class H> 
int Histogram<H>::setContent(int type, std::string formula,...) {

  va_list argList;
  va_start(argList, formula);
  char s[10000];
  vsprintf(s, formula.data(), argList);
  va_end(argList);
  formula=s;
  std::cout<<"\nProcessing formula: "<<formula<<std::endl;

  std::vector<std::vector<int> > params; // 0: iaux, 1: ibinX [2: ibinY...]
  int invalid=0;

  size_t dollar=formula.find_first_of("$");

  while (dollar!=std::string::npos) {

    std::vector<int> param;
    int bra=formula.find_first_of("{", dollar);
    size_t ket=bra-1;

    for (int i=0; i<this->GetDimension(); i++) {
      
      bra=ket+1;
      if (formula[bra]!='{') {
	invalid=1;
	break; // missing bra
      }

      // index of aux:
      if (i==0) {
	param.push_back(auxIndex(formula.substr(dollar+1, bra-dollar-1)));
	if (param[0]<0) {
	  invalid=1;
	  break; // aux histo does not exist
	}
      }
      
      ket=formula.find_first_of("}", bra);
      if (ket==std::string::npos) {
	invalid=1;
	break; // missing ket
      }
      param.push_back(atoi(formula.substr(bra+1, bra-ket-1).c_str())); // ibin
    } // for

    if (invalid) break;
    params.push_back(param);

    long len=ket-dollar+1;
    formula.erase(dollar, len);
    std::ostringstream par;
    int ipar=params.size()-1;
    par<<"["<<ipar<<"]";
    formula.insert(dollar, par.str());
    dollar=formula.find_first_of("$", dollar+par.str().size());
  } // while

  if (invalid) {
    std::cout<<"Invalid formula: "<<formula<<std::endl;
    return 1;
  }

  if (HISTOGRAM_DEBUG) {  
    //if (1) {
    std::cout<<"Formula: "<<formula<<std::endl;
    for (size_t i=0; i<params.size(); i++) {
      std::cout<<"Param ["<<i<<"]: ";
      std::cout<<aux(params[i][0])->GetName()<<" bin offset";
      for (int j=0; j<this->GetDimension(); j++) 
	std::cout<<" "<<params[i][j+1];
      std::cout<<std::endl;
    }
  }

  // Do the calculation
  Double_t pars[params.size()];
  TFormula f("f", formula.c_str());

  for (int i=1; i<=this->GetNbinsX(); i++) {
    for (int j=1; j<=this->GetNbinsY(); j++) {
      for (int k=1; k<=this->GetNbinsZ(); k++) {
	for (int l=0; l<int(params.size()); l++) {
	  pars[l]=aux(params[l][0])->GetBinContent(i+params[l][1],
						   j+params[l][2],
						   k+params[l][3]);
	}
	f.SetParameters(pars);
	if (type==0) {
	  this->SetBinContent(i, j, k, f.Eval(0));
	} else {
	  this->SetBinError(i, j, k, f.Eval(0));
	}
      }
    }
  }

  return 0;
}


template <class H> 
int Histogram<H>::setContent(std::string formula,...) {
  va_list argList;
  va_start(argList, formula);
  char s[10000];
  vsprintf(s, formula.data(), argList);
  va_end(argList);
  formula=s;
  return setContent(0, formula);
}


template <class H> 
int Histogram<H>::setError(std::string formula,...) {
  va_list argList;
  va_start(argList, formula);
  char s[10000];
  vsprintf(s, formula.data(), argList);
  va_end(argList);
  formula=s;
  return setContent(1, formula);
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

}
#endif
