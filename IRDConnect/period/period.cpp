/*
 * Period.cpp
 *
 *  Created on: 28-Aug-2010
 *      Author: vishist
 */

#include "period.h"
#include "errors.h"
#include "types.h"

namespace IRDConnect {

    Period::Period(Frequency f) {
        switch (f) {
          case Once:
          case NoFrequency:
            // same as Period()
            units_ = Days;
            length_ = 0;
            break;
          case Annual:
            units_ = Years;
            length_ = 1;
            break;
          case Semiannual:
          case EveryFourthMonth:
          case Quarterly:
          case Bimonthly:
          case Monthly:
            units_ = Months;
            length_ = 12/f;
            break;
          case Biweekly:
          case Weekly:
            units_ = Weeks;
            length_ = 52/f;
            break;
          case Daily:
            units_ = Days;
            length_ = 1;
            break;
          default:
            QL_FAIL(("unknown frequency ") << Integer(f));
        }

    }


Period::Period(String period) {

	cout << "Period Passed is : " << period << endl;
if ( period == "1D")
{
              Period(1,Days);
}
else if ( period == "1W")
{
               Period(1,Weeks);
}
else if ( period == "1M")
{
          	 Period(1,Months);
}
else if ( period == "2M")
{
              Period(2,Months);
}
else if ( period == "3M")
{
    cout << "It came here " << endl;
        	  Period(3,Months);
}
else if ( period == "4M")
{
            	 Period(4,Months);
}
else if ( period == "5M")
{
            	 Period(5,Months);
}
else if ( period == "6M")
{
            	 Period(6,Months);
}
else if ( period == "7M")
{
	 	 	 	 Period(7,Months);
}
else if ( period == "8M")
{
            	 Period(8,Months);
}
else if ( period == "9M")
{
            	 Period(9,Months);
}
else if ( period == "10M")
{
            	 Period(10,Months);
}
else if ( period == "11M")
{
            	 Period(11,Months);
}
else if ( period == "12M")
{
            	 Period(12,Months);
}
else if ( period == "2W")
{
	 Period(2,Weeks);
}
else if ( period == "1Y")
{
            	 Period(1,Years);
}
else if ( period == "2Y")
{
            	 Period(2,Years);
}



}

    Frequency Period::frequency() const {
        // unsigned version
        Size length = std::abs(length_);

        if (length==0) return NoFrequency;

        switch (units_) {
          case Years:
            QL_REQUIRE(length==1,
                       "cannot instantiate a Frequency from " << *this);
            return Annual;
          case Months:
            QL_REQUIRE((12%length)==0 && length<=12,
                       "cannot instantiate a Frequency from " << *this);
            return Frequency(12/length);
          case Weeks:
            if (length==1)
                return Weekly;
            else if (length==2)
                return Biweekly;
            else
                QL_FAIL("cannot instantiate a Frequency from " << *this);
          case Days:
            QL_REQUIRE(length==1,
                       "cannot instantiate a Frequency from " << *this);
            return Daily;
          default:
            QL_FAIL("unknown time unit (" << Integer(units_) << ")");
        }
    }

    /*
    Tenor Period::tenor() const {
          // unsigned version
          Size length = std::abs(length_);

          if (length==0) return null;

          switch (units_) {
            case Years:
              QL_REQUIRE(length==1,
                         "cannot instantiate a Tenor from " << *this);
              return year;
            case Months:
            	if (length==1)
            	    return month;
            	 else if (length==2)
            	     return twoMonth;
            	 else if (length==3)
            	      return quarter;
            	 else if (length==6)
            	      return halfYear;
            	 else
            	       QL_FAIL("cannot instantiate a Tenor from " << *this);
            case Weeks:
              if (length==1)
                  return week;
              else if (length==2)
                  return twoWeek;
              else
                  QL_FAIL("cannot instantiate a Tenor from " << *this);
            case Days:
              QL_REQUIRE(length==1,
                         "cannot instantiate a Tenor from " << *this);
              return day;
            default:
              QL_FAIL("unknown time unit (" << Integer(units_) << ")");
          }
      }
      */


