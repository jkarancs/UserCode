#include "TObject.h"
#include "TFile.h"
#include "TROOT.h"
#include "TTree.h"
#include "TH2.h"
#include <memory>
#include <cstdlib>
#include <string>
#include <sstream>

#define NOVAL_I -9999
#define NOVAL_F -9999.0
#define VERSION2 25

//Defining Dataset Structures

 // Event info
class EventData {
 public:
  int run;
  int ls;
  int orb;
  int bx;
  int evt;
  int nvtx;
  int trig;
  unsigned int beamint[2];
  float intlumi;
  float instlumi;
  float vtxndof;
  float vtxchi2;
  float vtxD0;
  float vtxX;
  float vtxY;
  float vtxZ;
  int vtxntrk;
  int good;
  float tmuon;
  float tmuon_err;
  float tecal;
  float tecal_raw;
  float tecal_err;
  float field;
  int wbc;
  int delay;
  int ntracks;
  int ntrackFPix[2]; // tracks crossing the pixels
  int ntrackBPix[3]; // tracks crossing the pixels
  int ntrackFPixvalid[2]; // tracks crossing the pixels with valid hits
  int ntrackBPixvalid[3]; // tracks crossing the pixels with valid hits
  float trackSep;
  int federrs_size;
  // must be the last variable of the object saved to TTree:
  int federrs[41][2]; // [error index] [0:fedId, 1:errorType]
  
  std::string list;
  
  EventData() { init(); };
  void init() {
    run=NOVAL_I;
    ls=NOVAL_I;
    orb=NOVAL_I;
    bx=NOVAL_I;
    evt=NOVAL_I;
    nvtx=NOVAL_I;
    trig=NOVAL_I;
    beamint[0]=beamint[1]=abs(NOVAL_I);
    intlumi=NOVAL_F;
    instlumi=NOVAL_F;
    vtxndof=vtxD0=vtxZ=NOVAL_F;
    vtxX=vtxY=vtxchi2=NOVAL_F;
    vtxntrk=NOVAL_I;
    good=NOVAL_I;
    tmuon=NOVAL_F;
    tmuon_err=NOVAL_F;
    tecal=NOVAL_F;
    tecal_raw=NOVAL_F;
    tecal_err=NOVAL_F;
    field=NOVAL_F;
    wbc=NOVAL_I;
    delay=NOVAL_I;
    ntracks=NOVAL_I;
    ntrackFPix[0]=ntrackFPix[1]=NOVAL_I;
    ntrackBPix[0]=ntrackBPix[1]=ntrackBPix[2]=NOVAL_I;
    ntrackFPixvalid[0]=ntrackFPixvalid[1]=NOVAL_I;
    ntrackBPixvalid[0]=ntrackBPixvalid[1]=ntrackBPixvalid[2]=NOVAL_I;
    trackSep=NOVAL_F;
    federrs_size=0;
    for (size_t i=0; i<41; i++) federrs[i][0]=federrs[i][0]=NOVAL_I;
    
    list="run/I:ls:orb:bx:evt:nvtx:trig:beamint[2]/i:intlumi/F:instlumi:"
      "vtxndof:vtxchi2:vtxD0:vtxX:vtxY:vtxZ:vtxntrk/I:good:tmuon/F:tmuon_err:"
      "tecal:tecal_raw:tecal_err:field:wbc/I:delay:ntracks:ntrackFPix[2]:"
      "ntrackBPix[3]:ntrackFPixvalid[2]:ntrackBPixvalid[3]:trackSep/F:"
      "federrs_size/I:federrs[federrs_size][2]";
  }
  
/*   int federrs_fedid(size_t i) { */
/*     assert(federrs_size!=NOVAL_I); */
/*     return (i<size_t(federrs_size)) ? federrs[i][0] : NOVAL_I; */
/*   } */
  
/*   int federrs_type(size_t i) { */
/*     assert(federrs_size!=NOVAL_I); */
/*     return (i<size_t(federrs_size)) ? federrs[i][1] : NOVAL_I; */
/*   } */
  
};


