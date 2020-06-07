// ETH32 - an Enemy Territory cheat for windows
// Copyright (c) 2007 eth32 team
// www.cheatersutopia.com & www.nixcoders.org
// (ported to unix by kobj and blof)

/*
	The main header file we might say, contains all the info that is used while playing.
	When you're adding something in here, make sure it's being added to the right struct!

	Also, please comment the members you're adding so other developers know what's the function of each part.
*/
#pragma once

#include "unixtypes.h"
#include "eth32shared.h"
//random Kick
#define IS_PLAYER_ENEMY(entityNum) (IS_PLAYER_VALID(entityNum) \
		&& (((eth32.clientInfo[entityNum].team != eth.clientInfo[eth.cg_clientNum].team) \
				&& (eth32.clientInfo[entityNum].targetType != PLIST_FRIEND)) \
			|| (eth32.clientInfo[entityNum].targetType == PLIST_TEAMKILLER)))


// stuff that we don't get from sdk
#include "q3_types.h"

// **************************
// Macros
// **************************
#define GET_PAGE(addr) ((void *)(((uint32)addr) & ~((uint32)(getpagesize() - 1))))
#define unprotect(addr) (mprotect(GET_PAGE(addr), getpagesize(), PROT_READ | PROT_WRITE | PROT_EXEC))
#define reprotect(addr) (mprotect(GET_PAGE(addr), getpagesize(), PROT_READ | PROT_EXEC))
#define BOUND_VALUE(var,min,max)	if((var)>(max)){(var)=(max);};if((var)<(min)){(var)=(min);}

#ifndef uint32
typedef unsigned int uint32;
#endif

#ifndef uchar
typedef unsigned char uchar;
#endif

#ifndef MAX_PATH
#define MAX_PATH	256
#endif

#define CG_VM   *eth32.game.vm == eth32.game.cgvm
#define UI_VM   *eth32.game.vm == eth32.game.uivm

typedef struct weapStat_s {
	int kills;
	int deaths;
	int shots;
	int hits;
	int headshots;
} weapStat_t;

#define WS_ABS_MAX	32
#define WS_ETM_MAX	22
#define WS_JAY_MAX	24 // ?
#define WS_NQ_MAX	32

typedef struct stats_s {
	int kills;
	int deaths;
	int spree;
	int longestSpree;
	float kdRatio;
	float threat;
	float accuracy;			// EV_BULLET based
	int suicides;
	int bulletsFired;		// EV_BULLET based
	int bulletsHit;			// EV_BULLET based

	int my_kills;
	int	my_deaths;
	int my_kdRatio;

	int killer;

	// noquarter seems to have most weapons - make big enough to fit all modz
	weapStat_t weap[WS_ABS_MAX];
	int bulletsFiredWS;
	int bulletsHitWS;
	float bulletAcc;
	int headshotsWS;
	float hr_kills;			// headshot ratio -> headshots/kills
	float hr_hits;			// headshot ratio -> headshots/hits
	float hr_shots;			// headshot ratio -> headshots/shots

}stats_t;

#define MAX_MULTI	48
#define MAX_HISTORY	100

typedef struct history_s {
	vec3_t	p;
	float	t;
} history_t;

typedef enum playerType_s {
	PLAYER_NORMAL,
	PLAYER_FRIEND,
	PLAYER_ENEMY,
} playerType_t;

typedef struct player_s {					// where we can access all the info we need on a player
	bool			*infoValid;		// we can add more data here later (aimpoints, visible, invunerable, etc.)
	centity_t		*cent;			// will be all pointers to the information we need in cg_entities and clientinfo
	entityState_t	*currentState;
	float			*lerpOrigin;
	char			*name;
	int				*team;
	int				*health;
	int				*cls;			// class
	lerpFrame_t		*lf;			// for animation correction

	orientation_t	orHead;			// head orientation (position & rotation)
// 	qhandle_t		OutlineShader;
	bool			friendly;		// true for teammates
	bool			invulnerable;	// to disable aiming at them, and possibly for use in chams
	bool			visible;		// is this player visible
	bool			targetingUs;	// is this player targeting us?
	float			distance;		// distance from view origin to player
	bool			allowPMSpam;	// allow PM killspam to this client

	int				screenX;		// x coord on screen
	int				screenY;		// y coord on screen

	int	ping;	//elite

	qhandle_t		headModel;

	stats_t			stats;
	vec3_t			headPt;			// visible point on the head
	vec3_t			bodyPt;			// visible point on body box
	vec3_t			aimPt;			// if aimbot is used, this will need to be set
	vec3_t			preAimPt;		// for early aim to reduce spread in the first shots

	int				clientNum;		// so we can use player_t* easier
	bool			eth32user;
	playerType_t	playerType;		// friend 'o f00
	char			portalName[64];	// store portal name
	history_t		history[MAX_HISTORY+1];	// store position history for prediction
	int				history_idx;			// current index in history table
} player_t;

