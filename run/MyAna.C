#define MyAna_cxx
#include "MyAna.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>

void MyAna::Loop()
{
//   In a ROOT session, you can do:
//      root> .L MyAna.C
//      root> MyAna t
//      root> t.GetEntry(12); // Fill t data members with entry number 12
//      root> t.Show();       // Show values of entry 12
//      root> t.Show(16);     // Read and show values of entry 16
//      root> t.Loop();       // Loop on all entries
//

//     This is the loop skeleton where:
//    jentry is the global entry number in the chain
//    ientry is the entry number in the current Tree
//  Note that the argument to GetEntry must be:
//    jentry for TChain::GetEntry
//    ientry for TTree::GetEntry and TBranch::GetEntry
//
//       To read only selected branches, Insert statements like:
// METHOD1:
//    fChain->SetBranchStatus("*",0);  // disable all branches
//    fChain->SetBranchStatus("branchname",1);  // activate branchname
// METHOD2: replace line
//    fChain->GetEntry(jentry);       //read all branches
//by  b_branchname->GetEntry(ientry); //read only this branch
   if (fChain == 0) return;
    
   TFile rootFile("hist.root","recreate");
   TH1D *h_muon_pt = new TH1D("muon_pt","muon_pt",100,0.,250.);
   TH1D *h_muon_eta = new TH1D("muon_eta","muon_eta",100,-3.,3.);
    
   Long64_t nentries = fChain->GetEntriesFast();

   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      for(int iMuon = 0;iMuon<nMuons;++iMuon){
        h_muon_pt->Fill(muon_pt->at(iMuon));
        h_muon_eta->Fill(muon_eta->at(iMuon));
      }
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      // if (Cut(ientry) < 0) continue;
   }
   rootFile.Write();
   rootFile.Close();
}
