#ifndef MVAPIDRESULT_H
#define MVAPIDRESULT_H

#include <map>
#include <string>
#include <vector>

namespace anab {

  struct MVAPIDResult {

    float evalRatio;
    float concentration;
    float coreHaloRatio;
    float conicalness;
    float dEdxStart;
    float dEdxEnd;
    float dEdxEndRatio;
    float length;
    float nSpacePoints;
    unsigned int trackID;
    int isTrack;
    int isStoppingReco;

    friend bool operator<(const MVAPIDResult& a, const MVAPIDResult& b);

    std::map<std::string, double> mvaOutput;
  };

  bool operator<(const MVAPIDResult& a, const MVAPIDResult& b)
  {
    return a.nSpacePoints < b.nSpacePoints;
  }

}

#endif
