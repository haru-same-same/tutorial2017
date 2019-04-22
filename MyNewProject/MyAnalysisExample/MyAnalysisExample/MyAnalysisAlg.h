#ifndef MYANALYSISALG_H // Include guard
#define MYANALYSISALG_H

#include "AthenaBaseComps/AthAlgorithm.h"
#include "MuonSelectorTools/IMuonSelectionTool.h"
#include "GaudiKernel/ToolHandle.h"

namespace Muon{class MuonIdHelperTool;}

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
  TH1D *m_h_muon_inv_mass;
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
  std::vector<double> *m_muon_charge;
  ToolHandle<CP::IMuonSelectionTool> m_selTool;
  ToolHandle<Muon::MuonIdHelperTool> m_idHelper;
  TH2D *m_h2_tgc_x_y;
};

#endif // MYANALYSISALG_H
