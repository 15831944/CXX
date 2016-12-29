//		 
// Copyright (c) 1994-1998 by
// SeaChange Technology Inc., West Concord, Mass.
// All Rights Reserved.  Unpublished rights  reserved  under  the  copyright
// laws of the United States.
// 
// The software contained  on  this media is proprietary to and embodies the
// confidential technology of SeaChange  Technology  Inc.   Possession, use,
// duplication or dissemination of the software and media is authorized only
// pursuant to a valid written license from SeaChange Technology Inc.
// 
// This software is furnished under a  license  and  may  be used and copied
// only in accordance with the terms of  such license and with the inclusion
// of the above copyright notice.  This software or any other copies thereof
// may not be provided or otherwise made available to  any other person.  No
// title to and ownership of the software is hereby transferred.
// 
// The information in this software is subject to change without  notice and
// should not be construed as a commitment by SeaChange Technology Inc.
// 
// SeaChange  assumes  no  responsibility  for the use or reliability of its
// software on equipment which is not supplied by SeaChange.
// 
// RESTRICTED RIGHTS  LEGEND  Use,  duplication,  or  disclosure by the U.S.
// Government is subject  to  restrictions  as  set  forth  in  Subparagraph
// (c)(1)(ii) of DFARS 252.227-7013, or in FAR 52.227-19, as applicable.
//
// title:       ItvMessages.MC
//
// version:     V0.0
//
// facility:    ITV
//
// abstract:    This is the message compiler source file for all ITV facility
//                         messages.
//
// Revision History:
// -----------------
//
//   Rev       Date           Who               Description
//  ------ ---------------- -------  -----------------------------------
//  V0.000   21-May-1998	   TMS	   Initial message file
//  V0.000   02-Nov-2000	   ADS	   SPR1954: added SCTP message for default language change
//  V0.000   02-Nov-2000	   ADS	   SPR1984: improved SCTP message for MaxConnections exceeded
//
//
//
//*******************************************************************************
//*
//*    Header Section
//*
//*  There will be no typedefs for ITV messages.  The severity names will be the
//*    the default ones: SeverityNames=(Success=0x0,Informational=0x1,Warning=0x2,
//*  Error=0x3). Language names will likewise default to:
//*    LanguageNames=(English=1:MSG00001)
//*
//*    The only thing defined in this section is the facility codes and names.
//*******************************************************************************
// DO NOT change Generic_Itv from 0x0000 without also changing DllExport.cpp
//*******************************************************************************
//*
//*     Generic Itv messages
//*
//*     Do not change the value of ITV_DLL_EXCEPTION unless you also change
//*     DllExport.cpp
//*******************************************************************************
//
//  Values are 32 bit values layed out as follows:
//
//   3 3 2 2 2 2 2 2 2 2 2 2 1 1 1 1 1 1 1 1 1 1
//   1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0
//  +---+-+-+-----------------------+-------------------------------+
//  |Sev|C|R|     Facility          |               Code            |
//  +---+-+-+-----------------------+-------------------------------+
//
//  where
//
//      Sev - is the severity code
//
//          00 - Success
//          01 - Informational
//          10 - Warning
//          11 - Error
//
//      C - is the Customer code flag
//
//      R - is a reserved bit
//
//      Facility - is the facility code
//
//      Code - is the facility's status code
//
//
// Define the facility codes
//
#define XML                              0x13
#define Vodometer                        0x10B
#define SRM                              0xE
#define SYSMON                           0xD
#define SYNAPI                           0x10A
#define ISSAPI                           0x8
#define SS                               0x5
#define SRMV2                            0x108
#define SCTP                             0x6
#define PS                               0x4
#define LA                               0xC
#define isaStream                        0x11
#define isaContent                       0x12
#define isaAs                            0x15
#define ITV                              0x0
#define ETF                              0x14
#define IDSAPI                           0x7
#define DS                               0x2
#define DCM                              0x9
#define CM                               0x1
#define ADIS                             0xF
#define AM                               0x3
#define IADAPI                           0xA
#define AD                               0xB


//
// Define the severity codes
//


//
// MessageId: ITV_DLL_EXCEPTION
//
// MessageText:
//
//  (%1)Exception in DLL.  Message is %2.
//
#define ITV_DLL_EXCEPTION                0xC0000000L

//*******************************************************************************
//*
//*     Connection Manager Messages 
//*
//*******************************************************************************
//
// MessageId: CMEVT_SYSERR
//
// MessageText:
//
//  (CM) Error - %1
//
#define CMEVT_SYSERR                     0xC0010001L

//
// MessageId: CMEVT_WARNING
//
// MessageText:
//
//  (CM) Warning - %1
//
#define CMEVT_WARNING                    0x80010002L

//
// MessageId: CMEVT_MAN_INIT
//
// MessageText:
//
//  (CM) Error - ManOpenSession failed: %1, extended status: %2
//
#define CMEVT_MAN_INIT                   0xC0010003L

//
// MessageId: CMEVT_CFG_INIT
//
// MessageText:
//
//  (CM) Error %1 initializing configuration package
//
#define CMEVT_CFG_INIT                   0xC0010004L

//
// MessageId: CMEVT_LOG_INIT
//
// MessageText:
//
//  (CM) Error %1 initializing circular logging package
//
#define CMEVT_LOG_INIT                   0xC0010005L

//
// MessageId: CMEVT_MALLOC
//
// MessageText:
//
//  (CM) Error - [%1/%2] Unable to allocate dynamic memory - %3
//
#define CMEVT_MALLOC                     0xC0010006L

//
// MessageId: CMEVT_MSME
//
// MessageText:
//
//  (CM) Error - State Machine Engine error: Routine %1, State %2, SMType %3, Status %4
//
#define CMEVT_MSME                       0xC0010007L

//
// MessageId: CMEVT_PS
//
// MessageText:
//
//  (CM) Error - [%1/%2] Propagation Service subsystem error, %3, extended status %4
//
#define CMEVT_PS                         0xC001000AL

//
// MessageId: CMEVT_DNP
//
// MessageText:
//
//  (CM) Information - [%1/%2] %3
//
#define CMEVT_DNP                        0x4001000EL

//
// MessageId: CMEVT_INITFAILED
//
// MessageText:
//
//  (CM) Error - [%1/%2] Failed to initialize CM subsystem %3, exiting..
//
#define CMEVT_INITFAILED                 0xC0010012L

//
// MessageId: CMEVT_SHUTDOWN
//
// MessageText:
//
//  (CM) Warning - [%1/%2] Shutdown request flag set, awaiting idle state
//
#define CMEVT_SHUTDOWN                   0x80010013L

//
// MessageId: CMEVT_TERMINATE
//
// MessageText:
//
//  (CM) Warning - [%1/%2] Shutdown/Idle, or CMTerminate() called, terminating..
//
#define CMEVT_TERMINATE                  0x80010014L

//
// MessageId: CMEVT_ABORT
//
// MessageText:
//
//  (CM) Error - [%1/%2] CMAbort() called, or unrecoverable condition, aborting..
//
#define CMEVT_ABORT                      0xC0010015L

//
// MessageId: CMEVT_START
//
// MessageText:
//
//  (CM) Information - CM Initializing.. %1
//
#define CMEVT_START                      0x40010016L

//
// MessageId: CMEVT_ENDING
//
// MessageText:
//
//  (CM) Information - [%1/%2] CM Terminating..
//
#define CMEVT_ENDING                     0x40010017L

//
// MessageId: CMEVT_SYSERR1
//
// MessageText:
//
//  (CM) Error -  %1 Error: %2
//
#define CMEVT_SYSERR1                    0xC0010018L

//
// MessageId: CMEVT_WARNING1
//
// MessageText:
//
//  (CM) Warning - %1 Error: %2
//
#define CMEVT_WARNING1                   0x80010019L

//
// MessageId: CMEVT_CFGINFO
//
// MessageText:
//
//  (CM) Information - CFGPKG using %1 for %2 value %3
//
#define CMEVT_CFGINFO                    0x4001001AL

//
// MessageId: CMEVT_MSME1
//
// MessageText:
//
//  (CM) Error - MSME %1 error: %2
//
#define CMEVT_MSME1                      0xC001001BL

//
// MessageId: CMEVT_INFO1
//
// MessageText:
//
//  (CM) Information - %1 Status: %2
//
#define CMEVT_INFO1                      0x4001001CL

//
// MessageId: CMEVT_INFO2
//
// MessageText:
//
//  (CM) Information - %1 Status: %2 Extended: %3
//
#define CMEVT_INFO2                      0x4001001DL

//
// MessageId: CMEVT_INFO
//
// MessageText:
//
//  (CM) Information - %1
//
#define CMEVT_INFO                       0x4001001EL

//
// MessageId: CMEVT_SYSERR2
//
// MessageText:
//
//  (CM) Error - %1 Error: %2, extended Error: %3
//
#define CMEVT_SYSERR2                    0xC001001FL

//
// MessageId: CMEVT_CONLOST
//
// MessageText:
//
//  (CM) Warning - [%1/%2] Connection to Delivery Network SRM lost: %3
//
#define CMEVT_CONLOST                    0x80010021L

//
// MessageId: CMEVT_DNINITERR
//
// MessageText:
//
//  (CM) Error - [%1/%2] Unrecoverable failure while initializing the delivery network interface: %3
//
#define CMEVT_DNINITERR                  0xC0010022L

//
// MessageId: CMEVT_IDSLOST
//
// MessageText:
//
//  (CM) Warning - [%1/%2] Connection (Binding) to IDS lost
//
#define CMEVT_IDSLOST                    0x80010024L

//
// MessageId: CMEVT_IDSOK
//
// MessageText:
//
//  (CM) Information - [%1/%2] Connection (Binding) to IDS established
//
#define CMEVT_IDSOK                      0x40010025L

//
// MessageId: CMEVT_IDSINIT
//
// MessageText:
//
//  (CM) Error - [%1/%2] Unable to Initialize/Bind to IDS interface - %3
//
#define CMEVT_IDSINIT                    0xC0010026L

//
// MessageId: CMEVT_INITDONE
//
// MessageText:
//
//  (CM) Information - [%1/%2] ************ Initialization Complete ****************
//
#define CMEVT_INITDONE                   0x40010027L

//
// MessageId: CMEVT_PSFAILED
//
// MessageText:
//
//  (CM) Warning - [%1/%2] Failed to initialize PSREP interface: Status=%3 - retrying..
//
#define CMEVT_PSFAILED                   0x80010028L

//
// MessageId: CMEVT_PSSTALE
//
// MessageText:
//
//  (CM) Warning - [%1/%2] PSREP Initialization suceeded, but information is stale
//
#define CMEVT_PSSTALE                    0x80010029L

//
// MessageId: CMEVT_PSOK
//
// MessageText:
//
//  (CM) Information - [%1/%2] PSREP Initialization suceeded
//
#define CMEVT_PSOK                       0x4001002AL

//
// MessageId: CMEVT_REQDBNOTOK
//
// MessageText:
//
//  (CM) Warning - [%1/%2] REQUEST LOG Database unavaliable for write
//
#define CMEVT_REQDBNOTOK                 0x8001002BL

//
// MessageId: CMEVT_STATDBNOTOK
//
// MessageText:
//
//  (CM) Warning - [%1/%2] STATS LOG Database unavaliable for write
//
#define CMEVT_STATDBNOTOK                0x8001002CL

//
// MessageId: CMEVT_REQDBOK
//
// MessageText:
//
//  (CM) Information - [%1/%2] REQUEST LOG Database bind successful
//
#define CMEVT_REQDBOK                    0x4001002DL

//
// MessageId: CMEVT_REQNAGGED
//
// MessageText:
//
//  (CM) Information - [%1/%2] Rejected repeated reqeust from clientID=%3
//
#define CMEVT_REQNAGGED                  0x4001002EL

//
// MessageId: CMEVT_LOGDBWRONGVERSION
//
// MessageText:
//
//  (CM) Error - [%1/%2] Incorrect, unsupported LOG DATABASE SCHEMA - %3
//
#define CMEVT_LOGDBWRONGVERSION          0xC001002FL

//
// MessageId: CMEVT_SYNCHOK
//
// MessageText:
//
//  (CM) Information - [%1/%2] Synchronized with PeerGroup
//
#define CMEVT_SYNCHOK                    0x40010030L

//
// MessageId: CMEVT_SYNCHNOTOK
//
// MessageText:
//
//  (CM) Warning - [%1/%2] Not synchronized with PeerGroup
//
#define CMEVT_SYNCHNOTOK                 0x80010031L

//
// MessageId: CMEVT_DNP0
//
// MessageText:
//
//  (CM) Warning - [%1/%2] SQL DNP Version is newer - %3
//
#define CMEVT_DNP0                       0x80010032L

//
// MessageId: CMEVT_DNP1
//
// MessageText:
//
//  (CM) Warning - [%1/%2] SQL DNP failure - %3
//
#define CMEVT_DNP1                       0x80010033L

//
// MessageId: CMEVT_DNP2
//
// MessageText:
//
//  (CM) Warning - [%1/%2] DNP SafeStore failure - %3
//
#define CMEVT_DNP2                       0x80010034L

//
// MessageId: CMEVT_DNP3
//
// MessageText:
//
//  (CM) Error - [%1/%2] Failed to initialize DNP configuration tables
//
#define CMEVT_DNP3                       0xC0010036L

//
// MessageId: CMEVT_MCA0
//
// MessageText:
//
//  (CM) Information - [%1/%2] Cluster %3 Configuration Change, capacity increased by %4 kb/s
//
#define CMEVT_MCA0                       0x40010037L

//
// MessageId: CMEVT_MCA1
//
// MessageText:
//
//  (CM) Warning - [%1/%2] Cluster %3 Configuration Change, capacity decreased by %4 kb/s
//
#define CMEVT_MCA1                       0x80010038L

//
// MessageId: CMEVT_DNP4
//
// MessageText:
//
//  (CM) Warning - [%1/%2] Unable to update DNP Configuration from SQL DB
//
#define CMEVT_DNP4                       0x80010039L

//
// MessageId: CMEVT_DNP5
//
// MessageText:
//
//  (CM) Information - [%1/%2] Updated DNP Configuration %3
//
#define CMEVT_DNP5                       0x4001003AL

//
// MessageId: CMEVT_MEMBERLOST
//
// MessageText:
//
//  (CM) Warning - [%1/%2] PeerMember instance %3 dropped off - resources retained for %4 milliseconds
//
#define CMEVT_MEMBERLOST                 0x8001003BL

//
// MessageId: CMEVT_MEMBERADDED
//
// MessageText:
//
//  (CM) Information - [%1/%2] PeerMember instance %3 joined
//
#define CMEVT_MEMBERADDED                0x4001003CL

//
// MessageId: CMEVT_NEWINTGRP
//
// MessageText:
//
//  (CM) Information - [%1/%2] PeerGroup %3 added to IGU list
//
#define CMEVT_NEWINTGRP                  0x4001003DL

//
// MessageId: CMEVT_NOTSAMEDNP
//
// MessageText:
//
//  (CM) Warning - [%1/%2] Member instance %3 dropped - incompatible DNP configuration
//
#define CMEVT_NOTSAMEDNP                 0x8001003FL

//
// MessageId: CMEVT_INTGRPNOMORE
//
// MessageText:
//
//  (CM) Warning - [%1/%2] PeerGroup %3 no longer considered in IGU list
//
#define CMEVT_INTGRPNOMORE               0x80010040L

//
// MessageId: CMEVT_MEMBERNOMORE
//
// MessageText:
//
//  (CM) Warning - [%1/%2] Member instance %3 no longer considered
//
#define CMEVT_MEMBERNOMORE               0x80010041L

//
// MessageId: CMEVT_REDUNDANTADD
//
// MessageText:
//
//  (CM) Warning - [%1/%2] Member add not heard - delivering redundant ADD
//
#define CMEVT_REDUNDANTADD               0x80010042L

//
// MessageId: CMEVT_REDUNDANTIGU
//
// MessageText:
//
//  (CM) Warning - [%1/%2] Member IGU message not heard - delivering redundant IGU
//
#define CMEVT_REDUNDANTIGU               0x80010043L

//
// MessageId: CMEVT_BADDNPSCHEMA
//
// MessageText:
//
//  (CM) Error - [%1/%2] Invalid or incompatible DNP Configuration schema %3
//
#define CMEVT_BADDNPSCHEMA               0xC0010044L

//
// MessageId: CMEVT_DNP6
//
// MessageText:
//
//  (CM) Warning - [%1/%2] ServiceGroup Usage Alarm: Group %3, Asset %4, SystemUsage %5, AssetUsage %6
//
#define CMEVT_DNP6                       0x80010045L

//
// MessageId: CMEVT_DNFAILED
//
// MessageText:
//
//  (CM) Warning - [%1/%2] DNResources error %3 TSID(ASI/RF)=%4/%5
//
#define CMEVT_DNFAILED                   0x80010046L

//
// MessageId: CMEVT_MCAFAILED
//
// MessageText:
//
//  (CM) Warning - [%1/%2] MCA Configure error %3/%4 Slice=%5/%6/%7
//
#define CMEVT_MCAFAILED                  0x80010047L

//
// MessageId: CMEVT_STREAMFAILED
//
// MessageText:
//
//  (CM) Warning - [%1/%2] MCA Stream error %3/%4 Slice=%5/%6/%7
//
#define CMEVT_STREAMFAILED               0x80010048L

//
// MessageId: CMEVT_NOPATH
//
// MessageText:
//
//  (CM) Warning - [%1/%2] No delivery path available: Asset=%3, SrvGrp=%4
//
#define CMEVT_NOPATH                     0x80010049L

//
// MessageId: CMEVT_NOREPLICA
//
// MessageText:
//
//  (CM) Warning - [%1/%2] No Replica for Asset %3, SrvGrp=%4, Set-top=%5, error=%6
//
#define CMEVT_NOREPLICA                  0x8001004AL

//
// MessageId: CMEVT_APPCREATEFAIL
//
// MessageText:
//
//  (CM) Warning - [%1/%2] No AppServer for Asset=%3, Nodegroup=%4, Error=%5/%6
//
#define CMEVT_APPCREATEFAIL              0x8001004BL

//
// MessageId: CMEVT_DNRELEASE
//
// MessageText:
//
//  (CM) Warning - [%1/%2] Delivery Network (SRM) released Session=%3, Path=%4/%5/%6/%7/%8
//
#define CMEVT_DNRELEASE                  0x8001004CL

//
// MessageId: CMEVT_TUNEERROR
//
// MessageText:
//
//  (CM) Warning - [%1/%2] TuneError Settop=%3, Path=%4/%5/%6/%7/%8
//
#define CMEVT_TUNEERROR                  0x8001004DL

//
// MessageId: CMEVT_POSITIONERROR
//
// MessageText:
//
//  (CM) Warning - [%1/%2] PositionError Settop=%3, Path=%4/%5/%6/%7/%8
//
#define CMEVT_POSITIONERROR              0x8001004EL

//
// MessageId: CMEVT_TRICKERROR
//
// MessageText:
//
//  (CM) Warning - [%1/%2] TrickCommError Settop=%3, Path=%4/%5/%6/%7/%8
//
#define CMEVT_TRICKERROR                 0x8001004FL

//
// MessageId: CMEVT_CLIENTERROR
//
// MessageText:
//
//  (CM) Warning - [%1/%2] UnknownError Settop=%3, Path=%4/%5/%6/%7/%8
//
#define CMEVT_CLIENTERROR                0x80010050L

//
// MessageId: CMEVT_NOASSET
//
// MessageText:
//
//  (CM) Warning - [%1/%2] No such Asset %3, SrvGrp=%4, Set-top=%5, error=%6
//
#define CMEVT_NOASSET                    0x80010051L

//
// MessageId: CMEVT_SSCREATEFAIL
//
// MessageText:
//
//  (CM) Warning - [%1/%2] No Streaming Service available on Cluster=%3, Node=%4, for Asset=%5, Nodegroup=%6, Error=%7/%8
//
#define CMEVT_SSCREATEFAIL               0x80010052L

//
// MessageId: CMEVT_CREATEFAIL
//
// MessageText:
//
//  (CM) Warning - [%1/%2] Unable to create stream on Cluster=%3, Node=%4, for Asset=%5, Nodegroup=%6, Error=%7/%8
//
#define CMEVT_CREATEFAIL                 0x80010053L

//
// MessageId: CMEVT_NOASLISTAVAILABLE
//
// MessageText:
//
//  (CM) Warning - [%1/%2] Unable to retrieve AppServer list from the Streaming Service, no AppServers will be advertised, Error=%3/%4
//
#define CMEVT_NOASLISTAVAILABLE          0x80010054L

//
// MessageId: CMEVT_USINGOLDASLIST
//
// MessageText:
//
//  (CM) Warning - [%1/%2] Unable to retrieve updated AppServer list from the Streaming Service, old AppServer list will be advertised, Error=%3/%4
//
#define CMEVT_USINGOLDASLIST             0x80010055L

//
// MessageId: CMEVT_NOAPPSERVERS
//
// MessageText:
//
//  (CM) Warning - [%1/%2] The Streaming Service reports no AppServers are available, none will be advertised this cycle
//
#define CMEVT_NOAPPSERVERS               0x80010056L

//
// MessageId: CMEVT_NOSRMAVAILABLE
//
// MessageText:
//
//  (CM) Warning - [%1/%2] Unable to establish a connection to the SRM at %3 [DSMCC Error=%4]
//
#define CMEVT_NOSRMAVAILABLE             0x80010057L

////////////////////////////////////////////////////////////////////////////////
// Connection Manager session setup failure messages.
////////////////////////////////////////////////////////////////////////////////
// Note: stream error messages start at 200 and go up from there to distinguish
// them from other events.
//
// MessageId: CMEVT_STRERR_BADFORMAT_BADFUNCTION
//
// MessageText:
//
//  (CM) Error - [%1/%2] Session setup failed for %3 - BADFORMAT/BADFUNCTION.  ICM rejected the ITV Client application's session setup request because it contained an invalid function specification.  This problem is typically due to an error in the Client application code.
//
#define CMEVT_STRERR_BADFORMAT_BADFUNCTION 0xC00100C8L

//
// MessageId: CMEVT_STRERR_BADFORMAT_BADSUBFUNCTION
//
// MessageText:
//
//  (CM) Error - [%1/%2] Session setup failed for %3 - BADFORMAT/BADSUBFUNCTION.  ICM rejected the ITV Client application's session setup request because it contained an invalid subfunction specification.  This problem is typically due to an error in the Client application code.
//
#define CMEVT_STRERR_BADFORMAT_BADSUBFUNCTION 0xC00100C9L

//
// MessageId: CMEVT_STRERR_BADFORMAT_UNSUPPORTED
//
// MessageText:
//
//  (CM) Error - [%1/%2] Session setup failed for %3 - BADFORMAT/UNSUPPORTED.  ICM rejected the ITV Client application's session setup request because it contained an unsupported operation.  This problem is typically due to an error in the Client application code.
//
#define CMEVT_STRERR_BADFORMAT_UNSUPPORTED 0xC00100CAL

