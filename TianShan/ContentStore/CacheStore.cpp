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

#include <CacheStore.h>
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

static const ::std::string __TianShanIce__Storage__AccessRegistrar__count_name = "count";

static const ::std::string __TianShanIce__Storage__AccessRegistrar__set_name = "set";

static const ::std::string __TianShanIce__Storage__AccessRegistrar__erase_name = "erase";

static const ::std::string __TianShanIce__Storage__AccessRegistrar__get_name = "get";

static const ::std::string __TianShanIce__Storage__AccessRegistrar__compress_name = "compress";

static const ::std::string __TianShanIce__Storage__AccessRegistrar__sort_name = "sort";

static const ::std::string __TianShanIce__Storage__AccessRegistrar__size_name = "size";

static const ::std::string __TianShanIce__Storage__TopFolder__eraseFromUnpopular_name = "eraseFromUnpopular";

static const ::std::string __TianShanIce__Storage__TopFolder__freeForSpace_name = "freeForSpace";

static const ::std::string __TianShanIce__Storage__TopFolder__getSpaceUsage_name = "getSpaceUsage";

static const ::std::string __TianShanIce__Storage__TopFolder__unpopularSize_name = "unpopularSize";

static const ::std::string __TianShanIce__Storage__TopFolder__doRefreshUnpopular_name = "doRefreshUnpopular";

static const ::std::string __TianShanIce__Storage__CacheTask__OnRestore_name = "OnRestore";

static const ::std::string __TianShanIce__Storage__CacheTask__destroy_name = "destroy";

void
IceInternal::incRef(::TianShanIce::Storage::AccessRegistrar* p)
{
    p->__incRef();
}

void
IceInternal::decRef(::TianShanIce::Storage::AccessRegistrar* p)
{
    p->__decRef();
}

void
IceInternal::incRef(::IceProxy::TianShanIce::Storage::AccessRegistrar* p)
{
    p->__incRef();
}

void
IceInternal::decRef(::IceProxy::TianShanIce::Storage::AccessRegistrar* p)
{
    p->__decRef();
}

void
IceInternal::incRef(::TianShanIce::Storage::TopFolder* p)
{
    p->__incRef();
}

void
IceInternal::decRef(::TianShanIce::Storage::TopFolder* p)
{
    p->__decRef();
}

void
IceInternal::incRef(::IceProxy::TianShanIce::Storage::TopFolder* p)
{
    p->__incRef();
}

void
IceInternal::decRef(::IceProxy::TianShanIce::Storage::TopFolder* p)
{
    p->__decRef();
}

void
IceInternal::incRef(::TianShanIce::Storage::CacheTask* p)
{
    p->__incRef();
}

void
IceInternal::decRef(::TianShanIce::Storage::CacheTask* p)
{
    p->__decRef();
}

void
IceInternal::incRef(::IceProxy::TianShanIce::Storage::CacheTask* p)
{
    p->__incRef();
}

void
IceInternal::decRef(::IceProxy::TianShanIce::Storage::CacheTask* p)
{
    p->__decRef();
}

void
IceInternal::incRef(::TianShanIce::Storage::CacheStoreEx* p)
{
    p->__incRef();
}

void
IceInternal::decRef(::TianShanIce::Storage::CacheStoreEx* p)
{
    p->__decRef();
}

void
IceInternal::incRef(::IceProxy::TianShanIce::Storage::CacheStoreEx* p)
{
    p->__incRef();
}

void
IceInternal::decRef(::IceProxy::TianShanIce::Storage::CacheStoreEx* p)
{
    p->__decRef();
}

void
TianShanIce::Storage::__write(::IceInternal::BasicStream* __os, const ::TianShanIce::Storage::AccessRegistrarPrx& v)
{
    __os->write(::Ice::ObjectPrx(v));
}

void
TianShanIce::Storage::__read(::IceInternal::BasicStream* __is, ::TianShanIce::Storage::AccessRegistrarPrx& v)
{
    ::Ice::ObjectPrx proxy;
    __is->read(proxy);
    if(!proxy)
    {
        v = 0;
    }
    else
    {
        v = new ::IceProxy::TianShanIce::Storage::AccessRegistrar;
        v->__copyFrom(proxy);
    }
}

void
TianShanIce::Storage::__write(::IceInternal::BasicStream* __os, const ::TianShanIce::Storage::AccessRegistrarPtr& v)
{
    __os->write(::Ice::ObjectPtr(v));
}

void
TianShanIce::Storage::__write(::IceInternal::BasicStream* __os, const ::TianShanIce::Storage::TopFolderPrx& v)
{
    __os->write(::Ice::ObjectPrx(v));
}

void
TianShanIce::Storage::__read(::IceInternal::BasicStream* __is, ::TianShanIce::Storage::TopFolderPrx& v)
{
    ::Ice::ObjectPrx proxy;
    __is->read(proxy);
    if(!proxy)
    {
        v = 0;
    }
    else
    {
        v = new ::IceProxy::TianShanIce::Storage::TopFolder;
        v->__copyFrom(proxy);
    }
}

void
TianShanIce::Storage::__write(::IceInternal::BasicStream* __os, const ::TianShanIce::Storage::TopFolderPtr& v)
{
    __os->write(::Ice::ObjectPtr(v));
}

void
TianShanIce::Storage::__write(::IceInternal::BasicStream* __os, const ::TianShanIce::Storage::CacheTaskPrx& v)
{
    __os->write(::Ice::ObjectPrx(v));
}

void
TianShanIce::Storage::__read(::IceInternal::BasicStream* __is, ::TianShanIce::Storage::CacheTaskPrx& v)
{
    ::Ice::ObjectPrx proxy;
    __is->read(proxy);
    if(!proxy)
    {
        v = 0;
    }
    else
    {
        v = new ::IceProxy::TianShanIce::Storage::CacheTask;
        v->__copyFrom(proxy);
    }
}

void
TianShanIce::Storage::__write(::IceInternal::BasicStream* __os, const ::TianShanIce::Storage::CacheTaskPtr& v)
{
    __os->write(::Ice::ObjectPtr(v));
}

void
TianShanIce::Storage::__write(::IceInternal::BasicStream* __os, const ::TianShanIce::Storage::CacheStoreExPrx& v)
{
    __os->write(::Ice::ObjectPrx(v));
}

void
TianShanIce::Storage::__read(::IceInternal::BasicStream* __is, ::TianShanIce::Storage::CacheStoreExPrx& v)
{
    ::Ice::ObjectPrx proxy;
    __is->read(proxy);
    if(!proxy)
    {
        v = 0;
    }
    else
    {
        v = new ::IceProxy::TianShanIce::Storage::CacheStoreEx;
        v->__copyFrom(proxy);
    }
}

void
TianShanIce::Storage::__write(::IceInternal::BasicStream* __os, const ::TianShanIce::Storage::CacheStoreExPtr& v)
{
    __os->write(::Ice::ObjectPtr(v));
}

bool
TianShanIce::Storage::AccessCounter::operator==(const AccessCounter& __rhs) const
{
    return !operator!=(__rhs);
}

bool
TianShanIce::Storage::AccessCounter::operator!=(const AccessCounter& __rhs) const
{
    if(this == &__rhs)
    {
        return false;
    }
    if(base != __rhs.base)
    {
        return true;
    }
    if(folderName != __rhs.folderName)
    {
        return true;
    }
    if(knownSince != __rhs.knownSince)
    {
        return true;
    }
    if(fileSizeMB != __rhs.fileSizeMB)
    {
        return true;
    }
    if(localState != __rhs.localState)
    {
        return true;
    }
    return false;
}

bool
TianShanIce::Storage::AccessCounter::operator<(const AccessCounter& __rhs) const
{
    if(this == &__rhs)
    {
        return false;
    }
    if(base < __rhs.base)
    {
        return true;
    }
    else if(__rhs.base < base)
    {
        return false;
    }
    if(folderName < __rhs.folderName)
    {
        return true;
    }
    else if(__rhs.folderName < folderName)
    {
        return false;
    }
    if(knownSince < __rhs.knownSince)
    {
        return true;
    }
    else if(__rhs.knownSince < knownSince)
    {
        return false;
    }
    if(fileSizeMB < __rhs.fileSizeMB)
    {
        return true;
    }
    else if(__rhs.fileSizeMB < fileSizeMB)
    {
        return false;
    }
    if(localState < __rhs.localState)
    {
        return true;
    }
    else if(__rhs.localState < localState)
    {
        return false;
    }
    return false;
}

void
TianShanIce::Storage::AccessCounter::__write(::IceInternal::BasicStream* __os) const
{
    base.__write(__os);
    __os->write(folderName);
    __os->write(knownSince);
    __os->write(fileSizeMB);
    ::TianShanIce::Storage::__write(__os, localState);
}

void
TianShanIce::Storage::AccessCounter::__read(::IceInternal::BasicStream* __is)
{
    base.__read(__is);
    __is->read(folderName);
    __is->read(knownSince);
    __is->read(fileSizeMB);
    ::TianShanIce::Storage::__read(__is, localState);
}

void
TianShanIce::Storage::__write(::IceInternal::BasicStream* __os, const ::TianShanIce::Storage::ContentCounterMap& v, ::TianShanIce::Storage::__U__ContentCounterMap)
{
    __os->writeSize(::Ice::Int(v.size()));
    ::TianShanIce::Storage::ContentCounterMap::const_iterator p;
    for(p = v.begin(); p != v.end(); ++p)
    {
        __os->write(p->first);
        p->second.__write(__os);
    }
}

void
TianShanIce::Storage::__read(::IceInternal::BasicStream* __is, ::TianShanIce::Storage::ContentCounterMap& v, ::TianShanIce::Storage::__U__ContentCounterMap)
{
    ::Ice::Int sz;
    __is->readSize(sz);
    while(sz--)
    {
        ::std::pair<const  ::std::string, ::TianShanIce::Storage::AccessCounter> pair;
        __is->read(const_cast< ::std::string&>(pair.first));
        ::TianShanIce::Storage::ContentCounterMap::iterator __i = v.insert(v.end(), pair);
        __i->second.__read(__is);
    }
}

void
TianShanIce::Storage::__write(::IceInternal::BasicStream* __os, const ::TianShanIce::Storage::AccessCounter* begin, const ::TianShanIce::Storage::AccessCounter* end, ::TianShanIce::Storage::__U__ContentCounterList)
{
    ::Ice::Int size = static_cast< ::Ice::Int>(end - begin);
    __os->writeSize(size);
    for(int i = 0; i < size; ++i)
    {
        begin[i].__write(__os);
    }
}

