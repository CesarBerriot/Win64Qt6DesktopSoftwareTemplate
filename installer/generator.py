import sys
import os
import shutil
from datetime import datetime

def get_unix_time_us():
    return datetime.timestamp(datetime.now())

def log_separator():
    print("\n---------------------------------------------------------------------------------------------------\n")

log_separator()

project_name = input("Project Name : ")
project_bio = input("Single Line Project Description : ")
owner_name = input("Publisher Name : ")
license_name = input("License Name (i.e. \"MIT License\") : ")
project_link = input("Project Link : ")
project_link_text = input("Project Link Text (i.e. \"MyProject On Github\") : ")

pre_generation_time = get_unix_time_us()

log_separator()

GEN_DIR = "Gen"
BIN_DIR = "bin"

if os.path.exists(GEN_DIR):
    print(f"deleting previous {GEN_DIR} directory")
    shutil.rmtree(GEN_DIR)
   
print(f"creating a new {GEN_DIR} directory")   
os.mkdir(GEN_DIR)

print(f"creating directory {GEN_DIR}/{BIN_DIR}")   
os.mkdir(f"{GEN_DIR}/{BIN_DIR}")

log_separator()

if not os.path.isfile("../LICENSE"):
    print("error : missing license at \"../LICENSE\"")
    os.exit()

print(f"copying LICENSE into {GEN_DIR}")
shutil.copyfile("../LICENSE", f"{GEN_DIR}/LICENSE")
print("done copying LICENSE")

log_separator()

print(f"generating howto.txt with project name : '{project_name}'")

file = open(f"{GEN_DIR}/howto.txt", "w")
file.write(
    f"Step 1 :\n"
    f"Download NSIS (https://nsis.sourceforge.io/Download)\n"
    f"\n"
    f"Step 2 :\n"
    f"Compile the program (This is basic CMake knowledge, just google how it's done).\n"
    f"\n"
    f"Step 3 :\n"
    f"Copy the following from your build folder into the bin folder :\n"
    f"- plugins/platforms/qwindows.dll\n"
    f"- {project_name}.exe\n"
    f"- libgcc_s_seh-1.dll\n"
    f"- libstdc++-6.dll\n"
    f"- libwinpthread-1.dll\n"
    f"- Qt6Core.dll\n"
    f"- Qt6Gui.dll\n"
    f"- Qt6Widgets.dll\n"
    f"\n"
    f"Step 3.5 (Optional) :\n"
    f"Run `bin/{project_name}.exe` and make sure you don't get any missing dll errors (which most likely means you forgot something).\n"
    f"\n"
    f"Step 4 :\n"
    f"Right click `{project_name}.nsi` and select \"Compile NSIS Script\""
)
file.close()

print("howto.txt generation done")

log_separator()

print(f"generating '{project_name}.nsi'")

