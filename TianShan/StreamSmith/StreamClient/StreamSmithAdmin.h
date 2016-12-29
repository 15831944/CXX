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

#ifndef __StreamSmithAdmin_h__
#define __StreamSmithAdmin_h__

#include <Ice/LocalObjectF.h>
#include <Ice/ProxyF.h>
#include <Ice/ObjectF.h>
#include <Ice/Exception.h>
#include <Ice/LocalObject.h>
#include <Ice/Proxy.h>
#include <Ice/Object.h>
#include <Ice/Outgoing.h>
#include <Ice/OutgoingAsync.h>
#include <Ice/Incoming.h>
#include <Ice/IncomingAsync.h>
#include <Ice/Direct.h>
#include <Ice/UserExceptionFactory.h>
#include <Ice/FactoryTable.h>
#include <Ice/StreamF.h>
#include <TsStreamer.h>
#include <Ice/UndefSysMacros.h>

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

namespace IceProxy
{

namespace TianShanIce
{

namespace Weiwoo
{

class Session;
bool operator==(const Session&, const Session&);
bool operator!=(const Session&, const Session&);
bool operator<(const Session&, const Session&);
bool operator<=(const Session&, const Session&);
bool operator>(const Session&, const Session&);
bool operator>=(const Session&, const Session&);

}

namespace Streamer
{

class PlaylistEx;
bool operator==(const PlaylistEx&, const PlaylistEx&);
bool operator!=(const PlaylistEx&, const PlaylistEx&);
bool operator<(const PlaylistEx&, const PlaylistEx&);
bool operator<=(const PlaylistEx&, const PlaylistEx&);
bool operator>(const PlaylistEx&, const PlaylistEx&);
bool operator>=(const PlaylistEx&, const PlaylistEx&);

class PlaylistItem;
bool operator==(const PlaylistItem&, const PlaylistItem&);
bool operator!=(const PlaylistItem&, const PlaylistItem&);
bool operator<(const PlaylistItem&, const PlaylistItem&);
bool operator<=(const PlaylistItem&, const PlaylistItem&);
bool operator>(const PlaylistItem&, const PlaylistItem&);
bool operator>=(const PlaylistItem&, const PlaylistItem&);

class StreamSmithAdmin;
bool operator==(const StreamSmithAdmin&, const StreamSmithAdmin&);
bool operator!=(const StreamSmithAdmin&, const StreamSmithAdmin&);
bool operator<(const StreamSmithAdmin&, const StreamSmithAdmin&);
bool operator<=(const StreamSmithAdmin&, const StreamSmithAdmin&);
bool operator>(const StreamSmithAdmin&, const StreamSmithAdmin&);
bool operator>=(const StreamSmithAdmin&, const StreamSmithAdmin&);

}

}

}

namespace TianShanIce
{

namespace Weiwoo
{

class Session;
bool operator==(const Session&, const Session&);
bool operator!=(const Session&, const Session&);
bool operator<(const Session&, const Session&);
bool operator<=(const Session&, const Session&);
bool operator>(const Session&, const Session&);
bool operator>=(const Session&, const Session&);

}

namespace Streamer
{

class PlaylistEx;
bool operator==(const PlaylistEx&, const PlaylistEx&);
bool operator!=(const PlaylistEx&, const PlaylistEx&);
bool operator<(const PlaylistEx&, const PlaylistEx&);
bool operator<=(const PlaylistEx&, const PlaylistEx&);
bool operator>(const PlaylistEx&, const PlaylistEx&);
bool operator>=(const PlaylistEx&, const PlaylistEx&);

class PlaylistItem;
bool operator==(const PlaylistItem&, const PlaylistItem&);
bool operator!=(const PlaylistItem&, const PlaylistItem&);
bool operator<(const PlaylistItem&, const PlaylistItem&);
bool operator<=(const PlaylistItem&, const PlaylistItem&);
bool operator>(const PlaylistItem&, const PlaylistItem&);
bool operator>=(const PlaylistItem&, const PlaylistItem&);

class StreamSmithAdmin;
bool operator==(const StreamSmithAdmin&, const StreamSmithAdmin&);
bool operator!=(const StreamSmithAdmin&, const StreamSmithAdmin&);
bool operator<(const StreamSmithAdmin&, const StreamSmithAdmin&);
bool operator<=(const StreamSmithAdmin&, const StreamSmithAdmin&);
bool operator>(const StreamSmithAdmin&, const StreamSmithAdmin&);
bool operator>=(const StreamSmithAdmin&, const StreamSmithAdmin&);

}

}

