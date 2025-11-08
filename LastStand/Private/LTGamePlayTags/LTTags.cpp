#include "LTGamePlayTags/LTTags.h"

namespace LTTags
{
	namespace SetByCaller
	{
		UE_DEFINE_GAMEPLAY_TAG_COMMENT(Projectile,"LTTags.SetByCaller.Projectile","Tag For set by caller magnitude class")

	}
	namespace LTAbilities
	{
		UE_DEFINE_GAMEPLAY_TAG_COMMENT(Primary,"LTTags.LTAbilities.Primary","Tag For The Primary Ability")
		UE_DEFINE_GAMEPLAY_TAG_COMMENT(Secondary,"LTTags.LTAbilities.Secondary","Tag For The Secondary Ability")
		UE_DEFINE_GAMEPLAY_TAG_COMMENT(Tertiary,"LTTags.LTAbilities.Tertiary","Tag For The Tertiary Ability")
		UE_DEFINE_GAMEPLAY_TAG_COMMENT(ActivateOnGiven,"LTTags.LTAbilities.ActivateOnGiven","Tag For The  Ability")

		namespace Enemy
		{
			UE_DEFINE_GAMEPLAY_TAG_COMMENT(Attack,"LTTags.LTAbilities.Enemy.Attack","Tag for attacking")
		}
	}

	namespace Events
	{
		UE_DEFINE_GAMEPLAY_TAG_COMMENT(KillScored,"LTTags.Events.KillScored","Tag For The  Kill scored event")
		namespace Enemy
		{
			UE_DEFINE_GAMEPLAY_TAG_COMMENT(HitReact,"LTTags.Events.Enemy.HitReact","Tag For The  Hit React")
			UE_DEFINE_GAMEPLAY_TAG_COMMENT(EndAttack,"LTTags.Events.Enemy.EndAttack","Tag For Ending Attack")
		}
	}
}