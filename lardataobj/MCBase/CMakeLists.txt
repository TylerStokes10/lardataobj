cet_make_library(SOURCE
  MCBaseException.cxx
  MCHitCollection.cxx
  MCHit.cxx
  MCShower.cxx
  MCStep.h
  MCTrack.cxx
  MCWireCollection.cxx
  MCWire.cxx
  LIBRARIES
  PUBLIC
  nusimdata::SimulationBase
  ROOT::Physics
)

build_dictionary(DICTIONARY_LIBRARIES
  lardataobj::MCBase canvas::canvas
)

install_headers()
install_source()
