/*
 * (C) Copyright 1996-2013 ECMWF.
 * 
 * This software is licensed under the terms of the Apache Licence Version 2.0
 * which can be obtained at http://www.apache.org/licenses/LICENSE-2.0. 
 * In applying this licence, ECMWF does not waive the privileges and immunities 
 * granted to it by virtue of its status as an intergovernmental organisation nor
 * does it submit to any jurisdiction.
 */

#ifndef eckit_LibBehavior_h
#define eckit_LibBehavior_h

#include "eckit/log/CallbackLogger.h"
#include "eckit/runtime/StandardBehavior.h"

//-----------------------------------------------------------------------------

namespace eckit {

//-----------------------------------------------------------------------------

class LibBehavior : public StandardBehavior {

public: // methods

    /// Contructors

	LibBehavior();

    /// Destructor

	~LibBehavior();
        
    void register_logger_callback(CallbackLogger::callback c, void* ctxt = 0 );
    
private: // interface methods
        
    virtual LogStream& infoStream();
    virtual LogStream& warnStream();
    virtual LogStream& errorStream();
    virtual LogStream& debugStream();

protected: // members
    
    CallbackLogger::callback c_;
    void* ctxt_;
    
};


//-----------------------------------------------------------------------------

} // namespace eckit

#endif // eckit_LibBehavior_h
