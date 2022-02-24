cet_make_library(
         SOURCE
           AuxDetSimChannel.cxx
           OpDetBacktrackerRecord.cxx
           SimChannel.cxx
           SimPhotons.cxx
           SupernovaTruth.cxx
         LIBRARIES
           canvas::canvas
           messagefacility::MF_MessageLogger
           ROOT::GenVector
           ROOT::Core
           ROOT::Physics
           PUBLIC
           nusimdata::SimulationBase
           larcoreobj::headers
         )

build_dictionary(DICTIONARY_LIBRARIES lardataobj_Simulation)

install_headers()
install_source()