//
// MessageId: CMEVT_STRERR_CLIENTERROR_POSITIONERROR
//
// MessageText:
//
//  (CM) Error - [%1/%2] Session setup failed for %3 - CLIENTERROR/POSITIONERROR.  The session failed because the ITV Client application was unable to successfully position and play the stream.  This problem can occur if the ITV Client application forwards an inaccurate starting point (Normal Play Time - NPT) specification when instructing the MCA about where (relative to the beginning of the asset) to resume a suspended stream. (For example, the Client may have specified an NPT beyond the end of the video.) When this happens, the instance of MCA running on the video server delivering the stream detects the positioning problem and reports the error (through the ICM to the SRM) to the Client application.
//
#define CMEVT_STRERR_CLIENTERROR_POSITIONERROR 0xC00100CBL

//
// MessageId: CMEVT_STRERR_CLIENTERROR_TRICKCOMMERROR
//
// MessageText:
//
//  (CM) Error - [%1/%2] Session setup failed for %3 - CLIENTERROR/TRICKCOMMERROR.  The session failed because the ITV Client application was unable to establish a stream operations (trick mode) connection with this instance of ICM.  This problem is typically caused by an intermittent loss of two-way (TCP/IP) connectivity (via the QPSK modulation/demodulation devices) between the ITV Client application and the ICM.  The problem can also occur if the Client application is using the a bad IP address (either primary or secondary) when attempting to communicate with the ICM.
//
#define CMEVT_STRERR_CLIENTERROR_TRICKCOMMERROR 0xC00100CCL

//
// MessageId: CMEVT_STRERR_CLIENTERROR_TUNEERROR
//
// MessageText:
//
//  (CM) Error - [%1/%2] Session setup failed for %3 - CLIENTERROR/TUNEERROR.  The session failed because the set-top O/S (under the direction of the requesting ITV Client application) was unable to tune to the RF frequency and/or program number specified by the SRM.
//
#define CMEVT_STRERR_CLIENTERROR_TUNEERROR 0xC00100CDL

//
// MessageId: CMEVT_STRERR_CLIENTERROR_UNKNOWN
//
// MessageText:
//
//  (CM) Error - [%1/%2] Session setup failed for %3 - CLIENTERROR/UNKNOWN.  For some unknown reason, the ITV Client application running on the set-top box issued a request to the ICM to release and tear down the referenced ACTIVE session.
//
#define CMEVT_STRERR_CLIENTERROR_UNKNOWN 0xC00100CEL

//
// MessageId: CMEVT_STRERR_COMMERROR_DSMCC
//
// MessageText:
//
//  (CM) Error - [%1/%2] Session setup failed for %3 - COMMERROR/DSMCC.  The session setup or teardown process failed due to an inability of the ICM to communicate with the SRM.
//
#define CMEVT_STRERR_COMMERROR_DSMCC     0xC00100CFL

//
// MessageId: CMEVT_STRERR_CONFIGUREFAILED_RESOURCENOTAVAILABLE
//
// MessageText:
//
//  (CM) Error - [%1/%2] Session setup failed for %3 - CONFIGUREFAILED/RESOURCENOTAVAILABLE.  The session configuration process failed because one of the MediaCluster elements (CLUSTER, SLICEGROUP, or SLICE) specified in path selected by ICM was not available to fulfill the request.
//
#define CMEVT_STRERR_CONFIGUREFAILED_RESOURCENOTAVAILABLE 0xC00100D0L

//
// MessageId: CMEVT_STRERR_CONFIGUREFAILED_RETRIESEXHAUSTED
//
// MessageText:
//
//  (CM) Error - [%1/%2] Session setup failed for %3 - CONFIGUREFAILED/RETRIESEXHAUSTED.  The session configuration process failed because of either of the following reasons: The MediaCluster elements (CLUSTER, SLICEGROUP, and SLICE) specified in original path selected by ICM had insufficient resources to fulfill the request and there were no alternative delivery paths configured; The MediaCluster elements (CLUSTER, SLICEGROUP, and SLICE) specified in original path selected by ICM, as well as those elements on all configured alternative paths, were found to have insufficient resources to fulfill the request.
//
#define CMEVT_STRERR_CONFIGUREFAILED_RETRIESEXHAUSTED 0xC00100D1L

//
// MessageId: CMEVT_STRERR_CONNECTFAILED_SYSTEMERROR
//
// MessageText:
//
//  (CM) Error - [%1/%2] Session setup failed for %3 - CONNECTFAILED/SYSTEMERROR.  ICM encountered a serious system error (e.g.  hardware failure, memory corruption, etc.) that has created an inconsistency in ICM's internal representation of active connections and their associated streams.
//
#define CMEVT_STRERR_CONNECTFAILED_SYSTEMERROR 0xC00100D2L

//
// MessageId: CMEVT_STRERR_CREATEFAILED_APPNOTAVAILABLE
//
// MessageText:
//
//  (CM) Error - [%1/%2] Session setup failed for %3 - CREATEFAILED/APPNOTAVAILABLE.  The stream creation process failed because MCAServer was unable to find any instance (in a compatible peer group) of the ITV Application Server associated with the requesting ITV client application to acknowledge or approve the stream creation request.  For example, in the case of the Movies-On-Demand application, no instance of the MOD Server Service was available to consider the request incoming from the requesting instance of the MOD Client application.
//
#define CMEVT_STRERR_CREATEFAILED_APPNOTAVAILABLE 0xC00100D3L

//
// MessageId: CMEVT_STRERR_CREATEFAILED_DUPLICATESESSIONID
//
// MessageText:
//
//  (CM) Error - [%1/%2] Session setup failed for %3 - CREATEFAILED/DUPLICATESESSIONID.  The stream creation process failed because the requesting ITV Client application forwarded a session setup request to the ICM that contained a Session ID identical to the ID of another session already known to the ICM.  This error is rare, but can sometimes occur when an ITV Client application starts, makes a session setup request to the ICM, re-starts (due to a power-off of the set-top box or other cause), then makes the same setup request to the same instance of ICM.  To generate the error, this process would have to complete before the SRM is able to detect that the Client has stopped sending 'keep-alive' messages for the original session and tears the session down.
//
#define CMEVT_STRERR_CREATEFAILED_DUPLICATESESSIONID 0xC00100D4L

//
// MessageId: CMEVT_STRERR_CREATEFAILED_EXSYSTEMERROR
//
// MessageText:
//
//  (CM) Error - [%1/%2] Session setup failed for %3 - CREATEFAILED/EXSYSTEMERROR.  The stream creation process failed due to serious internal ICM error or because the Streaming Service component returned a serious, unexpected error in response to the CreateStream request.
//
#define CMEVT_STRERR_CREATEFAILED_EXSYSTEMERROR 0xC00100D5L

//
// MessageId: CMEVT_STRERR_CREATEFAILED_NOTACCEPTED
//
// MessageText:
//
//  (CM) Error - [%1/%2] Session setup failed for %3 - CREATEFAILED/NOTACCEPTED.  The stream creation operation failed because the ITV Application Server service (e.g.  MOD Server service) associated with the requesting ITV Client application did not accept the stream creation request forwarded by MCA Server.
//
#define CMEVT_STRERR_CREATEFAILED_NOTACCEPTED 0xC00100D6L

//
// MessageId: CMEVT_STRERR_CREATEFAILED_NOTACCEPTED_BADASSET
//
// MessageText:
//
//  (CM) Error - [%1/%2] Session setup failed for %3 - CREATEFAILED/NOTACCEPTED_BADASSET.  The stream creation (resume) operation failed.  The MOD Server service rejected the session setup request because it detected a problem with the requested asset.  The asset may be missing one or more pieces of expected metadata or may recently have been de-activated and can no longer be purchased.  For streams-in- progress, this message can also be generated if the subscriber attempts to resume a suspended asset after it has been de-activated and if the MOD Server service is configured not to allow resumption of suspended assets.  Note: This message typically does not indicate a problem (corruption, etc.) with the MPEG file itself.
//
#define CMEVT_STRERR_CREATEFAILED_NOTACCEPTED_BADASSET 0xC00100D7L

//
// MessageId: CMEVT_STRERR_CREATEFAILED_NOTACCEPTED_BADCREDIT
//
// MessageText:
//
//  (CM) Error - [%1/%2] Session setup failed for %3 - CREATEFAILED/NOTACCEPTED_BADCREDIT.  The stream creation operation failed.  The MOD Server service rejected the session setup request because the subscriber account (associated with the set-top box on which the requesting ITV Client application is running) failed the session authorization check due to insufficient credit.
//
#define CMEVT_STRERR_CREATEFAILED_NOTACCEPTED_BADCREDIT 0xC00100D8L

//
// MessageId: CMEVT_STRERR_CREATEFAILED_NOTACCEPTED_BLOCKEDASSET
//
// MessageText:
//
//  (CM) Error - [%1/%2] Session setup failed for %3 - CREATEFAILED/NOTACCEPTED_BLOCKEDASSET.  The stream creation operation failed.  The MOD Server service rejected the session setup request because the requested asset has been blocked from viewing (by any subscriber) at this time.  The specific hours when an asset is available for purchase can be configured via the Asset Manager application (Studio tab in the Asset View window).  MSOs typically use this feature to restrict viewing of certain types of content (e.g.  adult content) to specific time slots.  For information on using the Asset Manager application, see the SeaChange Interactive Television System Asset Manager User's Guide.
//
#define CMEVT_STRERR_CREATEFAILED_NOTACCEPTED_BLOCKEDASSET 0xC00100D9L

//
// MessageId: CMEVT_STRERR_CREATEFAILED_NOTACCEPTED_DURATIONTIMEOUT
//
// MessageText:
//
//  (CM) Error - [%1/%2] Session setup failed for %3 - CREATEFAILED/NOTACCEPTED_DURATIONTIMEOUT.  The stream creation (resume) operation failed.  The MOD Server service rejected the session setup request because the configured rental time for the purchased asset (or SVOD package) had already expired.  This error most typically occurs when a subscriber suspends a stream-in-progress and does not attempt to resume the stream until after rental period for the asset (or for the SVOD package to which the asset belongs) has expired.
//
#define CMEVT_STRERR_CREATEFAILED_NOTACCEPTED_DURATIONTIMEOUT 0xC00100DAL

//
// MessageId: CMEVT_STRERR_CREATEFAILED_NOTACCEPTED_INTERNALERROR
//
// MessageText:
//
//  (CM) Error - [%1/%2] Session setup failed for %3 - CREATEFAILED/NOTACCEPTED_INTERNALERROR.  The stream creation operation failed.  The MOD Server service rejected the session setup request due to a serious, unexpected internal error.  This message can indicate a variety of internal problems including (but not limited to) inadequate virtual memory, use of the wrong version of an SQL stored procedure, or a version mis-match between MOD service and the IDS database (IdsData).
//
#define CMEVT_STRERR_CREATEFAILED_NOTACCEPTED_INTERNALERROR 0xC00100DBL

//
// MessageId: CMEVT_STRERR_CREATEFAILED_NOTACCEPTED_PKGINVALIDASSET
//
// MessageText:
//
//  (CM) Error - [%1/%2] Session setup failed for %3 - CREATEFAILED/NOTACCEPTED_PKGINVALIDASSET.  The stream creation operation failed.  The MOD Server service rejected the session setup request because the combination of the asset ID and its parent SVOD package ID provided by the Client application in the setup request does not exist in the IDS database (IdsData).
//
#define CMEVT_STRERR_CREATEFAILED_NOTACCEPTED_PKGINVALIDASSET 0xC00100DCL

//
// MessageId: CMEVT_STRERR_CREATEFAILED_NOTACCEPTED_PKGUNAVAILABLE
//
// MessageText:
//
//  (CM) Error - [%1/%2] Session setup failed for %3 - CREATEFAILED/NOTACCEPTED_PKGUNAVAILABLE.  The stream creation operation failed.  The MOD Server service rejected the session setup request because the subscriber has not yet signed up for SVOD service and does not yet exist in the Subscriber database (SubscriberData).  The requested asset has not been made available to the subscriber.
//
#define CMEVT_STRERR_CREATEFAILED_NOTACCEPTED_PKGUNAVAILABLE 0xC00100DDL

//
// MessageId: CMEVT_STRERR_CREATEFAILED_NOTACCEPTED_VIEWLIMIT
//
// MessageText:
//
//  (CM) Error - [%1/%2] Session setup failed for %3 - CREATEFAILED/NOTACCEPTED_VIEWLIMIT.  The stream creation operation failed.  The MOD Server service rejected the session setup request because the subscriber has already purchased the asset the maximum number of times permitted by the currently configured viewing limits for the asset.  The number of times that a subscriber is permitted to purchase an asset (within a specified time period) can be configured via the Asset Manager application.  For such assets, the MOD Server service keeps a running account (per subscriber) of the number times the asset has been purchased.  Once a subscriber has purchased the asset the maximum configured number of times permitted, the asset is no longer available to that subscriber for the remainder of the specified time period.  For information on using the Asset Manager application, see the SeaChange Interactive Television System Asset Manager User's Guide.
//
#define CMEVT_STRERR_CREATEFAILED_NOTACCEPTED_VIEWLIMIT 0xC00100DEL

//
// MessageId: CMEVT_STRERR_CREATEFAILED_SSNOTAVAILABLE
//
// MessageText:
//
//  (CM) Error - [%1/%2] Session setup failed for %3 - CREATEFAILED/SSNOTAVAILABLE.  The stream creation operation failed.  The ISS instance on the MediaCluster server referenced in the DNP selected by ICM to fulfill this session setup request was unavailable.  This may indicate a loss of connectivity between the ICM and the ISS component on the MediaCluster server or that the ISS component has stopped running.
//
#define CMEVT_STRERR_CREATEFAILED_SSNOTAVAILABLE 0xC00100DFL

//
// MessageId: CMEVT_STRERR_GETAEFAILED_COMMUNICATIONFAILED
//
// MessageText:
//
//  (CM) Error - [%1/%2] Session setup failed for %3 - GETAEFAILED/COMMUNICATIONFAILED.  The GET AE LIST operation failed.  While in the process of requesting the AE List from the IDS, ICM lost its ability to communicate with the IDS database due either to a communications/ network failure, or to an IDS or SQL problem on the IDS database machine.  See ‘‘GET AELIST Operation?for more information.  When ICM encounters this condition, it takes itself off-line and temporarily rejects all subsequent session setup requests. (See ‘‘REJECTED-NOCALLS?for more information.) The ICM instance also temporarily removes itself from the list of available ICM instances so that ITV clients will not attempt to use it until communications are restored and removes itself from the list of active System Components.
//
#define CMEVT_STRERR_GETAEFAILED_COMMUNICATIONFAILED 0xC00100E0L

//
// MessageId: CMEVT_STRERR_GETAEFAILED_INVALIDAELIST
//
// MessageText:
//
//  (CM) Error - [%1/%2] Session setup failed for %3 - GETAEFAILED/INVALIDAELIST.  The GET AELIST operation failed because the AE List retrieved by the ICM from the IDS was invalid.  The list may have been incomplete, may have been corrupted, may contain improperly configured asset or asset element attributes, or may contain one or more non-playable asset elements.
//
#define CMEVT_STRERR_GETAEFAILED_INVALIDAELIST 0xC00100E1L

//
// MessageId: CMEVT_STRERR_GETAEFAILED_INVALIDBITRATE
//
// MessageText:
//
//  (CM) Error - [%1/%2] Session setup failed for %3 - GETAEFAILED/INVALIDBITRATE.  The GET AELIST operation failed because one or more of the asset elements in the AE List returned by IDS contained an invalid bit-rate specification.  The ICM automatically rejects an AE lists that contain null (empty) zero, or negative (minus) bit-rate specifications.
//
#define CMEVT_STRERR_GETAEFAILED_INVALIDBITRATE 0xC00100E2L

//
// MessageId: CMEVT_STRERR_NOASSET_EXOK
//
// MessageText:
//
//  (CM) Error - [%1/%2] Session setup failed for %3 - NOASSET/EXOK.  The GET AELIST operation failed because the requested asset does not exist.  Although the IPS returned the location of at least one replica of the asset (in response to the GET REPLICA LIST operation), the IDS was unable to find any evidence of the asset when scanning the IdsData database during the GET AELIST operation.  The requested asset, which existed at the time the GET REPLICA LIST operation executed, may have been deleted before the GET AELIST operation was launched.  This error may indicate a problem with the ability of IPS to update instances of ICM with changes made to its table of available replicas. (See ‘‘How the ITV Connection Manager Processes Session Setup Requests?for more information on the GET REPLICA LIST and GET AELIST operations.)
//
#define CMEVT_STRERR_NOASSET_EXOK        0xC00100E3L

//
// MessageId: CMEVT_STRERR_NOASSET_SYSTEMERROR
//
// MessageText:
//
//  (CM) Error - [%1/%2] Session setup failed for %3 - NOASSET/SYSTEMERROR.  Session setup failed because ICM encountered an unexpected system error while processing an AE List.
//
#define CMEVT_STRERR_NOASSET_SYSTEMERROR 0xC00100E4L

//
// MessageId: CMEVT_STRERR_NODNP_DNCONGESTED
//
// MessageText:
//
//  (CM) Error - [%1/%2] Session setup failed for %3 - NODNP/DNCONGESTED.  This status message pair (exclusive to the Scientific-Atlanta environment) indicates that the stream creation process failed because the DNCS (Release 1.5 or later) was too busy to fulfill the AddResource request from the ICM within the configured time-out interval.
//
#define CMEVT_STRERR_NODNP_DNCONGESTED   0xC00100E5L

//
// MessageId: CMEVT_STRERR_NODNP_DNPPENALTYTOOHIGH
//
// MessageText:
//
//  (CM) Error - [%1/%2] Session setup failed for %3 - NODNP/DNPPENALTYTOOHIGH.  The stream creation process failed.  The ICM chose not to specify a DNP for the session because all candidate DNPs were found (due to insufficient remaining available bandwidth) to be 'over-penalized' and unable to support a session at that time.  When an ICM instance rejects a candidate DNP due to insufficient available bandwidth, it can apply a penalty (of variable severity) to that path, rendering it less likely to be selected (by that instance or other ICM instances) for configurable period of time.  The influence of a DNP penalty decreases over time.  This mechanism prevents ICM instances from immediately re-selecting a DNP that was recently found to have sufficient bandwidth to satisfy a stream creation request.  In the Scientific-Atlanta environment, this error may indicate resource problems with the QAMs (PIPEs) specified in the candidate DNPs.
//
#define CMEVT_STRERR_NODNP_DNPPENALTYTOOHIGH 0xC00100E6L

//
// MessageId: CMEVT_STRERR_NODNP_EXOK
//
// MessageText:
//
//  (CM) Error - [%1/%2] Session setup failed for %3 - NODNP/EXOK.  The session setup process failed because the ICM could find no complete DNP from a MediaCluster that stores the requested asset to the target set-top's Node Group.  This could indicate one or more of the following conditions: The requested asset has not yet been propagated to an ITV MediaCluster that is configured to service the target Node Group; The number of DNPs physically cabled and configured to service the target Node Group is insufficient or some (or all) existing cabled DNPs have not yet been specified in the DNP Table on which this instance of ICM is focused.
//
#define CMEVT_STRERR_NODNP_EXOK          0xC00100E7L

//
// MessageId: CMEVT_STRERR_NODNP_NOALTERNATES
//
// MessageText:
//
//  (CM) Error - [%1/%2] Session setup failed for %3 - NODNP/NOALTERNATES.  The session setup process failed.  After failing to successfully configure the delivery path initially selected during the GET DNP operation, the ICM repeated the GET DNP operation, selected an alternative delivery path, then re-tried the configuration.  When this path also failed, the ICM repeated this process with all remaining alternative delivery paths (maximum of three retries).  After exhausting the list of possible alternate paths without success, ICM abandoned the setup process and logged this error message in the ICM Request Log.
//
#define CMEVT_STRERR_NODNP_NOALTERNATES  0xC00100E8L

//
// MessageId: CMEVT_STRERR_NODNP_NOCLUSTERBW
//
// MessageText:
//
//  (CM) Error - [%1/%2] Session setup failed for %3 - NODNP/NOCLUSTERBW.  The session setup process failed.  During the GET DNP operation, the ITV MediaCluster specified in the network delivery path chosen by ICM was found to have insufficient available bandwidth to service the request.
//
#define CMEVT_STRERR_NODNP_NOCLUSTERBW   0xC00100E9L

//
// MessageId: CMEVT_STRERR_NODNP_NOCLUSTERSTR
//
// MessageText:
//
//  (CM) Error - [%1/%2] Session setup failed for %3 - NODNP/NOCLUSTERSTR.  The session setup process failed.  During the GET DNP operation, the ITV MediaCluster specified in the network delivery path chosen by ICM was found to have insufficient available stream capacity to service the request.
//
#define CMEVT_STRERR_NODNP_NOCLUSTERSTR  0xC00100EAL

//
// MessageId: CMEVT_STRERR_NODNP_NOPIPE
//
// MessageText:
//
//  (CM) Error - [%1/%2] Session setup failed for %3 - NODNP/NOPIPE.  The session setup process failed.  During the GET DNP operation, the QAM specified in the network delivery path chosen by ICM was found to have insufficient resources (bandwidth, etc.) to service the setup request.
//
#define CMEVT_STRERR_NODNP_NOPIPE        0xC00100EBL

//
// MessageId: CMEVT_STRERR_NODNP_NOSLICEGROUPBW
//
// MessageText:
//
//  (CM) Error - [%1/%2] Session setup failed for %3 - NODNP/NOSLICEGROUPBW.  The session setup process failed.  During the GET DNP operation, the SLICEGROUP (Video Server) specified in the network delivery path chosen by ICM was found to have insufficient available bandwidth to service the request.
//
#define CMEVT_STRERR_NODNP_NOSLICEGROUPBW 0xC00100ECL

//
// MessageId: CMEVT_STRERR_NODNP_NOSLICEGROUPSTR
//
// MessageText:
//
//  (CM) Error - [%1/%2] Session setup failed for %3 - NODNP/NOSLICEGROUPSTR.  The session setup process failed.  During the GET DNP operation, the SLICEGROUP (Video Server) specified in the network delivery path chosen by ICM was found to have insufficient available stream capacity to service the request.
//
#define CMEVT_STRERR_NODNP_NOSLICEGROUPSTR 0xC00100EDL

//
// MessageId: CMEVT_STRERR_NODNP_NOSLICEBW
//
// MessageText:
//
//  (CM) Error - [%1/%2] Session setup failed for %3 - NODNP/NOSLICEBW.  The session setup process failed.  During the GET DNP operation, the SLICE (DVB/ASI board) specified in the network delivery path chosen by ICM was found to have insufficient available bandwidth to service the request.
//
#define CMEVT_STRERR_NODNP_NOSLICEBW     0xC00100EEL

//
// MessageId: CMEVT_STRERR_NODNP_NOSLICESTR
//
// MessageText:
//
//  (CM) Error - [%1/%2] Session setup failed for %3 - NODNP/NOSLICESTR.  The session setup process failed.  During the GET DNP operation, the SLICE (edge card) specified in the network delivery path chosen by ICM was found to have insufficient available stream capacity to service the request.
//
#define CMEVT_STRERR_NODNP_NOSLICESTR    0xC00100EFL

