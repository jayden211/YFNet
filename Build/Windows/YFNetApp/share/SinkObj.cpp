// SinkObj.cpp : Implementation of CTVInsterApp and DLL registration.

//#include "stdafx.h"
//#include "TVInster.h"
#include "SinkObj.h"

/////////////////////////////////////////////////////////////////////////////
//
const IID DIID_IMEDIAPLAYEvents = {0x6BF52A51,0x394A,0x11D3,{0xB1,0x53,0x00,0xC0,0x4F,0x79,0xFA,0xA6}};
//                                       ---B153-00C04F79FAA6  6BF52A51-394A-11D3-B153-00C04F79FAA6
const IID LIBID_MEDIAPLAYLib = {0x6BF52A50,0x394A,0x11D3,{0xB1,0x53,0x00,0xC0,0x4F,0x79,0xFA,0xA6}};
										//
										//CFCDAA02-8BE4-11CF-B84B-0020AFBBCCFA
const IID DIID_IREALPLAYEvents = {0xCFCDAA02,0x8BE4,0x11CF,{0xB8,0x4B,0x00,0x20,0xAF,0xBB,0xCC,0xFA}};

									//CFCDAA00-8BE4-11CF-B84B-0020AFBBCCFA
const IID LIBID_REALPLAYLib = {0xCFCDAA00,0x8BE4,0x11CF,{0xB8,0x4B,0x00,0x20,0xAF,0xBB,0xCC,0xFA}};



//706BC692-B613-4B6E-97E7-2C2104C1D06E

//const IID DIID_IQUICKEvents = {0x706BC692, 0xB613, 0x4B6E, {0x97, 0xE7, 0x2C, 0x21, 0x04, 0xC1, 0xD0, 0x6E}};
//614E1495-1014-44F8-B350-5344C0770C1E
const IID DIID_IQUICKEvents = {0x614E1495, 0x1014, 0x44F8, {0xB3, 0x50, 0x53, 0x44, 0xC0, 0x77, 0x0C, 0x1E}};
//29866AED-1E14-417D-BA0F-1A2BE6F5A19E
//const IID DIID_IQUICKLib = {0x29866AED, 0x1E14, 0x417D, {0xBA, 0x0F, 0x1A, 0x2B, 0xE6, 0xF5, 0xA1, 0x9E}};
//7B92F833-027D-402B-BFF9-A67697366F4E
const IID DIID_IQUICKLib = {0x7B92F833, 0x027D, 0x402, {0xBF, 0xF9, 0xA6, 0x76, 0x97, 0x36, 0x6F, 0x4E}};