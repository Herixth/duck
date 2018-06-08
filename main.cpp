// CodeLines.cpp : 定义控制台应用程序的入口点。
//

#include <Commdlg.h>
#include <Shlobj.h>
#include <map>
#include <vector>
#include <iostream>
#include <io.h>
#include <string>
#include <set>
#include <fstream>
#pragma comment(lib,"Shell32.lib")

void InitValidTypes(std::set<std::string> &validTypes)
{
    validTypes.insert(".h");
    validTypes.insert(".cpp");
    validTypes.insert(".c");
    validTypes.insert(".hpp");
    validTypes.insert(".py");
    validTypes.insert(".txt");
    validTypes.insert(".cs");
    validTypes.insert(".css");
    validTypes.insert(".js");
    validTypes.insert(".lua");
    validTypes.insert(".html");
    validTypes.insert(".htm");
    validTypes.insert(".java");
    validTypes.insert(".bat");
    validTypes.insert("makefile");
}

int32_t WToChar(LPWSTR szWstr, char szCstr[], const int32_t chrLen)
{
    int iLength = WideCharToMultiByte(CP_ACP, 0, szWstr, -1, NULL, 0, NULL, NULL);
    return WideCharToMultiByte(CP_ACP, 0, szWstr, -1, szCstr, iLength, NULL, NULL);
}

void OpenDirectoryDialog(HWND hWnd, char directoryPath[], const int32_t directoryPathLen)
{
    TCHAR szBuffer[MAX_PATH] = { 0 };
    BROWSEINFO bi = { 0 };
    bi.hwndOwner = hWnd;//拥有着窗口句柄，为NULL表示对话框是非模态的，实际应用中一般都要有这个句柄  
    bi.pszDisplayName = szBuffer;//接收文件夹的缓冲区  
    bi.lpszTitle = TEXT("选择一个文件夹");//标题  
    bi.ulFlags = BIF_NEWDIALOGSTYLE;
    BOOL ret = FALSE;
    do {
        LPITEMIDLIST idl = SHBrowseForFolder(&bi);
        ret = SHGetPathFromIDList(idl, szBuffer);
        if (!ret)
        {
            MessageBox(NULL, TEXT("请选择一个文件夹"), NULL, MB_ICONERROR);
        }
        else
        {
            //MessageBox(NULL, szBuffer, TEXT("你选择的文件夹"), 0);
            WToChar(szBuffer, directoryPath, directoryPathLen);
        }
    } while (!ret);
}

void GetFilesFromDirectory(std::vector<std::string> &files, const char *directoryPath)
{
    struct _finddata_t fileinfo;
    long hFile = 0;
    char tmpPath[MAX_PATH] = { 0 };
    sprintf_s(tmpPath, "%s\\*", directoryPath);
    if ((hFile = _findfirst(tmpPath, &fileinfo)) == -1) { return; }
    do
    {
        if ((fileinfo.attrib &  _A_SUBDIR))
        {
            if (strcmp(fileinfo.name, ".") != 0 && strcmp(fileinfo.name, "..") != 0)
            {
                sprintf_s(tmpPath, "%s\\%s", directoryPath, fileinfo.name);
                GetFilesFromDirectory(files, tmpPath);
            }
        }
        else
        {
            sprintf_s(tmpPath, "%s\\%s", directoryPath, fileinfo.name);
            files.push_back(tmpPath);
        }
    } while (_findnext(hFile, &fileinfo) == 0);
    _findclose(hFile);
}

void StringToLower(std::string &str)
{
    for (uint32_t i = 0; i < str.length(); ++i)
    {
        if (str[i] >= 'A' && str[i] <= 'Z')
        {
            str[i] = str[i] + 'a' - 'A';
        }
    }
}

std::string GetFileExtention(const std::string &fileName)
{
    std::string localFileName = fileName;
    StringToLower(localFileName);
    int pos = localFileName.find_last_of('.');
    if (pos >= 0)
    {
        return localFileName.substr(pos);
    }
    return localFileName;
}

void DumpFiles(const std::vector<std::string> &files)
{
    for (uint32_t i = 0; i < files.size() && i < 100; ++i)
    {
        std::cout << files[i] << std::endl;
        std::cout << GetFileExtention(files[i]) << std::endl;
    }
    std::cout << files.size() << std::endl;
}

bool IfFileTypeValid(const std::string &fileExtention)
{
    static std::set<std::string> validTypes;
    if (validTypes.empty()) {
        InitValidTypes(validTypes);
    }
    return validTypes.find(fileExtention) != validTypes.end();
}

uint32_t CalculateCharShowTimesInBuf(char buf[], const uint32_t len, char aim)
{
    uint32_t i = 0, counter = 0;
    while (i < len && buf[i] != '\0')
    {
        if (buf[i] == aim) { ++counter; }
        ++i;
    }
    return counter;
}

uint32_t GetFileLines(const std::string &fileName)
{
    const uint32_t maxBufLen = 10240;
    static char buf[maxBufLen + 1];
    std::ifstream inFile(fileName, std::ios::in);
    if (!inFile) { return 0; }
    uint32_t counter = 0;
    while (!inFile.eof())
    {
        memset(buf, 0, maxBufLen);
        inFile.read(buf, maxBufLen);
        //std::cout << buf;
        counter += CalculateCharShowTimesInBuf(buf, maxBufLen, '\n');
    }
    return counter;
}

void StatisticCodeLines(std::map<std::string, uint32_t> &codeLines, const std::string &directoryPath)
{
    static std::vector<std::string> files;
    files.clear();
    GetFilesFromDirectory(files, directoryPath.c_str());
    // DumpFiles(files);
    for (const std::string &fileName : files)
    {
        std::string fileExtention = GetFileExtention(fileName);
        if (!IfFileTypeValid(fileExtention)) { continue; }
        codeLines[fileExtention] += GetFileLines(fileName);
    }
}

void PrintCodeLines(const std::map<std::string, uint32_t> &codeLines)
{
    for (const std::pair<std::string, uint32_t> &p : codeLines)
    {
        printf("%-6s:%-8u\n", p.first.c_str(), p.second);
    }
}

int _tmain(int argc, _TCHAR* argv[])
{
    char directoryPath[MAX_PATH] = { 0 };
    OpenDirectoryDialog(NULL, directoryPath, MAX_PATH);
    std::cout << directoryPath << std::endl;
    static std::map<std::string, uint32_t> codeLines;
    codeLines.clear();
    StatisticCodeLines(codeLines, directoryPath);
    PrintCodeLines(codeLines);
    getchar();
    return 0;
}