//
// MessageId: CMEVT_STRERR_NOREPLICA_EXOK
//
// MessageText:
//
//  (CM) Error - [%1/%2] Session setup failed for %3 - NOREPLICA/EXOK.  The session setup process failed during the Get Replica List operation.  IPS was unable to locate a playable replica of the requested asset on any ITV MediaCluster.  The requested asset may have just become ACTIVE (and so can be selected by the subscriber), but no replica of the asset has yet been copied to any MediaCluster configured to deliver the asset to the target Node Group.  This error could also be reported if a playable replica existed on an appropriate MediaCluster, but the entire cluster was unavailable at the time ICM requested the Replica List.
//
#define CMEVT_STRERR_NOREPLICA_EXOK      0xC00100F0L

//
// MessageId: CMEVT_STRERR_NOREPLICA_SYSTEMERROR
//
// MessageText:
//
//  (CM) Error - [%1/%2] Session setup failed for %3 - NOREPLICA/SYSTEMERROR.  The session setup process failed during the Get Replica List operation.  This instance of ICM encountered an unexpected system error while requesting (from the IPS) a list of the ITV MediaClusters that store a replica of the asset referenced in the ITV application client's session-setup request.
//
#define CMEVT_STRERR_NOREPLICA_SYSTEMERROR 0xC00100F1L

//
// MessageId: CMEVT_STRERR_READYFAILED_SYSTEMERROR
//
// MessageText:
//
//  (CM) Error - [%1/%2] Session setup failed for %3 - READYFAILED/SYSTEMERROR.  Session setup failed in the final stage of the setup process because the MCA Server service (running on the ITV MediaCluster selected by ICM to deliver the asset) was, for some reason, unable to prime or play the stream.
//
#define CMEVT_STRERR_READYFAILED_SYSTEMERROR 0xC00100F2L

//
// MessageId: CMEVT_STRERR_REJECTED_NAG
//
// MessageText:
//
//  (CM) Error - [%1/%2] Session setup failed for %3 - REJECTED/NAG.  The ICM rejected an incoming session setup request because an identical request from the same ITV Client application was received within the time-out threshold as specified by the value ICM's NagRequestTimeout service variable.  This mechanism is designed to defeat so-called 'denial of service' attacks from ITV Client applications mistakenly (or deliberately) programmed to continuously request the same asset over and over again, needlessly consuming ICM resources.  You can review the currently configured value of the NagRequestTimeout variable by choosing the ITV System Monitor's System Components query, and then selecting the instance of ICM (ICM@machine-name) in which you are interested.
//
#define CMEVT_STRERR_REJECTED_NAG        0xC00100F3L

//
// MessageId: CMEVT_STRERR_REJECTED_NOCALLS
//
// MessageText:
//
//  (CM) Error - [%1/%2] Session setup failed for %3 - REJECTED/NOCALLS.  The ICM rejected an incoming session setup request because, for some reason, it is currently refusing to handle any new requests.  Instances of ICM can deliberately remove themselves from active service for a variety of reasons including, loss of connectivity to a vital ITV Service (e.g.  IDS, IPS, MCA, etc.) or if it detects that it is no longer synchronized with the other ICM instances in its peer group.  In these cases the ICM instance temporarily stops advertising its availability to requesting Client applications, removes itself from the SeaChange System Monitor's list of active System Components, and places itself on the Inactive Components list until the problem is resolved.
//
#define CMEVT_STRERR_REJECTED_NOCALLS    0xC00100F4L

//
// MessageId: CMEVT_STRERR_RESOURCEFAILED_DNRESREJECTED
//
// MessageText:
//
//  (CM) Error - [%1/%2] Session setup failed for %3 - RESOURCEFAILED/DNRESREJECTED.  The session setup failed because the SRM (for some unspecified reason) did not approve use of the QAM specified in the ICM's AddResource request.  The requested QAM may be over-committed, or otherwise unavailable.  In certain rare cases, the PIPE element (and/or the DNP selected by the ICM) may no longer exist (due to recent deletion or other reason) in the DNP table associated with the peer group of which this instance of ICM is currently focused.
//
#define CMEVT_STRERR_RESOURCEFAILED_DNRESREJECTED 0xC00100F5L

//
// MessageId: CMEVT_STRERR_RESOURCEFAILED_DNTIMEOUT
//
// MessageText:
//
//  (CM) Error - [%1/%2] Session setup failed for %3 - RESOURCEFAILED/DNTIMEOUT.  The session setup failed because the SRM did not return a confirmation response to the ICM's AddResource request within the ICM's configured time-out interval.  This error may indicate a slow QAM or a possible network connectivity problem between the QAM and the DNCS.
//
#define CMEVT_STRERR_RESOURCEFAILED_DNTIMEOUT 0xC00100F6L

//
// MessageId: CMEVT_STRERR_RESOURCEFAILED_DSMCC
//
// MessageText:
//
//  (CM) Error - [%1/%2] Session setup failed for %3 - RESOURCEFAILED/DSMCC.  The session setup failed because SRM-to-ICM signaling was interrupted due to a communications error.
//
#define CMEVT_STRERR_RESOURCEFAILED_DSMCC 0xC00100F7L

//
// MessageId: CMEVT_STRERR_SETUPTIMEOUT_CLIENTTIMEOUT
//
// MessageText:
//
//  (CM) Error - [%1/%2] Session setup failed for %3 - SETUPTIMEOUT/CLIENTTIMEOUT.  Session setup failed because the requesting ITV Client application failed to respond to the ICM's session setup confirmation message within the configured time-out interval.  This problem is most typically caused by intermittent QPSK communications problems on the forward data channel.  This error can also be generated if the ICM's session setup confirmation message (transmitted to the ITV Client application via the UDP protocol) is lost in transit.
//
#define CMEVT_STRERR_SETUPTIMEOUT_CLIENTTIMEOUT 0xC00100F8L

//
// MessageId: CMEVT_STRERR_SETUPTIMEOUT_CONFIGSTRTIMEOUT
//
// MessageText:
//
//  (CM) Error - [%1/%2] Session setup failed for %3 - SETUPTIMEOUT/CONFIGSTRTIMEOUT.  Session setup failed because the MCA Server process on the ITV MediaCluster selected by ICM as the source for this stream failed to start configuring (priming) the stream within the configured time-out interval.  The most common reasons for this problem include the following: A temporary loss of network communication between the ICM and the MCA Server process on the target MediaCluster; A temporary delay in processing ICM's request due to an unexpectedly heavy MCA work load on the MediaCluster.
//
#define CMEVT_STRERR_SETUPTIMEOUT_CONFIGSTRTIMEOUT 0xC00100F9L

//
// MessageId: CMEVT_STRERR_SETUPTIMEOUT_CREATESTREAMTIMEOUT
//
// MessageText:
//
//  (CM) Error - [%1/%2] Session setup failed for %3 - SETUPTIMEOUT/CREATESTREAMTIMEOUT.  Session setup failed because it took longer than the configured time-out interval to create, configure, and start the stream.  The most common reason for this type of problem is a temporary communication problem causing a delay or failure in the delivery of inter-service messages.
//
#define CMEVT_STRERR_SETUPTIMEOUT_CREATESTREAMTIMEOUT 0xC00100FAL

//
// MessageId: CMEVT_STRERR_SETUPTIMEOUT_GETAELISTTIMEOUT
//
// MessageText:
//
//  (CM) Error - [%1/%2] Session setup failed for %3 - SETUPTIMEOUT/GETAELISTTIMEOUT.  Session setup failed because the IDS failed to respond to the ICM's request for an Asset Element List (AE List) within the configured time-out interval.  See ‘‘GET AELIST Operation?for more information.
//
#define CMEVT_STRERR_SETUPTIMEOUT_GETAELISTTIMEOUT 0xC00100FBL

//
// MessageId: CMEVT_STRERR_SETUPTIMEOUT_GETREPLICATIMEOUT
//
// MessageText:
//
//  (CM) Error - [%1/%2] Session setup failed for %3 - SETUPTIMEOUT/GETREPLICATIMEOUT.  Session setup failed because the IPS failed to respond to the ICM's request for a Replica List within the configured timeout interval.  This instance of ICM must rely on Replica List information in its cache which may no longer be up-to-date.
//
#define CMEVT_STRERR_SETUPTIMEOUT_GETREPLICATIMEOUT 0xC00100FCL

//
// MessageId: CMEVT_STRERR_STREAMABORTED_SYSTEMERROR
//
// MessageText:
//
//  (CM) Error - [%1/%2] Session setup failed for %3 - STREAMABORTED/SYSTEMERROR.  An active session was terminated due to a failure of the streaming subsystem components (MCA, VStream) delivering the stream.
//
#define CMEVT_STRERR_STREAMABORTED_SYSTEMERROR 0xC00100FDL

//
// MessageId: CMEVT_STRERR_SYSTEMERROR_NOMPEGDATA
//
// MessageText:
//
//  (CM) Error - [%1/%2] Session setup failed for %3 - SYSTEMERROR/NOMPEGDATA.  The Client was able to tune to the specified RF channel and MPEG program number, but suspended the session setup process when it was unable to detect any MPEG data.  This indicates a possible connectivity problem between the source MediaCluster server and the QAM and a problem with the source MediaCluster server itself.
//
#define CMEVT_STRERR_SYSTEMERROR_NOMPEGDATA 0xC00100FEL

//
// MessageId: CMEVT_STRERR_SYSTEMERROR_RFNOTAVAILABLE
//
// MessageText:
//
//  (CM) Error - [%1/%2] Session setup failed for %3 - SYSTEMERROR/RFNOTAVAILABLE.  The Client application suspended the session setup process when the Radio Frequency (RF) to which the Client was supposed to tune could not be found.  The Client was able to detect other frequencies (from other QAMs in the multi-QAM device) proving that the device is properly cabled and indicating a possible problem with the source QAM.
//
#define CMEVT_STRERR_SYSTEMERROR_RFNOTAVAILABLE 0xC00100FFL

//
// MessageId: CMEVT_STRERR_SYSTEMERROR_PROVIDERIDLOOKUPFAILED
//
// MessageText:
//
//  (CM) Error - [%1/%2] Session setup failed for %3 - SYSTEMERROR/PROVIDERIDLOOKUPFAILED.  Todo.
//
#define CMEVT_STRERR_SYSTEMERROR_PROVIDERIDLOOKUPFAILED 0xC0010100L

//
// MessageId: CMEVT_STRERR_NOASSET_PROVIDERIDLOOKUPFAILED
//
// MessageText:
//
//  (CM) Error - [%1/%2] Session setup failed for %3 - NOASSET/RFNOTAVAILABLE.  Todo.
//
#define CMEVT_STRERR_NOASSET_PROVIDERIDLOOKUPFAILED 0xC0010101L

//
// MessageId: CMEVT_STRERR_SETUPTIMEOUT_PROVIDERIDLOOKUPTIMEOUT
//
// MessageText:
//
//  (CM) Error - [%1/%2] Session setup failed for %3 - SETUPTIMEOUT/PROVIDERIDLOOKUPTIMEOUT.
//
#define CMEVT_STRERR_SETUPTIMEOUT_PROVIDERIDLOOKUPTIMEOUT 0xC0010102L

////////////////////////////////////////////////////////////////////////////////
// Connection Manager session failure messages.
////////////////////////////////////////////////////////////////////////////////
//
// MessageId: CMEVT_STRERR_CLIENTERROR_NETWORKRELEASE
//
// MessageText:
//
//  (CM) Error - [%1/%2] Session failed for %3 - CLIENTERROR/NETWORKRELEASE.  The SRM released (terminated) the session-in-progress because it did not receive the expected 'session-in-progress' message from the requesting ITV Client application.  Once a session is active, the SRM is configured to expect session-in-progress messages at regular intervals from the requesting Client application, notifying the SRM that the Client is still using the session.  (The SRM update interval between expected messages is configurable and can vary from one ITV site to another.) If the SRM fails to receive the session-in-progress message within the configured time-out interval, it waits through another interval and, if it still does not receive the message, releases the session.  This error is most typically caused by a power-off (or O/S crash) on the destination set-top box, but can also indicate a problem with a modulation/demodulation device (QPSK) or a network problem that is preventing the Client application from communicating with the SRM.
//
#define CMEVT_STRERR_CLIENTERROR_NETWORKRELEASE 0xC001012CL

//
// MessageId: CMEVT_STRERR_CLIENTERROR_SESSIONRESET
//
// MessageText:
//
//  (CM) Error - [%1/%2] Session failed for %3 - CLIENTERROR/SESSIONRESET.  One or more sessions-in-progress failed because the ITV Client application (for some unknown reason) requested the SRM to terminate all of its active sessions and release the delivery network resources associated with them. (Note: Client resets, as defined in the DSM-CC protocol, are supported only by the ISRM.  Client reset operations are not currently supported by Scientific-Atlanta's DNCS.) This error may also generate a corresponding ‘‘CLIENTERROR-NETWORKRELEASE?error.
//
#define CMEVT_STRERR_CLIENTERROR_SESSIONRESET 0xC001012DL

//
// MessageId: CMEVT_STRERR_SYSTEMERROR_VIDEOLOSTQAMOK
//
// MessageText:
//
//  (CM) Error - [%1/%2] Session failed for %3 - SYSTEMERROR/VIDEOLOSTQAMOK.  The Client application reported that the referenced video stream-in-progress terminated abnormally, but the associated QAM channel continues to successfully handle other MPEG streams and appears to be functioning normally.  This indicates a possible problem on the source MediaCluster server.
//
#define CMEVT_STRERR_SYSTEMERROR_VIDEOLOSTQAMOK 0xC001012EL

////////////////////////////////////////////////////////////////////////////////
// Connection Manager recovery/reconciliation failure messages.
////////////////////////////////////////////////////////////////////////////////
//
// MessageId: CMEVT_STRERR_RECONCILIATIONFAILED_EXOK
//
// MessageText:
//
//  (CM) Error - [%1/%2] Session reconciliation failed for %3 - RECONCILIATIONFAILED/EXOK.  After re-starting (due to a re-boot or other reason), the ICM was able to recover an interrupted session, but the reconciliation process failed because the SRM no longer had any knowledge of that session.
//
#define CMEVT_STRERR_RECONCILIATIONFAILED_EXOK 0xC0010190L

//
// MessageId: CMEVT_STRERR_RECOVERYFAILED_NOCONNECTION
//
// MessageText:
//
//  (CM) Error - [%1/%2] Session recovery failed for %3 - RECOVERYFAILED/NOCONNECTION.  Session recovery failed.  Following an interruption of service, ICM successfully recovered the session's stream information, but was unable to recover information about its associated connection.
//
#define CMEVT_STRERR_RECOVERYFAILED_NOCONNECTION 0xC0010191L

//
// MessageId: CMEVT_STRERR_RECOVERYFAILED_RECOVERYTIMEOUT
//
// MessageText:
//
//  (CM) Error - [%1/%2] Session recovery failed for %3 - RECOVERYFAILED/RECOVERYTIMEOUT.  Session recovery failed.  Following an interruption of service, ICM still had knowledge of the session's stream and corresponding connection information, but MCA Sever failed to signal its own knowledge of the session to ICM within the configured time-out interval.  This error may indicate a problem with MCA or with delivery network connections.
//
#define CMEVT_STRERR_RECOVERYFAILED_RECOVERYTIMEOUT 0xC0010192L

//
// MessageId: CMEVT_STRERR_RECOVERYFAILED_SSRECOVERYTIMEOUT
//
// MessageText:
//
//  (CM) Error - [%1/%2] Session recovery failed for %3 - RECOVERYFAILED/SSRECOVERYTIMEOUT.  After re-starting (due to a power outage, re-boot, or other reason), the ICM attempted to recover the interrupted session but was unable to do so because the operative ISS instance on the source MediaCluster failed (for some unspecified reason) to issue a reconnect callback to the ICM within the configured timeout interval.  As a result, the ICM was forced to tear down the session.
//
#define CMEVT_STRERR_RECOVERYFAILED_SSRECOVERYTIMEOUT 0xC0010193L

//
// MessageId: CMEVT_STRERR_RECOVERYFAILED_SHOULDNOTHAPPEN
//
// MessageText:
//
//  (CM) Error - [%1/%2] Session recovery failed for %3 - RECOVERYFAILED/SHOULDNOTHAPPEN.  ICM was unable to recover the session due to an unexpected, unknown failure condition.  This error is rare, but can occasionally occur if ICM crashes at certain stages of the session creation process.  In some cases, the setup information known to the ICM (when it re-starts) will be inconsistent with the information that has been successfully written to the ICM's SafeStore ICM Status Message List before the loss of service.  If ICM detects any discrepancy between these two data sets, it discards the session and logs this error message.
//
#define CMEVT_STRERR_RECOVERYFAILED_SHOULDNOTHAPPEN 0xC0010194L

//
// MessageId: CMEVT_STRERR_UNRECOVERABLE_EXOK
//
// MessageText:
//
//  (CM) Error - [%1/%2] Session recovery failed for %3 - UNRECOVERABLE/EXOK.  Session recovery failed.  Following an interruption of service, ICM was able to recover the session's stream and corresponding connection information, but the SRM no longer had any knowledge of that session.
//
#define CMEVT_STRERR_UNRECOVERABLE_EXOK  0xC0010195L

//
// MessageId: CMEVT_STRERR_UNRECOVERABLE_SYSTEMERROR
//
// MessageText:
//
//  (CM) Error - [%1/%2] Session recovery failed for %3 - UNRECOVERABLE/SYSTEMERROR.  Session recovery failed.  Following an interruption of service, ICM attempted to recover the session but failed due to an unexpected system error.
//
#define CMEVT_STRERR_UNRECOVERABLE_SYSTEMERROR 0xC0010196L

//*******************************************************************************
//*
//*     Directory Service Messages 
//*
//*******************************************************************************
//
// MessageId: DSEVT_SYSERR
//
// MessageText:
//
//  (DS) Error - %1
//
#define DSEVT_SYSERR                     0xC0020001L

//
// MessageId: DSEVT_WARNING
//
// MessageText:
//
//  (DS) Warning - %1
//
#define DSEVT_WARNING                    0x80020002L

//
// MessageId: DSEVT_MAN_INIT
//
// MessageText:
//
//  (DS) Error - ManOpenSession failed: %1, extended status: %2
//
#define DSEVT_MAN_INIT                   0xC0020003L

//
// MessageId: DSEVT_CFG_INIT
//
// MessageText:
//
//  (DS) Error %1 initializing configuration package
//
#define DSEVT_CFG_INIT                   0xC0020004L

//
// MessageId: DSEVT_LOG_INIT
//
// MessageText:
//
//  (DS) Error %1 initializing circular logging package
//
#define DSEVT_LOG_INIT                   0xC0020005L

//
// MessageId: DSEVT_OUTOFMEMORY
//
// MessageText:
//
//  (DS) Out of memory: Error %1, File %2, Line: %3
//
#define DSEVT_OUTOFMEMORY                0xC0020006L

//
// MessageId: DSEVT_TCP
//
// MessageText:
//
//  (DS) Error - TCPstate subsystem error, routine %1 status %2
//
#define DSEVT_TCP                        0xC0020007L

//
// MessageId: DSEVT_START
//
// MessageText:
//
//  (DS) Initializing...
//
#define DSEVT_START                      0x40020008L

//
// MessageId: DSEVT_STOP
//
// MessageText:
//
//  (DS) Terminating...
//
#define DSEVT_STOP                       0x40020009L

//
// MessageId: DSEVT_SYSERR1
//
// MessageText:
//
//  (DS) Error - %1 Error: %2
//
#define DSEVT_SYSERR1                    0xC002000AL

//
// MessageId: DSEVT_SYSERR2
//
// MessageText:
//
//  (DS) Error - %1 Error: %2, extended Error: %3
//
#define DSEVT_SYSERR2                    0xC002000BL

//
// MessageId: DSEVT_SYSERR3
//
// MessageText:
//
//  (DS) Error - %1 File: %2, Line: %3
//
#define DSEVT_SYSERR3                    0xC002000CL

//
// MessageId: DSEVT_SQLERR
//
// MessageText:
//
//  (DS) Error - %1 SQL State: %2, Msg: %3, Native error: %4
//
#define DSEVT_SQLERR                     0xC002000DL

//
// MessageId: DSEVT_SQL_SERVICE
//
// MessageText:
//
//  (DS) Error - Service %1 has restarted %2 times within %3 minutes 
//
#define DSEVT_SQL_SERVICE                0xC002000EL

//*******************************************************************************
//*
//*     Application Database Messages 
//*
//*******************************************************************************
//
// MessageId: ADEVT_SYSERR
//
// MessageText:
//
//  (AD) Error - %1
//
#define ADEVT_SYSERR                     0xC00B0001L

//
// MessageId: ADEVT_WARNING
//
// MessageText:
//
//  (AD) Warning - %1
//
#define ADEVT_WARNING                    0x800B0002L

//
// MessageId: ADEVT_MAN_INIT
//
// MessageText:
//
//  (AD) Error - ManOpenSession failed: %1, extended status: %2
//
#define ADEVT_MAN_INIT                   0xC00B0003L

//
// MessageId: ADEVT_CFG_INIT
//
// MessageText:
//
//  (AD) Error %1 initializing configuration package
//
#define ADEVT_CFG_INIT                   0xC00B0004L

//
// MessageId: ADEVT_LOG_INIT
//
// MessageText:
//
//  (AD) Error %1 initializing circular logging package
//
#define ADEVT_LOG_INIT                   0xC00B0005L

//
// MessageId: ADEVT_OUTOFMEMORY
//
// MessageText:
//
//  (AD) Out of memory: Error %1, File %2, Line: %3
//
#define ADEVT_OUTOFMEMORY                0xC00B0006L

//
// MessageId: ADEVT_TCP
//
// MessageText:
//
//  (AD) Error - TCPstate subsystem error, routine %1 status %2
//
#define ADEVT_TCP                        0xC00B0007L

//
// MessageId: ADEVT_START
//
// MessageText:
//
//  (AD) Initializing...
//
#define ADEVT_START                      0x400B0008L

//
// MessageId: ADEVT_STOP
//
// MessageText:
//
//  (AD) Terminating...
//
#define ADEVT_STOP                       0x400B0009L

//
// MessageId: ADEVT_SYSERR1
//
// MessageText:
//
//  (AD) Error - %1 Error: %2
//
#define ADEVT_SYSERR1                    0xC00B000AL

//
// MessageId: ADEVT_SYSERR2
//
// MessageText:
//
//  (AD) Error - %1 Error: %2, extended Error: %3
//
#define ADEVT_SYSERR2                    0xC00B000BL

//
// MessageId: ADEVT_SYSERR3
//
// MessageText:
//
//  (AD) Error - %1 File: %2, Line: %3
//
#define ADEVT_SYSERR3                    0xC00B000CL

//
// MessageId: ADEVT_SQLERR
//
// MessageText:
//
//  (AD) Error - %1 SQL State: %2, Msg: %3, Native error: %4
//
#define ADEVT_SQLERR                     0xC00B000DL

//
// MessageId: ADEVT_SQL_SERVICE
//
// MessageText:
//
//  (AD) Error - Service %1 has restarted %2 times within %3 minutes 
//
#define ADEVT_SQL_SERVICE                0xC00B000EL

//*******************************************************************************
//*
//*     Propagation Service Messages 
//*
//*******************************************************************************
//
// MessageId: PSEVT_SYSERR
//
// MessageText:
//
//  (PS) System Error - %1
//
#define PSEVT_SYSERR                     0xC0040001L

