/*
 * fixingRates.cpp
 *
 *  Created on: 12-Nov-2010
 *      Author: vishist
 */

#include <iostream>
#include <fstream>
#include "fixingRates.h"
#include "period.h"
#include "busDayConv.h"
#include "linearInterpolation.h"
#include "calendarUtil.h"
#include "curve.h"
#include "curveBuilder.h"
#include "curveCache.h"
#include "buildCurveFromZcdf.h"
#include "buildCurveFromMarketRates.h"
#include "moneyMkt.h"
#include "util.h"

using namespace std;
using namespace IRDConnect;

FixingRates::FixingRates(

Date 		currentDate,
String 		lastModifiedBy,
String 		lastVerifiedBy,
Date 		modifiedTimestamp,
Date 		quoteDate,
String 		quoteId,
String 		quoteType,
double		rate,
String 		ratesetMode,
Date 		verifiedTimestamp )

{


_currentDate  		= 	currentDate;
_lastModifiedBy		=	lastModifiedBy;
_lastVerifiedBy     =	lastVerifiedBy;
_modifiedTimestamp	=	modifiedTimestamp;
_quoteDate			=	quoteDate;
_quoteId			=	quoteId;
_quoteType			=	quoteType;
_rate				=	rate;
_ratesetMode		=	ratesetMode;
_verifiedTimestamp	=	verifiedTimestamp;

}

FixingRates::~FixingRates()
{
	//do nothing
}

