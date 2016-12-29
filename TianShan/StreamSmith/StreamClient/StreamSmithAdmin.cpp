// **********************************************************************
//
// Copyright (c) 2003-2007 ZeroC, Inc. All rights reserved.
//
// This copy of Ice is licensed to you under the terms described in the
// ICE_LICENSE file included in this distribution.
//
// **********************************************************************

// Ice version 3.2.1
// Generated from file `StreamSmithAdmin.ice'

#include <StreamSmithAdmin.h>
#include <Ice/LocalException.h>
#include <Ice/ObjectFactory.h>
#include <Ice/BasicStream.h>
#include <Ice/Object.h>
#include <IceUtil/Iterator.h>
#include <IceUtil/ScopedArray.h>

#ifndef ICE_IGNORE_VERSION
#   if ICE_INT_VERSION / 100 != 302
#       error Ice version mismatch!
#   endif
#   if ICE_INT_VERSION % 100 > 50
#       error Beta header file detected
#   endif
#   if ICE_INT_VERSION % 100 < 1
#       error Ice patch level mismatch!
#   endif
#endif

static const ::std::string __TianShanIce__Streamer__PlaylistEx__getAttr_name = "getAttr";

static const ::std::string __TianShanIce__Streamer__PlaylistEx__updateAttr_name = "updateAttr";

static const ::std::string __TianShanIce__Streamer__PlaylistEx__attachSession_name = "attachSession";

static const ::std::string __TianShanIce__Streamer__PlaylistEx__setDestination_name = "setDestination";

static const ::std::string __TianShanIce__Streamer__PlaylistEx__setDestMac_name = "setDestMac";

static const ::std::string __TianShanIce__Streamer__PlaylistEx__setSourceStrmPort_name = "setSourceStrmPort";

static const ::std::string __TianShanIce__Streamer__PlaylistEx__setPID_name = "setPID";

static const ::std::string __TianShanIce__Streamer__PlaylistEx__onTimer_name = "onTimer";

static const ::std::string __TianShanIce__Streamer__PlaylistItem__destroy_name = "destroy";

static const ::std::string __TianShanIce__Streamer__PlaylistItem__getAttr_name = "getAttr";

static const ::std::string __TianShanIce__Streamer__PlaylistItem__updateAttr_name = "updateAttr";

static const ::std::string __TianShanIce__Streamer__StreamSmithAdmin__listPlaylists_name = "listPlaylists";

static const ::std::string __TianShanIce__Streamer__StreamSmithAdmin__openPlaylist_name = "openPlaylist";

static const ::std::string __TianShanIce__Streamer__StreamSmithAdmin__createStreamBatch_name = "createStreamBatch";

static const ::std::string __TianShanIce__Streamer__StreamSmithAdmin__ShowMemory_name = "ShowMemory";

void
IceInternal::incRef(::TianShanIce::Streamer::PlaylistEx* p)
{
    p->__incRef();
}

void
IceInternal::decRef(::TianShanIce::Streamer::PlaylistEx* p)
{
    p->__decRef();
}

void
IceInternal::incRef(::IceProxy::TianShanIce::Streamer::PlaylistEx* p)
{
    p->__incRef();
}

void
IceInternal::decRef(::IceProxy::TianShanIce::Streamer::PlaylistEx* p)
{
    p->__decRef();
}

void
IceInternal::incRef(::TianShanIce::Streamer::PlaylistItem* p)
{
    p->__incRef();
}

void
IceInternal::decRef(::TianShanIce::Streamer::PlaylistItem* p)
{
    p->__decRef();
}

void
IceInternal::incRef(::IceProxy::TianShanIce::Streamer::PlaylistItem* p)
{
    p->__incRef();
}

void
IceInternal::decRef(::IceProxy::TianShanIce::Streamer::PlaylistItem* p)
{
    p->__decRef();
}

void
IceInternal::incRef(::TianShanIce::Streamer::StreamSmithAdmin* p)
{
    p->__incRef();
}

void
IceInternal::decRef(::TianShanIce::Streamer::StreamSmithAdmin* p)
{
    p->__decRef();
}

void
IceInternal::incRef(::IceProxy::TianShanIce::Streamer::StreamSmithAdmin* p)
{
    p->__incRef();
}

void
IceInternal::decRef(::IceProxy::TianShanIce::Streamer::StreamSmithAdmin* p)
{
    p->__decRef();
}

void
TianShanIce::Streamer::__write(::IceInternal::BasicStream* __os, const ::TianShanIce::Streamer::PlaylistExPrx& v)
{
    __os->write(::Ice::ObjectPrx(v));
}

void
TianShanIce::Streamer::__read(::IceInternal::BasicStream* __is, ::TianShanIce::Streamer::PlaylistExPrx& v)
{
    ::Ice::ObjectPrx proxy;
    __is->read(proxy);
    if(!proxy)
    {
        v = 0;
    }
    else
    {
        v = new ::IceProxy::TianShanIce::Streamer::PlaylistEx;
        v->__copyFrom(proxy);
    }
}

void
TianShanIce::Streamer::__write(::IceInternal::BasicStream* __os, const ::TianShanIce::Streamer::PlaylistExPtr& v)
{
    __os->write(::Ice::ObjectPtr(v));
}

void
TianShanIce::Streamer::__write(::IceInternal::BasicStream* __os, const ::TianShanIce::Streamer::PlaylistItemPrx& v)
{
    __os->write(::Ice::ObjectPrx(v));
}

void
TianShanIce::Streamer::__read(::IceInternal::BasicStream* __is, ::TianShanIce::Streamer::PlaylistItemPrx& v)
{
    ::Ice::ObjectPrx proxy;
    __is->read(proxy);
    if(!proxy)
    {
        v = 0;
    }
    else
    {
        v = new ::IceProxy::TianShanIce::Streamer::PlaylistItem;
        v->__copyFrom(proxy);
    }
}

void
TianShanIce::Streamer::__write(::IceInternal::BasicStream* __os, const ::TianShanIce::Streamer::PlaylistItemPtr& v)
{
    __os->write(::Ice::ObjectPtr(v));
}

void
TianShanIce::Streamer::__write(::IceInternal::BasicStream* __os, const ::TianShanIce::Streamer::StreamSmithAdminPrx& v)
{
    __os->write(::Ice::ObjectPrx(v));
}

void
TianShanIce::Streamer::__read(::IceInternal::BasicStream* __is, ::TianShanIce::Streamer::StreamSmithAdminPrx& v)
{
    ::Ice::ObjectPrx proxy;
    __is->read(proxy);
    if(!proxy)
    {
        v = 0;
    }
    else
    {
        v = new ::IceProxy::TianShanIce::Streamer::StreamSmithAdmin;
        v->__copyFrom(proxy);
    }
}

void
TianShanIce::Streamer::__write(::IceInternal::BasicStream* __os, const ::TianShanIce::Streamer::StreamSmithAdminPtr& v)
{
    __os->write(::Ice::ObjectPtr(v));
}

bool
TianShanIce::Streamer::PlaylistAttr::operator==(const PlaylistAttr& __rhs) const
{
    return !operator!=(__rhs);
}

bool
TianShanIce::Streamer::PlaylistAttr::operator!=(const PlaylistAttr& __rhs) const
{
    if(this == &__rhs)
    {
        return false;
    }
    if(Guid != __rhs.Guid)
    {
        return true;
    }
    if(StreamSmithSiteName != __rhs.StreamSmithSiteName)
    {
        return true;
    }
    if(ResourceGuid != __rhs.ResourceGuid)
    {
        return true;
    }
    if(ClientSessionID != __rhs.ClientSessionID)
    {
        return true;
    }
    if(endPoint != __rhs.endPoint)
    {
        return true;
    }
    if(MaxRate != __rhs.MaxRate)
    {
        return true;
    }
    if(MinRate != __rhs.MinRate)
    {
        return true;
    }
    if(NowRate != __rhs.NowRate)
    {
        return true;
    }
    if(destIP != __rhs.destIP)
    {
        return true;
    }
    if(destPort != __rhs.destPort)
    {
        return true;
    }
    if(destMac != __rhs.destMac)
    {
        return true;
    }
    if(vstrmPort != __rhs.vstrmPort)
    {
        return true;
    }
    if(programNumber != __rhs.programNumber)
    {
        return true;
    }
    if(playlistState != __rhs.playlistState)
    {
        return true;
    }
    if(currentCtrlNum != __rhs.currentCtrlNum)
    {
        return true;
    }
    if(vstrmSessID != __rhs.vstrmSessID)
    {
        return true;
    }
    if(streamPID != __rhs.streamPID)
    {
        return true;
    }
    if(property != __rhs.property)
    {
        return true;
    }
    return false;
}

bool
TianShanIce::Streamer::PlaylistAttr::operator<(const PlaylistAttr& __rhs) const
{
    if(this == &__rhs)
    {
        return false;
    }
    if(Guid < __rhs.Guid)
    {
        return true;
    }
    else if(__rhs.Guid < Guid)
    {
        return false;
    }
    if(StreamSmithSiteName < __rhs.StreamSmithSiteName)
    {
        return true;
    }
    else if(__rhs.StreamSmithSiteName < StreamSmithSiteName)
    {
        return false;
    }
    if(ResourceGuid < __rhs.ResourceGuid)
    {
        return true;
    }
    else if(__rhs.ResourceGuid < ResourceGuid)
    {
        return false;
    }
    if(ClientSessionID < __rhs.ClientSessionID)
    {
        return true;
    }
    else if(__rhs.ClientSessionID < ClientSessionID)
    {
        return false;
    }
    if(endPoint < __rhs.endPoint)
    {
        return true;
    }
    else if(__rhs.endPoint < endPoint)
    {
        return false;
    }
    if(MaxRate < __rhs.MaxRate)
    {
        return true;
    }
    else if(__rhs.MaxRate < MaxRate)
    {
        return false;
    }
    if(MinRate < __rhs.MinRate)
    {
        return true;
    }
    else if(__rhs.MinRate < MinRate)
    {
        return false;
    }
    if(NowRate < __rhs.NowRate)
    {
        return true;
    }
    else if(__rhs.NowRate < NowRate)
    {
        return false;
    }
    if(destIP < __rhs.destIP)
    {
        return true;
    }
    else if(__rhs.destIP < destIP)
    {
        return false;
    }
    if(destPort < __rhs.destPort)
    {
        return true;
    }
    else if(__rhs.destPort < destPort)
    {
        return false;
    }
    if(destMac < __rhs.destMac)
    {
        return true;
    }
    else if(__rhs.destMac < destMac)
    {
        return false;
    }
    if(vstrmPort < __rhs.vstrmPort)
    {
        return true;
    }
    else if(__rhs.vstrmPort < vstrmPort)
    {
        return false;
    }
    if(programNumber < __rhs.programNumber)
    {
        return true;
    }
    else if(__rhs.programNumber < programNumber)
    {
        return false;
    }
    if(playlistState < __rhs.playlistState)
    {
        return true;
    }
    else if(__rhs.playlistState < playlistState)
    {
        return false;
    }
    if(currentCtrlNum < __rhs.currentCtrlNum)
    {
        return true;
    }
    else if(__rhs.currentCtrlNum < currentCtrlNum)
    {
        return false;
    }
    if(vstrmSessID < __rhs.vstrmSessID)
    {
        return true;
    }
    else if(__rhs.vstrmSessID < vstrmSessID)
    {
        return false;
    }
    if(streamPID < __rhs.streamPID)
    {
        return true;
    }
    else if(__rhs.streamPID < streamPID)
    {
        return false;
    }
    if(property < __rhs.property)
    {
        return true;
    }
    else if(__rhs.property < property)
    {
        return false;
    }
    return false;
}

void
TianShanIce::Streamer::PlaylistAttr::__write(::IceInternal::BasicStream* __os) const
{
    __os->write(Guid);
    __os->write(StreamSmithSiteName);
    __os->write(ResourceGuid);
    __os->write(ClientSessionID);
    __os->write(endPoint);
    __os->write(MaxRate);
    __os->write(MinRate);
    __os->write(NowRate);
    __os->write(destIP);
    __os->write(destPort);
    __os->write(destMac);
    __os->write(vstrmPort);
    __os->write(programNumber);
    __os->write(playlistState);
    __os->write(currentCtrlNum);
    __os->write(vstrmSessID);
    __os->write(streamPID);
    ::TianShanIce::__write(__os, property, ::TianShanIce::__U__Properties());
}

void
TianShanIce::Streamer::PlaylistAttr::__read(::IceInternal::BasicStream* __is)
{
    __is->read(Guid);
    __is->read(StreamSmithSiteName);
    __is->read(ResourceGuid);
    __is->read(ClientSessionID);
    __is->read(endPoint);
    __is->read(MaxRate);
    __is->read(MinRate);
    __is->read(NowRate);
    __is->read(destIP);
    __is->read(destPort);
    __is->read(destMac);
    __is->read(vstrmPort);
    __is->read(programNumber);
    __is->read(playlistState);
    __is->read(currentCtrlNum);
    __is->read(vstrmSessID);
    __is->read(streamPID);
    ::TianShanIce::__read(__is, property, ::TianShanIce::__U__Properties());
}

void
TianShanIce::Streamer::__addObject(const PlaylistExPtr& p, ::IceInternal::GCCountMap& c)
{
    p->__addObject(c);
}

bool
TianShanIce::Streamer::__usesClasses(const PlaylistExPtr& p)
{
    return p->__usesClasses();
}

void
TianShanIce::Streamer::__decRefUnsafe(const PlaylistExPtr& p)
{
    p->__decRefUnsafe();
}

void
TianShanIce::Streamer::__clearHandleUnsafe(PlaylistExPtr& p)
{
    p.__clearHandleUnsafe();
}

bool
TianShanIce::Streamer::PlaylistItemAttr::operator==(const PlaylistItemAttr& __rhs) const
{
    return !operator!=(__rhs);
}

bool
TianShanIce::Streamer::PlaylistItemAttr::operator!=(const PlaylistItemAttr& __rhs) const
{
    if(this == &__rhs)
    {
        return false;
    }
    if(PlaylistGuid != __rhs.PlaylistGuid)
    {
        return true;
    }
    if(itemSetupInfo != __rhs.itemSetupInfo)
    {
        return true;
    }
    if(InternalCtrlNum != __rhs.InternalCtrlNum)
    {
        return true;
    }
    if(CtrlNumber != __rhs.CtrlNumber)
    {
        return true;
    }
    if(vStrmSessID != __rhs.vStrmSessID)
    {
        return true;
    }
    if(SessState != __rhs.SessState)
    {
        return true;
    }
    if(property != __rhs.property)
    {
        return true;
    }
    return false;
}

