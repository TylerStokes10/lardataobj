////////////////////////////////////////////////////////////////////////////
// \version
//
// \brief Definition of data product to hold ParticleID information
//
// \author brebel@fnal.gov, tjyang@fnal.gov
//
////////////////////////////////////////////////////////////////////////////
#ifndef ANAB_PARTICLEID_H
#define ANAB_PARTICLEID_H

#include <vector>
#include <iosfwd>
#include <iostream>
#include <iomanip>
#include <bitset>
#include "larcoreobj/SimpleTypesAndConstants/geo_types.h"
#include "lardataobj/AnalysisBase/ParticleID_VariableTypeEnums.h"

namespace anab {

struct sParticleIDAlgScores { ///< determined particle ID
  std::string fAlgName; ///< Algorithm name (to be defined by experiment). Set to "AlgNameNotSet" by default.
  kVariableType fVariableType; ///< Variable type enum: defined in ParticleID_VariableTypeEnums.h. Set to kNotSet by default.
  kTrackDir fTrackDir; ///< Track direction enum: defined in ParticleID_VariableTypeEnums.h. Set to kNoDirection by default.
  int fNdf; ///< Number of degrees of freedom used by algorithm, if applicable. Set to -9999 by default.
  int fAssumedPdg; ///< PDG of particle hypothesis assumed by algorithm, if applicable. Set to 0 by default.
  float fValue; ///< Result of Particle ID algorithm/test
  std::bitset<8> fPlaneMask; ///< Bitset for PlaneID used by algorithm, allowing for multiple planes and up to 8 total planes. Set to all 0s by default. Convention for bitset is that fPlaneMask[0] (i.e. bit 0) represents plane 0, bit 1 represents plane 1, and so on (with plane conventions defined by the experiment).
  geo::PlaneID fPlaneID_old; ///< For backwards compatibility only. Can't convert geo::PlaneID to PlaneMask in ioread when reading old files, so have to store it in this struct. Should be filled for old files only (where a std::bitset PlaneMask is not available).

  sParticleIDAlgScores(){
  fAlgName = "AlgNameNotSet";
  fVariableType = kNotSet;
  fTrackDir = kNoDirection;
  fAssumedPdg = 0;
  fNdf = -9999;
  fValue = -9999.;
  // fPlaneMask will use default constructor: sets all values to 0
  // fPlaneID_old will use default constructor: sets isValid to false
  }

  /// Use this to access plane mask instead of sParticleIDAlgScores.fPlaneMask for backwards compatibility. 
  std::bitset<8> getPlaneMask(){ 
    // First check if fPlaneMask has been filled. If it has, return that
    if (!fPlaneMask.none()){
      return fPlaneMask;
    }
    
    // If fPlaneMask has not been filled, check if fPlaneID_old has been filled. Default (i.e. not filled) PlaneIDs are set to be invalid
    if (fPlaneID_old.isValid){
      fPlaneMask.set(fPlaneID_old.Plane);
      return fPlaneMask;
    }

    // If neither, return fPlaneMask, which we know if it gets here is invalid (all 0s)
    return fPlaneMask;
  }
};

  class ParticleID{
  public:

    ParticleID();
    
    std::vector<sParticleIDAlgScores> fParticleIDAlgScores; ///< Vector of structs to hold outputs from generic PID algorithms

  public:

    ParticleID(std::vector<anab::sParticleIDAlgScores> &ParticleIDAlgScores);

    friend std::ostream& operator << (std::ostream &o, ParticleID const& a);

    const std::vector<anab::sParticleIDAlgScores> & ParticleIDAlgScores() const;

  };

}

inline const std::vector<anab::sParticleIDAlgScores> & anab::ParticleID::ParticleIDAlgScores() const { return fParticleIDAlgScores; }

#endif //ANAB_PARTICLEID_H