// for use by portal
typedef struct eth32user_s {
	char username[64];
	char server[32];
	int clientNum;
	int etVersion;
	int modVersion;
	float eth32Version;
	char serverName[64];
	char serverMapName[64];
	player_t *player;
	bool anon;
	bool frnd;	// friend
} eth32user_t;

// for tracking server info
typedef struct eth32server_s {
	char serverAddr[32];
	char serverName[64];
	char serverMapName[64];
	int numUsers;
	int numFriends;
	bool rampage;
} eth32server_t;

typedef struct gentity_s {
	bool			*infoValid;
	centity_t		*cent;			// will be all pointers to the information we need in cg_entities and clientinfo
	entityState_t	*currentState;
	float			*lerpOrigin;		// for greater portability

	bool			visible;		// is this gentity drawn inside screen coords?
	int				screenX;		// x coord on screen
	int				screenY;		// y coord on screen

	int				clientNum;
}gentity_t;

typedef enum weapType_s {
	WT_NONE,
	WT_KNIFE,
	WT_PISTOL,
	WT_SMG,
	WT_STEN,
	WT_MG,
	WT_RIFLE,
	WT_SNIPER,
	WT_SHOTGUN,
	WT_HEAVY,
	WT_EXPLOSIVE,
	WT_MAX,
} weapType_t;

typedef enum killSpamtype_s {
	KILLSPAM_ALL,
	KILLSPAM_SELECTED,
	KILLSPAM_MAX
} killSpamtype_t;

typedef enum aimProtect_s {
	PROTECT_OFF,
	PROTECT_SPECS,
	PROTECT_ALL,
	PROTECT_MAX
} aimProtect_t;

// sol: weapon attribs will be used for figuring out what kind of weapon we are dealing with
typedef enum weapAttrib_s {
	WA_NONE	=			0,
	WA_USER_DEFINED =	(1 << 0),	// allowed to configure through weapon window when enabled
	WA_OVERHEAT =		(1 << 1),	// this weapon can overheat
	WA_BLOCK_FIRE =		(1 << 2),	// this weapon should block fire in certain autofire modes
	WA_AKIMBO =			(1 << 3),	// dual weapons, need to know for drawing ammo properly
	WA_SCOPED =			(1 << 4),	// this weapon is in scoped mode
	WA_UNSCOPED =		(1 << 5),	// this weapon is in unscoped mode
	WA_RIFLE_GRENADE =	(1 << 6),	// camera use, grenade bot
	WA_MORTAR =			(1 << 7),	// camera use
	WA_PANZER =			(1 << 8),	// camera use
	WA_SATCHEL =		(1 << 9),	// camera use
	WA_NO_AMMO =		(1 << 10),	// this weapon doesn't use ammo
	WA_ONLY_CLIP =		(1 << 11),	// this weapon only uses clip (disregard ammo)
	WA_BALLISTIC =		(1 << 12),	// this weapon can be used for the ballistics aimbot
	WA_GRENADE =		(1 << 13),	// grenade bot (different code then riflenade)
} weapAttrib_t;

typedef struct weapdef_s {
	char	*name;
	// non user defined
	vec3_t	r_origin;		// weapon render: adjusted origin
	vec3_t	r_angle;		// weapon render: angle to place weapon
	float	r_dist;			// weapon render: camera distance from adjusted origin

	weapType_t	type;		// type of weapon, user can set a preference to all weapons of the same type
	unsigned int attribs;	// a mix of weapAttrib_t for filtering weapons
	int		otherAkimbo;	// if this weapon is akimbo, this is the matching weapon to use for ammo

	// things user can set per weapon if userDefined
	int		range;			// max range aimbot will search for targets
	int		headTraces;		// number of head traces to check
	int		bodyTraces;		// number of body traces to check
	int		delay;			// time in msec between firing
	float		Sdelay;
	bool	autofire;		// use autofire for this weap
	bool	antiOverheat;	// if weap can overheat, enable anti-overheat

} weapdef_t;

