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
UserInfoPage=true
AppVersion={#AppVersion}
UninstallDisplayIcon={app}\dana.exe
EnableDirDoesntExistWarning=false
DirExistsWarning=no
SolidCompression=true
LicenseFile=.\..\LICENSE

[Files]
Source: ..\release\dana.exe;                               DestDir: {app};
Source: {#Mingw}\bin\libgcc_s_dw2-1.dll;                   DestDir: {app};
Source: {#Mingw}\bin\libstdc++-6.dll;                      DestDir: {app};
Source: {#Mingw}\bin\libwinpthread-1.dll;                  DestDir: {app};
Source: {#QtDir}\bin\Qt5Core.dll;                          DestDir: {app};
Source: {#QtDir}\bin\Qt5Gui.dll;                           DestDir: {app};
Source: {#QtDir}\bin\Qt5Network.dll;                       DestDir: {app};
Source: {#QtDir}\bin\Qt5Widgets.dll;                       DestDir: {app};
Source: {#QtDir}\bin\Qt5Widgets.dll;                       DestDir: {app};
Source: {#QtDir}\bin\Qt5Xml.dll;                           DestDir: {app};
Source: {#QtDir}\bin\Qt5Sql.dll;                           DestDir: {app};
Source: {#QtDir}\bin\Qt5Widgets.dll;                       DestDir: {app};
Source: {#QtDir}\bin\Qt5Charts.dll;                        DestDir: {app};
Source: {#QtDir}\bin\Qt5TextToSpeech.dll;                  DestDir: {app};
Source: {#QtDir}\plugins\platforms\qwindows.dll;           DestDir: {app}\platforms\;
Source: {#QtDir}\plugins\sqldrivers\qsqlite.dll;           DestDir: {app}\plugins\sqldrivers\;
Source: {#QtDir}\plugins\bearer\qnativewifibearer.dll;     DestDir: {app}\plugins\bearer\;
Source: {#QtDir}\plugins\bearer\qgenericbearer.dll;        DestDir: {app}\plugins\bearer\;
Source: {#QtDir}\plugins\imageformats\qgif.dll;            DestDir: {app}\plugins\imageformats\;
Source: {#QtDir}\plugins\imageformats\qico.dll;            DestDir: {app}\plugins\imageformats\;
Source: {#QtDir}\plugins\imageformats\qjpeg.dll;           DestDir: {app}\plugins\imageformats\;
Source: {#QtDir}\plugins\imageformats\qsvg.dll;            DestDir: {app}\plugins\imageformats\;
Source: {#QtDir}\plugins\imageformats\qtga.dll;            DestDir: {app}\plugins\imageformats\;
Source: {#QtDir}\plugins\imageformats\qtiff.dll;           DestDir: {app}\plugins\imageformats\;
Source: {#QtDir}\plugins\imageformats\qwbmp.dll;           DestDir: {app}\plugins\imageformats\;
Source: {#QtDir}\plugins\imageformats\qicns.dll;           DestDir: {app}\plugins\imageformats\;
Source: {#QtDir}\plugins\imageformats\qwebp.dll;           DestDir: {app}\plugins\imageformats\;
Source: {#QtDir}\plugins\platforms\qwindows.dll;           DestDir: {app}\plugins\platforms\;

[Icons]
Name: {group}\Dana; Filename: {app}\Dana.exe; IconFilename: {app}\Dana.exe;
Name: {group}\Uninstall; Filename: {uninstallexe}; WorkingDir: {app};

;;; HKEY_CURRENT_USER\Software\dana

[UninstallDelete]
Type: filesandordirs; Name: {userappdata}\.dana
Type: dirifempty; Name: {app}
