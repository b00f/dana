#define AppName             "Dana"
#define AppVerName          "Dana"
#define AppVersion          "1.2"
#define AppExeName          "Dana"
#define AppDesc             "Dana"
#define AppCopyright        "Copyright 2014"
#define AppURL              "http://dana-box.com/"
#define AppGroupName        "Dana"
#define QtDir               GetEnv("QTDIR")
#define Mingw               GetEnv("MINGW")
#define AppID               "{AF273301-28D0-4DAB-A531-2021022C4C8B}"

[Setup]
AppName={#AppName}
AppVerName={#AppVerName}
AppCopyright={#AppCopyright}
AppId={{#AppID}
DefaultDirName={pf}\{#AppGroupName}
DefaultGroupName={#AppGroupName}
OutputBaseFilename={#AppName}-win32
OutputDir=..\Output
MinVersion=0,5.01.2600sp1
UserInfoPage=false
AppVersion={#AppVersion}
UninstallDisplayIcon={app}\dana.exe
EnableDirDoesntExistWarning=false
DirExistsWarning=no
SolidCompression=true
LicenseFile=.\..\LICENSE

[Files]
Source: ..\release\*; DestDir: {app}; Flags: recursesubdirs      


[Icons]
Name: {group}\Dana; Filename: {app}\Dana.exe; IconFilename: {app}\Dana.exe;
Name: {group}\Uninstall; Filename: {uninstallexe}; WorkingDir: {app};

;;; HKEY_CURRENT_USER\Software\dana

[UninstallDelete]
Type: filesandordirs; Name: {userappdata}\.dana
Type: dirifempty; Name: {app}