namespace IceInternal
{

void incRef(::TianShanIce::Weiwoo::Session*);
void decRef(::TianShanIce::Weiwoo::Session*);

void incRef(::IceProxy::TianShanIce::Weiwoo::Session*);
void decRef(::IceProxy::TianShanIce::Weiwoo::Session*);

void incRef(::TianShanIce::Streamer::PlaylistEx*);
void decRef(::TianShanIce::Streamer::PlaylistEx*);

void incRef(::IceProxy::TianShanIce::Streamer::PlaylistEx*);
void decRef(::IceProxy::TianShanIce::Streamer::PlaylistEx*);

void incRef(::TianShanIce::Streamer::PlaylistItem*);
void decRef(::TianShanIce::Streamer::PlaylistItem*);

void incRef(::IceProxy::TianShanIce::Streamer::PlaylistItem*);
void decRef(::IceProxy::TianShanIce::Streamer::PlaylistItem*);

void incRef(::TianShanIce::Streamer::StreamSmithAdmin*);
void decRef(::TianShanIce::Streamer::StreamSmithAdmin*);

void incRef(::IceProxy::TianShanIce::Streamer::StreamSmithAdmin*);
void decRef(::IceProxy::TianShanIce::Streamer::StreamSmithAdmin*);

}

namespace TianShanIce
{

namespace Weiwoo
{

typedef ::IceInternal::Handle< ::TianShanIce::Weiwoo::Session> SessionPtr;
typedef ::IceInternal::ProxyHandle< ::IceProxy::TianShanIce::Weiwoo::Session> SessionPrx;

void __write(::IceInternal::BasicStream*, const SessionPrx&);
void __read(::IceInternal::BasicStream*, SessionPrx&);
void __write(::IceInternal::BasicStream*, const SessionPtr&);
void __patch__SessionPtr(void*, ::Ice::ObjectPtr&);

void __addObject(const SessionPtr&, ::IceInternal::GCCountMap&);
bool __usesClasses(const SessionPtr&);
void __decRefUnsafe(const SessionPtr&);
void __clearHandleUnsafe(SessionPtr&);

}

namespace Streamer
{

typedef ::IceInternal::Handle< ::TianShanIce::Streamer::PlaylistEx> PlaylistExPtr;
typedef ::IceInternal::ProxyHandle< ::IceProxy::TianShanIce::Streamer::PlaylistEx> PlaylistExPrx;

void __write(::IceInternal::BasicStream*, const PlaylistExPrx&);
void __read(::IceInternal::BasicStream*, PlaylistExPrx&);
void __write(::IceInternal::BasicStream*, const PlaylistExPtr&);
void __patch__PlaylistExPtr(void*, ::Ice::ObjectPtr&);

void __addObject(const PlaylistExPtr&, ::IceInternal::GCCountMap&);
bool __usesClasses(const PlaylistExPtr&);
void __decRefUnsafe(const PlaylistExPtr&);
void __clearHandleUnsafe(PlaylistExPtr&);

typedef ::IceInternal::Handle< ::TianShanIce::Streamer::PlaylistItem> PlaylistItemPtr;
typedef ::IceInternal::ProxyHandle< ::IceProxy::TianShanIce::Streamer::PlaylistItem> PlaylistItemPrx;

void __write(::IceInternal::BasicStream*, const PlaylistItemPrx&);
void __read(::IceInternal::BasicStream*, PlaylistItemPrx&);
void __write(::IceInternal::BasicStream*, const PlaylistItemPtr&);
void __patch__PlaylistItemPtr(void*, ::Ice::ObjectPtr&);

void __addObject(const PlaylistItemPtr&, ::IceInternal::GCCountMap&);
bool __usesClasses(const PlaylistItemPtr&);
void __decRefUnsafe(const PlaylistItemPtr&);
void __clearHandleUnsafe(PlaylistItemPtr&);

typedef ::IceInternal::Handle< ::TianShanIce::Streamer::StreamSmithAdmin> StreamSmithAdminPtr;
typedef ::IceInternal::ProxyHandle< ::IceProxy::TianShanIce::Streamer::StreamSmithAdmin> StreamSmithAdminPrx;

void __write(::IceInternal::BasicStream*, const StreamSmithAdminPrx&);
void __read(::IceInternal::BasicStream*, StreamSmithAdminPrx&);
void __write(::IceInternal::BasicStream*, const StreamSmithAdminPtr&);
void __patch__StreamSmithAdminPtr(void*, ::Ice::ObjectPtr&);

void __addObject(const StreamSmithAdminPtr&, ::IceInternal::GCCountMap&);
bool __usesClasses(const StreamSmithAdminPtr&);
void __decRefUnsafe(const StreamSmithAdminPtr&);
void __clearHandleUnsafe(StreamSmithAdminPtr&);

}

}

