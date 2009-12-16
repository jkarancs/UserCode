

TH1F *first_muon_LM0;
TH1F *first_muon_TTbar;
TH1F *first_muon_Wjets_1;
TH1F *first_muon_Zjets;

double max;
int fillcolor;
int save2pdf;


double x_cross;
double num_events;
double max_events;
double luminosity;

double isolation_xrange;

void RA4MuonStudy()

{    
  
  //std::string normalization="integral";                // xsec,integral
  std::string normalization="xsec";
  
      
  fillcolor=0;
  save2pdf=0;
  
  luminosity=100.0; //pb^-1
  
  
  isolation_xrange=10.0;
  
  
///____________________________________________________________________________
///                                  hits

    TFile *f = TFile::Open("/home/aranyi/CMSSW_2_2_9/data/RA4_Study_20091201/LM0/LM0_RA4Synchronization_1.root");
    gDirectory->GetObject("RA4SynchronizationMod/RA4 Jet+Met+Muon  1st Muon  Number of innerTrack hits >= 11;1",first_muon_LM0);
    
    TFile *f = TFile::Open("/home/aranyi/CMSSW_2_2_9/data/RA4_Study_20091201/TTbar/TTbar_RA4Synchronization_1.root");    
    gDirectory->GetObject("RA4SynchronizationMod/RA4 Jet+Met+Muon  1st Muon  Number of innerTrack hits >= 11;1",first_muon_TTbar);
    
    TFile *f = TFile::Open("/home/aranyi/CMSSW_2_2_9/data/RA4_Study_20091201/Wjets_1/Wjets_1_RA4Synchronization_1.root");
    gDirectory->GetObject("RA4SynchronizationMod/RA4 Jet+Met+Muon  1st Muon  Number of innerTrack hits >= 11;1",first_muon_Wjets_1);
    
    TFile *f = TFile::Open("/home/aranyi/CMSSW_2_2_9/data/RA4_Study_20091201/Zjets/Zjets_RA4Synchronization_1.root");    
    gDirectory->GetObject("RA4SynchronizationMod/RA4 Jet+Met+Muon  1st Muon  Number of innerTrack hits >= 11;1",first_muon_Zjets);




  TCanvas *c1 = new TCanvas("c1","hits");  

    if (normalization=="xsec") {
      
      x_cross=110.0;       // cross section [pb]
      num_events=202686.0; // number of events were used in the calculation
      max_events=202686.0; // maximum number of events
      first_muon_LM0->Scale((x_cross*luminosity/num_events));         
      
      
      x_cross=317.0;       // cross section [pb]
      num_events=200000.0; // number of events were used in the calculation
      max_events=946644.0; // maximum number of events
      first_muon_TTbar->Scale((x_cross*luminosity/num_events));
      
      
      x_cross=40000.0;       // cross section [pb]
      num_events=200000.0; // number of events were used in the calculation
      max_events=9745661.0; // maximum number of events
      first_muon_Wjets_1->Scale((x_cross*luminosity/num_events));
      
      
      x_cross=3700.0;       // cross section [pb]
      num_events=200000.0; // number of events were used in the calculation
      max_events=1262816.0; // maximum number of events
      first_muon_Zjets->Scale((x_cross*luminosity/num_events));
    
    }
    
    if (normalization=="integral") {
      
      Double_t norm=first_muon_LM0->Integral();
      first_muon_LM0->Scale(1/norm);
      
      Double_t norm=first_muon_TTbar->Integral();
      first_muon_TTbar->Scale(1/norm);
      
      Double_t norm=first_muon_Wjets_1->Integral();
      first_muon_Wjets_1->Scale(1/norm);
      
      Double_t norm=first_muon_Zjets->Integral();
      first_muon_Zjets->Scale(1/norm);
    
    }
    
    first_muon_LM0->SetXTitle("Number of innerTrack hits");
    
    drawHist(first_muon_LM0,first_muon_TTbar,first_muon_Wjets_1,first_muon_Zjets,fillcolor);     
    
    TCanvas *c1_b=c1->Clone();
    c1_b->SetName("hits (log)");               
    
    c1_b->SetLogy(1);
    c1_b->Draw();
    
    if (save2pdf==1) c1->Print("test/scripts/hits.pdf");             
    if (save2pdf==1) c1_b->Print("test/scripts/hits_log.pdf");

    

///____________________________________________________________________________
///                                  eta

    TFile *f = TFile::Open("/home/aranyi/CMSSW_2_2_9/data/RA4_Study_20091201/LM0/LM0_RA4Synchronization_1.root");
    gDirectory->GetObject("RA4SynchronizationMod/RA4 Jet+Met+Muon  1st Muon  |eta| <= 2.1;1",first_muon_LM0);
    
    TFile *f = TFile::Open("/home/aranyi/CMSSW_2_2_9/data/RA4_Study_20091201/TTbar/TTbar_RA4Synchronization_1.root");    
    gDirectory->GetObject("RA4SynchronizationMod/RA4 Jet+Met+Muon  1st Muon  |eta| <= 2.1;1",first_muon_TTbar);
    
    TFile *f = TFile::Open("/home/aranyi/CMSSW_2_2_9/data/RA4_Study_20091201/Wjets_1/Wjets_1_RA4Synchronization_1.root");
    gDirectory->GetObject("RA4SynchronizationMod/RA4 Jet+Met+Muon  1st Muon  |eta| <= 2.1;1",first_muon_Wjets_1);
    
    TFile *f = TFile::Open("/home/aranyi/CMSSW_2_2_9/data/RA4_Study_20091201/Zjets/Zjets_RA4Synchronization_1.root");    
    gDirectory->GetObject("RA4SynchronizationMod/RA4 Jet+Met+Muon  1st Muon  |eta| <= 2.1;1",first_muon_Zjets);




    TCanvas *c2 = new TCanvas("c2","eta");

    if (normalization=="xsec") {
      
      x_cross=110.0;       // cross section [pb]
      num_events=202686.0; // number of events were used in the calculation
      max_events=202686.0; // maximum number of events
      first_muon_LM0->Scale((x_cross*luminosity/num_events));
      
      
      x_cross=317.0;       // cross section [pb]
      num_events=200000.0; // number of events were used in the calculation
      max_events=946644.0; // maximum number of events
      first_muon_TTbar->Scale((x_cross*luminosity/num_events));
      
      
      x_cross=40000.0;       // cross section [pb]
      num_events=200000.0; // number of events were used in the calculation
      max_events=9745661.0; // maximum number of events
      first_muon_Wjets_1->Scale((x_cross*luminosity/num_events));
      
      
      x_cross=3700.0;       // cross section [pb]
      num_events=200000.0; // number of events were used in the calculation
      max_events=1262816.0; // maximum number of events
      first_muon_Zjets->Scale((x_cross*luminosity/num_events));
    
    }
    
    if (normalization=="integral") {
      
      Double_t norm=first_muon_LM0->Integral();
      first_muon_LM0->Scale(1/norm);
      
      Double_t norm=first_muon_TTbar->Integral();
      first_muon_TTbar->Scale(1/norm);
      
      Double_t norm=first_muon_Wjets_1->Integral();
      first_muon_Wjets_1->Scale(1/norm);
      
      Double_t norm=first_muon_Zjets->Integral();
      first_muon_Zjets->Scale(1/norm);
    
    }
    
    first_muon_LM0->SetXTitle("|eta|");
    
    drawHist(first_muon_LM0,first_muon_TTbar,first_muon_Wjets_1,first_muon_Zjets,fillcolor);
    
    TCanvas *c2_b=c2->Clone();
    c2_b->SetName("eta (log)");               
    
    c2_b->SetLogy(1);
    c2_b->Draw();
    
    if (save2pdf==1) c2->Print("test/scripts/eta.pdf");             
    if (save2pdf==1) c2_b->Print("test/scripts/eta_log.pdf");
    

///____________________________________________________________________________
///                                  pt

    TFile *f = TFile::Open("/home/aranyi/CMSSW_2_2_9/data/RA4_Study_20091201/LM0/LM0_RA4Synchronization_1.root");
    gDirectory->GetObject("RA4SynchronizationMod/RA4 Jet+Met+Muon  1st Muon  pt >= 10 GeV;1",first_muon_LM0);
    
    TFile *f = TFile::Open("/home/aranyi/CMSSW_2_2_9/data/RA4_Study_20091201/TTbar/TTbar_RA4Synchronization_1.root");    
    gDirectory->GetObject("RA4SynchronizationMod/RA4 Jet+Met+Muon  1st Muon  pt >= 10 GeV;1",first_muon_TTbar);
    
    TFile *f = TFile::Open("/home/aranyi/CMSSW_2_2_9/data/RA4_Study_20091201/Wjets_1/Wjets_1_RA4Synchronization_1.root");
    gDirectory->GetObject("RA4SynchronizationMod/RA4 Jet+Met+Muon  1st Muon  pt >= 10 GeV;1",first_muon_Wjets_1);
    
    TFile *f = TFile::Open("/home/aranyi/CMSSW_2_2_9/data/RA4_Study_20091201/Zjets/Zjets_RA4Synchronization_1.root");    
    gDirectory->GetObject("RA4SynchronizationMod/RA4 Jet+Met+Muon  1st Muon  pt >= 10 GeV;1",first_muon_Zjets);




    TCanvas *c3 = new TCanvas("c3","pt");

    if (normalization=="xsec") {
      
      x_cross=110.0;       // cross section [pb]
      num_events=202686.0; // number of events were used in the calculation
      max_events=202686.0; // maximum number of events
      first_muon_LM0->Scale((x_cross*luminosity/num_events));
      
      
      x_cross=317.0;       // cross section [pb]
      num_events=200000.0; // number of events were used in the calculation
      max_events=946644.0; // maximum number of events
      first_muon_TTbar->Scale((x_cross*luminosity/num_events));
      
      
      x_cross=40000.0;       // cross section [pb]
      num_events=200000.0; // number of events were used in the calculation
      max_events=9745661.0; // maximum number of events
      first_muon_Wjets_1->Scale((x_cross*luminosity/num_events));
      
      
      x_cross=3700.0;       // cross section [pb]
      num_events=200000.0; // number of events were used in the calculation
      max_events=1262816.0; // maximum number of events
      first_muon_Zjets->Scale((x_cross*luminosity/num_events));
    
    }
    
    if (normalization=="integral") {
      
      Double_t norm=first_muon_LM0->Integral();
      first_muon_LM0->Scale(1/norm);
      
      Double_t norm=first_muon_TTbar->Integral();
      first_muon_TTbar->Scale(1/norm);
      
      Double_t norm=first_muon_Wjets_1->Integral();
      first_muon_Wjets_1->Scale(1/norm);
      
      Double_t norm=first_muon_Zjets->Integral();
      first_muon_Zjets->Scale(1/norm);
    
    }
    
    first_muon_LM0->SetXTitle("GeV");
    drawHist(first_muon_LM0,first_muon_TTbar,first_muon_Wjets_1,first_muon_Zjets,fillcolor);
    
    TCanvas *c3_b=c3->Clone();
    c3_b->SetName("pt (log)");               
    
    c3_b->SetLogy(1);
    c3_b->Draw();
    
    if (save2pdf==1) c3->Print("test/scripts/pt.pdf");             
    if (save2pdf==1) c3_b->Print("test/scripts/pt_log.pdf");
    
///____________________________________________________________________________
///                                  chi2_ndof

    TFile *f = TFile::Open("/home/aranyi/CMSSW_2_2_9/data/RA4_Study_20091201/LM0/LM0_RA4Synchronization_1.root");
    gDirectory->GetObject("RA4SynchronizationMod/RA4 Jet+Met+Muon  1st Muon  globalTrack fit chi2_ndof < 10;1",first_muon_LM0);
    
    TFile *f = TFile::Open("/home/aranyi/CMSSW_2_2_9/data/RA4_Study_20091201/TTbar/TTbar_RA4Synchronization_1.root");    
    gDirectory->GetObject("RA4SynchronizationMod/RA4 Jet+Met+Muon  1st Muon  globalTrack fit chi2_ndof < 10;1",first_muon_TTbar);
    
    TFile *f = TFile::Open("/home/aranyi/CMSSW_2_2_9/data/RA4_Study_20091201/Wjets_1/Wjets_1_RA4Synchronization_1.root");
    gDirectory->GetObject("RA4SynchronizationMod/RA4 Jet+Met+Muon  1st Muon  globalTrack fit chi2_ndof < 10;1",first_muon_Wjets_1);
    
    TFile *f = TFile::Open("/home/aranyi/CMSSW_2_2_9/data/RA4_Study_20091201/Zjets/Zjets_RA4Synchronization_1.root");    
    gDirectory->GetObject("RA4SynchronizationMod/RA4 Jet+Met+Muon  1st Muon  globalTrack fit chi2_ndof < 10;1",first_muon_Zjets);




    TCanvas *c4 = new TCanvas("c4","chi2/ndof");

    if (normalization=="xsec") {
      
      x_cross=110.0;       // cross section [pb]
      num_events=202686.0; // number of events were used in the calculation
      max_events=202686.0; // maximum number of events
      first_muon_LM0->Scale((x_cross*luminosity/num_events));
      
      
      x_cross=317.0;       // cross section [pb]
      num_events=200000.0; // number of events were used in the calculation
      max_events=946644.0; // maximum number of events
      first_muon_TTbar->Scale((x_cross*luminosity/num_events));
      
      
      x_cross=40000.0;       // cross section [pb]
      num_events=200000.0; // number of events were used in the calculation
      max_events=9745661.0; // maximum number of events
      first_muon_Wjets_1->Scale((x_cross*luminosity/num_events));
      
      
      x_cross=3700.0;       // cross section [pb]
      num_events=200000.0; // number of events were used in the calculation
      max_events=1262816.0; // maximum number of events
      first_muon_Zjets->Scale((x_cross*luminosity/num_events));
    
    }
    
    if (normalization=="integral") {
      
      Double_t norm=first_muon_LM0->Integral();
      first_muon_LM0->Scale(1/norm);
      
      Double_t norm=first_muon_TTbar->Integral();
      first_muon_TTbar->Scale(1/norm);
      
      Double_t norm=first_muon_Wjets_1->Integral();
      first_muon_Wjets_1->Scale(1/norm);
      
      Double_t norm=first_muon_Zjets->Integral();
      first_muon_Zjets->Scale(1/norm);
    
    }
    
    first_muon_LM0->SetAxisRange(0,8);
    first_muon_TTbar->SetAxisRange(0,8);
    first_muon_Wjets_1->SetAxisRange(0,8);
    first_muon_Zjets->SetAxisRange(0,8); 
    
    
    drawHist(first_muon_LM0,first_muon_TTbar,first_muon_Wjets_1,first_muon_Zjets,fillcolor);
    
    TCanvas *c4_b=c4->Clone();
    c4_b->SetName("chi2/ndof (log)");               
    
    c4_b->SetLogy(1);
    c4_b->Draw();
    
    if (save2pdf==1) c4->Print("test/scripts/chi2_ndof.pdf");             
    if (save2pdf==1) c4_b->Print("test/scripts/chi2_ndof_log.pdf");
        

///____________________________________________________________________________
///                                  bc_d0

    TFile *f = TFile::Open("/home/aranyi/CMSSW_2_2_9/data/RA4_Study_20091201/LM0/LM0_RA4Synchronization_1.root");
    gDirectory->GetObject("RA4SynchronizationMod/RA4 Jet+Met+Muon  1st Muon  d0 (from primary vertex) < 0.2 cm;1",first_muon_LM0);
    
    TFile *f = TFile::Open("/home/aranyi/CMSSW_2_2_9/data/RA4_Study_20091201/TTbar/TTbar_RA4Synchronization_1.root");    
    gDirectory->GetObject("RA4SynchronizationMod/RA4 Jet+Met+Muon  1st Muon  d0 (from primary vertex) < 0.2 cm;1",first_muon_TTbar);
    
    TFile *f = TFile::Open("/home/aranyi/CMSSW_2_2_9/data/RA4_Study_20091201/Wjets_1/Wjets_1_RA4Synchronization_1.root");
    gDirectory->GetObject("RA4SynchronizationMod/RA4 Jet+Met+Muon  1st Muon  d0 (from primary vertex) < 0.2 cm;1",first_muon_Wjets_1);
    
    TFile *f = TFile::Open("/home/aranyi/CMSSW_2_2_9/data/RA4_Study_20091201/Zjets/Zjets_RA4Synchronization_1.root");    
    gDirectory->GetObject("RA4SynchronizationMod/RA4 Jet+Met+Muon  1st Muon  d0 (from primary vertex) < 0.2 cm;1",first_muon_Zjets);




    TCanvas *c5 = new TCanvas("c5","d0");

    if (normalization=="xsec") {
      
      x_cross=110.0;       // cross section [pb]
      num_events=202686.0; // number of events were used in the calculation
      max_events=202686.0; // maximum number of events
      first_muon_LM0->Scale((x_cross*luminosity/num_events));
      
      
      x_cross=317.0;       // cross section [pb]
      num_events=200000.0; // number of events were used in the calculation
      max_events=946644.0; // maximum number of events
      first_muon_TTbar->Scale((x_cross*luminosity/num_events));
      
      
      x_cross=40000.0;       // cross section [pb]
      num_events=200000.0; // number of events were used in the calculation
      max_events=9745661.0; // maximum number of events
      first_muon_Wjets_1->Scale((x_cross*luminosity/num_events));
      
      
      x_cross=3700.0;       // cross section [pb]
      num_events=200000.0; // number of events were used in the calculation
      max_events=1262816.0; // maximum number of events
      first_muon_Zjets->Scale((x_cross*luminosity/num_events));
    
    }
    
    if (normalization=="integral") {
      
      Double_t norm=first_muon_LM0->Integral();
      first_muon_LM0->Scale(1/norm);
      
      Double_t norm=first_muon_TTbar->Integral();
      first_muon_TTbar->Scale(1/norm);
      
      Double_t norm=first_muon_Wjets_1->Integral();
      first_muon_Wjets_1->Scale(1/norm);
      
      Double_t norm=first_muon_Zjets->Integral();
      first_muon_Zjets->Scale(1/norm);
    
    }
    
    first_muon_LM0->SetAxisRange(0,0.05);
    first_muon_TTbar->SetAxisRange(0,0.05);
    first_muon_Wjets_1->SetAxisRange(0,0.05);
    first_muon_Zjets->SetAxisRange(0,0.05);  
    
    first_muon_LM0->SetXTitle("cm");
    
    drawHist(first_muon_LM0,first_muon_TTbar,first_muon_Wjets_1,first_muon_Zjets,fillcolor);
    
    TCanvas *c5_b=c5->Clone();
    c5_b->SetName("d0 (log)");               
    
    c5_b->SetLogy(1);
    c5_b->Draw();
    
    if (save2pdf==1) c5->Print("test/scripts/d0.pdf");             
    if (save2pdf==1) c5_b->Print("test/scripts/d0_log.pdf");
 
///____________________________________________________________________________
///                                isoR03_trk

    TFile *f = TFile::Open("/home/aranyi/CMSSW_2_2_9/data/RA4_Study_20091201/LM0/LM0_RA4Synchronization_1.root");
    gDirectory->GetObject("RA4SynchronizationMod/RA4 Jet+Met+Muon  1st Muon  Tracker Isolation < 6 GeV;1",first_muon_LM0);
    
    TFile *f = TFile::Open("/home/aranyi/CMSSW_2_2_9/data/RA4_Study_20091201/TTbar/TTbar_RA4Synchronization_1.root");    
    gDirectory->GetObject("RA4SynchronizationMod/RA4 Jet+Met+Muon  1st Muon  Tracker Isolation < 6 GeV;1",first_muon_TTbar);
    
    TFile *f = TFile::Open("/home/aranyi/CMSSW_2_2_9/data/RA4_Study_20091201/Wjets_1/Wjets_1_RA4Synchronization_1.root");
    gDirectory->GetObject("RA4SynchronizationMod/RA4 Jet+Met+Muon  1st Muon  Tracker Isolation < 6 GeV;1",first_muon_Wjets_1);
    
    TFile *f = TFile::Open("/home/aranyi/CMSSW_2_2_9/data/RA4_Study_20091201/Zjets/Zjets_RA4Synchronization_1.root");    
    gDirectory->GetObject("RA4SynchronizationMod/RA4 Jet+Met+Muon  1st Muon  Tracker Isolation < 6 GeV;1",first_muon_Zjets);




    TCanvas *c6 = new TCanvas("c6","isoR03_trk");

    if (normalization=="xsec") {
      
      x_cross=110.0;       // cross section [pb]
      num_events=202686.0; // number of events were used in the calculation
      max_events=202686.0; // maximum number of events
      first_muon_LM0->Scale((x_cross*luminosity/num_events));
      
      
      x_cross=317.0;       // cross section [pb]
      num_events=200000.0; // number of events were used in the calculation
      max_events=946644.0; // maximum number of events
      first_muon_TTbar->Scale((x_cross*luminosity/num_events));
      
      
      x_cross=40000.0;       // cross section [pb]
      num_events=200000.0; // number of events were used in the calculation
      max_events=9745661.0; // maximum number of events
      first_muon_Wjets_1->Scale((x_cross*luminosity/num_events));
      
      
      x_cross=3700.0;       // cross section [pb]
      num_events=200000.0; // number of events were used in the calculation
      max_events=1262816.0; // maximum number of events
      first_muon_Zjets->Scale((x_cross*luminosity/num_events));
    
    }
    
    if (normalization=="integral") {
      
      Double_t norm=first_muon_LM0->Integral();
      first_muon_LM0->Scale(1/norm);
      
      Double_t norm=first_muon_TTbar->Integral();
      first_muon_TTbar->Scale(1/norm);
      
      Double_t norm=first_muon_Wjets_1->Integral();
      first_muon_Wjets_1->Scale(1/norm);
      
      Double_t norm=first_muon_Zjets->Integral();
      first_muon_Zjets->Scale(1/norm);
    
    }
    
    first_muon_LM0->SetAxisRange(0,isolation_xrange);
    first_muon_TTbar->SetAxisRange(0,isolation_xrange);
    first_muon_Wjets_1->SetAxisRange(0,isolation_xrange);
    first_muon_Zjets->SetAxisRange(0,isolation_xrange);  
    
    first_muon_LM0->SetXTitle("GeV");
    
    drawHist(first_muon_LM0,first_muon_TTbar,first_muon_Wjets_1,first_muon_Zjets,fillcolor);
    
    TCanvas *c6_b=c6->Clone();
    c6_b->SetName("isoR03_trk (log)");               
    
    c6_b->SetLogy(1);
    c6_b->Draw();
    
    if (save2pdf==1) c6->Print("test/scripts/isoR03_trk.pdf");             
    if (save2pdf==1) c6_b->Print("test/scripts/isoR03_trk_log.pdf");
    
 
///____________________________________________________________________________
///                                isoR03_hcal

    TFile *f = TFile::Open("/home/aranyi/CMSSW_2_2_9/data/RA4_Study_20091201/LM0/LM0_RA4Synchronization_1.root");
    gDirectory->GetObject("RA4SynchronizationMod/RA4 Jet+Met+Muon  1st Muon  HCAL Isolation < 6 GeV;1",first_muon_LM0);
    
    TFile *f = TFile::Open("/home/aranyi/CMSSW_2_2_9/data/RA4_Study_20091201/TTbar/TTbar_RA4Synchronization_1.root");    
    gDirectory->GetObject("RA4SynchronizationMod/RA4 Jet+Met+Muon  1st Muon  HCAL Isolation < 6 GeV;1",first_muon_TTbar);
    
    TFile *f = TFile::Open("/home/aranyi/CMSSW_2_2_9/data/RA4_Study_20091201/Wjets_1/Wjets_1_RA4Synchronization_1.root");
    gDirectory->GetObject("RA4SynchronizationMod/RA4 Jet+Met+Muon  1st Muon  HCAL Isolation < 6 GeV;1",first_muon_Wjets_1);
    
    TFile *f = TFile::Open("/home/aranyi/CMSSW_2_2_9/data/RA4_Study_20091201/Zjets/Zjets_RA4Synchronization_1.root");    
    gDirectory->GetObject("RA4SynchronizationMod/RA4 Jet+Met+Muon  1st Muon  HCAL Isolation < 6 GeV;1",first_muon_Zjets);




    TCanvas *c7 = new TCanvas("c7","isoR03_hcal");

    if (normalization=="xsec") {
      
      x_cross=110.0;       // cross section [pb]
      num_events=202686.0; // number of events were used in the calculation
      max_events=202686.0; // maximum number of events
      first_muon_LM0->Scale((x_cross*luminosity/num_events));
      
      
      x_cross=317.0;       // cross section [pb]
      num_events=200000.0; // number of events were used in the calculation
      max_events=946644.0; // maximum number of events
      first_muon_TTbar->Scale((x_cross*luminosity/num_events));
      
      
      x_cross=40000.0;       // cross section [pb]
      num_events=200000.0; // number of events were used in the calculation
      max_events=9745661.0; // maximum number of events
      first_muon_Wjets_1->Scale((x_cross*luminosity/num_events));
      
      
      x_cross=3700.0;       // cross section [pb]
      num_events=200000.0; // number of events were used in the calculation
      max_events=1262816.0; // maximum number of events
      first_muon_Zjets->Scale((x_cross*luminosity/num_events));
    
    }
    
    if (normalization=="integral") {
      
      Double_t norm=first_muon_LM0->Integral();
      first_muon_LM0->Scale(1/norm);
      
      Double_t norm=first_muon_TTbar->Integral();
      first_muon_TTbar->Scale(1/norm);
      
      Double_t norm=first_muon_Wjets_1->Integral();
      first_muon_Wjets_1->Scale(1/norm);
      
      Double_t norm=first_muon_Zjets->Integral();
      first_muon_Zjets->Scale(1/norm);
    
    }
    
    first_muon_LM0->SetAxisRange(0,isolation_xrange);
    first_muon_TTbar->SetAxisRange(0,isolation_xrange);
    first_muon_Wjets_1->SetAxisRange(0,isolation_xrange);
    first_muon_Zjets->SetAxisRange(0,isolation_xrange);  
    
    first_muon_LM0->SetXTitle("GeV");
    
    drawHist(first_muon_LM0,first_muon_TTbar,first_muon_Wjets_1,first_muon_Zjets,fillcolor);
    
    TCanvas *c7_b=c7->Clone();
    c7_b->SetName("isoR03_hcal (log)");               
    
    c7_b->SetLogy(1);
    c7_b->Draw();
    
    if (save2pdf==1) c7->Print("test/scripts/isoR03_hcal.pdf");             
    if (save2pdf==1) c7_b->Print("test/scripts/isoR03_hcal_log.pdf");
  
///____________________________________________________________________________
///                                isoR03_ecal

    TFile *f = TFile::Open("/home/aranyi/CMSSW_2_2_9/data/RA4_Study_20091201/LM0/LM0_RA4Synchronization_1.root");
    gDirectory->GetObject("RA4SynchronizationMod/RA4 Jet+Met+Muon  1st Muon  ECAL Isolation < 6 GeV;1",first_muon_LM0);
    
    TFile *f = TFile::Open("/home/aranyi/CMSSW_2_2_9/data/RA4_Study_20091201/TTbar/TTbar_RA4Synchronization_1.root");    
    gDirectory->GetObject("RA4SynchronizationMod/RA4 Jet+Met+Muon  1st Muon  ECAL Isolation < 6 GeV;1",first_muon_TTbar);
    
    TFile *f = TFile::Open("/home/aranyi/CMSSW_2_2_9/data/RA4_Study_20091201/Wjets_1/Wjets_1_RA4Synchronization_1.root");
    gDirectory->GetObject("RA4SynchronizationMod/RA4 Jet+Met+Muon  1st Muon  ECAL Isolation < 6 GeV;1",first_muon_Wjets_1);
    
    TFile *f = TFile::Open("/home/aranyi/CMSSW_2_2_9/data/RA4_Study_20091201/Zjets/Zjets_RA4Synchronization_1.root");    
    gDirectory->GetObject("RA4SynchronizationMod/RA4 Jet+Met+Muon  1st Muon  ECAL Isolation < 6 GeV;1",first_muon_Zjets);




    TCanvas *c8 = new TCanvas("c8","isoR03_ecal");


    if (normalization=="xsec") {
      
      x_cross=110.0;       // cross section [pb]
      num_events=202686.0; // number of events were used in the calculation
      max_events=202686.0; // maximum number of events
      first_muon_LM0->Scale((x_cross*luminosity/num_events));
      
      
      x_cross=317.0;       // cross section [pb]
      num_events=200000.0; // number of events were used in the calculation
      max_events=946644.0; // maximum number of events
      first_muon_TTbar->Scale((x_cross*luminosity/num_events));
      
      
      x_cross=40000.0;       // cross section [pb]
      num_events=200000.0; // number of events were used in the calculation
      max_events=9745661.0; // maximum number of events
      first_muon_Wjets_1->Scale((x_cross*luminosity/num_events));
      
      
      x_cross=3700.0;       // cross section [pb]
      num_events=200000.0; // number of events were used in the calculation
      max_events=1262816.0; // maximum number of events
      first_muon_Zjets->Scale((x_cross*luminosity/num_events));
    
    }
    
    if (normalization=="integral") {
      
      Double_t norm=first_muon_LM0->Integral();
      first_muon_LM0->Scale(1/norm);
      
      Double_t norm=first_muon_TTbar->Integral();
      first_muon_TTbar->Scale(1/norm);
      
      Double_t norm=first_muon_Wjets_1->Integral();
      first_muon_Wjets_1->Scale(1/norm);
      
      Double_t norm=first_muon_Zjets->Integral();
      first_muon_Zjets->Scale(1/norm);
    
    }        
    
    first_muon_LM0->SetAxisRange(0,isolation_xrange);
    first_muon_TTbar->SetAxisRange(0,isolation_xrange);
    first_muon_Wjets_1->SetAxisRange(0,isolation_xrange);
    first_muon_Zjets->SetAxisRange(0,isolation_xrange);    
    
    first_muon_LM0->SetXTitle("GeV");
        
    drawHist(first_muon_LM0,first_muon_TTbar,first_muon_Wjets_1,first_muon_Zjets,fillcolor);
  
    TCanvas *c8_b=c8->Clone();
    c8_b->SetName("isoR03_ecal (log)");               
    
    c8_b->SetLogy(1);
    c8_b->Draw();
    
    if (save2pdf==1) c8->Print("test/scripts/isoR03_ecal.pdf");             
    if (save2pdf==1) c8_b->Print("test/scripts/isoR03_ecal_log.pdf");
      
}   

