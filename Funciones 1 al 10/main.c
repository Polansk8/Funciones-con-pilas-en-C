#include <stdio.h>
#include <stdlib.h>
#include "pila.h"
#include <conio.h>
#include <time.h>
#include "gotoxy.h"


#define ESC 27


void cargaPilaUsuario (Pila *p, char titulo[]);   /// 1) Carga una pila hasta donde quiera el usuario.
void cargaPilaRandom(Pila  *p, int limite);       /// Carga una pila con numeros aleatorios.
void muestraPila (Pila p, char titulo[]);         /// Muestra los datos de una pila.
void pasaPila (Pila *origen, Pila *destino);      /// 2) Pasa elementos de una pila a otra.
void igualPasaPila (Pila *origen, Pila *destino); /// 3) Pasa elementos de una pila a otra conservando el orden.
int cuentaPila (Pila p);                          /// Cuenta los datos de una pila.
int sumaPila (Pila p);                            /// Suma los elementos de una pila.
int buscaMenorPila (Pila *p);                     /// 4) Busca el menor elemento de una pila y lo retorna
void pasaPilaOrdenada (Pila *origen, Pila *destino);
void insertaElemento (Pila *ordenada, int elemento);
void ordenarPilaPorInsercion(Pila *a,Pila *ordenada);
int sumaTopeYAnterior (Pila c);
float promedioDePila (Pila p);
int dePilaADecimal (Pila p);
int buscaMenor (Pila *p);
void ordenaPila (Pila *origen, Pila *ordenada);


int main()
{

    srand(time(NULL));
    Pila DATOS, ORDENADA, AUX, TEMPERATURAS;

    inicpila(&DATOS);
    inicpila(&ORDENADA);
    inicpila(&AUX);
    inicpila(&TEMPERATURAS);

    cargaPilaRandom(&DATOS, 10);
    muestraPila(DATOS, "Se cargo la pila [DATOS]");
    system("pause");
    system("cls");

    int num;

    printf("\t Se busco y elimino el menor dato de la pila y es: >>%d<<", buscaMenor(&DATOS));
    muestraPila(DATOS, "Pila [DATOS]");

    return 0;
}


///1)
/** \brief Carga una pila por medio del usuario
 *
 * \param Un puntero a una pila
 * \param Un string para usar como titulo
 * \return No return
 *
 */
void cargaPilaUsuario (Pila *p, char titulo[])
{
    char opcion = 0;
    int num;
    do
        {

        if(opcion != ESC)
            {
            printf("\n\n%s", titulo);
            scanf("%d", &num);
            apilar(p, num);
            }
        printf("Presione <ENTER> para agregar un valor a la pila o <ESC> para salir");
        opcion = getch();
        system("cls");
        }while (opcion != ESC);
}


/** \brief Carga una pila con numeros aleatorios
 *
 * \param Una pila
 * \param Cantidad de elementos
 * \return No return
 *
 */
 void cargaPilaRandom(Pila  *p, int limite)
{
    for (int i=0;i<limite;i++)
        {
        apilar(p, rand()%50);
        }
}




/** \brief Muestra una pila por pantalla
 *
 * \param Una pila
 * \param Un string como titulo
 * \return No return
 *
 */
void muestraPila (Pila p, char titulo[])
{
    Pila AUX;

    inicpila(&AUX);
    int i = 0;

    pasaPila(&p, &AUX);

    printf("\n\n\t\t%s", titulo);
    printf("\n");
    while (!pilavacia(&AUX))
        {
            printf(" %02d |", tope(&AUX));
            apilar(&p, desapilar(&AUX));
        i++;
        if (i%12 == 0)
            {
            printf("\n");
            }
        }
    printf("\n");
}


///2)
 /** \brief Pasa elementos de una pila a otra
  *
  * \param Puntero a una pila cargada (ORIGEN)
  * \param Puntero a una pila vacia o no (DESTINO)
  * \return No return
  *
  */
void pasaPila (Pila *origen, Pila *destino)
{
    while (!pilavacia(origen))
        {
        apilar(destino, desapilar(origen));
        }
}



///3)
/** \brief Pasa los elementos de una pila a otra conservando el orden
 *
 * \param Una pila cargada (origen)
 * \param Una pila vacia o no (destino)
 * \return No return
 *
 */
void igualPasaPila (Pila *origen, Pila *destino)
{
    Pila AUX;
    inicpila(&AUX);

    pasaPila(origen, &AUX);
    pasaPila(&AUX, destino);
}





