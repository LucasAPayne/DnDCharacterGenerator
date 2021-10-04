project "DnDCharacterGenerator"
    kind "WindowedApp"
    language "C++"
    cppdialect "C++20"

    targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
	objdir ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")

    files 
    {
        "src/**.h",
        "src/**.cpp",
        "vendor/wxpdfdoc/include/**.h",
        "vendor/wxpdfdoc/include/**.cpp"
    }

    includedirs 
    {
        "src",
        "vendor/wxpdfdoc/include"
    }

    links {"wxpdfdoc"}

    filter "system:windows"
        systemversion "latest"

    filter "configurations:Debug"
        runtime "Debug"
        symbols "on"

    filter "configurations:Release"
        runtime "Release"
        optimize "on"