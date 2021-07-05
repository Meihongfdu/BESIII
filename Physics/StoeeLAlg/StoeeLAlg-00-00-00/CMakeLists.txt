#<===<===<===<===<===<===<===<===<===~===>===>===>===>===>===>===>===>===>
## File Name:    CMakeLists.txt
## Author:       Hao-Kai SUN
## Created:      2019-10-25 Fri 14:33:28 CST
## <<=====================================>>
## Last Updated: 2020-06-28 Sun 14:30:16 CST
##           By: Hao-Kai SUN
##     Update #: 176
## <<======== COPYRIGHT && LICENSE =======>>
##
## Copyright © 2019 SUN Hao-Kai <spin.hk@outlook.com>. All rights reserved.
##
## This program is free software: you can redistribute it and/or modify
## it under the terms of the GNU General Public License as published by
## the Free Software Foundation, either version 3 of the License, or (at
## your option) any later version.
##
## This program is distributed in the hope that it will be useful, but
## WITHOUT ANY WARRANTY; without even the implied warranty of
## MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
## General Public License for more details.
##
## You should have received a copy of the GNU General Public License
## along with GNU Emacs.  If not, see <https://www.gnu.org/licenses/>.
##
## ============================== CODES ==============================>>>
cmake_minimum_required(VERSION 3.15)

# apply CMake policies for specific CMake versions
if(${CMAKE_VERSION} VERSION_LESS 3.15)
    cmake_policy(VERSION ${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION})
else()
    cmake_policy(VERSION 3.17)
endif()

project(
    StoeelAlg
    VERSION 0.0.2
    DESCRIPTION "Sigma0 to e+ e- Lambda0."
    LANGUAGES CXX
    )

# set C++ stand to 98/03 since all BOSS versions are developed
# using g++ compiler that not fully support C++11
set(CMAKE_CXX_STANDARD 98)

# output compile_commands.json for LSP
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Set compiler for C
find_program(CMAKE_C_COMPILER gcc)
set(CMAKE_C_COMPILER
    "${CMAKE_C_COMPILER}"
    CACHE FILEPATH
    "The compiler for C language"
    FORCE
    )

# from `cmt show macro_value cflags`
set(CMAKE_C_FLAGS
    "-fmessage-length=0 -fPIC"
    CACHE STRING
    "The compiling flags for C compiler."
    FORCE
    )

# Set compiler for CPP
find_program(CMAKE_CXX_COMPILER g++)
set(CMAKE_CXX_COMPILER
    "${CMAKE_CXX_COMPILER}"
    CACHE FILEPATH
    "The compiler for C++ language"
    FORCE
    )

# from `cmt show macro_value cppflags`
# "-fmessage-length=0     -Wall -Wextra -pthread  -Wno-deprecated -Wno-empty-body -D_GNU_SOURCE -pthread -pipe -ansi -pedantic -W -Wall -Wwrite-strings -Wpointer-arith -Woverloaded-virtual -Wno-long-long   -march=x86-64 -mtune=x86-64 -pedantic-errors -O2 -DEXTEND"
set(CMAKE_CXX_FLAGS
    "-Wall -Wextra -g -pthread  -Wno-deprecated -Wno-empty-body -D_GNU_SOURCE -pthread -pipe -ansi -pedantic -W -Wwrite-strings -Wpointer-arith -Woverloaded-virtual -Wno-long-long   -march=x86-64 -mtune=x86-64 -pedantic-errors -Og -DEXTEND"
    CACHE STRING
    "The compiling flags for C++ compiler."
    )

