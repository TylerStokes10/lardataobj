cet_make(LIBRARIES lardataobj_RawData
                   canvas::canvas
                   messagefacility::MF_MessageLogger
                   cetlib_except::cetlib_except
                   ROOT::Physics
                   ROOT::Matrix
                   ROOT::GenVector
                   NO_DICTIONARY) ### MIGRATE-ACTION-RECOMMENDED (migrate-3.05.03) - deprecated: use cet_make_library(), build_dictonary(), cet_plugin() with explicit source lists and plugin base types

art_dictionary(DICTIONARY_LIBRARIES lardataobj_RecoBase)

add_subdirectory(AssnsDicts)
add_subdirectory(TrackingDicts)

install_headers(EXTRAS TrajectoryPointFlags.tcc TrackTrajectory.tcc Trajectory.tcc)
install_source(EXTRAS RecoBase.dox)
