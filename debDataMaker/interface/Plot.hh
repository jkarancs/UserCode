#ifndef debDataMaker_Plot_hh_
#define debDataMaker_Plot_hh_
// -*- C++ -*-
//
// Package:    debDataMaker
// Class:      Plot
// 
/**\class Plot Plot.hh debDataMaker/interface/Plot.hh

 Description: <one line class summary>

 Implementation:

*/
//
// Original Author:  Viktor VESZPREMI
//         Created:  Wed Oct 25 20:57:26 CET 2009
// $Id$
//
//
//-----------------------------------------------------------------------------

#include <iostream>
#include <fstream>
#include <string>

namespace deb {

//----------------------------- Class Definition ------------------------------

template<class H> class Plot : public std::map<std::string,H> {
 public:

  // Empty plot: format=<plot name>[;<plot title>]

  Plot(Int_t ww, Int_t wh, std::string format,...);

  //
  // TH1 constructors: format=<plot name>[;<plot title>[;<histo name>[;...]]]
  //

  Plot(Int_t ww, Int_t wh,
       Int_t nbinsx, Double_t xlow, Double_t xup, std::string format,...);

  Plot(Int_t ww, Int_t wh,
       Int_t nbins, const Float_t *xbins, std::string format,...);

  Plot(Int_t ww, Int_t wh,
       Int_t nbins, const Double_t *xbins, std::string format,...);

  //
  // TH2 constructors: format=<plot name>[;<plot title>[;<histo name>[;...]]]
  //

  Plot(Int_t ww, Int_t wh, Int_t nbinsx, Double_t xlow, Double_t xup, 
       Int_t nbinsy, Double_t ylow, Double_t yup, std::string format,...);

  Plot(Int_t ww, Int_t wh, Int_t nbinsx, const Double_t *xbins, 
       Int_t nbinsy, Double_t ylow, Double_t yup, std::string format,...);

  Plot(Int_t ww, Int_t wh, Int_t nbinsx, Double_t xlow, Double_t xup, 
       Int_t nbinsy, const Double_t *ybins, std::string format,...);

  Plot(Int_t ww, Int_t wh, Int_t nbinsx, const Double_t *xbins, 
       Int_t nbinsy, const Double_t *ybins, std::string format,...);

  Plot(Int_t ww, Int_t wh, Int_t nbinsx, const Float_t *xbins, 
       Int_t nbinsy, const Float_t *ybins, std::string format,...);

  ~Plot() { }

 private:
  TCanvas* can_;
  std::string style_;
  std::string init(Int_t ww, Int_t wh, std::string format);
  std::vector<std::string> generateNameTitleForH(std::string format);

  inline std::pair<std::string,std::string> splitString(std::string str, 
							std::string sep) {
    std::pair<std::string,std::string> ret(str, "");
    size_t pos=ret.first.find_first_of(sep);
    if (pos!=std::string::npos) {
      ret.second=ret.first.substr(pos+sep.size());
      ret.first.erase(pos);
    }
    return ret;
  }

  inline std::vector<std::string> itemizeString(std::string str, 
						std::string sep) {
    std::vector<std::string> ret;
    size_t pos=str.find_first_of(sep);
    while (pos!=std::string::npos) {
      std::pair<std::string,std::string> items = splitString(str, sep);
      ret.push_back(items.first);
      str=items.second;
      pos=str.find_first_of(sep);
    }
    ret.push_back(str);
    return ret;
  }


  inline std::vector<std::string> itemizeString(std::vector<std::string> vstr, 
						std::string sep) {
    std::vector<std::string> ret;
    for (size_t i=0; i<vstr.size(); i++) {
      std::vector<std::string> part=itemizeString(vstr[i], sep);
      ret.insert(ret.end(), part.begin(), part.end());
    }
    return ret;
  }

 public:
  TCanvas& canvas() { return *can_; }


  void add(Int_t nbinsx, Double_t xlow, Double_t xup, std::string format,...);

  void add(Int_t nbins, const Float_t *xbins, std::string format,...);

  void add(Int_t nbins, const Double_t *xbins, std::string format,...);

  void add(Int_t nbinsx, Double_t xlow, Double_t xup, 
	   Int_t nbinsy, Double_t ylow, Double_t yup, std::string format,...);

  void add(Int_t nbinsx, const Double_t *xbins, 
	   Int_t nbinsy, Double_t ylow, Double_t yup, std::string format,...);

  void add(Int_t nbinsx, Double_t xlow, Double_t xup, 
	   Int_t nbinsy, const Double_t *ybins, std::string format,...);

  void add(Int_t nbinsx, const Double_t *xbins, 
	   Int_t nbinsy, const Double_t *ybins, std::string format,...);

  void add(Int_t nbinsx, const Float_t *xbins, 
	   Int_t nbinsy, const Float_t *ybins, std::string format,...);


  H& operator()(size_t i) { return (*this)("[%d]", i); }
  H& operator()(std::string format, ...);

  void efficiency();

  void setColor(std::string attr, Color_t color);
  void setStyle(std::string attr, Style_t style);
  void setWidth(std::string attr, Width_t width);

  void setAxisRange(Double_t xmin, Double_t xmax, Option_t* axis = "X");

  int  Draw(std::vector<std::string> hists, int ncols=1, int nrows=-1);
  int  Draw(std::string hist, int ncols=1, int nrows=-1);

  void Write();

  void scaleMaximumTo(std::string kind="", double maximum=1.0);
  void scaleAreaTo(std::string kind="", double area=1.0);
  
  //void setCanvasStyle(std::string style="TDR");
  //void setPadStyle()
};


//--------------------------------- init --------------------------------------

template<class H>
std::string Plot<H>::init(Int_t ww, Int_t wh, std::string format) {

  std::pair<std::string,std::string> nameTitle=splitString(format, ";");
  std::ostringstream histNameTitle("");
  style_="";

  if (nameTitle.first.find_first_of("\\")!=std::string::npos) {
    std::pair<std::string,std::string> nameStyle;
    nameStyle=splitString(nameTitle.first, "\\");
    nameTitle.first=nameStyle.first;
    style_=nameStyle.second;
  }

  if (nameTitle.second.find_first_of(";")!=std::string::npos) {
    std::pair<std::string,std::string> titleHist;
    titleHist=splitString(nameTitle.second, ";");
    nameTitle.second=titleHist.first;
    if (titleHist.second.find_first_of(";")!=std::string::npos) {
      histNameTitle << titleHist.second;
    } else {
      histNameTitle << titleHist.second << ";" << nameTitle.second;
    }
  }

  if (ww<0) ww=600;
  if (wh<0) ww=600;

  can_=new TCanvas(nameTitle.first.data(), nameTitle.second.data(), ww, wh);
  can_->SetWindowSize(ww+(ww-can_->GetWw()), wh+(wh-can_->GetWh()));
  
  return histNameTitle.str();
}


//-------------------------- Empty Plot Constructor ---------------------------

template<class H>
Plot<H>::Plot(Int_t ww, Int_t wh, std::string format,...) {
  va_list argList;
  va_start(argList, format);
  char s[10000];
  vsprintf(s, format.data(), argList);
  va_end(argList);
  init(ww, wh, s);
}


//---------------------------- TH1 Constructors -------------------------------

template <class H> 
Plot<H>::Plot(Int_t ww, Int_t wh, Int_t nbinsx, Double_t xlow, 
	      Double_t xup, std::string format,...) {
  va_list argList;
  va_start(argList, format);
  char s[10000];
  vsprintf(s, format.data(), argList);
  va_end(argList);

  std::string histNameTitle=init(ww, wh, s);
  add(nbinsx, xlow, xup, histNameTitle);
}


template <class H> 
Plot<H>::Plot(Int_t ww, Int_t wh, Int_t nbins, const Float_t *xbins, 
	      std::string format,...) {
  va_list argList;
  va_start(argList, format);
  char s[10000];
  vsprintf(s, format.data(), argList);
  va_end(argList);

  std::string histNameTitle=init(ww, wh, s);
  add(nbins, xbins, histNameTitle);
}


template <class H> 
Plot<H>::Plot(Int_t ww, Int_t wh, Int_t nbins, const Double_t *xbins, 
	      std::string format,...) {
  va_list argList;
  va_start(argList, format);
  char s[10000];
  vsprintf(s, format.data(), argList);
  va_end(argList);

  std::string histNameTitle=init(ww, wh, s);
  add(nbins, xbins, histNameTitle);
}


//---------------------------- TH2 Constructors -------------------------------

template <class H> 
Plot<H>::Plot(Int_t ww, Int_t wh, Int_t nbinsx, Double_t xlow, 
	      Double_t xup, Int_t nbinsy, Double_t ylow, Double_t yup, 
	      std::string format,...) { 

  va_list argList;
  va_start(argList, format);
  char s[10000];
  vsprintf(s, format.data(), argList);
  va_end(argList);

  std::string histNameTitle=init(ww, wh, s);
  add(nbinsx, xlow, xup, nbinsy, ylow, yup, histNameTitle);
}

template <class H> 
Plot<H>::Plot(Int_t ww, Int_t wh, Int_t nbinsx, const Double_t *xbins, 
	      Int_t nbinsy, Double_t ylow, Double_t yup, 
	      std::string format,...) { 

  va_list argList;
  va_start(argList, format);
  char s[10000];
  vsprintf(s, format.data(), argList);
  va_end(argList);

  std::string histNameTitle=init(ww, wh, s);
  add(nbinsx, xbins, nbinsy, ylow, yup, histNameTitle);
}

template <class H> 
Plot<H>::Plot(Int_t ww, Int_t wh, Int_t nbinsx, Double_t xlow, 
	      Double_t xup, Int_t nbinsy, const Double_t *ybins, 
	      std::string format,...) { 

  va_list argList;
  va_start(argList, format);
  char s[10000];
  vsprintf(s, format.data(), argList);
  va_end(argList);

  std::string histNameTitle=init(ww, wh, s);
  add(nbinsx, xlow, xup, nbinsy, ybins, histNameTitle);
}

template <class H> 
Plot<H>::Plot(Int_t ww, Int_t wh, Int_t nbinsx, const Double_t *xbins, 
	      Int_t nbinsy, const Double_t *ybins, 
	      std::string format,...) { 

  va_list argList;
  va_start(argList, format);
  char s[10000];
  vsprintf(s, format.data(), argList);
  va_end(argList);

  std::string histNameTitle=init(ww, wh, s);
  add(nbinsx, xbins, nbinsy, ybins, histNameTitle);
}

template <class H> 
Plot<H>::Plot(Int_t ww, Int_t wh, Int_t nbinsx, const Float_t *xbins, 
	      Int_t nbinsy, const Float_t *ybins, 
	      std::string format,...) { 

  va_list argList;
  va_start(argList, format);
  char s[10000];
  vsprintf(s, format.data(), argList);
  va_end(argList);

  std::string histNameTitle=init(ww, wh, s);
  add(nbinsx, xbins, nbinsy, ybins, histNameTitle);
}


//------------------------ generateNameTitleForH() ----------------------------

template <class H>
std::vector<std::string> Plot<H>::generateNameTitleForH(std::string format) {

  std::pair<std::string,std::string> nameTitle=splitString(format, ";");

  std::vector<size_t> count;
  if (nameTitle.first.find_first_of("@")!=std::string::npos) {

    std::pair<std::string,std::string> nameNumber;
    nameNumber=splitString(nameTitle.first,"@");
    nameTitle.first=nameNumber.first;
    std::string s("@");
    s+=nameNumber.second;

    while(s[0]=='@') {
      size_t pos=s.find_first_not_of("1234567890", 1);
      std::string multiplier=s.substr(1, pos-1);
      count.push_back(atoi(multiplier.data()));
      s.erase(0, s.find_first_of("@", pos));
    }

  }

  std::vector<std::string> ret;

  if (count.size()==0) {
    if (nameTitle.first=="") return ret;
    
    std::ostringstream fullname;
    fullname << can_->GetName() << "_" << nameTitle.first;
    
    ret.push_back(nameTitle.first);
    ret.push_back(fullname.str());
    ret.push_back(format.find_first_of(";")!=std::string::npos ?
		  nameTitle.second : can_->GetTitle());
    return ret;
  }

  for (size_t i=0; i<count.size(); i++) {
    int ret_size=ret.size();
    for (int k= (ret_size ? 0 : -3); k<ret_size; k+=3) {
      for (size_t j=0; j<count[i]; j++) {
	std::ostringstream index;
	index << (k<0 ? nameTitle.first : ret[k]) << "[" << j << "]";
	
	std::ostringstream fullname;
	fullname << can_->GetName() << "_" << index.str();

	std::string title;
	if (k<0) {
	  title = format.find_first_of(";")!=std::string::npos ? 
	          nameTitle.second : can_->GetTitle();
	} else {
	  title = ret[k+2];
	}

	std::ostringstream cref;
	cref << "@#" << i+1;
	std::ostringstream idx;
	idx << j;
	size_t pos=title.find(cref.str());
	std::cout << cref.str() << "is found at" << pos << std::endl;
	while(pos!=std::string::npos) {
	  title.replace(pos, cref.str().size(), idx.str());
	  pos=title.find(cref.str(), pos+idx.str().size());
	}

	std::cout << "i,j,k = " << i << " " << j << " " << k << " " << fullname.str() << " " << title << std::endl;
	
	ret.push_back(index.str());
	ret.push_back(fullname.str());      
	ret.push_back(title);
      }
    }
    if (ret_size) ret.erase(ret.begin(), ret.begin()+ret_size);
  }
  
  return ret;
}


//---------------------------------- add() ------------------------------------

template <class H> void Plot<H>::add(Int_t nbinsx, Double_t xlow, Double_t xup,
				     std::string format,...) {
  va_list argList;
  va_start(argList, format);
  char s[10000];
  vsprintf(s, format.data(), argList);

  std::vector<std::string> labels=generateNameTitleForH(s);
  for (size_t i=0; i<labels.size(); i+=3) {
    (*this)[labels[i]]=H(labels[i+1].data(), labels[i+2].data(), 
			 nbinsx, xlow, xup);
  }
}


template <class H> void Plot<H>::add(Int_t nbins, const Float_t *xbins, 
				     std::string format,...) { 
  va_list argList;
  va_start(argList, format);
  char s[10000];
  vsprintf(s, format.data(), argList);

  std::vector<std::string> labels=generateNameTitleForH(s);
  (*this)[labels[0]]=H(labels[1].data(), labels[2].data(), nbins, xbins);
}


template <class H> void Plot<H>::add(Int_t nbins, const Double_t *xbins,
				     std::string format,...) { 
  va_list argList;
  va_start(argList, format);
  char s[10000];
  vsprintf(s, format.data(), argList);

  std::vector<std::string> labels=generateNameTitleForH(s);
  (*this)[labels[0]]=H(labels[1].data(), labels[2].data(), nbins, xbins);
}


template <class H> void Plot<H>::add(Int_t nbinsx, Double_t xlow, Double_t xup,
				     Int_t nbinsy, Double_t ylow, Double_t yup,
				     std::string format,...) { 
  va_list argList;
  va_start(argList, format);
  char s[10000];
  vsprintf(s, format.data(), argList);

  std::vector<std::string> labels=generateNameTitleForH(s);
  (*this)[labels[0]]=H(labels[1].data(), labels[2].data(), 
		       nbinsx, xlow, xup, nbinsy, ylow, yup);
}


template <class H> void Plot<H>::add(Int_t nbinsx, const Double_t *xbins, 
				     Int_t nbinsy, Double_t ylow, Double_t yup,
				     std::string format,...) { 
  va_list argList;
  va_start(argList, format);
  char s[10000];
  vsprintf(s, format.data(), argList);

  std::vector<std::string> labels=generateNameTitleForH(s);
  (*this)[labels[0]]=H(labels[1].data(), labels[2].data(), 
		       nbinsx, xbins, nbinsy, ylow, yup);
}


template <class H> void Plot<H>::add(Int_t nbinsx, Double_t xlow, Double_t xup,
				     Int_t nbinsy, const Double_t *ybins, 
				     std::string format,...) { 
  va_list argList;
  va_start(argList, format);
  char s[10000];
  vsprintf(s, format.data(), argList);

  std::vector<std::string> labels=generateNameTitleForH(s);
  (*this)[labels[0]]=H(labels[1].data(), labels[2].data(), 
		       nbinsx, xlow, xup, nbinsy, ybins);
}


template <class H> void Plot<H>::add(Int_t nbinsx, const Double_t *xbins, 
				     Int_t nbinsy, const Double_t *ybins, 
				     std::string format,...) { 
  va_list argList;
  va_start(argList, format);
  char s[10000];
  vsprintf(s, format.data(), argList);

  std::vector<std::string> labels=generateNameTitleForH(s);
  (*this)[labels[0]]=H(labels[1].data(), labels[2].data(), 
		       nbinsx, xbins, nbinsy, ybins);
}


template <class H> void Plot<H>::add(Int_t nbinsx, const Float_t *xbins, 
				     Int_t nbinsy, const Float_t *ybins, 
				     std::string format,...) { 
  va_list argList;
  va_start(argList, format);
  char s[10000];
  vsprintf(s, format.data(), argList);

  std::vector<std::string> labels=generateNameTitleForH(s);
  (*this)[labels[0]]=H(labels[1].data(), labels[2].data(), 
		       nbinsx, xbins, nbinsy, ybins);
}


//---------------------------------- operator() -------------------------------

template <class H>
H& Plot<H>::operator()(std::string format, ...) { 
  va_list argList;
  va_start(argList, format);
  char s[10000];
  vsprintf(s, format.data(), argList);
  va_end(argList);
  return (*this)[s];
}


//-------------------------------- efficiency() -------------------------------

template <class H>  
void Plot<H>::efficiency() {
  typename std::map<std::string,H>::iterator it;
  for (it=this->begin(); it!=this->end(); it++) it->second.efficiency();
}


//---------------------------------- setColor() -------------------------------

template <class H> 
void Plot<H>::setColor(std::string attr, Color_t color) {
  typename std::map<std::string,H>::iterator it;
  int c=0;
  for (it=this->begin(); it!=this->end(); it++) {
    if (attr.find("Line")!=std::string::npos || 
	attr.find("line")!=std::string::npos) {
      it->second.SetLineColor(color+c);
      it->second.num()->SetLineColor(color+c);
      it->second.den()->SetLineColor(color+c);
    }
    if (attr.find("Fill")!=std::string::npos || 
	attr.find("fill")!=std::string::npos) {
      it->second.SetFillColor(color+c);
      it->second.num()->SetFillColor(color+c);
      it->second.den()->SetFillColor(color+c);
    }
    c++;
  }
}


//---------------------------------- setStyle() -------------------------------

template <class H> 
void Plot<H>::setStyle(std::string attr, Style_t style) {
  typename std::map<std::string,H>::iterator it;
  for (it=this->begin(); it!=this->end(); it++) {
    if (attr.find("Line")!=std::string::npos || 
	attr.find("line")!=std::string::npos) {
      it->second.SetLineStyle(style);
      it->second.num()->SetLineStyle(style);
      it->second.den()->SetLineStyle(style);
    }
    if (attr.find("Fill")!=std::string::npos || 
	attr.find("fill")!=std::string::npos) {
      it->second.SetFillStyle(style);
      it->second.num()->SetFillStyle(style);
      it->second.den()->SetFillStyle(style);
    }
  }
}


//-------------------------------- setWidth() ---------------------------------

template <class H> 
void Plot<H>::setWidth(std::string attr, Width_t width) {
  typename std::map<std::string,H>::iterator it;
  for (it=this->begin(); it!=this->end(); it++) {
    if (attr.find("Line")!=std::string::npos || 
	attr.find("line")!=std::string::npos) {
      it->second.SetLineWidth(width);
      it->second.num()->SetLineWidth(width);
      it->second.den()->SetLineWidth(width);
    }
  }
}

//-------------------------------- setAxisRange() -----------------------------

template <class H>
void Plot<H>::setAxisRange(Double_t xmin, Double_t xmax, Option_t* axis){
  typename std::map<std::string,H>::iterator it;
  for (it=this->begin(); it!=this->end(); it++) {
    it->second.SetAxisRange(xmin, xmax, axis);
    if (it->second.num()) it->second.num()->SetAxisRange(xmin, xmax, axis);
    if (it->second.den()) it->second.den()->SetAxisRange(xmin, xmax, axis);
  }
}


//------------------------------------ Draw() ---------------------------------

template <class H> 
int Plot<H>::Draw(std::vector<std::string> hists, int ncols, int nrows) {

  std::vector<std::string> expList = itemizeString(hists, "\\");
  std::vector<std::pair<std::vector<std::string>,std::string> > pads;

  for (size_t i=0; i<expList.size(); i++) {
    std::pair<std::vector<std::string>,std::string> pad;

    std::pair<std::string,std::string> listOption=splitString(expList[i], ";");
    size_t space=listOption.first.find_first_of(" ");
    while (space!=std::string::npos) {
      listOption.first.erase(space, 1);
      space=listOption.first.find_first_of(" ", space);
    }
    pad.second=listOption.second;

    std::vector<std::string> items = itemizeString(listOption.first, ",");
    if (pad.second.find("overlay")!=std::string::npos ||
	pad.second.find("stack")!=std::string::npos) {
      pad.first.insert(pad.first.begin(), items.begin(), items.end());
      pads.push_back(pad);
      continue;
    }

    for (size_t j=0; j<items.size(); j++) {
      pad.first.push_back(items[j]);
      pads.push_back(pad);
      pad.first.clear();
    }
  }

  if (nrows<0) nrows=pads.size()/ncols;
  if (ncols*nrows<int(pads.size())) nrows=pads.size()/ncols+1;

  can_->Clear();
  can_->Divide(ncols, nrows);

  for (size_t i=0; i<pads.size(); i++) {

    std::string option=pads[i].second;
    size_t posOverlay=option.find("overlay");
    if (posOverlay!=std::string::npos) option.erase(posOverlay, 7);
    size_t posStack=option.find("stack");
    if (posStack!=std::string::npos) option.erase(posStack, 5);
    std::ostringstream opt;
    opt << option;

    can_->cd(i+1);

    for (size_t j=0; j<pads[i].first.size(); j++) {
      std::string hist=pads[i].first[j];

      size_t pos=hist.find(".num");
      if (pos!=std::string::npos) {
	hist.erase(pos, 4);
	typename std::map<std::string,H>::iterator it=this->find(hist);
	if (it!=this->end()) it->second.num()->Draw(opt.str().data());
      } else {
	pos=hist.find(".den");
	if (pos!=std::string::npos) {
	  hist.erase(pos, 4);
	  typename std::map<std::string,H>::iterator it=this->find(hist);
	  if (it!=this->end()) it->second.den()->Draw(opt.str().data());
	} else {
	  typename std::map<std::string,H>::iterator it=this->find(hist);
	  if (it!=this->end()) it->second.Draw(opt.str().data());
	}
      }

      if (j==0) opt << "SAME";
    }
  }

  return pads.size();
}


template <class H> 
int Plot<H>::Draw(std::string hist, int ncols, int nrows) {
  std::vector<std::string> vhist;
  vhist.push_back(hist);
  return this->Draw(vhist, ncols, nrows);
}


//------------------------------------ Write() --------------------------------

template <class H> void Plot<H>::Write() {
  typename std::map<std::string,H>::iterator it;
  for (it=this->begin(); it!=this->end(); it++) {
    it->second.Write();
  }
  can_->Write();
}


//------------------------------------ Scale() --------------------------------

template <class H>
void Plot<H>::scaleMaximumTo(std::string kind, double maximum) {
  typename std::map<std::string,H>::iterator it;
  int k=0;
  if (kind.find("num")!=std::string::npos) k=1;
  if (kind.find("den")!=std::string::npos) k=-1;

  for (it=this->begin(); it!=this->end(); it++) {
    double max;
    if (k) {
      if (k>0) {
	if (it->second.num()) {
	  max=it->second.num()->GetMaximum();
	  if (max!=0.) it->second.num()->Scale(maximum/max);
	}
      } else {
	if (it->second.den()) {
	  max=it->second.den()->GetMaximum();
	  if (max!=0.) it->second.den()->Scale(maximum/max);
	}
      }
    } else {
      max=it->second.GetMaximum();
      if (max!=0.) it->second.Scale(maximum/max);
    }
  }
  return;
}


template <class H>
void Plot<H>::scaleAreaTo(std::string kind, double area) {
  typename std::map<std::string,H>::iterator it;
  int k=0;
  if (kind.find("num")!=std::string::npos) k=1;
  if (kind.find("den")!=std::string::npos) k=-1;

  for (it=this->begin(); it!=this->end(); it++) {
    double integral;
    if (k) {
      if (k>0) {
	if (it->second.num()) {
	  integral=it->second.num()->Integral();
	  if (integral!=0.) it->second.num()->Scale(area/integral);
	}
      } else {
	if (it->second.den()) {
	  integral=it->second.den()->Integral();
	  if (integral!=0.) it->second.den()->Scale(area/integral);
	}
      }
    } else {
      integral=it->second.Integral();
      if (integral!=0.) it->second.Scale(area/integral);
    }
  }
  return;
}


// //-----------------------------------------------------------------------------

// template <class H> 
// void Plot<H>::setPlotStyle(std::string style) {

//   if (style.find("TDR")!=std::string::npos || 
//       style.find("tdr")!=std::string::npos ) {
//     // For the canvas:
//     can_->SetBorderMode(0);
//     can_->SetFillColor(kWhite);
//     //can_->SetCanvasDefH(600); //Height of canvas
//     //can_->SetCanvasDefW(600); //Width of canvas
//     //can_->SetCanvasDefX(0);   //POsition on screen
//     //can_->SetCanvasDefY(0);
    
//     // For the Pad:
//     can_->SetBorderMode(0);
//     // can_->SetPadBorderSize(Width_t size = 1);
//     can_->SetFramdeFillColor(kWhite);
//     can_->SetGridx(false);
//     can_->SetGridy(false);
//     can_->SetGridColor(0);
//     can_->SetGridStyle(3);
//     can_->SetGridWidth(1);
    
//     // For the frame:
//     can_->SetFrameBorderMode(0);
//     can_->SetFrameBorderSize(1);
//     can_->SetFrameFillColor(0);
//     can_->SetFrameFillStyle(0);
//     can_->SetFrameLineColor(1);
//     can_->SetFrameLineStyle(1);
//     can_->SetFrameLineWidth(1);
    
//     // For the histo:
//     // can_->SetHistFillColor(1);
//     // can_->SetHistFillStyle(0);
//     can_->SetHistLineColor(1);
//     can_->SetHistLineStyle(0);
//     can_->SetHistLineWidth(1);
//     // can_->SetLegoInnerR(Float_t rad = 0.5);
//     // can_->SetNumberContours(Int_t number = 20);
    
//     can_->SetEndErrorSize(2);
//     //can_->SetErrorMarker(20);
//     can_->SetErrorX(0.);
    
//     can_->SetMarkerStyle(20);
    
//     //For the fit/function:
//     can_->SetOptFit(1);
//     can_->SetFitFormat("5.4g");
//     can_->SetFuncColor(2);
//     can_->SetFuncStyle(1);
//     can_->SetFuncWidth(1);
    
//     //For the date:
//     can_->SetOptDate(0);
//     // can_->SetDateX(Float_t x = 0.01);
//     // can_->SetDateY(Float_t y = 0.01);
    
//     // For the statistics box:
//     can_->SetOptFile(0);
//     //can_->SetOptStat(0);
//     can_->SetOptStat("mr");
//     can_->SetStatColor(kWhite);
//     can_->SetStatFont(42);
//     can_->SetStatFontSize(0.04);//---> can_->SetStatFontSize(0.025);
//     can_->SetStatTextColor(1);
//     can_->SetStatFormat("6.4g");
//     can_->SetStatBorderSize(1);
//     can_->SetStatH(0.1);
//     can_->SetStatW(0.2);//---> can_->SetStatW(0.15);
    
//     // can_->SetStatStyle(Style_t style = 1001);
//     // can_->SetStatX(Float_t x = 0);
//     // can_->SetStatY(Float_t y = 0);
    
//     // Margins:
//     can_->SetPadTopMargin(0.05);
//     can_->SetPadBottomMargin(0.13);
//     can_->SetPadLeftMargin(0.16);
//     can_->SetPadRightMargin(0.02);
    
//     // For the Global title:
    
//     can_->SetOptTitle(0);
//     can_->SetTitleFont(42);
//     can_->SetTitleColor(1);
//     can_->SetTitleTextColor(1);
//     can_->SetTitleFillColor(10);
//     can_->SetTitleFontSize(0.05);
//     // can_->SetTitleH(0); // Set the height of the title box
//     // can_->SetTitleW(0); // Set the width of the title box
//     // can_->SetTitleX(0); // Set the position of the title box
//     // can_->SetTitleY(0.985); // Set the position of the title box
//     // can_->SetTitleStyle(Style_t style = 1001);
//     // can_->SetTitleBorderSize(2);
    
//     // For the axis titles:
    
//     can_->SetTitleColor(1, "XYZ");
//     can_->SetTitleFont(42, "XYZ");
//     can_->SetTitleSize(0.06, "XYZ");
//     // can_->SetTitleXSize(Float_t size = 0.02); 
//     // Another way to set the size?
//     // can_->SetTitleYSize(Float_t size = 0.02);
//     can_->SetTitleXOffset(0.9);
//     can_->SetTitleYOffset(1.25);
//     // can_->SetTitleOffset(1.1, "Y"); // Another way to set the Offset
    
//     // For the axis labels:
    
//     can_->SetLabelColor(1, "XYZ");
//     can_->SetLabelFont(42, "XYZ");
//     can_->SetLabelOffset(0.007, "XYZ");
//     can_->SetLabelSize(0.05, "XYZ");
    
//     // For the axis:
    
//     can_->SetAxisColor(1, "XYZ");
//     can_->SetStripDecimals(kTRUE);
//     can_->SetTickLength(0.03, "XYZ");
//     can_->SetNdivisions(510, "XYZ");
//     can_->SetPadTickX(1);  
//     // To get tick marks on the opposite side of the frame
//     can_->SetPadTickY(1);
    
//     // Change for log plots:
//     can_->SetOptLogx(0);
//     can_->SetOptLogy(0);
//     can_->SetOptLogz(0);
    
//     // Postscript options:
//     can_->SetPaperSize(20.,20.);
//     // can_->SetLineScalePS(Float_t scale = 3);
//     // can_->SetLineStyleString(Int_t i, const char* text);
//     // can_->SetHeaderPS(const char* header);
//     // can_->SetTitlePS(const char* pstitle);
    
//     // can_->SetBarOffset(Float_t baroff = 0.5);
//     // can_->SetBarWidth(Float_t barwidth = 0.5);
//     // can_->SetPaintTextFormat(const char* format = "g");
//     // can_->SetPalette(Int_t ncolors = 0, Int_t* colors = 0);
//     // can_->SetTimeOffset(Double_t toffset);
//     // can_->SetHistMinimumZero(kTRUE);
    
//     //   can_->cd();
    
//     //gROOT->ForceStyle();
//   }
// }


//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

}
#endif
