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
// $Id: Plot.hh,v 1.2 2009/11/24 09:51:45 veszpv Exp $
//
//
//-----------------------------------------------------------------------------

#include <iostream>
#include <fstream>
#include <string>
#include "Histogram.hh"
#include "TH1.h"
#include "TH2.h"
#include "TCanvas.h"
#include "TLegend.h"
#include "TStyle.h"
#include "TROOT.h"
#include "TF1.h"
#include "TFrame.h"
#include "TPaveStats.h"
#include "TDirectory.h"

namespace deb {

//----------------------------- Class Definition ------------------------------

template<class H> class Plot : public std::map<std::string,Histogram<H> > {
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
  std::map<std::string,H> stack_;
  std::vector<TLegend*> legend_;
  std::vector<H*> frame_;
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
  std::vector<TLegend>& legend() { return legend_; }
  std::vector<H*> frame() { return frame_; }
  int getNPads() { return frame_.size(); }

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


  Histogram<H>& operator()(size_t i) { return (*this)("[%d]", i); }
  Histogram<H>& operator()(std::string format, ...);

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

  void setPlotStyle(std::string);

  //void setOptStat(int);
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

  if (ww==0) ww=600;
  if (wh==0) ww=600;

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
    (*this)[labels[i]]=Histogram<H>(labels[i+1].data(), labels[i+2].data(), 
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
  (*this)[labels[0]]=Histogram<H>(labels[1].data(), labels[2].data(), 
				  nbins, xbins);
}


template <class H> void Plot<H>::add(Int_t nbins, const Double_t *xbins,
				     std::string format,...) { 
  va_list argList;
  va_start(argList, format);
  char s[10000];
  vsprintf(s, format.data(), argList);

  std::vector<std::string> labels=generateNameTitleForH(s);
  (*this)[labels[0]]=Histogram<H>(labels[1].data(), labels[2].data(), 
				  nbins, xbins);
}


template <class H> void Plot<H>::add(Int_t nbinsx, Double_t xlow, Double_t xup,
				     Int_t nbinsy, Double_t ylow, Double_t yup,
				     std::string format,...) { 
  va_list argList;
  va_start(argList, format);
  char s[10000];
  vsprintf(s, format.data(), argList);

  std::vector<std::string> labels=generateNameTitleForH(s);
  (*this)[labels[0]]=Histogram<H>(labels[1].data(), labels[2].data(), 
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
  (*this)[labels[0]]=Histogram<H>(labels[1].data(), labels[2].data(), 
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
  (*this)[labels[0]]=Histogram<H>(labels[1].data(), labels[2].data(), 
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
  (*this)[labels[0]]=Histogram<H>(labels[1].data(), labels[2].data(), 
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
  (*this)[labels[0]]=Histogram<H>(labels[1].data(), labels[2].data(), 
		       nbinsx, xbins, nbinsy, ybins);
}


//---------------------------------- operator() -------------------------------

template <class H>
Histogram<H>& Plot<H>::operator()(std::string format, ...) { 
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
  typename std::map<std::string,Histogram<H> >::iterator it;
  for (it=this->begin(); it!=this->end(); it++) it->second.efficiency();
}


//---------------------------------- setColor() -------------------------------

template <class H> 
void Plot<H>::setColor(std::string attr, Color_t color) {
  typename std::map<std::string,Histogram<H> >::iterator it;
  int c=0;
  for (it=this->begin(); it!=this->end(); it++) {
    if (attr.find("Line")!=std::string::npos || 
	attr.find("line")!=std::string::npos) {
      it->second.SetLineColor(color+c);
      if (it->second.num()) it->second.num()->SetLineColor(color+c);
      if (it->second.den()) it->second.den()->SetLineColor(color+c);
    }
    if (attr.find("Fill")!=std::string::npos || 
	attr.find("fill")!=std::string::npos) {
      it->second.SetFillColor(color+c);
      if (it->second.num()) it->second.num()->SetFillColor(color+c);
      if (it->second.den()) it->second.den()->SetFillColor(color+c);
    }
    c++;
  }
}


//---------------------------------- setStyle() -------------------------------

template <class H> 
void Plot<H>::setStyle(std::string attr, Style_t style) {
  typename std::map<std::string,Histogram<H> >::iterator it;
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
  typename std::map<std::string,Histogram<H> >::iterator it;
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
  typename std::map<std::string,Histogram<H> >::iterator it;
  for (it=this->begin(); it!=this->end(); it++) {
    it->second.SetAxisRange(xmin, xmax, axis);
    if (it->second.num()) it->second.num()->SetAxisRange(xmin, xmax, axis);
    if (it->second.den()) it->second.den()->SetAxisRange(xmin, xmax, axis);
  }
}


//------------------------------------ Draw() ---------------------------------

template <class H> 
int Plot<H>::Draw(std::vector<std::string> hists, int ncols, int nrows) {

  typedef std::vector<std::string> PlotNames;
  typedef std::vector<std::string> OptionList;

  // Collect list of pads ----------------------------------------------------

  std::vector<std::pair<PlotNames,OptionList> > pads;
  std::vector<std::string> expList = itemizeString(hists, "\\");

  std::cout<<"expanded list:\n";
  for (size_t i=0; i<expList.size(); i++) std::cout<<expList[i]<<std::endl;

  for (size_t i=0; i<expList.size(); i++) {
    std::pair<PlotNames,OptionList> pad;
    std::pair<std::string,std::string> split=splitString(expList[i], ";");
    std::string names=split.first;
    if (names=="") continue;
    split=splitString(split.second, ";");

    pad.second.push_back("");
    size_t posOverlay=split.first.find("overlay");
    if (posOverlay!=std::string::npos) {
      split.first.erase(posOverlay, 7);
      pad.second[0]="overlay";
    }
    size_t posStack=split.first.find("stack");
    if (posStack!=std::string::npos) {
      split.first.erase(posStack, 5);
      pad.second[0]="stack";
    }
    pad.second.push_back(split.first);
    pad.second.push_back(split.second);

    size_t space=names.find_first_of(" ");
    size_t pipe=names.find_last_of("|", space);
    size_t coma=names.find_last_of(",", space);
    while (space!=std::string::npos) {
      if (pipe==std::string::npos ) {
	names.erase(space, 1);
	space=names.find_first_of(" ", space);
      }
      else if (coma!=std::string::npos && coma>pipe) {
	names.erase(space, 1);
	space=names.find_first_of(" ", space);
      } else {
	space=names.find_first_of(" ", space+1);
      }
      pipe=names.find_last_of("|", space);
      coma=names.find_last_of(",", space);
    }
    std::vector<std::string> items = itemizeString(names, ",");
    if (pad.second[0]=="overlay" || pad.second[0]=="stack") {
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

  std::cout<<"pad list:\n";
  for (size_t i=0; i<pads.size(); i++) {
    for (size_t j=0; j<pads[i].first.size(); j++) std::cout<<pads[i].first[j]<<" ";
    std::cout<<pads[i].second[0]<<" "<<pads[i].second[1]<<" "<<pads[i].second[2]<<std::endl;
  }

  // Prepare canvass ----------------------------------------------------------

  for (size_t i=0; i<legend_.size(); i++) {
    delete legend_[i];
    delete frame_[i];
  }
  stack_.clear();
  legend_.clear();
  frame_.clear();
  can_->Clear();

  if (nrows<0) nrows=pads.size()/ncols;
  if (ncols*nrows<int(pads.size())) nrows=pads.size()/ncols+1;
  can_->Divide(ncols, nrows);

  // Draw pads ----------------------------------------------------------------

  std::cout<<"drawing pads"<<std::endl;
  for (size_t i=0; i<pads.size(); i++) {
    can_->cd(i+1);
    double min=0, max=0;
    std::string lastHist="";

    // Drop plots if not found and calculate stack  ---------------------------

    for (int j=pads[i].first.size()-1; j>=0; j--) {
      std::pair<std::string,std::string> nameRest;
      nameRest=splitString(pads[i].first[j], "|");
      std::cout<<j<<" "<<nameRest.first<<" | "<<nameRest.second<<std::endl;
      H *h=NULL;
      
      typename std::map<std::string,Histogram<H> >::iterator it;
      size_t pos;
      if ((pos=nameRest.first.find(".num"))!=std::string::npos) {
	std::string name=nameRest.first;
	name.erase(pos, 4);
	if ((it=this->find(name))!=this->end()) h=it->second.num();
      } else if ((pos=nameRest.first.find(".den"))!=std::string::npos) {
	std::string name=nameRest.first;
	name.erase(pos, 4);
	if ((it=this->find(name))!=this->end()) h=it->second.den();
      } else {
	if ((it=this->find(nameRest.first))!=this->end()) h=&(it->second);
      }

      if (h==NULL) { 
	std::cout << "Histogram "<<nameRest.first<<" not found\n";
	pads[i].first.erase(pads[i].first.begin()+j); 
	continue; 
      }
      if (j==int(pads[i].first.size())-1) {
	max=h->GetMaximum();
	min=h->GetMinimum();
      }
      if (max<h->GetMaximum()) max=h->GetMaximum();
      if (min>h->GetMinimum()) min=h->GetMinimum();
      std::cout<<nameRest.first<<" -> "<<h->GetName()<<std::endl;

      if (pads[i].second[0]!="stack") continue;

      stack_[nameRest.first]=(*h);
      if (lastHist=="") {
	lastHist=nameRest.first;
      } else {
	typename std::map<std::string,H>::iterator ith;
	ith=stack_.find(nameRest.first);
	ith->second.Add(&stack_[lastHist]);
	max=ith->second.GetMaximum();
	min=ith->second.GetMinimum();
	lastHist=nameRest.first;
      }
    }

    // Make record of empty pad and move on -----------------------------------

    std::cout<<"Pad "<<i<<std::endl;
    for (size_t j=0; j<pads[i].first.size(); j++) std::cout<<pads[i].first[j]<<" ";
    std::cout<<pads[i].second[0]<<" "<<pads[i].second[1]<<" "<<pads[i].second[2]<<std::endl;

    if (pads[i].first.size()==0) {
      legend_.push_back(NULL);
      frame_.push_back(NULL);
      continue;
    }

    // Plot the remaining histograms in this pad  -----------------------------

    std::ostringstream opt;
    opt << pads[i].second[1];
    std::string lastLeg="";

    for (size_t j=0; j<pads[i].first.size(); j++) {
      std::vector<std::string> nameLegendTitle;
      nameLegendTitle=itemizeString(pads[i].first[j], "|");
      std::string hist=nameLegendTitle[0];

      H* h=NULL;
      if (pads[i].second[0]!="stack") {
	typename std::map<std::string,Histogram<H> >::iterator it;
	size_t pos;
	if ((pos=hist.find(".num"))!=std::string::npos) {
	  hist.erase(pos, 4);
	  if ((it=this->find(hist))!=this->end()) h=it->second.num();
	} else if ((pos=hist.find(".den"))!=std::string::npos) {
	  hist.erase(pos, 4);
	  if ((it=this->find(hist))!=this->end()) h=it->second.den();
	} else {
	  if ((it=this->find(hist))!=this->end()) h=(H*)&(it->second);
	}
      } else {
	h=&stack_[hist];
      }

      if (j==0) {
	H* hc=(H*)h->DrawCopy(opt.str().data());
	opt << "SAME";
	frame_.push_back(hc);
	std::ostringstream ss;
	ss << "frame_" << i;
	frame_[i]->SetName(ss.str().data());
	std::cout<<i<<" "<<hist<<" -> "<<frame_[i]->GetName()<<std::endl;
	frame_[i]->SetAxisRange(min, max*1.05, "Y");
	if (pads[i].second[2]!="") {
	  frame_[i]->SetTitle(pads[i].second[2].data());
	}
	legend_.push_back(NULL);
      }

      if (legend_[i]==NULL&&nameLegendTitle.size()>1) {
	if (nameLegendTitle.size()>2) {
	  lastLeg=nameLegendTitle[2];
	  legend_[i]=new TLegend(0.8, 0.75, 0.95, 0.80);
	  legend_[i]->AddEntry((TObject*)NULL, lastLeg.data(),"h");
	  legend_[i]->SetY1(legend_[i]->GetY1()-0.05);
	} else {
	  legend_[i]=new TLegend(0.8, 0.75, 0.95, 0.80);
	}
      }

      std::cout<<hist<<" -> "<<h->GetName()<<" opt:"<<opt.str()<<std::endl;
      h->Draw(opt.str().data());
      if (nameLegendTitle.size()>1) {
	if (nameLegendTitle.size()>2 && lastLeg!=nameLegendTitle[2]) {
	  legend_[i]->AddEntry((TObject*)NULL, nameLegendTitle[2].data(),"h");
	  legend_[i]->SetY1(legend_[i]->GetY1()-0.05);
	}
	legend_[i]->AddEntry(h, nameLegendTitle[1].data());
	legend_[i]->SetY1(legend_[i]->GetY1()-0.05);
      }
    }

    frame_[i]->Draw("AXISSAME");
    if (legend_[i]!=NULL) {
      std::cout<<"drawing legend\n";
      legend_[i]->Draw();
    }
    // End of this pad --------------------------------------------------------

  }

  can_->Update();
  if (style_!="") setPlotStyle(style_);
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
  std::ostringstream sdir;
  sdir<<can_->GetName()<<"_HIST";
  TDirectory *dir=gDirectory->GetDirectory(sdir.str().data());
  if (!dir) dir=gDirectory->mkdir(sdir.str().data(), sdir.str().data());
  dir->cd();

  typename std::map<std::string,Histogram<H> >::iterator it;
  for (it=this->begin(); it!=this->end(); it++) {
    it->second.Write();
  }

  gDirectory->cd("../");
  can_->Write();
}


//------------------------------------ Scale() --------------------------------

template <class H>
void Plot<H>::scaleMaximumTo(std::string kind, double maximum) {
  typename std::map<std::string,Histogram<H> >::iterator it;
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
  typename std::map<std::string,Histogram<H> >::iterator it;
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


//-----------------------------------------------------------------------------

template <class H> 
void Plot<H>::setPlotStyle(std::string style) {

  if (getNPads()==0) return;

  if (style.find("TDR")!=std::string::npos || 
      style.find("tdr")!=std::string::npos ) {

    // For the canvas:
    can_->SetBorderMode(0);
    can_->SetFillColor(kWhite);
    can_->SetWindowSize(600+(600-can_->GetWw()), 600+(600-can_->GetWh()));    
    
    // For the Pad:
    for (int i=0; i<getNPads(); i++) {
      TVirtualPad *ipad=can_->GetPad(i+1);
      if (ipad==NULL) continue;
      ipad->SetBorderMode(0);
      ipad->SetFillColor(kWhite);
      ipad->SetBorderSize(1);
      ipad->SetGridx(false);
      ipad->SetGridy(true);
      //ipad->SetGridColor(0);
      //ipad->SetGridStyle(3);
      //ipad->SetGridWidth(1);
      ipad->SetTickx(1);  
      ipad->SetTicky(1);

      // Margins:
      ipad->SetMargin(0.16, 0.02, 0.13, 0.05);
 
      // For the frame:
      TFrame *f=ipad->GetFrame();
      if (f!=NULL) {
	ipad->SetFrameFillColor(kWhite);
	ipad->SetFrameBorderMode(0);
	ipad->SetFrameBorderSize(1);
	ipad->SetFrameFillStyle(0);
	ipad->SetFrameLineColor(1);
	ipad->SetFrameLineStyle(1);

	f->SetFillColor(kWhite);
	f->SetBorderMode(0);
	f->SetBorderSize(1);
	f->SetFillStyle(0);
	f->SetLineColor(1);
	f->SetLineStyle(1);
      }

      // Histo in frame:

      if (int(frame_.size())>i && frame_[i]!=NULL) {
	// Stat
	TPaveStats *st = (TPaveStats*)frame_[i]->FindObject("stats");
	if (st!=NULL) {
	  st->SetOptStat(1100);
	  st->SetFillColor(kWhite);
	  st->SetTextFont(42);
	  st->SetTextSize(0.04);
	  st->SetTextColor(1);
	  st->SetStatFormat("6.4g");
	  st->SetBorderSize(1);
	  st->SetY1(st->GetY1()-0.1);
	  st->SetX1(st->GetX1()-0.2);
	}

// 	// Title:
// 	frame_[i]->SetFillColor(kWhite); // Was 10 in tdrStyle()
// 	frame_[i]->SetFillStyle(1001);
// 	frame_[i]->SetTextFont(42);
// 	frame_[i]->SetTextSize(0.05);
// 	frame_[i]->SetTextColor(1);
// 	frame_[i]->SetBorderSize(2);
// 	frame_[i]->SetX1(0.1);
// 	frame_[i]->SetY1(0.985);
// 	frame_[i]->SetX2(0);
// 	frame_[i]->SetY2(0);

	frame_[i]->SetFillColor(kWhite);
	frame_[i]->SetFillStyle(0);
	frame_[i]->SetLineColor(1);
	frame_[i]->SetLineStyle(0);
	frame_[i]->SetLineWidth(1);
// 	frame_[i]->SetLegoInnerR(0.5);
// 	frame_[i]->SetNumberContours(20);
// 	frame_[i]->SetEndErrorSize(2);
// 	frame_[i]->SetErrorMarker(20);
// 	frame_[i]->SetErrorX(0.);
	frame_[i]->SetMarkerStyle(20);

	std::vector<std::string> axis;
	axis.push_back("X");
	axis.push_back("Y");
	axis.push_back("Z");
	
	for (size_t j=0; j<axis.size(); j++) {
	  TAxis *a=NULL;
	  if (axis[j]=="X") a=frame_[i]->GetXaxis();
	  if (axis[j]=="Y") a=frame_[i]->GetYaxis();
	  if (axis[j]=="Z") a=frame_[i]->GetZaxis();
	  if (a==NULL) continue;

	  // For the axis titles:
	  a->SetTitleColor(1);
	  a->SetTitleFont(42);
	  a->SetTitleSize(0.06);
	  
	  a->SetTitleOffset(1.1);
	  if (axis[j]=="X") a->SetTitleOffset(0.9);
	  if (axis[j]=="Y") a->SetTitleOffset(1.25);
	  
	  // For the axis labels:
	  
	  a->SetLabelColor(1);
	  a->SetLabelFont(42);
	  a->SetLabelOffset(0.007);
	  a->SetLabelSize(0.05);
	  
	  a->SetAxisColor(1);
	  a->SetTickLength(0.03);
	  a->SetNdivisions(510);
	} // axis

      } // frame

      // Legend:

      if (int(legend_.size())>i && legend_[i]!=NULL) {
	legend_[i]->SetFillColor(kWhite);
	legend_[i]->SetFillStyle(0);
	legend_[i]->SetLineColor(1);
	legend_[i]->SetLineStyle(0);
	legend_[i]->SetLineWidth(1);
	legend_[i]->SetBorderSize(0);
	legend_[i]->SetTextFont(42);
	legend_[i]->SetTextSize(0.06);
      }

    } // pad
    
//     // For the histo:

//     typename std::map<std::string,Histogram<H> >::iterator it;
//     for (it=this->begin(); it!=this->end(); it++) {
//       Histogram<H> *h=&(it->second);
//       //h->SetFillColor(1);
//       h->SetFillStyle(0);
//       //h->SetLineColor(1);
//       h->SetLineStyle(0);
//       h->SetLineWidth(1);
// //       h->SetLegoInnerR(0.5);
// //       h->SetNumberContours(20);
// //       h->SetEndErrorSize(2);
// //       h->SetErrorMarker(20);
// //       h->SetErrorX(0.);
//       h->SetMarkerStyle(20);

//       std::vector<std::string> axis;
//       axis.push_back("X");
//       axis.push_back("Y");
//       axis.push_back("Z");

//       for (size_t j=0; j<axis.size(); j++) {
// 	TAxis *a=NULL;
// 	if (axis[j]=="X") a=h->GetXaxis();
// 	if (axis[j]=="Y") a=h->GetYaxis();
// 	if (axis[j]=="Z") a=h->GetZaxis();
// 	if (a==NULL) continue;

// 	// For the axis titles:
// 	a->SetTitleColor(1);
// 	a->SetTitleFont(42);
// 	a->SetTitleSize(0.06);

// 	a->SetTitleOffset(1.1);
// 	if (axis[j]=="X") a->SetTitleOffset(0.9);
// 	if (axis[j]=="Y") a->SetTitleOffset(1.25);
	
// 	// For the axis labels:
	
// 	a->SetLabelColor(1);
// 	a->SetLabelFont(42);
// 	a->SetLabelOffset(0.007);
// 	a->SetLabelSize(0.05);

// 	a->SetAxisColor(1);
// 	a->SetTickLength(0.03);
// 	a->SetNdivisions(510);

//       } // Axis

//     } // Histograms

//
// L E F T O V E R
//


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
    
    // can_->SetStatStyle(Style_t style = 1001);
    // can_->SetStatX(Float_t x = 0);
    // can_->SetStatY(Float_t y = 0);
    
   
    // For the Global title:
    
    
    // For the axis:
    
    //can_->SetStripDecimals(kTRUE);
    

    // Change for log plots:
//     can_->SetOptLogx(0);
//     can_->SetOptLogy(0);
//     can_->SetOptLogz(0);
    
    // Postscript options:
//     can_->SetPaperSize(20.,20.);
    // can_->SetLineScalePS(Float_t scale = 3);
    // can_->SetLineStyleString(Int_t i, const char* text);
    // can_->SetHeaderPS(const char* header);
    // can_->SetTitlePS(const char* pstitle);
    
    // can_->SetBarOffset(Float_t baroff = 0.5);
    // can_->SetBarWidth(Float_t barwidth = 0.5);
    // can_->SetPaintTextFormat(const char* format = "g");
    // can_->SetPalette(Int_t ncolors = 0, Int_t* colors = 0);
    // can_->SetTimeOffset(Double_t toffset);
    // can_->SetHistMinimumZero(kTRUE);
    
    //   can_->cd();
    
    //gROOT->ForceStyle();

    can_->Update();
  }
}


//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

}
#endif
