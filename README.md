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
  //Required, this replaces the window procedure
  LRESULT operator()(MoWin::Event event) { return 0; }
  //Required, a constructor whose first parameter is HWND, there can be extra parameters so long as HWND is the first parameter
  MainApp(HWND hWnd){}
  
  //Optional
  static MoWin::WindowClassStyle Style();
  static int ExtraClassBytes();
  static int ExtraWindowBytes();
  static HICON Icon(HINSTANCE instance);
  static HCURSOR Cursor(HINSTANCE instance);
  static HBRUSH BackgroundBrush();
  static LPCSTR MenuName();
  static HICON SmallIcon(HINSTANCE instance);
  //Optional, A operator() overload that will handle a specific event
  //... just means there's a type alias defined in the Event class for specific events
  LRESULT operator()(MoWin::Event::... event)
};
```
Once a class was defined, a window can now be created by doing the following `MoWin::Window<MainApp> window();` where the constructor has similar params to CreateWindow, and then extra params to initialize `<MainApp>` as the class passed in to the window is directly associated as the window class
