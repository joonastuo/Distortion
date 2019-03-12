/*
  ==============================================================================

    Identifiers.h
    Created: 12 Mar 2019 10:34:42am
    Author:  Joonas

  ==============================================================================
*/

#pragma once

namespace IDs {

	#define DECLARE_ID(name) const String name (#name);

	DECLARE_ID(inputVolume)			// Input volume of the effects chain
	DECLARE_ID(HPFreq)				// Frequency of the highpass filter before the waveshaper
	DECLARE_ID(LPFreq)				// Frequency of the lowpass filter after the waveshaper	
	DECLARE_ID(outputVolume)		// Output volume of the effects chain
	DECLARE_ID(wetDry)				// Wet / dry control of the plugin

	#undef DECLARE_ID

}