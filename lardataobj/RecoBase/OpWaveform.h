/** ****************************************************************************
 * @file lardataobj/RecoBase/OpWaveform.h
 * @brief Declaration of basic channel signal object.
 * @author brebel@fnal.gov
 * @see  lardataobj/RecoBase/OpWaveform.cxx
 */

/*
 * Changes
 * 20190510 Gianluca Petrillo (petrillo@slac.stanford.edu)
 *   updated documentation
 * 20141211 Gianluca Petrillo (petrillo@fnal.gov)
 *   data architecture revision changes:
 *   - fSignalType and SignalType() removed
 *   - fRawDigit and RawDigit() removed
 *   - fChannel and Channel() added
 *   - constructors now take directly a RawDigit, not its art::Ptr
 *
 * ****************************************************************************/

#ifndef LARDATAOBJ_RECOBASE_OPWAVEFORM_H
#define LARDATAOBJ_RECOBASE_OPWAVEFORM_H


// LArSoft libraries
#include "lardataobj/Utilities/sparse_vector.h"
#include "lardataobj/RawData/RDTimeStamp.h"
#include "larcoreobj/SimpleTypesAndConstants/RawTypes.h" // raw::ChannelID_t
#include "larcoreobj/SimpleTypesAndConstants/geo_types.h"

// C/C++ standard libraries
#include <vector>
#include <cstddef> // std::size_t


namespace recob {

  /**
   * @brief Class holding the regions of interest of signal from a channel.
   * @note Despite the name, this class is associated to a readout channel, not
   *       just a wire
   *
   * The channel content is expected to have been filtered from noise and
   * corrected for electronics response, a process often called in jargon
   * "deconvolution".
   * 
   * The content is presented as calibrated ADC counts, pedestal removed, as
   * function of time in discrete TDC units. The time is expected to be the same
   * as for the `raw::RawDigit` that originates it, i.e. starting from
   * @ref DetectorClocksTPCelectronicsStartTime "TPC electronics start time"
   * (use `detinfo::DetectorClocks` to discover the exact extent of each tick).
   * 
   * The content is organized as time intervals where some signal is present
   * ("regions of interest", RoI), outside which we assume no signal.
   * By principle, the definition of the regions of interest is a negative one:
   * we determine time intervals where we are confident no signal is present;
   * the rest will constitute regions of interest where there _might_ be signal.
   * The identification of such regions is responsibility of the algorithm
   * creating the `OpWaveform` object. In the simplest approach, the whole readout
   * window is stored in a single region of interest, meaning that we don't
   * claim any of the channel signal to be definitely signal free.
   * More generally, the first tick of the waveform is #0, and if the first
   * region of interest starts after that tick, it implies that the region
   * between tick #0 and the start of that first region lacks signal.
   * Likewise, any samples in the end of the covered time window (defined above)
   * which lack signal are indicated by the overall size of the content, while
   * the last region of interest ends earlier.
   *
   * Algorithms using the regions of interest can access the channel signal
   * information either ignoring the regions of interest, and being potentially
   * flooded by zeroes from the non-signal regions:
   * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
   * for (float ADCcount: wire.Signal()) ...
   * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
   * or they can analyze region by region:
   * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
   * for (auto iROI = wire.begin_range(); iROI != wire.end_range(); ++iROI) {
   *   const datarange_t& ROI = *iROI;
   *   const int FirstTick = ROI.begin_index();
   *   const int EndTick = ROI.end_index();
   *   const float FirstADC = ROI[FirstTick]; // index access is by absolute tick number
   *   for (float ADC: ROI) // ... or you can just iterate through
   *   // ...
   * } // for
   * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
   * An alternative to the first form is:
   * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
   * for (float ADCcount: wire.SignalROI()) ...
   * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
   * which does not create a temporary dense vector, as `Signal()` does instead.
   *
   * Note that the indexed access is always by absolute tick number.
   * More examples of the use of `SignalROI()` return value are documented in
   * `lar::sparse_vector`.
   *
   * Each channel is associated with a `raw::RawDigit` object. These
   * associations should be stored together with `recob::OpWaveform` by the producer
   * in a `art::Assns` data product.
   * 
   * 
   * Creating `recob::OpWaveform` objects
   * ===============================
   * 
   * LArSoft "protocol" prescribes:
   * 
   * * creation of an association of each `recob::OpWaveform` with the `raw::RawDigit`
   *   it comes from; the association should be created by the same _art_ module
   *   producing the `recob::OpWaveform` collection
   * * `recob::OpWaveform` time span should be the same as its `raw::RawDigit`
   * 
   * Two patterns can be followed for creating a `recob::OpWaveform`:
   * 
   * 1. direct construction: see the constructor documentation
   * 2. with `recob::OpWaveformCreator`, which extracts some relevant information from
   *    the source `raw::RawDigit` but _does not help with their association_
   * 
   * In both cases, please read the documentation of `recob::OpWaveform` constructors.
   */

