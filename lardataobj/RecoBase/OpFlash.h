////////////////////////////////////////////////////////////////////////////
//
// \brief Definition of OpFlash object for LArSoft
//
// \author bjpjones@mit.edu
//         cschiu@mit.edu
//
////////////////////////////////////////////////////////////////////////////
#ifndef OPFLASH_H
#define OPFLASH_H

#include <vector>
#include <limits> // std::numeric_limits<>


namespace recob {

  // subevents are groupings of OpDet pulse peaks. Each peak comes from an OpDet and
  // has a certain number of PE; each subevent has a time associated with it
  class OpFlash {
    public:
      
      /// Special value used for absence of center location information.
      static constexpr double NoCenter = std::numeric_limits<double>::max();
      
      OpFlash() = default;

private:

      double                fTime { 0.0 }; ///< Time on @ref DetectorClocksHardwareTrigger "trigger time scale" [us]
      double                fTimeWidth;    ///< Width of the flash in time [us]
      double                fAbsTime;      ///< Time by PMT readout clock
      unsigned int          fFrame;        ///< Frame number
      std::vector< double > fPEperOpDet;   ///< Number of PE on each PMT
      std::vector< double > fWireCenters;  ///< Geometric center in each view
      std::vector< double > fWireWidths;   ///< Geometric width in each view
      double                fXCenter { NoCenter }; ///< Estimated center in x [cm]
      double                fXWidth { NoCenter }; ///< Estimated width in x [cm]
      double                fYCenter;      ///< Geometric center in y [cm]
      double                fYWidth;       ///< Geometric width in y [cm]
      double                fZCenter;      ///< Geometric center in z [cm]
      double                fZWidth;       ///< Geometric width in z [cm]
      double                fFastToTotal;  ///< Fast to total light ratio
      bool                  fInBeamFrame;  ///< Is this in the beam frame?
      int                   fOnBeamTime;   ///< Is this in time with beam?




  public:
      /// Constructor: all data members directly initialized.
      OpFlash(double time, double timewidth, double abstime, unsigned int frame,
	      std::vector< double > PEperOpDet,
	      bool InBeamFrame, int OnBeamTime, double FastToTotal,
	      double xCenter, double xWidth,
	      double yCenter, double yWidth,
	      double zCenter, double zWidth,
	      std::vector<double> WireCenters = std::vector<double>(0),
	      std::vector<double> WireWidths  = std::vector<double>(0));

      /// Constructor: all data members directly initialized except x coordinate.
      OpFlash(double time, double timewidth, double abstime, unsigned int frame,
	      std::vector< double > PEperOpDet,
	      bool InBeamFrame=0, int OnBeamTime=0, double FastToTotal=1,
	      double yCenter=0, double yWidth=0,
	      double zCenter=0, double zWidth=0,
	      std::vector<double> WireCenters = std::vector<double>(0),
	      std::vector<double> WireWidths  = std::vector<double>(0));

      // Get Methods
      double                Time()              const;
      double                TimeWidth()         const;
      double                AbsTime()           const;
      unsigned int          Frame()             const;
      double                PE(unsigned int i)  const;

      /// Returns a vector with a number of photoelectrons per channel.
      std::vector<double> const& PEs()          const;

      /// Returns whether the estimated center on _x_ direction is available.
      bool hasXCenter() const;
      
      /// Returns the estimated center on _x_ direction (@see `hasXCenter()`).
      double                XCenter()           const;
      double                XWidth()            const;
      double                YCenter()           const;
      double                YWidth()            const;
      double                ZCenter()           const;
      double                ZWidth()            const;

      bool                  InBeamFrame()       const;
      int                   OnBeamTime()        const;

      std::vector<double> const& WireCenters()  const;
      std::vector<double> const& WireWidths()   const;

      double                TotalPE()           const;
      double                FastToTotal()       const;


  };

}


inline double recob::OpFlash::Time()              const { return fTime;        }
inline double recob::OpFlash::TimeWidth()         const { return fTimeWidth;   }
inline double recob::OpFlash::AbsTime()           const { return fAbsTime;     }
inline unsigned int recob::OpFlash::Frame()       const { return fFrame;       }
inline double recob::OpFlash::PE(unsigned int i)  const { return fPEperOpDet[i]; }
inline std::vector<double> const& recob::OpFlash::PEs() const { return fPEperOpDet; }
inline bool recob::OpFlash::hasXCenter()          const { return fXCenter != NoCenter; }
inline double recob::OpFlash::XCenter()           const { return fXCenter;     }
inline double recob::OpFlash::XWidth()            const { return fXWidth;      }
inline double recob::OpFlash::YCenter()           const { return fYCenter;     }
inline double recob::OpFlash::YWidth()            const { return fYWidth;      }
inline double recob::OpFlash::ZCenter()           const { return fZCenter;     }
inline double recob::OpFlash::ZWidth()            const { return fZWidth;      }
inline double recob::OpFlash::FastToTotal()            const { return fFastToTotal;      }
inline std::vector<double> const& recob::OpFlash::WireCenters() const { return fWireCenters;      }
inline std::vector<double> const& recob::OpFlash::WireWidths() const { return fWireWidths;      }
inline bool  recob::OpFlash::InBeamFrame()          const { return fInBeamFrame;     }
inline int  recob::OpFlash::OnBeamTime()          const { return fOnBeamTime;     }

namespace recob{
  struct OpFlashSortByTime {
    bool operator() (recob::OpFlash const& i, recob::OpFlash const& j) const
      { return i.Time() < j.Time(); }
  };
}


#endif
