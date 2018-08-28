#include <SFML/Graphics.hpp>
#include <bits/stdc++.h>

using namespace sf;
using namespace std;

int N = 50, M = 50;         //window koto boro, bit size koto oi hishab
int size = 16;
int w = size*N;
int h = size*M;

int dir, num = 4;

int counte = 0;

struct Snake                            //mathematically saaper lomba gaa
{
	int x, y;
}  s[1000];

struct Fruit                            //saaper khana-pina er hishab
{
	int x, y;
} f;

int game_over()
{
    RenderWindow window(VideoMode(800,800),"Snake Game!");
    Texture texture;
    texture.loadFromFile("over.png");
    Sprite sprite(texture);

    return 0;
}

void Tick()
{
	for (int i = num; i>0; --i)         //mathematically pura saaper sorir tare aganor laiga
	{
		s[i].x = s[i - 1].x;
		s[i].y = s[i - 1].y;
	}

	if (dir == 0)
		s[0].y += 1;                                    // ei  4 ta if dia control onushare saap agaibo
	if (dir == 1)
		s[0].x -= 1;
	if (dir == 2)
		s[0].x += 1;
	if (dir == 3)
		s[0].y -= 1;

	if ((s[0].x == f.x) && (s[0].y == f.y))         //saap khabar khaise naki oita check korar jonno
	{
		num++;
		counte++;
		f.x = rand() % N;                              // khana khawar por notun random khana banano
		f.y = rand() % M;
	}

	if (s[0].x>=N)
		s[0].x = 0;
	if (s[0].x<0)
		s[0].x = N;
	if (s[0].y>=M)
		s[0].y = 0;
	if (s[0].y<0)
		s[0].y = M;

	for (int i = 1; i < num; i++){                  //saap nijer gaaye nije kamor khaise naki oita check korar jonno
		if (s[0].x == s[i].x && s[0].y == s[i].y){
			//game_over();
		}
	}
}

int game()
{
	srand(time(0));

	RenderWindow window(VideoMode(w, h), "Snake Game!");            //main window of game
    window.setFramerateLimit(30);
	Texture t1, t2, t3;                                             //texture
	t1.loadFromFile("images/white.png");
	t2.loadFromFile("images/red.png");
    t3.loadFromFile("images/green.png");

	Sprite sprite1(t1);                                             //sprite setting
	Sprite sprite2(t2);
	Sprite sprite3(t3);



	Clock clock;                                                     // timing thik rakhar leiga clock init
	float timer = 0, delay = 0.12;

	f.x = 10;                                                          // 1st khanar position
	f.y = 10;

	while (window.isOpen())
	{
		float time = clock.getElapsedTime().asSeconds();                 //time protibar agaitasi
		clock.restart();
		timer += time;

		Event e;
		while (window.pollEvent(e))
		{
			if (e.type == Event::Closed)
				window.close();
		}

		if (Keyboard::isKeyPressed(Keyboard::Left) && (dir!=2))             //keyboard controlling
			dir = 1;
		if (Keyboard::isKeyPressed(Keyboard::Right) && (dir!=1))
			dir = 2;
		if (Keyboard::isKeyPressed(Keyboard::Up) && (dir!=0))
			dir = 3;
		if (Keyboard::isKeyPressed(Keyboard::Down) && (dir!=3))
			dir = 0;

		if (timer>delay)                                                       // 0.1 second por por saaper position agano
		{
			timer = 0;
			Tick();
		}

		string title=to_string(counte);
        window.setTitle(title);

		window.clear();                                                        // ehon khali window te aka-aki

		for (int i = 0; i<N; i++)                                              //saap jeihan dia jaibo, oihaner block akano
			for (int j = 0; j<M; j++)
			{
				sprite1.setPosition(i*size, j*size);
				window.draw(sprite1);
			}

		for (int i = 0; i<num; i++)                                             //saaper body akano
		{
			sprite2.setPosition(s[i].x*size, s[i].y*size);
			window.draw(sprite2);
		}

		sprite3.setPosition(f.x*size, f.y*size);                                //saaper khana-pina akano
		window.draw(sprite3);

		window.display();                                                       // sob aikka dehano
	}

	return 0;                                                                   // hoga mara sesh
}
