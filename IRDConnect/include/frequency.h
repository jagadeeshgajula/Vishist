/*
 * frequency.h
 *
 *  Created on: 02-Sep-2010
 *      Author: vishist
 */

#ifndef IRDFREQUENCY_H_
#define IRDFREQUENCY_H_
#include <iostream>

using namespace std;
//using namespace IRDConnect;

namespace IRDConnect {

enum Frequency { NoFrequency = -1,     //!< null frequency
                     Once = 0,             //!< only once, e.g., a zero-coupon
                     Annual = 1,           //!< once a year
                     Semiannual = 2,       //!< twice a year
                     EveryFourthMonth = 3, //!< every fourth month
                     Quarterly = 4,        //!< every third month
                     Bimonthly = 6,        //!< every second month
                     Monthly = 12,         //!< once a month
                     Biweekly = 26,        //!< every second week
                     Weekly = 52,          //!< once a week
                     Daily = 365           //!< once a day
    };

    /*! \relates Frequency */
    std::ostream& operator<<(std::ostream& out, Frequency f);

}

#endif /* IRDFREQUENCY_H_ */
