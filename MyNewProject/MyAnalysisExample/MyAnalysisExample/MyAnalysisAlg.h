#ifndef MYANALYSISALG_H // Include guard
#define MYANALYSISALG_H

#include "AthenaBaseComps/AthAlgorithm.h"
#include "MuonSelectorTools/IMuonSelectionTool.h"

class ITHistSvc;
class TH1D;
class TH2D;
class TTree;

class MyAnalysisAlg:public AthAlgorithm
{
 public:
  MyAnalysisAlg(const std::string& name, ISvcLocator* pSvcLocator); // Constructor
  StatusCode initialize();
  StatusCode finalize();
  StatusCode execute();

 private:
  std::string m_message;
  ITHistSvc *m_thistSvc;
  TH1D *m_h_nMuons;
  TH1D *m_h_muon_e;
  TH1D *m_h_muon_pt;
  TH1D *m_h_muon_eta;
  TH1D *m_h_muon_phi;
  TH2D *m_h2_muon_eta_phi;
  TTree *m_tree;
  int m_eventNumber;
  int m_runNumber;
  int m_nMuons;
  std::vector<int> *m_muon_author;
  std::vector<double> *m_muon_phi;
  std::vector<double> *m_muon_eta;
  std::vector<double> *m_muon_pt;
  std::vector<double> *m_muon_e;
  std::vector<double> *m_muon_phi_sel1;
  std::vector<double> *m_muon_eta_sel1;
  std::vector<double> *m_muon_pt_sel1;
  std::vector<double> *m_muon_e_sel1;
  std::vector<double> *m_muon_phi_sel2;
  std::vector<double> *m_muon_eta_sel2;
  std::vector<double> *m_muon_pt_sel2;
  std::vector<double> *m_muon_e_sel2;
  std::vector<double> *m_muon_charge;
  ToolHandle<CP::IMuonSelectionTool> m_selTool;
};

#endif // MYANALYSISALG_H
