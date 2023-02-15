#ifndef PARTICLEANCESTRYMAP_CXX
#define PARTICLEANCESTRYMAP_CXX

#include "lardataobj/Simulation/ParticleAncestryMap.h"

namespace sim {

  void ParticleAncestryMap::SetMap(const std::map<int, std::set<int>>& map) { fParticleMap = map; }

  std::map<int, std::set<int>> ParticleAncestryMap::GetMap() const { return fParticleMap; }

  bool ParticleAncestryMap::HasDroppedDescendants(const int& trackid)
  {
    return fParticleMap.count(trackid) != 0;
  }

  std::set<int> ParticleAncestryMap::GetAllDroppedDescendants(const int& trackid)
  {
    return fParticleMap[trackid];
  }

  bool ParticleAncestryMap::HasAncestor(const int& trackid)
  {
    for (auto const& [ancestor, descendants] : fParticleMap) {
      if (descendants.count(trackid) != 0) return true;
    }

    return false;
  }

  int ParticleAncestryMap::GetAncestor(const int& trackid)
  {
    for (auto const& [ancestor, descendants] : fParticleMap) {
      if (descendants.count(trackid) != 0) return ancestor;
    }

    return -std::numeric_limits<int>::max();
  }
}

#endif
