/* -------------------------------------------

	Copyright ZKA Technologies

------------------------------------------- */

#include <GraphicsKit/GraphicsKit.hxx>

int main(int argc, char* argv[])
{
	MLCoreGraphicsContext* ctx = CGRequestContext(0, false, 1045, 1750);

	ctx->svg("./fb-output.svg")->start();
	ctx->color(0.6, 0.0, 0.69, 1)->move(0, 0)->rectangle(1045, 1750, 0);
	ctx->color(1, 1, 1, 1)->fontSize(100.0)->fontFamily("Inter", false)->move(20, 1750-110)->text("10:00", false);
	ctx->end();

	CGReleaseContext(ctx);

	return 0;
}
