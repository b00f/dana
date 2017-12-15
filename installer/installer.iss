#define AppName             "Dana"
#define AppVerName          "Dana"
#define AppVersion          "1.2"
#define AppExeName          "Dana"
#define AppDesc             "Dana"
#define AppCopyright        "Copyright 2014"
#define AppURL              "http://dana-box.com/"
#define AppGroupName        "Dana"
#define QtPath              QTDIR
#define AppID               "{AF273301-28D0-4DAB-A531-2021022C4C8B}"

[Setup]
AppName={#AppName}
AppVerName={#AppVerName}
AppCopyright={#AppCopyright}
AppId={{#AppID}
DefaultDirName={pf}\{#AppGroupName}
DefaultGroupName={#AppGroupName}
OutputBaseFilename={#AppExeName}
OutputDir=.
MinVersion=0,5.01.2600sp1
UserInfoPage=true
AppVersion={#AppVersion}
UninstallDisplayIcon={app}\dana.exe
EnableDirDoesntExistWarning=false
DirExistsWarning=no
SolidCompression=true
;;InfoBeforeFile=.\info.txt
;;;LicenseFile=.\License.txt

[Files]
Source: release\dana.exe;                                        DestDir: {app};
Source: release\zlibwapi.dll;                                DestDir: {app};
Source: release\miniunz.exe;                                 DestDir: {app};
Source: release\minizip.exe;                                 DestDir: {app};
Source: release\msvcp110.dll;                                DestDir: {app};
Source: release\msvcr110.dll;                                DestDir: {app};
Source: {#QtPath}\bin\icudt53.dll;                                     DestDir: {app};
Source: {#QtPath}\bin\icuin53.dll;                                     DestDir: {app};
Source: {#QtPath}\bin\icuuc53.dll;                                     DestDir: {app};
;;Source: {#QtPath}\bin\libEGL.dll;                                      DestDir: {app};
;;Source: {#QtPath}\bin\libEGLd.dll;                                     DestDir: {app};
;;Source: {#QtPath}\bin\libGLESv2.dll;                                   DestDir: {app};
Source: {#QtPath}\bin\Qt5Core.dll;                                     DestDir: {app};
Source: {#QtPath}\bin\Qt5Gui.dll;                                      DestDir: {app};
Source: {#QtPath}\bin\Qt5Network.dll;                                  DestDir: {app};
Source: {#QtPath}\bin\Qt5Widgets.dll;                                  DestDir: {app};
Source: {#QtPath}\bin\Qt5Widgets.dll;                                  DestDir: {app};
Source: {#QtPath}\bin\Qt5Xml.dll;                                      DestDir: {app};
Source: {#QtPath}\bin\Qt5Sql.dll;                                      DestDir: {app};
Source: {#QtPath}\bin\Qt5Svg.dll;                                      DestDir: {app};
Source: {#QtPath}\bin\Qt5Widgets.dll;                                  DestDir: {app};
Source: {#QtPath}\plugins\platforms\qwindows.dll;                      DestDir: {app}\platforms\;
Source: {#QtPath}\plugins\sqldrivers\qsqlite.dll;                      DestDir: {app}\plugins\sqldrivers\;
Source: {#QtPath}\plugins\bearer\qnativewifibearer.dll;                DestDir: {app}\plugins\bearer\;
Source: {#QtPath}\plugins\bearer\qgenericbearer.dll;                   DestDir: {app}\plugins\bearer\;
Source: {#QtPath}\plugins\imageformats\qgif.dll;                       DestDir: {app}\plugins\imageformats\;
Source: {#QtPath}\plugins\imageformats\qico.dll;                       DestDir: {app}\plugins\imageformats\;
Source: {#QtPath}\plugins\imageformats\qjpeg.dll;                      DestDir: {app}\plugins\imageformats\;
Source: {#QtPath}\plugins\imageformats\qmng.dll;                       DestDir: {app}\plugins\imageformats\;
Source: {#QtPath}\plugins\imageformats\qsvg.dll;                       DestDir: {app}\plugins\imageformats\;
Source: {#QtPath}\plugins\imageformats\qtga.dll;                       DestDir: {app}\plugins\imageformats\;
Source: {#QtPath}\plugins\imageformats\qtiff.dll;                      DestDir: {app}\plugins\imageformats\;
Source: {#QtPath}\plugins\imageformats\qwbmp.dll;                      DestDir: {app}\plugins\imageformats\;
Source: {#QtPath}\plugins\imageformats\qdds.dll;                       DestDir: {app}\plugins\imageformats\;
Source: {#QtPath}\plugins\imageformats\qicns.dll;                      DestDir: {app}\plugins\imageformats\;
Source: {#QtPath}\plugins\imageformats\qjp2.dll;                       DestDir: {app}\plugins\imageformats\;
Source: {#QtPath}\plugins\imageformats\qwebp.dll;                      DestDir: {app}\plugins\imageformats\;
Source: {#QtPath}\plugins\platforms\qwindows.dll;                      DestDir: {app}\plugins\platforms\;

[Icons]
Name: {group}\Dana; Filename: {app}\Dana.exe; IconFilename: {app}\Dana.exe;
Name: {group}\Uninstall; Filename: {uninstallexe}; WorkingDir: {app};

;;; HKEY_CURRENT_USER\Software\dana

[UninstallDelete]
Type: filesandordirs; Name: {userappdata}\..\..\Dana
Type: dirifempty; Name: {app}
