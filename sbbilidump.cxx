#include <cstdio>
#include <fstream>

using namespace std;

string GetFileNameFromPath(string file_path)
{
#ifdef _WIN32
        uint64_t len = file_path.find_last_of('\\');
        return file_path.substr(len + 1);
#elif
        uint64_t len = file_path.find_last_of('/');
        return file_path.substr(len + 1);
#endif
}

string GetFilePathFromAbsPath(string file_path)
{
#ifdef _WIN32
        uint64_t len = file_path.find_last_of('\\');
        return file_path.substr(0, len + 1);
#elif
        uint64_t len = file_path.find_last_of('/');
        return file_path.substr(len + 1);
#endif
}

int main(int argc, char const *argv[])
{
        fstream in_file;
        fstream out_file;
        string file_path;

        printf("[PROCESSING]");

        for(uint32_t seek_file = 1 ; seek_file < argc ; ++seek_file)
        {
                in_file.open(argv[seek_file], ios::in | ios::binary);
                in_file.seekg(3, ios::beg);

                file_path = GetFilePathFromAbsPath(argv[seek_file]) + "dump_" + GetFileNameFromPath(argv[seek_file]);      
                out_file.open(file_path.c_str(), ios::out | ios::binary);
                out_file << in_file.rdbuf();
                
                in_file.close();
                out_file.close();
        }
        return 0;
}
