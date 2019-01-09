#include "calendar.h" 

namespace IRDConnect {


bool Calendar::isBusDay (const Date & d ) const
{
   //  std::cout << d << std::endl ; 
     return true ; 
} 

bool
Calendar::isBusDay( const Date & d, const Calendar & secCalendar ) const
{
   return ( isBusDay ( d ) && secCalendar.isBusDay ( d ) )   ;
}


Calendar::Calendar()
{

}

Calendar::~Calendar()
{
}

//----------------------------------------------------------------------

Date
Calendar::nextBusDay( const Date & d ) const
{
    return addBusDay( d, 1 );
}

Date
Calendar::nextBusDay( const Date & d, const Calendar& secondCalendar ) const
{
    return addBusDay( d, 1, secondCalendar );
}

Date
Calendar::prevBusDay( const Date & d ) const
{
    return addBusDay( d, -1 );
}

Date
Calendar::prevBusDay( const Date & d, const Calendar& secondCalendar ) const
{
    return addBusDay( d, -1, secondCalendar );
}

Date
Calendar::addBusDay( const Date & d, int numBusDay ) const
{
    Date rv = d;
    addBusDayToDate( rv, numBusDay );
    return rv;
}

Date
Calendar::addBusDay( const Date & d, int numBusDay, 
        const Calendar& secondCalendar ) const
{
    Date rv = d;
    addBusDayToDate( rv, numBusDay, secondCalendar );
    return rv;
}

void
Calendar::setToNextBusDay( Date & d ) const
{
    addBusDayToDate( d, 1 );
}

void
Calendar::setToPrevBusDay( Date & d ) const
{
    addBusDayToDate( d, -1 );
}

void
Calendar::addBusDayToDate( Date & d, int numBusDay ) const
{   

	    const int inc = numBusDay < 0 ? 1 : -1;
	    long int julian = d.serialNumber();
	    for ( ; numBusDay; numBusDay += inc )
	        do {
	            julian -= inc;
	        } while ( !isBusDay( Date(julian ) ) );

	    const int equivCalDays = julian - d.serialNumber();
	    d +=  equivCalDays ;
}

void
Calendar::addBusDayToDate( Date & d, int numBusDay,
                    const Calendar & secondCalendar ) const
{

	    const int inc = numBusDay < 0 ? 1 : -1;

	    long int julian = d.serialNumber();
	    for ( ; numBusDay; numBusDay += inc )
	        do {
	            julian -= inc;
	        } while ( !(isBusDay(Date(julian), secondCalendar)));

	    const int equivCalDays = julian - d.serialNumber();
	    d += equivCalDays;
}

int
Calendar::busDayDiff( const Date & d1, const Date & d2 ) const
{
    
	Date start = d1 < d2 ? d1 : d2;
	    const Date & end  = d1 < d2 ? d2 : d1;

	    int diffDays = 0;
	    for ( ; start < end; ++start )
	        if ( isBusDay( start ) )
	            ++diffDays;

	    return d1 < d2 ? diffDays : -diffDays;

}
}
