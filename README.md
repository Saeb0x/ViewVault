# ViewVault
A Maya plugin inspired by Blender's [Stored Views](https://docs.blender.org/manual/en/latest/addons/3d_view/stored_views.html), designed to simplify managing and storing view locations for easy navigation between views. It allows creating cameras aligned to current or recalled views, even without being actively in the view, and previewing each camera in a pop-up window to streamline workflows and ensure continuity across sessions within Maya projects. Motivated by my interest in tools programming, I created this plugin to provide real benefits to Maya users. Developed for artists, riggers, animators, and technical artists. 

## Getting Started
Visual Studio 2022 is recommended, as ViewVault is officially untested on other development environments while focusing on a Windows build. ViewVault is built with a DLL configuration type and targets the .mll file extension, following the Autodesk Maya API. No build system generators are used at the moment.

1. <u>**Downloading the repository:**</u>

Start by cloning the repository with the following command: ```git clone https://github.com/Saeb0x/ViewVault.git```. There's no need to recursively clone since there are no submodules. 

2. <u>**Configuring the dependencies:**</u>

ViewVault depends on [Maya](https://aps.autodesk.com/developer/overview/maya) and Qt. Make sure to set up Maya's specific [Qt variant](https://help.autodesk.com/view/MAYAUL/2022/ENU/?guid=Maya_SDK_Working_with_Qt_html) as a dependency, alongside any other necessary Maya configurations.

3. <u>**Building the Project:**</u>

Open the project in Visual Studio 2022 ```ViewVault.sln```, configure the necessary settings, and proceed to build the project.

## Features
- [x] **Stored Views Management:** ViewVault simplifies managing and storing view locations within Maya projects. Users can save multiple view locations for easy navigation between views.
- [x] **Camera Creation:** Easily create cameras aligned to current or recalled views, even without being actively in the view, by selecting from the stored list. This feature ensures continuity across Maya sessions.
- [x] **Camera Preview Pop-up Window:** Easily preview each generated camera in a convenient pop-up window to streamline workflow and ensure accurate placement.

## Future Plans (To do)
- [ ]  **State Saving and Loading:** Implement serialization and deserialization to save ViewVault's settings within Maya scenes or projects. This feature will enable users to recall earlier states of ViewVault after closing and reopening sessions, maintaining continuity and workflow efficiency.
- [ ]  **Enhanced Camera Management:** Develop tools for bulk camera management, including batch creation, and updating of camera views based on user-defined criteria.

## Screenshot
![ViewVault_Screenshot1](https://github.com/user-attachments/assets/aa6708af-770e-484f-a20a-a277fdfb6427)

## In Action!
View [here](https://drive.google.com/file/d/1psgBcd2HqgkJd7J8aCNPUDQ7SDEngCt5/view?usp=sharing).



