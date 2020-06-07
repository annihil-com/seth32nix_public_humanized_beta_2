// ETH32 - an Enemy Territory cheat for windows
// Copyright (c) 2007 eth32 team
// www.cheatersutopia.com & www.nixcoders.org

// kobject: the idea is to put our own console commands in here, and
// leave hooked engine/cgame commands in CEngine


// Member functions are from Mars, ordinary functions are from Venus.

#include "eth32.h"
#include "settings.h"

#ifdef ETH32_PRIV
	#include "../priv/priv.h"
#endif


CXCommands CCommands;
extern void *etpro_A;
extern void *etpro_B;
extern void *etpro_C;
extern void *etpro_E;
extern uint32 etpro_win32;
extern uint32 etpro_linux;



// if manual namesteal disable auto. No args, do random steal, if arg, find match
void xcmd_Namesteal()
{
	eth32.settings.doNamesteal = false;
	int clients[MAX_CLIENTS];
	int i = 0;

	char name[256];

	if (Syscall.UI_Argc() == 1) {
		for (int n=0; n<MAX_CLIENTS; n++) {
			if (n == eth32.cg.clientNum || !IS_INFOVALID(n))
				continue;

			clients[i++] = n;
		}

		int n = (int)random()*i;
		strcpy(name, eth32.cg.players[clients[n]].name);
	} else {
		const char *m = Syscall.UI_Argv(1);

		for (int n=0; n<MAX_CLIENTS; n++) {
			if (n == eth32.cg.clientNum || !IS_INFOVALID(n))
				continue;

			if (stristr(Tools.CleanString(eth32.cg.players[n].name), m))
				clients[i++] = n;
		}

		if (i == 0) {
			Syscall.UI_Print("^3No player matching %s found\n", m);
			return;
		} else if (i>1) {
			Syscall.UI_Print("^3More players matching %s\n", m);
			return;
		} else
			strcpy(name, eth32.cg.players[clients[0]].name);
	}

	if (eth32.cg.pbserver)
		Tools.PBNamespoof(name);

	char buf[256];
	sprintf(buf, "name \"%s\"\n", name);
	Tools.BufferConsoleCommand(buf);
}

void xcmd_RandName()
{
	eth32.settings.doNamesteal = false;
	if (!Tools.nNames) {
		Syscall.UI_Print("^3No player names loaded\n");
		return;
	}

	int n = (int)(random()*Tools.nNames);
	//char buf[256];
	//sprintf(buf, "name \"%s\"\n", Tools.nameList[n]);
	//Tools.BufferConsoleCommand(buf);
	orig_syscall(UI_CMD_EXECUTETEXT, EXEC_APPEND,(va("name \"%s\"\n", Tools.nameList[n]))); 
}

void xcmd_RandClGuid()
{
	if (!Tools.nClguids) {
		Syscall.UI_Print("^3No guids loaded!\n");
		return;
	}

	int n = (int)(random()*Tools.nClguids);
	orig_syscall(UI_CMD_EXECUTETEXT, EXEC_APPEND,(va("cl_guid \"%s\"\n", Tools.clguidList[n])));
}

void xcmd_RandGuid()
{
	if (!Tools.nGuids) {
		Syscall.UI_Print("^3No guids loaded!\n");
		return;
	}

	int n = (int)(random()*Tools.nGuids);
	orig_syscall(UI_CMD_EXECUTETEXT, EXEC_APPEND,(va("eth_set etproguid \"%s\"\n", Tools.guidList[n])));
}

void xcmd_RandMac()
{
	if (!Tools.nMacs) {
		Syscall.UI_Print("^3No jaymacs loaded!\n");
		return;
	}

	int n = (int)(random()*Tools.nMacs);
	orig_syscall(UI_CMD_EXECUTETEXT, EXEC_APPEND,(va("eth_set jaymac \"%s\"\n", Tools.macList[n])));
}

void xcmd_unbanCommand()
{
	system("mv ~/.etwolf/etmain/etkey ~/.etwolf/etmain/etkey.old");
	orig_syscall(UI_CMD_EXECUTETEXT, EXEC_APPEND, "pb_cdkeyreg \n");
	orig_syscall(UI_CMD_EXECUTETEXT, EXEC_APPEND, "eth_randname; eth_randguid; eth_randmac; eth_randclguid; wait 50; reconnect \n");
}

