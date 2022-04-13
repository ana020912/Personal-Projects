#include <iostream>
#include <winbgim.h>
#include<string.h>
#include<math.h>
#include "Functii_elementare.h"
#include "algoritmica.h"
#define Infinit INT_MAX
#define Epsilon 0.00001
#define MAX 101
#define MAX_EXP 300
#define unitate 20
using namespace std;


//////////////////////////////////////////// STRUCTURI /////////////////////////////////////////////////////////


struct Functie
{
    char expresie[MAX_EXP];  // expresia matematica a functiei
    char comp[MAX][MAX]; // componentele functiei (operatori+operanzi)
    int lung; //lungimea expresiei
    int nr_comp; // nr de componente ale functiei
    double a = -20, b = 20; // intervalul de evaluare a functiei
    int nr_puncte; // numarul de puncte de evaluare
    double ymin, ymax;//minimul si maximul functiei
    bool eroare = false;
};

/////////////////ANTETE FUNCTII//////////////////////

void Meniu(int l);
void addSpatii(char sir[], bool &eroare);
void aflareComponente(char s[], char sir[][MAX], int &L);
void ReprezintaGrafic(int l, double a, double b, char sir[][MAX], int L);
void Minimul_Maximul(Functie E, double &ymin, double &ymax);
void Butonul_Grafic(int l);
void Butonul_Calculator(int l);
void Desen_Minim(double a, double b, double ymin, char sir[][MAX], int L, bool eroare);
void Desen_Maxim(double a, double b, double ymin, char sir[][MAX], int L, bool eroare);
void Butoane_Meniu(int l);
bool verificareFunctii (char sir[][MAX], int L, bool &eroare);

///////////////////////////////////////////////////////   GRAFICA   /////////////////////////////////////////////////////////

bool interiorButon(int x,int y, int x1,int y1,int x2, int y2)
{
    return (x1 <= x) && (x <= x2) && (y1 <= y) && (y <= y2);
}

void Butonul_Calculator(int l)
{
    double rezultat;
    Functie E;
    E.nr_comp = 0;
    while(1)
   {
    cin >> E.expresie;
    addSpatii(E.expresie, E.eroare);
    aflareComponente(E.expresie, E.comp, E.nr_comp);
    rezultat = Calculator(E.comp, E.nr_comp);
    if(l == 1)
     cout << "Calculeaza..." << '\n';
    else
     cout << "Calculate..." << '\n';
    delay(2000);
    if(rezultat == Infinit)
     cout << "ERROR" << '\n';
    else
     cout << rezultat << '\n';
    }
}

