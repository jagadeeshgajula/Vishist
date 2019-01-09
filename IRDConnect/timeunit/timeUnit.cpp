/*
 * TimeUnit.cpp
 *
 *  Created on: 05-Sep-2010
 *      Author: vishist
 */
#include "timeUnit.h"
#include "types.h"
#include "errors.h"

using namespace IRDConnect;

 std::ostream& operator<<(std::ostream& out, const TimeUnit& timeunit) {
        switch (timeunit) {
            case Years:
                return out << "Years";
            case Months:
                return out << "Months";
            case Weeks:
                return out << "Weeks";
            case Days:
                return out << "Days";
            default:
                QL_FAIL("unknown TimeUnit");
        }
    }