void FixingRates::init()
{

	FixingRates fixingRates;

	//int noOfResets = 1; ===== need to enable letter if needed
	// rate = 0.05;

	// 3M fixingRates

	fixingRates.setQuoteId("GBPDOM_3M.T3750");
	fixingRates.setQuoteDate(Date(15,10,2010));
	fixingRates.setQuoteType("RATE");
	fixingRates.setRate(0.73975);

	_fixingRatesList.push_back(fixingRates);

	fixingRates.setQuoteId("GBPDOM_3M.T3750");
	fixingRates.setQuoteDate(Date(15,12,2010));
	fixingRates.setQuoteType("RATE");
	fixingRates.setRate(0.74938);

	_fixingRatesList.push_back(fixingRates);

	fixingRates.setQuoteId("GBPDOM_3M.T3750");
	fixingRates.setQuoteDate(Date(14,1,2011));
	fixingRates.setQuoteType("RATE");
	fixingRates.setRate(0.76750);

	_fixingRatesList.push_back(fixingRates);

	fixingRates.setQuoteId("GBPDOM_3M.T3750");
	fixingRates.setQuoteDate(Date(15,1,2011));
	fixingRates.setQuoteType("RATE");
	fixingRates.setRate(0.0000);


	_fixingRatesList.push_back(fixingRates);

	fixingRates.setQuoteId("GBPDOM_3M.T3750");
	fixingRates.setQuoteDate(Date(22,02,2013));
	fixingRates.setQuoteType("RATE");
	fixingRates.setRate(0.50813);

	_fixingRatesList.push_back(fixingRates);

	fixingRates.setQuoteId("GBPDOM_6M.T3750");
	fixingRates.setQuoteDate(Date(22,02,2013));
	fixingRates.setQuoteType("RATE");
	fixingRates.setRate(0.62375);

	_fixingRatesList.push_back(fixingRates);



	fixingRates.setQuoteId("USDED_6M.T3750");
	fixingRates.setQuoteDate(Date(22,02,2013));
	fixingRates.setQuoteType("RATE");
	fixingRates.setRate(0.45990);

	_fixingRatesList.push_back(fixingRates);


	fixingRates.setQuoteId("EURED_6M.T248");
	fixingRates.setQuoteDate(Date(22,02,2013));
	fixingRates.setQuoteType("RATE");
	fixingRates.setRate(0.25429);

	_fixingRatesList.push_back(fixingRates);

	fixingRates.setQuoteId("GBPDOM_6M.T3750");
	fixingRates.setQuoteDate(Date(21,02,2013));
	fixingRates.setQuoteType("RATE");
	fixingRates.setRate(0.62250);

	_fixingRatesList.push_back(fixingRates);



	fixingRates.setQuoteId("USDED_6M.T3750");
	fixingRates.setQuoteDate(Date(21,02,2013));
	fixingRates.setQuoteType("RATE");
	fixingRates.setRate(0.46140);

	_fixingRatesList.push_back(fixingRates);


	fixingRates.setQuoteId("EURED_6M.T248");
	fixingRates.setQuoteDate(Date(21,02,2013));
	fixingRates.setQuoteType("RATE");
	fixingRates.setRate(0.25714);

	_fixingRatesList.push_back(fixingRates);


	fixingRates.setQuoteId("GBPDOM_3M.T3750");
	fixingRates.setQuoteDate(Date(17,1,2011));
	fixingRates.setQuoteType("RATE");
	fixingRates.setRate(0.76750);

	_fixingRatesList.push_back(fixingRates);

	fixingRates.setQuoteId("GBPDOM_3M.T3750");
	fixingRates.setQuoteDate(Date(16,3,2011));
	fixingRates.setQuoteType("RATE");
	fixingRates.setRate(0.90900);

	_fixingRatesList.push_back(fixingRates);

	fixingRates.setQuoteId("GBPDOM_3M.T3750");
	fixingRates.setQuoteDate(Date(15,4,2011));
	fixingRates.setQuoteType("RATE");
	fixingRates.setRate(0.97316);

	_fixingRatesList.push_back(fixingRates);

	fixingRates.setQuoteId("GBPDOM_3M.T3750");
	fixingRates.setQuoteDate(Date(18,4,2011));
	fixingRates.setQuoteType("RATE");
	fixingRates.setRate(0.98044);
	_fixingRatesList.push_back(fixingRates);

	fixingRates.setQuoteId("GBPDOM_3M.T3750");
	fixingRates.setQuoteDate(Date(15,6,2011));
	fixingRates.setQuoteType("RATE");
	fixingRates.setRate(1.13700);

	_fixingRatesList.push_back(fixingRates);

	fixingRates.setQuoteId("GBPDOM_3M.T3750");
	fixingRates.setQuoteDate(Date(18,7,2011));
	fixingRates.setQuoteType("RATE");
	fixingRates.setRate(1.21533);


	_fixingRatesList.push_back(fixingRates);

	fixingRates.setQuoteId("GBPDOM_3M.T3750");
	fixingRates.setQuoteDate(Date(15,7,2011));
	fixingRates.setQuoteType("RATE");
	fixingRates.setRate(1.21079);

	_fixingRatesList.push_back(fixingRates);

	fixingRates.setQuoteId("GBPDOM_3M.T3750");
	fixingRates.setQuoteDate(Date(9,9,2011));
	fixingRates.setQuoteType("RATE");
	fixingRates.setRate(1.33593);

	_fixingRatesList.push_back(fixingRates);

	fixingRates.setQuoteId("GBPDOM_3M.T3750");
	fixingRates.setQuoteDate(Date(10,9,2011));
	fixingRates.setQuoteType("RATE");
	fixingRates.setRate(1.34212);

	_fixingRatesList.push_back(fixingRates);

    fixingRates.setQuoteId("GBPDOM_3M.T3750");
	fixingRates.setQuoteDate(Date(21,9,2011));
	fixingRates.setQuoteType("RATE");
	fixingRates.setRate(1.36800);

   _fixingRatesList.push_back(fixingRates);

	fixingRates.setQuoteId("GBPDOM_3M.T3750");
	fixingRates.setQuoteDate(Date(14,10,2011));
	fixingRates.setQuoteType("RATE");
	fixingRates.setRate(1.44102);
   _fixingRatesList.push_back(fixingRates);

    fixingRates.setQuoteId("GBPDOM_3M.T3750");
	fixingRates.setQuoteDate(Date(15,10,2011));
	fixingRates.setQuoteType("RATE");
	fixingRates.setRate(1.44226);
  _fixingRatesList.push_back(fixingRates);

	fixingRates.setQuoteId("GBPDOM_3M.T3750");
	fixingRates.setQuoteDate(Date(17,10,2011));
	fixingRates.setQuoteType("RATE");
	fixingRates.setRate(1.44651);
_fixingRatesList.push_back(fixingRates);

    fixingRates.setQuoteId("GBPDOM_3M.T3750");
	fixingRates.setQuoteDate(Date(18,10,2011));
	fixingRates.setQuoteType("RATE");
	fixingRates.setRate(1.44950);
_fixingRatesList.push_back(fixingRates);

    fixingRates.setQuoteId("GBPDOM_3M.T3750");
	fixingRates.setQuoteDate(Date(9,12,2011));
	fixingRates.setQuoteType("RATE");
	fixingRates.setRate(1.60176);
_fixingRatesList.push_back(fixingRates);

    fixingRates.setQuoteId("GBPDOM_3M.T3750");
	fixingRates.setQuoteDate(Date(10,12,2011));
	fixingRates.setQuoteType("RATE");
	fixingRates.setRate(1.60858);
_fixingRatesList.push_back(fixingRates);

    fixingRates.setQuoteId("GBPDOM_3M.T3750");
	fixingRates.setQuoteDate(Date(21,12,2011));
	fixingRates.setQuoteType("RATE");
	fixingRates.setRate(1.63800);
_fixingRatesList.push_back(fixingRates);

	fixingRates.setQuoteId("GBPDOM_3M.T3750");
	fixingRates.setQuoteDate(Date(13,1,2012));
	fixingRates.setQuoteType("RATE");
	fixingRates.setRate(1.71078);

	_fixingRatesList.push_back(fixingRates);


	fixingRates.setQuoteId("GBPDOM_3M.T3750");
	fixingRates.setQuoteDate(Date(15,1,2012));
	fixingRates.setQuoteType("RATE");
	fixingRates.setRate(1.71887);
	_fixingRatesList.push_back(fixingRates);

	_fixingRatesList.push_back(fixingRates);


	fixingRates.setQuoteId("GBPDOM_3M.T3750");
	fixingRates.setQuoteDate(Date(16,1,2012));
	fixingRates.setQuoteType("RATE");
	fixingRates.setRate(1.72016);
	_fixingRatesList.push_back(fixingRates);

	fixingRates.setQuoteId("GBPDOM_3M.T3750");
	fixingRates.setQuoteDate(Date(18,1,2012));
	fixingRates.setQuoteType("RATE");
	fixingRates.setRate(1.72642);
	_fixingRatesList.push_back(fixingRates);

	fixingRates.setQuoteId("GBPDOM_3M.T3750");
	fixingRates.setQuoteDate(Date(9,3,2012));
	fixingRates.setQuoteType("RATE");
	fixingRates.setRate(1.89170);
	_fixingRatesList.push_back(fixingRates);

	fixingRates.setQuoteId("GBPDOM_3M.T3750");
	fixingRates.setQuoteDate(Date(10,3,2012));
	fixingRates.setQuoteType("RATE");
	fixingRates.setRate(1.89286);
	_fixingRatesList.push_back(fixingRates);

	fixingRates.setQuoteId("GBPDOM_3M.T3750");
	fixingRates.setQuoteDate(Date(21,3,2012));
	fixingRates.setQuoteType("RATE");
	fixingRates.setRate(1.92500);
	_fixingRatesList.push_back(fixingRates);


	fixingRates.setQuoteId("GBPDOM_3M.T3750");
	fixingRates.setQuoteDate(Date(13,4,2012));
	fixingRates.setQuoteType("RATE");
	fixingRates.setRate(1.99379);

	_fixingRatesList.push_back(fixingRates);

	fixingRates.setQuoteId("GBPDOM_3M.T3750");
	fixingRates.setQuoteDate(Date(15,4,2012));
	fixingRates.setQuoteType("RATE");
	fixingRates.setRate(2.00206);

	_fixingRatesList.push_back(fixingRates);

	fixingRates.setQuoteId("GBPDOM_3M.T3750");
	fixingRates.setQuoteDate(Date(18,4,2012));
	fixingRates.setQuoteType("RATE");
	fixingRates.setRate(2.00968);

	_fixingRatesList.push_back(fixingRates);

	fixingRates.setQuoteId("GBPDOM_3M.T3750");
	fixingRates.setQuoteDate(Date(10,6,2012));
	fixingRates.setQuoteType("RATE");
	fixingRates.setRate(2.18745);

	_fixingRatesList.push_back(fixingRates);

	fixingRates.setQuoteId("GBPDOM_3M.T3750");
	fixingRates.setQuoteDate(Date(20,6,2012));
	fixingRates.setQuoteType("RATE");
	fixingRates.setRate(2.22000);

	_fixingRatesList.push_back(fixingRates);

	fixingRates.setQuoteId("GBPDOM_3M.T3750");
	fixingRates.setQuoteDate(Date(8,6,2012));
	fixingRates.setQuoteType("RATE");
	fixingRates.setRate(2.18494);

	_fixingRatesList.push_back(fixingRates);

	fixingRates.setQuoteId("GBPDOM_3M.T3750");
	fixingRates.setQuoteDate(Date(13,7,2012));
	fixingRates.setQuoteType("RATE");
	fixingRates.setRate(2.29810);

	_fixingRatesList.push_back(fixingRates);

	//fixingRates.setQuoteId("GBPDOM_3M.T3750");
	//fixingRates.setQuoteDate(Date(15,7,2012));
	//fixingRates.setQuoteType("RATE");
	//fixingRates.setRate(2.30071);

	//_fixingRatesList.push_back(fixingRates);

	fixingRates.setQuoteId("GBPDOM_3M.T3750");
	fixingRates.setQuoteDate(Date(18,7,2012));
	fixingRates.setQuoteType("RATE");
	fixingRates.setRate(2.30905);

	_fixingRatesList.push_back(fixingRates);

	 fixingRates.setQuoteId("GBPDOM_3M.T3750");
	 fixingRates.setQuoteDate(Date(10,9,2012));
	 fixingRates.setQuoteType("RATE");
	 fixingRates.setRate(2.46836);


	_fixingRatesList.push_back(fixingRates);

	fixingRates.setQuoteId("GBPDOM_3M.T3750");
	fixingRates.setQuoteDate(Date(19,9,2012));
	fixingRates.setQuoteType("RATE");
	fixingRates.setRate(2.47823);

	_fixingRatesList.push_back(fixingRates);

	fixingRates.setQuoteId("GBPDOM_3M.T3750");
	fixingRates.setQuoteDate(Date(17,10,2012));
	fixingRates.setQuoteType("RATE");
	fixingRates.setRate(2.44599);

	_fixingRatesList.push_back(fixingRates);

	fixingRates.setQuoteId("GBPDOM_3M.T3750");
	fixingRates.setQuoteDate(Date(10,12,2010));
	fixingRates.setRate(0.74500);

	_fixingRatesList.push_back(fixingRates);

	fixingRates.setQuoteId("GBPDOM_3M.T3750");
	fixingRates.setQuoteDate(Date(10,3,2011));
	fixingRates.setRate(0.88979);

	_fixingRatesList.push_back(fixingRates);

	fixingRates.setQuoteId("GBPDOM_3M.T3750");
	fixingRates.setQuoteDate(Date(10,6,2011));
	fixingRates.setRate(1.12593);

	_fixingRatesList.push_back(fixingRates);

	fixingRates.setQuoteId("GBPDOM_3M.T3750");
	fixingRates.setQuoteDate(Date(12,9,2011));
	fixingRates.setRate(1.34370);

	_fixingRatesList.push_back(fixingRates);

	fixingRates.setQuoteId("GBPDOM_3M.T3750");
	fixingRates.setQuoteDate(Date(12,12,2011));
	fixingRates.setRate(1.61082);

	_fixingRatesList.push_back(fixingRates);

	fixingRates.setQuoteId("GBPDOM_3M.T3750");
	fixingRates.setQuoteDate(Date(12,3,2012));
	fixingRates.setRate(1.89715);

	_fixingRatesList.push_back(fixingRates);

    fixingRates.setQuoteId("GBPDOM_3M.T3750");
	fixingRates.setQuoteDate(Date(11,6,2012));
	fixingRates.setRate(2.19071);

	_fixingRatesList.push_back(fixingRates);

	fixingRates.setQuoteId("GBPDOM_3M.T3750");
	fixingRates.setQuoteDate(Date(10,9,2012));
	fixingRates.setRate(2.46836);

	fixingRates.setQuoteId("GBPDOM_3M.T3750");
	fixingRates.setQuoteDate(Date(15,10,2012));
	fixingRates.setQuoteType("RATE");
	fixingRates.setRate(2.55474);

	_fixingRatesList.push_back(fixingRates);


	fixingRates.setQuoteId("GBPDOM_1M.T3750");
	fixingRates.setQuoteDate(Date(15,10,2012));
	fixingRates.setQuoteType("RATE");
	fixingRates.setRate(0.57125);

	_fixingRatesList.push_back(fixingRates);

	fixingRates.setQuoteId("GBPDOM_2M.T3750");
	fixingRates.setQuoteDate(Date(15,10,2012));
	fixingRates.setQuoteType("RATE");
	fixingRates.setRate(0.62775);

	_fixingRatesList.push_back(fixingRates);

	fixingRates.setQuoteId("GBPDOM_3M.T3750");
	fixingRates.setQuoteDate(Date(16,4,2012));
	fixingRates.setQuoteType("RATE");
	fixingRates.setRate(2.00332);

	_fixingRatesList.push_back(fixingRates);


	fixingRates.setQuoteId("GBPDOM_3M.T3750");
	fixingRates.setQuoteDate(Date(16,7,2012));
	fixingRates.setQuoteType("RATE");
	fixingRates.setRate(2.30376);

	_fixingRatesList.push_back(fixingRates);

    fixingRates.setQuoteId("GBPDOM_3M.T3750");
	fixingRates.setQuoteDate(Date(15,10,2012));
	fixingRates.setQuoteType("RATE");
	fixingRates.setRate(2.55474);

_fixingRatesList.push_back(fixingRates);

    fixingRates.setQuoteId("GBPDOM_3M.T3750");
	fixingRates.setQuoteDate(Date(15,10,2012));
	fixingRates.setQuoteType("RATE");
	fixingRates.setRate(2.45130);

	_fixingRatesList.push_back(fixingRates);


	fixingRates.setQuoteId("GBPDOM_1M.T3750");
	fixingRates.setQuoteDate(Date(15,10,2012));
	fixingRates.setQuoteType("RATE");
	fixingRates.setRate(0.57125);

	_fixingRatesList.push_back(fixingRates);

	fixingRates.setQuoteId("GBPDOM_2M.T3750");
	fixingRates.setQuoteDate(Date(15,10,2012));
	fixingRates.setQuoteType("RATE");
	fixingRates.setRate(0.62775);

	_fixingRatesList.push_back(fixingRates);

	fixingRates.setQuoteId("GBPDOM_3M.T3750");
	fixingRates.setQuoteDate(Date(10,9,2012));
	fixingRates.setQuoteType("RATE");
	fixingRates.setRate(2.46836);

	_fixingRatesList.push_back(fixingRates);


	fixingRates.setQuoteId("GBPDOM_3M.T3750");
		fixingRates.setQuoteDate(Date(02,9,2013));
		fixingRates.setQuoteType("RATE");
		fixingRates.setRate(0.51500);

		_fixingRatesList.push_back(fixingRates);

	// 6m GBP rates

	//	fixingRates.setQuoteId("GBPDOM_6M.T3750");
	//	fixingRates.setQuoteDate(Date(15,10,2010));
	//	fixingRates.setQuoteType("RATE");
	//	fixingRates.setRate(0.61833);
	//	_fixingRatesList.push_back(fixingRates);


		fixingRates.setQuoteId("GBPDOM_6M.T3750");
		fixingRates.setQuoteDate(Date(15,10,2010));
		fixingRates.setQuoteType("RATE");
		fixingRates.setRate(1.02625);
		_fixingRatesList.push_back(fixingRates);


		fixingRates.setQuoteId("GBPDOM_6M.T3750");
		fixingRates.setQuoteDate(Date(10,12,2010));
		fixingRates.setQuoteType("RATE");
		fixingRates.setRate(1.04125);
		_fixingRatesList.push_back(fixingRates);


		fixingRates.setQuoteId("GBPDOM_6M.T3750");
		fixingRates.setQuoteDate(Date(16,3,2011));
		fixingRates.setQuoteType("RATE");
		fixingRates.setRate(1.21359);
		_fixingRatesList.push_back(fixingRates);


		fixingRates.setQuoteId("GBPDOM_6M.T3750");
		fixingRates.setQuoteDate(Date(15,4,2011));
		fixingRates.setQuoteType("RATE");
		fixingRates.setRate(1.29072);
		_fixingRatesList.push_back(fixingRates);


		fixingRates.setQuoteId("GBPDOM_6M.T3750");
		fixingRates.setQuoteDate(Date(18,4,2011));
		fixingRates.setQuoteType("RATE");
		fixingRates.setRate(1.29609);
		_fixingRatesList.push_back(fixingRates);


		fixingRates.setQuoteId("GBPDOM_6M.T3750");
		fixingRates.setQuoteDate(Date(10,6,2011));
		fixingRates.setQuoteType("RATE");
		fixingRates.setRate(1.43597);
		_fixingRatesList.push_back(fixingRates);


		fixingRates.setQuoteId("GBPDOM_6M.T3750");
		fixingRates.setQuoteDate(Date(21,9,2011));
		fixingRates.setQuoteType("RATE");
		fixingRates.setRate(1.70894);
		_fixingRatesList.push_back(fixingRates);

		fixingRates.setQuoteId("GBPDOM_6M.T3750");
		fixingRates.setQuoteDate(Date(14,10,2011));
		fixingRates.setQuoteType("RATE");
		fixingRates.setRate(1.78492);
		_fixingRatesList.push_back(fixingRates);

		fixingRates.setQuoteId("GBPDOM_6M.T3750");
		fixingRates.setQuoteDate(Date(15,10,2011));
		fixingRates.setQuoteType("RATE");
		fixingRates.setRate(1.78629);
		_fixingRatesList.push_back(fixingRates);



		fixingRates.setQuoteId("GBPDOM_6M.T3750");
		fixingRates.setQuoteDate(Date(17,10,2011));
		fixingRates.setQuoteType("RATE");
		fixingRates.setRate(1.79076);
		_fixingRatesList.push_back(fixingRates);

		fixingRates.setQuoteId("GBPDOM_6M.T3750");
		fixingRates.setQuoteDate(Date(9,12,2011));
		fixingRates.setQuoteType("RATE");
		fixingRates.setRate(1.95712);
		_fixingRatesList.push_back(fixingRates);


		fixingRates.setQuoteId("GBPDOM_6M.T3750");
		fixingRates.setQuoteDate(Date(10,12,2011));
		fixingRates.setQuoteType("RATE");
		fixingRates.setRate(1.95844);
		_fixingRatesList.push_back(fixingRates);


		fixingRates.setQuoteId("GBPDOM_6M.T3750");
		fixingRates.setQuoteDate(Date(12,12,2011));
		fixingRates.setQuoteType("RATE");
		fixingRates.setRate(1.96285);
		_fixingRatesList.push_back(fixingRates);


		fixingRates.setQuoteId("GBPDOM_6M.T3750");
		fixingRates.setQuoteDate(Date(21,3,2012));
		fixingRates.setQuoteType("RATE");
		fixingRates.setRate(2.28466);
		_fixingRatesList.push_back(fixingRates);

		fixingRates.setQuoteId("GBPDOM_6M.T3750");
		fixingRates.setQuoteDate(Date(13,4,2012));
		fixingRates.setQuoteType("RATE");
		fixingRates.setRate(2.35922);
		_fixingRatesList.push_back(fixingRates);

		fixingRates.setQuoteId("GBPDOM_6M.T3750");
		fixingRates.setQuoteDate(Date(15,4,2012));
		fixingRates.setQuoteType("RATE");
		fixingRates.setRate(2.36202);
		_fixingRatesList.push_back(fixingRates);


		fixingRates.setQuoteId("GBPDOM_6M.T3750");
		fixingRates.setQuoteDate(Date(16,4,2012));
		fixingRates.setQuoteType("RATE");
		fixingRates.setRate(2.36515);
		_fixingRatesList.push_back(fixingRates);

		fixingRates.setQuoteId("GBPDOM_6M.T3750");
		fixingRates.setQuoteDate(Date(17,4,2012));
		fixingRates.setQuoteType("RATE");
		fixingRates.setRate(2.36828);
		_fixingRatesList.push_back(fixingRates);

		fixingRates.setQuoteId("GBPDOM_6M.T3750");
		fixingRates.setQuoteDate(Date(8,6,2012));
		fixingRates.setQuoteType("RATE");
		fixingRates.setRate(2.53618);
		_fixingRatesList.push_back(fixingRates);


		fixingRates.setQuoteId("GBPDOM_6M.T3750");
		fixingRates.setQuoteDate(Date(10,6,2012));
		fixingRates.setQuoteType("RATE");
		fixingRates.setRate(2.53891);
		_fixingRatesList.push_back(fixingRates);

		fixingRates.setQuoteId("GBPDOM_6M.T3750");
		fixingRates.setQuoteDate(Date(11,6,2012));
		fixingRates.setQuoteType("RATE");
		fixingRates.setRate(2.54175);
		_fixingRatesList.push_back(fixingRates);


		fixingRates.setQuoteId("GBPDOM_6M.T3750");
		fixingRates.setQuoteDate(Date(19,9,2012));
		fixingRates.setQuoteType("RATE");
		fixingRates.setRate(2.47823);
		_fixingRatesList.push_back(fixingRates);


		fixingRates.setQuoteId("GBPDOM_6M.T3750");
		fixingRates.setQuoteDate(Date(15,10,2012));
		fixingRates.setQuoteType("RATE");
		fixingRates.setRate(2.47582);
		_fixingRatesList.push_back(fixingRates);


		fixingRates.setQuoteId("GBPDOM_6M.T3750");
		fixingRates.setQuoteDate(Date(17,10,2012));
		fixingRates.setQuoteType("RATE");
		fixingRates.setRate(2.44599);
		_fixingRatesList.push_back(fixingRates);

		fixingRates.setQuoteId("GBPDOM_6M.T3750");
		fixingRates.setQuoteDate(Date(22,8,2013));
		fixingRates.setQuoteType("RATE");
		fixingRates.setRate(0.59250);
		_fixingRatesList.push_back(fixingRates);
/*
		fixingRates.setQuoteId("GBPDOM_6M.T3750");
		fixingRates.setQuoteDate(Date(27,9,2013));
		fixingRates.setQuoteType("RATE");
		fixingRates.setRate(0.075);
		_fixingRatesList.push_back(fixingRates);
*/

		fixingRates.setQuoteId("GBPDOM_6M.T3750");
		fixingRates.setQuoteDate(Date(27,03,2014));
		fixingRates.setQuoteType("RATE");
	    fixingRates.setRate(0.70795);
		_fixingRatesList.push_back(fixingRates);

		fixingRates.setQuoteId("GBPDOM_6M.T3750");
		fixingRates.setQuoteDate(Date(19,8,2013));
		fixingRates.setQuoteType("RATE");
		fixingRates.setRate(0.59300);
		_fixingRatesList.push_back(fixingRates);

		fixingRates.setQuoteId("GBPDOM_6M.T3750");
		fixingRates.setQuoteDate(Date(02,9,2013));
		fixingRates.setQuoteType("RATE");
		fixingRates.setRate(0.38625);
		_fixingRatesList.push_back(fixingRates);

		fixingRates.setQuoteId("GBPDOM_6M.T3750");
		fixingRates.setQuoteDate(Date(18,9,2013));
		fixingRates.setQuoteType("RATE");
		fixingRates.setRate(0.59313);
		_fixingRatesList.push_back(fixingRates);

		fixingRates.setQuoteId("GBPDOM_6M.T3750");
		fixingRates.setQuoteDate(Date(27,9,2013));
		fixingRates.setQuoteType("RATE");
		fixingRates.setRate(0.53109329);
		_fixingRatesList.push_back(fixingRates);

		fixingRates.setQuoteId("GBPDOM_6M.T3750");
		fixingRates.setQuoteDate(Date(02,01,2014));
		fixingRates.setQuoteType("RATE");
		fixingRates.setRate(0.53896);
		_fixingRatesList.push_back(fixingRates);

		fixingRates.setQuoteId("GBPDOM_6M.T3750");
		fixingRates.setQuoteDate(Date(24,02,2014));
		fixingRates.setQuoteType("RATE");
		fixingRates.setRate(0.60243);
		_fixingRatesList.push_back(fixingRates);


		fixingRates.setQuoteId("GBPDOM_6M.T3750");
		fixingRates.setQuoteDate(Date(21,07,2014));
		fixingRates.setQuoteType("RATE");
		fixingRates.setRate(0.72285);
		_fixingRatesList.push_back(fixingRates);

		fixingRates.setQuoteId("GBPDOM_6M.T3750");
		fixingRates.setQuoteDate(Date(19,01,2015));
		fixingRates.setQuoteType("RATE");
		fixingRates.setRate(1.03644);
		_fixingRatesList.push_back(fixingRates);


		fixingRates.setQuoteId("GBPDOM_6M.T3750");
		fixingRates.setQuoteDate(Date(20,07,2015));
		fixingRates.setQuoteType("RATE");
		fixingRates.setRate(1.62144);
		_fixingRatesList.push_back(fixingRates);

		fixingRates.setQuoteId("GBPDOM_6M.T3750");
		fixingRates.setQuoteDate(Date(16,9,2015));
		fixingRates.setQuoteType("RATE");
		fixingRates.setRate(1.57553);
		_fixingRatesList.push_back(fixingRates);

		fixingRates.setQuoteId("GBPDOM_6M.T3750");
		fixingRates.setQuoteDate(Date(26,8,2015));
		fixingRates.setQuoteType("RATE");
		fixingRates.setRate(1.58802);
		_fixingRatesList.push_back(fixingRates);

		fixingRates.setQuoteId("GBPDOM_6M.T3750");
		fixingRates.setQuoteDate(Date(15,02,2016));
		fixingRates.setQuoteType("RATE");
		fixingRates.setRate(1.79597);
		_fixingRatesList.push_back(fixingRates);


	fixingRates.setQuoteId("GBPDOM_1M.T3750");
	fixingRates.setQuoteDate(Date(15,10,2010));
	fixingRates.setQuoteType("RATE");
	fixingRates.setRate(0.57125);
	_fixingRatesList.push_back(fixingRates);

	fixingRates.setQuoteId("GBPDOM_2M.T3750");
	fixingRates.setQuoteDate(Date(15,10,2010));
	fixingRates.setQuoteType("RATE");
	fixingRates.setRate(0.62775);
	_fixingRatesList.push_back(fixingRates);


	fixingRates.setQuoteId("GBPDOM_1M.T3750");
	fixingRates.setQuoteDate(Date(15,10,2012));
	fixingRates.setQuoteType("RATE");
	fixingRates.setRate(2.21422);
	_fixingRatesList.push_back(fixingRates);

	fixingRates.setQuoteId("GBPDOM_2M.T3750");
	fixingRates.setQuoteDate(Date(15,10,2012));
	fixingRates.setQuoteType("RATE");
	fixingRates.setRate(2.51768);
	_fixingRatesList.push_back(fixingRates);

	fixingRates.setQuoteId("GBPDOM_1M.T3750");
	fixingRates.setQuoteDate(Date(17,10,2012));
	fixingRates.setQuoteType("RATE");
	fixingRates.setRate(2.22474);
	_fixingRatesList.push_back(fixingRates);

	fixingRates.setQuoteId("GBPDOM_2M.T3750");
	fixingRates.setQuoteDate(Date(17,10,2012));
	fixingRates.setQuoteType("RATE");
	fixingRates.setRate(2.51974);
	_fixingRatesList.push_back(fixingRates);

	fixingRates.setQuoteId("GBPDOM_2M.T3750");
	fixingRates.setQuoteDate(Date(19,9,2012));
	fixingRates.setQuoteType("RATE");
	fixingRates.setRate(2.44912);
	_fixingRatesList.push_back(fixingRates);

	fixingRates.setQuoteId("GBPDOM_3M.T3750");
	fixingRates.setQuoteDate(Date(19,9,2012));
	fixingRates.setQuoteType("RATE");
	fixingRates.setRate(2.49071);
	_fixingRatesList.push_back(fixingRates);

	fixingRates.setQuoteId("GBPDOM_1M.T3750");
	fixingRates.setQuoteDate(Date(02,01,2014));
	fixingRates.setQuoteType("RATE");
	fixingRates.setRate(0.53556);
	_fixingRatesList.push_back(fixingRates);


	fixingRates.setQuoteId("GBPDOM_2M.T3750");
	fixingRates.setQuoteDate(Date(02,01,2014));
	fixingRates.setQuoteType("RATE");
	fixingRates.setRate(0.54009);
	_fixingRatesList.push_back(fixingRates);


	fixingRates.setQuoteId("GBPDOM_6M.T3750");
	fixingRates.setQuoteDate(Date(02,01,2014));
	fixingRates.setQuoteType("RATE");
	fixingRates.setRate(0.57342);
	_fixingRatesList.push_back(fixingRates);


	fixingRates.setQuoteId("GBPDOM_7M.T3750");
	fixingRates.setQuoteDate(Date(02,01,2014));
	fixingRates.setQuoteType("RATE");
	fixingRates.setRate(0.58339);
	_fixingRatesList.push_back(fixingRates);
/*

	_fixingRatesList.clear();

	fixingRates.setQuoteId("GBPDOM_3M.T3750");
	fixingRates.setQuoteDate(Date(15,10,2010));
	fixingRates.setQuoteType("RATE");
	fixingRates.setRate(0.79059);

	_fixingRatesList.push_back(fixingRates);

	fixingRates.setQuoteId("GBPDOM_3M.T3750");
	fixingRates.setQuoteDate(Date(17,1,2011));
	fixingRates.setQuoteType("RATE");
	fixingRates.setRate(0.86368);

	_fixingRatesList.push_back(fixingRates);

	fixingRates.setQuoteId("GBPDOM_3M.T3750");
	fixingRates.setQuoteDate(Date(15,4,2011));
	fixingRates.setQuoteType("RATE");
	fixingRates.setRate(0.99514);

	_fixingRatesList.push_back(fixingRates);


	fixingRates.setQuoteId("GBPDOM_3M.T3750");
	fixingRates.setQuoteDate(Date(15,7,2011));
	fixingRates.setQuoteType("RATE");
	fixingRates.setRate(1.17508);

	_fixingRatesList.push_back(fixingRates);


	fixingRates.setQuoteId("GBPDOM_3M.T3750");
	fixingRates.setQuoteDate(Date(17,10,2011));
	fixingRates.setQuoteType("RATE");
	fixingRates.setRate(1.34175);

	_fixingRatesList.push_back(fixingRates);


	fixingRates.setQuoteId("GBPDOM_3M.T3750");
	fixingRates.setQuoteDate(Date(16,1,2012));
	fixingRates.setQuoteType("RATE");
	fixingRates.setRate(1.53650);

	_fixingRatesList.push_back(fixingRates);


	fixingRates.setQuoteId("GBPDOM_3M.T3750");
	fixingRates.setQuoteDate(Date(10,12,2010));
	fixingRates.setRate(0.82589);

	_fixingRatesList.push_back(fixingRates);

	fixingRates.setQuoteId("GBPDOM_3M.T3750");
	fixingRates.setQuoteDate(Date(10,3,2011));
	fixingRates.setRate(0.93683);

	_fixingRatesList.push_back(fixingRates);

	fixingRates.setQuoteId("GBPDOM_3M.T3750");
	fixingRates.setQuoteDate(Date(10,6,2011));
	fixingRates.setRate(1.09177);

	_fixingRatesList.push_back(fixingRates);

	fixingRates.setQuoteId("GBPDOM_3M.T3750");
	fixingRates.setQuoteDate(Date(12,9,2011));
	fixingRates.setRate(1.27295);

	_fixingRatesList.push_back(fixingRates);

	fixingRates.setQuoteId("GBPDOM_3M.T3750");
	fixingRates.setQuoteDate(Date(12,12,2011));
	fixingRates.setRate(1.47784);

	_fixingRatesList.push_back(fixingRates);

	fixingRates.setQuoteId("GBPDOM_3M.T3750");
	fixingRates.setQuoteDate(Date(12,3,2012));
	fixingRates.setRate(1.67143);

	_fixingRatesList.push_back(fixingRates);

	fixingRates.setQuoteId("GBPDOM_3M.T3750");
	fixingRates.setQuoteDate(Date(11,6,2012));
	fixingRates.setRate(1.90321);

	_fixingRatesList.push_back(fixingRates);

	fixingRates.setQuoteId("GBPDOM_3M.T3750");
	fixingRates.setQuoteDate(Date(10,9,2012));
	fixingRates.setRate(2.15662);


	_fixingRatesList.push_back(fixingRates);

	fixingRates.setQuoteId("GBPDOM_3M.T3750");
	fixingRates.setQuoteDate(Date(16,4,2012));
	fixingRates.setQuoteType("RATE");
	fixingRates.setRate(1.75888);
	_fixingRatesList.push_back(fixingRates);


	fixingRates.setQuoteId("GBPDOM_3M.T3750");
	fixingRates.setQuoteDate(Date(16,7,2012));
	fixingRates.setQuoteType("RATE");
	fixingRates.setRate(2.00172);

	_fixingRatesList.push_back(fixingRates);


	fixingRates.setQuoteId("GBPDOM_1M.T3750");
	fixingRates.setQuoteDate(Date(15,10,2012));
	fixingRates.setQuoteType("RATE");
	fixingRates.setRate(1.90664);

	_fixingRatesList.push_back(fixingRates);

	fixingRates.setQuoteId("GBPDOM_2M.T3750");
	fixingRates.setQuoteDate(Date(15,10,2012));
	fixingRates.setQuoteType("RATE");
	fixingRates.setRate(2.21033);

	_fixingRatesList.push_back(fixingRates);


	// 6m GBP rates

		fixingRates.setQuoteId("GBPDOM_6M.T3750");
		fixingRates.setQuoteDate(Date(15,10,2010));
		fixingRates.setQuoteType("RATE");
		fixingRates.setRate(1.06212);
		_fixingRatesList.push_back(fixingRates);

		fixingRates.setQuoteId("GBPDOM_6M.T3750");
		fixingRates.setQuoteDate(Date(11,4,2011));
		fixingRates.setQuoteType("RATE");
		fixingRates.setRate(1.31088);

		_fixingRatesList.push_back(fixingRates);

		fixingRates.setQuoteId("GBPDOM_6M.T3750");
		fixingRates.setQuoteDate(Date(15,4,2011));
		fixingRates.setQuoteType("RATE");
		fixingRates.setRate(1.32055);
		_fixingRatesList.push_back(fixingRates);


		fixingRates.setQuoteId("GBPDOM_6M.T3750");
		fixingRates.setQuoteDate(Date(10,10,2011));
		fixingRates.setQuoteType("RATE");
		fixingRates.setRate(1.65832);
		_fixingRatesList.push_back(fixingRates);

		fixingRates.setQuoteId("GBPDOM_6M.T3750");
		fixingRates.setQuoteDate(Date(17,10,2011));
		fixingRates.setQuoteType("RATE");
		fixingRates.setRate(1.67247);

		_fixingRatesList.push_back(fixingRates);

		fixingRates.setQuoteId("GBPDOM_6M.T3750");
		fixingRates.setQuoteDate(Date(14,10,2011));
		fixingRates.setQuoteType("RATE");
		fixingRates.setRate(1.86877);
		_fixingRatesList.push_back(fixingRates);

		fixingRates.setQuoteId("GBPDOM_6M.T3750");
		fixingRates.setQuoteDate(Date(13,4,2012));
		fixingRates.setQuoteType("RATE");
		fixingRates.setRate(2.30593);
		_fixingRatesList.push_back(fixingRates);


		fixingRates.setQuoteId("GBPDOM_6M.T3750");
		fixingRates.setQuoteDate(Date(10,4,2012));
		fixingRates.setQuoteType("RATE");
		fixingRates.setRate(2.09532);

		_fixingRatesList.push_back(fixingRates);

		fixingRates.setQuoteId("GBPDOM_6M.T3750");
		fixingRates.setQuoteDate(Date(16,4,2012));
		fixingRates.setQuoteType("RATE");
		fixingRates.setRate(2.11085);
		_fixingRatesList.push_back(fixingRates);

        fixingRates.setQuoteId("GBPDOM_6M.T3750");
		fixingRates.setQuoteDate(Date(15,10,2012));
		fixingRates.setQuoteType("RATE");
		fixingRates.setRate(2.14390);
		_fixingRatesList.push_back(fixingRates);

		fixingRates.setQuoteId("GBPDOM_2M.T3750");
		fixingRates.setQuoteDate(Date(8,10,2012));
		fixingRates.setQuoteType("RATE");
		fixingRates.setRate(2.19241);

		_fixingRatesList.push_back(fixingRates);

		fixingRates.setQuoteId("GBPDOM_3M.T3750");
		fixingRates.setQuoteDate(Date(8,10,2012));
		fixingRates.setQuoteType("RATE");
		fixingRates.setRate(2.23020);

		_fixingRatesList.push_back(fixingRates);


		// few more fixings

		fixingRates.setQuoteId("GBPDOM_6M.T3750");
		fixingRates.setQuoteDate(Date(10,12,2010));
		fixingRates.setQuoteType("RATE");
		fixingRates.setRate(1.11690);

		_fixingRatesList.push_back(fixingRates);

		fixingRates.setQuoteId("GBPDOM_6M.T3750");
		fixingRates.setQuoteDate(Date(16,03,2011));
		fixingRates.setQuoteType("RATE");
		fixingRates.setRate(1.25714);

		_fixingRatesList.push_back(fixingRates);

		fixingRates.setQuoteId("GBPDOM_6M.T3750");
		fixingRates.setQuoteDate(Date(18,4,2011));
		fixingRates.setQuoteType("RATE");
		fixingRates.setRate(1.32411);

		_fixingRatesList.push_back(fixingRates);

		fixingRates.setQuoteId("GBPDOM_6M.T3750");
		fixingRates.setQuoteDate(Date(10,06,2011));
		fixingRates.setQuoteType("RATE");
		fixingRates.setRate(1.41515);

		_fixingRatesList.push_back(fixingRates);

		fixingRates.setQuoteId("GBPDOM_6M.T3750");
		fixingRates.setQuoteDate(Date(21,9,2011));
		fixingRates.setQuoteType("RATE");
		fixingRates.setRate(1.62153);

		_fixingRatesList.push_back(fixingRates);

		fixingRates.setQuoteId("GBPDOM_6M.T3750");
		fixingRates.setQuoteDate(Date(12,12,2011));
		fixingRates.setQuoteType("RATE");
		fixingRates.setRate(1.80717);

		_fixingRatesList.push_back(fixingRates);

		fixingRates.setQuoteId("GBPDOM_6M.T3750");
		fixingRates.setQuoteDate(Date(21,03,2012));
		fixingRates.setQuoteType("RATE");
		fixingRates.setRate(2.04596);

		_fixingRatesList.push_back(fixingRates);

		fixingRates.setQuoteId("GBPDOM_6M.T3750");
		fixingRates.setQuoteDate(Date(17,04,2012));
		fixingRates.setQuoteType("RATE");
		fixingRates.setRate(2.11345);

		_fixingRatesList.push_back(fixingRates);

		fixingRates.setQuoteId("GBPDOM_1M.T3750");
		fixingRates.setQuoteDate(Date(17,10,2012));
		fixingRates.setQuoteType("RATE");
		fixingRates.setRate(1.91441);

	    _fixingRatesList.push_back(fixingRates);

	    fixingRates.setQuoteId("GBPDOM_2M.T3750");
	    fixingRates.setQuoteDate(Date(17,10,2012));
	    fixingRates.setQuoteType("RATE");
	    fixingRates.setRate(2.21279);

	    _fixingRatesList.push_back(fixingRates);


		fixingRates.setQuoteId("GBPDOM_6M.T3750");
		fixingRates.setQuoteDate(Date(11,6,2012));
		fixingRates.setQuoteType("RATE");
		fixingRates.setRate(2.25962);

		_fixingRatesList.push_back(fixingRates);

		fixingRates.setQuoteId("GBPDOM_1M.T3750");
		fixingRates.setQuoteDate(Date(15,10,2010));
		fixingRates.setQuoteType("RATE");
		fixingRates.setRate(0.58605);

		_fixingRatesList.push_back(fixingRates);

		fixingRates.setQuoteId("GBPDOM_6M.T3750");
		fixingRates.setQuoteDate(Date(19,9,2012));
		fixingRates.setQuoteType("RATE");
		fixingRates.setRate(2.51517);

		_fixingRatesList.push_back(fixingRates);

		fixingRates.setQuoteId("GBPDOM_2M.T3750");
		fixingRates.setQuoteDate(Date(19,9,2012));
		fixingRates.setQuoteType("RATE");
		fixingRates.setRate(2.13972);

		_fixingRatesList.push_back(fixingRates);

		fixingRates.setQuoteId("GBPDOM_3M.T3750");
		fixingRates.setQuoteDate(Date(19,9,2012));
		fixingRates.setQuoteType("RATE");
		fixingRates.setRate(2.18032);

		_fixingRatesList.push_back(fixingRates);

		fixingRates.setQuoteId("GBPDOM_2M.T3750");
		fixingRates.setQuoteDate(Date(15,10,2010));
		fixingRates.setQuoteType("RATE");
		fixingRates.setRate(0.78165);

		_fixingRatesList.push_back(fixingRates);

		fixingRates.setQuoteId("GBPDOM_6M.T3750");
		fixingRates.setQuoteDate(Date(9,12,2011));
		fixingRates.setQuoteType("RATE");
		fixingRates.setRate(1.80132);

		_fixingRatesList.push_back(fixingRates);

		fixingRates.setQuoteId("GBPDOM_6M.T3750");
		fixingRates.setQuoteDate(Date(8,6,2012));
		fixingRates.setQuoteType("RATE");
		fixingRates.setRate(2.25438);

		_fixingRatesList.push_back(fixingRates);

		fixingRates.setQuoteId("GBPDOM_3M.T3750");
		fixingRates.setQuoteDate(Date(19,10,2010));
		fixingRates.setQuoteType("RATE");
		fixingRates.setRate(0.79265);

		_fixingRatesList.push_back(fixingRates);

		fixingRates.setQuoteId("GBPDOM_3M.T3750");
		fixingRates.setQuoteDate(Date(15,10,2010));
		fixingRates.setQuoteType("RATE");
		fixingRates.setRate(0.79059);

		_fixingRatesList.push_back(fixingRates);


		fixingRates.setQuoteId("GBP/USD_BOESAF");
		fixingRates.setQuoteDate(Date(15,10,2010));
		fixingRates.setQuoteType("PRICE");
		fixingRates.setRate(1.516);

		_fixingRatesList.push_back(fixingRates);

		fixingRates.setQuoteId("GBP/USD_BOESAF");
		fixingRates.setQuoteDate(Date(15,04,2011));
		fixingRates.setQuoteType("PRICE");
		fixingRates.setRate(1.520);

		_fixingRatesList.push_back(fixingRates);


		fixingRates.setQuoteId("GBP/USD_BOESAF");
		fixingRates.setQuoteDate(Date(17,10,2011));
		fixingRates.setQuoteType("PRICE");
		fixingRates.setRate(1.612);

		_fixingRatesList.push_back(fixingRates);


		fixingRates.setQuoteId("GBP/USD_BOESAF");
		fixingRates.setQuoteDate(Date(16,04,2012));
		fixingRates.setQuoteType("PRICE");
		fixingRates.setRate(1.630);

		_fixingRatesList.push_back(fixingRates);

		fixingRates.setQuoteId("GBP/USD_BOESAF");
		fixingRates.setQuoteDate(Date(15,10,2012));
		fixingRates.setQuoteType("PRICE");
		fixingRates.setRate(1.638);

		_fixingRatesList.push_back(fixingRates);



	while ( noOfResets != 1000 )
	{
		rate = rate + 0.0005;



		fixingRates.setQuoteId("GBPDOM_6M.T3750");
		fixingRates.setQuoteDate(Date(11,10,2010) + Period(noOfResets,Days));
		fixingRates.setRate(rate + 0.002);

		_fixingRatesList.push_back(fixingRates);

		fixingRates.setQuoteId("GBPDOM_1M.T3750");
		fixingRates.setQuoteDate(Date(11,10,2010) + Period(noOfResets,Days));
		fixingRates.setRate(rate - 0.001);

		_fixingRatesList.push_back(fixingRates);


		fixingRates.setQuoteId("GBPDOM_2M.T3750");
		fixingRates.setQuoteDate(Date(11,10,2010) + Period(noOfResets,Days));
		fixingRates.setRate(rate + 0.0005);

		_fixingRatesList.push_back(fixingRates);
		noOfResets++;

	}


	// only when we need to debug

			std::list < FixingRates > ::iterator iterFixingRates = FixingRates::getFixingRatesList().begin () ;

					int resetsCnt = FixingRates::getFixingRatesList().size();
					logFile << "No of Elements are :" << resetsCnt;


			         for ( ; iterFixingRates != FixingRates::getFixingRatesList().end () ; ++iterFixingRates )
			         {

			        	 logFile << "Fixing Rates are : ";
			        	 logFile << iterFixingRates->getQuoteId() << " : " <<  iterFixingRates->getQuoteDate() << " : " << iterFixingRates->getRate() << endl;
			         }

   */

}

