/*
 * (C) Copyright 1996-2012 ECMWF.
 * 
 * This software is licensed under the terms of the Apache Licence Version 2.0
 * which can be obtained at http://www.apache.org/licenses/LICENSE-2.0. 
 * In applying this licence, ECMWF does not waive the privileges and immunities 
 * granted to it by virtue of its status as an intergovernmental organisation nor
 * does it submit to any jurisdiction.
 */

/// @author Baudouin Raoult
/// @author Piotr Kuchta
/// @author Simon Smart
/// date April 2009
/// date January 2019

#ifndef eckit_sql_SchemaAnalyzer_H
#define eckit_sql_SchemaAnalyzer_H

#include "eckit/sql/SchemaComponents.h"
#include "eckit/sql/SQLTypedefs.h"


namespace eckit {
namespace sql {

//----------------------------------------------------------------------------------------------------------------------

class SchemaAnalyzer {

public: // methods

    SchemaAnalyzer();
    ~SchemaAnalyzer();

    void addTable(const std::string& name,
                  const ColumnDefs& columns,
                  const ConstraintDefs& constraints,
                  const std::vector<std::string>& parents,
                  const std::string& location);

    void addBitfieldType(const std::string& name, const FieldNames& fields, const Sizes& sizes, const std::string& typeSignature);
//    bool isBitfield(const std::string& columnName) const;
//    const BitfieldDef& getBitfieldTypeDefinition(const std::string& columnName);




//    bool tableKnown(const std::string& name) const;
//    const TableDef& findTable(const std::string& name) const;
//    void skipTable(std::string tableName);
//    std::string generateSELECT() const;
//    Definitions generateDefinitions();
//    std::string findColumnType(const std::string&);

private:
    BitfieldDefs bitfieldTypes_;
    //std::string currentSchema_;
    //SchemaDefs schemas_;
    //TableDefs tableDefs_;
    //BitfieldDefs bitfieldTypes_;
    //std::set<std::string> tablesToSkip_;
    //std::map<std::string,std::string> columnTypes_;

};

//----------------------------------------------------------------------------------------------------------------------

} // namespace sql
} // namespace eckit

#endif

