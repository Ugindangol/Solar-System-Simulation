#include<graphics.h>
#include<conio.h>
#include<math.h>
#include<stdlib.h>
#include<dos.h>
#include<stdio.h>

int sx[120], sy[120];

void initStars(int maxx, int maxy)
{
    for(int i=0;i<120;i++)
    {
        sx[i] = rand()%maxx;
        sy[i] = rand()%maxy;
    }
}

void drawStars()
{
    for(int i=0;i<120;i++)
    {
        int color = rand()%2 ? WHITE : DARKGRAY;
        putpixel(sx[i], sy[i], color);
    }
}

int main()
{
    int gd=DETECT, gm;
    initgraph(&gd,&gm,"");

    int maxx = getmaxx();
    int maxy = getmaxy();

    int xc = maxx/2;
    int yc = maxy/2;

    int r1=50, r2=75, r3=110, r4=140, r5=180, r6=210, r7=240, r8=260;

    float m=0,v=0,e=0,ma=0,j=0,s=0,u=0,n=0,moon=0;

    float sm=0.10, sv=0.07, se=0.05, sma=0.03;
    float sj=0.01, ss=0.008, su=0.005, sn=0.003;

    float speedFactor = 1.0;

    int page = 0;
    int shootx=0, shooty=50;

    initStars(maxx, maxy);

    while(1)
    {
        setactivepage(page);
        cleardevice();

        setcolor(WHITE);
        outtextxy(10,10,"SOLAR SYSTEM SIMULATION");
        outtextxy(10,25,"+ / - : Speed Control | ESC : Exit");

        char speedText[50];
        sprintf(speedText,"Speed: %.0fx",speedFactor);
        outtextxy(10,40,speedText);

        drawStars();

        // Shooting Star
        shootx += 10;
        shooty += 3;
        if(shootx > maxx)
        {
            shootx = 0;
            shooty = rand()%200;
        }
        line(shootx, shooty, shootx+15, shooty+5);

        // SUN
        setcolor(YELLOW);
        setfillstyle(SOLID_FILL,YELLOW);
        fillellipse(xc,yc,30,30);

        setcolor(LIGHTRED);
        circle(xc,yc,40);
        circle(xc,yc,45);
        circle(xc,yc,50);

        outtextxy(xc-15,yc+50,"SUN");

        // ORBITS
        setcolor(DARKGRAY);
        ellipse(xc,yc,0,360,r1,r1-10);
        ellipse(xc,yc,0,360,r2,r2-15);
        ellipse(xc,yc,0,360,r3,r3-20);
        ellipse(xc,yc,0,360,r4,r4-25);
        ellipse(xc,yc,0,360,r5,r5-30);
        ellipse(xc,yc,0,360,r6,r6-35);
        ellipse(xc,yc,0,360,r7,r7-40);
        ellipse(xc,yc,0,360,r8,r8-45);

        // Mercury
        int mx=xc+r1*cos(m);
        int my=yc+(r1-10)*sin(m);
        setcolor(LIGHTGRAY);
        fillellipse(mx,my,3,3);
        outtextxy(mx+5,my,"Mercury");

        // Venus
        int vx=xc+r2*cos(v);
        int vy=yc+(r2-15)*sin(v);
        setcolor(LIGHTMAGENTA);
        fillellipse(vx,vy,5,5);
        outtextxy(vx+5,vy,"Venus");

        // Earth
        int ex=xc+r3*cos(e);
        int ey=yc+(r3-20)*sin(e);
        setcolor(BLUE);
        fillellipse(ex,ey,6,6);
        outtextxy(ex+5,ey,"Earth");

        setcolor(WHITE);
        line(ex-4*cos(e), ey-4*sin(e), ex+4*cos(e), ey+4*sin(e));

        int moonx=ex+15*cos(moon);
        int moony=ey+15*sin(moon);
        fillellipse(moonx,moony,2,2);

        // Mars
        int marsx=xc+r4*cos(ma);
        int marsy=yc+(r4-25)*sin(ma);
        setcolor(RED);
        fillellipse(marsx,marsy,4,4);
        outtextxy(marsx+5,marsy,"Mars");

        // Jupiter
        int jx=xc+r5*cos(j);
        int jy=yc+(r5-30)*sin(j);
        setcolor(BROWN);
        fillellipse(jx,jy,10,10);
        outtextxy(jx+5,jy,"Jupiter");

        // Saturn
        int sx1=xc+r6*cos(s);
        int sy1=yc+(r6-35)*sin(s);
        setcolor(YELLOW);
        fillellipse(sx1,sy1,9,9);
        ellipse(sx1,sy1,30,210,15,5);
        ellipse(sx1,sy1,30,210,17,7);
        outtextxy(sx1+5,sy1,"Saturn");

        // Uranus
        int ux=xc+r7*cos(u);
        int uy=yc+(r7-40)*sin(u);
        setcolor(LIGHTCYAN);
        fillellipse(ux,uy,7,7);
        outtextxy(ux-25,uy,"Uranus");

        // Neptune
        int nx=xc+r8*cos(n);
        int ny=yc+(r8-45)*sin(n);
        setcolor(CYAN);
        fillellipse(nx,ny,7,7);
        outtextxy(nx-30,ny,"Neptune");

        // Motion
        m += sm * speedFactor;
        v += sv * speedFactor;
        e += se * speedFactor;
        ma += sma * speedFactor;
        j += sj * speedFactor;
        s += ss * speedFactor;
        u += su * speedFactor;
        n += sn * speedFactor;
        moon += 0.2 * speedFactor;

        // FIXED CONTROLS
        if(kbhit())
        {
            char ch = getch();

            if(ch=='+' || ch=='=')
            {
                speedFactor += 1.0;
            }
            else if(ch=='-')
            {
                speedFactor -= 1.0;
                if(speedFactor < 1.0)
                    speedFactor = 1.0; // prevent zero/negative
            }
            else if(ch==27)
            {
                break;
            }
        }

        setvisualpage(page);
        page = 1 - page;

        delay(40);
    }

    closegraph();
    return 0;
}
