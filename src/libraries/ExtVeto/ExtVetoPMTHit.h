// $Id$
//
//    File: ExtVetoDigiHit.h
// Created: Wed Jan 13 21:06:40 CET 2016
// Creator: celentan (on Linux localhost.localdomain 2.6.32-504.30.3.el6.x86_64 x86_64)
//

#ifndef _ExtVetoPMTHit_
#define _ExtVetoPMTHit_

#include <JANA/JObject.h>
#include <JANA/JFactory.h>
#include <TT/TranslationTable.h>

#include <DAQ/fa250ConvertedHit.h>
class ExtVetoPMTHit:public fa250ConvertedHit{
public:
	JOBJECT_PUBLIC(ExtVetoPMTHit);

	// Add data members here. For example:
	// int id;
	// double E;

	// This method is used primarily for pretty printing
	// the second argument to AddString is printf style format
	void toStrings(vector<pair<string,string> > &items)const{
		// AddString(items, "id", "%4d", id);
		// AddString(items, "E", "%f", E);
	}

	TranslationTable::ChannelInfo m_channel; //both crate-slot channel and detector-specific ID. Since this is a sensor-based object, the readout field will be !=0
	oid_t fa250Hit_id; //jana id for the fadc corresponding hit

	double Q,T;
};

#endif //

