#include "GaudiKernel/MsgStream.h"
#include "GaudiKernel/AlgFactory.h"
#include "GaudiKernel/ISvcLocator.h"
#include "GaudiKernel/SmartDataPtr.h"
#include "GaudiKernel/IDataProviderSvc.h"
#include "GaudiKernel/PropertyMgr.h"
#include "VertexFit/IVertexDbSvc.h"
#include "GaudiKernel/Bootstrap.h"
#include "GaudiKernel/ISvcLocator.h"

#include "EventModel/EventModel.h"
#include "EventModel/Event.h"

#include "EvtRecEvent/EvtRecEvent.h"
#include "EvtRecEvent/EvtRecTrack.h"
#include "DstEvent/TofHitStatus.h"
#include "EventModel/EventHeader.h"


#include "McTruth/McParticle.h"
#include "McTruth/MdcMcHit.h"



#include "TMath.h"
#include "GaudiKernel/INTupleSvc.h"
#include "GaudiKernel/Algorithm.h"
#include "GaudiKernel/NTuple.h"
#include "GaudiKernel/Bootstrap.h"
#include "GaudiKernel/IHistogramSvc.h"
#include "CLHEP/Vector/ThreeVector.h"
#include "CLHEP/Vector/LorentzVector.h"
#include "CLHEP/Vector/TwoVector.h"
using CLHEP::Hep3Vector;
using CLHEP::Hep2Vector;
using CLHEP::HepLorentzVector;
#include "CLHEP/Geometry/Point3D.h"
#ifndef ENABLE_BACKWARDS_COMPATIBILITY
   typedef HepGeom::Point3D<double> HepPoint3D;
#endif
#include "Jpsdecthreepi/Jpsdecthreepi.h"

#include "VertexFit/KinematicFit.h"
#include "VertexFit/KalmanKinematicFit.h"
#include "VertexFit/VertexFit.h"
#include "VertexFit/Helix.h"
#include "ParticleID/ParticleID.h"

#include "/besfs/users/vindy/cmt6.6.4/workarea/Reconstruction/GammaConv/GammaConv-00-00-01/GammaConv/GammaConv.h"

#include "VertexFit/BField.h"

#include <vector>
//const double twopi = 6.2831853;
//const double pi = 3.1415927;
const double mmu = 0.105658;
const double me =   0.000511;
const double mpi =  0.139570;
const double xmass[5] = {0.000511, 0.105658, 0.139570,0.493677, 0.938272};
//const double velc = 29.9792458;  tof_path unit in cm.
const double velc = 299.792458;   // tof path unit in mm
typedef std::vector<int> Vint;
typedef std::vector<HepLorentzVector> Vp4;



int Ncut0,Ncut1,Ncut2,Ncut3,Ncut4,Ncut5,Ncut6,Ncut7,Ncut8,Ncut9,Ncut10,Ncut11,Ncut12,Ncut13,Ncut14,Ncut15;

//////////////bestTrackNumber != -1///////////////////////////////////////////////////////////////

