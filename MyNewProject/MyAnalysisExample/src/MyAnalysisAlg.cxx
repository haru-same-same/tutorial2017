#include "xAODEventInfo/EventInfo.h"
#include "xAODMuon/MuonContainer.h"
#include "GaudiKernel/ITHistSvc.h"
#include "TH1.h"
#include "TH2.h"
#include "TTree.h"
#include "MyAnalysisExample/MyAnalysisAlg.h"
#include "MuonPrepRawData/TgcPrepDataContainer.h"
#include "MuonIdHelpers/MuonIdHelperTool.h"
#include <cmath>

//Calculating invariant mass
double inv_mass_calc(double pt1,double phi1,double eta1,double e1,double pt2,double phi2,double eta2,double e2){
    double theta1 = 2*atan(exp(-eta1)); //Calculate theta from eta
    double theta2 = 2*atan(exp(-eta2)); //Calculate theta from eta
 
    double p1_x = pt1*cos(phi1);
    double p1_y = pt1*sin(phi1);
    double p1_z = pt1*cos(theta1)/sin(theta1);
 
    double p2_x = pt2*cos(phi2);
    double p2_y = pt2*sin(phi2);
    double p2_z = pt2*cos(theta2)/sin(theta2);
 
    double invmass = sqrt((e1 + e2)*(e1 + e2) - (p1_x + p2_x)*(p1_x + p2_x) - (p1_y + p2_y)*(p1_y + p2_y) - (p1_z + p2_z)*(p1_z + p2_z));
    return invmass;
}


MyAnalysisAlg::MyAnalysisAlg(const std::string& name, ISvcLocator* pSvcLocator)
  : AthAlgorithm(name, pSvcLocator),
  m_selTool("CP::MuonSelectionTool/MyMuonSelectionTool",this)
{
  declareProperty("message", m_message="You cannot always get what you want.");
  declareProperty("MuonSelTool", m_selTool,"The private muon selection tool");
}

StatusCode MyAnalysisAlg::initialize() {
  ATH_MSG_INFO("initialize()");
  ATH_MSG_INFO("My message: " << m_message);
  ATH_CHECK(m_selTool.retrieve());
    
  StatusCode sc = service("THistSvc",m_thistSvc);
  if(sc.isFailure()){
    ATH_MSG_FATAL("Unable to retrieve THistSvc");
    return sc;
  }
  m_h_nMuons = new TH1D("h_nMuons","Number of muons",11,-0.5,10.5);
  m_thistSvc->regHist("/MyNewPackage/Muon/h_nMuons",m_h_nMuons).setChecked();
  m_h_muon_e = new TH1D("h_muon_e","Muon energy [GeV]",100,0.,250.);
  m_thistSvc->regHist("/MyNewPackage/Muon/h_muon_e",m_h_muon_e).setChecked();
  m_h_muon_pt = new TH1D("h_muon_pt","Muon p_{T} [GeV]",100,0.,250.);
  m_thistSvc->regHist("/MyNewPackage/Muon/h_muon_pt",m_h_muon_pt).setChecked();
  m_h_muon_eta = new TH1D("h_muon_eta","Muon #eta",100,-3.0,3.0);
  m_thistSvc->regHist("/MyNewPackage/Muon/h_muon_eta",m_h_muon_eta).setChecked();
  m_h_muon_phi = new TH1D("h_muon_phi","Muon #phi [radian]",100,-M_PI,M_PI);
  m_thistSvc->regHist("/MyNewPackage/Muon/h_muon_phi",m_h_muon_phi).setChecked();
  m_h_muon_inv_mass = new TH1D("h_muon_inv_mass","Muon invaliant mass [GeV]",100,0.,250);
  m_thistSvc->regHist("/MyNewPackage/Muon/h_muon_inv_mass",m_h_muon_inv_mass).setChecked();
  m_h2_muon_eta_phi = new TH2D("h2_muon_eta_phi","Muon #eta vs #phi",100,-3.0,3.0,100,-M_PI,M_PI);
  m_thistSvc->regHist("/MyNewPackage/Muon/h2_muon_eta_phi",m_h2_muon_eta_phi).setChecked();
  m_h2_tgc_x_y = new TH2D("h2_tgc_x_y","TGC hits",500,-15000,15000,500,-15000,15000);
  m_thistSvc->regHist("/MyNewPackage/TGC/h2_tgc_x_y",m_h2_tgc_x_y).setChecked();
    
  m_tree = new TTree("MyTree","Ntuple variables collection");
  m_tree->Branch("runNumber",&m_runNumber,"runNumber/I");
  m_tree->Branch("eventNumber",&m_eventNumber,"eventNumber/I");
  m_tree->Branch("nMuons",&m_nMuons,"nMuons/I");
  m_muon_author = new std::vector<int>;
  m_tree->Branch("muon_author",&m_muon_author);
  m_muon_phi = new std::vector<double>;
  m_tree->Branch("muon_phi",&m_muon_phi);
  m_muon_eta = new std::vector<double>;
  m_tree->Branch("muon_eta",&m_muon_eta);
  m_muon_pt = new std::vector<double>;
  m_tree->Branch("muon_pt",&m_muon_pt);
  m_muon_e = new std::vector<double>;
  m_tree->Branch("muon_e",&m_muon_e);
  m_muon_charge = new std::vector<double>;
  m_tree->Branch("muon_charge",&m_muon_charge);
  m_thistSvc->regTree("/MyNewPackage/MyTree",m_tree).setChecked();
  m_tree->Print();
 
  m_idHelper.setTypeAndName("Muon::MuonIdHelperTool/MuonIdHelperTool");
  m_idHelper.retrieve().setChecked();
 
  return StatusCode::SUCCESS;
}

