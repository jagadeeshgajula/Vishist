#ifndef CURRENCY_H
#define CURRENCY_H
#include "currency.h"
#include "calendarUtil.h"
#include "busDayConv.h"
#include "util.h"

//#include <list>
using namespace IRDConnect;

namespace IRDConnect {

//static std::list <  Currency * >	_currencyList;

using namespace std; // @suppress("Symbol is not resolved")

static std::list<Calendar *>  calendarList ; // @suppress("Type cannot be resolved")

//Calendar * CalendarUtil::getCalendar( const std::string & holidayCd )

const Currency *
Currency::eur = 0;


Currency::Currency(
const std::string 			name,
const String				defaultDiscountCurve,
const DayCountConv		* 	dcc,
const BusDayConv		* 	bdc,
const Calendar			* 	cal,
const Calendar        	* 	secondCal,
const String				mktType,
const String				timeSeries,
const RoundingConv		* 	roundingConv,
const String				defaultONInstrument,
const Frequency				defaultSwpFloatSettleFreq,
const Frequency				defaultSwpFixSettleFreq,
const DayCountConv		* 	defaultSwaFixDcc,
unsigned int				numDecimal,
int		        			valueDayLag,
const String				emuFlg,
double						euroConvRate,
const Date 					euroSettleEffDate,
const String                xccyBasisTsirId
) :
	 name_(name),
	_defaultDiscountCurve( defaultDiscountCurve),
    _xccyBasisTsirId ( xccyBasisTsirId ),
	_dcc( dcc ),
	_bdc( bdc ),
	_cal( cal ),
	_secondCal( secondCal ),
	_mktType( mktType ),
	_timeSeries( timeSeries ),
	_defaultONInstrument( defaultONInstrument ),
	_defaultSwpFloatSettleFreq( defaultSwpFloatSettleFreq ),
	_defaultSwpFixSettleFreq( defaultSwpFixSettleFreq ),
	_defaultSwaFixDcc( defaultSwaFixDcc ),
	_roundingConv( roundingConv ),
	_numDecimal( numDecimal ),
	_valueDayLag( valueDayLag ),
	_euroConvRate( euroConvRate ),
	_emuFlg( emuFlg ),
    _euroSettleEffDate (euroSettleEffDate )


{
	// do nothing here
}

Currency::~Currency()
{
// nothing to be done here
}

//----------------------------------------------------------------------

const String
Currency::getDefaultDiscountCurve() const
{
	return _defaultDiscountCurve;
}

const String
Currency::getXccyBasisTsirId() const
{
	return _xccyBasisTsirId;
}

const DayCountConv *
Currency::getDayCountConv() const
{
	return _dcc;
}

const BusDayConv *
Currency::getBusDayConv() const
{
	return _bdc;
}

const Calendar *
Currency::getCalendar() const
{
	return _cal;
}

const Calendar *
Currency::getSecondCalendar() const
{
    return _secondCal;
}

const String
Currency::getMktType() const
{
	return _mktType;
}

const String
Currency::getTimeSeries() const
{
	return _timeSeries;
}

const RoundingConv *
Currency::getRoundingConv() const
{
	return _roundingConv;
}

unsigned int
Currency::getNumDecimal() const
{
	return _numDecimal;
}

int
Currency::getValueDayLag() const
{
	return _valueDayLag;
}

double
Currency::getEuroConvRate() const
{
	return _euroConvRate;
}

const Date
Currency::getEuroSettleEffDate() const
{
	return _euroSettleEffDate;
}

const bool
Currency::isEuroSettleEffDateNull() const
{
	//if (_euroSettleEffDate.year() == Date::ERROR_YEAR &&
    //        _euroSettleEffDate.month() == Date::ERROR_MONTH &&
      //      _euroSettleEffDate.dayOfMonth() == Date::ERROR_DAY )
	if (_euroSettleEffDate.year() == 1901 &&
	    _euroSettleEffDate.month() == 01 &&
	    _euroSettleEffDate.dayOfMonth() == 01 )

		return true;
	return false;
}

const bool
Currency::isInEMU() const
{
	return ( _emuFlg == "Y" );
}

// added by nagesh for testing currency get

const std::string Currency::getCurrencyCode() const
{
	return name_;
}

const bool
Currency::isEur() const
{
	return ( "EUR" == name_);
			//getCurrencyCode();
}

const Currency *
Currency::find( unsigned int index )
{

	return (const Currency *)find();
}

const Currency *
Currency::find()
{

	return (const Currency *)find( );
}

const Currency *
Currency::find( const std::string & name )
{

	if ( _currencyList.empty() )
	{
		if ( ! Util::loadCurrencyList(_currencyList ) )
			cerr << "Problems in loading currencies " << endl;

	}

	if ( !_currencyList.empty()  )
	{
		std::list<Currency *>::const_iterator ccyIter = _currencyList.begin () ;

			for (; ccyIter != _currencyList.end() ; ++ccyIter)
	         {
	             if ( (*ccyIter)->getCurrencyCode () == name )
	                 return *ccyIter ;
	         }
	}

return 0; // make sure you check the return value at calling time
}

const Currency *
Currency::getEUR( )
{
	if (!eur)
		eur = find(std::string("EUR"));
	return eur;
}

//This method is no longer needed
void
Currency::init()
{

	if ( _currencyList.empty() )
		{
			if ( ! Util::loadCurrencyList(_currencyList ) )
				cerr << "Problems in loading currencies " << endl;

		}

}

std::istream &
operator >> ( std::istream & is, const Currency ** currency )
{
    std::string name_;

    is >>name_;

    *currency = Currency::find( name_ );

    return is;

}
}
#endif  // CURRENCY_H
