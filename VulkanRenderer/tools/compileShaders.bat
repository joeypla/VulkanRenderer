if not exist ..\shaders\compiled mkdir ..\shaders\compiled
cd ..\shaders\compiled
D:\VulkanSDK\1.1.101.0\Bin\glslangValidator.exe -V %cd%\..\shader.vert
D:\VulkanSDK\1.1.101.0\Bin\glslangValidator.exe -V %cd%\..\shader.frag
pause