# make shared library
add_library(
    ${PROJECT_NAME} SHARED
    src/components/entries.cxx
    src/components/load.cxx
    src/util/MyUtil.cxxbk
    src/util/current.cxx
    src/util/Print.cxx
    src/util/ReadBeamInfFromDb.cxx
    src/Selector/StoeeLAlgDsSelector.cxx
    src/Selector/StoeeLAlgElectronSelector.cxx
    src/Selector/StoeeLAlgEptoPiPiEtaSelector.cxx
    src/Selector/StoeeLAlgEtatoGGSelector.cxx
    src/Selector/StoeeLAlgEtatoPiPiPi0Selector.cxx
    src/Selector/StoeeLAlgGoodChrTrkSelector.cxx
    src/Selector/StoeeLAlgKaonSelector.cxx
    src/Selector/StoeeLAlgKsSelector.cxx
    src/Selector/StoeeLAlgLambdaSelector.cxx
    src/Selector/StoeeLAlgPhotonSelector.cxx
    src/Selector/StoeeLAlgPi0Selector.cxx
    src/Selector/StoeeLAlgPionSelector.cxx
    src/Selector/StoeeLAlgProtonSelector.cxx
    src/Selector/StoeeLAlgSigma0Selector.cxx
    src/Selector/StoeeLAlgSignalSelector.cxx
    src/StoeeLAlg.cxx
    src/FillInf.cxx
    src/GetParList.cxx
    src/KinematicFit.cxx
    src/initial.cxx
    )

# from `cmt show macro_value cppflags`

# -fmessage-length=0 -Wall -Wextra -pthread -Wno-deprecated
# -Wno-empty-body -D_GNU_SOURCE -pthread -pipe -ansi -pedantic -W -Wall
# -Wwrite-strings -Wpointer-arith -Woverloaded-virtual -Wno-long-long
# -march=x86-64 -mtune=x86-64 -pedantic-errors -O2 -DEXTEND
target_compile_options(${PROJECT_NAME} PUBLIC
    # -nostdinc++
    -Wall -Wextra -Wpadded -g -pthread -Wno-deprecated
    -Wno-empty-body -D_GNU_SOURCE -pthread -pipe -ansi -pedantic
    -Wwrite-strings -Wpointer-arith -Woverloaded-virtual -Wno-long-long
    -march=x86-64 -mtune=x86-64 -pedantic-errors -Og -DEXTEND
    )
# from `cmt show macro_value cpplinkflags`
# and partly from `cmt show macro_value <PACKAGE_NAME>_shlibflags`
target_link_options(${PROJECT_NAME} PUBLIC
    -Wl,-Bdynamic -ldl -Wl,--no-undefined -Wl,--export-dynamic -fPIC
    )

# set root path
set(CPP_VER "4.6.3") # boss-7.0.5
set(BOSS_VERN "$ENV{HOME}/Work/705")
# set include paths' common parent
set(BOSS_PATH "/cvmfs/bes3.ihep.ac.cn/bes3sw/Boss/7.0.5")
set(BOSS_ELIB "/cvmfs/bes3.ihep.ac.cn/bes3sw/ExternalLib/SLC6/ExternalLib")
set(BOSS_WORK "${BOSS_VERN}/workarea")

