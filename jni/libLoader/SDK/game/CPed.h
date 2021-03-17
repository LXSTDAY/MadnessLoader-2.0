#pragma once
#include "../../dllmain.h"
#include "CEntity.h"
#include "CVehicle.h"
#include "CWeapon.h"

typedef struct
{
	unsigned int   m_nFlags;
    CVector        m_vecOffset;
    class IFrame  *m_pIFrame;
    unsigned int   m_nNodeId;
} AnimBlendFrameData;

#pragma pack(push, 1)
class CPed {
public:
	CEntity entity; 		// 0000-0184	;entity
	PADDING(_pad106, 174);		// 0184-0358
	uint32_t _pad107;			// 0358-0362	;dwPedType
	PADDING(_pad101, 734);		// 0362-1096
	uint32_t dwAction;			// 1096-1100	;Action
	PADDING(_pad102, 36);		// 1100-1136
	struct {
        unsigned int bIsStanding : 1; // is ped standing on something
        unsigned int bWasStanding : 1; // was ped standing on something
        unsigned int bIsLooking : 1; // is ped looking at something or in a direction
        unsigned int bIsRestoringLook : 1; // is ped restoring head postion from a look
        unsigned int bIsAimingGun : 1; // is ped aiming gun
        unsigned int bIsRestoringGun : 1; // is ped moving gun back to default posn
        unsigned int bCanPointGunAtTarget : 1; // can ped point gun at target
        unsigned int bIsTalking : 1; // is ped talking(see Chat())

        unsigned int bInVehicle : 1; // is in a vehicle
        unsigned int bIsInTheAir : 1; // is in the air
        unsigned int bIsLanding : 1; // is landing after being in the air
        unsigned int bHitSomethingLastFrame : 1; // has been in a collision last fram
        unsigned int bIsNearCar : 1; // has been in a collision last fram
        unsigned int bRenderPedInCar : 1; // has been in a collision last fram
        unsigned int bUpdateAnimHeading : 1; // update ped heading due to heading change during anim sequence
        unsigned int bRemoveHead : 1; // waiting on AntiSpazTimer to remove head

        unsigned int bFiringWeapon : 1; // is pulling trigger
        unsigned int bHasACamera : 1; // does ped possess a camera to document accidents
        unsigned int bPedIsBleeding : 1; // Ped loses a lot of blood if true
        unsigned int bStopAndShoot : 1; // Ped cannot reach target to attack with fist, need to use gun
        unsigned int bIsPedDieAnimPlaying : 1; // is ped die animation finished so can dead now
        unsigned int bStayInSamePlace : 1; // when set, ped stays put
        unsigned int bKindaStayInSamePlace : 1; // when set, ped doesn't seek out opponent or cover large distances. Will still shuffle and look for cover
        unsigned int bBeingChasedByPolice : 1; // use nodes for routefind

        unsigned int bNotAllowedToDuck : 1; // Is this ped allowed to duck at all?
        unsigned int bCrouchWhenShooting : 1; // duck behind cars etc
        unsigned int bIsDucking : 1; // duck behind cars etc
        unsigned int bGetUpAnimStarted : 1; // don't want to play getup anim if under something
        unsigned int bDoBloodyFootprints : 1; // unsigned int bIsLeader :1;
        unsigned int bDontDragMeOutCar : 1;
        unsigned int bStillOnValidPoly : 1; // set if the polygon the ped is on is still valid for collision
        unsigned int bAllowMedicsToReviveMe : 1;

        unsigned int bResetWalkAnims : 1;
        unsigned int bOnBoat : 1; // flee but only using nodes
        unsigned int bBusJacked : 1; // flee but only using nodes
        unsigned int bFadeOut : 1; // set if you want ped to fade out
        unsigned int bKnockedUpIntoAir : 1; // has ped been knocked up into the air by a car collision
        unsigned int bHitSteepSlope : 1; // has ped collided/is standing on a steep slope (surface type)
        unsigned int bCullExtraFarAway : 1; // special ped only gets culled if it's extra far away (for roadblocks)
        unsigned int bTryingToReachDryLand : 1; // has ped just exited boat and trying to get to dry land

        unsigned int bCollidedWithMyVehicle : 1;
        unsigned int bRichFromMugging : 1; // ped has lots of cash cause they've been mugging people
        unsigned int bChrisCriminal : 1; // Is a criminal as killed during Chris' police mission (should be counted as such)
        unsigned int bShakeFist : 1; // test shake hand at look entity
        unsigned int bNoCriticalHits : 1; // ped cannot be killed by a single bullet
        unsigned int bHasAlreadyBeenRecorded : 1; // Used for replays
        unsigned int bUpdateMatricesRequired : 1; // if PedIK has altered bones so matrices need updated this frame
        unsigned int bFleeWhenStanding : 1; //

        unsigned int bMiamiViceCop : 1;  //
        unsigned int bMoneyHasBeenGivenByScript : 1; //
        unsigned int bHasBeenPhotographed : 1;  //
        unsigned int bIsDrowning : 1;
        unsigned int bDrownsInWater : 1;
        unsigned int bHeadStuckInCollision : 1;
        unsigned int bDeadPedInFrontOfCar : 1;
        unsigned int bStayInCarOnJack : 1;

