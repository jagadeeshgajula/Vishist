/*
 * Frequency.cpp
 *
 *  Created on: 02-Sep-2010
 *      Author: vishist
 */

#include "frequency.h"
#include "types.h"
#include "errors.h"

namespace IRDConnect {


    std::ostream& operator<<(std::ostream& out, Frequency f) {
        switch (f) {
          case NoFrequency:
            return out << "no-frequency";
          case Once:
            return out << "once";
          case Annual:
            return out << "annual";
          case Semiannual:
            return out << "semiannual";
          case EveryFourthMonth:
            return out << "every-fourth-month";
          case Quarterly:
            return out << "quarterly";
          case Bimonthly:
            return out << "bimonthly";
          case Monthly:
            return out << "monthly";
          case Biweekly:
            return out << "biweekly";
          case Weekly:
            return out << "weekly";
          case Daily:
            return out << "daily";
          default:
            QL_FAIL("unknown frequency (" << Integer(f) << ")");
        }
    }

}