void Butoane_Grafic(int l, double a, double b, double ymin, double ymax, char sir[][MAX], int L, bool eroare)
{
    settextstyle(3,0,4);
    if(l == 1)
         outtextxy(0, 1000, "INAPOI");

    else
         outtextxy(0, 1000, "BACK");

    readimagefile("Salvare.jpg", 900, 920, 1000, 1000);
    readimagefile("Maxim.jpg", 800, 920, 900, 1000);
    readimagefile("Minim.jpg",700, 920, 800, 1000);
    int x,y;
    do{
        x = mousex();
        y = mousey();
        if(ismouseclick(WM_LBUTTONDOWN) && interiorButon(x, y, 0, 900, 200, 1000))
        {
            clearmouseclick(WM_LBUTTONDOWN);
            Butonul_Grafic(l);
        }
        else
           if(ismouseclick(WM_LBUTTONDOWN) && interiorButon(x, y, 900, 920, 1000, 1000))
        {
            clearmouseclick(WM_LBUTTONDOWN);
            writeimagefile("Grafic.jpg", 0, 0.1000, 1000);
        }
        else
            if(ismouseclick(WM_LBUTTONDOWN) && interiorButon(x, y, 800, 920, 900, 1000))
        {
            clearmouseclick(WM_LBUTTONDOWN);
            Desen_Maxim(a, b, ymax, sir, L, eroare);
        }
        else
            if(ismouseclick(WM_LBUTTONDOWN) && interiorButon(x, y, 700, 920, 800, 1000))
            {
                clearmouseclick(WM_LBUTTONDOWN);
                Desen_Minim(a, b, ymin, sir, L, eroare);
            }

        clearmouseclick(WM_LBUTTONDOWN);
        Sleep(3);
    } while(true);
}
void Numerotare()
{
    char nrx[3], nry[3];
    int numarx, numary;
    setcolor(BLACK);
     //ox x>0
      numarx = 1;
     for (int i = 519; i <= 999; i = i + 20)
     {
         //convertesc din int in char
           itoa(numarx, nrx, 10);
           settextstyle(2, 0, 4);
           outtextxy(i+2, 518, nrx); //ox
           numarx++;
     }

     //ox x<0
      numarx = -1;
      for (int i = 479; i >= 0; i = i - 20)
      {
         itoa(numarx, nrx, 10);
         settextstyle(2, 0, 4);
         outtextxy(i + 2, 518, nrx); //ox
         numarx--;
      }

      //oy y>0
      numary = 1;
      for (int i = 479; i >= 0; i = i - 20)
      {
          itoa(numary, nry, 10);
          settextstyle(2, 0, 4);
          outtextxy(479, i+10, nry);
          numary++;
      }

      //oy y<0
      numary = -1;
      for (int i = 519; i <= 999; i = i + 20)
      {
          itoa(numary, nry, 10);
          settextstyle(2, 0, 4);
          outtextxy(479, i, nry);
          numary--;
      }
}
void Foaie_de_mate()
{
    int i;
    setbkcolor(WHITE);
    clearviewport();
    setlinestyle(SOLID_LINE, THICK_WIDTH, 3);
    for(i = 0; i <= 999; i = i + 20)
    {
     setcolor(LIGHTGREEN);
     line(0, i, 999, i);  //orizontale
     line(i, 0, i, 999);  //verticale
    }
    Numerotare();
}

void Desenare_Axe()
{
    Foaie_de_mate();
    setcolor(RED);
    settextstyle(0, 0, 3);
    outtextxy(915, 545, "X");
    outtextxy(525, 135, "Y");

    setlinestyle(SOLID_LINE,THICK_WIDTH,5);


    line(499, 0, 499, 999); //Oy
    line(0, 499, 999, 499); //Ox



    line(499, 0, 469, 100);
    line(499, 0, 530, 100);

    line(999, 499, 940, 450);
    line(999, 499, 940, 550);
}

void CitesteSir(int x, int y, char mesaj[300], char sir[300])
{

    int p;
    char Enter = 13;
    char BackSpace = 8;
    char Escape = 27;
    char s2[2];
    s2[1]='\0';
    char MultimeDeCaractereAcceptabile[300] = "A0123456789abcdefghijklmnopqrstuvwxyz~!`@#$%+-^&*/\\()_=[],;.?<>:;{} ";
    char S_initial[300];
    char tasta;
    char S_[300];
    char mesaj_[300];
    char sir2[300];
    setbkcolor(GREEN);
    clearviewport();
    readimagefile("Fundal5.jpg", 0, 0, 1000, 1000);
    strcpy(mesaj_, mesaj);strcpy(S_initial,sir);
    settextstyle(3,0,4); setcolor(WHITE);
    settextjustify(0,0); outtextxy(x,y,mesaj_);
    x = x + textwidth(mesaj); strcpy(sir,"");
    strcpy(S_, sir); strcat(S_, "_");
    setcolor(BLACK); outtextxy(x,y,S_);
    s2[0] = tasta; strcat(sir, s2); strcpy(S_, sir); strcat(S_,"_");
    setcolor(WHITE); outtextxy(x, y, S_);

    do {
        tasta = getch();
        if (tasta==0)
            {
                tasta = getch();
            }
        else
            if (strchr(MultimeDeCaractereAcceptabile, tasta))
            {
                // stergem fostul sir
                strcpy(S_, sir); strcat(S_, "_");
                setcolor(GREEN);
                outtextxy(x,y,S_);
                s2[0] = tasta; strcat(sir,s2); strcpy(S_,sir); strcat(S_,"_");
                setcolor(WHITE); outtextxy(x,y,S_);
            }
            if (tasta == BackSpace)
            {
               setcolor(GREEN); outtextxy(x,y,S_); setcolor(WHITE);
               sir[strlen(sir)-1]='\0'; strcpy(S_,sir); strcat(S_, "_") ;
               outtextxy(x,y,S_);
            }

    } while (tasta!=Enter && tasta!=Escape);

    if (tasta == Escape) strcpy(sir,S_initial);
    setcolor(GREEN); outtextxy(x,y,S_); setcolor(WHITE); outtextxy(x,y,sir);

}