        unsigned int bDontFight : 1;
        unsigned int bDoomAim : 1;
        unsigned int bCanBeShotInVehicle : 1;
        unsigned int bPushedAlongByCar : 1; // ped is getting pushed along by car collision (so don't take damage from horz velocity)
        unsigned int bNeverEverTargetThisPed : 1;
        unsigned int bThisPedIsATargetPriority : 1;
        unsigned int bCrouchWhenScared : 1;
        unsigned int bKnockedOffBike : 1;

        unsigned int bDonePositionOutOfCollision : 1;
        unsigned int bDontRender : 1;
        unsigned int bHasBeenAddedToPopulation : 1;
        unsigned int bHasJustLeftCar : 1;
        unsigned int bIsInDisguise : 1;
        unsigned int bDoesntListenToPlayerGroupCommands : 1;
        unsigned int bIsBeingArrested : 1;
        unsigned int bHasJustSoughtCover : 1;

        unsigned int bKilledByStealth : 1;
        unsigned int bDoesntDropWeaponsWhenDead : 1;
        unsigned int bCalledPreRender : 1;
        unsigned int bBloodPuddleCreated : 1; // Has a static puddle of blood been created yet
        unsigned int bPartOfAttackWave : 1;
        unsigned int bClearRadarBlipOnDeath : 1;
        unsigned int bNeverLeavesGroup : 1; // flag that we want to test 3 extra spheres on col model
        unsigned int bTestForBlockedPositions : 1; // this sets these indicator flags for various posisions on the front of the ped

        unsigned int bRightArmBlocked : 1;
        unsigned int bLeftArmBlocked : 1;
        unsigned int bDuckRightArmBlocked : 1;
        unsigned int bMidriffBlockedForJump : 1;
        unsigned int bFallenDown : 1;
        unsigned int bUseAttractorInstantly : 1;
        unsigned int bDontAcceptIKLookAts : 1;
        unsigned int bHasAScriptBrain : 1;

        unsigned int bWaitingForScriptBrainToLoad : 1;
        unsigned int bHasGroupDriveTask : 1;
        unsigned int bCanExitCar : 1;
        unsigned int CantBeKnockedOffBike : 2; // 0=Default(harder for mission peds) 1=Never 2=Always normal(also for mission peds)
        unsigned int bHasBeenRendered : 1;
        unsigned int bIsCached : 1;
        unsigned int bPushOtherPeds : 1; // GETS RESET EVERY FRAME - SET IN TASK: want to push other peds around (eg. leader of a group or ped trying to get in a car)

        unsigned int bHasBulletProofVest : 1;
        unsigned int bUsingMobilePhone : 1;
        unsigned int bUpperBodyDamageAnimsOnly : 1;
        unsigned int bStuckUnderCar : 1;
        unsigned int bKeepTasksAfterCleanUp : 1; // If true ped will carry on with task even after cleanup
        unsigned int bIsDyingStuck : 1;
        unsigned int bIgnoreHeightCheckOnGotoPointTask : 1; // set when walking round buildings, reset when task quits
        unsigned int bForceDieInCar : 1;

        unsigned int bCheckColAboveHead : 1;
        unsigned int bIgnoreWeaponRange : 1;
        unsigned int bDruggedUp : 1;
        unsigned int bWantedByPolice : 1; // if this is set, the cops will always go after this ped when they are doing a KillCriminal task
        unsigned int bSignalAfterKill : 1;
        unsigned int bCanClimbOntoBoat : 1;
        unsigned int bPedHitWallLastFrame : 1; // useful to store this so that AI knows (normal will still be available)
        unsigned int bIgnoreHeightDifferenceFollowingNodes : 1;

        unsigned int bMoveAnimSpeedHasBeenSetByTask : 1;
        unsigned int bGetOutUpsideDownCar : 1;
        unsigned int bJustGotOffTrain : 1;
        unsigned int bDeathPickupsPersist : 1;
        unsigned int bTestForShotInVehicle : 1;
        unsigned int bUsedForReplay : 1; // This ped is controlled by replay and should be removed when replay is done.
    } nPedFlags; 	// 1136-1140	0x1000 = can_decap
	PADDING(_pad228, 8); 		// 1140-1148
	uintptr_t Tasks; 			// 1148-1152
	uint32_t dwStateFlags; 	// 1152-1156	;StateFlags
	PADDING(_pad103, 12);		// 1156-1168
	AnimBlendFrameData* aPedBones[19];	// 1168-1244
	PADDING(_pad103_, 100);		// 1244-1344
	float fHealth;		 		// 1344-1348	;Health
	float fMaxHealth;			// 1348-1352	;MaxHealth
	float fArmour;				// 1352-1356	;Armour
	float fAim;
	PADDING(_pad104, 8);		// 1356-1368
	float fRotation1;			// 1368-1372	;Rotation1
	float fRotation2;			// 1372-1376	;Rotation2
	PADDING(_pad105, 44);		// 1376-1420
	CVehicle* pVehicle;			// 1420-1424	;pVehicle
	PADDING(_pad108, 8);		// 1424-1432
	uint32_t dwPedType;			// 1432-1436	;dwPedType
	uint32_t dwUnk1;	 // 1436-1440
	CWeapon *WeaponSlots[13]; // 1440-1804
	PADDING(_pad270, 12); // 1804-1816
	uint8_t byteCurWeaponSlot; // 1816-1817
	PADDING(_pad280, 23); // 1817-1840
	uint32_t pFireObject;	 // 1840-1844
	PADDING(_pad281, 44); // 1844-1888
	uint32_t  dwWeaponUsed; // 1888-1892
	uintptr_t pdwDamageEntity; // 1892-1896
};
#pragma pack(pop)