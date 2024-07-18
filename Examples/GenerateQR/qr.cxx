/*
 * Created on Sat May 11 2024
 *
 * Copyright (c) 2024 ZKA Technologies
 */

#include <CoreAnimation/CoreAnimation.hxx>
#include <CoreFoundation/CoreFoundation.hxx>
#include <CoreGraphics/CoreGraphics.hxx>
#include <CoreFoundation/MLString.hxx>
#include <cstdio>

#include "qr.h"

int main(int argc, char const* argv[])
{
	cWidth  = 204;
	cHeight = 204;

	if (!argv[1])
	{
		printf("generate_qr: %s", "please provide a valid string!\n");
		return -1;
	}

	cContext = CGRequestContext(0, 0, cWidth, cHeight);

	if (!cContext)
	{
		perror("generate_qr");
		return -1;
	}

	auto pdfRef = r("QR.pdf");

	cContext->PDF(pdfRef.asConstBytes())->Start()->PageLabel("#QR_CODE");

	cContext->Move(0, 0);

	constexpr auto cVer = 4;
	constexpr auto cECC = qr::Ecc::H;

	qr::Qr<cVer> qrCode;
	qrCode.encode(argv[1], strlen(argv[1]), cECC, 0);

	qr::QrDelegate delegate;
	delegate.draw<cVer>(qrCode, 0, 0, argv[1]);

	cContext->Present();

	MLLog("Object: %@ will be destroyed.\n", cContext);

	CGReleaseContext(cContext);

	pdfRef.dispose();

	return 0;
}