//
// MessageId: PSEVT_WARNING
//
// MessageText:
//
//  (PS) Warning - %1
//
#define PSEVT_WARNING                    0x80040002L

//
// MessageId: PSEVT_MAN_INIT
//
// MessageText:
//
//  (PS) Error %1 initializing management package, extended status %2
//
#define PSEVT_MAN_INIT                   0xC0040003L

//
// MessageId: PSEVT_CFG_INIT
//
// MessageText:
//
//  (PS) Error %1 initializing config package
//
#define PSEVT_CFG_INIT                   0xC0040004L

//
// MessageId: PSEVT_CLOGINIT
//
// MessageText:
//
//  (PS) Error %1 initializing circular logging package
//
#define PSEVT_CLOGINIT                   0xC0040005L

//
// MessageId: PSEVT_MALLOC
//
// MessageText:
//
//  (PS) Malloc error - %1
//
#define PSEVT_MALLOC                     0xC0040006L

//
// MessageId: PSEVT_MSME
//
// MessageText:
//
//  (PS) State Machine Engine error, routine %1 status %2
//
#define PSEVT_MSME                       0xC0040007L

//
// MessageId: PSEVT_MCA
//
// MessageText:
//
//  (PS) Media Cluster Agent error, routine %1, status %2, extended status %3.
//  %4
//
#define PSEVT_MCA                        0xC0040008L

//
// MessageId: PSEVT_TCP
//
// MessageText:
//
//  (PS) TCPstate subsystem error, routine %1 status %2
//
#define PSEVT_TCP                        0xC0040009L

//
// MessageId: PSEVT_CONN_WARNING
//
// MessageText:
//
//  (PS) DLL Connection Warning - %1
//
#define PSEVT_CONN_WARNING               0x8004000AL

//
// MessageId: PSEVT_ASSERT
//
// MessageText:
//
//  (PS) Application error - %1
//
#define PSEVT_ASSERT                     0xC004000BL

//
// MessageId: PSEVT_IDS
//
// MessageText:
//
//  (PS) Directory Service error %1, routine %2, status %3, ext status %4
//
#define PSEVT_IDS                        0xC004000CL

//
// MessageId: PSEVT_SBS
//
// MessageText:
//
//  (PS) System Broadcast Service (SBS) error %1 from %2.
//
#define PSEVT_SBS                        0xC004000DL

//
// MessageId: PSEVT_WQE
//
// MessageText:
//
//  (PS) Work Queue Entry failed - %1
//
#define PSEVT_WQE                        0x8004000EL

//
// MessageId: PSEVT_BIND_FAIL
//
// MessageText:
//
//  (PS) Failed to bind to Directory, status %1, extended status %2, will retry...
//
#define PSEVT_BIND_FAIL                  0x8004000FL

//
// MessageId: PSEVT_BIND_SUCCESS
//
// MessageText:
//
//  (PS) Directory bind success
//
#define PSEVT_BIND_SUCCESS               0x40040010L

//
// MessageId: PSEVT_NO_CLUSTERS
//
// MessageText:
//
//  (PS) No ClusterList value configured in registry
//
#define PSEVT_NO_CLUSTERS                0xC0040011L

//
// MessageId: PSEVT_UP
//
// MessageText:
//
//  (PS) Service initialized successfully
//
#define PSEVT_UP                         0x40040012L

//
// MessageId: PSEVT_DOWN
//
// MessageText:
//
//  (PS) Service exited
//
#define PSEVT_DOWN                       0xC0040013L

//
// MessageId: PSEVT_IDS_WARNING
//
// MessageText:
//
//  (PS) Directory Service warning %1, routine %2, status %3, ext status %4
//
#define PSEVT_IDS_WARNING                0x80040014L

//
// MessageId: PSEVT_CLUSTER_DOWN
//
// MessageText:
//
//  (PS) Connection to cluster ID %1 lost
//
#define PSEVT_CLUSTER_DOWN               0x80040015L

//
// MessageId: PSEVT_CLUSTER_UP
//
// MessageText:
//
//  (PS) Connection to cluster ID %1 restored
//
#define PSEVT_CLUSTER_UP                 0x40040016L

//
// MessageId: PSEVT_ORPHAN_UPLOAD_DELETED
//
// MessageText:
//
//  (PS) MCA_FILEEVENT_DELETED for orphan upload of element %1
//
#define PSEVT_ORPHAN_UPLOAD_DELETED      0x80040017L

//
// MessageId: PSEVT_ORPHAN_COPY_DELETED
//
// MessageText:
//
//  (PS) MCA_FILEEVENT_DELETED for orphan replication of element %1 to cluster %2
//
#define PSEVT_ORPHAN_COPY_DELETED        0x80040018L

//
// MessageId: PSEVT_UNKNOWN_INCOPY
//
// MessageText:
//
//  (PS) Ignoring detected in-copy operation for unknown element %1
//
#define PSEVT_UNKNOWN_INCOPY             0x80040019L

//
// MessageId: PSEVT_DELETED_REPS_STILL_EXIST
//
// MessageText:
//
//  (PS) Deleting element %1, but replicas still exist
//
#define PSEVT_DELETED_REPS_STILL_EXIST   0x8004001AL

//
// MessageId: PSEVT_DELETED_OWNERS_STILL_EXIST
//
// MessageText:
//
//  (PS) Deleting element %1, but owning assets still exist
//
#define PSEVT_DELETED_OWNERS_STILL_EXIST 0x8004001BL

//
// MessageId: PSEVT_SOURCE_REP_NOT_FOUND
//
// MessageText:
//
//  (PS) Failed to locate source replica for copy of element %1 from cluster %2
//
#define PSEVT_SOURCE_REP_NOT_FOUND       0x8004001CL

//
// MessageId: PSEVT_UNKNOWN_APP_UPDATED
//
// MessageText:
//
//  (PS) Received directory update to unkown application ID %1, adding it
//
#define PSEVT_UNKNOWN_APP_UPDATED        0x8004001DL

//
// MessageId: PSEVT_UNKNOWN_APP_DELETED
//
// MessageText:
//
//  (PS) Ignoring directory delete of unknown application ID %1
//
#define PSEVT_UNKNOWN_APP_DELETED        0x8004001EL

//
// MessageId: PSEVT_ASSET_DL_NO_REQUEST
//
// MessageText:
//
//  (PS) Asset Download message built, but no DLLs with pending download request
//
#define PSEVT_ASSET_DL_NO_REQUEST        0x8004001FL

//
// MessageId: PSEVT_MD_READ_FAILED
//
// MessageText:
//
//  (PS) Metadata read for asset %1 failed, status %2, ext status %3.
//  Removing asset record from PS server.
//
#define PSEVT_MD_READ_FAILED             0x80040020L

//
// MessageId: PSEVT_CA_READ_FAILED
//
// MessageText:
//
//  (PS) Complex asset read for asset %1 failed, status %2, ext status %3.
//  Removing asset record from PS server.
//
#define PSEVT_CA_READ_FAILED             0x80040021L

//
// MessageId: PSEVT_ST_READ_FAILED
//
// MessageText:
//
//  (PS) State read for asset %1 failed, status %2, ext status %3.
//  Continuing with previous state information.
//
#define PSEVT_ST_READ_FAILED             0x80040022L

//
// MessageId: PSEVT_BAD_CLUSTER_EVENT
//
// MessageText:
//
//  Ignoring unexpected cluster event code %1
//
#define PSEVT_BAD_CLUSTER_EVENT          0x80040023L

//
// MessageId: PSEVT_DOWNLOAD_ALREADY_REQUESTED
//
// MessageText:
//
//  Asset download already requested from DLL instance %1
//
#define PSEVT_DOWNLOAD_ALREADY_REQUESTED 0x80040024L

//
// MessageId: PSEVT_COPY_COUNT
//
// MessageText:
//
//  Copy count corrupt for cluster %1, resetting copies %2 from %3 to %4
//
#define PSEVT_COPY_COUNT                 0x80040025L

//
// MessageId: PSEVT_UPLOAD_NOSPACE
//
// MessageText:
//
//  Not enough space on cluster %1 to upload element %2
//
#define PSEVT_UPLOAD_NOSPACE             0x80040026L

//
// MessageId: PSEVT_DELETED_NOSPACE
//
// MessageText:
//
//  Files deleted, but not enough space created to upload element %1 to cluster %2
//
#define PSEVT_DELETED_NOSPACE            0x80040027L

//
// MessageId: PSEVT_SPACE_ALL_BUT_NOT_SOME
//
// MessageText:
//
//  No space for subset of elements of asset %1, but had space for all elements
//
#define PSEVT_SPACE_ALL_BUT_NOT_SOME     0x80040028L

//
// MessageId: PSEVT_DELETED_NOSPACE_REPLICATE
//
// MessageText:
//
//  Files deleted, but not enough space created to replicate asset %1 to cluster %2
//
#define PSEVT_DELETED_NOSPACE_REPLICATE  0x80040029L

//
// MessageId: PSEVT_NO_BASE_ASSET
//
// MessageText:
//
//  Replicating asset %1, but no base asset descriptor found
//
#define PSEVT_NO_BASE_ASSET              0x8004002AL

//
// MessageId: PSEVT_IDSERROR_APP_PRIORITY
//
// MessageText:
//
//  IDS error %1 reading priority attribute for application %2.
//  Using default priority of 50.
//
#define PSEVT_IDSERROR_APP_PRIORITY      0x8004002BL

//
// MessageId: PSEVT_MDERROR_APP_PRIORITY
//
// MessageText:
//
//  Metadata status %1 reading priority attribute for application %2.
//  Using default priority value of 50.
//
#define PSEVT_MDERROR_APP_PRIORITY       0x8004002CL

//
// MessageId: PSEVT_UNKNOWN_CBQ
//
// MessageText:
//
//  Ignoring unknown callback queue entry event %1 in %2
//
#define PSEVT_UNKNOWN_CBQ                0x8004002DL

//
// MessageId: PSEVT_IGNORE_WQE
//
// MessageText:
//
//  This PS is configured to ignore work queue entries
//
#define PSEVT_IGNORE_WQE                 0x8004002EL

//
// MessageId: PSEVT_UNKNOWN_ASSET_USED
//
// MessageText:
//
//  Ignoring use update for unknown asset %1
//
#define PSEVT_UNKNOWN_ASSET_USED         0x8004002FL

//
// MessageId: PSEVT_NO_CUREREP
//
// MessageText:
//
//  CUREREP current element replica structure not found for incopied element %1, cluster %2
//
#define PSEVT_NO_CUREREP                 0x80040030L

//
// MessageId: PSEVT_REMOVE_REFERENCING_ELIST
//
// MessageText:
//
//  SetHandled is removing an ELIST which still references replicas
//
#define PSEVT_REMOVE_REFERENCING_ELIST   0x80040031L

//
// MessageId: PSEVT_NO_ZEROED_SETS
//
// MessageText:
//
//  SetHandled completed, but no zero valued sets
//
#define PSEVT_NO_ZEROED_SETS             0x80040032L

//
// MessageId: PSEVT_UNKNOWN_INTERRUPT
//
// MessageText:
//
//  Ignoring %1 for unknown %2 %3
//
#define PSEVT_UNKNOWN_INTERRUPT          0x80040033L

//
// MessageId: PSEVT_INVALID_FILE_NAME
//
// MessageText:
//
//  Ignoring invalid MCA file name %1 from %2
//
#define PSEVT_INVALID_FILE_NAME          0x80040034L

//
// MessageId: PSEVT_NO_ATTRIBUTE
//
// MessageText:
//
//  %1 attribute not defined in directory for asset %2, using default value.
//
#define PSEVT_NO_ATTRIBUTE               0x80040035L

//
// MessageId: PSEVT_MDERROR_ASSET_USE_INFO
//
// MessageText:
//
//  Unexpected metadata status %1 reading asset use info for asset %2
//
#define PSEVT_MDERROR_ASSET_USE_INFO     0x80040036L

//
// MessageId: PSEVT_NEW_CLUSTER_ALREADY_EXISTS
//
// MessageText:
//
//  Ignoring new cluster %1, because DNP table entry for that cluster to nodegroup %2 already exists.
//
#define PSEVT_NEW_CLUSTER_ALREADY_EXISTS 0x80040037L

//
// MessageId: PSEVT_FILE_DELETED
//
// MessageText:
//
//  File %1, cluster %2, deleted
//
#define PSEVT_FILE_DELETED               0x40040038L

//
// MessageId: PSEVT_COPY_START
//
// MessageText:
//
//  File %1, copy starting from cluster %2 to cluster %3
//
#define PSEVT_COPY_START                 0x40040039L

//
// MessageId: PSEVT_COPY_SUCCESS
//
// MessageText:
//
//  File %1, copy from cluster %2 to %3 succeeded
//
#define PSEVT_COPY_SUCCESS               0x4004003AL

//
// MessageId: PSEVT_COPY_FAILED
//
// MessageText:
//
//  File %1, copy from cluster %2 to %3 failed.
//
#define PSEVT_COPY_FAILED                0x4004003BL

//
// MessageId: PSEVT_STATISTICS
//
// MessageText:
//
//  (PS) Statistics error - %1
//
#define PSEVT_STATISTICS                 0xC004003CL

//
// MessageId: PSEVT_NOSHARENAME
//
// MessageText:
//
//  (PS) Share name %1 could not be found
//
#define PSEVT_NOSHARENAME                0xC004003DL

//
// MessageId: PSEVT_NOHOSTNAME
//
// MessageText:
//
//  (PS) No host name translation found for %1 or %2
//
#define PSEVT_NOHOSTNAME                 0xC004003EL

//
// MessageId: PSEVT_BADXMLPATHNAME
//
// MessageText:
//
//  (PS) XMLPathname %1 improperly formatted
//
#define PSEVT_BADXMLPATHNAME             0xC004003FL

//
// MessageId: PSEVT_HOSTNAMEFAILED
//
// MessageText:
//
//  (PS) Last chance Host Name lookup failed - Error = %1
//
#define PSEVT_HOSTNAMEFAILED             0xC0040040L

//
// MessageId: PSEVT_XMLPATHDEFAULT
//
// MessageText:
//
//  (PS) Using Host Name - %1 - default ip address for XMLPathname
//
#define PSEVT_XMLPATHDEFAULT             0x80040041L

//
// MessageId: PSEVT_XMLOPENFORWRITE
//
// MessageText:
//
//  (PS) Cannot open XML Pathname - %1 - for writing - Error = %2
//
#define PSEVT_XMLOPENFORWRITE            0x80040042L

//*******************************************************************************
//*
//*     Streaming Service Messages 
//*
//*******************************************************************************
//
// MessageId: SSEVT_SYSERR
//
// MessageText:
//
//  (SS) System Error - %1
//
#define SSEVT_SYSERR                     0xC0050001L

//
// MessageId: SSEVT_WARNING
//
// MessageText:
//
//  (SS) Warning - %1
//
#define SSEVT_WARNING                    0x80050002L

//
// MessageId: SSEVT_MAN_INIT
//
// MessageText:
//
//  (SS) Error %1 initializing management package, extended status %2
//
#define SSEVT_MAN_INIT                   0xC0050003L

//
// MessageId: SSEVT_CFG_INIT
//
// MessageText:
//
//  (SS) Error %1 initializing config package
//
#define SSEVT_CFG_INIT                   0xC0050004L

//
// MessageId: SSEVT_CLOGINIT
//
// MessageText:
//
//  (SS) Error %1 initializing circular logging package
//
#define SSEVT_CLOGINIT                   0xC0050005L

//
// MessageId: SSEVT_MALLOC
//
// MessageText:
//
//  (SS) Malloc error - %1
//
#define SSEVT_MALLOC                     0xC0050006L

//
// MessageId: SSEVT_MSME
//
// MessageText:
//
//  (SS) State Machine Engine error, routine %1 status %2
//
#define SSEVT_MSME                       0xC0050007L

//
// MessageId: SSEVT_MCA
//
// MessageText:
//
//  (SS) Media Cluster Agent error, routine %1, status %2, extended status %3, stream handle %4
//
#define SSEVT_MCA                        0xC0050008L

//
// MessageId: SSEVT_INFORMATION
//
// MessageText:
//
//  (SS) %1
//
#define SSEVT_INFORMATION                0x40050009L

//
// MessageId: SSEVT_SSI_INITIALIZATION
//
// MessageText:
//
//  (SS) SafeStore Interface error, routine %1 status %2
//
#define SSEVT_SSI_INITIALIZATION         0x4005000AL

//
// MessageId: SSEVT_MANPKG_INITIALIZATION
//
// MessageText:
//
//  (SS) ManPkg initializaiton error, routine %1 status %2
//
#define SSEVT_MANPKG_INITIALIZATION      0x4005000BL

//*******************************************************************************
//*
//*     Asset Manager Messages 
//*
//*******************************************************************************
//
// MessageId: AMEVT_STARTING
//
// MessageText:
//
//  (AM) Starting...
//
#define AMEVT_STARTING                   0x40030001L

//
// MessageId: AMEVT_EXITING
//
// MessageText:
//
//  (AM) Exiting...
//
#define AMEVT_EXITING                    0x40030002L

//
// MessageId: AMEVT_SYSERR
//
// MessageText:
//
//  (AM) System error %1
//
#define AMEVT_SYSERR                     0xC0030003L

//
// MessageId: AMEVT_STARTFAILED
//
// MessageText:
//
//  (AM) Failed to start Asset Manager server
//
#define AMEVT_STARTFAILED                0xC0030004L

//
// MessageId: AMEVT_APIERR
//
// MessageText:
//
//  (AM) API %1 failed, error %2
//
#define AMEVT_APIERR                     0xC0030005L

//
// MessageId: AMEVT_OUTOFMEMOERY
//
// MessageText:
//
//  (AM) Out of memory
//
#define AMEVT_OUTOFMEMOERY               0xC0030006L

//
// MessageId: AMEVT_DBERR
//
// MessageText:
//
//  (AM) Log database error. %1
//
#define AMEVT_DBERR                      0xC0030007L

//
// MessageId: AMEVT_SM_HANG
//
// MessageText:
//
//  (AM) Have not heard from the State Machine for %1 minutes. Assume it is hung. Restart...
//
#define AMEVT_SM_HANG                    0xC0030008L

//
// MessageId: AMEVT_IMPORTWATCH_ERROR
//
// MessageText:
//
//  (AM) Failed to watch import path %1, error %2
//
#define AMEVT_IMPORTWATCH_ERROR          0xC0030009L

//
// MessageId: AMEVT_DISKQUOTA_ERROR
//
// MessageText:
//
//  (AM) Failed to update state of asset element %1 to upload, content provider exceeds its disk quota
//
#define AMEVT_DISKQUOTA_ERROR            0xC003000AL

//
// MessageId: AMEVT_MOTPREENCRYPTION_ERROR
//
// MessageText:
//
//  (AM) Failed to update state of asset element %1 to active. Failed to get Motorola pre-encryption ECM data from ERS.
//
#define AMEVT_MOTPREENCRYPTION_ERROR     0xC003000BL

//
// MessageId: AMEVT_PLAYTIME_ERROR
//
// MessageText:
//
//  (AM) PlayTime that is got from PS is 0 for Ae %1.
//
#define AMEVT_PLAYTIME_ERROR             0xC003000CL

//
// MessageId: AMEVT_PARSE_UPLOAD_DATA_ERROR
//
// MessageText:
//
//  (AM) Failed to parse upload response data %1 for %2, error %3
//
#define AMEVT_PARSE_UPLOAD_DATA_ERROR    0xC003000DL

//
// MessageId: AMEVT_MISSING_METADATA
//
// MessageText:
//
//  (AM) Missing metadata %1 for %2
//
#define AMEVT_MISSING_METADATA           0xC003000EL

//
// MessageId: AMEVT_MOTPREENCRYPTION_UPDATEECM_ERROR
//
// MessageText:
//
//  (AM) Failed to update Motorola pre-encryption ECM data for asset element %1
//
#define AMEVT_MOTPREENCRYPTION_UPDATEECM_ERROR 0xC003000FL

//*******************************************************************************
//*
//*     SCTP Service Messages 
//*
//*******************************************************************************
//
// MessageId: SCTPEVT_STARTED
//
// MessageText:
//
//  (SCTP) SeaChange Transfer Protocol Service started
//
#define SCTPEVT_STARTED                  0x40060001L

//
// MessageId: SCTPEVT_MANPKG
//
// MessageText:
//
//  (SCTP) Unable to initialize ManPkg %1 %2
//
#define SCTPEVT_MANPKG                   0xC0060002L

//
// MessageId: SCTPEVT_MANVAR
//
// MessageText:
//
//  (SCTP) Unable to manage variable %1 %2
//
#define SCTPEVT_MANVAR                   0xC0060003L

//
// MessageId: SCTPEVT_INIT
//
// MessageText:
//
//  (SCTP) Unable to initialize %1
//
#define SCTPEVT_INIT                     0xC0060004L

//
// MessageId: SCTPEVT_STOPPED
//
// MessageText:
//
//  (SCTP) SeaChange Transfer Protocol Service stopped
//
#define SCTPEVT_STOPPED                  0x40060005L

//
// MessageId: SCTPEVT_MANPKGCLOSE
//
// MessageText:
//
//  (SCTP) Unable to close ManPkg session %1 %2
//
#define SCTPEVT_MANPKGCLOSE              0xC0060006L

//
// MessageId: SCTPEVT_LOADDLL
//
// MessageText:
//
//  (SCTP) Unable to load DLL %1 %2
//
#define SCTPEVT_LOADDLL                  0xC0060007L

//
// MessageId: SCTPEVT_STARTTCP
//
// MessageText:
//
//  (SCTP) Unable to start TCP listener %1
//
#define SCTPEVT_STARTTCP                 0xC0060008L

//
// MessageId: SCTPEVT_UNLOADDLL
//
// MessageText:
//
//  (SCTP) Unable to unload DLL %1
//
#define SCTPEVT_UNLOADDLL                0xC0060009L

//
// MessageId: SCTPEVT_ERROR
//
// MessageText:
//
//  (SCTP) Error on %1 %2
//
#define SCTPEVT_ERROR                    0xC006000AL

//
// MessageId: SCTPEVT_CAUGHTINIT
//
// MessageText:
//
//  (SCTP) Caught exception calling initialize for %1
//
#define SCTPEVT_CAUGHTINIT               0xC006000BL

//
// MessageId: SCTPEVT_CAUGHTUNINIT
//
// MessageText:
//
//  (SCTP) Caught exception calling uninitialize for %1
//
#define SCTPEVT_CAUGHTUNINIT             0xC006000CL

//
// MessageId: SCTPEVT_NOMEMORY
//
// MessageText:
//
//  (SCTP) Out of memory
//
#define SCTPEVT_NOMEMORY                 0xC006000DL

//
// MessageId: SCTPEVT_ERRORFILE
//
// MessageText:
//
//  (SCTP) Error on %1 %2 %3
//
#define SCTPEVT_ERRORFILE                0xC006000EL

//
// MessageId: SCTPEVT_FINDDLL
//
// MessageText:
//
//  (SCTP) Unable to find %1 %2 %3
//
#define SCTPEVT_FINDDLL                  0xC006000FL

//
// MessageId: SCTPEVT_DLLOVERFLOW
//
// MessageText:
//
//  (SCTP) Counters overflowed for DLL %1 %2 %3 %4.  Reseting counters.
//
#define SCTPEVT_DLLOVERFLOW              0x40060010L

