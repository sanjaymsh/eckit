/*
 * (C) Copyright 1996-2013 ECMWF.
 *
 * This software is licensed under the terms of the Apache Licence Version 2.0
 * which can be obtained at http://www.apache.org/licenses/LICENSE-2.0.
 * In applying this licence, ECMWF does not waive the privileges and immunities
 * granted to it by virtue of its status as an intergovernmental organisation nor
 * does it submit to any jurisdiction.
 */

#include "eckit/thread/AutoLock.h"
#include "eckit/thread/Mutex.h"

#include "eckit/maths/Function.h"
#include "eckit/maths/Value.h"
#include "eckit/maths/Optimiser.h"

namespace eckit {
namespace maths {

//--------------------------------------------------------------------------------------------

Function::Function() : Expression()
{
}

Function::Function(const args_t &args) : Expression(args)
{
}

Function::~Function()
{
}

Function::dispatcher_t& Function::dispatcher()
{
    static dispatcher_t d;
    return d;
}

/*
Function::factory_t& Function::factory()
{
    static factory_t f;
    return f;
}*/

string Function::signature() const
{
    return signatureArguments( args_ );
}

ExpPtr Function::evaluate( Scope &ctx ) const
{
    DBG;

    args_t args = args_; // create temporary args

    const size_t nargs = args.size();
    for( size_t i = 0; i < nargs; ++i )
    {
        args[i] = param(i, ctx)->eval(ctx)->self();
    }

    std::string sig = signatureArguments( args );

    DBGX(sig);

    dispatcher_t& d = dispatcher();
    dispatcher_t::iterator itr = d.find( sig );
    if( itr == d.end() )
    {
        std::ostringstream msg;
        msg << "could not dispatch to function with signature: " << sig;
        throw Error( Here(), msg.str() );
    }

    return ((*itr).second)( ctx, args );
}

void Function::print(std::ostream&o) const
{
    o << typeName() << "("; printArgs(o); o << ")";
}

ExpPtr Function::optimise(size_t depth) const
{
    return Optimiser::apply(self(), depth);
}

string Function::signatureArguments(const args_t &args) const
{
    std::ostringstream o;
    o << typeName() << "(";
    for( size_t i = 0; i < args.size(); ++i )
    {
        if(i) o << ",";
        o << args[i]->signature();
    }
    o << ")";
    return o.str();
}

//--------------------------------------------------------------------------------------------

} // namespace maths
} // namespace eckit
