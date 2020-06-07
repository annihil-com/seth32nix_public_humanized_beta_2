// ETH32 - an Enemy Territory cheat for windows
// Copyright (c) 2007 eth32 team
// www.cheatersutopia.com & www.nixcoders.org

#include "../eth32.h"

CRadarWindow::CRadarWindow(char *wlabel, int wx, int wy, int ww, int wh)
: CWindow(wlabel, wx, wy, ww, ww) // set width and height to ww to keep it square
{
	showTitle = false;

	numPoints = 0;
	memset(points, 0, sizeof(points));

	cx = x + (w >> 1);
	cy = y + (h >> 1);
}

const char *crosshairText[XHAIR_MAX] =
{
	"Off",
	"Sniper",
	"Open Cross",
	"Closed Cross",
	"Dot",
};

const char *crosshairColorText[XHAIR_MAX] =
{
	"White",
	"Green",
	"Red",
	"Yellow",
	"Blue",
};

void CRadarWindow::Display(void)
{
	if (!show || eth32.settings.guiOriginal) return;

	CWindow::Display();

	vec4_t colorTeam, colorEnemy;
	vec3_t pt, my_ang, pt_ang;
	int px, py;
	float delta_ang;
	
	float distFactor = (cx - x - 5)/eth32.settings.radarRange;

	player_t *player;
	
	Vector4Set(colorTeam, eth32.settings.colorTeam[0]/255.f, eth32.settings.colorTeam[1]/255.f, eth32.settings.colorTeam[2]/255.f, 1);
	Vector4Set(colorEnemy, eth32.settings.colorEnemy[0]/255.f, eth32.settings.colorEnemy[1]/255.f, eth32.settings.colorEnemy[2]/255.f, 1);

	Tools.VectorAngles(eth32.cg.refdef->viewaxis[0], my_ang);

	Draw.RawFillRect(cx-2, cy-2, 5, 5, colorWhite);
		Draw.RawFillRect(tx, ty, 2, 15, colorGreen);
	Draw.RawFillRect(ttx, tty, 15, 2, colorGreen);
// Draw.RawFillRect(315.0, 239.5, 10, 1, colorGreen);

/*====================
CUSTOM CROSSHAIR
====================*/	
	int crossSize = eth32.settings.crossSize;
	int crossThick = eth32.settings.crossThick;
	int resWidth = eth32.game.glconfig->vidWidth;
	int resHeight = eth32.game.glconfig->vidHeight;

		//Format:	  //Res Width				//Res Height    		//W		//H		//Color

	if (eth32.settings.customXhair == 0) { }
	else if (eth32.settings.customXhair == 1) {
		//Sniper
		Draw.RawFillRect(((resWidth/2)-crossThick/2),  	     	(resHeight/2), 			crossThick, 	crossSize*1.3,  colorGreen);
		Draw.RawFillRect((((resWidth/2)-crossSize/2)-1), 	((resHeight/2)+crossThick/2), 	crossSize*(-1), crossThick*(-1), colorGreen);
		Draw.RawFillRect((((resWidth/2)+crossSize/2)+1),        ((resHeight/2)-crossThick/2),	crossSize, 	crossThick, 	colorGreen);
	} else if (eth32.settings.customXhair == 2) {
		//Cross Open
		Draw.RawFillRect(((resWidth/2)-crossThick/2), 	 	((resHeight/2)-crossThick/2), 	crossThick, crossThick, colorGreen);
		Draw.RawFillRect(((resWidth/2)-7), 	 		((resHeight/2)+crossThick/2), 	crossSize*(-1), crossThick*(-1), colorGreen);
		Draw.RawFillRect(((resWidth/2)+7),        		((resHeight/2)-crossThick/2),	crossSize, 	crossThick, 	colorGreen);
		Draw.RawFillRect(((resWidth/2)+crossThick/2), 		((resHeight/2)-7), 		crossThick*(-1), crossSize*(-1), colorGreen);
		Draw.RawFillRect(((resWidth/2)-crossThick/2),         	((resHeight/2)+7),		crossThick, 	crossSize, 	colorGreen);
	} else if (eth32.settings.customXhair == 3) {
		//Cross Closed
		Draw.RawFillRect(((resWidth/2)), 	 		((resHeight/2)+crossThick/2), 	crossSize*(-1), crossThick*(-1), colorGreen);
		Draw.RawFillRect(((resWidth/2)),         		((resHeight/2)-crossThick/2),	crossSize, 	crossThick, 	colorGreen);
		Draw.RawFillRect(((resWidth/2)+crossThick/2), 	 	((resHeight/2)), 		crossThick*(-1), crossSize*(-1), colorGreen);
		Draw.RawFillRect(((resWidth/2)-crossThick/2),         	((resHeight/2)),		crossThick, 	crossSize, 	colorGreen);
	} else if (eth32.settings.customXhair == 4) {
		//Dot
		Draw.RawFillRect(((resWidth/2)-((crossSize/5)/2)), 	((resHeight/2)-((crossSize/5)/2)), crossSize/5, crossSize/5, 	colorGreen);
	} else if (eth32.settings.customXhair == 5) {
		//Line
		Draw.RawFillRect(((resWidth/2)-crossThick/2),  	     	(resHeight/2), 			crossThick, 	crossSize*1.3,  colorGreen);
	}

	for (int i=0 ; i<numPoints ; i++) 
	{
		player = points[i];
		
		pt[0] = player->orHead.origin[0] - eth32.cg.refdef->vieworg[0];
		pt[1] = player->orHead.origin[1] - eth32.cg.refdef->vieworg[1];

		Tools.VectorAngles(pt, pt_ang);
		delta_ang = pt_ang[YAW] - my_ang[YAW] + 90.f;

		px = cx + cos(delta_ang * M_PI/180.f) * player->distance * distFactor;
		py = cy - sin(delta_ang * M_PI/180.f) * player->distance * distFactor;

		Draw.RawFillRect(px-2, py-2, 5, 5, (player->friendly) ? colorTeam : colorEnemy);
	}
	numPoints = 0;

	if (Gui.InputActive()) {
		char buf[64];
		sprintf(buf, "%i", (int)eth32.settings.radarRange);
		Draw.Text(x+GUI_SPACING, y2-GUI_FONTHEIGHT-GUI_SPACING, GUI_FONTSCALE, "Range", GUI_FONTCOLOR1, qtrue, qfalse, GUI_FONT, true);
		Draw.Text(x2-GUI_SPACING-TEXTWIDTH(buf), y2-GUI_FONTHEIGHT-GUI_SPACING, GUI_FONTSCALE, buf, GUI_FONTCOLOR2, qtrue, qfalse, GUI_FONT, true);
	}
}

int CRadarWindow::MouseWheel(int mx, int my, int wheel)
{
	if (!show) return 1; // not visible, can't process

	if (INBOUNDS(mx,my)) {
		eth32.settings.radarRange += -wheel * 100.f;

		if (eth32.settings.radarRange > 10000.f)
			eth32.settings.radarRange = 10000.f;
		else if (eth32.settings.radarRange < 100.f)
			eth32.settings.radarRange = 100.f;

		return 0;
	}
	return 1;
}

void CRadarWindow::SetOrigin(int ox, int oy)
{
	CControl::SetOrigin(ox, oy);

	cx = x + (w >> 1);
	cy = y + (h >> 1);
}

void CRadarWindow::Reposition(int ox, int oy)
{
	CWindow::Reposition(ox, oy);

	cx = x + (w >> 1);
	cy = y + (h >> 1);
}

void CRadarWindow::AddPlayer(player_t *player)
{
	if (numPoints < MAX_CLIENTS && player->distance < eth32.settings.radarRange) {
		points[numPoints] = player;
		numPoints++;
	}
}
