/*
 * (C) Copyright 1996-2013 ECMWF.
 * 
 * This software is licensed under the terms of the Apache Licence Version 2.0
 * which can be obtained at http://www.apache.org/licenses/LICENSE-2.0. 
 * In applying this licence, ECMWF does not waive the privileges and immunities 
 * granted to it by virtue of its status as an intergovernmental organisation nor
 * does it submit to any jurisdiction.
 */

/// @author Piotr Kuchta - ECMWF March 2015

#ifndef Cell_H
#define Cell_H

#include <string>
#include <list>
#include <vector>
#include <map>
#include <ostream>

namespace eckit {

class Cell {
public:
    Cell(const std::string&, const std::string&, Cell*, Cell*);

    static Cell* clone(Cell*);

    const std::string& tag() const;
    const std::string& text() const;
    Cell* value() const;
    Cell* rest() const;

    Cell* tag(const std::string&);
    Cell* text(const std::string&);
    Cell* value(Cell*);
    Cell* rest(Cell*);

    Cell* append(Cell*);

    // Set value pointed by a keyword
    Cell* value(const std::string& keyword, Cell* value); 
    Cell* value(const std::string& keyword, const std::string& value); 

    // Get value pointed by a keyword
    Cell* valueOrDefault(const std::string& keyword, Cell* defaultValue) const;
    std::string valueAsString(const std::string& keyword, const std::string& defaultValue) const;

    std::ostream& dot(std::ostream&, const std::string&, bool, bool) const;

    std::string str() const;

    void showGraph(bool background, bool detailed, bool clever);
    void showGraph(const std::string&, bool background, bool detailed, bool clever);
    void graph();
    void simpleGraph();

private:
    Cell(Cell*); // cloning

    std::string text_;
    std::string tag_;
    Cell *value_;
    Cell *rest_;

    std::ostream& print(std::ostream&, size_t depth=0) const;
    std::ostream& printAttributes(std::ostream&, size_t depth=0) const;
    std::ostream& printValues(std::ostream&, size_t depth=0) const;

    std::ostream& printDot(std::ostream&, bool, bool) const;
    std::ostream& printDotList(std::ostream&, bool) const;
    std::ostream& printDotVerb(std::ostream&, bool) const;

    friend std::ostream& operator<< (std::ostream& s, const Cell *r) { return r->print(s); }
};

} // namespace eckit

#endif