double FixingRates::getFixingRate( Date qDate, Date resetStartDate, String quoteId)
{

	double rate = 0.0; // rate 0.0 to start with - this is a major assumption

	if (  qDate <= Date::todaysDate() )
	{
		std::list < FixingRates > ::iterator iterFixingRates = FixingRates::getFixingRatesList().begin () ;

        for ( ; iterFixingRates != FixingRates::getFixingRatesList().end () ; ++iterFixingRates )
        {
        	 if ( iterFixingRates->getQuoteDate() == qDate &&  iterFixingRates->getQuoteId() == quoteId )
        	 {
	        		 if ( iterFixingRates->getQuoteType() == "RATE" )
				        {
				        	rate = iterFixingRates->getRate()/100;
				        	break;
				        }
				     else
				        {
				        	 rate = iterFixingRates->getRate();
				        	 break;
				        }
			  }
		}
	}
	 // if it comes here means , it could be for projected rate
		if ( qDate > Date::todaysDate() || ( qDate == Date::todaysDate() && rate == 0.0 ))
		{
			const Date resetEndDate = resetStartDate + MoneyMkt::find(quoteId)->getMaturityDateOffset();
			const Calendar * fwdCal = MoneyMkt::find(quoteId)->getCalendar() ;
			Date adjEndDate = MoneyMkt::find(quoteId)->getBusDayConv()->adjustToBusDay(resetEndDate, *fwdCal);

			double dcf = MoneyMkt::find(quoteId)->getDayCountConv()->getFraction( resetStartDate,
					adjEndDate , 0,0, (int) (MoneyMkt::find(quoteId)->getMaturityDateOffset().frequency()) ) ;

			boost::shared_ptr<IRDConnect::Curve>  curvePtr = CurveCache::instance().find(Util::getCurveDate(), std::string(MoneyMkt::find(quoteId)->getFwdCurve())) ; //(dates , zcdfs ) ;
			rate = curvePtr->getForwardRate ( resetStartDate, adjEndDate , dcf ) ;
			logFile << "Fwd rate and DCF for period : " << rate << " : " << dcf << " : " << resetStartDate << "  :  " <<  adjEndDate << endl;

		}
return rate;

}

