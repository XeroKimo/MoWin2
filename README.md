# MoWin2
An attempt to make a C++20 wrapper around Win32 API

# Requirements
- C++20 with modules support

# How to use
Create a class that will serve as a WindowClass, it will look something like the following
```c++
class MainApp
{
public:
  //Required
  static LPCSTR WindowTitle() { return "MainApp"; }
  
  //Requires either or both the following operator() overloads.
  //operator()(MoWin::Event event) Is for legacy support, with a custom EventProcessed return type 
  //which takes either a LRESULT or MoWin::eventUnprocessed. Unprocessed events will attempt
  //to match with a specialized operator()(MoWin::Event::... event) if they exist, otherwise
  //if there are absolutely no specialized operator()s, it is the equivalent of returning 0,
  //if there are specialized operator() but there are no matches, it is whatever DefWindowProc() will return.
  MoWin::EventProcessed operator()(MoWin::Event event) { return 0; }
  LRESULT operator()(MoWin::Event::... event)
  
  //Optional
  static MoWin::WindowClassStyle Style();
  static int ExtraClassBytes();
  static int ExtraWindowBytes();
  static HICON Icon(HINSTANCE instance);
  static HCURSOR Cursor(HINSTANCE instance);
  static HBRUSH BackgroundBrush();
  static LPCSTR MenuName();
  static HICON SmallIcon(HINSTANCE instance);
};
```
Once a class was defined, a window can now be created by doing the following `MoWin::Window<MainApp> window();` where the constructor has similar params to CreateWindow, and then extra params to initialize `<MainApp>` as the class passed in to the window is directly associated as the window class and contains an instance of one. The window class instance will first be initialized followed by the window, if the class instance requires the window handle for anything, they can get it as early as a NonClientCreate event
