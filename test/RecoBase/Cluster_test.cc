/**
 * @file    Cluster_test.cc
 * @brief   Simple test on a recob::Cluster object
 * @author  Gianluca Petrillo (petrillo@fnal.gov)
 * @date    20150114
 * @version 1.0
 *
 * This test simply creates recob::Cluster objects and verifies that the values
 * it can access are the right ones.
 *
 * See http://www.boost.org/libs/test for the Boost test library home page.
 *
 * Timing:
 * version 1.0: ~1.5" (debug mode)
 */

// C/C++ standard libraries
#include <utility> // std::move()


// Boost libraries
/*
 * Boost Magic: define the name of the module;
 * and do that before the inclusion of Boost unit test headers
 * because it will change what they provide.
 * Among the those, there is a main() function and some wrapping catching
 * unhandled exceptions and considering them test failures, and probably more.
 * This also makes fairly complicate to receive parameters from the command line
 * (for example, a random seed).
 */
#define BOOST_TEST_MODULE ( cluster_test )
#include "boost/test/unit_test.hpp"

// LArSoft libraries
#include "larcoreobj/SimpleTypesAndConstants/geo_types.h" // geo::View_t
#include "lardataobj/RecoBase/Cluster.h"



//------------------------------------------------------------------------------
//--- Test code
//