bool
TianShanIce::Streamer::PlaylistItemAttr::operator<(const PlaylistItemAttr& __rhs) const
{
    if(this == &__rhs)
    {
        return false;
    }
    if(PlaylistGuid < __rhs.PlaylistGuid)
    {
        return true;
    }
    else if(__rhs.PlaylistGuid < PlaylistGuid)
    {
        return false;
    }
    if(itemSetupInfo < __rhs.itemSetupInfo)
    {
        return true;
    }
    else if(__rhs.itemSetupInfo < itemSetupInfo)
    {
        return false;
    }
    if(InternalCtrlNum < __rhs.InternalCtrlNum)
    {
        return true;
    }
    else if(__rhs.InternalCtrlNum < InternalCtrlNum)
    {
        return false;
    }
    if(CtrlNumber < __rhs.CtrlNumber)
    {
        return true;
    }
    else if(__rhs.CtrlNumber < CtrlNumber)
    {
        return false;
    }
    if(vStrmSessID < __rhs.vStrmSessID)
    {
        return true;
    }
    else if(__rhs.vStrmSessID < vStrmSessID)
    {
        return false;
    }
    if(SessState < __rhs.SessState)
    {
        return true;
    }
    else if(__rhs.SessState < SessState)
    {
        return false;
    }
    if(property < __rhs.property)
    {
        return true;
    }
    else if(__rhs.property < property)
    {
        return false;
    }
    return false;
}

void
TianShanIce::Streamer::PlaylistItemAttr::__write(::IceInternal::BasicStream* __os) const
{
    __os->write(PlaylistGuid);
    itemSetupInfo.__write(__os);
    __os->write(InternalCtrlNum);
    __os->write(CtrlNumber);
    __os->write(vStrmSessID);
    __os->write(SessState);
    ::TianShanIce::__write(__os, property, ::TianShanIce::__U__Properties());
}

void
TianShanIce::Streamer::PlaylistItemAttr::__read(::IceInternal::BasicStream* __is)
{
    __is->read(PlaylistGuid);
    itemSetupInfo.__read(__is);
    __is->read(InternalCtrlNum);
    __is->read(CtrlNumber);
    __is->read(vStrmSessID);
    __is->read(SessState);
    ::TianShanIce::__read(__is, property, ::TianShanIce::__U__Properties());
}

void
TianShanIce::Streamer::__addObject(const PlaylistItemPtr& p, ::IceInternal::GCCountMap& c)
{
    p->__addObject(c);
}

bool
TianShanIce::Streamer::__usesClasses(const PlaylistItemPtr& p)
{
    return p->__usesClasses();
}

void
TianShanIce::Streamer::__decRefUnsafe(const PlaylistItemPtr& p)
{
    p->__decRefUnsafe();
}

void
TianShanIce::Streamer::__clearHandleUnsafe(PlaylistItemPtr& p)
{
    p.__clearHandleUnsafe();
}

void
TianShanIce::Streamer::__write(::IceInternal::BasicStream* __os, const ::TianShanIce::Streamer::PlaylistItemSetupInfo* begin, const ::TianShanIce::Streamer::PlaylistItemSetupInfo* end, ::TianShanIce::Streamer::__U__PlaylistItemInfoS)
{
    ::Ice::Int size = static_cast< ::Ice::Int>(end - begin);
    __os->writeSize(size);
    for(int i = 0; i < size; ++i)
    {
        begin[i].__write(__os);
    }
}

void
TianShanIce::Streamer::__read(::IceInternal::BasicStream* __is, ::TianShanIce::Streamer::PlaylistItemInfoS& v, ::TianShanIce::Streamer::__U__PlaylistItemInfoS)
{
    ::Ice::Int sz;
    __is->readSize(sz);
    __is->startSeq(sz, 37);
    v.resize(sz);
    for(int i = 0; i < sz; ++i)
    {
        v[i].__read(__is);
        __is->checkSeq();
        __is->endElement();
    }
    __is->endSeq(sz);
}

bool
TianShanIce::Streamer::StreamDuplicateReq::operator==(const StreamDuplicateReq& __rhs) const
{
    return !operator!=(__rhs);
}

bool
TianShanIce::Streamer::StreamDuplicateReq::operator!=(const StreamDuplicateReq& __rhs) const
{
    if(this == &__rhs)
    {
        return false;
    }
    if(resources != __rhs.resources)
    {
        return true;
    }
    if(properties != __rhs.properties)
    {
        return true;
    }
    if(state != __rhs.state)
    {
        return true;
    }
    if(timeoffset != __rhs.timeoffset)
    {
        return true;
    }
    if(scale != __rhs.scale)
    {
        return true;
    }
    if(items != __rhs.items)
    {
        return true;
    }
    if(reqTag != __rhs.reqTag)
    {
        return true;
    }
    return false;
}

bool
TianShanIce::Streamer::StreamDuplicateReq::operator<(const StreamDuplicateReq& __rhs) const
{
    if(this == &__rhs)
    {
        return false;
    }
    if(resources < __rhs.resources)
    {
        return true;
    }
    else if(__rhs.resources < resources)
    {
        return false;
    }
    if(properties < __rhs.properties)
    {
        return true;
    }
    else if(__rhs.properties < properties)
    {
        return false;
    }
    if(state < __rhs.state)
    {
        return true;
    }
    else if(__rhs.state < state)
    {
        return false;
    }
    if(timeoffset < __rhs.timeoffset)
    {
        return true;
    }
    else if(__rhs.timeoffset < timeoffset)
    {
        return false;
    }
    if(scale < __rhs.scale)
    {
        return true;
    }
    else if(__rhs.scale < scale)
    {
        return false;
    }
    if(items < __rhs.items)
    {
        return true;
    }
    else if(__rhs.items < items)
    {
        return false;
    }
    if(reqTag < __rhs.reqTag)
    {
        return true;
    }
    else if(__rhs.reqTag < reqTag)
    {
        return false;
    }
    return false;
}

void
TianShanIce::Streamer::StreamDuplicateReq::__write(::IceInternal::BasicStream* __os) const
{
    ::TianShanIce::SRM::__write(__os, resources, ::TianShanIce::SRM::__U__ResourceMap());
    ::TianShanIce::__write(__os, properties, ::TianShanIce::__U__Properties());
    ::TianShanIce::Streamer::__write(__os, state);
    __os->write(timeoffset);
    __os->write(scale);
    if(items.size() == 0)
    {
        __os->writeSize(0);
    }
    else
    {
        ::TianShanIce::Streamer::__write(__os, &items[0], &items[0] + items.size(), ::TianShanIce::Streamer::__U__PlaylistItemInfoS());
    }
    __os->write(reqTag);
}

void
TianShanIce::Streamer::StreamDuplicateReq::__read(::IceInternal::BasicStream* __is)
{
    ::TianShanIce::SRM::__read(__is, resources, ::TianShanIce::SRM::__U__ResourceMap());
    ::TianShanIce::__read(__is, properties, ::TianShanIce::__U__Properties());
    ::TianShanIce::Streamer::__read(__is, state);
    __is->read(timeoffset);
    __is->read(scale);
    ::TianShanIce::Streamer::__read(__is, items, ::TianShanIce::Streamer::__U__PlaylistItemInfoS());
    __is->read(reqTag);
}

bool
TianShanIce::Streamer::StreamDuplicateResp::operator==(const StreamDuplicateResp& __rhs) const
{
    return !operator!=(__rhs);
}

bool
TianShanIce::Streamer::StreamDuplicateResp::operator!=(const StreamDuplicateResp& __rhs) const
{
    if(this == &__rhs)
    {
        return false;
    }
    if(reqTag != __rhs.reqTag)
    {
        return true;
    }
    if(streamSessionId != __rhs.streamSessionId)
    {
        return true;
    }
    if(state != __rhs.state)
    {
        return true;
    }
    if(timeoffset != __rhs.timeoffset)
    {
        return true;
    }
    if(scale != __rhs.scale)
    {
        return true;
    }
    if(streamSession != __rhs.streamSession)
    {
        return true;
    }
    return false;
}

bool
TianShanIce::Streamer::StreamDuplicateResp::operator<(const StreamDuplicateResp& __rhs) const
{
    if(this == &__rhs)
    {
        return false;
    }
    if(reqTag < __rhs.reqTag)
    {
        return true;
    }
    else if(__rhs.reqTag < reqTag)
    {
        return false;
    }
    if(streamSessionId < __rhs.streamSessionId)
    {
        return true;
    }
    else if(__rhs.streamSessionId < streamSessionId)
    {
        return false;
    }
    if(state < __rhs.state)
    {
        return true;
    }
    else if(__rhs.state < state)
    {
        return false;
    }
    if(timeoffset < __rhs.timeoffset)
    {
        return true;
    }
    else if(__rhs.timeoffset < timeoffset)
    {
        return false;
    }
    if(scale < __rhs.scale)
    {
        return true;
    }
    else if(__rhs.scale < scale)
    {
        return false;
    }
    if(streamSession < __rhs.streamSession)
    {
        return true;
    }
    else if(__rhs.streamSession < streamSession)
    {
        return false;
    }
    return false;
}

void
TianShanIce::Streamer::StreamDuplicateResp::__write(::IceInternal::BasicStream* __os) const
{
    __os->write(reqTag);
    __os->write(streamSessionId);
    ::TianShanIce::Streamer::__write(__os, state);
    __os->write(timeoffset);
    __os->write(scale);
    ::TianShanIce::Streamer::__write(__os, streamSession);
}

void
TianShanIce::Streamer::StreamDuplicateResp::__read(::IceInternal::BasicStream* __is)
{
    __is->read(reqTag);
    __is->read(streamSessionId);
    ::TianShanIce::Streamer::__read(__is, state);
    __is->read(timeoffset);
    __is->read(scale);
    ::TianShanIce::Streamer::__read(__is, streamSession);
}

void
TianShanIce::Streamer::__write(::IceInternal::BasicStream* __os, const ::TianShanIce::Streamer::StreamDuplicateReq* begin, const ::TianShanIce::Streamer::StreamDuplicateReq* end, ::TianShanIce::Streamer::__U__StreamBatchRequest)
{
    ::Ice::Int size = static_cast< ::Ice::Int>(end - begin);
    __os->writeSize(size);
    for(int i = 0; i < size; ++i)
    {
        begin[i].__write(__os);
    }
}

void
TianShanIce::Streamer::__read(::IceInternal::BasicStream* __is, ::TianShanIce::Streamer::StreamBatchRequest& v, ::TianShanIce::Streamer::__U__StreamBatchRequest)
{
    ::Ice::Int sz;
    __is->readSize(sz);
    __is->startSeq(sz, 13);
    v.resize(sz);
    for(int i = 0; i < sz; ++i)
    {
        v[i].__read(__is);
        __is->checkSeq();
        __is->endElement();
    }
    __is->endSeq(sz);
}

void
TianShanIce::Streamer::__write(::IceInternal::BasicStream* __os, const ::TianShanIce::Streamer::StreamDuplicateResp* begin, const ::TianShanIce::Streamer::StreamDuplicateResp* end, ::TianShanIce::Streamer::__U__StreamBatchResponse)
{
    ::Ice::Int size = static_cast< ::Ice::Int>(end - begin);
    __os->writeSize(size);
    for(int i = 0; i < size; ++i)
    {
        begin[i].__write(__os);
    }
}

void
TianShanIce::Streamer::__read(::IceInternal::BasicStream* __is, ::TianShanIce::Streamer::StreamBatchResponse& v, ::TianShanIce::Streamer::__U__StreamBatchResponse)
{
    ::Ice::Int sz;
    __is->readSize(sz);
    __is->startSeq(sz, 13);
    v.resize(sz);
    for(int i = 0; i < sz; ++i)
    {
        v[i].__read(__is);
        __is->checkSeq();
        __is->endElement();
    }
    __is->endSeq(sz);
}

void
TianShanIce::Streamer::__addObject(const StreamSmithAdminPtr& p, ::IceInternal::GCCountMap& c)
{
    p->__addObject(c);
}

bool
TianShanIce::Streamer::__usesClasses(const StreamSmithAdminPtr& p)
{
    return p->__usesClasses();
}

void
TianShanIce::Streamer::__decRefUnsafe(const StreamSmithAdminPtr& p)
{
    p->__decRefUnsafe();
}

void
TianShanIce::Streamer::__clearHandleUnsafe(StreamSmithAdminPtr& p)
{
    p.__clearHandleUnsafe();
}

void
TianShanIce::Streamer::AMI_StreamSmithAdmin_createStreamBatch::__invoke(const ::TianShanIce::Streamer::StreamSmithAdminPrx& __prx, const ::TianShanIce::Streamer::StreamBatchRequest& req, const ::Ice::Context* __ctx)
{
    try
    {
        __prepare(__prx, __TianShanIce__Streamer__StreamSmithAdmin__createStreamBatch_name, ::Ice::Normal, __ctx);
        if(req.size() == 0)
        {
            __os->writeSize(0);
        }
        else
        {
            ::TianShanIce::Streamer::__write(__os, &req[0], &req[0] + req.size(), ::TianShanIce::Streamer::__U__StreamBatchRequest());
        }
        __os->endWriteEncaps();
    }
    catch(const ::Ice::LocalException& __ex)
    {
        __finished(__ex);
        return;
    }
    __send();
}

void
TianShanIce::Streamer::AMI_StreamSmithAdmin_createStreamBatch::__response(bool __ok)
{
    ::TianShanIce::Streamer::StreamBatchResponse __ret;
    try
    {
        if(!__ok)
        {
            try
            {
                __is->throwException();
            }
            catch(const ::TianShanIce::ServerError& __ex)
            {
                ice_exception(__ex);
                return;
            }
            catch(const ::Ice::UserException& __ex)
            {
                throw ::Ice::UnknownUserException(__FILE__, __LINE__, __ex.ice_name());
            }
        }
        ::TianShanIce::Streamer::__read(__is, __ret, ::TianShanIce::Streamer::__U__StreamBatchResponse());
    }
    catch(const ::Ice::LocalException& __ex)
    {
        __finished(__ex);
        return;
    }
    ice_response(__ret);
}

IceAsync::TianShanIce::Streamer::AMD_StreamSmithAdmin_createStreamBatch::AMD_StreamSmithAdmin_createStreamBatch(::IceInternal::Incoming& in) :
    ::IceInternal::IncomingAsync(in)
{
}

void
IceAsync::TianShanIce::Streamer::AMD_StreamSmithAdmin_createStreamBatch::ice_response(const ::TianShanIce::Streamer::StreamBatchResponse& __ret)
{
    try
    {
        ::IceInternal::BasicStream* __os = this->__os();
        if(__ret.size() == 0)
        {
            __os->writeSize(0);
        }
        else
        {
            ::TianShanIce::Streamer::__write(__os, &__ret[0], &__ret[0] + __ret.size(), ::TianShanIce::Streamer::__U__StreamBatchResponse());
        }
    }
    catch(const ::Ice::Exception& __ex)
    {
        __exception(__ex);
        return;
    }
    __response(true);
}

void
IceAsync::TianShanIce::Streamer::AMD_StreamSmithAdmin_createStreamBatch::ice_exception(const ::Ice::Exception& ex)
{
    try
    {
        ex.ice_throw();
    }
    catch(const ::TianShanIce::ServerError& __ex)
    {
        __os()->write(__ex);
        __response(false);
    }
    catch(const ::Ice::Exception& __ex)
    {
        __exception(__ex);
    }
}

void
IceAsync::TianShanIce::Streamer::AMD_StreamSmithAdmin_createStreamBatch::ice_exception(const ::std::exception& ex)
{
    __exception(ex);
}

void
IceAsync::TianShanIce::Streamer::AMD_StreamSmithAdmin_createStreamBatch::ice_exception()
{
    __exception();
}