namespace TianShanIce
{

namespace Weiwoo
{

}

namespace Streamer
{

struct PlaylistAttr
{
    ::std::string Guid;
    ::std::string StreamSmithSiteName;
    ::std::string ResourceGuid;
    ::std::string ClientSessionID;
    ::std::string endPoint;
    ::Ice::Int MaxRate;
    ::Ice::Int MinRate;
    ::Ice::Int NowRate;
    ::std::string destIP;
    ::Ice::Int destPort;
    ::std::string destMac;
    ::Ice::Int vstrmPort;
    ::Ice::Int programNumber;
    ::Ice::Short playlistState;
    ::Ice::Int currentCtrlNum;
    ::Ice::Int vstrmSessID;
    ::Ice::Int streamPID;
    ::TianShanIce::Properties property;

    bool operator==(const PlaylistAttr&) const;
    bool operator!=(const PlaylistAttr&) const;
    bool operator<(const PlaylistAttr&) const;
    bool operator<=(const PlaylistAttr& __rhs) const
    {
        return operator<(__rhs) || operator==(__rhs);
    }
    bool operator>(const PlaylistAttr& __rhs) const
    {
        return !operator<(__rhs) && !operator==(__rhs);
    }
    bool operator>=(const PlaylistAttr& __rhs) const
    {
        return !operator<(__rhs);
    }

    void __write(::IceInternal::BasicStream*) const;
    void __read(::IceInternal::BasicStream*);
};

typedef ::std::vector< ::std::string> PlaylistIDs;

class __U__PlaylistIDs { };

struct PlaylistItemAttr
{
    ::std::string PlaylistGuid;
    ::TianShanIce::Streamer::PlaylistItemSetupInfo itemSetupInfo;
    ::Ice::Int InternalCtrlNum;
    ::Ice::Int CtrlNumber;
    ::Ice::Int vStrmSessID;
    ::Ice::Short SessState;
    ::TianShanIce::Properties property;

    bool operator==(const PlaylistItemAttr&) const;
    bool operator!=(const PlaylistItemAttr&) const;
    bool operator<(const PlaylistItemAttr&) const;
    bool operator<=(const PlaylistItemAttr& __rhs) const
    {
        return operator<(__rhs) || operator==(__rhs);
    }
    bool operator>(const PlaylistItemAttr& __rhs) const
    {
        return !operator<(__rhs) && !operator==(__rhs);
    }
    bool operator>=(const PlaylistItemAttr& __rhs) const
    {
        return !operator<(__rhs);
    }

    void __write(::IceInternal::BasicStream*) const;
    void __read(::IceInternal::BasicStream*);
};

typedef ::std::vector< ::Ice::Int> SpigotBoards;

class __U__SpigotBoards { };

typedef ::std::vector< ::TianShanIce::Streamer::PlaylistItemSetupInfo> PlaylistItemInfoS;

class __U__PlaylistItemInfoS { };
void __write(::IceInternal::BasicStream*, const ::TianShanIce::Streamer::PlaylistItemSetupInfo*, const ::TianShanIce::Streamer::PlaylistItemSetupInfo*, __U__PlaylistItemInfoS);
void __read(::IceInternal::BasicStream*, PlaylistItemInfoS&, __U__PlaylistItemInfoS);

struct StreamDuplicateReq
{
    ::TianShanIce::SRM::ResourceMap resources;
    ::TianShanIce::Properties properties;
    ::TianShanIce::Streamer::StreamState state;
    ::Ice::Int timeoffset;
    ::Ice::Float scale;
    ::TianShanIce::Streamer::PlaylistItemInfoS items;
    ::std::string reqTag;

    bool operator==(const StreamDuplicateReq&) const;
    bool operator!=(const StreamDuplicateReq&) const;
    bool operator<(const StreamDuplicateReq&) const;
    bool operator<=(const StreamDuplicateReq& __rhs) const
    {
        return operator<(__rhs) || operator==(__rhs);
    }
    bool operator>(const StreamDuplicateReq& __rhs) const
    {
        return !operator<(__rhs) && !operator==(__rhs);
    }
    bool operator>=(const StreamDuplicateReq& __rhs) const
    {
        return !operator<(__rhs);
    }

    void __write(::IceInternal::BasicStream*) const;
    void __read(::IceInternal::BasicStream*);
};

struct StreamDuplicateResp
{
    ::std::string reqTag;
    ::std::string streamSessionId;
    ::TianShanIce::Streamer::StreamState state;
    ::Ice::Int timeoffset;
    ::Ice::Float scale;
    ::TianShanIce::Streamer::PlaylistPrx streamSession;

    bool operator==(const StreamDuplicateResp&) const;
    bool operator!=(const StreamDuplicateResp&) const;
    bool operator<(const StreamDuplicateResp&) const;
    bool operator<=(const StreamDuplicateResp& __rhs) const
    {
        return operator<(__rhs) || operator==(__rhs);
    }
    bool operator>(const StreamDuplicateResp& __rhs) const
    {
        return !operator<(__rhs) && !operator==(__rhs);
    }
    bool operator>=(const StreamDuplicateResp& __rhs) const
    {
        return !operator<(__rhs);
    }

