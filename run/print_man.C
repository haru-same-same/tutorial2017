{
    TFile *tf = new TFile("MyAnalysisAlgHistograms.root");
    TTree *tt = (TTree*)tf->Get("MyTree");
 
    tt->Draw("z_inv_mass_man >> man(100,0.,250.)");
    
    man->SetTitle("Z invariant mass reconstruction by manual");
    man->SetXTitle("Invariant mass[GeV/c^{2}]");
    man->SetYTitle("Entries");
}
