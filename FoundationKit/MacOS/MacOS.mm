/* -------------------------------------------

    Copyright ZKA Technologies

------------------------------------------- */

#import <AppKit/AppKit.h>
#import <Foundation/Foundation.h>

int MLAlertBox(const char* title, const char* msg)
{
    NSAlert* alert = [[NSAlert alloc] init];
    alert.alertStyle = NSAlertStyleCritical;
    alert.messageText = @(msg);
    alert.informativeText = @(title);
    [alert runModal];

    [alert release];

    return 0;
}
