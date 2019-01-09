#include<iostream>
#include<string>
#include "irdString.h"

using namespace std;
using namespace IRDConnect;

namespace IRDConnect {


class  ExternalSystemTrades
{

public:

ExternalSystemTrades(){;};              //  Constructor declared

ExternalSystemTrades(
String 		externalSystem,
String 		externalSystemRef,
String 		modifiedTimestamp,
String 		tradeRef,
double 		tradeVersion,
String 		verifiedBy)                //constructor with six orguments

{
_externalSystem		=	externalSystem;
_externalSystemRef	=	externalSystemRef;
_modifiedTimestamp	=	modifiedTimestamp;
_tradeRef			=	tradeRef;
_tradeVersion		=	tradeVersion;
_verifiedBy			=	verifiedBy;

}

String getExternalSystem(){return _externalSystem;}
void setExternalSystem(String externalSystem){ _externalSystem = externalSystem;}

String getExternalSystemRef(){return _externalSystemRef;}
void setExternalSystemRef(String externalSystemRef){ _externalSystemRef = externalSystemRef;}

String getModifiedTimestamp(){return _modifiedTimestamp;}
void setModifiedTimestamp(String modifiedTimestamp){ _modifiedTimestamp = modifiedTimestamp;}

String getTradeRef(){return _tradeRef;}
void setTradeRef(String tradeRef){ _tradeRef = tradeRef; }

double getTradeVersion(){return _tradeVersion;}
void setTradeVersion(double tradeVersion){ _tradeVersion = tradeVersion;}

String getVerifiedBy(){return _verifiedBy;}
void setVerifiedBy(String verifiedBy){ _verifiedBy = verifiedBy;}

protected: 
   
String 		_externalSystem;            // ExternalSystem is initialized to the empty String
String 		_externalSystemRef;         //ExternalSystemRef is initialized to the empty string
String 		_modifiedTimestamp;          // ModifiedTimestamp is initialized to the empty String
String 		_tradeRef;         // TradeRef is initialized to the empty string
double 		_tradeVersion;  // TradeVersion is initialized to the empty number
String 		_verifiedBy;        // VerifiedBy is initialized to the empty string
};       
}
