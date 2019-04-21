{
    TFile *tf = new TFile("MyAnalysisAlgHistograms.root");
    TTree *tt = (TTree*)tf->Get("MyTree");
 
    tt->Draw("z_inv_mass_tlv >> tlv(100,0.,250.)");
    
    tlv->SetTitle("Z invariant mass reconstruction by using TLorentzVector");
    tlv->SetXTitle("Invariant mass[GeV/c^{2}]");
    tlv->SetYTitle("Entries");
    
    tlv->Fit("gaus","","",80.,100.);
    gStyle->SetOptFit();
}
