#include "../../dllmain.h"

void CWorld::Add(CEntity *entity)
{
    CPatch::CallFunction<void>(g_libGTASA+0x3C14B0+1, entity);
}

void CWorld::Remove(CEntity* entity)
{
    CPatch::CallFunction<void>(g_libGTASA+0x3C1500+1, entity);
}

void CWorld::FindObjectsInRange(CVector const& point, float radius, bool b2D, short* outCount, short maxCount, CEntity** outEntities, bool buildings, bool vehicles, bool peds, bool objects, bool dummies)
{
    CPatch::CallFunction<void>(g_libGTASA+0x3C212C+1, point, radius, b2D, outCount, maxCount, outEntities, buildings, vehicles, peds, objects, dummies);
}

void CWorld::FindObjectsOfTypeInRange(unsigned int modelId, CVector const& point, float radius, bool b2D, short* outCount, short maxCount, CEntity** outEntities, bool buildings, bool vehicles, bool peds, bool objects, bool dummies)
{
    CPatch::CallFunction<void>(g_libGTASA+0x3C25E8+1, modelId, point, radius, b2D, outCount, maxCount, outEntities, buildings, vehicles, peds, objects, dummies);
}