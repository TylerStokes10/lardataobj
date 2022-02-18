cet_make_library(
         SOURCE
           MCBaseException.cxx
           MCHitCollection.cxx
           MCHit.cxx
           MCShower.cxx
           MCTrack.cxx
           MCWireCollection.cxx
           MCWire.cxx
         LIBRARIES
           nusimdata::SimulationBase
           ROOT::Core
           ROOT::Physics
         )

build_dictionary(DICTIONARY_LIBRARIES lardataobj_MCBase canvas::canvas)

install_headers()
install_source()
