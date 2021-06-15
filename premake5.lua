workspace "DnDCharacterGenerator"
    architecture "x86_64"
    startproject "DnDCharacterGenerator"
    configurations {"Debug", "Release"}

    outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

    group "Dependencies"
        include "vendor/premake"
    group ""

    include "DnDCharacterGenerator"
