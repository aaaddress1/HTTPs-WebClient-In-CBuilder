#pragma hdrstop
#include "NetClient.h"
#pragma package(smart_init)
#include "System.RegularExpressions.hpp"

__fastcall TNetClient::TNetClient(TComponent* Owner)
{
	this->IdHTTP = new TIdHTTP(NULL);
	this->IdHTTP->CookieManager = new TIdCookieManager(NULL) ;
	myStream = new TMemoryStream();
	this->IdHTTP->HandleRedirects = true;
	this->IdSSLIOHandlerSocketOpenSSL =  new TIdSSLIOHandlerSocketOpenSSL(NULL);
	this->IdHTTP->IOHandler = this->IdSSLIOHandlerSocketOpenSSL;
}

String TNetClient::GetCookieValue(String CookieName)
{
	if (this->IdHTTP->CookieManager->CookieCollection->Count == 0) return NULL;
	int Index = this->IdHTTP->CookieManager->CookieCollection->GetCookieIndex(CookieName);
	if (Index == -1) return NULL;
	return this->IdHTTP->CookieManager->CookieCollection->operator [](Index)->Value;
}

String TNetClient::GetPhoneHtml(String URL)
{
	try
	{
		this->IdHTTP->Request->UserAgent = "Mozilla/5.0 (Linux; U; Android 4.0.3; ko-kr; LG-L160L Build/IML74K) AppleWebkit/534.30 (KHTML, like Gecko) Version/4.0 Mobile Safari/534.30";
		String ret = this->IdHTTP->Get(URL);
		ret = StringReplace(ret,"&amp;","&",TReplaceFlags()<<rfReplaceAll);
		return ret;
	}
	catch(...)
	{
		//連線Fail
		return NULL;
	}
}

String TNetClient::GetHtml(String URL)
{
	try
	{
		this->IdHTTP->Request->UserAgent = "Mozilla/5.0 (Windows NT 6.1; rv:29.0) Gecko/20100101 Firefox/29.0";
		String ret = this->IdHTTP->Get(URL);
		ret = StringReplace(ret,"&amp;","&",TReplaceFlags()<<rfReplaceAll);
		return ret;
	}
	catch(const EIdHTTPProtocolException &e)
	{
		//連線Fail
		return NULL;
	}
}

void TNetClient::SetCookies(String nDomain,String InputCookieRaw)
{
	TMatchCollection matches = TRegEx::Matches(InputCookieRaw, L"([^=]+)=([^;]+);");
	TMatch match ;
	for (int i = 0; i < matches.Count ; i++)
	{
		match = matches[i] ;
		try
		{
			String KeyName = match.Groups[1].Value;
			String KeyValue = match.Groups[2].Value;
			TIdCookie *NewCookie = this->IdHTTP->CookieManager->CookieCollection->AddClientCookie(KeyName+ "=" + KeyValue);
			NewCookie->Domain = nDomain;
		} catch (...)
		{
		}
	}

}

String TNetClient::GetCookiesRaw()
{
	String nReturn = "";
	int Count = this->IdHTTP->CookieManager->CookieCollection->Count;
	for (int i = 0; i < Count; i++)
	{
		TIdCookie *CurrentCookie = this->IdHTTP->CookieManager->CookieCollection->operator [](i);
		nReturn += ( CurrentCookie->CookieName + "=" + CurrentCookie->Value +";");
	}
	return nReturn;
}
