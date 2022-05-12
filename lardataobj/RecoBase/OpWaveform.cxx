/** ****************************************************************************
 * @file OpWaveform.cxx
 * @brief Definition of basic channel signal object.
 * @author brebel@fnal.gov
 * @see  OpWaveform.h
 *
 * ****************************************************************************/

#include "lardataobj/RecoBase/OpWaveform.h"

// C/C++ standard libraries
#include <utility> // std::move()

namespace recob{

  //----------------------------------------------------------------------
  OpWaveform::OpWaveform()
    : fChannel(raw::InvalidChannelID)
    , fView(geo::kUnknown)
    , fSignalROI()
    {}

  //----------------------------------------------------------------------
  OpWaveform::OpWaveform(
    RegionsOfInterest_t const& sigROIlist,
    raw::ChannelID_t channel,
    geo::View_t view
    )
    : fChannel(channel)
    , fView(view)
    , fSignalROI(sigROIlist)
    {}

  //----------------------------------------------------------------------
  OpWaveform::OpWaveform(
    RegionsOfInterest_t&& sigROIlist,
    raw::ChannelID_t channel,
    geo::View_t view
    )
    : fChannel(channel)
    , fView(view)
    , fSignalROI(std::move(sigROIlist))
    {}


  //----------------------------------------------------------------------
  std::vector<float> OpWaveform::Signal() const {
    return { fSignalROI.begin(), fSignalROI.end() };
  } // OpWaveform::Signal()


}
////////////////////////////////////////////////////////////////////////