::TianShanIce::Streamer::PlaylistAttr
IceProxy::TianShanIce::Streamer::PlaylistEx::getAttr(const ::Ice::Context* __ctx)
{
    int __cnt = 0;
    while(true)
    {
        ::IceInternal::Handle< ::IceDelegate::Ice::Object> __delBase;
        try
        {
            __checkTwowayOnly(__TianShanIce__Streamer__PlaylistEx__getAttr_name);
            __delBase = __getDelegate();
            ::IceDelegate::TianShanIce::Streamer::PlaylistEx* __del = dynamic_cast< ::IceDelegate::TianShanIce::Streamer::PlaylistEx*>(__delBase.get());
            return __del->getAttr(__ctx);
        }
        catch(const ::IceInternal::LocalExceptionWrapper& __ex)
        {
            __handleExceptionWrapper(__delBase, __ex);
        }
        catch(const ::Ice::LocalException& __ex)
        {
            __handleException(__delBase, __ex, __cnt);
        }
    }
}

void
IceProxy::TianShanIce::Streamer::PlaylistEx::updateAttr(const ::TianShanIce::Streamer::PlaylistAttr& attr, const ::Ice::Context* __ctx)
{
    int __cnt = 0;
    while(true)
    {
        ::IceInternal::Handle< ::IceDelegate::Ice::Object> __delBase;
        try
        {
            __delBase = __getDelegate();
            ::IceDelegate::TianShanIce::Streamer::PlaylistEx* __del = dynamic_cast< ::IceDelegate::TianShanIce::Streamer::PlaylistEx*>(__delBase.get());
            __del->updateAttr(attr, __ctx);
            return;
        }
        catch(const ::IceInternal::LocalExceptionWrapper& __ex)
        {
            __handleExceptionWrapper(__delBase, __ex);
        }
        catch(const ::Ice::LocalException& __ex)
        {
            __handleException(__delBase, __ex, __cnt);
        }
    }
}

void
IceProxy::TianShanIce::Streamer::PlaylistEx::attachSession(const ::TianShanIce::SRM::SessionPrx& sess, const ::Ice::Context* __ctx)
{
    int __cnt = 0;
    while(true)
    {
        ::IceInternal::Handle< ::IceDelegate::Ice::Object> __delBase;
        try
        {
            __delBase = __getDelegate();
            ::IceDelegate::TianShanIce::Streamer::PlaylistEx* __del = dynamic_cast< ::IceDelegate::TianShanIce::Streamer::PlaylistEx*>(__delBase.get());
            __del->attachSession(sess, __ctx);
            return;
        }
        catch(const ::IceInternal::LocalExceptionWrapper& __ex)
        {
            __handleExceptionWrapper(__delBase, __ex);
        }
        catch(const ::Ice::LocalException& __ex)
        {
            __handleException(__delBase, __ex, __cnt);
        }
    }
}

void
IceProxy::TianShanIce::Streamer::PlaylistEx::setDestination(const ::std::string& destIP, ::Ice::Int port, const ::Ice::Context* __ctx)
{
    int __cnt = 0;
    while(true)
    {
        ::IceInternal::Handle< ::IceDelegate::Ice::Object> __delBase;
        try
        {
            __delBase = __getDelegate();
            ::IceDelegate::TianShanIce::Streamer::PlaylistEx* __del = dynamic_cast< ::IceDelegate::TianShanIce::Streamer::PlaylistEx*>(__delBase.get());
            __del->setDestination(destIP, port, __ctx);
            return;
        }
        catch(const ::IceInternal::LocalExceptionWrapper& __ex)
        {
            __handleExceptionWrapper(__delBase, __ex);
        }
        catch(const ::Ice::LocalException& __ex)
        {
            __handleException(__delBase, __ex, __cnt);
        }
    }
}

void
IceProxy::TianShanIce::Streamer::PlaylistEx::setDestMac(const ::std::string& strMac, const ::Ice::Context* __ctx)
{
    int __cnt = 0;
    while(true)
    {
        ::IceInternal::Handle< ::IceDelegate::Ice::Object> __delBase;
        try
        {
            __delBase = __getDelegate();
            ::IceDelegate::TianShanIce::Streamer::PlaylistEx* __del = dynamic_cast< ::IceDelegate::TianShanIce::Streamer::PlaylistEx*>(__delBase.get());
            __del->setDestMac(strMac, __ctx);
            return;
        }
        catch(const ::IceInternal::LocalExceptionWrapper& __ex)
        {
            __handleExceptionWrapper(__delBase, __ex);
        }
        catch(const ::Ice::LocalException& __ex)
        {
            __handleException(__delBase, __ex, __cnt);
        }
    }
}

void
IceProxy::TianShanIce::Streamer::PlaylistEx::setSourceStrmPort(::Ice::Int port, const ::Ice::Context* __ctx)
{
    int __cnt = 0;
    while(true)
    {
        ::IceInternal::Handle< ::IceDelegate::Ice::Object> __delBase;
        try
        {
            __delBase = __getDelegate();
            ::IceDelegate::TianShanIce::Streamer::PlaylistEx* __del = dynamic_cast< ::IceDelegate::TianShanIce::Streamer::PlaylistEx*>(__delBase.get());
            __del->setSourceStrmPort(port, __ctx);
            return;
        }
        catch(const ::IceInternal::LocalExceptionWrapper& __ex)
        {
            __handleExceptionWrapper(__delBase, __ex);
        }
        catch(const ::Ice::LocalException& __ex)
        {
            __handleException(__delBase, __ex, __cnt);
        }
    }
}

void
IceProxy::TianShanIce::Streamer::PlaylistEx::setPID(::Ice::Int pid, const ::Ice::Context* __ctx)
{
    int __cnt = 0;
    while(true)
    {
        ::IceInternal::Handle< ::IceDelegate::Ice::Object> __delBase;
        try
        {
            __delBase = __getDelegate();
            ::IceDelegate::TianShanIce::Streamer::PlaylistEx* __del = dynamic_cast< ::IceDelegate::TianShanIce::Streamer::PlaylistEx*>(__delBase.get());
            __del->setPID(pid, __ctx);
            return;
        }
        catch(const ::IceInternal::LocalExceptionWrapper& __ex)
        {
            __handleExceptionWrapper(__delBase, __ex);
        }
        catch(const ::Ice::LocalException& __ex)
        {
            __handleException(__delBase, __ex, __cnt);
        }
    }
}

void
IceProxy::TianShanIce::Streamer::PlaylistEx::onTimer(const ::Ice::Context* __ctx)
{
    int __cnt = 0;
    while(true)
    {
        ::IceInternal::Handle< ::IceDelegate::Ice::Object> __delBase;
        try
        {
            __delBase = __getDelegate();
            ::IceDelegate::TianShanIce::Streamer::PlaylistEx* __del = dynamic_cast< ::IceDelegate::TianShanIce::Streamer::PlaylistEx*>(__delBase.get());
            __del->onTimer(__ctx);
            return;
        }
        catch(const ::IceInternal::LocalExceptionWrapper& __ex)
        {
            __handleExceptionWrapper(__delBase, __ex);
        }
        catch(const ::Ice::LocalException& __ex)
        {
            __handleException(__delBase, __ex, __cnt);
        }
    }
}

const ::std::string&
IceProxy::TianShanIce::Streamer::PlaylistEx::ice_staticId()
{
    return ::TianShanIce::Streamer::PlaylistEx::ice_staticId();
}

::IceInternal::Handle< ::IceDelegateM::Ice::Object>
IceProxy::TianShanIce::Streamer::PlaylistEx::__createDelegateM()
{
    return ::IceInternal::Handle< ::IceDelegateM::Ice::Object>(new ::IceDelegateM::TianShanIce::Streamer::PlaylistEx);
}

::IceInternal::Handle< ::IceDelegateD::Ice::Object>
IceProxy::TianShanIce::Streamer::PlaylistEx::__createDelegateD()
{
    return ::IceInternal::Handle< ::IceDelegateD::Ice::Object>(new ::IceDelegateD::TianShanIce::Streamer::PlaylistEx);
}

bool
IceProxy::TianShanIce::Streamer::operator==(const ::IceProxy::TianShanIce::Streamer::PlaylistEx& l, const ::IceProxy::TianShanIce::Streamer::PlaylistEx& r)
{
    return static_cast<const ::IceProxy::Ice::Object&>(l) == static_cast<const ::IceProxy::Ice::Object&>(r);
}

bool
IceProxy::TianShanIce::Streamer::operator!=(const ::IceProxy::TianShanIce::Streamer::PlaylistEx& l, const ::IceProxy::TianShanIce::Streamer::PlaylistEx& r)
{
    return static_cast<const ::IceProxy::Ice::Object&>(l) != static_cast<const ::IceProxy::Ice::Object&>(r);
}

bool
IceProxy::TianShanIce::Streamer::operator<(const ::IceProxy::TianShanIce::Streamer::PlaylistEx& l, const ::IceProxy::TianShanIce::Streamer::PlaylistEx& r)
{
    return static_cast<const ::IceProxy::Ice::Object&>(l) < static_cast<const ::IceProxy::Ice::Object&>(r);
}

bool
IceProxy::TianShanIce::Streamer::operator<=(const ::IceProxy::TianShanIce::Streamer::PlaylistEx& l, const ::IceProxy::TianShanIce::Streamer::PlaylistEx& r)
{
    return l < r || l == r;
}

bool
IceProxy::TianShanIce::Streamer::operator>(const ::IceProxy::TianShanIce::Streamer::PlaylistEx& l, const ::IceProxy::TianShanIce::Streamer::PlaylistEx& r)
{
    return !(l < r) && !(l == r);
}

bool
IceProxy::TianShanIce::Streamer::operator>=(const ::IceProxy::TianShanIce::Streamer::PlaylistEx& l, const ::IceProxy::TianShanIce::Streamer::PlaylistEx& r)
{
    return !(l < r);
}

void
IceProxy::TianShanIce::Streamer::PlaylistItem::destroy(const ::Ice::Context* __ctx)
{
    int __cnt = 0;
    while(true)
    {
        ::IceInternal::Handle< ::IceDelegate::Ice::Object> __delBase;
        try
        {
            __delBase = __getDelegate();
            ::IceDelegate::TianShanIce::Streamer::PlaylistItem* __del = dynamic_cast< ::IceDelegate::TianShanIce::Streamer::PlaylistItem*>(__delBase.get());
            __del->destroy(__ctx);
            return;
        }
        catch(const ::IceInternal::LocalExceptionWrapper& __ex)
        {
            __handleExceptionWrapper(__delBase, __ex);
        }
        catch(const ::Ice::LocalException& __ex)
        {
            __handleException(__delBase, __ex, __cnt);
        }
    }
}

::TianShanIce::Streamer::PlaylistItemAttr
IceProxy::TianShanIce::Streamer::PlaylistItem::getAttr(const ::Ice::Context* __ctx)
{
    int __cnt = 0;
    while(true)
    {
        ::IceInternal::Handle< ::IceDelegate::Ice::Object> __delBase;
        try
        {
            __checkTwowayOnly(__TianShanIce__Streamer__PlaylistItem__getAttr_name);
            __delBase = __getDelegate();
            ::IceDelegate::TianShanIce::Streamer::PlaylistItem* __del = dynamic_cast< ::IceDelegate::TianShanIce::Streamer::PlaylistItem*>(__delBase.get());
            return __del->getAttr(__ctx);
        }
        catch(const ::IceInternal::LocalExceptionWrapper& __ex)
        {
            __handleExceptionWrapper(__delBase, __ex);
        }
        catch(const ::Ice::LocalException& __ex)
        {
            __handleException(__delBase, __ex, __cnt);
        }
    }
}

void
IceProxy::TianShanIce::Streamer::PlaylistItem::updateAttr(const ::TianShanIce::Streamer::PlaylistItemAttr& attr, const ::Ice::Context* __ctx)
{
    int __cnt = 0;
    while(true)
    {
        ::IceInternal::Handle< ::IceDelegate::Ice::Object> __delBase;
        try
        {
            __delBase = __getDelegate();
            ::IceDelegate::TianShanIce::Streamer::PlaylistItem* __del = dynamic_cast< ::IceDelegate::TianShanIce::Streamer::PlaylistItem*>(__delBase.get());
            __del->updateAttr(attr, __ctx);
            return;
        }
        catch(const ::IceInternal::LocalExceptionWrapper& __ex)
        {
            __handleExceptionWrapper(__delBase, __ex);
        }
        catch(const ::Ice::LocalException& __ex)
        {
            __handleException(__delBase, __ex, __cnt);
        }
    }
}

const ::std::string&
IceProxy::TianShanIce::Streamer::PlaylistItem::ice_staticId()
{
    return ::TianShanIce::Streamer::PlaylistItem::ice_staticId();
}

::IceInternal::Handle< ::IceDelegateM::Ice::Object>
IceProxy::TianShanIce::Streamer::PlaylistItem::__createDelegateM()
{
    return ::IceInternal::Handle< ::IceDelegateM::Ice::Object>(new ::IceDelegateM::TianShanIce::Streamer::PlaylistItem);
}

::IceInternal::Handle< ::IceDelegateD::Ice::Object>
IceProxy::TianShanIce::Streamer::PlaylistItem::__createDelegateD()
{
    return ::IceInternal::Handle< ::IceDelegateD::Ice::Object>(new ::IceDelegateD::TianShanIce::Streamer::PlaylistItem);
}

bool
IceProxy::TianShanIce::Streamer::operator==(const ::IceProxy::TianShanIce::Streamer::PlaylistItem& l, const ::IceProxy::TianShanIce::Streamer::PlaylistItem& r)
{
    return static_cast<const ::IceProxy::Ice::Object&>(l) == static_cast<const ::IceProxy::Ice::Object&>(r);
}

bool
IceProxy::TianShanIce::Streamer::operator!=(const ::IceProxy::TianShanIce::Streamer::PlaylistItem& l, const ::IceProxy::TianShanIce::Streamer::PlaylistItem& r)
{
    return static_cast<const ::IceProxy::Ice::Object&>(l) != static_cast<const ::IceProxy::Ice::Object&>(r);
}

bool
IceProxy::TianShanIce::Streamer::operator<(const ::IceProxy::TianShanIce::Streamer::PlaylistItem& l, const ::IceProxy::TianShanIce::Streamer::PlaylistItem& r)
{
    return static_cast<const ::IceProxy::Ice::Object&>(l) < static_cast<const ::IceProxy::Ice::Object&>(r);
}

bool
IceProxy::TianShanIce::Streamer::operator<=(const ::IceProxy::TianShanIce::Streamer::PlaylistItem& l, const ::IceProxy::TianShanIce::Streamer::PlaylistItem& r)
{
    return l < r || l == r;
}

bool
IceProxy::TianShanIce::Streamer::operator>(const ::IceProxy::TianShanIce::Streamer::PlaylistItem& l, const ::IceProxy::TianShanIce::Streamer::PlaylistItem& r)
{
    return !(l < r) && !(l == r);
}

bool
IceProxy::TianShanIce::Streamer::operator>=(const ::IceProxy::TianShanIce::Streamer::PlaylistItem& l, const ::IceProxy::TianShanIce::Streamer::PlaylistItem& r)
{
    return !(l < r);
}