void Butonul_Limba(int l)
{
setbkcolor(GREEN);
clearviewport();
readimagefile("Fundal5.jpg", 0, 0, 1000, 1000);
if(l == 1)
    {
    outtextxy(30,60,"Selecteaza limba");
    }
    else
    {
        outtextxy(30,60,"Select the language");
    }
    readimagefile("romania.jpg", 40, 170, 200, 250);
    readimagefile("uk.jpg", 500, 170, 660, 250);
    outtextxy(30, 110, "Romana");
    outtextxy(500, 110, "English");
    int p = 1, x, y;
    do{
        x=mousex();
        y=mousey();
        if(ismouseclick(WM_LBUTTONDOWN) && interiorButon(x, y, 40, 170, 200, 250))
        {
            clearmouseclick(WM_LBUTTONDOWN);
            l = 1;
            Meniu(l);
            Butoane_Meniu(l);
            p = 0;
        }
        if(ismouseclick(WM_LBUTTONDOWN) && interiorButon(x, y, 500, 170, 660, 250))
        {
            clearmouseclick(WM_LBUTTONDOWN);
            l = 2;
            Meniu(l);
            Butoane_Meniu(l);
            p = 0;
        }
        clearmouseclick(WM_LBUTTONDOWN);
        Sleep(3);
    } while(p != 0);

}

//verificarea corectitudinii d.p.d.v sintactic
void verificareFunctii (int l, char sir[][MAX], int L, bool &eroare, double a)
{
    double y;
    y = calculFunctie(a, sir, L, eroare);
    if (eroare == true)
    {
         if(l == 1)
        {
            showerrorbox("Functia a fost introdusa incorect!");
        }
        else
        {
            showerrorbox("The function was inserted incorectly!");
        }
        Butonul_Grafic(l);
        return;
    }
    char Operatii_Unare[] = "scalerA";
    char Caractere_nepermise[]="bdfghifjkmnpqtvwqyzx";

    for (int i = 1; i <= L; ++i)
    {
        if (strchr(Operatii_Unare, sir[i][0])||strchr(Caractere_nepermise, sir[i][0]))
        {
            switch(sir[i][0])
            {
                case 's':
                {
                    if (strcmp(sir[i], "sin"))
                        eroare = true;
                    break;
                }

                case 'c':
                {
                    if (strcmp(sir[i], "cos"))
                        eroare = true;
                    break;
                }

                case 'a':
                {
                    if (strcmp(sir[i], "abs"))
                        eroare = true;
                    break;
                }

                case 'l':
                {
                    if (strcmp(sir[i], "log"))
                        eroare = true;
                    break;
                }

                case 'e':
                {
                    if (strcmp(sir[i], "exp"))
                        eroare = true;
                    break;
                }

                case 'r':
                {
                    if (strcmp(sir[i], "rad"))
                        eroare = true;
                    break;
                }

                case 'b':
                {
                    if (strcmp(sir[i], "rad"))
                    eroare=true;
                    break;
                }
                 case 'd':
                {
                    if (strcmp(sir[i], "rad"))
                    eroare = true;
                    break;
                }
                 case 'f':
                {
                    if (strcmp(sir[i], "rad"))
                    eroare = true;
                    break;
                }
                 case 'g':
                {
                    if (strcmp(sir[i], "rad"))
                    eroare = true;
                    break;
                }
                 case 'h':
                {
                    if (strcmp(sir[i], "rad"))
                    eroare = true;
                    break;
                }
                 case 'i':
                {
                    if (strcmp(sir[i], "rad"))
                    eroare = true;
                    break;
                }
                 case 'j':
                {
                    if (strcmp(sir[i], "rad"))
                    eroare = true;
                    break;
                }
                 case 'k':
                {
                    if (strcmp(sir[i], "rad"))
                    eroare = true;
                    break;
                }
                 case 'm':
                {
                    if (strcmp(sir[i], "rad"))
                    eroare = true;
                    break;
                }
                 case 'n':
                {
                    if (strcmp(sir[i], "rad"))
                    eroare = true;
                    break;
                }
                 case 'p':
                {
                    if (strcmp(sir[i], "pi"))
                    eroare = true;
                    break;
                }
                 case 'q':
                {
                    if (strcmp(sir[i], "rad"))
                    eroare = true;
                    break;
                }
                 case 't':
                {
                    if (strcmp(sir[i], "rad"))
                    eroare = true;
                    break;
                }
                 case 'v':
                {
                    if (strcmp(sir[i], "rad"))
                    eroare = true;
                    break;
                }
                 case 'w':
                {
                    if (strcmp(sir[i], "rad"))
                    eroare = true;
                    break;
                }

                 case 'y':
                {
                    if (strcmp(sir[i], "rad"))
                    eroare = true;
                    break;
                }
                 case 'z':
                {
                    if (strcmp(sir[i], "rad"))
                    eroare = true;
                    break;
                }
                 case 'A':
                    {
                        if(strcmp(sir[i],"Arc"))
                        eroare=true;
                        break;
                    }

            }
        }

    }
}

