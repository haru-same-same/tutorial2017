{
    TFile *tf = new TFile("MyAnalysisAlgHistograms.root");
    TTree *mt = (TTree*)tf->Get("MyTree");
 
    vector<double> *pt_1;
    //vector<double> *phi_1 = 0;
    //vector<double> *eta_1 = 0;
    //vector<double> *e_1 = 0;
    //vector<double> *pt_2 = 0;
    //vector<double> *phi_2 = 0;
    //vector<double> *eta_2 = 0;
    //vector<double> *e_2 = 0;
    
    mt->SetBranchAddress("muon_pt_sel1",&pt_1);
    //mt->SetBranchAddress("muon_phi_sel1",&phi_1);
    //mt->SetBranchAddress("muon_eta_sel1",&eta_1);
    //mt->SetBranchAddress("muon_e_sel1",&e_1);
    //mt->SetBranchAddress("muon_pt_sel2",&pt_2);
    //mt->SetBranchAddress("muon_phi_sel2",&phi_2);
    //mt->SetBranchAddress("muon_eta_sel2",&eta_2);
    //mt->SetBranchAddress("muon_e_sel2",&e_2);

    //TLorentzVector mu1;
    //TLorentzVector mu2;
 
    const long N = mt->GetEntries();
    for(long ient = 0;ient < 100;ient++){
        mt->GetEntry(ient);
        for(int j = 0;j < 100;j++){
            cout << pt_1->at(j) << endl;
        }
    }
}