::TianShanIce::Streamer::PlaylistIDs
IceProxy::TianShanIce::Streamer::StreamSmithAdmin::listPlaylists(const ::Ice::Context* __ctx)
{
    int __cnt = 0;
    while(true)
    {
        ::IceInternal::Handle< ::IceDelegate::Ice::Object> __delBase;
        try
        {
            __checkTwowayOnly(__TianShanIce__Streamer__StreamSmithAdmin__listPlaylists_name);
            __delBase = __getDelegate();
            ::IceDelegate::TianShanIce::Streamer::StreamSmithAdmin* __del = dynamic_cast< ::IceDelegate::TianShanIce::Streamer::StreamSmithAdmin*>(__delBase.get());
            return __del->listPlaylists(__ctx);
        }
        catch(const ::IceInternal::LocalExceptionWrapper& __ex)
        {
            __handleExceptionWrapper(__delBase, __ex);
        }
        catch(const ::Ice::LocalException& __ex)
        {
            __handleException(__delBase, __ex, __cnt);
        }
    }
}

::TianShanIce::Streamer::PlaylistPrx
IceProxy::TianShanIce::Streamer::StreamSmithAdmin::openPlaylist(const ::std::string& guid, const ::TianShanIce::Streamer::SpigotBoards& EdgeCards, bool bCreateIfNotExist, const ::Ice::Context* __ctx)
{
    int __cnt = 0;
    while(true)
    {
        ::IceInternal::Handle< ::IceDelegate::Ice::Object> __delBase;
        try
        {
            __checkTwowayOnly(__TianShanIce__Streamer__StreamSmithAdmin__openPlaylist_name);
            __delBase = __getDelegate();
            ::IceDelegate::TianShanIce::Streamer::StreamSmithAdmin* __del = dynamic_cast< ::IceDelegate::TianShanIce::Streamer::StreamSmithAdmin*>(__delBase.get());
            return __del->openPlaylist(guid, EdgeCards, bCreateIfNotExist, __ctx);
        }
        catch(const ::IceInternal::LocalExceptionWrapper& __ex)
        {
            __handleExceptionWrapper(__delBase, __ex);
        }
        catch(const ::Ice::LocalException& __ex)
        {
            __handleException(__delBase, __ex, __cnt);
        }
    }
}

::TianShanIce::Streamer::StreamBatchResponse
IceProxy::TianShanIce::Streamer::StreamSmithAdmin::createStreamBatch(const ::TianShanIce::Streamer::StreamBatchRequest& req, const ::Ice::Context* __ctx)
{
    int __cnt = 0;
    while(true)
    {
        ::IceInternal::Handle< ::IceDelegate::Ice::Object> __delBase;
        try
        {
            __checkTwowayOnly(__TianShanIce__Streamer__StreamSmithAdmin__createStreamBatch_name);
            __delBase = __getDelegate();
            ::IceDelegate::TianShanIce::Streamer::StreamSmithAdmin* __del = dynamic_cast< ::IceDelegate::TianShanIce::Streamer::StreamSmithAdmin*>(__delBase.get());
            return __del->createStreamBatch(req, __ctx);
        }
        catch(const ::IceInternal::LocalExceptionWrapper& __ex)
        {
            __handleExceptionWrapper(__delBase, __ex);
        }
        catch(const ::Ice::LocalException& __ex)
        {
            __handleException(__delBase, __ex, __cnt);
        }
    }
}

void
IceProxy::TianShanIce::Streamer::StreamSmithAdmin::createStreamBatch_async(const ::TianShanIce::Streamer::AMI_StreamSmithAdmin_createStreamBatchPtr& __cb, const ::TianShanIce::Streamer::StreamBatchRequest& req)
{
    __cb->__invoke(this, req, 0);
}

void
IceProxy::TianShanIce::Streamer::StreamSmithAdmin::createStreamBatch_async(const ::TianShanIce::Streamer::AMI_StreamSmithAdmin_createStreamBatchPtr& __cb, const ::TianShanIce::Streamer::StreamBatchRequest& req, const ::Ice::Context& __ctx)
{
    __cb->__invoke(this, req, &__ctx);
}

::std::string
IceProxy::TianShanIce::Streamer::StreamSmithAdmin::ShowMemory(const ::Ice::Context* __ctx)
{
    int __cnt = 0;
    while(true)
    {
        ::IceInternal::Handle< ::IceDelegate::Ice::Object> __delBase;
        try
        {
            __checkTwowayOnly(__TianShanIce__Streamer__StreamSmithAdmin__ShowMemory_name);
            __delBase = __getDelegate();
            ::IceDelegate::TianShanIce::Streamer::StreamSmithAdmin* __del = dynamic_cast< ::IceDelegate::TianShanIce::Streamer::StreamSmithAdmin*>(__delBase.get());
            return __del->ShowMemory(__ctx);
        }
        catch(const ::IceInternal::LocalExceptionWrapper& __ex)
        {
            __handleExceptionWrapper(__delBase, __ex);
        }
        catch(const ::Ice::LocalException& __ex)
        {
            __handleException(__delBase, __ex, __cnt);
        }
    }
}

const ::std::string&
IceProxy::TianShanIce::Streamer::StreamSmithAdmin::ice_staticId()
{
    return ::TianShanIce::Streamer::StreamSmithAdmin::ice_staticId();
}

::IceInternal::Handle< ::IceDelegateM::Ice::Object>
IceProxy::TianShanIce::Streamer::StreamSmithAdmin::__createDelegateM()
{
    return ::IceInternal::Handle< ::IceDelegateM::Ice::Object>(new ::IceDelegateM::TianShanIce::Streamer::StreamSmithAdmin);
}

::IceInternal::Handle< ::IceDelegateD::Ice::Object>
IceProxy::TianShanIce::Streamer::StreamSmithAdmin::__createDelegateD()
{
    return ::IceInternal::Handle< ::IceDelegateD::Ice::Object>(new ::IceDelegateD::TianShanIce::Streamer::StreamSmithAdmin);
}

bool
IceProxy::TianShanIce::Streamer::operator==(const ::IceProxy::TianShanIce::Streamer::StreamSmithAdmin& l, const ::IceProxy::TianShanIce::Streamer::StreamSmithAdmin& r)
{
    return static_cast<const ::IceProxy::Ice::Object&>(l) == static_cast<const ::IceProxy::Ice::Object&>(r);
}

bool
IceProxy::TianShanIce::Streamer::operator!=(const ::IceProxy::TianShanIce::Streamer::StreamSmithAdmin& l, const ::IceProxy::TianShanIce::Streamer::StreamSmithAdmin& r)
{
    return static_cast<const ::IceProxy::Ice::Object&>(l) != static_cast<const ::IceProxy::Ice::Object&>(r);
}

bool
IceProxy::TianShanIce::Streamer::operator<(const ::IceProxy::TianShanIce::Streamer::StreamSmithAdmin& l, const ::IceProxy::TianShanIce::Streamer::StreamSmithAdmin& r)
{
    return static_cast<const ::IceProxy::Ice::Object&>(l) < static_cast<const ::IceProxy::Ice::Object&>(r);
}

bool
IceProxy::TianShanIce::Streamer::operator<=(const ::IceProxy::TianShanIce::Streamer::StreamSmithAdmin& l, const ::IceProxy::TianShanIce::Streamer::StreamSmithAdmin& r)
{
    return l < r || l == r;
}

bool
IceProxy::TianShanIce::Streamer::operator>(const ::IceProxy::TianShanIce::Streamer::StreamSmithAdmin& l, const ::IceProxy::TianShanIce::Streamer::StreamSmithAdmin& r)
{
    return !(l < r) && !(l == r);
}

bool
IceProxy::TianShanIce::Streamer::operator>=(const ::IceProxy::TianShanIce::Streamer::StreamSmithAdmin& l, const ::IceProxy::TianShanIce::Streamer::StreamSmithAdmin& r)
{
    return !(l < r);
}

::TianShanIce::Streamer::PlaylistAttr
IceDelegateM::TianShanIce::Streamer::PlaylistEx::getAttr(const ::Ice::Context* __context)
{
    ::IceInternal::Outgoing __og(__connection.get(), __reference.get(), __TianShanIce__Streamer__PlaylistEx__getAttr_name, ::Ice::Normal, __context, __compress);
    bool __ok = __og.invoke();
    try
    {
        ::IceInternal::BasicStream* __is = __og.is();
        if(!__ok)
        {
            try
            {
                __is->throwException();
            }
            catch(const ::Ice::UserException& __ex)
            {
                throw ::Ice::UnknownUserException(__FILE__, __LINE__, __ex.ice_name());
            }
        }
        ::TianShanIce::Streamer::PlaylistAttr __ret;
        __ret.__read(__is);
        return __ret;
    }
    catch(const ::Ice::LocalException& __ex)
    {
        throw ::IceInternal::LocalExceptionWrapper(__ex, false);
    }
}

void
IceDelegateM::TianShanIce::Streamer::PlaylistEx::updateAttr(const ::TianShanIce::Streamer::PlaylistAttr& attr, const ::Ice::Context* __context)
{
    ::IceInternal::Outgoing __og(__connection.get(), __reference.get(), __TianShanIce__Streamer__PlaylistEx__updateAttr_name, ::Ice::Normal, __context, __compress);
    try
    {
        ::IceInternal::BasicStream* __os = __og.os();
        attr.__write(__os);
    }
    catch(const ::Ice::LocalException& __ex)
    {
        __og.abort(__ex);
    }
    bool __ok = __og.invoke();
    try
    {
        ::IceInternal::BasicStream* __is = __og.is();
        if(!__ok)
        {
            try
            {
                __is->throwException();
            }
            catch(const ::Ice::UserException& __ex)
            {
                throw ::Ice::UnknownUserException(__FILE__, __LINE__, __ex.ice_name());
            }
        }
    }
    catch(const ::Ice::LocalException& __ex)
    {
        throw ::IceInternal::LocalExceptionWrapper(__ex, false);
    }
}

void
IceDelegateM::TianShanIce::Streamer::PlaylistEx::attachSession(const ::TianShanIce::SRM::SessionPrx& sess, const ::Ice::Context* __context)
{
    ::IceInternal::Outgoing __og(__connection.get(), __reference.get(), __TianShanIce__Streamer__PlaylistEx__attachSession_name, ::Ice::Normal, __context, __compress);
    try
    {
        ::IceInternal::BasicStream* __os = __og.os();
        ::TianShanIce::SRM::__write(__os, sess);
    }
    catch(const ::Ice::LocalException& __ex)
    {
        __og.abort(__ex);
    }
    bool __ok = __og.invoke();
    try
    {
        ::IceInternal::BasicStream* __is = __og.is();
        if(!__ok)
        {
            try
            {
                __is->throwException();
            }
            catch(const ::Ice::UserException& __ex)
            {
                throw ::Ice::UnknownUserException(__FILE__, __LINE__, __ex.ice_name());
            }
        }
    }
    catch(const ::Ice::LocalException& __ex)
    {
        throw ::IceInternal::LocalExceptionWrapper(__ex, false);
    }
}

void
IceDelegateM::TianShanIce::Streamer::PlaylistEx::setDestination(const ::std::string& destIP, ::Ice::Int port, const ::Ice::Context* __context)
{
    ::IceInternal::Outgoing __og(__connection.get(), __reference.get(), __TianShanIce__Streamer__PlaylistEx__setDestination_name, ::Ice::Normal, __context, __compress);
    try
    {
        ::IceInternal::BasicStream* __os = __og.os();
        __os->write(destIP);
        __os->write(port);
    }
    catch(const ::Ice::LocalException& __ex)
    {
        __og.abort(__ex);
    }
    bool __ok = __og.invoke();
    try
    {
        ::IceInternal::BasicStream* __is = __og.is();
        if(!__ok)
        {
            try
            {
                __is->throwException();
            }
            catch(const ::Ice::UserException& __ex)
            {
                throw ::Ice::UnknownUserException(__FILE__, __LINE__, __ex.ice_name());
            }
        }
    }
    catch(const ::Ice::LocalException& __ex)
    {
        throw ::IceInternal::LocalExceptionWrapper(__ex, false);
    }
}

void
IceDelegateM::TianShanIce::Streamer::PlaylistEx::setDestMac(const ::std::string& strMac, const ::Ice::Context* __context)
{
    ::IceInternal::Outgoing __og(__connection.get(), __reference.get(), __TianShanIce__Streamer__PlaylistEx__setDestMac_name, ::Ice::Normal, __context, __compress);
    try
    {
        ::IceInternal::BasicStream* __os = __og.os();
        __os->write(strMac);
    }
    catch(const ::Ice::LocalException& __ex)
    {
        __og.abort(__ex);
    }
    bool __ok = __og.invoke();
    try
    {
        ::IceInternal::BasicStream* __is = __og.is();
        if(!__ok)
        {
            try
            {
                __is->throwException();
            }
            catch(const ::Ice::UserException& __ex)
            {
                throw ::Ice::UnknownUserException(__FILE__, __LINE__, __ex.ice_name());
            }
        }
    }
    catch(const ::Ice::LocalException& __ex)
    {
        throw ::IceInternal::LocalExceptionWrapper(__ex, false);
    }
}

void
IceDelegateM::TianShanIce::Streamer::PlaylistEx::setSourceStrmPort(::Ice::Int port, const ::Ice::Context* __context)
{
    ::IceInternal::Outgoing __og(__connection.get(), __reference.get(), __TianShanIce__Streamer__PlaylistEx__setSourceStrmPort_name, ::Ice::Normal, __context, __compress);
    try
    {
        ::IceInternal::BasicStream* __os = __og.os();
        __os->write(port);
    }
    catch(const ::Ice::LocalException& __ex)
    {
        __og.abort(__ex);
    }
    bool __ok = __og.invoke();
    try
    {
        ::IceInternal::BasicStream* __is = __og.is();
        if(!__ok)
        {
            try
            {
                __is->throwException();
            }
            catch(const ::Ice::UserException& __ex)
            {
                throw ::Ice::UnknownUserException(__FILE__, __LINE__, __ex.ice_name());
            }
        }
    }
    catch(const ::Ice::LocalException& __ex)
    {
        throw ::IceInternal::LocalExceptionWrapper(__ex, false);
    }
}

void
IceDelegateM::TianShanIce::Streamer::PlaylistEx::setPID(::Ice::Int pid, const ::Ice::Context* __context)
{
    ::IceInternal::Outgoing __og(__connection.get(), __reference.get(), __TianShanIce__Streamer__PlaylistEx__setPID_name, ::Ice::Normal, __context, __compress);
    try
    {
        ::IceInternal::BasicStream* __os = __og.os();
        __os->write(pid);
    }
    catch(const ::Ice::LocalException& __ex)
    {
        __og.abort(__ex);
    }
    bool __ok = __og.invoke();
    try
    {
        ::IceInternal::BasicStream* __is = __og.is();
        if(!__ok)
        {
            try
            {
                __is->throwException();
            }
            catch(const ::Ice::UserException& __ex)
            {
                throw ::Ice::UnknownUserException(__FILE__, __LINE__, __ex.ice_name());
            }
        }
    }
    catch(const ::Ice::LocalException& __ex)
    {
        throw ::IceInternal::LocalExceptionWrapper(__ex, false);
    }
}

