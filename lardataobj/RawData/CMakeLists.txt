cet_make_library(
         SOURCE
           AuxDetDigit.cxx
           BeamInfo.cxx
           DAQHeader.cxx
           ExternalTrigger.cxx
           OpDetPulse.cxx
           raw.cxx
           RawDigit.cxx
           TriggerData.cxx
         LIBRARIES
           larcoreobj::SummaryData
           canvas::canvas
           messagefacility::MF_MessageLogger
           cetlib_except::cetlib_except
           ROOT::Core)

build_dictionary(DICTIONARY_LIBRARIES lardataobj_RawData)

install_headers()
install_source()
