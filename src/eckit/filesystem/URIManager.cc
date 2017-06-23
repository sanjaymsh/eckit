/*
 * (C) Copyright 1996-2017 ECMWF.
 *
 * This software is licensed under the terms of the Apache Licence Version 2.0
 * which can be obtained at http://www.apache.org/licenses/LICENSE-2.0.
 * In applying this licence, ECMWF does not waive the privileges and immunities
 * granted to it by virtue of its status as an intergovernmental organisation nor
 * does it submit to any jurisdiction.
 */

#include "eckit/filesystem/URI.h"
#include "eckit/filesystem/URIManager.h"
#include "eckit/thread/AutoLock.h"
#include "eckit/thread/StaticMutex.h"
#include "eckit/filesystem/PathName.h"
#include "eckit/filesystem/PathName.h"


namespace eckit {

//----------------------------------------------------------------------------------------------------------------------

typedef std::map<std::string, URIManager*> FileManagerMap;

// Builds the map on demand, needed for correct static initialization because factories can be initialized first
struct FileManagerRegistry {

    static FileManagerRegistry& instance() {
        static FileManagerRegistry reg;
        return reg;
    }

    FileManagerMap map_;

    FileManagerMap& map() { return map_; }
};


static StaticMutex local_mutex;

//----------------------------------------------------------------------------------------------------------------------

URIManager::URIManager(const std::string& name):
        name_(name)
{
    
    AutoLock<StaticMutex> lock(local_mutex);
    FileManagerMap& m = FileManagerRegistry::instance().map();

    ASSERT(m.find(name) == m.end());
    m[name] = this;
}

URIManager::~URIManager()
{
    AutoLock<StaticMutex> lock(local_mutex);
    FileManagerMap& m = FileManagerRegistry::instance().map();

    m.erase(name_);
}

URIManager& URIManager::lookUp(const std::string& name)
{
 
    AutoLock<StaticMutex> lock(local_mutex);
    FileManagerMap& m = FileManagerRegistry::instance().map();

    std::map<std::string, URIManager*>::const_iterator j = m.find(name);
    
    Log::info() << "Looking for URIManager [" << name << "]" << std::endl;

    if (j == m.end())
    {
	Log::error() << "No URIManager for [" << name << "]" << std::endl;
	Log::error() << "Managers are:" << std::endl;
	for(j = m.begin() ; j != m.end() ; ++j)
	  Log::error() << "   " << *((*j).second) << std::endl;
        throw SeriousBug(std::string("No URIManager called ") + name);
    }

    return *((*j).second);
}


void URIManager::print(std::ostream& s) const
{
    s << "URIManager[" << name_ << "]";
}

//----------------------------------------------------------------------------------------------------------------------


class LocalFileManager : public URIManager {
      
    virtual bool exists(const URI& f) {
        return PathName(f.name()).exists();
    }
    
    virtual DataHandle*  newWriteHandle(const URI& f) {
        return PathName(f.name()).fileHandle();
    }
    
    virtual DataHandle*  newReadHandle(const URI& f) {
        return PathName(f.name()).fileHandle();
    }
    
    virtual DataHandle*  newReadHandle(const URI& f,const OffsetList& ol, const LengthList& ll) {
        return PathName(f.name()).partHandle(ol,ll);
    }

public:
    LocalFileManager(const std::string& name) : URIManager(name) {}
};



class MarsFSFileManager : public URIManager {
  
    virtual bool exists(const URI& f) {
        return PathName(f.scheme() + ":" + f.name()).exists();
    }
    
    virtual DataHandle*  newWriteHandle(const URI& f) {
        return PathName(f.scheme() + ":" + f.name()).fileHandle();
    }
    
    virtual DataHandle*  newReadHandle(const URI& f) {
        return PathName(f.scheme() + ":" + f.name()).fileHandle();
    }
    
    virtual DataHandle*  newReadHandle(const URI& f,const OffsetList& ol, const LengthList& ll) {
        return PathName(f.scheme() + ":" + f.name()).partHandle(ol,ll);
    }

public:
    MarsFSFileManager(const std::string& name) : URIManager(name) {}
};


static LocalFileManager  manager_unix("unix");
static LocalFileManager  manager_file("file");
static MarsFSFileManager manager_marsfs("marsfs");

//----------------------------------------------------------------------------------------------------------------------

} // namespace eckit