    void Period::normalize() {
            if (length_!=0)
                switch (units_) {
                  case Days:
                    if (!(length_%7)) {
                        length_/=7;
                        units_ = Weeks;
                    }
                    break;
                  case Months:
                    if (!(length_%12)) {
                        length_/=12;
                        units_ = Years;
                    }
                    break;
                  case Weeks:
                  case Years:
                    break;
                  default:
                    QL_FAIL("unknown time unit (" << Integer(units_) << ")");
                }
        }


    bool operator<(const Period& p1, const Period& p2) {
        if (p1.length()==0) return (p2.length()>0);
        if (p2.length()==0) return (p1.length()<0);

        switch (p1.units()) {
          case Days:
            switch (p2.units()) {
              case Days:
                return (p1.length() < p2.length());
              case Weeks:
                return (p1.length() < p2.length() * 7);
              case Months:
                if (p1.length() < p2.length() * 28)
                    return true;
                else
                    QL_FAIL("undecidable comparison between "
                             << p1 << " and " << p2);
              case Years:
                return (p1.length() < p2.length() * 365);
              default:
                QL_FAIL("unknown units");
            }
          case Weeks:
            switch (p2.units()) {
              case Days:
                return (p1.length() * 7 < p2.length());
              case Weeks:
                return (p1.length() < p2.length());
              case Months:
                if (p1.length() * 7 < p2.length() * 28)
                    return true;
                else
                    QL_FAIL("undecidable comparison between "
                             << p1 << " and " << p2);
              case Years:
                if (p1.length() * 7 < p2.length() * 365)
                    return true;
                else
                    QL_FAIL("undecidable comparison between "
                             << p1 << " and " << p2);
              default:
                QL_FAIL("unknown units");
            }
          case Months:
            switch (p2.units()) {
              case Days:
                // Sup[days in p1.length() months] < days in p2
                if (p1.length() * 31 < p2.length())
                    return true;
                // almost 28 days in p1 and less than 28 days in p2
                else if ((p1.length()!=0) && p2.length()< 28)
                    return false;
                else
                    QL_FAIL("undecidable comparison between "
                             << p1 << " and " << p2);
              case Weeks:
                if (p1.length()* 31 < p2.length()  * 7)
                    return true;
                else
                    QL_FAIL("undecidable comparison between "
                             << p1 << " and " << p2);
              case Months:
                return (p1.length() < p2.length());
              case Years:
                return (p1.length() < p2.length() * 12);
              default:
                QL_FAIL("unknown units");
            }
          case Years:
            switch (p2.units()) {
              case Days:
                if (p1.length() * 366 < p2.length())
                    return true;
                // almost 365 days in p1 and less than 365 days in p2
                else if ((p1.length()!=0) && p2.length()< 365)
                    return false;
                else
                    QL_FAIL("undecidable comparison between "
                             << p1 << " and " << p2);
              case Weeks:
                if (p1.length() * 366 < p2.length() * 7)
                    return true;
                else
                    QL_FAIL("undecidable comparison between "
                             << p1 << " and " << p2);
              case Months:
                return (p1.length() * 12 < p2.length());
              case Years:
                return (p1.length() < p2.length());
              default:
                QL_FAIL("unknown units");
            }
          default:
            QL_FAIL("unknown units");
        }
    }

Period& Period::operator+=(const Period& p) {

           if (length_== 0) {
               length_ = p.length();
               units_ = p.units();
           } else if (units_== p.units()) {
               // no conversion needed
               length_ += p.length();
           } else {
               switch (units_) {

                 case Years:
                   switch (p.units()) {
                     case Months:
                       units_ = Months;
                       length_ = length_*12 + p.length();
                       break;
                     case Weeks:
                     case Days:
                       QL_REQUIRE(p.length()==0,
                                  "impossible addition between " << *this <<
                                  " and " << p);
                       break;
                     default:
                       QL_FAIL("unknown time unit (" << Integer(p.units()) << ")");
                   }
                   break;

                 case Months:
                   switch (p.units()) {
                     case Years:
                       length_ += p.length()*12;
                       break;
                     case Weeks:
                     case Days:
                       QL_REQUIRE(p.length()==0,
                                  "impossible addition between " << *this <<
                                  " and " << p);
                       break;
                     default:
                       QL_FAIL("unknown time unit (" << Integer(p.units()) << ")");
                   }
                   break;

                 case Weeks:
                   switch (p.units()) {
                     case Days:
                       units_ = Days;
                       length_ = length_*7 + p.length();
                       break;
                     case Years:
                     case Months:
                       QL_REQUIRE(p.length()==0,
                                  "impossible addition between " << *this <<
                                  " and " << p);
                       break;
                     default:
                       QL_FAIL("unknown time unit (" << Integer(p.units()) << ")");
                   }
                   break;

                 case Days:
                   switch (p.units()) {
                     case Weeks:
                       length_ += p.length()*7;
                       break;
                     case Years:
                     case Months:
                       QL_REQUIRE(p.length()==0,
                                  "impossible addition between " << *this <<
                                  " and " << p);
                       break;
                     default:
                       QL_FAIL("unknown time unit (" << Integer(p.units()) << ")");
                   }
                   break;

                 default:
                   QL_FAIL("unknown time unit (" << Integer(units_) << ")");
               }
           }

           //this->normalize();
           return *this;
       }

