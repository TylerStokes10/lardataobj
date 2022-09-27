# Purpose of this directory

This directory was added when the `sim::IDE` class version changed from 11 to 12.  Due to an error in ROOT (discovered in version 6.22/08, and fixed in version 6.XY/UV), the streamer information for `sim::IDE` was not stored in any art/ROOT file that contained a nested collection of `sim::IDE` objects.  ROOT is therefore not able to ensure backwards-compatibility for the `sim::IDE` class, even though an IO read rule exists.

To work around this limitation, the 'simIDE_streamer_info.root' file in this directory was generated with the necessary `sim::IDE` streamer information.  Backwards compatibility is restored by loading this file whenever the `lardataobj::Simulation` dictionary library is loaded.

**N.B.** ROOT files are not generally permitted in LArSoft repositories.  An exception has been made for this case so that backwards compatibility could be restored.
