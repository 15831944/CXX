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
// name="TianShanIce::EdgeResource::QAMSessOfAllocationEx", type="::TianShanIce::EdgeResource::AllocationEx", member="qamSessionId"

#ifndef ____QAMSessOfAllocationEx_h__
#define ____QAMSessOfAllocationEx_h__

#include <Freeze/Index.h>
#include <EdgeRM.h>

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

namespace TianShanIce
{

namespace EdgeResource
{

class QAMSessOfAllocationEx : public Freeze::Index
{
public:

    QAMSessOfAllocationEx(const std::string&, const std::string& = "");

    std::vector<Ice::Identity>
    findFirst(const ::std::string&, Ice::Int) const;

    std::vector<Ice::Identity>
    find(const ::std::string&) const;

    Ice::Int
    count(const ::std::string&) const;

private:

    virtual bool
    marshalKey(const Ice::ObjectPtr&, Freeze::Key&) const;

    void
    marshalKey(const ::std::string&, Freeze::Key&) const;
};

typedef IceUtil::Handle<QAMSessOfAllocationEx> QAMSessOfAllocationExPtr;

}

}

#endif