void xcmd_HackSpam()
{	// sol: added simple spam, feel free to modify however you like
	orig_syscall(UI_CMD_EXECUTETEXT, EXEC_APPEND, "say \"^9[ ^3s^7ETH32^9nix ^7Public ^3" ETH32_VERSION " ^7by ^7STAR^9/^7rabbnix.com ^9& ^3*^7nixCoders.org ^9]\n\"");
	orig_syscall(UI_CMD_EXECUTETEXT, EXEC_APPEND, "say \"^9[ ^7Cheat different^9 - ^7Cheat FREELY^9 ]\n\" \n");
}

void xcmd_RabbSpam()
{	//added simple rabbnixspam!
	orig_syscall(UI_CMD_EXECUTETEXT, EXEC_APPEND, "say \"^9[ ^7Visit ^3rabbnix^9.^3com ^7for the best Linuxbots^9!! ^9]\n\"");
}

// Stupid and useless spam ;) from http://www.network-science.de/ascii/ - star
void xcmd_spamCommand()
{	//added simple sETH32nix spam
	orig_syscall(UI_CMD_EXECUTETEXT, EXEC_APPEND, "say \"^7        _______ _______ _______ ______ ______        ^9 __\"\n");
	orig_syscall(UI_CMD_EXECUTETEXT, EXEC_APPEND, "say \"^3.-----.^7|    ___|_     _|   |   |__    |__    |^9.-----.|__|.--.--.\"\n");
	orig_syscall(UI_CMD_EXECUTETEXT, EXEC_APPEND, "say \"^3|__ --|^7|    ___| |   | |       |__    |    __|^9|     ||  ||_   _|\"\n");
	orig_syscall(UI_CMD_EXECUTETEXT, EXEC_APPEND, "say \"^3|_____|^7|_______| |___| |___|___|______|______|^9|__|__||__||__.__|\"\n");

}

void cleanPK3Command()
{
	system("find ~/.etwolf/ -name '*.pk3' -size -1200k -delete");
	orig_syscall(UI_PRINT, "^nClean pk3 done.\nYou must restart the game now.\n");
}

void cheatspamCommand1() {

	orig_syscall(UI_CMD_EXECUTETEXT, EXEC_APPEND, "say \"^9[ ^7Cheat ^3Different ^9- ^7Cheat ^3OPEN SOURCE ^9]\"\n");
}

void cheatspamCommand2() {

	orig_syscall(UI_CMD_EXECUTETEXT, EXEC_APPEND, "say \"^9[ ^7Undetected for ^3years ^9- 7Clean^3PBss ^9- ^7Only for ^3LINUX ^9]\"\n");
}

void xcmd_savesettings()
{
	if (Syscall.UI_Argc() == 1){
		Syscall.UI_Print("^2must specify a file\n");
		return;
	}

	char file[256];
	sprintf(file, "%s/%s", eth32.path, Syscall.UI_Argv(1));

	if (Settings.SaveUserSettings((const char*)file))
		Syscall.UI_Print("^2done.\n");
	else
		Syscall.UI_Print("^1error while saving to %s\n", Syscall.UI_Argv(1));
}

void xcmd_loadsettings()
{
	if (Syscall.UI_Argc() == 1){
		Syscall.UI_Print("^2must specify a file\n");
		return;
	}

	Settings.Load(Syscall.UI_Argv(1));
	Syscall.UI_Print("^2done.\n");
}

void goHome()
{
	Syscall.UI_ExecuteText("connect 87.99.33.29:27962\n");
}

void formatSetting(char *out, size_t o_s, const settingdef_t *setting)
{
	switch (setting->type) {
		case SETTING_INT:
			sprintf(out, "^9%i", *(int *)setting->target);
			break;
		case SETTING_FLOAT:
			sprintf(out, "^9%.3f", *(float *)setting->target);
			break;
		case SETTING_BOOL:
			(*(bool *)setting->target) ? strcpy(out, "^2true") : strcpy(out, "^1false");
			break;
		case SETTING_VEC3:
		{
			float *v = (float*)setting->target;
			sprintf(out, "^2{^9%.3f^2, ^9%.3f^2, ^9%.3f^2}", v[0], v[1], v[2]);
			break;
		}
		case SETTING_VEC4:
		{
			float *v = (float*)setting->target;
			sprintf(out, "^2{^9%.3f^2, ^9%.3f^2, ^9%.3f^2, ^9%.3f^2}", v[0], v[1], v[2], v[3]);
			break;
		}
		case SETTING_BYTE3:
		{
			char *b = (char*)setting->target;
			sprintf(out, "^9%3i %3i %3i", b[0], b[1], b[2]);
			break;
		}
		case SETTING_STRING:
		{
			sprintf(out, "^o%s", (char *)setting->target);
			break;
		}
		default:
			strcpy(out, "^3unknown type");
			break;
	}
}