typedef enum eth32Chams_s {
	CHAMS_OFF,
	CHAMS_KERAMIC,
	CHAMS_CRYSTAL,
	CHAMS_GLOW,
	CHAMS_FLAME,
	CHAMS_SOLIDA,
	CHAMS_SOLIDB,
	CHAMS_QUADA,
	CHAMS_QUADB,
	CHAMS_QUADC,
	CHAMS_QUADD,
	CHAMS_MATRIX,
	CHAMS_THERMAL,
	CHAMS_PLASTIC,
	CHAMS_PLASMA,
	CHAMS_TEST,
	MAX_CHAMS
} eth32Chams_t;

typedef enum playerESP_s {
	ESP_PLAYER_MIDDLE,
	ESP_PLAYER_SIDE,
	ESP_PLAYER_STAGERED,
	ESP_PLAYER_MAX
} playerESP_t;

typedef enum gentityESP_s {
	ESP_GENT_GRENADE,
	ESP_GENT_GRENADEP,
	ESP_GENT_DYNAMITE,
	ESP_GENT_LANDMINE,
	ESP_GENT_MORTAR,
	ESP_GENT_PANZER,
	ESP_GENT_RIFLENADE,
	ESP_GENT_SATCHEL,
	ESP_GENT_SMOKE,
	ESP_GENT_MAX
} gentityESP_t;

typedef enum gentityESPTCE_s {
	ESP_GENT_TCE_GRENADE,
	ESP_GENT_TCE_FLASH,
	ESP_GENT_TCE_SMOKE,
	ESP_GENT_TCE_DYNAMITE,
	ESP_GENT_TCE_MAX
} gentityESPTCE_t;

typedef enum namestealMode_s {
	NAMESTEAL_TEAM,
	NAMESTEAL_ENEMY,
	NAMESTEAL_ALL,
	NAMESTEAL_FILE,
	NAMESTEAL_MAX
} namestealMode_t;

typedef enum eth32AutoPoints_s {
	AUTOPT_OFF,
	AUTOPT_LOW,
	AUTOPT_HIGH,
	AUTOPT_MAX
} eth32AutoPoints_t;


typedef enum soundLevel_s {
	SOUND_LEVEL_ONE,
	SOUND_LEVEL_TWO,
	SOUND_LEVEL_THREE,
	SOUND_LEVEL_FOUR,
	SOUND_LEVEL_FIVE,
	SOUND_LEVEL_MAX

} soundLevel_t;

typedef enum soundLevelSize_s {
	SOUND_LEVEL_SIZE_ONE,
	SOUND_LEVEL_SIZE_TWO,
	SOUND_LEVEL_SIZE_THREE,
	SOUND_LEVEL_SIZE_FOUR,
	SOUND_LEVEL_SIZE_FIVE,
	SOUND_LEVEL_SIZE_MAX

} soundLevelSize_t;

typedef enum pbss_s {
	PB_SS_NORMAL,
 	PB_SS_CUSTOM,
  	PB_SS_CLEAN,
   	PB_SS_MAX
} pbss_t;

typedef enum customxhair_s {
	XHAIR_OFF,
 	XHAIR_SNIPER,
  	XHAIR_CROSS,
   	XHAIR_CROSS2,
	XHAIR_DOT,
	XHAIR_LINE,
	XHAIR_MAX
} customxhair_t;

typedef struct eth32sounds_s {

	sfxHandle_t		hitsound;
	sfxHandle_t		hitsound2;
	sfxHandle_t		hitsound3;
	sfxHandle_t		hitsoundtm;

	sfxHandle_t		playsound[SOUND_LEVEL_MAX][SOUND_LEVEL_SIZE_MAX];
} eth32sounds_t;

