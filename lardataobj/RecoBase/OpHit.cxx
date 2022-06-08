////////////////////////////////////////////////////////////////////////
//
// \brief Definition of OpHit reconstruction object
//
// \author bjpjones@mit.edu
//         cschiu@mit.edu
//
////////////////////////////////////////////////////////////////////////

#include "lardataobj/RecoBase/OpHit.h"

namespace recob{

  //----------------------------------------------------------------------
  OpHit::OpHit()
    : fOpChannel     (-1)
    , fFrame         (0 )
    , fPeakTime      (0 )
    , fPeakTimeAbs   (0 )
    , fStartTime     (DefaultTime)
    , fRiseTime      (DefaultTime)
    , fWidth         (0 )
    , fArea          (0 )
    , fAmplitude     (0.)
    , fPE            (0.)
    , fFastToTotal   (0.)
  {

  }

  //----------------------------------------------------------------------
  OpHit::OpHit(int opchannel,
	       double peaktime,
	       double peaktimeabs,
	       double starttime,
	       double risetime,
	       unsigned short frame,
	       double width,
	       double area,
	       double amplitude,
	       double pe,
	       double fasttototal)
    : fOpChannel     (opchannel     )
    , fFrame         (frame         )
    , fPeakTime      (peaktime      )
    , fPeakTimeAbs   (peaktimeabs   )
    , fStartTime     (starttime     )
    , fRiseTime      (risetime      )
    , fWidth         (width         )
    , fArea          (area          )
    , fAmplitude     (amplitude     )
    , fPE            (pe            )
    , fFastToTotal   (fasttototal   )
  {

  }

  //----------------------------------------------------------------------
  OpHit::OpHit(int opchannel,
         double peaktime,
         double peaktimeabs,
         unsigned short frame,
         double width,
         double area,
         double amplitude,
         double pe,
         double fasttototal)
    : OpHit{
        opchannel, peaktime, peaktimeabs,
        DefaultTime, DefaultTime, frame,
        width, area, amplitude, pe, fasttototal
      }
    {}

  //----------------------------------------------------------------------
  bool operator < (const OpHit & a, const OpHit & b)
  {
    return a.PE() < b.PE();
  }

}
