// main91.cc is a part of the PYTHIA event generator.
// Copyright (C) 2015 Torbjorn Sjostrand.
// PYTHIA is licenced under the GNU GPL version 2, see COPYING for details.
// Please respect the MCnet Guidelines, see GUIDELINES for details.

// This is a simple test program.
// It studies the charged multiplicity distribution at the LHC.
// Modified by Rene Brun, Axel Naumann and Bernhard Meirose
// to use ROOT for histogramming.

// Stdlib header file for input and output.
#include <iostream>

// Header file to access Pythia 8 program elements.
#include "Pythia8/Pythia.h"

// ROOT, for histogramming.
#include "TH1.h"
#include "TTree.h"

// ROOT, for interactive graphics.
#include "TVirtualPad.h"
#include "TApplication.h"

// ROOT, for saving file.
#include "TFile.h"

using namespace Pythia8;

int nCharged, nNeutral, nTot;
Int_t APID[5000];
Float_t Apx[5000];
Float_t Apy[5000];
Float_t Apz[5000];
Float_t Ae[5000]; 

int main(int argc, char* argv[]) {

  // Create the ROOT application environment.
  TApplication theApp("hist", &argc, argv);

  // Create Pythia instance and set it up to generate hard QCD processes
  // above pTHat = 20 GeV for pp collisions at 14 TeV.
  Pythia pythia;
  pythia.readFile("minBias.cmnd");
  pythia.init();

  // Create file on which histogram(s) can be saved.
  TFile* outFile = new TFile("PythiaOutput.root", "RECREATE");

  // Book histogram.
  TH1F *multch = new TH1F("multch","charged multiplicity", 100, -0.5, 799.5);
  TH1F *multneu = new TH1F("multneu","neutral multiplicity", 100, -0.5, 799.5);
  TH1F *ppid = new TH1F("ppid","particle identification number", 1000, -500, 500);

  // Book tree
  TTree* t1= new TTree("t1","a tree");
  t1->Branch("nCharged",&nCharged,"nCharged/I");
  t1->Branch("nNeutral",&nNeutral,"nNeutral/I");
  t1->Branch("nTot",&nTot,"nTot/I");
  t1->Branch("APID",APID,"APID[nTot]/I");
  t1->Branch("Apx",Apx,"Apx[nTot]/F");
  t1->Branch("Apy",Apy,"Apy[nTot]/F");
  t1->Branch("Apz",Apz,"Apz[nTot]/F");
  t1->Branch("Ae",Ae,"Ae[nTot]/F");

  // Begin event loop. Generate event; skip if generation aborted.
  //  std::cout<<"New Event"<<std::endl;
  for (int iEvent = 0; iEvent < 50000; ++iEvent) {
    if (!pythia.next()) continue;

    // Find number of all final charged particles.
    nCharged = 0;  // for counting the number of stable charged particles in the event
    nNeutral = 0;  // ditto neutral
    nTot=0;
    int i1=0;
    int i2=0;
    for (int i = 0; i < pythia.event.size(); ++i) {  // loop over all particles in the event
      //      std::cout<<pythia.event[i].isCharged()<<endl;
      if (pythia.event[i].isFinal() && pythia.event[i].isCharged()==0)  // count if stable and charged
        ++nCharged;

      if (pythia.event[i].isFinal() && pythia.event[i].isCharged()!=0) // count if stable and neutral
        ++nNeutral;

      if(pythia.event[i].isFinal()) {  // if stable
	ppid->Fill( pythia.event[i].id() );  // get the type of the particle
	nTot=nTot+1;  //count
        APID[nTot-1]=pythia.event[i].id();  
        Apx[nTot-1]=pythia.event[i].px();
        Apy[nTot-1]=pythia.event[i].py();
        Apz[nTot-1]=pythia.event[i].pz(); 
        Ae[nTot-1]=pythia.event[i].e();
	//	cout<<"   id px py pz e "<<pythia.event[i].id()<<" "<<pythia.event[i].px()<<" "<<pythia.event[i].py()<<" "<<pythia.event[i].pz()<<" "<<pythia.event[i].e()<<std::endl;
      }
    }  // end particle list loop 
    // Fill charged multiplicity in histogram. End event loop.
    multch->Fill( nCharged );
    multneu->Fill( nNeutral );
    if(nTot>5000) std::cout<<"Danger Danger Will Robinson"<<std::endl;
    t1->Fill();
  }

  // Statistics on event generation.
  pythia.stat();


  // Save histogram on file and close file.
  multch->Write();
  multneu->Write();
  ppid->Write();
  t1->Write();
  delete outFile;

  // Done.
  return 0;
}