typedef struct media_s {					// all the medias (pictures, sounds, models, etc)
	qhandle_t		white;
	qhandle_t		cursor;
	qhandle_t		binoc;
	qhandle_t		smokePuff;
	qhandle_t		reticleSimple;
	qhandle_t		eth32Icon;

	fontInfo_t		fontArial;

	qhandle_t		chams[MAX_CHAMS];

	// effects
	qhandle_t		disk;
	qhandle_t		circle;

	eth32sounds_t   sounds;
	// menu stuff
	qhandle_t		statbar;
	qhandle_t		statbar2;
	qhandle_t		colorTable;

	// TCE model
	qhandle_t			grenadeTCE;			// TCE grenade Model
	qhandle_t			dynamiteTCE;		// TCE dynamite Model
	qhandle_t			flashGrenadeTCE;	// TCE flash Grenade Model
	qhandle_t			smokeGrenadeTCE;	// TCE smoke Grenade Model
	qhandle_t			medpackTCE;			// TCE med pack model
	// TCE icons
	qhandle_t			grenadeTCEIcon;		// TCE grenade Icon
	qhandle_t			dynamiteTCEIcon;	// TCE dynamite Icon
	qhandle_t			smokeGrenadeTCEIcon;// TCE flash Grenade Icon
	qhandle_t			flashGrenadeTCEIcon;// TCE smoke Grenade Icon

	// Regular Models
	qhandle_t			chamsOut;
	qhandle_t			disguisedIcon;		// for disguised players
	qhandle_t			supplyRackAmmo;		// rack for Ammo Model
	qhandle_t			supplyRackHealth;	// rack for Health Model
	qhandle_t			rackAmmo;			// Ammo on rack Model
	qhandle_t			rackHealth;			// Health on rack Model
	qhandle_t 			medPack;			// Health pack pickup Model
	qhandle_t			ammoPack;			// Ammo pack pickup Model
	qhandle_t			grenadeAxisModel;	// Axis grenade
	qhandle_t			grenadeAlliedModel;	// Allied grenade
	qhandle_t			dynamiteModel;		// Dynamite Model
	qhandle_t			satchelModel;		// Satchel Model
	qhandle_t			rocketModel;		// Panzer rocket Model - some cheat servers use this for grenade
	qhandle_t			mortarModel;		// Mortar shell Model
	qhandle_t			thompsonModel;		// Thompson Model
	qhandle_t			mp40Model;			// Mp40 Model
	qhandle_t			stenModel;			// Sten Model
	qhandle_t			rifleNadeAxis;		// axis grenade model for riflelauncher
	qhandle_t			rifleNadeAllied;	// allied grenade model for riflelauncher
	// icons
	qhandle_t			grenadeAxisIcon;		// Axis grenade Icon
	qhandle_t			grenadeAlliedIcon;	// Allied grenade Icon
	qhandle_t			dynamiteIcon;		// Dynamite Icon
	qhandle_t			satchelIcon;		// Satchel Icon
	qhandle_t			landmineIcon;		// Landmine Icon

	qhandle_t			railCore;			// shader for railtrails
	qhandle_t			portalMarker;
	qhandle_t			combtnLeft, combtnRight, combtnCenter;
	qhandle_t			comselLeft, comselRight, comselCenter;

	//grenade target
	qhandle_t			grenTarget;

	qhandle_t			nullShader;
	qhandle_t			etlogoShader;

} media_t;

typedef struct bools_s {
	bool spawntimerReady;					// we can't use spawntimer until cgame gathers some info
} bools_t;

typedef enum teamState_s {
	TEAM_ENEMY,
	TEAM_FRIEND,
	MAX_TEAMSTATES,
} teamState_t;

typedef struct chargeTimes_s {
	int soldier[2];
	int medic[2];
	int engineer[2];
	int lt[2];
	int covops[2];
} chargeTimes_t;

