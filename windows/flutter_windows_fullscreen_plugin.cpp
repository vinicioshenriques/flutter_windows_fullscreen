#include "include/flutter_windows_fullscreen/flutter_windows_fullscreen_plugin.h"

// This must be included before many other Windows headers.
#include <windows.h>

// For getPlatformVersion; remove unless needed for your plugin implementation.
#include <VersionHelpers.h>

#include <flutter/method_channel.h>
#include <flutter/plugin_registrar_windows.h>
#include <flutter/standard_method_codec.h>

#include <map>
#include <memory>
#include <sstream>

namespace {

  const char* kEnableFullscreenMethod = "enableFullscreen";
  const char* kDisableFullscreenMethod = "disableFullscreen";

class FlutterWindowsFullscreenPlugin : public flutter::Plugin {
 public:
  static void RegisterWithRegistrar(flutter::PluginRegistrarWindows *registrar);

  FlutterWindowsFullscreenPlugin();

  virtual ~FlutterWindowsFullscreenPlugin();

 private:
  // Called when a method is called on this plugin's channel from Dart.
  void HandleMethodCall(
      const flutter::MethodCall<flutter::EncodableValue> &method_call,
      std::unique_ptr<flutter::MethodResult<flutter::EncodableValue>> result);
};

// static
void FlutterWindowsFullscreenPlugin::RegisterWithRegistrar(
    flutter::PluginRegistrarWindows *registrar) {
  auto channel =
      std::make_unique<flutter::MethodChannel<flutter::EncodableValue>>(
          registrar->messenger(), "flutter_windows_fullscreen",
          &flutter::StandardMethodCodec::GetInstance());

  auto plugin = std::make_unique<FlutterWindowsFullscreenPlugin>();

  channel->SetMethodCallHandler(
      [plugin_pointer = plugin.get()](const auto &call, auto result) {
        plugin_pointer->HandleMethodCall(call, std::move(result));
      });

  registrar->AddPlugin(std::move(plugin));
}

FlutterWindowsFullscreenPlugin::FlutterWindowsFullscreenPlugin() {}

FlutterWindowsFullscreenPlugin::~FlutterWindowsFullscreenPlugin() {}

void FlutterWindowsFullscreenPlugin::HandleMethodCall(
    const flutter::MethodCall<flutter::EncodableValue> &method_call,
    std::unique_ptr<flutter::MethodResult<flutter::EncodableValue>> result) {
  // Replace "getPlatformVersion" check with your plugin's method.
  // See:
  // https://github.com/flutter/engine/tree/master/shell/platform/common/cpp/client_wrapper/include/flutter
  // and
  // https://github.com/flutter/engine/tree/master/shell/platform/glfw/client_wrapper/include/flutter
  // for the relevant Flutter APIs.
  if (method_call.method_name().compare(kEnableFullscreenMethod) == 0) {

    HWND hwnd = GetActiveWindow();
    int w = GetSystemMetrics(SM_CXSCREEN);
    int h = GetSystemMetrics(SM_CYSCREEN);
    SetWindowLongPtr(hwnd, GWL_STYLE, WS_VISIBLE | WS_POPUP);
    SetWindowPos(hwnd, HWND_TOP, 0, 0, w, h, SWP_FRAMECHANGED);
    
    result->Success();
  } else if (method_call.method_name().compare(kDisableFullscreenMethod) == 0) {

    HWND hwnd = GetActiveWindow();
    int w = GetSystemMetrics(SM_CXSCREEN);
    int h = GetSystemMetrics(SM_CYSCREEN);
    SetWindowLongPtr(hwnd, GWL_STYLE, WS_VISIBLE | WS_OVERLAPPEDWINDOW);
    SetWindowPos(hwnd, NULL, (w/2)/2, (h/2)/2, w/2, h/2, SWP_FRAMECHANGED);

    result->Success();
  } else {
    result->NotImplemented();
  }
}

}  // namespace

void FlutterWindowsFullscreenPluginRegisterWithRegistrar(
    FlutterDesktopPluginRegistrarRef registrar) {
  FlutterWindowsFullscreenPlugin::RegisterWithRegistrar(
      flutter::PluginRegistrarManager::GetInstance()
          ->GetRegistrar<flutter::PluginRegistrarWindows>(registrar));
}
