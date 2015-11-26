### AudioReflectorDriver ###

===========================================================================
DESCRIPTION:

This project builds a kernel-based audio driver that:
- builds for both Intel and PowerPC
- reflects data going out one channel back to the corresponding input channel
- has a completely configurable list of supported formats and stream layouts via it's Info.plist
- provides a dummy control for just about every standard kind control supported by the IOAudio family
- demonstrates how to localize strings
- includes a configurable time stamp generator to allow the simulation of various timing situations
- includes an integer-to-floating-point and floating-point-to-integer blitting library optimized for SSE3 on Intel processors and Altivec on PowerPC processors

===========================================================================
BUILD REQUIREMENTS:

Mac OS X v10.6 or later

===========================================================================
RUNTIME REQUIREMENTS:

Mac OS X v10.6 or later

===========================================================================
PACKAGING LIST:

ARClip.cpp
- Utility class for clipping samples
ARDebug.h- Utility class for displaying debug messages

ARDevice.cppARDevice.h
- ARDevice class

AREngine.cppAREngine.h
- AREngine class

ARStereoPanControl.cppARStereoPanControl.h
- ARStereoPanControl class

ARTimeStampGenerator.cppARTimeStampGenerator.h
- ARTimeStampGenerator class

FPU.h
- Utility class for denormalization

PCMBlitterLib.hPCMBlitterLib.cpp
- Utility code for Float -> Int blitting library

===========================================================================
CHANGES FROM PREVIOUS VERSIONS:

Version 1.0
- First version.

===========================================================================
Copyright (C) 2009 Apple Inc. All rights reserved.