double FixingRates::getFixingRate( Date qDate, String stubAIndex, String stubBIndex,
		Date couponStartDate, Date couponEndDate, const BusDayConv * busDay )
{

	Period ATenor = MoneyMkt::find(stubAIndex)->getMaturityDateOffset();
	Period BTenor = MoneyMkt::find(stubBIndex)->getMaturityDateOffset();

	logFile << "print stub tenors " << ATenor << " : " << BTenor << " : " << stubAIndex << " : " << stubBIndex << endl;

	double stubARate = 0.0;
	double stubBRate = 0.0;
	double stubRate = 0.0; // interpolated rate
	bool needInterpolation = true;
	bool stubAFound = false;
	bool stubBFound = false;

	if ( qDate <= Date::todaysDate() )
	{
			std::list < FixingRates > ::iterator iterFixingRates = FixingRates::getFixingRatesList().begin () ;

				        for ( ; iterFixingRates != FixingRates::getFixingRatesList().end () ; ++iterFixingRates )
				        {
				        	 if ( iterFixingRates->getQuoteDate() == qDate &&  iterFixingRates->getQuoteId() == stubAIndex )
				        	 {
				        		 stubARate = iterFixingRates->getRate()/100;
				        		 stubAFound = true;

				        		 if ( stubBFound )
				        			 break;
				        	 }
				        	 else if ( iterFixingRates->getQuoteDate() == qDate &&  iterFixingRates->getQuoteId() == stubBIndex )
				        	 {
				        			stubBRate = iterFixingRates->getRate()/100;
				        			stubBFound = true;

				        			if ( stubAFound )
				        				break;
				        	 }
				        	 else if ( stubAIndex == stubBIndex && ( iterFixingRates->getQuoteDate() == qDate ) )
				        	 {
				        			stubRate = iterFixingRates->getRate()/100; // no interpolation needed
				        			needInterpolation = false;
				        			return stubRate; // khatham
				        	 }
				        }

	}


	if ( qDate > Date::todaysDate() || ( qDate == Date::todaysDate() && stubARate == 0.0 ))
	{
			const Date resetEndDate = couponStartDate + MoneyMkt::find(stubAIndex)->getMaturityDateOffset();
			const Calendar * fwdCal = MoneyMkt::find(stubAIndex)->getCalendar() ;
			Date adjEndDate = MoneyMkt::find(stubAIndex)->getBusDayConv()->adjustToBusDay(resetEndDate, *fwdCal);

			double dcf = MoneyMkt::find(stubAIndex)->getDayCountConv()->getFraction( couponStartDate,
						adjEndDate , 0,0, 0)  ;// no of periods is not imp here - so last argument is 0

			boost::shared_ptr<IRDConnect::Curve>  curvePtr = CurveCache::instance().find(Util::getCurveDate(),std::string(MoneyMkt::find(stubAIndex)->getFwdCurve()) ) ; //(dates , zcdfs ) ;
			stubARate = curvePtr->getForwardRate ( couponStartDate, adjEndDate , dcf ) ;
			logFile << "Stub A Fwd rate and DCF for period : " << stubARate << " : " << dcf << " : " << couponStartDate << "  :  " <<  adjEndDate << endl;

	}

	if ( qDate > Date::todaysDate() || ( qDate == Date::todaysDate() && stubARate == 0.0 ))
	{

			const Date resetEndDate = couponStartDate + MoneyMkt::find(stubBIndex)->getMaturityDateOffset();
			const Calendar * fwdCal = MoneyMkt::find(stubBIndex)->getCalendar() ;
			Date adjEndDate = MoneyMkt::find(stubBIndex)->getBusDayConv()->adjustToBusDay(resetEndDate, *fwdCal);

			double dcf = MoneyMkt::find(stubBIndex)->getDayCountConv()->getFraction( couponStartDate,
					adjEndDate , 0,0, 0 ) ;// no of periods is not imp here - so last argument is 0

			boost::shared_ptr<IRDConnect::Curve>  curvePtr = CurveCache::instance().find(Util::getCurveDate(),std::string(MoneyMkt::find(stubAIndex)->getFwdCurve())) ; //(dates , zcdfs ) ;
			stubBRate = curvePtr->getForwardRate ( couponStartDate, adjEndDate , dcf ) ;
			logFile << "Stub B Fwd rate and DCF for period : " << stubBRate << " : " << dcf << " : " << couponStartDate << "  :  " <<  adjEndDate << endl;

	 }

				  if ( needInterpolation )
				  {
					  //std::set < std::string > _stubCals;

					  //_stubCals.insert("LON");

					  //const std::string busDayTmp = "MOD" ;
					  //const BusDayConv * stubBusDay = BusDayConv::find(busDayTmp);

					  //Date startDate = busDay->adjustToBusDay(couponStartDate + ATenor, *CalendarUtil::getCalendar(_stubCals));

					  Date startDate = busDay->adjustToBusDay(couponStartDate + ATenor,  *MoneyMkt::find(stubAIndex)->getCalendar());

					  long startDays = startDate.serialNumber();

					  //Date endDate = busDay->adjustToBusDay(couponStartDate + BTenor, *CalendarUtil::getCalendar(_stubCals));

					  Date endDate = busDay->adjustToBusDay(couponStartDate + BTenor, *MoneyMkt::find(stubBIndex)->getCalendar());

					  long endDays = endDate.serialNumber();

					  long stubDays = couponEndDate.serialNumber();

					  logFile << "stub Dates : " << startDate << " : " << endDate << " : " << couponEndDate << endl;

	    		          std::vector<long> stubs ;

				          stubs.push_back ( startDays ) ;
				          stubs.push_back ( endDays ) ;

				          std::vector<double> stubRates ;
				          stubRates.push_back ( stubARate ) ;
				          stubRates.push_back ( stubBRate ) ;

				          for ( unsigned int i=0 ;i<stubs.size(); i++)
				          {
				        	  logFile << "I " <<i << " Days " << stubs[i] << "  : " << stubRates[i]  << endl ;
				          }


				          LinearInterpolationIRD<long, double> interPol ( stubs, stubRates );

				          double r = interPol( stubDays);

				          logFile << stubDays <<  " Interpolated Rate is : " << r << endl;

				          return r; // return the value

				  }

return 0.0; // rate not present

}