typedef struct cgame_s {
	void 		*module;			// module (base) of cgame.dll in memory
	void		*handle;			// (unix) dlopen handle
	bool		automod;			// did we redirect unsupported mod to etmain?
	int			supported;			// used by VM_Create, if supported then modify vm->entryPoint

	int			clientNum;			// our ID on a server
	int			team;				// set once per frame to allow viewing team/enemy chams even while spec
	int			time;				// current server time
	int			zerohour;			// time of real first active frame
	int			frametime;			// time needed to draw this frame - can be used for prediction later
	int			xhairClientNum;		// client num at crosshair (-1 if none)

	player_t	players[MAX_CLIENTS];		// our player data , NOTE: we must know mod cent base/size and clientinfo base/size
	gentity_t	gentity[MAX_GENTITIES];		// gentity data
	char		spectators[MAX_CLIENTS][MAX_NAME_LENGTH];	// holds who is spectating us
	int			nspectators;		// no. of spectators
	player_t	*self;				// me!
	bool		pbserver;			// sv_punkbuster 1
	bool		serverObits;		// server-side obits (some etpub servers)

	snapshot_t		*snap;
	gameState_t		*gameState;
	pmoveExt_t		*pmext;
	playerState_t	*predictedps;

	weapdef_t   *currentWeapon;		// current weapon out of weaponList
	weapdef_t	*weaponList;		// current mod list of weapons
	weapdef_t	*modifyWeapon;		// used by weapon window
	int	modifyWeapNum;				// used by weapon window
	int numWeapons;					// mod dependent

	// rendering info
	float		screenXScale;
	float		screenYScale;
	refdef_t	*refdef;
	float		*refdefViewAngles;
	int			centerX, centerY;

	char		serverName[50];
	char		serverMapName[25];

	vec3_t		lerpOrigin;
	vec3_t		lerpAngles;

	// muzzle, viewangles
	vec3_t		muzzle;
	float		ourViewAngleX;
	float		ourViewAngleY;

	media_t		media;				// all our medias

	bools_t		bools;				// various checks

	int				spawnTimes[MAX_TEAMSTATES];	// spawntimes
	chargeTimes_t	chargeTimes;	// for use by weap charge

	int			lastTrackerUpdate;	// tracker update interval check
	char		selectedPortalUser[64];	// used by portal users window
	char		replyPlayer[128];	// stores sender name of last priv msg
	int			cgTime;				// cgame time
	bool		hasInit;			// finished CG_Init()
	float		spreadIndex;		// spread index for current weapon
	float		ping;
	int 		limbo;				// ammount of limbo players, used for aimbot and banner

	uint32		defaultConsoleShader;	// name says it all

	vec3_t		tempRenderVector;

	vmCvar_t	*cg_teamchatheight;
	bool		hooked;
	int			pbss;				// number of PB screenshots taken

	int			lastStatsReq;		// time of last stats request
	bool		wantStats;			// +stats down
	int			ws_max;				// mod dependant WS_MAX

	localEntity_t	*firstle;		// first entry of le's in cgame (needed for clean ss)
	localEntity_t	*highle;		// highest entry of le's in cgame found
} cgame_t;

typedef struct ui_s {
	void		*module;			// module (base) of ui.dll in memory
	void		*handle;			// (unix) dlopen handle
} ui_t;

typedef struct game_s {
	void		*module;				// et.exe module
	char		path[MAX_PATH];		// C:\path\to\ET\

	float		*viewAngleX;		// view angle x
	float		*viewAngleY;		// view angle y
	glconfig_t	*glconfig;			// et's glconfig
	int			*com_frameTime;		// continous, cgame independent msec counter

	qhandle_t	console[3];			// the three shares used for the console

	// ptrs to some cvars so we don't have to do Cvar_VariableStringBuffer
	cvar_t	*cg_fov;
	cvar_t	*sensitivity;
	cvar_t	*cg_railTrailTime;

	// linux only
	uint32	textSectionStart;
	uint32	textSectionEnd;

        uint32  cgvm;                                   // location of et's cg vm
        uint32  uivm;                                   // location of et's ui vm
        uint32  *vm;                                    // ptr to et's current vm
} game_t;

// MOD/ET defines - these values must never change
// Every new mod/et version must be added to the portal defines as well
#define MOD_ETMAIN		0
#define MOD_ETPUB		1
#define MOD_JAYMOD1		2
#define MOD_JAYMOD2		3
#define MOD_NOQUARTER	4
#define MOD_ETPRO		5
#define MOD_TCE			6

#define ET_255			0
#define	ET_256			1
#define ET_260			2
#define	ET_260b			3

typedef struct et_s {
	char			version[64];	// ET.exe version
	uint32			crc32;		// crc32 checksum of ET.exe
	int				ver;		// for portal communication

	uint32			viewAngleX;
	uint32			viewAngleY;
	uint32			inButtons;
	uint32			glConfig;
	uint32			com_frameTime;
	uint32			consoleshader;

	uint32			etroq_video;
	char			etroq_safe[5];

	uint32			syscall;
	uint32			Cvar_Get;
	uint32			Cvar_Set2;
	uint32			fs_searchpaths;
	uint32			FS_PureServerSetLoadedPaks;
	uint32			FS_AddGameDirectory;
	uint32			FS_AddGameDirectory2;
	uint32			FS_Startup;
	uint32			FS_Startup2;
	uint32			Cmd_AddCommand;
	uint32			VM_Create;
	uint32			Sys_LoadDll;
	uint32			LoadTGA;
	uint32			server_ip;
	uint32			SCR_UpdateScreen;
	uint32			Con_DrawConsole;
	uint32			currentVm;
	uint32			Cvar_VariableString;

	uint32			aimHackSize;
	uint32			aimHackOffs;
	char			aimHack[50];
} et_t;

