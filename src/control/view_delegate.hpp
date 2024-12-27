#ifndef VIEW_DELEGATE_HPP
#define VIEW_DELEGATE_HPP

#include <Metal/Metal.hpp>
#include <AppKit/AppKit.hpp>
#include <MetalKit/MetalKit.hpp>
#include "view/renderer.hpp"

class ViewDelegate : public MTK::ViewDelegate {

    public:
        ViewDelegate(MTL::Device* device);
        virtual ~ViewDelegate() override;
        virtual void drawInMTKView(MTK::View* view) override;

    private:
        Renderer* renderer;

};

#endif /* VIEW_DELEGATE_HPP */