target_include_directories(
    ${PROJECT_NAME} PUBLIC
    "/home/sunhk/Work/705/StoeeLAlg"
    "${BOSS_WORK}/InstallArea/include/StoeeLAlg"
    "${BOSS_WORK}/InstallArea/x86_64-slc6-gcc46-opt/include"
    "${BOSS_PATH}/InstallArea/x86_64-slc6-gcc46-opt/include"
    "${BOSS_ELIB}/gaudi/GAUDI_v23r9/InstallArea/x86_64-slc6-gcc46-opt/include"
    "${BOSS_WORK}/InstallArea/include/DataBaseReader"
    "${BOSS_WORK}/InstallArea/include/MCTruthMatchSvc"
    "${BOSS_WORK}/InstallArea/include/McDecayModeSvc"
    "${BOSS_WORK}/InstallArea/include/GammaConv"
    "${BOSS_PATH}/InstallArea/include/EventNavigator"
    "${BOSS_WORK}/InstallArea/include/HadronInfo"
    "${BOSS_PATH}/Event/McTruth/McTruth-00-02-19/McTruth"
    "${BOSS_PATH}/InstallArea/include/McTruth"
    "${BOSS_PATH}/InstallArea/include/ParticleID"
    "${BOSS_PATH}/InstallArea/include/BesDChain"
    "${BOSS_PATH}/Analysis/VertexFit/VertexFit-00-02-85/VertexDbSvc"
    "${BOSS_PATH}/Analysis/VertexFit/VertexFit-00-02-85/src/test"
    "${BOSS_PATH}/InstallArea/include/VertexFit"
    "${BOSS_PATH}/InstallArea/include/EvtRecEvent"
    "${BOSS_PATH}/Event/RawDataProviderSvc/RawDataProviderSvc-00-03-48"
    "${BOSS_PATH}/InstallArea/include/RawDataProviderSvc"
    "${BOSS_PATH}/Event/EvTimeEvent/EvTimeEvent-00-00-08"
    "${BOSS_PATH}/InstallArea/include/EvTimeEvent"
    "${BOSS_PATH}/Mdc/MdcRecEvent/MdcRecEvent-00-05-14"
    "${BOSS_PATH}/InstallArea/include/MdcRecEvent"
    "${BOSS_PATH}/Mdc/MdcCalibFunSvc/MdcCalibFunSvc-00-03-16"
    "${BOSS_PATH}/InstallArea/include/MdcCalibFunSvc"
    "${BOSS_PATH}/Mdc/DedxCorrecSvc/DedxCorrecSvc-00-02-54"
    "${BOSS_PATH}/InstallArea/include/DedxCorrecSvc"
    "${BOSS_PATH}/Mdc/MdcGeomSvc/MdcGeomSvc-00-01-37"
    "${BOSS_PATH}/InstallArea/include/MdcGeomSvc"
    "${BOSS_PATH}/Tof/TofRecEvent/TofRecEvent-00-02-14"
    "${BOSS_PATH}/InstallArea/include/TofRecEvent"
    "${BOSS_PATH}/Emc/EmcRecEventModel/EmcRecEventModel-01-01-18"
    "${BOSS_PATH}/InstallArea/include/EmcRecEventModel"
    "${BOSS_PATH}/InstallArea/include/MucRecEvent"
    "${BOSS_PATH}/InstallArea/include/ReconEvent"
    "${BOSS_PATH}/Event/ExtEvent/ExtEvent-00-00-13"
    "${BOSS_PATH}/InstallArea/include/ExtEvent"
    "${BOSS_PATH}/Tof/TofCaliSvc/TofCaliSvc-00-01-19"
    "${BOSS_PATH}/InstallArea/include/TofCaliSvc"
    "${BOSS_PATH}/Tof/TofQElecSvc/TofQElecSvc-00-00-05"
    "${BOSS_PATH}/InstallArea/include/TofQElecSvc"
    "${BOSS_PATH}/InstallArea/include/CalibSvc"
    "${BOSS_PATH}/Emc/EmcCalibConstSvc/EmcCalibConstSvc-00-00-12/EmcCalibConstSvc"
    "${BOSS_PATH}/InstallArea/include/EmcCalibConstSvc"
    "${BOSS_PATH}/Calibration/CalibSvc/CalibROOTCnv/CalibROOTCnv-00-01-16"
    "${BOSS_PATH}/Calibration/CalibSvc/CalibROOTCnv/CalibROOTCnv-00-01-16/src/cnv"
    "${BOSS_PATH}/Calibration/CalibSvc/CalibROOTCnv/CalibROOTCnv-00-01-16/src/test"
    "${BOSS_PATH}/InstallArea/include/CalibROOTCnv"
    "${BOSS_PATH}/Calibration/CalibSvc/CalibTreeCnv/CalibTreeCnv-00-01-22"
    "${BOSS_PATH}/Calibration/CalibSvc/CalibTreeCnv/CalibTreeCnv-00-01-22/src/cnv"
    "${BOSS_PATH}/Calibration/CalibSvc/CalibTreeCnv/CalibTreeCnv-00-01-22/src/test"
    "${BOSS_PATH}/InstallArea/include/CalibTreeCnv"
    "${BOSS_PATH}/Calibration/CalibSvc/CalibMySQLCnv/CalibMySQLCnv-00-01-09"
    "${BOSS_PATH}/InstallArea/include/CalibMySQLCnv"
    "${BOSS_PATH}/Calibration/CalibSvc/CalibDataSvc/CalibDataSvc-00-01-04"
    "${BOSS_PATH}/InstallArea/include/CalibDataSvc"
    "${BOSS_PATH}/Event/DstEvent/DstEvent-00-02-51"
    "${BOSS_PATH}/InstallArea/include/DstEvent"
    "${BOSS_PATH}/InstallArea/include/MagneticField"
    "${BOSS_PATH}/Mdc/MdcRawEvent/MdcRawEvent-00-03-08"
    "${BOSS_PATH}/InstallArea/include/MdcRawEvent"
    "${BOSS_PATH}/Tof/TofRawEvent/TofRawEvent-00-02-07"
    "${BOSS_PATH}/InstallArea/include/TofRawEvent"
    "${BOSS_PATH}/InstallArea/include/EmcRawEvent"
    "${BOSS_PATH}/InstallArea/include/RawEvent"
    "${BOSS_PATH}/Tof/TofCaliSvc/TofCaliSvc-00-01-19"
    "${BOSS_PATH}/InstallArea/include/TofQCorrSvc"
    "${BOSS_PATH}/Event/EventModel/EventModel-01-05-34"
    "${BOSS_PATH}/InstallArea/include/EventModel"
    "${BOSS_PATH}/Emc/EmcRecGeoSvc/EmcRecGeoSvc-01-01-07"
    "${BOSS_PATH}/InstallArea/include/EmcRecGeoSvc"
    "${BOSS_PATH}/InstallArea/include/MucGeomSvc"
    "${BOSS_PATH}/InstallArea/include/G4Geo"
    "${BOSS_PATH}/InstallArea/include/EmcGeneralClass"
    "${BOSS_PATH}/DetectorDescription/Identifier/Identifier-00-02-17"
    "${BOSS_PATH}/InstallArea/include/Identifier"
    "${BOSS_PATH}/Event/RelTable/RelTable-00-00-02"
    "${BOSS_PATH}/InstallArea/include/RelTable"
    "${BOSS_PATH}/InstallArea/include/calibUtil"
    "${BOSS_PATH}/InstallArea/include/rdbModel"
    "${BOSS_PATH}/InstallArea/include/xmlBase"
    "${BOSS_PATH}/InstallArea/include/CalibData"
    "${BOSS_PATH}/InstallArea/include/facilities"
    "${BOSS_PATH}/InstallArea/include/DatabaseSvc"
    "${BOSS_PATH}/InstallArea/include/ROOTGeo"
    "${BOSS_PATH}/Simulation/BOOST/SimUtil/SimUtil-00-00-37/SimUtil"
    "${BOSS_PATH}/InstallArea/include/SimUtil"
    "${BOSS_PATH}/InstallArea/include/BesTimerSvc"
    "${BOSS_PATH}/InstallArea/include/RootPolicy"
    "${BOSS_PATH}/InstallArea/include/DetVerSvc"
    "${BOSS_PATH}/Emc/EmcWaveform/EmcWaveform-00-00-03/EmcWaveform"
    "${BOSS_PATH}/InstallArea/include/EmcWaveform"
    "${BOSS_PATH}/InstallArea/include/DecayChain"
    "${BOSS_PATH}/BesCxxPolicy/BesCxxPolicy-00-01-01"
    "${BOSS_ELIB}/external/ROOT/5.34.09/x86_64-slc6-gcc46-opt/root/include"
    "${BOSS_PATH}/External/GdmlToRoot/GdmlToRoot-00-00-14/src"
    "${BOSS_ELIB}/external/BesGDML/2.8.0/x86_64-slc6-gcc46-opt/include/Common/Saxana"
    "${BOSS_ELIB}/external/BesGDML/2.8.0/x86_64-slc6-gcc46-opt/include/Common/Saxana/Saxana"
    "${BOSS_ELIB}/external/BesGDML/2.8.0/x86_64-slc6-gcc46-opt/include/Common/Processes"
    "${BOSS_ELIB}/external/BesGDML/2.8.0/x86_64-slc6-gcc46-opt/include/Common/Processes/Processes"
    "${BOSS_ELIB}/external/BesGDML/2.8.0/x86_64-slc6-gcc46-opt/include/Common/Schema"
    "${BOSS_ELIB}/external/BesGDML/2.8.0/x86_64-slc6-gcc46-opt/include/Common/Schema/Schema"
    "${BOSS_ELIB}/external/BesGDML/2.8.0/x86_64-slc6-gcc46-opt/include/Common/Writer"
    "${BOSS_ELIB}/external/BesGDML/2.8.0/x86_64-slc6-gcc46-opt/include/Common/Writer/Writer"
    "${BOSS_ELIB}/external/BesGDML/2.8.0/x86_64-slc6-gcc46-opt/include/ROOTBinding/Processor"
    "${BOSS_ELIB}/external/BesGDML/2.8.0/x86_64-slc6-gcc46-opt/include/ROOTBinding/Processor/Processor"
    "${BOSS_ELIB}/external/BesGDML/2.8.0/x86_64-slc6-gcc46-opt/include/ROOTBinding/Subscribers"
    "${BOSS_ELIB}/external/BesGDML/2.8.0/x86_64-slc6-gcc46-opt/include/ROOTBinding/Subscribers/Subscribers"
    "${BOSS_ELIB}/external/BesGDML/2.8.0/x86_64-slc6-gcc46-opt/include/ROOTBinding/Evaluator"
    "${BOSS_ELIB}/external/BesGDML/2.8.0/x86_64-slc6-gcc46-opt/include/ROOTBinding/Evaluator/Evaluator"
    "${BOSS_PATH}/External/BesROOT/BesROOT-00-00-08/src"
    "${BOSS_ELIB}/external/ROOT/5.34.09/x86_64-slc6-gcc46-opt/root/include"
    "${BOSS_ELIB}/external/Boost/1.50.0_python2.7/x86_64-slc6-gcc46-opt/include/boost-1_50"
    "${BOSS_PATH}/BesFortranPolicy/BesFortranPolicy-00-01-03/src"
    "${BOSS_ELIB}/external/xrootd/3.2.7/x86_64-slc6-gcc46-opt/include"
    "${BOSS_PATH}/External/GdmlToG4/GdmlToG4-00-00-11/src"
    "${BOSS_ELIB}/external/BesGDML/2.8.0/x86_64-slc6-gcc46-opt/include/Common/Saxana"
    "${BOSS_ELIB}/external/BesGDML/2.8.0/x86_64-slc6-gcc46-opt/include/Common/Saxana/Saxana"
    "${BOSS_ELIB}/external/BesGDML/2.8.0/x86_64-slc6-gcc46-opt/include/Common/Processes/"
    "${BOSS_ELIB}/external/BesGDML/2.8.0/x86_64-slc6-gcc46-opt/include/Common/Processes/Processes"
    "${BOSS_ELIB}/external/BesGDML/2.8.0/x86_64-slc6-gcc46-opt/include/Common/Schema"
    "${BOSS_ELIB}/external/BesGDML/2.8.0/x86_64-slc6-gcc46-opt/include/Common/Schema/Schema"
    "${BOSS_ELIB}/external/BesGDML/2.8.0/x86_64-slc6-gcc46-opt/include/Common/Writer"
    "${BOSS_ELIB}/external/BesGDML/2.8.0/x86_64-slc6-gcc46-opt/include/Common/Writer/Writer"
    "${BOSS_ELIB}/external/BesGDML/2.8.0/x86_64-slc6-gcc46-opt/include/G4Binding/G4Evaluator"
    "${BOSS_ELIB}/external/BesGDML/2.8.0/x86_64-slc6-gcc46-opt/include/G4Binding/G4Evaluator/G4Evaluator"
    "${BOSS_ELIB}/external/BesGDML/2.8.0/x86_64-slc6-gcc46-opt/include/G4Binding/G4Processor"
    "${BOSS_ELIB}/external/BesGDML/2.8.0/x86_64-slc6-gcc46-opt/include/G4Binding/G4Processor/G4Processor"
    "${BOSS_ELIB}/external/BesGDML/2.8.0/x86_64-slc6-gcc46-opt/include/G4Binding/G4Subscribers"
    "${BOSS_ELIB}/external/BesGDML/2.8.0/x86_64-slc6-gcc46-opt/include/G4Binding/G4Subscribers/G4Subscribers"
    "${BOSS_ELIB}/external/BesGDML/2.8.0/x86_64-slc6-gcc46-opt/include/G4Binding/G4Writer"
    "${BOSS_ELIB}/external/BesGDML/2.8.0/x86_64-slc6-gcc46-opt/include/G4Binding/G4Writer/G4Writer"
    "${BOSS_PATH}/External/BesGeant4/BesGeant4-00-00-11/src"
    "${BOSS_ELIB}/external/geant4/4.9.3p01/x86_64-slc6-gcc46-opt/include"
    "${BOSS_PATH}/External/BesCLHEP/BesCLHEP-00-00-11/src"
    "${BOSS_ELIB}/external/CLHEP/Alist/Alist-00-00-06"
    "${BOSS_ELIB}/external/CLHEP/String/String-00-00-05"
    "${BOSS_ELIB}/external/clhep/2.0.4.5/x86_64-slc6-gcc46-opt/include"
    "${BOSS_ELIB}/external/HepMC/2.06.08/x86_64-slc6-gcc46-opt/include"
    "${BOSS_ELIB}/external/HepPDT/2.06.01/x86_64-slc6-gcc46-opt/include"
    "${BOSS_ELIB}/external/XercesC/3.1.1p1/x86_64-slc6-gcc46-opt/include"
    "${BOSS_PATH}/External/MYSQL/MYSQL-00-00-09/src"
    "${BOSS_ELIB}/external/mysql/5.5.14/x86_64-slc6-gcc46-opt/include"
    "${BOSS_ELIB}/external/mysql/5.5.14/x86_64-slc6-gcc46-opt/include/mysql"
    "${BOSS_PATH}/External/CERNLIB/CERNLIB-01-02-03/src"
    "${BOSS_ELIB}/external/sqlite/3070900/x86_64-slc6-gcc46-opt/include"
    "${BOSS_ELIB}/external/cernlib/2006a/x86_64-slc6-gcc46-opt/include"
    "${BOSS_ELIB}/LCGCMT/LCGCMT_65a/LCG_Platforms/src"
    "${BOSS_PATH}/DetectorDescription/GdmlManagement/GdmlManagement-00-00-43/src"
    "${BOSS_PATH}/External/BesExternalArea/BesExternalArea-00-00-22/src"
    "${BOSS_PATH}/External/Xt/Xt-00-00-02/src"
    # "/usr/X11R6/include"
    # "${BOSS_VERN}/SystemUsr/include"
    )
#===================================================================<<<
#====================== CMakeLists.txt ends here ======================
