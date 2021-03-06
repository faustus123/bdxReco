// $Id$
//
//    File: TranslationTable.h
// Created: Tue Jan 12 09:29:14 CET 2016
// Creator: celentan (on Linux apcx4 2.6.32-504.30.3.el6.x86_64 x86_64)
//

#ifndef _TranslationTable_
#define _TranslationTable_


#include <JANA/JObject.h>
#include <JANA/JFactory.h>
#include <JANA/JEventLoop.h>
#include <JANA/JCalibration.h>
#include <JANA/JException.h>
#include <JANA/JEventSource.h>

using namespace jana;

class TranslationTable:public jana::JObject{

public:
	JOBJECT_PUBLIC(TranslationTable);

	TranslationTable(JEventLoop *loop);
	~TranslationTable();

	// Each detector system has its own native indexing scheme.
	// Here, we define a class for each of them that has those
	// indexes. These are then used below in the DChannelInfo
	// class to relate them to the DAQ indexing scheme of
	// crate, slot, channel.
	struct csc_t{
		uint32_t rocid;
		uint32_t slot;
		uint32_t channel;

		inline bool operator==(const struct csc_t &rhs) const {
			return (rocid==rhs.rocid) && (slot==rhs.slot) && (channel==rhs.channel);
		}
	};

	enum Detector_t{
		UNKNOWN_DETECTOR,
		EXT_VETO,
		INT_VETO,
		CALO,
		OTHER,
		NUM_DETECTOR_TYPES
	};

	string DetectorName(Detector_t type) const {
		switch(type){
		case EXT_VETO: return "ExtVeto";
		case INT_VETO: return "IntVeto";
		case CALO: return "CALO";
		case OTHER: return "OTHER";
		case UNKNOWN_DETECTOR:
		default:
			return "UNKNOWN";
		}
	}


	/*Here follows the classes to handle the IDs and intrinsic indexes of the different detectors
	 *
	 * There are some conventions on few indexes:
	 *
	 * - sector is an index regarding different, identical, detectors (in BDX we think about independent, but equal, detectors)
	 * - readout is an index to handle the case of different sensors reading out the same active volume
	 *
	 * Since we use these indexes both for the readout sensor and for the active volume, the convention is to use
	 * readout = 0 when dealing with the PHYSICAL volume
	 * readout = 1 ... Nreadouts when dealing with the sensors
	 * */
	class EXT_VETO_Index_t{
	public:
		int sector;
		int layer;
		int component;
		int readout;
		inline bool isSameActive(const EXT_VETO_Index_t &rhs) const {
			return (sector==rhs.sector) && (layer==rhs.layer) && (component==rhs.component);
		}
		inline bool operator==(const EXT_VETO_Index_t &rhs) const {
			return isSameActive(rhs) && (readout==rhs.readout);
		}
		inline bool operator<(const EXT_VETO_Index_t &rhs) const {  //A.C. for the maps
			if (sector>rhs.sector) return true;
			if (sector<rhs.sector) return false;
			if (layer>rhs.layer)   return true;
			if (layer<rhs.layer)   return false;
			if (component>rhs.component) return true;
			if (component<rhs.component) return false;
			if (readout>rhs.readout) return true;
			if (readout<rhs.readout) return false;
			return false;
		}
	};

	class INT_VETO_Index_t{
	public:
		int sector;
		int layer;
		int component;
		int readout;
		static const int nIDs(){return 4;};
		inline bool isSameActive(const INT_VETO_Index_t &rhs) const{
			return (sector==rhs.sector) && (layer==rhs.layer) && (component==rhs.component);
		}
		inline bool operator==(const INT_VETO_Index_t &rhs) const {
			return isSameActive(rhs) && (readout==rhs.readout);
		}
		inline bool operator<(const INT_VETO_Index_t &rhs) const {  //A.C. for the maps
			if (sector>rhs.sector) return true;
			if (sector<rhs.sector) return false;
			if (layer>rhs.layer)   return true;
			if (layer<rhs.layer)   return false;
			if (component>rhs.component) return true;
			if (component<rhs.component) return false;
			if (readout>rhs.readout) return true;
			if (readout<rhs.readout) return false;
			return false;
		}
	};