    void __write(::IceInternal::BasicStream*) const;
    void __read(::IceInternal::BasicStream*);
};

typedef ::std::vector< ::TianShanIce::Streamer::StreamDuplicateReq> StreamBatchRequest;

class __U__StreamBatchRequest { };
void __write(::IceInternal::BasicStream*, const ::TianShanIce::Streamer::StreamDuplicateReq*, const ::TianShanIce::Streamer::StreamDuplicateReq*, __U__StreamBatchRequest);
void __read(::IceInternal::BasicStream*, StreamBatchRequest&, __U__StreamBatchRequest);

typedef ::std::vector< ::TianShanIce::Streamer::StreamDuplicateResp> StreamBatchResponse;

class __U__StreamBatchResponse { };
void __write(::IceInternal::BasicStream*, const ::TianShanIce::Streamer::StreamDuplicateResp*, const ::TianShanIce::Streamer::StreamDuplicateResp*, __U__StreamBatchResponse);
void __read(::IceInternal::BasicStream*, StreamBatchResponse&, __U__StreamBatchResponse);

}

}

namespace TianShanIce
{

namespace Streamer
{

class AMI_StreamSmithAdmin_createStreamBatch : public ::IceInternal::OutgoingAsync
{
public:

    virtual void ice_response(const ::TianShanIce::Streamer::StreamBatchResponse&) = 0;
    virtual void ice_exception(const ::Ice::Exception&) = 0;

    void __invoke(const ::TianShanIce::Streamer::StreamSmithAdminPrx&, const ::TianShanIce::Streamer::StreamBatchRequest&, const ::Ice::Context*);

protected:

    virtual void __response(bool);
};

typedef ::IceUtil::Handle< ::TianShanIce::Streamer::AMI_StreamSmithAdmin_createStreamBatch> AMI_StreamSmithAdmin_createStreamBatchPtr;

class AMD_StreamSmithAdmin_createStreamBatch : virtual public ::IceUtil::Shared
{
public:

    virtual void ice_response(const ::TianShanIce::Streamer::StreamBatchResponse&) = 0;
    virtual void ice_exception(const ::Ice::Exception&) = 0;
    virtual void ice_exception(const ::std::exception&) = 0;
    virtual void ice_exception() = 0;
};

typedef ::IceUtil::Handle< ::TianShanIce::Streamer::AMD_StreamSmithAdmin_createStreamBatch> AMD_StreamSmithAdmin_createStreamBatchPtr;

}

}

namespace IceAsync
{

namespace TianShanIce
{

namespace Streamer
{

class AMD_StreamSmithAdmin_createStreamBatch : public ::TianShanIce::Streamer::AMD_StreamSmithAdmin_createStreamBatch, public ::IceInternal::IncomingAsync
{
public:

    AMD_StreamSmithAdmin_createStreamBatch(::IceInternal::Incoming&);

    virtual void ice_response(const ::TianShanIce::Streamer::StreamBatchResponse&);
    virtual void ice_exception(const ::Ice::Exception&);
    virtual void ice_exception(const ::std::exception&);
    virtual void ice_exception();
};

}

}

}

namespace IceProxy
{

namespace TianShanIce
{

namespace Weiwoo
{

}

namespace Streamer
{

class PlaylistEx : virtual public ::IceProxy::TianShanIce::Streamer::Playlist
{
public:

    ::TianShanIce::Streamer::PlaylistAttr getAttr()
    {
        return getAttr(0);
    }
    ::TianShanIce::Streamer::PlaylistAttr getAttr(const ::Ice::Context& __ctx)
    {
        return getAttr(&__ctx);
    }
    
private:

    ::TianShanIce::Streamer::PlaylistAttr getAttr(const ::Ice::Context*);
    
public:

    void updateAttr(const ::TianShanIce::Streamer::PlaylistAttr& attr)
    {
        updateAttr(attr, 0);
    }
    void updateAttr(const ::TianShanIce::Streamer::PlaylistAttr& attr, const ::Ice::Context& __ctx)
    {
        updateAttr(attr, &__ctx);
    }
    
private:

    void updateAttr(const ::TianShanIce::Streamer::PlaylistAttr&, const ::Ice::Context*);
    
public:

    void attachSession(const ::TianShanIce::SRM::SessionPrx& sess)
    {
        attachSession(sess, 0);
    }
    void attachSession(const ::TianShanIce::SRM::SessionPrx& sess, const ::Ice::Context& __ctx)
    {
        attachSession(sess, &__ctx);
    }
    
private:

