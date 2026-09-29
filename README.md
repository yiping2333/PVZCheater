# PVZCheater

A Windows C++/MFC experiment for modifying values in the Chinese version of *Plants vs. Zombies*. The source locates the game window and uses Windows process memory APIs to change in-game values such as sun and zombie behavior.

## Status

This is a small personal project last updated in January 2023. It has no published release or verified compatibility matrix. The memory addresses are hard-coded and may not work with other game versions. Build and runtime behavior have not been revalidated for this publication.

## Build

Open `PVZCheater.sln` in Visual Studio with the C++ MFC components and Windows 10 SDK. The project file targets the Visual Studio 2019 `v142` toolset. Build the desired configuration and platform in Visual Studio.

## License

The code in this repository is available under the [MIT License](LICENSE). *Plants vs. Zombies* and its assets are not part of this repository or license.