//
// MessageId: SCTPEVT_SVCOVERFLOW
//
// MessageText:
//
//  (SCTP) Counters overflowed for Service %1 %2.  Reseting counters.
//
#define SCTPEVT_SVCOVERFLOW              0x40060011L

//
// MessageId: SCTPEVT_DCMDISABLED
//
// MessageText:
//
//  (SCTP) Unable to initialize Data Carousel.  Functionality disabled.
//
#define SCTPEVT_DCMDISABLED              0x80060012L

//
// MessageId: SCTPEVT_MAXCONNS
//
// MessageText:
//
//  (SCTP) Maximum connections (%1) exceeded for client %2. Releasing oldest connection for this client.
//
#define SCTPEVT_MAXCONNS                 0x80060013L

//
// MessageId: SCTPEVT_DEFAULTDLL
//
// MessageText:
//
//  (SCTP) Language for client %1 reset to default english.
//
#define SCTPEVT_DEFAULTDLL               0x80060014L

//
// MessageId: SCTPEVT_MAXCONNS_DROP_NEWEST
//
// MessageText:
//
//  (SCTP) Maximum connections (%1) exceeded for client %2. Dropping newest connection for this client.
//
#define SCTPEVT_MAXCONNS_DROP_NEWEST     0x80060015L

//
// MessageId: SCTPEVT_INVOKEDLLERR
//
// MessageText:
//
//  (SCTP) SCTP Invoke (%1) DLL failed.  ClientID = %2.  Request = %3.
//
#define SCTPEVT_INVOKEDLLERR             0x80060016L

//*******************************************************************************
//*
//*     Directory Service API Messages 
//*
//*******************************************************************************
//
// MessageId: IDSAPIEVT_SYSERR
//
// MessageText:
//
//  (IDSAPI) Error - %1
//
#define IDSAPIEVT_SYSERR                 0xC0070001L

//
// MessageId: IDSAPIEVT_WARNING
//
// MessageText:
//
//  (IDSAPI) Warning - %1
//
#define IDSAPIEVT_WARNING                0x80070002L

//
// MessageId: IDSAPIEVT_CFG_INIT
//
// MessageText:
//
//  (IDSAPI) Error %1 initializing configuration package
//
#define IDSAPIEVT_CFG_INIT               0xC0070003L

//
// MessageId: IDSAPIEVT_LOG_INIT
//
// MessageText:
//
//  (IDSAPI) Error %1 initializing circular logging package
//
#define IDSAPIEVT_LOG_INIT               0xC0070004L

//
// MessageId: IDSAPIEVT_OUTOFMEMORY
//
// MessageText:
//
//  (IDSAPI) Out of memory: Error %1, File %2, Line: %3
//
#define IDSAPIEVT_OUTOFMEMORY            0xC0070005L

//
// MessageId: IDSAPIEVT_TCP
//
// MessageText:
//
//  (IDSAPI) Error - TCPstate subsystem error, routine %1 status %2
//
#define IDSAPIEVT_TCP                    0xC0070006L

//
// MessageId: IDSAPIEVT_SYSERR1
//
// MessageText:
//
//  (IDSAPI) Error - %1 Error: %2
//
#define IDSAPIEVT_SYSERR1                0xC0070007L

//
// MessageId: IDSAPIEVT_SYSERR2
//
// MessageText:
//
//  (IDSAPI) Error - %1 Error: %2, extended Error: %3
//
#define IDSAPIEVT_SYSERR2                0xC0070008L

//
// MessageId: IDSAPIEVT_SYSERR3
//
// MessageText:
//
//  (IDSAPI) Error - %1 File: %2, Line: %3
//
#define IDSAPIEVT_SYSERR3                0xC0070009L

//*******************************************************************************
//*
//*     Application Database API Messages 
//*
//*******************************************************************************
//
// MessageId: IADAPIEVT_SYSERR
//
// MessageText:
//
//  (IADAPI) Error - %1
//
#define IADAPIEVT_SYSERR                 0xC00A0001L

//
// MessageId: IADAPIEVT_WARNING
//
// MessageText:
//
//  (IADAPI) Warning - %1
//
#define IADAPIEVT_WARNING                0x800A0002L

//
// MessageId: IADAPIEVT_CFG_INIT
//
// MessageText:
//
//  (IADAPI) Error %1 initializing configuration package
//
#define IADAPIEVT_CFG_INIT               0xC00A0003L

//
// MessageId: IADAPIEVT_LOG_INIT
//
// MessageText:
//
//  (IADAPI) Error %1 initializing circular logging package
//
#define IADAPIEVT_LOG_INIT               0xC00A0004L

//
// MessageId: IADAPIEVT_OUTOFMEMORY
//
// MessageText:
//
//  (IADAPI) Out of memory: Error %1, File %2, Line: %3
//
#define IADAPIEVT_OUTOFMEMORY            0xC00A0005L

//
// MessageId: IADAPIEVT_TCP
//
// MessageText:
//
//  (IADAPI) Error - TCPstate subsystem error, routine %1 status %2
//
#define IADAPIEVT_TCP                    0xC00A0006L

//
// MessageId: IADAPIEVT_SYSERR1
//
// MessageText:
//
//  (IADAPI) Error - %1 Error: %2
//
#define IADAPIEVT_SYSERR1                0xC00A0007L

//
// MessageId: IADAPIEVT_SYSERR2
//
// MessageText:
//
//  (IADAPI) Error - %1 Error: %2, extended Error: %3
//
#define IADAPIEVT_SYSERR2                0xC00A0008L

//
// MessageId: IADAPIEVT_SYSERR3
//
// MessageText:
//
//  (IADAPI) Error - %1 File: %2, Line: %3
//
#define IADAPIEVT_SYSERR3                0xC00A0009L

//*******************************************************************************
//*
//*     Streaming Service API Messages 
//*
//*******************************************************************************
//		The first three errors are general catchall errors.  They should be
//		obsolete.
//
// MessageId: ISSAPIEVT_GENERAL_ERROR
//
// MessageText:
//
//  (ISSAPI) Error - %1
//
#define ISSAPIEVT_GENERAL_ERROR          0xC0080001L

//
// MessageId: ISSAPIEVT_GENERAL_WARNING
//
// MessageText:
//
//  (ISSAPI) Warning - %1
//
#define ISSAPIEVT_GENERAL_WARNING        0x80080002L

//
// MessageId: ISSAPIEVT_GENERAL_INFORMATION
//
// MessageText:
//
//  (ISSAPI) Information - %1
//
#define ISSAPIEVT_GENERAL_INFORMATION    0x40080003L

//		from here on are the real errors.  These can be mapped on to 
//		alarms.
//
// MessageId: ISSAPIEVT_INVALID_MEMORY
//
// MessageText:
//
//  (ISSAPI) %1
//
#define ISSAPIEVT_INVALID_MEMORY         0xC0080004L

//
// MessageId: ISSAPIEVT_API_CALLBACK_EXCEPTION
//
// MessageText:
//
//  (ISSAPI) %1
//
#define ISSAPIEVT_API_CALLBACK_EXCEPTION 0xC0080005L

//
// MessageId: ISSAPIEVT_API_CALLBACK_RETURNED_FALSE
//
// MessageText:
//
//  (ISSAPI) %1
//
#define ISSAPIEVT_API_CALLBACK_RETURNED_FALSE 0x80080006L

//
// MessageId: ISSAPIEVT_PROGRAMMING_ERROR
//
// MessageText:
//
//  (ISSAPI) %1
//
#define ISSAPIEVT_PROGRAMMING_ERROR      0xC0080007L

//
// MessageId: ISSAPIEVT_CALLBACK_THREADSTART_ERROR
//
// MessageText:
//
//  (ISSAPI) %1
//
#define ISSAPIEVT_CALLBACK_THREADSTART_ERROR 0xC0080008L

//
// MessageId: ISSAPIEVT_CALLBACK_TYPEINST_UNKNOWN
//
// MessageText:
//
//  (ISSAPI) %1
//
#define ISSAPIEVT_CALLBACK_TYPEINST_UNKNOWN 0x80080009L

//
// MessageId: ISSAPIEVT_API_CALLBACK_CM_NOT_CONNECTED
//
// MessageText:
//
//  (ISSAPI) %1
//
#define ISSAPIEVT_API_CALLBACK_CM_NOT_CONNECTED 0x8008000AL

//
// MessageId: ISSAPIEVT_API_CALLBACK_REMOTE_TYPEINST_NOT_CONNECTED
//
// MessageText:
//
//  (ISSAPI) %1
//
#define ISSAPIEVT_API_CALLBACK_REMOTE_TYPEINST_NOT_CONNECTED 0x8008000BL

//
// MessageId: ISSAPIEVT_API_CALLBACK_UNKNOWN_LINK_TYPE
//
// MessageText:
//
//  (ISSAPI) %1
//
#define ISSAPIEVT_API_CALLBACK_UNKNOWN_LINK_TYPE 0xC008000CL

//
// MessageId: ISSAPIEVT_WIN32_ERROR
//
// MessageText:
//
//  (ISSAPI) %1
//
#define ISSAPIEVT_WIN32_ERROR            0xC008000DL

//
// MessageId: ISSAPIEVT_API_TIMED_OUT
//
// MessageText:
//
//  (ISSAPI) %1
//
#define ISSAPIEVT_API_TIMED_OUT          0xC008000EL

//
// MessageId: ISSAPIEVT_API_ARGUMENT_VALIDATION_TYPEINST_UNKNOWN
//
// MessageText:
//
//  (ISSAPI) %1
//
#define ISSAPIEVT_API_ARGUMENT_VALIDATION_TYPEINST_UNKNOWN 0x8008000FL

//
// MessageId: ISSAPIEVT_API_ARGUMENT_VALIDATION_INVALID_METATYPE
//
// MessageText:
//
//  (ISSAPI) %1
//
#define ISSAPIEVT_API_ARGUMENT_VALIDATION_INVALID_METATYPE 0xC0080010L

//
// MessageId: ISSAPIEVT_API_ARGUMENT_VALIDATION_INVALID_SID
//
// MessageText:
//
//  (ISSAPI) %1
//
#define ISSAPIEVT_API_ARGUMENT_VALIDATION_INVALID_SID 0x80080011L

//
// MessageId: ISSAPIEVT_API_ARGUMENT_VALIDATION_INVALID_APPSTATUS
//
// MessageText:
//
//  (ISSAPI) %1
//
#define ISSAPIEVT_API_ARGUMENT_VALIDATION_INVALID_APPSTATUS 0xC0080012L

//
// MessageId: ISSAPIEVT_API_ARGUMENT_VALIDATION_INVALID_ITV_STATUS_BLOCK
//
// MessageText:
//
//  (ISSAPI) %1
//
#define ISSAPIEVT_API_ARGUMENT_VALIDATION_INVALID_ITV_STATUS_BLOCK 0xC0080013L

//
// MessageId: ISSAPIEVT_API_ARGUMENT_VALIDATION_INVALID_AELIST_PTR
//
// MessageText:
//
//  (ISSAPI) %1
//
#define ISSAPIEVT_API_ARGUMENT_VALIDATION_INVALID_AELIST_PTR 0xC0080014L

//
// MessageId: ISSAPIEVT_API_ARGUMENT_VALIDATION_AELIST_PTR_SHOULD_BE_NULL
//
// MessageText:
//
//  (ISSAPI) %1
//
#define ISSAPIEVT_API_ARGUMENT_VALIDATION_AELIST_PTR_SHOULD_BE_NULL 0xC0080015L

//
// MessageId: ISSAPIEVT_API_ACCEPTRDYASSET_UNSUPPORTED_FOR_TYPE
//
// MessageText:
//
//  (ISSAPI) %1
//
#define ISSAPIEVT_API_ACCEPTRDYASSET_UNSUPPORTED_FOR_TYPE 0xC0080016L

//
// MessageId: ISSAPIEVT_SET_TIMER_FAILED
//
// MessageText:
//
//  (ISSAPI) %1
//
#define ISSAPIEVT_SET_TIMER_FAILED       0x80080017L

//
// MessageId: ISSAPIEVT_SET_TIMER_NOT_FOUND
//
// MessageText:
//
//  (ISSAPI) %1
//
#define ISSAPIEVT_SET_TIMER_NOT_FOUND    0x80080018L

//
// MessageId: ISSAPIEVT_UNEXPECTED_METATYPE
//
// MessageText:
//
//  (ISSAPI) %1
//
#define ISSAPIEVT_UNEXPECTED_METATYPE    0xC0080019L

//
// MessageId: ISSAPIEVT_API_ACCEPTSTREAM_UNSUPPORTED_FOR_TYPE
//
// MessageText:
//
//  (ISSAPI) %1
//
#define ISSAPIEVT_API_ACCEPTSTREAM_UNSUPPORTED_FOR_TYPE 0xC008001AL

//
// MessageId: ISSAPIEVT_API_SHUTDOWN_FAILED_RELEASE_SUBSYSTEM
//
// MessageText:
//
//  (ISSAPI) %1
//
#define ISSAPIEVT_API_SHUTDOWN_FAILED_RELEASE_SUBSYSTEM 0x8008001BL

//
// MessageId: ISSAPIEVT_API_TYPEINST_NOT_TERMINATED
//
// MessageText:
//
//  (ISSAPI) %1
//
#define ISSAPIEVT_API_TYPEINST_NOT_TERMINATED 0x8008001CL

//
// MessageId: ISSAPIEVT_API_CONFIGURE_STREAM_UNSUPPORTED_FOR_TYPE
//
// MessageText:
//
//  (ISSAPI) %1
//
#define ISSAPIEVT_API_CONFIGURE_STREAM_UNSUPPORTED_FOR_TYPE 0xC008001DL

//
// MessageId: ISSAPIEVT_API_CREATE_STREAM_UNSUPPORTED_FOR_TYPE
//
// MessageText:
//
//  (ISSAPI) %1
//
#define ISSAPIEVT_API_CREATE_STREAM_UNSUPPORTED_FOR_TYPE 0xC008001EL

//
// MessageId: ISSAPIEVT_API_DNET_READY_UNSUPPORTED_FOR_TYPE
//
// MessageText:
//
//  (ISSAPI) %1
//
#define ISSAPIEVT_API_DNET_READY_UNSUPPORTED_FOR_TYPE 0xC008001FL

//
// MessageId: ISSAPIEVT_API_FINDAPPSERVERINSTANCE_UNSUPPORTED_FOR_TYPE
//
// MessageText:
//
//  (ISSAPI) %1
//
#define ISSAPIEVT_API_FINDAPPSERVERINSTANCE_UNSUPPORTED_FOR_TYPE 0xC0080020L

//
// MessageId: ISSAPIEVT_API_GETSERVERINFORMATION_UNSUPPORTED_FOR_TYPE
//
// MessageText:
//
//  (ISSAPI) %1
//
#define ISSAPIEVT_API_GETSERVERINFORMATION_UNSUPPORTED_FOR_TYPE 0xC0080021L

//
// MessageId: ISSAPIEVT_API_STREAMMODIFY_UNSUPPORTED_FOR_TYPE
//
// MessageText:
//
//  (ISSAPI) %1
//
#define ISSAPIEVT_API_STREAMMODIFY_UNSUPPORTED_FOR_TYPE 0xC0080022L

//
// MessageId: ISSAPIEVT_API_RECONFIGURESTREAM_UNSUPPORTED_FOR_TYPE
//
// MessageText:
//
//  (ISSAPI) %1
//
#define ISSAPIEVT_API_RECONFIGURESTREAM_UNSUPPORTED_FOR_TYPE 0xC0080023L

//
// MessageId: ISSAPIEVT_API_SETOPCTL_UNSUPPORTED_FOR_TYPE
//
// MessageText:
//
//  (ISSAPI) %1
//
#define ISSAPIEVT_API_SETOPCTL_UNSUPPORTED_FOR_TYPE 0xC0080024L

//
// MessageId: ISSAPIEVT_API_STREAMOPERATION_UNSUPPORTED_FOR_TYPE
//
// MessageText:
//
//  (ISSAPI) %1
//
#define ISSAPIEVT_API_STREAMOPERATION_UNSUPPORTED_FOR_TYPE 0xC0080025L

//
// MessageId: ISSAPIEVT_API_ARGUMENT_VALIDATION_INVALID_RESOURCE_DESCRIPTOR_POINTER
//
// MessageText:
//
//  (ISSAPI) %1
//
#define ISSAPIEVT_API_ARGUMENT_VALIDATION_INVALID_RESOURCE_DESCRIPTOR_POINTER 0xC0080026L

//
// MessageId: ISSAPIEVT_API_ARGUMENT_VALIDATION_INVALID_AELIST
//
// MessageText:
//
//  (ISSAPI) %1
//
#define ISSAPIEVT_API_ARGUMENT_VALIDATION_INVALID_AELIST 0xC0080027L

//
// MessageId: ISSAPIEVT_API_ARGUMENT_VALIDATION_INVALID_USER_PARAMETER
//
// MessageText:
//
//  (ISSAPI) %1
//
#define ISSAPIEVT_API_ARGUMENT_VALIDATION_INVALID_USER_PARAMETER 0xC0080028L

//
// MessageId: ISSAPIEVT_API_ARGUMENT_VALIDATION_NO_SERVER_AVAILABLE
//
// MessageText:
//
//  (ISSAPI) %1
//
#define ISSAPIEVT_API_ARGUMENT_VALIDATION_NO_SERVER_AVAILABLE 0xC0080029L

//
// MessageId: ISSAPIEVT_API_ISS_TERM_IN_PROGRESS
//
// MessageText:
//
//  (ISSAPI) %1
//
#define ISSAPIEVT_API_ISS_TERM_IN_PROGRESS 0xC008002AL

//
// MessageId: ISSAPIEVT_API_STREAM_TABLE_FULL
//
// MessageText:
//
//  (ISSAPI) %1
//
#define ISSAPIEVT_API_STREAM_TABLE_FULL  0xC008002BL

//
// MessageId: ISSAPIEVT_API_ARGUMENT_VALIDATION_INVALID_STREAMSTATUS_SPECIFICATION
//
// MessageText:
//
//  (ISSAPI) %1
//
#define ISSAPIEVT_API_ARGUMENT_VALIDATION_INVALID_STREAMSTATUS_SPECIFICATION 0xC008002CL

//
// MessageId: ISSAPIEVT_API_TCPCOMM_CONNECT_FAILED
//
// MessageText:
//
//  (ISSAPI) %1
//
#define ISSAPIEVT_API_TCPCOMM_CONNECT_FAILED 0xC008002DL

//
// MessageId: ISSAPIEVT_API_INITIALIZATION_FAILED
//
// MessageText:
//
//  (ISSAPI) %1
//
#define ISSAPIEVT_API_INITIALIZATION_FAILED 0xC008002EL

//
// MessageId: ISSAPIEVT_API_ARGUMENT_VALIDATION_INVALID_VERSION
//
// MessageText:
//
//  (ISSAPI) %1
//
#define ISSAPIEVT_API_ARGUMENT_VALIDATION_INVALID_VERSION 0xC008002FL

//
// MessageId: ISSAPIEVT_API_ARGUMENT_VALIDATION_INVALID_SUBSET_VALUE
//
// MessageText:
//
//  (ISSAPI) %1
//
#define ISSAPIEVT_API_ARGUMENT_VALIDATION_INVALID_SUBSET_VALUE 0xC0080030L

//
// MessageId: ISSAPIEVT_API_ARGUMENT_VALIDATION_INVALID_OPCTL_TABLE
//
// MessageText:
//
//  (ISSAPI) %1
//
#define ISSAPIEVT_API_ARGUMENT_VALIDATION_INVALID_OPCTL_TABLE 0xC0080031L

//
// MessageId: ISSAPIEVT_API_ARGUMENT_VALIDATION_INVALID_OPCTL_VALUE
//
// MessageText:
//
//  (ISSAPI) %1
//
#define ISSAPIEVT_API_ARGUMENT_VALIDATION_INVALID_OPCTL_VALUE 0xC0080032L

//
// MessageId: ISSAPIEVT_API_ARGUMENT_VALIDATION_INVALID_CALLBACK_MASK
//
// MessageText:
//
//  (ISSAPI) %1
//
#define ISSAPIEVT_API_ARGUMENT_VALIDATION_INVALID_CALLBACK_MASK 0xC0080033L

//
// MessageId: ISSAPIEVT_API_ARGUMENT_VALIDATION_INVALID_STATECHG_MASK
//
// MessageText:
//
//  (ISSAPI) %1
//
#define ISSAPIEVT_API_ARGUMENT_VALIDATION_INVALID_STATECHG_MASK 0xC0080034L

//
// MessageId: ISSAPIEVT_API_TYPEINST_INITIALIZED_ALREADY
//
// MessageText:
//
//  (ISSAPI) %1
//
#define ISSAPIEVT_API_TYPEINST_INITIALIZED_ALREADY 0x80080035L

//
// MessageId: ISSAPIEVT_API_MEMORY_ALLOCATION_FAILURE
//
// MessageText:
//
//  (ISSAPI) %1
//
#define ISSAPIEVT_API_MEMORY_ALLOCATION_FAILURE 0xC0080036L

//
// MessageId: ISSAPIEVT_API_LISTENER_START_ERROR
//
// MessageText:
//
//  (ISSAPI) %1
//
#define ISSAPIEVT_API_LISTENER_START_ERROR 0xC0080037L

//
// MessageId: ISSAPIEVT_API_MCS_INITIALIZATION_FAILURE
//
// MessageText:
//
//  (ISSAPI) %1
//
#define ISSAPIEVT_API_MCS_INITIALIZATION_FAILURE 0xC0080038L

//
// MessageId: ISSAPIEVT_API_SS_RECONNECT_FAILURE
//
// MessageText:
//
//  (ISSAPI) %1
//
#define ISSAPIEVT_API_SS_RECONNECT_FAILURE 0xC0080039L

//
// MessageId: ISSAPIEVT_API_RECONNECT_EXCEPTION
//
// MessageText:
//
//  (ISSAPI) %1
//
#define ISSAPIEVT_API_RECONNECT_EXCEPTION 0xC008003AL

//
// MessageId: ISSAPIEVT_API_ARGUMENT_VALIDATION_INVALID_LOAD_VALUE
//
// MessageText:
//
//  (ISSAPI) %1
//
#define ISSAPIEVT_API_ARGUMENT_VALIDATION_INVALID_LOAD_VALUE 0xC008003BL

//
// MessageId: ISSAPIEVT_API_ARGUMENT_VALIDATION_INVALID_MODOP
//
// MessageText:
//
//  (ISSAPI) %1
//
#define ISSAPIEVT_API_ARGUMENT_VALIDATION_INVALID_MODOP 0xC008003CL

//
// MessageId: ISSAPIEVT_API_RECONNECT_ERROR
//
// MessageText:
//
//  (ISSAPI) %1
//
#define ISSAPIEVT_API_RECONNECT_ERROR    0xC008003DL

//
// MessageId: ISSAPIEVT_API_RECOVERY_DUPLICATE_SID
//
// MessageText:
//
//  (ISSAPI) %1
//
#define ISSAPIEVT_API_RECOVERY_DUPLICATE_SID 0xC008003EL