Jpsdecthreepi::Jpsdecthreepi(const std::string& name, ISvcLocator* pSvcLocator) :
  Algorithm(name, pSvcLocator) {
 
  //Declare the properties 
 
  declareProperty("TestMC",    m_testMC=false);
  declareProperty("TestJPSMC",    m_testJpsMC=false);
  declareProperty("EnergyThreshold1",   m_energyThreshold1=0.025);
  declareProperty("EnergyThreshold2",   m_energyThreshold2=0.05);
  declareProperty("nGam_cut",           m_nGam_cut=50);
  declareProperty("Timedown",           m_timedown=0);
  declareProperty("Timeup",             m_timeup=14);
  declareProperty("GammaAngleCut",      m_gammaAngleCut=10.0); 
 }

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
StatusCode Jpsdecthreepi::initialize(){
  MsgStream log(msgSvc(), name());

  log << MSG::INFO << "in initialize()" << endmsg;
  
  StatusCode status;
  NTuplePtr nt1(ntupleSvc(), "FILE1/h1");
  if ( nt1 ) m_tuple1 = nt1;
  else {
    m_tuple1 = ntupleSvc()->book ("FILE1/h1", CLID_ColumnWiseTuple, "ks N-Tuple example");
    if ( m_tuple1 )    {

      status = m_tuple1->addItem ("run",  m_run );
      status = m_tuple1->addItem ("rec",  m_rec ); 



      status = m_tuple1->addItem ("ncharge", m_nCharge);
      status = m_tuple1->addItem ("nTracks", m_nTracks);




      // MC Truth information
    if (m_testMC == true)
     {

     status = m_tuple1->addItem("indexmc",              m_idxmc, 0, 100);
     status = m_tuple1->addIndexedItem("trkidx",        m_idxmc, m_trkidx);
     status = m_tuple1->addIndexedItem("pdgid",         m_idxmc, m_pdgid);
     status = m_tuple1->addIndexedItem("motheridx",     m_idxmc, m_motheridx);


     status = m_tuple1->addItem ("m_mcPhotonInvMass",   m_mcPhotonInvMass);
     status = m_tuple1->addItem ("m_mcPhotonTheta",     m_mcPhotonTheta);
     status = m_tuple1->addItem ("m_mcPhotonPhi",       m_mcPhotonPhi);
     status = m_tuple1->addItem ("m_mcPhotonEnergy",    m_mcPhotonEnergy);

     status = m_tuple1->addItem ("m_mcnPhoton",          m_mcnPhoton);


     status = m_tuple1->addItem ("m_mcElectronInvMass",     m_mcElectronInvMass);
     status = m_tuple1->addItem ("m_mcElectronTheta",       m_mcElectronTheta);
     status = m_tuple1->addItem ("m_mcElectronPhi",         m_mcElectronPhi);
     status = m_tuple1->addItem ("m_mcElectronEnergy",      m_mcElectronEnergy);
     status = m_tuple1->addItem ("m_mcElectronX",       m_mcElectronX);
     status = m_tuple1->addItem ("m_mcElectronY",         m_mcElectronY);
     status = m_tuple1->addItem ("m_mcElectronZ",      m_mcElectronZ);
     status = m_tuple1->addItem ("m_mcnElectron",           m_mcnElectron);


     status = m_tuple1->addItem ("m_mcPositronInvMass",     m_mcPositronInvMass);
     status = m_tuple1->addItem ("m_mcPositronTheta",       m_mcPositronTheta);
     status = m_tuple1->addItem ("m_mcPositronPhi",         m_mcPositronPhi);
     status = m_tuple1->addItem ("m_mcPositronEnergy",      m_mcPositronEnergy);
     status = m_tuple1->addItem ("m_mcPositronX",       m_mcPositronX);
     status = m_tuple1->addItem ("m_mcPositronY",         m_mcPositronY);
     status = m_tuple1->addItem ("m_mcPositronZ",      m_mcPositronZ);
     status = m_tuple1->addItem ("m_mcnPositron",           m_mcnPositron);



     status = m_tuple1->addItem ("m_mcPi0InvMass",      m_mcPi0InvMass);
     status = m_tuple1->addItem ("m_mcPi0Theta",        m_mcPi0Theta);
     status = m_tuple1->addItem ("m_mcPi0Phi",          m_mcPi0Phi);
     status = m_tuple1->addItem ("m_mcPi0Energy",       m_mcPi0Energy);
     status = m_tuple1->addItem ("m_mcnPi0",             m_mcnPi0);


     status = m_tuple1->addItem ("m_mcEta0InvMass",      m_mcEta0InvMass);
     status = m_tuple1->addItem ("m_mcEta0Theta",        m_mcEta0Theta);
     status = m_tuple1->addItem ("m_mcEta0Phi",          m_mcEta0Phi);
     status = m_tuple1->addItem ("m_mcEta0Energy",       m_mcEta0Energy);
     status = m_tuple1->addItem ("m_mcnEta0",             m_mcnEta0);


     // Properties of single energetic photon

     status = m_tuple1->addItem ("m_mcPhoton1Energy",       m_mcPhoton1Energy);
     status = m_tuple1->addItem ("m_mcPhoton1Theta",        m_mcPhoton1Theta);
     status = m_tuple1->addItem ("m_mcPhoton1Phi",          m_mcPhoton1Phi);

     status = m_tuple1->addItem ("m_mcPhoton2Energy",       m_mcPhoton2Energy);
     status = m_tuple1->addItem ("m_mcPhoton2Theta",        m_mcPhoton2Theta);
     status = m_tuple1->addItem ("m_mcPhoton2Phi",          m_mcPhoton2Phi);


     status = m_tuple1->addItem ("m_mcPhoton3Energy",       m_mcPhoton3Energy);
     status = m_tuple1->addItem ("m_mcPhoton3Theta",        m_mcPhoton3Theta);
     status = m_tuple1->addItem ("m_mcPhoton3Phi",          m_mcPhoton3Phi);


     status = m_tuple1->addItem ("m_mcPhoton4Energy",       m_mcPhoton4Energy);
     status = m_tuple1->addItem ("m_mcPhoton4Theta",        m_mcPhoton4Theta);
     status = m_tuple1->addItem ("m_mcPhoton4Phi",          m_mcPhoton4Phi);


     status = m_tuple1->addItem ("m_mcHighestenergeticPhotonEnergy",       m_mcHighestenergeticPhotonEnergy);
     status = m_tuple1->addItem ("m_mcHighestenergeticPhotonTheta",        m_mcHighestenergeticPhotonTheta);
     status = m_tuple1->addItem ("m_mcHighestenergeticPhotonPhi",          m_mcHighestenergeticPhotonPhi);


     status = m_tuple1->addItem ("m_mcHighestenergeticPhotonX",       m_mcHighestenergeticPhotonX);
     status = m_tuple1->addItem ("m_mcHighestenergeticPhotonY",        m_mcHighestenergeticPhotonY);
     status = m_tuple1->addItem ("m_mcHighestenergeticPhotonZ",          m_mcHighestenergeticPhotonZ);

     }
      ///////////////////////////////////////////




      status = m_tuple1->addItem ("nNeutral", m_nNeutral); //what happens when nneu>100?
      status = m_tuple1->addItem ("nGam", m_nGam, 0, 500); //what happens when nneu>100?   
      status = m_tuple1->addIndexedItem ("numHits",m_nGam, m_numHits);
      status = m_tuple1->addIndexedItem ("status", m_nGam,m_status  );
      status = m_tuple1->addIndexedItem ("cellId", m_nGam,m_cellId  );
      status = m_tuple1->addIndexedItem ("module", m_nGam,m_module  );
      status = m_tuple1->addIndexedItem ("x", m_nGam,m_x  );
      status = m_tuple1->addIndexedItem ("y", m_nGam,m_y  );
      status = m_tuple1->addIndexedItem ("z", m_nGam,m_z  );
      status = m_tuple1->addIndexedItem ("theta", m_nGam,m_theta  );
      status = m_tuple1->addIndexedItem ("phi", m_nGam,m_phi  );
      status = m_tuple1->addIndexedItem ("dx", m_nGam,m_dx  );
      status = m_tuple1->addIndexedItem ("dy", m_nGam,m_dy  );
      status = m_tuple1->addIndexedItem ("dz", m_nGam,m_dz  ); 
      status = m_tuple1->addIndexedItem ("dtheta", m_nGam, m_dtheta);
      status = m_tuple1->addIndexedItem ("dphi", m_nGam, m_dphi);
      status = m_tuple1->addIndexedItem ("energy", m_nGam, m_energy);
      status = m_tuple1->addIndexedItem ("dE", m_nGam,m_dE  );
      status = m_tuple1->addIndexedItem ("eSeed", m_nGam,m_eSeed  );
      status = m_tuple1->addIndexedItem ("e3x3", m_nGam,m_e3x3  );
      status = m_tuple1->addIndexedItem ("e5x5", m_nGam,m_e5x5  );
      status = m_tuple1->addIndexedItem ("secondMoment",m_nGam, m_secondMoment  );
      status = m_tuple1->addIndexedItem ("latMoment", m_nGam,m_latMoment  );
      status = m_tuple1->addIndexedItem ("A20Moment", m_nGam,m_a20Moment  );
      status = m_tuple1->addIndexedItem ("A42Moment", m_nGam,m_a42Moment  );
      status = m_tuple1->addIndexedItem ("time", m_nGam, m_time);

  

     
      status = m_tuple1->addIndexedItem ("emcpos_theta",m_nGam,m_emcpos_theta );
      status = m_tuple1->addIndexedItem ("emcpos_phi",m_nGam,m_emcpos_phi );
      
      status = m_tuple1->addIndexedItem ("dthe_ch", m_nGam,m_dthe_ch  );
      status = m_tuple1->addIndexedItem ("dphi_ch", m_nGam,m_dphi_ch  );
      status = m_tuple1->addIndexedItem ("dang_ch", m_nGam,m_dang_ch  );
      
      status = m_tuple1->addIndexedItem ("extpos_x", m_nGam,m_extpos_x  );
      status = m_tuple1->addIndexedItem ("extpos_y", m_nGam,m_extpos_y  );
      status = m_tuple1->addIndexedItem ("extpos_z", m_nGam,m_extpos_z  );
 
 
 
      status = m_tuple1->addItem("vx0",     m_vx0);
      status = m_tuple1->addItem("vy0",     m_vy0);
      status = m_tuple1->addItem("vz0",     m_vz0);
      status = m_tuple1->addItem("vr0",     m_vr0);
      status = m_tuple1->addItem("rvxy0",   m_rvxy0);
      status = m_tuple1->addItem("rvz0",    m_rvz0);
      status = m_tuple1->addItem("rvphi0",  m_rvphi0);
    


      ////////////////////////////////////////////////////////

     status = m_tuple1->addItem ("nGood",             m_nGood, 0, 4);  

 
 
     
      status = m_tuple1->addIndexedItem ("ptrk_pid",     m_nGood,  m_ptrk_pid);
      status = m_tuple1->addIndexedItem ("cost",         m_nGood,  m_cost_pid);
      status = m_tuple1->addIndexedItem ("dedx",         m_nGood,  m_dedx_pid);
      status = m_tuple1->addIndexedItem ("tof1",         m_nGood,  m_tof1_pid);
      status = m_tuple1->addIndexedItem ("tof2",         m_nGood,  m_tof2_pid);
      status = m_tuple1->addIndexedItem ("electron_PID", m_nGood,  m_electron_pid);
      status = m_tuple1->addIndexedItem ("m_pion_pid",   m_nGood,  m_pion_pid);
      status = m_tuple1->addIndexedItem ("m_kaon_pid",   m_nGood,  m_kaon_pid);  



      status = m_tuple1->addItem ("ep_electronPID",     ep_electronPID);
      status = m_tuple1->addItem ("em_electronPID",     em_electronPID);
      status = m_tuple1->addItem ("ep_kaonPID",         ep_kaonPID);
      status = m_tuple1->addItem ("em_kaonPID",         em_kaonPID);
      status = m_tuple1->addItem ("ep_pionPID",         ep_pionPID);
      status = m_tuple1->addItem ("em_pionPID",         em_pionPID);

      status = m_tuple1->addItem ("pip_electronPID",    pip_electronPID);
      status = m_tuple1->addItem ("pim_electronPID",    pim_electronPID);
      status = m_tuple1->addItem ("pip_kaonPID",        pip_kaonPID);
      status = m_tuple1->addItem ("pim_kaonPID",        pim_kaonPID);
      status = m_tuple1->addItem ("pip_pionPID",        pip_pionPID);
      status = m_tuple1->addItem ("pim_pionPID",        pim_pionPID);


      status = m_tuple1->addItem ("nep",                m_nep);
      status = m_tuple1->addItem ("nem",                m_nem);


      status = m_tuple1->addItem ("npip",                m_npip);
      status = m_tuple1->addItem ("npim",                m_npim);

      status = m_tuple1->addItem ("pip_exttheta",     pip_exttheta);
      status = m_tuple1->addItem ("pip_extphi",       pip_extphi);
      status = m_tuple1->addItem ("pip_ext_x",        pip_ext_x);
      status = m_tuple1->addItem ("pip_ext_y",        pip_ext_y);
      status = m_tuple1->addItem ("pip_ext_z",        pip_ext_z);

      status = m_tuple1->addItem ("pim_exttheta",     pim_exttheta);
      status = m_tuple1->addItem ("pim_extphi",       pim_extphi);
      status = m_tuple1->addItem ("pim_ext_x",        pim_ext_x);
      status = m_tuple1->addItem ("pim_ext_y",        pim_ext_y);
      status = m_tuple1->addItem ("pim_ext_z",        pim_ext_z);

      status = m_tuple1->addItem ("pip_EOP",          pip_EOP);
      status = m_tuple1->addItem ("pim_EOP",          pim_EOP);
      status = m_tuple1->addItem ("pip_ECAL",         pip_ECAL);
      status = m_tuple1->addItem ("pim_ECAL",         pim_ECAL);

      status = m_tuple1->addItem ("pip_A42",                pip_A42);
      status = m_tuple1->addItem ("pip_lat",                pip_lat);
      status = m_tuple1->addItem ("pip_e3x3",               pip_e3x3);
      status = m_tuple1->addItem ("pip_e5x5",               pip_e5x5);
      status = m_tuple1->addItem ("pip_A20",                pip_A20);
      status = m_tuple1->addItem ("pip_numhits",            pip_numhits);

      status = m_tuple1->addItem ("pip_secondMoment",       pip_secondMoment);
      status = m_tuple1->addItem ("pip_eSeed",              pip_eSeed);
      status = m_tuple1->addItem ("pip_e5divSeed_fromEM",   pip_e5divSeed_fromEMC);
      status = m_tuple1->addItem ("pip_e3divSeed_fromEMC",  pip_e3divSeed_fromEMC);
      status = m_tuple1->addItem ("pip_e5div3_fromEMC",     pip_e5div3_fromEMC);
      status = m_tuple1->addItem ("pip_theta_fromEMC",      pip_theta_fromEMC);
      status = m_tuple1->addItem ("pip_phi_fromEMC",        pip_phi_fromEMC);
      status = m_tuple1->addItem ("pip_x_fromEMC",          pip_x_fromEMC);
      status = m_tuple1->addItem ("pip_y_fromEMC",          pip_y_fromEMC);
      status = m_tuple1->addItem ("pip_z_fromEMC",          pip_z_fromEMC);

      status = m_tuple1->addItem ("pim_A42",                pim_A42);
      status = m_tuple1->addItem ("pim_lat",                pim_lat);
      status = m_tuple1->addItem ("pim_e3x3",               pim_e3x3);
      status = m_tuple1->addItem ("pim_e5x5",               pim_e5x5);
      status = m_tuple1->addItem ("pim_A20",                pim_A20);
      status = m_tuple1->addItem ("pim_numhits",            pim_numhits);
      status = m_tuple1->addItem ("pim_secondMoment",       pim_secondMoment);
      status = m_tuple1->addItem ("pim_eSeed",              pim_eSeed);
      status = m_tuple1->addItem ("pim_e5divSeed_fromEM",   pim_e5divSeed_fromEMC);
      status = m_tuple1->addItem ("pim_e3divSeed_fromEMC",  pim_e3divSeed_fromEMC);
      status = m_tuple1->addItem ("pim_e5div3_fromEMC",     pim_e5div3_fromEMC);
      status = m_tuple1->addItem ("pim_theta_fromEMC",      pim_theta_fromEMC);
      status = m_tuple1->addItem ("pim_phi_fromEMC",        pim_phi_fromEMC);
      status = m_tuple1->addItem ("pim_x_fromEMC",          pim_x_fromEMC);
      status = m_tuple1->addItem ("pim_y_fromEMC",          pim_y_fromEMC);
      status = m_tuple1->addItem ("pim_z_fromEMC",          pim_z_fromEMC);

      status = m_tuple1->addItem ("pip_exttheta",           pip_exttheta);
      status = m_tuple1->addItem ("pip_extphi",             pip_extphi);
      status = m_tuple1->addItem ("pim_exttheta",           pim_exttheta);
      status = m_tuple1->addItem ("pim_extphi",             pim_extphi);

      status = m_tuple1->addItem ("pip_numGoodHits",        pip_numGoodHits);
      status = m_tuple1->addItem ("pip_numTotalHits",       pip_numTotalHits);
      status = m_tuple1->addItem ("pip_dedxchi",            pip_dedxchi);

      status = m_tuple1->addItem ("pim_numGoodHits",        pim_numGoodHits);
      status = m_tuple1->addItem ("pim_numTotalHits",       pim_numTotalHits);
      status = m_tuple1->addItem ("pim_dedxchi",            pim_dedxchi);

      status = m_tuple1->addItem ("dipi_vtxfit_chi2",      dipi_vtxfit_chi2);

      status = m_tuple1->addItem ("Dipimass",         Dipimass);
      status = m_tuple1->addItem ("Dipipx",           Dipipx);
      status = m_tuple1->addItem ("Dipipy",           Dipipy);
      status = m_tuple1->addItem ("Dipipz",           Dipipz);
      status = m_tuple1->addItem ("Dipie",            Dipie);
      status = m_tuple1->addItem ("Dipitheta",        Dipitheta);
      status = m_tuple1->addItem ("Dipiphi",          Dipiphi);
      status = m_tuple1->addItem ("Dipimom",          Dipimom);

      status = m_tuple1->addItem ("pipmass",          pipmass);
      status = m_tuple1->addItem ("pippx",            pippx);
      status = m_tuple1->addItem ("pippy",            pippy);
      status = m_tuple1->addItem ("pippz",            pippz);
      status = m_tuple1->addItem ("pipe",             pipe);
      status = m_tuple1->addItem ("piptheta",         piptheta);
      status = m_tuple1->addItem ("pipphi",           pipphi);
      status = m_tuple1->addItem ("pipmom",           pipmom);



      status = m_tuple1->addItem ("pimmass",          pimmass);
      status = m_tuple1->addItem ("pimpx",            pimpx);
      status = m_tuple1->addItem ("pimpy",            pimpy);
      status = m_tuple1->addItem ("pimpz",            pimpz);
      status = m_tuple1->addItem ("pime",             pime);
      status = m_tuple1->addItem ("pimtheta",         pimtheta);
      status = m_tuple1->addItem ("pimphi",           pimphi);
      status = m_tuple1->addItem ("pimmom",           pimmom);

      status = m_tuple1->addItem ("fourCchi2",           fourCchi2);


      status = m_tuple1->addItem ("Dipi_fit_mass",     Dipi_fit_mass);
      status = m_tuple1->addItem ("Dipi_fit_e",        Dipi_fit_e);
      status = m_tuple1->addItem ("Dipi_fit_px",       Dipi_fit_px);
      status = m_tuple1->addItem ("Dipi_fit_py",       Dipi_fit_py);
      status = m_tuple1->addItem ("Dipi_fit_pz",       Dipi_fit_pz);
      status = m_tuple1->addItem ("Dipi_fit_Theta",    Dipi_fit_theta);
      status = m_tuple1->addItem ("Dipi_fit_Phi",      Dipi_fit_phi);
      status = m_tuple1->addItem ("Dipi_fit_p3",       Dipi_fit_mom);

      status = m_tuple1->addItem ("pip_fit_mass",       pip_fit_mass);
      status = m_tuple1->addItem ("pip_fit_e",          pip_fit_e);
      status = m_tuple1->addItem ("pip_fit_px",         pip_fit_px);
      status = m_tuple1->addItem ("pip_fit_py",         pip_fit_py);
      status = m_tuple1->addItem ("pip_fit_pz",         pip_fit_pz);
      status = m_tuple1->addItem ("pip_fit_Theta",      pip_fit_theta);
      status = m_tuple1->addItem ("pip_fit_Phi",        pip_fit_phi);
      status = m_tuple1->addItem ("pip_fit_p3",         pip_fit_mom);

      status = m_tuple1->addItem ("pim_fit_mass",       pim_fit_mass);
      status = m_tuple1->addItem ("pim_fit_e",          pim_fit_e);
      status = m_tuple1->addItem ("pim_fit_px",         pim_fit_px);
      status = m_tuple1->addItem ("pim_fit_py",         pim_fit_py);
      status = m_tuple1->addItem ("pim_fit_pz",         pim_fit_pz);
      status = m_tuple1->addItem ("pim_fit_Theta",      pim_fit_theta);
      status = m_tuple1->addItem ("pim_fit_Phi",        pim_fit_phi);
      status = m_tuple1->addItem ("pim_fit_p3",         pim_fit_mom);

      status = m_tuple1->addItem ("ep_exttheta",     ep_exttheta);
      status = m_tuple1->addItem ("ep_extphi",       ep_extphi);
      status = m_tuple1->addItem ("ep_ext_x",        ep_ext_x);
      status = m_tuple1->addItem ("ep_ext_y",        ep_ext_y);
      status = m_tuple1->addItem ("ep_ext_z",        ep_ext_z);
   
      status = m_tuple1->addItem ("em_exttheta",      em_exttheta);
      status = m_tuple1->addItem ("em_extphi",        em_extphi);
      status = m_tuple1->addItem ("em_ext_x",         em_ext_x);
      status = m_tuple1->addItem ("em_ext_y",         em_ext_y);
      status = m_tuple1->addItem ("em_ext_z",         em_ext_z);
  


      status = m_tuple1->addItem("pip_pull", 5,  m_pip_pull);
      status = m_tuple1->addItem("pim_pull", 5,  m_pim_pull);
      status = m_tuple1->addItem("ep_pull",  5,  m_ep_pull);
      status = m_tuple1->addItem("em_pull",  5,  m_em_pull);



    status = m_tuple1->addItem ("ep_EOP",          ep_EOP);
    status = m_tuple1->addItem ("em_EOP",          em_EOP);
    status = m_tuple1->addItem ("ep_ECAL",               ep_ECAL);
    status = m_tuple1->addItem ("em_ECAL",               em_ECAL);

    status = m_tuple1->addItem ("ep_A42",                ep_A42);
    status = m_tuple1->addItem ("ep_lat",                ep_lat);
    status = m_tuple1->addItem ("ep_e3x3",               ep_e3x3);
    status = m_tuple1->addItem ("ep_e5x5",               ep_e5x5);
    status = m_tuple1->addItem ("ep_A20",                ep_A20);
    status = m_tuple1->addItem ("ep_numhits",            ep_numhits);

    status = m_tuple1->addItem ("ep_secondMoment",       ep_secondMoment);
    status = m_tuple1->addItem ("ep_eSeed",              ep_eSeed);
    status = m_tuple1->addItem ("ep_e5divSeed_fromEM",   ep_e5divSeed_fromEMC);
    status = m_tuple1->addItem ("ep_e3divSeed_fromEMC",  ep_e3divSeed_fromEMC);
    status = m_tuple1->addItem ("ep_e5div3_fromEMC",     ep_e5div3_fromEMC);
    status = m_tuple1->addItem ("ep_theta_fromEMC",      ep_theta_fromEMC);
    status = m_tuple1->addItem ("ep_phi_fromEMC",        ep_phi_fromEMC); 
    status = m_tuple1->addItem ("ep_x_fromEMC",          ep_x_fromEMC); 
    status = m_tuple1->addItem ("ep_y_fromEMC",          ep_y_fromEMC); 
    status = m_tuple1->addItem ("ep_z_fromEMC",          ep_z_fromEMC); 

 
    status = m_tuple1->addItem ("npart",                 m_digi_npart);
    status = m_tuple1->addItem ("ntheta",                m_digi_ntheta);
    status = m_tuple1->addItem ("nphi",                  m_digi_nphi);


    status = m_tuple1->addItem ("em_A42",                em_A42);
    status = m_tuple1->addItem ("em_lat",                em_lat);
    status = m_tuple1->addItem ("em_e3x3",               em_e3x3);
    status = m_tuple1->addItem ("em_e5x5",               em_e5x5);
    status = m_tuple1->addItem ("em_A20",                em_A20);
    status = m_tuple1->addItem ("em_numhits",            em_numhits);
    status = m_tuple1->addItem ("em_secondMoment",       em_secondMoment);
    status = m_tuple1->addItem ("em_eSeed",              em_eSeed);
    status = m_tuple1->addItem ("em_e5divSeed_fromEM",   em_e5divSeed_fromEMC);
    status = m_tuple1->addItem ("em_e3divSeed_fromEMC",  em_e3divSeed_fromEMC);
    status = m_tuple1->addItem ("em_e5div3_fromEMC",     em_e5div3_fromEMC); 
    status = m_tuple1->addItem ("em_theta_fromEMC",      em_theta_fromEMC);
    status = m_tuple1->addItem ("em_phi_fromEMC",        em_phi_fromEMC);
    status = m_tuple1->addItem ("em_x_fromEMC",          em_x_fromEMC); 
    status = m_tuple1->addItem ("em_y_fromEMC",          em_y_fromEMC); 
    status = m_tuple1->addItem ("em_z_fromEMC",          em_z_fromEMC);  

    status = m_tuple1->addItem ("ep_exttheta",           ep_exttheta);
    status = m_tuple1->addItem ("ep_extphi",             ep_extphi);
    status = m_tuple1->addItem ("em_exttheta",           em_exttheta);
    status = m_tuple1->addItem ("em_extphi",             em_extphi);


    status = m_tuple1->addItem ("ep_numGoodHits",        ep_numGoodHits);
    status = m_tuple1->addItem ("ep_numTotalHits",       ep_numTotalHits);
    status = m_tuple1->addItem ("ep_dedxchi",            ep_dedxchi);

    status = m_tuple1->addItem ("em_numGoodHits",        em_numGoodHits);
    status = m_tuple1->addItem ("em_numTotalHits",       em_numTotalHits); 
    status = m_tuple1->addItem ("em_dedxchi",            em_dedxchi);




     status = m_tuple1->addItem ("elect_vtxfit_chi2",   elect_vtxfit_chi2);


      status = m_tuple1->addItem ("Dielecmass",     Dielecmass);
      status = m_tuple1->addItem ("DielecPx",       Dielecpx);
      status = m_tuple1->addItem ("DielecPy",       Dielecpy);
      status = m_tuple1->addItem ("DielecPz",       Dielecpz);
      status = m_tuple1->addItem ("DielecE",        Dielece);
      status = m_tuple1->addItem ("DielecTheta",    Dielectheta);
      status = m_tuple1->addItem ("DielecPhi",      Dielecphi);


      status = m_tuple1->addItem ("Epmass",        _epmass);
      status = m_tuple1->addItem ("EpPx",          _eppx);
      status = m_tuple1->addItem ("EpPy",          _eppy);
      status = m_tuple1->addItem ("EpPz",          _eppz);
      status = m_tuple1->addItem ("EpE",           _epe);
      status = m_tuple1->addItem ("EpTheta",       _eptheta);
      status = m_tuple1->addItem ("EpPhi",         _epphi);


      status = m_tuple1->addItem ("Emmass",       _emmass);
      status = m_tuple1->addItem ("EmPx",         _empx);
      status = m_tuple1->addItem ("EmPy",         _empy);
      status = m_tuple1->addItem ("EmPz",         _empz);
      status = m_tuple1->addItem ("EmE",          _eme);
      status = m_tuple1->addItem ("EmTheta",      _emtheta);
      status = m_tuple1->addItem ("EmPhi",        _emphi);


      status = m_tuple1->addItem ("fourCchi2",           fourCchi2);

    
      status = m_tuple1->addItem ("Dielec_fit_mass",     Dielec_fit_mass);
      status = m_tuple1->addItem ("Dielec_fit_px",       Dielec_fit_px);
      status = m_tuple1->addItem ("Dielec_fit_py",       Dielec_fit_py);
      status = m_tuple1->addItem ("Dielec_fit_pz",       Dielec_fit_pz);

      status = m_tuple1->addItem ("Dielec_fit_e",        Dielec_fit_e);
      status = m_tuple1->addItem ("Dielec_fit_Theta",    Dielec_fit_theta);
      status = m_tuple1->addItem ("Dielec_fit_Phi",      Dielec_fit_phi);
      status = m_tuple1->addItem ("Dielec_fit_p3",       Dielec_fit_mom);


      status = m_tuple1->addItem ("Ep_fit_mass",       epmass);
      status = m_tuple1->addItem ("Ep_fit_Px",         eppx);
      status = m_tuple1->addItem ("Ep_fit_Py",         eppy);
      status = m_tuple1->addItem ("Ep_fit_Pz",         eppz);
      status = m_tuple1->addItem ("Ep_fit_E",          epe);
      status = m_tuple1->addItem ("Ep_fit_Theta",      eptheta);
      status = m_tuple1->addItem ("Ep_fit_Phi",        epphi);
      status = m_tuple1->addItem ("Ep_fit_P",          epmom);


      status = m_tuple1->addItem ("Em_fit_mass",       emmass);
      status = m_tuple1->addItem ("Em_fit_Px",         empx);
      status = m_tuple1->addItem ("Em_fit_Py",         empy);
      status = m_tuple1->addItem ("Em_fit_Pz",         empz);
      status = m_tuple1->addItem ("Em_fit_E",          eme);
      status = m_tuple1->addItem ("Em_fit_Theta",      emtheta);
      status = m_tuple1->addItem ("Em_fit_Phi",        emphi);
      status = m_tuple1->addItem ("Em_fit_P",          emmom);
  


      status = m_tuple1->addItem ("pi0_fit_mass",       pi0_fit_mass);
      status = m_tuple1->addItem ("pi0_fit_e",          pi0_fit_e);
      status = m_tuple1->addItem ("pi0_fit_px",         pi0_fit_px);
      status = m_tuple1->addItem ("pi0_fit_py",         pi0_fit_py);
      status = m_tuple1->addItem ("pi0_fit_pz",         pi0_fit_pz);
      status = m_tuple1->addItem ("pi0_fit_Theta",      pi0_fit_theta);
      status = m_tuple1->addItem ("pi0_fit_Phi",        pi0_fit_phi);
      status = m_tuple1->addItem ("pi0_fit_p3",         pi0_fit_mom);


      status = m_tuple1->addItem ("Rx_Gam_gamcon",       Rx_Gam_gamcon);
      status = m_tuple1->addItem ("Ry_Gam_gamcon",       Ry_Gam_gamcon);
      status = m_tuple1->addItem ("Rvxy_Gam_gamcon",     Rvxy_Gam_gamcon);

      status = m_tuple1->addItem ("mee_gamcon",         mee_gamcon);
      status = m_tuple1->addItem ("xconv_gamcon",       xconv_gamcon);
      status = m_tuple1->addItem ("yconv_gamcon",       yconv_gamcon);
      status = m_tuple1->addItem ("rconv_gamcon",       rconv_gamcon); 

      status = m_tuple1->addItem ("xconv1_gamcon",       xconv1_gamcon);
      status = m_tuple1->addItem ("yconv1_gamcon",       yconv1_gamcon);
      status = m_tuple1->addItem ("rconv1_gamcon",       rconv1_gamcon); 

      status = m_tuple1->addItem ("xconv2_gamcon",       xconv2_gamcon);
      status = m_tuple1->addItem ("yconv2_gamcon",       yconv2_gamcon);
      status = m_tuple1->addItem ("rconv2_gamcon",       rconv2_gamcon); 



      status = m_tuple1->addItem ("zconv_gamcon",       zconv_gamcon); 
      status = m_tuple1->addItem ("Dee_Mdc_gamcon",     Dee_Mdc_gamcon); 
      status = m_tuple1->addItem ("Dee_Bp_gamcon",      Dee_Bp_gamcon);  

      status = m_tuple1->addItem ("xiep_gamcon",        xiep_gamcon); 
      status = m_tuple1->addItem ("deltaxy_gamcon",     deltaxy_gamcon); 

      status = m_tuple1->addItem ("mconv_gamcon",       mconv_gamcon); 
      status = m_tuple1->addItem ("econv_gamcon",       econv_gamcon); 
      status = m_tuple1->addItem ("thetaconv_gamcon",   thetaconv_gamcon); 
      status = m_tuple1->addItem ("costhetaconv_gamcon",costhetaconv_gamcon); 
      status = m_tuple1->addItem ("phiconv_gamcon",     phiconv_gamcon); 
      status = m_tuple1->addItem ("angEE_gamcon",       angEE_gamcon);
 
      status = m_tuple1->addItem ("em_time_tof",        em_time_tof);
      status = m_tuple1->addItem ("em_sigma_tof",       em_sigma_tof);
      status = m_tuple1->addItem ("em_expEtof",         em_expEtof);


      status = m_tuple1->addItem ("ep_time_tof",        ep_time_tof);
      status = m_tuple1->addItem ("ep_sigma_tof",       ep_sigma_tof);
      status = m_tuple1->addItem ("ep_expEtof",         ep_expEtof);

      status = m_tuple1->addItem ("Goodphotlab",        Goodphotlab);


      status = m_tuple1->addItem ("misTrkGam_fit_mass",  misTrkGammass);
      status = m_tuple1->addItem ("misTrkGam_fit_Px",    misTrkGampx);
      status = m_tuple1->addItem ("misTrkGam_fit_Py",    misTrkGampy);
      status = m_tuple1->addItem ("misTrkGam_fit_Pz",    misTrkGampz);
      status = m_tuple1->addItem ("misTrkGam_fit_E",     misTrkGame);
      status = m_tuple1->addItem ("misTrkGam_fit_Theta", misTrkGamtheta);
      status = m_tuple1->addItem ("misTrkGam_fit_Phi",   misTrkGamphi);
      status = m_tuple1->addItem ("misTrkGam_fit_mom",   misTrkGammom);


      status = m_tuple1->addItem ("misGamTrkanglephoton",  misGamTrkanglephoton);

 
      status = m_tuple1->addItem ("game",            game);
      status = m_tuple1->addItem ("gamP",            gammom);
      status = m_tuple1->addItem ("gamtheta",        gamtheta);
      status = m_tuple1->addItem ("gamphi",          gamphi);

      status = m_tuple1->addItem("A42Mom",          _A42);
      status = m_tuple1->addItem("latMom",          _lat);
      status = m_tuple1->addItem("e3x3Neutral",     _e3x3);
      status = m_tuple1->addItem("e5x5Neutral",     _e5x5);
      status = m_tuple1->addItem("A20Mom",          _A20);
      status = m_tuple1->addItem("gamx",            gamx);
      status = m_tuple1->addItem("gamy",            gamy);
      status = m_tuple1->addItem("gamz",            gamz);
      status = m_tuple1->addItem("gamdx",           gamdx);
      status = m_tuple1->addItem("gamdy",           gamdy);
      status = m_tuple1->addItem("gamdz",           gamdz);
      status = m_tuple1->addItem("gamdtheta",       gamdtheta);
      status = m_tuple1->addItem("gamdphi",         gamdphi);  
      status = m_tuple1->addItem("gamdE",           gamdE);
      status = m_tuple1->addItem("gamseed",         gameseed);
      status = m_tuple1->addItem("gamsecondMoment", gamesecondMoment);
      status = m_tuple1->addItem("gamtime",         gametime);
      status = m_tuple1->addItem("gammodule",       gamemodule);
      status = m_tuple1->addItem("gamcellId",       gamecellId);
      status = m_tuple1->addItem("gamstatus",       gamestatus);
      status = m_tuple1->addItem("gamnumHits",      gamenumHits);



   }
    else    { 
      log << MSG::ERROR << "    Cannot book N-tuple:" << long(m_tuple1) << endmsg;
      return StatusCode::FAILURE;
    }

  }






  log << MSG::INFO << "successfully return from initialize()" <<endmsg;
  return StatusCode::SUCCESS;

}

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
StatusCode Jpsdecthreepi::execute() {
  
  //  std::cout << "execute()" << std::endl;

  MsgStream log(msgSvc(), name());
  log << MSG::INFO << "in execute()" << endreq;


   SmartDataPtr<Event::EventHeader> eventHeader(eventSvc(),"/Event/EventHeader");
  int runNo=eventHeader->runNumber();
  int event=eventHeader->eventNumber();

  m_run = runNo;
  m_rec = event;

  log << MSG::DEBUG <<"run, evtnum = "
      << runNo << " , "
      << event <<endreq;

  // event counter

  if(event%1000 == 0)
    {
  cout<<"event  number:  " << event << endl;
    }

 Ncut0++;

 // std::cout << __LINE__ << std::endl;

  SmartDataPtr<EvtRecEvent> evtRecEvent(eventSvc(), EventModel::EvtRec::EvtRecEvent);
  //  log << MSG::INFO << "get event tag OK" << endreq;
    log << MSG::DEBUG <<"ncharg, nneu, tottks = " 
      << evtRecEvent->totalCharged() << " , "
      << evtRecEvent->totalNeutral() << " , "
      << evtRecEvent->totalTracks() <<endreq;


   m_nCharge   =  evtRecEvent->totalCharged();
   m_nNeutral  =  evtRecEvent->totalNeutral();
   m_nTracks   =  evtRecEvent->totalTracks();




  // MC truth information 

   if (m_testMC == true)
     {
  if (eventHeader->runNumber()<0)
  {
   vector<HepLorentzVector> mc_nElectrons;
   vector<HepLorentzVector> mc_nPositrons;
   vector<HepLorentzVector> mc_nPhotons;
   vector<HepLorentzVector> mc_nPi0s;
  vector<HepLorentzVector> mc_nEta0s;



    SmartDataPtr<Event::McParticleCol> mcParticleCol(eventSvc(), "/Event/MC/McParticleCol");

    int  m_numParticle = 0;
    if (!mcParticleCol)
    {
      std::cout << "Could not retrieve McParticelCol" << std::endl;
      return StatusCode::FAILURE;
    }
    else
    {
     bool jpsiDecay = false;
     long  rootIndex = -1;

      Event::McParticleCol::iterator iter_mc = mcParticleCol->begin();
 
     for (; iter_mc != mcParticleCol->end(); iter_mc++)
      {
	//  if ((*iter_mc)->primaryParticle()) continue;
	// if (!(*iter_mc)->decayFromGenerator()) continue;
    
     int pdgid = (*iter_mc)->particleProperty(); 
     //       cout << pdgid  << endl;
    
     m_pdgid[m_numParticle] = pdgid;
  
 



 // photons

	  if(pdgid == 22) {
	    m_mcPhotonInvMass = (*iter_mc)->initialFourMomentum().m();
	    m_mcPhotonTheta   = (*iter_mc)->initialFourMomentum().theta();
	    m_mcPhotonPhi     = (*iter_mc)->initialFourMomentum().phi();
	    m_mcPhotonEnergy  = (*iter_mc)->initialFourMomentum().e();
	    HepLorentzVector initial_p = (*iter_mc)->initialFourMomentum();
	    mc_nPhotons.push_back(initial_p);
	  }

 // Electron

	  if(pdgid == 11) {
	    m_mcElectronInvMass  = (*iter_mc)->initialFourMomentum().m();
	    m_mcElectronTheta    = (*iter_mc)->initialFourMomentum().theta();
	    m_mcElectronPhi      = (*iter_mc)->initialFourMomentum().phi();
	    m_mcElectronEnergy   = (*iter_mc)->initialFourMomentum().e();

	    m_mcElectronX        = (*iter_mc)->initialFourMomentum().x();
	    m_mcElectronY        = (*iter_mc)->initialFourMomentum().y();
	    m_mcElectronZ        = (*iter_mc)->initialFourMomentum().z();

	    HepLorentzVector initial_p = (*iter_mc)->initialFourMomentum();
	    mc_nElectrons.push_back(initial_p);
	    }


 // Electron

	  if(pdgid == -11) {
	    m_mcPositronInvMass  = (*iter_mc)->initialFourMomentum().m();
	    m_mcPositronTheta    = (*iter_mc)->initialFourMomentum().theta();
	    m_mcPositronPhi      = (*iter_mc)->initialFourMomentum().phi();
	    m_mcPositronEnergy   = (*iter_mc)->initialFourMomentum().e();

	    m_mcPositronX        = (*iter_mc)->initialFourMomentum().x();
	    m_mcPositronY        = (*iter_mc)->initialFourMomentum().y();
	    m_mcPositronZ        = (*iter_mc)->initialFourMomentum().z();

	    HepLorentzVector initial_p = (*iter_mc)->initialFourMomentum();
	    mc_nPositrons.push_back(initial_p);
	    }




 //Pi0

	  if(pdgid == 111) {
	    m_mcPi0InvMass    = (*iter_mc)->initialFourMomentum().m();
	    m_mcPi0Theta      = (*iter_mc)->initialFourMomentum().theta();
	    m_mcPi0Phi        = (*iter_mc)->initialFourMomentum().phi();
	    m_mcPi0Energy     = (*iter_mc)->initialFourMomentum().e();
	    HepLorentzVector initial_p = (*iter_mc)->initialFourMomentum();
	    mc_nPi0s.push_back(initial_p);
	  }



 //Eta0

	  if(pdgid == 221) {
	    m_mcEta0InvMass    = (*iter_mc)->initialFourMomentum().m();
	    m_mcEta0Theta      = (*iter_mc)->initialFourMomentum().theta();
	    m_mcEta0Phi        = (*iter_mc)->initialFourMomentum().phi();
	    m_mcEta0Energy     = (*iter_mc)->initialFourMomentum().e();
	    HepLorentzVector initial_p = (*iter_mc)->initialFourMomentum();
	    mc_nEta0s.push_back(initial_p);
	  }



     if (m_testJpsMC == true)
     {
     if ((*iter_mc)->primaryParticle()) continue;
     if (!(*iter_mc)->decayFromGenerator()) continue;
    

    if ((*iter_mc)->particleProperty()==443) 
       {
       jpsiDecay = true;
       rootIndex = (*iter_mc)->trackIndex();
        }
     if (!jpsiDecay) continue;
      int  trkidx = (*iter_mc)->trackIndex() - rootIndex;
      int  mcidx = ((*iter_mc)->mother()).trackIndex() - rootIndex;

       m_trkidx[m_numParticle] = trkidx;
       m_motheridx[m_numParticle] = mcidx;
     }    else {
      int  trkidx = (*iter_mc)->trackIndex();
      int  mcidx = ((*iter_mc)->mother()).trackIndex();

       m_trkidx[m_numParticle] = trkidx;
       m_motheridx[m_numParticle] = mcidx;
    }

   m_numParticle += 1;


      }
    }
    m_idxmc = m_numParticle;


          m_mcnPhoton = mc_nPhotons.size();
          m_mcnElectron   = mc_nElectrons.size();
          m_mcnPositron   = mc_nPositrons.size();
          m_mcnPi0    = mc_nPi0s.size(); 
          m_mcnEta0    = mc_nEta0s.size(); 
 
	  // Properties of single photons

	  if(mc_nPhotons.size() > 0)
	    {
	    m_mcPhoton1Energy                = mc_nPhotons[0].e();
	    m_mcPhoton1Theta                 = mc_nPhotons[0].theta();
	    m_mcPhoton1Phi                   = mc_nPhotons[0].phi();
	    m_mcHighestenergeticPhotonEnergy = mc_nPhotons[0].e(); 
	    m_mcHighestenergeticPhotonTheta  = mc_nPhotons[0].theta();
	    m_mcHighestenergeticPhotonPhi    = mc_nPhotons[0].phi();
	    m_mcHighestenergeticPhotonX      = mc_nPhotons[0].x();
	    m_mcHighestenergeticPhotonY      = mc_nPhotons[0].y();
	    m_mcHighestenergeticPhotonZ      = mc_nPhotons[0].z();
	    }

	  if(mc_nPhotons.size() > 1)
	    {
	    m_mcPhoton2Energy                = mc_nPhotons[1].e();
	    m_mcPhoton2Theta                 = mc_nPhotons[1].theta();
	    m_mcPhoton2Phi                   = mc_nPhotons[1].phi();
	    if(mc_nPhotons[1].e() > mc_nPhotons[0].e())
	      {
	    m_mcHighestenergeticPhotonEnergy = mc_nPhotons[1].e(); 
	    m_mcHighestenergeticPhotonTheta  = mc_nPhotons[1].theta();
	    m_mcHighestenergeticPhotonPhi    = mc_nPhotons[1].phi();
	    m_mcHighestenergeticPhotonX      = mc_nPhotons[1].x();
	    m_mcHighestenergeticPhotonY      = mc_nPhotons[1].y();
	    m_mcHighestenergeticPhotonZ      = mc_nPhotons[1].z();
	      }}

	  if(mc_nPhotons.size() > 2)
	    {
	    m_mcPhoton3Energy                = mc_nPhotons[2].e();
	    m_mcPhoton3Theta                 = mc_nPhotons[2].theta();
	    m_mcPhoton3Phi                   = mc_nPhotons[2].phi();
	    if(mc_nPhotons[2].e() > mc_nPhotons[1].e() && mc_nPhotons[2].e() > mc_nPhotons[0].e())
	      {
	    m_mcHighestenergeticPhotonEnergy = mc_nPhotons[2].e(); 
	    m_mcHighestenergeticPhotonTheta  = mc_nPhotons[2].theta();
	    m_mcHighestenergeticPhotonPhi    = mc_nPhotons[2].phi();
	    m_mcHighestenergeticPhotonX      = mc_nPhotons[2].x();
	    m_mcHighestenergeticPhotonY      = mc_nPhotons[2].y();
	    m_mcHighestenergeticPhotonZ      = mc_nPhotons[2].z();
	      }}

	  if(mc_nPhotons.size() > 3)
	    {
	    m_mcPhoton4Energy                = mc_nPhotons[3].e();
	    m_mcPhoton4Theta                 = mc_nPhotons[3].theta();
	    m_mcPhoton4Phi                   = mc_nPhotons[3].phi();
	    if(mc_nPhotons[3].e() > mc_nPhotons[2].e() && mc_nPhotons[3].e() > mc_nPhotons[1].e() && mc_nPhotons[3].e() > mc_nPhotons[0].e())
	      {
	    m_mcHighestenergeticPhotonEnergy = mc_nPhotons[3].e(); 
	    m_mcHighestenergeticPhotonTheta  = mc_nPhotons[3].theta();
	    m_mcHighestenergeticPhotonPhi    = mc_nPhotons[3].phi();
	    m_mcHighestenergeticPhotonX      = mc_nPhotons[3].x();
	    m_mcHighestenergeticPhotonY      = mc_nPhotons[3].y();
	    m_mcHighestenergeticPhotonZ      = mc_nPhotons[3].z();
	      }}
   
  }}

 





  SmartDataPtr<EvtRecTrackCol> evtRecTrkCol(eventSvc(),  EventModel::EvtRec::EvtRecTrackCol);

  Vint iGood, iep, iem, ipip, ipim;
  iGood.clear();
  iep.clear();
  iem.clear();
  ipip.clear();
  ipim.clear();



  Vp4 pep, pem, ppip, ppim;

  pep.clear();
  pem.clear();
  ppip.clear();
  ppim.clear();


  int nCharge = 0;

  Hep3Vector xorigin(0,0,0);
  HepPoint3D xorigin1(0,0,0);  
  
  IVertexDbSvc*  vtxsvc;
  Gaudi::svcLocator()->service("VertexDbSvc", vtxsvc);
  if(vtxsvc->isVertexValid()){
  double* dbv = vtxsvc->PrimaryVertex(); 
  double*  vv = vtxsvc->SigmaPrimaryVertex();  

  xorigin.setX(dbv[0]);
  xorigin.setY(dbv[1]);
  xorigin.setZ(dbv[2]);
  }

  for(int i = 0; i < evtRecEvent->totalCharged(); i++){
    EvtRecTrackIterator itTrk=evtRecTrkCol->begin() + i;
    if(!(*itTrk)->isMdcTrackValid()) continue;
    RecMdcTrack *mdcTrk = (*itTrk)->mdcTrack();
    double pch=mdcTrk->p();
    double x0=mdcTrk->x();
    double y0=mdcTrk->y();
    double z0=mdcTrk->z();
    double phi0=mdcTrk->helix(1);
    double xv=xorigin.x();
    double yv=xorigin.y();
    double Rxy=(x0-xv)*cos(phi0)+(y0-yv)*sin(phi0);
    m_vx0 = x0;
    m_vy0 = y0;
    m_vz0 = z0;
    m_vr0 = Rxy;

    HepVector a = mdcTrk->helix();
    HepSymMatrix Ea = mdcTrk->err();
    HepPoint3D point0(0.,0.,0.);   // the initial point for MDC recosntruction
    HepPoint3D IP(xorigin[0],xorigin[1],xorigin[2]); 
    VFHelix helixip(point0,a,Ea); 
    helixip.pivot(IP);
    HepVector vecipa = helixip.a();
    double  Rvxy0=fabs(vecipa[0]);  //the nearest distance to IP in xy plane
    double  Rvz0=vecipa[3];         //the nearest distance to IP in z direction
    double  Rvphi0=vecipa[1];
 
    m_rvxy0  =  Rvxy0;
    m_rvz0   =  Rvz0;
    m_rvphi0 =  Rvphi0;

    
    if(fabs(Rvz0)  >= 10.0) continue;
    if(fabs(Rvxy0) >= 1.0) continue;
    
    iGood.push_back(i);
    nCharge += mdcTrk->charge();
  }
  
  //
  // Finish Good Charged Track Selection
  //

  int nGood = iGood.size();

  m_nGood = nGood;

  log << MSG::DEBUG << "ngood, totcharge = " << nGood << " , " << nCharge << endreq;
  if((nGood != 4)||(nCharge!=0)){
    return StatusCode::SUCCESS;
  }
  Ncut1++;



  // Study the properties of photon


  Vint iGam;
  iGam.clear();

  // Compute the correct values of gamma variables ... //Added by Vindy

  for(int i = evtRecEvent->totalCharged(); i< evtRecEvent->totalTracks(); i++) {
    
    EvtRecTrackIterator itTrk=evtRecTrkCol->begin() + i;
      
    if(!(*itTrk)->isEmcShowerValid()) continue;
    RecEmcShower *emcTrk = (*itTrk)->emcShower();
    Hep3Vector emcpos(emcTrk->x(), emcTrk->y(), emcTrk->z());
    HepPoint3D EmcPos(emcTrk->x(), emcTrk->y(), emcTrk->z());
    m_emcpos_theta[i-m_nCharge]          =  EmcPos.theta();
    m_emcpos_theta[i-m_nCharge]          =  EmcPos.theta();
    m_emcpos_phi[i-m_nCharge]            =  EmcPos.phi();
    m_numHits[i-m_nCharge]               =  emcTrk->numHits();
    m_status[i-m_nCharge]                =  emcTrk->status();
    m_cellId[i-m_nCharge]                =  emcTrk->cellId();
    m_module[i-m_nCharge]                =  emcTrk->module();
    m_x[i-m_nCharge]                     =  emcTrk->x();
    m_y[i-m_nCharge]                     =  emcTrk->y();
    m_z[i-m_nCharge]                     =  emcTrk->z();
    m_theta[i-m_nCharge]                 =  emcTrk->theta();
    m_phi[i-m_nCharge]                   =  emcTrk->phi();
    m_dx[i-m_nCharge]                    =  emcTrk->dx();
    m_dy[i-m_nCharge]                    =  emcTrk->dy();
    m_dz[i-m_nCharge]                    =  emcTrk->dz();
    m_dtheta[i-m_nCharge]                =  emcTrk->dtheta();
    m_dphi[i-m_nCharge]                  =  emcTrk->dphi();
    m_energy[i-m_nCharge]                =  emcTrk->energy();
    m_dE[i-m_nCharge]                    =  emcTrk->dE();
    m_eSeed[i-m_nCharge]                 =  emcTrk->eSeed();
    m_e3x3[i-m_nCharge]                  =  emcTrk->e3x3();
    m_e5x5[i-m_nCharge]                  =  emcTrk->e5x5();
    m_secondMoment[i-m_nCharge]          =  emcTrk->secondMoment();
    m_latMoment[i-m_nCharge]             =  emcTrk->latMoment();
    m_a20Moment[i-m_nCharge]             =  emcTrk->a20Moment();
    m_a42Moment[i-m_nCharge]             =  emcTrk->a42Moment();
    m_time[i-m_nCharge]                  =  emcTrk->time();

    

    // find the nearest charged track
    double dthe = 200.;
    double dphi = 200.;
    double dang = 200.;

 
    for(int j = 0; j < evtRecEvent->totalCharged(); j++) {
      EvtRecTrackIterator jtTrk = evtRecTrkCol->begin() + j;
      if(!(*jtTrk)->isExtTrackValid()) continue;
      RecExtTrack *extTrk = (*jtTrk)->extTrack();
      if(extTrk->emcVolumeNumber() == -1) continue;
      Hep3Vector extpos = extTrk->emcPosition();
      //      double ctht = extpos.cosTheta(emcpos);
      double angd = extpos.angle(emcpos);
      double thed = extpos.theta() - emcpos.theta();
      double phid = extpos.deltaPhi(emcpos);
      thed = fmod(thed+CLHEP::twopi+CLHEP::twopi+pi, CLHEP::twopi) - CLHEP::pi;
      phid = fmod(phid+CLHEP::twopi+CLHEP::twopi+pi, CLHEP::twopi) - CLHEP::pi;
      if(angd < dang){
        dang = angd;
        dthe = thed;
        dphi = phid;
      }
    }

    //  if(dang>200) continue;

    dthe = dthe * 180 / (CLHEP::pi);
    dphi = dphi * 180 / (CLHEP::pi);
    dang = dang * 180 / (CLHEP::pi);
    
    m_dthe_ch[i-m_nCharge] = dthe;
    m_dphi_ch[i-m_nCharge] = dphi;
    m_dang_ch[i-m_nCharge] = dang;
   

   double ctht = cos(emcTrk->theta());
   //  if((emcTrk->module() == 1) && (fabs(ctht) > 0.8 )) continue;
   //   if((emcTrk->module() == 0 || emcTrk->module() == 2) && ( fabs(ctht)> 0.92|| fabs(ctht) <0.86 )) continue;

   //   if(fabs(dang) < m_gammaAngleCut) continue; 
   if(emcTrk->module() == 1){
     //   if(m_energy[i-m_nCharge]<m_energyThreshold1) continue;
       }
   if(emcTrk->module() == 0 || emcTrk->module() == 2){
     //  if(m_energy[i-m_nCharge]<m_energyThreshold2) continue;
        }    
   //   if(emcTrk->time()<m_timedown || emcTrk->time()>m_timeup) continue;

   iGam.push_back(i);
      }


  int nGam = iGam.size();
  m_nGam = nGam;




  Vp4 pGam;
  pGam.clear();
  for(int i = 0; i < nGam; i++) {
    EvtRecTrackIterator itTrk = evtRecTrkCol->begin() + iGam[i]; 
    RecEmcShower* emcTrk = (*itTrk)->emcShower();
    double eraw = emcTrk->energy();
    double phi = emcTrk->phi();
    double the = emcTrk->theta();
    HepLorentzVector ptrk;
    ptrk.setPx(eraw*sin(the)*cos(phi));
    ptrk.setPy(eraw*sin(the)*sin(phi));
    ptrk.setPz(eraw*cos(the));
    ptrk.setE(eraw);

//    ptrk = ptrk.boost(-0.011,0,0);// boost to cms

    pGam.push_back(ptrk);
  }


  // Finish the PID Selection

        ParticleID *pid = ParticleID::instance();
        int npid=0;
        for(int i = 0; i < nGood; i++) {
            EvtRecTrackIterator itTrk = evtRecTrkCol->begin() + iGood[i];
    


        pid->init();
            pid->setMethod(pid->methodProbability());
            pid->setChiMinCut(4);
            pid->setRecTrack(*itTrk);
            pid->usePidSys(pid->useDedx() | pid->useTof1() | pid->useTof2() | pid->useTofE()); // use PID sub-system
            pid->identify(pid->onlyMuon() | pid->onlyPion() | pid->onlyKaon() | pid->onlyElectron() | pid->onlyProton());    // seperater Pion/Kaon
            pid->calculate();
            if(!(pid->IsPidInfoValid())) continue;
            if(!(*itTrk)->isMdcKalTrackValid()) continue;
         
            RecMdcTrack* mdcTrk = (*itTrk)->mdcTrack(); 
            m_ptrk_pid[i]       =    mdcTrk->p();
            m_cost_pid[i]       =    cos(mdcTrk->theta()); 
            m_dedx_pid[i]       =    pid->chiDedx(1);
            m_tof1_pid[i]       =    pid->chiTof1(1);
            m_tof2_pid[i]       =    pid->chiTof2(1);
     	    m_electron_pid[i]   =    pid->probElectron();
            m_pion_pid[i]       =    pid->probPion();
            m_kaon_pid[i]       =    pid->probKaon();


     if((pid->probElectron()>pid->probPion())&&(pid->probElectron()>pid->probKaon())){
       if(!(*itTrk)->isMdcKalTrackValid()) continue;
       RecMdcKalTrack* mdcKalTrk = (*itTrk)->mdcKalTrack();
       RecMdcKalTrack::setPidType(RecMdcKalTrack::electron);
       if(mdcKalTrk->charge()>0){
         iep.push_back(iGood[i]);
         HepLorentzVector ptrk;
         ptrk.setPx(mdcKalTrk->px());
         ptrk.setPy(mdcKalTrk->py());
         ptrk.setPz(mdcKalTrk->pz());
         double p3 = ptrk.mag();
         ptrk.setE(sqrt(p3*p3+me*me));
         pep.push_back(ptrk);
         ep_electronPID = pid->probElectron();
         ep_kaonPID = pid->probKaon();
         ep_pionPID= pid->probPion();
       } else {
        iem.push_back(iGood[i]);
         HepLorentzVector ptrk;
         ptrk.setPx(mdcKalTrk->px());
         ptrk.setPy(mdcKalTrk->py());
         ptrk.setPz(mdcKalTrk->pz());
         double p3 = ptrk.mag();
         ptrk.setE(sqrt(p3*p3+me*me));
         pem.push_back(ptrk);
         em_electronPID = pid->probElectron();
         em_kaonPID = pid->probKaon();
         em_pionPID= pid->probPion();
       }}else{
       if(!(*itTrk)->isMdcKalTrackValid()) continue;
       RecMdcKalTrack* mdcKalTrk = (*itTrk)->mdcKalTrack();
       RecMdcKalTrack::setPidType(RecMdcKalTrack::pion);
       if(mdcKalTrk->charge()>0){
         ipip.push_back(iGood[i]);
         HepLorentzVector ptrk;
         ptrk.setPx(mdcKalTrk->px());
         ptrk.setPy(mdcKalTrk->py());
         ptrk.setPz(mdcKalTrk->pz());
         double p3 = ptrk.mag();
         ptrk.setE(sqrt(p3*p3+mpi*mpi));
         ppip.push_back(ptrk);
         pip_electronPID = pid->probElectron();
         pip_kaonPID = pid->probKaon();
         pip_pionPID= pid->probPion();
         }else{
         ipim.push_back(iGood[i]);
         HepLorentzVector ptrk;
         ptrk.setPx(mdcKalTrk->px());
         ptrk.setPy(mdcKalTrk->py());
         ptrk.setPz(mdcKalTrk->pz());
         double p3 = ptrk.mag();
         ptrk.setE(sqrt(p3*p3+mpi*mpi));
         ppim.push_back(ptrk);
         pim_electronPID = pid->probElectron();
         pim_kaonPID = pid->probKaon();
         pim_pionPID= pid->probPion();
          }}}


        int npip = ipip.size();
        int npim = ipim.size();

         int nep = iep.size();
         int nem = iem.size();

        if(nep*nem*npip*npim != 1)  return SUCCESS;

	 m_nep =  nep;
	 m_nem =  nem;

         m_npip =  npip;
         m_npim =  npim;

	 Ncut2++;


  // Calculate the E/P
   double pipEop = 10000.0;
   double pimEop = 10000.0;

   if ((*(evtRecTrkCol->begin()+ipip[0]))->isMdcTrackValid() && (*(evtRecTrkCol->begin()+ipip[0]))->isEmcShowerValid() && (*(evtRecTrkCol->begin()+ipip[0]))->mdcTrack()->p() > 0) pipEop = (*(evtRecTrkCol->begin()+ipip[0]))->emcShower()->energy()/(*(evtRecTrkCol->begin()+ipip[0]))->mdcTrack()->p();


   if ((*(evtRecTrkCol->begin()+ipim[0]))->isMdcTrackValid() && (*(evtRecTrkCol->begin()+ipim[0]))->isEmcShowerValid() && (*(evtRecTrkCol->begin()+ipim[0]))->mdcTrack()->p() > 0) pimEop = (*(evtRecTrkCol->begin()+ipim[0]))->emcShower()->energy()/(*(evtRecTrkCol->begin()+ipim[0]))->mdcTrack()->p();


  pip_EOP              =  pipEop;
  pim_EOP              =  pimEop;


  if ((*(evtRecTrkCol->begin()+ipip[0]))->isEmcShowerValid())
    {
      pip_ECAL = (*(evtRecTrkCol->begin()+ipip[0]))->emcShower()->energy();
      pip_theta_fromEMC = (*(evtRecTrkCol->begin()+ipip[0]))->emcShower()->theta();
      pip_phi_fromEMC   = (*(evtRecTrkCol->begin()+ipip[0]))->emcShower()->phi();

      pip_A42  = (*(evtRecTrkCol->begin()+ipip[0]))->emcShower()->a42Moment();
      pip_lat  = (*(evtRecTrkCol->begin()+ipip[0]))->emcShower()->latMoment();
      pip_e3x3  = (*(evtRecTrkCol->begin()+ipip[0]))->emcShower()->e3x3();
      pip_e5x5  = (*(evtRecTrkCol->begin()+ipip[0]))->emcShower()->e5x5();
      pip_A20  = (*(evtRecTrkCol->begin()+ipip[0]))->emcShower()->a20Moment();
      pip_secondMoment  = (*(evtRecTrkCol->begin()+ipip[0]))->emcShower()->secondMoment();
      pip_eSeed  = (*(evtRecTrkCol->begin()+ipip[0]))->emcShower()->eSeed();

      if(pip_eSeed != 0)
        {
          pip_e5divSeed_fromEMC = pip_e5x5/pip_eSeed;
          pip_e3divSeed_fromEMC = pip_e3x3/pip_eSeed;
        } else {
	pip_e5divSeed_fromEMC = -10.0;
        pip_e3divSeed_fromEMC = -10.0;
      }
     if(pip_e3x3 != 0) pip_e5div3_fromEMC = pip_e5x5/pip_e3x3;
     else pip_e5div3_fromEMC = -10.0;
    } else {

    pip_ECAL                = -10.0;
    pip_theta_fromEMC       = -10.0;
    pip_phi_fromEMC         = -10.0;
    pip_A42                 = -10.0;
    pip_lat                 = -10.0;
    pip_e3x3                = -10.0;
    pip_e5x5                = -10.0;
    pip_A20                 = -10.0;
    pip_secondMoment        = -10.0;
    pip_eSeed               = -10.0;
    pip_e5divSeed_fromEMC   = -10.0;
    pip_e3divSeed_fromEMC   = -10.0;
    pip_e5div3_fromEMC      = -10.0;

  }

  if ((*(evtRecTrkCol->begin()+ipim[0]))->isEmcShowerValid())
    {
  pim_ECAL = (*(evtRecTrkCol->begin()+ipim[0]))->emcShower()->energy();
  pim_theta_fromEMC = (*(evtRecTrkCol->begin()+ipim[0]))->emcShower()->theta();
  pim_phi_fromEMC   = (*(evtRecTrkCol->begin()+ipim[0]))->emcShower()->phi();
  pim_A42  = (*(evtRecTrkCol->begin()+ipim[0]))->emcShower()->a42Moment();
  pim_lat  = (*(evtRecTrkCol->begin()+ipim[0]))->emcShower()->latMoment();
  pim_e3x3  = (*(evtRecTrkCol->begin()+ipim[0]))->emcShower()->e3x3();
  pim_e5x5  = (*(evtRecTrkCol->begin()+ipim[0]))->emcShower()->e5x5();
  pim_A20  = (*(evtRecTrkCol->begin()+ipim[0]))->emcShower()->a20Moment();
  pim_secondMoment  = (*(evtRecTrkCol->begin()+ipim[0]))->emcShower()->secondMoment();
  pim_eSeed  = (*(evtRecTrkCol->begin()+ipim[0]))->emcShower()->eSeed();

  if(pim_eSeed != 0 )
   {
  pim_e5divSeed_fromEMC = pim_e5x5/pim_eSeed;
  pim_e3divSeed_fromEMC = pim_e3x3/pim_eSeed;
   } else {
  pim_e5divSeed_fromEMC = -10.0;
  pim_e3divSeed_fromEMC = -10.0;
   }
 if(pim_e3x3 != 0) pim_e5div3_fromEMC = pim_e5x5/pim_e3x3;
 else pim_e5div3_fromEMC = -10.0;
      }
 else {
  pim_ECAL                 = -10.0;
  pim_theta_fromEMC        = -10.0;
  pim_phi_fromEMC          = -10.0;
  pim_A42                  = -10.0;
  pim_lat                  = -10.0;
  pim_e3x3                 = -10.0;
  pim_e5x5                 = -10.0;
  pim_A20                  = -10.0;
  pim_secondMoment         = -10.0;
  pim_eSeed                = -10.0;
  pim_e5divSeed_fromEMC    = -10.0;
  pim_e3divSeed_fromEMC    = -10.0;
  pim_e5div3_fromEMC       = -10.0;
  }


  if ((*(evtRecTrkCol->begin()+ipip[0]))->isExtTrackValid() && (*(evtRecTrkCol->begin()+ipip[0]))->extTrack()->emcVolumeNumber() != -1)
    {
  pip_exttheta = (*(evtRecTrkCol->begin()+ipip[0]))->extTrack()->emcPosition().theta();
  pip_extphi = (*(evtRecTrkCol->begin()+ipip[0]))->extTrack()->emcPosition().phi();
    }    else {
  pip_exttheta = -10.0;
  pip_extphi = -10.0;
  }


  if ((*(evtRecTrkCol->begin()+ipim[0]))->isExtTrackValid() && (*(evtRecTrkCol->begin()+ipim[0]))->extTrack()->emcVolumeNumber() != -1)
    {
  pim_exttheta = (*(evtRecTrkCol->begin()+ipim[0]))->extTrack()->emcPosition().theta();
  pim_extphi = (*(evtRecTrkCol->begin()+ipim[0]))->extTrack()->emcPosition().phi();
    }   else {
  pim_exttheta  = -10.0;
  pim_extphi    = -10;
  }



  //********************************************************
 // properties from dEdx for Pions
 //********************************************************

 if((*(evtRecTrkCol->begin()+ipip[0]))->isMdcDedxValid())
      {
 pip_numGoodHits  = (*(evtRecTrkCol->begin()+ipip[0]))->mdcDedx()->numGoodHits();
 pip_numTotalHits = (*(evtRecTrkCol->begin()+ipip[0]))->mdcDedx()->numTotalHits();
 pip_dedxchi = (*(evtRecTrkCol->begin()+ipip[0]))->mdcDedx()->chiE();
      } else {
   pip_numGoodHits  = -10.0;
   pip_numTotalHits = -10.0;
   pip_dedxchi      = -10.0;
  }

 if((*(evtRecTrkCol->begin()+ipim[0]))->isMdcDedxValid())
      {
 pim_numGoodHits  = (*(evtRecTrkCol->begin()+ipim[0]))->mdcDedx()->numGoodHits();
 pim_numTotalHits = (*(evtRecTrkCol->begin()+ipim[0]))->mdcDedx()->numTotalHits();
 pim_dedxchi = (*(evtRecTrkCol->begin()+ipim[0]))->mdcDedx()->chiE();
      } else {
   pim_numGoodHits  = -10.0;
   pim_numTotalHits = -10.0;
   pim_dedxchi      = -10.0;
  }



 // Calculate the extrapolated track positions

  if ((*(evtRecTrkCol->begin()+iep[0]))->isExtTrackValid() && (*(evtRecTrkCol->begin()+iep[0]))->extTrack()->emcVolumeNumber() != -1)
    {
 ep_exttheta = (*(evtRecTrkCol->begin()+iep[0]))->extTrack()->emcPosition().theta();
 ep_extphi = (*(evtRecTrkCol->begin()+iep[0]))->extTrack()->emcPosition().phi();
 ep_ext_x  = (*(evtRecTrkCol->begin()+iep[0]))->extTrack()->emcPosition().x();
 ep_ext_y  = (*(evtRecTrkCol->begin()+iep[0]))->extTrack()->emcPosition().y();
 ep_ext_z  = (*(evtRecTrkCol->begin()+iep[0]))->extTrack()->emcPosition().z();


    } else {

    ep_exttheta  = -100.0;
    ep_extphi    = -100.0;
    ep_ext_x     = -100.0;
    ep_ext_y     = -100.0;
    ep_ext_z     = -100.0;
 
  }

  if ((*(evtRecTrkCol->begin()+iem[0]))->isExtTrackValid() && (*(evtRecTrkCol->begin()+iem[0]))->extTrack()->emcVolumeNumber() != -1)
    {
 em_exttheta = (*(evtRecTrkCol->begin()+iem[0]))->extTrack()->emcPosition().theta();
 em_extphi = (*(evtRecTrkCol->begin()+iem[0]))->extTrack()->emcPosition().phi();
 em_ext_x  = (*(evtRecTrkCol->begin()+iem[0]))->extTrack()->emcPosition().x();
 em_ext_y  = (*(evtRecTrkCol->begin()+iem[0]))->extTrack()->emcPosition().y();
 em_ext_z  = (*(evtRecTrkCol->begin()+iem[0]))->extTrack()->emcPosition().z();

    }  else {

    em_exttheta  = -100.0;
    em_extphi    = -100.0;
    em_ext_x     = -100.0;
    em_ext_y     = -100.0;
    em_ext_z     = -100.0;
   }





  if((*(evtRecTrkCol->begin()+iem[0]))->isTofTrackValid()) 
    {
  SmartRefVector<RecTofTrack> tofTrkCol1=(*(evtRecTrkCol->begin()+iem[0]))->tofTrack();
  SmartRefVector<RecTofTrack>::iterator iter_tof1=tofTrkCol1.begin();

  for(;iter_tof1!=tofTrkCol1.end();iter_tof1++){
         
  TofHitStatus* status1 =new TofHitStatus;
  status1->setStatus( (*iter_tof1)->status() );
  if(status1->is_cluster()){
  em_time_tof     = (*iter_tof1)->tof();
  em_sigma_tof    = (*iter_tof1)->sigmaElectron();
  em_expEtof     = (*iter_tof1)->texpElectron();
  }}} else {
    em_time_tof   = -99.0;
    em_sigma_tof  = -99.0;
    em_expEtof   = -99.0;
  }



  if((*(evtRecTrkCol->begin()+iep[0]))->isTofTrackValid()) 
    {
  SmartRefVector<RecTofTrack> tofTrkCol2          = (*(evtRecTrkCol->begin()+iep[0]))->tofTrack();
  SmartRefVector<RecTofTrack>::iterator iter_tof2 = tofTrkCol2.begin();

  for(;iter_tof2!=tofTrkCol2.end();iter_tof2++){
         
  TofHitStatus* status2 =new TofHitStatus;
  status2->setStatus( (*iter_tof2)->status() );
  if(status2->is_cluster()){
  ep_time_tof     = (*iter_tof2)->tof();
  ep_sigma_tof    = (*iter_tof2)->sigmaElectron();
  ep_expEtof     = (*iter_tof2)->texpElectron();
  }}} else {
    ep_time_tof   = -99.0;
    ep_sigma_tof  = -99.0;
    ep_expEtof   = -99.0;
  }







 // Calculate the E/P 

 


  // Calculate the E/P 
   double epEop = -100.0;
   double emEop = -100.0;  

   if ((*(evtRecTrkCol->begin()+iep[0]))->isMdcTrackValid() && (*(evtRecTrkCol->begin()+iep[0]))->isEmcShowerValid() && (*(evtRecTrkCol->begin()+iep[0]))->mdcTrack()->p() > 0) epEop = (*(evtRecTrkCol->begin()+iep[0]))->emcShower()->energy()/(*(evtRecTrkCol->begin()+iep[0]))->mdcTrack()->p();


   if ((*(evtRecTrkCol->begin()+iem[0]))->isMdcTrackValid() && (*(evtRecTrkCol->begin()+iem[0]))->isEmcShowerValid() && (*(evtRecTrkCol->begin()+iem[0]))->mdcTrack()->p() > 0) emEop = (*(evtRecTrkCol->begin()+iem[0]))->emcShower()->energy()/(*(evtRecTrkCol->begin()+iem[0]))->mdcTrack()->p();


   ep_EOP              =  epEop;
   em_EOP              =  emEop;



  if ((*(evtRecTrkCol->begin()+iep[0]))->isEmcShowerValid())
    {
      ep_ECAL = (*(evtRecTrkCol->begin()+iep[0]))->emcShower()->energy();
      ep_theta_fromEMC = (*(evtRecTrkCol->begin()+iep[0]))->emcShower()->theta();
      ep_phi_fromEMC   = (*(evtRecTrkCol->begin()+iep[0]))->emcShower()->phi();
      ep_x_fromEMC   = (*(evtRecTrkCol->begin()+iep[0]))->emcShower()->x();
      ep_y_fromEMC   = (*(evtRecTrkCol->begin()+iep[0]))->emcShower()->y();
      ep_z_fromEMC   = (*(evtRecTrkCol->begin()+iep[0]))->emcShower()->z();
      ep_numhits     = (*(evtRecTrkCol->begin()+iep[0]))->emcShower()->numHits();
      ep_A42  = (*(evtRecTrkCol->begin()+iep[0]))->emcShower()->a42Moment();
      ep_lat  = (*(evtRecTrkCol->begin()+iep[0]))->emcShower()->latMoment();
      ep_e3x3  = (*(evtRecTrkCol->begin()+iep[0]))->emcShower()->e3x3();
      ep_e5x5  = (*(evtRecTrkCol->begin()+iep[0]))->emcShower()->e5x5();
      ep_A20  = (*(evtRecTrkCol->begin()+iep[0]))->emcShower()->a20Moment();
      ep_secondMoment  = (*(evtRecTrkCol->begin()+iep[0]))->emcShower()->secondMoment();
      ep_eSeed  = (*(evtRecTrkCol->begin()+iep[0]))->emcShower()->eSeed();

  
      if(ep_eSeed != 0)
	{
	  ep_e5divSeed_fromEMC = ep_e5x5/ep_eSeed;
	  ep_e3divSeed_fromEMC = ep_e3x3/ep_eSeed;
	} else {
	ep_e5divSeed_fromEMC = -10.0;
	ep_e3divSeed_fromEMC = -10.0;
      }
     if(ep_e3x3 != 0) ep_e5div3_fromEMC = ep_e5x5/ep_e3x3;
     else ep_e5div3_fromEMC = -10.0; 
    } else {
 
    ep_ECAL                = -100.0;
    ep_theta_fromEMC       = -100.0;
    ep_phi_fromEMC         = -100.0;
    ep_A42                 = -100.0;
    ep_lat                 = -100.0;
    ep_e3x3                = -100.0;
    ep_e5x5                = -100.0;
    ep_A20                 = -100.0;
    ep_secondMoment        = -100.0;
    ep_eSeed               = -100.0;
    ep_e5divSeed_fromEMC   = -100.0;
    ep_e3divSeed_fromEMC   = -100.0;
    ep_e5div3_fromEMC      = -100.0;  
    ep_x_fromEMC           = -100.0;
    ep_y_fromEMC           = -100.0;
    ep_z_fromEMC           = -100.0;
    ep_numhits             = -100.0;
  }  



  if ((*(evtRecTrkCol->begin()+iem[0]))->isEmcShowerValid())
    {
  em_ECAL = (*(evtRecTrkCol->begin()+iem[0]))->emcShower()->energy();
  em_theta_fromEMC = (*(evtRecTrkCol->begin()+iem[0]))->emcShower()->theta();
  em_phi_fromEMC   = (*(evtRecTrkCol->begin()+iem[0]))->emcShower()->phi();
  em_x_fromEMC   = (*(evtRecTrkCol->begin()+iem[0]))->emcShower()->x();
  em_y_fromEMC   = (*(evtRecTrkCol->begin()+iem[0]))->emcShower()->y();
  em_z_fromEMC   = (*(evtRecTrkCol->begin()+iem[0]))->emcShower()->z();
  em_numhits     = (*(evtRecTrkCol->begin()+iem[0]))->emcShower()->numHits();
  em_A42  = (*(evtRecTrkCol->begin()+iem[0]))->emcShower()->a42Moment();
  em_lat  = (*(evtRecTrkCol->begin()+iem[0]))->emcShower()->latMoment();
  em_e3x3  = (*(evtRecTrkCol->begin()+iem[0]))->emcShower()->e3x3();
  em_e5x5  = (*(evtRecTrkCol->begin()+iem[0]))->emcShower()->e5x5();
  em_A20  = (*(evtRecTrkCol->begin()+iem[0]))->emcShower()->a20Moment();
  em_secondMoment  = (*(evtRecTrkCol->begin()+iem[0]))->emcShower()->secondMoment();
  em_eSeed  = (*(evtRecTrkCol->begin()+iem[0]))->emcShower()->eSeed();

  if(em_eSeed != 0 )
   {
  em_e5divSeed_fromEMC = em_e5x5/em_eSeed;
  em_e3divSeed_fromEMC = em_e3x3/em_eSeed;
   } else {
  em_e5divSeed_fromEMC = -10.0;
  em_e3divSeed_fromEMC = -10.0;
   }
 if(em_e3x3 != 0) em_e5div3_fromEMC = em_e5x5/em_e3x3;
 else em_e5div3_fromEMC = -10.0;
      }
 else {
  em_ECAL                 = -100.0;
  em_theta_fromEMC        = -100.0;
  em_phi_fromEMC          = -100.0;
  em_x_fromEMC            = -100.0;
  em_y_fromEMC            = -100.0;
  em_z_fromEMC            = -100.0;
  em_numhits              = -100.0;

  em_A42                  = -100.0;
  em_lat                  = -100.0;
  em_e3x3                 = -100.0;
  em_e5x5                 = -100.0;
  em_A20                  = -100.0;
  em_secondMoment         = -100.0;
  em_eSeed                = -100.0;
  em_e5divSeed_fromEMC    = -100.0;
  em_e3divSeed_fromEMC    = -100.0;
  em_e5div3_fromEMC       = -100.0;
  }  




  //********************************************************
 // properties from dEdx for Electrons
 //********************************************************
 
 if((*(evtRecTrkCol->begin()+iep[0]))->isMdcDedxValid())
      {
 ep_numGoodHits  = (*(evtRecTrkCol->begin()+iep[0]))->mdcDedx()->numGoodHits();
 ep_numTotalHits = (*(evtRecTrkCol->begin()+iep[0]))->mdcDedx()->numTotalHits();
 ep_dedxchi = (*(evtRecTrkCol->begin()+iep[0]))->mdcDedx()->chiE();
      } else {
   ep_numGoodHits  = -100.0;
   ep_numTotalHits = -100.0;
   ep_dedxchi      = -100.0;
  }  


 if((*(evtRecTrkCol->begin()+iem[0]))->isMdcDedxValid())
      {
 em_numGoodHits  = (*(evtRecTrkCol->begin()+iem[0]))->mdcDedx()->numGoodHits();
 em_numTotalHits = (*(evtRecTrkCol->begin()+iem[0]))->mdcDedx()->numTotalHits();
 em_dedxchi = (*(evtRecTrkCol->begin()+iem[0]))->mdcDedx()->chiE();
      } else {
   em_numGoodHits  = -100.0;
   em_numTotalHits = -100.0;
   em_dedxchi      = -100.0;
  }  
 


	//    Test the vertex fit for Pions

        RecMdcKalTrack *pipTrk = (*(evtRecTrkCol->begin()+ipip[0]))->mdcKalTrack();
        RecMdcKalTrack *pimTrk = (*(evtRecTrkCol->begin()+ipim[0]))->mdcKalTrack();

        WTrackParameter wvpipTrk, wvpimTrk;

        wvpipTrk = WTrackParameter(mpi, pipTrk->getZHelix(), pipTrk->getZError());
        wvpimTrk = WTrackParameter(mpi, pimTrk->getZHelix(), pimTrk->getZError());

	/*	HepPoint3D vx1(0., 0., 0.);
	HepSymMatrix Evx1(3, 0);
	double bx1 = 1E+6;
	double by1 = 1E+6;
        double bz1 = 1E+6;
        Evx1[0][0] = bx1*bx1;
	Evx1[1][1] = by1*by1;
        Evx1[2][2] = bz1*bz1;


        VertexParameter vxpar1;
	vxpar1.setVx(vx1);
	vxpar1.setEvx(Evx1);


	VertexFit* vtxfit1 = VertexFit::instance();
	vtxfit1->init();
	vtxfit1->AddTrack(0,  wvpipTrk);
	vtxfit1->AddTrack(1,  wvpimTrk);
        vtxfit1->AddVertex(0, vxpar1,0, 1);
        if(!vtxfit1->Fit(0)) return SUCCESS;
	vtxfit1->Swim(0);


	dipi_vtxfit_chi2 = vtxfit1->chisq(0);

	WTrackParameter wpip = vtxfit1->wtrk(0);
	WTrackParameter wpim = vtxfit1->wtrk(1);



     HepLorentzVector pip_vtx = wpip.p();
     HepLorentzVector pim_vtx = wpim.p();

     HepLorentzVector Dipi = pip_vtx + pim_vtx;
	

     Dipimass     =    Dipi.m();
     Dipipx       =    Dipi.px();
     Dipipy       =    Dipi.py();
     Dipipz       =    Dipi.pz();
     Dipie        =    Dipi.e();
     Dipitheta    =    Dipi.theta();
     Dipiphi      =    Dipi.phi();
     Dipimom      =    Dipi.vect().mag();


     pipmass      =    pip_vtx.m();
     pippx        =    pip_vtx.px();
     pippy        =    pip_vtx.py();
     pippz        =    pip_vtx.pz();
     pipe         =    pip_vtx.e();
     piptheta     =    pip_vtx.theta();
     pipphi       =    pip_vtx.phi();
     pipmom       =    pip_vtx.vect().mag();


     pimmass      =    pim_vtx.m();
     pimpx        =    pim_vtx.px();
     pimpy        =    pim_vtx.py();
     pimpz        =    pim_vtx.pz();
     pime         =    pim_vtx.e();
     pimtheta     =    pim_vtx.theta();
     pimphi       =    pim_vtx.phi();
     pimmom       =    pim_vtx.vect().mag();

*/


  //    Test the vertex fit for electrons

  RecMdcKalTrack *epTrk = (*(evtRecTrkCol->begin()+iep[0]))->mdcKalTrack();
  RecMdcKalTrack *emTrk = (*(evtRecTrkCol->begin()+iem[0]))->mdcKalTrack();

  WTrackParameter wvepTrk, wvemTrk;

  wvepTrk = WTrackParameter(me, epTrk->getZHelixE(), epTrk->getZErrorE());
  wvemTrk = WTrackParameter(me, emTrk->getZHelixE(), emTrk->getZErrorE());
 
 
  
  HepPoint3D vx(0., 0., 0.);
  HepSymMatrix Evx(3, 0);
  double bx = 1E+6;
  double by = 1E+6;
  double bz = 1E+6;
  Evx[0][0] = bx*bx;
  Evx[1][1] = by*by;
  Evx[2][2] = bz*bz;


  VertexParameter vxpar;
  vxpar.setVx(vx);
  vxpar.setEvx(Evx);
  

  VertexFit* vtxfit = VertexFit::instance();
  vtxfit->init();
  vtxfit->AddTrack(0,  wvpipTrk);
  vtxfit->AddTrack(1,  wvpimTrk);
  vtxfit->AddTrack(2,  wvepTrk);
  vtxfit->AddTrack(3,  wvemTrk);
  vtxfit->AddVertex(0, vxpar,0, 1, 2, 3);
  if(!vtxfit->Fit(0)) return StatusCode::SUCCESS;
  Ncut3++;


 vtxfit->Swim(0);


  elect_vtxfit_chi2 = vtxfit->chisq();

  WTrackParameter wep = vtxfit->wtrk(2);
  WTrackParameter wem = vtxfit->wtrk(3);

  HepLorentzVector ep_vtx = wep.p();
  HepLorentzVector em_vtx = wem.p();

  HepLorentzVector Dielec = ep_vtx + em_vtx;

  WTrackParameter wpip = vtxfit->wtrk(0);
  WTrackParameter wpim = vtxfit->wtrk(1);






  HepLorentzVector pip_vtx = wpip.p();
  HepLorentzVector pim_vtx = wpim.p();

  HepLorentzVector Dipi = pip_vtx + pim_vtx;
  

  Dipimass     =    Dipi.m();
  Dipipx       =    Dipi.px();
  Dipipy       =    Dipi.py();
  Dipipz       =    Dipi.pz();
  Dipie        =    Dipi.e();
  Dipitheta    =    Dipi.theta();
  Dipiphi      =    Dipi.phi();
  Dipimom      =    Dipi.vect().mag();


  pipmass      =    pip_vtx.m();
  pippx        =    pip_vtx.px();
  pippy        =    pip_vtx.py();
  pippz        =    pip_vtx.pz();
  pipe         =    pip_vtx.e();
  piptheta     =    pip_vtx.theta();
  pipphi       =    pip_vtx.phi();
  pipmom       =    pip_vtx.vect().mag();


  pimmass      =    pim_vtx.m();
  pimpx        =    pim_vtx.px();
  pimpy        =    pim_vtx.py();
  pimpz        =    pim_vtx.pz();
  pime         =    pim_vtx.e();
  pimtheta     =    pim_vtx.theta();
  pimphi       =    pim_vtx.phi();
  pimmom       =    pim_vtx.vect().mag();


  Dielecmass  = Dielec.m();
  Dielecpx    = Dielec.px();
  Dielecpy    = Dielec.py();
  Dielecpz    = Dielec.pz();
  Dielece     = Dielec.e();
  Dielectheta = Dielec.theta();
  Dielecphi   = Dielec.phi();



  _epmass    = ep_vtx.m();
  _eppx      = ep_vtx.px();
  _eppy      = ep_vtx.py();
  _eppz      = ep_vtx.pz();
  _epe       = ep_vtx.e();
  _eptheta   = ep_vtx.theta();
  _epphi     = ep_vtx.phi();


  _emmass    = em_vtx.m();
  _empx      = em_vtx.px();
  _empy      = em_vtx.py();
  _empz      = em_vtx.pz();
  _eme       = em_vtx.e();
  _emtheta   = em_vtx.theta();
  _emphi     = em_vtx.phi();



  // Apply 4C Kinematic fit

   HepLorentzVector ecms(0.034,0,0,3.097);

  //   HepLorentzVector ecms(3.650*sin(0.022*0.5),0.0,0.0,3.650); // 3.65 GeV resonance

  HepLorentzVector MissingP4Gamma = ecms - Dipi - Dielec;

  KalmanKinematicFit * kmfit = KalmanKinematicFit::instance();

	kmfit->init();

	kmfit->AddTrack(0, wpip);
	kmfit->AddTrack(1, wpim);
	kmfit->AddTrack(2, wep);
	kmfit->AddTrack(3, wem);
        kmfit->AddMissTrack(4, 0.0, MissingP4Gamma);
        kmfit->AddFourMomentum(0, ecms);
	bool oksq = kmfit->Fit();
	if(oksq) {
 
     HepLorentzVector dipi   = kmfit->pfit(0) + kmfit->pfit(1);
     HepLorentzVector dielec = kmfit->pfit(2) + kmfit->pfit(3);
     HepLorentzVector pi0    = kmfit->pfit(2) + kmfit->pfit(3) + kmfit->pfit(4);


    fourCchi2 = kmfit->chisq();

    Dielec_fit_mass   =  dielec.m();
    Dielec_fit_px     =  dielec.px();
    Dielec_fit_py     =  dielec.px();
    Dielec_fit_pz     =  dielec.py();
    Dielec_fit_e      =  dielec.e();
    Dielec_fit_theta  =  dielec.theta();
    Dielec_fit_phi    =  dielec.phi();
    Dielec_fit_mom    =  dielec.vect().mag();


    epmass      = kmfit->pfit(2).m();
    eppx        = kmfit->pfit(2).px();
    eppy        = kmfit->pfit(2).py();
    eppz        = kmfit->pfit(2).pz();
    epe         = kmfit->pfit(2).e();
    eptheta     = kmfit->pfit(2).theta();
    epphi       = kmfit->pfit(2).phi();
    epmom       = kmfit->pfit(2).vect().mag();

    emmass      = kmfit->pfit(3).m();
    empx        = kmfit->pfit(3).px();
    empy        = kmfit->pfit(3).py();
    empz        = kmfit->pfit(3).pz();
    eme         = kmfit->pfit(3).e();
    emtheta     = kmfit->pfit(3).theta();
    emphi       = kmfit->pfit(3).phi();
    emmom       = kmfit->pfit(3).vect().mag();

    Dipi_fit_mass   =   dipi.m();
    Dipi_fit_e      =   dipi.e();
    Dipi_fit_px     =   dipi.px();
    Dipi_fit_py     =   dipi.py();
    Dipi_fit_pz     =   dipi.pz();
    Dipi_fit_theta  =   dipi.theta();
    Dipi_fit_phi    =   dipi.phi();
    Dipi_fit_mom    =   dipi.vect().mag();

    pip_fit_mass    =  kmfit->pfit(0).m();
    pip_fit_e       =  kmfit->pfit(0).e();
    pip_fit_px      =  kmfit->pfit(0).px();
    pip_fit_py      =  kmfit->pfit(0).py();
    pip_fit_pz      =  kmfit->pfit(0).pz();
    pip_fit_theta   =  kmfit->pfit(0).theta();
    pip_fit_phi     =  kmfit->pfit(0).phi();
    pip_fit_mom     =  kmfit->pfit(0).vect().mag();

    pim_fit_mass    =  kmfit->pfit(1).m();
    pim_fit_e       =  kmfit->pfit(1).e();
    pim_fit_px      =  kmfit->pfit(1).px();
    pim_fit_py      =  kmfit->pfit(1).py();
    pim_fit_pz      =  kmfit->pfit(1).pz();
    pim_fit_theta   =  kmfit->pfit(1).theta();
    pim_fit_phi     =  kmfit->pfit(1).phi();
    pim_fit_mom     =  kmfit->pfit(1).vect().mag();

    pi0_fit_mass    =   pi0.m();
    pi0_fit_e       =   pi0.e();
    pi0_fit_px      =   pi0.px();
    pi0_fit_py      =   pi0.py();
    pi0_fit_pz      =   pi0.pz();
    pi0_fit_theta   =   pi0.theta();
    pi0_fit_phi     =   pi0.phi();
    pi0_fit_mom     =   pi0.vect().mag();


    misTrkGammass   =   kmfit->pfit(4).m();
    misTrkGampx     =   kmfit->pfit(4).px();
    misTrkGampy     =   kmfit->pfit(4).py();
    misTrkGampz     =   kmfit->pfit(4).pz();
    misTrkGame      =   kmfit->pfit(4).e();
    misTrkGamtheta  =   kmfit->pfit(4).theta();
    misTrkGamphi    =   kmfit->pfit(4).phi();
    misTrkGammom    =   kmfit->pfit(4).vect().mag();


    m_pip_pull[0] = kmfit->pull(0)[0];
    m_pip_pull[1] = kmfit->pull(0)[1];
    m_pip_pull[2] = kmfit->pull(0)[2];
    m_pip_pull[3] = kmfit->pull(0)[3];
    m_pip_pull[4] = kmfit->pull(0)[4];

    m_pim_pull[0] = kmfit->pull(1)[0];
    m_pim_pull[1] = kmfit->pull(1)[1];
    m_pim_pull[2] = kmfit->pull(1)[2];
    m_pim_pull[3] = kmfit->pull(1)[3];
    m_pim_pull[4] = kmfit->pull(1)[4];


    m_ep_pull[0] = kmfit->pull(2)[0];
    m_ep_pull[1] = kmfit->pull(2)[1];
    m_ep_pull[2] = kmfit->pull(2)[2];
    m_ep_pull[3] = kmfit->pull(2)[3];
    m_ep_pull[4] = kmfit->pull(2)[4];

    m_em_pull[0] = kmfit->pull(3)[0];
    m_em_pull[1] = kmfit->pull(3)[1];
    m_em_pull[2] = kmfit->pull(3)[2];
    m_em_pull[3] = kmfit->pull(3)[3];
    m_em_pull[4] = kmfit->pull(3)[4];

//Gamma-Conversion Background vertex information /////////////////////////////////////////
//e+ e- vertex fit

  RecMdcKalTrack *epTrk_Gam = (*(evtRecTrkCol->begin()+iep[0]))->mdcKalTrack();
  RecMdcKalTrack *emTrk_Gam = (*(evtRecTrkCol->begin()+iem[0]))->mdcKalTrack();

  WTrackParameter wvepTrk_Gam, wvemTrk_Gam;

  wvepTrk_Gam = WTrackParameter(me, epTrk_Gam->getZHelixE(), epTrk_Gam->getZErrorE());
  wvemTrk_Gam = WTrackParameter(me, emTrk_Gam->getZHelixE(), emTrk_Gam->getZErrorE());

    HepPoint3D IP_Gam(0,0,0);

    HepPoint3D vx_Gam(0., 0., 0.);
    HepSymMatrix Evx_Gam(3, 0);
    double bx_Gam = 1E+6;
    double by_Gam = 1E+6;
    double bz_Gam = 1E+6;
    Evx_Gam[0][0] = bx_Gam*bx_Gam;
    Evx_Gam[1][1] = by_Gam*by_Gam;
    Evx_Gam[2][2] = bz_Gam*bz_Gam;

    VertexParameter vxpar_Gam;
    vxpar_Gam.setVx(vx_Gam);
    vxpar_Gam.setEvx(Evx_Gam);

    VertexFit* vtxfit_Gam = VertexFit::instance();
    vtxfit_Gam->init();
    vtxfit_Gam->AddTrack(0,  wvepTrk_Gam);
    vtxfit_Gam->AddTrack(1,  wvemTrk_Gam);
    vtxfit_Gam->AddVertex(0, vxpar_Gam,0, 1);
           
    double  Rx_Gam  = -100.;
    double  Ry_Gam  = -100.;
    double  Rvxy_Gam= -100.; 
 
    double  xconv=-100. ;
    double  yconv=-100. ;
    double  zconv=-100. ;
    double  rconv=-100. ;
   
    double  Dee_Mdc=-100. ;
    double  Dee_Bp=-100. ;

    double  xiep =  -100. ;
    double  deltaxy=-100.;
 
    double  mconv=-100.;
    double  econv= -100.;
    double  thetaconv= -100.; 
    double  costhetaconv= -100.;
    double  phiconv= -100.;
    double  angEE = -100.;
  
    if(vtxfit_Gam->Fit(0)) { 
    vtxfit_Gam->Swim(0);
    WTrackParameter wep_Gam = vtxfit_Gam->wtrk(0);
    WTrackParameter wem_Gam = vtxfit_Gam->wtrk(1);

    HepSymMatrix xem_use_Gam = vtxfit_Gam->Evx(0);
    HepPoint3D xorigin_use_Gam = vtxfit_Gam->vx(0);

   //Invariant mass distribution
    HepLorentzVector p4Ep = wep_Gam.p();
    HepLorentzVector p4Em = wem_Gam.p();
  

    HepLorentzVector gammaVector(0,0,0,0);
    gammaVector=HepLorentzVector(epTrk_Gam->p4(me)+emTrk_Gam->p4(me));

    mee_gamcon = gammaVector.m();

    Rx_Gam= xorigin_use_Gam.x();
    Ry_Gam= xorigin_use_Gam.y();
    Rvxy_Gam= sqrt(Rx_Gam*Rx_Gam + Ry_Gam*Ry_Gam);  


 GammaConv gconv = GammaConv(epTrk_Gam->helix(), emTrk_Gam->helix(),IP_Gam);

    xconv = gconv.getRX();
    yconv = gconv.getRY();
    zconv = gconv.getRZ();   
    rconv = gconv.getRXY();
    xiep  = gconv.getXiep();    
    deltaxy=gconv.getDeltaXY();

    Dee_Mdc = Get_Dee(epTrk_Gam->helix(),emTrk_Gam->helix(),5.9);
    Dee_Bp  = Get_Dee(epTrk_Gam->helix(),emTrk_Gam->helix(),3.15);

    mconv= ( (epTrk_Gam->p4(xmass[0])) + (emTrk_Gam->p4(xmass[0]))).m();
    econv= ( (epTrk_Gam->p4(xmass[0])) + (emTrk_Gam->p4(xmass[0]))).e();
    thetaconv= ( (epTrk_Gam->p4(xmass[0])) + (emTrk_Gam->p4(xmass[0]))).theta();
    costhetaconv= ( (epTrk_Gam->p4(xmass[0])) + (emTrk_Gam->p4(xmass[0]))).cosTheta();
    phiconv= ( (epTrk_Gam->p4(xmass[0])) + (emTrk_Gam->p4(xmass[0]))).phi();
    // end of gamma conversion

    angEE = p4Ep.angle(p4Em);
  
    //    cout<< " angEE "<<angEE<<endl;
    // cout<< " xiep "<<xiep<<endl;



    Rx_Gam_gamcon         = Rx_Gam;
    Ry_Gam_gamcon         = Ry_Gam;
    Rvxy_Gam_gamcon       = Rvxy_Gam; 
 
    if(xiep<10.) {
    xconv_gamcon         = xconv;
    yconv_gamcon         = yconv;
    rconv_gamcon         = rconv;
    xconv1_gamcon        = xconv;
    yconv1_gamcon        = yconv;
    rconv1_gamcon        = rconv;
  

    } else {

    xconv_gamcon         = Rx_Gam;
    yconv_gamcon         = Ry_Gam;
    rconv_gamcon         = Rvxy_Gam;
    xconv2_gamcon        = Rx_Gam;
    yconv2_gamcon        = Ry_Gam;
    rconv2_gamcon        = Rvxy_Gam;
    }

    zconv_gamcon         = zconv; 
    Dee_Mdc_gamcon       = Dee_Mdc;
    Dee_Bp_gamcon        = Dee_Bp;
    xiep_gamcon           = xiep;
    deltaxy_gamcon        = deltaxy;
 
    mconv_gamcon          = mconv;
    econv_gamcon          = econv;
    thetaconv_gamcon      = thetaconv; 
    costhetaconv_gamcon   = costhetaconv;
    phiconv_gamcon        = phiconv;
    angEE_gamcon          = angEE;


    }



 ///////////////////// end of the gamma conversion calculation  ///////////////////////////////

      } else {
   return StatusCode::SUCCESS;
      }
   Ncut4++;

 
   Hep3Vector MisTrkGam(misTrkGampx,misTrkGampy,misTrkGampz);

   double Angle = 9999;

   double minAngle       = 3.14;
   int bestTrackNumber = -1;
   double gammom = 9999;
  for(int i = 0; i < nGam; i++) {

   HepLorentzVector photon;
   photon.setRThetaPhi(m_energy[i], m_theta[i], m_phi[i]);
   photon.setE(m_energy[i]); 

  double angleTest = MisTrkGam.angle(photon); 

  if(angleTest <= minAngle)
     {
   minAngle             =  angleTest;
   Angle                =  minAngle;

   game                 =  m_energy[i]; 
   gammom               =  photon.vect().mag();
 
   gamtheta             =  m_theta[i];
   gamphi               =  m_phi[i];

   _A42                 =  m_a42Moment[i];
   _lat                 =  m_latMoment[i];
   _e3x3                =  m_e3x3[i];
   _e5x5                =  m_e5x5[i];
   _A20                 =  m_a20Moment[i];
 
   gamx                 =  m_x[i]; 
   gamy                 =  m_y[i];
   gamz                 =  m_z[i];
   gamdx                =  m_dx[i];
   gamdy                =  m_dy[i];
   gamdz                =  m_dz[i];
   gamdtheta            =  m_dtheta[i];
   gamdphi              =  m_dphi[i];
   gamdE                =  m_dE[i];
   gameseed             =  m_eSeed[i];
   gamesecondMoment     =  m_secondMoment[i];
   gametime             =  m_time[i];
   gamemodule           =  m_module[i];
   gamecellId           =  m_cellId[i];
   gamestatus           =  m_status[i];
   gamenumHits          =  m_numHits[i];
   misGamTrkanglephoton   =  angleTest; 

   bestTrackNumber        =  iGam[i];
     }}

  if(bestTrackNumber == -1) {
  return StatusCode::SUCCESS;
   }
   Ncut5++;



   int photLab = -1;
  for(int i =0; i< nGam; i++)
    {
  if((m_energy[i] > 0.025 && TMath::Abs(TMath::Cos(m_theta[i])) < 0.80) || (m_energy[i] > 0.05 && TMath::Abs(TMath::Cos(m_theta[i])) > 0.86 && TMath::Abs(TMath::Cos(m_theta[i])) < 0.92)) 
    {
  if(m_energy[i] > 0.025 && m_time[i] >=0 && m_time[i] <= 14)
    {
  photLab = 1;
  // cout <<  m_energy[i] << "        " << m_time[i] << endl;

    }}}


  Goodphotlab = photLab;

   RecEmcID id = Identifier(gamecellId);
   m_digi_npart                       = EmcID::barrel_ec(id);
    m_digi_ntheta = EmcID::theta_module(id);
    m_digi_nphi = EmcID::phi_module(id);


  m_tuple1->write();


}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
StatusCode Jpsdecthreepi::finalize() {

  cout<<"total number:              "    <<Ncut0<<endl;
  cout<<"nGood==4, nCharge==0:      "    <<Ncut1<<endl;
  cout<<"Pass Pid:                  "    <<Ncut2<<endl;
  cout<<"e+e- vertex fit:           "    <<Ncut3<<endl;
  cout<<"4C Kinematic fit           "    <<Ncut4<<endl;  
  cout<<"Good pi+pi-e+e-gamma selection  " <<Ncut5<<endl;  



  MsgStream log(msgSvc(), name());
  log << MSG::INFO << "in finalize()" << endmsg;
  return StatusCode::SUCCESS;
}