void
IceDelegateM::TianShanIce::Streamer::PlaylistEx::onTimer(const ::Ice::Context* __context)
{
    ::IceInternal::Outgoing __og(__connection.get(), __reference.get(), __TianShanIce__Streamer__PlaylistEx__onTimer_name, ::Ice::Normal, __context, __compress);
    bool __ok = __og.invoke();
    try
    {
        ::IceInternal::BasicStream* __is = __og.is();
        if(!__ok)
        {
            try
            {
                __is->throwException();
            }
            catch(const ::Ice::UserException& __ex)
            {
                throw ::Ice::UnknownUserException(__FILE__, __LINE__, __ex.ice_name());
            }
        }
    }
    catch(const ::Ice::LocalException& __ex)
    {
        throw ::IceInternal::LocalExceptionWrapper(__ex, false);
    }
}

void
IceDelegateM::TianShanIce::Streamer::PlaylistItem::destroy(const ::Ice::Context* __context)
{
    ::IceInternal::Outgoing __og(__connection.get(), __reference.get(), __TianShanIce__Streamer__PlaylistItem__destroy_name, ::Ice::Normal, __context, __compress);
    bool __ok = __og.invoke();
    try
    {
        ::IceInternal::BasicStream* __is = __og.is();
        if(!__ok)
        {
            try
            {
                __is->throwException();
            }
            catch(const ::Ice::UserException& __ex)
            {
                throw ::Ice::UnknownUserException(__FILE__, __LINE__, __ex.ice_name());
            }
        }
    }
    catch(const ::Ice::LocalException& __ex)
    {
        throw ::IceInternal::LocalExceptionWrapper(__ex, false);
    }
}

::TianShanIce::Streamer::PlaylistItemAttr
IceDelegateM::TianShanIce::Streamer::PlaylistItem::getAttr(const ::Ice::Context* __context)
{
    ::IceInternal::Outgoing __og(__connection.get(), __reference.get(), __TianShanIce__Streamer__PlaylistItem__getAttr_name, ::Ice::Normal, __context, __compress);
    bool __ok = __og.invoke();
    try
    {
        ::IceInternal::BasicStream* __is = __og.is();
        if(!__ok)
        {
            try
            {
                __is->throwException();
            }
            catch(const ::Ice::UserException& __ex)
            {
                throw ::Ice::UnknownUserException(__FILE__, __LINE__, __ex.ice_name());
            }
        }
        ::TianShanIce::Streamer::PlaylistItemAttr __ret;
        __ret.__read(__is);
        return __ret;
    }
    catch(const ::Ice::LocalException& __ex)
    {
        throw ::IceInternal::LocalExceptionWrapper(__ex, false);
    }
}

void
IceDelegateM::TianShanIce::Streamer::PlaylistItem::updateAttr(const ::TianShanIce::Streamer::PlaylistItemAttr& attr, const ::Ice::Context* __context)
{
    ::IceInternal::Outgoing __og(__connection.get(), __reference.get(), __TianShanIce__Streamer__PlaylistItem__updateAttr_name, ::Ice::Normal, __context, __compress);
    try
    {
        ::IceInternal::BasicStream* __os = __og.os();
        attr.__write(__os);
    }
    catch(const ::Ice::LocalException& __ex)
    {
        __og.abort(__ex);
    }
    bool __ok = __og.invoke();
    try
    {
        ::IceInternal::BasicStream* __is = __og.is();
        if(!__ok)
        {
            try
            {
                __is->throwException();
            }
            catch(const ::Ice::UserException& __ex)
            {
                throw ::Ice::UnknownUserException(__FILE__, __LINE__, __ex.ice_name());
            }
        }
    }
    catch(const ::Ice::LocalException& __ex)
    {
        throw ::IceInternal::LocalExceptionWrapper(__ex, false);
    }
}

::TianShanIce::Streamer::PlaylistIDs
IceDelegateM::TianShanIce::Streamer::StreamSmithAdmin::listPlaylists(const ::Ice::Context* __context)
{
    ::IceInternal::Outgoing __og(__connection.get(), __reference.get(), __TianShanIce__Streamer__StreamSmithAdmin__listPlaylists_name, ::Ice::Normal, __context, __compress);
    bool __ok = __og.invoke();
    try
    {
        ::IceInternal::BasicStream* __is = __og.is();
        if(!__ok)
        {
            try
            {
                __is->throwException();
            }
            catch(const ::Ice::UserException& __ex)
            {
                throw ::Ice::UnknownUserException(__FILE__, __LINE__, __ex.ice_name());
            }
        }
        ::TianShanIce::Streamer::PlaylistIDs __ret;
        __is->read(__ret);
        return __ret;
    }
    catch(const ::Ice::LocalException& __ex)
    {
        throw ::IceInternal::LocalExceptionWrapper(__ex, false);
    }
}

::TianShanIce::Streamer::PlaylistPrx
IceDelegateM::TianShanIce::Streamer::StreamSmithAdmin::openPlaylist(const ::std::string& guid, const ::TianShanIce::Streamer::SpigotBoards& EdgeCards, bool bCreateIfNotExist, const ::Ice::Context* __context)
{
    ::IceInternal::Outgoing __og(__connection.get(), __reference.get(), __TianShanIce__Streamer__StreamSmithAdmin__openPlaylist_name, ::Ice::Normal, __context, __compress);
    try
    {
        ::IceInternal::BasicStream* __os = __og.os();
        __os->write(guid);
        if(EdgeCards.size() == 0)
        {
            __os->writeSize(0);
        }
        else
        {
            __os->write(&EdgeCards[0], &EdgeCards[0] + EdgeCards.size());
        }
        __os->write(bCreateIfNotExist);
    }
    catch(const ::Ice::LocalException& __ex)
    {
        __og.abort(__ex);
    }
    bool __ok = __og.invoke();
    try
    {
        ::IceInternal::BasicStream* __is = __og.is();
        if(!__ok)
        {
            try
            {
                __is->throwException();
            }
            catch(const ::Ice::UserException& __ex)
            {
                throw ::Ice::UnknownUserException(__FILE__, __LINE__, __ex.ice_name());
            }
        }
        ::TianShanIce::Streamer::PlaylistPrx __ret;
        ::TianShanIce::Streamer::__read(__is, __ret);
        return __ret;
    }
    catch(const ::Ice::LocalException& __ex)
    {
        throw ::IceInternal::LocalExceptionWrapper(__ex, false);
    }
}

::TianShanIce::Streamer::StreamBatchResponse
IceDelegateM::TianShanIce::Streamer::StreamSmithAdmin::createStreamBatch(const ::TianShanIce::Streamer::StreamBatchRequest& req, const ::Ice::Context* __context)
{
    ::IceInternal::Outgoing __og(__connection.get(), __reference.get(), __TianShanIce__Streamer__StreamSmithAdmin__createStreamBatch_name, ::Ice::Normal, __context, __compress);
    try
    {
        ::IceInternal::BasicStream* __os = __og.os();
        if(req.size() == 0)
        {
            __os->writeSize(0);
        }
        else
        {
            ::TianShanIce::Streamer::__write(__os, &req[0], &req[0] + req.size(), ::TianShanIce::Streamer::__U__StreamBatchRequest());
        }
    }
    catch(const ::Ice::LocalException& __ex)
    {
        __og.abort(__ex);
    }
    bool __ok = __og.invoke();
    try
    {
        ::IceInternal::BasicStream* __is = __og.is();
        if(!__ok)
        {
            try
            {
                __is->throwException();
            }
            catch(const ::TianShanIce::ServerError&)
            {
                throw;
            }
            catch(const ::Ice::UserException& __ex)
            {
                throw ::Ice::UnknownUserException(__FILE__, __LINE__, __ex.ice_name());
            }
        }
        ::TianShanIce::Streamer::StreamBatchResponse __ret;
        ::TianShanIce::Streamer::__read(__is, __ret, ::TianShanIce::Streamer::__U__StreamBatchResponse());
        return __ret;
    }
    catch(const ::Ice::LocalException& __ex)
    {
        throw ::IceInternal::LocalExceptionWrapper(__ex, false);
    }
}

::std::string
IceDelegateM::TianShanIce::Streamer::StreamSmithAdmin::ShowMemory(const ::Ice::Context* __context)
{
    ::IceInternal::Outgoing __og(__connection.get(), __reference.get(), __TianShanIce__Streamer__StreamSmithAdmin__ShowMemory_name, ::Ice::Normal, __context, __compress);
    bool __ok = __og.invoke();
    try
    {
        ::IceInternal::BasicStream* __is = __og.is();
        if(!__ok)
        {
            try
            {
                __is->throwException();
            }
            catch(const ::Ice::UserException& __ex)
            {
                throw ::Ice::UnknownUserException(__FILE__, __LINE__, __ex.ice_name());
            }
        }
        ::std::string __ret;
        __is->read(__ret);
        return __ret;
    }
    catch(const ::Ice::LocalException& __ex)
    {
        throw ::IceInternal::LocalExceptionWrapper(__ex, false);
    }
}

::TianShanIce::Streamer::PlaylistAttr
IceDelegateD::TianShanIce::Streamer::PlaylistEx::getAttr(const ::Ice::Context* __context)
{
    ::Ice::Current __current;
    __initCurrent(__current, __TianShanIce__Streamer__PlaylistEx__getAttr_name, ::Ice::Normal, __context);
    while(true)
    {
        ::IceInternal::Direct __direct(__current);
        ::TianShanIce::Streamer::PlaylistAttr __ret;
        try
        {
            ::TianShanIce::Streamer::PlaylistEx* __servant = dynamic_cast< ::TianShanIce::Streamer::PlaylistEx*>(__direct.servant().get());
            if(!__servant)
            {
                ::Ice::OperationNotExistException __opEx(__FILE__, __LINE__);
                __opEx.id = __current.id;
                __opEx.facet = __current.facet;
                __opEx.operation = __current.operation;
                throw __opEx;
            }
            try
            {
                __ret = __servant->getAttr(__current);
            }
            catch(const ::Ice::LocalException& __ex)
            {
                throw ::IceInternal::LocalExceptionWrapper(__ex, false);
            }
        }
        catch(...)
        {
            __direct.destroy();
            throw;
        }
        __direct.destroy();
        return __ret;
    }
}

void
IceDelegateD::TianShanIce::Streamer::PlaylistEx::updateAttr(const ::TianShanIce::Streamer::PlaylistAttr& attr, const ::Ice::Context* __context)
{
    ::Ice::Current __current;
    __initCurrent(__current, __TianShanIce__Streamer__PlaylistEx__updateAttr_name, ::Ice::Normal, __context);
    while(true)
    {
        ::IceInternal::Direct __direct(__current);
        try
        {
            ::TianShanIce::Streamer::PlaylistEx* __servant = dynamic_cast< ::TianShanIce::Streamer::PlaylistEx*>(__direct.servant().get());
            if(!__servant)
            {
                ::Ice::OperationNotExistException __opEx(__FILE__, __LINE__);
                __opEx.id = __current.id;
                __opEx.facet = __current.facet;
                __opEx.operation = __current.operation;
                throw __opEx;
            }
            try
            {
                __servant->updateAttr(attr, __current);
            }
            catch(const ::Ice::LocalException& __ex)
            {
                throw ::IceInternal::LocalExceptionWrapper(__ex, false);
            }
        }
        catch(...)
        {
            __direct.destroy();
            throw;
        }
        __direct.destroy();
        return;
    }
}

void
IceDelegateD::TianShanIce::Streamer::PlaylistEx::attachSession(const ::TianShanIce::SRM::SessionPrx& sess, const ::Ice::Context* __context)
{
    ::Ice::Current __current;
    __initCurrent(__current, __TianShanIce__Streamer__PlaylistEx__attachSession_name, ::Ice::Normal, __context);
    while(true)
    {
        ::IceInternal::Direct __direct(__current);
        try
        {
            ::TianShanIce::Streamer::PlaylistEx* __servant = dynamic_cast< ::TianShanIce::Streamer::PlaylistEx*>(__direct.servant().get());
            if(!__servant)
            {
                ::Ice::OperationNotExistException __opEx(__FILE__, __LINE__);
                __opEx.id = __current.id;
                __opEx.facet = __current.facet;
                __opEx.operation = __current.operation;
                throw __opEx;
            }
            try
            {
                __servant->attachSession(sess, __current);
            }
            catch(const ::Ice::LocalException& __ex)
            {
                throw ::IceInternal::LocalExceptionWrapper(__ex, false);
            }
        }
        catch(...)
        {
            __direct.destroy();
            throw;
        }
        __direct.destroy();
        return;
    }
}

void
IceDelegateD::TianShanIce::Streamer::PlaylistEx::setDestination(const ::std::string& destIP, ::Ice::Int port, const ::Ice::Context* __context)
{
    ::Ice::Current __current;
    __initCurrent(__current, __TianShanIce__Streamer__PlaylistEx__setDestination_name, ::Ice::Normal, __context);
    while(true)
    {
        ::IceInternal::Direct __direct(__current);
        try
        {
            ::TianShanIce::Streamer::PlaylistEx* __servant = dynamic_cast< ::TianShanIce::Streamer::PlaylistEx*>(__direct.servant().get());
            if(!__servant)
            {
                ::Ice::OperationNotExistException __opEx(__FILE__, __LINE__);
                __opEx.id = __current.id;
                __opEx.facet = __current.facet;
                __opEx.operation = __current.operation;
                throw __opEx;
            }
            try
            {
                __servant->setDestination(destIP, port, __current);
            }
            catch(const ::Ice::LocalException& __ex)
            {
                throw ::IceInternal::LocalExceptionWrapper(__ex, false);
            }
        }
        catch(...)
        {
            __direct.destroy();
            throw;
        }
        __direct.destroy();
        return;
    }
}

void
IceDelegateD::TianShanIce::Streamer::PlaylistEx::setDestMac(const ::std::string& strMac, const ::Ice::Context* __context)
{
    ::Ice::Current __current;
    __initCurrent(__current, __TianShanIce__Streamer__PlaylistEx__setDestMac_name, ::Ice::Normal, __context);
    while(true)
    {
        ::IceInternal::Direct __direct(__current);
        try
        {
            ::TianShanIce::Streamer::PlaylistEx* __servant = dynamic_cast< ::TianShanIce::Streamer::PlaylistEx*>(__direct.servant().get());
            if(!__servant)
            {
                ::Ice::OperationNotExistException __opEx(__FILE__, __LINE__);
                __opEx.id = __current.id;
                __opEx.facet = __current.facet;
                __opEx.operation = __current.operation;
                throw __opEx;
            }
            try
            {
                __servant->setDestMac(strMac, __current);
            }
            catch(const ::Ice::LocalException& __ex)
            {
                throw ::IceInternal::LocalExceptionWrapper(__ex, false);
            }
        }
        catch(...)
        {
            __direct.destroy();
            throw;
        }
        __direct.destroy();
        return;
    }
}