//
// MessageId: ISSAPIEVT_API_TCPCOMM_CONNECT_ENABLE_RECEIVE_FAILED
//
// MessageText:
//
//  (ISSAPI) %1
//
#define ISSAPIEVT_API_TCPCOMM_CONNECT_ENABLE_RECEIVE_FAILED 0xC008003FL

//
// MessageId: ISSAPIEVT_API_ARGUMENT_VALIDATION_STREAM_STATUS_FULL_NOT_SUPPORTED_FOR_THIS_CALL
//
// MessageText:
//
//  (ISSAPI) %1
//
#define ISSAPIEVT_API_ARGUMENT_VALIDATION_STREAM_STATUS_FULL_NOT_SUPPORTED_FOR_THIS_CALL 0xC0080040L

//
// MessageId: ISSAPIEVT_API_INITIALIZATION_LOGFILE_PREFIX_ERROR
//
// MessageText:
//
//  (ISSAPI) %1
//
#define ISSAPIEVT_API_INITIALIZATION_LOGFILE_PREFIX_ERROR 0xC0080041L

//
// MessageId: ISSAPIEVT_API_INITIALIZATION_THREADPOOL_ERROR
//
// MessageText:
//
//  (ISSAPI) %1
//
#define ISSAPIEVT_API_INITIALIZATION_THREADPOOL_ERROR 0xC0080042L

//
// MessageId: ISSAPIEVT_API_INITIALIZATION_ITV_TIMER
//
// MessageText:
//
//  (ISSAPI) %1
//
#define ISSAPIEVT_API_INITIALIZATION_ITV_TIMER 0xC0080043L

//
// MessageId: ISSAPIEVT_API_INITIALIZATION_LOAD_ALGORITHM
//
// MessageText:
//
//  (ISSAPI) %1
//
#define ISSAPIEVT_API_INITIALIZATION_LOAD_ALGORITHM 0xC0080044L

//
// MessageId: ISSAPIEVT_API_INITIALIZATION_LINEAR_SEARCH_ON_CLASH
//
// MessageText:
//
//  (ISSAPI) %1
//
#define ISSAPIEVT_API_INITIALIZATION_LINEAR_SEARCH_ON_CLASH 0xC0080045L

//
// MessageId: ISSAPIEVT_API_INITIALIZATION_UNICODE_CONVERT_TO_ASCII_ERROR
//
// MessageText:
//
//  (ISSAPI) %1
//
#define ISSAPIEVT_API_INITIALIZATION_UNICODE_CONVERT_TO_ASCII_ERROR 0xC0080046L

//
// MessageId: ISSAPIEVT_API_INITIALIZATION_MTCOMM_FAILURE
//
// MessageText:
//
//  (ISSAPI) %1
//
#define ISSAPIEVT_API_INITIALIZATION_MTCOMM_FAILURE 0xC0080047L

//
// MessageId: ISSAPIEVT_API_INITIALIZATION_MTCOMM_NO_NICS
//
// MessageText:
//
//  (ISSAPI) %1
//
#define ISSAPIEVT_API_INITIALIZATION_MTCOMM_NO_NICS 0xC0080048L

//
// MessageId: ISSAPIEVT_API_INITIALIZATION_PEERGROUP_RESERVED_BITS_SET
//
// MessageText:
//
//  (ISSAPI) %1
//
#define ISSAPIEVT_API_INITIALIZATION_PEERGROUP_RESERVED_BITS_SET 0xC0080049L

//
// MessageId: ISSAPIEVT_API_ALLOCATION_UNKNOWN_DATATYPE
//
// MessageText:
//
//  (ISSAPI) %1
//
#define ISSAPIEVT_API_ALLOCATION_UNKNOWN_DATATYPE 0xC008004AL

//
// MessageId: ISSAPIEVT_API_COLLECTING_STREAM_TABLE_EXCEPTION
//
// MessageText:
//
//  (ISSAPI) %1
//
#define ISSAPIEVT_API_COLLECTING_STREAM_TABLE_EXCEPTION 0xC008004BL

//
// MessageId: ISSAPIEVT_API_ALLOCATING_SID_EXCEPTION
//
// MessageText:
//
//  (ISSAPI) %1
//
#define ISSAPIEVT_API_ALLOCATING_SID_EXCEPTION 0xC008004CL

//
// MessageId: ISSAPIEVT_API_ALLOCATING_SID_ALREADY_EXISTS
//
// MessageText:
//
//  (ISSAPI) %1
//
#define ISSAPIEVT_API_ALLOCATING_SID_ALREADY_EXISTS 0xC008004DL

//
// MessageId: ISSAPIEVT_API_FINDING_SID_EXCEPTION
//
// MessageText:
//
//  (ISSAPI) %1
//
#define ISSAPIEVT_API_FINDING_SID_EXCEPTION 0xC008004EL

//
// MessageId: ISSAPIEVT_API_DELETEING_SID_EXCEPTION
//
// MessageText:
//
//  (ISSAPI) %1
//
#define ISSAPIEVT_API_DELETEING_SID_EXCEPTION 0xC008004FL

//
// MessageId: ISSAPIEVT_API_GARBAGE_COLLECTION_CALLED_AHEAD_OF_SCHEDULE
//
// MessageText:
//
//  (ISSAPI) %1
//
#define ISSAPIEVT_API_GARBAGE_COLLECTION_CALLED_AHEAD_OF_SCHEDULE 0xC0080050L

//
// MessageId: ISSAPIEVT_API_MANPACKAGE_VARIABLE_SETUP_ERROR
//
// MessageText:
//
//  (ISSAPI) %1
//
#define ISSAPIEVT_API_MANPACKAGE_VARIABLE_SETUP_ERROR 0xC0080051L

//
// MessageId: ISSAPIEVT_API_MANPACKAGE_VARIABLE_SHUTDOWN_ERROR
//
// MessageText:
//
//  (ISSAPI) %1
//
#define ISSAPIEVT_API_MANPACKAGE_VARIABLE_SHUTDOWN_ERROR 0xC0080052L

//
// MessageId: ISSAPIEVT_API_MANPACKAGE_UNKNOWN_VARIABLE
//
// MessageText:
//
//  (ISSAPI) %1
//
#define ISSAPIEVT_API_MANPACKAGE_UNKNOWN_VARIABLE 0xC0080053L

//
// MessageId: ISSAPIEVT_API_MANPACKAGE_BUILDING_VARIABLE_BUFFER_OVERFLOW
//
// MessageText:
//
//  (ISSAPI) %1
//
#define ISSAPIEVT_API_MANPACKAGE_BUILDING_VARIABLE_BUFFER_OVERFLOW 0xC0080054L

//
// MessageId: ISSAPIEVT_API_MANPACKAGE_EXCEPTION
//
// MessageText:
//
//  (ISSAPI) %1
//
#define ISSAPIEVT_API_MANPACKAGE_EXCEPTION 0xC0080055L

//
// MessageId: ISSAPIEVT_API_TCPCOMM_SEND_ERROR
//
// MessageText:
//
//  (ISSAPI) %1
//
#define ISSAPIEVT_API_TCPCOMM_SEND_ERROR 0xC0080056L

//
// MessageId: ISSAPIEVT_API_TCPCOMM_EXCEPTION
//
// MessageText:
//
//  (ISSAPI) %1
//
#define ISSAPIEVT_API_TCPCOMM_EXCEPTION  0xC0080057L

//
// MessageId: ISSAPIEVT_API_TCPCOMM_STREAM_PREVIOUSLY_DELETED
//
// MessageText:
//
//  (ISSAPI) %1
//
#define ISSAPIEVT_API_TCPCOMM_STREAM_PREVIOUSLY_DELETED 0xC0080058L

//
// MessageId: ISSAPIEVT_API_TCPCOMM_FREE_ERROR
//
// MessageText:
//
//  (ISSAPI) %1
//
#define ISSAPIEVT_API_TCPCOMM_FREE_ERROR 0xC0080059L

//
// MessageId: ISSAPIEVT_API_TCPCOMM_STREAM_NOT_FOUND
//
// MessageText:
//
//  (ISSAPI) %1
//
#define ISSAPIEVT_API_TCPCOMM_STREAM_NOT_FOUND 0xC008005AL

//
// MessageId: ISSAPIEVT_API_TCPCOMM_POSTIT_NOT_FOUND
//
// MessageText:
//
//  (ISSAPI) %1
//
#define ISSAPIEVT_API_TCPCOMM_POSTIT_NOT_FOUND 0xC008005BL

//
// MessageId: ISSAPIEVT_API_TCPCOMM_TIMER_NOT_FOUND
//
// MessageText:
//
//  (ISSAPI) %1
//
#define ISSAPIEVT_API_TCPCOMM_TIMER_NOT_FOUND 0xC008005CL

//
// MessageId: ISSAPIEVT_API_TCPCOMM_LOAD_MESSAGE_LOST
//
// MessageText:
//
//  (ISSAPI) %1
//
#define ISSAPIEVT_API_TCPCOMM_LOAD_MESSAGE_LOST 0xC008005DL

//
// MessageId: ISSAPIEVT_API_TCPCOMM_GET_CONNECT_CONTEXT_FAILED
//
// MessageText:
//
//  (ISSAPI) %1
//
#define ISSAPIEVT_API_TCPCOMM_GET_CONNECT_CONTEXT_FAILED 0xC008005EL

//
// MessageId: ISSAPIEVT_API_TCPCOMM_CONNECT_ACCEPT_FAILED
//
// MessageText:
//
//  (ISSAPI) %1
//
#define ISSAPIEVT_API_TCPCOMM_CONNECT_ACCEPT_FAILED 0xC008005FL

//
// MessageId: ISSAPIEVT_API_TCPCOMM_CONNECT_EXPECTED_DISCONNECTED
//
// MessageText:
//
//  (ISSAPI) %1
//
#define ISSAPIEVT_API_TCPCOMM_CONNECT_EXPECTED_DISCONNECTED 0x80080060L

//
// MessageId: ISSAPIEVT_API_TCPCOMM_DROP_CONNECTION_FAILED
//
// MessageText:
//
//  (ISSAPI) %1
//
#define ISSAPIEVT_API_TCPCOMM_DROP_CONNECTION_FAILED 0xC0080061L

//
// MessageId: ISSAPIEVT_API_TCPCOMM_CONNECT_CLOSED
//
// MessageText:
//
//  (ISSAPI) %1
//
#define ISSAPIEVT_API_TCPCOMM_CONNECT_CLOSED 0x80080062L

//
// MessageId: ISSAPIEVT_API_TCPCOMM_LISTENER_WAS_DROPPED
//
// MessageText:
//
//  (ISSAPI) %1
//
#define ISSAPIEVT_API_TCPCOMM_LISTENER_WAS_DROPPED 0x80080063L

//
// MessageId: ISSAPIEVT_API_TCPCOMM_DROPPED_CONNECTION_TYPEINST_NOT_FOUND
//
// MessageText:
//
//  (ISSAPI) %1
//
#define ISSAPIEVT_API_TCPCOMM_DROPPED_CONNECTION_TYPEINST_NOT_FOUND 0x80080064L

//
// MessageId: ISSAPIEVT_API_TCPCOMM_CONNECTION_FAILING_OVER
//
// MessageText:
//
//  (ISSAPI) %1
//
#define ISSAPIEVT_API_TCPCOMM_CONNECTION_FAILING_OVER 0x80080065L

//
// MessageId: ISSAPIEVT_API_TCPCOMM_DROPPING_CONNECTION_IN_FAILOVER
//
// MessageText:
//
//  (ISSAPI) %1
//
#define ISSAPIEVT_API_TCPCOMM_DROPPING_CONNECTION_IN_FAILOVER 0x80080066L

//
// MessageId: ISSAPIEVT_API_MCAST_SERVICE_INITIALIZATION_FAILURE
//
// MessageText:
//
//  (ISSAPI) %1
//
#define ISSAPIEVT_API_MCAST_SERVICE_INITIALIZATION_FAILURE 0xC0080067L

//
// MessageId: ISSAPIEVT_API_MCAST_SERVICE_MSG_ALLOCATION_FAILURE
//
// MessageText:
//
//  (ISSAPI) %1
//
#define ISSAPIEVT_API_MCAST_SERVICE_MSG_ALLOCATION_FAILURE 0x80080068L

//
// MessageId: ISSAPIEVT_API_MCAST_SERVICE_SEND_FAILURE
//
// MessageText:
//
//  (ISSAPI) %1
//
#define ISSAPIEVT_API_MCAST_SERVICE_SEND_FAILURE 0xC0080069L

//
// MessageId: ISSAPIEVT_API_MCAST_SERVICE_DEINITIALIZATION_FAILURE
//
// MessageText:
//
//  (ISSAPI) %1
//
#define ISSAPIEVT_API_MCAST_SERVICE_DEINITIALIZATION_FAILURE 0x8008006AL

//
// MessageId: ISSAPIEVT_API_MCAST_STATE_FAILURE
//
// MessageText:
//
//  (ISSAPI) %1
//
#define ISSAPIEVT_API_MCAST_STATE_FAILURE 0x8008006BL

//
// MessageId: ISSAPIEVT_API_BAD_CM_NOTIFICATION_MESSAGE
//
// MessageText:
//
//  (ISSAPI) %1
//
#define ISSAPIEVT_API_BAD_CM_NOTIFICATION_MESSAGE 0x8008006CL

//
// MessageId: ISSAPIEVT_API_HELPERS_CREATE_SM_FAILED
//
// MessageText:
//
//  (ISSAPI) %1
//
#define ISSAPIEVT_API_HELPERS_CREATE_SM_FAILED 0xC008006DL

//
// MessageId: ISSAPIEVT_API_INITIALIZATION_EXCEPTION
//
// MessageText:
//
//  (ISSAPI) %1
//
#define ISSAPIEVT_API_INITIALIZATION_EXCEPTION 0xC008006EL

//
// MessageId: ISSAPIEVT_API_INITIALIZING_GARBAGE_COLLECTION_THREAD
//
// MessageText:
//
//  (ISSAPI) %1
//
#define ISSAPIEVT_API_INITIALIZING_GARBAGE_COLLECTION_THREAD 0xC008006FL

//
// MessageId: ISSAPIEVT_API_ACCEPTSTREAMOPERATION_UNSUPPORTED_FOR_TYPE
//
// MessageText:
//
//  (ISSAPI) %1
//
#define ISSAPIEVT_API_ACCEPTSTREAMOPERATION_UNSUPPORTED_FOR_TYPE 0xC0080070L

//
// MessageId: ISSAPIEVT_API_ARGUMENT_VALIDATION_INVALID_SERVERINFORMATIONVALUE
//
// MessageText:
//
//  (ISSAPI) %1
//
#define ISSAPIEVT_API_ARGUMENT_VALIDATION_INVALID_SERVERINFORMATIONVALUE 0xC0080071L

//
// MessageId: ISSAPIEVT_LOGGING_MESSAGE_TOO_LONG
//
// MessageText:
//
//  (ISSAPI) %1
//
#define ISSAPIEVT_LOGGING_MESSAGE_TOO_LONG 0xC0080072L

//
// MessageId: ISSAPIEVT_UNICODE_CONVERSION_ERROR
//
// MessageText:
//
//  (ISSAPI) %1
//
#define ISSAPIEVT_UNICODE_CONVERSION_ERROR 0xC0080073L

//
// MessageId: ISSAPIEVT_SID_DOES_NOT_EXIST
//
// MessageText:
//
//  (ISSAPI) %1
//
#define ISSAPIEVT_SID_DOES_NOT_EXIST     0xC0080074L

//
// MessageId: ISSAPIEVT_NUKING_STREAM_EXCEPTION
//
// MessageText:
//
//  (ISSAPI) %1
//
#define ISSAPIEVT_NUKING_STREAM_EXCEPTION 0xC0080075L

//
// MessageId: ISSAPIEVT_POLLING_THREAD_SET_EVENT_FAILED
//
// MessageText:
//
//  (ISSAPI) %1
//
#define ISSAPIEVT_POLLING_THREAD_SET_EVENT_FAILED 0xC0080076L

//
// MessageId: ISSAPIEVT_EVENT_TIME_OUT
//
// MessageText:
//
//  (ISSAPI) %1
//
#define ISSAPIEVT_EVENT_TIME_OUT         0xC0080077L

//
// MessageId: ISSAPIEVT_EVENT_UNEXPECTED_ERROR
//
// MessageText:
//
//  (ISSAPI) %1
//
#define ISSAPIEVT_EVENT_UNEXPECTED_ERROR 0xC0080078L

//
// MessageId: ISSAPIEVT_UNEXPECTED_APP_SELECTION_ALGORITHM
//
// MessageText:
//
//  (ISSAPI) %1
//
#define ISSAPIEVT_UNEXPECTED_APP_SELECTION_ALGORITHM 0xC0080079L

//
// MessageId: ISSAPIEVT_SERVER_SELECTION_ALGORITHM_FAILED_TO_SELECT_A_SERVER
//
// MessageText:
//
//  (ISSAPI) %1
//
#define ISSAPIEVT_SERVER_SELECTION_ALGORITHM_FAILED_TO_SELECT_A_SERVER 0xC008007AL

//
// MessageId: ISSAPIEVT_STREAM_STATUS_INCONSISTENCY
//
// MessageText:
//
//  (ISSAPI) %1
//
#define ISSAPIEVT_STREAM_STATUS_INCONSISTENCY 0xC008007BL

//
// MessageId: ISSAPIEVT_API_CALLBACK_UNKNOWN_CALLBACK_TYPE
//
// MessageText:
//
//  (ISSAPI) %1
//
#define ISSAPIEVT_API_CALLBACK_UNKNOWN_CALLBACK_TYPE 0xC008007CL

//
// MessageId: ISSAPIEVT_API_TCPCOMM_CONNECT_DESTROYED
//
// MessageText:
//
//  (ISSAPI) %1
//
#define ISSAPIEVT_API_TCPCOMM_CONNECT_DESTROYED 0xC008007DL

//
// MessageId: ISSAPIEVT_API_ARGUMENT_VALIDATION_APPSPECTYPE_UNKNOWN
//
// MessageText:
//
//  (ISSAPI) %1
//
#define ISSAPIEVT_API_ARGUMENT_VALIDATION_APPSPECTYPE_UNKNOWN 0xC008007EL

//
// MessageId: ISSAPIEVT_API_STREAM_ID_ALREADY_IN_USE
//
// MessageText:
//
//  (ISSAPI) %1
//  
//
#define ISSAPIEVT_API_STREAM_ID_ALREADY_IN_USE 0xC008007FL

//
// MessageId: ISSAPIEVT_SS_NOT_AVAILABLE
//
// MessageText:
//
//  (ISSAPI) %1
//
#define ISSAPIEVT_SS_NOT_AVAILABLE       0xC0080080L

//
// MessageId: ISSAPIEVT_API_TCPCOMM_RECEIVE_FAILED
//
// MessageText:
//
//  (ISSAPI) %1
//
#define ISSAPIEVT_API_TCPCOMM_RECEIVE_FAILED 0xC0080081L

//
// MessageId: ISSAPIEVT_API_TCPCOMM_CLOSE_FAILED
//
// MessageText:
//
//  (ISSAPI) %1
//
#define ISSAPIEVT_API_TCPCOMM_CLOSE_FAILED 0xC0080082L

//
// MessageId: ISSAPIEVT_API_TCPCOMM_FAILOVER_FAILED
//
// MessageText:
//
//  (ISSAPI) %1
//
#define ISSAPIEVT_API_TCPCOMM_FAILOVER_FAILED 0xC0080083L

//*******************************************************************************
//*
//*     Data Carousel Manager Messages 
//*
//*******************************************************************************
//
// MessageId: DCMEVT_STARTED
//
// MessageText:
//
//  (DCM) SeaChange Data Carousel Manager started
//
#define DCMEVT_STARTED                   0x40090001L

//
// MessageId: DCMEVT_MANPKG
//
// MessageText:
//
//  (DCM) Unable to initialize ManPkg %1 %2
//
#define DCMEVT_MANPKG                    0xC0090002L

//
// MessageId: DCMEVT_MANVAR
//
// MessageText:
//
//  (DCM) Unable to manage variable %1 %2
//
#define DCMEVT_MANVAR                    0xC0090003L

//
// MessageId: DCMEVT_INIT
//
// MessageText:
//
//  (DCM) Unable to initialize %1
//
#define DCMEVT_INIT                      0xC0090004L

//
// MessageId: DCMEVT_STOPPED
//
// MessageText:
//
//  (DCM) SeaChange Data Carousel Manager stopped
//
#define DCMEVT_STOPPED                   0x40090005L

//
// MessageId: DCMEVT_MANPKGCLOSE
//
// MessageText:
//
//  (DCM) Unable to close ManPkg session %1 %2
//
#define DCMEVT_MANPKGCLOSE               0xC0090006L

//
// MessageId: DCMEVT_ERROR
//
// MessageText:
//
//  (DCM) Error on %1 %2
//
#define DCMEVT_ERROR                     0xC0090007L

//
// MessageId: DCMEVT_NOMEMORY
//
// MessageText:
//
//  (DCM) Out of memory
//
#define DCMEVT_NOMEMORY                  0xC0090008L

//
// MessageId: DCMEVT_FREEERROR
//
// MessageText:
//
//  (DCM) Error while freeing hierarchy information %1
//
#define DCMEVT_FREEERROR                 0xC0090009L

//
// MessageId: DCMEVT_FILEERROR
//
// MessageText:
//
//  (DCM) Error %1 on call %2 for file %3
//
#define DCMEVT_FILEERROR                 0xC009000AL

//
// MessageId: DCMEVT_FINDHIER
//
// MessageText:
//
//  (DCM) Unable to find hierarchy entry %1
//
#define DCMEVT_FINDHIER                  0xC009000BL

//
// MessageId: DCMEVT_REMOVEHIER
//
// MessageText:
//
//  (DCM) Unable to remove hierarchy entry %1
//
#define DCMEVT_REMOVEHIER                0xC009000CL

//
// MessageId: DCMEVT_FREEHIER
//
// MessageText:
//
//  (DCM) Unable to free hierarchy entry %1
//
#define DCMEVT_FREEHIER                  0xC009000DL

//
// MessageId: DCMEVT_NOPARENT
//
// MessageText:
//
//  (DCM) Parent %1 no longer exists
//
#define DCMEVT_NOPARENT                  0xC009000EL

//
// MessageId: DCMEVT_FILETOOBIG
//
// MessageText:
//
//  (DCM) File %1 too big for carousel data %2 %3
//
#define DCMEVT_FILETOOBIG                0xC009000FL

//
// MessageId: DCMEVT_SIZEEXCEEDED
//
// MessageText:
//
//  (DCM) The carousel data %1 has exceeded the maximum size %2
//
#define DCMEVT_SIZEEXCEEDED              0xC0090010L

//
// MessageId: DCMEVT_INFO
//
// MessageText:
//
//  (DCM) %1
//
#define DCMEVT_INFO                      0x40090011L

//*******************************************************************************
//*
//*     Load Advertiser Messages 
//*
//*******************************************************************************
//
// MessageId: LAEVT_SYSERR
//
// MessageText:
//
//  (LA) Error - %1
//
#define LAEVT_SYSERR                     0xC00C0001L

//
// MessageId: LAEVT_WARNING
//
// MessageText:
//
//  (LA) Warning - %1
//
#define LAEVT_WARNING                    0x800C0002L

