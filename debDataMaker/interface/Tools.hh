#ifndef SusyAnalysis_debDataMaker_Tools_hh_
#define SusyAnalysis_debDataMaker_Tools_hh_
// -*- C++ -*-
//
// Package:    debDataMaker
// Class:      Data
// 
/**\class Data Data.hh SusyAnalysis/debDataMaker/interface/Tools.hh

 Description:  Helper functions used in derived classes of Data

 Implementation:
 
*/
//
// Original Author:  Viktor VESZPREMI
//         Created:  Wed Mar 18 10:28:26 CET 2009
// $Id: Data.hh,v 1.10 2009/06/15 09:39:26 veszpv Exp $
//
//
//-----------------------------------------------------------------------------

namespace deb {

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

template<class T> bool isContext(std::string context) {
  if (strstr(typeid(T).name(), context.data())!=NULL) return true;
  return false;
}

template<class T> std::string humanTypeId(T& t) {
  char *name=abi::__cxa_demangle(typeid(t).name(), NULL, NULL, NULL);
  std::string humanTypeId=name;
  free(name);
  return humanTypeId;
}


//-----------------------------------------------------------------------------
//              convert string to int

   class BadConversion : public std::runtime_error {
     public:
	     
     BadConversion(const std::string& s) : std::runtime_error(s){ }
     
   };
 
   inline int string2int(const std::string& s) {
     std::istringstream i(s);
     int x;
     if (!(i >> x))
       throw BadConversion("string2int(\"" + s + "\")");
     return x;
   }

//-----------------------------------------------------------------------------

std::map<std::string,std::pair<char, size_t> > getVariableMap(std::string v) {
  std::map<std::string, std::pair<char, size_t> > ret;
  size_t beg=0;
  size_t sep=v.find_first_of(":");
  char type='0';
  size_t offset=0;
  std::string types="FIDLil";
  while (beg<v.size()) {
    if (sep==std::string::npos) sep=v.size();
    std::string var=v.substr(beg, sep-beg);
    if (var.find("/")!=std::string::npos) {
      if (var.size()-var.find("/")==2) {
	type=var[var.size()-1];
	var.erase(var.size()-2);
      } else {
	printf("*** ERROR in getVariableMap() can only accept one-character"\
	       "variable following a '/'. It is not so for %s in %s, "	\
	       "assuming (F)loat", var.data(), v.data());
	type='F';
	var.erase(var.find("/"));
      }
    } else if (type=='0') {
      printf("*** ERROR in getVariableMap(): Missing variable "
	     "type for %s in %s, assuming (F)loat", var.data(), v.data());
      type='F';
    }
    if (types.find(type)==std::string::npos) {
      printf("*** ERROR in getVariableMap(): Invalid variable type %c for %s "\
	     "in %s, assuming (F)loat", type, var.data(), v.data());
      type='F';
    }
    unsigned int n=1;
    size_t l=0, p=var.find("[");
    if (p!=std::string::npos) {
      p++;
      l=var.find("]")-p;
      n=atoi(var.substr(p,l).data());
    }
    for (unsigned int i=0; i<n; i++) {
      std::string var2=var;
      if (p!=std::string::npos) {
	char num[12];
	sprintf(num, "%d", i);
	var2.replace(p, l, num);
      }
      ret[var2]=std::make_pair(type, offset);
      if (type=='F') offset+=sizeof(float);
      else if (type=='D') offset+=sizeof(double);
      else if (type=='I') offset+=sizeof(int);
      else if (type=='i') offset+=sizeof(unsigned int);
      else if (type=='L') offset+=sizeof(long);
      else if (type=='l') offset+=sizeof(unsigned long);
    }
    beg=sep+1;
    sep=v.find_first_of(":", beg);
  }
  return ret;
}


size_t generateIndices(unsigned int N, unsigned int K, 
		       std::vector<std::vector<unsigned int> >& result,
		       std::vector<unsigned int>* symm=NULL, 
		       std::vector<unsigned int>* ii=NULL) {
  bool received_symm=true;
  if (ii==NULL) {
    ii=new std::vector<unsigned int>;
    if (symm==NULL) {
      received_symm=false;
      symm=new std::vector<unsigned int> (K,K);
    }
  }
  unsigned int k=ii->size();
  if (k==K) {
    result.push_back((*ii));
    return result.size();
  }
  for (unsigned int i=(*symm)[k]<k ? (*ii)[(*symm)[k]]+1 : 0; i<N; i++) {
    unsigned int j=0; 
    for (; j<ii->size(); j++) if ((*ii)[j]==i) break;
    if (j!=ii->size()) continue; // Dont use same index twice
    ii->push_back(i);
    generateIndices(N,K,result,symm,ii);
    ii->pop_back();
  }
  if (ii->size()==0) {
    delete ii;
    if (received_symm==false) delete symm;
  }
  return result.size();
}





}
//-----------------------------------------------------------------------------
#endif
