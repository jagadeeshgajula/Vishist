// Class automatically generated by Dev-C++ New Class wizard

#ifndef TRADETICKET_H
#define TRADETICKET_H

#include <iostream>
#include "irdString.h"
#include "date.h"
#include "rightToTerminate.h"
#include "additionalPayments.h"
#include <boost/shared_ptr.hpp>
#include "premiums.h"
#include "salesCredit.h"
#include "tradeMargin.h"


using namespace std;
using namespace boost;
using namespace IRDConnect;

namespace IRDConnect {

typedef std::list <  AdditionalPayments *  >  AdditionalPaymentsList;
typedef std::list <  SalesCredit *  >  SalesCreditList;
typedef std::list <  Premiums *  >  PremiumsList;

class TradeTicket
{
      
public:

TradeTicket();

virtual ~TradeTicket();

TradeTicket(
String  	alternateRef,
String  	bookingType,
String  	customerAccount,
Date  		earlyTermDate,
String  	earlyTermReason,
String  	externalSystem,
String  	externalRef,
String  	firmAccount,
String  	flowStatus,
String  	lastModifiedBy,
String  	lastVerifiedBy,
String  	legalEntity,
String  	location,
String  	matchingStatus,
Date  		terminationDate,
String  	modifiedTimeStamp,
String  	operationsRef,
String  	originalTradeRef,
String  	productType,
String  	salesPerson,
Date  		effectiveDate,
String  	subType,
Date  		tradeDate,
String  	trader,
String  	tradeRef,
String		tradeRemarks,
String  	tradeStatus,
String  	tradeType,
double  	tradeVersion,
String  	verifiedTimeStamp,
String  	washAccount
);


String  getAlternateRef (){return _alternateRef ;}
void setAlternateRef (String  alternateRef ){ _alternateRef = alternateRef ;}

String  getBookingType (){return _bookingType ;}
void setBookingType (String  bookingType ){ _bookingType = bookingType ;}

String  getCustomerAccount(){return _customerAccount;}
void setCustomerAccount(String  customerAccount){ _customerAccount = customerAccount;}

Date  getEarlyTermDate (){return _earlyTermDate ;}
void setEarlyTermDate (Date  earlyTermDate ){ _earlyTermDate = earlyTermDate ;}

String  getEarlyTermReason (){return _earlyTermReason ;}
void setEarlyTermReason (String  earlyTermReason ){ _earlyTermReason = earlyTermReason ;}

String  getExternalSystem (){return _externalSystem ;}
void setExternalSystem (String  externalSystem ){ _externalSystem = externalSystem ;}

String  getExternalRef (){return _externalRef ;}
void setExternalRef (String  externalRef ){ _externalRef = externalRef ;}

String  getFirmAccount(){return _firmAccount;}
void setFirmAccount(String  firmAccount){ _firmAccount = firmAccount;}

String  getFlowStatus (){return _flowStatus;}
void setFlowStatus (String  flowStatus ){ _flowStatus = flowStatus ;}

String  getLastModifiedBy (){return _lastModifiedBy ;}
void setLastModifiedBy (String  lastModifiedBy ){ _lastModifiedBy = lastModifiedBy ;}

String  getLastVerifiedBy (){return _lastVerifiedBy ;}
void setLastVerifiedBy (String  lastVerifiedBy ){ _lastVerifiedBy = lastVerifiedBy ;}

String  getLegalEntity (){return _legalEntity ;}
void setLegalEntity (String  legalEntity ){ _legalEntity =legalEntity ;}

String  getLocation(){ return  _location;}
void setLocation(String  location){ _location=location;}

String  getMatchingStatus (){return _matchingStatus ;}
void setMatchingStatus (String  matchingStatus ){ _matchingStatus = matchingStatus ;}

Date  getTerminationDate(){return _terminationDate;}
void setTerminationDate(Date  terminationDate){ _terminationDate = terminationDate;}

String  getModifiedTimeStamp (){return _modifiedTimeStamp ;}
void setModifiedTimeStamp (String  modifiedTimeStamp ){ _modifiedTimeStamp = modifiedTimeStamp ;}

String  getOperationsRef (){return _operationsRef ;}
void setOperationsRef (String  operationsRef ){ _operationsRef = operationsRef ;}

String  getOriginalTradeRef (){return _originalTradeRef;}
void setOriginalTradeRef (String  originalTradeRef ){ _originalTradeRef = originalTradeRef ;}

String  getProductType (){return _productType ;}
void setProductType (String  productType ){ _productType = productType ;}

String  getSalesPerson (){return _salesPerson;}
void setSalesPerson (String  salesPerson ){ _salesPerson = salesPerson ;}

Date  getEffectiveDate(){return _effectiveDate;}
void setEffectiveDate(Date  effectiveDate){_effectiveDate = effectiveDate;}

String  getSubType (){return _subType ;}
void setSubType (String  subType ){ _subType = subType ;}

Date  getTradeDate(){return _tradeDate;}
void setTradeDate(Date  tradeDate){ _tradeDate = tradeDate; }

String  getTrader(){return _trader;}
void setTrader (String  trader ){ _trader = trader ;}

String  getTradeRef() { return _tradeRef;}
void setTradeRef(String  tradeRef) { _tradeRef = tradeRef; }

String  getTradeRemarks() { return _tradeRemarks;}
void setTradeRemarks(String  tradeRemarks) { _tradeRemarks = tradeRemarks; }

String  getTradeStatus (){return _tradeStatus;}
void setTradeStatus (String  tradeStatus ){ _tradeStatus = tradeStatus ;}

String  getTradeType (){return _tradeType ;}
void setTradeType (String  tradeType ){ _tradeType = tradeType ;}

double  getTradeVersion(){return _tradeVersion;}
void setTradeVersion(double  tradeVersion){ _tradeVersion = tradeVersion; }

String  getVerifiedTimeStamp (){return _verifiedTimeStamp ;}
void setVerifiedTimeStamp (String  verifiedTimeStamp){ _verifiedTimeStamp = verifiedTimeStamp ;}

String  getWashAccount (){return _washAccount;}
void setWashAccount(String  washAccount ){ _washAccount = washAccount ;}

int  getNoOfLegs (){return  _noOfLegs;}
void setNoOfLegs(int  noOfLegs ){ _noOfLegs = noOfLegs ;}

RightToTerminate * getRightToTerminate () { return _rightToTerminate;};
void setRightToTerminate( RightToTerminate * rightToTerminate) { _rightToTerminate = rightToTerminate; };

AdditionalPaymentsList & getAdditionalPayments() { return _additionalPaymentsList; };

void setAdditionalPayments(AdditionalPayments * fee )
{
	_additionalPaymentsList.push_back(fee);
};

SalesCreditList & getSalesCredits() { return _salesCreditList; };

void setSalesCredit(SalesCredit * sc )
{
	_salesCreditList.push_back(sc);
};

PremiumsList & getPremiums() { return _premiumsList; };

void setPremiums(Premiums * premium )
{
	_premiumsList.push_back(premium);
};

TradeMargin * getTradeMargin() { return _tradeMargin; };
void setTradeMargin( TradeMargin * tradeMargin ) { _tradeMargin = tradeMargin; };


protected:

String genSeqNo();

String  	_alternateRef;
String  	_bookingType;
String  	_customerAccount;
Date    	_earlyTermDate;
String  	_earlyTermReason;
String  	_externalRef;
String  	_externalSystem;
String  	_firmAccount;
String  	_flowStatus;
String  	_lastModifiedBy;
String  	_lastVerifiedBy;
String  	_legalEntity;
String  	_location;
String  	_matchingStatus;
Date  		_terminationDate;
String  	_modifiedTimeStamp;
int 		_noOfLegs;
String  	_operationsRef;
String  	_originalTradeRef;
String  	_productType;
String  	_salesPerson;
Date  		_effectiveDate;
String  	_subType;
Date  		_tradeDate;
String  	_trader;
String  	_tradeRef;
String		_tradeRemarks;
String  	_tradeStatus;
String  	_tradeType;
double 		_tradeVersion;
String  	_verifiedTimeStamp;
String  	_washAccount;

AdditionalPaymentsList  _additionalPaymentsList;

SalesCreditList  _salesCreditList;

PremiumsList  _premiumsList;

RightToTerminate * _rightToTerminate;

TradeMargin * _tradeMargin;

};

}

#endif // TRADETICKET_H