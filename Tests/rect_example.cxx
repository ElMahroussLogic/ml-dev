/* -------------------------------------------

	Copyright ZKA Technologies

------------------------------------------- */

#include <GraphicsKit/GraphicsKit.hxx>

int main(int argc, char const *argv[])
{
    MLCoreGraphicsContext* ctx = CGRequestContext(0, false, 800, 600);

    ctx->SVG("./test.svg")->start()->color(0x00, 0x00, 0x00, 0xFF)->move(0, 0)->rectangle(800, 600, 0)->end();

    CGReleaseContext(ctx);

    return 0;
}
