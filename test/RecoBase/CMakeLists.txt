cet_test(Wire_test USE_BOOST_UNIT
  LIBRARIES PRIVATE
  lardataobj::RecoBase
  larcoreobj::SimpleTypesAndConstants
)

cet_test(Hit_test USE_BOOST_UNIT
  LIBRARIES PRIVATE
  lardataobj::RecoBase
  larcoreobj::SimpleTypesAndConstants
)

cet_test(Cluster_test USE_BOOST_UNIT
  LIBRARIES PRIVATE
  lardataobj::RecoBase
  larcoreobj::SimpleTypesAndConstants
)

cet_test(PointCharge_test USE_BOOST_UNIT
  LIBRARIES PRIVATE
  lardataobj::RecoBase
)

cet_test(Edge_test USE_BOOST_UNIT
  LIBRARIES PRIVATE
  lardataobj::RecoBase
)

cet_test(TrajectoryPointFlags_test USE_BOOST_UNIT
  LIBRARIES PRIVATE
  lardataobj::RecoBase
)

cet_test(Trajectory_test USE_BOOST_UNIT
  LIBRARIES PRIVATE
  lardataobj::RecoBase
  larcoreobj::headers
  ROOT::Matrix
  ROOT::Physics
)

cet_test(TrackTrajectory_test USE_BOOST_UNIT
  LIBRARIES PRIVATE
  lardataobj::RecoBase
  larcoreobj::headers
  ROOT::Matrix
  ROOT::Physics
)

install_headers()
install_source()