// handles main settings only for now
void xcmd_Settings()
{
	Settings.ConsoleCommand();
}

void xcmd_Toggle()
{
	Settings.Toggle();
}

void xcmd_CvarForce()
{
	if (Syscall.UI_Argc() == 1){
		Syscall.UI_Print("^dCvar Force List\n");
		cvarInfo_t *c = Tools.userCvarList;
		int i = 0;
		while (c) {
			Syscall.UI_Print("^3%03i  ^2%16s   ^9\"^o%s^9\"\n",i, c->name, c->ourValue);
			c = c->next;
			i++;
		}

		return;
	} else if (Syscall.UI_Argc() == 2){
		const char *s = Syscall.UI_Argv(1);
		cvarInfo_t *c = Tools.userCvarList;
		while (c) {
			if (!strcasecmp(s, c->name))
				Syscall.UI_Print("^2%16s   ^9\"^o%s^9\"\n", c->name, c->ourValue);
			c = c->next;
		}
		return;
	}

	char *cvarName = strdup(Syscall.UI_Argv(1));
	char *val = strdup(Syscall.UI_Argv(2));

	// delete a cvar (( FIX the 0th cvar)
	if (!strcasecmp(cvarName, "del")){
		int num = atoi(val);
		if (num > 0){
			if (Tools.userCvarList[num].next)
				Tools.userCvarList[num-1].next = &Tools.userCvarList[num+1];
			else
				Tools.userCvarList[num-1].next = NULL;

			Syscall.UI_Print("^dDeleted ^2%s\n", Tools.userCvarList[num].name);
		}
	}

	// see if we should update an already present cvar
	bool found = false;
	cvarInfo_t *c = Tools.userCvarList;
	while (c) {
		if (!strcasecmp(cvarName, c->name)){
			strncpy(c->ourValue, val, MAX_STRING_CHARS);
			Syscall.UI_Print("^dUpdated:\n^2%16s   ^9\"^o%s^9\"\n", c->name, c->ourValue);
			found = true;
			break;
		}
		c = c->next;
	}

	if (!found && strcasecmp(cvarName, "del")){
		Syscall.UI_Print("^dAdded new entry:\n^2%16s   ^9\"^o%s^9\"\n", cvarName, val);
		Tools.AddUserCvar(cvarName, val);
	}

	Tools.SaveUserCvars();

	free(val);
	free(cvarName);
}

void xcmd_setEtproGuid()
{
	if (Syscall.UI_Argc() == 1)
	{
		if (!eth32.settings.etproGuid || strlen(eth32.settings.etproGuid) < 2)
			Syscall.UI_Print("^dEtpro Guid: ^2original");
		else
			Syscall.UI_Print("^dEtpro Guid: ^7%s", eth32.settings.etproGuid);
		return;
	}

	strncpy(eth32.settings.etproGuid, Syscall.UI_Argv(1), 1024);
	Syscall.UI_Print("^dNew etpro guid: ^7%s\n^dSetting won't take effect until next map (or do /reconnect)!", eth32.settings.etproGuid);
}

void xcmd_SetSpecServ()
{
	if (!eth32.cg.hooked){
		Syscall.UI_Print("^dNot connected\n");
		return;
	}

	if (Syscall.UI_Argc() == 1){
		Syscall.UI_Print("^dserver_ip:port\n");
		return;
	}

	if (!strchr(Syscall.UI_Argv(1), ':')) {
		Syscall.UI_Print("^dwrong format, must be server_ip:port\n");
		return;
	}

	Spectator.KillThread();
	Sleep(3000);
	if (Spectator.active) {
		Syscall.UI_Print("^dError shutting thread down :(\n");
		return;
	}

	strcpy(eth32.settings.specServer, Syscall.UI_Argv(1));
	Spectator.LaunchThread();
}

