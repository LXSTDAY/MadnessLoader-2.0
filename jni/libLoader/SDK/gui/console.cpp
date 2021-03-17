#include "../../dllmain.h"
#include "gui.h"
#include "keyboard.h"
#include "console.h"
#include <time.h>

std::string consoleLog;
std::string sendText;
std::string cmdLine;

extern CGUI *pGUI;
extern CKeyBoard *pKeyBoard;

void ConsoleInputHandler(const char* str)
{
	sendText = str;
}

void ConsoleGUI::Render()
{	
	ImGuiIO& io = ImGui::GetIO();
	ImGui::PushStyleVar(ImGuiStyleVar_ButtonTextAlign, ImVec2(0.05f, 0.7f));

	ImGui::SetNextWindowPos(ImVec2(io.DisplaySize.x * 0.01, io.DisplaySize.y * 0.3));
	ImGui::SetNextWindowSize(ImVec2(pGUI->ScaleX(550), pGUI->ScaleY(370)));

	ImGui::Begin("cmdline", nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse);

		ImGui::BeginChild("", ImVec2(ImGui::GetWindowSize().x * 0.95, ImGui::GetWindowSize().y * 0.7), true, ImGuiWindowFlags_NoMouseInputs);

			ImGui::Text("%s", consoleLog.c_str());
			ImGui::SetScrollHere(1.0f);
		
		ImGui::EndChild();

	if(ImGui::Button(sendText.c_str(), ImVec2(ImGui::GetWindowSize().x * 0.75, pGUI->ScaleY(40)))) pKeyBoard->Open(&ConsoleInputHandler); ImGui::SameLine();
	ImGui::PopStyleVar();
	if(ImGui::Button("Send", ImVec2(pGUI->ScaleX(100), pGUI->ScaleY(40)))) { SystemCmds(sendText); NewLine(sendText); sendText = "";}

	ImGui::End();

	
}

void ConsoleGUI::SystemCmds(std::string cmd)
{	
	if(!cmd.compare(0, 1, "/"))
	{
		if(cmd == "/timestamp") 
		{
			if(!bTimeStamp) 
			{	
				NewLine("Time stamp enabled");
				bTimeStamp = true;
			}
			else 
			{	
				bTimeStamp = false;
				NewLine("Time stamp disabled");
			}
		}
	}
}

void ConsoleGUI::NewLine(std::string text, ...)
{	

	if(!text.compare(0, 1, "")) return;
	if(!text.compare(0, 1, "/")) {cmdLine = text; return;}

	if(bTimeStamp) 
	{	
		const struct tm *tm;
		time_t  now;

		now = time(NULL);
		tm = localtime(&now);
		char s[256];

		strftime(s, 256, "[%H:%M:%S] ", tm);
		consoleLog += s + text + "\n";
	}
	else consoleLog += text + "\n";
}

bool ConsoleGUI::CheckCmd(std::string line)
{	
	string localline = "/" + line;

    if(cmdLine == localline)
    {
        cmdLine = "";
        return true;
	}
	else return false;
}

string* ConsoleGUI::CheckCmdWithArgs(std::string cmd, uint iargs)
{	
	string bfargs[iargs];
	for(int i = 0; i <= iargs - 1; i++) bfargs[i] = "-0";

	string localLine = "/" + cmd;
	string localcmdLine = cmdLine + "_END_";

	if(localcmdLine.find(localLine) != -1)
	{
		localcmdLine.erase(0, localLine.size());

		// ��������� iargs ���
		for(int i = 0; i <= iargs - 1; i++)
		{	
			while (localcmdLine[0] == ' ')
			{
				localcmdLine.erase(0, 1);
			}

			if(localcmdLine == "_END_") break;
			//���� true
			while (true)
			{	
				//���� ����� ������ ��� �����
				if(localcmdLine[0] == ' ' || localcmdLine == "_END_")
				{	
					Log("break");
					//��������� ��������
					break;
				}
				// ���� ����� � �������
				if(bfargs[i] == "-0")
				{   
					Log("Empty");
					//������ �� �����
					bfargs[i] = localcmdLine[0];
					localcmdLine.erase(0, 1);
				}
				else //���� �� �����
				{	
					//���� ����� ������ ��� �����
					if(localcmdLine[0] == ' ' || localcmdLine == "_END_")
					{	
						Log("break");
						//��������� ��������
						break;
					}
					else
					{
						//�������� ������
						Log("Add symbol");
						bfargs[i] += localcmdLine[0];
						localcmdLine.erase(0, 1);
					}

				}
			
			}
		}

		//������ ���������� ������
		cmdLine = "";
	}

	//������� ������� ����������
	return bfargs;
}

void ConsoleGUI::OpenKeyBoard(callback* handler)
{
	pKeyBoard->Open(*&handler);
}