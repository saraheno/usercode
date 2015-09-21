#include "TFile.h"
#include "TTree.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>

#include "TMath.h"
#include "TLorentzVector.h"



void analyse() 
{

   cout<<"1"<<endl;
   TH1F* hntot = new TH1F("hntot","number particles",100,0.,1000.);
   TH2F* hnchneu = new TH2F("hnchneu","number charged versus neutral", 100,0.,1000.,100,0.,1000.);
   TH2F* hncenf = new TH2F("hncenf","number central versus forward", 100,0.,100.,100,0.,100.);
   TH1F* hpid = new TH1F("hpid","pid particles",1000,-500.,500.);
   TH1F* hpT = new TH1F("hpT","PT particles",100,0.,10.);
   TH1F* heta = new TH1F("heta","eta particles",100,-10.,10.);
   TH1F* hphi = new TH1F("hphi","phi particles",50,-4.,4.);
   TH2F* hetaphi = new TH2F("hetaphi","delta eta delta phi between particles",100,0.,5.,100,0.,3.5);
   TH1F* hdeta = new TH1F("hdeta","deta particles",100,0.,10.);
   TH1F* hdphi = new TH1F("hdphi","dphi particles",50,0.,3.5);

   cout<<"2"<<endl;
   TLorentzVector * vv= new TLorentzVector();
   TLorentzVector * vv2= new TLorentzVector();

   cout<<"3"<<endl;
   float deta,dphi,dphi2;

  Int_t totalSize=0;
  TFile *f = TFile::Open("PythiaOutput.root");
  if (f==0) {
    printf("Error: can not open file");
    return;
  }

  TTree *T = (TTree*)f->Get("t1");
  Int_t nCharged,nNeutral,nTot,APID[5000];
  Float_t Apx[5000],Apy[5000],Apz[5000],Ae[5000];
  t1->SetBranchAddress("nCharged",&nCharged);
  t1->SetBranchAddress("nNeutral",&nNeutral);
  t1->SetBranchAddress("nTot",&nTot);
  t1->SetBranchAddress("APID",&APID);
  t1->SetBranchAddress("Apx",&Apx);
  t1->SetBranchAddress("Apy",&Apy);
  t1->SetBranchAddress("Apz",&Apz);
  t1->SetBranchAddress("Ae",&Ae);

  Long64_t nentries = t1->GetEntries();
  for (Long64_t jentry=0; jentry<nentries;jentry++) {  // loop over events
  //  for (Long64_t jentry=0; jentry<100;jentry++) {  // loop over events
    cout<<"     "<<jentry<<endl;
    t1->GetEntry(jentry);

    if(nTot>5000) cout<<"Danger Danger Will Robinson"<<endl;


    hntot->Fill(nTot);
    if(nCharged>3&&nNeutral>3) hnchneu->Fill(nCharged,nNeutral);

    Int_t ncnt=0;
    Int_t nCen=0;
    Int_t nF=0;; // count in different rapidity regions    
    for(int jj=0; jj<nTot; ++jj) {  // for each particle         
      hpid->Fill(APID[jj]);
      vv->SetPxPyPzE(Apx[jj],Apy[jj],Apz[jj],Ae[jj]);        
      if(fabs(vv->Eta())<5.&&vv->Pt()>0.1) {
	ncnt+=1;
	if(fabs(vv->Eta())<3.) {
	  nCen+=1;
	} else {
	  nF+=1;
	}
        hpT->Fill(vv->Pt());
        heta->Fill(vv->Eta());
        hphi->Fill(vv->Phi());
    // for each particle, fill a 2D histogram with delta-eta, delta-phi with all other particles              
        for(int kk=jj+1; kk<nTot; ++kk) {
          vv2->SetPxPyPzE(Apx[kk],Apy[kk],Apz[kk],Ae[kk]);
          if(fabs(vv2->Eta())<5.&&vv2->Pt()>0.1) {
	    deta=fabs(vv->Eta() - vv2->Eta());
	    dphi=fabs(vv->Phi() - vv2->Phi());
	    dphi2=(6.2831853-dphi);
	    if(dphi2<dphi) dphi=dphi2;
	    hetaphi->Fill(deta,dphi);
	    hdeta->Fill(deta);
	    hdphi->Fill(dphi);
          }
        }
      }
    }  //end loop over particles                                                                  
    //    cout<<nCen<<" "<<nF<<" "<<ncnt<<endl;
    if(nCen>2&&nF>2) hncenf->Fill(nCen,nF);

  }  // end loop over events

   cout<<"4"<<endl;
   gStyle->SetOptStat(111111);
   hetaphi->SetFillColor(17);
   //   hetaphi->Draw("lego");a                                                             
   //   TFile *newfile = new TFile("morehists.root","recreate");                            
   //   hetaphi->Write();                                                                   
   //   newfile->Close();                                                                   
   cout<<"5"<<endl;
   TCanvas *c1 = new TCanvas("c1","c1",0,0,900,1000);
   hntot->Draw();
   c1->Print("aaantot.gif");
   heta->Draw();
   c1->Print("aaaeta.gif");
   hphi->Draw();
   c1->Print("aaaphi.gif");
   hpT->Draw();
   c1->Print("aaapt.gif");
   hetaphi->Draw("lego");
   c1->Print("aaaetaphi.gif");
   hnchneu->Draw("lego");
   c1->Print("aaanchneu.gif");
   hncenf->Draw("lego");
   c1->Print("aaanccenf.gif");

   //   hdphi->Draw();      


}