    void attachSession(const ::TianShanIce::SRM::SessionPrx&, const ::Ice::Context*);
    
public:

    void setDestination(const ::std::string& destIP, ::Ice::Int port)
    {
        setDestination(destIP, port, 0);
    }
    void setDestination(const ::std::string& destIP, ::Ice::Int port, const ::Ice::Context& __ctx)
    {
        setDestination(destIP, port, &__ctx);
    }
    
private:

    void setDestination(const ::std::string&, ::Ice::Int, const ::Ice::Context*);
    
public:

    void setDestMac(const ::std::string& strMac)
    {
        setDestMac(strMac, 0);
    }
    void setDestMac(const ::std::string& strMac, const ::Ice::Context& __ctx)
    {
        setDestMac(strMac, &__ctx);
    }
    
private:

    void setDestMac(const ::std::string&, const ::Ice::Context*);
    
public:

    void setSourceStrmPort(::Ice::Int port)
    {
        setSourceStrmPort(port, 0);
    }
    void setSourceStrmPort(::Ice::Int port, const ::Ice::Context& __ctx)
    {
        setSourceStrmPort(port, &__ctx);
    }
    
private:

    void setSourceStrmPort(::Ice::Int, const ::Ice::Context*);
    
public:

    void setPID(::Ice::Int pid)
    {
        setPID(pid, 0);
    }
    void setPID(::Ice::Int pid, const ::Ice::Context& __ctx)
    {
        setPID(pid, &__ctx);
    }
    
private:

    void setPID(::Ice::Int, const ::Ice::Context*);
    
public:

    void onTimer()
    {
        onTimer(0);
    }
    void onTimer(const ::Ice::Context& __ctx)
    {
        onTimer(&__ctx);
    }
    
private:

    void onTimer(const ::Ice::Context*);
    
public:
    
    static const ::std::string& ice_staticId();

private: 

    virtual ::IceInternal::Handle< ::IceDelegateM::Ice::Object> __createDelegateM();
    virtual ::IceInternal::Handle< ::IceDelegateD::Ice::Object> __createDelegateD();
};

class PlaylistItem : virtual public ::IceProxy::Ice::Object
{
public:

    void destroy()
    {
        destroy(0);
    }
    void destroy(const ::Ice::Context& __ctx)
    {
        destroy(&__ctx);
    }
    
private:

    void destroy(const ::Ice::Context*);
    
public:

    ::TianShanIce::Streamer::PlaylistItemAttr getAttr()
    {
        return getAttr(0);
    }
    ::TianShanIce::Streamer::PlaylistItemAttr getAttr(const ::Ice::Context& __ctx)
    {
        return getAttr(&__ctx);
    }
    
private:

    ::TianShanIce::Streamer::PlaylistItemAttr getAttr(const ::Ice::Context*);
    
public:

    void updateAttr(const ::TianShanIce::Streamer::PlaylistItemAttr& attr)
    {
        updateAttr(attr, 0);
    }
    void updateAttr(const ::TianShanIce::Streamer::PlaylistItemAttr& attr, const ::Ice::Context& __ctx)
    {
        updateAttr(attr, &__ctx);
    }
    
private:

    void updateAttr(const ::TianShanIce::Streamer::PlaylistItemAttr&, const ::Ice::Context*);
    
public:
    
    static const ::std::string& ice_staticId();

private: 

    virtual ::IceInternal::Handle< ::IceDelegateM::Ice::Object> __createDelegateM();
    virtual ::IceInternal::Handle< ::IceDelegateD::Ice::Object> __createDelegateD();
};

class StreamSmithAdmin : virtual public ::IceProxy::TianShanIce::Streamer::StreamSmith
{
public:

    ::TianShanIce::Streamer::PlaylistIDs listPlaylists()
    {
        return listPlaylists(0);
    }
    ::TianShanIce::Streamer::PlaylistIDs listPlaylists(const ::Ice::Context& __ctx)
    {
        return listPlaylists(&__ctx);
    }
    
private:

    ::TianShanIce::Streamer::PlaylistIDs listPlaylists(const ::Ice::Context*);
    
public:

    ::TianShanIce::Streamer::PlaylistPrx openPlaylist(const ::std::string& guid, const ::TianShanIce::Streamer::SpigotBoards& EdgeCards, bool bCreateIfNotExist)
    {
        return openPlaylist(guid, EdgeCards, bCreateIfNotExist, 0);
    }
    ::TianShanIce::Streamer::PlaylistPrx openPlaylist(const ::std::string& guid, const ::TianShanIce::Streamer::SpigotBoards& EdgeCards, bool bCreateIfNotExist, const ::Ice::Context& __ctx)
    {
        return openPlaylist(guid, EdgeCards, bCreateIfNotExist, &__ctx);
    }
    
private:

