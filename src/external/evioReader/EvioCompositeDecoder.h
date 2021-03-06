/**
* Autogenerated Header File for EvioCompositeDecoder
* \\file EvioCompositeDecoder.h
* \\author G.Gavalian
* \\date 2014-09-19
*/
#ifndef __EVIOCOMPOSITEDECODER__
#define __EVIOCOMPOSITEDECODER__
#include <iostream>
#include <string>
#include <cmath>
#include <vector>
#include <string>
#include <cstring>
//#include "common_std.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

//! A Brief Description
/*
 * A detailed description
 */


typedef struct {
  int slot;
  int time;
  int trigger;
  int channel;
  vector<short> samples;
} CompositeADCRaw_t;

typedef struct {
  int tdc;
  int adc;
  int ped;
  int max;
} Pulse_t;

typedef struct {
  int slot;
  int time;
  int trigger;
  int channel;
  vector<Pulse_t> pulses;
} CompositeADCPulse_t;


class EvioCompositeDecoder  {

private:
  vector<CompositeADCRaw_t>  adcSamples;
  vector<CompositeADCPulse_t>  adcSamplesPulse;
public:

/** Default Constructor */
EvioCompositeDecoder();
/** Default Destructor */
~EvioCompositeDecoder();
/** Copy Constructor if one is needed */
/*EvioCompositeDecoder( const EvioCompositeDecoder &obj); */ 

/** An operator = if one is needed */
/* const EvioCompositeDecoder &operator=(const EvioCompositeDecoder &obj); */
 uint8_t          getInt8 (char *data, int offset);
 uint16_t         getInt16(char *data, int offset);
 uint32_t         getInt32(char *data, int offset);
 int64_t          getInt64(char *data, int offset);

 vector<CompositeADCRaw_t>  getData(){ return adcSamples;};
 vector<CompositeADCPulse_t>  getDataPulse(){ return adcSamplesPulse;};

 void    decode(vector<uint32_t> *vec, int size);
 void    decodePulse(vector<uint32_t> *vec, int size);

 void    createStructures();
 string  formatString(const void *data, int *len);
 

};
#endif