void Butonul_Grafic(int l)
{
    Functie E;
    readimagefile("Fundal5.jpg", 0, 0, 1000, 1000);
    settextstyle(3, 0, 2);
    if(l == 1)
    CitesteSir(30, 100, "Introduceti functia: ", E.expresie);
    else
    CitesteSir(30, 100, "Insert the function: ", E.expresie);
    addSpatii(E.expresie, E.eroare);
    aflareComponente(E.expresie, E.comp, E.nr_comp);
    verificareFunctii(l, E.comp, E.nr_comp, E.eroare, E.a);
    if(E.eroare == false)
    {
        Desenare_Axe();
        setcolor(BLUE);
        setlinestyle(0, 0, 4);
        ReprezintaGrafic(l, E.a, E.b, E.comp, E.nr_comp);
    }
    else
    {
        if(l == 1)
        {
            showerrorbox("Functia a fost introdusa incorect!");
            Butonul_Grafic(l);
        }
        else
        {
            showerrorbox("The function was inserted incorectly!");
            Butonul_Grafic(l);
        }
    }
    Butoane_Grafic(l, E.a, E.b, E.ymin, E.ymax, E.comp, E.nr_comp, E.eroare);
}

void Butoane_Meniu(int l)
{
    int x, y;
    do{
        x = mousex();
        y = mousey();
        if(ismouseclick(WM_LBUTTONDOWN) && interiorButon(x, y, 400, 300, 600, 400))
        {
            clearmouseclick(WM_LBUTTONDOWN);
             Butonul_Grafic(l);
        }
        else
            if(ismouseclick(WM_LBUTTONDOWN) && interiorButon(x, y, 400, 500, 600, 600))
        {
            clearmouseclick(WM_LBUTTONDOWN);
            Butonul_Limba(l);
        }
        else
            if(ismouseclick(WM_LBUTTONDOWN) && interiorButon(x, y, 400, 700, 600, 800))
        {
            clearmouseclick(WM_LBUTTONDOWN);
            Butonul_Calculator(l);
        }
        clearmouseclick(WM_LBUTTONDOWN);
        Sleep(3);
    } while(true);
    getch();
}

void Meniu(int l)
{
    if(l == 1)
        readimagefile("Fundal7.jpg", 0, 0, 1000, 1000);
    else
        readimagefile("Fundal8.jpg", 0, 0, 1000, 1000);
    settextstyle(3, 0, 5);
    Butoane_Meniu(l);
}

int main()
{
    int l = 1;
    initwindow(1000, 1000, "GRAFIC");
    Meniu(l);
    getch();
    closegraph();
    return 0;
}