    ::TianShanIce::Streamer::PlaylistPrx openPlaylist(const ::std::string&, const ::TianShanIce::Streamer::SpigotBoards&, bool, const ::Ice::Context*);
    
public:

    ::TianShanIce::Streamer::StreamBatchResponse createStreamBatch(const ::TianShanIce::Streamer::StreamBatchRequest& req)
    {
        return createStreamBatch(req, 0);
    }
    ::TianShanIce::Streamer::StreamBatchResponse createStreamBatch(const ::TianShanIce::Streamer::StreamBatchRequest& req, const ::Ice::Context& __ctx)
    {
        return createStreamBatch(req, &__ctx);
    }
    
private:

    ::TianShanIce::Streamer::StreamBatchResponse createStreamBatch(const ::TianShanIce::Streamer::StreamBatchRequest&, const ::Ice::Context*);
    
public:
    void createStreamBatch_async(const ::TianShanIce::Streamer::AMI_StreamSmithAdmin_createStreamBatchPtr&, const ::TianShanIce::Streamer::StreamBatchRequest&);
    void createStreamBatch_async(const ::TianShanIce::Streamer::AMI_StreamSmithAdmin_createStreamBatchPtr&, const ::TianShanIce::Streamer::StreamBatchRequest&, const ::Ice::Context&);

    ::std::string ShowMemory()
    {
        return ShowMemory(0);
    }
    ::std::string ShowMemory(const ::Ice::Context& __ctx)
    {
        return ShowMemory(&__ctx);
    }
    
private:

    ::std::string ShowMemory(const ::Ice::Context*);
    
public:
    
    static const ::std::string& ice_staticId();

private: 

    virtual ::IceInternal::Handle< ::IceDelegateM::Ice::Object> __createDelegateM();
    virtual ::IceInternal::Handle< ::IceDelegateD::Ice::Object> __createDelegateD();
};

}

}

}

namespace IceDelegate
{

namespace TianShanIce
{

namespace Weiwoo
{

}

namespace Streamer
{

class PlaylistEx : virtual public ::IceDelegate::TianShanIce::Streamer::Playlist
{
public:

    virtual ::TianShanIce::Streamer::PlaylistAttr getAttr(const ::Ice::Context*) = 0;

    virtual void updateAttr(const ::TianShanIce::Streamer::PlaylistAttr&, const ::Ice::Context*) = 0;

    virtual void attachSession(const ::TianShanIce::SRM::SessionPrx&, const ::Ice::Context*) = 0;

    virtual void setDestination(const ::std::string&, ::Ice::Int, const ::Ice::Context*) = 0;

    virtual void setDestMac(const ::std::string&, const ::Ice::Context*) = 0;

    virtual void setSourceStrmPort(::Ice::Int, const ::Ice::Context*) = 0;

    virtual void setPID(::Ice::Int, const ::Ice::Context*) = 0;

    virtual void onTimer(const ::Ice::Context*) = 0;
};

class PlaylistItem : virtual public ::IceDelegate::Ice::Object
{
public:

    virtual void destroy(const ::Ice::Context*) = 0;

    virtual ::TianShanIce::Streamer::PlaylistItemAttr getAttr(const ::Ice::Context*) = 0;

    virtual void updateAttr(const ::TianShanIce::Streamer::PlaylistItemAttr&, const ::Ice::Context*) = 0;
};

class StreamSmithAdmin : virtual public ::IceDelegate::TianShanIce::Streamer::StreamSmith
{
public:

    virtual ::TianShanIce::Streamer::PlaylistIDs listPlaylists(const ::Ice::Context*) = 0;

    virtual ::TianShanIce::Streamer::PlaylistPrx openPlaylist(const ::std::string&, const ::TianShanIce::Streamer::SpigotBoards&, bool, const ::Ice::Context*) = 0;

    virtual ::TianShanIce::Streamer::StreamBatchResponse createStreamBatch(const ::TianShanIce::Streamer::StreamBatchRequest&, const ::Ice::Context*) = 0;

    virtual ::std::string ShowMemory(const ::Ice::Context*) = 0;
};

}

}

}

