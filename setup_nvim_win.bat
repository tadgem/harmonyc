call "C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Auxiliary\Build\vcvars64.bat"
mkdir build
cd build
cmake .. -G "Ninja"
xcopy /F /y "compile_commands.json" "../compile_commands.json"
    
