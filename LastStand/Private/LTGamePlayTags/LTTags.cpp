#include "LTGamePlayTags/LTTags.h"

namespace LTTags
{
	namespace LTAbilities
	{
		UE_DEFINE_GAMEPLAY_TAG_COMMENT(Primary,"LTTags.LTAbilities.Primary","Tag For The Primary Ability")
		UE_DEFINE_GAMEPLAY_TAG_COMMENT(Secondary,"LTTags.LTAbilities.Secondary","Tag For The Secondary Ability")
		UE_DEFINE_GAMEPLAY_TAG_COMMENT(Tertiary,"LTTags.LTAbilities.Tertiary","Tag For The Tertiary Ability")
		UE_DEFINE_GAMEPLAY_TAG_COMMENT(ActivateOnGiven,"LTTags.LTAbilities.ActivateOnGiven","Tag For The  Ability")
	}

	namespace Events
	{
		namespace Enemy
		{
			UE_DEFINE_GAMEPLAY_TAG_COMMENT(HitReact,"LTTags.Events.Enemy.HitReact","Tag For The  Hit React")
		}
	}
}