
#ifndef ENUMS_H_
#define ENUMS_H_

enum Order {
	LIVING,
	STATUS,
	ENTITY,
	ITEM,
	UNIT,
	BLOCK,
	GRAVITY
};

enum BlockType {
	NULL_BLOCK_TYPE,

	NONE,
	FULL,
	UPSTAIRS,
	DOWNSTAIRS,
	SPIRALSTAIRS
};

enum Tag {
	NULL_TAG,

	INVISIBLE,
	REVEALED,
	ROOTED,
	PHASING,
	FLYING,
	FALLING,
	LEVITATING,
	TRUESIGHT,
	STUNNED,
	HELPLESS,
	PREY,
	NUMBING,
	WARDED,
	FOOD,
	ORE,

	SMELTABLE,
	MINEABLE,
	ETERNAL

};

enum ItemTag {
	NULL_ITEM_TAG,

	LEGLIKE,
	HANDLIKE,
	HEARTLIKE,
	GUNLIKE,
	BULLETLIKE,
	CORELIKE
};

enum ActionTag {
	NULL_ACTION_TAG,

	COMBAT,
	MOVEMENT,
	GRAB,
	DROP,
	STORE,
	MISC
};

enum ActionSubtag {
	NULL_ACTION_SUBTAG,

	WALK,
	RISKWALK,
	FLY,
	TELEPORT,

	MELEE,
	RANGED
};

enum FailType {
	NULL_FAIL_TYPE,

	SUCCESS,
	OUT_OF_RANGE,
	BROKEN,
	NO_AMMO,
	NO_PATH,
	CANT_MOVE_THERE,
	CANT_MOVE
};

enum StatusSpreadingType {
	NULL_STATUS_SPREADING_TYPE,

	SOLO,
	SPREADING
};

// CURRENTLY: non-organ parts can't hold anything
enum ItemCarryStatus {
	NULL_ITEM_CARRY_STATUS,

	JUST_ADDED, // Fake carry statuses only used to indicate how things should be added / set on init / attached to eachother
	AUTO,
	BRAIN,
	ARMORED,
	ARMORING,

	GROUND,
	CARRIED, // Indicates we're not on the ground and not an organ but being carried anyways, either being held/subheld, stored, or embedded/subembedded
	STORED,
	HELD,
	EMBEDDED, // this is embedded by one or more things
	EMBEDDING, // this is embedding into something else
	ORGAN
};

#endif /* ENUMS_H_ */
