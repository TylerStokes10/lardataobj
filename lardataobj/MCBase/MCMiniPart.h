/**
 * \file MCMiniPart.h
 *
 * \ingroup MCBase
 *
 * \brief Class def header for MCMiniPart data container
 *
 * @author Temigo
 */

/** \addtogroup MCBase

    @{*/
#ifndef MCMINIPART_H
#define MCMINIPART_H

// LArSoft
//#include "lardataobj/MCBase/MCStep.h"
#include "lardataobj/MCBase/MCLimits.h" // kINVALID_X
#include "nusimdata/SimulationBase/MCParticle.h"
#include "nusimdata/SimulationBase/MCTruth.h" // simb::Origin_t

// ROOT libraries
#include <TVector3.h>

// STL
//#include <set>
#include <utility> // std::pair<>
#include <vector>

#include "TLorentzVector.h"

namespace sim
{

  class MCMiniPart {

  public:

    MCMiniPart(){};

    void ScaleStartMom(double factor) { _start_mom *= factor; }
    void ScaleEndMom(double factor)  { _end_mom *= factor; }
    void AddDaughter(unsigned int d) {
      if (!this->HasDaughter(d))
        _daughters.push_back(d);
    }
    bool HasDaughter(unsigned int d) const {
      return std::find(_daughters.begin(), _daughters.end(), d) != _daughters.end();
    }

    // Getters
    const simb::Origin_t& Origin () const { return _origin; }
    int            PdgCode() const { return _pdgcode; }
    unsigned int   TrackID() const { return _track_id; }
    const std::string&    Process() const { return _process; }
    unsigned int   Mother()  const { return _mother; }
    unsigned int   Ancestor() const { return _ancestor; }
    const TLorentzVector& StartVtx() const { return _start_vtx; }
    const TLorentzVector& StartMom() const { return _start_mom; }
    const TLorentzVector& EndVtx()   const { return _end_vtx; }
    const TLorentzVector& EndMom()   const { return _end_mom; }
    const std::vector<std::pair<TLorentzVector,TLorentzVector> >& DetPath() const { return _det_path; }
    const std::vector<unsigned int>& Daughters() const { return _daughters; }

    // Setters
    void Origin (simb::Origin_t o) { _origin = o; }
    void PdgCode(int id)           { _pdgcode = id; }
    void TrackID(unsigned int id)  { _track_id = id; }
    void Process(const std::string &name) { _process = name; }
    void Mother(unsigned int id)   { _mother = id; }
    void Ancestor(unsigned int id) { _ancestor = id; }
    void StartVtx(const TLorentzVector& vtx) { _start_vtx = vtx; }
    void StartMom(const TLorentzVector& mom) { _start_mom = mom; }
    void EndVtx(const TLorentzVector& vtx)   { _end_vtx = vtx; }
    void EndMom(const TLorentzVector& mom)   { _end_mom = mom; }
    void DetPath(const std::vector<std::pair<TLorentzVector,TLorentzVector> >& p) { _det_path = p; }
    void DetPath(std::vector<std::pair<TLorentzVector,TLorentzVector> >&& p) { _det_path = std::move(p); }
    void Daughters(const std::vector<unsigned int>& d) { _daughters = d; }
    void Daughters(std::vector<unsigned int>&& d) { _daughters = std::move(d); }

    operator simb::MCParticle() const {
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

    MCMiniPart(const simb::MCParticle& p) {
      _daughters.clear();
      _det_path.clear();
      _track_id = (unsigned int) p.TrackId();
      _pdgcode  = p.PdgCode();
      _mother   = (unsigned int) p.Mother();
      _process  = p.Process();
      _start_vtx = p.Position();
      _start_mom = 1.e3 * p.Momentum(); // Change units to LArSoft (MeV, cm, us)
      _end_vtx = p.EndPosition();
      _end_mom = 1.e3 * p.EndMomentum(); // idem as above
    }

  protected:
    unsigned int   _track_id{kINVALID_UINT};
    std::string    _process{};
    unsigned int   _mother{kINVALID_UINT};
    unsigned int   _ancestor{kINVALID_UINT};
    int            _pdgcode{kINVALID_INT};
    TLorentzVector _start_vtx{TLorentzVector(kINVALID_DOUBLE, kINVALID_DOUBLE, kINVALID_DOUBLE, kINVALID_DOUBLE)};
    TLorentzVector _start_mom{TLorentzVector(kINVALID_DOUBLE, kINVALID_DOUBLE, kINVALID_DOUBLE, kINVALID_DOUBLE)}; ///< Start momentum in MeV
    TLorentzVector _end_vtx{TLorentzVector(kINVALID_DOUBLE, kINVALID_DOUBLE, kINVALID_DOUBLE, kINVALID_DOUBLE)};
    TLorentzVector _end_mom{TLorentzVector(kINVALID_DOUBLE, kINVALID_DOUBLE, kINVALID_DOUBLE, kINVALID_DOUBLE)}; ///< End momentum in MeV
    std::vector<std::pair<TLorentzVector,TLorentzVector> > _det_path;
    std::vector<unsigned int> _daughters;
    ::simb::Origin_t _origin{::simb::kUnknown};
  };
} // namespace sim

#endif