String FixingRates::getFixingQuote( String index, Period stubTenor)
{
/*
	String srcPage = MoneyMkt::find(index)->getSrcPage();
		String mmMasterId = MoneyMkt::find(index)->getMMMasterId();
		//const Period maturityDateOffset = MoneyMkt::find(index)->getMaturityDateOffset();

		cout << "Index passed : src page : mmMasterId " << index << ":" << srcPage << ":" << mmMasterId << endl;

		String stubIndex =  MoneyMkt::find( mmMasterId, stubTenor, srcPage );

		cout << "Stub Index is " << stubIndex << endl;

		return stubIndex;
*/

	if ( stubTenor.units() == Months && stubTenor.length() == 1)
			return "GBPDOM_1M.T3750";
		else if ( stubTenor.units() == Months && stubTenor.length() == 2)
			return "GBPDOM_2M.T3750";
		else if ( stubTenor.units() == Months && stubTenor.length() == 3)
				return "GBPDOM_3M.T3750";
		else if ( stubTenor.units() == Months && stubTenor.length() == 4)
				return "GBPDOM_4M.T3750";
		else if ( stubTenor.units() == Months && stubTenor.length() == 5)
				return "GBPDOM_5M.T3750";
		else if ( stubTenor.units() == Months && stubTenor.length() == 6)
				return "GBPDOM_6M.T3750";
		else if ( stubTenor.units() == Weeks && stubTenor.length() == 1)
				return "GBPDOM_1W.T3750";
		else if ( stubTenor.units() == Weeks && stubTenor.length() == 2)
				return "GBPDOM_2W.T3750";
		else if ( stubTenor.units() == Months && stubTenor.length() == 3)
				return "GBPDOM_3W.T3750";
		else if ( stubTenor.units() == Days && stubTenor.length() == 2)
				return "GBPDOM_2D.T3750";
		else
			return index;

}
