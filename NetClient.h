//---------------------------------------------------------------------------

#ifndef NetClientH
#define NetClientH
#include <System.Classes.hpp>
#include <FMX.Controls.hpp>
#include <FMX.Forms.hpp>
#include <FMX.StdCtrls.hpp>
#include <FMX.Types.hpp>
#include <IdBaseComponent.hpp>
#include <IdComponent.hpp>
#include <IdHTTP.hpp>
#include <IdTCPClient.hpp>
#include <IdTCPConnection.hpp>
#include <IdIOHandler.hpp>
#include <IdIOHandlerSocket.hpp>
#include <IdIOHandlerStack.hpp>
#include <IdSSL.hpp>
#include <IdSSLOpenSSL.hpp>
//---------------------------------------------------------------------------

class TNetClient
{

private:	// User declarations

public:		// User declarations
	TIdHTTP *IdHTTP;
	TMemoryStream * myStream;
	TIdSSLIOHandlerSocketOpenSSL *IdSSLIOHandlerSocketOpenSSL;
	__fastcall TNetClient(TComponent* Owner);
	TMemoryStream GetNetImg(String URL);
	String GetCookieValue(String CookieName);
	String GetHtml(String URL);
	String GetPhoneHtml(String URL);
	void SetCookies(String nDomain,String InputCookieRaw);
	String GetCookiesRaw() ;
};
#endif