// Lumi info
class LumiData {
 public:
  int run;
  int ls;
  unsigned int beamint[2];
  float intlumi;
  float instlumi;
  int ntriggers;
  int prescale[32];
  
  std::string list;
  
  LumiData() { init(); };
  void init() {
    run=NOVAL_I;
    ls=NOVAL_I;
    beamint[0]=beamint[1]=abs(NOVAL_I);
    intlumi=NOVAL_F;
    instlumi=NOVAL_F;
    ntriggers=0;
    
    list="run/I:ls:beamint[2]/i:intlumi/F:instlumi:ntriggers/I:prescale[ntriggers]";
  }
  
};


// Track info
class TrackData {
 public:
  // Non-split mode from here - keep order of variables
  int validfpix[2]; // valid recHits in Diks1,2 
  int validbpix[3]; // valid recHits in Layer 1,2,3
  int strip; // total valid hits
  int quality;
  float d0;
  float dz;
  float pt;
  // From here Split mode (if SPLIT defined)
  float ndof;
  float chi2;
  float eta;
  float phi;
  float theta;
  float p;
  int algo;
  int fromVtx;
  int i;
  int pix; // total valid hits
  int pixhit[2]; // 0: top, 1: bottom
  int validpixhit[2]; // 0: top, 1: bottom
  int fpix[2]; // recHits in Diks1,2 
  int bpix[3]; // recHits in Layer 1,2,3
  int highPurity;
  
  std::string list;
  
  TrackData() { init(); }
  void init() {
    validfpix[0]=validfpix[1]=NOVAL_I;
    validbpix[0]=validbpix[1]=validbpix[2]=NOVAL_I;
    strip=NOVAL_I;
    quality=NOVAL_I;
    d0=NOVAL_F;
    dz=NOVAL_F;
    pt=NOVAL_F;
    ndof=NOVAL_F;
    chi2=NOVAL_F;
    eta=NOVAL_F;
    phi=NOVAL_F;
    theta=NOVAL_F;
    p=NOVAL_F;
    algo=NOVAL_I;
    fromVtx=NOVAL_I;
    i=NOVAL_I;
    pix=NOVAL_I;
    pixhit[0]=pixhit[1]=NOVAL_I;
    validpixhit[0]=validpixhit[1]=NOVAL_I;
    fpix[0]=fpix[1]=NOVAL_I;
    bpix[0]=bpix[1]=bpix[2]=NOVAL_I;
    highPurity=NOVAL_I;
#ifdef COMPLETE
    list="validfpix[2]/I:validbpix[3]:strip:quality:d0/F:dz:pt:ndof:chi2:eta:phi:theta:p:"
      "algo/I:fromVtx:i:pix:pixhit[2]:validpixhit[2]:fpix[2]:bpix[3]:highPurity";
#else
    list="validfpix[2]/I:validbpix[3]:strip:quality:d0/F:dz:pt:ndof:chi2:eta:phi";
#endif
  }
  
};


// Module info
class ModuleData {
 public:
  int det;
  int layer;
  int ladder;
  int half;
  int module;
  int disk;
  int blade;
  int panel;
  
  int federr;
  
  int side;
  int prt;
  int shl;
  int sec;
  
  int outer;
  
  unsigned int rawid;
  
  std::map<int, std::string> federrortypes;
  
  std::string list;
  
