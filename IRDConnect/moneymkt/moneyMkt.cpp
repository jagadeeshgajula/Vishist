/*
 * moneyMkt.cpp
 *
 *  Created on: 27-Dec-2010
 *      Author: vishist
 */

#include "moneyMkt.h"
#include <assert.h>
# include <iostream>
#include <map>
#include "frequency.h"
#include "instrumentClassCd.h"
#include "timeUnit.h"
#include "dayCountConv.h"
#include "util.h"

#include <math.h>
typedef int RetCode;

using namespace std;


namespace IRDConnect {

//static std::list <  MoneyMkt * >	_moneyMktList;

//
// The MoneyMkt class member function implementation
//

// --- Constructors and Destructor ---
MoneyMktMaster::MoneyMktMaster(
		const String &     	 	mmMasterId, // instrumentId
		const Currency *     	ccy,
		const BusDayConv *   	bdc,
		const DayCountConv * 	dcc,
		const Calendar *     	calendar,
		String				 	fwdCurve,
		String				 	marketType, // euro-dollar/repo/prime rate etc
		String				 	quoteType,
		String				 	description
			)
			:
			_mmMasterId(mmMasterId),
	    	_ccy(ccy),
	    	_bdc(bdc),
	    	_dcc(dcc),
	    	_calendar(calendar),
	    	_fwdCurve(fwdCurve),
	    	_marketType(marketType),
	    	_quoteType(quoteType),
	    	_description(description)


{
}

MoneyMkt::MoneyMkt(
				String		 		 	quoteId, // need this for grouping
		        int                  	settlementDateOffset,
		        const Period     &   	maturityDateOffset, //like 3M or 6M instruments
		        String				 	marketSource, // Bloomberg/Reuters/telerate etc
		        Frequency			 	compFreq,
		        Frequency			 	payFreq,
		        String				 	quoteDescription,// details of the instrument
		        String 			     	srcPage,  // where this rate available
		        double				 	precision,
		        double                  rate,
			    const String &     	 	mmMasterId, // instrumentId
			    const Currency *     	ccy,
			    const BusDayConv *   	bdc,
			    const DayCountConv * 	dcc,
			    const Calendar *     	calendar,
			    String				 	fwdCurve,
			    String				 	marketType, // euro-dollar/repo/prime rate etc
			    String				 	quoteType,
			    String				 	description )// details of master)
				: 	MoneyMktMaster
				      ( mmMasterId,
				    	ccy,
				    	bdc,
				    	dcc,
				    	calendar,
				    	fwdCurve,
				    	marketType,
				    	quoteType,
				    	description)
{


				   	_quoteId = quoteId;
			    	_settlementDateOffset = settlementDateOffset;
			    	_maturityDateOffset = maturityDateOffset;
			    	_marketSource = marketSource;
			    	_compFreq = compFreq;
			    	_payFreq = payFreq;
			    	_quoteDescription = quoteDescription;
			    	_srcPage = srcPage;
			    	_precision = precision;
			    	_rate = rate;

}


MoneyMktMaster::~MoneyMktMaster()
{

}

MoneyMkt::~MoneyMkt()
{

}

MoneyMktMaster::MoneyMktMaster( const MoneyMktMaster & mm )
      :
		_mmMasterId	(mm.getMMMasterId()),
		 _ccy			(mm.getCurrency()),
		 _bdc			(mm.getBusDayConv()),
		 _dcc			(mm.getDayCountConv()),
		 _calendar		(mm.getCalendar()),
		 _fwdCurve		(mm.getFwdCurve()),
		 _marketType	(mm.getMarketType()),
		 _quoteType		(mm.getQuoteType()),
		 _description	(mm.getDescription())

{
  //  _maturityDateOffset = Tenor( mm._maturityDateOffset.getAmount(),
  //                               mm._maturityDateOffset.getPeriod(),
  //                               &_calendar );
}


MoneyMkt::MoneyMkt( const MoneyMkt & mm )
		: MoneyMktMaster(
				mm.getMMMasterId(),
				mm.getCurrency(),
				mm.getBusDayConv(),
				mm.getDayCountConv(),
				mm.getCalendar(),
				mm.getFwdCurve(),
				mm.getMarketType(),
				mm.getQuoteType(),
				mm.getDescription())


{

	_quoteId							= mm.getQuoteId();
	_settlementDateOffset				= mm.getSettlementDateOffset();
	_maturityDateOffset					= mm.getMaturityDateOffset();
	_marketSource						= mm.getMarketSource();
	_compFreq							= mm.getCompFreq();
	_payFreq							= mm.getPayFreq();
	_quoteDescription					= mm.getQuoteDescription();
	_srcPage							= mm.getSrcPage();
	_precision							= mm.getPrecision();
	_rate								= mm.getRate();
}

MoneyMktMaster & MoneyMktMaster::operator= ( const MoneyMktMaster & mm )
{
    if ( this == &mm )
       return *this;

	 _mmMasterId	= mm.getMMMasterId();
	 _ccy			= mm.getCurrency();
	 _bdc			=mm.getBusDayConv();
	 _dcc			=mm.getDayCountConv();
	 _calendar		=mm.getCalendar();
	 _fwdCurve		=mm.getFwdCurve();
	 _marketType	=mm.getMarketType();
	 _quoteType		=mm.getQuoteType();
	 _description	=mm.getDescription();

    return *this;
}

MoneyMkt & MoneyMkt::operator= ( const MoneyMkt & mm )
{
    if ( this == &mm )
       return *this;

    		_mmMasterId 		= mm.getMMMasterId();
            _ccy 				= mm.getCurrency();
            _bdc 				= mm.getBusDayConv();
            _dcc 				= mm.getDayCountConv();
            _calendar			= mm.getCalendar();
            _fwdCurve 			= mm.getFwdCurve();
            _marketType 		= mm.getMarketType();
            _quoteType 			= mm.getQuoteType();
            _description 		= mm.getDescription();

            _quoteId   				=	mm.getQuoteId();
            _settlementDateOffset 	=	mm.getSettlementDateOffset();
            _maturityDateOffset		=	mm.getMaturityDateOffset();
            _marketSource			=	mm.getMarketSource();
            _compFreq				=	mm.getCompFreq();
            _payFreq				=	mm.getPayFreq();
            _quoteDescription		=	mm.getQuoteDescription();
            _srcPage				=	mm.getSrcPage();
            _precision				=	mm.getPrecision();
            _rate					=	mm.getRate();

    return *this;
}

/*
const shared_ptr < MoneyMktMaster >
MoneyMktMaster::find( const String name )
{
    MoneyMktMasterList::const_iterator itMM = getMoneyMktMasterList().begin() ;

    for ( ; itMM != getMoneyMktMasterList().end() ; ++itMM )
    {
    	if ( (*itMM)->getMMMasterId() == name )
    	return *itMM;
    }

}


const shared_ptr < MoneyMkt >
MoneyMkt::find( const String name )
{
    MoneyMktList::const_iterator itMM = getMoneyMktList().begin() ;

    for ( ; itMM != getMoneyMktList().end() ; ++itMM )
    {
    	if ( (*itMM)->getQuoteId() == name )
    	return *itMM;
    }

}

*/

const MoneyMkt *
MoneyMkt::find( const String name )
{
	if ( _moneyMktList.empty() )
		{
			if ( ! Util::loadMoneyMktList(_moneyMktList) )
				cerr << "Problems in loading Money Mkt List " << endl;

		}
	std::list < MoneyMkt * > ::const_iterator mktIter = _moneyMktList.begin () ;
		         for (; mktIter != _moneyMktList.end() ; ++mktIter)
		         {
		             if ( (*mktIter)->getQuoteId() == name )
		                 return *mktIter ;
		         }

	return NULL;
}


String
MoneyMkt::find( String mmMasterId, const Period maturityDateOffset, String srcPage )
{
	if ( _moneyMktList.empty() )
		{
			if ( ! Util::loadMoneyMktList(_moneyMktList) )
				cerr << "Problems in loading Money Mkt List " << endl;

		}
	std::list < MoneyMkt * > ::const_iterator mktIter = _moneyMktList.begin () ;
		         for (; mktIter != _moneyMktList.end() ; ++mktIter)
		         {
		             if ( (*mktIter)->getMMMasterId() == mmMasterId &&
		            		 (*mktIter)->getMaturityDateOffset()  == maturityDateOffset &&
		            		 (*mktIter)->getSrcPage() == srcPage )
		                 return (*mktIter)->getQuoteId() ;
		         }

	return NULL;
}
/*
std::map<std::string, const MoneyMkt *> & MoneyMkt::getMoneyMktMap ( )

{
     static BdcMap bdcMap ;
     static bool inited = false ;
     if ( !inited ) {
         bdcMap.insert ( BdcMap::value_type("NONE",new None )) ;
         bdcMap.insert ( BdcMap::value_type("FOL",new Following )) ;
         bdcMap.insert ( BdcMap::value_type("MOD",new ModifiedFollowing )) ;
         bdcMap.insert ( BdcMap::value_type("PRE",new Preceding )) ;
         inited = true ;
     }
     return bdcMap ;
}
*/
// --- Accessor Methods ---
// defined as inline in moneymkt.h
/*
Period
MoneyMkt::getValueDayLag() const
{
   return Period( _settlementDateOffset, Days) ;
   // return Tenor ( _settlementDateOffset,
   //                Period::busdays,
   //                &_calendar );
}
*/

/*void
MoneyMkt::setCompFreq( const Frequency * f )
{

   double               value = _rate.getRate();
// const Frequency    * freq  = _rate.getCompFreq();
   const YieldType    * yield = _rate.getYieldType();
   const DayCountConv * dcc   = _rate.getDayCountConv();

   _rate = Rate( value, f, yield, dcc );

   return;
}
*/

/*
void
MoneyMkt::setYieldType( const YieldType * y )
{

   double               value = _rate.getRate();
   const Frequency    * freq  = _rate.getCompFreq();
// const YieldType    * yield = _rate.getYieldType();
   const DayCountConv * dcc   = _rate.getDayCountConv();

   _rate = Rate( value, freq, y, dcc );

   return;
}


void
MoneyMkt::setDayCountConv( const DayCountConv * d )
{

   double               value = _rate.getRate();
   const Frequency    * freq  = _rate.getCompFreq();
 //  const YieldType    * yield = _rate.getYieldType();
 const DayCountConv * dcc   = _rate.getDayCountConv();

  // _rate = Rate( value, freq, yield, d );

   return;
}


void
MoneyMkt::setRateValue( const double v )
{

// double               value = _rate.getRate();
   const Frequency    * freq  = _rate.getCompFreq();
//   const YieldType    * yield = _rate.getYieldType();
   const DayCountConv * dcc   = _rate.getDayCountConv();

 //  _rate = Rate( v, freq, yield, dcc );

   return;
}
*/

Date
MoneyMkt::getSettlementDate( const Date & d ) const
{

    Date settleDate( d );
    _calendar->addBusDayToDate( settleDate, _settlementDateOffset );

    return settleDate;
}

Date
MoneyMkt::getQuoteDate( const Date & settleDate ) const
{

    Date quoteDate( settleDate );
    _calendar->addBusDayToDate( quoteDate, -1 * _settlementDateOffset );

    return quoteDate;
}


Date
MoneyMkt::getMaturityDate( const Date & d ) const
{

	Date matureDate ;
    if ( _maturityDateOffset.units () == Days )
    	matureDate = _calendar->addBusDay ( d, _maturityDateOffset.length () ) ;
    else
        matureDate = getSettlementDate(d) + _maturityDateOffset;

    if ( _bdc )
    {
    	   matureDate =  _bdc->adjustToBusDay( matureDate, *_calendar ) ;
    }

    return matureDate;
}

// --- Analytic Functions ---


double
MoneyMkt::getFwdAmount( const Date & d, const double & quote ) const
{
   double result = 0.0;

   Date settleDate = getSettlementDate( d );
   Date matureDate = getMaturityDate ( d ) ;
/*   Date matureDate = settleDate + getMaturityDateOffset();
   if ( _bdc )
      matureDate = ( _bdc->adjustToBusDay( matureDate, *_calendar ) );
*/

   double dcf = _dcc -> getFraction( settleDate, matureDate) ;
   cout << settleDate <<"," << matureDate << "RATE = " << _rate << "DCF = " << dcf << endl ;

   if ( _compFreq > 0 and _compFreq <= 365 )
	   result =  pow( 1 + _rate / _compFreq, _compFreq * dcf ) ;
   else
       result = ( 1 + _rate * dcf ) ;

   return result;
}



bool
MoneyMkt::validateQuote(double quote) const
{
   //return (bool) (_isSpread ? true : (quote > 0.0));
   return (bool) true;
}

/*void
MoneyMkt::getProjectDates(const Date & quoteDate, Date & effDate,
            Date & matDate) const
{
   effDate = getSettlementDate(quoteDate);
   matDate = getMaturityDate(quoteDate);
}
*/

}
