#ifndef POKEMON_H //inclusion de las guards
#define POKEMON_H
#include <iostream>
#include <vector>
#include <math.h> //libreria para hacer uso de modf() durante las validaciones
#include <time.h> //libreria para generar numeros aleatorios
#include <stdlib.h> //libreria para hacer uso de la funcion atoi()
using namespace std;

namespace pocketMonsters{
    /*struct que contiene las propiedades de un ataque. nombre contiene el nombre en string, char tipo espera recibir un numero
    con el que se identifican las debilidades o resistencias y poder recibe una int que hace referencia al daño base del ataque.*/
    struct StrAtaque{
        string nombre;
        char tipo;
        int poder;
    };
    //definicion de el tipo ataque, vector que contiene cuatro estructuras del tipo StrAtaque y es un parametro para el constructor de la clase pokemon
    typedef  vector<StrAtaque> ataque;
    enum tipos {agua, hierva, fuego, hielo, roca, tierra, electrico, normal};
    /*arreglo de strings usado para imprimir el tipo del ataque a la hora de solicitar un movimiento al usuario, el programa reconoce
    las debilidades y las resistencias con diferentes numeros correspondiendo a la enumeracion tipos.*/
    string tipoAtk[] = {"agua", "hierva", "fuego", "hielo", "roca", "tierra", "electrico", "normal"};
    //struct que contiene las tres stats de vida, ataque y velocidad. lo recibe como un parametro en el constructor de la clase pokemon
    struct stats{
        int HP;
        int ATK;
        int SPD;
    };
    class Pokemon{
        protected:
            string nombre; //nombre del pokemon
            string tipo; //tipo del pokemon, en letras
            stats estadisticas; //struct con las estadisticas del pokemon
            ataque ataques; //vector de tipo StrAtaque con los 4 ataques del pokemon
            string debilidades; //string con diferentes numeros correspondientes a las debilidades del pokemon, segun el enum tipos
            string resistencias; //string con diferentes numeros correspondientes a las fortalezas del pokemon, segun el enum tipos
            int totalHP; //numero de HP total del pokemon, usada para curar a los pokemon cuando termina una batalla por si el usuario desea iniciar otra.

        public:
            //constructor de la clase pokemon, recibe un vector con 4 ataques, un nombre y una estructura con sus stats.
            Pokemon(ataque, string, stats);
            //recibe el ataque a utilizar, un objetivo y una int correspondiente a la stat de ataque de el pokemon atacante
            void atacar(StrAtaque, Pokemon&, int);
            //funcion para cambiar el stat de HP del struct stats.
            void setVida(int);
            /*recibe un ataque y un objeto de la clase pokemon correspondiente al pokemon atacado. Verifica todos los strings correspondientes
            a las debilidades y resistencias del pokemon y retorna 1 si el pokemon es debil, 2 si el pokemon es resistente y 0 si es neutro*/
            int verificar(StrAtaque, Pokemon&);
            //retorna la vida actual del pokemon
            int getVida();
            //cambia las resistencias del pokemon.
            void setResistencias(string);
            //retorna las resistencias del pokemon
            string getResistencias();
            //cambia las debilidades del pokemon
            void setDebilidades(string);
            //retorna las debilidades del pokemon
            string getDebilidades();
            //retorna el nombre del pokemon
            string getNombre();
            //retorna los ataques del pokemon
            std::vector<StrAtaque> getAtaques();
            //retorna la stat de SPD del struct stats
            int getVelocidad();
            //retorna la stat de ATK del struct stats
            int getAtaque();
            //retorna la vida total del pokemon
            int getTotalHP();
    };
    class Fuego : public Pokemon{
        public:
            /*recibe 4 ataques, una string con el nombre y las stats del pokemon. a la hora de que el constructor es llamado, define automaticamente
            el tipo, debilidades y resistencias del pokemon. lo mismo para el constructor de las clases hierva y agua.*/
            Fuego(ataque, string, stats);
    };
    class Hierva : public Pokemon{
        public:
            Hierva(ataque, string, stats);
    };
    class Agua : public Pokemon{
        public:
            Agua(ataque, string, stats);
    };

    //vector de tipo Pokemon, usado para almacenar un equipo de pokemon.
    typedef vector<Pokemon> pkmnTeam;

    class Simulador{
        public:
            /*muestra el menu del programa, con las opciones de iniciar batalla o cerrar el programa, recibe un pkmnTeam desde el main
            que contiene todos los pokemon programados, para poder iniciar los diferentes metodos de la clase simulador que reciben pokemon
            como parametros.*/
            void mostrarMenu(pkmnTeam&);
            //metodo usado para inciar batallas 1v1
            void iniciarBatalla(Pokemon&, Pokemon&);
            //metodo sobrecargado usado para iniciar batallas 2v2 y 3v3
            void iniciarBatalla(pkmnTeam&, pkmnTeam&);
            //metodo usado para solicitar un movimiento al usuario, recibe los ataques de un pokemon y el nombre de este.
            StrAtaque solicitarMovimiento(ataque, string);
            //metodo que finaliza la batalla 1v1, cura a ambos pokemon participando.
            void finalizarBatalla(Pokemon&, Pokemon&);
            //metodo sobrecargado que cura a un solo pokemon, usado cuando en una batalla multiple cae un pokemon pero no termina la batalla.
            void finalizarBatalla(Pokemon&);
            //metodo sobrecargado que cura a un equipo entero, usado en el equipo ganador al finalizar una batalla multiple.
            void finalizarBatalla(pkmnTeam&);
    };
}
//inclusion del archivo cpp
#include "Pokemon.cpp"
#endif

