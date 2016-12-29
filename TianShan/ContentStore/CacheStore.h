// **********************************************************************
//
// Copyright (c) 2003-2007 ZeroC, Inc. All rights reserved.
//
// This copy of Ice is licensed to you under the terms described in the
// ICE_LICENSE file included in this distribution.
//
// **********************************************************************

// Ice version 3.2.1
// Generated from file `CacheStore.ice'

#ifndef __CacheStore_h__
#define __CacheStore_h__

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
#include <TsCache.h>
#include <ContentStore.h>
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

namespace Storage
{

class AccessRegistrar;
bool operator==(const AccessRegistrar&, const AccessRegistrar&);
bool operator!=(const AccessRegistrar&, const AccessRegistrar&);
bool operator<(const AccessRegistrar&, const AccessRegistrar&);
bool operator<=(const AccessRegistrar&, const AccessRegistrar&);
bool operator>(const AccessRegistrar&, const AccessRegistrar&);
bool operator>=(const AccessRegistrar&, const AccessRegistrar&);

class TopFolder;
bool operator==(const TopFolder&, const TopFolder&);
bool operator!=(const TopFolder&, const TopFolder&);
bool operator<(const TopFolder&, const TopFolder&);
bool operator<=(const TopFolder&, const TopFolder&);
bool operator>(const TopFolder&, const TopFolder&);
bool operator>=(const TopFolder&, const TopFolder&);

class CacheTask;
bool operator==(const CacheTask&, const CacheTask&);
bool operator!=(const CacheTask&, const CacheTask&);
bool operator<(const CacheTask&, const CacheTask&);
bool operator<=(const CacheTask&, const CacheTask&);
bool operator>(const CacheTask&, const CacheTask&);
bool operator>=(const CacheTask&, const CacheTask&);

class CacheStoreEx;
bool operator==(const CacheStoreEx&, const CacheStoreEx&);
bool operator!=(const CacheStoreEx&, const CacheStoreEx&);
bool operator<(const CacheStoreEx&, const CacheStoreEx&);
bool operator<=(const CacheStoreEx&, const CacheStoreEx&);
bool operator>(const CacheStoreEx&, const CacheStoreEx&);
bool operator>=(const CacheStoreEx&, const CacheStoreEx&);

}

}

}

namespace TianShanIce
{

namespace Storage
{

class AccessRegistrar;
bool operator==(const AccessRegistrar&, const AccessRegistrar&);
bool operator!=(const AccessRegistrar&, const AccessRegistrar&);
bool operator<(const AccessRegistrar&, const AccessRegistrar&);
bool operator<=(const AccessRegistrar&, const AccessRegistrar&);
bool operator>(const AccessRegistrar&, const AccessRegistrar&);
bool operator>=(const AccessRegistrar&, const AccessRegistrar&);

class TopFolder;
bool operator==(const TopFolder&, const TopFolder&);
bool operator!=(const TopFolder&, const TopFolder&);
bool operator<(const TopFolder&, const TopFolder&);
bool operator<=(const TopFolder&, const TopFolder&);
bool operator>(const TopFolder&, const TopFolder&);
bool operator>=(const TopFolder&, const TopFolder&);

class CacheTask;
bool operator==(const CacheTask&, const CacheTask&);
bool operator!=(const CacheTask&, const CacheTask&);
bool operator<(const CacheTask&, const CacheTask&);
bool operator<=(const CacheTask&, const CacheTask&);
bool operator>(const CacheTask&, const CacheTask&);
bool operator>=(const CacheTask&, const CacheTask&);

class CacheStoreEx;
bool operator==(const CacheStoreEx&, const CacheStoreEx&);
bool operator!=(const CacheStoreEx&, const CacheStoreEx&);
bool operator<(const CacheStoreEx&, const CacheStoreEx&);
bool operator<=(const CacheStoreEx&, const CacheStoreEx&);
bool operator>(const CacheStoreEx&, const CacheStoreEx&);
bool operator>=(const CacheStoreEx&, const CacheStoreEx&);

}

}