typedef enum camType_s {
	CAM_MORTAR,
	CAM_FOLLOW,
	CAM_RIFLE,
	CAM_ENEMY,
	CAM_MIRROR,
	CAM_PANZER,
	CAM_SATCHEL,
	CAM_TARGET,
	CAM_DROP_ONE,
	CAM_DROP_TWO,
	CAM_DROP_THREE,
	CAM_DROP_FOUR,
	CAM_MAX
} camType_t;

typedef struct camInfo_s {
	int x1, y1, x2, y2;
	bool	display;
	float	distance;
	float	angle;
	float	fov;
	// dropcams
	bool	active;
	vec3_t	origin;
	vec3_t	axis;
} camInfo_t;

typedef struct gentityInfo_s {
	bool	chams;
	bool	text;
	bool	icon;
	bool	radarIcon;
	int		distance;
} gentityInfo_t;

typedef struct settings_s {	
	int snapDelay;
	float crossSize;
	float crossThick;
	int customXhair;
	bool removeFoliage;
	bool	specLockRemove;		// remove speclock blackscreen
	bool	loaded;		// not for normal use, to prevent saving settings when they are not rdy
	bool	requeststats;	// requests stats from server automatically (might cause floodkick on some servers)

	//outline chams
	int	outShader;
	int 	hasOutlineShader;
	int	hasOutlineShaderB;
	int	chamsPlayer;// player chams
	int	chamsWeapon;// weapon chams
	bool	chamsOurWeapon; // apply chams to our own weapon
	bool	espName;	// name esp
	bool	espTracker;	// draw portal names
	gentityInfo_t gentInfo[ESP_GENT_MAX];
	int	playerEspType; // sets value for esp type
	int	gentitySetting; // used for cycle throught type of gent for esp config

	// Human Vars
	float	humanPredict;
	float 	humanPitch;
	float	humanYaw;
	float	humanvalue;
	float	divmin;
	float	divmax;
	float	yspeed;
	float	xspeed;

	bool 	customSkies;	//custom skies (fueldump so far!)
	bool	grenadeDlight;	// extra grenade visuals
	bool	mortarDlight;	// extra mortar visuals
	bool	mortarTrace;	// extra mortar trace + esp
	bool	artyMarkers;	// extra arty markers

	bool	iconTracker;// draw portal icon
	bool	wallhack;	// wallhack :f
	bool	drawDisguised;	// draw disguised marker
	float	wallhackDistance;	// for players only
	bool	doDistWallhack;	// for players only
	bool	blackout;	// draw sniper/binocs blackout
	bool	weaponZoom;	// draw scoped weapon zoom
	float	scopedTurnSpeed;	// scoped turning speed
	int	smoketrnsp;	// smoke transparency changer
	bool	respawnTimers; // draw respawn timers window
	bool	autoTapout;	// tapout on death right to reinforce queue
	bool	getSpeclist;	// get spectator list
	char	specServer[64];		// alternate spec server

	int	aimMode;		// type of aimbot
	int	humanAimMode;	// type of human aim to do
	int	aimType;	// global setting to set aim style (always, on key, etc.) or disable aim globally
	int	aimSort;	// global target sort
	bool	autofire;	// global autofire settings (each weapon can be set for autofire as well)
	bool	lockTarget;
	bool	atkValidate;
	int	hitboxType;
	int	traceType;
	float	fov;
	float	predTarget;
	float   predTest;

	float spread;
	bool	predTargzor;
	float	predSelf;
	float 	bodybox;

	//Auto stuff
	bool 	autocorrections;
	bool    autoBoxSize;
	float   farBoxSize;
	float   closeBoxSize;
	float   rangeBoxSize;

/*    bool    standX;
    bool    crouchX;
    bool    standY;
    bool    crouchY;
    bool    standZ;
    bool    crouchZ;*/
    float   RangE;

    float   vecstandcloseX;
    float   vecstandfarX;
    float   veccrouchcloseX;
    float   veccrouchfarX;
    float   vecstandcloseY;
    float   vecstandfarY;
    float   veccrouchcloseY;
    float   veccrouchfarY;
    float   vecstandcloseZ;
    float   vecstandfarZ;
    float   veccrouchcloseZ;
    float   veccrouchfarZ;
    float   vecpronecloseX;
    float   vecpronefarX;
    float   vecpronecloseY;
    float   vecpronefarY;
    float   vecpronecloseZ;
    float   vecpronefarZ;

    bool    delaycorr;
    float   delayclose;
    float   delayfar;
    float   delayrange;

	int		predSelfType;
	float	dynamicHitboxScale;	// to scale dynamic hitboxes (or not)

	bool	drawHeadHitbox;
	bool	drawBodyHitbox;
	bool	drawBulletRail;
	bool	railWallhack;		// see the rails trough walls
	bool	drawHeadAxes;
	vec3_t	colorHeadHitbox;
	vec3_t	colorBodyHitbox;
	vec3_t	colorBulletRail;

	vec3_t	colorXAxis;	// originally just for head hitbox, but probably useful for whatever we want to draw axes with
	vec3_t	colorYAxis;
	vec3_t	colorZAxis;

	int		headRailTime;
	int		bulletRailTime;
	int		bodyRailTime;

	// for grenade aimbot
	bool	grenadeBot;
	bool	rifleBot;
	bool	grenadeBlockFire;
	bool	valGrenTrajectory;
	bool	valRifleTrajectory;
	bool	grenadeSenslock;
	int		grenadeFireDelay;
	float	grenadeZ;
	float	riflenadeZ;
	bool	grenadeAutoFire;
	bool	rifleAutoFire;
	int		ballisticPredict;
	bool	allowMultiBounce;
	float	radiusDamage;
	bool	ballisticRadiusDamage;
	bool	autoGrenTargets;

	/*bool	portalAnon;			// send anonymous info to tracker
	int		portalRampageNum;	// minimum number of players on server to qualify as a rampage
	bool	portalRampageNotify;// post current rampages to center print on portal update*/

	bool	killSounds;			// kill sounds :P
	bool	hitsounds;			// custom hitsound for mods that dont have it
	bool	hitsounds2;			// custom hitsound for mods that dont have it
	bool	hitsounds3;			// custom hitsound for mods that dont have it
	float		mkResetTime;		// multikill sound reset time
	//bool	customSounds;		// if custom sounds should be used
	bool	hqSounds;			// if HQ sounds are to be played
	bool	pureSounds;			// only play 'pure' sounds - usefull against annoying voicespam

	bool	killSpam;			// enable killspam
	bool	multikillSpam;		// enable multikill spam
	bool	deathSpam;			// enable spam when you die
	bool	suicideSpam;		// PM spam when someone /kill
	bool	pmKillspam;			// PM killspam
	bool	selfkillSpam;		// /kill spam
	int		KillspamType;		// Selected clients only or everyone

	float	radarRange;	// range used by CRadarWindow

	bool	nameClick;	// allow clicking names in chat window to start a pm
	bool	xhairInfo;	// display esp window of xhair entity
	int		xhairInfoTime;	// time xhairinfo will stay up

	uchar	colorTeam[3];
	uchar	colorTeamOut[3];
	uchar	colorTeamHidden[3];
	uchar	colorEnemy[3];
	uchar	colorEnemyOut[3];
	uchar	colorEnemyHidden[3];
	uchar	colorInvulnerable[3];
	uchar	colorTeamWeapon[3];
	uchar	colorEnemyWeapon[3];
	uchar	colorHealth[3];
	uchar	colorAmmo[3];

	char	pk3file[MAX_STRING_CHARS];
	char	etproGuid[MAX_STRING_CHARS];
	bool	etproOs;
	char	jayMac[MAX_STRING_CHARS];

	bool	thirdPerson;
	bool	origViewValues;
	bool	interpolatedPs;
	bool	dmgFeedback;

	int	autoPoints;		// automatic hitpoint number selection
	bool	autoCrouch;
	int	headbody;
	int	aimprotect;		// to disable aimbot on certain conditions
	float   pointsclose;
    	float   pointsfar;
    	float   pointsrange;
	//bool     vecCor; //rabbit

	bool	preAim;
	float	preAimTime;
	bool	preShoot;
	float	preShootTime;
	//float 	trigger;

	float	animCorrection;

	//bool	panzerSuicide;			// auto suicide if imminent panzer hit
	//float	panzerImpactDist;		// minimum distance to panzer impact point to commit suicide

	bool	defaultSoundsLoaded;

	bool	transparantConsole;
	bool	showStats;

	// cameras
	int			camType;
	int			dropCamCount;
	camInfo_t	cams[CAM_MAX];

	bool	grenadeTracer;
	bool	rifleTracer;

	// used for figuring out render settings per weapon, temporary
	//vec3_t weapOrigin;
	//vec3_t weapAngle;
	//float weapDist;
	

	// linux only settings go here
	bool	drawHackVisuals;
	int	pbScreenShot;


	/*bool    Avecz;
	bool    Apoint;
	bool    Ahitbox;*/
	bool    autoHeadsmg;

	// gui display options
	bool	guiBanner;
	bool	guiChat;
	bool	guiCenterPrint;
	bool	guiCenterPrintAnim;
	float	guiCenterPrintScale;
	bool	guiOriginal;
	float	BannerScale;
	char	BannerFmt[MAX_STRING_CHARS];

	// name steal options
	bool	doNamesteal;		// do namesteal - forced to off on connect!
	int	NamestealGrace;		// time to wait after joining
	int	NamestealMode;		// type of namestealing
	int	NamestealDelay;		// delay between steals
	int test;
} settings_t;

