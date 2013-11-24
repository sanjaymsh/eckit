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

//#include "eckit/maths/BinaryFunc.h"
//#include "eckit/maths/BinaryPredicate.h"
//#include "eckit/maths/Count.h"
//#include "eckit/maths/Expr.h"
//#include "eckit/maths/FMap.h"
//#include "eckit/maths/Filter.h"
//#include "eckit/maths/Reduce.h"
//#include "eckit/maths/List.h"
//#include "eckit/maths/Scalar.h"
//#include "eckit/maths/UnaryFunc.h"
//#include "eckit/maths/Vector.h"
//#include "eckit/maths/ZipWith.h"
//#include "eckit/maths/Bind.h"
#include "eckit/maths/IfElse.h"
#include "eckit/maths/Lambda.h"
//#include "eckit/maths/Param.h"
#include "eckit/maths/ParamDef.h"
#include "eckit/maths/Call.h"

#include "eckit/maths/Math.h"

using namespace eckit;
using namespace eckit::maths;

using namespace eckit;

//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------

class YCombinator : public Tool {
public:

    YCombinator(int argc,char **argv): Tool(argc,argv) {
    }

    ~YCombinator() {
    }

    virtual void run();
};

//-----------------------------------------------------------------------------

void YCombinator::run()
{


    Math a( 2. );
    Math b( 4. );
    Math c( 7. );
    Math z( 0. );

    if(0)
    {
        Math g = a > z;
        cout << g << endl;

        cout << g() << endl;
    }

    Math e = maths::lambda("1", "2",
                           ifelse(Math("1") > Math("2"), b, c));

    cout << e << endl;

    e = maths::call(e);
    cout << e(a, z) << endl;

    if(1)
    {
        Math s = Math("a") - Math("b");
        Math f = maths::lambda("a", "b", s);
        Math c = Math(maths::call(f))( Math(1.0), Math(3.0));
        cout << c << endl;
        cout << c() << endl;
    }

    if(1)
    {
        Math s = Math("n") - Math(1.0);
        Math r = Math(maths::call(Math("recurse")))(Math("recurse"), s);
        Math e = Math("n") == Math(0.0);
        Math i = maths::ifelse(e, Math(1.0),  r * Math("n"));

        Math X = maths::lambda("recurse", "n", i);

        Math Y = maths::lambda("builder", "x",
                               Math(maths::call(Math("builder")))(Math("builder"), Math("x")
                                                                  ));
        cout << X << endl;
        cout << Y << endl;

        Y = maths::call(Y);
        cout << Y(X, Math(0.0)) << endl;
    }


}

//-----------------------------------------------------------------------------

int main(int argc,char **argv)
{
    YCombinator app(argc,argv);
    app.start();
    return 0;
}
