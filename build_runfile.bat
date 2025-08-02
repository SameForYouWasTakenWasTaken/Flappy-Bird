@echo off
setlocal

:: Prompt user for build type
echo ! RUN THIS ANYWHERE, MAKE SURE THERE IS NO 'Flappy-Bird' FOLDER IN YOUR build_runfile.bat DIRECTORY WHEN RUNNING THIS !
echo Select build configuration:
echo 1 - Release
echo 2 - Debug
set /p build_choice=Enter choice (1 or 2): 

:: Default to Release unless 2 is chosen
if "%build_choice%"=="2" (
    set "build_type=Debug"
) else (
    set "build_type=Release"
)

echo Using build type: %build_type%
echo.

:: Main logic
if exist CMakeLists.txt (
    echo Found CMakeLists.txt in current directory.
    echo Creating build directory...
    mkdir build-%build_type% 2>nul
    echo Created build directory
    echo Configuring CMake in build directory...
    cmake -E chdir build-%build_type% cmake -DCMAKE_BUILD_TYPE=%build_type% ..
    echo Building...
    cmake --build build-%build_type%
    echo Build finished!
    echo Executable is in build-%build_type%/bin
) else (
    echo CMakeLists.txt not found. Cloning repo...
    git clone https://github.com/SameForYouWasTakenWasTaken/Flappy-Bird.git || exit /b
    pushd Flappy-Bird
    mkdir build-%build_type% 2>nul
    echo Created build directory...
    echo Configuring CMake in build directory...
    cmake -E chdir build-%build_type% cmake -DCMAKE_BUILD_TYPE=%build_type% ..
    echo Building...
    cmake --build build-%build_type%
    echo Build finished!
    echo Executable is in Flappy-Bird/build-%build_type%/bin
    popd
)

endlocal