void
IceDelegateD::TianShanIce::Streamer::PlaylistEx::setSourceStrmPort(::Ice::Int port, const ::Ice::Context* __context)
{
    ::Ice::Current __current;
    __initCurrent(__current, __TianShanIce__Streamer__PlaylistEx__setSourceStrmPort_name, ::Ice::Normal, __context);
    while(true)
    {
        ::IceInternal::Direct __direct(__current);
        try
        {
            ::TianShanIce::Streamer::PlaylistEx* __servant = dynamic_cast< ::TianShanIce::Streamer::PlaylistEx*>(__direct.servant().get());
            if(!__servant)
            {
                ::Ice::OperationNotExistException __opEx(__FILE__, __LINE__);
                __opEx.id = __current.id;
                __opEx.facet = __current.facet;
                __opEx.operation = __current.operation;
                throw __opEx;
            }
            try
            {
                __servant->setSourceStrmPort(port, __current);
            }
            catch(const ::Ice::LocalException& __ex)
            {
                throw ::IceInternal::LocalExceptionWrapper(__ex, false);
            }
        }
        catch(...)
        {
            __direct.destroy();
            throw;
        }
        __direct.destroy();
        return;
    }
}

void
IceDelegateD::TianShanIce::Streamer::PlaylistEx::setPID(::Ice::Int pid, const ::Ice::Context* __context)
{
    ::Ice::Current __current;
    __initCurrent(__current, __TianShanIce__Streamer__PlaylistEx__setPID_name, ::Ice::Normal, __context);
    while(true)
    {
        ::IceInternal::Direct __direct(__current);
        try
        {
            ::TianShanIce::Streamer::PlaylistEx* __servant = dynamic_cast< ::TianShanIce::Streamer::PlaylistEx*>(__direct.servant().get());
            if(!__servant)
            {
                ::Ice::OperationNotExistException __opEx(__FILE__, __LINE__);
                __opEx.id = __current.id;
                __opEx.facet = __current.facet;
                __opEx.operation = __current.operation;
                throw __opEx;
            }
            try
            {
                __servant->setPID(pid, __current);
            }
            catch(const ::Ice::LocalException& __ex)
            {
                throw ::IceInternal::LocalExceptionWrapper(__ex, false);
            }
        }
        catch(...)
        {
            __direct.destroy();
            throw;
        }
        __direct.destroy();
        return;
    }
}

void
IceDelegateD::TianShanIce::Streamer::PlaylistEx::onTimer(const ::Ice::Context* __context)
{
    ::Ice::Current __current;
    __initCurrent(__current, __TianShanIce__Streamer__PlaylistEx__onTimer_name, ::Ice::Normal, __context);
    while(true)
    {
        ::IceInternal::Direct __direct(__current);
        try
        {
            ::TianShanIce::Streamer::PlaylistEx* __servant = dynamic_cast< ::TianShanIce::Streamer::PlaylistEx*>(__direct.servant().get());
            if(!__servant)
            {
                ::Ice::OperationNotExistException __opEx(__FILE__, __LINE__);
                __opEx.id = __current.id;
                __opEx.facet = __current.facet;
                __opEx.operation = __current.operation;
                throw __opEx;
            }
            try
            {
                __servant->onTimer(__current);
            }
            catch(const ::Ice::LocalException& __ex)
            {
                throw ::IceInternal::LocalExceptionWrapper(__ex, false);
            }
        }
        catch(...)
        {
            __direct.destroy();
            throw;
        }
        __direct.destroy();
        return;
    }
}

void
IceDelegateD::TianShanIce::Streamer::PlaylistItem::destroy(const ::Ice::Context* __context)
{
    ::Ice::Current __current;
    __initCurrent(__current, __TianShanIce__Streamer__PlaylistItem__destroy_name, ::Ice::Normal, __context);
    while(true)
    {
        ::IceInternal::Direct __direct(__current);
        try
        {
            ::TianShanIce::Streamer::PlaylistItem* __servant = dynamic_cast< ::TianShanIce::Streamer::PlaylistItem*>(__direct.servant().get());
            if(!__servant)
            {
                ::Ice::OperationNotExistException __opEx(__FILE__, __LINE__);
                __opEx.id = __current.id;
                __opEx.facet = __current.facet;
                __opEx.operation = __current.operation;
                throw __opEx;
            }
            try
            {
                __servant->destroy(__current);
            }
            catch(const ::Ice::LocalException& __ex)
            {
                throw ::IceInternal::LocalExceptionWrapper(__ex, false);
            }
        }
        catch(...)
        {
            __direct.destroy();
            throw;
        }
        __direct.destroy();
        return;
    }
}

::TianShanIce::Streamer::PlaylistItemAttr
IceDelegateD::TianShanIce::Streamer::PlaylistItem::getAttr(const ::Ice::Context* __context)
{
    ::Ice::Current __current;
    __initCurrent(__current, __TianShanIce__Streamer__PlaylistItem__getAttr_name, ::Ice::Normal, __context);
    while(true)
    {
        ::IceInternal::Direct __direct(__current);
        ::TianShanIce::Streamer::PlaylistItemAttr __ret;
        try
        {
            ::TianShanIce::Streamer::PlaylistItem* __servant = dynamic_cast< ::TianShanIce::Streamer::PlaylistItem*>(__direct.servant().get());
            if(!__servant)
            {
                ::Ice::OperationNotExistException __opEx(__FILE__, __LINE__);
                __opEx.id = __current.id;
                __opEx.facet = __current.facet;
                __opEx.operation = __current.operation;
                throw __opEx;
            }
            try
            {
                __ret = __servant->getAttr(__current);
            }
            catch(const ::Ice::LocalException& __ex)
            {
                throw ::IceInternal::LocalExceptionWrapper(__ex, false);
            }
        }
        catch(...)
        {
            __direct.destroy();
            throw;
        }
        __direct.destroy();
        return __ret;
    }
}

void
IceDelegateD::TianShanIce::Streamer::PlaylistItem::updateAttr(const ::TianShanIce::Streamer::PlaylistItemAttr& attr, const ::Ice::Context* __context)
{
    ::Ice::Current __current;
    __initCurrent(__current, __TianShanIce__Streamer__PlaylistItem__updateAttr_name, ::Ice::Normal, __context);
    while(true)
    {
        ::IceInternal::Direct __direct(__current);
        try
        {
            ::TianShanIce::Streamer::PlaylistItem* __servant = dynamic_cast< ::TianShanIce::Streamer::PlaylistItem*>(__direct.servant().get());
            if(!__servant)
            {
                ::Ice::OperationNotExistException __opEx(__FILE__, __LINE__);
                __opEx.id = __current.id;
                __opEx.facet = __current.facet;
                __opEx.operation = __current.operation;
                throw __opEx;
            }
            try
            {
                __servant->updateAttr(attr, __current);
            }
            catch(const ::Ice::LocalException& __ex)
            {
                throw ::IceInternal::LocalExceptionWrapper(__ex, false);
            }
        }
        catch(...)
        {
            __direct.destroy();
            throw;
        }
        __direct.destroy();
        return;
    }
}

::TianShanIce::Streamer::PlaylistIDs
IceDelegateD::TianShanIce::Streamer::StreamSmithAdmin::listPlaylists(const ::Ice::Context* __context)
{
    ::Ice::Current __current;
    __initCurrent(__current, __TianShanIce__Streamer__StreamSmithAdmin__listPlaylists_name, ::Ice::Normal, __context);
    while(true)
    {
        ::IceInternal::Direct __direct(__current);
        ::TianShanIce::Streamer::PlaylistIDs __ret;
        try
        {
            ::TianShanIce::Streamer::StreamSmithAdmin* __servant = dynamic_cast< ::TianShanIce::Streamer::StreamSmithAdmin*>(__direct.servant().get());
            if(!__servant)
            {
                ::Ice::OperationNotExistException __opEx(__FILE__, __LINE__);
                __opEx.id = __current.id;
                __opEx.facet = __current.facet;
                __opEx.operation = __current.operation;
                throw __opEx;
            }
            try
            {
                __ret = __servant->listPlaylists(__current);
            }
            catch(const ::Ice::LocalException& __ex)
            {
                throw ::IceInternal::LocalExceptionWrapper(__ex, false);
            }
        }
        catch(...)
        {
            __direct.destroy();
            throw;
        }
        __direct.destroy();
        return __ret;
    }
}

::TianShanIce::Streamer::PlaylistPrx
IceDelegateD::TianShanIce::Streamer::StreamSmithAdmin::openPlaylist(const ::std::string& guid, const ::TianShanIce::Streamer::SpigotBoards& EdgeCards, bool bCreateIfNotExist, const ::Ice::Context* __context)
{
    ::Ice::Current __current;
    __initCurrent(__current, __TianShanIce__Streamer__StreamSmithAdmin__openPlaylist_name, ::Ice::Normal, __context);
    while(true)
    {
        ::IceInternal::Direct __direct(__current);
        ::TianShanIce::Streamer::PlaylistPrx __ret;
        try
        {
            ::TianShanIce::Streamer::StreamSmithAdmin* __servant = dynamic_cast< ::TianShanIce::Streamer::StreamSmithAdmin*>(__direct.servant().get());
            if(!__servant)
            {
                ::Ice::OperationNotExistException __opEx(__FILE__, __LINE__);
                __opEx.id = __current.id;
                __opEx.facet = __current.facet;
                __opEx.operation = __current.operation;
                throw __opEx;
            }
            try
            {
                __ret = __servant->openPlaylist(guid, EdgeCards, bCreateIfNotExist, __current);
            }
            catch(const ::Ice::LocalException& __ex)
            {
                throw ::IceInternal::LocalExceptionWrapper(__ex, false);
            }
        }
        catch(...)
        {
            __direct.destroy();
            throw;
        }
        __direct.destroy();
        return __ret;
    }
}

::TianShanIce::Streamer::StreamBatchResponse
IceDelegateD::TianShanIce::Streamer::StreamSmithAdmin::createStreamBatch(const ::TianShanIce::Streamer::StreamBatchRequest&, const ::Ice::Context*)
{
    throw ::Ice::CollocationOptimizationException(__FILE__, __LINE__);
    return ::TianShanIce::Streamer::StreamBatchResponse(); // to avoid a warning with some compilers;
}

::std::string
IceDelegateD::TianShanIce::Streamer::StreamSmithAdmin::ShowMemory(const ::Ice::Context* __context)
{
    ::Ice::Current __current;
    __initCurrent(__current, __TianShanIce__Streamer__StreamSmithAdmin__ShowMemory_name, ::Ice::Normal, __context);
    while(true)
    {
        ::IceInternal::Direct __direct(__current);
        ::std::string __ret;
        try
        {
            ::TianShanIce::Streamer::StreamSmithAdmin* __servant = dynamic_cast< ::TianShanIce::Streamer::StreamSmithAdmin*>(__direct.servant().get());
            if(!__servant)
            {
                ::Ice::OperationNotExistException __opEx(__FILE__, __LINE__);
                __opEx.id = __current.id;
                __opEx.facet = __current.facet;
                __opEx.operation = __current.operation;
                throw __opEx;
            }
            try
            {
                __ret = __servant->ShowMemory(__current);
            }
            catch(const ::Ice::LocalException& __ex)
            {
                throw ::IceInternal::LocalExceptionWrapper(__ex, false);
            }
        }
        catch(...)
        {
            __direct.destroy();
            throw;
        }
        __direct.destroy();
        return __ret;
    }
}

TianShanIce::Streamer::PlaylistEx::PlaylistEx(const ::Ice::Identity& __ice_ident, const ::std::string& __ice_guid, const ::TianShanIce::Streamer::PlaylistAttr& __ice_attr) :
#if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
    Stream(__ice_ident)
#else
    ::TianShanIce::Streamer::Stream(__ice_ident)
#endif
,
#if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
    Playlist(__ice_ident)
#else
    ::TianShanIce::Streamer::Playlist(__ice_ident)
#endif
,
    guid(__ice_guid),
    attr(__ice_attr)
{
}

::Ice::ObjectPtr
TianShanIce::Streamer::PlaylistEx::ice_clone() const
{
    throw ::Ice::CloneNotImplementedException(__FILE__, __LINE__);
    return 0; // to avoid a warning with some compilers
}

static const ::std::string __TianShanIce__Streamer__PlaylistEx_ids[4] =
{
    "::Ice::Object",
    "::TianShanIce::Streamer::Playlist",
    "::TianShanIce::Streamer::PlaylistEx",
    "::TianShanIce::Streamer::Stream"
};

bool
TianShanIce::Streamer::PlaylistEx::ice_isA(const ::std::string& _s, const ::Ice::Current&) const
{
    return ::std::binary_search(__TianShanIce__Streamer__PlaylistEx_ids, __TianShanIce__Streamer__PlaylistEx_ids + 4, _s);
}

::std::vector< ::std::string>
TianShanIce::Streamer::PlaylistEx::ice_ids(const ::Ice::Current&) const
{
    return ::std::vector< ::std::string>(&__TianShanIce__Streamer__PlaylistEx_ids[0], &__TianShanIce__Streamer__PlaylistEx_ids[4]);
}

const ::std::string&
TianShanIce::Streamer::PlaylistEx::ice_id(const ::Ice::Current&) const
{
    return __TianShanIce__Streamer__PlaylistEx_ids[2];
}

const ::std::string&
TianShanIce::Streamer::PlaylistEx::ice_staticId()
{
    return __TianShanIce__Streamer__PlaylistEx_ids[2];
}

::IceInternal::DispatchStatus
TianShanIce::Streamer::PlaylistEx::___getAttr(::IceInternal::Incoming&__inS, const ::Ice::Current& __current)
{
    __checkMode(::Ice::Normal, __current.mode);
    ::IceInternal::BasicStream* __os = __inS.os();
    ::TianShanIce::Streamer::PlaylistAttr __ret = getAttr(__current);
    __ret.__write(__os);
    return ::IceInternal::DispatchOK;
}

::IceInternal::DispatchStatus
TianShanIce::Streamer::PlaylistEx::___updateAttr(::IceInternal::Incoming&__inS, const ::Ice::Current& __current)
{
    __checkMode(::Ice::Normal, __current.mode);
    ::IceInternal::BasicStream* __is = __inS.is();
    ::TianShanIce::Streamer::PlaylistAttr attr;
    attr.__read(__is);
    updateAttr(attr, __current);
    return ::IceInternal::DispatchOK;
}

::IceInternal::DispatchStatus
TianShanIce::Streamer::PlaylistEx::___attachSession(::IceInternal::Incoming&__inS, const ::Ice::Current& __current)
{
    __checkMode(::Ice::Normal, __current.mode);
    ::IceInternal::BasicStream* __is = __inS.is();
    ::TianShanIce::SRM::SessionPrx sess;
    ::TianShanIce::SRM::__read(__is, sess);
    attachSession(sess, __current);
    return ::IceInternal::DispatchOK;
}

::IceInternal::DispatchStatus
TianShanIce::Streamer::PlaylistEx::___setDestination(::IceInternal::Incoming&__inS, const ::Ice::Current& __current)
{
    __checkMode(::Ice::Normal, __current.mode);
    ::IceInternal::BasicStream* __is = __inS.is();
    ::std::string destIP;
    ::Ice::Int port;
    __is->read(destIP);
    __is->read(port);
    setDestination(destIP, port, __current);
    return ::IceInternal::DispatchOK;
}

