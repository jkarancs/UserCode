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

 File handling: 
   - Write() writes selected histograms on the file+path given in the argument.
   This is the recommended method to use.
   - Another possibility to write the histograms into file is to add them to
   a ROOT TDirectory inside the file, and call TFile::Write(). In order to use
   this feature, you need to call setDirectory on the selected histograms
   IMPORTANT: closing the file without removing the directory assignment of
   the histograms in the Plot will crash your code. To sort it out, you are on
   your own.
   - All the above applies to TCanvas, too.

 ROOT TDirectory handling: 
   - all Histograms are created in the memory directory independent. If you 
   want to add selected histograms to a TDirectory, call 
   setDirectory(std::string regexp=""). This will not write the histograms to
   file, just "assigns" them to the TDirectory. 
   - Every copy/clone of the Plot is also put in the memory regardless where 
   the original is located.
   - Operator= does not relocate a Plot, the content of the STL container is
   still created in the memory.

 Histo naming:
   - every histo bears the name of the plot itself (in canName_) and its key
   used in the map separated by an underscore.
   - add() uses the plot name and key to construct the histo name
   - write() saves histos with their full name
   - load() loads histograms into the plot from a plot of given name, the name
   of the original plot is replaced by this plot, the key is kept
   - setName() replaces the plot name in canName_ and renames all histograms in
   the plot (leaves the keys untouched)

// REGEXP cheat-sheet:
//
// ^	The pattern has to appear at the beginning of a string.	^cat matches 
//      any string that begins with cat
// $	The pattern has to appear at the end of a string. cat$ matches any 
//      string that ends with cat
// .	Matches any character.	cat. matches catT and cat2 but not catty
// []	Bracket expression. Matches one of any characters enclosed. gr[ae]y 
//      matches gray or grey
// [^]	Negates a bracket expression. Matches one of any characters EXCEPT 
//      those enclosed. 1[^02] matches 13 but not 10 or 12
// [-]	Range. Matches any characters within the range.	[1-9] matches any 
//      single digit EXCEPT 0
// ?	Preceeding item must match one or zero times. colou?r matches color or
//      colour but not colouur
// +	Preceeding item must match one or more times. be+ matches be or bee 
//      but not b
// *	Preceeding item must match zero or more times.	be* matches b or be or
//      beeeeeeeeee
// ()	Parentheses. Creates a substring or item that metacharacters can be 
//      applied to a(bee)?t matches at or abeet but not abet
// {n}	Bound. Specifies exact number of times for the preceeding item to 
//      match. [0-9]{3} matches any three digits
// {n,}	Bound. Specifies minimum number of times for the preceeding item to 
//      match. [0-9]{3,} matches any three or more digits
// {n,m} Bound. Specifies minimum and maximum number of times for the 
//      preceeding item to match. [0-9]{3,5} matches any three, four, or 
//      five digits
// |	Alternation. One of the alternatives has to match. July (first|1st|1) 
//      will match July 1st but not July 2

// POSIX Character Classes
// [:alnum:]	alphanumeric character	[[:alnum:]]{3} matches any three 
//              letters or numbers, like 7Ds
// [:alpha:]	alphabetic character, any case	[[:alpha:]]{5} matches five 
//              alphabetic characters, any case, like aBcDe
// [:blank:]	space and tab	[[:blank:]]{3,5} matches any three, four, or 
//              five spaces and tabs
// [:digit:]	digits	[[:digit:]]{3,5} matches any three, four, or five 
//              digits, like 3, 05, 489
// [:lower:]	lowercase alphabetics	[[:lower:]] matches a but not A
// [:punct:]	punctuation characters	[[:punct:]] matches ! or . or , but 
//              not a or 3
// [:space:]	all whitespace characters, including newline and carriage 
//              return [[:space:]] matches any space, tab, newline, or 
//              carriage return
// [:upper:]	uppercase alphabetics	[[:upper:]] matches A but not a

// Perl-Style Metacharacters
// //	Default delimiters for pattern	/colou?r/ matches color or colour
// i	Append to pattern to specify a case insensitive match	/colou?r/i 
//      matches COLOR or Colour
// \b	A word boundary, the spot between word (\w) and non-word (\W) 
//      characters /\bfred\b/i matches Fred but not Alfred or Frederick
// \B	A non-word boundary	/fred\B/i matches Frederick but not Fred
// \d	A single digit character	/a\db/i matches a2b but not acb
// \D	A single non-digit character	/a\Db/i matches aCb but not a2b
// \n	The newline character. (ASCII 10)	/\n/ matches a newline
// \r	The carriage return character. (ASCII 13)	/\r/ matches a 
//      carriage return
// \s	A single whitespace character	/a\sb/ matches a b but not ab
// \S	A single non-whitespace character	/a\Sb/ matches a2b but not a b
// \t	The tab character. (ASCII 9)	/\t/ matches a tab.
// \w	A single word character - alphanumeric and underscore	/\w/ matches 1
//      or _ but not ?
// \W	A single non-word character	/a\Wb/i matches a!b but not a2b
*/
//
// Original Author:  Viktor VESZPREMI
//         Created:  Wed Oct 25 20:57:26 CET 2009
// $Id: Plot.hh,v 1.9 2010/04/21 08:45:18 veszpv Exp $
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
#include "TList.h"
#include "TKey.h"
#include <boost/regex.hpp>

#define PLOTDEBUG 0

