
#pragma once

#include "base/memory/ref_counted.h"

class A : public base::RefCounted<A>
{
public:
    A()
    {
        LOG(INFO) << "A ctor";
    }
    ~A()
    {
        LOG(INFO) << "A dtor";
    }

};


void TestRefCount()
{
    scoped_refptr<A> p(new A());
}