file = open(f"{GEN_DIR}/{project_name}.nsi", "w")
file.write(
    f"!include \"MUI2.nsh\"\n"
    f"\n"
    f"Name \"{project_name}\"\n"
    f"OutFile \"{project_name} x64 Installer.exe\"\n"
    f"InstallDir \"C:\\Program Files\\{project_name}\"\n"
    f"\n"
    f"# Use default images from NSIS\n"
    f"!define MUI_HEADERIMAGE\n"
    f"\n"
    f"# Header\n"
    f"!define MUI_PAGE_HEADER_TEXT \"{owner_name} Presents:\"\n"
    f"!define MUI_PAGE_HEADER_SUBTEXT \"{project_name} (c) 2024\"\n"
    f"\n"
    f"# Welcome Page\n"
    f"!define MUI_WELCOMEPAGE_TITLE \"{project_name}\"\n"
    f"!define MUI_WELCOMEPAGE_TEXT \"{project_bio}\"\n"
    f"!insertmacro MUI_PAGE_WELCOME\n"
    f"\n"
    f"# License Page\n"
    f"!define MUI_LICENSEPAGE_TEXT_TOP \"This software is distributed under the {license_name} :\"\n"
    f"!define MUI_LICENSEPAGE_TEXT_BOTTOM \"Please read and agree with this license to continue the installation.\"\n"
    f"!define MUI_LICENSEPAGE_CHECKBOX\n"
    f"!define MUI_LICENSEPAGE_CHECKBOX_TEXT \"I agree.\"\n"
    f"!insertmacro MUI_PAGE_LICENSE \"LICENSE\"\n"
    f"\n"
    f"# Installation Page\n"
    f"!insertmacro MUI_PAGE_INSTFILES\n"
    f"\n"
    f"\n"
    f"# Finish Page\n"
    f"!define MUI_FINISHPAGE_TITLE \"The installation has been completed.\"\n"
    f"!define MUI_FINISHPAGE_TEXT \"You may now use {project_name}\"\n"
    f"!define MUI_FINISHPAGE_RUN \"$INSTDIR\\{project_name}.exe\"\n"
    f"!define MUI_FINISHPAGE_RUN_TEXT \"Run {project_name}.\"\n"
    f"!define MUI_FINISHPAGE_LINK \"{project_link_text}\"\n"
    f"!define MUI_FINISHPAGE_LINK_LOCATION \"{project_link}\"\n"
    f"!insertmacro MUI_PAGE_FINISH\n"
    f"\n"
    f"# Language\n"
    f"!insertmacro MUI_LANGUAGE \"English\"\n"
    f"\n"
    f"Section\n"
    f"    # Require admin rights\n"
    f"    UserInfo::GetAccountType\n"
    f"    Pop $0\n"
    f"    StrCmp $0 \"Admin\" +3\n"
    f"    MessageBox MB_OK \"This installer requires administrator permissions. Please restart the application as an administrator.\"\n"
    f"    Quit\n"
    f"	  # Copy binaries\n"
    f"	  SetOutPath $INSTDIR\n"
    f"	  File /r \"bin\\\"\n"
    f"	  # Create the scripts directory\n"
    f"	  # CreateDirectory \"$\\\"$INSTDIR\\scripts$\\\"\"\n"
    f"    # Write the uninstaller\n"
    f"    SetOutPath $INSTDIR\n"
    f"    WriteUninstaller \"{project_name} Uninstaller.exe\"\n"
    f"    # Write start menu items\n"
    f"	  CreateDirectory \"$SMPROGRAMS\\{project_name}\"\n"
    f"    CreateShortcut \"$SMPROGRAMS\\{project_name}\\{project_name}.lnk\" \"$INSTDIR\\{project_name}.exe\"\n"
    f"	  CreateShortcut \"$SMPROGRAMS\\{project_name}\\Uninstall {project_name}.lnk\" \"$INSTDIR\\{project_name} Uninstaller.exe\"\n"
    f"    # Write a control panel program entry in the registry\n"
    f"    WriteRegStr HKLM \"Software\\Microsoft\\Windows\\CurrentVersion\\Uninstall\\{project_name}\" \\\n"
    f"        \"DisplayName\" \"{project_name}\"\n"
    f"    WriteRegStr HKLM \"Software\\Microsoft\\Windows\\CurrentVersion\\Uninstall\\{project_name}\" \\\n"
    f"        \"UninstallString\" \"$\\\"$INSTDIR\\{project_name} Uninstaller.exe$\\\"\"\n"
    f"    WriteRegStr HKLM \"Software\\Microsoft\\Windows\\CurrentVersion\\Uninstall\\{project_name}\" \\\n"
    f"        \"InstallLocation\" \"$\\\"$INSTDIR$\\\"\"\n"
    f"    WriteRegStr HKLM \"Software\\Microsoft\\Windows\\CurrentVersion\\Uninstall\\{project_name}\" \\\n"
    f"        \"Publisher\" \"{owner_name}\"\n"
    f"    WriteRegStr HKLM \"Software\\Microsoft\\Windows\\CurrentVersion\\Uninstall\\{project_name}\" \\\n"
    f"        \"URLInfoAbout\" \"{project_link}\"\n"
    f"SectionEnd\n"
    f"\n"
    f"Section \"Uninstall\"\n"
    f"    # Delete files\n"
    f"    RMDir /r \"$INSTDIR\"\n"
    f"    # Delete start menu items\n"
    f"	  RMDir /r \"$SMPROGRAMS\\{project_name}\"\n"
    f"    # Delete registry keys\n"
    f"    DeleteRegKey HKLM \"Software\\Microsoft\\Windows\\CurrentVersion\\Uninstall\\{project_name}\"\n"
    f"SectionEnd\n"
)

print("NSIS script generation done")

log_separator()

print(f"finished all generations in { (get_unix_time_us() - pre_generation_time) / 1000000 } microseconds")

log_separator()

input("Press any key to continue...")