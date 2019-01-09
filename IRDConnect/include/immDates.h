/*
 * immDates.h
 *
 *  Created on: 18-Sep-2010
 *      Author: vishist
 */

#ifndef IRDIMMDATES_H_
#define IRDIMMDATES_H_
#include "busDayConv.h"
#include "currency.h"

using namespace std;
using namespace IRDConnect;

namespace IRDConnect {


Date nthWeekday( Year year, Month month, int dayOfWeek, int occurence );

Date    thirdIMMDay( Year year,
                     Month month,
                     const Currency * ccy = 0 );

int     isIMMDate( const Date           & date,
                   const BusDayConv   * bdc = 0,
                   const Calendar       * cal = 0,
                   const Currency       * ccy = 0 );

// Returns the next IMM date after 'date' i.e. if 'date' is an IMM day
// it returns a date 3 months after 'date'.

Date    nextIMMDate( const Date         & date,
                     const BusDayConv   * bdc = 0 ,
                     const Calendar     * cal = 0,
                     const Currency     * ccy = 0 );

// Returns the previous IMM date before 'date' i.e. if 'date' is an IMM day
// it returns a date 3 months before 'date'.

Date    prevIMMDate( const Date         & date,
                     const BusDayConv   * bdc = 0,
                     const Calendar     * cal = 0,
                     const Currency     * ccy = 0);

}
#endif /* IRDIMMDATES_H_ */