void CheckCluster(
  recob::Cluster const& cluster,
  float start_wire,
  float sigma_start_wire,
  float start_tick,
  float sigma_start_tick,
  float start_charge,
  float start_angle,
  float start_opening,
  float end_wire,
  float sigma_end_wire,
  float end_tick,
  float sigma_end_tick,
  float end_charge,
  float end_angle,
  float end_opening,
  float integral,
  float integral_stddev,
  float summedADC,
  float summedADC_stddev,
  unsigned int n_hits,
  float multiple_hit_density,
  float width,
  recob::Cluster::ID_t ID,
  geo::View_t view,
  geo::PlaneID const& plane
) {

  // verify that the values are as expected
  // - NHits
  BOOST_TEST(cluster.NHits() == n_hits);

  // - start wire
  BOOST_TEST(cluster.StartWire() == start_wire);

  // - start wire uncertainty
  BOOST_TEST(cluster.SigmaStartWire() == sigma_start_wire);

  // - start tick
  BOOST_TEST(cluster.StartTick() == start_tick);

  // - start tick uncertainty
  BOOST_TEST(cluster.SigmaStartTick() == sigma_start_tick);

  // - end wire
  BOOST_TEST(cluster.EndWire() == end_wire);

  // - end wire uncertainty
  BOOST_TEST(cluster.SigmaEndWire() == sigma_end_wire);

  // - end tick
  BOOST_TEST(cluster.EndTick() == end_tick);

  // - end tick uncertainty
  BOOST_TEST(cluster.SigmaEndTick() == sigma_end_tick);

  // - wire coordinates
  BOOST_TEST
    (cluster.WireCoord(recob::Cluster::clStart) == start_wire);
  BOOST_TEST
    (cluster.WireCoord((unsigned int) recob::Cluster::clStart) == start_wire);
  BOOST_TEST
    (cluster.WireCoord(recob::Cluster::clEnd) == end_wire);
  BOOST_TEST
    (cluster.WireCoord((unsigned int) recob::Cluster::clEnd) == end_wire);

  // - tick coordinates
  BOOST_TEST
    (cluster.TickCoord(recob::Cluster::clStart) == start_tick);
  BOOST_TEST
    (cluster.TickCoord((unsigned int) recob::Cluster::clStart) == start_tick);
  BOOST_TEST
    (cluster.TickCoord(recob::Cluster::clEnd) == end_tick);
  BOOST_TEST
    (cluster.TickCoord((unsigned int) recob::Cluster::clEnd) == end_tick);

  // - start charge
  BOOST_TEST(cluster.StartCharge() == start_charge);

  // - start angle
  BOOST_TEST(cluster.StartAngle() == start_angle);

  // - start opening angle
  BOOST_TEST(cluster.StartOpeningAngle() == start_opening);

  // - end charge
  BOOST_TEST(cluster.EndCharge() == end_charge);

  // - end angle
  BOOST_TEST(cluster.EndAngle() == end_angle);

  // - end opening angle
  BOOST_TEST(cluster.EndOpeningAngle() == end_opening);

  // - edge charge
  BOOST_TEST
    (cluster.EdgeCharge(recob::Cluster::clStart) == start_charge);
  BOOST_TEST
    (cluster.EdgeCharge((unsigned int) recob::Cluster::clStart) == start_charge);
  BOOST_TEST
    (cluster.EdgeCharge(recob::Cluster::clEnd) == end_charge);
  BOOST_TEST
    (cluster.EdgeCharge((unsigned int) recob::Cluster::clEnd) == end_charge);

  // - angle
  BOOST_TEST
    (cluster.Angle(recob::Cluster::clStart) == start_angle);
  BOOST_TEST
    (cluster.Angle((unsigned int) recob::Cluster::clStart) == start_angle);
  BOOST_TEST
    (cluster.Angle(recob::Cluster::clEnd) == end_angle);
  BOOST_TEST
    (cluster.Angle((unsigned int) recob::Cluster::clEnd) == end_angle);

  // - edge opening angle
  BOOST_TEST
    (cluster.OpeningAngle(recob::Cluster::clStart) == start_opening);
  BOOST_TEST
    (cluster.OpeningAngle((unsigned int) recob::Cluster::clStart) == start_opening);
  BOOST_TEST
    (cluster.OpeningAngle(recob::Cluster::clEnd) == end_opening);
  BOOST_TEST
    (cluster.OpeningAngle((unsigned int) recob::Cluster::clEnd) == end_opening);

  // - integral
  BOOST_TEST(cluster.Integral() == integral);

  // - integral standard deviation
  BOOST_TEST(cluster.IntegralStdDev() == integral_stddev);

  // - integral average
  const float integral_average = (n_hits != 0)? integral / n_hits: 0.;
  BOOST_TEST(cluster.IntegralAverage() == integral_average);

  // - summed ADC
  BOOST_TEST(cluster.SummedADC() == summedADC);

  // - summed ADC standard deviation
  BOOST_TEST(cluster.SummedADCstdDev() == summedADC_stddev);

  // - summed ADC average
  const float summedADC_average = (n_hits != 0)? summedADC / n_hits: 0.;
  BOOST_TEST(cluster.SummedADCaverage() == summedADC_average);

  // - charge
  BOOST_TEST(cluster.Charge(recob::Cluster::cmFit) == integral);
  BOOST_TEST
    (cluster.Charge((unsigned int) recob::Cluster::cmFit) == integral);
  BOOST_TEST
    (cluster.Charge(recob::Cluster::cmADC) == summedADC);
  BOOST_TEST
    (cluster.Charge((unsigned int) recob::Cluster::cmADC) == summedADC);

  // - charge standard deviation
  BOOST_TEST
    (cluster.ChargeStdDev(recob::Cluster::cmFit) == integral_stddev);
  BOOST_TEST
    (cluster.ChargeStdDev((unsigned int) recob::Cluster::cmFit) == integral_stddev);
  BOOST_TEST
    (cluster.ChargeStdDev(recob::Cluster::cmADC) == summedADC_stddev);
  BOOST_TEST
    (cluster.ChargeStdDev((unsigned int) recob::Cluster::cmADC) == summedADC_stddev);

  // - charge standard deviation
  BOOST_TEST
    (cluster.ChargeAverage(recob::Cluster::cmFit) == integral_average);
  BOOST_TEST
    (cluster.ChargeAverage((unsigned int) recob::Cluster::cmFit) == integral_average);
  BOOST_TEST
    (cluster.ChargeAverage(recob::Cluster::cmADC) == summedADC_average);
  BOOST_TEST
    (cluster.ChargeAverage((unsigned int) recob::Cluster::cmADC) == summedADC_average);

  // - wires over hits
  BOOST_TEST(cluster.MultipleHitDensity() == multiple_hit_density);

  // - width
  BOOST_TEST(cluster.Width() == width);

  // - ID
  BOOST_TEST(cluster.ID() == ID);

  // - view
  BOOST_TEST(cluster.View() == view);

  // - plane
  BOOST_TEST(cluster.Plane() == plane);
  BOOST_TEST(cluster.hasPlane() == plane.isValid);

} // CheckCluster()


