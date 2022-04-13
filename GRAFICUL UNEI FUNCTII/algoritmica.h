#define Infinit INT_MAX
#define Epsilon 0.00001
#define pi 3.1415926
#define MAX 101
#define MAX_EXP 300
#define Infinit INT_MAX
#define Epsilon 0.00001
#define pi 3.1415926
#define MAX 101
#define MAX_EXP 300
#define unitate 20

struct Operanzi
{
    double st1[MAX];
    int top1;
} s_operand;

struct Operatori
{
    char st2[MAX];
    int top2;
} s_operator;

unsigned prioritate (char op)
{
    if (op == '(' || op == ')')
        return 0;
    if (op == '+' || op == '-')
        return 1 ;
    if (op == '*' || op == '/')
        return 2;
    if (op == '^')
        return 3;
    if (op == '#' || op =='=' || op =='<' || op == '>')
        return 4;
    return 5;
}

//verifica daca un sir de caractere este numar
bool Este_Numar(char sir[100])
{
    int i, ok;
    int L = strlen(sir);
    ok = 1;
    if(sir[0] == '-')//modificat
    {

        for (i = 1; i < L && ok != 0; i++)
        if (strchr("0123456789.eE", sir[i]) == NULL)//modificat
         ok = 0;
    }
    else
        {
        for (i = 0; i < L && ok != 0; i++)
        if (strchr("0123456789.eE", sir[i]) == NULL)
         ok = 0;
        }
    return ok;
}

//inserez caracterul ' ' pe o pozitie data
void insereazaSpatiu (char sir[], int poz, int &lung)
{
    lung++;
    for (int i = lung - 2; i >= poz; --i)
    {
        sir[i + 1] = sir[i];
    }
    sir[poz] = ' ';
}

//adaug spatii intre elementele diferie pentru a putea fi diferentiate
void addSpatii(char sir[], bool &eroare)
{
    char Operatii_Binare[] = "+-*/&<>=#^";
    char Operatii_Unare[] = "scalerA";
    char Cifre[] = " 0123456789.eE";
    strcat(sir,"$");
        int i = 0, L = strlen(sir);
        if (sir[0] == '-') i++;
        while (i < L)
        {
            if (sir[i] == 'x')
            {
                insereazaSpatiu(sir, i+1, L);
                i++;
            }
            else if (strchr(Operatii_Binare, sir[i]))
            {
                if (strchr(Cifre,sir[i-2]) || sir[i-2] == 'x' || sir[i-2] == ')')
                {
                     insereazaSpatiu(sir , i + 1, L);
                     i++;
                }
            }
            else if (strchr("()",sir[i]))
            {
                 insereazaSpatiu(sir , i + 1, L);
                 i++;
            }
            else if (strchr(Operatii_Unare, sir[i]))
            {
                insereazaSpatiu(sir , i + 3, L);
                i += 3;
            }
            else if (strchr(Cifre, sir[i]))
            {
                //daca numarul incepe cu "." sau "E" functia este incorecta d.p.d.v sintactic
                if (sir[i] == '.' || sir[i] == 'E')
                {
                    eroare = true;
                    return;
                }
                int p = i;
                unsigned nr = 0; // nr de puncte zecimale pentru verificarea daca numarul este corect d.p.d.v sintactic (pt numere reale)
                while (sir[p + 1] && nr <= 1 && strchr(Cifre, sir[p]))
                {
                    if (sir[p] == '.')
                        nr++;

                    if (sir[p] == 'E')
                    {
                        p++; //sar peste operatorul + sau - care apare dupa E
                    }
                    p++;
                }

                if (nr > 1)
                {
                    eroare = true;
                    return;
                }
                insereazaSpatiu(sir, p, L);
                i = p;
            }
            i++;
        }
        sir[L - 1] = '\0';
}

//despart expresia functiei pe componente si le memorez in E.comp[MAX]
void aflareComponente(char s[], char sir[][MAX], int &L)
{
    L = 0;
    strcpy(sir[++L],"(");
    char *componenta;
    componenta = strtok(s, " $");
  //  cout << componenta << '\n';
    while (componenta)
    {
        strcpy(sir[++L], componenta);
        componenta = strtok(NULL, " $");
    }
     strcpy(sir[++L],")");
}

