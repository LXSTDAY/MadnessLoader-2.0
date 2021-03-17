#include "../../dllmain.h"

CStreamingInfo *CStreaming::ms_aInfoForModel = (CStreamingInfo*)(g_libGTASA+0x6706D8);
tStreamingFileDesc *CStreaming::ms_files = (tStreamingFileDesc*)(g_libGTASA+0x6702FC);

bool CStreamingInfo::GetCdPosnAndSize(unsigned int *CdPosn, unsigned int *CdSize)
{
    return CPatch::CallFunction<bool>(g_libGTASA+0x28E6C8+1, this, CdPosn, CdSize);
}

void CStreaming::RequestModel(int modelId, eStreamingFlags flags)
{   
    CPatch::CallFunction<void>(g_libGTASA+0x28EB10+1, modelId, flags);
}

void CStreaming::LoadAllRequestedModels(bool bOnlyPriorityRequests)
{
    CPatch::CallFunction<void>(g_libGTASA+0x294CB4+1, bOnlyPriorityRequests);
}

void CStreaming::RemoveModel(int Modelindex)
{
    CPatch::CallFunction<void>(g_libGTASA+0x290C4C+1, Modelindex);
}