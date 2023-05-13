/**
 *  File: GUI.cpp
 *  Author: 張皓鈞(HAO) m831718@gmail.com
 *  Create Date: 2023/04/22 20:39:44
 *  Editor: 張皓鈞(HAO) m831718@gmail.com
 *  Update Date: 2023/05/14 02:16:14
 *  Description: GUI
 */

#include "gui/GUI.hpp"
#include "core/player/PlayerUtil.hpp"

#include <iostream>
#include <string>
#include <vector>

#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720

Game game;

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

#if DEBUG
    // Start inspector whe debugging
    // app_->renderer()->StartRemoteInspectorServer("127.0.0.1", 19998);
    overlay_->view()->CreateLocalInspectorView();
#endif
}

RefPtr<View> GUI::OnCreateInspectorView(ultralight::View *caller, bool is_local,
                                        const String &inspected_url)
{
    inspector_ = new Inspector(app_);
    return inspector_->GetOverlay()->view();
}

GUI::~GUI()
{
    if ( inspector_ != nullptr )
        delete inspector_;
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
     * GetCurrentPlayer
     */
    JSStringRef name_GetCurrentPlayer =
        JSStringCreateWithUTF8CString("apiGetCurrentPlayer");

    JSObjectRef func_GetCurrentPlayer =
        JSObjectMakeFunctionWithCallback(ctx, name_GetCurrentPlayer,
                                         GUI::GetCurrentPlayer);

    JSObjectSetProperty(ctx, globalObj, name_GetCurrentPlayer,
                        func_GetCurrentPlayer, 0, 0);

    JSStringRelease(name_GetCurrentPlayer);

    /**
     * Test
     */
    JSStringRef name_Test = JSStringCreateWithUTF8CString("apiTest");

    JSObjectRef func_Test =
        JSObjectMakeFunctionWithCallback(ctx, name_Test, GUI::Test);

    JSObjectSetProperty(ctx, globalObj, name_Test, func_Test, 0, 0);

    JSStringRelease(name_Test);

    /**
     * GetBoard
     */
    JSStringRef name_GetBoard = JSStringCreateWithUTF8CString("apiGetBoard");

    JSObjectRef func_GetBoard =
        JSObjectMakeFunctionWithCallback(ctx, name_GetBoard, GUI::GetBoard);

    JSObjectSetProperty(ctx, globalObj, name_GetBoard, func_GetBoard, 0, 0);

    JSStringRelease(name_GetBoard);

    /**
     * GetBoardPieceMovablePos
     */
    JSStringRef name_GetBoardPieceMovablePos =
        JSStringCreateWithUTF8CString("apiGetBoardPieceMovablePos");

    JSObjectRef func_GetBoardPieceMovablePos =
        JSObjectMakeFunctionWithCallback(ctx, name_GetBoardPieceMovablePos,
                                         GUI::GetBoardPieceMovablePos);

    JSObjectSetProperty(ctx, globalObj, name_GetBoardPieceMovablePos,
                        func_GetBoardPieceMovablePos, 0, 0);

    JSStringRelease(name_GetBoardPieceMovablePos);

    /**
     * BoardMovePiece
     */
    JSStringRef name_BoardMovePiece =
        JSStringCreateWithUTF8CString("apiBoardMovePiece");

    JSObjectRef func_BoardMovePiece =
        JSObjectMakeFunctionWithCallback(ctx, name_BoardMovePiece,
                                         GUI::BoardMovePiece);

    JSObjectSetProperty(ctx, globalObj, name_BoardMovePiece,
                        func_BoardMovePiece, 0, 0);

    JSStringRelease(name_BoardMovePiece);
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

JSValueRef GUI::GetCurrentPlayer(JSContextRef ctx, JSObjectRef function,
                                 JSObjectRef thisObject, size_t argumentCount,
                                 const JSValueRef arguments[],
                                 JSValueRef *exception)
{
    std::string player = PlayerUtil::typeToString(game.getCurrentPlayerType());

    JSStringRef r_str = JSStringCreateWithUTF8CString(player.c_str());
    JSValueRef r = JSValueMakeString(ctx, r_str);
    JSStringRelease(r_str);

    return r;
}

JSValueRef GUI::GetBoard(JSContextRef ctx, JSObjectRef function,
                         JSObjectRef thisObject, size_t argumentCount,
                         const JSValueRef arguments[],
                         JSValueRef *exception)
{
    size_t width = game.getBoard().width();
    size_t height = game.getBoard().height();
    Json data;
    data["width"] = width;
    data["height"] = height;

    Json boardData;
    Position pos;
    for ( pos.y = 0; pos.y < height; ++pos.y )
    {
        Json rowData;
        for ( pos.x = 0; pos.x < width; ++pos.x )
        {
            Json pieceData;
            pieceData["type"] = "null";
            pieceData["owner"] = "null";
            pieceData["movable"] = false;
            if ( game.getBoard().isPositionPiece(pos) )
            {
                pieceData["type"] =
                    PieceUtil::typeToString(game.getBoard()(pos)->type());
                pieceData["owner"] =
                    PlayerUtil::typeToString(game.getBoard()(pos)->getOwner());
                pieceData["movable"] =
                    (game.getBoard()(pos)->getOwner() == game.getCurrentPlayerType());
            }
            rowData.push_back(pieceData);
        }
        boardData.push_back(rowData);
    }
    data["board"] = boardData;

    return GUI::JsonToJSValue(ctx, data);
}

JSValueRef GUI::GetBoardPieceMovablePos(JSContextRef ctx, JSObjectRef function,
                                        JSObjectRef thisObject, size_t argumentCount,
                                        const JSValueRef arguments[],
                                        JSValueRef *exception)
{
    // x, y
    if ( argumentCount < 2 ||
         !JSValueIsNumber(ctx, arguments[0]) ||
         !JSValueIsNumber(ctx, arguments[1]) )
        return JSValueMakeBoolean(ctx, false);

    Position pos;
    pos.x = JSValueToNumber(ctx, arguments[0], exception);
    pos.y = JSValueToNumber(ctx, arguments[1], exception);

    std::vector<Position> movablePos = game.getBoardPieceMovablePos(pos);

    Json data;
    for ( const Position &p : movablePos )
    {
        Json pJson;
        pJson["x"] = p.x;
        pJson["y"] = p.y;
        data.push_back(pJson);
    }

    return GUI::JsonToJSValue(ctx, data);
}

JSValueRef GUI::BoardMovePiece(JSContextRef ctx, JSObjectRef function,
                               JSObjectRef thisObject, size_t argumentCount,
                               const JSValueRef arguments[],
                               JSValueRef *exception)
{
    // from_x, from_y, to_x, to_y
    if ( argumentCount < 4 ||
         !JSValueIsNumber(ctx, arguments[0]) ||
         !JSValueIsNumber(ctx, arguments[1]) ||
         !JSValueIsNumber(ctx, arguments[2]) ||
         !JSValueIsNumber(ctx, arguments[3]) )
        return JSValueMakeBoolean(ctx, false);

    Position fromPos, toPos;
    fromPos.x = JSValueToNumber(ctx, arguments[0], exception);
    fromPos.y = JSValueToNumber(ctx, arguments[1], exception);
    toPos.x = JSValueToNumber(ctx, arguments[2], exception);
    toPos.y = JSValueToNumber(ctx, arguments[3], exception);

    Move move(game.getCurrentPlayerType(), fromPos, toPos);
    bool success = game.makeMove(move);

    JSValueRef r = JSValueMakeBoolean(ctx, success);

    return r;
}