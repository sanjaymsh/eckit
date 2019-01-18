/*
 * (C) Copyright 1996- ECMWF.
 * 
 * This software is licensed under the terms of the Apache Licence Version 2.0
 * which can be obtained at http://www.apache.org/licenses/LICENSE-2.0. 
 * In applying this licence, ECMWF does not waive the privileges and immunities 
 * granted to it by virtue of its status as an intergovernmental organisation nor
 * does it submit to any jurisdiction.
 */

// @author Simon Smart
// @date January 2019

#ifndef eckit_sql_SchemaComponents_H
#define eckit_sql_SchemaComponents_H

#include <string>


namespace eckit {
namespace sql {

//----------------------------------------------------------------------------------------------------------------------

class ColumnDef {

public: // methods

    ColumnDef(const std::string& name,
              const std::string& type);
//              const Range& range,
//              const std::string& defaultValue);
    ColumnDef();
    ~ColumnDef();

    const std::string& name() const { return name_; }
    const std::string& type() const { return type_; }

private: // members

    std::string name_;
    std::string type_;
};

//----------------------------------------------------------------------------------------------------------------------


//----------------------------------------------------------------------------------------------------------------------

} // namespace sql
} // namespace eckit

#endif