namespace IceInternal
{

void incRef(::TianShanIce::Storage::AccessRegistrar*);
void decRef(::TianShanIce::Storage::AccessRegistrar*);

void incRef(::IceProxy::TianShanIce::Storage::AccessRegistrar*);
void decRef(::IceProxy::TianShanIce::Storage::AccessRegistrar*);

void incRef(::TianShanIce::Storage::TopFolder*);
void decRef(::TianShanIce::Storage::TopFolder*);

void incRef(::IceProxy::TianShanIce::Storage::TopFolder*);
void decRef(::IceProxy::TianShanIce::Storage::TopFolder*);

void incRef(::TianShanIce::Storage::CacheTask*);
void decRef(::TianShanIce::Storage::CacheTask*);

void incRef(::IceProxy::TianShanIce::Storage::CacheTask*);
void decRef(::IceProxy::TianShanIce::Storage::CacheTask*);

void incRef(::TianShanIce::Storage::CacheStoreEx*);
void decRef(::TianShanIce::Storage::CacheStoreEx*);

void incRef(::IceProxy::TianShanIce::Storage::CacheStoreEx*);
void decRef(::IceProxy::TianShanIce::Storage::CacheStoreEx*);

}

namespace TianShanIce
{

namespace Storage
{

typedef ::IceInternal::Handle< ::TianShanIce::Storage::AccessRegistrar> AccessRegistrarPtr;
typedef ::IceInternal::ProxyHandle< ::IceProxy::TianShanIce::Storage::AccessRegistrar> AccessRegistrarPrx;

void __write(::IceInternal::BasicStream*, const AccessRegistrarPrx&);
void __read(::IceInternal::BasicStream*, AccessRegistrarPrx&);
void __write(::IceInternal::BasicStream*, const AccessRegistrarPtr&);
void __patch__AccessRegistrarPtr(void*, ::Ice::ObjectPtr&);

void __addObject(const AccessRegistrarPtr&, ::IceInternal::GCCountMap&);
bool __usesClasses(const AccessRegistrarPtr&);
void __decRefUnsafe(const AccessRegistrarPtr&);
void __clearHandleUnsafe(AccessRegistrarPtr&);

typedef ::IceInternal::Handle< ::TianShanIce::Storage::TopFolder> TopFolderPtr;
typedef ::IceInternal::ProxyHandle< ::IceProxy::TianShanIce::Storage::TopFolder> TopFolderPrx;

void __write(::IceInternal::BasicStream*, const TopFolderPrx&);
void __read(::IceInternal::BasicStream*, TopFolderPrx&);
void __write(::IceInternal::BasicStream*, const TopFolderPtr&);
void __patch__TopFolderPtr(void*, ::Ice::ObjectPtr&);

void __addObject(const TopFolderPtr&, ::IceInternal::GCCountMap&);
bool __usesClasses(const TopFolderPtr&);
void __decRefUnsafe(const TopFolderPtr&);
void __clearHandleUnsafe(TopFolderPtr&);

typedef ::IceInternal::Handle< ::TianShanIce::Storage::CacheTask> CacheTaskPtr;
typedef ::IceInternal::ProxyHandle< ::IceProxy::TianShanIce::Storage::CacheTask> CacheTaskPrx;

void __write(::IceInternal::BasicStream*, const CacheTaskPrx&);
void __read(::IceInternal::BasicStream*, CacheTaskPrx&);
void __write(::IceInternal::BasicStream*, const CacheTaskPtr&);
void __patch__CacheTaskPtr(void*, ::Ice::ObjectPtr&);

void __addObject(const CacheTaskPtr&, ::IceInternal::GCCountMap&);
bool __usesClasses(const CacheTaskPtr&);
void __decRefUnsafe(const CacheTaskPtr&);
void __clearHandleUnsafe(CacheTaskPtr&);

typedef ::IceInternal::Handle< ::TianShanIce::Storage::CacheStoreEx> CacheStoreExPtr;
typedef ::IceInternal::ProxyHandle< ::IceProxy::TianShanIce::Storage::CacheStoreEx> CacheStoreExPrx;

void __write(::IceInternal::BasicStream*, const CacheStoreExPrx&);
void __read(::IceInternal::BasicStream*, CacheStoreExPrx&);
void __write(::IceInternal::BasicStream*, const CacheStoreExPtr&);
void __patch__CacheStoreExPtr(void*, ::Ice::ObjectPtr&);

void __addObject(const CacheStoreExPtr&, ::IceInternal::GCCountMap&);
bool __usesClasses(const CacheStoreExPtr&);
void __decRefUnsafe(const CacheStoreExPtr&);
void __clearHandleUnsafe(CacheStoreExPtr&);

}

}

