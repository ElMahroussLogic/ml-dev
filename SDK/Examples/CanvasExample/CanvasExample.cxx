/*
 * Created on Sat May 11 2024
 *
 * Copyright (c) 2024 SoftwareLabs B.V
 */

#include <CoreGraphics.hxx>
#include <MLString.hxx>
#include <string.h>

int main(int argc, char const* argv[])
{
	MLCoreGraphicsContext* context = CGRequestContext(0, 0, 1000, 666);

	context->PDF("rsrc://CanvasExample.pdf")->Start()->Image("rsrc://CanvasBackground.png", 1000, 666, 0, 0);

	context->Color(1.0, 1.0, 1.0, .4)->Move(0.0, 0.0)->Rectangle(1000, 666, 5);
	context->Color(1.0, 1.0, 1.0, 1.0)->Stroke(5.0);

	context->FontFamily("SF-Pro", true)->FontSize(20.0)->Move(50.0, 50.0)->Text("Hello, CoreGraphics!");

	context->End();

	CGReleaseContext(context);

	return 0;
}
