cet_make_library(LIBRARY_NAME RDTimeStamp INTERFACE
  SOURCE RDTimeStamp.h
  LIBRARIES INTERFACE
  ROOT::Core
)

cet_make_library(SOURCE
  Calorimetry.cxx
  CosmicTag.cxx
  FlashMatch.cxx
  MVAOutput.cxx
  ParticleID.cxx
  T0.cxx
  LIBRARIES
  PUBLIC
  lardataobj::RawData
  lardataobj::RecoBase
  larcoreobj::SimpleTypesAndConstants
  nusimdata::SimulationBase
  canvas::canvas
  cetlib_except::cetlib_except
)

build_dictionary(DICTIONARY_LIBRARIES
  lardataobj::AnalysisBase
  canvas::canvas
)

install_headers()
install_source()