//
// MessageId: LAEVT_LOG_INIT
//
// MessageText:
//
//  (LA) Error %1 initializing circular logging package
//
#define LAEVT_LOG_INIT                   0xC00C0003L

//
// MessageId: LAEVT_OUTOFMEMORY
//
// MessageText:
//
//  (LA) Out of memory: Error %1, Line: %2
//
#define LAEVT_OUTOFMEMORY                0xC00C0004L

//
// MessageId: LAEVT_START
//
// MessageText:
//
//  (LA) Initializing...
//
#define LAEVT_START                      0x400C0005L

//
// MessageId: LAEVT_STOP
//
// MessageText:
//
//  (LA) Terminating...
//
#define LAEVT_STOP                       0x400C0006L

//
// MessageId: LAEVT_SYSERR1
//
// MessageText:
//
//  (LA) Error - %1 Error: %2
//
#define LAEVT_SYSERR1                    0xC00C0007L

//
// MessageId: LAEVT_SYSERR2
//
// MessageText:
//
//  (LA) Error - %1 Error: %2, extended Error: %3
//
#define LAEVT_SYSERR2                    0xC00C0008L

//
// MessageId: LAEVT_NOINIT
//
// MessageText:
//
//  (LA) Unable to initialize. Error %1, extended Error: %2
//
#define LAEVT_NOINIT                     0xC00C0009L

//
// MessageId: LAEVT_NOUNINIT
//
// MessageText:
//
//  (LA) Unable to uninitialize. Error %1, extended Error: %2
//
#define LAEVT_NOUNINIT                   0xC00C000AL

//
// MessageId: LAEVT_NOQUEUETIMER
//
// MessageText:
//
//  (LA) Unable to queue timer event
//
#define LAEVT_NOQUEUETIMER               0xC00C000BL

//
// MessageId: LAEVT_SBS
//
// MessageText:
//
//  (LA) Error - System Broadcast Service (SBS) error %1 from %2
//
#define LAEVT_SBS                        0xC00C000CL

//
// MessageId: LAEVT_MSME
//
// MessageText:
//
//  (LA) State Machine Engine error, routine %1 status %2
//
#define LAEVT_MSME                       0xC00C000DL

//
// MessageId: LAEVT_NOCONTEXT
//
// MessageText:
//
//  (LA) State Machine Engine error, no context %1
//
#define LAEVT_NOCONTEXT                  0xC00C000EL

//*******************************************************************************
//*
//*     System Monitor Messages 
//*
//*******************************************************************************
//
// MessageId: SYSMONEVT_STARTING
//
// MessageText:
//
//  (SysMon) Starting...
//
#define SYSMONEVT_STARTING               0x400D0001L

//
// MessageId: SYSMONEVT_EXITING
//
// MessageText:
//
//  (SysMon) Exiting...
//
#define SYSMONEVT_EXITING                0x400D0002L

//
// MessageId: SYSMONEVT_SYSERR
//
// MessageText:
//
//  (SysMon) System error %1
//
#define SYSMONEVT_SYSERR                 0xC00D0003L

//
// MessageId: SYSMONEVT_STARTFAILED
//
// MessageText:
//
//  (SysMon) Failed to start System Monitor service
//
#define SYSMONEVT_STARTFAILED            0xC00D0004L

//
// MessageId: SYSMONEVT_APIERR
//
// MessageText:
//
//  (SysMon) API %1 failed, error %2
//
#define SYSMONEVT_APIERR                 0xC00D0005L

//
// MessageId: SYSMONEVT_OUTOFMEMOERY
//
// MessageText:
//
//  (SysMon) Out of memory
//
#define SYSMONEVT_OUTOFMEMOERY           0xC00D0006L

//
// MessageId: SYSMONEVT_BADMESSAGEFORMAT
//
// MessageText:
//
//  (SysMon) Bad message format. Message from service type %1, instance %2
//
#define SYSMONEVT_BADMESSAGEFORMAT       0xC00D0007L

//
// MessageId: SYSMONEVT_DBERR
//
// MessageText:
//
//  (SysMon) Database error. %1
//
#define SYSMONEVT_DBERR                  0xC00D0008L

//
// MessageId: SYSMONEVT_RUNSTATS
//
// MessageText:
//
//  (SysMon) CM Runstats %1
//
#define SYSMONEVT_RUNSTATS               0x400D0009L

//
// MessageId: SYSMONEVT_INACTIVE_COMPONENT
//
// MessageText:
//
//  (SysMon) Service %1 was stopped, last known active at %2
//
#define SYSMONEVT_INACTIVE_COMPONENT     0xC00D000AL

//*******************************************************************************
//*
//*     System Resource Manager Messages 
//*
//*******************************************************************************
//
// MessageId: SRMEVT_SYSERR
//
// MessageText:
//
//  (SRM) Error - %1
//
#define SRMEVT_SYSERR                    0xC00E0001L

//
// MessageId: SRMEVT_SYSERR1
//
// MessageText:
//
//  (SRM) Error -  %1 Error: %2
//
#define SRMEVT_SYSERR1                   0xC00E0002L

//
// MessageId: SRMEVT_WARNING
//
// MessageText:
//
//  (SRM) Warning - %1
//
#define SRMEVT_WARNING                   0x800E0003L

//
// MessageId: SRMEVT_INFO
//
// MessageText:
//
//  (SRM) Information - %1
//
#define SRMEVT_INFO                      0x400E0004L

//
// MessageId: SRMEVT_CFG_INIT
//
// MessageText:
//
//  (SRM) Error %1 initializing configuration package
//
#define SRMEVT_CFG_INIT                  0xC00E0005L

//
// MessageId: SRMEVT_LOG_INIT
//
// MessageText:
//
//  (SRM) Error %1 initializing circular logging package
//
#define SRMEVT_LOG_INIT                  0xC00E0006L

//
// MessageId: SRMEVT_START
//
// MessageText:
//
//  (SRM) Information - SRM Initializing.. %1
//
#define SRMEVT_START                     0x400E0007L

//
// MessageId: SRMEVT_INITFAILED
//
// MessageText:
//
//  (SRM) Error - SRM Failed to initialize %1, exiting..
//
#define SRMEVT_INITFAILED                0xC00E0008L

//
// MessageId: SRMEVT_INIT_INFO
//
// MessageText:
//
//  (SRM) Information - SRM initializing: %1
//
#define SRMEVT_INIT_INFO                 0x400E0009L

//
// MessageId: SRMEVT_INITDONE
//
// MessageText:
//
//  (SRM) Information - SRM initialization done.
//
#define SRMEVT_INITDONE                  0x400E000AL

//
// MessageId: SRMEVT_LSC_ERROR
//
// MessageText:
//
//  (SRM) Error - LSC Handler: %1
//
#define SRMEVT_LSC_ERROR                 0xC00E000BL

//
// MessageId: SRMEVT_LSC_SOCKETFAIL
//
// MessageText:
//
//  (SRM) Error - LSC Handler Socket Failure with: %1
//
#define SRMEVT_LSC_SOCKETFAIL            0xC00E000CL

//
// MessageId: SRMEVT_LSC_INFO
//
// MessageText:
//
//  (SRM) Information - LSC Handler: %1
//
#define SRMEVT_LSC_INFO                  0x400E000DL

//
// MessageId: SRMEVT_ALIVE_ERROR
//
// MessageText:
//
//  (SRM) Error - KeepAlive Thread: %1
//
#define SRMEVT_ALIVE_ERROR               0xC00E000EL

//
// MessageId: SRMEVT_ALIVE_WARNING
//
// MessageText:
//
//  (SRM) Warning - KeepAlive Thread: %1
//
#define SRMEVT_ALIVE_WARNING             0x800E000FL

//
// MessageId: SRMEVT_PIPE_INFO
//
// MessageText:
//
//  (SRM) Information - PIPE: %1
//
#define SRMEVT_PIPE_INFO                 0x400E0010L

//
// MessageId: SRMEVT_CASCOMM_ERROR
//
// MessageText:
//
//  (SRM) Error - CASCOMM: %1
//
#define SRMEVT_CASCOMM_ERROR             0xC00E0011L

//
// MessageId: SRMEVT_CASCOMM_WARNING
//
// MessageText:
//
//  (SRM) Warning - CASCOMM: %1
//
#define SRMEVT_CASCOMM_WARNING           0x800E0012L

//
// MessageId: SRMEVT_CASCOMM_INFO
//
// MessageText:
//
//  (SRM) Information - CASCOMM: %1
//
#define SRMEVT_CASCOMM_INFO              0x400E0013L

//
// MessageId: SRMEVT_SESSION_ERROR
//
// MessageText:
//
//  (SRM) Error - SESSION: %1
//
#define SRMEVT_SESSION_ERROR             0xC00E0014L

//
// MessageId: SRMEVT_SESSION_WARNING
//
// MessageText:
//
//  (SRM) Warning - SESSION: %1
//
#define SRMEVT_SESSION_WARNING           0x800E0015L

//
// MessageId: SRMEVT_SESSION_INFO
//
// MessageText:
//
//  (SRM) Information - SESSION: %1
//
#define SRMEVT_SESSION_INFO              0x400E0016L

//
// MessageId: SRMEVT_RTSP_ERROR
//
// MessageText:
//
//  (SRM) Error - RTSP: %1
//
#define SRMEVT_RTSP_ERROR                0xC00E0017L

//
// MessageId: SRMEVT_RTSP_WARNING
//
// MessageText:
//
//  (SRM) Warning - RTSP: %1
//
#define SRMEVT_RTSP_WARNING              0x800E0018L

//
// MessageId: SRMEVT_RTSP_INFO
//
// MessageText:
//
//  (SRM) Information - RTSP: %1
//
#define SRMEVT_RTSP_INFO                 0x400E0019L

//
// MessageId: SRMEVT_CLIENT_ERROR
//
// MessageText:
//
//  (SRM) Error - CLIENT: %1
//
#define SRMEVT_CLIENT_ERROR              0xC00E001AL

//
// MessageId: SRMEVT_CLIENT_WARNING
//
// MessageText:
//
//  (SRM) Warning - CLIENT: %1
//
#define SRMEVT_CLIENT_WARNING            0x800E001BL

//
// MessageId: SRMEVT_CLIENT_INFO
//
// MessageText:
//
//  (SRM) Information - CLIENT: %1
//
#define SRMEVT_CLIENT_INFO               0x400E001CL

//
// MessageId: SRMEVT_SERVER_ERROR
//
// MessageText:
//
//  (SRM) Error - SERVER: %1
//
#define SRMEVT_SERVER_ERROR              0xC00E001DL

//
// MessageId: SRMEVT_SERVER_WARNING
//
// MessageText:
//
//  (SRM) Warning - SERVER: %1
//
#define SRMEVT_SERVER_WARNING            0x800E001EL

//
// MessageId: SRMEVT_SERVER_INFO
//
// MessageText:
//
//  (SRM) Information - SERVER: %1
//
#define SRMEVT_SERVER_INFO               0x400E001FL

//*******************************************************************************
//*
//*     Asset Manager Corba interface Messages 
//*
//*******************************************************************************
//
// MessageId: AMSEVT_STARTING
//
// MessageText:
//
//  (ADIS) Starting...
//
#define AMSEVT_STARTING                  0x400F0001L

//
// MessageId: AMSEVT_EXITING
//
// MessageText:
//
//  (ADIS) Exiting...
//
#define AMSEVT_EXITING                   0x400F0002L

//
// MessageId: AMSEVT_SYSERR
//
// MessageText:
//
//  (ADIS) System error %1
//
#define AMSEVT_SYSERR                    0xC00F0003L

//
// MessageId: AMSEVT_STARTFAILED
//
// MessageText:
//
//  (ADIS) Failed to start Asset Management System service
//
#define AMSEVT_STARTFAILED               0xC00F0004L

//
// MessageId: AMSEVT_APIERR
//
// MessageText:
//
//  (ADIS) API %1 failed, error %2
//
#define AMSEVT_APIERR                    0xC00F0005L

//
// MessageId: AMSEVT_INITFAILED
//
// MessageText:
//
//  (ADIS) Failed to initialize. %1
//
#define AMSEVT_INITFAILED                0xC00F0006L

//
// MessageId: AMSEVT_OUTOFMEMOERY
//
// MessageText:
//
//  (ADIS) Out of memory
//
#define AMSEVT_OUTOFMEMOERY              0xC00F0007L

//
// MessageId: AMSEVT_SUCCESS
//
// MessageText:
//
//  (ADIS) Success
//
#define AMSEVT_SUCCESS                   0x400F0008L

//
// MessageId: AMSEVT_BAD_URL
//
// MessageText:
//
//  (ADIS) Bad url %1
//
#define AMSEVT_BAD_URL                   0xC00F0009L

//
// MessageId: AMSEVT_SERVICETYPE_NOT_SUPPORTED
//
// MessageText:
//
//  (ADIS) url service type %1 not supported
//
#define AMSEVT_SERVICETYPE_NOT_SUPPORTED 0xC00F000AL

//
// MessageId: AMSEVT_BAD_REPORT_FORMAT
//
// MessageText:
//
//  (ADIS) Bad report file format %1
//
#define AMSEVT_BAD_REPORT_FORMAT         0xC00F000BL

//
// MessageId: AMSEVT_UPLOAD_FAILED
//
// MessageText:
//
//  (ADIS) Failed to upload content %1 (0x%2), error %3
//
#define AMSEVT_UPLOAD_FAILED             0xC00F000CL

//
// MessageId: AMSEVT_WAITFORREPORT_FAILED
//
// MessageText:
//
//  (ADIS) Failed to watch report path %1
//
#define AMSEVT_WAITFORREPORT_FAILED      0xC00F000DL

//
// MessageId: AMSEVT_GETREPORT_FAILED
//
// MessageText:
//
//  (ADIS) Failed to get report file %1, error %2
//
#define AMSEVT_GETREPORT_FAILED          0xC00F000EL

//
// MessageId: AMSEVT_FTP_FAILED
//
// MessageText:
//
//  (ADIS) Failed to ftp get file %1%2 to %3, error %4
//
#define AMSEVT_FTP_FAILED                0xC00F000FL

//
// MessageId: AMSEVT_HTTP_FAILED
//
// MessageText:
//
//  (ADIS) Failed to http get file %1%2 to %3, error %4
//
#define AMSEVT_HTTP_FAILED               0xC00F0010L

//
// MessageId: AMSEVT_PARSEASSETDATAFILE_FAILED
//
// MessageText:
//
//  (ADIS) Failed to parse file %1. Please refer to the import report file for status
//
#define AMSEVT_PARSEASSETDATAFILE_FAILED 0xC00F0011L

//
// MessageId: AMSEVT_NO_DISK_SPACE
//
// MessageText:
//
//  (ADIS) Not enough free disk space on %1, %2
//
#define AMSEVT_NO_DISK_SPACE             0xC00F0012L

//*******************************************************************************
//*
//*     ISA Stream Interface Messages 
//*
//*******************************************************************************
//
// MessageId: ISA_STREAM_START_ERR
//
// MessageText:
//
//  (isaStream) Error while starting isaStream service. Detail : %1
//
#define ISA_STREAM_START_ERR             0xC0110001L

//
// MessageId: ISA_STREAM_START_SUCCESS
//
// MessageText:
//
//  (isaStream) ------------- isaStream service is ready -------------
//
#define ISA_STREAM_START_SUCCESS         0x40110002L

//
// MessageId: ISA_STREAM_REGISTRATION_ERR
//
// MessageText:
//
//  (isaStream) Error while registering to CORBA NameService : %1.
//
#define ISA_STREAM_REGISTRATION_ERR      0xC0110003L

//
// MessageId: ISA_STREAM_REGISTRATION_SUCCESS
//
// MessageText:
//
//  (isaStream) StreamService has registered in NameService.
//
#define ISA_STREAM_REGISTRATION_SUCCESS  0x40110004L

//
// MessageId: ISA_STREAM_OPERATION_ERR
//
// MessageText:
//
//  (isaStream) %1.
//
#define ISA_STREAM_OPERATION_ERR         0xC0110005L

//*******************************************************************************
//*
//*     ISA Content Interface Messages 
//*
//*******************************************************************************
//
// MessageId: ISA_CONTENT_START_ERR
//
// MessageText:
//
//  (isaContent) Error while starting isaContent service. Detail : %1
//
#define ISA_CONTENT_START_ERR            0xC0120001L

//
// MessageId: ISA_CONTENT_START_SUCCESS
//
// MessageText:
//
//  (isaContent) ------------- isaContent service is ready -------------
//
#define ISA_CONTENT_START_SUCCESS        0x40120002L

//
// MessageId: ISA_CONTENT_REGISTRATION_ERR
//
// MessageText:
//
//  (isaContent) Error while registering to CORBA NameService : %1.
//
#define ISA_CONTENT_REGISTRATION_ERR     0xC0120003L

//
// MessageId: ISA_CONTENT_REGISTRATION_SUCCESS
//
// MessageText:
//
//  (isaContent) ContentStore has registered in NameService.
//
#define ISA_CONTENT_REGISTRATION_SUCCESS 0x40120004L

//
// MessageId: ISA_CONTENT_OPERATION_ERR
//
// MessageText:
//
//  (isaContent) %1.
//
#define ISA_CONTENT_OPERATION_ERR        0xC0120005L

//*******************************************************************************
//*
//*     ISA AppServer Service Messages 
//*
//*******************************************************************************
//
// MessageId: ISA_AS_START_ERR
//
// MessageText:
//
//  (isaAs) Error while starting isaAs service. Detail : %1
//
#define ISA_AS_START_ERR                 0xC0150001L

//
// MessageId: ISA_AS_START_SUCCESS
//
// MessageText:
//
//  (isaAs) ------------- isaAs service is ready -------------
//
#define ISA_AS_START_SUCCESS             0x40150002L

//
// MessageId: ISA_AS_OPERATION_ERR
//
// MessageText:
//
//  (isaAs) %1.
//
#define ISA_AS_OPERATION_ERR             0xC0150003L

//*******************************************************************************
//*
//*     XML Interface DLL Messages 
//*
//*******************************************************************************
//
// MessageId: XMLEVT_CREATEFILE
//
// MessageText:
//
//  (XML) Unable to create file %1
//
#define XMLEVT_CREATEFILE                0xC0130001L

//
// MessageId: XMLEVT_DSCONN
//
// MessageText:
//
//  (XML) Established connection to ITV DS
//
#define XMLEVT_DSCONN                    0x40130002L

//
// MessageId: XMLEVT_DSCONNLOST
//
// MessageText:
//
//  (XML) Lost connection to ITV DS at site %1
//
#define XMLEVT_DSCONNLOST                0x80130003L

//
// MessageId: XMLEVT_FINDHIER
//
// MessageText:
//
//  (XML) Unable to find hierarchy entry %1 %2
//
#define XMLEVT_FINDHIER                  0xC0130004L

//
// MessageId: XMLEVT_FREEERROR
//
// MessageText:
//
//  (XML) Error while freeing hierarchy information %1
//
#define XMLEVT_FREEERROR                 0xC0130005L

//
// MessageId: XMLEVT_FREEHIER
//
// MessageText:
//
//  (XML) Unable to free hierarchy entry %1 %2
//
#define XMLEVT_FREEHIER                  0xC0130006L

//
// MessageId: XMLEVT_IDSERROR
//
// MessageText:
//
//  (XML) Error on %1 %2 %3
//
#define XMLEVT_IDSERROR                  0xC0130007L

//
// MessageId: XMLEVT_MANPKG
//
// MessageText:
//
//  (XML) Unable to initialize ManPkg %1 %2
//
#define XMLEVT_MANPKG                    0xC0130008L

//
// MessageId: XMLEVT_MANPKGCLOSE
//
// MessageText:
//
//  (XML) Unable to close ManPkg session %1 %2
//
#define XMLEVT_MANPKGCLOSE               0xC0130009L

//
// MessageId: XMLEVT_MANVAR
//
// MessageText:
//
//  (XML) Unable to manage variable %1 %2
//
#define XMLEVT_MANVAR                    0xC013000AL

//
// MessageId: XMLEVT_NODUPLIST
//
// MessageText:
//
//  (XML) Unable to duplicate selection list %1
//
#define XMLEVT_NODUPLIST                 0xC013000BL

//
// MessageId: XMLEVT_NOENTRY
//
// MessageText:
//
//  (XML) Entry %1 no longer exists
//
#define XMLEVT_NOENTRY                   0xC013000CL

//
// MessageId: XMLEVT_NOLIST
//
// MessageText:
//
//  (XML) Required selection does not exist for %1
//
#define XMLEVT_NOLIST                    0xC013000DL

//
// MessageId: XMLEVT_NOMEMORY
//
// MessageText:
//
//  (XML) Unable to allocate memory for %1
//
#define XMLEVT_NOMEMORY                  0xC013000EL

//
// MessageId: XMLEVT_NONEWPARENT
//
// MessageText:
//
//  (XML) Unable to associate folder with new parent %1
//
#define XMLEVT_NONEWPARENT               0xC013000FL

//
// MessageId: XMLEVT_NOPARENT
//
// MessageText:
//
//  (XML) Parent %1 no longer exists
//
#define XMLEVT_NOPARENT                  0xC0130010L

//
// MessageId: XMLEVT_OLDSTAMP
//
// MessageText:
//
//  (XML) Update stamp for %1 is not as recent as current value
//
#define XMLEVT_OLDSTAMP                  0xC0130011L

//
// MessageId: XMLEVT_REMOVEHIER
//
// MessageText:
//
//  (XML) Unable to remove hierarchy entry %1 %2
//
#define XMLEVT_REMOVEHIER                0xC0130012L

//
// MessageId: XMLEVT_TRIGGERNOTFOUND
//
// MessageText:
//
//  (XML) No site found for trigger ID %1
//
#define XMLEVT_TRIGGERNOTFOUND           0xC0130013L

//
// MessageId: XMLEVT_STOPPED
//
// MessageText:
//
//  (XML) XML Interfaces DLL stopped
//
#define XMLEVT_STOPPED                   0x40130014L

//*******************************************************************************
//*
//*     Asset Manager Messages 
//*
//*******************************************************************************
//
// MessageId: ETFEVT_STARTING
//
// MessageText:
//
//  (ETF) Starting...
//
#define ETFEVT_STARTING                  0x40140001L

//
// MessageId: ETFEVT_EXITING
//
// MessageText:
//
//  (ETF) Exiting...
//
#define ETFEVT_EXITING                   0x40140002L

//
// MessageId: ETFEVT_SYSERR
//
// MessageText:
//
//  (ETF) System error %1
//
#define ETFEVT_SYSERR                    0xC0140003L

//
// MessageId: ETFEVT_STARTFAILED
//
// MessageText:
//
//  (ETF) Failed to start Encryption and Trick File service
//
#define ETFEVT_STARTFAILED               0xC0140004L

//
// MessageId: ETFEVT_APIERR
//
// MessageText:
//
//  (ETF) API %1 failed, error %2
//
#define ETFEVT_APIERR                    0xC0140005L

//
// MessageId: ETFEVT_OUTOFMEMOERY
//
// MessageText:
//
//  (ETF) Out of memory
//
#define ETFEVT_OUTOFMEMOERY              0xC0140006L

//
// MessageId: ETFEVT_BIND_FAILED
//
// MessageText:
//
//  (ETF) Failed to connect to DS, error %1
//
#define ETFEVT_BIND_FAILED               0xC0140007L

