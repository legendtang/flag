/**************************************************************
** ³ÌÐòÃû³Æ£ºÄ£ÄâÊµÏÖ
** ³ÌÐò¹¦ÄÜ£ºÍ¼ÏñÄ£Ê½£¨¢
** ±àÒë»·¾³£ºVC++2010 EGE 13.03
** ×÷ÕßÐÅÏ¢£ºLegend <legendt@outlook.com> 
** ×îºóÐÞ¸Ä£º2013-04-04
**************************************************************/
//#include <graphics.h>
//#include <ege/fps.h>
//#include <stdio.h>
//#include <time.h>
//
//int main(void)
//{
//	char Line[162];
//	FILE *fp;
//	int loop;
//
//
//	/*³õÊ¼»¯*/
//	initgraph(960, 720, ege::INIT_ANIMATION);
//	setbkcolor(EGERGB(0xF5, 0xF5, 0xDC));
//
//
//	/*´ò¿ªÎÄ¼þ*/
//	if((fp = fopen("AscPic.txt", "r")) == NULL)
//	{
//		outtextxy(0, 0, "ÎÄ¼þ´ò¿ªÊ§°Ü");
//		Sleep(2000);
//		exit(EXIT_FAILURE);
//	}
//
//	/*Ìí¼ÓÒôÀÖ*/
//	mciSendString(L"open BadApple.mp3 alias BadApple", NULL, 0, NULL);
//	mciSendString(L"play BadApple", NULL, 0, NULL);
//
//
//	/*¶¯»­ÑÝÊ¾*/
//	fps f;
//	setcolor(EGERGB(0xFF, 0x0, 0x0));
//    for ( ; !feof(fp) && is_run(); delay_fps(30))
//	{
//
//		for(loop = 0; loop < 61; loop++)
//		{
//			if(fgets(Line, 162, fp) == NULL)
//				break;
//			setcolor(EGERGB(0x0, 0x0, 0x0));
//			outtextxy(0, loop * 12, Line);
//		}
//
//	}
//
//
//	/*ÉÆºó´¦Àí*/
//	fclose(fp);
//	closegraph();
//
//	return 0;
//}

#include <graphics.h>
#include <ege/fps.h>
#include <stdio.h>
#include <time.h>
#define HEIGHT 205
#define RANGE 80

//¶¨ÒåÒ»¸öAniObj£¬¼´»÷´ò¹Äµã£¬Ïà¹ØÊôÐÔÐ´ÔÚÕâ¸ö½á¹¹ÌåÀï
struct AniObj
{
	int x;
	int dx;
	int tktype;
	PIMAGE img;
};

//³õÊ¼»¯£¬ÉèÖÃ×ø±ê£¬ËÙ¶È·½Ïò£¬´´½¨IMAGEµÈ
void initobj(AniObj* obj)
{
	// random(n) ·µ»ØÒ»¸ö 0 µ½ n Ö®¼äµÄËæ»úÕûÊý(unsigned)
	obj->x = 800;
	obj->dx = - 10; // Éú³É-1»ò1
	obj->tktype = 1;
}

void initBk() {
	PIMAGE img = newimage(800, 600);
	getimage(img, "badapple.jpg", 0, 0);
	putimage(0, 0, img);
	delimage(img);
}

//¸ù¾ÝÊôÐÔÖµ»æ»­
void drawobj(AniObj* obj)
{
	if (obj->tktype)
	{
		obj->img = newimage(RANGE, RANGE);
		getimage(obj->img, "dong.png", 0, 0);
		putimage_transparent(NULL,obj->img,obj->x,205,BLACK);
		//delimage(obj->img);
	}
	if (!obj->tktype)
	{
		obj->img = newimage(RANGE, RANGE);
		getimage(obj->img, "ka.png", 0, 0);
		putimage_transparent(NULL,obj->img,obj->x,205,BLACK);
		//delimage(obj->img);
	}
}


//ÊÍ·ÅÕâ¸ö¶ÔÏóÊ±µ÷ÓÃ
void releaseobj(AniObj* obj)
{
	delimage(obj->img);
}

//¸üÐÂÎ»ÖÃµÈÏà¹ØÊôÐÔ
void updateobj(AniObj* obj)
{
	// µ±Ç°Î»ÖÃ + ËÙ¶È
	obj->x += obj->dx;
	//if (obj->x <= 160) delimage(obj->img); //Åö×ó
}

void mainloop()
{
	const int MAXOBJ = 15;
	AniObj obj[MAXOBJ]; //¶¨Òå¶ÔÏóÊý×é
	int n;
	for (n = 0; n < MAXOBJ; ++n)
	{
		initobj(&obj[n]); //³õÊ¼»¯
	}

	for ( ; is_run(); delay_fps(60) )
	{
		initBk();
		for (n = 0; n < MAXOBJ; ++n)
		{
			drawobj(&obj[n]); //»æ»­
		}
		
		for (n = 0; n < MAXOBJ; ++n, delay_fps(60))
		{
			updateobj(&obj[n]); //¸üÐÂÎ»ÖÃ
			if (obj->x <= 160)
			{
				cleardevice();
				initBk();
			}
		}
		for (n = 0; n < MAXOBJ; ++n)
		{
			releaseobj(&obj[n]); //release
		}
	}
}

void playBgm() {
	mciSendString(L"open BadApple.mp3 alias BadApple", NULL, 0, NULL);
	mciSendString(L"play BadApple", NULL, 0, NULL);
}

int main() {
	
	//setinitmode(INIT_WITHLOGO); 
	initgraph(800, 600);
	playBgm();
	fps f;
	mainloop();
	//hit();
	//¶Ôimg»­ÊµÐÄ¾ØÐÎ
	//bar(40, 20, 70, 50, img);
	//int x, y;
	//°ÑimgÆ½ÆÌÔÚÆÁÄ»ÉÏ£¬Ê¹ÓÃÒ»¸ö¶þÖØÑ­»·
	//getkey();
	closegraph();
	return 0;

}



//void hit() {
//	key_msg k;
//	HITC.x = 50;
//	HITC.y = 50;
//	//HITC.img = newimage();
//	setcolor(LIGHTGRAY);
//	setfillcolor(LIGHTGRAY);
//	fillellipse(HITC.x, HITC.y, RANGE, RANGE);
//	setfillcolor(LIGHTBLUE);
//	fillellipse(HITC.x, HITC.y, RANGE-4, RANGE-4);
//	setcolor(WHITE);
//	setfont(-50, 0,"Aria");
//	setfontbkcolor(LIGHTBLUE);
//	outtextxy(HITC.x-12, HITC.y-25,"1");
//	setcolor(LIGHTGRAY);
//}