namespace TianShanIce
{

namespace Storage
{

struct AccessCounter
{
    ::TianShanIce::Storage::ContentAccess base;
    ::std::string folderName;
    ::Ice::Long knownSince;
    ::Ice::Long fileSizeMB;
    ::TianShanIce::Storage::ContentState localState;

    bool operator==(const AccessCounter&) const;
    bool operator!=(const AccessCounter&) const;
    bool operator<(const AccessCounter&) const;
    bool operator<=(const AccessCounter& __rhs) const
    {
        return operator<(__rhs) || operator==(__rhs);
    }
    bool operator>(const AccessCounter& __rhs) const
    {
        return !operator<(__rhs) && !operator==(__rhs);
    }
    bool operator>=(const AccessCounter& __rhs) const
    {
        return !operator<(__rhs);
    }

    void __write(::IceInternal::BasicStream*) const;
    void __read(::IceInternal::BasicStream*);
};

typedef ::std::map< ::std::string, ::TianShanIce::Storage::AccessCounter> ContentCounterMap;

class __U__ContentCounterMap { };
void __write(::IceInternal::BasicStream*, const ContentCounterMap&, __U__ContentCounterMap);
void __read(::IceInternal::BasicStream*, ContentCounterMap&, __U__ContentCounterMap);

typedef ::std::vector< ::TianShanIce::Storage::AccessCounter> ContentCounterList;

class __U__ContentCounterList { };
void __write(::IceInternal::BasicStream*, const ::TianShanIce::Storage::AccessCounter*, const ::TianShanIce::Storage::AccessCounter*, __U__ContentCounterList);
void __read(::IceInternal::BasicStream*, ContentCounterList&, __U__ContentCounterList);

}

}

namespace IceAsync
{

}

namespace IceProxy
{

namespace TianShanIce
{

namespace Storage
{

class AccessRegistrar : virtual public ::IceProxy::Ice::Object
{
public:

    ::TianShanIce::Storage::ContentAccess count(const ::std::string& contentName, const ::std::string& subfile, ::Ice::Int countToAdd)
    {
        return count(contentName, subfile, countToAdd, 0);
    }
    ::TianShanIce::Storage::ContentAccess count(const ::std::string& contentName, const ::std::string& subfile, ::Ice::Int countToAdd, const ::Ice::Context& __ctx)
    {
        return count(contentName, subfile, countToAdd, &__ctx);
    }
    
private:

    ::TianShanIce::Storage::ContentAccess count(const ::std::string&, const ::std::string&, ::Ice::Int, const ::Ice::Context*);
    
public:

    void set(const ::TianShanIce::Storage::AccessCounter& counterToOverwrite)
    {
        set(counterToOverwrite, 0);
    }
    void set(const ::TianShanIce::Storage::AccessCounter& counterToOverwrite, const ::Ice::Context& __ctx)
    {
        set(counterToOverwrite, &__ctx);
    }
    
private:

    void set(const ::TianShanIce::Storage::AccessCounter&, const ::Ice::Context*);
    
public:

    void erase(const ::std::string& contentName)
    {
        erase(contentName, 0);
    }
    void erase(const ::std::string& contentName, const ::Ice::Context& __ctx)
    {
        erase(contentName, &__ctx);
    }
    
private:

    void erase(const ::std::string&, const ::Ice::Context*);
    
public:

    bool get(const ::std::string& contentName, ::TianShanIce::Storage::AccessCounter& counter)
    {
        return get(contentName, counter, 0);
    }
    bool get(const ::std::string& contentName, ::TianShanIce::Storage::AccessCounter& counter, const ::Ice::Context& __ctx)
    {
        return get(contentName, counter, &__ctx);
    }
    
private:

    bool get(const ::std::string&, ::TianShanIce::Storage::AccessCounter&, const ::Ice::Context*);
    
public:

