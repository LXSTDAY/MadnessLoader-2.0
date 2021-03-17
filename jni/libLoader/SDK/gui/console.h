#pragma once


extern std::string consoleLog;
extern std::string sendText;
extern std::string cmdLine;

typedef void callback(const char* result);

class ConsoleGUI
{
private:
    void SystemCmds(std::string cmd);
public:
    ConsoleGUI() {}
    ~ConsoleGUI() {}

    void Render();
    void NewLine(std::string text, ...);
    bool CheckCmd(std::string line);
    string* CheckCmdWithArgs(std::string line, uint iargs);

    void OpenKeyBoard(callback* handler);

private:
    bool bTimeStamp = false;
};
