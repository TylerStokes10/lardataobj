cet_make_library(SOURCE OpticalDetectorData.cxx)

build_dictionary(DICTIONARY_LIBRARIES lardataobj_OpticalDetectorData canvas::canvas)

install_headers()
install_source()
