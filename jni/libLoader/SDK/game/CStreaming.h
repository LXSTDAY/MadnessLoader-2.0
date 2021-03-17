#pragma once
#include "../../dllmain.h"

#pragma pack(push, 1)
struct tStreamingFileDesc
{
  char m_szName[40];    //0-40
  bool bNotPlayerImg;   //40-41
  char __pad[3];        //41-44
  int m_StreamHandle;   //44-48
};

enum eStreamingFlags {
    GAME_REQUIRED = 0x2,
    MISSION_REQUIRED = 0x4,
    KEEP_IN_MEMORY = 0x8,
    PRIORITY_REQUEST = 0x10
};

enum eStreamingLoadState {
    LOADSTATE_NOT_LOADED = 0,
    LOADSTATE_LOADED = 1,
    LOADSTATE_Requested = 2,
    LOADSTATE_Channeled = 3,
    LOADSTATE_Finishing = 4
};

class CStreamingInfo {
public:
    short m_nNextIndex; // ms_pArrayBase array index    //00-02
    short m_nPrevIndex; // ms_pArrayBase array index    //02-04
    short m_nNextIndexOnCd;                             //04-06
    unsigned char m_nFlags; // see eStreamingFlags      //06-07
    unsigned char m_nImgId;                             //07-08
    unsigned int m_nCdPosn;                             //08-12
    unsigned int m_nCdSize; // number of blocks/sectors; m_nCdSize * STREAMING_BLOCK_SIZE = actual size in bytes //12-16
    unsigned char m_nLoadState; // see eStreamingLoadState  //16-17
private:
    char  __pad[3];                                      //17-20

public:
    static CStreamingInfo *&ms_pArrayBase;

    void AddToList(CStreamingInfo *listStart);
    //! unused
    unsigned int GetCdPosn();
    bool GetCdPosnAndSize(unsigned int *CdPosn, unsigned int *CdSize);
    //! unused
    unsigned int GetCdSize();
    //! unused
    CStreamingInfo *GetNext();
    //! unused
    CStreamingInfo *GetPrev();
    //! unused
    bool InList();
    void Init();
    void RemoveFromList();
    void SetCdPosnAndSize(unsigned int CdPosn, unsigned int CdSize);
};

class CStreaming 
{   
public:
    static CStreamingInfo *ms_aInfoForModel; // static CStreamingInfo ms_aInfoForModel[26316]
    static tStreamingFileDesc *ms_files; // static tStreamingFileDesc ms_files[8]
    static void RequestModel(int modelId, eStreamingFlags flags);
    static void LoadAllRequestedModels(bool bOnlyPriorityRequests);
    static void RemoveModel(int Modelindex);
};
#pragma pack(pop)