double calculFunctie (double x, char sir[][MAX], int L, bool &eroare)
{
    double rezultat;
    s_operand.top1 = 0;
    s_operator.top2 = 1;
    s_operator.st2[s_operator.top2] = '(';
    int i = 2; // contorul componentelor
    if (L == 3 && !strcmp(sir[2],"x"))
        return x;
        while (i <= L)
        {
            if ((Este_Numar(sir[i])&&sir[i][0]!='-')||(sir[i][0]=='-'&&sir[i][1]>='1'&&sir[i][1]<='9'))
            {
                double nr = atof(sir[i]);
                s_operand.st1[++s_operand.top1] = nr;
            }


            else
            {
                switch(sir[i][0])
                {

                    case 'x':
                        {
                            s_operand.st1[++s_operand.top1] = x;
                            break;
                        }
                        //inceput de bloc nou
                    case '(':
                        {
                            s_operator.st2[++s_operator.top2] = '(';
                            break;
                        }
                    default:
                        {
                            unsigned pr_curent = prioritate(sir[i][0]); //prioritatea operatorului curent
                            unsigned pr_top = prioritate(s_operator.st2[s_operator.top2]); //prioritatea operatorului din vf stivei
                            if (pr_curent > pr_top)
                            {
                                s_operator.st2[++s_operator.top2] = sir[i][0];
                            }
                             // nr negativ aflat intre paranteze
                            else if ((s_operator.st2[s_operator.top2] == '(' && sir[i][0] == ')')||s_operator.st2[s_operator.top2]==')')
                                {
                                    s_operator.top2--;
                                }
                            else
                            {
                                double val;
                                double x1, x2;
                                x1 = s_operand.st1[s_operand.top1 - 1]; //penultimul operand
                                x2 = s_operand.st1[s_operand.top1]; // ultimul operand
                                while (s_operator.top2 > 1 && !(pr_curent > pr_top))
                                {
                                   int g=0;//AM ADAUGAT ACEST g PENTRU APELUL FUNCTIILOR CARE FOLOSESC O SINGURA VARIABILA

                                    switch(s_operator.st2[s_operator.top2]) //! daca nu se verifica niciun caz iese automat din switch?
                                    {

                                        case '=':
                                            {
                                                val = Egal(x1,x2);

                                                break;
                                            }
                                        case '#':
                                            {
                                                val = Diferit(x1,x2);
                                                break;
                                            }
                                        case '<':
                                            {
                                                val = Mai_Mic(x1,x2);
                                                break;
                                            }
                                        case '>':
                                            {
                                                val = Mai_Mare(x1,x2);
                                                break;
                                            }
                                        case '+':
                                            {
                                                val = Plus(x1,x2);
                                                break;
                                            }
                                        case '-':
                                            {
                                                val = Minus(x1,x2);
                                                break;
                                            }
                                        case '*':
                                            {
                                                val = Inmultire(x1,x2);
                                                break;
                                            }
                                        case '/':
                                            {
                                                val = Impartire(x1, x2);
                                                break;
                                            }
                                        case '^':
                                            {
                                                val = Putere(x1, x2);
                                                break;
                                            }
                                        case 's':
                                            {
                                            val = Sinus(x2); g = 1;//MODIFICAT TREBUIA X2 +g1=1
                                            break;
                                            }
                                        case 'c':
                                            {
                                                val = Cosinus(x2); g = 1;//MODIFICAT TREBUIA X2 +g1=1
                                                break;
                                            }
                                        case 'A':
                                            {
                                                val = Arctan(x2); g = 1;//g1=1
                                                break;
                                            }
                                        case 'l':
                                            {
                                                val = Logaritm(x2); g=1;//g1=1
                                                break;
                                            }
                                        case 'e':
                                            {
                                                val = Exponential(x2); g=1;//g1=1
                                                break;
                                            }
                                        case 'r':
                                            {
                                                val = Radical(x2); g=1;//g1=1
                                                break;
                                            }
                                        case 'a':
                                            {
                                                val= Modul(x2);g=1;
                                                break;
                                            }

                                    }
                                    if (s_operator.st2[s_operator.top2] == '(')
                                    {
                                        s_operator.top2--;
                                        break;
                                    }
                                    if(g==0)//ACEST IF INSEAMNA: DACA AM FOLOSIT O FUNCTIE CU 2 PARAMETRI CARE AU FORMAT UN PARAMETRU (ADUNARE/SCADERE/INMULTIRE)
                                        s_operand.top1--;//ATUNCI REDUCEM NUMARUL DE ELEMENTE DIN STIVA 1 CA SA NU DEA EROARE LA IF-ul DE LA LINIA 492
                                    s_operand.st1[s_operand.top1] = val;
                                    s_operator.top2--;
                                    pr_top = prioritate(s_operator.st2[s_operator.top2]);
                                     x1 = s_operand.st1[s_operand.top1 - 1];//MODIFICAT !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
                                     x2 = s_operand.st1[s_operand.top1];//MODIFICAT !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

                            } //while
                            if (sir[i][0] != ')')
                                s_operator.st2[++s_operator.top2] = sir[i][0];
                        } //else
                        break;
                    } //default
            }
        }
        i++;
    }//while

  if (s_operand.top1 == 1 && s_operator.top2 == 1 )
        rezultat = s_operand.st1[s_operand.top1];

  else
  {
       eroare = true;
       rezultat = Infinit;
  }
  return rezultat;
}