    ::Ice::Int compress(::Ice::Int windowSize, ::Ice::Int flushWinSize, ::Ice::Int& reqsInWindow, ::TianShanIce::Storage::ContentCounterList& listToFlush, ::TianShanIce::Storage::ContentCounterList& listEvicted)
    {
        return compress(windowSize, flushWinSize, reqsInWindow, listToFlush, listEvicted, 0);
    }
    ::Ice::Int compress(::Ice::Int windowSize, ::Ice::Int flushWinSize, ::Ice::Int& reqsInWindow, ::TianShanIce::Storage::ContentCounterList& listToFlush, ::TianShanIce::Storage::ContentCounterList& listEvicted, const ::Ice::Context& __ctx)
    {
        return compress(windowSize, flushWinSize, reqsInWindow, listToFlush, listEvicted, &__ctx);
    }
    
private:

    ::Ice::Int compress(::Ice::Int, ::Ice::Int, ::Ice::Int&, ::TianShanIce::Storage::ContentCounterList&, ::TianShanIce::Storage::ContentCounterList&, const ::Ice::Context*);
    
public:

    void sort(::Ice::Int windowSize, bool unpopular1st, ::Ice::Int minCount, ::TianShanIce::Storage::ContentCounterList& resultList)
    {
        sort(windowSize, unpopular1st, minCount, resultList, 0);
    }
    void sort(::Ice::Int windowSize, bool unpopular1st, ::Ice::Int minCount, ::TianShanIce::Storage::ContentCounterList& resultList, const ::Ice::Context& __ctx)
    {
        sort(windowSize, unpopular1st, minCount, resultList, &__ctx);
    }
    
private:

    void sort(::Ice::Int, bool, ::Ice::Int, ::TianShanIce::Storage::ContentCounterList&, const ::Ice::Context*);
    
public:

    ::Ice::Int size()
    {
        return size(0);
    }
    ::Ice::Int size(const ::Ice::Context& __ctx)
    {
        return size(&__ctx);
    }
    
private:

    ::Ice::Int size(const ::Ice::Context*);
    
public:
    
    static const ::std::string& ice_staticId();

private: 

    virtual ::IceInternal::Handle< ::IceDelegateM::Ice::Object> __createDelegateM();
    virtual ::IceInternal::Handle< ::IceDelegateD::Ice::Object> __createDelegateD();
};

class TopFolder : virtual public ::IceProxy::TianShanUtils::TimeoutObj
{
public:

    bool eraseFromUnpopular(const ::std::string& fullContentName)
    {
        return eraseFromUnpopular(fullContentName, 0);
    }
    bool eraseFromUnpopular(const ::std::string& fullContentName, const ::Ice::Context& __ctx)
    {
        return eraseFromUnpopular(fullContentName, &__ctx);
    }
    
private:

    bool eraseFromUnpopular(const ::std::string&, const ::Ice::Context*);
    
public:

    ::TianShanIce::StrValues freeForSpace(::Ice::Long wishedSpaceMB, ::Ice::Long& freedMB)
    {
        return freeForSpace(wishedSpaceMB, freedMB, 0);
    }
    ::TianShanIce::StrValues freeForSpace(::Ice::Long wishedSpaceMB, ::Ice::Long& freedMB, const ::Ice::Context& __ctx)
    {
        return freeForSpace(wishedSpaceMB, freedMB, &__ctx);
    }
    
private:

    ::TianShanIce::StrValues freeForSpace(::Ice::Long, ::Ice::Long&, const ::Ice::Context*);
    
public:

    bool getSpaceUsage(::Ice::Long& totalMB, ::Ice::Long& freeMB, ::Ice::Long& usedMB)
    {
        return getSpaceUsage(totalMB, freeMB, usedMB, 0);
    }
    bool getSpaceUsage(::Ice::Long& totalMB, ::Ice::Long& freeMB, ::Ice::Long& usedMB, const ::Ice::Context& __ctx)
    {
        return getSpaceUsage(totalMB, freeMB, usedMB, &__ctx);
    }
    
private:

    bool getSpaceUsage(::Ice::Long&, ::Ice::Long&, ::Ice::Long&, const ::Ice::Context*);
    
public:

    ::Ice::Int unpopularSize()
    {
        return unpopularSize(0);
    }
    ::Ice::Int unpopularSize(const ::Ice::Context& __ctx)
    {
        return unpopularSize(&__ctx);
    }
    
private:

    ::Ice::Int unpopularSize(const ::Ice::Context*);
    
public:

    void doRefreshUnpopular()
    {
        doRefreshUnpopular(0);
    }
    void doRefreshUnpopular(const ::Ice::Context& __ctx)
    {
        doRefreshUnpopular(&__ctx);
    }
    
private:

