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
	constexpr auto cWidth  = 1000;
	constexpr auto cHeight = 666;

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

	cContext->PDF(pdfRef.asConstBytes())->Start();

	cContext->PageLabel("QR")->ThumbnailSize(cWidth, cHeight);

	cContext->Move(0, 0);

	qr::Qr<8> qrCode;
	qrCode.encode(argv[1], strlen(argv[1]), qr::Ecc::H, 0);

	qr::QrDelegate delegate;
	delegate.draw(qrCode, 0, 0);

	MLLog("Object: %@ will be destroyed.\n", cContext);

	CGReleaseContext(cContext);

	pdfRef.dispose();

	return 0;
}
