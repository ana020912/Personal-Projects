#include<string.h>
#include<math.h>
#define Infinit INT_MAX
#define Epsilon 0.00001
#define pi 3.1415926

double Diferit_de_Infinit(double x)
{
    return fabs(Infinit - fabs(x)) > (Infinit / 2.0);
}

double Logaritm(double x)
{
    if (x > Epsilon && Diferit_de_Infinit(x) == 1)
        return log(x);
}

double Exponential(double x)
{
    if (Diferit_de_Infinit(x) == 1)
        return exp(x);
    return 1.0 * Infinit;

}
double Inmultire(double x, double y)
{
    if (fabs(x) < Epsilon || fabs(y) < Epsilon)
        return 0;
    else if (Diferit_de_Infinit(x) == 1 && Diferit_de_Infinit(y) == 1)
        return x * y;
    else
        return 1.0 * Infinit;
}

double Impartire(double x, double y)
{
    if (fabs(x) < Epsilon)
        return 0;
    if (Diferit_de_Infinit(x) == 1 && Diferit_de_Infinit(y) == 1 && fabs(y) >= Epsilon)
        return x / y;
    return 1.0 * Infinit;
}

double Putere(double x, double y)
{
    if (x == 0)
        return 0;
    else if (y == 0)
        return 1;
    else if (Diferit_de_Infinit(x) == 0 || Diferit_de_Infinit(y) == 0)
        return 1.0 * Infinit;
    else
        return pow(x, y);


}

bool Egal(double x, double y)
{
    return (x == y);
}

bool Diferit(double x, double y)
{
    return (x != y);
}

bool Mai_Mic(double x, double y)
{
    return (x < y);
}

bool Mai_Mare(double x, double y)
{
    return (x >= y);
}

double Plus(double x, double y)
{
    if (Diferit_de_Infinit(x) == 1 && Diferit_de_Infinit(y) == 1)
        return x + y;
    return 1.0 * Infinit;
}

double Minus(double x, double y)
{
    if (Diferit_de_Infinit(x) == 1 && Diferit_de_Infinit(y) == 1)
        return x - y;
    return 1.0 * Infinit;

}

double Sinus(float x)
{
    if (Diferit_de_Infinit(x) == 1)
        return sin(x);
    return 1.0 * Infinit;

}
double Arctan (float x)
{
    if (Diferit_de_Infinit(x) == 1)
        return atan(x);
    return 1.0 * Infinit;
}

double Cosinus(double x)
{
    if (Diferit_de_Infinit(x) == 1)
        return cos(x);
    return 1.0 * Infinit;
}

double Modul(double x)
{
    if (Diferit_de_Infinit(x) == 1)
        return fabs(x);
    return 1.0 * Infinit;
}

double Radical(double x)
{
if (Diferit_de_Infinit(x) == 1 && x > Epsilon)
        return sqrt(x);
return 1.0 * Infinit;
}