double Calculator (char sir[][MAX], int L)
{
char Operatii_Binare[] = "+-*/&<>=#^";
char Operatii_Unare[] = "scalerA";
char Cifre[] = " 0123456789.eE";
bool eroare = false; // memoreaza true/false in functie de corectitudinea d.p.d.v sintactic a expresiei functiei
double rezultat;
s_operand.top1 = 0;
s_operator.top2 = 1;
s_operator.st2[s_operator.top2] = '(';
int i = 2; // contorul componentelor
        while (i <= L)
        {
            if ((Este_Numar(sir[i])&&sir[i][0]!='-')||(sir[i][0]=='-'&&sir[i][1]>='1'&&sir[i][1]<='9'))//MODIFICAT !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

            {
                double nr = atof(sir[i]);
                s_operand.st1[++s_operand.top1] = nr;
                //depanare();
            }

              else
            {
                switch(sir[i][0])
                {

                        //inceput de bloc nou
                    case '(':
                        {
                            s_operator.st2[++s_operator.top2] = '(';
                            break;
                        }
                    default:
                        {
                            unsigned pr_curent = prioritate(sir[i][0]); //prioritatea operatorului curent
                            unsigned pr_top = prioritate(s_operator.st2[s_operator.top2]); //prioritatea operatorului din vf stivei
                            if (pr_curent > pr_top)
                            {
                                s_operator.st2[++s_operator.top2] = sir[i][0];
                            }
                             // nr negativ aflat intre paranteze
                            else if ((s_operator.st2[s_operator.top2] == '(' && sir[i][0] == ')')||s_operator.st2[s_operator.top2]==')')
                                {
                                    s_operator.top2--;
                                }
                                  else
                            {
                                double val;
                                double x1, x2;
                                x1 = s_operand.st1[s_operand.top1 - 1]; //penultimul operand
                                x2 = s_operand.st1[s_operand.top1]; // ultimul operand
                                while (s_operator.top2 > 1 && !(pr_curent > pr_top))
                                {
                                   int g=0;//AM ADAUGAT ACEST g PENTRU APELUL FUNCTIILOR CARE FOLOSESC O SINGURA VARIABILA

                                    switch(s_operator.st2[s_operator.top2]) //! daca nu se verifica niciun caz iese automat din switch?
                                    {

                                        case '=':
                                            {
                                                val = Egal(x1,x2);

                                                break;
                                            }
                                        case '#':
                                            {
                                                val = Diferit(x1,x2);
                                                break;
                                            }
                                        case '<':
                                            {
                                                val = Mai_Mic(x1,x2);
                                                break;
                                            }
                                        case '>':
                                            {
                                                val = Mai_Mare(x1,x2);
                                                break;
                                            }
                                        case '+':
                                            {
                                                val = Plus(x1,x2);
                                                break;
                                            }
                                        case '-':
                                            {
                                                val = Minus(x1,x2);
                                                break;
                                            }
                                        case '*':
                                            {
                                                val = Inmultire(x1,x2);
                                                break;
                                            }
                                        case '/':
                                            {
                                                val = Impartire(x1,x2);
                                                break;
                                            }
                                        case '^':
                                            {
                                                val = Putere(x1,x2);
                                                break;
                                            }
                                        case 's':
                                            {
                                            val = Sinus(x2); g=1;//MODIFICAT TREBUIA X2 +g1=1
                                            break;
                                            }
                                        case 'c':
                                            {
                                                val = Cosinus(x2); g=1;//MODIFICAT TREBUIA X2 +g1=1
                                                break;
                                            }
                                        case 'a':
                                            {
                                                val = Modul(x2); g=1;//g1=1
                                                break;
                                            }
                                        case 'l':
                                            {
                                                val = Logaritm(x2); g=1;//g1=1
                                                break;
                                            }
                                        case 'e':
                                            {
                                                val = Exponential(x2); g=1;//g1=1
                                                break;
                                            }
                                        case 'r':
                                            {
                                                val = Radical(x2); g=1;//g1=1
                                                break;
                                            }
                                    }
                                   // depanare();
                                    if (s_operator.st2[s_operator.top2] == '(')
                                    {
                                        s_operator.top2--;
                                        break;
                                    }
                                    if(g == 0)//ACEST IF INSEAMNA: DACA AM FOLOSIT O FUNCTIE CU 2 PARAMETRI CARE AU FORMAT UN PARAMETRU (ADUNARE/SCADERE/INMULTIRE)
                                     s_operand.top1--;//ATUNCI REDUCEM NUMARUL DE ELEMENTE DIN STIVA 1 CA SA NU DEA EROARE LA IF-ul DE LA LINIA 492
                                     s_operand.st1[s_operand.top1] = val;
                                     s_operator.top2--;
                                     pr_top = prioritate(s_operator.st2[s_operator.top2]);
                                     x1 = s_operand.st1[s_operand.top1 - 1];//MODIFICAT !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
                                     x2 = s_operand.st1[s_operand.top1];//MODIFICAT !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

                            } //while
                            if (sir[i][0] != ')')
                                s_operator.st2[++s_operator.top2] = sir[i][0];
                        } //else
                        break;
                    } //default
            }
        }
        i++;
    }//while

  if (s_operand.top1 == 1)
        rezultat = s_operand.st1[s_operand.top1];

  else
  {
       eroare = true;
       rezultat = Infinit;
  }
  return rezultat;

}

