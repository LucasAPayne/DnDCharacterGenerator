# DnDCharacterGenerator
Randomly generates the information necessary for the first page of a Dungeons & Dragons 5th edition character sheet for a first level character.

## Prerequisites
vcpkg is the package manager used for this project, and wxWidgets is the main library. The following steps will only need to be followed once per device for initial setup. Instructions are also available at [vcpkg.io](https://vcpkg.io/en/getting-started.html) and [wxwidgets.org](https://www.wxwidgets.org/blog/2019/01/wxwidgets-and-vcpkg/). To set up vcpkg, it is recommended to create a folder such as `C:\dev\vcpkg` or `C:\src\vcpkg`. Then, inside that folder, run the following commands:

**Clone the GitHub repo:**

    git clone https://github.com/Microsoft/vcpkg.git

**Run the botstrap:**
    
    cd vcpkg
    bootstrap-vcpkg.bat

**Make vcpkg libraries available in Visual Studio:**

    vcpkg integrate install

**Install wxWidgets (32-bit DLL version):**

    vcpkg install wxwidgets

Now, wxWidgets should be usable in Visual Studio.

## Getting Started
This repository uses [Premake](https://github.com/premake/premake-core) as its build system, but no install is necessary, as Premake is included in this repository. Also, note that this project uses some C++20 features.

To set up the repository on your local machine, use your preferred method of downloading the repository. Then, on Windows, navigate to the scripts folder and run the `Win-GenProjects.bat` file. There may be a warning dialog that pops up when you try to do this. If so, click "More Info", then click "Run Anyway". This batch file will generate a Visual Studio 2019 solution that is ready to run.

When the program is run, it will generate an FDF (Forms Data Format) file that will fill the character sheet PDF in the templates folder of this repository. For now, to fill and view the PDF, navigate to the assets/scripts folder and open the FDF file in a PDF reader that supports it, such as Adobe Reader/Acrobat.

## Future Features
* Implement a GUI and give the user more control over how a character is generated.
* Allow generation of higher-level characters.
* Generate all the information for a full three-page character sheet.
