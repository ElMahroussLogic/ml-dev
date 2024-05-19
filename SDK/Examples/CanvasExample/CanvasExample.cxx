/*
 * Created on Sat May 11 2024
 *
 * Copyright (c) 2024 SoftwareLabs B.V
 */

#include <CoreGraphics.hxx>
#include <MLString.hxx>
#include <stdio.h>
#include <string.h>

int main(int argc, char const* argv[])
{
	MLCoreGraphicsContext* context = CGRequestContext(0, 0, 1000, 666);

	if (!context)
	{
		printf("Out of memory!\n");
		return -1;
	}

	auto pdfRef = r("CanvasExample.pdf");
	auto imageRef = r("CanvasBackground.png");

	context->PDF(pdfRef.asConstBytes())->Start()->Image(imageRef.asConstBytes(), 1000, 666, 0, 0);

	context->PageLabel("MLCoreGraphicsContext")->ThumbnailSize(64, 64);

	context->Color(1.0, 1.0, 1.0, .4)->Move(0.0, 0.0)->Rectangle(1000, 666, 5);
	context->Color(1.0, 1.0, 1.0, 1.0)->Stroke(5.0);

	context->FontFamily("Arial", true)->FontSize(20.0)->Move(50.0, 50.0)->Text(context->toString().asConstBytes());

	context->Present()->Image(imageRef.asConstBytes(), 1000, 666, 0, 0);

	context->PageLabel("Greet")->ThumbnailSize(64, 64);

	context->Color(1.0, 1.0, 1.0, .4)->Move(0.0, 0.0)->Rectangle(1000, 666, 5);
	context->Color(1.0, 1.0, 1.0, 1.0)->Stroke(5.0);

	context->FontFamily("Arial", true)->FontSize(20.0)->Move(50.0, 50.0)->Text("Hello again.");

	context->End();
	
	MLLog("Object: %@, will be destroyed.\n", context);

	CGReleaseContext(context);

	pdfRef.dispose();
	imageRef.dispose();

	return 0;
}
