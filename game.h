#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <bits/stdc++.h>
#include "wall.h"

using namespace sf;
using namespace std;


int N = 50, M = 50, size = 16, w = size*N, h = size*M, over=0, lvl=1, dir=2, num = 4, counte = 0, tle=0, inx=0;      //window koto boro, bit size koto oi hishab

struct Snake                            //mathematically saaper lomba gaa
{
    int x, y;
}  s[2000];

struct Fruit                            //saaper khana-pina er hishab
{
    int x, y;
} f;


struct BonusFruit
{
    int x,y;
} bf;

int PreviousScore()
{
    int x;
    FILE *fp;
    fp=fopen("images/scr.bin","r");
    if(fp==NULL)
    {
        x=-5;
    }
    else
    {
        fscanf(fp,"%d", &x);
        fclose(fp);
    }

    return x;
}

void SaveScore(int x)
{
    FILE *fp;
    fp=fopen("images/scr.bin", "w");
    fprintf(fp,"%d",x);
    fclose(fp);
}

void setdir(int x)
{
     if (dir == 0)
        s[0].y++;                                    // ei  4 ta if dia control onushare saap agaibo
    if (dir == 1)
        s[0].x--;
    if (dir == 2)
        s[0].x++;
    if (dir == 3)
        s[0].y--;
}

