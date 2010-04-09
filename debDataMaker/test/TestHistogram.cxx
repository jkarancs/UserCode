#ifndef __CINT__
#include "TFile.h"
#include "TH1.h"
#include "../interface/Histogram.hh"


int main(int argc, char* argv[]) 
{

  if (argc<2) {
    std::cout << "Usage: TestHistogram ";
    std::cout << "<output file>" << std::endl;
    return 0;
  }

  std::string outfilename=argv[1];
  TFile outfile(outfilename.data(), "RECREATE");

  deb::Histogram<TH1F> h(100, 0, 100, "test!legend!legendHead;Title;Xlabel;Ylabel");
  h.print();

  for (int i=0; i<100; i++) h.Fill(i, i*2);
  h.Write();

  outfile.Close();
  return 1;   
}

#endif
