cet_make(NO_DICTIONARY
         LIBRARIES
           larcoreobj_SummaryData
           canvas::canvas
           messagefacility::MF_MessageLogger
           cetlib_except::cetlib_except
           ROOT::Core) ### MIGRATE-ACTION-RECOMMENDED (migrate-3.05.03) - deprecated: use cet_make_library(), build_dictonary(), cet_plugin() with explicit source lists and plugin base types

art_dictionary(DICTIONARY_LIBRARIES lardataobj_RawData)

install_headers()
install_source()
