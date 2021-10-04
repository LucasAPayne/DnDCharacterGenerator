workspace "DnDCharacterGenerator"
    architecture "x86"
    startproject "DnDCharacterGenerator"
    configurations {"Debug", "Release"}

    outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

    group "Dependencies"
        include "vendor/premake"
        include "DnDCharacterGenerator/vendor/wxpdfdoc"
    group ""

    include "DnDCharacterGenerator"
