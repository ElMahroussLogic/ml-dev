/* -------------------------------------------

	Copyright ZKA Technologies

------------------------------------------- */

#include <FoundationKit/Foundation.hxx>
#include <FoundationKit/MLAllocator.hxx>
#include <FoundationKit/MLAlert.hxx>
#include <FoundationKit/MLXMLCoder.hxx>
#include <FoundationKit/MLApplication.hxx>
#include <FoundationKit/MLURL.hxx>
#include <thread>

MLInteger MLShowModalMain()
{
	MLApplication::shared().showAboutModal();
	return 0;
}