typedef struct cvarInfo_s {
	char name[MAX_STRING_CHARS];
	char ourValue[MAX_STRING_CHARS];
	char restoreValue[MAX_STRING_CHARS];
	bool isSet;
	cvarInfo_s *next;
} cvarInfo_t;

typedef struct guiassets_s {				// barebones of style management
	float fontScale;
	int	fontHeight;

	vec4_t titleColor;
	vec4_t textColor1;
	vec4_t textColor2;

	qhandle_t titleLeft, titleCenter, titleRight;

	qhandle_t winLeft;
	qhandle_t winTop;
	qhandle_t winTopLeft;
	qhandle_t winCenter; 

	qhandle_t txtinputLeft, txtinputCenter, txtinputRight;
	qhandle_t btnLeft, btnCenter, btnRight;
	qhandle_t btnselLeft, btnselCenter, btnselRight;

	qhandle_t dropboxArrow;
	qhandle_t check, checkBox;
	qhandle_t scrollbarArrow, scrollbarBtn, scrollbarTrack;

	qhandle_t sliderTrack, sliderBtn;
	qhandle_t camCorner;

	qhandle_t mousePtr;
} guiassets_t;

#define PB_CVAR_IN			0x1
#define PB_CVAR_OUT			0x2
#define PB_CVAR_INCLUDE		0x15
#define PB_CVAR_EXCLUDE		0x16

