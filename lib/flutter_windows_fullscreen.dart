
import 'dart:async';

import 'package:flutter/services.dart';

class FlutterWindowsFullscreen {
  static const MethodChannel _channel =
      const MethodChannel('flutter_windows_fullscreen');

  static Future enableFullscreen() async {
    await _channel.invokeMethod('enableFullscreen');
  }

  static Future disableFullscreen() async {
    await _channel.invokeMethod('disableFullscreen');
  }
}