    void doRefreshUnpopular(const ::Ice::Context*);
    
public:
    
    static const ::std::string& ice_staticId();

private: 

    virtual ::IceInternal::Handle< ::IceDelegateM::Ice::Object> __createDelegateM();
    virtual ::IceInternal::Handle< ::IceDelegateD::Ice::Object> __createDelegateD();
};

class CacheTask : virtual public ::IceProxy::TianShanUtils::TimeoutObj
{
public:

    void OnRestore()
    {
        OnRestore(0);
    }
    void OnRestore(const ::Ice::Context& __ctx)
    {
        OnRestore(&__ctx);
    }
    
private:

    void OnRestore(const ::Ice::Context*);
    
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
    
    static const ::std::string& ice_staticId();

private: 

    virtual ::IceInternal::Handle< ::IceDelegateM::Ice::Object> __createDelegateM();
    virtual ::IceInternal::Handle< ::IceDelegateD::Ice::Object> __createDelegateD();
};

class CacheStoreEx : virtual public ::IceProxy::TianShanIce::Storage::CacheStore,
                     virtual public ::IceProxy::TianShanIce::ReplicaQuery,
                     virtual public ::IceProxy::TianShanUtils::TimeoutObj
{
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

namespace Storage
{

class AccessRegistrar : virtual public ::IceDelegate::Ice::Object
{
public:

    virtual ::TianShanIce::Storage::ContentAccess count(const ::std::string&, const ::std::string&, ::Ice::Int, const ::Ice::Context*) = 0;

    virtual void set(const ::TianShanIce::Storage::AccessCounter&, const ::Ice::Context*) = 0;

    virtual void erase(const ::std::string&, const ::Ice::Context*) = 0;

    virtual bool get(const ::std::string&, ::TianShanIce::Storage::AccessCounter&, const ::Ice::Context*) = 0;

    virtual ::Ice::Int compress(::Ice::Int, ::Ice::Int, ::Ice::Int&, ::TianShanIce::Storage::ContentCounterList&, ::TianShanIce::Storage::ContentCounterList&, const ::Ice::Context*) = 0;

    virtual void sort(::Ice::Int, bool, ::Ice::Int, ::TianShanIce::Storage::ContentCounterList&, const ::Ice::Context*) = 0;

    virtual ::Ice::Int size(const ::Ice::Context*) = 0;
};

class TopFolder : virtual public ::IceDelegate::TianShanUtils::TimeoutObj
{
public:

    virtual bool eraseFromUnpopular(const ::std::string&, const ::Ice::Context*) = 0;

    virtual ::TianShanIce::StrValues freeForSpace(::Ice::Long, ::Ice::Long&, const ::Ice::Context*) = 0;

    virtual bool getSpaceUsage(::Ice::Long&, ::Ice::Long&, ::Ice::Long&, const ::Ice::Context*) = 0;

    virtual ::Ice::Int unpopularSize(const ::Ice::Context*) = 0;

    virtual void doRefreshUnpopular(const ::Ice::Context*) = 0;
};

class CacheTask : virtual public ::IceDelegate::TianShanUtils::TimeoutObj
{
public:

    virtual void OnRestore(const ::Ice::Context*) = 0;

    virtual void destroy(const ::Ice::Context*) = 0;
};

class CacheStoreEx : virtual public ::IceDelegate::TianShanIce::Storage::CacheStore,
                     virtual public ::IceDelegate::TianShanIce::ReplicaQuery,
                     virtual public ::IceDelegate::TianShanUtils::TimeoutObj
{
public:
};

}

}

}

namespace IceDelegateM
{

namespace TianShanIce
{

namespace Storage
{

class AccessRegistrar : virtual public ::IceDelegate::TianShanIce::Storage::AccessRegistrar,
                        virtual public ::IceDelegateM::Ice::Object
{
public:

    virtual ::TianShanIce::Storage::ContentAccess count(const ::std::string&, const ::std::string&, ::Ice::Int, const ::Ice::Context*);

    virtual void set(const ::TianShanIce::Storage::AccessCounter&, const ::Ice::Context*);

    virtual void erase(const ::std::string&, const ::Ice::Context*);

    virtual bool get(const ::std::string&, ::TianShanIce::Storage::AccessCounter&, const ::Ice::Context*);

    virtual ::Ice::Int compress(::Ice::Int, ::Ice::Int, ::Ice::Int&, ::TianShanIce::Storage::ContentCounterList&, ::TianShanIce::Storage::ContentCounterList&, const ::Ice::Context*);

    virtual void sort(::Ice::Int, bool, ::Ice::Int, ::TianShanIce::Storage::ContentCounterList&, const ::Ice::Context*);

    virtual ::Ice::Int size(const ::Ice::Context*);
};

class TopFolder : virtual public ::IceDelegate::TianShanIce::Storage::TopFolder,
                  virtual public ::IceDelegateM::TianShanUtils::TimeoutObj
{
public:

    virtual bool eraseFromUnpopular(const ::std::string&, const ::Ice::Context*);

    virtual ::TianShanIce::StrValues freeForSpace(::Ice::Long, ::Ice::Long&, const ::Ice::Context*);

    virtual bool getSpaceUsage(::Ice::Long&, ::Ice::Long&, ::Ice::Long&, const ::Ice::Context*);

    virtual ::Ice::Int unpopularSize(const ::Ice::Context*);

    virtual void doRefreshUnpopular(const ::Ice::Context*);
};

class CacheTask : virtual public ::IceDelegate::TianShanIce::Storage::CacheTask,
                  virtual public ::IceDelegateM::TianShanUtils::TimeoutObj
{
public:

    virtual void OnRestore(const ::Ice::Context*);

    virtual void destroy(const ::Ice::Context*);
};

class CacheStoreEx : virtual public ::IceDelegate::TianShanIce::Storage::CacheStoreEx,
                     virtual public ::IceDelegateM::TianShanIce::Storage::CacheStore,
                     virtual public ::IceDelegateM::TianShanIce::ReplicaQuery,
                     virtual public ::IceDelegateM::TianShanUtils::TimeoutObj
{
public:
};

}

}

}

namespace IceDelegateD
{

namespace TianShanIce
{

namespace Storage
{

class AccessRegistrar : virtual public ::IceDelegate::TianShanIce::Storage::AccessRegistrar,
                        virtual public ::IceDelegateD::Ice::Object
{
public:

    virtual ::TianShanIce::Storage::ContentAccess count(const ::std::string&, const ::std::string&, ::Ice::Int, const ::Ice::Context*);

    virtual void set(const ::TianShanIce::Storage::AccessCounter&, const ::Ice::Context*);

    virtual void erase(const ::std::string&, const ::Ice::Context*);

    virtual bool get(const ::std::string&, ::TianShanIce::Storage::AccessCounter&, const ::Ice::Context*);

    virtual ::Ice::Int compress(::Ice::Int, ::Ice::Int, ::Ice::Int&, ::TianShanIce::Storage::ContentCounterList&, ::TianShanIce::Storage::ContentCounterList&, const ::Ice::Context*);

    virtual void sort(::Ice::Int, bool, ::Ice::Int, ::TianShanIce::Storage::ContentCounterList&, const ::Ice::Context*);

    virtual ::Ice::Int size(const ::Ice::Context*);
};

class TopFolder : virtual public ::IceDelegate::TianShanIce::Storage::TopFolder,
                  virtual public ::IceDelegateD::TianShanUtils::TimeoutObj
{
public:

    virtual bool eraseFromUnpopular(const ::std::string&, const ::Ice::Context*);

    virtual ::TianShanIce::StrValues freeForSpace(::Ice::Long, ::Ice::Long&, const ::Ice::Context*);

    virtual bool getSpaceUsage(::Ice::Long&, ::Ice::Long&, ::Ice::Long&, const ::Ice::Context*);

    virtual ::Ice::Int unpopularSize(const ::Ice::Context*);

    virtual void doRefreshUnpopular(const ::Ice::Context*);
};

class CacheTask : virtual public ::IceDelegate::TianShanIce::Storage::CacheTask,
                  virtual public ::IceDelegateD::TianShanUtils::TimeoutObj
{
public:

    virtual void OnRestore(const ::Ice::Context*);

    virtual void destroy(const ::Ice::Context*);
};

class CacheStoreEx : virtual public ::IceDelegate::TianShanIce::Storage::CacheStoreEx,
                     virtual public ::IceDelegateD::TianShanIce::Storage::CacheStore,
                     virtual public ::IceDelegateD::TianShanIce::ReplicaQuery,
                     virtual public ::IceDelegateD::TianShanUtils::TimeoutObj
{
public:
};

}

}

}

namespace TianShanIce
{

namespace Storage
{

class AccessRegistrar : virtual public ::Ice::Object
{
public:

