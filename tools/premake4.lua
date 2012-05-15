--Build script for GameEngine2012
--Author: Ian Lilley

--Appliaction name
local name = "GameEngine2012"

--Directory stuff
local cwd = os.getcwd() .. "/"
local project_location_rel = "../"
local build_location_rel =   project_location_rel .. "build/"                  -- Build
local source_location_rel =  project_location_rel .. "src/"                    -- Source
local data_location_rel =    project_location_rel .. "data/"                   -- Data
local headers_location_rel = project_location_rel .. "externals/headers/"      -- Headers
local libs_location_rel =    project_location_rel .. "externals/libs/"         -- Libraries

--Converts a list of lib paths to lib names
function matchlibs(dir)
	local libs = os.matchfiles(dir .. "*")
	for i=1, #libs do
		libs[i] = string.gsub(libs[i],".lib$", "")
		libs[i] = string.gsub(libs[i],dir, "")
	end
	return libs
end

--Adds libs to the project
function addlibs(build_type) --"Debug" or "Release"
	local libs = {"SFML_2.0/", "bullet_2.80/"} --This is the only line that needs to be updated for new libs
	local os_type =       _OPTIONS["os"] .. "/"
	local platform_type = _OPTIONS["platform"] .. "/"
	local build_type =    build_type .. "/"
	local endpath = os_type .. platform_type .. build_type
	for i,lib in pairs(libs) do
		local full_path = libs_location_rel .. lib .. endpath
		links(matchlibs(cwd .. full_path))
		libdirs(full_path)
	end
end

--Delete the old build folder
os.rmdir( cwd .. string.gsub(build_location_rel,"/$", "") ) 

--Set up debug and release versions
solution ( name )
	configurations { "Debug", "Release" }
	location ( build_location_rel )

	--Various variables defined here
	defines {"_CRT_SECURE_NO_WARNINGS"}
	defines {"SFML_STATIC"}
	defines {"SRUTIL_DELEGATE_PREFERRED_SYNTAX"}
	
project ( name )
	kind ("ConsoleApp")
	language ("C++")
	files { source_location_rel  .. "**"}           --include all of our source code (resursive)
	files { data_location_rel    .. "**"}           --include all of the data files
	files { headers_location_rel .. "gl3w/**" }     --include GL3W
	files { headers_location_rel .. "tinyxml/**" }  --include tinyxml
	includedirs { headers_location_rel }            --this accounts for all library headers
	location ( build_location_rel )                 --this is where the project is built
	debugdir ( project_location_rel )               --this is where the IDE-generated-exe accesses data and other folders
	targetdir ( build_location_rel )                --this is where the exe gets built
	targetextension ( ".exe" )                      --Windows executable type
	links( "opengl32" )                             --finds the opengl lib file

	--Debug-----------------------------------
	configuration "Debug"
		flags { "Symbols" }
		defines { "DEBUG" }
		addlibs ("Debug")
		
	--Release---------------------------------	
	configuration "Release"
		flags { "Optimize" }
		defines { "NDEBUG" }
		addlibs ("Release")
