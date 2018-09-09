#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <bits/stdc++.h>
using namespace std;
using namespace sf;

int menu()
{
    RenderWindow window(VideoMode(800,800),"Snake Game!" , Style::Titlebar | Style::Close);
    window.setFramerateLimit(8);
    window.setVerticalSyncEnabled(true);

    string str;
    FILE *fp;
    fp=fopen("images/scr.bin","r");
    if(fp==NULL)
    {
        str="You Have NOT \nPlayed Yet!";
    }
    else{
        int a;
        fscanf(fp,"%d", &a);
        str="\tYour \nHighest Score \n\tis : ";
        str.append(to_string(a));
    }
    int x=0,n=0,i=1;
    Texture t1, t2, t3, t4, t5, t6, t7;
    t1.loadFromFile("images/menu.png");
    t2.loadFromFile("images/ng.png");
    t3.loadFromFile("images/obj.png");
    t4.loadFromFile("images/hs.png");
    t5.loadFromFile("images/abt.png");
    t6.loadFromFile("images/objective.png");
    t7.loadFromFile("images/about.png");

    Sprite sMenu(t1), sNg(t2), sObj(t3), sHs(t4), sAbt(t5), sObjective(t6), sAbout(t7);

    SoundBuffer buff;
    buff.loadFromFile("audios/bg.ogg");
    Sound sound(buff);
    sound.setLoop(true);
    sound.setVolume(20);

    Text text;
    Font font;
    font.loadFromFile("images/tscope.ttf");
    text.setFont(font);
    text.setFillColor(Color::Black);
    text.setStyle(Text::Bold);
    text.setCharacterSize(54);
    text.setPosition(400,100);
    text.setString(str);

    while(window.isOpen())
    {
        Event e;
        while(window.pollEvent(e))
        {
            if(e.type == Event::Closed)
                window.close();
        }

        auto var = Mouse::getPosition(window);

        if((var.x > 67 && var.x < 311) && (var.y > 100 && var.y < 200)) x=1;
        if((var.x > 67 && var.x < 311) && (var.y > 220 && var.y < 320)) x=2;
        if((var.x > 67 && var.x < 311) && (var.y > 342 && var.y < 444)) x=3;
        if((var.x > 67 && var.x < 311) && (var.y > 462 && var.y < 560)) x=4;

        if(n==0) sound.play();
        n++;

        if(Keyboard::isKeyPressed(Keyboard::Up))
        {
            x--;
        }

        if(Keyboard::isKeyPressed(Keyboard::Down))
        {
            x++;
        }

        if(x==1 && (Keyboard::isKeyPressed(Keyboard::Enter) || Mouse::isButtonPressed(Mouse::Left)) && i<2) return 1;
        if(x==2 && (Keyboard::isKeyPressed(Keyboard::Enter) || Mouse::isButtonPressed(Mouse::Left)) && (i<2))
        {
            i=2;
        }
        if(x==3 && (Keyboard::isKeyPressed(Keyboard::Enter) || Mouse::isButtonPressed(Mouse::Left)) && (i<2))
        {
            i=3;
        }
        if(x==4 && (Keyboard::isKeyPressed(Keyboard::Enter) || Mouse::isButtonPressed(Mouse::Left)) && (i<2))
        {
            i=4;
        }

        if(x>4)
            x=1;
        if(x<0)
            x=4;

       if(i<2)
       {
            if(x==0) window.draw(sMenu);
            if(x==1) window.draw(sNg);
            if(x==2) window.draw(sObj);
            if(x==3) window.draw(sHs);
            if(x==4) window.draw(sAbt);
       }
       else{
        if(x==2 && i==2) window.draw(sObjective);
        if(Keyboard::isKeyPressed(Keyboard::Escape)) i=0;
        if(x==3 && i==3) window.draw(text);
        if(x==4 && i==4) window.draw(sAbout);
       }
        window.display();
    }
    return 0;
}