::IceInternal::DispatchStatus
TianShanIce::Streamer::PlaylistEx::___setDestMac(::IceInternal::Incoming&__inS, const ::Ice::Current& __current)
{
    __checkMode(::Ice::Normal, __current.mode);
    ::IceInternal::BasicStream* __is = __inS.is();
    ::std::string strMac;
    __is->read(strMac);
    setDestMac(strMac, __current);
    return ::IceInternal::DispatchOK;
}

::IceInternal::DispatchStatus
TianShanIce::Streamer::PlaylistEx::___setSourceStrmPort(::IceInternal::Incoming&__inS, const ::Ice::Current& __current)
{
    __checkMode(::Ice::Normal, __current.mode);
    ::IceInternal::BasicStream* __is = __inS.is();
    ::Ice::Int port;
    __is->read(port);
    setSourceStrmPort(port, __current);
    return ::IceInternal::DispatchOK;
}

::IceInternal::DispatchStatus
TianShanIce::Streamer::PlaylistEx::___setPID(::IceInternal::Incoming&__inS, const ::Ice::Current& __current)
{
    __checkMode(::Ice::Normal, __current.mode);
    ::IceInternal::BasicStream* __is = __inS.is();
    ::Ice::Int pid;
    __is->read(pid);
    setPID(pid, __current);
    return ::IceInternal::DispatchOK;
}

::IceInternal::DispatchStatus
TianShanIce::Streamer::PlaylistEx::___onTimer(::IceInternal::Incoming&, const ::Ice::Current& __current)
{
    __checkMode(::Ice::Normal, __current.mode);
    onTimer(__current);
    return ::IceInternal::DispatchOK;
}

static ::std::string __TianShanIce__Streamer__PlaylistEx_all[] =
{
    "allocDVBCResource",
    "allotPathTicket",
    "attachSession",
    "clearPending",
    "commit",
    "current",
    "destroy",
    "destroy2",
    "distance",
    "empty",
    "enableEoT",
    "erase",
    "findItem",
    "flushExpired",
    "getAttr",
    "getCurrentState",
    "getId",
    "getIdent",
    "getInfo",
    "getPlaylistItems",
    "getProperties",
    "getResources",
    "getSequence",
    "getSession",
    "ice_id",
    "ice_ids",
    "ice_isA",
    "ice_ping",
    "insert",
    "isCompleted",
    "lastError",
    "left",
    "onTimer",
    "pause",
    "pauseEx",
    "play",
    "playEx",
    "playItem",
    "pushBack",
    "resume",
    "seekStream",
    "seekToPosition",
    "setConditionalControl",
    "setDestMac",
    "setDestination",
    "setMuxRate",
    "setPID",
    "setProperties",
    "setSourceStrmPort",
    "setSpeed",
    "size",
    "skipToItem",
    "updateAttr"
};

::IceInternal::DispatchStatus
TianShanIce::Streamer::PlaylistEx::__dispatch(::IceInternal::Incoming& in, const ::Ice::Current& current)
{
    ::std::pair< ::std::string*, ::std::string*> r = ::std::equal_range(__TianShanIce__Streamer__PlaylistEx_all, __TianShanIce__Streamer__PlaylistEx_all + 53, current.operation);
    if(r.first == r.second)
    {
        return ::IceInternal::DispatchOperationNotExist;
    }

    switch(r.first - __TianShanIce__Streamer__PlaylistEx_all)
    {
        case 0:
        {
            return ___allocDVBCResource(in, current);
        }
        case 1:
        {
            return ___allotPathTicket(in, current);
        }
        case 2:
        {
            return ___attachSession(in, current);
        }
        case 3:
        {
            return ___clearPending(in, current);
        }
        case 4:
        {
            return ___commit(in, current);
        }
        case 5:
        {
            return ___current(in, current);
        }
        case 6:
        {
            return ___destroy(in, current);
        }
        case 7:
        {
            return ___destroy2(in, current);
        }
        case 8:
        {
            return ___distance(in, current);
        }
        case 9:
        {
            return ___empty(in, current);
        }
        case 10:
        {
            return ___enableEoT(in, current);
        }
        case 11:
        {
            return ___erase(in, current);
        }
        case 12:
        {
            return ___findItem(in, current);
        }
        case 13:
        {
            return ___flushExpired(in, current);
        }
        case 14:
        {
            return ___getAttr(in, current);
        }
        case 15:
        {
            return ___getCurrentState(in, current);
        }
        case 16:
        {
            return ___getId(in, current);
        }
        case 17:
        {
            return ___getIdent(in, current);
        }
        case 18:
        {
            return ___getInfo(in, current);
        }
        case 19:
        {
            return ___getPlaylistItems(in, current);
        }
        case 20:
        {
            return ___getProperties(in, current);
        }
        case 21:
        {
            return ___getResources(in, current);
        }
        case 22:
        {
            return ___getSequence(in, current);
        }
        case 23:
        {
            return ___getSession(in, current);
        }
        case 24:
        {
            return ___ice_id(in, current);
        }
        case 25:
        {
            return ___ice_ids(in, current);
        }
        case 26:
        {
            return ___ice_isA(in, current);
        }
        case 27:
        {
            return ___ice_ping(in, current);
        }
        case 28:
        {
            return ___insert(in, current);
        }
        case 29:
        {
            return ___isCompleted(in, current);
        }
        case 30:
        {
            return ___lastError(in, current);
        }
        case 31:
        {
            return ___left(in, current);
        }
        case 32:
        {
            return ___onTimer(in, current);
        }
        case 33:
        {
            return ___pause(in, current);
        }
        case 34:
        {
            return ___pauseEx(in, current);
        }
        case 35:
        {
            return ___play(in, current);
        }
        case 36:
        {
            return ___playEx(in, current);
        }
        case 37:
        {
            return ___playItem(in, current);
        }
        case 38:
        {
            return ___pushBack(in, current);
        }
        case 39:
        {
            return ___resume(in, current);
        }
        case 40:
        {
            return ___seekStream(in, current);
        }
        case 41:
        {
            return ___seekToPosition(in, current);
        }
        case 42:
        {
            return ___setConditionalControl(in, current);
        }
        case 43:
        {
            return ___setDestMac(in, current);
        }
        case 44:
        {
            return ___setDestination(in, current);
        }
        case 45:
        {
            return ___setMuxRate(in, current);
        }
        case 46:
        {
            return ___setPID(in, current);
        }
        case 47:
        {
            return ___setProperties(in, current);
        }
        case 48:
        {
            return ___setSourceStrmPort(in, current);
        }
        case 49:
        {
            return ___setSpeed(in, current);
        }
        case 50:
        {
            return ___size(in, current);
        }
        case 51:
        {
            return ___skipToItem(in, current);
        }
        case 52:
        {
            return ___updateAttr(in, current);
        }
    }

    assert(false);
    return ::IceInternal::DispatchOperationNotExist;
}

static ::std::string __TianShanIce__Streamer__PlaylistEx_freezeWriteOperations[] =
{
    "allocDVBCResource",
    "allotPathTicket",
    "attachSession",
    "clearPending",
    "commit",
    "destroy",
    "destroy2",
    "distance",
    "enableEoT",
    "erase",
    "findItem",
    "flushExpired",
    "getAttr",
    "getCurrentState",
    "getInfo",
    "getSession",
    "insert",
    "isCompleted",
    "onTimer",
    "pause",
    "pauseEx",
    "play",
    "playEx",
    "playItem",
    "pushBack",
    "resume",
    "seekStream",
    "seekToPosition",
    "setConditionalControl",
    "setDestMac",
    "setDestination",
    "setMuxRate",
    "setPID",
    "setProperties",
    "setSourceStrmPort",
    "setSpeed",
    "skipToItem",
    "updateAttr"
};

::Ice::Int
TianShanIce::Streamer::PlaylistEx::ice_operationAttributes(const ::std::string& opName) const
{
    ::std::string* end = __TianShanIce__Streamer__PlaylistEx_freezeWriteOperations + 38;
    ::std::string* r = ::std::find(__TianShanIce__Streamer__PlaylistEx_freezeWriteOperations, end, opName);
    return r == end ? 0 : 1;
}

void
TianShanIce::Streamer::PlaylistEx::__write(::IceInternal::BasicStream* __os) const
{
    __os->writeTypeId(ice_staticId());
    __os->startWriteSlice();
    __os->write(guid);
    attr.__write(__os);
    __os->endWriteSlice();
#if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
    Playlist::__write(__os);
#else
    ::TianShanIce::Streamer::Playlist::__write(__os);
#endif
}

void
TianShanIce::Streamer::PlaylistEx::__read(::IceInternal::BasicStream* __is, bool __rid)
{
    if(__rid)
    {
        ::std::string myId;
        __is->readTypeId(myId);
    }
    __is->startReadSlice();
    __is->read(guid);
    attr.__read(__is);
    __is->endReadSlice();
#if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
    Playlist::__read(__is, true);
#else
    ::TianShanIce::Streamer::Playlist::__read(__is, true);
#endif
}

void
TianShanIce::Streamer::PlaylistEx::__write(const ::Ice::OutputStreamPtr&) const
{
    Ice::MarshalException ex(__FILE__, __LINE__);
    ex.reason = "type TianShanIce::Streamer::PlaylistEx was not generated with stream support";
    throw ex;
}

void
TianShanIce::Streamer::PlaylistEx::__read(const ::Ice::InputStreamPtr&, bool)
{
    Ice::MarshalException ex(__FILE__, __LINE__);
    ex.reason = "type TianShanIce::Streamer::PlaylistEx was not generated with stream support";
    throw ex;
}

void 
TianShanIce::Streamer::__patch__PlaylistExPtr(void* __addr, ::Ice::ObjectPtr& v)
{
    ::TianShanIce::Streamer::PlaylistExPtr* p = static_cast< ::TianShanIce::Streamer::PlaylistExPtr*>(__addr);
    assert(p);
    *p = ::TianShanIce::Streamer::PlaylistExPtr::dynamicCast(v);
    if(v && !*p)
    {
        ::Ice::UnexpectedObjectException e(__FILE__, __LINE__);
        e.type = v->ice_id();
        e.expectedType = ::TianShanIce::Streamer::PlaylistEx::ice_staticId();
        throw e;
    }
}

bool
TianShanIce::Streamer::operator==(const ::TianShanIce::Streamer::PlaylistEx& l, const ::TianShanIce::Streamer::PlaylistEx& r)
{
    return static_cast<const ::Ice::Object&>(l) == static_cast<const ::Ice::Object&>(r);
}

bool
TianShanIce::Streamer::operator!=(const ::TianShanIce::Streamer::PlaylistEx& l, const ::TianShanIce::Streamer::PlaylistEx& r)
{
    return static_cast<const ::Ice::Object&>(l) != static_cast<const ::Ice::Object&>(r);
}

bool
TianShanIce::Streamer::operator<(const ::TianShanIce::Streamer::PlaylistEx& l, const ::TianShanIce::Streamer::PlaylistEx& r)
{
    return static_cast<const ::Ice::Object&>(l) < static_cast<const ::Ice::Object&>(r);
}

bool
TianShanIce::Streamer::operator<=(const ::TianShanIce::Streamer::PlaylistEx& l, const ::TianShanIce::Streamer::PlaylistEx& r)
{
    return l < r || l == r;
}

bool
TianShanIce::Streamer::operator>(const ::TianShanIce::Streamer::PlaylistEx& l, const ::TianShanIce::Streamer::PlaylistEx& r)
{
    return !(l < r) && !(l == r);
}

bool
TianShanIce::Streamer::operator>=(const ::TianShanIce::Streamer::PlaylistEx& l, const ::TianShanIce::Streamer::PlaylistEx& r)
{
    return !(l < r);
}

TianShanIce::Streamer::PlaylistItem::PlaylistItem(const ::std::string& __ice_guid, const ::TianShanIce::Streamer::PlaylistItemAttr& __ice_attr) :
    guid(__ice_guid),
    attr(__ice_attr)
{
}

::Ice::ObjectPtr
TianShanIce::Streamer::PlaylistItem::ice_clone() const
{
    throw ::Ice::CloneNotImplementedException(__FILE__, __LINE__);
    return 0; // to avoid a warning with some compilers
}

static const ::std::string __TianShanIce__Streamer__PlaylistItem_ids[2] =
{
    "::Ice::Object",
    "::TianShanIce::Streamer::PlaylistItem"
};

bool
TianShanIce::Streamer::PlaylistItem::ice_isA(const ::std::string& _s, const ::Ice::Current&) const
{
    return ::std::binary_search(__TianShanIce__Streamer__PlaylistItem_ids, __TianShanIce__Streamer__PlaylistItem_ids + 2, _s);
}

::std::vector< ::std::string>
TianShanIce::Streamer::PlaylistItem::ice_ids(const ::Ice::Current&) const
{
    return ::std::vector< ::std::string>(&__TianShanIce__Streamer__PlaylistItem_ids[0], &__TianShanIce__Streamer__PlaylistItem_ids[2]);
}

const ::std::string&
TianShanIce::Streamer::PlaylistItem::ice_id(const ::Ice::Current&) const
{
    return __TianShanIce__Streamer__PlaylistItem_ids[1];
}

const ::std::string&
TianShanIce::Streamer::PlaylistItem::ice_staticId()
{
    return __TianShanIce__Streamer__PlaylistItem_ids[1];
}

::IceInternal::DispatchStatus
TianShanIce::Streamer::PlaylistItem::___destroy(::IceInternal::Incoming&, const ::Ice::Current& __current)
{
    __checkMode(::Ice::Normal, __current.mode);
    destroy(__current);
    return ::IceInternal::DispatchOK;
}

::IceInternal::DispatchStatus
TianShanIce::Streamer::PlaylistItem::___getAttr(::IceInternal::Incoming&__inS, const ::Ice::Current& __current) const
{
    __checkMode(::Ice::Normal, __current.mode);
    ::IceInternal::BasicStream* __os = __inS.os();
    ::TianShanIce::Streamer::PlaylistItemAttr __ret = getAttr(__current);
    __ret.__write(__os);
    return ::IceInternal::DispatchOK;
}

::IceInternal::DispatchStatus
TianShanIce::Streamer::PlaylistItem::___updateAttr(::IceInternal::Incoming&__inS, const ::Ice::Current& __current)
{
    __checkMode(::Ice::Normal, __current.mode);
    ::IceInternal::BasicStream* __is = __inS.is();
    ::TianShanIce::Streamer::PlaylistItemAttr attr;
    attr.__read(__is);
    updateAttr(attr, __current);
    return ::IceInternal::DispatchOK;
}

static ::std::string __TianShanIce__Streamer__PlaylistItem_all[] =
{
    "destroy",
    "getAttr",
    "ice_id",
    "ice_ids",
    "ice_isA",
    "ice_ping",
    "updateAttr"
};

