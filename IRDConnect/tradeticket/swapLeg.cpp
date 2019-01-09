/*
 * swapLegs.cpp
 *
 *  Created on: 17-Aug-2010
 *      Author: vishist
 */
#include <string>
#include <fstream>
#include "swapLeg.h"
#include "paySchedule.h"
#include "resetSchedule.h"
#include "compSchedule.h"
#include "rollDayConv.h"
#include "calendarUtil.h"
#include "marchingConv.h"
#include "fixingRates.h"
#include "stubResets.h"
#include <set>
#include <list>
#include <boost/lexical_cast.hpp>
#include <math.h>

#include "irdXML.h"
#include "util.h"

using namespace std;
using namespace IRDConnect;
using namespace IRDdetail;


namespace IRDConnect {


SwapLeg::SwapLeg()
{
	// do nothing...
}

SwapLeg::~SwapLeg()
{
	// do nothing...
}

SwapLeg::SwapLeg(
const BusDayConv * 			accrualBusDay,
std::set < std::string > 	accrualCalendars,
Frequency 					accrualFreq,
const DateMarcher * 		accrualMarching,
int 						accrualRollDay,
DayOfWeek 					accrualRollWeek,
int 						amortRollDay,
DayOfWeek 					amortRollWeek,
double 						amortAmount,
const BusDayConv * 			amortBusDay,
std::set < std::string > 	amortCalendars,
Date 						amortEndDate,
Frequency 					amortFreq,
const DateMarcher * 		amortMarching,
Date 						amortStartDate,
String 						amortType,
String 						averagingMethod,
Date 						backStubDate,
double 						backStubManualRate,
Frequency 					compFreq,
String 						compoundingConv,
const Currency * 			currency,
DayCountConv * 				dayCount,
String 						discountCurve,
Date 						endDate,
String 						endDateRollFlag,
String 						endOfMonthIndicator,
double 						fixedQuote,
Date 						frontStubDate,
double 						frontStubManualRate,
double 						gearFactor,
std::set < std::string > 	initialQuoteCalendars,
Date 						initialQuoteDate,
int 						initialQuoteLag,
int 						legNo,
String 						legType,
String 						marketIndex,
double 						notional,
String 						notionalExchange,
const BusDayConv * 			payBusDay,
std::set < std::string > 	payCalendars,
Frequency 					payFreq,
const DateMarcher * 		payMarching,
String 						paymentConvention,
const Currency * 			paymentConversionCurrency,
String 						paymentConversionIndex,
int 						paymentConversionLag,
int							payLag,
int 						payRollDay,
DayOfWeek 					payRollWeek,
String 						position,
int							precision,
std::set < std::string > 	quoteCalendars,
int 						quoteLag,
int 						rateCutOff,
String 						resetAveraging,
const BusDayConv * 			resetBusDay,
String 						resetConvention,
Frequency 					resetFreq,
const DateMarcher * 		resetMarching,
int 						resetRollDay,
DayOfWeek 					resetRollWeek,
String 						resetType,
int 						scheduleCustomFlag,
double 						spread,
Date 						startDate,
String 						startDateRollFlag
)
{
_accrualBusDay 			= accrualBusDay;
_accrualCalendars 		= accrualCalendars;
_accrualFreq			= accrualFreq;
_accrualMarching		= accrualMarching;
_accrualRollDay			= accrualRollDay;
_accrualRollWeek		= accrualRollWeek;
_amortRollDay			= amortRollDay;
_amortRollWeek			= amortRollWeek;
_amortAmount			= amortAmount;
_amortBusDay 			= amortBusDay;
_amortCalendars 		= amortCalendars;
_amortEndDate 			= amortEndDate;
_amortFreq				= amortFreq;
_amortMarching			= amortMarching;
_amortStartDate 		= amortStartDate;
_amortType				= amortType;
_averagingMethod		= averagingMethod;
_backStubDate			= backStubDate;
_backStubManualRate		= backStubManualRate;
_compFreq				= compFreq;
_compoundingConv		= compoundingConv;
_currency				= currency;
_dayCount				= dayCount;
_discountCurve			= discountCurve;
_endDate				= endDate;
_endDateRollFlag		= endDateRollFlag;
_endOfMonthIndicator	= endOfMonthIndicator;
_fixedQuote				= fixedQuote;
_frontStubDate			= frontStubDate;
_frontStubManualRate	= frontStubManualRate;
_gearFactor				= gearFactor;
_initialQuoteCalendars	= initialQuoteCalendars;
_initialQuoteDate		= initialQuoteDate;
_initialQuoteLag		= initialQuoteLag;
_legNo					= legNo;
_legType				= legType;
_marketIndex			= marketIndex;
_notional				= notional;
_notionalExchange		= notionalExchange;
_payBusDay				= payBusDay;
_payCalendars			= payCalendars;
_payFreq				= payFreq;
_payMarching			= payMarching;
_paymentConvention		= paymentConvention;
_paymentConversionCurrency	=	paymentConversionCurrency;
_paymentConversionIndex	= paymentConversionIndex;
_paymentConversionLag	= paymentConversionLag;
_payLag					= payLag;
_payRollDay				= payRollDay;
_payRollWeek			= payRollWeek;
_position				= position;
_precision				= precision;
_quoteCalendars			= quoteCalendars;
_quoteLag				= quoteLag;
_rateCutOff				= rateCutOff;
_resetAveraging 		= resetAveraging;
_resetBusDay	 		= resetBusDay;
_resetConvention		= resetConvention;
_resetFreq				= resetFreq;
_resetMarching			= resetMarching;
_resetRollDay			= resetRollDay;
_resetRollWeek			= resetRollWeek;
_resetType				= resetType;
_scheduleCustomFlag		= scheduleCustomFlag;
_spread					= spread;
_startDate				= startDate;
_startDateRollFlag		= startDateRollFlag;

// some deafults
_isCustomized = false;
_isPSGenerated = false;
_isRSGenerated = false;

 }


/* generate payment schedule here */

bool SwapLeg::genPaySchedule()
{

	BusOrCalConv  busOrCalConv(CAL);
	if ( getAccrualBusDay() != BusDayConv::find("NONE") && getAccrualRollWeek() != NULL_DOW )
	{
		busOrCalConv =  BusOrCalConv(BUS);
	}

	RollDayConv  * rollDayConv = new RollDayConv  (getAccrualRollWeek(),getAccrualRollDay(), busOrCalConv);
	logFile << "Roll and Day " << getAccrualRollWeek() << " : " << getAccrualRollDay() << endl;

	Date frontStubDate = getFrontStubDate();
	Date backStubDate = getBackStubDate();
	Date startDate = getStartDate();
	Date endDate   = getEndDate();

	if ( getStartDateRollFlag() == "Yes" )
	{
		startDate = getAccrualBusDay()->adjustToBusDay(startDate,*CalendarUtil::getCalendar(getAccrualCalendars()));
				 logFile << "\nstub routine : Start Date is : " << startDate << endl;
	}

	if ( getEndDateRollFlag() == "Yes" )
	{
		endDate = getAccrualBusDay()->adjustToBusDay(endDate,*CalendarUtil::getCalendar(getAccrualCalendars()));
		logFile << "\nstub routine : End Date is : " << endDate << endl;
	}


	if ( frontStubDate == getStartDate() )
	{
			// there is no front stub
			frontStubDate = startDate;  // set to rolled date to calculate schedule
	}


	if ( backStubDate == getEndDate() )
	{
		// there is no back stub
		backStubDate = endDate;  // set to rolled date to calculate schedule
	}


	if ( ! isPSGenerated() )
	{
		logFile << "GENERATE PAY SCHEDULE " << endl;

		DateMarcher::GenSchedule  genSchedulePay;

	if ( getAccrualMarching()->genSchedule (
	frontStubDate,
	backStubDate,
	getAccrualFreq(),
	*CalendarUtil::getCalendar(getAccrualCalendars()),
	getAccrualBusDay(),
	genSchedulePay,
	1,  //evenFinalPeriod,
	rollDayConv  ) )
	{

		if ( startDate != genSchedulePay.getESMinDate() )
		{
			logFile << "\nFront Stub Date is : ";
			logFile << genSchedulePay.getESMinDate() << endl;
			setFrontStubDate(genSchedulePay.getESMinDate());
		 }

		if ( endDate != genSchedulePay.getESMaxDate() )
		{
			logFile << "\nBack Stub Date is : ";
			logFile << genSchedulePay.getESMaxDate() << endl;
			setBackStubDate(genSchedulePay.getESMaxDate());

		}

		 genSchedulePay.getEventList().sort(); // for backward dates come in reverse order, so need to order ascending order.
		 std::list<Date>::const_iterator iterEvent = genSchedulePay.getEventList().begin () ;
     	 int noOfEvents = genSchedulePay.getEventList().size();
		 logFile << "No of Elements are front :" << noOfEvents << endl;
		 int cnt = 0;

		    for ( ; iterEvent != genSchedulePay.getEventList().end () ; ++iterEvent )
		      {
		        shared_ptr <PaySchedule> paySchedule( new PaySchedule());
		        cnt++;

		        if ( cnt != noOfEvents )
		        {
		        	paySchedule->setCouponStartDate(*iterEvent);
		        	paySchedule->setCouponEndDate(*(++iterEvent));

		        	int payLagCnt = getPayLag();
		        	Date paymentDate = paySchedule->getCouponEndDate();

		        	while ( payLagCnt > 0 )
		        	{
		        		paymentDate += Period(1, Days);
		        		paymentDate = getPayBusDay()->adjustToBusDay(paymentDate, *CalendarUtil::getCalendar(getPayCalendars()));
		        		cout << "PayLag is : " << payLagCnt << endl;
		        		payLagCnt--;
		        	}

		        	if ( payLagCnt == 0 )
		        		paymentDate = getPayBusDay()->adjustToBusDay(paymentDate, *CalendarUtil::getCalendar(getPayCalendars()));

		        	paySchedule->setPaymentDate(paymentDate);
		        	logFile << "payment date : coupon start and end  : " << paymentDate << ":" << paySchedule->getCouponStartDate()
		        			<< " : " << paySchedule->getCouponEndDate() << endl;
		        	//paySchedule->setPaymentType("Coupon");
		        	//paySchedule->setNotional(getNotional());
		        	 --iterEvent;
		        	 _payScheduleList.push_back(paySchedule);
		        }

		       }

	}

	if ( ! genCompSchedule() )
		logFile << "Comp Schedule generation failed " << endl;

	if ( ! genAmortSchedule() )
			logFile << "Amort Schedule generation failed " << endl;

	if ( isFloatLeg()) // RESETS only for float side
		if ( genResetSchedule() )
			logFile << "\nReset Schedule generated ..." << endl;

		setIsPSGenerated(true); // ps generated now

	} // is ps generated - finished

	return true;
}


// Reset Schedule Routine - can be called independent from payment schedule if needed...

bool SwapLeg::genResetSchedule()
{

	if ( ! isRSGenerated() )
	{
		DateMarcher::GenSchedule  genScheduleReset;
		BusOrCalConv busOrCalConv(CAL);

		if ( getResetBusDay() != BusDayConv::find("NONE") && getResetRollDay() == 0 )
		{
			 busOrCalConv = BusOrCalConv(BUS);
		}

		RollDayConv  * rollDayConv = new RollDayConv (getResetRollWeek(), getResetRollDay(), busOrCalConv);
		Date frontStubDate = getFrontStubDate();
		Date backStubDate = getBackStubDate();
		Date startDate = getStartDate();
		Date endDate   = getEndDate();

		if ( getStartDateRollFlag() == "Yes" )
		{
			startDate = getResetBusDay()->adjustToBusDay(startDate,*CalendarUtil::getCalendar(getAccrualCalendars()));
		    logFile << "\nstub routine reset : Start Date is : " << startDate << endl;
		}

		if ( getEndDateRollFlag() == "Yes" )
		{
			endDate = getResetBusDay()->adjustToBusDay(endDate,*CalendarUtil::getCalendar(getAccrualCalendars()));
			logFile << "\nstub routine reset : End Date is : " << endDate << endl;
		}

		if ( frontStubDate == getStartDate() )
		{
				// there is no front stub
			frontStubDate = startDate;  // set to rolled date to calculate schedule
		}

		if ( backStubDate == getEndDate() )
		{
			// there is no back stub
			backStubDate = endDate;  // set to rolled date to calculate schedule
		}

		_resetScheduleList.clear(); // clear the lists

		if ( getResetMarching()->genSchedule (frontStubDate,backStubDate,	getResetFreq(),
				*CalendarUtil::getCalendar(getAccrualCalendars()),	getResetBusDay(),		genScheduleReset,		1, 		rollDayConv  ) )
		{

			genScheduleReset.getEventList().sort(); // for backward dates will come in reverse order, so need to sort in ascending order.
			std::list<Date>::const_iterator iterEventReset = genScheduleReset.getEventList().begin () ;

			int noOfEvents = genScheduleReset.getEventList().size();
			logFile << "No of Elements are front :" << noOfEvents << endl;

			int lagSign = getQuoteLag() >= 0 ? 1 : -1;
			logFile << "lag sign is : " << lagSign << endl;
			const BusDayConv * resetBusDay = lagSign > 0 ? BusDayConv::find("FOL") : BusDayConv::find("PRE") ;
			int lag = getQuoteLag() * lagSign;
			logFile << "lag is : " << lag << endl;
			int resetCnt = 0;

			for ( ; iterEventReset != genScheduleReset.getEventList().end () ; ++iterEventReset )
			{
			    shared_ptr <ResetSchedule> resetSchedule( new ResetSchedule());
			  	resetSchedule->setResetStartDate(*iterEventReset);
        		Date quoteDate = resetSchedule->getResetStartDate();
			    resetCnt++;

			    logFile << "Quote Date started off " << quoteDate << endl;

			    if ( resetCnt != noOfEvents)
			    {
			       	resetSchedule->setResetEndDate(*(++iterEventReset));
			       	//logFile << "Reset Start - End Date : " << resetSchedule->getResetStartDate() << ":" << resetSchedule->getResetEndDate() << endl;
			       	--iterEventReset; // CHANGE IT BACK

	        		if ( getResetConvention() == "IN_ARREARS" )
	        			quoteDate = resetSchedule->getResetEndDate();
			    }

   	        	resetSchedule->setRateIndexType("IRRATE");

        		if ( getInitialQuoteDate() != Date(01,01,1901) && resetCnt == 1
        				&& getFrontStubDate() == getStartDate()  )  // no front stub
        		{
        		   	 quoteDate = getInitialQuoteDate();
        		   	// logFile << "Quote Date is : " << quoteDate << endl;
        		}
        		else
        		{
        			//logFile << "Dates are : " << resetSchedule->getResetStartDate() <<
        			// resetSchedule->getResetEndDate() << endl;

        			int cntReset = lag;

        			while ( cntReset > 0 )
        			{
        				Period period(lagSign * 1,Days);
        				quoteDate = quoteDate + period;
        				quoteDate = resetBusDay->adjustToBusDay(quoteDate,*CalendarUtil::getCalendar(getQuoteCalendars()) );
        				cntReset--;

        			}

				// if accrual bus day none - don't roll rates if lag is 0
        			if (  cntReset == 0 ) // && getAccrualBusDay() != BusDayConv::find("NONE") )
        				quoteDate = getResetBusDay()->adjustToBusDay(quoteDate,*CalendarUtil::getCalendar(getQuoteCalendars()) );
				//else if ( cntReset == 0 && getAccrualBusDay() == BusDayConv::find("NONE") )
				//	quoteDate = getAccrualBusDay()->adjustToBusDay(quoteDate,*CalendarUtil::getCalendar(getQuoteCalendars()) );

        		}
				resetSchedule->setQuoteDate( quoteDate );
				logFile << "Quote Date is : " << quoteDate << endl;
				logFile << "Market Index is : " << getMarketIndex() << endl;

				if ( FixingRates::getFixingRate(quoteDate, resetSchedule->getResetStartDate(), getMarketIndex()) == 0.0
					&& quoteDate < Date::todaysDate() )
							resetSchedule->setRateSettingType("HISTORIC");
				else if ( FixingRates::getFixingRate(quoteDate, resetSchedule->getResetStartDate(),getMarketIndex()) != 0.0
					&& quoteDate <= Date::todaysDate() )
							resetSchedule->setRateSettingType("RATESET");
				else if ( quoteDate >= Date::todaysDate() )
							resetSchedule->setRateSettingType("PROJECTED");

                resetSchedule->setRate(getPeriodRate(FixingRates::getFixingRate(quoteDate, resetSchedule->getResetStartDate(), getMarketIndex())));

				if ( resetSchedule->getResetStartDate() != backStubDate && getBackStubDate() == getEndDate() )
					_resetScheduleList.push_back(resetSchedule);
				else if ( getBackStubDate() != getEndDate() )
				{
					_resetScheduleList.push_back(resetSchedule);
				}

				if ( getBackStubDate() != getEndDate() && getBackStubDate() == resetSchedule->getResetStartDate() )
				{
					// we are going to force generate stub tenors
					setIsPSGenerated(true);

					if ( ! generateStubs() )
						logFile << "failed stub generation" << endl;

					setIsPSGenerated(false);

						//displayPaySchedule().sort();
						PayScheduleList::const_iterator iterPay = displayPaySchedule().begin();
						Date couponStartDate(01,01,1901);
						Date couponEndDate(01,01,1901);

						for ( ; iterPay != displayPaySchedule().end() ; ++iterPay )
						{

							if ( (*iterPay)->getCouponStartDate() == getBackStubDate() )
							{
								couponStartDate = (*iterPay)->getCouponStartDate();
								couponEndDate = (*iterPay)->getCouponEndDate();
								//break; // no need to continue, got the dates
							}
						}

						_stubResetsList.sort();
						resetSchedule->setResetEndDate(couponEndDate);

						StubResetsList::const_iterator iterStubReset = _stubResetsList.begin() ;
						String marketIndexA = "";
						String marketIndexB = "";
						Period stubTenorA;
						Period stubTenorB;

						for ( ; iterStubReset != _stubResetsList.end() ; ++iterStubReset )
						{

							if ( (*iterStubReset)->getStartDate() == resetSchedule->getResetStartDate() && (*iterStubReset)->getStubType() == "BStubA" )
							{
								marketIndexA = (*iterStubReset)->getStubMarketIndex();
								stubTenorA = (*iterStubReset)->getStubTenor();

							}
							else if ( (*iterStubReset)->getStartDate() == resetSchedule->getResetStartDate() && (*iterStubReset)->getStubType() == "BStubB" )
							{
								marketIndexB = (*iterStubReset)->getStubMarketIndex();
								stubTenorB = (*iterStubReset)->getStubTenor();

							}
						}

						if ( FixingRates::getFixingRate(quoteDate, resetSchedule->getResetStartDate(), getMarketIndex()) == 0.0
									&& quoteDate < Date::todaysDate() )
								resetSchedule->setRateSettingType("HISTORIC");
							else if ( FixingRates::getFixingRate(quoteDate, resetSchedule->getResetStartDate(),getMarketIndex()) != 0.0
									&& quoteDate <= Date::todaysDate() )
								resetSchedule->setRateSettingType("RATESET");
							else if ( quoteDate >= Date::todaysDate() )
								resetSchedule->setRateSettingType("PROJECTED");

						resetSchedule->setRate(getPeriodRate(FixingRates::getFixingRate( resetSchedule->getQuoteDate(),
												marketIndexA, marketIndexB, couponStartDate ,
											couponEndDate, getResetBusDay() )) );

					 	logFile << "Reset Start - End Date : " << resetSchedule->getResetStartDate() << ":" << resetSchedule->getResetEndDate() << endl;

						_resetScheduleList.pop_back();
						_resetScheduleList.push_back(resetSchedule); // update with latest info

				}

			  }

		     // take care of front and back stubs now

		     if ( getFrontStubDate() != getStartDate() )
		     {
     		     shared_ptr <ResetSchedule> resetScheduleStub( new ResetSchedule());

			     resetScheduleStub->setResetStartDate(startDate);
			     resetScheduleStub->setResetEndDate(getFrontStubDate());
			     resetScheduleStub->setRateIndexType("IRRATE");
			     Date quoteDate = resetScheduleStub->getResetStartDate();

	        		if ( getResetConvention() == "IN_ARREARS" )
	        	        	quoteDate = resetScheduleStub->getResetEndDate();

			     if ( getInitialQuoteDate() != Date(01,01,1901) )
			     {
			    	 quoteDate = getInitialQuoteDate();
			     }
			     else
			     {


			    	 int cntReset = lag;

			    	 while ( cntReset > 0 )
			    	 {
			    		 Period period(lagSign * 1,Days);
			    		 quoteDate = quoteDate + period;
			    		 quoteDate = resetBusDay->adjustToBusDay(quoteDate,*CalendarUtil::getCalendar(getQuoteCalendars()) );
			    		 cntReset--;

			    	 }

			     if (  cntReset == 0 )
						quoteDate = getResetBusDay()->adjustToBusDay(quoteDate,*CalendarUtil::getCalendar(getQuoteCalendars()) );
			     }

			     resetScheduleStub->setQuoteDate( quoteDate );
			     resetScheduleStub->setRate(getPeriodRate(FixingRates::getFixingRate(quoteDate, resetScheduleStub->getResetStartDate(),getMarketIndex())));

		    	 //displayPaySchedule().sort();
			     PayScheduleList::const_iterator iterPay = displayPaySchedule().begin();

			     	_resetScheduleList.push_front(resetScheduleStub);

					setIsPSGenerated(true);

					if ( ! generateStubs() )
						logFile << "failed stub generation" << endl;

					setIsPSGenerated(false);

			     	Date couponStartDate(01,01,1901);
			     	Date couponEndDate(01,01,1901);

			     		for ( ; iterPay != displayPaySchedule().end() ; ++iterPay )
			     		{

			     			if ( (*iterPay)->getCouponEndDate() == getFrontStubDate() )
			     			{
			     				couponStartDate = (*iterPay)->getCouponStartDate();
			     				couponEndDate = (*iterPay)->getCouponEndDate();
			     				//break; // no need to continue, got the dates
			     			}
			     		}

			     		_stubResetsList.sort();

			     		StubResetsList::const_iterator iterStubReset = _stubResetsList.begin() ;
			     		String marketIndexA = "";
			     		String marketIndexB = "";
			     		Period stubTenorA;
			     		Period stubTenorB;

			     		for ( ; iterStubReset != _stubResetsList.end() ; ++iterStubReset )
			     		{

			     			//logFile << "details " << (*iterStubReset)->getStartDate() << " : " << startDate << endl;

			     			if ( (*iterStubReset)->getStartDate() == startDate && (*iterStubReset)->getStubType() == "FStubA" )
			     			{
			     				marketIndexA = (*iterStubReset)->getStubMarketIndex();
			     				stubTenorA = (*iterStubReset)->getStubTenor();
			     			}
			     			else if ( (*iterStubReset)->getStartDate() == startDate && (*iterStubReset)->getStubType() == "FStubB" )
			     			{
			     				marketIndexB = (*iterStubReset)->getStubMarketIndex();
			     				stubTenorB = (*iterStubReset)->getStubTenor();
			     			}
			     		}

			     			resetScheduleStub->setRate(getPeriodRate(FixingRates::getFixingRate( quoteDate,
			     							marketIndexA, marketIndexB,  couponStartDate ,
			     								couponEndDate, getResetBusDay() )) );


			     		 	//logFile << "Reset Start - End Date : " << resetScheduleStub->getResetStartDate() << ":"
			     		 			//<< resetScheduleStub->getResetEndDate() << endl;

			     _resetScheduleList.pop_front();
			     _resetScheduleList.push_front(resetScheduleStub);

			  }

		      ResetScheduleList::const_iterator iterReset = displayResetSchedule().begin() ;

		      for ( ; iterReset != displayResetSchedule().end() ; ++iterReset )
   		      {
				logFile <<"\n Reset Start Date : Quote Date : Period Rate  - ";
				logFile << (*iterReset)->getResetStartDate() << " : " << (*iterReset)->getQuoteDate() << " : "
						<< (*iterReset)->getRate() << " : " << (*iterReset)->getRateIndexType() << ":" <<  (*iterReset)->getRateSettingType()  << endl;

   		       }

		} // genSchedule finished

			setIsRSGenerated(true); // resets generated now
	} // schedule generation finished

	return true;

}



bool SwapLeg::genCompSchedule()
{

	// let us generate compounding schedule now independently - they should match with pay as the reference data inputs are same
	 	if ( getCompoundingConv() != "NONE" )  // compounding is for float leg only ??? - let us give chance for fixed leg as well
		{
	 		BusOrCalConv  busOrCalConv(CAL);
	 		if ( getAccrualBusDay() != BusDayConv::find("NONE") && getAccrualRollWeek() != NULL_DOW )
	 			{
	 				busOrCalConv =  BusOrCalConv(BUS);
	 			}

	 			RollDayConv  * rollDayConv = new RollDayConv  (getAccrualRollWeek(),getAccrualRollDay(), busOrCalConv);
	 			Date frontStubDate = getFrontStubDate();
	 			Date backStubDate = getBackStubDate();
	 			Date startDate = getStartDate();
	 			Date endDate   = getEndDate();

	 			if ( getStartDateRollFlag() == "Yes" )
	 			{
	 				startDate = getAccrualBusDay()->adjustToBusDay(startDate,*CalendarUtil::getCalendar(getAccrualCalendars()));
	 						 logFile << "\nstub routine : Start Date is : " << startDate << endl;
	 			}

	 			if ( getEndDateRollFlag() == "Yes" )
	 			{
	 				endDate = getAccrualBusDay()->adjustToBusDay(endDate,*CalendarUtil::getCalendar(getAccrualCalendars()));
	 				logFile << "\nstub routine : End Date is : " << endDate << endl;
	 			}

	 			if ( frontStubDate == getStartDate() )
	 			{
	 					// there is no front stub
	 					frontStubDate = startDate;  // set to rolled date to calculate schedule
	 			}


	 			if ( backStubDate == getEndDate() )
	 			{
	 				// there is no back stub
	 				backStubDate = endDate;  // set to rolled date to calculate schedule
	 			}

			 DateMarcher::GenSchedule  genScheduleComp;
			 const DateMarcher * compMarching = getAccrualMarching(); // always forward

			 if ( compMarching->genSchedule (
				frontStubDate,
			 	backStubDate,
			 	getCompFreq(),
			 	*CalendarUtil::getCalendar(getAccrualCalendars()),
			 	getAccrualBusDay(),
			 	genScheduleComp,
			 	1,  //evenFinalPeriod,
			 	rollDayConv  ) )
			 {

				genScheduleComp.getEventList().sort(); // for backward dates come in reverse order, so need to order ascending order.
				std::list<Date>::const_iterator iterEvent = genScheduleComp.getEventList().begin () ;

				int noOfEvents = genScheduleComp.getEventList().size();
				logFile << "No of Elements in comp schedule :" << noOfEvents - 1 << endl;;
				int cnt = 0;

				for ( ; iterEvent != genScheduleComp.getEventList().end () ; ++iterEvent )
				{
					shared_ptr <CompSchedule> compSchedule( new CompSchedule());
					cnt++;

					if ( cnt != noOfEvents )
					{
						compSchedule->setCompStartDate(*iterEvent);
						compSchedule->setCompEndDate(*(++iterEvent));
						compSchedule->setNotional(getNotional());
						--iterEvent;
						_compScheduleList.push_back(compSchedule);
						logFile << "Comp start:end dates	:" << compSchedule->getCompStartDate() << ":" << compSchedule->getCompEndDate() << endl;
					}
				}

			}

			 if ( startDate != getFrontStubDate() ) // front stub exists
			 {
				 // add front stub
				 shared_ptr <CompSchedule> compSchedule( new CompSchedule());
				 compSchedule->setCompStartDate(startDate);
				 compSchedule->setCompEndDate(getFrontStubDate());
				 compSchedule->setNotional(getNotional());
				 _compScheduleList.push_front(compSchedule);
				logFile << "Comp start:end dates	:" << compSchedule->getCompStartDate() << ":" << compSchedule->getCompEndDate() << endl;

			 }

			 if ( endDate != getBackStubDate() ) // back stub exists
			 {
				 // add front stub

				 shared_ptr <CompSchedule> compSchedule( new CompSchedule());
				 compSchedule->setCompStartDate(getBackStubDate());
				 compSchedule->setCompEndDate(endDate);
				 compSchedule->setNotional(getNotional());
				 _compScheduleList.push_back(compSchedule);
				logFile << "Comp start:end dates	:" << compSchedule->getCompStartDate() << ":" << compSchedule->getCompEndDate() << endl;

			 }


		} // compounding schedule done

	 	CompScheduleList::const_iterator iterComp = displayCompSchedule().begin();


	 			  for ( ; iterComp != displayCompSchedule().end() ; ++iterComp )
	 				{

	 				 logFile << "COMP start : end " << (*iterComp)->getCompStartDate() << " : " << (*iterComp)->getCompEndDate() << endl;

	 				}
	 	return true;

}

bool SwapLeg::genAmortSchedule()
{

 	if ( getAmortType() != "NONE" )
	{
		 logFile << "GENERATE Amort SCHEDULE " << endl;

			 	 	BusOrCalConv  busOrCalConv(CAL);
		 	 		if ( getAccrualBusDay() != BusDayConv::find("NONE") && getAccrualRollWeek() != NULL_DOW )
	 	 			{
	 	 				busOrCalConv =  BusOrCalConv(BUS);
	 	 			}

		 	 			RollDayConv  * rollDayConv = new RollDayConv  (getAccrualRollWeek(),getAccrualRollDay(), busOrCalConv);

		 	 			Date frontStubDate = getFrontStubDate();
		 	 			Date backStubDate = getBackStubDate();
		 	 			Date startDate = getStartDate();
		 	 			Date endDate   = getEndDate();

		 	 			if ( getStartDateRollFlag() == "Yes" )
		 	 			{
		 	 				startDate = getAccrualBusDay()->adjustToBusDay(startDate,*CalendarUtil::getCalendar(getAccrualCalendars()));
		 	 						 logFile << "\nstub routine : Start Date is : " << startDate << endl;
		 	 			}

		 	 			if ( getEndDateRollFlag() == "Yes" )
		 	 			{
		 	 				endDate = getAccrualBusDay()->adjustToBusDay(endDate,*CalendarUtil::getCalendar(getAccrualCalendars()));
		 	 				logFile << "\nstub routine : End Date is : " << endDate << endl;
		 	 			}


		 	 			if ( frontStubDate == getStartDate() )
		 	 			{
		 	 					// there is no front stub
		 	 					frontStubDate = startDate;  // set to rolled date to calculate schedule
		 	 			}


		 	 			if ( backStubDate == getEndDate() )
		 	 			{
		 	 				// there is no back stub
		 	 				backStubDate = endDate;  // set to rolled date to calculate schedule
		 	 			}

		 DateMarcher::GenSchedule  genScheduleAmort;
		 double amortNotionalTmp = getNotional(); // initialize to leg notional for now
		 Date amortStubDate(01,01,1901);
	 	 const DateMarcher * amortMarching = getAmortMarching();
		 genScheduleAmort.getEventList().clear();

		 if ( amortMarching->genSchedule (
			getAmortStartDate(),
		 	getAmortEndDate(),
		 	getAmortFreq(),
		 	*CalendarUtil::getCalendar(getAmortCalendars()),
		 	getAmortBusDay(),
		 	genScheduleAmort,
		 	1,  //evenFinalPeriod,
		 	rollDayConv  ) )
		 {

		 	genScheduleAmort.getEventList().sort(); // for backward, dates come in reverse order, so need to order ascending order.
		 	std::list<Date>::const_iterator iterEvent = genScheduleAmort.getEventList().begin () ;
		 	int noOfEvents = genScheduleAmort.getEventList().size();
		 	logFile << "No of Elements are front or back - amort :" << noOfEvents - 1 << endl;;
		 	int cnt = 0;

		 	for ( ; iterEvent != genScheduleAmort.getEventList().end () ; ++iterEvent )
		 	{
		 		shared_ptr <AmortSchedule> amortSchedule( new AmortSchedule());
		 		shared_ptr <AmortSchedule> amortScheduleStub( new AmortSchedule());
		 		cnt++;

		 		if ( cnt != 1 )
		 		{
		 			if ( getAmortType() == "PERCENT" )
		 			{
		 				amortNotionalTmp =  amortNotionalTmp - (amortNotionalTmp * getAmortAmount()/100);
		 			}

		 			if ( getAmortType() == "AMOUNT" )
		 			{
		 				amortNotionalTmp = amortNotionalTmp - getAmortAmount();
		 			}

		 			if ( getAmortType() == "EQUAL" )
		 			{
		 				amortNotionalTmp = amortNotionalTmp - (getNotional()/(noOfEvents - 1));

		 				if ( amortNotionalTmp < 0 )
		 					amortNotionalTmp = 0.0;

		 			}
		 			if ( getAmortType() == "MORTGAGE" )
		 			{
		 				double mortExpN = pow((1 + ( getAmortAmount()/(100 * (int) getPayFreq())) ) , (noOfEvents -2 ));
		 				double mortExpC = pow((1 + ( getAmortAmount()/(100 * (int) getPayFreq())) ) , (cnt -1 ));

		 				amortNotionalTmp = getNotional() * ( (mortExpN - mortExpC) / ( mortExpN -1 ));

		 			}
		 		}

		 		if ( cnt != noOfEvents )
		 		{

		 			amortSchedule->setStartDate(*iterEvent);
		 		    amortSchedule->setEndDate(*(++iterEvent));
		 			 --iterEvent;

		 			if ( getFrontStubDate() != getStartDate() && getFrontStubDate() < amortSchedule->getEndDate()
		 					&& cnt == 1 )
		 			{
		 				amortScheduleStub->setStartDate( getStartDate() );
		 				amortScheduleStub->setEndDate( getFrontStubDate() );
		 				amortScheduleStub->setAmortNotional(amortNotionalTmp);
		 				_amortScheduleList.push_back(amortScheduleStub);
		 				amortSchedule->setStartDate( getFrontStubDate() );
		 				logFile << "Amort Dates and Notionals for Front Stub : " << amortScheduleStub->getStartDate() << " : "
		 						 			<< amortScheduleStub->getEndDate() << " : " << amortScheduleStub->getAmortNotional() << endl;

		 				if ( getAmortType() == "PERCENT" )
		 				{
		 					 amortNotionalTmp =  amortNotionalTmp - (amortNotionalTmp * getAmortAmount()/100);
		 				}

		 				if ( getAmortType() == "AMOUNT" )
		 				{
		 					 amortNotionalTmp = amortNotionalTmp - getAmortAmount();
		 				}

		 				if ( getAmortType() == "EQUAL" )
		 				{
		 					 amortNotionalTmp = amortNotionalTmp - (getNotional()/(noOfEvents - 1));

		 					if ( amortNotionalTmp < 0 )
		 						amortNotionalTmp = 0.0;

		 				}

		 				if ( getAmortType() == "MORTGAGE" )
		 				{
		 					double mortExpN = pow((1 + ( getAmortAmount()/(100 * (int) getPayFreq())) ) , (noOfEvents - 2 ));
		 					double mortExpC = pow((1 + ( getAmortAmount()/(100 * (int) getPayFreq())) ) , (cnt ));

		 					amortNotionalTmp = getNotional() * ( (mortExpN - mortExpC) / ( mortExpN -1 ));

		 				}


		 			}

		 			amortSchedule->setAmortNotional(amortNotionalTmp);
		 			_amortScheduleList.push_back(amortSchedule);
		 			logFile << "Amort Dates and Notionals : " << amortSchedule->getStartDate() << " : " << amortSchedule->getEndDate() << " : "
		 					<< amortSchedule->getAmortNotional() << endl;
		 		}
		 		if ( cnt == noOfEvents )
		 		{
		 			amortSchedule->setStartDate(*iterEvent);
		 			if ( amortSchedule->getStartDate() < getEndDate() )
		 			{
		 				amortSchedule->setEndDate(*iterEvent);

		 				if ( getAmortType() == "MORTGAGE" )
		 					amortNotionalTmp = 0.0;

		 				amortSchedule->setAmortNotional(amortNotionalTmp);
		 				_amortScheduleList.push_back(amortSchedule);
		 				logFile << "Amort Dates and Notionals - last : " << amortSchedule->getStartDate() << " : " << amortSchedule->getEndDate() << " : "
		 					<< amortSchedule->getAmortNotional() << endl;
		 			}
		 		}

		   }

		 }
 	   } // amort schedule done here


	AmortScheduleList::const_iterator iterAmort = displayAmortSchedule().begin();

			for ( ; iterAmort != displayAmortSchedule().end() ; ++iterAmort )
			{
				logFile << "Amort Dates : " << (*iterAmort)->getStartDate() << " : " << (*iterAmort)->getEndDate() << endl;
			}


 	return  true;

}

double SwapLeg::getPeriodRate( double rate)  // gets period rate including spread and gear factor
{
 if ( isFloatLeg() )
 {
	if ( getCompoundingConv() == "FLAT/ADJ" || getCompoundingConv() == "FLAT/FLAT"  ||  getCompoundingConv() == "ADJ/FLAT" )
	   return getCurrency()->getRoundingConv()->round(rate,getPrecision());
	else if ( getCompoundingConv() == "NONE" ||  getCompoundingConv() == "ADJ/ADJ" )
		return getCurrency()->getRoundingConv()->round(rate * getGearFactor() + getSpread()/10000, getPrecision()); // note spread is in basis points
 }

	return getCurrency()->getRoundingConv()->round(rate,getPrecision()); // should come for Fixed leg  here
}


bool SwapLeg::generateStubs()
{

	Date startDate = getStartDate();
	Date endDate = getEndDate();
	Date fDate = getStartDate();
	Date bDate = getEndDate();

	if ( getStartDateRollFlag() == "Yes" )
	{
		startDate = getAccrualBusDay()->adjustToBusDay(startDate,*CalendarUtil::getCalendar(getAccrualCalendars()));
		logFile << "\nstub routine gen stubs  : Start Date is : " << startDate << endl;
	}

	if ( getEndDateRollFlag() == "Yes" )
	{
		endDate = getAccrualBusDay()->adjustToBusDay(endDate,*CalendarUtil::getCalendar(getAccrualCalendars()));
		 logFile << "\nstub routine gen stubs : End Date is : " << endDate << endl;
	}


	if (! isPSGenerated() ) // generate payment schedule if not generated already
		if ( ! genPaySchedule() )
			return false; // issues in generating payment schedule


	if ( isFloatLeg() ) // stub tenors should be generated only for float leg
	{

		shared_ptr <StubResets> fsResetsA( new StubResets());
		shared_ptr <StubResets> fsResetsB( new StubResets());
		shared_ptr <StubResets> bsResetsA( new StubResets());
		shared_ptr <StubResets> bsResetsB( new StubResets());
		Period fsTenorA(0,Days);
		Period fsTenorB(0,Days);
		Period bsTenorA(0,Days);
		Period bsTenorB(0,Days);

		if ( getFrontStubDate() != fDate )
		{
			int daysDiff = getFrontStubDate().serialNumber() - startDate.serialNumber();

			if ( daysDiff > 0 && daysDiff <= 2 )
			{
				fsTenorA = Period(2,Days);
				fsTenorB = Period(2,Days);
				logFile << "Stubf Tenors are : 2D:2D" << endl;
			}

			if ( daysDiff <= 7 && daysDiff > 2 )
			{
				fsTenorA = Period(2,Days);
				fsTenorB = Period(1,Weeks);
				logFile << "Stubf Tenors are : 2D:1W " << endl;
			}

			if ( daysDiff <= 14 && daysDiff > 7)
			{
				fsTenorA = Period(1, Weeks);
				fsTenorB = Period(2, Weeks);
				logFile << "Stubf Tenors are : 1W:2W" << endl;
			}

			if ( daysDiff <= startDate.monthLength(startDate.month(),Date::isLeap(startDate.year())) && daysDiff > 14 )
			{
				fsTenorA = Period(2, Weeks);
				fsTenorB = Period(1, Months);
				logFile << "Stubf Tenors are : 2W:1M" << endl;
			}

			if ( daysDiff > startDate.monthLength(startDate.month(),Date::isLeap(startDate.year()) ) )
			{
				int month = 0;
				Date tmpDate = startDate;

				while ( tmpDate < getFrontStubDate()  )
				{
					tmpDate += Period(1,Months);
					month++;
				}


				fsTenorA = Period(month-1,Months);
				fsTenorB = Period(month,Months);
				logFile << "Stubf Tenors are : " << month -1 << "M::" << month << "M" << endl;
			}

			ResetScheduleList::const_iterator iterReset = displayResetSchedule().begin() ;

			for ( ; iterReset != displayResetSchedule().end() ; ++iterReset )
			{
				if ( getFrontStubDate() == (*iterReset)->getResetStartDate() &&
						(*iterReset)->getRateIndexType() == "IRRATE" )
				{
					// note, it is the event that starts before the front stub, we are interested in :-) ...
					fsResetsA->setStartDate((*(--iterReset))->getResetStartDate());
					++iterReset;
					fsResetsA->setQuoteDate((*(--iterReset))->getQuoteDate());
					++iterReset;
					fsResetsA->setStubRateType("P"); // projected first time even if it is in the past.
					fsResetsA->setStubMarketIndex(FixingRates::getFixingQuote(getMarketIndex(),fsTenorA));
					fsResetsA->setStubType("FStubA");
					fsResetsA->setStubTenor(fsTenorA);
					fsResetsA->setManualStub(false);

					_stubResetsList.push_back(fsResetsA);

					fsResetsB->setStartDate((*(--iterReset))->getResetStartDate());
					++iterReset;
					fsResetsB->setQuoteDate((*(--iterReset))->getQuoteDate());
					++iterReset;
					fsResetsB->setStubRateType("P"); // projected first time even if it is in the past
					fsResetsB->setStubMarketIndex(FixingRates::getFixingQuote(getMarketIndex(),fsTenorB));
					fsResetsB->setStubType("FStubB");
					fsResetsB->setStubTenor(fsTenorB);
					fsResetsB->setManualStub(false);

					_stubResetsList.push_back(fsResetsB);
				}

			}

		}

		if ( getBackStubDate() != bDate )
		{
			int daysDiff = endDate.serialNumber() - getBackStubDate().serialNumber();

			if ( daysDiff > 0 && daysDiff <= 2 )
			{
				bsTenorA = Period(2, Days);
				bsTenorB = Period(2, Days);
				logFile << "Stub Tenors are : 2D:2D" << endl;
			}

			if ( daysDiff <= 7 && daysDiff > 2 )
			{
				bsTenorA = Period(2, Days);
				bsTenorB = Period(1, Weeks);
				logFile << "Stub Tenors are : 2D:1W" << endl;
			}

			if ( daysDiff <= 14 && daysDiff > 7)
			{
				bsTenorA = Period(1, Weeks);
				bsTenorB = Period(2, Weeks);
				logFile << "Stub Tenors are : 1W:2W" << endl;
			}

			if ( daysDiff <= endDate.monthLength(endDate.month(),Date::isLeap(endDate.year())) && daysDiff > 14 )
			{
				bsTenorA = Period(2, Weeks);
				bsTenorB = Period(1, Months);
				logFile << "Stub Tenors are : 2W:1M" << endl;
			}

			if ( daysDiff > endDate.monthLength(endDate.month(),Date::isLeap(endDate.year()) ) )
			{
				int month = 0;
				Date tmpDate = endDate;

				while ( tmpDate > getBackStubDate()  )
				{
					tmpDate = tmpDate - Period(1,Months);
					month++;
				}

			  bsTenorA = Period(month -1 , Months );
			  bsTenorB = Period(month, Months );

			  logFile << "Stub Tenors are : " << month -1 << "M::" << month <<"M" << endl;

			}

			ResetScheduleList::const_iterator iterReset = displayResetSchedule().begin() ;

			for ( ; iterReset != displayResetSchedule().end() ; ++iterReset )
			{
				if ( getBackStubDate() == (*iterReset)->getResetStartDate() &&
						(*iterReset)->getRateIndexType() == "IRRATE" )
				{
						bsResetsA->setStartDate((*iterReset)->getResetStartDate());
						bsResetsA->setQuoteDate((*iterReset)->getQuoteDate());
						bsResetsA->setStubRateType("P"); // projected first time even if it is in the past.
						bsResetsA->setStubMarketIndex(FixingRates::getFixingQuote(getMarketIndex(),bsTenorA));
						bsResetsA->setStubType("BStubA");
						bsResetsA->setStubTenor(bsTenorA);
						bsResetsA->setManualStub(false);
						_stubResetsList.push_back(bsResetsA);

						bsResetsB->setStartDate((*iterReset)->getResetStartDate());
						bsResetsB->setQuoteDate((*iterReset)->getQuoteDate());
						bsResetsB->setStubRateType("P"); // projected first time even if it is in the past
						bsResetsB->setStubMarketIndex(FixingRates::getFixingQuote(getMarketIndex(),bsTenorB));
						bsResetsB->setStubType("BStubB");
						bsResetsB->setStubTenor(bsTenorB);
						bsResetsB->setManualStub(false);
						_stubResetsList.push_back(bsResetsB);

				}

			}

		}

	} // now we have stub tenors generated

		return true;
}

// generate cash flow method can be called separately

bool SwapLeg::genLegCashFlows()
{


	if (! isPSGenerated() && ! isCustomized() ) // generate payment schedule if not generated already and not customized
		if ( ! genPaySchedule() )
			return false; // issues in generating payment schedule

	//displayPaySchedule().sort();

	PayScheduleList::const_iterator iterPay = displayPaySchedule().begin();
	Date amortStubDate(01,01,1901);
	double lastAmortNotional = getNotional();
	double dcfNot = 0.0;
	double periodRate = 0.0;


	for ( ; iterPay != displayPaySchedule().end() ; ++iterPay )
	{

		if ( isCustomized() )
			lastAmortNotional = (*iterPay)->getNotional();

		logFile << "Payment Start and End Dates " << (*iterPay)->getCouponStartDate() << " : " << (*iterPay)->getCouponEndDate() << endl;

		double compAmount = 0.0;
		double spreadAmount = 0.0;
		bool finalPeriod = ( getEndDate() != getBackStubDate() &&
						getBackStubDate() == (*iterPay)->getCouponStartDate() ) ? true : false ;
		bool stubPeriod =  ( (getEndDate() != getBackStubDate() && getBackStubDate() == (*iterPay)->getCouponStartDate()) ||
							( getStartDate() != getFrontStubDate() && getFrontStubDate() == (*iterPay)->getCouponEndDate() ) ) ? true : false ;


		if ( getCompoundingConv() != "NONE" ) //&& isFloatLeg() ) - check this
		{
			//displayCompSchedule().sort();
		   CompScheduleList::const_iterator iterComp = displayCompSchedule().begin();


		   for ( ; iterComp != displayCompSchedule().end() ; ++iterComp )
			{

			 if ( ( (*iterPay)->getCouponStartDate() <= (*iterComp)->getCompStartDate() ) &&
						 ( (*iterPay)->getCouponEndDate() >= (*iterComp)->getCompEndDate() ) )
			 {

				logFile << "comp start : end " << (*iterComp)->getCompStartDate() << " : " << (*iterComp)->getCompEndDate() << endl;
				 logFile << "PAY start : end " << (*iterPay)->getCouponStartDate() << " : " << (*iterPay)->getCouponEndDate() << endl;
				 // check resets
				 if ( isFloatLeg() )
				 {
					 displayResetSchedule().sort();
					 ResetScheduleList::const_iterator iterReset = displayResetSchedule().begin();

					 for ( ; iterReset != displayResetSchedule().end() ; ++iterReset )
					 {
						 if ( (*iterReset)->getRateIndexType() == "IRRATE" )
						 {

							// logFile << " dates : " <<  (*iterComp)->getCompStartDate() << " : " << (*iterReset)->getResetStartDate() << endl;

						 if ( ( getCompFreq() == getResetFreq() ) && ( (*iterComp)->getCompStartDate() == (*iterReset)->getResetStartDate() ) )
						 {
							 if ( getFrontStubDate() != getStartDate() && (*iterPay)->getCouponEndDate() == getFrontStubDate() ) // there is a front stub
							 {
								 _stubResetsList.sort();

								 StubResetsList::const_iterator iterStubReset = _stubResetsList.begin() ;
								 String marketIndexA = "";
								 String marketIndexB = "";
								 Period stubTenorA;
								 Period stubTenorB;

								 for ( ; iterStubReset != _stubResetsList.end() ; ++iterStubReset )
								 {
									 if ( (*iterStubReset)->getStartDate() == (*iterReset)->getResetStartDate() && (*iterStubReset)->getStubType() == "FStubA" )
									 {
										 marketIndexA = (*iterStubReset)->getStubMarketIndex();
										 stubTenorA = (*iterStubReset)->getStubTenor();
									 }
									 else if ( (*iterStubReset)->getStartDate() == (*iterReset)->getResetStartDate() && (*iterStubReset)->getStubType() == "FStubB" )
									 {
										 marketIndexB = (*iterStubReset)->getStubMarketIndex();
										 stubTenorB = (*iterStubReset)->getStubTenor();
									 }
								  }

								 periodRate = getPeriodRate(FixingRates::getFixingRate( (*iterReset)->getQuoteDate(),
								 marketIndexA, marketIndexB, (*iterPay)->getCouponStartDate() ,
								 (*iterPay)->getCouponEndDate(), getAccrualBusDay() ));
							  }
							  else if ( getBackStubDate() != getEndDate() && (*iterPay)->getCouponStartDate() == getBackStubDate() ) // there is a back stub
							  {
								  _stubResetsList.sort();

								  StubResetsList::const_iterator iterStubReset = _stubResetsList.begin() ;
								  String marketIndexA = "";
								  String marketIndexB = "";
								  Period stubTenorA;
								  Period stubTenorB;

								  for ( ; iterStubReset != _stubResetsList.end() ; ++iterStubReset )
								  {
									  if ( (*iterStubReset)->getStartDate() == (*iterReset)->getResetStartDate() && (*iterStubReset)->getStubType() == "BStubA" )
									  {
										  marketIndexA = (*iterStubReset)->getStubMarketIndex();
										  stubTenorA = (*iterStubReset)->getStubTenor();
									  }
									  else if ( (*iterStubReset)->getStartDate() == (*iterReset)->getResetStartDate() && (*iterStubReset)->getStubType() == "BStubB" )
									  {
										  marketIndexB = (*iterStubReset)->getStubMarketIndex();
										  stubTenorB = (*iterStubReset)->getStubTenor();
									  }
								   }

								   periodRate = getPeriodRate(FixingRates::getFixingRate( (*iterReset)->getQuoteDate(), marketIndexA,
								   marketIndexB , (*iterPay)->getCouponStartDate() ,
								   (*iterPay)->getCouponEndDate(), getAccrualBusDay() ));

							  }
							  else
							  {
								  periodRate = getPeriodRate(FixingRates::getFixingRate((*iterReset)->getQuoteDate(), (*iterReset)->getResetStartDate(), getMarketIndex()));
							  }
						 }
						 else if ( ( getAccrualFreq() == getResetFreq() ) && ( (*iterPay)->getCouponStartDate() == (*iterReset)->getResetStartDate() ) )
						 {

							 if ( getFrontStubDate() != getStartDate() && (*iterPay)->getCouponEndDate() == getFrontStubDate() ) // there is a front stub
							 {
				 				_stubResetsList.sort();

				 				StubResetsList::const_iterator iterStubReset = _stubResetsList.begin() ;
				 				String marketIndexA = "";
				 				String marketIndexB = "";
				 				Period stubTenorA;
				 				Period stubTenorB;

				 				for ( ; iterStubReset != _stubResetsList.end() ; ++iterStubReset )
				 				{
				 					if ( (*iterStubReset)->getStartDate() == (*iterReset)->getResetStartDate() && (*iterStubReset)->getStubType() == "FStubA" )
				 					{
				 						marketIndexA = (*iterStubReset)->getStubMarketIndex();
				 						stubTenorA = (*iterStubReset)->getStubTenor();
				 					}
				 					else if ( (*iterStubReset)->getStartDate() == (*iterReset)->getResetStartDate() && (*iterStubReset)->getStubType() == "FStubB" )
				 					{
				 						marketIndexB = (*iterStubReset)->getStubMarketIndex();
				 						stubTenorB = (*iterStubReset)->getStubTenor();
				 					 }
				 				 }

				 				 periodRate = getPeriodRate(FixingRates::getFixingRate( (*iterReset)->getQuoteDate(), marketIndexA,
				 				 marketIndexB, (*iterPay)->getCouponStartDate() ,
				 				 (*iterPay)->getCouponEndDate(), getAccrualBusDay() ));
							  }
							 else if ( getBackStubDate() != getEndDate() && (*iterPay)->getCouponStartDate() == getBackStubDate() ) // there is a back stub
							 {
				 				_stubResetsList.sort();
					 			StubResetsList::const_iterator iterStubReset = _stubResetsList.begin() ;
					 			String marketIndexA = "";
					 			String marketIndexB = "";
					 			Period stubTenorA;
					 			Period stubTenorB;

					 			for ( ; iterStubReset != _stubResetsList.end() ; ++iterStubReset )
						 		{
					 				if ( (*iterStubReset)->getStartDate() == (*iterReset)->getResetStartDate() && (*iterStubReset)->getStubType() == "BStubA" )
					 				{
					 					marketIndexA = (*iterStubReset)->getStubMarketIndex();
					 					stubTenorA = (*iterStubReset)->getStubTenor();
					 				}
					 				else if ( ( *iterStubReset)->getStartDate() == (*iterReset)->getResetStartDate() && (*iterStubReset)->getStubType() == "BStubB" )
					 				{
					 					marketIndexB = (*iterStubReset)->getStubMarketIndex();
					 					stubTenorB = (*iterStubReset)->getStubTenor();
					 				}
						 		 }

					 			 periodRate = getPeriodRate(FixingRates::getFixingRate( (*iterReset)->getQuoteDate(), marketIndexA,
				 				 marketIndexB , (*iterPay)->getCouponStartDate() ,
				 				 (*iterPay)->getCouponEndDate() , getAccrualBusDay() ));
							 }
							 else
							 {
								 periodRate = getPeriodRate(FixingRates::getFixingRate((*iterReset)->getQuoteDate(),(*iterReset)->getResetStartDate(), getMarketIndex() ));
							 }
						 }
						 }
					 }
				 } // float check finished
				 else
					 periodRate = getFixedQuote() / 100;


		dcfNot = getNotional() * getDayCount()->getFraction((*iterComp)->getCompStartDate(),
								(*iterComp)->getCompEndDate(), finalPeriod,stubPeriod,(int) getCompFreq() ) * periodRate;

		if ( getAmortType() != "NONE" )
		{

			dcfNot = 0.0;
			double spAmortAmount = 0.0;
			double spreadAmortAmount = 0.0;

			//displayAmortSchedule().reverse();
			AmortScheduleList::const_iterator iterAmort = displayAmortSchedule().begin();

		if ( (*iterComp)->getCompStartDate() <= getAmortEndDate() )
		{

			for ( ; iterAmort != displayAmortSchedule().end() ; ++iterAmort )
			{

				if (  ( (*iterComp)->getCompStartDate() >= (*iterAmort)->getStartDate()  &&
				 		(*iterComp)->getCompStartDate() < (*iterAmort)->getEndDate()  &&
						(*iterComp)->getCompEndDate() >= (*iterAmort)->getEndDate()  ) )
				{

					//logFile << "start AMORT:end AMORT : " << (*iterAmort)->getStartDate() << " : " << (*iterAmort)->getEndDate() << endl;

					if ( amortStubDate > (*iterAmort)->getStartDate() )
					{

						dcfNot += ((*iterAmort)->getAmortNotional()) * getDayCount()->getFraction( amortStubDate,
					     	         (*iterAmort)->getEndDate(), finalPeriod,stubPeriod,(int) getAmortFreq() ) * periodRate;

						spAmortAmount =  (*iterAmort)->getAmortNotional() * getDayCount()->getFraction(amortStubDate,
								(*iterAmort)->getEndDate(), finalPeriod,stubPeriod,(int) getAmortFreq() ) * getSpread()/10000 ;

	    	 		if ( getCompoundingConv() == "ADJ/FLAT" && compAmount != 0.0 )
	    	 		{

	    	 			spAmortAmount = spAmortAmount + spreadAmount * periodRate * getDayCount()->getFraction(amortStubDate,
	    	 					(*iterAmort)->getEndDate(), finalPeriod,stubPeriod, (int) getAmortFreq() );

	    	 		}

	    	 		if ( getCompoundingConv() == "ADJ/ADJ" && compAmount != 0.0 )
	   	 			{

	    	 			spAmortAmount = spAmortAmount + spreadAmount * (periodRate + getSpread()/10000) * getDayCount()->getFraction(amortStubDate,
	    	 					(*iterAmort)->getEndDate(), finalPeriod,stubPeriod, (int) getAmortFreq() );

		    	 	 }

	    	 		spreadAmortAmount += spAmortAmount;

						lastAmortNotional = (*iterAmort)->getAmortNotional();
						logFile << "Notional 1 is : " << lastAmortNotional << endl;
					}
					else
					{
						dcfNot += ( (*iterAmort)->getAmortNotional())  * getDayCount()->getFraction((*iterAmort)->getStartDate(),
					 		         (*iterAmort)->getEndDate(), finalPeriod,stubPeriod, (int) getAmortFreq()) * periodRate;

						logFile << " Period Rate is : " << periodRate << endl;

						spAmortAmount =  (*iterAmort)->getAmortNotional() * getDayCount()->getFraction((*iterAmort)->getStartDate(),
														(*iterAmort)->getEndDate(), finalPeriod,stubPeriod, (int) getAmortFreq() ) * getSpread()/10000 ;

						if ( getCompoundingConv() == "ADJ/FLAT" && compAmount != 0.0 )
						{

							 spAmortAmount = spAmortAmount + spreadAmount * periodRate * getDayCount()->getFraction((*iterAmort)->getStartDate(),
							    	 		(*iterAmort)->getEndDate(), finalPeriod,stubPeriod, (int) getAmortFreq() );

						}

						if ( getCompoundingConv() == "ADJ/ADJ" && compAmount != 0.0 )
						{

							  spAmortAmount = spAmortAmount + spreadAmount * (periodRate + getSpread()/10000) * getDayCount()->getFraction((*iterAmort)->getStartDate(),
							    	 		(*iterAmort)->getEndDate(), finalPeriod,stubPeriod, (int) getAmortFreq() );

						}

						spreadAmortAmount += spAmortAmount;


						lastAmortNotional = (*iterAmort)->getAmortNotional();
						logFile << "Notional 11 is : " << lastAmortNotional << " : " << spAmortAmount << endl;
					}

				 	logFile << "Payment Amount 1: " << (*iterComp)->getCompStartDate() << " : " << (*iterComp)->getCompEndDate()
			 		 << " : " << (*iterAmort)->getStartDate() << " : " << amortStubDate << " : " << (*iterAmort)->getEndDate()
			 		 << " : " << dcfNot << endl;
				 //	logFile << "Payment Amount spread 1: " << spreadAmortAmount <<endl;

				 	amortStubDate = (*iterAmort)->getEndDate();
					logFile << "Notional 1 is : " << lastAmortNotional << endl;
				 }
				 else if ( (*iterComp)->getCompEndDate() > (*iterAmort)->getStartDate() &&
				 		 amortStubDate <= (*iterAmort)->getStartDate() )
				 {
				 	if ( (*iterComp)->getCompEndDate() >= (*iterAmort)->getEndDate() )
				 	{
				 		if ( (*iterAmort)->getStartDate() == getAmortEndDate() )
				 		{
				 			dcfNot += ( (*iterAmort)->getAmortNotional() ) * getDayCount()->getFraction((*iterAmort)->getStartDate(),
				 					(*iterComp)->getCompEndDate(), finalPeriod,stubPeriod, (int) getAmortFreq() ) * periodRate;

				 			spAmortAmount =  (*iterAmort)->getAmortNotional() * getDayCount()->getFraction((*iterAmort)->getStartDate(),
				 					(*iterComp)->getCompEndDate(), finalPeriod,stubPeriod, (int) getAmortFreq() ) * getSpread()/10000 ;

				 			if ( getCompoundingConv() == "ADJ/FLAT" && compAmount != 0.0 )
				 			{

				 				spAmortAmount = spAmortAmount + spreadAmount * periodRate * getDayCount()->getFraction((*iterAmort)->getStartDate(),
				 						(*iterComp)->getCompEndDate()  , finalPeriod,stubPeriod, (int) getAmortFreq() );

				 			}

				 			if ( getCompoundingConv() == "ADJ/ADJ" && compAmount != 0.0 )
				 			{

				 				 spAmortAmount = spAmortAmount + spreadAmount * (periodRate + getSpread()/10000) * getDayCount()->getFraction((*iterAmort)->getStartDate(),
				 						(*iterComp)->getCompEndDate(), finalPeriod,stubPeriod, (int) getAmortFreq() );

				 			}

				 			spreadAmortAmount += spAmortAmount;

				 			amortStubDate = (*iterComp)->getCompEndDate();
					 		lastAmortNotional = (*iterAmort)->getAmortNotional();

					 		logFile << "Payment Amount stub 1: " << (*iterComp)->getCompStartDate() << " : " << (*iterComp)->getCompEndDate()
				 				<< " : " << (*iterAmort)->getStartDate() << " : " << (*iterComp)->getCompEndDate() << " : " << dcfNot << endl;
					 		logFile << "Payment Amount stub spread 1: " << spreadAmortAmount <<endl;
					 		logFile << "Notional 2 is : " << lastAmortNotional << endl;
						}
						else if ( amortStubDate >= (*iterAmort)->getStartDate() )
						{
							dcfNot += ( (*iterAmort)->getAmortNotional() ) * getDayCount()->getFraction((*iterAmort)->getStartDate(),
									 (*iterAmort)->getEndDate(), finalPeriod,stubPeriod, (int) getAmortFreq() ) * periodRate;

							spAmortAmount =  (*iterAmort)->getAmortNotional() * getDayCount()->getFraction((*iterAmort)->getStartDate(),
									(*iterAmort)->getEndDate(), finalPeriod,stubPeriod, (int) getAmortFreq() ) * getSpread()/10000 ;

							if ( getCompoundingConv() == "ADJ/FLAT" && compAmount != 0.0 )
							{

								spAmortAmount = spAmortAmount + spreadAmount * periodRate * getDayCount()->getFraction((*iterAmort)->getStartDate(),
										(*iterAmort)->getEndDate() , finalPeriod,stubPeriod, (int) getAmortFreq() );

								logFile << " amount is : " << spAmortAmount << endl;

							}

							if ( getCompoundingConv() == "ADJ/ADJ" && compAmount != 0.0 )
							{

								spAmortAmount = spAmortAmount + spreadAmount * (periodRate + getSpread()/10000) * getDayCount()->getFraction((*iterAmort)->getStartDate(),
										(*iterAmort)->getEndDate(), finalPeriod,stubPeriod, (int) getAmortFreq() );

							}

							spreadAmortAmount += spAmortAmount;

							amortStubDate = (*iterAmort)->getEndDate();
							lastAmortNotional = (*iterAmort)->getAmortNotional();

							logFile << "Payment Amount stub 2: " << (*iterComp)->getCompStartDate() << " : " << (*iterComp)->getCompEndDate()
								<< " : " << (*iterAmort)->getStartDate() << " : " << (*iterAmort)->getEndDate() << " : " <<  dcfNot << endl;
							logFile << "Payment Amount stub spread 2: " << spreadAmortAmount <<endl;
					 		logFile << "Notional 3 is : " << lastAmortNotional << endl;
					 	}
					  }
					  else
					  {
					 		dcfNot += ( (*iterAmort)->getAmortNotional() ) * getDayCount()->getFraction((*iterAmort)->getStartDate(),
					 			(*iterComp)->getCompEndDate(), finalPeriod,stubPeriod, (int) getAmortFreq() ) * periodRate;

					 		spAmortAmount =  (*iterAmort)->getAmortNotional() * getDayCount()->getFraction((*iterAmort)->getStartDate(),
					 				(*iterComp)->getCompEndDate(), finalPeriod,stubPeriod, (int) getAmortFreq() ) * getSpread()/10000 ;

					 		if ( getCompoundingConv() == "ADJ/FLAT" && compAmount != 0.0 )
					 		{

					 				spAmortAmount = spAmortAmount + spreadAmount * periodRate * getDayCount()->getFraction((*iterAmort)->getStartDate(),
					 						(*iterComp)->getCompEndDate(), finalPeriod,stubPeriod, (int) getAmortFreq() );

					 		}

					 		if ( getCompoundingConv() == "ADJ/ADJ" && compAmount != 0.0 )
					 		{

					 				spAmortAmount = spAmortAmount + spreadAmount * (periodRate + getSpread()/10000) * getDayCount()->getFraction((*iterAmort)->getStartDate(),
					 						(*iterComp)->getCompEndDate(), finalPeriod,stubPeriod, (int) getAmortFreq() );

					 		}

					 		spreadAmortAmount += spAmortAmount;

					 		amortStubDate = (*iterComp)->getCompEndDate();
					 		lastAmortNotional = (*iterAmort)->getAmortNotional();

						    logFile << "Payment Amount stub 3: " << (*iterComp)->getCompStartDate() << " : " << (*iterComp)->getCompEndDate()
						 		 << " : " << (*iterAmort)->getStartDate() << " : " << (*iterAmort)->getEndDate() << " : " << dcfNot << endl;
						    logFile << "Payment Amount stub spread 3: " << spreadAmortAmount <<endl;
						 	logFile << "Notional 4 is : " << lastAmortNotional << endl;
					   }
				}
			 } // amort event


			if ( (*iterPay)->getCouponStartDate() <= (*iterComp)->getCompStartDate() &&
					 (*iterPay)->getCouponEndDate() >= (*iterComp)->getCompEndDate() )
			{
				// logFile << "coupon before : " << compAmount << endl;


				 if ( getCompoundingConv() == "FLAT/FLAT")
				 {
				 	   (*iterComp)->setAccrualInterest(dcfNot + (compAmount * getDayCount()->getFraction((*iterComp)->getCompStartDate(),
				 	    	 			(*iterComp)->getCompEndDate(), finalPeriod,stubPeriod, (int) getCompFreq() ) * periodRate ) );

				 	   if (  (*iterComp)->getCompStartDate() == (*iterPay)->getCouponStartDate() )
				 	   {
				 		   (*iterPay)->setNotional(lastAmortNotional);
				 		  (*iterPay)->setPeriodRate(periodRate);

				 	   }

				 	  (*iterComp)->setNotional(lastAmortNotional);
				 	 (*iterComp)->setAccrualRate( periodRate);

				 	   logFile << "current coupon amount : " << dcfNot + (compAmount * getDayCount()->getFraction((*iterComp)->getCompStartDate(),
				 	    	 					 			(*iterComp)->getCompEndDate(), finalPeriod,stubPeriod, (int) getCompFreq() ) * periodRate ) + spreadAmortAmount << endl;

				 	   compAmount = compAmount + dcfNot + (compAmount * getDayCount()->getFraction((*iterComp)->getCompStartDate(),
				 	    	 		    	 (*iterComp)->getCompEndDate(), finalPeriod,stubPeriod, (int) getCompFreq() ) * periodRate );

				 }
				 else if ( getCompoundingConv() == "ADJ/ADJ" )
				 {
				 	  (*iterComp)->setAccrualInterest(dcfNot + (compAmount * getDayCount()->getFraction((*iterComp)->getCompStartDate(),
				 	    	 		    	 	(*iterComp)->getCompEndDate(), finalPeriod,stubPeriod, (int) getCompFreq() ) * periodRate ));

				 	 if ( (*iterComp)->getCompStartDate() == (*iterPay)->getCouponStartDate() )
				 		{
				 		   (*iterPay)->setNotional(lastAmortNotional);
				 		  (*iterPay)->setPeriodRate(periodRate);
				 		}

				 	 (*iterComp)->setNotional(lastAmortNotional);
				 	(*iterComp)->setAccrualRate( periodRate);

				 	   logFile << "current coupon amount : " << dcfNot + (compAmount * getDayCount()->getFraction((*iterComp)->getCompStartDate(),
				 	    	 		    	 	(*iterComp)->getCompEndDate(), finalPeriod,stubPeriod,(int) getCompFreq()) * periodRate )  << endl;

				 	    compAmount = compAmount + dcfNot + (compAmount * getDayCount()->getFraction((*iterComp)->getCompStartDate(),
				 	    	 		    	 			 	(*iterComp)->getCompEndDate(), finalPeriod,stubPeriod, (int) getCompFreq() ) * periodRate );

				 }
				 else if ( getCompoundingConv() == "FLAT/ADJ" )
				 {
				 	  (*iterComp)->setAccrualInterest(dcfNot + (compAmount  * getDayCount()->getFraction((*iterComp)->getCompStartDate(),
				 	    	   	 	(*iterComp)->getCompEndDate(), finalPeriod,stubPeriod, (int) getCompFreq() ) * ( periodRate + getSpread()/10000 ) ) + spreadAmortAmount);

				 	 if ( (*iterComp)->getCompStartDate() == (*iterPay)->getCouponStartDate() )
				 	   {
				 		 (*iterPay)->setNotional(lastAmortNotional);
				 		(*iterPay)->setPeriodRate(periodRate);
				 		}

				 	 (*iterComp)->setNotional(lastAmortNotional);
				 	(*iterComp)->setAccrualRate( periodRate );

				 	   logFile << "current coupon amount : " << dcfNot + (compAmount * getDayCount()->getFraction((*iterComp)->getCompStartDate(),
				 	    	 	    	 (*iterComp)->getCompEndDate(), finalPeriod,stubPeriod, (int) getCompFreq() ) * ( periodRate + getSpread()/10000 ) ) + spreadAmortAmount << endl;

				 	   compAmount = compAmount + dcfNot + (compAmount * getDayCount()->getFraction((*iterComp)->getCompStartDate(),
				 	    	   	 			 (*iterComp)->getCompEndDate(), finalPeriod,stubPeriod, (int) getCompFreq() ) * ( periodRate + getSpread()/10000));

				 }
				 else if ( getCompoundingConv() == "ADJ/FLAT" )
				 {

				 	   (*iterComp)->setAccrualInterest(dcfNot + (compAmount  * getDayCount()->getFraction((*iterComp)->getCompStartDate(),
				 	    	     	 			(*iterComp)->getCompEndDate(), finalPeriod,stubPeriod, (int) getCompFreq() ) * periodRate) + spreadAmortAmount);

				 	  if ( (*iterComp)->getCompStartDate() == (*iterPay)->getCouponStartDate() )
				 	 	{
				 	 	   (*iterPay)->setNotional(lastAmortNotional);
				 	 	 (*iterPay)->setPeriodRate(periodRate);
				 	 	}

				 	  (*iterComp)->setNotional(lastAmortNotional);
				 	 (*iterComp)->setAccrualRate( periodRate);

				 	    logFile << "current coupon amount adj flat : " << dcfNot + ( compAmount  * getDayCount()->getFraction((*iterComp)->getCompStartDate(),
				 	    	 		    	 	(*iterComp)->getCompEndDate(), finalPeriod,stubPeriod, (int) getCompFreq() ) * periodRate ) + spreadAmortAmount  << endl;


				 	    compAmount = compAmount + dcfNot + ( compAmount  * getDayCount()->getFraction((*iterComp)->getCompStartDate(),
				 	    	     	 			 (*iterComp)->getCompEndDate(), finalPeriod,stubPeriod, (int) getCompFreq() ) * periodRate ) ;

				 }

				 spreadAmount += spreadAmortAmount;

				 //logFile << "total SPREAD Amount : " << spreadAmount  << endl;

				 if ( getCompoundingConv() != "FLAT/FLAT"
				 	    	&& getCompoundingConv() != "ADJ/FLAT" && getCompoundingConv() != "FLAT/ADJ" )
				 {
					 (*iterPay)->setAmount(compAmount);
					 //(*iterPay)->setNotional(lastAmortNotional);
				 	   logFile << "total coupon Amount 1: " << compAmount  << endl;
				 }
				 else
				 {
					 (*iterPay)->setAmount(compAmount + spreadAmount );
					 //(*iterPay)->setNotional(lastAmortNotional);
				 	   logFile << "total coupon Amount 2: " << compAmount + spreadAmount << endl;
				 }

			 }

			 	 logFile << "Payment Amount 2 : " << (*iterComp)->getCompStartDate() << " : " << (*iterComp)->getCompEndDate() << " : "
					 << (*iterComp)->getAccrualInterest()  << endl;

		}
		else
		{
			logFile << "Notional final is : " << lastAmortNotional << endl;
			dcfNot = lastAmortNotional * getDayCount()->getFraction((*iterComp)->getCompStartDate(),
					(*iterComp)->getCompEndDate(), finalPeriod,stubPeriod, (int) getCompFreq() ) * periodRate;

			spAmortAmount =  lastAmortNotional * getDayCount()->getFraction((*iterComp)->getCompStartDate(),
					(*iterComp)->getCompEndDate(), finalPeriod,stubPeriod, (int) getCompFreq() ) * getSpread()/10000 ;


			if ( getCompoundingConv() == "ADJ/FLAT" && compAmount != 0.0 )
			{

				spAmortAmount = spAmortAmount + spreadAmount * periodRate * getDayCount()->getFraction((*iterComp)->getCompStartDate(),
						(*iterComp)->getCompEndDate(), finalPeriod,stubPeriod, (int) getCompFreq() );

			}

			if ( getCompoundingConv() == "ADJ/ADJ" && compAmount != 0.0 )
			{

				spAmortAmount = spAmortAmount + spreadAmount * (periodRate + getSpread()/10000) * getDayCount()->getFraction((*iterComp)->getCompStartDate(),
						(*iterComp)->getCompEndDate(), finalPeriod,stubPeriod, (int) getCompFreq() );

			}

			spreadAmortAmount += spAmortAmount;


			if ( (*iterPay)->getCouponStartDate() <= (*iterComp)->getCompStartDate() &&
					 (*iterPay)->getCouponEndDate() >= (*iterComp)->getCompEndDate() )
			{
				 //logFile << "coupon before : " << compAmount << endl;

				 if ( getCompoundingConv() == "FLAT/FLAT")
				{
					(*iterComp)->setAccrualInterest(dcfNot + (compAmount * getDayCount()->getFraction((*iterComp)->getCompStartDate(),
							 	    	 	(*iterComp)->getCompEndDate(), finalPeriod,stubPeriod, (int) getCompFreq() ) * periodRate ) );


					 if ( (*iterComp)->getCompStartDate() == (*iterPay)->getCouponStartDate() )
					   {
						   (*iterPay)->setNotional(lastAmortNotional);
						   (*iterPay)->setPeriodRate(periodRate);
					   }

					(*iterComp)->setNotional(lastAmortNotional);
					(*iterComp)->setAccrualRate( periodRate);


					logFile << "current coupon amount : " << dcfNot + (compAmount * getDayCount()->getFraction((*iterComp)->getCompStartDate(),
							 	    	 				(*iterComp)->getCompEndDate(), finalPeriod,stubPeriod, (int) getCompFreq() ) * periodRate ) + spreadAmortAmount << endl;

					compAmount = compAmount + dcfNot + (compAmount * getDayCount()->getFraction((*iterComp)->getCompStartDate(),
							 	    	 		    	 (*iterComp)->getCompEndDate(), finalPeriod,stubPeriod, (int) getCompFreq() ) * periodRate );

				}
				else if ( getCompoundingConv() == "ADJ/ADJ" )
				{
					(*iterComp)->setAccrualInterest(dcfNot + (compAmount * getDayCount()->getFraction((*iterComp)->getCompStartDate(),
							 	    	 		   (*iterComp)->getCompEndDate(), finalPeriod,stubPeriod, (int) getCompFreq() ) * periodRate ));

					 if ( (*iterComp)->getCompStartDate() == (*iterPay)->getCouponStartDate() )
					   {
						 (*iterPay)->setNotional(lastAmortNotional);
						 (*iterPay)->setPeriodRate(periodRate);
						}

					(*iterComp)->setNotional(lastAmortNotional);
					(*iterComp)->setAccrualRate( periodRate);

					logFile << "current coupon amount : " << dcfNot + (compAmount * getDayCount()->getFraction((*iterComp)->getCompStartDate(),
							 	    	 		    	 	(*iterComp)->getCompEndDate(), finalPeriod,stubPeriod, (int) getCompFreq() ) * periodRate )  << endl;

					compAmount = compAmount + dcfNot + (compAmount * getDayCount()->getFraction((*iterComp)->getCompStartDate(),
							 	    	 		    	 			 	(*iterComp)->getCompEndDate(), finalPeriod,stubPeriod, (int) getCompFreq() ) * periodRate );

				}
				else if ( getCompoundingConv() == "FLAT/ADJ" )
				{
					(*iterComp)->setAccrualInterest(dcfNot + (compAmount  * getDayCount()->getFraction((*iterComp)->getCompStartDate(),
							 	    	(*iterComp)->getCompEndDate(), finalPeriod,stubPeriod, (int) getCompFreq() ) * ( periodRate + getSpread()/10000 ) ) + spreadAmortAmount);

					 if ( (*iterComp)->getCompStartDate() == (*iterPay)->getCouponStartDate() )
					   {
						   (*iterPay)->setNotional(lastAmortNotional);
						   (*iterPay)->setPeriodRate(periodRate);
					   }

					(*iterComp)->setNotional(lastAmortNotional);
					(*iterComp)->setAccrualRate( periodRate);

					logFile << "current coupon amount : " << dcfNot + (compAmount * getDayCount()->getFraction((*iterComp)->getCompStartDate(),
							 	    	 (*iterComp)->getCompEndDate(), finalPeriod,stubPeriod, (int) getCompFreq() ) * ( periodRate + getSpread()/10000 ) ) + spreadAmortAmount << endl;

					compAmount = compAmount + dcfNot + (compAmount * getDayCount()->getFraction((*iterComp)->getCompStartDate(),
							 	    	   	  (*iterComp)->getCompEndDate(), finalPeriod,stubPeriod, (int) getCompFreq() ) * ( periodRate + getSpread()/10000));

				}
				else if ( getCompoundingConv() == "ADJ/FLAT" )
				{

					(*iterComp)->setAccrualInterest(dcfNot + (compAmount  * getDayCount()->getFraction((*iterComp)->getCompStartDate(),
							 	    	     	 (*iterComp)->getCompEndDate(), finalPeriod,stubPeriod, (int) getCompFreq() ) * periodRate) + spreadAmortAmount);

					 if ( (*iterComp)->getCompStartDate() == (*iterPay)->getCouponStartDate() )
					   {
						 (*iterPay)->setNotional(lastAmortNotional);
						 (*iterPay)->setPeriodRate(periodRate);
						}

					(*iterComp)->setNotional(lastAmortNotional);
					(*iterComp)->setAccrualRate( periodRate);

					logFile << "current coupon amount : " << dcfNot + ( compAmount  * getDayCount()->getFraction((*iterComp)->getCompStartDate(),
							 	    	 		  (*iterComp)->getCompEndDate(), finalPeriod,stubPeriod, (int) getCompFreq() ) * periodRate ) + spreadAmortAmount  << endl;

					compAmount = compAmount + dcfNot + ( compAmount  * getDayCount()->getFraction((*iterComp)->getCompStartDate(),
							 	    	     	 (*iterComp)->getCompEndDate(), finalPeriod,stubPeriod, (int) getCompFreq() ) * periodRate ) ;

				}

				spreadAmount += spreadAmortAmount;

				//logFile << "total SPREAD Amount : " << spreadAmount  << endl;

				if ( getCompoundingConv() != "FLAT/FLAT"
							 	&& getCompoundingConv() != "ADJ/FLAT" && getCompoundingConv() != "FLAT/ADJ" )
				{
					(*iterPay)->setAmount(compAmount);
					//(*iterPay)->setNotional(lastAmortNotional);
					logFile << "total coupon Amount 1: " << compAmount  << endl;\
				}
				else
				{
					(*iterPay)->setAmount(compAmount + spreadAmount );
					//(*iterPay)->setNotional(lastAmortNotional);
					logFile << "total coupon Amount 2: " << compAmount + spreadAmount << endl;
				}


			  }


				logFile << "Payment Amount outside amort : " << (*iterComp)->getCompStartDate() << " : " << (*iterComp)->getCompEndDate()
						<< " : " << lastAmortNotional << ": " << (*iterComp)->getAccrualInterest() << ":" <<
						"PrincipalAmount is : "  << endl;


		 }
	} // AMORT FINISHED
	else
	{

	    if ( (*iterPay)->getCouponStartDate() <= (*iterComp)->getCompStartDate() &&
	    			(*iterPay)->getCouponEndDate() >= (*iterComp)->getCompEndDate() )
	    {
	     		//logFile << "coupon before : period rate " << compAmount << " : " << periodRate << endl;
    	 		//logFile << "Spread amount " << " : " << getNotional() * getDayCount()->getFraction((*iterComp)->getCompStartDate(),
    	 					 			//(*iterComp)->getCompEndDate(), finalPeriod,stubPeriod, (int) getCompFreq() ) * getSpread()/10000 << endl;

    	 		double spAmount = getNotional() * getDayCount()->getFraction((*iterComp)->getCompStartDate(),
				 			(*iterComp)->getCompEndDate(), finalPeriod,stubPeriod, (int) getCompFreq() ) * getSpread()/10000 ;

    	 		if ( getCompoundingConv() == "ADJ/FLAT" && compAmount != 0.0 )
    	 		{

    	 			spAmount = spAmount + spreadAmount * periodRate * getDayCount()->getFraction((*iterComp)->getCompStartDate(),
				 			(*iterComp)->getCompEndDate(), finalPeriod,stubPeriod, (int) getCompFreq() );

    	 		}

    	 		if ( getCompoundingConv() == "ADJ/ADJ" && compAmount != 0.0 )
   	 			{

    	 			spAmount = spAmount + spreadAmount * (periodRate + getSpread()/10000) * getDayCount()->getFraction((*iterComp)->getCompStartDate(),
	    	 				 (*iterComp)->getCompEndDate(), finalPeriod,stubPeriod, (int) getCompFreq() );

	    	 	 }


	    	 	if ( getCompoundingConv() == "FLAT/FLAT")
	    	 	{
	    	 		(*iterComp)->setAccrualInterest(dcfNot + (compAmount * getDayCount()->getFraction((*iterComp)->getCompStartDate(),
	    	 					 	(*iterComp)->getCompEndDate(), finalPeriod,stubPeriod, (int) getCompFreq() ) * periodRate ) );

	    	 		 if ( (*iterComp)->getCompStartDate() == (*iterPay)->getCouponStartDate() )
	    	 		   {
	    	 			 (*iterPay)->setNotional(lastAmortNotional);
	    	 			(*iterPay)->setPeriodRate(periodRate);
	    	 			}

	    	 		(*iterComp)->setNotional(lastAmortNotional);
	    	 		(*iterComp)->setAccrualRate( periodRate);

	    	 		logFile << "current coupon amount : " << dcfNot + (compAmount * getDayCount()->getFraction((*iterComp)->getCompStartDate(),
	    	 					 			(*iterComp)->getCompEndDate(), finalPeriod,stubPeriod, (int) getCompFreq() ) * periodRate ) + spAmount << endl;

	    	 		compAmount = compAmount + dcfNot + (compAmount * getDayCount()->getFraction((*iterComp)->getCompStartDate(),
	    	 		    	 			 	(*iterComp)->getCompEndDate(), finalPeriod,stubPeriod, (int) getCompFreq() ) * periodRate );

	    	 	}
	    	 	else if ( getCompoundingConv() == "ADJ/ADJ" )
	    	 	{
	    	 		(*iterComp)->setAccrualInterest(dcfNot + (compAmount * getDayCount()->getFraction((*iterComp)->getCompStartDate(),
	    	 		    	 					 	(*iterComp)->getCompEndDate(), finalPeriod,stubPeriod, (int) getCompFreq() ) * periodRate ));

	    	 		 if ( (*iterComp)->getCompStartDate() == (*iterPay)->getCouponStartDate() )
	    	 		   {
	    	 			   (*iterPay)->setNotional(lastAmortNotional);
	    	 			  (*iterPay)->setPeriodRate(periodRate);
	    	 		   }

	    	 		(*iterComp)->setNotional(lastAmortNotional);
	    	 		(*iterComp)->setAccrualRate( periodRate);

	    	 		logFile << "current coupon amount : " << dcfNot + (compAmount * getDayCount()->getFraction((*iterComp)->getCompStartDate(),
	    	 		    	 				(*iterComp)->getCompEndDate(), finalPeriod,stubPeriod, (int) getCompFreq() ) * periodRate )  << endl;

	    	 		compAmount = compAmount + dcfNot + (compAmount * getDayCount()->getFraction((*iterComp)->getCompStartDate(),
	    	 		    	 			 	(*iterComp)->getCompEndDate(), finalPeriod,stubPeriod, (int) getCompFreq() ) * periodRate );

	    	 	}
	    	 	else if ( getCompoundingConv() == "FLAT/ADJ" )
	    	 	{
	    	 		(*iterComp)->setAccrualInterest(dcfNot + (compAmount  * getDayCount()->getFraction((*iterComp)->getCompStartDate(),
	    	   	 					 	(*iterComp)->getCompEndDate(), finalPeriod,stubPeriod, (int) getCompFreq() ) * ( periodRate + getSpread()/10000 ) ) + spAmount);

	    	 		 if ( (*iterComp)->getCompStartDate() == (*iterPay)->getCouponStartDate() )
	    	 		   {
	    	 			 (*iterPay)->setNotional(lastAmortNotional);
	    	 			(*iterPay)->setPeriodRate(periodRate);
	    	 			}

	    	 		(*iterComp)->setNotional(lastAmortNotional);
	    	 		(*iterComp)->setAccrualRate( periodRate);

	    	 		logFile << "current coupon amount : " << dcfNot + (compAmount * getDayCount()->getFraction((*iterComp)->getCompStartDate(),
	    	 	    	 				(*iterComp)->getCompEndDate(), finalPeriod,stubPeriod, (int) getCompFreq() ) * ( periodRate + getSpread()/10000 ) ) + spAmount << endl;

	    	 		compAmount = compAmount + dcfNot + (compAmount * getDayCount()->getFraction((*iterComp)->getCompStartDate(),
	    	   	 			 			(*iterComp)->getCompEndDate(), finalPeriod,stubPeriod, (int) getCompFreq() ) * ( periodRate + getSpread()/10000));

	    	 	}
	    	 	else if ( getCompoundingConv() == "ADJ/FLAT" )
	    	 	{

	    	 		(*iterComp)->setAccrualInterest(dcfNot + (compAmount  * getDayCount()->getFraction((*iterComp)->getCompStartDate(),
	    	     	 					 	(*iterComp)->getCompEndDate(), finalPeriod,stubPeriod, (int) getCompFreq() ) * periodRate) + spAmount);

	    	 		 if ( (*iterComp)->getCompStartDate() == (*iterPay)->getCouponStartDate() )
	    	 		   {
	    	 			 (*iterPay)->setNotional(lastAmortNotional);
	    	 			(*iterPay)->setPeriodRate(periodRate);
	    	 			}

	    	 		(*iterComp)->setNotional(lastAmortNotional);
	    	 		(*iterComp)->setAccrualRate( periodRate);

	    	 		logFile << "current coupon amount : " << dcfNot + ( compAmount  * getDayCount()->getFraction((*iterComp)->getCompStartDate(),
	    	 		    	 				(*iterComp)->getCompEndDate(), finalPeriod,stubPeriod, (int) getCompFreq() ) * periodRate ) + spAmount  << endl;

	    	 		compAmount = compAmount + dcfNot + ( compAmount  * getDayCount()->getFraction((*iterComp)->getCompStartDate(),
	    	     	 			 			(*iterComp)->getCompEndDate(), finalPeriod,stubPeriod, (int) getCompFreq() ) * periodRate ) ;

	    	 	}

	    	 	spreadAmount += spAmount;

      	 	    //logFile << "total SPREAD Amount : " << spreadAmount  << endl;

	    	 	if ( getCompoundingConv() != "FLAT/FLAT"
	    	 			&& getCompoundingConv() != "ADJ/FLAT" && getCompoundingConv() != "FLAT/ADJ" )
	    	 	{
	    	 		(*iterPay)->setAmount(compAmount);
	    	 		//(*iterPay)->setNotional(lastAmortNotional);
	    	 	 	logFile << "total coupon Amount 1: " << compAmount  << endl;
	    	 	}
	    	 	else
	    	 	{
	    	 		(*iterPay)->setAmount(compAmount + spreadAmount );
	    	 		//(*iterPay)->setNotional(lastAmortNotional);
	    	 	    logFile << "total coupon Amount 2: " << compAmount + spreadAmount << endl;
	    	 	}

	    	}


		logFile << "Payment Amount not amortized : " << (*iterComp)->getCompStartDate() << " : " << (*iterComp)->getCompEndDate() << " : "
				<< (*iterComp)->getAccrualInterest()  << endl;

		}
			 }
			}
		} // COMPOUND FINISHED
		else
		{

			// check resets
			if ( isFloatLeg() )
			{
				 ResetScheduleList::const_iterator iterReset = displayResetSchedule().begin();
				 int resetCnt = 0;
				 double tmpPeriodRate = 0.0;

				 for ( ; iterReset != displayResetSchedule().end() ; ++iterReset )
				 {
					if ( (*iterReset)->getRateIndexType() == "IRRATE" )
					{

				 	if ( ( (*iterPay)->getCouponStartDate() <= (*iterReset)->getResetStartDate() &&
				 			(*iterPay)->getCouponEndDate() > (*iterReset)->getResetStartDate() &&
				 			getResetAveraging() != "NONE" )	|| ( (*iterPay)->getCouponStartDate() == (*iterReset)->getResetStartDate()
				 					&& getResetAveraging() == "NONE" ) )
				 	{

				 		if ( getFrontStubDate() != getStartDate() && (*iterPay)->getCouponEndDate() == getFrontStubDate() ) // there is a front stub
				 		{
				 			_stubResetsList.sort();

				 			StubResetsList::const_iterator iterStubReset = _stubResetsList.begin() ;
				 			String marketIndexA = "";
				 			String marketIndexB = "";
				 			Period stubTenorA;
				 			Period stubTenorB;

				 			for ( ; iterStubReset != _stubResetsList.end() ; ++iterStubReset )
				 			{
				 				if ( (*iterStubReset)->getStartDate() == (*iterReset)->getResetStartDate() && (*iterStubReset)->getStubType() == "FStubA" )
				 				{
				 					marketIndexA = (*iterStubReset)->getStubMarketIndex();
				 					stubTenorA = (*iterStubReset)->getStubTenor();
				 				}
				 				else if ( (*iterStubReset)->getStartDate() == (*iterReset)->getResetStartDate() && (*iterStubReset)->getStubType() == "FStubB" )
				 				{
				 					marketIndexB = (*iterStubReset)->getStubMarketIndex();
				 					stubTenorB = (*iterStubReset)->getStubTenor();
				 				}
				 			}

				 			   periodRate = getPeriodRate(FixingRates::getFixingRate((*iterReset)->getQuoteDate(), marketIndexA,
				 					   marketIndexB, (*iterPay)->getCouponStartDate(),
				 					   (*iterPay)->getCouponEndDate() , getAccrualBusDay()));


				 			  resetCnt++;
				 			  if ( getResetAveraging() == "WEIGHTED_CAL" )
				 			  {
				 				  tmpPeriodRate += periodRate * ( (*iterPay)->getCouponEndDate().serialNumber() - (*iterPay)->getCouponStartDate().serialNumber() );
				 				  logFile << "tmpPeriod Rate front is : " << tmpPeriodRate << endl;
				 			  }
				 			  else if ( getResetAveraging() == "WEIGHTED_BUS" )
				 			  {
				 				 DayCountConv * dayCount = DayCountConv::find("_bus360"); // just to mimic bus days
				 				 dayCount->setCalendar(getAccrualCalendars()); // always accrual
				 				 tmpPeriodRate += periodRate * ( dayCount->getDay( (*iterPay)->getCouponStartDate(), (*iterPay)->getCouponEndDate() ) );
				 			  }
				 			  else if ( getResetAveraging() == "UNWEIGHTED" )
				 			  {
				 				 tmpPeriodRate += periodRate;
				 				  logFile << "tmpPeriod Rate front is : " << tmpPeriodRate << endl;
				 			  }

				 		}
				 		else if ( getBackStubDate() != getEndDate() && (*iterPay)->getCouponStartDate() == getBackStubDate() ) // there is a back stub
				 		{
				 				_stubResetsList.sort();

				 				StubResetsList::const_iterator iterStubReset = _stubResetsList.begin() ;
				 				String marketIndexA = "";
				 				String marketIndexB = "";
				 				Period stubTenorA;
				 				Period stubTenorB;


				 			for ( ; iterStubReset != _stubResetsList.end() ; ++iterStubReset )
				 			{
				 				if ( (*iterStubReset)->getStartDate() == (*iterReset)->getResetStartDate() && (*iterStubReset)->getStubType() == "BStubA" )
				 				{
				 					marketIndexA = (*iterStubReset)->getStubMarketIndex();
				 					stubTenorA = (*iterStubReset)->getStubTenor();

				 				}
				 				else if ( (*iterStubReset)->getStartDate() == (*iterReset)->getResetStartDate() && (*iterStubReset)->getStubType() == "BStubB" )
				 				{
				 					marketIndexB = (*iterStubReset)->getStubMarketIndex();
				 					stubTenorB = (*iterStubReset)->getStubTenor();
				 				}
				 			}

				 				periodRate = getPeriodRate(FixingRates::getFixingRate( (*iterReset)->getQuoteDate(), marketIndexA,
				 						marketIndexB ,  (*iterPay)->getCouponStartDate(),
				 						(*iterPay)->getCouponEndDate(), getAccrualBusDay() ));

				 				resetCnt++;

				 				if ( getResetAveraging() == "WEIGHTED_CAL" )
				 				{
				 				  tmpPeriodRate += periodRate * ( (*iterPay)->getCouponEndDate().serialNumber() - (*iterPay)->getCouponStartDate().serialNumber() );
				 				  logFile << "tmpPeriod Rate front is : " << tmpPeriodRate << endl;
				 				}
				 				else if ( getResetAveraging() == "WEIGHTED_BUS" )
				 				{
				 					DayCountConv * dayCount = DayCountConv::find("_bus360"); // just to mimic bus days
				 					dayCount->setCalendar(getAccrualCalendars()); // always accrual
				 					tmpPeriodRate += periodRate * ( dayCount->getDay( (*iterPay)->getCouponStartDate(), (*iterPay)->getCouponEndDate() ) );
				 				}
				 				else if ( getResetAveraging() == "UNWEIGHTED" )
				 				{
				 				  tmpPeriodRate += periodRate;
				 				  logFile << "tmpPeriod Rate front is : " << tmpPeriodRate << endl;
				 				}

				 		}
				 		else
				 		{
				 				periodRate = getPeriodRate(FixingRates::getFixingRate((*iterReset)->getQuoteDate(), (*iterReset)->getResetStartDate(),getMarketIndex()));
				 				resetCnt++;

				 				if ( getResetAveraging() == "WEIGHTED_CAL" )
				 				{
				 					tmpPeriodRate += periodRate * ( (*(++iterReset))->getResetStartDate().serialNumber() - (*(--iterReset))->getResetStartDate().serialNumber()) ;
				 					logFile << "tmpPeriod Rate back is : " << tmpPeriodRate << endl;
				 				}
				 				else if ( getResetAveraging() == "WEIGHTED_BUS" )
				 				{
				 					DayCountConv * dayCount = DayCountConv::find("_bus360"); // just to mimic bus days
				 					dayCount->setCalendar(getAccrualCalendars()); // always accrual
				 					tmpPeriodRate += periodRate * ( dayCount->getDay( (*(--iterReset))->getResetStartDate() , (*(++iterReset))->getResetStartDate() ) );
				 				}
				 				else if ( getResetAveraging() == "UNWEIGHTED" )
				 				{
				 				    tmpPeriodRate += periodRate;
				 					logFile << "tmpPeriod Rate back is : " << tmpPeriodRate << endl;
				 				}
				 		}

				 	}
				}
			  }

				 if ( getResetAveraging() == "WEIGHTED_CAL" )
					 periodRate = tmpPeriodRate/( (*iterPay)->getCouponEndDate().serialNumber() - (*iterPay)->getCouponStartDate().serialNumber() );
				 else if ( getResetAveraging() == "WEIGHTED_BUS" )
				 {
				 	DayCountConv * dayCount = DayCountConv::find("_bus360"); // just to mimic bus days
				 	dayCount->setCalendar(getAccrualCalendars()); // always accrual
				 	periodRate = tmpPeriodRate / ( dayCount->getDay( (*iterPay)->getCouponStartDate(), (*iterPay)->getCouponEndDate() ) );
				 }
				 else if ( getResetAveraging() == "UNWEIGHTED" )
					 periodRate = tmpPeriodRate / resetCnt;

				 logFile << "ultimate period rate is : " << periodRate << endl;
			}
			else
				periodRate = getFixedQuote() / 100;


			if ( isFXReset() && isFloatLeg() )
			{
				displayAmortSchedule().sort();
				AmortScheduleList::const_iterator iterFXAmort = displayAmortSchedule().begin();

				for ( ; iterFXAmort != displayAmortSchedule().end() ; ++iterFXAmort )
				{
					if ( (*iterPay)->getCouponStartDate() == ((*iterFXAmort)->getStartDate() ) )
					{
						logFile << "Amort Notional is : " << (*iterFXAmort)->getAmortNotional() << endl;

						lastAmortNotional = (*iterFXAmort)->getAmortNotional();

						dcfNot = (*iterFXAmort)->getAmortNotional() * getDayCount()->getFraction((*iterPay)->getCouponStartDate(),
				 							 		(*iterPay)->getCouponEndDate(), finalPeriod,stubPeriod, (int) getAccrualFreq() );
					}
				}
			}
			else
			{

				dcfNot = getNotional() * getDayCount()->getFraction((*iterPay)->getCouponStartDate(),
								 			(*iterPay)->getCouponEndDate(), finalPeriod,stubPeriod, (int) getAccrualFreq() );

				logFile << " dcf Notional is : " << dcfNot << endl;

			}


		if ( getAmortType() != "NONE" )
		{

			dcfNot = 0.0;
			//displayAmortSchedule().sort();
			AmortScheduleList::const_iterator iterAmort = displayAmortSchedule().begin();

			if ( (*iterPay)->getCouponStartDate() <= getAmortEndDate() )
			{
				 for ( ; iterAmort != displayAmortSchedule().end() ; ++iterAmort )
				 {
					logFile << "Amort Dates: " << (*iterAmort)->getStartDate() << " : " << (*iterAmort)->getEndDate() << endl;

				 if (  ( (*iterPay)->getCouponStartDate() >= (*iterAmort)->getStartDate()  &&
				 		 (*iterPay)->getCouponStartDate() < (*iterAmort)->getEndDate()  &&
				 		(*iterPay)->getCouponEndDate() >= (*iterAmort)->getEndDate()  ) )
				 	{
				 		if ( amortStubDate > (*iterAmort)->getStartDate() )
				 		{
				 			dcfNot += (*iterAmort)->getAmortNotional() * getDayCount()->getFraction( amortStubDate,
				 							 		 		         (*iterAmort)->getEndDate(), finalPeriod,stubPeriod, (int) getAmortFreq() ) * periodRate;

				 			lastAmortNotional = (*iterAmort)->getAmortNotional();
				 			logFile << "Notional 1-1 is : " << lastAmortNotional << endl;
				 		}
				 		else
				 		{
				 			dcfNot += (*iterAmort)->getAmortNotional() * getDayCount()->getFraction((*iterAmort)->getStartDate(),
				 							 		(*iterAmort)->getEndDate(), finalPeriod,stubPeriod, (int) getAmortFreq() ) * periodRate;

				 			lastAmortNotional = (*iterAmort)->getAmortNotional();
				 			logFile << "Notional 11 is : " << lastAmortNotional << endl;
				 		}


				 		logFile << "Payment Amount 1: " << (*iterPay)->getCouponStartDate() << " : " << (*iterPay)->getCouponEndDate()
				 				 << " : " << (*iterAmort)->getStartDate() << " : " << amortStubDate << " : " << (*iterAmort)->getEndDate() << " : " <<  dcfNot << endl;
				 		amortStubDate = (*iterAmort)->getEndDate();
				 		logFile << "Notional 1 is : " << lastAmortNotional << endl;
				 		logFile << "Period rate 1 is : " << periodRate << endl;
				 	}
				 	else if ( (*iterPay)->getCouponEndDate() > (*iterAmort)->getStartDate() &&
				 			 amortStubDate <= (*iterAmort)->getStartDate() )
				 	{
				 		if ( (*iterPay)->getCouponEndDate() >= (*iterAmort)->getEndDate() )
				 		{
				 			if ( (*iterAmort)->getStartDate() == getAmortEndDate() )
				 			{
				 				dcfNot += (*iterAmort)->getAmortNotional() * getDayCount()->getFraction((*iterAmort)->getStartDate(),
				 						(*iterPay)->getCouponEndDate(), finalPeriod,stubPeriod,  (int) getAmortFreq() ) * periodRate;

				 				amortStubDate = (*iterPay)->getCouponEndDate();
				 				lastAmortNotional = (*iterAmort)->getAmortNotional();

				 				logFile << "Payment Amount stub 1: " << (*iterPay)->getCouponStartDate() << " : " << (*iterPay)->getCouponEndDate()
				 					<< " : " << (*iterAmort)->getStartDate() << " : " << (*iterPay)->getCouponEndDate() << " : " <<  dcfNot << endl;
				 				logFile << "Period rate is 0: " << periodRate << endl;
				 				logFile << "Notional 2 is : " << lastAmortNotional << endl;

				 			}
				 			else
				 			{
				 				dcfNot += (*iterAmort)->getAmortNotional() * getDayCount()->getFraction((*iterAmort)->getStartDate(),
				 						 (*iterAmort)->getEndDate(), finalPeriod,stubPeriod,  (int) getAmortFreq() ) * periodRate;

				 				amortStubDate = (*iterAmort)->getEndDate();
				 				lastAmortNotional = (*iterAmort)->getAmortNotional();

				 				logFile << "Payment Amount stub 2: " << (*iterPay)->getCouponStartDate() << " : " << (*iterPay)->getCouponEndDate()
				 				<< " : " << (*iterAmort)->getStartDate() << " : " << (*iterAmort)->getEndDate() << " : " <<  dcfNot << endl;
				 				logFile << "Period rate is : " << periodRate << endl;
				 				logFile << "Notional 3 is : " << lastAmortNotional << endl;
				 			}


				 		}
				 		else
				 		{
				 			dcfNot += (*iterAmort)->getAmortNotional() * getDayCount()->getFraction((*iterAmort)->getStartDate(),
				 						(*iterPay)->getCouponEndDate(), finalPeriod,stubPeriod,  (int) getAmortFreq() ) * periodRate;

				 			amortStubDate = (*iterPay)->getCouponEndDate();
				 			lastAmortNotional = (*iterAmort)->getAmortNotional();

				 			 logFile << "Payment Amount stub 3: " << (*iterPay)->getCouponStartDate() << " : " << (*iterPay)->getCouponEndDate()
				 					 << " : " << (*iterAmort)->getStartDate() << " : " << (*iterAmort)->getEndDate() << " : " <<  dcfNot << endl;
				 			logFile << "Period rate is 2 : " << periodRate << endl;
				 			logFile << "Notional 4 is : " << lastAmortNotional << endl;
				 		}
				 	}
				 }


			 	 (*iterPay)->setNotional(lastAmortNotional);
			 	(*iterPay)->setPeriodRate(periodRate);
				 (*iterPay)->setAmount(dcfNot);
				 logFile << "Payment Amount 2 : " << (*iterPay)->getCouponStartDate() << " : "
						 << (*iterPay)->getCouponEndDate() << " : " << (*iterPay)->getAmount()
						  << endl;

			}
			else
			{
				logFile << "Notional final is : " << lastAmortNotional << endl;
				dcfNot = lastAmortNotional * getDayCount()->getFraction((*iterPay)->getCouponStartDate(),
						(*iterPay)->getCouponEndDate(), finalPeriod,stubPeriod, (int) getAccrualFreq() );


			(*iterPay)->setNotional(lastAmortNotional);
			(*iterPay)->setPeriodRate(periodRate);
			(*iterPay)->setAmount(dcfNot * periodRate );
				logFile << "Payment Amount outside amort : " << (*iterPay)->getCouponStartDate() << " : " << (*iterPay)->getCouponEndDate()
						<< " : " << lastAmortNotional << ": " << (*iterPay)->getAmount() <<
						":"  << endl;
			}
		}
		else
		{

				(*iterPay)->setNotional(getNotional());
				(*iterPay)->setPeriodRate(periodRate);
				(*iterPay)->setAmount(dcfNot * periodRate );
				logFile << "Payment Amount not amort : " << (*iterPay)->getCouponStartDate() << " : "
						<< (*iterPay)->getCouponEndDate() << " : " << "Period Rate  :" <<
						setprecision(15) << periodRate << "Payment  " << dcfNot * periodRate << " : " << setprecision(15) << (*iterPay)->getAmount()
						 << endl;

		}
	  }

	}

/*
	PayScheduleList::const_iterator iterPay1 = displayPaySchedule().begin();


	for ( ; iterPay1 != displayPaySchedule().end() ; ++iterPay1 )
	{

		logFile << " Pay Schedule : " << (*iterPay1)->getCouponStartDate() << " : " << (*iterPay1)->getCouponEndDate() <<" : " <<
				(*iterPay1)->getPaymentDate() << " : " << (*iterPay1)->getPeriodRate() << " : " << (*iterPay1)->getNotional() << " : " << (*iterPay1)->getAmount()   << endl;
	}

 	CompScheduleList::const_iterator iterComp1 = displayCompSchedule().begin();


 			  for ( ; iterComp1 != displayCompSchedule().end() ; ++iterComp1 )
 				{

 				logFile << "COMP start : end " << (*iterComp1)->getCompStartDate() << " : " << (*iterComp1)->getCompEndDate() <<
 						" : " << (*iterComp1)->getNotional() << " : " << (*iterComp1)->getAccrualRate() << " : " << (*iterComp1)->getAccrualInterest() << endl;

 				}

 				*/


 			  if ( ! genPrincipalSchedule() )
 				  logFile << "Notional XChange Amounts Calculation failed " << endl;

	 return true;
}

bool SwapLeg::genPrincipalSchedule()
{
	PayScheduleList::const_iterator iterPay = displayPaySchedule().begin();
	double prevNotional = getNotional();
	int totalCnt = displayPaySchedule().size();
	int runningCnt = 0;

	for ( ; iterPay != displayPaySchedule().end() ; ++iterPay )
	{
		runningCnt++;

		double notionalXchg = (*iterPay)->getNotional();

		Date cpnStart = (*iterPay)->getCouponStartDate();
		Date cpnEnd = (*iterPay)->getCouponEndDate();

	    shared_ptr <PrincipalSchedule> principalSchedule( new PrincipalSchedule());
	    shared_ptr <PrincipalSchedule> principalScheduleLast( new PrincipalSchedule());

	    if ( runningCnt == 1 )
	    {

	    	if ( getNotionalExchange() == "START" || getNotionalExchange() == "ALLNOEND" ||
	    		getNotionalExchange() == "ALL" || getNotionalExchange() == "BOTH" )
	    	{
	    		if ( isPayLeg() )
	    			principalSchedule->setPrincipalAmt(notionalXchg);
	    		else
	    			principalSchedule->setPrincipalAmt(-1 * notionalXchg );

	    		principalSchedule->setPaymentDate( getPayBusDay()->adjustToBusDay(cpnStart, *CalendarUtil::getCalendar(getPayCalendars())));

	    		_principalScheduleList.push_back(principalSchedule);

	    	}
	    }
	    else
	    {
	    	if ( getNotionalExchange() == "ALLNOSTART" || getNotionalExchange() == "ALLNOSTARTEND" ||
	    		getNotionalExchange() == "ALL" || getNotionalExchange() == "ALLNOEND"  )
	    	{
	    		 if ( isPayLeg() )
	    			 principalSchedule->setPrincipalAmt(notionalXchg - prevNotional);
	    		 else
	    			 principalSchedule->setPrincipalAmt(prevNotional - notionalXchg );

	    			principalSchedule->setPaymentDate( getPayBusDay()->adjustToBusDay(cpnStart, *CalendarUtil::getCalendar(getPayCalendars())) );

	    		 _principalScheduleList.push_back(principalSchedule);
	    	}

	    }


	    if( runningCnt == totalCnt )
	   	{
	   	    	if ( getNotionalExchange() == "ALLNOSTART" || getNotionalExchange() == "ALL"  || getNotionalExchange() == "BOTH"
	   	    			|| getNotionalExchange() == "END" )
	   	    	{
	   	    		if ( isPayLeg() )
	   	    			principalScheduleLast->setPrincipalAmt(-1 * notionalXchg); // it is opposite to first coupon
	   	    		else
	   	    			principalScheduleLast->setPrincipalAmt(notionalXchg);

	   	    		principalScheduleLast->setPaymentDate( getPayBusDay()->adjustToBusDay(cpnEnd, *CalendarUtil::getCalendar(getPayCalendars())) );

	   	    		_principalScheduleList.push_back(principalScheduleLast);
	   	    	}
	   	}

	    prevNotional = notionalXchg;

		//logFile << " Pay Schedule : " << (*iterPay)->getCouponStartDate() << " : " << (*iterPay)->getCouponEndDate() <<" : " <<
			//		(*iterPay)->getPaymentDate() << " : " << (*iterPay)->getPeriodRate() << " : " << (*iterPay)->getNotional() << " : " << (*iterPay)->getAmount() <<  endl;
		}

		PrincipalScheduleList::const_iterator iterPrin = displayPrincipalSchedule().begin();

		for ( ; iterPrin != displayPrincipalSchedule().end() ; ++iterPrin )
		{

		    logFile << "Principal Schedule : " << (*iterPrin)->getPaymentDate()  << " : " << (*iterPrin)->getPrincipalAmt() <<  endl;

		}

		return true;
}


double SwapLeg::calculatePV(std::string bumpTenor, double bumpSize)
{
	double pv = 0.0;

	//Date curveDate(05,11,2012) ;


	boost::shared_ptr<IRDConnect::Curve>  curvePtr;

	if ( bumpTenor != "" && bumpSize != 0.0 )
	{
		curvePtr = CurveCache::instance().find(Util::getCurveDate(), std::string(getDiscountCurve()), bumpTenor, bumpSize) ;
	}
	else
	{
		curvePtr = CurveCache::instance().find(Util::getCurveDate(), std::string(getDiscountCurve())) ;
	}

	int payMultiplier = 1.0;

	if ( isPayLeg() )
		payMultiplier = -1.0;

	PayScheduleList::const_iterator iterPay = displayPaySchedule().begin();

	for ( ; iterPay != displayPaySchedule().end() ; ++iterPay )
		{
			// PAY is negative

			if ( (*iterPay)->getPaymentDate()  > Date::todaysDate() )
				pv += (*iterPay)->getAmount() * payMultiplier * curvePtr->getZcdf((*iterPay)->getPaymentDate());

//logFile << "Payment amounts : " << curvePtr->getZcdf((*iterPay)->getPaymentDate()) << " Payment Date : " << (*iterPay)->getPaymentDate() <<  endl;

		}

		PrincipalScheduleList::const_iterator iterPrin = displayPrincipalSchedule().begin();

		for ( ; iterPrin != displayPrincipalSchedule().end() ; ++iterPrin )
		{
			if ( (*iterPrin)->getPaymentDate() > Date::todaysDate() )
				pv +=  curvePtr->getZcdf((*iterPrin)->getPaymentDate())  * (*iterPrin)->getPrincipalAmt();



		}

		return pv;

}

double SwapLeg::calculateDV01(std::string bumpTenor, double bumpSizeUp, double bumpSizeDown)
{


	cout << "SwapLeg PV - dv01 " << " : " << isPayLeg() << " : UP : " << getDiscountCurve() <<":" << calculatePV(bumpTenor, bumpSizeUp)
										<< " DOWN : " << getDiscountCurve() << ":" << calculatePV(bumpTenor, -1 * bumpSizeDown ) << endl;
	return calculatePV(bumpTenor, bumpSizeUp) - calculatePV(bumpTenor, -1 * bumpSizeDown ) ;

}

double SwapLeg::calculateTheta(double bumpSize)
{


	cout << "SwapLeg PV Theta " << " : " << isPayLeg() << " : T : " << getDiscountCurve() << ":" <<  calculatePV() << endl;
	cout << "SwapLeg PV Theta " << " : " << isPayLeg() << " : T+1 : " << getDiscountCurve() << ":" << calculatePV("Theta", bumpSize) << endl;
	return calculatePV("Theta", bumpSize) - calculatePV() ;

}

std::string SwapLeg::scheduleSerialize()
{
	CMarkup xml;

           xml.AddElem( "Schedules" );
	   	   xml.IntoElem();

	  xml.AddElem( "PayScheduleList" );
	 xml.IntoElem();


	PayScheduleList::const_iterator iterPay = displayPaySchedule().begin();

			for ( ; iterPay != displayPaySchedule().end() ; ++iterPay )
			{
					  xml.AddElem("PaySchedule");
				 	  xml.IntoElem();

				 	 xml.AddElem("CouponStartDate", (*iterPay)->getCouponStartDate().string());
				 	 xml.AddElem("Amount", String::doubleToFourDecString((*iterPay)->getAmount(),getCurrency()->getNumDecimal()));
				 	 xml.AddElem("ConvertedAmount", (*iterPay)->getConvertedAmount());
				 	 xml.AddElem("CouponEndDate", (*iterPay)->getCouponEndDate().string());
				 	 xml.AddElem("PaymentDate", (*iterPay)->getPaymentDate().string());
				 	 xml.AddElem("PeriodRate", String::doubleToFourDecString((*iterPay)->getPeriodRate(),7));
				 	 xml.AddElem("Notional", (*iterPay)->getNotional());
				    xml.OutOfElem();  // come out from Payment schedule

				   // logFile << "Payment Dates " << (*iterPay)->getCouponStartDate() << " : " << (*iterPay)->getCouponEndDate() << endl;
			}
		    xml.OutOfElem();

		    xml.AddElem( "CompScheduleList" );
		    	  // xml.SetAttrib( "classtype", "CXyz" ); // not needed now as we don't have attributes
		    	  xml.IntoElem();


		    	CompScheduleList::const_iterator iterComp = displayCompSchedule().begin();

		    			for ( ; iterComp != displayCompSchedule().end() ; ++iterComp )
		    			{
		    					  xml.AddElem("CompSchedule");
		    				 	  xml.IntoElem();
		     	 	 	 	 	 xml.AddElem("AccrualInterest", (*iterComp)->getAccrualInterest());
		    				 	 xml.AddElem("CompConvertedAmount", (*iterComp)->getConvertedAmount());
		    				 	 xml.AddElem("CompStartDate", (*iterComp)->getCompStartDate().string());
		    				 	 xml.AddElem("CompEndDate", (*iterComp)->getCompEndDate().string());
		    				 	 //xml.AddElem("Notional", (*iterComp)->getNotional());
		    				 	  xml.AddElem("AccrualRate", (*iterComp)->getAccrualRate());
		    				    xml.OutOfElem();  // come out from Comp schedule


		    			}

		    				  // you may need gointo as many times you have inner loops like pay schedulelist etc.
		    				 // xml.AddElem( "SwapLegFields", getFirstPayLeg()->get swapleg fields  ); this is needed check later
		    		    xml.OutOfElem();

		    		    xml.AddElem( "AmortScheduleList" );
		    		   	  // xml.SetAttrib( "classtype", "CXyz" ); // not needed now as we don't have attributes
		    		   	  xml.IntoElem();


		    		   	AmortScheduleList::const_iterator iterAmort = displayAmortSchedule().begin();

		    		   			for ( ; iterAmort != displayAmortSchedule().end() ; ++iterAmort )
		    		   			{
		    		   					  xml.AddElem("AmortSchedule");
		    		   				 	  xml.IntoElem();

		    		   				 	  	 xml.AddElem("AmortNotional", (*iterAmort)->getAmortNotional());
		    		   				 	  	 xml.AddElem("StartDate", (*iterAmort)->getStartDate().string());
		    		   				 	     xml.AddElem("EndDate", (*iterAmort)->getEndDate().string());

		    		   				 	  xml.OutOfElem();  // come out from amort schedule

		    		   				//    logFile << "Amort Dates : " << (*iterAmort)->getStartDate() << " : " << (*iterAmort)->getEndDate() << endl;
		    		   			}

		    		   				  // you may need gointo as many times you have inner loops like pay schedulelist etc.
		    		   				 // xml.AddElem( "SwapLegFields", getFirstPayLeg()->get swapleg fields  ); this is needed check later
		    		   		    xml.OutOfElem();

		    		   		 xml.AddElem( "ResetScheduleList" );
		    		   		 	  // xml.SetAttrib( "classtype", "CXyz" ); // not needed now as we don't have attributes
		    		   		 	  xml.IntoElem();


		    		   		 	ResetScheduleList::const_iterator iterReset = displayResetSchedule().begin();

		    		   		 			for ( ; iterReset != displayResetSchedule().end() ; ++iterReset )
		    		   		 			{
		    		   		 					  xml.AddElem("ResetSchedule");
		    		   		 				 	  xml.IntoElem();

		    		   		 				 	 xml.AddElem("QuoteDate", (*iterReset)->getQuoteDate().string());
		    		   		 				     xml.AddElem("Rate", String::doubleToFourDecString((*iterReset)->getRate(),7));
		    		   		 				 	 xml.AddElem("RateIndexType", (*iterReset)->getRateIndexType().getStr());
		    		   		 				 	xml.AddElem("RateSettingType", (*iterReset)->getRateSettingType().getStr());
		    		   		 				 	 xml.AddElem("ResetStartDate", (*iterReset)->getResetStartDate().string());
		    		   		 				 	 xml.AddElem("ResetEndDate", (*iterReset)->getResetEndDate().string());
		    		   		 				    xml.OutOfElem();  // come out from Reset schedule

		    		   		 				//    logFile << "Reset Dates : " << (*iterReset)->getResetStartDate() << " : " << (*iterReset)->getResetEndDate() << endl;
		    		   		 			}

		    		   		 				xml.OutOfElem(); //reset end


		    		   		 			xml.OutOfElem(); //Schedules end

return xml.GetDoc();
}


}