// from 1.738
typedef struct pb_cvar_s {
	char name[0x80];			// restricted cvar name
	char type;					// type of restriction
	char string[0x80];			// string value
	char padding[3];
	double low;					// lower bound
	double high;				// higher bound
	int unknown;
} pb_cvar_t;

typedef struct pb_s {
	bool 		loaded;
	bool		statusOK;
	void 		*handle;
	void 		*module;
	char 		file[MAX_PATH];

	uint32 		text;					// start of .text
	uint32		text_size;
	uint32		bss;					// start of .bss
	uint32		bss_size;

	uint32 		*nCvars;				// total PB restricted cvars
	pb_cvar_t 	**cvarlist;

	char		spoofIp[16];
	char		realIp[16];
} pb_t;

typedef struct eth32_s {
	cgame_t			cg;					// info from cgame lib
	ui_t			ui;					// info from ui lib
	game_t			game;				// info from et.exe

	const et_t		*et;				// needed info about et.exe
	const cgMod_t	*cgMod;				// needed info about cgame.dll
	pb_t			pb;					// infos about PB module

	settings_t		settings;			// our user settings

	stats_t			stats;				// EntitiyEvent info

	guiassets_t		guiAssets;			// used for CGui for rendering

	char			path[MAX_PATH];		// C:\path\to\eth32\

	bool			authed;
	bool			authEnabled;
	bool			SetTrigger;
	bool			cgameLoaded;		// tracker
	char			server[64];			// tracker

	char			pk3File[MAX_STRING_CHARS];	// pk3file
	uint32			eth32CRC;

	Display 		*x11disp;			// for restoring X params on crash
	Window 			*x11win;			// for restoring X params on crash
	bool			eth32mod;			// dump eth32's client offsets
	uint32			eth32modcrc;
	//Test for random Kick
	bool			clientInfo;
	bool			cg_clientNum;
} eth32_t;

extern eth32_t eth32;

// kobject: imported this from Q3 SDK
// downtime & msec only have effect for movement buttons, so for attack we're in the clear
typedef struct kbutton_s {
	int			down[2];		// key nums holding it down
	unsigned	downtime;		// msec timestamp
	unsigned	msec;			// msec down this frame if both a down and up happened
	int			active;			// current state
	int			wasPressed;		// set when down, not cleared when up
} kbutton_t;

// for perl scripting
/*typedef struct perlScript_s {
	char	basename[256];
	char	path[MAX_STRING_CHARS];
	perlScript_s *next;
} perlScript_t;*/

//extern perlScript_t *perl_scripts;