double getMax(TH1F *LM0,TH1F *TTbar,TH1F *Wjets_1,TH1F *Zjets){
  double max=0.0;
  for (unsigned int i=0;i<LM0->GetSize();i++){
    if (max < LM0->GetBinContent(i))
      max = LM0->GetBinContent(i);
  }
  for (unsigned int i=0;i<TTbar->GetSize();i++){
    if (max < TTbar->GetBinContent(i))
      max = TTbar->GetBinContent(i);
  }
  for (unsigned int i=0;i<Wjets_1->GetSize();i++){
    if (max < Wjets_1->GetBinContent(i))
      max = Wjets_1->GetBinContent(i);
  }
  for (unsigned int i=0;i<Zjets->GetSize();i++){
    if (max < Zjets->GetBinContent(i))
      max = Zjets->GetBinContent(i);
  }
  return max;
};

void drawHist(TH1F *LM0,TH1F *TTbar,TH1F *Wjets_1,TH1F *Zjets,int fillcolor){
  if (fillcolor==1) {
    
    LM0->SetFillColor(kRed);
    TTbar->SetFillColor(kGreen);
    Wjets_1->SetFillColor(kBlue);
    Zjets->SetFillColor(kBlack); 
    
  }
    
        
  LM0->SetLineColor(kRed);
  TTbar->SetLineColor(kGreen);
  Wjets_1->SetLineColor(kBlue);
  Zjets->SetLineColor(kBlack);
    
  LM0->SetStats(0);
  TTbar->SetStats(0);
  Wjets_1->SetStats(0);
  Zjets->SetStats(0);        
    
    //first_muon_LM0->SetAxisRange(0,6);
    
  max=getMax(LM0,TTbar,Wjets_1,Zjets);
            
  LM0->SetMaximum(max*1.1);
    
  LM0->Draw("same");
  TTbar->Draw("same");
  Wjets_1->Draw("same");
  Zjets->Draw("same");
    
  TLegend *legend = new TLegend(.75,.80,.95,.95); 
  legend->AddEntry(LM0,"LM0"); 
  legend->AddEntry(TTbar,"TTbar"); 
  legend->AddEntry(Wjets_1,"Wjets"); 
  legend->AddEntry(Zjets,"Zjets");
  legend->Draw();  
};
    

//c19b->Print("test/scripts/pt_all.pdf");                             
