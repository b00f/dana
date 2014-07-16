#define AppName 		    "Dana"
#define AppVerName 		  "Dana"
#define AppVersion 		  "1.0"
#define AppExeName 		  "Dana"
#define AppDesc 		    "Dana"
#define AppCopyright 	  "Copyright© 2014"
#define AppURL 			    "http://danasrs.com/"
#define AppGroupName 	  "dana"
#define SourcePath      "..\bin\msvc2012"
#define QtPath          "C:\Qt\Qt5.1.0.msvc2012\5.1.0\msvc2012"
#define AppID  			    "{AF273301-28D0-4DAB-A531-2021022C4C8B}"

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
Source: {#SourcePath}\dana.exe;                                        DestDir: {app}; 
Source: {#SourcePath}\zlibwapi.dll;                                    DestDir: {app}; 
Source: {#SourcePath}\miniunz.exe;                                     DestDir: {app}; 
Source: {#SourcePath}\minizip.exe;                                     DestDir: {app}; 
Source: {#SourcePath}\msvcp110.dll;                                    DestDir: {app}; 
Source: {#SourcePath}\msvcr110.dll;                                    DestDir: {app}; 
Source: {#QtPath}\bin\icudt51.dll;                                     DestDir: {app}; 
Source: {#QtPath}\bin\icuin51.dll;                                     DestDir: {app}; 
Source: {#QtPath}\bin\icuuc51.dll;                                     DestDir: {app}; 
Source: {#QtPath}\bin\libEGL.dll;                                      DestDir: {app}; 
Source: {#QtPath}\bin\libEGLd.dll;                                     DestDir: {app}; 
Source: {#QtPath}\bin\libGLESv2.dll;                                   DestDir: {app}; 
Source: {#QtPath}\bin\Qt5Core.dll;                                     DestDir: {app}; 
Source: {#QtPath}\bin\Qt5Gui.dll;                                      DestDir: {app}; 
Source: {#QtPath}\bin\Qt5Network.dll;                                  DestDir: {app}; 
Source: {#QtPath}\bin\Qt5Widgets.dll;                                  DestDir: {app}; 
Source: {#QtPath}\bin\Qt5Widgets.dll;                                  DestDir: {app}; 
Source: {#QtPath}\bin\Qt5Xml.dll;                                      DestDir: {app}; 
Source: {#QtPath}\bin\Qt5Widgets.dll;                                  DestDir: {app}; 
Source: {#QtPath}\plugins\platforms\qwindows.dll;                              DestDir: {app}\platforms\; 
Source: {#QtPath}\plugins\imageformats\qgif.dll;                       DestDir: {app}\plugins\imageformats\; 
Source: {#QtPath}\plugins\imageformats\qico.dll;                       DestDir: {app}\plugins\imageformats\; 
Source: {#QtPath}\plugins\imageformats\qjpeg.dll;                      DestDir: {app}\plugins\imageformats\; 
Source: {#QtPath}\plugins\imageformats\qmng.dll;                       DestDir: {app}\plugins\imageformats\; 
Source: {#QtPath}\plugins\imageformats\qsvg.dll;                       DestDir: {app}\plugins\imageformats\; 
Source: {#QtPath}\plugins\imageformats\qtga.dll;                       DestDir: {app}\plugins\imageformats\; 
Source: {#QtPath}\plugins\imageformats\qtiff.dll;                      DestDir: {app}\plugins\imageformats\; 
Source: {#QtPath}\plugins\imageformats\qwbmp.dll;                      DestDir: {app}\plugins\imageformats\; 
Source: {#QtPath}\plugins\accessible\qtaccessiblewidgets.dll;          DestDir: {app}\plugins\accessible\; 

[Icons]
Name: {group}\dana; Filename: {app}\dana.exe; IconFilename: {app}\dana.exe; 
Name: {group}\uninstall; Filename: {uninstallexe}; WorkingDir: {app};

;;; HKEY_CURRENT_USER\Software\dana

[UninstallDelete]
Type: filesandordirs; Name: {userappdata}\..\..\dana
Type: dirifempty; Name: {app}