       Period& Period::operator-=(const Period& p) {
           return operator+=(-p);
       }

       Period & Period::operator=(const Period & p) {
    	   length_ = p.length();
    	   units_  = p.units();
    	  return *this;
       }
       Period& Period::operator/=(Integer n) {
           QL_REQUIRE(n != 0, "cannot be divided by zero");
           if (length_ % n == 0) {
               // keep the original units. If the user created a
               // 24-months period, he'll probably want a 12-months one
               // when he halves it.
               length_ /= n;
           } else {
               // try
               TimeUnit units = units_;
               Integer length = length_;
               switch (units) {
                 case Years:
                   length *= 12;
                   units = Months;
                   break;
                 case Weeks:
                   length *= 7;
                   units = Days;
                   break;
                 default:
                   ;
               }
               QL_REQUIRE(length % n == 0,
                          *this << " cannot be divided by " << n);
               length_ = length/n;
               units_ = units;
               // if normalization were possible, we wouldn't be
               // here---the "if" branch would have been executed
               // instead.
               // result.normalize();
           }
           return *this;
       }


    // period formatting

    std::ostream& operator<<(std::ostream& out, const Period& p) {
        return out << IRDio::short_period(p);
    }

    namespace IRDdetail {

        std::ostream& operator<<(std::ostream& out,
                                 const long_period_holder& holder) {
            Integer n = holder.p.length();
            out << n << " ";
            switch (holder.p.units()) {
              case Days:
                return out << (n == 1 ? "day" : "days");
              case Weeks:
                return out << (n == 1 ? "week" : "weeks");
              case Months:
                return out << (n == 1 ? "month" : "months");
              case Years:
                return out << (n == 1 ? "year" : "years");
              default:
                QL_FAIL("unknown time unit");
            }
        }

        std::ostream& operator<<(std::ostream& out,
                                 const short_period_holder& holder) {
            Integer n = holder.p.length();
            out << n;
            switch (holder.p.units()) {
              case Days:
                return out << "D";
              case Weeks:
                return out << "W";
              case Months:
                return out << "M";
              case Years:
                return out << "Y";
              default:
                QL_FAIL("unknown time unit");
            }
        }

    }

    namespace IRDio {

        IRDdetail::long_period_holder long_period(const Period& p) {
            return IRDdetail::long_period_holder(p);
        }

        IRDdetail::short_period_holder short_period(const Period& p) {
            return IRDdetail::short_period_holder(p);
        }

    }

}

