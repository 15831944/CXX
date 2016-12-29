// **********************************************************************
//
// Copyright (c) 2003-2007 ZeroC, Inc. All rights reserved.
//
// This copy of Ice is licensed to you under the terms described in the
// ICE_LICENSE file included in this distribution.
//
// **********************************************************************

// Ice version 3.2.1

// Freeze types in this file:
// name="TianShanIce::EdgeResource::OwnerOfAllocationEx", type="::TianShanIce::EdgeResource::AllocationEx", member="ownerKey"

#include <Ice/BasicStream.h>
#include <OwnerOfAllocationEx.h>

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

TianShanIce::EdgeResource::OwnerOfAllocationEx::OwnerOfAllocationEx(const ::std::string& __name, const ::std::string& __facet)
    : Freeze::Index(__name, __facet)
{
}

std::vector<Ice::Identity>
TianShanIce::EdgeResource::OwnerOfAllocationEx::findFirst(const ::std::string& __index, ::Ice::Int __firstN) const
{
    Freeze::Key __bytes;
    marshalKey(__index, __bytes);
    return untypedFindFirst(__bytes, __firstN);
}

std::vector<Ice::Identity>
TianShanIce::EdgeResource::OwnerOfAllocationEx::find(const ::std::string& __index) const
{
    Freeze::Key __bytes;
    marshalKey(__index, __bytes);
    return untypedFind(__bytes);
}

Ice::Int
TianShanIce::EdgeResource::OwnerOfAllocationEx::count(const ::std::string& __index) const
{
    Freeze::Key __bytes;
    marshalKey(__index, __bytes);
    return untypedCount(__bytes);
}

bool
TianShanIce::EdgeResource::OwnerOfAllocationEx::marshalKey(const Ice::ObjectPtr& __servant, Freeze::Key& __bytes) const
{
    ::TianShanIce::EdgeResource::AllocationExPtr __s = ::TianShanIce::EdgeResource::AllocationExPtr::dynamicCast(__servant);
    if(__s != 0)
    {
        marshalKey(__s->ownerKey, __bytes);
        return true;
    }
    else
    {
        return false;
    }
}

void
TianShanIce::EdgeResource::OwnerOfAllocationEx::marshalKey(const ::std::string& __index, Freeze::Key& __bytes) const
{
    IceInternal::InstancePtr __instance = IceInternal::getInstance(_communicator);
    IceInternal::BasicStream __stream(__instance.get());
    __stream.write(__index);
    ::std::vector<Ice::Byte>(__stream.b.begin(), __stream.b.end()).swap(__bytes);
}
