# DnDCharacterGenerator
Randomly generates the information necessary for the first page of a Dungeons & Dragons 5th edition character sheet for a first level character.

## Getting Started
This repository uses [Premake](https://github.com/premake/premake-core) as its build system, but no install is necessary, as Premake is included in this repository. Also, note that this project uses some C++20 features.

To set up the repository on your local machine, use your preferred method of downloading the repository. Then, on Windows, navigate to the scripts folder and run the `Win-GenProjects.bat` file. There may be a warning dialog that pops up when you try to do this. If so, click "More Info", then click "Run Anyway". This batch file will generate a Visual Studio 2019 solution that is ready to run.

## Future Features
* Generate a form-fillable PDF of the character sheet.
* Implement a GUI and give the user more control over how a character is generated.
* Generate all the information for a full three-page character sheet.