HepPoint3D Jpsdecthreepi::Get_HelixCenter(HepVector helix){

    double bField = VertexFitBField::instance()->getBFieldZ(HepPoint3D(helix[0]*cos(helix[1]), helix[0]*sin(helix[1]), helix[3]));
    //  int charge = helix[2] > 0 ? +1: -1;
    int charge = 1;
    const double alpha = -0.00299792458;
    double a = alpha * bField * charge;
    double pxy = charge/helix[2];
    double rad = pxy/a;
    double x = (helix[0] + rad) * cos(helix[1]);
    double y = (helix[0] + rad) * sin(helix[1]);
    double z = 0.0;
    return HepPoint3D(x, y, z);
}

double Jpsdecthreepi::Get_HelixRadius(HepVector helix){
    double bField = VertexFitBField::instance()->getBFieldZ(HepPoint3D(helix[0]*cos(helix[1]), helix[0]*sin(helix[1]), helix[3])); 
    int charge = 1;
    const double alpha = -0.00299792458;
    double a = alpha * bField * charge;
    double pxy = charge/helix[2];
    double radius = pxy/a;
    return radius;
}

HepPoint3D Jpsdecthreepi::intersections(HepVector helix,double r){
    double xc, yc,rc;
    xc = Get_HelixCenter(helix).x();
    yc = Get_HelixCenter(helix).y();
    rc = Get_HelixRadius(helix);
    double a,b,c; 
    double d0 =helix[0];
    a = r; // radius of Mdc or Beam Pipe 
    b = d0 + rc;
    c = rc;
    double dphi = acos((a*a-b*b-c*c)/(-2.*b*c));
    double fltlen = dphi * rc;
    double phi  = acos((c*c-a*a-b*b)/(-2.*a*b));
    double x    = r*cos(phi+helix[1]);
    double y    = r*sin(phi+helix[1]);
    double z    = helix[3]+fltlen*helix[4];
    return HepPoint3D(x, y, z);
}

double Jpsdecthreepi::Get_Dee(HepVector helixe,HepVector helixp,double r){
    HepPoint3D Inter_e = intersections(helixe,r);
    HepPoint3D Inter_p = intersections(helixp,r);
    double Dee = sqrt(pow((Inter_e.x()-Inter_p.x()),2)+pow((Inter_e.y()-Inter_p.y()),2));
    return Dee;
}