  ModuleData() { init(); }
  void init() {
    det=NOVAL_I;
    layer=NOVAL_I;
    ladder=NOVAL_I;
    half=NOVAL_I;
    module=NOVAL_I;
    disk=NOVAL_I;
    blade=NOVAL_I;
    panel=NOVAL_I;
    federr = NOVAL_I;
    side=NOVAL_I;
    prt=NOVAL_I;
    shl=NOVAL_I;
    sec=NOVAL_I;
    outer=NOVAL_I;
    rawid=abs(NOVAL_I);
    
    
    federrortypes.insert(std::pair<int, std::string>(25, "invalidROC"));
    federrortypes.insert(std::pair<int, std::string>(26, "gap word"));
    federrortypes.insert(std::pair<int, std::string>(27, "dummy word"));
    federrortypes.insert(std::pair<int, std::string>(28, "FIFO full error"));
    federrortypes.insert(std::pair<int, std::string>(29, "timeout error"));
    federrortypes.insert(std::pair<int, std::string>(30, "TBM error trailer"));
    federrortypes.insert(std::pair<int, std::string>(31, "event number error (TBM and FED event number mismatch)"));
    federrortypes.insert(std::pair<int, std::string>(32, "incorrectly formatted Slink Header"));
    federrortypes.insert(std::pair<int, std::string>(33, "incorrectly formatted Slink Trailer"));
    federrortypes.insert(std::pair<int, std::string>(34, "the event size encoded in the Slink Trailer is different than the size found at raw to digi conversion "));
    federrortypes.insert(std::pair<int, std::string>(35, "invalid FED channel number"));
    federrortypes.insert(std::pair<int, std::string>(36, "invalid ROC value "));
    federrortypes.insert(std::pair<int, std::string>(37, "invalid dcol or pixel value "));
    federrortypes.insert(std::pair<int, std::string>(38, "the pixels on a ROC weren't read out from lowest to highest row and dcol value"));
    federrortypes.insert(std::pair<int, std::string>(39, "CRC error"));
#ifdef COMPLETE
    list="det/I:layer:ladder:half:module:disk:blade:panel:federr:side:prt:shl:"
      "sec:outer:rawid/i";
#else
    list="det/I:layer:ladder:half:module:disk:blade:panel:federr";
#endif
  }
  
  std::string shell() {
    std::ostringstream ss;
    if (det==0) {
      ss << "B" << ((module>0) ? "p" : "m") << ((ladder>0) ? "I" : "O");
    } else if (det==1) {
      ss << "B" << ((disk>0) ? "p" : "m") << ((blade>0) ? "I" : "O");
    }
    return ss.str();
  }
  
  int shell_num() {
    if (det==0)      return ((module>0) ? 0 : 2) + ((ladder>0) ? 0 : 1);
    else if (det==1) return ((disk>0) ? 0 : 2) + ((blade>0) ? 0 : 1);
    return -1;
  }
  
  std::string federr_name() {
    std::map<int, std::string>::const_iterator it=federrortypes.find(federr);
    return (it!=federrortypes.end()) ? it->second : "FED error not interpreted";
  }
  
};


// Cluster info
class ClustData {
 public:
  // Paired branches (SPLIT mode)
  float x;
  float y;
  int sizeX;
  int sizeY;
  // From here Split mode (if SPLIT defined)
  int i; // serial num of cluster in the given module
  int edge;     // set if there is a valid hit
  int badpix;   // set if there is a valid hit
  int tworoc;   // set if there is a valid hit
  int size;
  float charge;
  // must be the last variable of the object saved to TTree:
  // adc, x, y
  float pix[1000][3];
  
  std::string list;
  
  ClustData() { init(); }
  void init() {
    x=NOVAL_F;
    y=NOVAL_F;
    sizeX=NOVAL_I;
    sizeY=NOVAL_I;
    i=NOVAL_I;
    edge=NOVAL_I;
    badpix=NOVAL_I;
    tworoc=NOVAL_I;
    size=0;
    charge=NOVAL_F;
    for (size_t i=0; i<1000; i++) pix[i][0]=pix[i][1]=pix[i][2]=NOVAL_F;
    
    list="x:y:sizeX/I:sizeY:i:edge:badpix:tworoc:size:charge/F:pix[size][3]";
  }
  
};


// Digi info
class DigiData {
 public:
  int i; // serial num of digi in the given module
  int row;
  int col;
  int adc;
  
  std::string list;
  
  DigiData() { init(); }
  void init() {
    i=NOVAL_I;
    row=NOVAL_I;
    col=NOVAL_I;
    adc=NOVAL_I;
    list="i/I:row:col:adc";
  }
  
};