void ClusterTestDefaultConstructor() {

  //
  // Part I: initialization of cluster inputs
  //
  // these are the values expected for a default-constructed cluster
  const float start_wire         =    0.0;
  const float sigma_start_wire   =    0.0;
  const float start_tick         =    0.0;
  const float sigma_start_tick   =    0.0;
  const float start_charge       =    0.0;
  const float start_angle        =    0.0;
  const float start_opening      =    0.0;
  const float end_wire           =    0.0;
  const float sigma_end_wire     =    0.0;
  const float end_tick           =    0.0;
  const float sigma_end_tick     =    0.0;
  const float end_charge         =    0.0;
  const float end_angle          =    0.0;
  const float end_opening        =    0.0;
  const float integral           =    0.0;
  const float integral_stddev    =    0.0;
  const float summedADC          =    0.0;
  const float summedADC_stddev   =    0.0;
  const unsigned int n_hits      =    0;
  const float multiple_hit_density =    0.0;
  const float width              =    0.0;
  const recob::Cluster::ID_t ID  = recob::Cluster::InvalidID;
  const geo::View_t view         = geo::kUnknown;
  const geo::PlaneID plane;

  //
  // Part II: default constructor
  //
  // step II.1: create a cluster with default constructor
  recob::Cluster cluster;


  // step II.2: verify that the values are as expected
  CheckCluster(cluster,
    start_wire,
    sigma_start_wire,
    start_tick,
    sigma_start_tick,
    start_charge,
    start_angle,
    start_opening,
    end_wire,
    sigma_end_wire,
    end_tick,
    sigma_end_tick,
    end_charge,
    end_angle,
    end_opening,
    integral,
    integral_stddev,
    summedADC,
    summedADC_stddev,
    n_hits,
    multiple_hit_density,
    width,
    ID,
    view,
    plane
    );

} // WireTestDefaultConstructor()


void ClusterTestCustomConstructor() {

  //
  // Part I: initialization of cluster inputs
  //
  const float start_wire         =   12.5;
  const float sigma_start_wire   =    1.0;
  const float start_tick         =  141.3;
  const float sigma_start_tick   =    0.2;
  const float start_charge       =   45.2;
  const float start_angle        =    1.5;
  const float start_opening      =    0.7;
  const float end_wire           =  223.4;
  const float sigma_end_wire     =    1.0;
  const float end_tick           =  563.2;
  const float sigma_end_tick     =    0.3;
  const float end_charge         =  152.1;
  const float end_angle          =    0.6;
  const float end_opening        =    0.1;
  const float integral           = 4856.7;
  const float integral_stddev    =    4.3;
  const float summedADC          = 4702.4;
  const float summedADC_stddev   =    6.2;
  const unsigned int n_hits      =  210;
  const float multiple_hit_density =    1.0;
  const float width              =   75.2;
  const recob::Cluster::ID_t ID  = 1234;
  const geo::View_t view         = geo::kV;
  const geo::PlaneID plane(0, 1, 2);

  //
  // Part II: constructor
  //
  // step II.1: create a cluster
  recob::Cluster cluster(
    start_wire,
    sigma_start_wire,
    start_tick,
    sigma_start_tick,
    start_charge,
    start_angle,
    start_opening,
    end_wire,
    sigma_end_wire,
    end_tick,
    sigma_end_tick,
    end_charge,
    end_angle,
    end_opening,
    integral,
    integral_stddev,
    summedADC,
    summedADC_stddev,
    n_hits,
    multiple_hit_density,
    width,
    ID,
    view,
    plane,
    recob::Cluster::Sentry
    );


  // step II.2: verify that the values are as expected
  CheckCluster(cluster,
    start_wire,
    sigma_start_wire,
    start_tick,
    sigma_start_tick,
    start_charge,
    start_angle,
    start_opening,
    end_wire,
    sigma_end_wire,
    end_tick,
    sigma_end_tick,
    end_charge,
    end_angle,
    end_opening,
    integral,
    integral_stddev,
    summedADC,
    summedADC_stddev,
    n_hits,
    multiple_hit_density,
    width,
    ID,
    view,
    plane
    );


} // ClusterTestCustomConstructor()