namespace IceDelegateM
{

namespace TianShanIce
{

namespace Weiwoo
{

}

namespace Streamer
{

class PlaylistEx : virtual public ::IceDelegate::TianShanIce::Streamer::PlaylistEx,
                   virtual public ::IceDelegateM::TianShanIce::Streamer::Playlist
{
public:

    virtual ::TianShanIce::Streamer::PlaylistAttr getAttr(const ::Ice::Context*);

    virtual void updateAttr(const ::TianShanIce::Streamer::PlaylistAttr&, const ::Ice::Context*);

    virtual void attachSession(const ::TianShanIce::SRM::SessionPrx&, const ::Ice::Context*);

    virtual void setDestination(const ::std::string&, ::Ice::Int, const ::Ice::Context*);

    virtual void setDestMac(const ::std::string&, const ::Ice::Context*);

    virtual void setSourceStrmPort(::Ice::Int, const ::Ice::Context*);

    virtual void setPID(::Ice::Int, const ::Ice::Context*);

    virtual void onTimer(const ::Ice::Context*);
};

class PlaylistItem : virtual public ::IceDelegate::TianShanIce::Streamer::PlaylistItem,
                     virtual public ::IceDelegateM::Ice::Object
{
public:

    virtual void destroy(const ::Ice::Context*);

    virtual ::TianShanIce::Streamer::PlaylistItemAttr getAttr(const ::Ice::Context*);

    virtual void updateAttr(const ::TianShanIce::Streamer::PlaylistItemAttr&, const ::Ice::Context*);
};

class StreamSmithAdmin : virtual public ::IceDelegate::TianShanIce::Streamer::StreamSmithAdmin,
                         virtual public ::IceDelegateM::TianShanIce::Streamer::StreamSmith
{
public:

    virtual ::TianShanIce::Streamer::PlaylistIDs listPlaylists(const ::Ice::Context*);

    virtual ::TianShanIce::Streamer::PlaylistPrx openPlaylist(const ::std::string&, const ::TianShanIce::Streamer::SpigotBoards&, bool, const ::Ice::Context*);

    virtual ::TianShanIce::Streamer::StreamBatchResponse createStreamBatch(const ::TianShanIce::Streamer::StreamBatchRequest&, const ::Ice::Context*);

    virtual ::std::string ShowMemory(const ::Ice::Context*);
};

}

}

}

namespace IceDelegateD
{

namespace TianShanIce
{

namespace Weiwoo
{

}

namespace Streamer
{

class PlaylistEx : virtual public ::IceDelegate::TianShanIce::Streamer::PlaylistEx,
                   virtual public ::IceDelegateD::TianShanIce::Streamer::Playlist
{
public:

    virtual ::TianShanIce::Streamer::PlaylistAttr getAttr(const ::Ice::Context*);

    virtual void updateAttr(const ::TianShanIce::Streamer::PlaylistAttr&, const ::Ice::Context*);

    virtual void attachSession(const ::TianShanIce::SRM::SessionPrx&, const ::Ice::Context*);

    virtual void setDestination(const ::std::string&, ::Ice::Int, const ::Ice::Context*);

    virtual void setDestMac(const ::std::string&, const ::Ice::Context*);

    virtual void setSourceStrmPort(::Ice::Int, const ::Ice::Context*);

    virtual void setPID(::Ice::Int, const ::Ice::Context*);

    virtual void onTimer(const ::Ice::Context*);
};

class PlaylistItem : virtual public ::IceDelegate::TianShanIce::Streamer::PlaylistItem,
                     virtual public ::IceDelegateD::Ice::Object
{
public:

    virtual void destroy(const ::Ice::Context*);

    virtual ::TianShanIce::Streamer::PlaylistItemAttr getAttr(const ::Ice::Context*);

    virtual void updateAttr(const ::TianShanIce::Streamer::PlaylistItemAttr&, const ::Ice::Context*);
};

class StreamSmithAdmin : virtual public ::IceDelegate::TianShanIce::Streamer::StreamSmithAdmin,
                         virtual public ::IceDelegateD::TianShanIce::Streamer::StreamSmith
{
public:

    virtual ::TianShanIce::Streamer::PlaylistIDs listPlaylists(const ::Ice::Context*);

    virtual ::TianShanIce::Streamer::PlaylistPrx openPlaylist(const ::std::string&, const ::TianShanIce::Streamer::SpigotBoards&, bool, const ::Ice::Context*);

    virtual ::TianShanIce::Streamer::StreamBatchResponse createStreamBatch(const ::TianShanIce::Streamer::StreamBatchRequest&, const ::Ice::Context*);

    virtual ::std::string ShowMemory(const ::Ice::Context*);
};

}

}

}

namespace TianShanIce
{

namespace Streamer
{

class PlaylistEx : virtual public ::TianShanIce::Streamer::Playlist
{
public:

    typedef PlaylistExPrx ProxyType;
    typedef PlaylistExPtr PointerType;
    
    PlaylistEx() {}
    PlaylistEx(const ::Ice::Identity&, const ::std::string&, const ::TianShanIce::Streamer::PlaylistAttr&);
    virtual ::Ice::ObjectPtr ice_clone() const;

    virtual bool ice_isA(const ::std::string&, const ::Ice::Current& = ::Ice::Current()) const;
    virtual ::std::vector< ::std::string> ice_ids(const ::Ice::Current& = ::Ice::Current()) const;
    virtual const ::std::string& ice_id(const ::Ice::Current& = ::Ice::Current()) const;
    static const ::std::string& ice_staticId();


