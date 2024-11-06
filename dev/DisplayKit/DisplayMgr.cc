/**
 *
 * Copyright (c) 2024 Amlal EL Mahrouss
 *
 */

#include <DisplayKit/DisplayKit.h>
#include <FoundationKit/MLAllocator.h>
#include <FoundationKit/MLPoint.h>
#include <FoundationKit/MLRect.h>

struct MLDisplay
{
    explicit MLDisplay(const MLChar* name)
        : d_name(name)
    {}

    ~MLDisplay() noexcept
    {
        d_name.dispose();
    }

    MLString d_name;
    MLPoint d_point;
    MLRect d_frame;
};

MLDisplayRef MLCreateDisplay(const MLChar* name, const MLInteger& x, const MLInteger& y, const MLInteger& w, const MLInteger& h)
{
    auto object = MLAllocator::shared().init<MLDisplay>(name);
    ML_MUST_PASS(object);

    object->d_point.x = x;
    object->d_point.y = y;

    object->d_frame.width = w;
    object->d_frame.height = h;

    return *reinterpret_cast<MLDisplayRef*>(object);
}

#define kInvalidAddressAsIntPtr 0UL

BOOL MLRemoveDisplay(MLDisplayRef& display)
{
    if (display == kInvalidAddressAsIntPtr) return NO;

    MLAllocator::shared().dispose<MLDisplay>(reinterpret_cast<MLDisplay*>(display));
    display = 0;

    return YES;
}
