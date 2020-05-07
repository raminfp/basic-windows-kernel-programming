### Windows Kernel Programming +++ Tutorial 


### Visual Studio Configuration 

```bash
General ==> Windows SDK Version ===> 10.0.10586.0

VC++ Directories ==> Include Directories = $(VC_IncludePath);$(WindowsSDK_IncludePath);

C/C++ ===> General ===> Additional Include Directories ===> C:\Program Files %28x86%29\Windows Kits\10\Include\10.0.17134.0\km;%(AdditionalIncludeDirectories)

Linker ===> Advanced ===> Entry Point ===> DriverEntry

Delete file .inf
```

#### Enable kernel debug Of registery
```bash
HKEY_LOCAL_MACHINE\SYSTEM\CurrentControlSet\Control\Session manager\Deubug Print Filter\DEFAULT 0xf
```