void
TianShanIce::Storage::__read(::IceInternal::BasicStream* __is, ::TianShanIce::Storage::ContentCounterList& v, ::TianShanIce::Storage::__U__ContentCounterList)
{
    ::Ice::Int sz;
    __is->readSize(sz);
    __is->startSeq(sz, 39);
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
TianShanIce::Storage::__addObject(const AccessRegistrarPtr& p, ::IceInternal::GCCountMap& c)
{
    p->__addObject(c);
}

bool
TianShanIce::Storage::__usesClasses(const AccessRegistrarPtr& p)
{
    return p->__usesClasses();
}

void
TianShanIce::Storage::__decRefUnsafe(const AccessRegistrarPtr& p)
{
    p->__decRefUnsafe();
}

void
TianShanIce::Storage::__clearHandleUnsafe(AccessRegistrarPtr& p)
{
    p.__clearHandleUnsafe();
}

void
TianShanIce::Storage::__addObject(const TopFolderPtr& p, ::IceInternal::GCCountMap& c)
{
    p->__addObject(c);
}

bool
TianShanIce::Storage::__usesClasses(const TopFolderPtr& p)
{
    return p->__usesClasses();
}

void
TianShanIce::Storage::__decRefUnsafe(const TopFolderPtr& p)
{
    p->__decRefUnsafe();
}

void
TianShanIce::Storage::__clearHandleUnsafe(TopFolderPtr& p)
{
    p.__clearHandleUnsafe();
}

void
TianShanIce::Storage::__addObject(const CacheTaskPtr& p, ::IceInternal::GCCountMap& c)
{
    p->__addObject(c);
}

bool
TianShanIce::Storage::__usesClasses(const CacheTaskPtr& p)
{
    return p->__usesClasses();
}

void
TianShanIce::Storage::__decRefUnsafe(const CacheTaskPtr& p)
{
    p->__decRefUnsafe();
}

void
TianShanIce::Storage::__clearHandleUnsafe(CacheTaskPtr& p)
{
    p.__clearHandleUnsafe();
}

void
TianShanIce::Storage::__addObject(const CacheStoreExPtr& p, ::IceInternal::GCCountMap& c)
{
    p->__addObject(c);
}

bool
TianShanIce::Storage::__usesClasses(const CacheStoreExPtr& p)
{
    return p->__usesClasses();
}

void
TianShanIce::Storage::__decRefUnsafe(const CacheStoreExPtr& p)
{
    p->__decRefUnsafe();
}

void
TianShanIce::Storage::__clearHandleUnsafe(CacheStoreExPtr& p)
{
    p.__clearHandleUnsafe();
}

::TianShanIce::Storage::ContentAccess
IceProxy::TianShanIce::Storage::AccessRegistrar::count(const ::std::string& contentName, const ::std::string& subfile, ::Ice::Int countToAdd, const ::Ice::Context* __ctx)
{
    int __cnt = 0;
    while(true)
    {
        ::IceInternal::Handle< ::IceDelegate::Ice::Object> __delBase;
        try
        {
            __checkTwowayOnly(__TianShanIce__Storage__AccessRegistrar__count_name);
            __delBase = __getDelegate();
            ::IceDelegate::TianShanIce::Storage::AccessRegistrar* __del = dynamic_cast< ::IceDelegate::TianShanIce::Storage::AccessRegistrar*>(__delBase.get());
            return __del->count(contentName, subfile, countToAdd, __ctx);
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
IceProxy::TianShanIce::Storage::AccessRegistrar::set(const ::TianShanIce::Storage::AccessCounter& counterToOverwrite, const ::Ice::Context* __ctx)
{
    int __cnt = 0;
    while(true)
    {
        ::IceInternal::Handle< ::IceDelegate::Ice::Object> __delBase;
        try
        {
            __delBase = __getDelegate();
            ::IceDelegate::TianShanIce::Storage::AccessRegistrar* __del = dynamic_cast< ::IceDelegate::TianShanIce::Storage::AccessRegistrar*>(__delBase.get());
            __del->set(counterToOverwrite, __ctx);
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
IceProxy::TianShanIce::Storage::AccessRegistrar::erase(const ::std::string& contentName, const ::Ice::Context* __ctx)
{
    int __cnt = 0;
    while(true)
    {
        ::IceInternal::Handle< ::IceDelegate::Ice::Object> __delBase;
        try
        {
            __delBase = __getDelegate();
            ::IceDelegate::TianShanIce::Storage::AccessRegistrar* __del = dynamic_cast< ::IceDelegate::TianShanIce::Storage::AccessRegistrar*>(__delBase.get());
            __del->erase(contentName, __ctx);
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

bool
IceProxy::TianShanIce::Storage::AccessRegistrar::get(const ::std::string& contentName, ::TianShanIce::Storage::AccessCounter& counter, const ::Ice::Context* __ctx)
{
    int __cnt = 0;
    while(true)
    {
        ::IceInternal::Handle< ::IceDelegate::Ice::Object> __delBase;
        try
        {
            __checkTwowayOnly(__TianShanIce__Storage__AccessRegistrar__get_name);
            __delBase = __getDelegate();
            ::IceDelegate::TianShanIce::Storage::AccessRegistrar* __del = dynamic_cast< ::IceDelegate::TianShanIce::Storage::AccessRegistrar*>(__delBase.get());
            return __del->get(contentName, counter, __ctx);
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

::Ice::Int
IceProxy::TianShanIce::Storage::AccessRegistrar::compress(::Ice::Int windowSize, ::Ice::Int flushWinSize, ::Ice::Int& reqsInWindow, ::TianShanIce::Storage::ContentCounterList& listToFlush, ::TianShanIce::Storage::ContentCounterList& listEvicted, const ::Ice::Context* __ctx)
{
    int __cnt = 0;
    while(true)
    {
        ::IceInternal::Handle< ::IceDelegate::Ice::Object> __delBase;
        try
        {
            __checkTwowayOnly(__TianShanIce__Storage__AccessRegistrar__compress_name);
            __delBase = __getDelegate();
            ::IceDelegate::TianShanIce::Storage::AccessRegistrar* __del = dynamic_cast< ::IceDelegate::TianShanIce::Storage::AccessRegistrar*>(__delBase.get());
            return __del->compress(windowSize, flushWinSize, reqsInWindow, listToFlush, listEvicted, __ctx);
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
IceProxy::TianShanIce::Storage::AccessRegistrar::sort(::Ice::Int windowSize, bool unpopular1st, ::Ice::Int minCount, ::TianShanIce::Storage::ContentCounterList& resultList, const ::Ice::Context* __ctx)
{
    int __cnt = 0;
    while(true)
    {
        ::IceInternal::Handle< ::IceDelegate::Ice::Object> __delBase;
        try
        {
            __checkTwowayOnly(__TianShanIce__Storage__AccessRegistrar__sort_name);
            __delBase = __getDelegate();
            ::IceDelegate::TianShanIce::Storage::AccessRegistrar* __del = dynamic_cast< ::IceDelegate::TianShanIce::Storage::AccessRegistrar*>(__delBase.get());
            __del->sort(windowSize, unpopular1st, minCount, resultList, __ctx);
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

::Ice::Int
IceProxy::TianShanIce::Storage::AccessRegistrar::size(const ::Ice::Context* __ctx)
{
    int __cnt = 0;
    while(true)
    {
        ::IceInternal::Handle< ::IceDelegate::Ice::Object> __delBase;
        try
        {
            __checkTwowayOnly(__TianShanIce__Storage__AccessRegistrar__size_name);
            __delBase = __getDelegate();
            ::IceDelegate::TianShanIce::Storage::AccessRegistrar* __del = dynamic_cast< ::IceDelegate::TianShanIce::Storage::AccessRegistrar*>(__delBase.get());
            return __del->size(__ctx);
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
IceProxy::TianShanIce::Storage::AccessRegistrar::ice_staticId()
{
    return ::TianShanIce::Storage::AccessRegistrar::ice_staticId();
}

::IceInternal::Handle< ::IceDelegateM::Ice::Object>
IceProxy::TianShanIce::Storage::AccessRegistrar::__createDelegateM()
{
    return ::IceInternal::Handle< ::IceDelegateM::Ice::Object>(new ::IceDelegateM::TianShanIce::Storage::AccessRegistrar);
}

::IceInternal::Handle< ::IceDelegateD::Ice::Object>
IceProxy::TianShanIce::Storage::AccessRegistrar::__createDelegateD()
{
    return ::IceInternal::Handle< ::IceDelegateD::Ice::Object>(new ::IceDelegateD::TianShanIce::Storage::AccessRegistrar);
}

bool
IceProxy::TianShanIce::Storage::operator==(const ::IceProxy::TianShanIce::Storage::AccessRegistrar& l, const ::IceProxy::TianShanIce::Storage::AccessRegistrar& r)
{
    return static_cast<const ::IceProxy::Ice::Object&>(l) == static_cast<const ::IceProxy::Ice::Object&>(r);
}

bool
IceProxy::TianShanIce::Storage::operator!=(const ::IceProxy::TianShanIce::Storage::AccessRegistrar& l, const ::IceProxy::TianShanIce::Storage::AccessRegistrar& r)
{
    return static_cast<const ::IceProxy::Ice::Object&>(l) != static_cast<const ::IceProxy::Ice::Object&>(r);
}

bool
IceProxy::TianShanIce::Storage::operator<(const ::IceProxy::TianShanIce::Storage::AccessRegistrar& l, const ::IceProxy::TianShanIce::Storage::AccessRegistrar& r)
{
    return static_cast<const ::IceProxy::Ice::Object&>(l) < static_cast<const ::IceProxy::Ice::Object&>(r);
}

bool
IceProxy::TianShanIce::Storage::operator<=(const ::IceProxy::TianShanIce::Storage::AccessRegistrar& l, const ::IceProxy::TianShanIce::Storage::AccessRegistrar& r)
{
    return l < r || l == r;
}

bool
IceProxy::TianShanIce::Storage::operator>(const ::IceProxy::TianShanIce::Storage::AccessRegistrar& l, const ::IceProxy::TianShanIce::Storage::AccessRegistrar& r)
{
    return !(l < r) && !(l == r);
}

bool
IceProxy::TianShanIce::Storage::operator>=(const ::IceProxy::TianShanIce::Storage::AccessRegistrar& l, const ::IceProxy::TianShanIce::Storage::AccessRegistrar& r)
{
    return !(l < r);
}

bool
IceProxy::TianShanIce::Storage::TopFolder::eraseFromUnpopular(const ::std::string& fullContentName, const ::Ice::Context* __ctx)
{
    int __cnt = 0;
    while(true)
    {
        ::IceInternal::Handle< ::IceDelegate::Ice::Object> __delBase;
        try
        {
            __checkTwowayOnly(__TianShanIce__Storage__TopFolder__eraseFromUnpopular_name);
            __delBase = __getDelegate();
            ::IceDelegate::TianShanIce::Storage::TopFolder* __del = dynamic_cast< ::IceDelegate::TianShanIce::Storage::TopFolder*>(__delBase.get());
            return __del->eraseFromUnpopular(fullContentName, __ctx);
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

::TianShanIce::StrValues
IceProxy::TianShanIce::Storage::TopFolder::freeForSpace(::Ice::Long wishedSpaceMB, ::Ice::Long& freedMB, const ::Ice::Context* __ctx)
{
    int __cnt = 0;
    while(true)
    {
        ::IceInternal::Handle< ::IceDelegate::Ice::Object> __delBase;
        try
        {
            __checkTwowayOnly(__TianShanIce__Storage__TopFolder__freeForSpace_name);
            __delBase = __getDelegate();
            ::IceDelegate::TianShanIce::Storage::TopFolder* __del = dynamic_cast< ::IceDelegate::TianShanIce::Storage::TopFolder*>(__delBase.get());
            return __del->freeForSpace(wishedSpaceMB, freedMB, __ctx);
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

bool
IceProxy::TianShanIce::Storage::TopFolder::getSpaceUsage(::Ice::Long& totalMB, ::Ice::Long& freeMB, ::Ice::Long& usedMB, const ::Ice::Context* __ctx)
{
    int __cnt = 0;
    while(true)
    {
        ::IceInternal::Handle< ::IceDelegate::Ice::Object> __delBase;
        try
        {
            __checkTwowayOnly(__TianShanIce__Storage__TopFolder__getSpaceUsage_name);
            __delBase = __getDelegate();
            ::IceDelegate::TianShanIce::Storage::TopFolder* __del = dynamic_cast< ::IceDelegate::TianShanIce::Storage::TopFolder*>(__delBase.get());
            return __del->getSpaceUsage(totalMB, freeMB, usedMB, __ctx);
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

::Ice::Int
IceProxy::TianShanIce::Storage::TopFolder::unpopularSize(const ::Ice::Context* __ctx)
{
    int __cnt = 0;
    while(true)
    {
        ::IceInternal::Handle< ::IceDelegate::Ice::Object> __delBase;
        try
        {
            __checkTwowayOnly(__TianShanIce__Storage__TopFolder__unpopularSize_name);
            __delBase = __getDelegate();
            ::IceDelegate::TianShanIce::Storage::TopFolder* __del = dynamic_cast< ::IceDelegate::TianShanIce::Storage::TopFolder*>(__delBase.get());
            return __del->unpopularSize(__ctx);
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
IceProxy::TianShanIce::Storage::TopFolder::doRefreshUnpopular(const ::Ice::Context* __ctx)
{
    int __cnt = 0;
    while(true)
    {
        ::IceInternal::Handle< ::IceDelegate::Ice::Object> __delBase;
        try
        {
            __delBase = __getDelegate();
            ::IceDelegate::TianShanIce::Storage::TopFolder* __del = dynamic_cast< ::IceDelegate::TianShanIce::Storage::TopFolder*>(__delBase.get());
            __del->doRefreshUnpopular(__ctx);
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
IceProxy::TianShanIce::Storage::TopFolder::ice_staticId()
{
    return ::TianShanIce::Storage::TopFolder::ice_staticId();
}

::IceInternal::Handle< ::IceDelegateM::Ice::Object>
IceProxy::TianShanIce::Storage::TopFolder::__createDelegateM()
{
    return ::IceInternal::Handle< ::IceDelegateM::Ice::Object>(new ::IceDelegateM::TianShanIce::Storage::TopFolder);
}

::IceInternal::Handle< ::IceDelegateD::Ice::Object>
IceProxy::TianShanIce::Storage::TopFolder::__createDelegateD()
{
    return ::IceInternal::Handle< ::IceDelegateD::Ice::Object>(new ::IceDelegateD::TianShanIce::Storage::TopFolder);
}

bool
IceProxy::TianShanIce::Storage::operator==(const ::IceProxy::TianShanIce::Storage::TopFolder& l, const ::IceProxy::TianShanIce::Storage::TopFolder& r)
{
    return static_cast<const ::IceProxy::Ice::Object&>(l) == static_cast<const ::IceProxy::Ice::Object&>(r);
}

bool
IceProxy::TianShanIce::Storage::operator!=(const ::IceProxy::TianShanIce::Storage::TopFolder& l, const ::IceProxy::TianShanIce::Storage::TopFolder& r)
{
    return static_cast<const ::IceProxy::Ice::Object&>(l) != static_cast<const ::IceProxy::Ice::Object&>(r);
}

bool
IceProxy::TianShanIce::Storage::operator<(const ::IceProxy::TianShanIce::Storage::TopFolder& l, const ::IceProxy::TianShanIce::Storage::TopFolder& r)
{
    return static_cast<const ::IceProxy::Ice::Object&>(l) < static_cast<const ::IceProxy::Ice::Object&>(r);
}

bool
IceProxy::TianShanIce::Storage::operator<=(const ::IceProxy::TianShanIce::Storage::TopFolder& l, const ::IceProxy::TianShanIce::Storage::TopFolder& r)
{
    return l < r || l == r;
}

bool
IceProxy::TianShanIce::Storage::operator>(const ::IceProxy::TianShanIce::Storage::TopFolder& l, const ::IceProxy::TianShanIce::Storage::TopFolder& r)
{
    return !(l < r) && !(l == r);
}

bool
IceProxy::TianShanIce::Storage::operator>=(const ::IceProxy::TianShanIce::Storage::TopFolder& l, const ::IceProxy::TianShanIce::Storage::TopFolder& r)
{
    return !(l < r);
}

void
IceProxy::TianShanIce::Storage::CacheTask::OnRestore(const ::Ice::Context* __ctx)
{
    int __cnt = 0;
    while(true)
    {
        ::IceInternal::Handle< ::IceDelegate::Ice::Object> __delBase;
        try
        {
            __delBase = __getDelegate();
            ::IceDelegate::TianShanIce::Storage::CacheTask* __del = dynamic_cast< ::IceDelegate::TianShanIce::Storage::CacheTask*>(__delBase.get());
            __del->OnRestore(__ctx);
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
IceProxy::TianShanIce::Storage::CacheTask::destroy(const ::Ice::Context* __ctx)
{
    int __cnt = 0;
    while(true)
    {
        ::IceInternal::Handle< ::IceDelegate::Ice::Object> __delBase;
        try
        {
            __delBase = __getDelegate();
            ::IceDelegate::TianShanIce::Storage::CacheTask* __del = dynamic_cast< ::IceDelegate::TianShanIce::Storage::CacheTask*>(__delBase.get());
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

const ::std::string&
IceProxy::TianShanIce::Storage::CacheTask::ice_staticId()
{
    return ::TianShanIce::Storage::CacheTask::ice_staticId();
}

::IceInternal::Handle< ::IceDelegateM::Ice::Object>
IceProxy::TianShanIce::Storage::CacheTask::__createDelegateM()
{
    return ::IceInternal::Handle< ::IceDelegateM::Ice::Object>(new ::IceDelegateM::TianShanIce::Storage::CacheTask);
}

::IceInternal::Handle< ::IceDelegateD::Ice::Object>
IceProxy::TianShanIce::Storage::CacheTask::__createDelegateD()
{
    return ::IceInternal::Handle< ::IceDelegateD::Ice::Object>(new ::IceDelegateD::TianShanIce::Storage::CacheTask);
}

bool
IceProxy::TianShanIce::Storage::operator==(const ::IceProxy::TianShanIce::Storage::CacheTask& l, const ::IceProxy::TianShanIce::Storage::CacheTask& r)
{
    return static_cast<const ::IceProxy::Ice::Object&>(l) == static_cast<const ::IceProxy::Ice::Object&>(r);
}

bool
IceProxy::TianShanIce::Storage::operator!=(const ::IceProxy::TianShanIce::Storage::CacheTask& l, const ::IceProxy::TianShanIce::Storage::CacheTask& r)
{
    return static_cast<const ::IceProxy::Ice::Object&>(l) != static_cast<const ::IceProxy::Ice::Object&>(r);
}

bool
IceProxy::TianShanIce::Storage::operator<(const ::IceProxy::TianShanIce::Storage::CacheTask& l, const ::IceProxy::TianShanIce::Storage::CacheTask& r)
{
    return static_cast<const ::IceProxy::Ice::Object&>(l) < static_cast<const ::IceProxy::Ice::Object&>(r);
}

bool
IceProxy::TianShanIce::Storage::operator<=(const ::IceProxy::TianShanIce::Storage::CacheTask& l, const ::IceProxy::TianShanIce::Storage::CacheTask& r)
{
    return l < r || l == r;
}

bool
IceProxy::TianShanIce::Storage::operator>(const ::IceProxy::TianShanIce::Storage::CacheTask& l, const ::IceProxy::TianShanIce::Storage::CacheTask& r)
{
    return !(l < r) && !(l == r);
}

bool
IceProxy::TianShanIce::Storage::operator>=(const ::IceProxy::TianShanIce::Storage::CacheTask& l, const ::IceProxy::TianShanIce::Storage::CacheTask& r)
{
    return !(l < r);
}

const ::std::string&
IceProxy::TianShanIce::Storage::CacheStoreEx::ice_staticId()
{
    return ::TianShanIce::Storage::CacheStoreEx::ice_staticId();
}

::IceInternal::Handle< ::IceDelegateM::Ice::Object>
IceProxy::TianShanIce::Storage::CacheStoreEx::__createDelegateM()
{
    return ::IceInternal::Handle< ::IceDelegateM::Ice::Object>(new ::IceDelegateM::TianShanIce::Storage::CacheStoreEx);
}

::IceInternal::Handle< ::IceDelegateD::Ice::Object>
IceProxy::TianShanIce::Storage::CacheStoreEx::__createDelegateD()
{
    return ::IceInternal::Handle< ::IceDelegateD::Ice::Object>(new ::IceDelegateD::TianShanIce::Storage::CacheStoreEx);
}

bool
IceProxy::TianShanIce::Storage::operator==(const ::IceProxy::TianShanIce::Storage::CacheStoreEx& l, const ::IceProxy::TianShanIce::Storage::CacheStoreEx& r)
{
    return static_cast<const ::IceProxy::Ice::Object&>(l) == static_cast<const ::IceProxy::Ice::Object&>(r);
}

bool
IceProxy::TianShanIce::Storage::operator!=(const ::IceProxy::TianShanIce::Storage::CacheStoreEx& l, const ::IceProxy::TianShanIce::Storage::CacheStoreEx& r)
{
    return static_cast<const ::IceProxy::Ice::Object&>(l) != static_cast<const ::IceProxy::Ice::Object&>(r);
}

bool
IceProxy::TianShanIce::Storage::operator<(const ::IceProxy::TianShanIce::Storage::CacheStoreEx& l, const ::IceProxy::TianShanIce::Storage::CacheStoreEx& r)
{
    return static_cast<const ::IceProxy::Ice::Object&>(l) < static_cast<const ::IceProxy::Ice::Object&>(r);
}

bool
IceProxy::TianShanIce::Storage::operator<=(const ::IceProxy::TianShanIce::Storage::CacheStoreEx& l, const ::IceProxy::TianShanIce::Storage::CacheStoreEx& r)
{
    return l < r || l == r;
}

bool
IceProxy::TianShanIce::Storage::operator>(const ::IceProxy::TianShanIce::Storage::CacheStoreEx& l, const ::IceProxy::TianShanIce::Storage::CacheStoreEx& r)
{
    return !(l < r) && !(l == r);
}

bool
IceProxy::TianShanIce::Storage::operator>=(const ::IceProxy::TianShanIce::Storage::CacheStoreEx& l, const ::IceProxy::TianShanIce::Storage::CacheStoreEx& r)
{
    return !(l < r);
}

::TianShanIce::Storage::ContentAccess
IceDelegateM::TianShanIce::Storage::AccessRegistrar::count(const ::std::string& contentName, const ::std::string& subfile, ::Ice::Int countToAdd, const ::Ice::Context* __context)
{
    ::IceInternal::Outgoing __og(__connection.get(), __reference.get(), __TianShanIce__Storage__AccessRegistrar__count_name, ::Ice::Normal, __context, __compress);
    try
    {
        ::IceInternal::BasicStream* __os = __og.os();
        __os->write(contentName);
        __os->write(subfile);
        __os->write(countToAdd);
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
        ::TianShanIce::Storage::ContentAccess __ret;
        __ret.__read(__is);
        return __ret;
    }
    catch(const ::Ice::LocalException& __ex)
    {
        throw ::IceInternal::LocalExceptionWrapper(__ex, false);
    }
}

void
IceDelegateM::TianShanIce::Storage::AccessRegistrar::set(const ::TianShanIce::Storage::AccessCounter& counterToOverwrite, const ::Ice::Context* __context)
{
    ::IceInternal::Outgoing __og(__connection.get(), __reference.get(), __TianShanIce__Storage__AccessRegistrar__set_name, ::Ice::Normal, __context, __compress);
    try
    {
        ::IceInternal::BasicStream* __os = __og.os();
        counterToOverwrite.__write(__os);
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
IceDelegateM::TianShanIce::Storage::AccessRegistrar::erase(const ::std::string& contentName, const ::Ice::Context* __context)
{
    ::IceInternal::Outgoing __og(__connection.get(), __reference.get(), __TianShanIce__Storage__AccessRegistrar__erase_name, ::Ice::Normal, __context, __compress);
    try
    {
        ::IceInternal::BasicStream* __os = __og.os();
        __os->write(contentName);
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

bool
IceDelegateM::TianShanIce::Storage::AccessRegistrar::get(const ::std::string& contentName, ::TianShanIce::Storage::AccessCounter& counter, const ::Ice::Context* __context)
{
    ::IceInternal::Outgoing __og(__connection.get(), __reference.get(), __TianShanIce__Storage__AccessRegistrar__get_name, ::Ice::Normal, __context, __compress);
    try
    {
        ::IceInternal::BasicStream* __os = __og.os();
        __os->write(contentName);
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
        bool __ret;
        counter.__read(__is);
        __is->read(__ret);
        return __ret;
    }
    catch(const ::Ice::LocalException& __ex)
    {
        throw ::IceInternal::LocalExceptionWrapper(__ex, false);
    }
}

::Ice::Int
IceDelegateM::TianShanIce::Storage::AccessRegistrar::compress(::Ice::Int windowSize, ::Ice::Int flushWinSize, ::Ice::Int& reqsInWindow, ::TianShanIce::Storage::ContentCounterList& listToFlush, ::TianShanIce::Storage::ContentCounterList& listEvicted, const ::Ice::Context* __context)
{
    ::IceInternal::Outgoing __og(__connection.get(), __reference.get(), __TianShanIce__Storage__AccessRegistrar__compress_name, ::Ice::Normal, __context, __compress);
    try
    {
        ::IceInternal::BasicStream* __os = __og.os();
        __os->write(windowSize);
        __os->write(flushWinSize);
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
        ::Ice::Int __ret;
        __is->read(reqsInWindow);
        ::TianShanIce::Storage::__read(__is, listToFlush, ::TianShanIce::Storage::__U__ContentCounterList());
        ::TianShanIce::Storage::__read(__is, listEvicted, ::TianShanIce::Storage::__U__ContentCounterList());
        __is->read(__ret);
        return __ret;
    }
    catch(const ::Ice::LocalException& __ex)
    {
        throw ::IceInternal::LocalExceptionWrapper(__ex, false);
    }
}

void
IceDelegateM::TianShanIce::Storage::AccessRegistrar::sort(::Ice::Int windowSize, bool unpopular1st, ::Ice::Int minCount, ::TianShanIce::Storage::ContentCounterList& resultList, const ::Ice::Context* __context)
{
    ::IceInternal::Outgoing __og(__connection.get(), __reference.get(), __TianShanIce__Storage__AccessRegistrar__sort_name, ::Ice::Normal, __context, __compress);
    try
    {
        ::IceInternal::BasicStream* __os = __og.os();
        __os->write(windowSize);
        __os->write(unpopular1st);
        __os->write(minCount);
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
        ::TianShanIce::Storage::__read(__is, resultList, ::TianShanIce::Storage::__U__ContentCounterList());
    }
    catch(const ::Ice::LocalException& __ex)
    {
        throw ::IceInternal::LocalExceptionWrapper(__ex, false);
    }
}

::Ice::Int
IceDelegateM::TianShanIce::Storage::AccessRegistrar::size(const ::Ice::Context* __context)
{
    ::IceInternal::Outgoing __og(__connection.get(), __reference.get(), __TianShanIce__Storage__AccessRegistrar__size_name, ::Ice::Normal, __context, __compress);
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
        ::Ice::Int __ret;
        __is->read(__ret);
        return __ret;
    }
    catch(const ::Ice::LocalException& __ex)
    {
        throw ::IceInternal::LocalExceptionWrapper(__ex, false);
    }
}

bool
IceDelegateM::TianShanIce::Storage::TopFolder::eraseFromUnpopular(const ::std::string& fullContentName, const ::Ice::Context* __context)
{
    ::IceInternal::Outgoing __og(__connection.get(), __reference.get(), __TianShanIce__Storage__TopFolder__eraseFromUnpopular_name, ::Ice::Normal, __context, __compress);
    try
    {
        ::IceInternal::BasicStream* __os = __og.os();
        __os->write(fullContentName);
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
        bool __ret;
        __is->read(__ret);
        return __ret;
    }
    catch(const ::Ice::LocalException& __ex)
    {
        throw ::IceInternal::LocalExceptionWrapper(__ex, false);
    }
}

::TianShanIce::StrValues
IceDelegateM::TianShanIce::Storage::TopFolder::freeForSpace(::Ice::Long wishedSpaceMB, ::Ice::Long& freedMB, const ::Ice::Context* __context)
{
    ::IceInternal::Outgoing __og(__connection.get(), __reference.get(), __TianShanIce__Storage__TopFolder__freeForSpace_name, ::Ice::Normal, __context, __compress);
    try
    {
        ::IceInternal::BasicStream* __os = __og.os();
        __os->write(wishedSpaceMB);
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
        ::TianShanIce::StrValues __ret;
        __is->read(freedMB);
        __is->read(__ret);
        return __ret;
    }
    catch(const ::Ice::LocalException& __ex)
    {
        throw ::IceInternal::LocalExceptionWrapper(__ex, false);
    }
}

bool
IceDelegateM::TianShanIce::Storage::TopFolder::getSpaceUsage(::Ice::Long& totalMB, ::Ice::Long& freeMB, ::Ice::Long& usedMB, const ::Ice::Context* __context)
{
    ::IceInternal::Outgoing __og(__connection.get(), __reference.get(), __TianShanIce__Storage__TopFolder__getSpaceUsage_name, ::Ice::Normal, __context, __compress);
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
        bool __ret;
        __is->read(totalMB);
        __is->read(freeMB);
        __is->read(usedMB);
        __is->read(__ret);
        return __ret;
    }
    catch(const ::Ice::LocalException& __ex)
    {
        throw ::IceInternal::LocalExceptionWrapper(__ex, false);
    }
}

::Ice::Int
IceDelegateM::TianShanIce::Storage::TopFolder::unpopularSize(const ::Ice::Context* __context)
{
    ::IceInternal::Outgoing __og(__connection.get(), __reference.get(), __TianShanIce__Storage__TopFolder__unpopularSize_name, ::Ice::Normal, __context, __compress);
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
        ::Ice::Int __ret;
        __is->read(__ret);
        return __ret;
    }
    catch(const ::Ice::LocalException& __ex)
    {
        throw ::IceInternal::LocalExceptionWrapper(__ex, false);
    }
}

void
IceDelegateM::TianShanIce::Storage::TopFolder::doRefreshUnpopular(const ::Ice::Context* __context)
{
    ::IceInternal::Outgoing __og(__connection.get(), __reference.get(), __TianShanIce__Storage__TopFolder__doRefreshUnpopular_name, ::Ice::Normal, __context, __compress);
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
IceDelegateM::TianShanIce::Storage::CacheTask::OnRestore(const ::Ice::Context* __context)
{
    ::IceInternal::Outgoing __og(__connection.get(), __reference.get(), __TianShanIce__Storage__CacheTask__OnRestore_name, ::Ice::Normal, __context, __compress);
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
IceDelegateM::TianShanIce::Storage::CacheTask::destroy(const ::Ice::Context* __context)
{
    ::IceInternal::Outgoing __og(__connection.get(), __reference.get(), __TianShanIce__Storage__CacheTask__destroy_name, ::Ice::Normal, __context, __compress);
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

::TianShanIce::Storage::ContentAccess
IceDelegateD::TianShanIce::Storage::AccessRegistrar::count(const ::std::string& contentName, const ::std::string& subfile, ::Ice::Int countToAdd, const ::Ice::Context* __context)
{
    ::Ice::Current __current;
    __initCurrent(__current, __TianShanIce__Storage__AccessRegistrar__count_name, ::Ice::Normal, __context);
    while(true)
    {
        ::IceInternal::Direct __direct(__current);
        ::TianShanIce::Storage::ContentAccess __ret;
        try
        {
            ::TianShanIce::Storage::AccessRegistrar* __servant = dynamic_cast< ::TianShanIce::Storage::AccessRegistrar*>(__direct.servant().get());
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
                __ret = __servant->count(contentName, subfile, countToAdd, __current);
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
IceDelegateD::TianShanIce::Storage::AccessRegistrar::set(const ::TianShanIce::Storage::AccessCounter& counterToOverwrite, const ::Ice::Context* __context)
{
    ::Ice::Current __current;
    __initCurrent(__current, __TianShanIce__Storage__AccessRegistrar__set_name, ::Ice::Normal, __context);
    while(true)
    {
        ::IceInternal::Direct __direct(__current);
        try
        {
            ::TianShanIce::Storage::AccessRegistrar* __servant = dynamic_cast< ::TianShanIce::Storage::AccessRegistrar*>(__direct.servant().get());
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
                __servant->set(counterToOverwrite, __current);
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
IceDelegateD::TianShanIce::Storage::AccessRegistrar::erase(const ::std::string& contentName, const ::Ice::Context* __context)
{
    ::Ice::Current __current;
    __initCurrent(__current, __TianShanIce__Storage__AccessRegistrar__erase_name, ::Ice::Normal, __context);
    while(true)
    {
        ::IceInternal::Direct __direct(__current);
        try
        {
            ::TianShanIce::Storage::AccessRegistrar* __servant = dynamic_cast< ::TianShanIce::Storage::AccessRegistrar*>(__direct.servant().get());
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
                __servant->erase(contentName, __current);
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

bool
IceDelegateD::TianShanIce::Storage::AccessRegistrar::get(const ::std::string& contentName, ::TianShanIce::Storage::AccessCounter& counter, const ::Ice::Context* __context)
{
    ::Ice::Current __current;
    __initCurrent(__current, __TianShanIce__Storage__AccessRegistrar__get_name, ::Ice::Normal, __context);
    while(true)
    {
        ::IceInternal::Direct __direct(__current);
        bool __ret;
        try
        {
            ::TianShanIce::Storage::AccessRegistrar* __servant = dynamic_cast< ::TianShanIce::Storage::AccessRegistrar*>(__direct.servant().get());
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
                __ret = __servant->get(contentName, counter, __current);
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

::Ice::Int
IceDelegateD::TianShanIce::Storage::AccessRegistrar::compress(::Ice::Int windowSize, ::Ice::Int flushWinSize, ::Ice::Int& reqsInWindow, ::TianShanIce::Storage::ContentCounterList& listToFlush, ::TianShanIce::Storage::ContentCounterList& listEvicted, const ::Ice::Context* __context)
{
    ::Ice::Current __current;
    __initCurrent(__current, __TianShanIce__Storage__AccessRegistrar__compress_name, ::Ice::Normal, __context);
    while(true)
    {
        ::IceInternal::Direct __direct(__current);
        ::Ice::Int __ret;
        try
        {
            ::TianShanIce::Storage::AccessRegistrar* __servant = dynamic_cast< ::TianShanIce::Storage::AccessRegistrar*>(__direct.servant().get());
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
                __ret = __servant->compress(windowSize, flushWinSize, reqsInWindow, listToFlush, listEvicted, __current);
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
IceDelegateD::TianShanIce::Storage::AccessRegistrar::sort(::Ice::Int windowSize, bool unpopular1st, ::Ice::Int minCount, ::TianShanIce::Storage::ContentCounterList& resultList, const ::Ice::Context* __context)
{
    ::Ice::Current __current;
    __initCurrent(__current, __TianShanIce__Storage__AccessRegistrar__sort_name, ::Ice::Normal, __context);
    while(true)
    {
        ::IceInternal::Direct __direct(__current);
        try
        {
            ::TianShanIce::Storage::AccessRegistrar* __servant = dynamic_cast< ::TianShanIce::Storage::AccessRegistrar*>(__direct.servant().get());
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
                __servant->sort(windowSize, unpopular1st, minCount, resultList, __current);
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

::Ice::Int
IceDelegateD::TianShanIce::Storage::AccessRegistrar::size(const ::Ice::Context* __context)
{
    ::Ice::Current __current;
    __initCurrent(__current, __TianShanIce__Storage__AccessRegistrar__size_name, ::Ice::Normal, __context);
    while(true)
    {
        ::IceInternal::Direct __direct(__current);
        ::Ice::Int __ret;
        try
        {
            ::TianShanIce::Storage::AccessRegistrar* __servant = dynamic_cast< ::TianShanIce::Storage::AccessRegistrar*>(__direct.servant().get());
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
                __ret = __servant->size(__current);
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

bool
IceDelegateD::TianShanIce::Storage::TopFolder::eraseFromUnpopular(const ::std::string& fullContentName, const ::Ice::Context* __context)
{
    ::Ice::Current __current;
    __initCurrent(__current, __TianShanIce__Storage__TopFolder__eraseFromUnpopular_name, ::Ice::Normal, __context);
    while(true)
    {
        ::IceInternal::Direct __direct(__current);
        bool __ret;
        try
        {
            ::TianShanIce::Storage::TopFolder* __servant = dynamic_cast< ::TianShanIce::Storage::TopFolder*>(__direct.servant().get());
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
                __ret = __servant->eraseFromUnpopular(fullContentName, __current);
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

::TianShanIce::StrValues
IceDelegateD::TianShanIce::Storage::TopFolder::freeForSpace(::Ice::Long wishedSpaceMB, ::Ice::Long& freedMB, const ::Ice::Context* __context)
{
    ::Ice::Current __current;
    __initCurrent(__current, __TianShanIce__Storage__TopFolder__freeForSpace_name, ::Ice::Normal, __context);
    while(true)
    {
        ::IceInternal::Direct __direct(__current);
        ::TianShanIce::StrValues __ret;
        try
        {
            ::TianShanIce::Storage::TopFolder* __servant = dynamic_cast< ::TianShanIce::Storage::TopFolder*>(__direct.servant().get());
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
                __ret = __servant->freeForSpace(wishedSpaceMB, freedMB, __current);
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

bool
IceDelegateD::TianShanIce::Storage::TopFolder::getSpaceUsage(::Ice::Long& totalMB, ::Ice::Long& freeMB, ::Ice::Long& usedMB, const ::Ice::Context* __context)
{
    ::Ice::Current __current;
    __initCurrent(__current, __TianShanIce__Storage__TopFolder__getSpaceUsage_name, ::Ice::Normal, __context);
    while(true)
    {
        ::IceInternal::Direct __direct(__current);
        bool __ret;
        try
        {
            ::TianShanIce::Storage::TopFolder* __servant = dynamic_cast< ::TianShanIce::Storage::TopFolder*>(__direct.servant().get());
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
                __ret = __servant->getSpaceUsage(totalMB, freeMB, usedMB, __current);
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

::Ice::Int
IceDelegateD::TianShanIce::Storage::TopFolder::unpopularSize(const ::Ice::Context* __context)
{
    ::Ice::Current __current;
    __initCurrent(__current, __TianShanIce__Storage__TopFolder__unpopularSize_name, ::Ice::Normal, __context);
    while(true)
    {
        ::IceInternal::Direct __direct(__current);
        ::Ice::Int __ret;
        try
        {
            ::TianShanIce::Storage::TopFolder* __servant = dynamic_cast< ::TianShanIce::Storage::TopFolder*>(__direct.servant().get());
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
                __ret = __servant->unpopularSize(__current);
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
IceDelegateD::TianShanIce::Storage::TopFolder::doRefreshUnpopular(const ::Ice::Context* __context)
{
    ::Ice::Current __current;
    __initCurrent(__current, __TianShanIce__Storage__TopFolder__doRefreshUnpopular_name, ::Ice::Normal, __context);
    while(true)
    {
        ::IceInternal::Direct __direct(__current);
        try
        {
            ::TianShanIce::Storage::TopFolder* __servant = dynamic_cast< ::TianShanIce::Storage::TopFolder*>(__direct.servant().get());
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
                __servant->doRefreshUnpopular(__current);
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
IceDelegateD::TianShanIce::Storage::CacheTask::OnRestore(const ::Ice::Context* __context)
{
    ::Ice::Current __current;
    __initCurrent(__current, __TianShanIce__Storage__CacheTask__OnRestore_name, ::Ice::Normal, __context);
    while(true)
    {
        ::IceInternal::Direct __direct(__current);
        try
        {
            ::TianShanIce::Storage::CacheTask* __servant = dynamic_cast< ::TianShanIce::Storage::CacheTask*>(__direct.servant().get());
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
                __servant->OnRestore(__current);
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
IceDelegateD::TianShanIce::Storage::CacheTask::destroy(const ::Ice::Context* __context)
{
    ::Ice::Current __current;
    __initCurrent(__current, __TianShanIce__Storage__CacheTask__destroy_name, ::Ice::Normal, __context);
    while(true)
    {
        ::IceInternal::Direct __direct(__current);
        try
        {
            ::TianShanIce::Storage::CacheTask* __servant = dynamic_cast< ::TianShanIce::Storage::CacheTask*>(__direct.servant().get());
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

TianShanIce::Storage::AccessRegistrar::AccessRegistrar(const ::std::string& __ice_name, const ::TianShanIce::Storage::ContentCounterMap& __ice_counters) :
    name(__ice_name),
    counters(__ice_counters)
{
}

::Ice::ObjectPtr
TianShanIce::Storage::AccessRegistrar::ice_clone() const
{
    throw ::Ice::CloneNotImplementedException(__FILE__, __LINE__);
    return 0; // to avoid a warning with some compilers
}

static const ::std::string __TianShanIce__Storage__AccessRegistrar_ids[2] =
{
    "::Ice::Object",
    "::TianShanIce::Storage::AccessRegistrar"
};

bool
TianShanIce::Storage::AccessRegistrar::ice_isA(const ::std::string& _s, const ::Ice::Current&) const
{
    return ::std::binary_search(__TianShanIce__Storage__AccessRegistrar_ids, __TianShanIce__Storage__AccessRegistrar_ids + 2, _s);
}

::std::vector< ::std::string>
TianShanIce::Storage::AccessRegistrar::ice_ids(const ::Ice::Current&) const
{
    return ::std::vector< ::std::string>(&__TianShanIce__Storage__AccessRegistrar_ids[0], &__TianShanIce__Storage__AccessRegistrar_ids[2]);
}

const ::std::string&
TianShanIce::Storage::AccessRegistrar::ice_id(const ::Ice::Current&) const
{
    return __TianShanIce__Storage__AccessRegistrar_ids[1];
}

const ::std::string&
TianShanIce::Storage::AccessRegistrar::ice_staticId()
{
    return __TianShanIce__Storage__AccessRegistrar_ids[1];
}

::IceInternal::DispatchStatus
TianShanIce::Storage::AccessRegistrar::___count(::IceInternal::Incoming&__inS, const ::Ice::Current& __current)
{
    __checkMode(::Ice::Normal, __current.mode);
    ::IceInternal::BasicStream* __is = __inS.is();
    ::IceInternal::BasicStream* __os = __inS.os();
    ::std::string contentName;
    ::std::string subfile;
    ::Ice::Int countToAdd;
    __is->read(contentName);
    __is->read(subfile);
    __is->read(countToAdd);
    ::TianShanIce::Storage::ContentAccess __ret = count(contentName, subfile, countToAdd, __current);
    __ret.__write(__os);
    return ::IceInternal::DispatchOK;
}

::IceInternal::DispatchStatus
TianShanIce::Storage::AccessRegistrar::___set(::IceInternal::Incoming&__inS, const ::Ice::Current& __current)
{
    __checkMode(::Ice::Normal, __current.mode);
    ::IceInternal::BasicStream* __is = __inS.is();
    ::TianShanIce::Storage::AccessCounter counterToOverwrite;
    counterToOverwrite.__read(__is);
    set(counterToOverwrite, __current);
    return ::IceInternal::DispatchOK;
}

::IceInternal::DispatchStatus
TianShanIce::Storage::AccessRegistrar::___erase(::IceInternal::Incoming&__inS, const ::Ice::Current& __current)
{
    __checkMode(::Ice::Normal, __current.mode);
    ::IceInternal::BasicStream* __is = __inS.is();
    ::std::string contentName;
    __is->read(contentName);
    erase(contentName, __current);
    return ::IceInternal::DispatchOK;
}

::IceInternal::DispatchStatus
TianShanIce::Storage::AccessRegistrar::___get(::IceInternal::Incoming&__inS, const ::Ice::Current& __current)
{
    __checkMode(::Ice::Normal, __current.mode);
    ::IceInternal::BasicStream* __is = __inS.is();
    ::IceInternal::BasicStream* __os = __inS.os();
    ::std::string contentName;
    __is->read(contentName);
    ::TianShanIce::Storage::AccessCounter counter;
    bool __ret = get(contentName, counter, __current);
    counter.__write(__os);
    __os->write(__ret);
    return ::IceInternal::DispatchOK;
}

::IceInternal::DispatchStatus
TianShanIce::Storage::AccessRegistrar::___compress(::IceInternal::Incoming&__inS, const ::Ice::Current& __current)
{
    __checkMode(::Ice::Normal, __current.mode);
    ::IceInternal::BasicStream* __is = __inS.is();
    ::IceInternal::BasicStream* __os = __inS.os();
    ::Ice::Int windowSize;
    ::Ice::Int flushWinSize;
    __is->read(windowSize);
    __is->read(flushWinSize);
    ::Ice::Int reqsInWindow;
    ::TianShanIce::Storage::ContentCounterList listToFlush;
    ::TianShanIce::Storage::ContentCounterList listEvicted;
    ::Ice::Int __ret = compress(windowSize, flushWinSize, reqsInWindow, listToFlush, listEvicted, __current);
    __os->write(reqsInWindow);
    if(listToFlush.size() == 0)
    {
        __os->writeSize(0);
    }
    else
    {
        ::TianShanIce::Storage::__write(__os, &listToFlush[0], &listToFlush[0] + listToFlush.size(), ::TianShanIce::Storage::__U__ContentCounterList());
    }
    if(listEvicted.size() == 0)
    {
        __os->writeSize(0);
    }
    else
    {
        ::TianShanIce::Storage::__write(__os, &listEvicted[0], &listEvicted[0] + listEvicted.size(), ::TianShanIce::Storage::__U__ContentCounterList());
    }
    __os->write(__ret);
    return ::IceInternal::DispatchOK;
}

::IceInternal::DispatchStatus
TianShanIce::Storage::AccessRegistrar::___sort(::IceInternal::Incoming&__inS, const ::Ice::Current& __current)
{
    __checkMode(::Ice::Normal, __current.mode);
    ::IceInternal::BasicStream* __is = __inS.is();
    ::IceInternal::BasicStream* __os = __inS.os();
    ::Ice::Int windowSize;
    bool unpopular1st;
    ::Ice::Int minCount;
    __is->read(windowSize);
    __is->read(unpopular1st);
    __is->read(minCount);
    ::TianShanIce::Storage::ContentCounterList resultList;
    sort(windowSize, unpopular1st, minCount, resultList, __current);
    if(resultList.size() == 0)
    {
        __os->writeSize(0);
    }
    else
    {
        ::TianShanIce::Storage::__write(__os, &resultList[0], &resultList[0] + resultList.size(), ::TianShanIce::Storage::__U__ContentCounterList());
    }
    return ::IceInternal::DispatchOK;
}

::IceInternal::DispatchStatus
TianShanIce::Storage::AccessRegistrar::___size(::IceInternal::Incoming&__inS, const ::Ice::Current& __current)
{
    __checkMode(::Ice::Normal, __current.mode);
    ::IceInternal::BasicStream* __os = __inS.os();
    ::Ice::Int __ret = size(__current);
    __os->write(__ret);
    return ::IceInternal::DispatchOK;
}

static ::std::string __TianShanIce__Storage__AccessRegistrar_all[] =
{
    "compress",
    "count",
    "erase",
    "get",
    "ice_id",
    "ice_ids",
    "ice_isA",
    "ice_ping",
    "set",
    "size",
    "sort"
};

::IceInternal::DispatchStatus
TianShanIce::Storage::AccessRegistrar::__dispatch(::IceInternal::Incoming& in, const ::Ice::Current& current)
{
    ::std::pair< ::std::string*, ::std::string*> r = ::std::equal_range(__TianShanIce__Storage__AccessRegistrar_all, __TianShanIce__Storage__AccessRegistrar_all + 11, current.operation);
    if(r.first == r.second)
    {
        return ::IceInternal::DispatchOperationNotExist;
    }

    switch(r.first - __TianShanIce__Storage__AccessRegistrar_all)
    {
        case 0:
        {
            return ___compress(in, current);
        }
        case 1:
        {
            return ___count(in, current);
        }
        case 2:
        {
            return ___erase(in, current);
        }
        case 3:
        {
            return ___get(in, current);
        }
        case 4:
        {
            return ___ice_id(in, current);
        }
        case 5:
        {
            return ___ice_ids(in, current);
        }
        case 6:
        {
            return ___ice_isA(in, current);
        }
        case 7:
        {
            return ___ice_ping(in, current);
        }
        case 8:
        {
            return ___set(in, current);
        }
        case 9:
        {
            return ___size(in, current);
        }
        case 10:
        {
            return ___sort(in, current);
        }
    }

    assert(false);
    return ::IceInternal::DispatchOperationNotExist;
}

void
TianShanIce::Storage::AccessRegistrar::__write(::IceInternal::BasicStream* __os) const
{
    __os->writeTypeId(ice_staticId());
    __os->startWriteSlice();
    __os->write(name);
    ::TianShanIce::Storage::__write(__os, counters, ::TianShanIce::Storage::__U__ContentCounterMap());
    __os->endWriteSlice();
#if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
    Object::__write(__os);
#else
    ::Ice::Object::__write(__os);
#endif
}

void
TianShanIce::Storage::AccessRegistrar::__read(::IceInternal::BasicStream* __is, bool __rid)
{
    if(__rid)
    {
        ::std::string myId;
        __is->readTypeId(myId);
    }
    __is->startReadSlice();
    __is->read(name);
    ::TianShanIce::Storage::__read(__is, counters, ::TianShanIce::Storage::__U__ContentCounterMap());
    __is->endReadSlice();
#if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
    Object::__read(__is, true);
#else
    ::Ice::Object::__read(__is, true);
#endif
}

void
TianShanIce::Storage::AccessRegistrar::__write(const ::Ice::OutputStreamPtr&) const
{
    Ice::MarshalException ex(__FILE__, __LINE__);
    ex.reason = "type TianShanIce::Storage::AccessRegistrar was not generated with stream support";
    throw ex;
}

void
TianShanIce::Storage::AccessRegistrar::__read(const ::Ice::InputStreamPtr&, bool)
{
    Ice::MarshalException ex(__FILE__, __LINE__);
    ex.reason = "type TianShanIce::Storage::AccessRegistrar was not generated with stream support";
    throw ex;
}

void 
TianShanIce::Storage::__patch__AccessRegistrarPtr(void* __addr, ::Ice::ObjectPtr& v)
{
    ::TianShanIce::Storage::AccessRegistrarPtr* p = static_cast< ::TianShanIce::Storage::AccessRegistrarPtr*>(__addr);
    assert(p);
    *p = ::TianShanIce::Storage::AccessRegistrarPtr::dynamicCast(v);
    if(v && !*p)
    {
        ::Ice::UnexpectedObjectException e(__FILE__, __LINE__);
        e.type = v->ice_id();
        e.expectedType = ::TianShanIce::Storage::AccessRegistrar::ice_staticId();
        throw e;
    }
}

bool
TianShanIce::Storage::operator==(const ::TianShanIce::Storage::AccessRegistrar& l, const ::TianShanIce::Storage::AccessRegistrar& r)
{
    return static_cast<const ::Ice::Object&>(l) == static_cast<const ::Ice::Object&>(r);
}

bool
TianShanIce::Storage::operator!=(const ::TianShanIce::Storage::AccessRegistrar& l, const ::TianShanIce::Storage::AccessRegistrar& r)
{
    return static_cast<const ::Ice::Object&>(l) != static_cast<const ::Ice::Object&>(r);
}

bool
TianShanIce::Storage::operator<(const ::TianShanIce::Storage::AccessRegistrar& l, const ::TianShanIce::Storage::AccessRegistrar& r)
{
    return static_cast<const ::Ice::Object&>(l) < static_cast<const ::Ice::Object&>(r);
}

bool
TianShanIce::Storage::operator<=(const ::TianShanIce::Storage::AccessRegistrar& l, const ::TianShanIce::Storage::AccessRegistrar& r)
{
    return l < r || l == r;
}

bool
TianShanIce::Storage::operator>(const ::TianShanIce::Storage::AccessRegistrar& l, const ::TianShanIce::Storage::AccessRegistrar& r)
{
    return !(l < r) && !(l == r);
}

bool
TianShanIce::Storage::operator>=(const ::TianShanIce::Storage::AccessRegistrar& l, const ::TianShanIce::Storage::AccessRegistrar& r)
{
    return !(l < r);
}

TianShanIce::Storage::TopFolder::TopFolder(const ::Ice::Identity& __ice_ident, ::Ice::Long __ice_stampLastRefresh, const ::TianShanIce::StrValues& __ice_unpopularQueue, const ::TianShanIce::Storage::AccessRegistrarPtr& __ice_unpopulars, ::Ice::Int __ice_maxUnpopular, ::Ice::Long __ice_usedSpaceMB, const ::TianShanIce::IValues& __ice_contentsOfleaves, ::Ice::Int __ice_contentSubtotal) :
    ident(__ice_ident),
    stampLastRefresh(__ice_stampLastRefresh),
    unpopularQueue(__ice_unpopularQueue),
    unpopulars(__ice_unpopulars),
    maxUnpopular(__ice_maxUnpopular),
    usedSpaceMB(__ice_usedSpaceMB),
    contentsOfleaves(__ice_contentsOfleaves),
    contentSubtotal(__ice_contentSubtotal)
{
}

::Ice::ObjectPtr
TianShanIce::Storage::TopFolder::ice_clone() const
{
    throw ::Ice::CloneNotImplementedException(__FILE__, __LINE__);
    return 0; // to avoid a warning with some compilers
}

static const ::std::string __TianShanIce__Storage__TopFolder_ids[3] =
{
    "::Ice::Object",
    "::TianShanIce::Storage::TopFolder",
    "::TianShanUtils::TimeoutObj"
};

bool
TianShanIce::Storage::TopFolder::ice_isA(const ::std::string& _s, const ::Ice::Current&) const
{
    return ::std::binary_search(__TianShanIce__Storage__TopFolder_ids, __TianShanIce__Storage__TopFolder_ids + 3, _s);
}

::std::vector< ::std::string>
TianShanIce::Storage::TopFolder::ice_ids(const ::Ice::Current&) const
{
    return ::std::vector< ::std::string>(&__TianShanIce__Storage__TopFolder_ids[0], &__TianShanIce__Storage__TopFolder_ids[3]);
}

const ::std::string&
TianShanIce::Storage::TopFolder::ice_id(const ::Ice::Current&) const
{
    return __TianShanIce__Storage__TopFolder_ids[1];
}

const ::std::string&
TianShanIce::Storage::TopFolder::ice_staticId()
{
    return __TianShanIce__Storage__TopFolder_ids[1];
}

void
TianShanIce::Storage::TopFolder::__incRef()
{
    __gcIncRef();
}

void
TianShanIce::Storage::TopFolder::__decRef()
{
    __gcDecRef();
}

void
TianShanIce::Storage::TopFolder::__addObject(::IceInternal::GCCountMap& _c)
{
    ::IceInternal::GCCountMap::iterator pos = _c.find(this);
    if(pos == _c.end())
    {
        _c[this] = 1;
    }
    else
    {
        ++pos->second;
    }
}

bool
TianShanIce::Storage::TopFolder::__usesClasses()
{
    return true;
}

void
TianShanIce::Storage::TopFolder::__gcReachable(::IceInternal::GCCountMap& _c) const
{
    if(unpopulars)
    {
        ::TianShanIce::Storage::__addObject(unpopulars, _c);
    }
}

void
TianShanIce::Storage::TopFolder::__gcClear()
{
    if(unpopulars)
    {
        if(::TianShanIce::Storage::__usesClasses(unpopulars))
        {
            ::TianShanIce::Storage::__decRefUnsafe(unpopulars);
            ::TianShanIce::Storage::__clearHandleUnsafe(unpopulars);
        }
        else
        {
            unpopulars = 0;
        }
    }
}

::IceInternal::DispatchStatus
TianShanIce::Storage::TopFolder::___eraseFromUnpopular(::IceInternal::Incoming&__inS, const ::Ice::Current& __current)
{
    __checkMode(::Ice::Normal, __current.mode);
    ::IceInternal::BasicStream* __is = __inS.is();
    ::IceInternal::BasicStream* __os = __inS.os();
    ::std::string fullContentName;
    __is->read(fullContentName);
    bool __ret = eraseFromUnpopular(fullContentName, __current);
    __os->write(__ret);
    return ::IceInternal::DispatchOK;
}

::IceInternal::DispatchStatus
TianShanIce::Storage::TopFolder::___freeForSpace(::IceInternal::Incoming&__inS, const ::Ice::Current& __current)
{
    __checkMode(::Ice::Normal, __current.mode);
    ::IceInternal::BasicStream* __is = __inS.is();
    ::IceInternal::BasicStream* __os = __inS.os();
    ::Ice::Long wishedSpaceMB;
    __is->read(wishedSpaceMB);
    ::Ice::Long freedMB;
    ::TianShanIce::StrValues __ret = freeForSpace(wishedSpaceMB, freedMB, __current);
    __os->write(freedMB);
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
TianShanIce::Storage::TopFolder::___getSpaceUsage(::IceInternal::Incoming&__inS, const ::Ice::Current& __current)
{
    __checkMode(::Ice::Normal, __current.mode);
    ::IceInternal::BasicStream* __os = __inS.os();
    ::Ice::Long totalMB;
    ::Ice::Long freeMB;
    ::Ice::Long usedMB;
    bool __ret = getSpaceUsage(totalMB, freeMB, usedMB, __current);
    __os->write(totalMB);
    __os->write(freeMB);
    __os->write(usedMB);
    __os->write(__ret);
    return ::IceInternal::DispatchOK;
}

::IceInternal::DispatchStatus
TianShanIce::Storage::TopFolder::___unpopularSize(::IceInternal::Incoming&__inS, const ::Ice::Current& __current)
{
    __checkMode(::Ice::Normal, __current.mode);
    ::IceInternal::BasicStream* __os = __inS.os();
    ::Ice::Int __ret = unpopularSize(__current);
    __os->write(__ret);
    return ::IceInternal::DispatchOK;
}

::IceInternal::DispatchStatus
TianShanIce::Storage::TopFolder::___doRefreshUnpopular(::IceInternal::Incoming&, const ::Ice::Current& __current)
{
    __checkMode(::Ice::Normal, __current.mode);
    doRefreshUnpopular(__current);
    return ::IceInternal::DispatchOK;
}

static ::std::string __TianShanIce__Storage__TopFolder_all[] =
{
    "OnTimer",
    "doRefreshUnpopular",
    "eraseFromUnpopular",
    "freeForSpace",
    "getSpaceUsage",
    "ice_id",
    "ice_ids",
    "ice_isA",
    "ice_ping",
    "unpopularSize"
};

::IceInternal::DispatchStatus
TianShanIce::Storage::TopFolder::__dispatch(::IceInternal::Incoming& in, const ::Ice::Current& current)
{
    ::std::pair< ::std::string*, ::std::string*> r = ::std::equal_range(__TianShanIce__Storage__TopFolder_all, __TianShanIce__Storage__TopFolder_all + 10, current.operation);
    if(r.first == r.second)
    {
        return ::IceInternal::DispatchOperationNotExist;
    }

    switch(r.first - __TianShanIce__Storage__TopFolder_all)
    {
        case 0:
        {
            return ___OnTimer(in, current);
        }
        case 1:
        {
            return ___doRefreshUnpopular(in, current);
        }
        case 2:
        {
            return ___eraseFromUnpopular(in, current);
        }
        case 3:
        {
            return ___freeForSpace(in, current);
        }
        case 4:
        {
            return ___getSpaceUsage(in, current);
        }
        case 5:
        {
            return ___ice_id(in, current);
        }
        case 6:
        {
            return ___ice_ids(in, current);
        }
        case 7:
        {
            return ___ice_isA(in, current);
        }
        case 8:
        {
            return ___ice_ping(in, current);
        }
        case 9:
        {
            return ___unpopularSize(in, current);
        }
    }

    assert(false);
    return ::IceInternal::DispatchOperationNotExist;
}

static ::std::string __TianShanIce__Storage__TopFolder_freezeWriteOperations[] =
{
    "doRefreshUnpopular",
    "eraseFromUnpopular",
    "freeForSpace",
    "getSpaceUsage",
    "unpopularSize"
};

::Ice::Int
TianShanIce::Storage::TopFolder::ice_operationAttributes(const ::std::string& opName) const
{
    ::std::string* end = __TianShanIce__Storage__TopFolder_freezeWriteOperations + 5;
    ::std::string* r = ::std::find(__TianShanIce__Storage__TopFolder_freezeWriteOperations, end, opName);
    return r == end ? 0 : 1;
}

void
TianShanIce::Storage::TopFolder::__write(::IceInternal::BasicStream* __os) const
{
    __os->writeTypeId(ice_staticId());
    __os->startWriteSlice();
    ident.__write(__os);
    __os->write(stampLastRefresh);
    if(unpopularQueue.size() == 0)
    {
        __os->writeSize(0);
    }
    else
    {
        __os->write(&unpopularQueue[0], &unpopularQueue[0] + unpopularQueue.size());
    }
    ::TianShanIce::Storage::__write(__os, unpopulars);
    __os->write(maxUnpopular);
    __os->write(usedSpaceMB);
    if(contentsOfleaves.size() == 0)
    {
        __os->writeSize(0);
    }
    else
    {
        __os->write(&contentsOfleaves[0], &contentsOfleaves[0] + contentsOfleaves.size());
    }
    __os->write(contentSubtotal);
    __os->endWriteSlice();
#if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
    Object::__write(__os);
#else
    ::Ice::Object::__write(__os);
#endif
}

void
TianShanIce::Storage::TopFolder::__read(::IceInternal::BasicStream* __is, bool __rid)
{
    if(__rid)
    {
        ::std::string myId;
        __is->readTypeId(myId);
    }
    __is->startReadSlice();
    ident.__read(__is);
    __is->read(stampLastRefresh);
    __is->read(unpopularQueue);
    __is->read(::TianShanIce::Storage::__patch__AccessRegistrarPtr, &unpopulars);
    __is->read(maxUnpopular);
    __is->read(usedSpaceMB);
    __is->read(contentsOfleaves);
    __is->read(contentSubtotal);
    __is->endReadSlice();
#if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
    Object::__read(__is, true);
#else
    ::Ice::Object::__read(__is, true);
#endif
}

void
TianShanIce::Storage::TopFolder::__write(const ::Ice::OutputStreamPtr&) const
{
    Ice::MarshalException ex(__FILE__, __LINE__);
    ex.reason = "type TianShanIce::Storage::TopFolder was not generated with stream support";
    throw ex;
}

void
TianShanIce::Storage::TopFolder::__read(const ::Ice::InputStreamPtr&, bool)
{
    Ice::MarshalException ex(__FILE__, __LINE__);
    ex.reason = "type TianShanIce::Storage::TopFolder was not generated with stream support";
    throw ex;
}

void 
TianShanIce::Storage::__patch__TopFolderPtr(void* __addr, ::Ice::ObjectPtr& v)
{
    ::TianShanIce::Storage::TopFolderPtr* p = static_cast< ::TianShanIce::Storage::TopFolderPtr*>(__addr);
    assert(p);
    *p = ::TianShanIce::Storage::TopFolderPtr::dynamicCast(v);
    if(v && !*p)
    {
        ::Ice::UnexpectedObjectException e(__FILE__, __LINE__);
        e.type = v->ice_id();
        e.expectedType = ::TianShanIce::Storage::TopFolder::ice_staticId();
        throw e;
    }
}

bool
TianShanIce::Storage::operator==(const ::TianShanIce::Storage::TopFolder& l, const ::TianShanIce::Storage::TopFolder& r)
{
    return static_cast<const ::Ice::Object&>(l) == static_cast<const ::Ice::Object&>(r);
}

bool
TianShanIce::Storage::operator!=(const ::TianShanIce::Storage::TopFolder& l, const ::TianShanIce::Storage::TopFolder& r)
{
    return static_cast<const ::Ice::Object&>(l) != static_cast<const ::Ice::Object&>(r);
}

bool
TianShanIce::Storage::operator<(const ::TianShanIce::Storage::TopFolder& l, const ::TianShanIce::Storage::TopFolder& r)
{
    return static_cast<const ::Ice::Object&>(l) < static_cast<const ::Ice::Object&>(r);
}

bool
TianShanIce::Storage::operator<=(const ::TianShanIce::Storage::TopFolder& l, const ::TianShanIce::Storage::TopFolder& r)
{
    return l < r || l == r;
}

bool
TianShanIce::Storage::operator>(const ::TianShanIce::Storage::TopFolder& l, const ::TianShanIce::Storage::TopFolder& r)
{
    return !(l < r) && !(l == r);
}

bool
TianShanIce::Storage::operator>=(const ::TianShanIce::Storage::TopFolder& l, const ::TianShanIce::Storage::TopFolder& r)
{
    return !(l < r);
}

TianShanIce::Storage::CacheTask::CacheTask(const ::Ice::Identity& __ice_ident, const ::TianShanIce::Storage::UnivContentPrx& __ice_localContent, const ::TianShanIce::Properties& __ice_nameFields, const ::TianShanIce::Streamer::StreamPrx& __ice_srcStream, const ::std::string& __ice_urlSrcStream, const ::std::string& __ice_srcContentType, bool __ice_isSrcPWE, ::Ice::Int __ice_bwMin, ::Ice::Int __ice_bwMax, ::Ice::Int __ice_bwCommitted, ::Ice::Long __ice_startOffset, ::Ice::Long __ice_endOffset, const ::std::string& __ice_scheduledStart, const ::std::string& __ice_scheduledEnd, const ::TianShanIce::ContentProvision::ProvisionSessionPrx& __ice_provisionSess, ::Ice::Long __ice_stampCreated, ::Ice::Long __ice_stampCommitted, ::Ice::Long __ice_stampStopped) :
    ident(__ice_ident),
    localContent(__ice_localContent),
    nameFields(__ice_nameFields),
    srcStream(__ice_srcStream),
    urlSrcStream(__ice_urlSrcStream),
    srcContentType(__ice_srcContentType),
    isSrcPWE(__ice_isSrcPWE),
    bwMin(__ice_bwMin),
    bwMax(__ice_bwMax),
    bwCommitted(__ice_bwCommitted),
    startOffset(__ice_startOffset),
    endOffset(__ice_endOffset),
    scheduledStart(__ice_scheduledStart),
    scheduledEnd(__ice_scheduledEnd),
    provisionSess(__ice_provisionSess),
    stampCreated(__ice_stampCreated),
    stampCommitted(__ice_stampCommitted),
    stampStopped(__ice_stampStopped)
{
}

::Ice::ObjectPtr
TianShanIce::Storage::CacheTask::ice_clone() const
{
    throw ::Ice::CloneNotImplementedException(__FILE__, __LINE__);
    return 0; // to avoid a warning with some compilers
}

static const ::std::string __TianShanIce__Storage__CacheTask_ids[3] =
{
    "::Ice::Object",
    "::TianShanIce::Storage::CacheTask",
    "::TianShanUtils::TimeoutObj"
};

bool
TianShanIce::Storage::CacheTask::ice_isA(const ::std::string& _s, const ::Ice::Current&) const
{
    return ::std::binary_search(__TianShanIce__Storage__CacheTask_ids, __TianShanIce__Storage__CacheTask_ids + 3, _s);
}

::std::vector< ::std::string>
TianShanIce::Storage::CacheTask::ice_ids(const ::Ice::Current&) const
{
    return ::std::vector< ::std::string>(&__TianShanIce__Storage__CacheTask_ids[0], &__TianShanIce__Storage__CacheTask_ids[3]);
}

const ::std::string&
TianShanIce::Storage::CacheTask::ice_id(const ::Ice::Current&) const
{
    return __TianShanIce__Storage__CacheTask_ids[1];
}

const ::std::string&
TianShanIce::Storage::CacheTask::ice_staticId()
{
    return __TianShanIce__Storage__CacheTask_ids[1];
}

::IceInternal::DispatchStatus
TianShanIce::Storage::CacheTask::___OnRestore(::IceInternal::Incoming&, const ::Ice::Current& __current)
{
    __checkMode(::Ice::Normal, __current.mode);
    OnRestore(__current);
    return ::IceInternal::DispatchOK;
}

::IceInternal::DispatchStatus
TianShanIce::Storage::CacheTask::___destroy(::IceInternal::Incoming&, const ::Ice::Current& __current)
{
    __checkMode(::Ice::Normal, __current.mode);
    destroy(__current);
    return ::IceInternal::DispatchOK;
}

static ::std::string __TianShanIce__Storage__CacheTask_all[] =
{
    "OnRestore",
    "OnTimer",
    "destroy",
    "ice_id",
    "ice_ids",
    "ice_isA",
    "ice_ping"
};

::IceInternal::DispatchStatus
TianShanIce::Storage::CacheTask::__dispatch(::IceInternal::Incoming& in, const ::Ice::Current& current)
{
    ::std::pair< ::std::string*, ::std::string*> r = ::std::equal_range(__TianShanIce__Storage__CacheTask_all, __TianShanIce__Storage__CacheTask_all + 7, current.operation);
    if(r.first == r.second)
    {
        return ::IceInternal::DispatchOperationNotExist;
    }

    switch(r.first - __TianShanIce__Storage__CacheTask_all)
    {
        case 0:
        {
            return ___OnRestore(in, current);
        }
        case 1:
        {
            return ___OnTimer(in, current);
        }
        case 2:
        {
            return ___destroy(in, current);
        }
        case 3:
        {
            return ___ice_id(in, current);
        }
        case 4:
        {
            return ___ice_ids(in, current);
        }
        case 5:
        {
            return ___ice_isA(in, current);
        }
        case 6:
        {
            return ___ice_ping(in, current);
        }
    }

    assert(false);
    return ::IceInternal::DispatchOperationNotExist;
}

static ::std::string __TianShanIce__Storage__CacheTask_freezeWriteOperations[] =
{
    "OnRestore",
    "destroy"
};

::Ice::Int
TianShanIce::Storage::CacheTask::ice_operationAttributes(const ::std::string& opName) const
{
    ::std::string* end = __TianShanIce__Storage__CacheTask_freezeWriteOperations + 2;
    ::std::string* r = ::std::find(__TianShanIce__Storage__CacheTask_freezeWriteOperations, end, opName);
    return r == end ? 0 : 1;
}

void
TianShanIce::Storage::CacheTask::__write(::IceInternal::BasicStream* __os) const
{
    __os->writeTypeId(ice_staticId());
    __os->startWriteSlice();
    ident.__write(__os);
    ::TianShanIce::Storage::__write(__os, localContent);
    ::TianShanIce::__write(__os, nameFields, ::TianShanIce::__U__Properties());
    ::TianShanIce::Streamer::__write(__os, srcStream);
    __os->write(urlSrcStream);
    __os->write(srcContentType);
    __os->write(isSrcPWE);
    __os->write(bwMin);
    __os->write(bwMax);
    __os->write(bwCommitted);
    __os->write(startOffset);
    __os->write(endOffset);
    __os->write(scheduledStart);
    __os->write(scheduledEnd);
    ::TianShanIce::ContentProvision::__write(__os, provisionSess);
    __os->write(stampCreated);
    __os->write(stampCommitted);
    __os->write(stampStopped);
    __os->endWriteSlice();
#if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
    Object::__write(__os);
#else
    ::Ice::Object::__write(__os);
#endif
}

void
TianShanIce::Storage::CacheTask::__read(::IceInternal::BasicStream* __is, bool __rid)
{
    if(__rid)
    {
        ::std::string myId;
        __is->readTypeId(myId);
    }
    __is->startReadSlice();
    ident.__read(__is);
    ::TianShanIce::Storage::__read(__is, localContent);
    ::TianShanIce::__read(__is, nameFields, ::TianShanIce::__U__Properties());
    ::TianShanIce::Streamer::__read(__is, srcStream);
    __is->read(urlSrcStream);
    __is->read(srcContentType);
    __is->read(isSrcPWE);
    __is->read(bwMin);
    __is->read(bwMax);
    __is->read(bwCommitted);
    __is->read(startOffset);
    __is->read(endOffset);
    __is->read(scheduledStart);
    __is->read(scheduledEnd);
    ::TianShanIce::ContentProvision::__read(__is, provisionSess);
    __is->read(stampCreated);
    __is->read(stampCommitted);
    __is->read(stampStopped);
    __is->endReadSlice();
#if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
    Object::__read(__is, true);
#else
    ::Ice::Object::__read(__is, true);
#endif
}

void
TianShanIce::Storage::CacheTask::__write(const ::Ice::OutputStreamPtr&) const
{
    Ice::MarshalException ex(__FILE__, __LINE__);
    ex.reason = "type TianShanIce::Storage::CacheTask was not generated with stream support";
    throw ex;
}

void
TianShanIce::Storage::CacheTask::__read(const ::Ice::InputStreamPtr&, bool)
{
    Ice::MarshalException ex(__FILE__, __LINE__);
    ex.reason = "type TianShanIce::Storage::CacheTask was not generated with stream support";
    throw ex;
}

void 
TianShanIce::Storage::__patch__CacheTaskPtr(void* __addr, ::Ice::ObjectPtr& v)
{
    ::TianShanIce::Storage::CacheTaskPtr* p = static_cast< ::TianShanIce::Storage::CacheTaskPtr*>(__addr);
    assert(p);
    *p = ::TianShanIce::Storage::CacheTaskPtr::dynamicCast(v);
    if(v && !*p)
    {
        ::Ice::UnexpectedObjectException e(__FILE__, __LINE__);
        e.type = v->ice_id();
        e.expectedType = ::TianShanIce::Storage::CacheTask::ice_staticId();
        throw e;
    }
}

bool
TianShanIce::Storage::operator==(const ::TianShanIce::Storage::CacheTask& l, const ::TianShanIce::Storage::CacheTask& r)
{
    return static_cast<const ::Ice::Object&>(l) == static_cast<const ::Ice::Object&>(r);
}

bool
TianShanIce::Storage::operator!=(const ::TianShanIce::Storage::CacheTask& l, const ::TianShanIce::Storage::CacheTask& r)
{
    return static_cast<const ::Ice::Object&>(l) != static_cast<const ::Ice::Object&>(r);
}

bool
TianShanIce::Storage::operator<(const ::TianShanIce::Storage::CacheTask& l, const ::TianShanIce::Storage::CacheTask& r)
{
    return static_cast<const ::Ice::Object&>(l) < static_cast<const ::Ice::Object&>(r);
}

bool
TianShanIce::Storage::operator<=(const ::TianShanIce::Storage::CacheTask& l, const ::TianShanIce::Storage::CacheTask& r)
{
    return l < r || l == r;
}

bool
TianShanIce::Storage::operator>(const ::TianShanIce::Storage::CacheTask& l, const ::TianShanIce::Storage::CacheTask& r)
{
    return !(l < r) && !(l == r);
}

bool
TianShanIce::Storage::operator>=(const ::TianShanIce::Storage::CacheTask& l, const ::TianShanIce::Storage::CacheTask& r)
{
    return !(l < r);
}

::Ice::ObjectPtr
TianShanIce::Storage::CacheStoreEx::ice_clone() const
{
    throw ::Ice::CloneNotImplementedException(__FILE__, __LINE__);
    return 0; // to avoid a warning with some compilers
}

static const ::std::string __TianShanIce__Storage__CacheStoreEx_ids[5] =
{
    "::Ice::Object",
    "::TianShanIce::ReplicaQuery",
    "::TianShanIce::Storage::CacheStore",
    "::TianShanIce::Storage::CacheStoreEx",
    "::TianShanUtils::TimeoutObj"
};

bool
TianShanIce::Storage::CacheStoreEx::ice_isA(const ::std::string& _s, const ::Ice::Current&) const
{
    return ::std::binary_search(__TianShanIce__Storage__CacheStoreEx_ids, __TianShanIce__Storage__CacheStoreEx_ids + 5, _s);
}

::std::vector< ::std::string>
TianShanIce::Storage::CacheStoreEx::ice_ids(const ::Ice::Current&) const
{
    return ::std::vector< ::std::string>(&__TianShanIce__Storage__CacheStoreEx_ids[0], &__TianShanIce__Storage__CacheStoreEx_ids[5]);
}

const ::std::string&
TianShanIce::Storage::CacheStoreEx::ice_id(const ::Ice::Current&) const
{
    return __TianShanIce__Storage__CacheStoreEx_ids[3];
}

const ::std::string&
TianShanIce::Storage::CacheStoreEx::ice_staticId()
{
    return __TianShanIce__Storage__CacheStoreEx_ids[3];
}

static ::std::string __TianShanIce__Storage__CacheStoreEx_all[] =
{
    "OnTimer",
    "addAccessCount",
    "cacheContent",
    "calculateCacheDistance",
    "exportContentAsStream",
    "getAccessCount",
    "getAccessThreshold",
    "getCandidatesOfContent",
    "getFileNameOfLocalContent",
    "getFolderNameOfContent",
    "ice_id",
    "ice_ids",
    "ice_isA",
    "ice_ping",
    "listHotLocals",
    "listMissedContents",
    "listNeighors",
    "queryReplicas",
    "setAccessThreshold",
    "theContentStore"
};

::IceInternal::DispatchStatus
TianShanIce::Storage::CacheStoreEx::__dispatch(::IceInternal::Incoming& in, const ::Ice::Current& current)
{
    ::std::pair< ::std::string*, ::std::string*> r = ::std::equal_range(__TianShanIce__Storage__CacheStoreEx_all, __TianShanIce__Storage__CacheStoreEx_all + 20, current.operation);
    if(r.first == r.second)
    {
        return ::IceInternal::DispatchOperationNotExist;
    }

    switch(r.first - __TianShanIce__Storage__CacheStoreEx_all)
    {
        case 0:
        {
            return ___OnTimer(in, current);
        }
        case 1:
        {
            return ___addAccessCount(in, current);
        }
        case 2:
        {
            return ___cacheContent(in, current);
        }
        case 3:
        {
            return ___calculateCacheDistance(in, current);
        }
        case 4:
        {
            return ___exportContentAsStream(in, current);
        }
        case 5:
        {
            return ___getAccessCount(in, current);
        }
        case 6:
        {
            return ___getAccessThreshold(in, current);
        }
        case 7:
        {
            return ___getCandidatesOfContent(in, current);
        }
        case 8:
        {
            return ___getFileNameOfLocalContent(in, current);
        }
        case 9:
        {
            return ___getFolderNameOfContent(in, current);
        }
        case 10:
        {
            return ___ice_id(in, current);
        }
        case 11:
        {
            return ___ice_ids(in, current);
        }
        case 12:
        {
            return ___ice_isA(in, current);
        }
        case 13:
        {
            return ___ice_ping(in, current);
        }
        case 14:
        {
            return ___listHotLocals(in, current);
        }
        case 15:
        {
            return ___listMissedContents(in, current);
        }
        case 16:
        {
            return ___listNeighors(in, current);
        }
        case 17:
        {
            return ___queryReplicas(in, current);
        }
        case 18:
        {
            return ___setAccessThreshold(in, current);
        }
        case 19:
        {
            return ___theContentStore(in, current);
        }
    }

    assert(false);
    return ::IceInternal::DispatchOperationNotExist;
}

void
TianShanIce::Storage::CacheStoreEx::__write(::IceInternal::BasicStream* __os) const
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
TianShanIce::Storage::CacheStoreEx::__read(::IceInternal::BasicStream* __is, bool __rid)
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
TianShanIce::Storage::CacheStoreEx::__write(const ::Ice::OutputStreamPtr&) const
{
    Ice::MarshalException ex(__FILE__, __LINE__);
    ex.reason = "type TianShanIce::Storage::CacheStoreEx was not generated with stream support";
    throw ex;
}

void
TianShanIce::Storage::CacheStoreEx::__read(const ::Ice::InputStreamPtr&, bool)
{
    Ice::MarshalException ex(__FILE__, __LINE__);
    ex.reason = "type TianShanIce::Storage::CacheStoreEx was not generated with stream support";
    throw ex;
}

void 
TianShanIce::Storage::__patch__CacheStoreExPtr(void* __addr, ::Ice::ObjectPtr& v)
{
    ::TianShanIce::Storage::CacheStoreExPtr* p = static_cast< ::TianShanIce::Storage::CacheStoreExPtr*>(__addr);
    assert(p);
    *p = ::TianShanIce::Storage::CacheStoreExPtr::dynamicCast(v);
    if(v && !*p)
    {
        ::Ice::UnexpectedObjectException e(__FILE__, __LINE__);
        e.type = v->ice_id();
        e.expectedType = ::TianShanIce::Storage::CacheStoreEx::ice_staticId();
        throw e;
    }
}

bool
TianShanIce::Storage::operator==(const ::TianShanIce::Storage::CacheStoreEx& l, const ::TianShanIce::Storage::CacheStoreEx& r)
{
    return static_cast<const ::Ice::Object&>(l) == static_cast<const ::Ice::Object&>(r);
}

bool
TianShanIce::Storage::operator!=(const ::TianShanIce::Storage::CacheStoreEx& l, const ::TianShanIce::Storage::CacheStoreEx& r)
{
    return static_cast<const ::Ice::Object&>(l) != static_cast<const ::Ice::Object&>(r);
}

bool
TianShanIce::Storage::operator<(const ::TianShanIce::Storage::CacheStoreEx& l, const ::TianShanIce::Storage::CacheStoreEx& r)
{
    return static_cast<const ::Ice::Object&>(l) < static_cast<const ::Ice::Object&>(r);
}

bool
TianShanIce::Storage::operator<=(const ::TianShanIce::Storage::CacheStoreEx& l, const ::TianShanIce::Storage::CacheStoreEx& r)
{
    return l < r || l == r;
}

bool
TianShanIce::Storage::operator>(const ::TianShanIce::Storage::CacheStoreEx& l, const ::TianShanIce::Storage::CacheStoreEx& r)
{
    return !(l < r) && !(l == r);
}

bool
TianShanIce::Storage::operator>=(const ::TianShanIce::Storage::CacheStoreEx& l, const ::TianShanIce::Storage::CacheStoreEx& r)
{
    return !(l < r);
}
