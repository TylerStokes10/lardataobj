cet_make_library(SOURCE load_fixit_file.cxx
  LIBRARIES PRIVATE ROOT::RIO cetlib::cetlib)

install_source()
install_fw(LIST simIDE_streamer_info.root)