int game()
{
    srand(time(0));

    RenderWindow window(VideoMode(w, h), "Snake Game!", Style::Titlebar | Style::Close);            //main window of game
    window.setFramerateLimit(30);
    window.setVerticalSyncEnabled(true);

    int svscr = PreviousScore();
    Texture t1, t2, t3, t4, t5, t6, t7;                                             //texture
    t1.loadFromFile("images/white.png");
    t2.loadFromFile("images/bd.png");
    t3.loadFromFile("images/fd.png");
    t4.loadFromFile("images/over.png");
    t5.loadFromFile("images/bon.png");
    t6.loadFromFile("images/head.png");
    t7.loadFromFile("images/wall.png");

    Sprite sprite1(t1), sprite2(t2), sprite3(t3), sOver(t4), sBon(t5), spriteH(t6), sWall(t7);                      //sprite setting

    SoundBuffer buf1, buf2, buf3, buf4, buf5, buf6;
    buf1.loadFromFile("audios/eat.ogg");
    buf2.loadFromFile("audios/bonus.ogg");
    buf3.loadFromFile("audios/be.ogg");
    buf4.loadFromFile("audios/die.wav");
    buf5.loadFromFile("audios/bg.ogg");
    buf6.loadFromFile("audios/Game_Over.ogg");

    Sound EatSound(buf1), BonusSound(buf2), EatBonSound(buf3), DieSound(buf4), Bg(buf5), GOver(buf6);
    BonusSound.setVolume(30);
    Bg.setLoop(true);
    Bg.setVolume(50);
    GOver.setLoop(true);

    Text text;
    Font font;
    font.loadFromFile("images/tscope.ttf");
    text.setFont(font);
    text.setFillColor(Color::Black);
    text.setStyle(Text::Bold);
    text.setCharacterSize(54);
    text.setPosition(50,100);
    int in=1;
    if(in==1)
    {
        Bg.play();
        in++;
    }

    Clock clock;                                                     // timing thik rakhar leiga clock init
    float timer = 0, delay = 0.1;

    f.x = 10;                                                          // 1st khanar position
    f.y = 13;

    wall();
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

        if (Keyboard::isKeyPressed(Keyboard::Left) && (dir!=2) && (timer<0.09))             //keyboard controlling
            setdir(1);
        if (Keyboard::isKeyPressed(Keyboard::Right) && (dir!=1) && (timer<0.09))
            setdir(2);
        if (Keyboard::isKeyPressed(Keyboard::Up) && (dir!=0) && (timer<0.09))
            setdir(3);
        if (Keyboard::isKeyPressed(Keyboard::Down) && (dir!=3) && (timer<0.09))
            setdir(0);

        if(Keyboard::isKeyPressed(Keyboard::P))
        {
            while(1)
            {
                if(Keyboard::isKeyPressed(Keyboard::C))
                    goto out;
            }
        }

out:

        if (timer>delay)                                                       // 0.1 second por por saaper position agano
        {
            timer = 0;
            for (int i = num; i >= 1; --i)         //mathematically pura saaper sorir tare aganor laiga
            {
                s[i].x = s[i - 1].x;
                s[i].y = s[i - 1].y;
            }



            if ((s[0].x == f.x) && (s[0].y == f.y))         //saap khabar khaise naki oita check korar jonno
            {
                EatSound.play();
                num++;
                tle=0;
                counte = counte+10;
a:
                f.x = rand_r() % N;                                   // khana khawar por notun random khana banano
                f.y = rand_r() % M;

                for(int i=0; i<108; i++)
                {
                    if(wl[i].x == f.x && wl[i].y == f.y)
                        goto a;

                    if(i>=7 && i<=41 && i == f.x && 25 == f.y )
                        goto a;
                }
            }

            if(tle<50)
                if ((s[0].x == bf.x) && (s[0].y == bf.y))         //saap bonus khabar khaise naki oita check korar jonno
                {
                    EatBonSound.play();
                    tle=9999;
                    counte = counte+100;
                }

            if(num%7==0)
            {
                if(tle==0)
                {
b:
                    BonusSound.play();
                    bf.x = rand_r() % N;
                    bf.y = rand_r() % M;

                    for(int i=0; i<108; i++)
                    {
                        if(wl[i].x == bf.x && wl[i].y == bf.y)
                            goto b;

                        if(i>=7 && i<=41 && i == bf.x && 25 == bf.y )
                            goto b;
                    }
                }
                tle++;
            }

            if (s[0].x>=N)
                s[0].x = 0;
            if (s[0].x<0)
                s[0].x = N;
            if (s[0].y>=M)
                s[0].y = 0;
            if (s[0].y<0)
                s[0].y = M;

            for (int i = 1; i < num; i++)
            {
                //saap nijer gaaye nije kamor khaise naki oita check korar jonno
                if (s[0].x == s[i].x && s[0].y == s[i].y)
                {
                    if(!over)
                        DieSound.play();
                    over=1;
                }
            }
            for (int i=0; i<108; i++)       // saap wall e bari khaise naki
            {
                if(wl[i].x == s[0].x && wl[i].y == s[0].y)
                {
                    if(!over)
                        DieSound.play();
                    over=1;
                }

                if(i>=7 && i<=41 && i == s[0].x && 25 == s[0].y )
                {
                    if(!over)
                        DieSound.play();
                    over=1;
                }
            }
        }

        string title="Snake Game!!                                                            SCORE : ";
        title.append(to_string(counte));
        window.setTitle(title);

        window.clear();                                                        // ehon khali window te aka-aki
        if(!over)
        {
            for (int i = 0; i<N; i++)                                              //saap jeihan dia jaibo, oihaner block akano
                for (int j = 0; j<M; j++)
                {
                    sprite1.setPosition(i*size, j*size);
                    window.draw(sprite1);
                }

            for (int i = 0; i<num; i++)                                             //saaper body akano
            {
                if(i==0)
                {
                    spriteH.setPosition(s[0].x*size, s[0].y*size);
                    window.draw(spriteH);
                }
                else
                {
                    sprite2.setPosition(s[i].x*size, s[i].y*size);
                    window.draw(sprite2);
                }
            }

            for(int i=0; i<108; i++)
            {
                sWall.setPosition(wl[i].x*size, wl[i].y*size);
                window.draw(sWall);
                if(i>=7 && i<=41)
                    sWall.setPosition( i*size, 25*size );
                window.draw(sWall);
            }

            sprite3.setPosition(f.x*size, f.y*size);                                //saaper khana-pina akano
            window.draw(sprite3);
            sBon.setPosition(bf.x*size, bf.y*size);

            if((tle<50)&&(num%7==0))
                window.draw(sBon);
        }
        else
        {
            if(svscr<=0)
            {
                SaveScore(counte);
            }
            if(counte > svscr)
            {
                string str="You've Gained a New HighScore\n\t\t   ";
                str.append(to_string(counte));
                text.setString(str);
                SaveScore(counte);
            }
            window.draw(sOver);
            window.draw(text);
            Bg.pause();
            if(inx==0)
            {
                GOver.play();
                inx++;
            }

            if(Keyboard::isKeyPressed(Keyboard::Escape))
            {
                tle=0;
                over=0;
                num=4;
                counte=0;
                inx=0;
                s[0].x = 2;
                s[0].y = 24;
                return 1;
            }
        }

        window.display();                                                                   // mara sesh
    }

    return 0;
}

