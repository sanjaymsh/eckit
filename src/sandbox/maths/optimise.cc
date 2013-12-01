/*
 * (C) Copyright 1996-2012 ECMWF.
 *
 * This software is licensed under the terms of the Apache Licence Version 2.0
 * which can be obtained at http://www.apache.org/licenses/LICENSE-2.0.
 * In applying this licence, ECMWF does not waive the privileges and immunities
 * granted to it by virtue of its status as an intergovernmental organisation nor
 * does it submit to any jurisdiction.
 */

#include "eckit/log/Log.h"
#include "eckit/runtime/Tool.h"

#include "eckit/maths/IfElse.h"
#include "eckit/maths/Lambda.h"
#include "eckit/maths/ParamDef.h"
#include "eckit/maths/Call.h"
#include "eckit/maths/Bind.h"

#include "eckit/maths/Math.h"
#include "eckit/maths/Scalar.h"
#include "eckit/maths/Vector.h"
#include "eckit/maths/List.h"
#include "eckit/maths/BinaryOperator.h"
#include "eckit/maths/Count.h"
#include "eckit/maths/Merge.h"

using namespace std;

using namespace eckit;
using namespace eckit::maths;

//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------

class Quicksort : public Tool {
public:

    Quicksort(int argc,char **argv): Tool(argc,argv) {
    }

    ~Quicksort() {
    }

    virtual void run();
};

//-----------------------------------------------------------------------------

void Quicksort::run()
{

    setformat(cout,maths::CodeFormat);

    Math a = maths::scalar( 2. );
    Math b = maths::scalar( 4. );
    Math x = maths::vector( 3, 5. );
    Math y = maths::vector( 3, 7. );

    if(false)
    {
        std::cout << std::endl << "************************" << std::endl;
        Math X = maths::list( maths::add(a,b), maths::add(x,y));

        std::cout << "-----------------------" << std::endl;
        std::cout << X.optimise()              << std::endl;
        std::cout << "-----------------------" << std::endl;
    }

    if(false)
    {
        std::cout << std::endl << "************************" << std::endl;
        Math e = a+b;
        Math z = (a-b) * e;
        Math X = maths::add( maths::prod(e,x), maths::prod(z,y));

        std::cout << "-----------------------" << std::endl;
        std::cout << X.optimise()              << std::endl;
        std::cout << "-----------------------" << std::endl;
    }

    if(true)
    {
        std::cout << std::endl << "************************" << std::endl;
        Math e = maths::count(
                    maths::merge(
                        maths::list(a,a,a,a,a,a,a),
                               maths::list(b,b,b))
                                 );
        Math X = maths::add( maths::prod(e,x), maths::prod(b,y));

        std::cout << "-----------------------" << std::endl;
        std::cout << X.optimise()              << std::endl;
        std::cout << "-----------------------" << std::endl;
    }

}

//-----------------------------------------------------------------------------

int main(int argc,char **argv)
{
    Quicksort app(argc,argv);
    app.start();
    return 0;
}
