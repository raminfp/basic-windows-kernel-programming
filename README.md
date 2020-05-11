### Basic Windows Kernel Programming +++ Tutorial 



### Visual Studio Configuration 

    1- General ==> Windows SDK Version ===> 10.0.10586.0

    2- VC++ Directories ==> Include Directories = $(VC_IncludePath);$(WindowsSDK_IncludePath);

    3- C/C++ ===> General ===> Additional Include Directories ===> C:\Program Files %28x86%29\Windows Kits\10\Include\10.0.17134.0\km;%(AdditionalIncludeDirectories)

    4- Linker ===> Advanced ===> Entry Point ===> DriverEntry

    5- Delete file .inf
    

#### Enable kernel debug Of registery

    HKEY_LOCAL_MACHINE\SYSTEM\CurrentControlSet\Control\Session manager\Deubug Print Filter\DEFAULT 0xf

#### Topics:
  1- [KeCPU](https://github.com/raminfp/basicwindowskernelprogramming/tree/master/KeCPU) <br />
  2- [KeDateTime](https://github.com/raminfp/basicwindowskernelprogramming/tree/master/KeDateTime) <br />
  3- [KeDebug](https://github.com/raminfp/basicwindowskernelprogramming/tree/master/KeDebug) <br />
  4- [KeJsonParser](https://github.com/raminfp/basicwindowskernelprogramming/tree/master/KeJsonParser) <br />
  5- [KeMalloc](https://github.com/raminfp/basicwindowskernelprogramming/tree/master/KeMalloc) <br />
  6- [KeOSBuild](https://github.com/raminfp/basicwindowskernelprogramming/tree/master/KeOSBuild) <br />
  7- [KeOSVersion](https://github.com/raminfp/basicwindowskernelprogramming/tree/master/KeOSVersion) <br />
  8- [KeShellCode](https://github.com/raminfp/basicwindowskernelprogramming/tree/master/KeShellCode) <br />
  9- [KeString](https://github.com/raminfp/basicwindowskernelprogramming/tree/master/KeString) <br />
  10- [KeThread](https://github.com/raminfp/basicwindowskernelprogramming/tree/master/KeThread) <br />
  11- [KeTimer](https://github.com/raminfp/basicwindowskernelprogramming/tree/master/KeTimer) <br />
  12- [KeVector](https://github.com/raminfp/basicwindowskernelprogramming/tree/master/KeVector) <br />
  13- [KeHeapAlloc](https://github.com/raminfp/basicwindowskernelprogramming/tree/master/KeHeapAlloc) <br />
  14- [KeFileWrite](https://github.com/raminfp/basicwindowskernelprogramming/tree/master/KeFileWrite) <br />
  15- [KeFileRead](https://github.com/raminfp/basicwindowskernelprogramming/tree/master/KeFileRead) <br />
  16- [KeLinkList](https://github.com/raminfp/basicwindowskernelprogramming/tree/master/KeLinkList) <br />
  17- [KeSpinLock](https://github.com/raminfp/basicwindowskernelprogramming/tree/master/KeSpinLock) <br />
  17- [KeWdmVersion](https://github.com/raminfp/basicwindowskernelprogramming/tree/master/KeWdmVersion) <br />
  
#### TODO
      - Advance Windows kernel Programming
      
    
#### Awesome Book by Pavel Yosifovich - https://leanpub.com/windowskernelprogramming

![windows kernel programming](https://m.media-amazon.com/images/I/41qJOhBcKuL.jpg "
Pavel Yosifovich")