  class OpWaveform {
    public:
      /// a region of interest is a pair (TDC offset, readings)
      typedef lar::sparse_vector<float> RegionsOfInterest_t;

      /// Default constructor: a wire with no signal information
      OpWaveform();

    private:
      raw::RDTimeStamp    fTimeStamp; ///< Time stamp
      raw::ChannelID_t    fChannel;   ///< ID of the associated channel.
      RegionsOfInterest_t fSignalROI; ///< Signal on the channel as function of time tick.

      //friend class OpWaveformCreator; // helper to create wires in art

    public:
      
      // --- BEGIN -- Constructors ---------------------------------------------
      /**
       * @brief Constructor: uses specified signal in regions of interest.
       * @param sigROIlist signal organized in regions of interest
       * @param channel the ID of the channel
       * @param view the view the channel belongs to
       *
       * Signal is copied into the `recob::OpWaveform` object, including the sparse
       * region of interest structure within `sigROIlist`.
       * If possible, use the other constructor that moves the data instead.
       * 
       * For more details, see the other constructor documentation.
       */
      OpWaveform(
        raw::RDTimeStamp time,
        raw::ChannelID_t channel,
        RegionsOfInterest_t const& sigROIlist
        );

      /**
       * @brief Constructor: uses specified signal in regions of interest.
       * @param sigROIlist signal organized in regions of interest
       * @param channel the ID of the channel
       * @param view the view the channel belongs to
       *
       * The `recob::OpWaveform` object is constructed with the waveform information
       * in `sigROIlist` and assigned the specified `channel` and `view`.
       * 
       * The signal is stored in a sparse vector, each entry corresponding to a
       * tick in the calibrated waveform. The tick range of the sparse vector
       * reflects the one in the wire, i.e. the first sample in `sigROIlist`
       * becomes the sample #0 of the `recob::OpWaveform` waveform.
       * The total length of the waveform (that is, its duration in ticks) is
       * also learned from the (nominal) size of `sigROIlist` (see also
       * `lar::sparse_vector::resize()`), which can and should extend beyond
       * the last region of interest.
       * 
       * This constructor moves the signal information is moved `sigROIlist`,
       * that becomes invalid.
       * This also preserves the sparse region of interest structure within
       * `sigROIlist`.
       */
      OpWaveform(
        raw::RDTimeStamp time,
        raw::ChannelID_t channel,
        RegionsOfInterest_t&& sigROIlist
        );
      // --- END -- Constructors -----------------------------------------------


      // --- BEGIN -- Accessors ------------------------------------------------
      ///@name Accessors
      ///@{

      /// Return a zero-padded full length vector filled with RoI signal
      std::vector<float>  Signal() const;

      /// Returns the list of regions of interest
      const RegionsOfInterest_t& SignalROI()  const;

      /// Returns the number of time ticks, or samples, in the channel
      std::size_t                NSignal()    const;

      /// Returns the ID of the channel (or InvalidChannelID)
      raw::ChannelID_t           Channel()    const;

      /// Returns the time stamp
      raw::RDTimeStamp           TimeStamp()  const;
      
      ///@}
      // --- END -- Accessors --------------------------------------------------

      
      // --- BEGIN -- Sorting and comparison operations ------------------------
      /// @name Sorting and comparison operations
      /// @{
      
      /// Returns whether this channel ID is smaller than the other
      bool operator< (const OpWaveform& than) const;
      
      // --- END -- Sorting and comparison operations --------------------------


  }; // class OpWaveform

} // namespace recob


//------------------------------------------------------------------------------
//--- inline implementation
//------------------------------------------------------------------------------
inline const recob::OpWaveform::RegionsOfInterest_t&
                                  recob::OpWaveform::SignalROI()  const { return fSignalROI;        }
inline std::size_t                recob::OpWaveform::NSignal()    const { return fSignalROI.size(); }
inline raw::ChannelID_t           recob::OpWaveform::Channel()    const { return fChannel;          }
inline raw::RDTimeStamp           recob::OpWaveform::TimeStamp()  const { return fTimeStamp;          }
inline bool                       recob::OpWaveform::operator< (const OpWaveform& than) const
  { return Channel() < than.Channel(); }

//------------------------------------------------------------------------------


#endif // LARDATAOBJ_RECOBASE_OPWAVEFORM_H

////////////////////////////////////////////////////////////////////////
