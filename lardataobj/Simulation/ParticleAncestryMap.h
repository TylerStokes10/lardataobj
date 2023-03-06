/**
 * \class ParticleAncestryMap
 *
 * \brief Product to store the mapping of track IDs that were
 *        dropped in largeant back to their ancestor that wasn't
 *        dropped.
 *
 * \author Henry Lay (h.lay@lancaster.ac.uk)
 *
 */

#ifndef PARTICLEANCESTRYMAP_H
#define PARTICLEANCESTRYMAP_H

#include <map>
#include <set>

namespace sim {

  class ParticleAncestryMap {

    std::map<int, std::set<int>> fParticleMap;

  public:
    ParticleAncestryMap() {}

    ParticleAncestryMap(const std::map<int, std::set<int>>& particleMap) : fParticleMap(particleMap)
    {}

    void SetMap(const std::map<int, std::set<int>>& map);

    std::map<int, std::set<int>> const& GetMap() const;

    bool HasDroppedDescendants(const int trackid);

    std::set<int> const& GetAllDroppedDescendants(const int trackid);

    bool HasAncestor(const int trackid);

    int GetAncestor(const int trackid);
  };
}
#endif
