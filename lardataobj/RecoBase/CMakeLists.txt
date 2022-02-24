cet_make_library(
  SOURCE
    Cluster.cxx
    Edge.cxx
    EndPoint2D.cxx
    Event.cxx
    Hit.cxx
    OpFlash.cxx
    OpHit.cxx
    PCAxis.cxx
    PFParticle.cxx
    PFParticleMetadata.cxx
    Seed.cxx
    Shower.cxx
    Slice.cxx
    SpacePoint.cxx
    Track.cxx
    TrackingPlane.cxx
    TrackTrajectory.cxx
    Trajectory.cxx
    TrajectoryPointFlags.cxx
    Vertex.cxx
    Wire.cxx
  LIBRARIES
                   canvas::canvas
                   messagefacility::MF_MessageLogger
                   cetlib_except::cetlib_except
                   ROOT::Physics
                   ROOT::Matrix
                   ROOT::GenVector
  PUBLIC
     lardataobj::RawData
     larcorealg::geoVectorUtils
)

build_dictionary(DICTIONARY_LIBRARIES lardataobj_RecoBase)

add_subdirectory(AssnsDicts)
add_subdirectory(TrackingDicts)

install_headers(EXTRAS TrajectoryPointFlags.tcc TrackTrajectory.tcc Trajectory.tcc)
install_source(EXTRAS RecoBase.dox)
