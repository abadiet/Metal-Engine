#include "controller/app_delegate.hpp"

#define UNUSED(x) (void)(x)


AppDelegate::~AppDelegate() {
    mtkView->release();
    window->release();
    device->release();
    delete renderer;
}

void AppDelegate::applicationWillFinishLaunching(NS::Notification* notification) {
    NS::Application* app = reinterpret_cast<NS::Application*>(notification->object());
    app->setActivationPolicy(NS::ActivationPolicy::ActivationPolicyRegular);
}

void AppDelegate::applicationDidFinishLaunching(NS::Notification* notification) {
    CGRect frame;
    frame.origin = {100.0, 100.0};
    frame.size = {1000.0, 750.0};

    window = NS::Window::alloc()->init(
        frame,
        NS::WindowStyleMaskClosable | NS::WindowStyleMaskTitled,
        NS::BackingStoreBuffered,
        false
    );

    device = MTL::CreateSystemDefaultDevice();

    mtkView = MTK::View::alloc()->init(frame, device);
    mtkView->setColorPixelFormat(MTL::PixelFormat::PixelFormatBGRA8Unorm_sRGB);
    mtkView->setClearColor(MTL::ClearColor::Make(1.0, 1.0, 0.6, 1.0));

    renderer = new Renderer(device);
    mtkView->setDelegate(renderer);

    window->setContentView(mtkView);
    window->setTitle(NS::String::string("Metal Engine", NS::StringEncoding::UTF8StringEncoding));
    window->makeKeyAndOrderFront(nullptr);

    NS::Application* app = reinterpret_cast<NS::Application*>(notification->object());
    app->activateIgnoringOtherApps(true);
}

bool AppDelegate::applicationShouldTerminateAfterLastWindowClosed(NS::Application* sender) {
    return true;
    UNUSED(sender);
}
