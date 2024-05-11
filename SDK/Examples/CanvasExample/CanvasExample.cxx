/*
 * Created on Sat May 11 2024
 *
 * Copyright (c) 2024 SystemLabs B.V
 */

#include <MLCoreGraphicsContext.hxx>
#include <MLString.hxx>

int main(int argc, char const* argv[])
{
	MLCoreGraphicsContext* context = CGRequestContext(0, false, 1280, 720);

	context->Move(0, 0);
	context->Color(0xFF, 0xFF, 0xFF, 0.2);
	context->Rectangle(1280, 720, 0);
	context->GaussianBlur(100.0);
	context->Color(0xFF, 0xFF, 0xFF, 0.2);

	context->TextSize(15.0);
	context->Color(0xFF, 0xFF, 0xFF, 1);
	context->Move(5, 22);
	context->Font("SF Pro", false);
	context->Text("Install OS.");

	context->FlushAs("CanvasExample.png");

	MLLog("%s%s\n", context->toString().asConstBytes(), ", will be written.");

	CGReleaseContext(context);

	return 0;
}
