cet_make_library(
      SOURCE
        Calorimetry.cxx
        CosmicTag.cxx
        FlashMatch.cxx
        MVAOutput.cxx
        ParticleID.cxx
        T0.cxx
      LIBRARIES
        canvas::canvas
        cetlib_except::cetlib_except
        ROOT::Core)

build_dictionary(DICTIONARY_LIBRARIES lardataobj_AnalysisBase nusimdata::SimulationBase)

install_headers()
install_source()
