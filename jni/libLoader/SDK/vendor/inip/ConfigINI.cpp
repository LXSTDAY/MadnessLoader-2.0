/*
 * Create by fuzhuo at 11/12/2013
 */
#include "ConfigINI.h"

#include <iostream>
#include <sstream>
#include <string>
#include <map>

#define CONFIGINI_DEBUG 0
#define log printf
#define mlog(msg...) do{\
if(CONFIGINI_DEBUG) printf(msg);\
}while(0)

ConfigINI::ConfigINI(const char *fileNameWithPath, bool _autoCreate):
    data(NULL),
    fStream(NULL),
    autoSave(false),
    autoCreate(_autoCreate)
{
    strcpy(iniFileName, fileNameWithPath);
    loadConfigFile();
}

void ConfigINI::loadConfigFile()
{
    fstream fStream;
    string p = iniFileName;

    fStream.open(p,ios::in);
    if(!fStream){
        if(!autoCreate){
        }else{
        }
        return;
    }else{
    }
    char line[4096];
    char ch;
    int i=0;
    string index;
    string str;
    bool isComment=false;
    while(!fStream.eof()){
        fStream.read(&ch, 1);

        ConfigINIEntry entry;
        if(ch=='#' && i==0) isComment = true;
        if(isComment==true && (ch=='\n' || ch=='\r')) {
            isComment=false;
            line[i++]='\0';
            i=0;
            entry.isComment = true;
            entry.comment = line;
            datas.push_back(entry);
        }
        if(isComment==true) {
            line[i++]=ch;
            continue;
        }
        //zfu: all up for comment
        if(ch != '\n' || ch=='\r') line[i++]=ch;
        else{
            if(i==0) continue;
            line[i]='\0';
            str = string(line);
            if(line[0]=='['){
                index = str;
            }else{
                entry.index = index.substr(1,index.length()-2);
                int fIndex = str.find_first_of('=');
                entry.name = str.substr(0,fIndex);
                entry.value = str.substr(fIndex+1, str.length()-fIndex-1);
                datas.push_back(entry);
            }
            i=0;
        }
    }
    if(i!=0) {
        ConfigINIEntry entry;
        entry.index = str;
        int fIndex = str.find_first_of('=');
        entry.name = str.substr(0,fIndex);
        entry.value = str.substr(fIndex+1, str.length()-fIndex-1);
        datas.push_back(entry);
    }
    fStream.close();
}

ConfigINI::~ConfigINI()
{
    if(autoSave){
        cout<<"AUTO save Config file["<<iniFileName<<"]"<<endl;
        writeConfigFile();
    }
}

void ConfigINI::writeConfigFile(const char* fileName)
{
    autoSave=false;
    if(fileName==NULL) fileName = iniFileName;
    fstream fStream;
    fStream.open(fileName, ios_base::out | ios_base::trunc);
    string index = string("");
    bool withComment = false;
    bool isStart=true;
    for(vector<ConfigINIEntry>::iterator it=datas.begin(); it!= datas.end(); it++){
        ConfigINIEntry entry = *it;
        if(entry.isComment) {
            withComment=true;
            if(isStart) fStream<<entry.comment.c_str()<<endl;
            else fStream<<endl<<entry.comment.c_str()<<endl;
            isStart=false;
            
            continue;
        }
        if(strcmp(index.c_str(), entry.index.c_str()) != 0){
            index = entry.index;
            if(withComment || isStart) {
                fStream<<'['<<entry.index<<']'<<endl;
                withComment=false; isStart=false;
            }
            else{
                fStream<<endl<<'['<<entry.index<<']'<<endl;
            }
        }
        if (strlen(entry.name.c_str())==0 || strlen(entry.value.c_str())==0) {
            continue;
        }
        fStream<<entry.name<<'='<<entry.value<<endl;
    }
    fStream<<endl;
    fStream.close();
}

void ConfigINI::setStringValueWithIndex(const char *index, const char* name, const char* value)
{
    autoSave = true;
    ConfigINIEntry entry;
    entry.index = index;
    entry.name = name;
    entry.value = value;
    if(datas.size() == 0) {/*cout<<"data is NULL, push and return"<<endl; */
        datas.push_back(entry);
        return;
    }
    vector<ConfigINIEntry>::iterator it=datas.begin();
    bool findIndex=false;
    bool findName=false;
    vector<ConfigINIEntry>::iterator itInsertPos;
    for(it=datas.begin(); it!=datas.end(); it++){
        if(findIndex==false){
            if(strcmp(it->index.c_str(), index) == 0){
                findIndex=true;
            }
        }
        if(findIndex==true){
            if(strcmp(it->index.c_str(), index) != 0){
                break;
            }else{
                itInsertPos = it;
            }
            if(strcmp(it->name.c_str(), name)==0){
                findName=true;
                itInsertPos = it;
                break;
            }
            continue;
        }
        itInsertPos=it;
    }
    if(findIndex && findName){
        itInsertPos->value = string(value);
        return;
    }

    datas.insert(++itInsertPos, 1, entry);
}

/***********getter*************/
bool ConfigINI::getBoolValue(const char* index, const char *name)
{
    const char *str = getStringValue(index, name);
    if(str == NULL) {log("notfound for [%s]-[%s]", index, name); return false;}
    if(strcmp(str,"true") == 0) return true;
    else return false;
}

int ConfigINI::getIntValue(const char *index, const char* name)
{
    const char *str = getStringValue(index, name);
    if(!str){
        return -1;
    }else{
        return atoi(str);
    }
}

float ConfigINI::getFloatValue(const char* index, const char *name)
{
    const char *str = getStringValue(index, name);
    if(str == NULL) {cout<<"notfound"<<endl; return -1.0;}
    return atof(str);
}

const char* ConfigINI::getStringValue(const char* index, const char *name)
{
    for(unsigned int i=0; i<datas.size(); i++){
        if(strcmp(datas[i].index.c_str(), index) == 0){
            for(;i<datas.size();i++){
                if(strcmp(datas[i].name.c_str(), name)==0)
                    return datas[i].value.c_str();
            }
        }
    }
    return NULL;
}

/***********setter*************/
void ConfigINI::setBoolValue(const char* index, const char *name, bool value)
{
    if(value) sprintf(str, "true");
    else sprintf(str, "false");
    setStringValueWithIndex(index,name,str);
}

void ConfigINI::setIntValue(const char* index, const char *name, int value)
{
    sprintf(str, "%d", value);
    setStringValueWithIndex(index,name,str);
}

void ConfigINI::setFloatValue(const char* index, const char *name, float value)
{
    sprintf(str, "%f", value);
    setStringValueWithIndex(index,name,str);
}

void ConfigINI::setStringValue(const char *index, const char* name, const char* value)
{
    setStringValueWithIndex(index,name,value);
}