StatusCode MyAnalysisAlg::finalize() {
  ATH_MSG_INFO("finalize()");
    
  delete m_muon_author; m_muon_author = 0;
  delete m_muon_phi; m_muon_phi = 0;
  delete m_muon_eta; m_muon_eta = 0;
  delete m_muon_pt; m_muon_pt = 0;
  delete m_muon_e; m_muon_e = 0;
  delete m_muon_charge; m_muon_charge = 0;
  return StatusCode::SUCCESS;
}

StatusCode MyAnalysisAlg::execute() {
  ATH_MSG_INFO("execute()");
  
  //init in each event
  m_muon_author->clear();
  m_muon_phi->clear();
  m_muon_eta->clear();
  m_muon_pt->clear();
  m_muon_e->clear();
  m_muon_charge->clear();
    
  //Event information
  const xAOD::EventInfo *eventInfo = 0;
  StatusCode sc = evtStore()->retrieve(eventInfo);
  if(StatusCode::SUCCESS!=sc || !eventInfo){
    ATH_MSG_WARNING("Could not retrieve EventInfo");
    return StatusCode::SUCCESS;
  }
  uint32_t runNumber = eventInfo->runNumber();
  unsigned long long eventNumber = eventInfo->eventNumber();
  ATH_MSG_INFO("Run = " << runNumber << " : Event = " << eventNumber);
  m_runNumber = runNumber;
  m_eventNumber = eventNumber;
  
  double m_muon_pt_1 = 0; 
  double m_muon_pt_2 = 0; 
  double m_muon_e_1 = 0; 
  double m_muon_e_2 = 0; 
  double m_muon_phi_1 = 0;
  double m_muon_phi_2 = 0;
  double m_muon_eta_1 = 0;
  double m_muon_eta_2 = 0;
  double m_muon_inv_mass = 0;
 
  //TGC hits
  const Muon::TgcPrepDataContainer *tgcContainer = 0;
  sc = evtStore()->retrieve(tgcContainer,"TGC_MeasurementsAllBCs");
 
  if(StatusCode::SUCCESS != sc || !tgcContainer){
    ATH_MSG_WARNING("Could not retrieve Muons");
    return StatusCode::SUCCESS;
  }
 
  Muon::TgcPrepDataContainer::const_iterator tpdc_it;
  Muon::TgcPrepDataCollection::const_iterator cit;
 
  for(tpdc_it = tgcContainer->begin(); tpdc_it != tgcContainer->end(); tpdc_it++){
    for(cit = (*tpdc_it)->begin(); cit != (*tpdc_it)->end(); cit++){
        const Muon::TgcPrepData *tgc = *cit;
        
        //only current bunch hits
        if((tgc->getBcBitMap()&Muon::TgcPrepData::BCBIT_CURRENT)!=Muon::TgcPrepData::BCBIT_CURRENT)
            continue;
        
        const TgcIdHelper& tgcIdHelper = m_idHelper->tgcIdHelper();
        const MuonGM::TgcReadoutElement *element = tgc->detectorElement();
        const Identifier id = tgc->identify();
        const int gasGap = tgcIdHelper.gasGap(id);
        const int channel = tgcIdHelper.channel(id);
        const bool isStrip = tgcIdHelper.isStrip(id);
        const Amg::Vector3D& pos = isStrip ? element->stripPos(gasGap,channel) : element->gangPos(gasGap,channel);
        m_h2_tgc_x_y->Fill(pos[0],pos[1]);
    }
  } 
 
  //Muon
  const xAOD::MuonContainer *muonContainer = 0;
  sc = evtStore()->retrieve(muonContainer,"Muons");
  if(StatusCode::SUCCESS!=sc || !muonContainer){
    ATH_MSG_WARNING("Could not retrieve Muons");
    return StatusCode::SUCCESS;
  }
  ATH_MSG_DEBUG("Muons successfully retrieved");
  ATH_MSG_DEBUG("# of muons = " << muonContainer->size());
  unsigned int nMuons = 0;
  xAOD::MuonContainer::const_iterator muonItrE = muonContainer->end();
  for(xAOD::MuonContainer::const_iterator muonItr = muonContainer->begin(); muonItr != muonItrE; ++muonItr){
    const xAOD::Muon *muon = *muonItr;
    if(!m_selTool->accept(*muon)){
        ATH_MSG_INFO("The muon is rejected");
        continue;
    }
    else if(muon->pt() > m_muon_pt_1){    //ここからmuon p_tの順位付け
        m_muon_pt_2 = m_muon_pt_1;
        m_muon_pt_1 = muon->pt();
        m_muon_e_2 = m_muon_e_1;
        m_muon_e_1 = muon->e();
        m_muon_phi_2 = m_muon_phi_1;
        m_muon_phi_1 = muon->phi();
        m_muon_eta_2 = m_muon_eta_1;
        m_muon_eta_1 = muon->eta();
    }
    else if(muon->pt() > m_muon_pt_2){
        m_muon_pt_2 = muon->pt();    
        m_muon_e_2 = muon->e();
        m_muon_phi_2 = muon->phi();
        m_muon_eta_2 = muon->eta();
    }                                     //ここまで
    ATH_MSG_INFO(nMuons << "th muon :" <<
                 " Pt : " << muon->pt() <<
                 " Eta : " << muon->eta() <<
                 " Phi : " << muon->phi() << 
                 " E : " << muon->e() <<
                 " M : " << muon->m());
    m_h_muon_e->Fill(muon->e()/1000.);
    m_h_muon_pt->Fill(muon->pt()/1000.);
    m_h_muon_eta->Fill(muon->eta());
    m_h_muon_phi->Fill(muon->phi());
    m_h2_muon_eta_phi->Fill(muon->eta(),muon->phi());
    
    m_muon_author->push_back(muon->author());
    m_muon_phi->push_back(muon->phi());
    m_muon_eta->push_back(muon->eta());
    m_muon_pt->push_back(muon->pt()/1000.);
    m_muon_e->push_back(muon->e()/1000.);
    if(muon->primaryTrackParticle()){
        m_muon_charge->push_back(muon->primaryTrackParticle()->charge());
    }
    else{
        m_muon_charge->push_back(0.);
    }
  
    ++nMuons;
  }
  m_h_nMuons->Fill(nMuons);
 
  if(m_muon_pt_2 != 0){
    m_muon_inv_mass = inv_mass_calc(m_muon_pt_1,m_muon_phi_1,m_muon_eta_1,m_muon_e_1,m_muon_pt_2,m_muon_phi_2,m_muon_eta_2,m_muon_e_2);
    ATH_MSG_INFO("p_t No.1 is:" << m_muon_pt_1 << " , p_t No.2 is:" << m_muon_pt_2 << " , inv_mass is:" << m_muon_inv_mass);
    m_h_muon_inv_mass->Fill(m_muon_inv_mass/1000.);
  }
    
  m_nMuons = static_cast<int>(nMuons);
  int nbytes = m_tree->Fill();
  ATH_MSG_DEBUG("Number of bytes written = " << nbytes);
  
  return StatusCode::SUCCESS;
}