void xcmd_specstats()
{
	if (!eth32.settings.getSpeclist) {
		Syscall.UI_Print("^dspeclisting not activated\n");
		return;
	}

	if (!eth32.cg.hooked){
		Syscall.UI_Print("^dNot connected\n");
		return;
	}

	int bs, rq;
	char server[64];
	Spectator.GetStats(&bs, &rq, server);
	Syscall.UI_Print("^dServer: ^2%s ^dBytes rec: ^2%i ^dReq: ^2%i\n", bs, rq, server);
}

void xcmd_AimKeyDown()
{
	Aimbot.SetAimkeyStatus(true);
}

void xcmd_AimKeyUp()
{
	Aimbot.SetAimkeyStatus(false);
}

void setEtproOS()
{
	if (Syscall.UI_Argc() == 1){
		Syscall.UI_Print("^2%s", eth32.settings.etproOs ? "linux" : "win32");
		return;
	}

	char *cmd = strdup(Syscall.UI_Argv(1));

	if (!strcasecmp(cmd, "win"))
		eth32.settings.etproOs = false;
	else
		eth32.settings.etproOs = true;

	Syscall.UI_Print("^2new etpro OS set to %s", eth32.settings.etproOs ? "linux" : "win32");
	free(cmd);

	if (eth32.cgMod->type == MOD_ETPRO)
		orig_etproAntiCheat(etpro_A, etpro_B, etpro_C, eth32.settings.etproOs ? etpro_linux : etpro_win32, etpro_E, eth32.settings.etproGuid);
}

void xcmd_killspam()
{
	if (Syscall.UI_Argc() == 1){
		if (Tools.TotalKillspam() == 0) {
			Syscall.UI_Print("^dno kill spam loaded\n");
			return;
		}
		Syscall.UI_Print("^2%i killspam definitions loaded\n", Tools.TotalKillspam());
		Syscall.UI_Print("^9--------------------------------\n");
		for (int i=0; i<Tools.TotalKillspam(); i++)
			Syscall.UI_Print("^3%0.2i    %s\n", i, Tools.GetKillspam(i));

		return;
	}

	if (!strcmp(Syscall.UI_Argv(1), "clear")) {
		Tools.ClearKillspam();
		return;
	}

	Tools.AddKillspam((char*)Syscall.UI_Argv(1));
	Syscall.UI_Print("^2added %s\n", Syscall.UI_Argv(1));
}

void xcmd_multikillspam()
{
	if (Syscall.UI_Argc() == 1){
		if (Tools.TotalMultikillspam() == 0) {
			Syscall.UI_Print("^dno multikill spam loaded\n");
			return;
		}
		Syscall.UI_Print("^2%i multikillspam definitions loaded\n", Tools.TotalMultikillspam());
		Syscall.UI_Print("^9--------------------------------\n");
		for (int i=0; i<Tools.TotalMultikillspam(); i++)
			Syscall.UI_Print("^3%0.2i    %s\n", i, Tools.GetMultikillspam(i));

		return;
	}

	if (!strcmp(Syscall.UI_Argv(1), "clear")) {
		Tools.ClearMultikillspam();
		return;
	}

	Tools.AddMultikillspam((char*)Syscall.UI_Argv(1));
	Syscall.UI_Print("^2added %s\n", Syscall.UI_Argv(1));
}

void xcmd_selfkillspam()
{
	if (Syscall.UI_Argc() == 1){
		if (Tools.TotalSelfkillspam() == 0) {
			Syscall.UI_Print("^dno kill spam loaded\n");
			return;
		}
		Syscall.UI_Print("^2%i killspam definitions loaded\n", Tools.TotalSelfkillspam());
		Syscall.UI_Print("^9--------------------------------\n");
		for (int i=0; i<Tools.TotalSelfkillspam(); i++)
			Syscall.UI_Print("^3%0.2i    %s\n", i, Tools.GetSelfkillspam(i));

		return;
	}

	if (!strcmp(Syscall.UI_Argv(1), "clear")) {
		Tools.ClearSelfkillspam();
		return;
	}

	Tools.AddSelfkillspam((char*)Syscall.UI_Argv(1));
	Syscall.UI_Print("^2added %s\n", Syscall.UI_Argv(1));
}

