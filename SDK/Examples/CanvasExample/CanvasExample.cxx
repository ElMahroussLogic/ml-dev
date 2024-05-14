/*
 * Created on Sat May 11 2024
 *
 * Copyright (c) 2024 SoftwareLabs B.V
 */

#include <MLCoreGraphicsContext.hxx>
#include <MLString.hxx>
#include <string.h>

int main(int argc, char const* argv[])
{
	MLCoreGraphicsContext* context = CGRequestContext(0, false, 1000, 666);

	context->Start()->Image("rsrc://CanvasBackground.png", 1000, 666, 0, 0);

	context->Color(1, 1, 1, 0.200)->Move(50.0, 100.0)->Rectangle(200, 200, 0)->Blur(400, 200, 200);

	context->Color(.2, .2, .2, 1);
	context->Stroke(0.5);

	context->WriteTo("rsrc://CanvasExample.png")->End();

	CGReleaseContext(context);

	return 0;
}