void ReprezintaGrafic(int l, double a, double b, char sir[][MAX], int L)
{
    float x, y; // f(x)=y
    float x_next, y_next; //coordonatele succesoare lui x, y
    int x_ecran, y_ecran; //coordonatele x,y transpuse pe ecran
    int x_nextEcran, y_nextEcran; //coordonatele de pe ecran succesoare lui x_ecran, y_ecran
    bool eroare = false;
    const float k = 2;
    x = a;
    y = calculFunctie(x, sir, L, eroare); //f(a) = y

    x_ecran = 499 + unitate * x;  //499, deoarece coordonatele originii graficului sunt O(499,499)
    y_ecran = 499 - unitate * y;

    for (double i = 1; (i <= b - a && x <= b) ; i+=0.01)
    {
        x_next = a + i * k;
        if (x_next <= b)
        {

            y_next = calculFunctie(x_next, sir, L, eroare);
            x_nextEcran = 499 + unitate * x_next;
            y_nextEcran = 499 - unitate * y_next;
            setlinestyle(0,0,3);
            if(y_ecran>1080 || y_ecran<-110)
                putpixel(x_ecran,y_ecran,GREEN);
            else if (y != Infinit && y_next != Infinit)
            {
                line(x_ecran, y_ecran, x_nextEcran, y_nextEcran);
                  //daca se afla pe axa Ox
                  if (y_ecran == 499||y_ecran==500)
                  {
                     setcolor(YELLOW);
                     circle(x_ecran, y_ecran, 4);
                     setfillstyle(SOLID_FILL, YELLOW);
                     floodfill(x_ecran, y_ecran, YELLOW);
                     setcolor(BLUE);
                  }

                  //daca se afla pe axa Oy
                  if (x_ecran == 499||x_ecran==500)
                  {
                     setcolor(YELLOW);
                     circle(x_ecran, y_ecran, 4);
                     setfillstyle(SOLID_FILL, YELLOW);
                     floodfill(x_ecran, y_ecran, YELLOW);
                     setcolor(BLUE);
                  }
            }
            x = x_next;
            y = y_next;
            x_ecran = x_nextEcran;
            y_ecran = y_nextEcran;
        }
    }

}

void Desen_Minim(double a, double b, double ymin, char sir[][MAX], int L, bool eroare)
{
     int x_ecran, y_ecran;
     double x, y;
     ymin=100000000;

     for(double i = a; i <= b; i = i + 0.01)
     {
         y = calculFunctie(i, sir, L, eroare);
         if(y < ymin)
            ymin = y;
     }

     for(double i = a; i <= b; i = i + 0.01)
     {
         y = calculFunctie(i, sir, L, eroare);
         if(y == ymin)
         {
             x = i;
             x_ecran = 499 + unitate * x;
             y_ecran = 499 - unitate * ymin;
             setcolor(BLACK);
             circle(x_ecran, y_ecran, 8);
             setfillstyle(SOLID_FILL, BLACK);
             floodfill(x_ecran, y_ecran, BLACK);
         }
     }

}

void Desen_Maxim(double a, double b, double ymax, char sir[][MAX], int L, bool eroare)
{
    int x_ecran, y_ecran;
    double x, y;
    ymax=-10000000;

     for(double i = a; i <= b; i = i + 0.01)
     {
        y = calculFunctie(i, sir, L, eroare);
        if(y > ymax)
        {
            if(y != Infinit)
                ymax = y;
        }

     }

     for(double i = a; i <= b; i = i + 0.01)
     {
          y = calculFunctie(i, sir, L, eroare);
          if(y == ymax)
          {
             x=i;
             x_ecran = 499 + unitate * x;
             y_ecran = 499 - unitate * ymax;
             setcolor(MAGENTA);
             circle(x_ecran,y_ecran,8);
             setfillstyle(SOLID_FILL,MAGENTA);
             floodfill(x_ecran, y_ecran,MAGENTA);
          }
     }
}
