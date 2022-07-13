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
  //Required functions:
  static LPCSTR WindowTitle() { return "MainApp"; }
  
  //Non copy or move constructors require the first parameter in 
  //the parameter list must be HWND
  MainApp(HWND hwnd);
  
  //Requires either or both the following operator() overloads.
  //operator()(MoWin::Event event) Is for legacy support
  //If operator()(MoWin::Event) does not exist, it'll try to match
  //the operator()(MoWin::Event::...) of the correct type where ... represent 
  //a specific event like WM_CHAR.
  //If operator()(MoWin::Event event) does exist, the library will only call
  //said operator. In order to call a event specific operator, the user must call
  //it explicitly. We provide MoWin::WindowClassTraits<MainApp>::VisitEvent() to help
  //everyone out
  LRESULT operator()(MoWin::Event event) { return 0; }
  LRESULT operator()(MoWin::Event::... event)
  
  //Optional functions:
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
Once a class was defined, a window can now be created by doing the following `MoWin::Window<MainApp> window();` where the constructor has similar params to CreateWindow, and then extra params to initialize `<MainApp>` as the class passed in to the window is directly associated as the window class and contains an instance of one. 
The window will be initialized first, followed by the class data. Since the class data is initialized after, all events during the creation of the window are currently lost.
