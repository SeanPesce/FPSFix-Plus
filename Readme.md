# Bonfire Input Fix (FPSFix+)  
**For Dark Souls: Prepare to Die Edition**  
**Author: Sean Pesce**  
[Dark Souls Nexus page](https://www.nexusmods.com/darksouls/mods/1343/)  


## Background  
This is a ground-up remake of Nullby7e's "FPSFix" ([NexusMods](https://www.nexusmods.com/darksouls/mods/862)/[GitHub](https://github.com/NullBy7e/FPSFix)), which was a solution to the bonfire input bug in *Dark Souls™: Prepare to Die Edition*. Basically, if a player used the "Reverse hollowing" option at a bonfire with the frame rate unlocked, there was a significant chance that their character could get stuck when attempting to leave the bonfire (the bonfire menu would disappear, but the player character would remain sitting at the bonfire, with no way to get up). When this happened, the only way to remedy the issue was to restart the game. Luckily, the original FPSFix implemented a re-bindable hotkey that the player could press to escape the bonfire if they encountered this annoying bug.  


## Improvements  
The new bonfire input fix, or **FPSFix+**, has a few improvements over the original FPSFix:  

*  **Automation:** Removes the need for the hot-key, as FPSFix+ automatically detects and fixes the glitch when it occurs. If players want to know when it happens, they can set `BeepOnDetection=1` in the configuration file (`FPSFix.ini`) to hear a beep every time the fix is automatically applied.  
*  **DLL Chaining:** The original FPSFix was a wrapper for `d3d9.dll`, but couldn't chain additional `d3d9.dll` wrappers. FPSFix+ has multiple builds, and each build is a wrapper for a different shared library. Additionally, each build can chain other wrappers for its respective library.  
*  **File size:** This isn't really important, but FPSFix+ is less than one tenth of the size of the original FPSFix (~100KB vs ~1300KB).  


## Builds  
Below is the current list of available builds:  

* `dinput8.dll`  
* `d3d9.dll`  
* `d3dx9_43.dll`  
* **`winmm.dll` (Recommended)**  


## Installation  
To install the fix, [download one of the builds](https://github.com/SeanPesce/FPSFix-Plus/releases), extract the DLL and configuration file, and copy them into your Dark Souls directory (the default game directory is `C:\Program Files (x86)\Steam\steamapps\common\Dark Souls Prepare to Die Edition\DATA`). To load additional library wrappers through FPSFix+, enter the name of the chained DLL in the `DllChain=` entry in `FIPSFix.ini`. The fix is only compatible with the latest Steamworks version of Dark Souls. **NOTE:** To chain a library wrapper (such as d3d9.dll), you must use the corresponding build of FPSFix+. If you're already using a wrapper for that library, you can rename FPSFix+ and load it through the config file of the other wrapper DLL. Below are instructions for using FPSFix+ with the most common library-wrapper mods for Dark Souls, but note that it's easier to use one of the builds that isn't already wrapped by these mods (I recommend the `d3dx9_43.dll` or `winmm.dll` build).  


**Installation instructions:**   
* **[DSFix](https://github.com/PeterTh/dsfix)** by **Durante**: Download the **dinput8** build of FPSFix+, rename the DLL to something like `FPSFix.dll`, and add it to `DSFix.ini` (the edited line would read `dinput8dllWrapper FPSFix.dll`).  
* **[PvP Watchdog](https://www.nexusmods.com/darksouls/mods/849/)** by **eur0pa**: Download the **d3d9** build of FPSFix+, rename the DLL, and add it to `DSPWSteam.ini` (the edited line would read `d3d9dllWrapper FPSFix.dll`).  
* **[SweetFX](https://www.nexusmods.com/darksouls/mods/144)** by **CeeJaydk**: Copy all SweetFX files into the DATA folder. Rename the SweetFX DirectX9 DLL (`d3d9.dll`) to `d3d9_sweetfx.dll`. Download the **d3d9** build of FPSFix+ and copy the files to your DATA folder. In your `FPSFix.ini` file, set your DLL chain to the SweetFX library (the edited line would read `DllChain=d3d9_sweetfx.dll`).  
* **[ReShade](https://github.com/crosire/reshade)** by **crosire**: Create a folder *inside* the DATA folder and name it `ReShade`. Copy all ReShade files into the new folder. Download the **d3d9** build of FPSFix+ and copy the files to your DATA folder. In your `FPSFix.ini` file, set your DLL chain to the ReShade library (the edited line would read `DllChain=ReShade\d3d9.dll`).   

To uninstall the fix, simply remove the edited lines from the config file, and/or delete the FPSFix+ files from the Dark Souls DATA folder (depending on your installation method).  


## Compiling  
To compile the project, open it in [Visual Studio 2015](https://www.visualstudio.com/vs/older-downloads/), choose your build configuration (**d3d9** to compile the `d3d9.dll` wrapper, **dinput8** for the `dinput8.dll` wrapper, etc.), and go to **Build->Build Solution**. The compiled library can be found in the `/bin/` folder in the main project directory. Additionally, a pre-made configuration file can be found in the `/rsrc/` folder.  


## Acknowledgments  
* **Youri "NullBy7e" de Mooij** ([GitHub](https://github.com/nullby7e)) for finding the pointer needed to fix the bug when he made the [original Bonfire FPSFix](https://github.com/NullBy7e/FPSFix)  
* **Lin "mavenlin" Min** ([GitHub](https://github.com/mavenlin)) for his [DLL Wrapper Generator](https://github.com/mavenlin/Dll_Wrapper_Gen), which I forked a while back to modify and use for my own projects  


## Built With  
 * [Visual Studio 2015](https://www.visualstudio.com/vs/older-downloads/)  


## Contact  
If you have any questions/comments/concerns/suggestions, you can visit **[my website](https://SeanPesce.github.io/)**, or contact me on social media:  

* **[GitHub](https://github.com/SeanPesce)**  
* **[Reddit](https://reddit.com/u/SeanPesce/)**  
* **[Twitter](https://twitter.com/SeanPesce)**  
* **[YouTube](https://youtube.com/channel/UCgsMpXiR3PawqKM7MWLJGzQ)**  
* **[Discord](https://discordapp.com):** @SeanP#5604  


## Media  
![image](https://staticdelivery.nexusmods.com/mods/162/images/1343-0-1506614671.jpg)  
<sup>Player stuck at the bonfire after restoring humanity (Note that the bonfire menu is missing)</sup>  


## License  
[GNU General Public License v3.0](LICENSE)  
