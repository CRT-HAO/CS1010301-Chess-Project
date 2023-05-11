/**
 *  File: GUI.cpp
 *  Author: 張皓鈞(HAO) m831718@gmail.com
 *  Create Date: 2023/04/22 20:39:44
 *  Editor: 張皓鈞(HAO) m831718@gmail.com
 *  Update Date: 2023/05/12 03:21:28
 *  Description: GUI
 */

#include "gui/GUI.hpp"

#include <iostream>

#define WINDOW_WIDTH 1920
#define WINDOW_HEIGHT 1080

GUI::GUI()
{
    Settings settings;

    settings.force_cpu_renderer = false;

    ///
    /// Create our main App instance.
    ///
    app_ = App::Create(settings);

    ///
    /// Create a resizable window by passing by OR'ing our window flags with
    /// kWindowFlags_Resizable.
    ///
    window_ = Window::Create(app_->main_monitor(), WINDOW_WIDTH, WINDOW_HEIGHT,
                             true, kWindowFlags_Titled | kWindowFlags_Resizable);

    ///
    /// Create our HTML overlay-- we don't care about its initial size and
    /// position because it'll be calculated when we call OnResize() below.
    ///
    overlay_ = Overlay::Create(window_, 1, 1, 0, 0);

    ///
    /// Force a call to OnResize to perform size/layout of our overlay.
    ///
    OnResize(window_.get(), window_->width(), window_->height());

    ///
    /// Load a page into our overlay's View
    ///
    overlay_->view()->LoadURL("file:///debug.html");

    ///
    /// Register our GUI instance as an AppListener so we can handle the
    /// App's OnUpdate event below.
    ///
    app_->set_listener(this);

    ///
    /// Register our GUI instance as a WindowListener so we can handle the
    /// Window's OnResize event below.
    ///
    window_->set_listener(this);

    ///
    /// Register our GUI instance as a LoadListener so we can handle the
    /// View's OnFinishLoading and OnDOMReady events below.
    ///
    overlay_->view()->set_load_listener(this);

    ///
    /// Register our GUI instance as a ViewListener so we can handle the
    /// View's OnChangeCursor and OnChangeTitle events below.
    ///
    overlay_->view()->set_view_listener(this);
}

GUI::~GUI()
{
}

void GUI::Run()
{
    app_->Run();
}

void GUI::OnUpdate()
{
    ///
    /// This is called repeatedly from the application's update loop.
    ///
    /// You should update any app logic here.
    ///
}

void GUI::OnClose(ultralight::Window *window)
{
    app_->Quit();
}

void GUI::OnResize(ultralight::Window *window, uint32_t width, uint32_t height)
{
    ///
    /// This is called whenever the window changes size (values in pixels).
    ///
    /// We resize our overlay here to take up the entire window.
    ///
    overlay_->Resize(width, height);
}

void GUI::OnFinishLoading(ultralight::View *caller,
                          uint64_t frame_id,
                          bool is_main_frame,
                          const String &url)
{
    ///
    /// This is called when a frame finishes loading on the page.
    ///
}

void GUI::OnDOMReady(ultralight::View *caller,
                     uint64_t frame_id,
                     bool is_main_frame,
                     const String &url)
{
    // Acquire the JS execution context for the current page.
    //
    // This call will lock the execution context for the current
    // thread as long as the Ref<> is alive.
    //
    RefPtr<JSContext> context = caller->LockJSContext();

    // Get the underlying JSContextRef for use with the
    // JavaScriptCore C API.
    JSContextRef ctx = context->ctx();

    // Get the global JavaScript object (aka 'window')
    JSObjectRef globalObj = JSContextGetGlobalObject(ctx);

    /**
     * Test
     */
    JSStringRef name_Test = JSStringCreateWithUTF8CString("apiTest");

    JSObjectRef func_Test =
        JSObjectMakeFunctionWithCallback(ctx, name_Test, GUI::Test);

    JSObjectSetProperty(ctx, globalObj, name_Test, func_Test, 0, 0);

    JSStringRelease(name_Test);
}

void GUI::OnChangeCursor(ultralight::View *caller,
                         Cursor cursor)
{
    ///
    /// This is called whenever the page requests to change the cursor.
    ///
    /// We update the main window's cursor here.
    ///
    window_->SetCursor(cursor);
}

void GUI::OnChangeTitle(ultralight::View *caller,
                        const String &title)
{
    ///
    /// This is called whenever the page requests to change the title.
    ///
    /// We update the main window's title here.
    ///
    window_->SetTitle(title.utf8().data());
}

JSValueRef GUI::JsonToJSValue(JSContextRef ctx, const Json &json)
{
    JSStringRef jsonStr =
        JSStringCreateWithUTF8CString(json.dump().c_str());
    JSValueRef r = JSValueMakeFromJSONString(ctx, jsonStr);
    JSStringRelease(jsonStr);
    return r;
}

JSValueRef GUI::Test(JSContextRef ctx, JSObjectRef function,
                     JSObjectRef thisObject, size_t argumentCount,
                     const JSValueRef arguments[],
                     JSValueRef *exception)
{
    Json data;
    data["width"] = 5432;
    data["height"] = 9487;
    return GUI::JsonToJSValue(ctx, data);
}