	class CALO_Index_t{
	public:
		int sector;
		int x,y;
		int readout;
		inline bool isSameActive(const CALO_Index_t &rhs) const{
			return (sector==rhs.sector) && (x==rhs.x) && (y==rhs.y);
		}
		inline bool operator==(const CALO_Index_t &rhs) const {
			return isSameActive(rhs) && (readout == rhs.readout);
		}
		inline bool operator<(const CALO_Index_t &rhs) const {  //A.C. for the maps
			if (sector>rhs.sector) return true;
			if (sector<rhs.sector) return false;
			if (x>rhs.x)   return true;
			if (x<rhs.x)   return false;
			if (y>rhs.y) return true;
			if (y<rhs.y) return false;
			if (readout>rhs.readout) return true;
			if (readout<rhs.readout) return false;
			return false;
		}
	};

	class OTHER_Index_t{
	public:
		int sector;
		int id;
		int readout;
		inline bool isSameActive(const OTHER_Index_t &rhs) const{
			return  (sector==rhs.sector) && (id==rhs.id);
		}
		inline bool operator==(const OTHER_Index_t &rhs) const {
			return  isSameActive(rhs)&&(readout==rhs.readout);
		}


	};

	/*A single class that handles ALL the possible indexes trough a C++ union*/
	class ChannelInfo{
	public:
		csc_t CSC;   //This is crate - slot - channel
		//DModuleType::type_id_t module_type;
		Detector_t det_sys;
		union{
			EXT_VETO_Index_t ext_veto;
			INT_VETO_Index_t int_veto;
			CALO_Index_t calo;
			OTHER_Index_t other;
		};
	};


	// This method is used primarily for pretty printing
	// the second argument to AddString is printf style format
	void toStrings(vector<pair<string,string> > &items)const{
		// AddString(items, "id", "%4d", id);
		// AddString(items, "E", "%f", E);
	}

	void ReadTranslationTable(JCalibration *jcalib=NULL);


	/*Here goes the methods to return the channel info (detector name / detector-specific id) given the csc*/
	TranslationTable::ChannelInfo getChannelInfo(const csc_t &csc) const;
	TranslationTable::ChannelInfo getChannelInfo(int crate,int slot,int channel) const;
protected:
	string XML_FILENAME;
	bool NO_CCDB;
	set<string> supplied_data_types;
	int VERBOSE;
	string SYSTEMS_TO_PARSE;
	string ROCID_MAP_FILENAME;

	mutable JStreamLog ttout;





private:

	/****************************************** STATIC-VARIABLE-ACCESSING PRIVATE MEMBER FUNCTIONS ******************************************/

	//Some variables needs to be shared amongst threads (e.g. the memory used for the branch variables)
	//However, you cannot make them global/extern/static/static-member variables in the header file:
	//The header file is included in the TTAB library AND in each plugin that uses it
	//When a header file is included in a src file, it's contents are essentially copied directly into it
	//Thus there are two instances of each static variable: one in each translation unit (library)
	//Supposedly(?) they are linked together during runtime when loading, so there is (supposedly) no undefined behavior.
	//However, this causes a double free (double-deletion) when these libraries are closed at the end of the program, crashing it.
	//Thus the variables must be in a single source file that is compiled into a single library
	//However, you (somehow?) cannot make them global/extern variables in the cpp function
	//This also (somehow?) causes the double-free problem above for (at least) stl containers
	//It works for pointers-to-stl-containers and fundamental types, but I dunno why.
	//It's not good encapsulation anyway though.
	//THE SOLUTION:
	//Define the variables as static, in the source file, WITHIN A PRIVATE MEMBER FUNCTION.
	//Thus the static variables themselves only have function scope.
	//Access is only available via the private member functions, thus access is fully controlled.
	//They are shared amongst threads, so locks are necessary, but since they are private this class can handle it internally

	pthread_mutex_t& Get_TT_Mutex(void) const;
	bool& Get_TT_Initialized(void) const;
	map<TranslationTable::csc_t, TranslationTable::ChannelInfo>& Get_TT(void) const;


};

#endif // _TranslationTable_