namespace deb {





//----------------------------- Class Definition ------------------------------

template<class H> class Plot : public std::map<std::string,Histogram<H> > {
 public:

  typedef           Histogram<H>                         HType;
  typedef           std::map<std::string,Histogram<H> >  PlotBase;
  typedef typename  PlotBase::iterator                   iterator;
  typedef typename  PlotBase::const_iterator             const_iterator;


  //
  // Default Constructor
  // 
  Plot () { init(0, 0, ""); }


  //
  // Copy Constructor
  //
  Plot (const Plot<H> &plot) { *this=plot; }


  //
  // Empty Plot Constructor: format=<plot name>[;<plot title>]
  //

  Plot (Int_t ww, Int_t wh, std::string format,...);


  //
  // TH1 constructors: format=<plot name>[;<plot title>[;<histo name>[;...]]]
  //

  Plot (Int_t ww, Int_t wh,
	Int_t nbinsx, Double_t xlow, Double_t xup, 
	std::string format,...);

  Plot (Int_t ww, Int_t wh,
	Int_t nbins, const Float_t *xbins, 
	std::string format,...);

  Plot (Int_t ww, Int_t wh,
	Int_t nbins, const Double_t *xbins, 
	std::string format,...);


  //
  // TH2 constructors: format=<plot name>[;<plot title>[;<histo name>[;...]]]
  //

  Plot (Int_t ww, Int_t wh, 
	Int_t nbinsx, Double_t xlow, Double_t xup, 
	Int_t nbinsy, Double_t ylow, Double_t yup, 
	std::string format,...);

  Plot (Int_t ww, Int_t wh, 
	Int_t nbinsx, const Double_t *xbins, 
	Int_t nbinsy, Double_t ylow, Double_t yup, 
	std::string format,...);
  
  Plot (Int_t ww, Int_t wh, 
	Int_t nbinsx, Double_t xlow, Double_t xup, 
	Int_t nbinsy, const Double_t *ybins, 
	std::string format,...);

  Plot (Int_t ww, Int_t wh, 
	Int_t nbinsx, const Double_t *xbins, 
	Int_t nbinsy, const Double_t *ybins, 
	std::string format,...);

  Plot (Int_t ww, Int_t wh, 
	Int_t nbinsx, const Float_t *xbins, 
	Int_t nbinsy, const Float_t *ybins, 
	std::string format,...);


  //
  // Destructor
  //
  ~Plot() { this->deleteCanvas(); }
  

  //
  // Private data members and fuctions
  //

 private:
  //
  // Variables
  //
  TCanvas* can_;                        // The canvas drawn by Draw()
  Int_t ww_, wh_;
  std::string canName_, canTitle_;
  int ntiles_;

  std::vector<std::string> lastDrawFormat_; // Iportant!!! : 
  int lastDrawNCols_, lastDrawNRows_;      // ---------------------------------
  std::map<std::string,H> stack_;         // These five variables are meant to
  std::vector<TLegend*> legend_;         // be filled simultaneously by Draw()!
  std::vector<H*> frame_;               // ------------------------------------

  std::string style_;

  
  //
  // Functions
  //
  std::string init(Int_t ww, Int_t wh, std::string format);

  std::vector<std::string> generateNameTitleForH(std::string format);
  std::vector<std::string> generateNameTitleForHNew(std::string format);

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

  // general
  inline std::string histNameFromKey(std::string key, std::string pname) {
    return (pname=="") ? key : key.insert(0, pname+"_");
  }

  // applied to this object
  inline std::string histNameFromKey(std::string key) {
    return histNameFromKey(key, canName_);
  }

  // general
  inline std::string keyFromHistName(std::string hname, std::string pname) {
    return (pname=="") ? hname : hname.erase(0, pname.size()+1);
  }

  // applied to this object
  inline std::string keyFromHistName(std::string hname) {
    return keyFromHistName(hname, canName_);
  }

  // general
  inline std::string replacePlotNameInHistName(std::string hname, 
					       std::string newplotname,
					       std::string oldplotname) {
    return histNameFromKey(keyFromHistName(hname, oldplotname), newplotname);
  }

  // applied to this object
  inline std::string replacePlotNameInHistName(std::string hname, 
					       std::string newplotname) {
    return histNameFromKey(keyFromHistName(hname, canName_), newplotname);
  }

  //
  // Public functions
  //

 public:

  // delete canvas
  //
  void deleteCanvas() {
    for(size_t i=0; i<frame_.size(); i++) {
      if (frame_[i]!=NULL) delete frame_[i];
    }
    frame_.clear();
    for(size_t i=0; i<legend_.size(); i++) {
      if (legend_[i]!=NULL) delete legend_[i];
    }
    legend_.clear();
    stack_.clear();

    if (can_!=NULL) delete can_;    
    can_=NULL;
  }


  // Assignment operator
  //
  Plot<H>& operator= (const Plot<H> &plot) {
    *dynamic_cast<PlotBase*>(this) = dynamic_cast<const PlotBase&>(plot);
    this->setDirectory(0);
    can_ = NULL;
    ww_ = plot.ww_; 
    wh_ = plot.wh_;
    canName_ = plot.canName_;
    canTitle_ = plot.canTitle_;
    ntiles_ = 0;
    lastDrawFormat_ = plot.lastDrawFormat_;
    lastDrawNCols_ = plot.lastDrawNCols_;
    lastDrawNRows_ = plot.lastDrawNRows_;
    style_ = plot.style_;
    return *this;
  }


  // Canvas operations
  bool                   isDrawn()     { return (can_==NULL) ? false : true; }
  TCanvas*               canvas()      { return can_; }
  std::vector<TLegend>   legend()      { return legend_; }
  std::vector<H*>        frames()      { return frame_; }
  int                    getNPads()    { return frame_.size(); }
  int                    getMaxNPads() { return ntiles_; }

  std::vector<std::string> getLastDrawFormat() { return lastDrawFormat_; }
  std::string              getLastDrawNCols()  { return lastDrawNCols_;  }
  std::string              getLastDrawNRows()  { return lastDrawNRows_;  }

  // Add histograms to plot
  void add(const Histogram<H>& h, std::string format,...);

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

  

  // Accessors
  // IMPORTANT!!! OPERATORS () and [] do not use regexp. This is to make sure
  // that the matching is unambiguous.
  Histogram<H>& operator()(size_t i) { return (*this)("[%d]", i); }

  Histogram<H>& operator()(size_t i, size_t j) { 
    return (*this)("[%d][%d]", i, j); 
  }

  Histogram<H>& operator()(size_t i, size_t j, size_t k) { 
    return (*this)("[%d][%d][%d]", i, j, k); 
  }

  // NOTE: operator() does not use regular expression
  Histogram<H>& operator()(std::string format, ...);


  // Search
  // NOTE: "[" and "]" need to be escaped by "\" for search()
  std::vector<iterator> search(std::string format_regexpr, ...);


  // Compound operations on histograms (for individuals use operators (), [])
  // by regular expressions. Most of the time using variable parameters in when
  // constructing the regular expression would be an overcomplication. For 
  // such effect, functions should be combined with search(format_regexpr, ...)

  void efficiency(std::string format_regexpr="", ...);
  void efficiency(std::vector<iterator> list);


  void setSumw2(std::string format_regexpr="", ...);
  void setSumw2(std::vector<iterator> list);


  void setColor(std::string regexpr, std::string attr, 
		Color_t color, int step=0);
  void setColor(std::vector<iterator> list, std::string what="", 
		std::string attr, Color_t color, int step=0);


  void setDirectory(TDirectory *dir=NULL);
  void setDirectory(std::string regexpr, TDirectory *dir);
  void setDirectory(std::vector<iterator> list, TDirectory *dir);


  void setStyle(std::string regexpr, std::string attr, Style_t style);
  void setStyle(std::vector<iterator> list, std::string what="", 
		std::string attr, Style_t style);


  void setWidth(std::string regexpr, std::string attr, Width_t width);
  void setWidth(std::vector<iterator> list, std::string what="",
		std::string attr, Width_t width);


  void setAxisRange(std::string regexpr, Double_t xmin, Double_t xmax, 
		    Option_t* axis = "X");
  void setAxisRange(std::vector<iterator> list, std::string what="",
		    Double_t xmin, Double_t xmax, Option_t* axis = "X");


  void scaleMaximumTo(std::string regexpr, double maximum=1.0);
  void scaleMaximumTo(std::vector<iterator> list, std::string what="", 
		      double maximum=1.0);


  void scaleAreaTo(std::string regexpr, double area=1.0);
  void scaleAreaTo(std::vector<iterator> list, std::string what="", 
		   double area=1.0);


  int  Draw(std::vector<std::string> hists, int ncols=1, int nrows=-1);
  int  Draw(std::string hist, int ncols=1, int nrows=-1);
  //Not implemented: int Draw(std::string regexpr, int ncols=1,int nrows=-1);
  //Not implemented: int Draw(std::vector<iterator>, int ncols=1,int nrows=-1);


  int redraw() {
    deleteCanvas();
    if (lastDrawFormat_.size()) {
      return this->Draw(lastDrawFormat_, lastDrawNCols_, lastDrawNRows_);
    }
    return 0;
  }


  // Plot level operations
  void Write();

  void clear() {
    PlotBase::clear();
    deleteCanvas();
  }

  //
  // Load entire plot 'name' and replace current content with it
  //
  int  load(std::string name=""); // returns 0 if no error occured

  //
  // Load histograms in plot 'name' on file that match regexp
  //
  int  load(std::string name, std::string format_regexpr, ...) { // 0: no error
    va_list argList;
    va_start(argList, format_regexpr);
    char s[10000];
    vsprintf(s, format_regexpr.data(), argList);
    va_end(argList);
    Plot<H> temp;
    int ret=temp.load(name);
    clear();
    append(temp, temp.search(s));
    return ret;
  }


  void setName(std::string name);
  std::string getName() const          { return canName_; }

  void print();

  //
  // Append all histograms in 'plot' to this one
  //
  void append(const Plot<H>& plot) {
    Plot<H> temp(plot);
    temp.setName(canName_);
    this->insert(temp.begin(), temp.end());    
    this->setDirectory(0);
  }

  //
  // Append histogramss in 'plot' that are listed in 'list'. Note: 'list' can 
  // be generated by plot.search("what we want to select")
  //
  void append(const Plot<H>& plot, std::vector<iterator> list) {
    for (size_t i=0; i<list.size(); i++) {
      (*this)[list[i]->first]=list[i]->second;
      iterator it=this->find(list[i]->first);
      it->second.setDirectory(0);
      it->second.setName(replacePlotNameInHistName(it->second.GetName(),
						   canName_, plot.getName()));
    }
  }

  void setPlotStyle(std::string);

  //void setOptStat(int);

//   void addText(float x1, float y1, float x2, float y2, std::string text) {
//     TPaveText text(0.3, 0.3, 0.5, 0.8)
//       text.AddText("Valami")
//       root [15] text.SetFillColor(0)
//       root [16] text.SetBorderSize(0)
//       root [17] text.Draw()
//       root [18] text.SetFillStyle(0)
//       root [19] text.SetTextSize(0.06)
//       root [20] text.SetTextFont(42)
//       root [21] text.Draw()
      
//       }


};




//-----------------------------------------------------------------------------
//------------------------------ Implementations  -----------------------------
//-----------------------------------------------------------------------------




//--------------------------------- init --------------------------------------

template<class H>
std::string Plot<H>::init(Int_t ww, Int_t wh, std::string format) {

  std::pair<std::string,std::string> nameTitle=splitString(format, ";");
  std::ostringstream histNameTitle("");
  style_="";

  if (nameTitle.first.find_first_of("\n")!=std::string::npos) {
    std::pair<std::string,std::string> nameStyle;
    nameStyle=splitString(nameTitle.first, "\n");
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

  if (ww==0) ww = 600;
  if (wh==0) wh = 600;

  can_ = NULL;
  ww_ = ww; 
  wh_ = wh;
  canName_ = nameTitle.first;
  canTitle_ = nameTitle.second;
  ntiles_ = 0;
  lastDrawNCols_= 0;
  lastDrawNRows_= 0;

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


//------------------------ generateNameTitleForHNew() -------------------------

template <class H>
std::vector<std::string> Plot<H>::generateNameTitleForHNew(std::string format){

  std::pair<std::string,std::string> nameRest=splitString(format, ";");

  std::vector<size_t> count;
  if (nameRest.first.find_first_of("@")!=std::string::npos) {

    std::pair<std::string,std::string> nameNumber;
    nameNumber=splitString(nameRest.first,"@");
    nameRest.first=nameNumber.first;
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
    if (nameRest.first=="") return ret;
    
    std::string fullname;
    //    fullname << can_->GetName() << "_" << nameRest.first;
    // fullname << canName_ << "_" << nameRest.first;
    fullname=histNameFromKey(nameRest.first);

    ret.push_back(nameRest.first);
    ret.push_back(fullname);
    ret.push_back(format.find_first_of(";")!=std::string::npos ?
		  nameRest.second : canTitle_);
    //		  nameRest.second : can_->GetTitle());
    return ret;
  }

  for (size_t i=0; i<count.size(); i++) {
    int ret_size=ret.size();
    for (int k= (ret_size ? 0 : -3); k<ret_size; k+=3) {
      for (size_t j=0; j<count[i]; j++) {
	std::ostringstream index;
	index << (k<0 ? nameRest.first : ret[k]) << "[" << j << "]";
	
	std::string fullname;
	//	fullname << can_->GetName() << "_" << index.str();
	//fullname << canName_ << "_" << index.str();
	fullname=histNameFromKey(nameRest.first);

	std::string title;
	if (k<0) {
	  title = format.find_first_of(";")!=std::string::npos ? 
	          nameRest.second : canTitle_;
	  //	          nameRest.second : can_->GetTitle();
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

	std::cout << "i,j,k = " << i << " " << j << " " << k << " " << fullname
		  << " " << title << std::endl;
	
	ret.push_back(index.str());
	ret.push_back(fullname);      
	ret.push_back(title);
      }
    }
    if (ret_size) ret.erase(ret.begin(), ret.begin()+ret_size);
  }
  
  return ret;
}


//------------------------ generateNameTitleForH() ----------------------------

template <class H>
std::vector<std::string> Plot<H>::generateNameTitleForH(std::string format){

  std::pair<std::string,std::string> nameTitle=splitString(format, ";");
  std::pair<std::string,std::string> nameLegend;
  nameLegend=splitString(nameTitle.first, "!");

  std::vector<std::string> ret;
  if (nameLegend.first=="") return ret;
  ret.push_back(nameLegend.first);

//   std::ostringstream fullname;
//   fullname << canName_ << "_" << nameLegend.first;
  ret.push_back(histNameFromKey(nameLegend.first));

  ret.push_back(format.find_first_of(";")!=std::string::npos ?
		nameTitle.second : canTitle_);

  std::pair<std::string,std::string> legendHead;
  legendHead=splitString(nameLegend.second, "!");
  ret.push_back(legendHead.first);
  ret.push_back(legendHead.second);
  return ret;

}


//---------------------------------- add() ------------------------------------

template <class H> 
void Plot<H>::add(const Histogram<H>& h, std::string format,...) {

  va_list argList;
  va_start(argList, format);
  char s[10000];
  vsprintf(s, format.data(), argList);

  std::vector<std::string> labels=generateNameTitleForH(s);
  for (size_t i=0; i<labels.size(); i+=5) {
    (*this)[labels[i]]=h;
    (*this)[labels[i]].SetName(labels[i+1].data());
    (*this)[labels[i]].SetTitle(labels[i+2].data());
    (*this)[labels[i]].setDirectory(0);
    (*this)[labels[i]].setLegend(labels[i+3], labels[i+4]);
  }
}

template <class H> void Plot<H>::add(Int_t nbinsx, Double_t xlow, Double_t xup,
				     std::string format,...) {
  va_list argList;
  va_start(argList, format);
  char s[10000];
  vsprintf(s, format.data(), argList);

  std::vector<std::string> labels=generateNameTitleForH(s);
  for (size_t i=0; i<labels.size(); i+=5) {
    (*this)[labels[i]]=Histogram<H>(labels[i+1].data(), labels[i+2].data(), 
				    nbinsx, xlow, xup);
    (*this)[labels[i]].setDirectory(0);
    (*this)[labels[i]].setLegend(labels[i+3], labels[i+4]);
  }
}

  // NEED TO REVISE IMPLEMENTATIONS (USE THE ONE ABOVE AS AN EXAMPLE)

// template <class H> void Plot<H>::add(Int_t nbins, const Float_t *xbins, 
// 				     std::string format,...) { 
//   va_list argList;
//   va_start(argList, format);
//   char s[10000];
//   vsprintf(s, format.data(), argList);

//   std::vector<std::string> labels=generateNameTitleForH(s);
//   (*this)[labels[0]]=Histogram<H>(labels[1].data(), labels[2].data(), 
// 				  nbins, xbins);
//   (*this)[labels[0]].setLegend(labels[3], labels[4]);
// }


// template <class H> void Plot<H>::add(Int_t nbins, const Double_t *xbins,
// 				     std::string format,...) { 
//   va_list argList;
//   va_start(argList, format);
//   char s[10000];
//   vsprintf(s, format.data(), argList);

//   std::vector<std::string> labels=generateNameTitleForH(s);
//   (*this)[labels[0]]=Histogram<H>(labels[1].data(), labels[2].data(), 
// 				  nbins, xbins);
//   (*this)[labels[0]].setLegend(labels[3], labels[4]);
// }


template <class H> void Plot<H>::add(Int_t nbinsx, Double_t xlow, Double_t xup,
				     Int_t nbinsy, Double_t ylow, Double_t yup,
				     std::string format,...) { 
  va_list argList;
  va_start(argList, format);
  char s[10000];
  vsprintf(s, format.data(), argList);

  std::vector<std::string> labels=generateNameTitleForH(s);
  for (size_t i=0; i<labels.size(); i+=5) {
    (*this)[labels[i]]=Histogram<H>(labels[i+1].data(), labels[i+2].data(), 
				    nbinsx, xlow, xup, nbinsy, ylow, yup);
    (*this)[labels[i]].setDirectory(0);
    (*this)[labels[i]].setLegend(labels[i+3], labels[i+4]);
  }
}


// template <class H> void Plot<H>::add(Int_t nbinsx, const Double_t *xbins, 
// 				     Int_t nbinsy, Double_t ylow, Double_t yup,
// 				     std::string format,...) { 
//   va_list argList;
//   va_start(argList, format);
//   char s[10000];
//   vsprintf(s, format.data(), argList);

//   std::vector<std::string> labels=generateNameTitleForH(s);
//   (*this)[labels[0]]=Histogram<H>(labels[1].data(), labels[2].data(), 
// 		       nbinsx, xbins, nbinsy, ylow, yup);
// }


// template <class H> void Plot<H>::add(Int_t nbinsx, Double_t xlow, Double_t xup,
// 				     Int_t nbinsy, const Double_t *ybins, 
// 				     std::string format,...) { 
//   va_list argList;
//   va_start(argList, format);
//   char s[10000];
//   vsprintf(s, format.data(), argList);

//   std::vector<std::string> labels=generateNameTitleForH(s);
//   (*this)[labels[0]]=Histogram<H>(labels[1].data(), labels[2].data(), 
// 				  nbinsx, xlow, xup, nbinsy, ybins);
//   (*this)[labels[0]].setLegend(labels[3], labels[4]);
// }


// template <class H> void Plot<H>::add(Int_t nbinsx, const Double_t *xbins, 
// 				     Int_t nbinsy, const Double_t *ybins, 
// 				     std::string format,...) { 
//   va_list argList;
//   va_start(argList, format);
//   char s[10000];
//   vsprintf(s, format.data(), argList);

//   std::vector<std::string> labels=generateNameTitleForH(s);
//   (*this)[labels[0]]=Histogram<H>(labels[1].data(), labels[2].data(), 
// 				  nbinsx, xbins, nbinsy, ybins);
//   (*this)[labels[0]].setLegend(labels[3], labels[4]);
// }


// template <class H> void Plot<H>::add(Int_t nbinsx, const Float_t *xbins, 
// 				     Int_t nbinsy, const Float_t *ybins, 
// 				     std::string format,...) { 
//   va_list argList;
//   va_start(argList, format);
//   char s[10000];
//   vsprintf(s, format.data(), argList);

//   std::vector<std::string> labels=generateNameTitleForH(s);
//   (*this)[labels[0]]=Histogram<H>(labels[1].data(), labels[2].data(), 
// 				  nbinsx, xbins, nbinsy, ybins);
//   (*this)[labels[0]].setLegend(labels[3], labels[4]);
// }


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


//---------------------------------- search() ---------------------------------

template <class H>
std::vector<typename Plot<H>::iterator> 
Plot<H>::search(std::string format_regexpr, ...) {

  va_list argList;
  va_start(argList, format_regexpr);
  char s[10000];
  vsprintf(s, format_regexpr.data(), argList);
  va_end(argList);

  std::vector<iterator> ret;
  boost::regex e(s);
  for (iterator it=this->begin(); it!=this->end(); it++) {
    boost::match_results<std::string::const_iterator> what;
//     if (boost::regex_match(it->first, what, e, 
// 			   boost::match_default | boost::match_partial)) {
    if (boost::regex_match(it->first, what, e, 
			   boost::match_default)) {
      ret.push_back(it);
    }
  }
  return ret;
}



//-------------------------------- efficiency() -------------------------------

template <class H>  
void Plot<H>::efficiency(std::string format_regexpr, ...) {

  if (format_regexpr=="") {
    typename std::map<std::string,Histogram<H> >::iterator it;
    for (it=this->begin(); it!=this->end(); it++) it->second.efficiency();
    return;
  }

  va_list argList;
  va_start(argList, format_regexpr);
  char s[10000];
  vsprintf(s, format_regexpr.data(), argList);
  this->efficiency(search(s));
}


template <class H>  
void Plot<H>::efficiency(std::vector<typename Plot<H>::iterator> list) {
  for (size_t i=0; i<list.size(); i++) list[i]->second.efficiency();
}


//------------------------------- setSumw2() ----------------------------------

template <class H>  
void Plot<H>::setSumw2(std::string format_regexpr, ...) {

  if (format_regexpr=="") {
    typename std::map<std::string,Histogram<H> >::iterator it;
    for (it=this->begin(); it!=this->end(); it++) it->second.Sumw2();
    return;
  }

  va_list argList;
  va_start(argList, format_regexpr);
  char s[10000];
  vsprintf(s, format_regexpr.data(), argList);
  this->setSumw2(search(s));
}


template <class H>  
void Plot<H>::setSumw2(std::vector<typename Plot<H>::iterator> list) {
  for (size_t i=0; i<list.size(); i++) list[i]->second.Sumw2();
}


//---------------------------------- setColor() -------------------------------

template <class H> 
void Plot<H>::setColor(std::vector<typename Plot<H>::iterator> list, 
		       std::string what, 
		       std::string attr, Color_t color, int step) {
  int k=0;
  if (what.find("num")!=std::string::npos) k=1;
  if (what.find("den")!=std::string::npos) k=-1;
  
  for (size_t i=0; i<list.size(); i++) {
    if (attr.find("Line")!=std::string::npos || 
	attr.find("line")!=std::string::npos) {
      if (k) {
	if (k>0) {
	  if (list[i]->second.num()) {
	    list[i]->second.num()->SetLineColor(color+step*i);
	  }
	} else {
	  if (list[i]->second.den()) {
	    list[i]->second.den()->SetLineColor(color+step*i);
	  }
	}
      } else {
	list[i]->second.SetLineColor(color+step*i);
      }
    }
    if (attr.find("Fill")!=std::string::npos || 
	attr.find("fill")!=std::string::npos) {
      if (k) {
	if (k>0) {
	  if (list[i]->second.num()) {
	    list[i]->second.num()->SetFillColor(color+step*i);
	  }
	} else {
	  if (list[i]->second.den()) {
	    list[i]->second.den()->SetFillColor(color+step*i);
	  }
	}
      } else {
	list[i]->second.SetFillColor(color+step*i);
      }
    }
    if (attr.find("Marker")!=std::string::npos || 
	attr.find("marker")!=std::string::npos) {
      if (k) {
	if (k>0) {
	  if (list[i]->second.num()) {
	    list[i]->second.num()->SetMarkerColor(color+step*i);
	  }
	} else {
	  if (list[i]->second.den()) {
	    list[i]->second.den()->SetMarkerColor(color+step*i);
	  }
	}
      } else {
	list[i]->second.SetMarkerColor(color+step*i);
      }
    }
  }
}


template <class H> 
void Plot<H>::setColor(std::string regexpr, std::string attr, 
		       Color_t color, int step) {
  if (regexpr.size()>4) {
    std::string ext=regexpr.substr(regexpr.size()-4, 4);
    if (ext!=".den" && ext!=".num") {
      ext="";
    }
    setColor(search(regexpr), ext, attr, color, step);
    return;
  }
  setColor(search(regexpr), "", attr, color, step);
  return;
}


//-------------------------------- setDirectory() -----------------------------

template <class H> 
void Plot<H>::setDirectory(std::vector<typename Plot<H>::iterator> list, 
			   TDirectory* dir) {
  
  for (size_t i=0; i<list.size(); i++) list[i]->second.setDirectory(dir);
}


template <class H> 
void Plot<H>::setDirectory(std::string regexpr, TDirectory* dir) {

  setDirectory(search(regexpr), dir);

}


template <class H> 
void Plot<H>::setDirectory(TDirectory* dir) {  
    
  for (iterator it=this->begin(); it!=this->end(); it++) {
    it->second.setDirectory(dir);
  }
  
}


//---------------------------------- setStyle() -------------------------------

template <class H> 
void Plot<H>::setStyle(std::vector<typename Plot<H>::iterator> list, 
		       std::string what,
		       std::string attr, Style_t style) {

  int k=0;
  if (what.find("num")!=std::string::npos) k=1;
  if (what.find("den")!=std::string::npos) k=-1;

  for (size_t i=0; i<list.size(); i++) {
    if (attr.find("Line")!=std::string::npos || 
	attr.find("line")!=std::string::npos) {
      if (k) {
	if (k>0) {
	  if (list[i]->second.num()) {
	    list[i]->second.num()->SetLineStyle(style);
	  }
	} else {
	  if (list[i]->second.den()) {
	    list[i]->second.den()->SetLineStyle(style);
	  }
	}
      } else {
	list[i]->second.SetLineStyle(style);
      }
    }
    if (attr.find("Fill")!=std::string::npos || 
	attr.find("fill")!=std::string::npos) {
      if (k) {
	if (k>0) {
	  if (list[i]->second.num()) {
	    list[i]->second.num()->SetFillStyle(style);
	  }
	} else {
	  if (list[i]->second.den()) {
	    list[i]->second.den()->SetFillStyle(style);
	  }
	}
      } else {
	list[i]->second.SetFillStyle(style);
      }
    }
  }
}


template <class H> 
void Plot<H>::setStyle(std::string regexpr, std::string attr, Style_t style) {
  if (regexpr.size()>4) {
    std::string ext=regexpr.substr(regexpr.size()-4, 4);
    if (ext!=".den" && ext!=".num") {
      ext="";
    }
    setStyle(search(regexpr), ext, attr, style);
    return;
  }
  setStyle(search(regexpr), "", attr, style);
  return;
}


//-------------------------------- setWidth() ---------------------------------

template <class H> 
void Plot<H>::setWidth(std::vector<typename Plot<H>::iterator> list, 
		       std::string what,
		       std::string attr, Width_t width) {

  int k=0;
  if (what.find("num")!=std::string::npos) k=1;
  if (what.find("den")!=std::string::npos) k=-1;
  
  for (size_t i=0; i<list.size(); i++) {
    if (attr.find("Line")!=std::string::npos || 
	attr.find("line")!=std::string::npos) {
      if (k) {
	if (k>0) {
	  if (list[i]->second.num()) {
	    list[i]->second.num()->SetLineWidth(width);
	  }
	} else {
	  if (list[i]->second.den()) {
	    list[i]->second.den()->SetLineWidth(width);
	  }
	}
      } else {
	list[i]->second.SetLineWidth(width);
      }
    }
  }
}


template <class H> 
void Plot<H>::setWidth(std::string regexpr, std::string attr, Width_t width) {
  if (regexpr.size()>4) {
    std::string ext=regexpr.substr(regexpr.size()-4, 4);
    if (ext!=".den" && ext!=".num") {
      ext="";
    }
    setWidth(search(regexpr), ext, attr, width);
    return;
  }
  setWidth(search(regexpr), "", attr, width);
  return;
}


//-------------------------------- setAxisRange() -----------------------------

template <class H>
void Plot<H>::setAxisRange(std::vector<typename Plot<H>::iterator> list, 
			   std::string what,
			   Double_t xmin, Double_t xmax, Option_t* axis){
  int k=0;
  if (what.find("num")!=std::string::npos) k=1;
  if (what.find("den")!=std::string::npos) k=-1;

  for (size_t i=0; i<list.size(); i++) {
    if (k) {
      if (k>0) {
	if (list[i]->second.num()) {
	  list[i]->second.num()->SetAxisRange(xmin, xmax, axis);
	}
      } else {
	if (list[i]->second.den()) {
	  list[i]->second.den()->SetAxisRange(xmin, xmax, axis);
	}
      }
    } else {
      list[i]->second.SetAxisRange(xmin, xmax, axis);
    }
  }
}


template <class H>
void Plot<H>::setAxisRange(std::string regexpr, 
			   Double_t xmin, Double_t xmax, Option_t* axis){
  if (regexpr.size()>4) {
    std::string ext=regexpr.substr(regexpr.size()-4, 4);
    if (ext!=".den" && ext!=".num") {
      ext="";
    }
    setAxisRange(search(regexpr), ext, xmin, xmax, axis);
    return;
  }
  setAxisRange(search(regexpr), "", xmin, xmax, axis);
  return;
}


//------------------------------------ Scale() --------------------------------

template <class H>
void Plot<H>::scaleMaximumTo(std::vector<iterator> list, std::string what,
			     double maximum) {

  int k=0;
  if (what.find("num")!=std::string::npos) k=1;
  if (what.find("den")!=std::string::npos) k=-1;

  for (size_t i=0; i<list.size(); i++) {
    double max;
    if (k) {
      if (k>0) {
	if (list[i]->second.num()) {
	  max=list[i]->second.num()->GetMaximum();
	  if (max!=0.) list[i]->second.num()->Scale(maximum/max);
	}
      } else {
	if (list[i]->second.den()) {
	  max=list[i]->second.den()->GetMaximum();
	  if (max!=0.) list[i]->second.den()->Scale(maximum/max);
	}
      }
    } else {
      max=list[i]->second.GetMaximum();
      if (max!=0.) list[i]->second.Scale(maximum/max);
    }
  }
  return;
}


template <class H>
void Plot<H>::scaleMaximumTo(std::string regexpr, double maximum) {
  if (regexpr.size()>4) {
    std::string ext=regexpr.substr(regexpr.size()-4, 4);
    if (ext!=".den" && ext!=".num") {
      ext="";
    }
    scaleMaximumTo(search(regexpr), ext, maximum);
    return;
  }
  scaleMaximumTo(search(regexpr), "", maximum);
  return;
}


template <class H>
void Plot<H>::scaleAreaTo(std::vector<iterator> list, std::string what, 
			  double area) {

  int k=0;
  if (what.find("num")!=std::string::npos) k=1;
  if (what.find("den")!=std::string::npos) k=-1;

  for (size_t i=0; i<list.size(); i++) {
    double integral;
    if (k) {
      if (k>0) {
	if (list[i]->second.num()) {
	  integral=list[i]->second.num()->Integral();
	  if (integral!=0.) list[i]->second.num()->Scale(area/integral);
	}
      } else {
	if (list[i]->second.den()) {
	  integral=list[i]->second.den()->Integral();
	  if (integral!=0.) list[i]->second.den()->Scale(area/integral);
	}
      }
    } else {
      integral=list[i]->second.Integral();
      if (integral!=0.) list[i]->second.Scale(area/integral);
    }
  }
  return;
}


template <class H>
void Plot<H>::scaleAreaTo(std::string regexpr, double area) {
  if (regexpr.size()>4) {
    std::string ext=regexpr.substr(regexpr.size()-4, 4);
    if (ext!=".den" && ext!=".num") {
      ext="";
    }
    scaleAreaTo(search(regexpr), ext, area);
    return;
  }
  scaleAreaTo(search(regexpr), "", area);
  return;
}


//------------------------------------ Draw() ---------------------------------

template <class H> 
int Plot<H>::Draw(std::vector<std::string> hists, int ncols, int nrows) {

  int debug=1;
  
  typedef std::vector<std::string> PlotNames; // list of names
  typedef std::vector<std::string> OptionList; // 0:pad op, 1:draw op, 2:title 

  // Collect list of pads ----------------------------------------------------
  std::vector<std::pair<PlotNames,OptionList> > pads;

  // break each input string into line(s), make a list with one line per entry
  std::vector<std::string> expList = itemizeString(hists, "\n");

  if (debug) {
    std::cout<<"expanded list:\n";
    for (size_t i=0; i<expList.size(); i++) std::cout<<expList[i]<<std::endl;
  }

  // decide if hitos in one line should be plotted on a single or separate pads
  for (size_t i=0; i<expList.size(); i++) {
    std::pair<PlotNames,OptionList> pad;
    std::pair<std::string,std::string> split=splitString(expList[i], ";");
    // first item is list of histogram names(+legend lables)
    std::string names=split.first;
    if (names=="") continue;
    // second item is pad+hist drawing option, third is pad frame(histo) titles
    split=splitString(split.second, ";");

    // pad draw option "" : separate pads, "overlay"/"stack" : single pad
    pad.second.push_back(""); // pad draw option
    size_t posOverlay=split.first.find("overlay");
    if (posOverlay!=std::string::npos) {
      split.first.erase(posOverlay, 7);
      pad.second[0]="overlay"; // pad draw option
    }
    size_t posStack=split.first.find("stack");
    if (posStack!=std::string::npos) {
      split.first.erase(posStack, 5);
      pad.second[0]="stack"; // pad draw option
    }
    pad.second.push_back(split.first); // histo draw option
    pad.second.push_back(split.second); // frame titles (includes axis titles)

    // remove spaces from histogram names (but not from the legends)
    size_t space=names.find_first_of(" ");
    size_t excl=names.find_last_of("!", space); // separates name and legend
    size_t et=names.find_last_of("&", space); // separates histos listed here
    while (space!=std::string::npos) {
      if (excl==std::string::npos ) {
	names.erase(space, 1);
	space=names.find_first_of(" ", space);
      }
      else if (et!=std::string::npos && et>excl) {
	names.erase(space, 1);
	space=names.find_first_of(" ", space);
      } else {
	space=names.find_first_of(" ", space+1);
      }
      excl=names.find_last_of("!", space);
      et=names.find_last_of("&", space);
    }
    // itemize histonames (+legends)
    std::vector<std::string> items = itemizeString(names, "&");
    // expand regular expressions, but only on names (omit .den/.num extension)
    // PLUS: figure out what legend to use if delimeter "!" is present
    for (int j=0; j<int(items.size()); j++) {
      std::pair<std::string,std::string> nameLegend=splitString(items[j], "!");
      std::string ext="";
      if (nameLegend.first.size()>4) {
	ext=nameLegend.first.substr(nameLegend.first.size()-4, 4);
	if (ext!=".den" && ext!=".num") {
	  ext="";
	} else {
	  nameLegend.first.erase(nameLegend.first.size()-4, 4);
	}
      }
      std::vector<iterator> candidates=search(nameLegend.first);
      if (candidates.size()==0) {
	items.erase(items.begin()+j--);
	continue;
      }
      for (size_t k=0; k<candidates.size(); k++) {
	std::ostringstream newname;
	newname << candidates[k]->first << ext;

// 	std::string newlegend=nameLegend.second;
// 	if (newlegend=="") newlegend=candidates[k]->second.getLegend();
// 	if (items[j].find("!")!=std::string::npos && newlegend=="") {
// 	  newlegend=newname.str();
// 	}
// 	if (newlegend!="") {
// 	  if (newlegend[0]=='!') {
// 	    newname << "!" << candidates[k]->first << ext;
// 	    newlegend.erase(0, 1);
// 	  }
// 	  newname << "!" << newlegend;
// 	}

	// if there was at least one "!"
	if (items[j].find("!")!=std::string::npos) {
	  std::vector<std::string> legs=itemizeString(nameLegend.second,"!");
	  if (legs[0]=="") legs[0]=candidates[k]->second.getLegend();
	  if (legs[0]=="") legs[0]=candidates[k]->first;
	  newname << "!" << legs[0];
	  if (legs.size()>1) { // if there is a header for the legend
	    if (legs[1]=="") legs[1]=candidates[k]->second.getLegendHead();
	    if (legs[1]=="") legs[1]="<MISSING>";
	    newname << "!" << legs[1];
	  }
	}
	if (k==candidates.size()-1) {
	  items[j]=newname.str();
	} else {
	  items.insert(items.begin()+j++, newname.str());
	}
      }
    }
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
  } // for expList

  if (debug) {
    std::cout<<"pad list:\n";
    for (size_t i=0; i<pads.size(); i++) {
      for (size_t j=0; j<pads[i].first.size(); j++) std::cout<<pads[i].first[j]<<" ";
      std::cout<<pads[i].second[0]<<" "<<pads[i].second[1]<<" "<<pads[i].second[2]<<std::endl;
    }
  }

  // Prepare canvass ----------------------------------------------------------
  deleteCanvas();
  can_=new TCanvas(canName_.data(), canTitle_.data(), ww_, wh_);
  ntiles_=0;

  if (nrows<0) nrows=pads.size()/ncols;
  if (ncols*nrows<int(pads.size())) nrows=pads.size()/ncols+1;
  if (ncols*nrows) can_->Divide(ncols, nrows);
  ntiles_=ncols*nrows;

  // Draw pads ----------------------------------------------------------------
  if (debug) {
    std::cout<<"drawing pads"<<std::endl;
  }

  for (size_t i=0; i<pads.size(); i++) {
    can_->cd(i+1);
    double min=0, max=0;
    std::string lastHist="";

    // Drop plots if not found and calculate stack  ---------------------------

    for (int j=pads[i].first.size()-1; j>=0; j--) {
      std::pair<std::string,std::string> nameRest;
      nameRest=splitString(pads[i].first[j], "!");
      if (debug) 
	std::cout<<j<<" "<<nameRest.first<<" ! "<<nameRest.second<<std::endl;
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

      // check if histo exists at all. (note, "num"/"den" has not been checked)
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
      if (debug) std::cout<<nameRest.first<<" -> "<<h->GetName()<<std::endl;

      if (pads[i].second[0]!="stack") continue;

      stack_[nameRest.first]=(*h);
      stack_[nameRest.first].SetDirectory(0);

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

    // Make record of empty pad and move on to the next one -------------------

    if (debug) {
      std::cout<<"Pad "<<i<<std::endl;
      for (size_t j=0; j<pads[i].first.size(); j++) std::cout<<pads[i].first[j]<<" ";
      std::cout<<pads[i].second[0]<<" "<<pads[i].second[1]<<" "<<pads[i].second[2]<<std::endl;
    }      

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
      nameLegendTitle=itemizeString(pads[i].first[j], "!");
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
	hc->Reset();
	hc->SetDirectory(0);
	opt << "SAME";
	frame_.push_back(hc);
	std::ostringstream ss;
	ss << "frame_" << i;
	frame_[i]->SetName(ss.str().data());
	if (debug) 
	  std::cout<<i<<" "<<hist<<" -> "<<frame_[i]->GetName()<<std::endl;
	if (h->GetDimension()==1) 
	  frame_[i]->SetAxisRange(min*0.9, max*1.05, "Y");
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

      if (debug)
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

    //frame_[i]->Draw("AXISSAME");
    if (legend_[i]!=NULL) {
      if (debug) std::cout<<"drawing legend\n";
      legend_[i]->Draw();
    }
    // End of this pad --------------------------------------------------------

  }

  can_->Update();
  if (style_!="") setPlotStyle(style_);

  lastDrawFormat_ = hists;
  lastDrawNCols_ = ncols;
  lastDrawNRows_ = nrows;

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
  if (canName_!="") {
    sdir<<canName_<<"_HIST";
    TDirectory *dir=gDirectory->GetDirectory(sdir.str().data());
    if (!dir) dir=gDirectory->mkdir(sdir.str().data(), sdir.str().data());
    dir->cd();
  }
  for (iterator it=this->begin(); it!=this->end(); it++) it->second.Write();
  if (canName_!="") {
    gDirectory->cd("../");
    if (can_!=NULL) can_->Write();
  } else {
    if (can_!=NULL) std::cout<<"*** Write: Canvas with no name! Skipped.\n";
  }
}


//------------------------------------ load() ---------------------------------

template <class H> int Plot<H>::load(std::string name) {
  if (PLOTDEBUG) {
    std::cout << "=========================================================\n";
    std::cout << "Current dir: ";
    gDirectory->pwd();
  }

  clear();

  if (name=="") name=canName_;
  std::string dirname=name;
  dirname+="_HIST";
  TDirectory tDir;
  TDirectory *dir=(TDirectory *) gDirectory->GetObjectChecked(dirname.c_str(),
							      tDir.IsA());
  if (dir==NULL) return 1;
  if (PLOTDEBUG) {
    std::cout << "Reading from dir: ";
    dir->pwd();
  }
  //dir->ls();

  TIter next(dir->GetListOfKeys());
  TKey *key;
  while (key=(TKey*)next()) {
    if (PLOTDEBUG) std::cout<<"Key "<<key->GetName()<<std::endl;
    std::string hname=key->GetName();
//     std::string htype=hname.substr(hname.length()-4, 4);
//     if (htype=="_num" || htype=="_den") continue;
    if (hname.find('.')!=std::string::npos) continue; // this is an aux histo
    H *obj=NULL;
    dir->GetObject(hname.c_str(), obj);
    if (obj==NULL) continue; // make sure it's an "H" object, should do smarter
    Histogram<H> h;
    h.load(hname, dir);
    if (PLOTDEBUG) h.print();
    //hname.erase(0, name.length()+1);
    std::string hkey=keyFromHistName(hname, name);
    (*this)[hkey]=h;
    (*this)[hkey].setDirectory(0);
    (*this)[hkey].setName(histNameFromKey(hkey));
    if (PLOTDEBUG) {
      std::cout<<"Plot "<<canName_<<"["<<hkey<<"]=\n";
      (*this)[hkey].print();		     
      std::cout<<"Added histogram "<<(*this)[hkey].GetName()<<std::endl;
    }
  }
  if (PLOTDEBUG) {
    std::cout<<" End of loading plot"<<std::endl;
    gDirectory->pwd();
    gDirectory->ls();
  }

  return 0;
}



//----------------------------- setName() -------------------------------------

// Set name, or rename, or what?
template <class H> 
void Plot<H>::setName(std::string name) { 

  for (iterator it=this->begin(); it!=this->end(); it++) {
    it->second.setName(replacePlotNameInHistName(it->second.GetName(), name));
  }

  if (can_!=NULL) can_->SetName(name.c_str());
  canName_=name;
}



//----------------------------- print() -------------------------------------
//   TCanvas* can_;                        // The canvas drawn by Draw()
//   Int_t ww_, wh_;
//   std::string canName_, canTitle_;
//   int ntiles_;

//   std::vector<std::string> lastDrawFormat_; // Iportant!!! : 
//   int lastDrawNCols_, lastDrawNRows_;      // ---------------------------------
//   std::map<std::string,H> stack_;         // These five variables are meant to
//   std::vector<TLegend*> legend_;         // be filled simultaneously by Draw()!
//   std::vector<H*> frame_;               // ------------------------------------

//   std::string style_;


template <class H> 
void Plot<H>::print() { 

  std::cout<<"\n-----------------------------------------------------------\n";
  std::cout<<"Plot name: "<<canName_<<"\n     title: "<<canTitle_<<std::endl;
  std::cout<<"Size: "<<ww_<<"x"<<wh_<<std::endl;
  if (can_!=NULL) {
    std::cout<<"Canvas: "<<can_->GetName()<<std::endl;
    std::cout<<"Number of pads: "<<ntiles_<<std::endl;
  }

  if (lastDrawFormat_.size()!=0) {
    std::cout<<"Last drawn plot in arrangement (columns by rows): ";
    std::cout<<lastDrawNCols_<<"x"<<lastDrawNRows_<<std::endl;
    std::cout<<"Drawing options for pads:\n";
    for (size_t i=0; i<lastDrawFormat_.size(); i++) {
      std::cout<<"\t\""<<lastDrawFormat_[i]<<"\""<<std::endl;
    }
  }
  
  if (this->size()!=0) {
    std::cout<<"List of histograms stored in this plot:\n";
    for (iterator it=this->begin(); it!=this->end(); it++) {
      it->second.print();
    }
  }

  std::cout<<"-----------------------------------------------------------\n\n";
}



//------------------------------ setPlotStyle ---------------------------------

template <class H> 
void Plot<H>::setPlotStyle(std::string style) {

  if (can_==NULL) return;
  //  if (getNPads()==0) return;

  if (style.find("TDR")!=std::string::npos || 
      style.find("tdr")!=std::string::npos ) {

    // For the canvas:
    can_->SetBorderMode(0);
    can_->SetFillColor(kWhite);
    can_->SetWindowSize(600+(600-can_->GetWw()), 600+(600-can_->GetWh()));    
    
    // For the Pad:
    for (int i=0; i<getMaxNPads(); i++) {//getNPads(); i++) {
      TVirtualPad *ipad=can_->GetPad(i+1);
      if (ipad==NULL) continue;
      ipad->SetBorderMode(0);
      ipad->SetFillColor(kWhite);
      ipad->SetBorderSize(1);
      ipad->SetGridx(false);
      ipad->SetGridy(false);
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
    

    // For the histo:
    
    typename std::map<std::string,Histogram<H> >::iterator it;
    for (it=this->begin(); it!=this->end(); it++) {
      Histogram<H> *h=&(it->second);
      
      // Stat
      TPaveStats *st = (TPaveStats*)h->FindObject("stats");
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
      // 	h->SetFillColor(kWhite); // Was 10 in tdrStyle()
      // 	h->SetFillStyle(1001);
      // 	h->SetTextFont(42);
      // 	h->SetTextSize(0.05);
      // 	h->SetTextColor(1);
      // 	h->SetBorderSize(2);
      // 	h->SetX1(0.1);
      // 	h->SetY1(0.985);
      // 	h->SetX2(0);
      // 	h->SetY2(0);
      
      h->SetFillColor(kWhite);
      h->SetFillStyle(0);
      //h->SetLineColor(1);
      h->SetLineStyle(0);
      //h->SetLineWidth(1);
      // 	h->SetLegoInnerR(0.5);
      // 	h->SetNumberContours(20);
      // 	h->SetEndErrorSize(2);
      // 	h->SetErrorMarker(20);
      // 	h->SetErrorX(0.);
      h->SetMarkerStyle(20);
      
      std::vector<std::string> axis;
      axis.push_back("X");
      axis.push_back("Y");
      axis.push_back("Z");
      
      for (size_t j=0; j<axis.size(); j++) {
	TAxis *a=NULL;
	if (axis[j]=="X") a=h->GetXaxis();
	if (axis[j]=="Y") a=h->GetYaxis();
	if (axis[j]=="Z") a=h->GetZaxis();
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
