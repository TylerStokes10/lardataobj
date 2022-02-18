cet_make_library(
         SOURCE
           AuxDetSimChannel.cxx
           OpDetBacktrackerRecord.cxx
           SimChannel.cxx
           SimPhotons.cxx
           SupernovaTruth.cxx
         LIBRARIES
           nusimdata::SimulationBase
           canvas::canvas
           messagefacility::MF_MessageLogger
           ROOT::GenVector
           ROOT::Core
           ROOT::Physics
         )

build_dictionary(DICTIONARY_LIBRARIES lardataobj_Simulation)

install_headers()
install_source()