    virtual ::TianShanIce::Streamer::PlaylistAttr getAttr(const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___getAttr(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual void updateAttr(const ::TianShanIce::Streamer::PlaylistAttr&, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___updateAttr(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual void attachSession(const ::TianShanIce::SRM::SessionPrx&, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___attachSession(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual void setDestination(const ::std::string&, ::Ice::Int, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___setDestination(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual void setDestMac(const ::std::string&, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___setDestMac(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual void setSourceStrmPort(::Ice::Int, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___setSourceStrmPort(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual void setPID(::Ice::Int, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___setPID(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual void onTimer(const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___onTimer(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual ::IceInternal::DispatchStatus __dispatch(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual ::Ice::Int ice_operationAttributes(const ::std::string&) const;

    virtual void __write(::IceInternal::BasicStream*) const;
    virtual void __read(::IceInternal::BasicStream*, bool);
    virtual void __write(const ::Ice::OutputStreamPtr&) const;
    virtual void __read(const ::Ice::InputStreamPtr&, bool);

    ::std::string guid;

    ::TianShanIce::Streamer::PlaylistAttr attr;
};

void __patch__PlaylistExPtr(void*, ::Ice::ObjectPtr&);

class PlaylistItem : virtual public ::Ice::Object
{
public:

    typedef PlaylistItemPrx ProxyType;
    typedef PlaylistItemPtr PointerType;
    
    PlaylistItem() {}
    PlaylistItem(const ::std::string&, const ::TianShanIce::Streamer::PlaylistItemAttr&);
    virtual ::Ice::ObjectPtr ice_clone() const;

    virtual bool ice_isA(const ::std::string&, const ::Ice::Current& = ::Ice::Current()) const;
    virtual ::std::vector< ::std::string> ice_ids(const ::Ice::Current& = ::Ice::Current()) const;
    virtual const ::std::string& ice_id(const ::Ice::Current& = ::Ice::Current()) const;
    static const ::std::string& ice_staticId();


    virtual void destroy(const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___destroy(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual ::TianShanIce::Streamer::PlaylistItemAttr getAttr(const ::Ice::Current& = ::Ice::Current()) const = 0;
    ::IceInternal::DispatchStatus ___getAttr(::IceInternal::Incoming&, const ::Ice::Current&) const;

    virtual void updateAttr(const ::TianShanIce::Streamer::PlaylistItemAttr&, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___updateAttr(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual ::IceInternal::DispatchStatus __dispatch(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual ::Ice::Int ice_operationAttributes(const ::std::string&) const;

    virtual void __write(::IceInternal::BasicStream*) const;
    virtual void __read(::IceInternal::BasicStream*, bool);
    virtual void __write(const ::Ice::OutputStreamPtr&) const;
    virtual void __read(const ::Ice::InputStreamPtr&, bool);

    ::std::string guid;

    ::TianShanIce::Streamer::PlaylistItemAttr attr;
};

void __patch__PlaylistItemPtr(void*, ::Ice::ObjectPtr&);

class StreamSmithAdmin : virtual public ::TianShanIce::Streamer::StreamSmith
{
public:

    typedef StreamSmithAdminPrx ProxyType;
    typedef StreamSmithAdminPtr PointerType;
    
    virtual ::Ice::ObjectPtr ice_clone() const;

    virtual bool ice_isA(const ::std::string&, const ::Ice::Current& = ::Ice::Current()) const;
    virtual ::std::vector< ::std::string> ice_ids(const ::Ice::Current& = ::Ice::Current()) const;
    virtual const ::std::string& ice_id(const ::Ice::Current& = ::Ice::Current()) const;
    static const ::std::string& ice_staticId();

    virtual ::TianShanIce::Streamer::PlaylistIDs listPlaylists(const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___listPlaylists(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual ::TianShanIce::Streamer::PlaylistPrx openPlaylist(const ::std::string&, const ::TianShanIce::Streamer::SpigotBoards&, bool, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___openPlaylist(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual void createStreamBatch_async(const ::TianShanIce::Streamer::AMD_StreamSmithAdmin_createStreamBatchPtr&, const ::TianShanIce::Streamer::StreamBatchRequest&, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___createStreamBatch(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual ::std::string ShowMemory(const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___ShowMemory(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual ::IceInternal::DispatchStatus __dispatch(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual void __write(::IceInternal::BasicStream*) const;
    virtual void __read(::IceInternal::BasicStream*, bool);
    virtual void __write(const ::Ice::OutputStreamPtr&) const;
    virtual void __read(const ::Ice::InputStreamPtr&, bool);
};

void __patch__StreamSmithAdminPtr(void*, ::Ice::ObjectPtr&);

}

}

#endif