::IceInternal::DispatchStatus
TianShanIce::Streamer::PlaylistItem::__dispatch(::IceInternal::Incoming& in, const ::Ice::Current& current)
{
    ::std::pair< ::std::string*, ::std::string*> r = ::std::equal_range(__TianShanIce__Streamer__PlaylistItem_all, __TianShanIce__Streamer__PlaylistItem_all + 7, current.operation);
    if(r.first == r.second)
    {
        return ::IceInternal::DispatchOperationNotExist;
    }

    switch(r.first - __TianShanIce__Streamer__PlaylistItem_all)
    {
        case 0:
        {
            return ___destroy(in, current);
        }
        case 1:
        {
            return ___getAttr(in, current);
        }
        case 2:
        {
            return ___ice_id(in, current);
        }
        case 3:
        {
            return ___ice_ids(in, current);
        }
        case 4:
        {
            return ___ice_isA(in, current);
        }
        case 5:
        {
            return ___ice_ping(in, current);
        }
        case 6:
        {
            return ___updateAttr(in, current);
        }
    }

    assert(false);
    return ::IceInternal::DispatchOperationNotExist;
}

static ::std::string __TianShanIce__Streamer__PlaylistItem_freezeWriteOperations[] =
{
    "destroy",
    "updateAttr"
};

::Ice::Int
TianShanIce::Streamer::PlaylistItem::ice_operationAttributes(const ::std::string& opName) const
{
    ::std::string* end = __TianShanIce__Streamer__PlaylistItem_freezeWriteOperations + 2;
    ::std::string* r = ::std::find(__TianShanIce__Streamer__PlaylistItem_freezeWriteOperations, end, opName);
    return r == end ? 0 : 1;
}

void
TianShanIce::Streamer::PlaylistItem::__write(::IceInternal::BasicStream* __os) const
{
    __os->writeTypeId(ice_staticId());
    __os->startWriteSlice();
    __os->write(guid);
    attr.__write(__os);
    __os->endWriteSlice();
#if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
    Object::__write(__os);
#else
    ::Ice::Object::__write(__os);
#endif
}

void
TianShanIce::Streamer::PlaylistItem::__read(::IceInternal::BasicStream* __is, bool __rid)
{
    if(__rid)
    {
        ::std::string myId;
        __is->readTypeId(myId);
    }
    __is->startReadSlice();
    __is->read(guid);
    attr.__read(__is);
    __is->endReadSlice();
#if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
    Object::__read(__is, true);
#else
    ::Ice::Object::__read(__is, true);
#endif
}

void
TianShanIce::Streamer::PlaylistItem::__write(const ::Ice::OutputStreamPtr&) const
{
    Ice::MarshalException ex(__FILE__, __LINE__);
    ex.reason = "type TianShanIce::Streamer::PlaylistItem was not generated with stream support";
    throw ex;
}

void
TianShanIce::Streamer::PlaylistItem::__read(const ::Ice::InputStreamPtr&, bool)
{
    Ice::MarshalException ex(__FILE__, __LINE__);
    ex.reason = "type TianShanIce::Streamer::PlaylistItem was not generated with stream support";
    throw ex;
}

void 
TianShanIce::Streamer::__patch__PlaylistItemPtr(void* __addr, ::Ice::ObjectPtr& v)
{
    ::TianShanIce::Streamer::PlaylistItemPtr* p = static_cast< ::TianShanIce::Streamer::PlaylistItemPtr*>(__addr);
    assert(p);
    *p = ::TianShanIce::Streamer::PlaylistItemPtr::dynamicCast(v);
    if(v && !*p)
    {
        ::Ice::UnexpectedObjectException e(__FILE__, __LINE__);
        e.type = v->ice_id();
        e.expectedType = ::TianShanIce::Streamer::PlaylistItem::ice_staticId();
        throw e;
    }
}

bool
TianShanIce::Streamer::operator==(const ::TianShanIce::Streamer::PlaylistItem& l, const ::TianShanIce::Streamer::PlaylistItem& r)
{
    return static_cast<const ::Ice::Object&>(l) == static_cast<const ::Ice::Object&>(r);
}

bool
TianShanIce::Streamer::operator!=(const ::TianShanIce::Streamer::PlaylistItem& l, const ::TianShanIce::Streamer::PlaylistItem& r)
{
    return static_cast<const ::Ice::Object&>(l) != static_cast<const ::Ice::Object&>(r);
}

bool
TianShanIce::Streamer::operator<(const ::TianShanIce::Streamer::PlaylistItem& l, const ::TianShanIce::Streamer::PlaylistItem& r)
{
    return static_cast<const ::Ice::Object&>(l) < static_cast<const ::Ice::Object&>(r);
}

bool
TianShanIce::Streamer::operator<=(const ::TianShanIce::Streamer::PlaylistItem& l, const ::TianShanIce::Streamer::PlaylistItem& r)
{
    return l < r || l == r;
}

bool
TianShanIce::Streamer::operator>(const ::TianShanIce::Streamer::PlaylistItem& l, const ::TianShanIce::Streamer::PlaylistItem& r)
{
    return !(l < r) && !(l == r);
}

bool
TianShanIce::Streamer::operator>=(const ::TianShanIce::Streamer::PlaylistItem& l, const ::TianShanIce::Streamer::PlaylistItem& r)
{
    return !(l < r);
}

::Ice::ObjectPtr
TianShanIce::Streamer::StreamSmithAdmin::ice_clone() const
{
    throw ::Ice::CloneNotImplementedException(__FILE__, __LINE__);
    return 0; // to avoid a warning with some compilers
}

static const ::std::string __TianShanIce__Streamer__StreamSmithAdmin_ids[6] =
{
    "::Ice::Object",
    "::TianShanIce::BaseService",
    "::TianShanIce::ReplicaQuery",
    "::TianShanIce::Streamer::StreamService",
    "::TianShanIce::Streamer::StreamSmith",
    "::TianShanIce::Streamer::StreamSmithAdmin"
};

bool
TianShanIce::Streamer::StreamSmithAdmin::ice_isA(const ::std::string& _s, const ::Ice::Current&) const
{
    return ::std::binary_search(__TianShanIce__Streamer__StreamSmithAdmin_ids, __TianShanIce__Streamer__StreamSmithAdmin_ids + 6, _s);
}

::std::vector< ::std::string>
TianShanIce::Streamer::StreamSmithAdmin::ice_ids(const ::Ice::Current&) const
{
    return ::std::vector< ::std::string>(&__TianShanIce__Streamer__StreamSmithAdmin_ids[0], &__TianShanIce__Streamer__StreamSmithAdmin_ids[6]);
}

const ::std::string&
TianShanIce::Streamer::StreamSmithAdmin::ice_id(const ::Ice::Current&) const
{
    return __TianShanIce__Streamer__StreamSmithAdmin_ids[5];
}

const ::std::string&
TianShanIce::Streamer::StreamSmithAdmin::ice_staticId()
{
    return __TianShanIce__Streamer__StreamSmithAdmin_ids[5];
}

::IceInternal::DispatchStatus
TianShanIce::Streamer::StreamSmithAdmin::___listPlaylists(::IceInternal::Incoming&__inS, const ::Ice::Current& __current)
{
    __checkMode(::Ice::Normal, __current.mode);
    ::IceInternal::BasicStream* __os = __inS.os();
    ::TianShanIce::Streamer::PlaylistIDs __ret = listPlaylists(__current);
    if(__ret.size() == 0)
    {
        __os->writeSize(0);
    }
    else
    {
        __os->write(&__ret[0], &__ret[0] + __ret.size());
    }
    return ::IceInternal::DispatchOK;
}

::IceInternal::DispatchStatus
TianShanIce::Streamer::StreamSmithAdmin::___openPlaylist(::IceInternal::Incoming&__inS, const ::Ice::Current& __current)
{
    __checkMode(::Ice::Normal, __current.mode);
    ::IceInternal::BasicStream* __is = __inS.is();
    ::IceInternal::BasicStream* __os = __inS.os();
    ::std::string guid;
    ::TianShanIce::Streamer::SpigotBoards EdgeCards;
    bool bCreateIfNotExist;
    __is->read(guid);
    __is->read(EdgeCards);
    __is->read(bCreateIfNotExist);
    ::TianShanIce::Streamer::PlaylistPrx __ret = openPlaylist(guid, EdgeCards, bCreateIfNotExist, __current);
    ::TianShanIce::Streamer::__write(__os, __ret);
    return ::IceInternal::DispatchOK;
}

::IceInternal::DispatchStatus
TianShanIce::Streamer::StreamSmithAdmin::___createStreamBatch(::IceInternal::Incoming&__inS, const ::Ice::Current& __current)
{
    __checkMode(::Ice::Normal, __current.mode);
    ::IceInternal::BasicStream* __is = __inS.is();
    ::TianShanIce::Streamer::StreamBatchRequest req;
    ::TianShanIce::Streamer::__read(__is, req, ::TianShanIce::Streamer::__U__StreamBatchRequest());
    ::TianShanIce::Streamer::AMD_StreamSmithAdmin_createStreamBatchPtr __cb = new IceAsync::TianShanIce::Streamer::AMD_StreamSmithAdmin_createStreamBatch(__inS);
    try
    {
        createStreamBatch_async(__cb, req, __current);
    }
    catch(const ::Ice::Exception& __ex)
    {
        __cb->ice_exception(__ex);
    }
    catch(const ::std::exception& __ex)
    {
        __cb->ice_exception(__ex);
    }
    catch(...)
    {
        __cb->ice_exception();
    }
    return ::IceInternal::DispatchAsync;
}

::IceInternal::DispatchStatus
TianShanIce::Streamer::StreamSmithAdmin::___ShowMemory(::IceInternal::Incoming&__inS, const ::Ice::Current& __current)
{
    __checkMode(::Ice::Normal, __current.mode);
    ::IceInternal::BasicStream* __os = __inS.os();
    ::std::string __ret = ShowMemory(__current);
    __os->write(__ret);
    return ::IceInternal::DispatchOK;
}

static ::std::string __TianShanIce__Streamer__StreamSmithAdmin_all[] =
{
    "ShowMemory",
    "createStream",
    "createStreamBatch",
    "createStreamByResource",
    "getAdminUri",
    "getNetId",
    "getState",
    "ice_id",
    "ice_ids",
    "ice_isA",
    "ice_ping",
    "listPlaylists",
    "listStreamers",
    "openPlaylist",
    "openStream",
    "queryReplicas"
};

::IceInternal::DispatchStatus
TianShanIce::Streamer::StreamSmithAdmin::__dispatch(::IceInternal::Incoming& in, const ::Ice::Current& current)
{
    ::std::pair< ::std::string*, ::std::string*> r = ::std::equal_range(__TianShanIce__Streamer__StreamSmithAdmin_all, __TianShanIce__Streamer__StreamSmithAdmin_all + 16, current.operation);
    if(r.first == r.second)
    {
        return ::IceInternal::DispatchOperationNotExist;
    }

    switch(r.first - __TianShanIce__Streamer__StreamSmithAdmin_all)
    {
        case 0:
        {
            return ___ShowMemory(in, current);
        }
        case 1:
        {
            return ___createStream(in, current);
        }
        case 2:
        {
            return ___createStreamBatch(in, current);
        }
        case 3:
        {
            return ___createStreamByResource(in, current);
        }
        case 4:
        {
            return ___getAdminUri(in, current);
        }
        case 5:
        {
            return ___getNetId(in, current);
        }
        case 6:
        {
            return ___getState(in, current);
        }
        case 7:
        {
            return ___ice_id(in, current);
        }
        case 8:
        {
            return ___ice_ids(in, current);
        }
        case 9:
        {
            return ___ice_isA(in, current);
        }
        case 10:
        {
            return ___ice_ping(in, current);
        }
        case 11:
        {
            return ___listPlaylists(in, current);
        }
        case 12:
        {
            return ___listStreamers(in, current);
        }
        case 13:
        {
            return ___openPlaylist(in, current);
        }
        case 14:
        {
            return ___openStream(in, current);
        }
        case 15:
        {
            return ___queryReplicas(in, current);
        }
    }

    assert(false);
    return ::IceInternal::DispatchOperationNotExist;
}

void
TianShanIce::Streamer::StreamSmithAdmin::__write(::IceInternal::BasicStream* __os) const
{
    __os->writeTypeId(ice_staticId());
    __os->startWriteSlice();
    __os->endWriteSlice();
#if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
    Object::__write(__os);
#else
    ::Ice::Object::__write(__os);
#endif
}

void
TianShanIce::Streamer::StreamSmithAdmin::__read(::IceInternal::BasicStream* __is, bool __rid)
{
    if(__rid)
    {
        ::std::string myId;
        __is->readTypeId(myId);
    }
    __is->startReadSlice();
    __is->endReadSlice();
#if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
    Object::__read(__is, true);
#else
    ::Ice::Object::__read(__is, true);
#endif
}

void
TianShanIce::Streamer::StreamSmithAdmin::__write(const ::Ice::OutputStreamPtr&) const
{
    Ice::MarshalException ex(__FILE__, __LINE__);
    ex.reason = "type TianShanIce::Streamer::StreamSmithAdmin was not generated with stream support";
    throw ex;
}

void
TianShanIce::Streamer::StreamSmithAdmin::__read(const ::Ice::InputStreamPtr&, bool)
{
    Ice::MarshalException ex(__FILE__, __LINE__);
    ex.reason = "type TianShanIce::Streamer::StreamSmithAdmin was not generated with stream support";
    throw ex;
}

void 
TianShanIce::Streamer::__patch__StreamSmithAdminPtr(void* __addr, ::Ice::ObjectPtr& v)
{
    ::TianShanIce::Streamer::StreamSmithAdminPtr* p = static_cast< ::TianShanIce::Streamer::StreamSmithAdminPtr*>(__addr);
    assert(p);
    *p = ::TianShanIce::Streamer::StreamSmithAdminPtr::dynamicCast(v);
    if(v && !*p)
    {
        ::Ice::UnexpectedObjectException e(__FILE__, __LINE__);
        e.type = v->ice_id();
        e.expectedType = ::TianShanIce::Streamer::StreamSmithAdmin::ice_staticId();
        throw e;
    }
}

bool
TianShanIce::Streamer::operator==(const ::TianShanIce::Streamer::StreamSmithAdmin& l, const ::TianShanIce::Streamer::StreamSmithAdmin& r)
{
    return static_cast<const ::Ice::Object&>(l) == static_cast<const ::Ice::Object&>(r);
}

bool
TianShanIce::Streamer::operator!=(const ::TianShanIce::Streamer::StreamSmithAdmin& l, const ::TianShanIce::Streamer::StreamSmithAdmin& r)
{
    return static_cast<const ::Ice::Object&>(l) != static_cast<const ::Ice::Object&>(r);
}

bool
TianShanIce::Streamer::operator<(const ::TianShanIce::Streamer::StreamSmithAdmin& l, const ::TianShanIce::Streamer::StreamSmithAdmin& r)
{
    return static_cast<const ::Ice::Object&>(l) < static_cast<const ::Ice::Object&>(r);
}

bool
TianShanIce::Streamer::operator<=(const ::TianShanIce::Streamer::StreamSmithAdmin& l, const ::TianShanIce::Streamer::StreamSmithAdmin& r)
{
    return l < r || l == r;
}

bool
TianShanIce::Streamer::operator>(const ::TianShanIce::Streamer::StreamSmithAdmin& l, const ::TianShanIce::Streamer::StreamSmithAdmin& r)
{
    return !(l < r) && !(l == r);
}

bool
TianShanIce::Streamer::operator>=(const ::TianShanIce::Streamer::StreamSmithAdmin& l, const ::TianShanIce::Streamer::StreamSmithAdmin& r)
{
    return !(l < r);
}
