----------> uses
# use BesPolicy BesPolicy-* 
#   use BesCxxPolicy BesCxxPolicy-* 
#     use GaudiPolicy v*  (no_version_directory)
#       use LCG_Settings *  (no_version_directory)
#       use Python * LCG_Interfaces (no_auto_imports) (no_version_directory) (native_version=2.7.3)
#         use LCG_Configuration v*  (no_version_directory)
#         use LCG_Settings v*  (no_version_directory)
#       use tcmalloc * LCG_Interfaces (no_auto_imports) (no_version_directory) (native_version=1.7p3)
#         use LCG_Configuration v*  (no_version_directory)
#         use LCG_Settings v*  (no_version_directory)
#         use libunwind v* LCG_Interfaces (no_version_directory) (native_version=5c2cade)
#           use LCG_Configuration v*  (no_version_directory)
#           use LCG_Settings v*  (no_version_directory)
#   use BesFortranPolicy BesFortranPolicy-* 
#     use LCG_Settings v*  (no_version_directory)
# use GaudiInterface GaudiInterface-* External
#   use GaudiKernel *  (no_version_directory)
#     use GaudiPolicy *  (no_version_directory)
#     use Reflex * LCG_Interfaces (no_version_directory)
#       use LCG_Configuration v*  (no_version_directory)
#         use LCG_Platforms *  (no_version_directory)
#       use LCG_Settings v*  (no_version_directory)
#       use ROOT v* LCG_Interfaces (no_auto_imports) (no_version_directory) (native_version=5.34.09)
#     use Boost * LCG_Interfaces (no_version_directory) (native_version=1.50.0_python2.7)
#       use LCG_Configuration v*  (no_version_directory)
#       use LCG_Settings v*  (no_version_directory)
#       use Python v* LCG_Interfaces (no_auto_imports) (no_version_directory) (native_version=2.7.3)
#   use GaudiSvc *  (no_version_directory)
#     use GaudiKernel *  (no_version_directory)
#     use CLHEP * LCG_Interfaces (no_auto_imports) (no_version_directory) (native_version=2.0.4.5)
#     use Boost * LCG_Interfaces (no_auto_imports) (no_version_directory) (native_version=1.50.0_python2.7)
#     use ROOT * LCG_Interfaces (no_auto_imports) (no_version_directory) (native_version=5.34.09)
# use McTruth McTruth-* Event
#   use BesPolicy BesPolicy-01-* 
#   use EventModel EventModel-* Event
#     use BesPolicy BesPolicy-* 
#     use GaudiInterface GaudiInterface-* External
#   use GaudiInterface GaudiInterface-01-* External
#   use Identifier Identifier-* DetectorDescription
#     use BesPolicy BesPolicy-* 
#   use RelTable RelTable-* Event
#     use BesPolicy BesPolicy-01-* 
#     use GaudiInterface GaudiInterface-01-* External
# use EventModel EventModel-* Event
# use EvtRecEvent EvtRecEvent-* Event
#   use BesPolicy BesPolicy-* 
#   use GaudiInterface GaudiInterface-* External
#   use BesCLHEP BesCLHEP-* External
#     use CLHEP v* LCG_Interfaces (no_version_directory) (native_version=2.0.4.5)
#       use LCG_Configuration v*  (no_version_directory)
#       use LCG_Settings v*  (no_version_directory)
#     use HepMC * LCG_Interfaces (no_version_directory) (native_version=2.06.08)
#       use LCG_Configuration v*  (no_version_directory)
#       use LCG_Settings v*  (no_version_directory)
#     use HepPDT * LCG_Interfaces (no_version_directory) (native_version=2.06.01)
#       use LCG_Configuration v*  (no_version_directory)
#       use LCG_Settings v*  (no_version_directory)
#     use BesExternalArea BesExternalArea-* External
#   use EventModel EventModel-* Event
#   use EvTimeEvent EvTimeEvent-* Event
#     use BesPolicy BesPolicy-01-* 
#     use GaudiInterface GaudiInterface-01-* External
#     use BesCLHEP BesCLHEP-* External
#     use MdcGeomSvc MdcGeomSvc-* Mdc
#       use BesPolicy BesPolicy-01-* 
#       use GaudiInterface GaudiInterface-* External
#       use calibUtil * Calibration
#         use GaudiInterface GaudiInterface-01-* External
#         use facilities * Calibration
#           use BesPolicy BesPolicy-* 
#         use xmlBase * Calibration
#           use BesPolicy * 
#           use XercesC * LCG_Interfaces (no_version_directory) (native_version=3.1.1p1)
#             use LCG_Configuration v*  (no_version_directory)
#             use LCG_Settings v*  (no_version_directory)
#           use facilities * Calibration
#         use rdbModel * Calibration
#           use BesPolicy * 
#           use facilities * Calibration
#           use xmlBase * Calibration
#           use MYSQL * External
#             use mysql * LCG_Interfaces (no_version_directory) (native_version=5.5.14)
#               use LCG_Configuration v*  (no_version_directory)
#               use LCG_Settings v*  (no_version_directory)
#         use BesROOT BesROOT-00-* External
#           use CASTOR v* LCG_Interfaces (no_version_directory) (native_version=2.1.13-6)
#             use LCG_Configuration v*  (no_version_directory)
#             use LCG_Settings v*  (no_version_directory)
#           use ROOT v* LCG_Interfaces (no_version_directory) (native_version=5.34.09)
#             use LCG_Configuration v*  (no_version_directory)
#             use LCG_Settings v*  (no_version_directory)
#             use GCCXML v* LCG_Interfaces (no_auto_imports) (no_version_directory) (native_version=0.9.0_20120309p2)
#               use LCG_Configuration v*  (no_version_directory)
#               use LCG_Settings v*  (no_version_directory)
#             use Python v* LCG_Interfaces (no_auto_imports) (no_version_directory) (native_version=2.7.3)
#             use xrootd v* LCG_Interfaces (no_version_directory) (native_version=3.2.7)
#               use LCG_Configuration v*  (no_version_directory)
#               use LCG_Settings v*  (no_version_directory)
#         use DatabaseSvc DatabaseSvc-* Database
#           use BesPolicy BesPolicy-* 
#           use GaudiInterface GaudiInterface-* External
#           use mysql * LCG_Interfaces (no_version_directory) (native_version=5.5.14)
#           use sqlite * LCG_Interfaces (no_version_directory) (native_version=3070900)
#             use LCG_Configuration v*  (no_version_directory)
#             use LCG_Settings v*  (no_version_directory)
#           use BesROOT * External
#       use CalibData * Calibration
#         use facilities facilities-* Calibration
#         use GaudiInterface * External
#         use BesROOT BesROOT-00-* External
#       use EventModel EventModel-* Event
#     use RelTable RelTable-* Event
#     use EventModel EventModel-* Event
#     use Identifier Identifier-* DetectorDescription
#   use MdcRecEvent MdcRecEvent-* Mdc
#     use BesPolicy BesPolicy-01-* 
#     use GaudiInterface GaudiInterface-01-* External
#     use MdcGeomSvc MdcGeomSvc-* Mdc
#     use RelTable RelTable-* Event
#     use EventModel EventModel-* Event
#     use Identifier Identifier-* DetectorDescription
#     use DstEvent DstEvent-* Event
#       use BesPolicy BesPolicy-* 
#       use GaudiInterface GaudiInterface-* External
#       use BesCLHEP BesCLHEP-* External
#       use EventModel EventModel-* Event
#   use TofRecEvent TofRecEvent-* Tof
#     use BesPolicy BesPolicy-01-* 
#     use GaudiInterface GaudiInterface-01-* External
#     use Identifier Identifier-* DetectorDescription
#     use EventModel EventModel-* Event
#     use DstEvent * Event
#   use EmcRecEventModel EmcRecEventModel-* Emc
#     use BesPolicy BesPolicy-* 
#     use Identifier Identifier-* DetectorDescription
#     use BesCLHEP BesCLHEP-* External
#     use EventModel EventModel-* Event
#     use DstEvent DstEvent-* Event
#     use EmcRecGeoSvc EmcRecGeoSvc-* Emc
#       use BesPolicy BesPolicy-* 
#       use Identifier Identifier-* DetectorDescription
#       use ROOTGeo ROOTGeo-* DetectorDescription
#         use BesPolicy BesPolicy-01-* 
#         use GaudiInterface GaudiInterface-* External
#         use BesCLHEP BesCLHEP-* External
#         use BesROOT BesROOT-* External
#         use XercesC * LCG_Interfaces (no_version_directory) (native_version=3.1.1p1)
#         use GdmlToRoot GdmlToRoot-* External
#           use BesExternalArea BesExternalArea-* External
#           use BesROOT BesROOT-* External
#         use GdmlManagement GdmlManagement-* DetectorDescription
#           use BesExternalArea BesExternalArea-* External
#       use BesCLHEP BesCLHEP-* External
#       use GaudiInterface GaudiInterface-* External
#   use MucRecEvent MucRecEvent-* Muc
#     use BesPolicy BesPolicy-01-* 
#     use GaudiInterface GaudiInterface-01-* External
#     use Identifier Identifier-* DetectorDescription
#     use EventModel EventModel-* Event
#     use ExtEvent ExtEvent-* Event
#       use BesPolicy BesPolicy-01-* 
#       use GaudiInterface GaudiInterface-01-* External
#       use BesCLHEP BesCLHEP-* External
#       use EventModel EventModel-* Event
#       use DstEvent DstEvent-* Event
#     use MucGeomSvc MucGeomSvc-* Muc
#       use BesPolicy BesPolicy-01-* 
#       use GaudiInterface GaudiInterface-* External
#       use Identifier Identifier-* DetectorDescription
#       use ROOTGeo ROOTGeo-* DetectorDescription
#       use BesCLHEP BesCLHEP-* External
#       use BesROOT BesROOT-* External
#       use XercesC * LCG_Interfaces (no_version_directory) (native_version=3.1.1p1)
#       use GdmlToRoot GdmlToRoot-* External
#       use G4Geo G4Geo-* DetectorDescription
#         use BesPolicy BesPolicy-01-* 
#         use GaudiInterface GaudiInterface-* External
#         use BesCLHEP BesCLHEP-* External
#         use BesGeant4 BesGeant4-* External
#           use BesExternalArea BesExternalArea-00-* External
#           use BesCLHEP BesCLHEP-00-* External
#         use XercesC * LCG_Interfaces (no_version_directory) (native_version=3.1.1p1)
#         use GdmlToG4 GdmlToG4-* External
#           use BesExternalArea BesExternalArea-* External
#           use BesGeant4 BesGeant4-* External
#           use XercesC * LCG_Interfaces (no_version_directory) (native_version=3.1.1p1)
#         use GdmlManagement GdmlManagement-* DetectorDescription
#         use Identifier Identifier-* DetectorDescription
#         use SimUtil SimUtil-* Simulation/BOOST
#           use BesPolicy BesPolicy-01-* 
#           use BesGeant4 BesGeant4-00-* External
#     use DstEvent DstEvent-* Event
#   use ExtEvent ExtEvent-* Event
#   use DstEvent DstEvent-* Event
# use ParticleID ParticleID-* Analysis
#   use BesPolicy BesPolicy-01-* 
#   use GaudiInterface GaudiInterface-01-* External
#   use DstEvent DstEvent-* Event
#   use BesROOT BesROOT-* External
#   use EvtRecEvent EvtRecEvent-* Event
#   use MdcRecEvent MdcRecEvent-* Mdc
#   use TofRecEvent TofRecEvent-* Tof
#   use EmcRecEventModel EmcRecEventModel-* Emc
#   use MucRecEvent MucRecEvent-* Muc
#   use ExtEvent ExtEvent-* Event
# use VertexFit VertexFit-* Analysis
#   use BesPolicy BesPolicy-01-* 
#   use GaudiInterface GaudiInterface-* External
#   use BesCLHEP BesCLHEP-* External
#   use MYSQL MYSQL-* External
#   use DstEvent DstEvent-* Event
#   use MdcRecEvent MdcRecEvent-* Mdc
#   use EmcRecEventModel EmcRecEventModel-* Emc
#   use MagneticField MagneticField-* 
#     use BesPolicy BesPolicy-01-* 
#     use GaudiInterface GaudiInterface-* External
#     use BesCLHEP * External
#     use BesROOT * External
#     use EventModel EventModel-* Event
#     use rdbModel * Calibration
#     use DatabaseSvc * Database
#     use BesTimerSvc BesTimerSvc-* Utilities
#       use BesPolicy BesPolicy-* 
#       use GaudiInterface GaudiInterface-* External
#   use EventModel EventModel-* Event
#   use EvtRecEvent EvtRecEvent-* Event
#   use DatabaseSvc DatabaseSvc-* Database
# use DataBaseReader DataBaseReader-* 
#   use BesPolicy BesPolicy-* 
#   use GaudiInterface GaudiInterface-* External
#   use DstEvent DstEvent-* Event
#   use EventModel EventModel-* Event
#   use EvtRecEvent EvtRecEvent-* Event
#   use McTruth McTruth-* Event
#   use VertexFit VertexFit-* Analysis
#   use ParticleID ParticleID-* Analysis
#   use BesROOT BesROOT-00-* External
# use McDecayModeSvc McDecayModeSvc-* 
#   use BesPolicy BesPolicy-01-* 
#   use GaudiInterface GaudiInterface-01-* External
#   use BesCLHEP BesCLHEP-* External
#   use McTruth McTruth-* Event
# use GammaConv GammaConv-* 
#   use BesPolicy BesPolicy-01-* 
#   use GaudiInterface GaudiInterface-01-* External
#   use GaudiAlg v*  (no_version_directory)
#     use GaudiKernel *  (no_version_directory)
#     use GaudiUtils *  (no_version_directory)
#       use GaudiKernel *  (no_version_directory)
#       use ROOT * LCG_Interfaces (no_version_directory) (native_version=5.34.09)
#       use AIDA * LCG_Interfaces (no_auto_imports) (no_version_directory) (native_version=3.2.1)
#         use LCG_Configuration v*  (no_version_directory)
#         use LCG_Settings v*  (no_version_directory)
#       use Boost * LCG_Interfaces (no_auto_imports) (no_version_directory) (native_version=1.50.0_python2.7)
#       use uuid * LCG_Interfaces (no_auto_imports) (no_version_directory) (native_version=1.42)
#         use LCG_Configuration v*  (no_version_directory)
#         use LCG_Settings v*  (no_version_directory)
#       use Reflex * LCG_Interfaces (no_auto_imports) (no_version_directory)
#       use XercesC * LCG_Interfaces (no_auto_imports) (no_version_directory) (native_version=3.1.1p1)
#     use ROOT * LCG_Interfaces (no_version_directory) (native_version=5.34.09)
#     use AIDA * LCG_Interfaces (no_auto_imports) (no_version_directory) (native_version=3.2.1)
#     use Boost * LCG_Interfaces (no_auto_imports) (no_version_directory) (native_version=1.50.0_python2.7)
#   use BesCLHEP BesCLHEP-* External
#   use MYSQL MYSQL-* External
#   use McTruth McTruth-* Event
#   use DstEvent DstEvent-* Event
#   use EventModel EventModel-* Event
#   use EvtRecEvent EvtRecEvent-* Event
#   use BesROOT BesROOT-00-* External
#   use MdcRawEvent MdcRawEvent-* Mdc
#     use BesPolicy BesPolicy-* 
#     use GaudiInterface GaudiInterface-01-* External
#     use RawEvent RawEvent-* Event
#       use BesPolicy BesPolicy-* 
#       use GaudiInterface GaudiInterface-01-* External
#       use Identifier Identifier-* DetectorDescription
#       use EventModel EventModel-* Event
#     use EventModel EventModel-* Event
#   use MdcRecEvent MdcRecEvent-* Mdc
#   use EmcRecEventModel EmcRecEventModel-* Emc
#   use MagneticField MagneticField-* 
#   use VertexFit VertexFit-* Analysis
# use MCTruthMatchSvc MCTruthMatchSvc-* 
#   use BesPolicy BesPolicy-* 
#   use GaudiInterface GaudiInterface-01-* External
#   use EvtRecEvent EvtRecEvent-* Event
#   use EventNavigator EventNavigator-* Event
#     use BesPolicy * 
#     use GaudiInterface * External
#     use McTruth McTruth-* Event
#     use EmcRecEventModel * Emc
#     use MdcRecEvent * Mdc
#     use MdcRawEvent * Mdc
#     use MucRecEvent * Muc
#     use TofRecEvent * Tof
#   use McTruth McTruth-* Event
#   use MdcRecEvent MdcRecEvent-* Mdc
#   use McDecayModeSvc McDecayModeSvc-* 
# use HadronInfo HadronInfo-* 
#   use BesPolicy BesPolicy-01-* 
#   use GaudiInterface GaudiInterface-01-* External
#   use CERNLIB CERNLIB-* External
#     use cernlib v* LCG_Interfaces (no_version_directory) (native_version=2006a)
#       use LCG_Configuration v*  (no_version_directory)
#       use LCG_Settings v*  (no_version_directory)
#       use blas v* LCG_Interfaces (no_version_directory) (native_version=20110419)
#         use LCG_Configuration v*  (no_version_directory)
#         use LCG_Settings v*  (no_version_directory)
#       use lapack v* LCG_Interfaces (no_version_directory) (native_version=3.4.0)
#         use LCG_Configuration v*  (no_version_directory)
#         use LCG_Settings v*  (no_version_directory)
#         use blas v* LCG_Interfaces (no_version_directory) (native_version=20110419)
#     use CASTOR v* LCG_Interfaces (no_version_directory) (native_version=2.1.13-6)
#     use Xt * External (native_version=X11R6)
#   use DstEvent DstEvent-* Event
#   use McTruth McTruth-* Event
#   use BesROOT BesROOT-* External
#   use CERNLIB CERNLIB-* External
#   use ReconEvent ReconEvent-* Event
#     use BesPolicy BesPolicy-* 
#     use GaudiInterface GaudiInterface-* External
#     use BesCLHEP BesCLHEP-* External
#     use EventModel EventModel-* Event
#     use ExtEvent ExtEvent-* Event
#   use RawDataProviderSvc RawDataProviderSvc-* Event
#     use BesPolicy BesPolicy-01-* 
#     use RootPolicy RootPolicy-* 
#       use BesPolicy BesPolicy-* 
#       use BesROOT BesROOT-00-* External
#     use GaudiInterface GaudiInterface-01-* External
#     use BesCLHEP BesCLHEP-* External
#     use DetVerSvc DetVerSvc-* Utilities
#       use BesPolicy BesPolicy-* 
#       use GaudiInterface GaudiInterface-* External
#       use mysql * LCG_Interfaces (no_version_directory) (native_version=5.5.14)
#     use MdcRawEvent MdcRawEvent-* Mdc
#     use MdcRecEvent MdcRecEvent-* Mdc
#     use TofRawEvent TofRawEvent-* Tof
#       use BesPolicy BesPolicy-* 
#       use GaudiInterface GaudiInterface-01-* External
#       use RawEvent RawEvent-* Event
#       use EventModel EventModel-* Event
#     use TofCaliSvc TofCaliSvc-* Tof
#       use BesPolicy BesPolicy-01-* 
#       use GaudiInterface GaudiInterface-* External
#       use calibUtil * Calibration
#       use CalibData * Calibration
#       use CalibSvc * Calibration
#         use CalibMySQLCnv * Calibration/CalibSvc
#           use BesPolicy * 
#           use calibUtil * Calibration
#           use CalibData * Calibration
#           use GaudiInterface * External
#           use MYSQL MYSQL-00-* External
#           use CalibDataSvc * Calibration/CalibSvc
#             use BesPolicy * 
#             use BesROOT * External
#             use calibUtil * Calibration
#             use CalibData * Calibration
#             use DstEvent DstEvent-* Event
#             use EventModel EventModel-* Event
#             use GaudiKernel *  (no_version_directory)
#         use CalibROOTCnv * Calibration/CalibSvc
#           use BesPolicy * 
#           use calibUtil * Calibration
#           use CalibData * Calibration
#           use GaudiInterface * External
#           use BesROOT BesROOT-00-* External
#           use EventModel EventModel-* Event
#           use CalibDataSvc * Calibration/CalibSvc
#           use CalibMySQLCnv * Calibration/CalibSvc
#         use CalibDataSvc * Calibration/CalibSvc
#         use CalibTreeCnv * Calibration/CalibSvc
#           use BesPolicy * 
#           use calibUtil * Calibration
#           use CalibData * Calibration
#           use MYSQL MYSQL-00-* External
#           use GaudiInterface * External
#           use BesROOT BesROOT-00-* External
#           use DstEvent DstEvent-* Event
#           use EventModel EventModel-* Event
#           use CalibDataSvc * Calibration/CalibSvc
#           use CalibMySQLCnv * Calibration/CalibSvc
#           use DatabaseSvc DatabaseSvc-* Database
#       use XercesC * LCG_Interfaces (no_version_directory) (native_version=3.1.1p1)
#       use MYSQL MYSQL-00-00-* External
#       use BesROOT BesROOT-* External
#     use TofQCorrSvc TofQCorrSvc-* Tof
#       use BesPolicy BesPolicy-01-* 
#       use GaudiInterface GaudiInterface-* External
#       use CalibData * Calibration
#       use EventModel EventModel-* Event
#       use DatabaseSvc DatabaseSvc-* Database
#       use XercesC * LCG_Interfaces (no_version_directory) (native_version=3.1.1p1)
#       use MYSQL MYSQL-00-00-* External
#       use BesROOT BesROOT-* External
#     use TofQElecSvc TofQElecSvc-* Tof
#       use BesPolicy BesPolicy-01-* 
#       use GaudiInterface GaudiInterface-* External
#       use calibUtil * Calibration
#       use CalibData * Calibration
#       use CalibSvc * Calibration
#       use XercesC * LCG_Interfaces (no_version_directory) (native_version=3.1.1p1)
#       use MYSQL MYSQL-00-00-* External
#       use BesROOT BesROOT-* External
#     use EmcRawEvent EmcRawEvent-* Emc
#       use BesPolicy BesPolicy-* 
#       use GaudiInterface GaudiInterface-01-* External
#       use RawEvent RawEvent-* Event
#       use EventModel EventModel-* Event
#       use Identifier Identifier-* DetectorDescription
#       use EmcWaveform EmcWaveform-* Emc
#         use BesPolicy BesPolicy-* 
#         use GaudiInterface GaudiInterface-* External
#     use EmcCalibConstSvc EmcCalibConstSvc-* Emc
#       use BesPolicy BesPolicy-* 
#       use GaudiInterface GaudiInterface-* External
#       use CalibData CalibData-* Calibration
#       use CalibDataSvc CalibDataSvc-* Calibration/CalibSvc
#       use CalibROOTCnv CalibROOTCnv-* Calibration/CalibSvc
#       use EmcRecGeoSvc EmcRecGeoSvc-* Emc
#       use EmcGeneralClass EmcGeneralClass-* Emc
#         use BesPolicy BesPolicy-* 
#         use Identifier Identifier-* DetectorDescription
#       use BesCLHEP BesCLHEP-* External
#     use MdcCalibFunSvc MdcCalibFunSvc-* Mdc
#       use BesPolicy BesPolicy-01-* 
#       use GaudiInterface GaudiInterface-01-* External
#       use CalibData CalibData-* Calibration
#       use CalibSvc CalibSvc-* Calibration
#       use MdcGeomSvc MdcGeomSvc-* Mdc
#       use BesCLHEP BesCLHEP-* External
#     use EvTimeEvent EvTimeEvent-* Event
#   use EvtRecEvent EvtRecEvent-* Event
#   use MdcRecEvent MdcRecEvent-* Mdc
#   use DedxCorrecSvc DedxCorrecSvc-* Mdc
#     use BesPolicy BesPolicy-* 
#     use GaudiInterface GaudiInterface-* External
#     use BesCLHEP BesCLHEP-* External
#     use MdcGeomSvc MdcGeomSvc-* Mdc
#     use calibUtil * Calibration
#     use CalibData * Calibration
#     use MagneticField MagneticField-* 
#     use Identifier * DetectorDescription
#     use XercesC * LCG_Interfaces (no_version_directory) (native_version=3.1.1p1)
#     use MYSQL MYSQL-00-00-* External
#   use TofRecEvent TofRecEvent-* Tof
#   use EmcRecEventModel EmcRecEventModel-* Emc
#   use MucRecEvent MucRecEvent-* Muc
#   use ExtEvent ExtEvent-* Event
#   use BesDChain BesDChain-* Event
#     use BesPolicy BesPolicy-* 
#     use BesCLHEP BesCLHEP-* External
#     use EvtRecEvent EvtRecEvent-* Event
#     use MdcRecEvent MdcRecEvent-* Mdc
#     use EmcRecEventModel EmcRecEventModel-* Emc
#     use VertexFit VertexFit-* Analysis
#     use DecayChain DecayChain-* Event
#       use BesPolicy BesPolicy-* 
#   use VertexFit VertexFit-* Analysis
#   use ParticleID ParticleID-* Analysis
# use BesDChain BesDChain-* Event
#
# Selection :
use CMT v1r25 (/cvmfs/bes3.ihep.ac.cn/bes3sw/ExternalLib/SLC6/contrib)
use Xt Xt-00-00-02 External (/cvmfs/bes3.ihep.ac.cn/bes3sw/Boss/7.0.5)
use BesExternalArea BesExternalArea-00-00-22 External (/cvmfs/bes3.ihep.ac.cn/bes3sw/Boss/7.0.5)
use GdmlManagement GdmlManagement-00-00-43 DetectorDescription (/cvmfs/bes3.ihep.ac.cn/bes3sw/Boss/7.0.5)
use LCG_Platforms v1  (/cvmfs/bes3.ihep.ac.cn/bes3sw/ExternalLib/SLC6/ExternalLib/LCGCMT/LCGCMT_65a)
use LCG_Configuration v1  (/cvmfs/bes3.ihep.ac.cn/bes3sw/ExternalLib/SLC6/ExternalLib/LCGCMT/LCGCMT_65a)
use LCG_Settings v1  (/cvmfs/bes3.ihep.ac.cn/bes3sw/ExternalLib/SLC6/ExternalLib/LCGCMT/LCGCMT_65a)
use blas v1 LCG_Interfaces (/cvmfs/bes3.ihep.ac.cn/bes3sw/ExternalLib/SLC6/ExternalLib/LCGCMT/LCGCMT_65a)
use lapack v1 LCG_Interfaces (/cvmfs/bes3.ihep.ac.cn/bes3sw/ExternalLib/SLC6/ExternalLib/LCGCMT/LCGCMT_65a)
use cernlib v1 LCG_Interfaces (/cvmfs/bes3.ihep.ac.cn/bes3sw/ExternalLib/SLC6/ExternalLib/LCGCMT/LCGCMT_65a)
use uuid v1 LCG_Interfaces (/cvmfs/bes3.ihep.ac.cn/bes3sw/ExternalLib/SLC6/ExternalLib/LCGCMT/LCGCMT_65a) (no_auto_imports)
use AIDA v1 LCG_Interfaces (/cvmfs/bes3.ihep.ac.cn/bes3sw/ExternalLib/SLC6/ExternalLib/LCGCMT/LCGCMT_65a) (no_auto_imports)
use sqlite v1 LCG_Interfaces (/cvmfs/bes3.ihep.ac.cn/bes3sw/ExternalLib/SLC6/ExternalLib/LCGCMT/LCGCMT_65a)
use CASTOR v1 LCG_Interfaces (/cvmfs/bes3.ihep.ac.cn/bes3sw/ExternalLib/SLC6/ExternalLib/LCGCMT/LCGCMT_65a)
use CERNLIB CERNLIB-01-02-03 External (/cvmfs/bes3.ihep.ac.cn/bes3sw/Boss/7.0.5)
use mysql v1 LCG_Interfaces (/cvmfs/bes3.ihep.ac.cn/bes3sw/ExternalLib/SLC6/ExternalLib/LCGCMT/LCGCMT_65a)
use MYSQL MYSQL-00-00-09 External (/cvmfs/bes3.ihep.ac.cn/bes3sw/Boss/7.0.5)
use XercesC v1 LCG_Interfaces (/cvmfs/bes3.ihep.ac.cn/bes3sw/ExternalLib/SLC6/ExternalLib/LCGCMT/LCGCMT_65a)
use HepPDT v1 LCG_Interfaces (/cvmfs/bes3.ihep.ac.cn/bes3sw/ExternalLib/SLC6/ExternalLib/LCGCMT/LCGCMT_65a)
use HepMC v1 LCG_Interfaces (/cvmfs/bes3.ihep.ac.cn/bes3sw/ExternalLib/SLC6/ExternalLib/LCGCMT/LCGCMT_65a)
use CLHEP v1 LCG_Interfaces (/cvmfs/bes3.ihep.ac.cn/bes3sw/ExternalLib/SLC6/ExternalLib/LCGCMT/LCGCMT_65a)
use BesCLHEP BesCLHEP-00-00-11 External (/cvmfs/bes3.ihep.ac.cn/bes3sw/Boss/7.0.5)
use BesGeant4 BesGeant4-00-00-11 External (/cvmfs/bes3.ihep.ac.cn/bes3sw/Boss/7.0.5)
use GdmlToG4 GdmlToG4-00-00-11 External (/cvmfs/bes3.ihep.ac.cn/bes3sw/Boss/7.0.5)
use xrootd v1 LCG_Interfaces (/cvmfs/bes3.ihep.ac.cn/bes3sw/ExternalLib/SLC6/ExternalLib/LCGCMT/LCGCMT_65a)
use GCCXML v1 LCG_Interfaces (/cvmfs/bes3.ihep.ac.cn/bes3sw/ExternalLib/SLC6/ExternalLib/LCGCMT/LCGCMT_65a) (no_auto_imports)
use BesFortranPolicy BesFortranPolicy-00-01-03  (/cvmfs/bes3.ihep.ac.cn/bes3sw/Boss/7.0.5)
use libunwind v1 LCG_Interfaces (/cvmfs/bes3.ihep.ac.cn/bes3sw/ExternalLib/SLC6/ExternalLib/LCGCMT/LCGCMT_65a) (no_auto_imports)
use tcmalloc v1 LCG_Interfaces (/cvmfs/bes3.ihep.ac.cn/bes3sw/ExternalLib/SLC6/ExternalLib/LCGCMT/LCGCMT_65a) (no_auto_imports)
use Python v1 LCG_Interfaces (/cvmfs/bes3.ihep.ac.cn/bes3sw/ExternalLib/SLC6/ExternalLib/LCGCMT/LCGCMT_65a) (no_auto_imports)
use Boost v1 LCG_Interfaces (/cvmfs/bes3.ihep.ac.cn/bes3sw/ExternalLib/SLC6/ExternalLib/LCGCMT/LCGCMT_65a)
use ROOT v1 LCG_Interfaces (/cvmfs/bes3.ihep.ac.cn/bes3sw/ExternalLib/SLC6/ExternalLib/LCGCMT/LCGCMT_65a)
use BesROOT BesROOT-00-00-08 External (/cvmfs/bes3.ihep.ac.cn/bes3sw/Boss/7.0.5)
use GdmlToRoot GdmlToRoot-00-00-14 External (/cvmfs/bes3.ihep.ac.cn/bes3sw/Boss/7.0.5)
use Reflex v1 LCG_Interfaces (/cvmfs/bes3.ihep.ac.cn/bes3sw/ExternalLib/SLC6/ExternalLib/LCGCMT/LCGCMT_65a)
use GaudiPolicy v12r7  (/cvmfs/bes3.ihep.ac.cn/bes3sw/ExternalLib/SLC6/ExternalLib/gaudi/GAUDI_v23r9)
use GaudiKernel v28r8  (/cvmfs/bes3.ihep.ac.cn/bes3sw/ExternalLib/SLC6/ExternalLib/gaudi/GAUDI_v23r9)
use GaudiUtils v4r6  (/cvmfs/bes3.ihep.ac.cn/bes3sw/ExternalLib/SLC6/ExternalLib/gaudi/GAUDI_v23r9)
use GaudiAlg v14r6  (/cvmfs/bes3.ihep.ac.cn/bes3sw/ExternalLib/SLC6/ExternalLib/gaudi/GAUDI_v23r9)
use GaudiSvc v19r4  (/cvmfs/bes3.ihep.ac.cn/bes3sw/ExternalLib/SLC6/ExternalLib/gaudi/GAUDI_v23r9)
use GaudiInterface GaudiInterface-01-03-07 External (/cvmfs/bes3.ihep.ac.cn/bes3sw/Boss/7.0.5)
use BesCxxPolicy BesCxxPolicy-00-01-01  (/cvmfs/bes3.ihep.ac.cn/bes3sw/Boss/7.0.5)
use BesPolicy BesPolicy-01-05-05  (/cvmfs/bes3.ihep.ac.cn/bes3sw/Boss/7.0.5)
use DecayChain DecayChain-00-00-03-slc6tag Event (/cvmfs/bes3.ihep.ac.cn/bes3sw/Boss/7.0.5)
use EmcWaveform EmcWaveform-00-00-03 Emc (/cvmfs/bes3.ihep.ac.cn/bes3sw/Boss/7.0.5)
use DetVerSvc DetVerSvc-00-00-07 Utilities (/cvmfs/bes3.ihep.ac.cn/bes3sw/Boss/7.0.5)
use RootPolicy RootPolicy-00-01-03  (/cvmfs/bes3.ihep.ac.cn/bes3sw/Boss/7.0.5)
use BesTimerSvc BesTimerSvc-00-00-12 Utilities (/besfs/groups/jpsi/jpsigroup/user/liumeihong/boss/boss7.0.5)
use SimUtil SimUtil-00-00-37 Simulation/BOOST (/cvmfs/bes3.ihep.ac.cn/bes3sw/Boss/7.0.5)
use ROOTGeo ROOTGeo-00-00-15 DetectorDescription (/cvmfs/bes3.ihep.ac.cn/bes3sw/Boss/7.0.5)
use DatabaseSvc DatabaseSvc-00-00-26 Database (/cvmfs/bes3.ihep.ac.cn/bes3sw/Boss/7.0.5)
use facilities facilities-00-00-04 Calibration (/cvmfs/bes3.ihep.ac.cn/bes3sw/Boss/7.0.5)
use CalibData CalibData-00-01-22 Calibration (/cvmfs/bes3.ihep.ac.cn/bes3sw/Boss/7.0.5)
use xmlBase xmlBase-00-00-03 Calibration (/cvmfs/bes3.ihep.ac.cn/bes3sw/Boss/7.0.5)
use rdbModel rdbModel-00-01-01 Calibration (/cvmfs/bes3.ihep.ac.cn/bes3sw/Boss/7.0.5)
use calibUtil calibUtil-00-00-43 Calibration (/cvmfs/bes3.ihep.ac.cn/bes3sw/Boss/7.0.5)
use RelTable RelTable-00-00-02 Event (/cvmfs/bes3.ihep.ac.cn/bes3sw/Boss/7.0.5)
use Identifier Identifier-00-02-17 DetectorDescription (/cvmfs/bes3.ihep.ac.cn/bes3sw/Boss/7.0.5)
use EmcGeneralClass EmcGeneralClass-00-00-04 Emc (/cvmfs/bes3.ihep.ac.cn/bes3sw/Boss/7.0.5)
use G4Geo G4Geo-00-00-13 DetectorDescription (/cvmfs/bes3.ihep.ac.cn/bes3sw/Boss/7.0.5)
use MucGeomSvc MucGeomSvc-00-02-25 Muc (/cvmfs/bes3.ihep.ac.cn/bes3sw/Boss/7.0.5)
use EmcRecGeoSvc EmcRecGeoSvc-01-01-07 Emc (/cvmfs/bes3.ihep.ac.cn/bes3sw/Boss/7.0.5)
use EventModel EventModel-01-05-34 Event (/cvmfs/bes3.ihep.ac.cn/bes3sw/Boss/7.0.5)
use TofQCorrSvc TofQCorrSvc-00-00-10 Tof (/cvmfs/bes3.ihep.ac.cn/bes3sw/Boss/7.0.5)
use RawEvent RawEvent-00-03-19 Event (/cvmfs/bes3.ihep.ac.cn/bes3sw/Boss/7.0.5)
use EmcRawEvent EmcRawEvent-00-02-06 Emc (/cvmfs/bes3.ihep.ac.cn/bes3sw/Boss/7.0.5)
use TofRawEvent TofRawEvent-00-02-07 Tof (/cvmfs/bes3.ihep.ac.cn/bes3sw/Boss/7.0.5)
use MdcRawEvent MdcRawEvent-00-03-08 Mdc (/cvmfs/bes3.ihep.ac.cn/bes3sw/Boss/7.0.5)
use MagneticField MagneticField-00-02-03  (/cvmfs/bes3.ihep.ac.cn/bes3sw/Boss/7.0.5)
use DstEvent DstEvent-00-02-51 Event (/cvmfs/bes3.ihep.ac.cn/bes3sw/Boss/7.0.5)
use CalibDataSvc CalibDataSvc-00-01-04 Calibration/CalibSvc (/cvmfs/bes3.ihep.ac.cn/bes3sw/Boss/7.0.5)
use CalibMySQLCnv CalibMySQLCnv-00-01-09 Calibration/CalibSvc (/cvmfs/bes3.ihep.ac.cn/bes3sw/Boss/7.0.5)
use CalibTreeCnv CalibTreeCnv-00-01-22 Calibration/CalibSvc (/cvmfs/bes3.ihep.ac.cn/bes3sw/Boss/7.0.5)
use CalibROOTCnv CalibROOTCnv-00-01-16 Calibration/CalibSvc (/cvmfs/bes3.ihep.ac.cn/bes3sw/Boss/7.0.5)
use EmcCalibConstSvc EmcCalibConstSvc-00-00-12 Emc (/cvmfs/bes3.ihep.ac.cn/bes3sw/Boss/7.0.5)
use CalibSvc CalibSvc-00-02-07 Calibration (/cvmfs/bes3.ihep.ac.cn/bes3sw/Boss/7.0.5)
use TofQElecSvc TofQElecSvc-00-00-05 Tof (/cvmfs/bes3.ihep.ac.cn/bes3sw/Boss/7.0.5)
use TofCaliSvc TofCaliSvc-00-01-19 Tof (/cvmfs/bes3.ihep.ac.cn/bes3sw/Boss/7.0.5)
use ExtEvent ExtEvent-00-00-13 Event (/cvmfs/bes3.ihep.ac.cn/bes3sw/Boss/7.0.5)
use ReconEvent ReconEvent-00-00-04 Event (/cvmfs/bes3.ihep.ac.cn/bes3sw/Boss/7.0.5)
use MucRecEvent MucRecEvent-00-02-52 Muc (/cvmfs/bes3.ihep.ac.cn/bes3sw/Boss/7.0.5)
use EmcRecEventModel EmcRecEventModel-01-01-18 Emc (/cvmfs/bes3.ihep.ac.cn/bes3sw/Boss/7.0.5)
use TofRecEvent TofRecEvent-00-02-14 Tof (/cvmfs/bes3.ihep.ac.cn/bes3sw/Boss/7.0.5)
use MdcGeomSvc MdcGeomSvc-00-01-37 Mdc (/cvmfs/bes3.ihep.ac.cn/bes3sw/Boss/7.0.5)
use DedxCorrecSvc DedxCorrecSvc-00-02-54 Mdc (/cvmfs/bes3.ihep.ac.cn/bes3sw/Boss/7.0.5)
use MdcCalibFunSvc MdcCalibFunSvc-00-03-16 Mdc (/cvmfs/bes3.ihep.ac.cn/bes3sw/Boss/7.0.5)
use MdcRecEvent MdcRecEvent-00-05-14 Mdc (/cvmfs/bes3.ihep.ac.cn/bes3sw/Boss/7.0.5)
use EvTimeEvent EvTimeEvent-00-00-08 Event (/cvmfs/bes3.ihep.ac.cn/bes3sw/Boss/7.0.5)
use RawDataProviderSvc RawDataProviderSvc-00-03-48 Event (/cvmfs/bes3.ihep.ac.cn/bes3sw/Boss/7.0.5)
use EvtRecEvent EvtRecEvent-00-02-03 Event (/cvmfs/bes3.ihep.ac.cn/bes3sw/Boss/7.0.5)
use VertexFit VertexFit-00-02-85 Analysis (/besfs/groups/jpsi/jpsigroup/user/liumeihong/boss/boss7.0.5)
use BesDChain BesDChain-00-00-14 Event (/cvmfs/bes3.ihep.ac.cn/bes3sw/Boss/7.0.5)
use ParticleID ParticleID-00-04-68 Analysis (/cvmfs/bes3.ihep.ac.cn/bes3sw/Boss/7.0.5)
use McTruth McTruth-00-02-19 Event (/cvmfs/bes3.ihep.ac.cn/bes3sw/Boss/7.0.5)
use HadronInfo HadronInfo-00-00-02  (/besfs/groups/jpsi/jpsigroup/user/liumeihong/boss/boss7.0.5)
use EventNavigator EventNavigator-00-01-03 Event (/cvmfs/bes3.ihep.ac.cn/bes3sw/Boss/7.0.5)
use GammaConv GammaConv-00-00-04  (/besfs/groups/jpsi/jpsigroup/user/liumeihong/boss/boss7.0.5)
use McDecayModeSvc McDecayModeSvc-00-00-02  (/besfs/groups/jpsi/jpsigroup/user/liumeihong/boss/boss7.0.5)
use MCTruthMatchSvc MCTruthMatchSvc-00-00-02  (/besfs/groups/jpsi/jpsigroup/user/liumeihong/boss/boss7.0.5)
use DataBaseReader DataBaseReader-00-00-02  (/besfs/groups/jpsi/jpsigroup/user/liumeihong/boss/boss7.0.5)
----------> tags
CMTv1 (from CMTVERSION)
CMTr25 (from CMTVERSION)
CMTp0 (from CMTVERSION)
Linux (from uname) package [CMT LCG_Platforms BesPolicy] implies [Unix host-linux]
x86_64-slc6-gcc46-opt (from CMTCONFIG) package [LCG_Platforms] implies [target-x86_64 target-slc6 target-gcc46 target-opt]
boss_no_config (from PROJECT) excludes [boss_config]
boss_root (from PROJECT) excludes [boss_no_root]
boss_cleanup (from PROJECT) excludes [boss_no_cleanup]
boss_scripts (from PROJECT) excludes [boss_no_scripts]
boss_prototypes (from PROJECT) excludes [boss_no_prototypes]
boss_with_installarea (from PROJECT) excludes [boss_without_installarea]
boss_with_version_directory (from PROJECT) excludes [boss_without_version_directory]
boss (from PROJECT)
BOSS_no_config (from PROJECT) excludes [BOSS_config]
BOSS_root (from PROJECT) excludes [BOSS_no_root]
BOSS_cleanup (from PROJECT) excludes [BOSS_no_cleanup]
BOSS_scripts (from PROJECT) excludes [BOSS_no_scripts]
BOSS_no_prototypes (from PROJECT) excludes [BOSS_prototypes]
BOSS_with_installarea (from PROJECT) excludes [BOSS_without_installarea]
BOSS_with_version_directory (from PROJECT) excludes [BOSS_without_version_directory]
GAUDI_no_config (from PROJECT) excludes [GAUDI_config]
GAUDI_root (from PROJECT) excludes [GAUDI_no_root]
GAUDI_cleanup (from PROJECT) excludes [GAUDI_no_cleanup]
GAUDI_scripts (from PROJECT) excludes [GAUDI_no_scripts]
GAUDI_prototypes (from PROJECT) excludes [GAUDI_no_prototypes]
GAUDI_with_installarea (from PROJECT) excludes [GAUDI_without_installarea]
GAUDI_without_version_directory (from PROJECT) excludes [GAUDI_with_version_directory]
LCGCMT_no_config (from PROJECT) excludes [LCGCMT_config]
LCGCMT_no_root (from PROJECT) excludes [LCGCMT_root]
LCGCMT_cleanup (from PROJECT) excludes [LCGCMT_no_cleanup]
LCGCMT_scripts (from PROJECT) excludes [LCGCMT_no_scripts]
LCGCMT_prototypes (from PROJECT) excludes [LCGCMT_no_prototypes]
LCGCMT_without_installarea (from PROJECT) excludes [LCGCMT_with_installarea]
LCGCMT_with_version_directory (from PROJECT) excludes [LCGCMT_without_version_directory]
x86_64 (from package CMT) package [LCG_Platforms] implies [host-x86_64]
slc78 (from package CMT)
gcc463 (from package CMT)
Unix (from package CMT) package [LCG_Platforms] implies [host-unix] excludes [WIN32 Win32]
c_native_dependencies (from package CMT) activated GaudiPolicy
cpp_native_dependencies (from package CMT) activated GaudiPolicy
target-unix (from package LCG_Settings) activated LCG_Platforms
target-x86_64 (from package LCG_Settings) activated LCG_Platforms
target-gcc46 (from package LCG_Settings) package [LCG_Platforms] implies [target-gcc4 target-lcg-compiler lcg-compiler] activated LCG_Platforms
host-x86_64 (from package LCG_Settings) activated LCG_Platforms
target-slc (from package LCG_Settings) package [LCG_Platforms] implies [target-linux] activated LCG_Platforms
target-gcc (from package LCG_Settings) activated LCG_Platforms
target-gcc4 (from package LCG_Settings) package [LCG_Platforms] implies [target-gcc] activated LCG_Platforms
target-lcg-compiler (from package LCG_Settings) activated LCG_Platforms
host-linux (from package LCG_Platforms) package [LCG_Platforms] implies [host-unix]
host-unix (from package LCG_Platforms)
target-opt (from package LCG_Platforms)
target-slc6 (from package LCG_Platforms) package [LCG_Platforms] implies [target-slc]
target-linux (from package LCG_Platforms) package [LCG_Platforms] implies [target-unix]
lcg-compiler (from package LCG_Platforms)
ROOT_GE_5_15 (from package LCG_Configuration)
ROOT_GE_5_19 (from package LCG_Configuration)
HasAthenaRunTime (from package BesPolicy)
ROOTBasicLibs (from package BesROOT)
----------> CMTPATH
# Add path /besfs/groups/jpsi/jpsigroup/user/liumeihong/boss/boss7.0.5 from initialization
# Add path /cvmfs/bes3.ihep.ac.cn/bes3sw/Boss/7.0.5 from initialization
# Add path /cvmfs/bes3.ihep.ac.cn/bes3sw/ExternalLib/SLC6/ExternalLib/gaudi/GAUDI_v23r9 from initialization
# Add path /cvmfs/bes3.ihep.ac.cn/bes3sw/ExternalLib/SLC6/ExternalLib/LCGCMT/LCGCMT_65a from initialization
