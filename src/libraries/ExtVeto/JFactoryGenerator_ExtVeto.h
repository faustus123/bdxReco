// $Id$
//
//    File: JFactoryGenerator_ExtVeto.h
// Created: Wed Jan 13 21:06:57 CET 2016
// Creator: celentan (on Linux localhost.localdomain 2.6.32-504.30.3.el6.x86_64 x86_64)
//

#ifndef _JFactoryGenerator_ExtVeto_
#define _JFactoryGenerator_ExtVeto_

#include <JANA/jerror.h>
#include <JANA/JFactoryGenerator.h>

#include "ExtVetoPMTHit_factory.h"
#include "ExtVetoDigiHit_factory.h"
#include "ExtVetoHit_factory.h"
#include "ExtVetofa250Converter_factory.h"

class JFactoryGenerator_ExtVeto: public jana::JFactoryGenerator{
	public:
		JFactoryGenerator_ExtVeto(){}
		virtual ~JFactoryGenerator_ExtVeto(){}
		virtual const char* className(void){return static_className();}
		static const char* static_className(void){return "JFactoryGenerator_ExtVeto";}
		
		jerror_t GenerateFactories(jana::JEventLoop *loop){
			loop->AddFactory(new ExtVetoPMTHit_factory());
			loop->AddFactory(new ExtVetofa250Converter_factory());
			loop->AddFactory(new ExtVetoDigiHit_factory());
			loop->AddFactory(new ExtVetoHit_factory());

			return NOERROR;
		}

};

#endif // _JFactoryGenerator_ExtVeto_