// Trajectory info
class TrajMeasData {
 public:
  // Non-split mode from here - keep order of variables
  int validhit;
  int missing;
  float lx;
  float ly;
  float dx_cl[2];
  float dy_cl[2];
  float dx_hit;
  float dy_hit;
  // Paired branch (keep order)
  float alpha;
  float beta;
  // From here Split mode (if SPLIT defined)
  float lz;
  float glx;
  float gly;
  float glz;
  float lxmatch;
  float lymatch;
  float norm_charge;
  int i; // serial num of trajectory measurement on the (single) track of the event
  int onedge;
  int inactive;
  int badhit;
  int telescope;
  int telescope_valid;
  int dmodule; // D(propagated hit, valid hit)
  int dladder; // D(propagated hit, valid hit)
  float glmatch;
  float lx_err;
  float ly_err;
  float lz_err;
  float lxymatch;
  float res_hit;
  float sig_hit;
  float d_cl[2];
  
  std::string list;
  
  TrajMeasData() { init(); }
  void init() {
    validhit=NOVAL_I;
    missing=NOVAL_I;
    lx=NOVAL_F;
    ly=NOVAL_F;
    dx_cl[0]=dx_cl[1]=NOVAL_F;
    dy_cl[0]=dy_cl[1]=NOVAL_F;
    dx_hit=NOVAL_F;
    dy_hit=NOVAL_F;
    alpha=NOVAL_F;
    beta=NOVAL_F;
    lz=NOVAL_F;
    glx=NOVAL_F;
    gly=NOVAL_F;
    glz=NOVAL_F;
    lxmatch=NOVAL_F;
    lymatch=NOVAL_F;
    norm_charge=NOVAL_F;
    i=NOVAL_I;
    onedge=NOVAL_I;
    inactive=NOVAL_I;
    badhit=NOVAL_I;
    telescope=NOVAL_I;
    telescope_valid=NOVAL_I;
    dmodule=NOVAL_I;
    dladder=NOVAL_I;
    glmatch=NOVAL_F;
    lx_err=NOVAL_F;
    ly_err=NOVAL_F;
    lz_err=NOVAL_F;
    lxymatch=NOVAL_F;
    res_hit=NOVAL_F;
    sig_hit=NOVAL_F;
    d_cl[0]=d_cl[1]=NOVAL_F;
    
#ifdef COMPLETE
    list="validhit/I:missing:lx/F:ly:dx_cl[2]:dy_cl[2]:dx_hit:dy_hit:alpha:beta:"
      "lz:glx:gly:glz:lxmatch:lymatch:norm_charge:i/I:onedge:inactive:badhit:"
      "telescope:telescope_valid:dmodule:dladder:glmatch/F:lx_err:ly_err:lz_err:"
      "lxymatch:res_hit:sig_hit:d_cl[2]";
#else
    list="validhit/I:missing:lx/F:ly:dx_cl[2]:dy_cl[2]:dx_hit:dy_hit:alpha:beta:";
#endif
  }
  
};


class Cluster : public ClustData {
 public:

  ModuleData mod; // offline module number
  ModuleData mod_on; // online module number

  Cluster() { mod.init(); mod_on.init();}
  void init() {
    ClustData::init();
    mod.init();
    mod_on.init();
  }
  
};


class Digi : public DigiData {
 public:

  ModuleData mod; // offline module number
  ModuleData mod_on; // online module number
  
  Digi() { mod.init(); mod_on.init(); }
  void init() {
    DigiData::init();
    mod.init();
    mod_on.init();
  }
  
};


class TrajMeasurement : public TrajMeasData {
 public:
  ModuleData mod; // offline module number
  ModuleData mod_on; // online module number
  ClustData clu;
  TrackData trk;

  TrajMeasurement() { mod.init(); mod_on.init(); clu.init(); trk.init(); }
  void init() {
    TrajMeasData::init();
    mod.init();
    mod_on.init();
    clu.init();
    trk.init();
  }
};