void xcmd_suicidespam()
{
	if (Syscall.UI_Argc() == 1){
		if (Tools.TotalSuicidespam() == 0) {
			Syscall.UI_Print("^dno suicide spam loaded\n");
			return;
		}
		Syscall.UI_Print("^2%i suicide spam definitions loaded\n", Tools.TotalSuicidespam());
		Syscall.UI_Print("^9--------------------------------\n");
		for (int i=0; i<Tools.TotalSuicidespam(); i++)
			Syscall.UI_Print("^3%0.2i    %s\n", i, Tools.GetSuicidespam(i));

		return;
	}

	if (!strcmp(Syscall.UI_Argv(1), "clear")) {
		Tools.ClearSuicidespam();
		return;
	}

	Tools.AddSuicidespam((char*)Syscall.UI_Argv(1));
	Syscall.UI_Print("^2added %s\n", Syscall.UI_Argv(1));
}

void xcmd_deathspam()
{
	if (Syscall.UI_Argc() == 1){
		if (Tools.TotalDeathspam() == 0) {
			Syscall.UI_Print("^dno death spam loaded\n");
			return;
		}
		Syscall.UI_Print("^2%i deathspam definitions loaded\n", Tools.TotalDeathspam());
		Syscall.UI_Print("^9--------------------------------\n");
		for (int i=0; i<Tools.TotalDeathspam(); i++)
			Syscall.UI_Print("^3%0.2i    %s\n", i, Tools.GetDeathspam(i));

		return;
	}

	if (!strcmp(Syscall.UI_Argv(1), "clear")) {
		Tools.ClearDeathspam();
		return;
	}

	Tools.AddDeathspam((char*)Syscall.UI_Argv(1));
	Syscall.UI_Print("^2added %s\n", Syscall.UI_Argv(1));
}

CXCommands::CXCommands(void)
{
	cmdsRegistered = false;
}

void CXCommands::RegisterCommands()
{
	if (cmdsRegistered || !orig_Cmd_AddCommand)
		return;

	orig_Cmd_AddCommand("eth_home", &goHome);
	orig_Cmd_AddCommand("eth_namesteal", &xcmd_Namesteal);
	orig_Cmd_AddCommand("eth_randname", &xcmd_RandName);
	orig_Cmd_AddCommand("eth_cvar", &xcmd_CvarForce);
	orig_Cmd_AddCommand("eth_randclguid", &xcmd_RandGuid);
	orig_Cmd_AddCommand("eth_randmac", &xcmd_RandMac);
	orig_Cmd_AddCommand("eth_etproguid", &xcmd_setEtproGuid);
	orig_Cmd_AddCommand("eth_set", &xcmd_Settings);
	orig_Cmd_AddCommand("eth_toggle", &xcmd_Toggle);
	orig_Cmd_AddCommand("eth_unban", &xcmd_unbanCommand);
	orig_Cmd_AddCommand("eth_load", &xcmd_loadsettings);
	orig_Cmd_AddCommand("eth_save", &xcmd_savesettings);
	orig_Cmd_AddCommand("eth_spam", &xcmd_spamCommand);
	orig_Cmd_AddCommand("eth_cleanpk3", &cleanPK3Command);
//	orig_Cmd_AddCommand("eth_randkick", &randomKickCommand);
	orig_Cmd_AddCommand("eth_etproos", &setEtproOS);

	// spamz
	orig_Cmd_AddCommand("eth_killspam", &xcmd_killspam);
	orig_Cmd_AddCommand("eth_selfkillspam", &xcmd_selfkillspam);
	orig_Cmd_AddCommand("eth_suicidespam", &xcmd_suicidespam);
	orig_Cmd_AddCommand("eth_deathspam", &xcmd_deathspam);
	orig_Cmd_AddCommand("eth_multikillspam", &xcmd_multikillspam);
	orig_Cmd_AddCommand("eth_cheat1", &cheatspamCommand1);
	orig_Cmd_AddCommand("eth_cheat2", &cheatspamCommand2);
	orig_Cmd_AddCommand("eth_hack", &xcmd_HackSpam);
	orig_Cmd_AddCommand("eth_rabb", &xcmd_RabbSpam);

	orig_Cmd_AddCommand("eth_specserv", &xcmd_SetSpecServ);
	orig_Cmd_AddCommand("eth_specstats", &xcmd_specstats);

	orig_Cmd_AddCommand("+aim", &xcmd_AimKeyDown);
	orig_Cmd_AddCommand("-aim", &xcmd_AimKeyUp);

	#ifdef ETH32_PRIV
		RegisterPrivCommands();
	#endif


	cmdsRegistered = true;
}
