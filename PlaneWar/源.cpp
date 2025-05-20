#include<iostream>
#include<graphics.h>
using namespace std;

constexpr auto swidth = 600;
constexpr auto sheight = 1100;
bool PointInRect(int x, int y, RECT& r)
{
	return(r.left <= x && x <= r.right && r.top <= y && y <= r.bottom);
}
//��ʼ����
void Welcome()
{
	
	LPCTSTR title = _T("�ɻ���ս");
	LPCTSTR textPlay = _T("��ʼ��Ϸ");
	LPCTSTR textExit = _T("�˳���Ϸ");

	RECT textPlayR, textExitR;
	BeginBatchDraw();

	setbkcolor(WHITE);
	cleardevice();
	settextstyle(50, 0, _T("����"));
	settextcolor(BLACK);
	outtextxy(swidth / 2 - textwidth(title) / 2, sheight / 10, title);
	settextstyle(30, 0, _T("����"));
	textPlayR.left = swidth / 2 - textwidth(textPlay) / 2;
	textPlayR.right = textPlayR.left + textwidth(textPlay);
	textPlayR.top = sheight / 3;
	textPlayR.bottom = textPlayR.top + textheight(textPlay);
	outtextxy(textPlayR.left, textPlayR.top, textPlay);
	textExitR.left = swidth / 2 - textwidth(textExit) / 2;
	textExitR.right = textExitR.left + textwidth(textExit);
	textExitR.top = (sheight / 3)+100;
	textExitR.bottom = textExitR.top + textheight(textExit);
	outtextxy(textExitR.left, textExitR.top, textExit);
	
	EndBatchDraw();
	while (true)
	{
		ExMessage mess;
		getmessage(&mess, EX_MOUSE);
		if (mess.lbutton)
		{
			if (PointInRect(mess.x, mess.y, textPlayR))
			{
				return;
			}
			else if (PointInRect(mess.x, mess.y, textExitR))
			{
				exit(0);
			}
		}

	}

}

//���� �л� Ӣ�� �ӵ�
class BK
{
public:
	BK(IMAGE& img)
		:img(img),y(-sheight)
	{
	}

	void Show()
	{
		if (y == 0) { y = -sheight; }
		y += 1;
		putimage(0, y, &img);


	}
private:
	IMAGE& img;
	int y;




};
class HERO
{
public:
	HERO(IMAGE& img)
		:img(img)
	{
		rect.left = swidth / 2 - img.getwidth() / 2;
		rect.right = swidth + img.getwidth();
		rect.top = sheight - img.getheight();
		rect.bottom = sheight;
	}
	void Show()
	{
		putimage(rect.left, rect.bottom, &img);
	}
	void Control()
	{
		ExMessage mess;
		while (peekmessage(&mess, EX_KEY))
		{
			if (mess.message == WM_KEYDOWN)
			{
				switch (mess.vkcode)
				{
				case VK_LEFT:
					rect.left -= 5;
					rect.right -= 5;
					break;
				case VK_RIGHT:
					rect.left += 5;
					rect.right += 5;
					break;
				}
			}
			if (rect.left < 0) {
				rect.left = 0;
				rect.right =img.getwidth();
			}
			if (rect.right > swidth) {
				rect.left = swidth-img.getwidth();
				rect.right = swidth;
			}
			
		}
	}
private:
	IMAGE img;
	RECT rect;

};
bool Play()
{
	setbkcolor(WHITE);
	cleardevice();
	bool is_play = true;

	IMAGE heroimg, enemyimg, bulletimg, bkimg;
	loadimage(&heroimg, _T("C:\\Users\\YEUWEN\\source\\repos\\PlaneWar\\images\\me2.png"));
	loadimage(&enemyimg, _T("C:\\Users\\YEUWEN\\source\\repos\\PlaneWar\\images\\enemy1.png"));
	loadimage(&bkimg, _T("C:\\Users\\YEUWEN\\source\\repos\\PlaneWar\\images\\bk2.png"),600,sheight*2,true);
	loadimage(&bulletimg, _T("C:\\Users\\YEUWEN\\source\\repos\\PlaneWar\\images\\bullet1.png"));

	BK bk = BK(bkimg);
	HERO hp = HERO(heroimg);

	MSG mess;


	while (is_play)
	{
		BeginBatchDraw;
		bk.Show();
		hp.Control();
		hp.Show();
		
		while (PeekMessage(&mess, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&mess);
			DispatchMessage(&mess);
		}


		
		
		//Sleep(2);
		EndBatchDraw();
	}


	return true;
}

int main()
{
	//easyx��ʼ��
	initgraph(swidth, sheight, EX_NOMINIMIZE| EX_SHOWCONSOLE);
	bool is_live = true;
	while (is_live)
	{
		Welcome();
		//Play
		is_live = Play();
	}


	return 0;
}