void ClusterTestCopyMoveOperations() {

  //
  // Part I: initialization of wire inputs
  //
  const float start_wire         =   12.5;
  const float sigma_start_wire   =    1.0;
  const float start_tick         =  141.3;
  const float sigma_start_tick   =    0.2;
  const float start_charge       =   45.2;
  const float start_angle        =    1.5;
  const float start_opening      =    0.7;
  const float end_wire           =  223.4;
  const float sigma_end_wire     =    1.0;
  const float end_tick           =  563.2;
  const float sigma_end_tick     =    0.3;
  const float end_charge         =  152.1;
  const float end_angle          =    0.6;
  const float end_opening        =    0.1;
  const float integral           = 4856.7;
  const float integral_stddev    =    4.3;
  const float summedADC          = 4702.4;
  const float summedADC_stddev   =    6.2;
  const unsigned int n_hits      =  210;
  const float multiple_hit_density =    1.0;
  const float width              =   75.2;
  const recob::Cluster::ID_t ID  = 1234;
  const geo::View_t view         = geo::kV;
  const geo::PlaneID plane(0, 1, 2);

  //
  // Part II: full constructor (tested elsewhere)
  //
  const recob::Cluster cluster(
    start_wire,
    sigma_start_wire,
    start_tick,
    sigma_start_tick,
    start_charge,
    start_angle,
    start_opening,
    end_wire,
    sigma_end_wire,
    end_tick,
    sigma_end_tick,
    end_charge,
    end_angle,
    end_opening,
    integral,
    integral_stddev,
    summedADC,
    summedADC_stddev,
    n_hits,
    multiple_hit_density,
    width,
    ID,
    view,
    plane,
    recob::Cluster::Sentry
    );


  //
  // Part III: copy constructor
  //
  // step III.1: copy the cluster
  recob::Cluster cluster_copy(cluster);

  // step III.2: verify that the original cluster has not changed
  CheckCluster(cluster,
    start_wire,
    sigma_start_wire,
    start_tick,
    sigma_start_tick,
    start_charge,
    start_angle,
    start_opening,
    end_wire,
    sigma_end_wire,
    end_tick,
    sigma_end_tick,
    end_charge,
    end_angle,
    end_opening,
    integral,
    integral_stddev,
    summedADC,
    summedADC_stddev,
    n_hits,
    multiple_hit_density,
    width,
    ID,
    view,
    plane
    );

  // step III.3: verify that the copy cluster is as the original one
  CheckCluster(cluster_copy,
    start_wire,
    sigma_start_wire,
    start_tick,
    sigma_start_tick,
    start_charge,
    start_angle,
    start_opening,
    end_wire,
    sigma_end_wire,
    end_tick,
    sigma_end_tick,
    end_charge,
    end_angle,
    end_opening,
    integral,
    integral_stddev,
    summedADC,
    summedADC_stddev,
    n_hits,
    multiple_hit_density,
    width,
    ID,
    view,
    plane
    );


  //
  // Part IV: move constructor
  //
  // step IV.1: move the cluster
  recob::Cluster cluster_move(std::move(cluster_copy));

  // step IV.2: verify that the original cluster differ only by the invalid ID
  CheckCluster(cluster_copy,
    start_wire,
    sigma_start_wire,
    start_tick,
    sigma_start_tick,
    start_charge,
    start_angle,
    start_opening,
    end_wire,
    sigma_end_wire,
    end_tick,
    sigma_end_tick,
    end_charge,
    end_angle,
    end_opening,
    integral,
    integral_stddev,
    summedADC,
    summedADC_stddev,
    n_hits,
    multiple_hit_density,
    width,
    recob::Cluster::InvalidID,
    view,
    plane
    );

  // step IV.3: verify that the new cluster is as the original was
  CheckCluster(cluster_move,
    start_wire,
    sigma_start_wire,
    start_tick,
    sigma_start_tick,
    start_charge,
    start_angle,
    start_opening,
    end_wire,
    sigma_end_wire,
    end_tick,
    sigma_end_tick,
    end_charge,
    end_angle,
    end_opening,
    integral,
    integral_stddev,
    summedADC,
    summedADC_stddev,
    n_hits,
    multiple_hit_density,
    width,
    ID,
    view,
    plane
    );


  //
  // Part V: copy assignment
  //
  // step V.1: copy over the cluster
  cluster_copy = cluster;

  // step V.2: verify that the original cluster is unchanged
  CheckCluster(cluster,
    start_wire,
    sigma_start_wire,
    start_tick,
    sigma_start_tick,
    start_charge,
    start_angle,
    start_opening,
    end_wire,
    sigma_end_wire,
    end_tick,
    sigma_end_tick,
    end_charge,
    end_angle,
    end_opening,
    integral,
    integral_stddev,
    summedADC,
    summedADC_stddev,
    n_hits,
    multiple_hit_density,
    width,
    ID,
    view,
    plane
    );

  // step V.3: verify that the new cluster is as the original
  CheckCluster(cluster_copy,
    start_wire,
    sigma_start_wire,
    start_tick,
    sigma_start_tick,
    start_charge,
    start_angle,
    start_opening,
    end_wire,
    sigma_end_wire,
    end_tick,
    sigma_end_tick,
    end_charge,
    end_angle,
    end_opening,
    integral,
    integral_stddev,
    summedADC,
    summedADC_stddev,
    n_hits,
    multiple_hit_density,
    width,
    ID,
    view,
    plane
    );


  //
  // Part VI: move assignment (regular)
  //
  // step VI.1: move the cluster
  cluster_move = std::move(cluster_copy);

  // step IV.2: verify that the original cluster differ only by the invalid ID
  CheckCluster(cluster_copy,
    start_wire,
    sigma_start_wire,
    start_tick,
    sigma_start_tick,
    start_charge,
    start_angle,
    start_opening,
    end_wire,
    sigma_end_wire,
    end_tick,
    sigma_end_tick,
    end_charge,
    end_angle,
    end_opening,
    integral,
    integral_stddev,
    summedADC,
    summedADC_stddev,
    n_hits,
    multiple_hit_density,
    width,
    recob::Cluster::InvalidID,
    view,
    plane
    );

  // step VI.3: verify that the new cluster is as the original was
  CheckCluster(cluster_move,
    start_wire,
    sigma_start_wire,
    start_tick,
    sigma_start_tick,
    start_charge,
    start_angle,
    start_opening,
    end_wire,
    sigma_end_wire,
    end_tick,
    sigma_end_tick,
    end_charge,
    end_angle,
    end_opening,
    integral,
    integral_stddev,
    summedADC,
    summedADC_stddev,
    n_hits,
    multiple_hit_density,
    width,
    ID,
    view,
    plane
    );

  //
  // Part VII: move assignment (self)
  //
  // step VII.1: move the cluster into itself
  // for c2: redundant and illegal => not testing it any more
  /*
  cluster_move = std::move(cluster_move);

  // step VII.3: verify that the cluster is unchanged
  CheckCluster(cluster_move,
    start_wire,
    sigma_start_wire,
    start_tick,
    sigma_start_tick,
    start_charge,
    start_angle,
    start_opening,
    end_wire,
    sigma_end_wire,
    end_tick,
    sigma_end_tick,
    end_charge,
    end_angle,
    end_opening,
    integral,
    integral_stddev,
    summedADC,
    summedADC_stddev,
    n_hits,
    multiple_hit_density,
    width,
    ID,
    view,
    plane
    );
  */

} // ClusterTestCopyMoveOperations()



//------------------------------------------------------------------------------
//--- registration of tests
//
// Boost needs now to know which tests we want to run.
// Tests are "automatically" registered, hence the BOOST_AUTO_TEST_CASE()
// macro name. The argument is the name of the test; each step may have a
// number of checks and it will fail if any of them does.
//

BOOST_AUTO_TEST_CASE(ClusterDefaultConstructor) {
  ClusterTestDefaultConstructor();
}

BOOST_AUTO_TEST_CASE(ClusterCustomConstructors) {
  ClusterTestCustomConstructor();
}

BOOST_AUTO_TEST_CASE(ClusterCopyMoveOperations) {
  ClusterTestCopyMoveOperations();
}
