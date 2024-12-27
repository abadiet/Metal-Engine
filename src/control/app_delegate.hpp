#ifndef APP_DELEGATE_HPP
#define APP_DELEGATE_HPP

#include <Foundation/Foundation.hpp>
#include <AppKit/AppKit.hpp>
#include <MetalKit/MetalKit.hpp>
#include <Metal/Metal.hpp>
#include "control/view_delegate.hpp"

class AppDelegate : public NS::ApplicationDelegate {

    public:
        ~AppDelegate();

        virtual void applicationWillFinishLaunching(NS::Notification* notification) override;
        virtual void applicationDidFinishLaunching(NS::Notification* notification) override;
        virtual bool applicationShouldTerminateAfterLastWindowClosed(NS::Application* sender) override;

    private:
        NS::Window* window;
        MTK::View* mtkView;
        MTL::Device* device;
        ViewDelegate* viewDelegate = nullptr;

};

#endif /* APP_DELEGATE_HPP */
