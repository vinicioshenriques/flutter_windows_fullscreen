import 'package:flutter/material.dart';
import 'dart:async';

import 'package:flutter/services.dart';
import 'package:flutter_windows_fullscreen/flutter_windows_fullscreen.dart';

void main() {
  runApp(MyApp());
}

class MyApp extends StatefulWidget {
  @override
  _MyAppState createState() => _MyAppState();
}

class _MyAppState extends State<MyApp> {

  @override
  void initState() {
    super.initState();
  }

  Future<void> enableFullscreen() async {
    try{
      await FlutterWindowsFullscreen.enableFullscreen();
    } catch (e){
      throw e.toString();
    }

  }
  Future<void> disableFullscreen() async {
    try{
      await FlutterWindowsFullscreen.disableFullscreen();
    } catch (e){
      throw e.toString();
    }

  }

  @override
  Widget build(BuildContext context) {
    return MaterialApp(
      home: Scaffold(
        appBar: AppBar(
          title: const Text('Plugin example app'),
        ),
        body: Row(
          mainAxisAlignment: MainAxisAlignment.center,
          children: [
            Center(child: ElevatedButton(child: Text('Enable Fullscreen'), onPressed: enableFullscreen,)),
            SizedBox(width: 10.0),
            Center(child: ElevatedButton(child: Text('Disable Fullscreen'), onPressed: disableFullscreen,)),
          ],
        ),
      ),
    );
  }
}
