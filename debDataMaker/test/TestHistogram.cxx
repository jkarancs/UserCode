#ifndef __CINT__
#include "TFile.h"
#include "TH1.h"
#include "TH2.h"
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

  // Test constructors:
  //
  if (0) {
    deb::Histogram<TH1F> a1;
    a1.SetName("a1");
    a1.addAux("b1");
    a1.print();

    TH1F *a2_h= new TH1F("a2_h", "a2_h", 1,0,1);
    deb::Histogram<TH1F> a2(*a2_h);
    a2.addAux("b2");
    a2.SetName("a2");
    a2.print();

    TFile outfile2("test2.root", "RECREATE");
    deb::Histogram<TH1F> a3(a2);
    a3.SetName("a3");
    a3.print();
    a3.aux().print();
    a3.addAux("b3");
    a3.print();
    a3.aux().print();
    a3.eraseAux("b2");
    a3.print();
    a3.aux().print();

    TFile outfile3("test3.root", "RECREATE");
    a1=a3;
    a1.SetName("a1");
    a1.print();

    outfile2.Close();
    std::cout<<"Output2 file closed\n";
    outfile3.Close();
    std::cout<<"Output3 file closed\n";
  }
  // END OF Test constructors:
  //


  // Test nesting aux histos, setDirectory(), Write(), load()
  //
  if (0) {
    deb::Histogram<TH1F> h(100, 0, 100, 
			   "et!top!SM bck;Et of jets;et (GeV);Yield");
    h.addAux("valami");
    h.aux("valami")->addAux("mas1");
    h.aux("valami")->addAux("mas2");
    h.addAux("valami2");
    h.print();
    h.Write();

    deb::Histogram<TH1F> h2(h);
    h2.setDirectory(outfile.GetDirectory(""));
    h2.print();
    h2=h;
    h2.SetName("h2");
    h2.print();
    h2.load("et");
    h2.print();
  }
  // END OF Test nesting aux histos, setDirectory()
  //


  // Test efficiency(), write(), load(), setContent() and setError(),
  // shiftBinContent(), print(), eraseAux(), addAux() with formula
  //
  if (1) {
    deb::Histogram<TH1F> h(100, 0, 100, 
			   "h!top!SM bck;Et of jets;et (GeV);Yield");
    h.efficiency();
    h.print();

    for (int i=0; i<100; i++) {
      h.num()->Fill(i, i);
      h.den()->Fill(i, i*i);
    }

    h.efficiency();
    h.print();

    h.Write();


    std::cout<<std::endl;
    gDirectory->ls();

    deb::Histogram<TH1F> h2(100, 0, 100, 
			    "h2!top!SM bck;Et of jets;et (GeV);Yield");
    h2.load("h");
    h2.print();
    h2.Reset();

    h2.num()->shiftBinContent(2.2);
    h2.den()->shiftBinContent(2.2);
    h2.print();
    h2.setContent("$num{}/$den{}");
    h2.addAux("ntilde", h, "$den{}+4");
    h2.addAux("ptilde", "($num{}+2) / $ntilde{}");
    h2.setError("1.96 * sqrt( ($ptilde{}*(1-$ptilde{})) / $ntilde{} )");
    h2.print();
    h2.eraseAux("ntilde");
    h2.eraseAux("ptilde");
    h2.print();
    h2.Write();
   
    deb::Histogram<TH2F> h3(100, 0, 100, 100, 0, 100, "h3");
    h3.efficiency();
    h3.setContent("%f", 11.1);
    h3.Write();



    deb::rmap<int,int> noval(-1);
    deb::rmap<int,deb::rmap<int,int> > delayscan(noval);

    deb::rmap<int,int> defval(300);
    delayscan.insert(0, 132599, defval);

    deb::rmap<int,int> run132599(-1);
    run132599.insertn(5, 
		      1, 75, 300,
		      75, 126, 250,
		      126, 178, 200,
		      178, 233, 150,
		      233, 283, 70);
    delayscan.insert(132599, 132599, run132599);

    delayscan.insert(132600, 132600, noval);

    deb::rmap<int,int> run132601(-1);
    run132601.insertn(6,
		      1, 50, 70,
		      50, 105, 60,
		      105, 155, 50,
		      155, 207, 40,
		      207, 258, 30,
		      258, 9999, 300);
    delayscan.insert(132601, 132601, run132601);

    delayscan.insert(132602, 999999, defval);


    delayscan(132000).print();
    delayscan(132599).print();
    delayscan(132600).print();
    delayscan(132601).print();
    delayscan(133000).print();
    std::cout<<"Run 132601, LS 156: HV="<<delayscan(132601)(156)<<std::endl;

    std::vector<int> image2=delayscan.image<int>();
    for (int i=0; i<image2.size(); i++) {
      //if (i>lower_bound(image2.begin(), image2.end(), image2.back())-image2.begin()) break;
      std::cout<<i<<": "<<image2[i]<<std::endl;
    }

    std::vector<int> image=delayscan(132601).image();
    for (int i=0; i<image.size(); i++) {
      std::cout<<i<<": "<<image[i]<<std::endl;
    }

    deb::mvector<int> a;
  }
  // END OF Test nesting aux histos, setDirectory()
  //



  outfile.Close();
  std::cout<<"Output file closed\n";

  return 1;
}
#endif
