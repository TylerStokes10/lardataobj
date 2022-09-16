/**
 * \file MCMiniPart.h
 *
 * \ingroup MCBase
 *
 * \brief Class def header for MCMiniPart data container
 *
 * It is the same information as MCParticleLite. The only difference
 * is in the units of momentum/energy: MeV for MCMiniPart and GeV for
 * MCParticleLite. This is to keep backwards compatibility for modules
 * and experiments that might be assuming sim::MCMiniPart has units of
 * MeV for momentum/energy.
 *
 * @author Temigo
 */

/** \addtogroup MCBase

    @{*/
#ifndef MCMINIPART_H
#define MCMINIPART_H

// LArSoft
#include "lardataobj/MCBase/MCParticleLite.h"
#include "nusimdata/SimulationBase/MCParticle.h"

namespace sim
{

  class MCMiniPart : public MCParticleLite {

  public:

    MCMiniPart(){};

    void ScaleStartMom(double factor) { _start_mom *= factor; }
    void ScaleEndMom(double factor)  { _end_mom *= factor; }

    operator simb::MCParticle() const override {
      simb::MCParticle mcpart(_track_id,
                              _pdgcode,
                              _process,
                              _mother);
      // Also converting back from LArSoft units
      mcpart.AddTrajectoryPoint(_start_vtx, 1.e-3 * _start_mom);
      mcpart.AddTrajectoryPoint(_end_vtx, 1.e-3 * _end_mom);
      for (auto const & d : _daughters) mcpart.AddDaughter(d);
      return mcpart;
    }

    MCMiniPart(const simb::MCParticle& p) : MCParticleLite(p) {
      ScaleStartMom(1.e3); // Change units to (MeV, cm, us)
      ScaleEndMom(1.e3); // idem as above
    }

    MCMiniPart(const sim::MCParticleLite& p) : MCParticleLite(p) {
      ScaleStartMom(1.e3); // Change units to (MeV, cm, us)
      ScaleEndMom(1.e3); // idem as above
    }

  };
} // namespace sim

#endif
