#define NS_PRIVATE_IMPLEMENTATION
#define MTL_PRIVATE_IMPLEMENTATION
#define MTK_PRIVATE_IMPLEMENTATION
#define CA_PRIVATE_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION

#include <Foundation/Foundation.hpp>
#include <AppKit/AppKit.hpp>
#include "controller/app_delegate.hpp"

#define UNUSED(x) (void)(x)


int main(int argc, char* argv[]){
    NS::AutoreleasePool* autoreleasePool;
    NS::Application* app;
    AppDelegate controller;

    autoreleasePool = NS::AutoreleasePool::alloc()->init();

    app = NS::Application::sharedApplication();
    app->setDelegate(&controller);
    app->run();

    autoreleasePool->release();

    return 0;

    UNUSED(argc);
    UNUSED(argv);
}
