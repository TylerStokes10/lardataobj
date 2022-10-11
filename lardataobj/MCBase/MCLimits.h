
#ifndef MCLIMITS_H
#define MCLIMITS_H

#include <climits>
#include <limits>

namespace sim {

  const double kINVALID_DOUBLE = std::numeric_limits<double>::max();

  const float kINVALID_FLOAT = std::numeric_limits<float>::max();

  const unsigned int kINVALID_UINT = std::numeric_limits<unsigned int>::max();

  const int kINVALID_INT = std::numeric_limits<int>::max();

}

#endif