    typedef AccessRegistrarPrx ProxyType;
    typedef AccessRegistrarPtr PointerType;
    
    AccessRegistrar() {}
    AccessRegistrar(const ::std::string&, const ::TianShanIce::Storage::ContentCounterMap&);
    virtual ::Ice::ObjectPtr ice_clone() const;

    virtual bool ice_isA(const ::std::string&, const ::Ice::Current& = ::Ice::Current()) const;
    virtual ::std::vector< ::std::string> ice_ids(const ::Ice::Current& = ::Ice::Current()) const;
    virtual const ::std::string& ice_id(const ::Ice::Current& = ::Ice::Current()) const;
    static const ::std::string& ice_staticId();


    virtual ::TianShanIce::Storage::ContentAccess count(const ::std::string&, const ::std::string&, ::Ice::Int, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___count(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual void set(const ::TianShanIce::Storage::AccessCounter&, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___set(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual void erase(const ::std::string&, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___erase(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual bool get(const ::std::string&, ::TianShanIce::Storage::AccessCounter&, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___get(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual ::Ice::Int compress(::Ice::Int, ::Ice::Int, ::Ice::Int&, ::TianShanIce::Storage::ContentCounterList&, ::TianShanIce::Storage::ContentCounterList&, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___compress(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual void sort(::Ice::Int, bool, ::Ice::Int, ::TianShanIce::Storage::ContentCounterList&, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___sort(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual ::Ice::Int size(const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___size(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual ::IceInternal::DispatchStatus __dispatch(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual void __write(::IceInternal::BasicStream*) const;
    virtual void __read(::IceInternal::BasicStream*, bool);
    virtual void __write(const ::Ice::OutputStreamPtr&) const;
    virtual void __read(const ::Ice::InputStreamPtr&, bool);

    ::std::string name;

    ::TianShanIce::Storage::ContentCounterMap counters;
};

void __patch__AccessRegistrarPtr(void*, ::Ice::ObjectPtr&);

class TopFolder : virtual public ::TianShanUtils::TimeoutObj
{
public:

    typedef TopFolderPrx ProxyType;
    typedef TopFolderPtr PointerType;
    
    TopFolder() {}
    TopFolder(const ::Ice::Identity&, ::Ice::Long, const ::TianShanIce::StrValues&, const ::TianShanIce::Storage::AccessRegistrarPtr&, ::Ice::Int, ::Ice::Long, const ::TianShanIce::IValues&, ::Ice::Int);
    virtual ::Ice::ObjectPtr ice_clone() const;

    virtual bool ice_isA(const ::std::string&, const ::Ice::Current& = ::Ice::Current()) const;
    virtual ::std::vector< ::std::string> ice_ids(const ::Ice::Current& = ::Ice::Current()) const;
    virtual const ::std::string& ice_id(const ::Ice::Current& = ::Ice::Current()) const;
    static const ::std::string& ice_staticId();

    virtual void __incRef();
    virtual void __decRef();
    virtual void __addObject(::IceInternal::GCCountMap&);
    virtual bool __usesClasses();
    virtual void __gcReachable(::IceInternal::GCCountMap&) const;
    virtual void __gcClear();

    virtual bool eraseFromUnpopular(const ::std::string&, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___eraseFromUnpopular(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual ::TianShanIce::StrValues freeForSpace(::Ice::Long, ::Ice::Long&, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___freeForSpace(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual bool getSpaceUsage(::Ice::Long&, ::Ice::Long&, ::Ice::Long&, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___getSpaceUsage(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual ::Ice::Int unpopularSize(const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___unpopularSize(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual void doRefreshUnpopular(const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___doRefreshUnpopular(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual ::IceInternal::DispatchStatus __dispatch(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual ::Ice::Int ice_operationAttributes(const ::std::string&) const;

    virtual void __write(::IceInternal::BasicStream*) const;
    virtual void __read(::IceInternal::BasicStream*, bool);
    virtual void __write(const ::Ice::OutputStreamPtr&) const;
    virtual void __read(const ::Ice::InputStreamPtr&, bool);

    ::Ice::Identity ident;

    ::Ice::Long stampLastRefresh;

    ::TianShanIce::StrValues unpopularQueue;

    ::TianShanIce::Storage::AccessRegistrarPtr unpopulars;

    ::Ice::Int maxUnpopular;

    ::Ice::Long usedSpaceMB;

    ::TianShanIce::IValues contentsOfleaves;

    ::Ice::Int contentSubtotal;
};

void __patch__TopFolderPtr(void*, ::Ice::ObjectPtr&);

class CacheTask : virtual public ::TianShanUtils::TimeoutObj
{
public:

    typedef CacheTaskPrx ProxyType;
    typedef CacheTaskPtr PointerType;
    
    CacheTask() {}
    CacheTask(const ::Ice::Identity&, const ::TianShanIce::Storage::UnivContentPrx&, const ::TianShanIce::Properties&, const ::TianShanIce::Streamer::StreamPrx&, const ::std::string&, const ::std::string&, bool, ::Ice::Int, ::Ice::Int, ::Ice::Int, ::Ice::Long, ::Ice::Long, const ::std::string&, const ::std::string&, const ::TianShanIce::ContentProvision::ProvisionSessionPrx&, ::Ice::Long, ::Ice::Long, ::Ice::Long);
    virtual ::Ice::ObjectPtr ice_clone() const;

    virtual bool ice_isA(const ::std::string&, const ::Ice::Current& = ::Ice::Current()) const;
    virtual ::std::vector< ::std::string> ice_ids(const ::Ice::Current& = ::Ice::Current()) const;
    virtual const ::std::string& ice_id(const ::Ice::Current& = ::Ice::Current()) const;
    static const ::std::string& ice_staticId();


    virtual void OnRestore(const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___OnRestore(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual void destroy(const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___destroy(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual ::IceInternal::DispatchStatus __dispatch(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual ::Ice::Int ice_operationAttributes(const ::std::string&) const;

    virtual void __write(::IceInternal::BasicStream*) const;
    virtual void __read(::IceInternal::BasicStream*, bool);
    virtual void __write(const ::Ice::OutputStreamPtr&) const;
    virtual void __read(const ::Ice::InputStreamPtr&, bool);

    ::Ice::Identity ident;

    ::TianShanIce::Storage::UnivContentPrx localContent;

    ::TianShanIce::Properties nameFields;

    ::TianShanIce::Streamer::StreamPrx srcStream;

    ::std::string urlSrcStream;

    ::std::string srcContentType;

    bool isSrcPWE;

    ::Ice::Int bwMin;

    ::Ice::Int bwMax;

    ::Ice::Int bwCommitted;

    ::Ice::Long startOffset;

    ::Ice::Long endOffset;

    ::std::string scheduledStart;

    ::std::string scheduledEnd;

    ::TianShanIce::ContentProvision::ProvisionSessionPrx provisionSess;

    ::Ice::Long stampCreated;

    ::Ice::Long stampCommitted;

    ::Ice::Long stampStopped;
};

void __patch__CacheTaskPtr(void*, ::Ice::ObjectPtr&);

class CacheStoreEx : virtual public ::TianShanIce::Storage::CacheStore,
                     virtual public ::TianShanIce::ReplicaQuery,
                     virtual public ::TianShanUtils::TimeoutObj
{
public:

    typedef CacheStoreExPrx ProxyType;
    typedef CacheStoreExPtr PointerType;
    
    virtual ::Ice::ObjectPtr ice_clone() const;

    virtual bool ice_isA(const ::std::string&, const ::Ice::Current& = ::Ice::Current()) const;
    virtual ::std::vector< ::std::string> ice_ids(const ::Ice::Current& = ::Ice::Current()) const;
    virtual const ::std::string& ice_id(const ::Ice::Current& = ::Ice::Current()) const;
    static const ::std::string& ice_staticId();

    virtual ::IceInternal::DispatchStatus __dispatch(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual void __write(::IceInternal::BasicStream*) const;
    virtual void __read(::IceInternal::BasicStream*, bool);
    virtual void __write(const ::Ice::OutputStreamPtr&) const;
    virtual void __read(const ::Ice::InputStreamPtr&, bool);
};

void __patch__CacheStoreExPtr(void*, ::Ice::ObjectPtr&);

}

}

#endif
