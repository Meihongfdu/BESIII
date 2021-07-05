#include "StoeeLAlg/StoeeLAlg.h"
using std::cout;
using std::endl;

StoeeLAlg::StoeeLAlg(const std::string& name, ISvcLocator* pSvcLocator)
    : Algorithm(name, pSvcLocator)
{
    declareProperty("DoMatch", m_doMatch = false);
    declareProperty("Mother", m_Mother = 100443);
    declareProperty("BeamE", m_BeamE = 3.686);
    declareProperty("FillMCInf", m_fillMCInf = true);
    declareProperty("MinChargedTracks", m_minTrks = 0);
    declareProperty("MaxChargedTracks", m_maxTrks = 100);
    declareProperty("MinShowers", m_minShowers = 0);
    declareProperty("MaxShowers", m_maxShowers = 100);
    declareProperty("FID", m_fid);
    declareProperty("Debug", m_debug = true);
    declareProperty("InfL", m_InfL = 0);
}

StatusCode StoeeLAlg::initialize()
{
    //   vector<int> index;
    //   for(int i =0 ; i < m_fid.size() ; i++) {
    //       index.push_back(0) ;
    //       for(int j =0 ; j <= i ; j++) {
    //           if(m_fid[i]==m_fid[j]) index[i]++ ;
    //       }
    //   }
    MsgStream log(msgSvc(), name());
    log << MSG::INFO << "BENCHMARK: " << currentDT() << endmsg;
    std::cout << "BENCHMARK: " << currentDT() << std::endl;
    log << MSG::INFO << "in initialize()" << endmsg;

    _parname = this->NamePar(m_fid);
    StatusCode status;
    NTuplePtr tuple(ntupleSvc(), "FILE/sig");
    if (tuple) {
        tp = tuple;
    } else {
        tp = ntupleSvc()->book("FILE/sig", CLID_ColumnWiseTuple, "Psi(2S)");
        if (tp) {
            //--------tot-----------
            tp->addItem("run", m_run);
            tp->addItem("events", m_events);
            tp->addItem("tracks", m_tracks);
            tp->addItem("showers", m_NShowers);
            tp->addItem("beamE", m_beamE);
            ParticleInf pInf;
            pInf.SetChildren(m_fid);
            for (unsigned i = 0; i < m_fid.size(); ++i) {
                char name[40];
                if (abs(m_fid[i]) == 211 || abs(m_fid[i]) == 321 ||
                    abs(m_fid[i]) == 11 || abs(m_fid[i]) == 2212 ||
                    abs(m_fid[i]) == 22)
                    continue;
                // add mass term
                sprintf(name, "m%s", this->_parname[i].c_str());
                cout << i << "\t" << name << endl;
                tp->addItem(name, m_mass[i]);
            }

            for (unsigned i = 0; i < m_fid.size(); ++i) {
                char name[40];
                if (abs(m_fid[i]) == 11 || abs(m_fid[i]) == 211 ||
                    abs(m_fid[i]) == 321 || abs(m_fid[i]) == 2212 ||
                    abs(m_fid[i]) == 13) {
                    // add Rxy
                    sprintf(name, "rxy%s", this->_parname[i].c_str());
                    cout << i << "\t" << name << endl;
                    tp->addItem(name, m_Rxy[i]);

                    // add Vz0
                    sprintf(name, "vz0%s", this->_parname[i].c_str());
                    cout << i << "\t" << name << endl;
                    tp->addItem(name, m_Vz0[i]);

                    // add CosTheta
                    sprintf(name, "cost%s", this->_parname[i].c_str());
                    cout << i << "\t" << name << endl;
                    tp->addItem(name, m_CosTheta[i]);
                }
            }

            for (unsigned i = 0; i < m_fid.size(); ++i) {
                char name[40];
                sprintf(name, "P4%s", this->_parname[i].c_str());
                cout << i << "\t" << name << endl;
                tp->addItem(name, 4, m_p4[i]);
            }

            for (unsigned i = 0; i < m_fid.size(); i++) {
                if (!(m_fid[i] == 111 || m_fid[i] == 221)) continue;
                char name[40];
                sprintf(name, "chisq%s", this->_parname[i].c_str());
                cout << i << "\t" << name << endl;
                tp->addItem(name, m_chisqs[i]);
            }
            for (unsigned i = 0; i < m_fid.size(); i++) {
                if (!(m_fid[i] == 22)) continue;
                char name[40];
                sprintf(name, "showershape%s", this->_parname[i].c_str());
                // cout<<i<<"\t"<<name<<endl;
                // tp->addItem(name,      m_showershape[i]);
            }
            for (unsigned i = 0; i < m_fid.size(); i++) {
                if (!(m_fid[i] == 22)) continue;
                char name[40];
                sprintf(name, "showertime%s", this->_parname[i].c_str());
                // cout<<i<<"\t"<<name<<endl;
                // tp->addItem(name,      m_showertime[i]);
            }
            vector<int> eleIds = pInf.GammaCov();
            if (m_InfL > 0) {
                cout << "#gamma coversion\t" << eleIds.size() / 2 << endl;
            }
            for (unsigned i = 0; i < eleIds.size(); i += 2) {
                char name[100], nm2[20], nm3[20];
                sprintf(name, "RxyGammaCov%d", i);
                sprintf(nm2, "Rx%d", i);
                sprintf(nm3, "Ry%d", i);
                tp->addItem(name, m_GammaCov_Rxy[i / 2]);
                tp->addItem(nm2, m_GammaCov_Rx[i / 2]);
                tp->addItem(nm3, m_GammaCov_Ry[i / 2]);
                cout << "Gamma Gov\t" << name << endl;
            }
            tp->addItem("helixEp", 5, m_helixEp);
            tp->addItem("helixEm", 5, m_helixEm);
            tp->addItem("match", m_match);
            tp->addItem("chisq", m_chisq);
            // information of Lambda
            int numLam = -1;
            for (unsigned i = 0; i < m_fid.size(); ++i) {
                if (abs(m_fid[i]) != 3122) continue;
                numLam += 1;
                if (numLam > 4) {
                    cout << "Error :too much Lambda!!!" << endl;
                    return StatusCode::FAILURE;
                }
                char name[40];
                sprintf(name, "mLam%s", _parname[i].c_str());
                tp->addItem(name, m_mLamCol[numLam]);
                cout << "addItem " << name << endl;

                sprintf(name, "Rlam%s", _parname[i].c_str());
                tp->addItem(name, m_RLamCol[numLam]);
                cout << "addItem " << name << endl;

                sprintf(name, "dL%s", _parname[i].c_str());
                tp->addItem(name, m_dLamCol[numLam]);
                cout << "addItem " << name << endl;

                sprintf(name, "chisq1%s", _parname[i].c_str());
                tp->addItem(name, m_chisq1LamCol[numLam]);
                cout << "addItem " << name << endl;

                sprintf(name, "chisq2%s", _parname[i].c_str());
                tp->addItem(name, m_chisq2LamCol[numLam]);
                cout << "addItem " << name << endl;

                // Proton Info from Lambda
                sprintf(name, "p4Pr%s", _parname[i].c_str());
                tp->addItem(name, 4, m_p4PrLamCol[numLam]);
                cout << "addItem " << name << endl;

                sprintf(name, "rxyPr%s", _parname[i].c_str());
                tp->addItem(name, m_RxyPrLam[numLam]);
                cout << "addItem " << name << endl;

                sprintf(name, "vz0Pr%s", _parname[i].c_str());
                tp->addItem(name, m_Vz0PrLam[numLam]);
                cout << "addItem " << name << endl;

                sprintf(name, "costPr%s", _parname[i].c_str());
                tp->addItem(name, m_CosThetaPrLam[numLam]);
                cout << "addItem " << name << endl;

                // Pion Info frm Lambda
                sprintf(name, "P4Pi%s", _parname[i].c_str());
                tp->addItem(name, 4, m_p4PiLamCol[numLam]);
                cout << "addItem " << name << endl;

                sprintf(name, "rxyPi%s", _parname[i].c_str());
                tp->addItem(name, m_RxyPiLam[numLam]);
                cout << "addItem " << name << endl;

                sprintf(name, "vz0Pi%s", _parname[i].c_str());
                tp->addItem(name, m_Vz0PiLam[numLam]);
                cout << "addItem " << name << endl;

                sprintf(name, "costPi%s", _parname[i].c_str());
                tp->addItem(name, m_CosThetaPiLam[numLam]);
                cout << "addItem " << name << endl;
            }
            // the kinematic result
            for (unsigned i = 0; i < m_fid.size(); i++) {
                char name[40];
                sprintf(name, "P4Fit%s", this->_parname[i].c_str());
                cout << i << "\t" << name << endl;
                tp->addItem(name, 4, m_fitP4[i]);
            }

            tp->addItem("indexmc", tag_indexmc, 0, 100);
            tp->addIndexedItem("pdgid", tag_indexmc, tag_pdgid);
            tp->addIndexedItem("motheridx", tag_indexmc, tag_motheridx);

        } else {
            log << MSG::ERROR << "    Cannot sig N-tuple:" << long(tp)
                << endmsg;
            return StatusCode::FAILURE;
        }
    }

    NTuplePtr mctuple(ntupleSvc(), "FILE/mc");

    if (mctuple) {
        mctp = mctuple;
    }

    else {
        mctp = ntupleSvc()->book("FILE/mc", CLID_ColumnWiseTuple,
                                 "mc decay chain");

        if (mctp) {
            ParticleInf pInf;
            pInf.SetChildren(m_fid);
            for (unsigned i = 0; i < m_fid.size(); i++) {
                char name[40];
                sprintf(name, "P4%s", _parname[i].c_str());
                cout << i << "\t" << name << endl;
                mctp->addItem(name, 4, m_truthP4[i]);
            }
            mctp->addItem("indexmc", m_indexmc, 0, 100);
            mctp->addIndexedItem("pdgid", m_indexmc, m_pdgid);
            mctp->addIndexedItem("motheridx", m_indexmc, m_motheridx);
        }

        else {
            log << MSG::ERROR << " cannot book mcds:" << long(mctp) << endmsg;
            return StatusCode::FAILURE;
        }
    }

    IMcDecayModeSvc* i_McDecayModeSvc;
    StatusCode sc_McDecayModeSvc = service("McDecayModeSvc", i_McDecayModeSvc);

    if (sc_McDecayModeSvc.isFailure()) {
        log << MSG::FATAL << "could not load McDecayModeSvc" << endmsg;
        return sc_McDecayModeSvc;
    }
    m_svc = dynamic_cast<McDecayModeSvc*>(i_McDecayModeSvc);

    log << MSG::INFO << "successfully return from initialize()" << endmsg;
    // init match service
    IMCTruthMatchSvc* i_matchSvc;
    StatusCode sc_MC = service("MCTruthMatchSvc", i_matchSvc);
    if (sc_MC.isFailure()) {
        cout << "could not load MCTruthMatchSvc!" << endl;
        return 0;
    }
    matchSvc = dynamic_cast<MCTruthMatchSvc*>(i_matchSvc);
    return StatusCode::SUCCESS;
}

StatusCode StoeeLAlg::finalize()
{
    MsgStream log(msgSvc(), name());
    log << MSG::INFO << "BENCHMARK: " << currentDT() << endmsg;
    std::cout << "BENCHMARK: " << currentDT() << std::endl;

    return StatusCode::SUCCESS;
}
vector<string> StoeeLAlg::NamePar(vector<int> _fid)
{
    vector<string> _name;
    vector<int> index;
    for (unsigned i = 0; i < m_fid.size(); i++) {
        index.push_back(0);
        for (unsigned j = 0; j <= i; j++) {
            if (_fid[i] == _fid[j]) index[i]++;
        }
    }
    ParticleInf pInf;
    pInf.SetChildren(_fid);
    string name(""), dd;
    for (unsigned i = 0; i < _fid.size(); ++i) {
        name = pInf.Name(_fid[i]);
        if (index[i] > 1) {
            stringstream ss;
            ss << index[i];
            ss >> dd;
            name += dd;
        }
        _name.push_back(name);
    }
    return _name;
}