/// 4)
/** \brief Busca el menor elemento de una pila y lo retorna
 *
 * \param Un puntero a una pila
 * \return El menor elemento
 *
 */
int buscaMenorPila (Pila *p)
{
    Pila AUX;

    inicpila(&AUX);

    int menor;

    if (!pilavacia(p))
        {
        menor = desapilar(p);
        while (!pilavacia(p))
            {
            if (tope(p) > menor)
                {
                apilar(&AUX, menor);
                menor = desapilar(p);
                }
                else
                    {
                    apilar(&AUX, desapilar(p));
                    }
            }
        }
    pasaPila(&AUX, p);
    return menor;
}



/// 5)
/** \brief Pasa los elementos de una pila a otra ordenandola de menor a mayor
 *
 * \param Un puntero a una pila (ORIGEN)
 * \param Un puntero a otra pila (DESTINO)
 * \return No return
 *
 */
void pasaPilaOrdenada (Pila *origen, Pila *destino)
{
    Pila ORDENADA;

    inicpila(&ORDENADA);

    while (!pilavacia(origen))
        {
        apilar(&ORDENADA, buscaMenorPila(origen));
        }

    pasaPila(&ORDENADA, destino);
}



///6
/** \brief Inserta un elemento en una pila ORDENADA
 *
 * \param Una pila que este ordenada (mayor (base) a menor (tope)
 * \param Un numero que desee igresar
 * \return No return
 *
 */
void insertaElemento (Pila *ordenada, int elemento)
{
    Pila AUX;

    inicpila(&AUX);

    while (!pilavacia(ordenada) && tope(ordenada) < elemento)
        {
        apilar(&AUX, desapilar(ordenada));
        }

    apilar(ordenada, elemento);

    pasaPila(&AUX, ordenada);
}

/** \brief Ordena una pila por insercion
 *
 * \param Puntero a una pila cargada
 * \return No return
 *
 */
void ordenarPilaPorInsercion(Pila *origen,Pila *ordenada)
{
    Pila aux;
    inicpila(&aux);
    while(!pilavacia(origen))
    {
        insertaElemento(ordenada,tope(origen));
        apilar(&aux,desapilar(origen));
    }
}


int sumaTopeYAnterior (Pila c)
{
    int suma;

    suma = desapilar(&c);

    suma = suma + desapilar(&c);

    return suma;
}

/** \brief Cuenta los datos de una pila
 *
 * \param Una copia a una pila
 * \param
 * \return La cantidad de datos de la pila
 *
 */
int cuentaPila (Pila p)
{
    Pila AUX;
    inicpila(&AUX);

    int cont = 0;

    while (!pilavacia(&p))
        {
        apilar(&AUX, desapilar(&p));
        cont++;
        }

    return cont;
}




/** \brief Suma los elementos de una pila
 *
 * \param Una copia de pila
 * \return La suma de los elementos
 *
 */
int sumaPila (Pila p)
{
    Pila AUX;
    inicpila(&AUX);

    int total = 0;

    while (!pilavacia(&p))
        {
        total += tope(&p);
        apilar(&AUX, desapilar(&p));
        }

    return total;
}


float division (int num, int divisor)
{
    return (float) num / divisor;
}

float promedioDePila (Pila p)
{
    cuentaPila(p);
    sumaPila(p);

    return division(sumaPila(p), cuentaPila(p));
}


int dePilaADecimal (Pila p)
{
    Pila aux;

    inicpila(&aux);

    pasaPila(&p, &aux);

    int resultado = 0;
    int suma = 0;
    int mult = 1;

    while (!pilavacia (&aux))
        {
        resultado = mult * desapilar(&aux);
        suma = suma + resultado;
        mult = mult * 10;
        }
    return suma;
}


///Ejercicio 4
int buscaMenor (Pila *p)
{
    Pila AUX;
    inicpila(&AUX);

    int menor;

    if (!pilavacia(p))
        {
        menor = desapilar(p);
        while (!pilavacia(p))
            {
            if (tope(p) < menor)
                {
                apilar(&AUX, menor);
                menor = desapilar(p);
                }
                else
                    {
                    apilar(&AUX, desapilar(p));
                    }
            }
        }
    pasaPila(&AUX, p);

    return menor;
}


void ordenaPila (Pila *origen, Pila *ordenada)
{
    while (!pilavacia(origen))
        {
        apilar(ordenada, buscaMenor(origen));
        }
}


