/** ****************************************************************************
 * @file OpWaveform.cxx
 * @brief Definition of calibrated photon detector waveform.
 * @author tjyang@fnal.gov
 * @see  OpWaveform.h
 *
 * ****************************************************************************/

#include "lardataobj/RecoBase/OpWaveform.h"

// C/C++ standard libraries
#include <utility> // std::move()

namespace recob {

  //----------------------------------------------------------------------
  OpWaveform::OpWaveform() : fTimeStamp(0), fChannel(raw::InvalidChannelID), fSignalROI() {}

  //----------------------------------------------------------------------
  OpWaveform::OpWaveform(double time,
                         raw::ChannelID_t channel,
                         RegionsOfInterest_t const& sigROIlist)
    : fTimeStamp(time), fChannel(channel), fSignalROI(sigROIlist)
  {}

  //----------------------------------------------------------------------
  OpWaveform::OpWaveform(double time,
                         raw::ChannelID_t channel,
                         RegionsOfInterest_t&& sigROIlist)
    : fTimeStamp(time), fChannel(channel), fSignalROI(std::move(sigROIlist))
  {}

  //----------------------------------------------------------------------
  std::vector<float> OpWaveform::Signal() const
  {
    return {fSignalROI.begin(), fSignalROI.end()};
  } // OpWaveform::Signal()

}
////////////////////////////////////////////////////////////////////////
