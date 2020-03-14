#include <iostream>
#include <filesystem>
#include <string>
#include <locale>

int main ( int argc, char** argv ) {
    
    std::filesystem::path rootDirectory = argv[1];
    std::string targetDirName = "A";
    
    try
    {
        for(auto& entry : std::filesystem::directory_iterator(rootDirectory))
        {
            if(!entry.is_directory() && entry.is_regular_file())
            {
                std::filesystem::path targetDirFilePath = rootDirectory;            
                targetDirName[0] = std::toupper(entry.path().filename().string()[0]) ;
                
                if(!std::isalpha(targetDirName[0]))
                {
                    targetDirName[0] = '#';
                }
                
                targetDirFilePath /= targetDirName;
                
                if(!std::filesystem::exists(targetDirFilePath))
                {
                    std::filesystem::create_directory(targetDirFilePath);
                }
                
                targetDirFilePath /= entry.path().filename();
                
                if(std::filesystem::exists(targetDirFilePath))
                {
                    std::filesystem::rename(entry.path(), targetDirFilePath);
                }
            }
        }
    }
    catch(std::exception &e)
    {
        std::cout << "error: " <<  e.what() << std::endl;
    }
    catch(...)
    {
        std::cout << "Unknown exception" << std::endl;
    }
    
    return ( 0 );
}
