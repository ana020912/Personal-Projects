#ifndef GRAFICA_H_INCLUDED
#define GRAFICA_H_INCLUDED
#include <iostream>
#include <graphics.h>
#include <winbgim.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>

bool interiorButon(int x,int y, int x1,int y1,int x2, int y2)
{
    return x1<=x&&x<=x2&&y1<=y&&y<=y2;
}
void Desenare_Buton_Grafic_Functie()
{
readimagefile("Buton.jpg",400,300,600,400);

settextstyle(3,0,4);
outtextxy(425,330,"GRAFIC");

}

void Butonul_Grafic()
{

}
void Desenare_Buton_Despre()
{
readimagefile("Buton.jpg",400,500,600,600);
/*
line(400,600,600,600);
line(400,500,600,500);
line(400,600,400,500);
line(600,600,600,500);
*/
setcolor(WHITE);
settextstyle(3,0,4);
outtextxy(420,530,"DESPRE");

}

void Desenare_Buton_Iesire()
{
readimagefile("Buton.jpg",400,700,600,800);
/*
line(400,800,600,800);
line(400,700,600,700);
line(400,800,400,700);
line(600,800,600,700);
*/

settextstyle(3,0,4);
outtextxy(455,735,"EXIT");
}
void Foaie_de_mate()
{
    int i;
    setbkcolor(WHITE);
    clearviewport();
    for(i=0;i<=1000;i=i+50)
    {
     setcolor(BLUE);
     line(0,i,1000,i);
     line(i,0,i,1000);
    }
}
void Desenare_Axe()
{


    initwindow(1000,1000);

{
    Foaie_de_mate();

    setcolor(YELLOW);
    outtextxy(900,550,"X");

    setlinestyle(SOLID_LINE,NORM_WIDTH,5);

    line(500,0,500,1000);
    line(0,500,1000,500);

    line(500,0,470,100);
    line(500,0,530,100);

    line(1000,500,940,450);
    line(1000,500,940,550);

        getch();
        closegraph();
}

void Butoane_Meniu()
{
    int x,y;
    do{
        x=mousex();
        y=mousey();
        if(ismouseclick(WM_LBUTTONDOWN)&& interiorButon(x,y,400,300,600,400))
        {
            clearmouseclick(WM_LBUTTONDOWN);
             Desenare_Axe();
        }
        else
            if(ismouseclick(WM_LBUTTONDOWN)&&interiorButon(x,y,400,500,600,600))
        {
            clearmouseclick(WM_LBUTTONDOWN);
        }
        else
            if(ismouseclick(WM_LBUTTONDOWN)&&interiorButon(x,y,400,700,600,800))
        {
            clearmouseclick(WM_LBUTTONDOWN);
            exit(0);
        }
        clearmouseclick(WM_LBUTTONDOWN);
    Sleep(3);
    }while(true);
}
void Meniu()
{
initwindow(1000,1000);

settextstyle(3,0,5);
outtextxy(237,140,"GRAFICUL UNEI FUNCTII");

Desenare_Buton_Grafic_Functie();
Desenare_Buton_Despre();
Desenare_Buton_Iesire();
Butoane_Meniu();
 getch();
 closegraph();

}

/*
void Reprezinta_Grafic_Functia(Functie E,int x1,int x2,int y1,int y2)
{
    int x0,y0;
    int xe,ye,i;
    int xev,yev,aux;
    float x,y;
    double ymin,ymax;
    rectangle(x1,y1,x2,y2);
    ymin=calcul_functie(E.a,E);
    ymax=ymin;
    for(i=0;i<=x2-x1;i++)
    {
        x=E.a+i*(E.b-E.a)/(x2-x1);//punctul in care ne aflam
        y=calcul_functie(x,E);//valoare punctului in care ne aflam
        //actualizare pentru ymax respectiv ymin
        if(y>ymax)
            ymax=y;
        if(y<ymin)
            ymin=y;
    }
    x0=round((E.b*x1-E.a*x2)/(E.b-E.a));//se determina originea lui x;
    if(E.a<=0 && 0<=E.b)//se va trasa yy' daca x0 este in intervalul [a,b]
        line(x0,y2,x0,y1);

    y0=round((ymax*y1-ymin*y2)/(ymax-ymin));
    if(ymin<=0&&0<=ymax)
        line(x1,y0,x2,y0);

     x=E.a;
     y=calcul_functie(E.a,E);
    xev=round((x2-x1)*x/(E.b-E.a)+(E.b*x1-E.a*x2)/(E.b-E.a));
    yev=round((y2-y1)*y/(ymax-ymin)+(ymax*y1-ymin*y2)/(ymax-ymin));

    for(i=0;i<=x2-x1;i++)
    {
        x=E.a+i*(E.b-E.a)/(x2-x1);//stabilirea a (x2-x1+1) puncte curente x
        xe=round((x2-x1)*x/(E.b-E.a)+(E.b*x1-E.a*x2)/(E.b-E.a)); //transformarea lui x in x ecran
        y=(E.a);
        ye=round((y2-y1)*y/(ymax-ymin)+(ymax*y1-ymin*y2)/(ymax-ymin));
        line(xev,yev,xe,ye);
        xev=xe;yev=ye;
    }

}
*/



#endif // GRAFICA_H_INCLUDED
