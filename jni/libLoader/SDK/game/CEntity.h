#pragma once 
#include "../../dllmain.h"
#include "CVector.h"
#include "CMatrix.h"

#pragma pack(push, 1)
class CEntity {  
public:
	uint32_t vtable; 			// 0-4
	
	PADDING(_pad0, 12);			// 4-16
		
	float fRotZBeforeMat;		// 16-20
	
	CMatrix *mat;				// 20-24
	
	union {
		RwObject *m_pRwObject;
		RpClump *m_pRpClump;
		RpAtomic *m_pRpAtomic;
	};							// 24-26
	
	union {
		uint32_t m_nEntityFlags;// 26-30
		struct {
			uint32_t m_bUsesCollision : 1;           // does entity use collision
            uint32_t m_bCollisionProcessed : 1;  // has object been processed by a ProcessEntityCollision function
            uint32_t m_bIsStatic : 1;                // is entity static
            uint32_t m_bHasContacted : 1;            // has entity processed some contact forces
            uint32_t m_bIsStuck : 1;             // is entity stuck
            uint32_t m_bIsInSafePosition : 1;        // is entity in a collision free safe position
            uint32_t m_bWasPostponed : 1;            // was entity control processing postponed
            uint32_t m_bIsVisible : 1;               //is the entity visible

            uint32_t m_bIsBIGBuilding : 1;           // Set if this entity is a big building
            uint32_t m_bRenderDamaged : 1;           // use damaged LOD models for objects with applicable damage
            uint32_t m_bStreamingDontDelete : 1; // Dont let the streaming remove this 
            uint32_t m_bRemoveFromWorld : 1;     // remove this entity next time it should be processed
            uint32_t m_bHasHitWall : 1;              // has collided with a building (changes subsequent collisions)
            uint32_t m_bImBeingRendered : 1;     // don't delete me because I'm being rendered
            uint32_t m_bDrawLast : 1;             // draw object last
            uint32_t m_bDistanceFade : 1;         // Fade entity because it is far away

            uint32_t m_bDontCastShadowsOn : 1;       // Dont cast shadows on this object
            uint32_t m_bOffscreen : 1;               // offscreen flag. This can only be trusted when it is set to true
            uint32_t m_bIsStaticWaitingForCollision : 1; // this is used by script created entities - they are static until the collision is loaded below them
            uint32_t m_bDontStream : 1;              // tell the streaming not to stream me
            uint32_t m_bUnderwater : 1;              // this object is underwater change drawing order
            uint32_t m_bHasPreRenderEffects : 1; // Object has a prerender effects attached to it
            uint32_t m_bIsTempBuilding : 1;          // whether or not the building is temporary (i.e. can be created and deleted more than once)
            uint32_t m_bDontUpdateHierarchy : 1; // Don't update the aniamtion hierarchy this frame

            uint32_t m_bHasRoadsignText : 1;     // entity is roadsign and has some 2deffect text stuff to be rendered
            uint32_t m_bDisplayedSuperLowLOD : 1;
            uint32_t m_bIsProcObject : 1;            // set object has been generate by procedural object generator
            uint32_t m_bBackfaceCulled : 1;          // has backface culling on
            uint32_t m_bLightObject : 1;         // light object with directional lights
            uint32_t m_bUnimportantStream : 1;       // set that this object is unimportant, if streaming is having problems
            uint32_t m_bTunnel : 1;          // Is this model part of a tunnel
            uint32_t m_bTunnelTransition : 1;        // This model should be rendered from within and outside of the tunnel
		} nEntityFlags;
	};
	
	PADDING(_pad1, 2); 			// 30-32 ;uint16_t struct m_nRandomSeed;
	
	uint16_t nModelIndex;		//32-34
	uintptr_t* pCarFXRenderer;	//34-38

	PADDING(_pad2, 28);

	CVector vecMoveSpeed;
	CVector vecTurnSpeed;
	
	PADDING(_pad3, 88);
	
	uint32_t dwUnkModelRel;
};
#pragma pack(pop)