//
// MessageId: ETFEVT_LISTWQ_FAILED
//
// MessageText:
//
//  (ETF) Failed to get wqe list from DS, %1
//
#define ETFEVT_LISTWQ_FAILED             0xC0140008L

//*******************************************************************************
//*
//* SRM Messages  - SRM V2 (new SRM)
//*
//*******************************************************************************
//******************************************************************************
//*
//*     SRM Success Messages 
//*
//******************************************************************************
//
// MessageId: GSRMEVT_INFO
//
// MessageText:
//
//  %1
//
#define GSRMEVT_INFO                     0x41080001L

//
// MessageId: GSRMEVT_INITDONE
//
// MessageText:
//
//  SRM initialization done.
//
#define GSRMEVT_INITDONE                 0x41080002L

//
// MessageId: GSRMEVT_EXIT
//
// MessageText:
//
//  %1
//
#define GSRMEVT_EXIT                     0x41080003L

//
// MessageId: GSRMEVT_CFG_INFO
//
// MessageText:
//
//  CFGPKG using %1 for %2 value %3
//
#define GSRMEVT_CFG_INFO                 0x41080004L

//
// MessageId: GSRMEVT_START
//
// MessageText:
//
//  SRM Initializing.. %1
//
#define GSRMEVT_START                    0x41080005L

//
// MessageId: GSRMEVT_INIT_INFO
//
// MessageText:
//
//  SRM initializing: %1
//
#define GSRMEVT_INIT_INFO                0x41080006L

// un-used
//
// MessageId: GSRMEVT_PIPE_INFO
//
// MessageText:
//
//  PIPE: %1
//
#define GSRMEVT_PIPE_INFO                0x41080007L

//
// MessageId: GSRMEVT_SESSION_GETAPPLIST_INFO
//
// MessageText:
//
//  SESSION MGR: GetAppListCallback: %1
//
#define GSRMEVT_SESSION_GETAPPLIST_INFO  0x41080008L

//
// MessageId: GSRMEVT_SESSION_RMRES_INFO
//
// MessageText:
//
//  SESSION MGR: RMReserveCompletionRoutine:  %1
//
#define GSRMEVT_SESSION_RMRES_INFO       0x41080009L

//
// MessageId: GSRMEVT_SESSION_RMRES_SUCC
//
// MessageText:
//
//  SESSION MGR: RMReserveCompletionRoutine: RM Reserve suceeded - %1
//
#define GSRMEVT_SESSION_RMRES_SUCC       0x4108000AL

//
// MessageId: GSRMEVT_SESSION_RMREL_INFO
//
// MessageText:
//
//  SESSION MGR: RMReleaseCompletionRoutine: %1
//
#define GSRMEVT_SESSION_RMREL_INFO       0x4108000BL

//
// MessageId: GSRMEVT_SESSION_RMREL_SUCC
//
// MessageText:
//
//  SESSION MGR: RMReleaseCompletionRoutine: RM Release suceeded - %1
//
#define GSRMEVT_SESSION_RMREL_SUCC       0x4108000CL

//
// MessageId: GSRMEVT_SESSION_RMREC_INFO
//
// MessageText:
//
//  SESSION MGR: RMRecoveryCompletionRoutine: %1
//
#define GSRMEVT_SESSION_RMREC_INFO       0x4108000DL

//
// MessageId: GSRMEVT_SESSION_RMREC_SUCC
//
// MessageText:
//
//  SESSION MGR: RMRecoveryCompletionRoutine: RM Recovery suceeded - %1 
//
#define GSRMEVT_SESSION_RMREC_SUCC       0x4108000EL

//
// MessageId: GSRMEVT_SESSION_FOUND
//
// MessageText:
//
//  SESSION MGR: FindSession - Session found %1
//
#define GSRMEVT_SESSION_FOUND            0x4108000FL

//
// MessageId: GSRMEVT_SESSION_NOTFOUND
//
// MessageText:
//
//  SESSION MGR: FindSession - Session not found %1
//
#define GSRMEVT_SESSION_NOTFOUND         0x41080010L

//
// MessageId: GSRMEVT_SESSION_REMOVED
//
// MessageText:
//
//  SESSION MGR: removeSessionLocked - Session removed %1
//
#define GSRMEVT_SESSION_REMOVED          0x41080011L

//
// MessageId: GSRMEVT_SESSION_NOTREMOVED
//
// MessageText:
//
//  SESSION MGR: removeSessionLocked - Session not found, not removed %1
//
#define GSRMEVT_SESSION_NOTREMOVED       0x41080012L

//
// MessageId: GSRMEVT_SESSION_ADDED
//
// MessageText:
//
//  SESSION MGR: addSessionLocked - Session %1 added to list
//
#define GSRMEVT_SESSION_ADDED            0x41080013L

//
// MessageId: GSRMEVT_SESSION_INFO
//
// MessageText:
//
//  SESSION MGR: %1
//
#define GSRMEVT_SESSION_INFO             0x41080014L

//
// MessageId: GSRMEVT_PTCLIENT_INFO
//
// MessageText:
//
//  PASSTHRU CLIENT: %1
//
#define GSRMEVT_PTCLIENT_INFO            0x41080015L

//
// MessageId: GSRMEVT_CLIENT_INFO
//
// MessageText:
//
//  CLIENT: %1
//
#define GSRMEVT_CLIENT_INFO              0x41080016L

//
// MessageId: GSRMEVT_SERVER_INFO
//
// MessageText:
//
//  SERVER: %1
//
#define GSRMEVT_SERVER_INFO              0x41080017L

//
// MessageId: GSRMEVT_DNCS_INFO
//
// MessageText:
//
//  OtherSRM: %1
//
#define GSRMEVT_DNCS_INFO                0x41080018L

//
// MessageId: GSRMEVT_SESSSM_TIMER_INFO
//
// MessageText:
//
//  SESSION SM TIMER: %1
//
#define GSRMEVT_SESSSM_TIMER_INFO        0x41080019L

//
// MessageId: GSRMEVT_SESSSM_INFO
//
// MessageText:
//
//  SESSION SM: %1
//
#define GSRMEVT_SESSSM_INFO              0x4108001AL

//
// MessageId: GSRMEVT_DISPATCH_INFO
//
// MessageText:
//
//  Dispatcher: %1
//
#define GSRMEVT_DISPATCH_INFO            0x4108001BL

//
// MessageId: GSRMEVT_SESSOSM_INFO
//
// MessageText:
//
//  OSM: %1
//
#define GSRMEVT_SESSOSM_INFO             0x4108001CL

//
// MessageId: GSRMEVT_RM_INFO
//
// MessageText:
//
//  RSRCMGR: %1
//
#define GSRMEVT_RM_INFO                  0x4108001DL

//
// MessageId: GSRMEVT_RSM_INFO
//
// MessageText:
//
//  RSRC SM: %1
//
#define GSRMEVT_RSM_INFO                 0x4108001EL

//
// MessageId: GSRMEVT_REQLOG_INFO
//
// MessageText:
//
//  ReqLog DB: %1
//
#define GSRMEVT_REQLOG_INFO              0x4108001FL

//
// MessageId: GSRMEVT_SRMDB_INFO
//
// MessageText:
//
//  SRM DB: %1
//
#define GSRMEVT_SRMDB_INFO               0x41080020L

//******************************************************************************
//*
//*     SRM Warning Messages 
//*
//******************************************************************************
//
// MessageId: GSRMEVT_WARNING
//
// MessageText:
//
//  %1
//
#define GSRMEVT_WARNING                  0x81080021L

//
// MessageId: GSRMEVT_ALIVE_WARNING
//
// MessageText:
//
//  SESSION MGR: KeepAlive Timer: %1
//
#define GSRMEVT_ALIVE_WARNING            0x81080022L

//
// MessageId: GSRMEVT_SESSION_RMRES_WARNING
//
// MessageText:
//
//  SESSION MGR: RMReserveCompletionRoutine: RM Reserve failed - %1
//
#define GSRMEVT_SESSION_RMRES_WARNING    0x81080023L

//
// MessageId: GSRMEVT_SESSION_RMRES_UNEXPECTED
//
// MessageText:
//
//  SESSION MGR: RMReserveCompletionRoutine: Unexpected event - %1
//
#define GSRMEVT_SESSION_RMRES_UNEXPECTED 0x81080024L

//
// MessageId: GSRMEVT_SESSION_RMREL_WARNING
//
// MessageText:
//
//  SESSION MGR: RMReleaseCompletionRoutine: RM Release failed - %1
//
#define GSRMEVT_SESSION_RMREL_WARNING    0x81080025L

//
// MessageId: GSRMEVT_SESSION_RMREL_UNEXPECTED
//
// MessageText:
//
//  SESSION MGR: RMReleaseCompletionRoutine: Unexpected event - %1
//
#define GSRMEVT_SESSION_RMREL_UNEXPECTED 0x81080026L

//
// MessageId: GSRMEVT_SESSION_GETAPPLIST_UNEXPECTED
//
// MessageText:
//
//  SESSION MGR: GetAppListCallback: Unexpected event - %1
//
#define GSRMEVT_SESSION_GETAPPLIST_UNEXPECTED 0x81080027L

//
// MessageId: GSRMEVT_SESSION_RMREC_WARNING
//
// MessageText:
//
//  SESSION MGR: RMRecoveryCompletionRoutine: RM Recovery failed - %1
//
#define GSRMEVT_SESSION_RMREC_WARNING    0x81080028L

//
// MessageId: GSRMEVT_SESSION_RMREC_UNEXPECTED
//
// MessageText:
//
//  SESSION MGR: RMRecoveryCompletionRoutine: Unexpected event - %1
//
#define GSRMEVT_SESSION_RMREC_UNEXPECTED 0x81080029L

//
// MessageId: GSRMEVT_SESSION_WARNING
//
// MessageText:
//
//  SESSION MGR: %1
//
#define GSRMEVT_SESSION_WARNING          0x8108002AL

//
// MessageId: GSRMEVT_CLIENT_CONNECTWARNING
//
// MessageText:
//
//  ClientConnMgr::OnClientConnect: %1
//
#define GSRMEVT_CLIENT_CONNECTWARNING    0x8108002BL

//
// MessageId: GSRMEVT_CLIENT_TCPRCVWARNING
//
// MessageText:
//
//  ClientConnMgr::OnTcpMessageReceived: %1
//
#define GSRMEVT_CLIENT_TCPRCVWARNING     0x8108002CL

//
// MessageId: GSRMEVT_CLIENT_UDPRCVWARNING
//
// MessageText:
//
//  ClientConnMgr::OnUdpMessageReceived: %1
//
#define GSRMEVT_CLIENT_UDPRCVWARNING     0x8108002DL

//
// MessageId: GSRMEVT_CLIENT_WARNING
//
// MessageText:
//
//  CLIENT: %1
//
#define GSRMEVT_CLIENT_WARNING           0x8108002EL

//
// MessageId: GSRMEVT_SERVER_TCPRCVWARNING
//
// MessageText:
//
//  ServerConnMgr::OnTcpMessageReceived: %1
//
#define GSRMEVT_SERVER_TCPRCVWARNING     0x8108002FL

//
// MessageId: GSRMEVT_SERVER_UDPRCVWARNING
//
// MessageText:
//
//  ServerConnMgr::OnUdpMessageReceived: %1
//
#define GSRMEVT_SERVER_UDPRCVWARNING     0x81080030L

//
// MessageId: GSRMEVT_SERVER_WARNING
//
// MessageText:
//
//  SERVER: %1
//
#define GSRMEVT_SERVER_WARNING           0x81080031L

//
// MessageId: GSRMEVT_DNCS_CONNWARNING
//
// MessageText:
//
//  OtherSRMConnMgr::OnClientConnect: %1
//
#define GSRMEVT_DNCS_CONNWARNING         0x81080032L

//
// MessageId: GSRMEVT_DNCS_WARNING
//
// MessageText:
//
//  OtherSRM: %1
//
#define GSRMEVT_DNCS_WARNING             0x81080033L

//
// MessageId: GSRMEVT_DNCS_TCPRCVWARNING
//
// MessageText:
//
//  OtherSRMConnMgr::OnTcpMessageReceived %1
//
#define GSRMEVT_DNCS_TCPRCVWARNING       0x81080034L

//
// MessageId: GSRMEVT_DNCS_UDPRCVWARNING
//
// MessageText:
//
//  OtherSRMConnMgr::OnUdpMessageReceived: %1
//
#define GSRMEVT_DNCS_UDPRCVWARNING       0x81080035L

//
// MessageId: GSRMEVT_SESSSM_NOSERVER_WARNING
//
// MessageText:
//
//  SESSION SM: Server not connected %1
//
#define GSRMEVT_SESSSM_NOSERVER_WARNING  0x81080036L

//
// MessageId: GSRMEVT_SESSSM_RETRY_LIMIT_WARNING
//
// MessageText:
//
//  SESSION SM: Server Message Retry Limit Exceeded %1
//
#define GSRMEVT_SESSSM_RETRY_LIMIT_WARNING 0x81080037L

//
// MessageId: GSRMEVT_SESSSM_SSP_WARNING
//
// MessageText:
//
//  SESSION SM: Malformed SSP section %1
//
#define GSRMEVT_SESSSM_SSP_WARNING       0x81080038L

//
// MessageId: GSRMEVT_SESSSM_WARNING
//
// MessageText:
//
//  SESSION SM: %1
//
#define GSRMEVT_SESSSM_WARNING           0x81080039L

//
// MessageId: GSRMEVT_DISPATCH_WARNING
//
// MessageText:
//
//  Dispatcher: %1
//
#define GSRMEVT_DISPATCH_WARNING         0x8108003AL

// un-used
//
// MessageId: GSRMEVT_SESSOSM_WARNING
//
// MessageText:
//
//  OSM: %1
//
#define GSRMEVT_SESSOSM_WARNING          0x8108003BL

//
// MessageId: GSRMEVT_RM_WARNING
//
// MessageText:
//
//  RSRCMGR: %1
//
#define GSRMEVT_RM_WARNING               0x8108003CL

//
// MessageId: GSRMEVT_RSM_WARNING
//
// MessageText:
//
//  RSRC SM: %1
//
#define GSRMEVT_RSM_WARNING              0x8108003DL

//
// MessageId: GSRMEVT_REQLOG_WARNING
//
// MessageText:
//
//  ReqLog DB: %1
//
#define GSRMEVT_REQLOG_WARNING           0x8108003EL

//
// MessageId: GSRMEVT_SRMDB_WARNING
//
// MessageText:
//
//  SRM DB: %1
//
#define GSRMEVT_SRMDB_WARNING            0x8108003FL

//******************************************************************************
//*
//*     SRM Error Messages 
//*
//******************************************************************************
//
// MessageId: GSRMEVT_SYSERR
//
// MessageText:
//
//  %1
//
#define GSRMEVT_SYSERR                   0xC1080040L

//
// MessageId: GSRMEVT_INITFAILED
//
// MessageText:
//
//  SRM Failed to initialize %1, exiting..
//
#define GSRMEVT_INITFAILED               0xC1080041L

//
// MessageId: GSRMEVT_CFG_INIT
//
// MessageText:
//
//  %1 initializing configuration package
//
#define GSRMEVT_CFG_INIT                 0xC1080042L

// un-used
//
// MessageId: GSRMEVT_LOG_INIT
//
// MessageText:
//
//  %1 initializing circular logging package
//
#define GSRMEVT_LOG_INIT                 0xC1080043L

// un-used
//
// MessageId: GSRMEVT_ALIVE_ERROR
//
// MessageText:
//
//  KeepAlive Thread: %1
//
#define GSRMEVT_ALIVE_ERROR              0xC1080044L

//
// MessageId: GSRMEVT_SESSION_QUEUEING_ERROR
//
// MessageText:
//
//  SESSION MGR: Queuing Problems - %1
//
#define GSRMEVT_SESSION_QUEUEING_ERROR   0xC1080045L

//
// MessageId: GSRMEVT_SESSION_ERROR
//
// MessageText:
//
//  SESSION MGR: %1
//
#define GSRMEVT_SESSION_ERROR            0xC1080046L

//
// MessageId: GSRMEVT_PTCLIENT_CONNECTERR
//
// MessageText:
//
//  PASSTHRU CLIENT: Connection Error %1
//
#define GSRMEVT_PTCLIENT_CONNECTERR      0xC1080047L

//
// MessageId: GSRMEVT_CLIENT_DISCONN
//
// MessageText:
//
//  ClientConnMgr::OnClientDisconnect %1
//
#define GSRMEVT_CLIENT_DISCONN           0xC1080048L

//
// MessageId: GSRMEVT_CLIENT_CONNERROR
//
// MessageText:
//
//  ClientConnMgr::OnClientDisconnect %1
//
#define GSRMEVT_CLIENT_CONNERROR         0xC1080049L

//
// MessageId: GSRMEVT_CLIENT_ERROR
//
// MessageText:
//
//  CLIENT: %1
//
#define GSRMEVT_CLIENT_ERROR             0xC108004AL

//
// MessageId: GSRMEVT_SERVER_DISCONNERROR
//
// MessageText:
//
//  ServerConnMgr::OnClientDisconnect: %1
//
#define GSRMEVT_SERVER_DISCONNERROR      0xC108004BL

//
// MessageId: GSRMEVT_SERVER_ERROR
//
// MessageText:
//
//  SERVER: %1
//
#define GSRMEVT_SERVER_ERROR             0xC108004CL

//
// MessageId: GSRMEVT_DNCS_DISCONNERROR
//
// MessageText:
//
//  OtherSRMConnMgr::OnClientDisconnect: %1
//
#define GSRMEVT_DNCS_DISCONNERROR        0xC108004DL

//
// MessageId: GSRMEVT_DNCS_ERROR
//
// MessageText:
//
//  OtherSRMConnMgr:: %1
//
#define GSRMEVT_DNCS_ERROR               0xC108004EL

//
// MessageId: GSRMEVT_SESSSM_TIMER_ERROR
//
// MessageText:
//
//  SESSION SM TIMER: %1
//
#define GSRMEVT_SESSSM_TIMER_ERROR       0xC108004FL

//
// MessageId: GSRMEVT_SESSSM_WRONGEVENT_ERROR
//
// MessageText:
//
//  SESSION SM: Wrong Event Type %1
//
#define GSRMEVT_SESSSM_WRONGEVENT_ERROR  0xC1080050L

//
// MessageId: GSRMEVT_SESSSM_BADACTION_ERROR
//
// MessageText:
//
//  SESSION SM: %1
//
#define GSRMEVT_SESSSM_BADACTION_ERROR   0xC1080051L

//
// MessageId: GSRMEVT_SESSSM_SS_ERROR
//
// MessageText:
//
//  SESSION SM: %1
//
#define GSRMEVT_SESSSM_SS_ERROR          0xC1080052L

//
// MessageId: GSRMEVT_SESSSM_DUPSESSION_ERROR
//
// MessageText:
//
//  SESSION SM: %1
//
#define GSRMEVT_SESSSM_DUPSESSION_ERROR  0xC1080053L

//
// MessageId: GSRMEVT_SESSSM_SSP_ERROR
//
// MessageText:
//
//  SESSION SM: Unsupported SSP SEACHANGE section %1
//
#define GSRMEVT_SESSSM_SSP_ERROR         0xC1080054L

//
// MessageId: GSRMEVT_SESSSM_ERROR
//
// MessageText:
//
//  SESSION SM: %1
//
#define GSRMEVT_SESSSM_ERROR             0xC1080055L

//
// MessageId: GSRMEVT_SESSOSM_ERROR
//
// MessageText:
//
//  OSM: %1
//
#define GSRMEVT_SESSOSM_ERROR            0xC1080056L

//
// MessageId: GSRMEVT_RM_ERROR
//
// MessageText:
//
//  RSRCMGR: %1
//
#define GSRMEVT_RM_ERROR                 0xC1080057L

//
// MessageId: GSRMEVT_RSM_ERROR
//
// MessageText:
//
//  RSRC SM: %1
//
#define GSRMEVT_RSM_ERROR                0xC1080058L

//
// MessageId: GSRMEVT_REQLOG_ERROR
//
// MessageText:
//
//  ReqLog DB: %1
//
#define GSRMEVT_REQLOG_ERROR             0xC1080059L

//
// MessageId: GSRMEVT_REQLOG_OPEN_ERROR
//
// MessageText:
//
//  ReqLog DB: Unable to open Request Log database interface: %1
//
#define GSRMEVT_REQLOG_OPEN_ERROR        0xC108005AL

//
// MessageId: GSRMEVT_NAD_PARSE_ERROR
//
// MessageText:
//
//  NADSRV: Unable to parse NAD report from client %1: %2 [GLE=%3]
//
#define GSRMEVT_NAD_PARSE_ERROR          0xC108005BL

//
// MessageId: GSRMEVT_SRMDB_ERROR
//
// MessageText:
//
//  SRM DB: %1
//
#define GSRMEVT_SRMDB_ERROR              0xC108005CL

//******************************************************************************
//*
//* Synchronizer Api Module (SYNAPI)
//*
//******************************************************************************
//*******************************************************************************
//*
//*     Vodometer Service Messages 
//*
//*******************************************************************************
//
// MessageId: VODOMETEREVT_STARTING
//
// MessageText:
//
//  (Vodometer) Starting...
//
#define VODOMETEREVT_STARTING            0x410B0001L

//
// MessageId: VODOMETEREVT_EXITING
//
// MessageText:
//
//  (Vodometer) Exiting...
//
#define VODOMETEREVT_EXITING             0x410B0002L

//
// MessageId: VODOMETEREVT_SYSERR
//
// MessageText:
//
//  (Vodometer) System error %1
//
#define VODOMETEREVT_SYSERR              0xC10B0003L

//
// MessageId: VODOMETEREVT_STARTFAILED
//
// MessageText:
//
//  (Vodometer) Failed to start System Monitor service
//
#define VODOMETEREVT_STARTFAILED         0xC10B0004L

//
// MessageId: VODOMETEREVT_APIERR
//
// MessageText:
//
//  (Vodometer) API %1 failed, error %2
//
#define VODOMETEREVT_APIERR              0xC10B0005L

//
// MessageId: VODOMETEREVT_OUTOFMEMOERY
//
// MessageText:
//
//  (Vodometer) Out of memory
//
#define VODOMETEREVT_OUTOFMEMOERY        0xC10B0006L

//
// MessageId: VODOMETEREVT_BADMESSAGEFORMAT
//
// MessageText:
//
//  (Vodometer) Bad message format. Message from service type %1, instance %2
//
#define VODOMETEREVT_BADMESSAGEFORMAT    0xC10B0007L

//
// MessageId: VODOMETEREVT_DBERR
//
// MessageText:
//
//  (Vodometer) Database error. %1
//
#define VODOMETEREVT_DBERR               0xC10B0008L

//
// MessageId: VODOMETEREVT_RUNSTATS
//
// MessageText:
//
//  (Vodometer) CM Runstats %1
//
#define VODOMETEREVT_RUNSTATS            0x410B0009L

//
// MessageId: VODOMETEREVT_INACTIVE_COMPONENT
//
// MessageText:
//
//  (Vodometer) Service %1 was stopped, last known active at %2
//
#define VODOMETEREVT_INACTIVE_COMPONENT  0xC10B000AL

