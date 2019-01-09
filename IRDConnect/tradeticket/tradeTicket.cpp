#include<iostream>
#include<string>
#include "tradeTicket.h"

using namespace std;

namespace IRDConnect {

TradeTicket::TradeTicket()
{
	// do nothing
}
TradeTicket::~TradeTicket()
{
	// do nothing
}

TradeTicket::TradeTicket (

String   		alternateRef,
String  		bookingType,
String  		customerAccount,
Date  			earlyTermDate,
String  		earlyTermReason,
String  		externalSystem,
String  		externalRef,
String  		firmAccount,
String  		flowStatus,
String  		lastModifiedBy,
String  		lastVerifiedBy,
String  		legalEntity,
String  		location,
String  		matchingStatus,
Date  			terminationDate,
String  		modifiedTimeStamp,
String  		operationsRef,
String  		originalTradeRef,
String  		productType,
String  		salesPerson,
Date  			effectiveDate,
String  		subType,
Date  			tradeDate,
String  		trader,
String  		tradeRef,
String  		tradeRemarks,
String  		tradeStatus,
String  		tradeType,
double  		tradeVersion,
String  		verifiedTimeStamp,
String  		washAccount
)
{

_alternateRef		=	alternateRef;
_bookingType		=	bookingType;
_customerAccount	=	customerAccount;
_externalSystem		=	externalSystem;
_externalRef		=	externalRef;
_earlyTermDate		=	earlyTermDate;
_earlyTermReason	=	earlyTermReason;
_firmAccount		=	firmAccount;
_flowStatus			=	flowStatus;
_location			=	location;
_legalEntity		=	legalEntity;
_lastModifiedBy		=	lastModifiedBy;
_lastVerifiedBy		=	lastVerifiedBy;
_modifiedTimeStamp	=	modifiedTimeStamp;
_matchingStatus		=	matchingStatus;
_terminationDate	=	terminationDate;
_operationsRef		=	operationsRef;
_originalTradeRef	=	originalTradeRef;
_productType		=	productType;
_subType			=	subType;
_salesPerson		=	salesPerson;
_effectiveDate	    =	effectiveDate;
_trader				=	trader;
_tradeType			=	tradeType;
_tradeRef			=	tradeRef;
_tradeRemarks		=	tradeRemarks;
_tradeStatus		=	tradeStatus;
_tradeDate			=	tradeDate;
_tradeVersion 		=	tradeVersion;
_verifiedTimeStamp	=	verifiedTimeStamp;
_washAccount		=	washAccount;
}

}
