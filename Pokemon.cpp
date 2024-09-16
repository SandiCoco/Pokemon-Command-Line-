#include "Pokemon.h"
using namespace std;
using namespace pocketMonsters; //uso del namespace declarado en pokemon.h

//Constructor de la clase Pokemon
Pokemon::Pokemon(ataque _atks, string _nombre, stats _stats){
    ataques = _atks;
    nombre = _nombre;
    estadisticas = _stats;
    totalHP = _stats.HP;
}

//Setter del atributo vida, si recibe un numero menor que 0 automaticamente la vida se establece en 0.
void Pokemon::setVida(int _vida){
    if(_vida>=0){
        estadisticas.HP = _vida;
    }
    else{
        estadisticas.HP = 0;
    }
}

//retorna vida.
int Pokemon::getVida(){
    return estadisticas.HP;
}

//setter y getter del atributo debilidades.
string Pokemon::getDebilidades() {
	return this->debilidades;
}
void Pokemon::setDebilidades(string debilidades) {
	this->debilidades = debilidades;
}

//setter y getter del atributo resistencias.
string Pokemon::getResistencias() {
    return this->resistencias;
}
void Pokemon::setResistencias(string resistencias) {
    this->resistencias = resistencias;
}

//retorna los ataques del pokemon.
std::vector<StrAtaque> Pokemon::getAtaques(){
    return ataques;
}

//retorna el nombre del pokemon
string Pokemon::getNombre(){
    return nombre;
}

//retorna velocidad.
int Pokemon::getVelocidad(){
    return estadisticas.SPD;
}

//retorna ataque
int Pokemon::getAtaque(){
    return estadisticas.ATK;
}

//retorna la vida total del pokemon
int Pokemon::getTotalHP(){
    return totalHP;
}

int Pokemon::verificar(StrAtaque _ataque, Pokemon& pkmnAtacado){

    char tipo = _ataque.tipo; // asigna el numero de la variable char de la estructura del ataque, correspondiente al tipo del ataque.
    /*Los siguientes dos for recorren el string de resistencias que corresponde a la clase pokemon, si encuentran en ese string el mismo numero
    que corresponde al tipo del ataque, retorna 1, significando que el pokemon atacado es resistente al ataque usado.*/
    for(int i=0; i<pkmnAtacado.getResistencias().length(); i++)
    {
        if (tipo==pkmnAtacado.getResistencias()[i])
        {
            return 1;
            break;
        }
        i++;
    }
    for(int i=1; i<pkmnAtacado.getResistencias().length(); i++)
    {
        if (tipo==pkmnAtacado.getResistencias()[i])
        {
            return 1;
            break;
        }
        i++;
    }
    /*Los siguientes dos for recorren el string de debilidades que corresponde a la clase pokemon, si encuentran en ese string el mismo numero
    que corresponde al tipo del ataque, retorna 2, significando que el pokemon atacado es debil al ataque usado.*/
    for(int i=0; i<pkmnAtacado.getDebilidades().length(); i++)
    {
        if (tipo==pkmnAtacado.getDebilidades()[i])
        {
            return 2;
            break;
        }
        i++;
    }
    for(int i=1; i<pkmnAtacado.getDebilidades().length(); i++)
    {
        if (tipo==pkmnAtacado.getDebilidades()[i])
        {
            return 2;
            break;
        }
        i++;
    }
    //si la funcion verificar retorna 0, significa que no ha podido encontrar ninguna resistencia ni debilidad ante el ataque usado.
    return 0;
}

void Pokemon::atacar(StrAtaque _atkseleccionado, Pokemon& pkmnAtacado, int atkstat){ //atkseleccionado hace referencia al ataque retornado por la funcion solicitarMovimiento()
    int verificador, promedio; //verificador hace referencia a la int que recibe de usar la funcion verificar(), para calcular los daños.
    promedio = (atkstat+ _atkseleccionado.poder)/2; //promedio del poder del ataque y la stat de ataque del pokemon
    verificador = verificar(_atkseleccionado, pkmnAtacado); //llamado a la funcion verificar para guardarlo en la variable verificador
    if(verificador == 0){
        //si el verificador es 0, el pokemon atacado es neutro al ataque recibido por lo que el daño es simplemente promedio.
        pkmnAtacado.setVida(pkmnAtacado.getVida()-promedio);
        cout<<"--------------------------------------------------------------------------"<<endl;
        cout<<"se ha usado: "<<_atkseleccionado.nombre<<" contra: "<<pkmnAtacado.getNombre()<<" realizando "<<promedio<<" de da"<<(char)164<<"o!"<<endl;
        cout<<"--------------------------------------------------------------------------"<<endl;
    }
    else if (verificador == 1)
    {
        //si el verificador es 1, significa que el pokemon es resistente al ataque recibido, por lo que el daño se reduce en 20%
        promedio = promedio*0.80;
        pkmnAtacado.setVida(pkmnAtacado.getVida()-promedio);
        cout<<"--------------------------------------------------------------------------"<<endl;
        cout<<"se ha usado: "<<_atkseleccionado.nombre<<" contra: "<<pkmnAtacado.getNombre()<<" realizando "<<promedio<<" de da"<<(char)164<<"o!"<<endl;
        //notificacion de que el daño realizado fue menor debido a la resistencia de tipo
        cout<<"no es muy efectivo..."<<endl;
        cout<<"--------------------------------------------------------------------------"<<endl;
    }
    else if (verificador == 2){
        //si el verificador es 2, significa que el pokemon es debil al ataque recibido, por lo que el daño se aumenta en 20%
        promedio = promedio*1.20;
        pkmnAtacado.setVida(pkmnAtacado.getVida()-promedio);
        cout<<"--------------------------------------------------------------------------"<<endl;
        cout<<"se ha usado: "<<_atkseleccionado.nombre<<" contra: "<<pkmnAtacado.getNombre()<<" realizando "<<promedio<<" de da"<<(char)164<<"o!"<<endl;
        //notificacion de que el daño realizado es mayor debido a la debilidad de tipo
        cout<<"es super efectivo!"<<endl;
        cout<<"--------------------------------------------------------------------------"<<endl;
    }
}

Fuego::Fuego(ataque _atks, string _nombre, stats _stats) : Pokemon(_atks, _nombre, _stats){
    //asignacion automatica de las debilidades y resistencias de la clase fuego
    tipo = "fuego";
    debilidades = "045";
    resistencias = "123";
}

Agua::Agua(ataque _atks, string _nombre, stats _stats) : Pokemon(_atks, _nombre, _stats){
    //asignacion automatica de las debilidades y resistencias de la clase agua
    tipo = "agua";
    debilidades = "16";
    resistencias = "023";
}

Hierva::Hierva(ataque _atks, string _nombre, stats _stats) : Pokemon(_atks, _nombre, _stats){
    //asignacion automatica de las debilidades y resistencias de la clase hierva
    tipo = "hierva";
    debilidades = "23";
    resistencias = "016";
}


StrAtaque Simulador::solicitarMovimiento(ataque _ataques, string nombre){
    StrAtaque atkretornado; //variable usada para hacer return acorde al ataque seleccionado por el usuario
    int n1,n2,n3,n4;
    /*ints que reciben un char tipo del struct ataque, lo pasan a numeros y luego usan el arreglo de strings para imprimir el tipo
    a la par del ataque, para que el usuario sepa diferenciar de que tipo es cada ataque.*/
    n1 = atoi(&_ataques[0].tipo);
    n2 = atoi(&_ataques[1].tipo);
    n3 = atoi(&_ataques[2].tipo);
    n4 = atoi(&_ataques[3].tipo);

    //impresion de los ataques a seleccionar
    cout<<"Seleccione un ataque para el pokemon: "<<nombre<<endl;
    cout<<"1- "<<_ataques[0].nombre<<" ("<<tipoAtk[n1]<<") "<<endl;
    cout<<"2- "<<_ataques[1].nombre<<" ("<<tipoAtk[n2]<<") "<<endl;
    cout<<"3- "<<_ataques[2].nombre<<" ("<<tipoAtk[n3]<<") "<<endl;
    cout<<"4- "<<_ataques[3].nombre<<" ("<<tipoAtk[n4]<<") "<<endl;
    cout<<"--------------------------------------------------------------------------"<<endl;
    //validacion de la entrada del usuario.
    int op;
    double v, intpart;
    cin>>v;
    while(cin.fail()||modf(v, &intpart)!=0||v<1||v>4){
        cin.clear();
        cin.ignore(123, '\n');
        cout<<"ha ingresado un valor incorrecto, por favor vuelva a ingresar una opcion:"<<endl;
        cin>>v;
    }
    op=(int)v;
    //switch para retornar el ataque elegido por el usuario.
    switch(op){
        case 1:
            atkretornado = _ataques[0];
            break;
        case 2:
            atkretornado = _ataques[1];
            break;
        case 3:
            atkretornado = _ataques[2];
            break;
        case 4:
            atkretornado = _ataques[3];
            break;
        default:
            cout<<"ha ingresado un valor incorrecto."<<endl;
            break;
    }
    //retorno del ataque seleccionado
    return atkretornado;
}

void Simulador::iniciarBatalla(Pokemon& pkm1, Pokemon& pkm2){
    short int i=1; //short int usada como contador de turnos, para hacer un cout indicando el numero de turno.
    while(pkm1.getVida()!=0&&pkm2.getVida()!=0){
        system("cls"); //para limpiar la batalla a la hora de un nuevo turno
        //cout que indica el turno, y el pokemon que esta usando cada jugador
        cout<<"---------------------------------TURNO "<<i<<"----------------------------------"<<endl;
        cout<<"Pokemon actual del jugador 1: "<<pkm1.getNombre()<<endl;
        cout<<"Pokemon actual del jugador 2: "<<pkm2.getNombre()<<endl;
        cout<<"--------------------------------------------------------------------------"<<endl;
        /*ifs y else ifs que revisan la velocidad de ambos pokemon, y realizan el orden de ataques segun su velocidad*/
        if(pkm1.getVelocidad()>pkm2.getVelocidad()){
            cout<<"El pokemon "<<pkm1.getNombre()<<" es mas rapido y ataca primero!"<<endl;
            pkm1.atacar(solicitarMovimiento(pkm1.getAtaques(), pkm1.getNombre()), pkm2, pkm1.getAtaque());
            //verificacion de que el pokemon que recibio un ataque no haya caido en combate
            if(pkm2.getVida()!=0){
                pkm2.atacar(solicitarMovimiento(pkm2.getAtaques(), pkm2.getNombre()), pkm1, pkm2.getAtaque());
            }
        }
        else if (pkm1.getVelocidad()<pkm2.getVelocidad()){
            cout<<"El pokemon "<<pkm2.getNombre()<<" es mas rapido y ataca primero!"<<endl;
            pkm2.atacar(solicitarMovimiento(pkm2.getAtaques(), pkm2.getNombre()), pkm1, pkm2.getAtaque());
            //verificacion de que el pokemon que recibio un ataque no haya caido en combate
            if(pkm1.getVida()!=0){
                pkm1.atacar(solicitarMovimiento(pkm1.getAtaques(), pkm1.getNombre()), pkm2, pkm1.getAtaque());
            }
        }
        //si ambos pokemon tienen la misma velocidad, se elige de manera aleatoria el primer pokemon a atacar, usando la funcion srand()
        else if (pkm1.getVelocidad()==pkm2.getVelocidad()){
            int n;
            srand(time(NULL));//genera un numero aleatorio
            n = 0 + rand() % (2);
            if(n==0){
                cout<<"Ambos pokemon son igual de rapidos, pero "<<pkm1.getNombre()<<" ataca primero!"<<endl;
                pkm1.atacar(solicitarMovimiento(pkm1.getAtaques(), pkm1.getNombre()), pkm2, pkm1.getAtaque());
                //verificacion de que el pokemon que recibio un ataque no haya caido en combate
                if(pkm2.getVida()!=0){
                    pkm2.atacar(solicitarMovimiento(pkm2.getAtaques(), pkm2.getNombre()), pkm1, pkm2.getAtaque());
                }
            }
            else if(n==1){
                cout<<"Ambos pokemon son igual de rapidos, pero "<<pkm2.getNombre()<<" ataca primero!"<<endl;
                pkm2.atacar(solicitarMovimiento(pkm2.getAtaques(), pkm2.getNombre()), pkm1, pkm2.getAtaque());
                //verificacion de que el pokemon que recibio un ataque no haya caido en combate
                if(pkm1.getVida()!=0){
                    pkm1.atacar(solicitarMovimiento(pkm1.getAtaques(), pkm1.getNombre()), pkm2, pkm1.getAtaque());
                }
            }
        }
        //cout de la vida de cada pokemon despues de atacarse
        cout<<pkm1.getNombre()<<" HP: "<<pkm1.getVida()<<endl;
        cout<<pkm2.getNombre()<<" HP: "<<pkm2.getVida()<<endl;
        //si la vida de un pokemon llega a 0, se imprime un mensaje indicando que jugador gano.
        if (pkm1.getVida()==0){
            cout<<pkm1.getNombre()<<" ya no puede combatir!"<<endl;
            cout<<pkm2.getNombre()<<" es el ganador!"<<endl;

        }
        if (pkm2.getVida()==0){
            cout<<pkm2.getNombre()<<" ya no puede combatir!"<<endl;
            cout<<pkm1.getNombre()<< " es el ganador!"<<endl;
        }
        cout<<"-------------------------------------------------------------------------"<<endl;
        //pausa del sistema para que se pueda leer lo que ha ocurrido antes de que se realice un system("cls")
        system("PAUSE");
        //incremento del contador de turnos
        i++;
    }
    //cuando un pokemon tiene 0 de vida y termina la batalla, se curan ambos pokemon.
    finalizarBatalla(pkm1, pkm2);
}

//metodo para curar dos pokemon, obtiene su vida total con la variable totalHP
void Simulador::finalizarBatalla(Pokemon& pkm1, Pokemon& pkm2){
    pkm1.setVida(pkm1.getTotalHP());
    pkm2.setVida(pkm2.getTotalHP());
    cout<<"ha terminado la batalla!"<<endl;
}

void Simulador::iniciarBatalla(pkmnTeam& team1, pkmnTeam& team2){
    short int i=1; //short int para el contador de turnos
    vector<string> derrotados1, derrotados2; //vector que contiene los nombres de los pokemon derrotados.
    system("cls"); //limpia la pantalla para mostrar ambos equipos
    //cout de cada equipo con sus stats
    cout<<"---------------------------------EQUIPO 1---------------------------------"<<endl;
     for(int i=0; i<team1.size(); i++){
        cout<<i+1<<"- "<<team1[i].getNombre();
        cout<<" HP: "<<team1[i].getTotalHP();
        cout<<" ATK: "<<team1[i].getAtaque();
        cout<<" SPD: "<<team1[i].getVelocidad()<<endl;
    }
    cout<<"---------------------------------EQUIPO 2---------------------------------"<<endl;
     for(int i=0; i<team2.size(); i++){
        cout<<i+1<<"- "<<team2[i].getNombre();
        cout<<" HP: "<<team2[i].getTotalHP();
        cout<<" ATK: "<<team2[i].getAtaque();
        cout<<" SPD: "<<team2[i].getVelocidad()<<endl;
    }
     cout<<"--------------------------------------------------------------------------"<<endl;
     system("PAUSE"); //pausa para que los jugadores puedan leer los equipos
    while(team1.empty()==false&&team2.empty()==false){
        system("cls"); //limpieza de la pantalla para cada turno
        short int a, b;
        //las ints a y b representan el ultimo pokemon de cada vector de equipos pokemon, siendo el pokemon que sera usado siempre hasta que caiga en combate
        a=team1.size()-1;
        b=team2.size()-1;
        //impresion del turno y de los pokemon actuales
        cout<<"---------------------------------TURNO "<<i<<"----------------------------------"<<endl;
        cout<<"Pokemon actual del equipo 1: "<<team1[a].getNombre()<<endl;
        cout<<"Pokemon actual del equipo 2: "<<team2[b].getNombre()<<endl;
        cout<<"--------------------------------------------------------------------------"<<endl;
        //impresion de los pokemon derrotados, en caso de que hayan pokemon derrotados.
        if(derrotados1.empty()==false){
            cout<<"Pokemon derrotados del equipo 1: ";
            for(int i=0; i<derrotados1.size(); i++){
                cout<<derrotados1[i];
                  if(derrotados1.size()==2){
                    if(i==0){
                        cout<<", ";
                    }
                }
            }
            cout<<endl;
        }
        if(derrotados2.empty()==false){
            cout<<"Pokemon derrotados del equipo 2: ";
            for(int i=0; i<derrotados2.size(); i++){
                cout<<derrotados2[i];
                if(derrotados2.size()==2){
                    if(i==0){
                        cout<<", ";
                    }
                }
            }
            cout<<endl;
        }
        cout<<"--------------------------------------------------------------------------"<<endl;
        //los pokemon atacan en orden dependiendo de su velocidad, el if y else if determinando en caso de que tengan velocidades diferentes.
        if(team1[a].getVelocidad()>team2[b].getVelocidad()){
            cout<<"El pokemon "<<team1[a].getNombre()<<" es mas rapido, ataca primero."<<endl;
            team1[a].atacar(solicitarMovimiento(team1[a].getAtaques(), team1[a].getNombre()), team2[b], team1[a].getAtaque());
            //verificacion de que el pokemon que recibio el ataque no haya caido en combate
            if(team2[b].getVida()!=0){
                team2[b].atacar(solicitarMovimiento(team2[b].getAtaques(), team2[b].getNombre()),team1[a], team2[b].getAtaque());
            }
        }
        else if (team1[a].getVelocidad()<team2[b].getVelocidad()){

            cout<<"El pokemon "<<team2[b].getNombre()<<" es mas rapido, ataca primero."<<endl;
            team2[b].atacar(solicitarMovimiento(team2[b].getAtaques(), team2[b].getNombre()), team1[a], team2[b].getAtaque());
            //verificacion de que el pokemon que recibio el ataque no haya caido en combate
            if(team1[a].getVida()!=0){
                team1[a].atacar(solicitarMovimiento(team1[a].getAtaques(), team1[a].getNombre()), team2[b], team1[a].getAtaque());
            }
        }
        //si los pokemon tienen diferente velocidad, atacan en orden aleatorio.
        else if (team1[a].getVelocidad()==team2[b].getVelocidad()){
            int n;
            srand(time(NULL));//genera un numero aleatorio
            n = 0 + rand() % (2);
            if(n==0){
                cout<<"Ambos pokemon tienen la misma velocidad, pero "<<team1[a].getNombre()<<" ataca primero!"<<endl;
                team1[a].atacar(solicitarMovimiento(team1[a].getAtaques(), team1[a].getNombre()), team2[b], team1[a].getAtaque());
                //verificacion de que el pokemon que recibio el ataque no haya caido en combate
                if(team2[b].getVida()!=0){
                    team2[b].atacar(solicitarMovimiento(team2[b].getAtaques(), team2[b].getNombre()), team1[a], team2[b].getAtaque());
                }
            }
            else if(n==1){

                cout<<"Ambos pokemon tienen la misma velocidad, pero "<<team2[b].getNombre()<<" ataca primero!"<<endl;
                team2[b].atacar(solicitarMovimiento(team2[b].getAtaques(), team2[b].getNombre()), team1[a], team2[b].getAtaque());
                //verificacion de que el pokemon que recibio el ataque no haya caido en combate
                if(team1[a].getVida()!=0){
                    team1[a].atacar(solicitarMovimiento(team1[a].getAtaques(), team1[a].getNombre()), team2[b], team1[a].getAtaque());
                }

            }
        }
        //impresion de la vida actual de cada pokemon luego de hacer los ataques
        cout<<team1[a].getNombre()<<" HP: "<<team1[a].getVida()<<endl;
        cout<<team2[b].getNombre()<<" HP: "<<team2[b].getVida()<<endl;

       /*couts en caso de que un pokemon del equipo 1 o 2 haya caido en combate. Cuando un pokemon cae en combate, es sacado del vector
       haciendo uso de la funcion pop_back(), para que cuando se use la funcion size() arriba use el siguiente pokemon.*/
        if(team1[a].getVida()==0&&team1.size()>1){
            cout<<"El pokemon "<<team1[a].getNombre()<<" del equipo 1 ha sido derrotado!"<<endl;
            derrotados1.push_back(team1[a].getNombre()); //inclusion del nombre del pokemon derrotado en el vector de strings derrotados1
            cout<<"El equipo 1 lanza a: "<<team1[a-1].getNombre()<<"!"<<endl;
            //curacion del pokemon derrotado
            finalizarBatalla(team1[a]);
            //retiro del pokemon debilitado con pop_back()
            team1.pop_back();
        }
        if(team2[b].getVida()==0&&team2.size()>1){
            cout<<"El pokemon "<<team2[b].getNombre()<<" del equipo 2 ha sido derrotado!"<<endl;
            derrotados2.push_back(team2[b].getNombre());  //inclusion del nombre del pokemon derrotado en el vector de strings derrotados2
            cout<<"El equipo 2 lanza a: "<<team2[b-1].getNombre()<<"!"<<endl;
            //curacion del pokemon derrotado
            finalizarBatalla(team2[b]);
            //retiro del pokemon debilitado con pop_back()
            team2.pop_back();
        }
        //cout en caso de que todos los pokemon de un equipo esten derrotados
        if(team1[a].getVida()==0){
            cout<<"El pokemon "<<team1[a].getNombre()<<" del equipo 1 ha sido derrotado!"<<endl;
            //curacion del ultimo pokemon derrotado del equipo 1
            finalizarBatalla(team1[a]);
            cout<<"El equipo 1 ya no cuenta con Pokemon aptos para combatir!"<<endl;
            cout<<"El equipo 2 es el ganador!"<<endl;
            //curacion del equipo ganador
            finalizarBatalla(team2);
            //retiro del pokemon debilitado
            team1.pop_back();
        }
        if(team2[b].getVida()==0){
            cout<<"El pokemon "<<team2[b].getNombre()<<" del equipo 2 ha sido derrotado!"<<endl;
            //curacion del ultimo pokemon derrotado del equipo 2
            finalizarBatalla(team2[b]);
            cout<<"El equipo 2 ya no cuenta con Pokemon aptos para combatir!"<<endl;
            cout<<"El equipo 1 es el ganador!"<<endl;
            //curacion del equipo ganador
            finalizarBatalla(team1);
            //retiro del pokemon debilitado
            team2.pop_back();
        }
        cout<<"-------------------------------------------------------------------------"<<endl;
        //pausa para que el usuario pueda leer todo lo que ocurrio dentro del turno
        system("PAUSE");
        i++; //incremento del contador de turnos
    }
}

//cura a un solo pokemon, usado en batallas multiples cuando un pokemon es debilitado pero la batalla sigue
void Simulador::finalizarBatalla(Pokemon& pkm){
    pkm.setVida(pkm.getTotalHP());
}

//cura a todos los pokemon de un equipo, usado cuando un equipo se declara ganador en una batalla multiple
void Simulador::finalizarBatalla(pkmnTeam& team){
    for(int i=0; i<team.size(); i++){
        team[i].setVida(team[i].getTotalHP());
    }
}


void Simulador::mostrarMenu(pkmnTeam& _pokedex){
    short int confirmacion = 1; //variable para verificar si el usuario desea realizar otra accion luego de una batalla pokemon.
    while(confirmacion==1){
    //impresion de las opciones del menu
    cout<<"------------------------------------------------------------------------"<<endl;
    cout<<endl<<"\tBienvenido al simulador de batallas de Pokemon."<<endl;
    cout<<"\t\t\tElija una opcion:"<<endl;
    cout<<"1- Iniciar una batalla"<<endl;
    cout<<"2- Salir del programa"<<endl;
    cout<<"------------------------------------------------------------------------"<<endl;
    //validacion de la entrada del usuario
    int op;
    double v, intpart;
    pkmnTeam team1, team2;
    cin>>v;
    while(cin.fail()||modf(v, &intpart)!=0||v<1||v>2){
        cin.clear();
        cin.ignore(123, '\n');
        cout<<"ha ingresado un valor incorrecto, por favor vuelva a ingresar una opcion:"<<endl;
        cin>>v;
    }
    op=(int)v;
    //switch con la entrada del usuario
    switch(op){
        case 1:
            system("cls");
            cout<<"--------------------------------------------------------------------------"<<endl;
            cout<<"-  \t\t\tElija una opcion de batalla:                     -"<<endl;
            cout<<"-  1- Batalla 1v1                                                        -"<<endl;
            cout<<"-  2- Batalla 2v2                                                        -"<<endl;
            cout<<"-  3- Batalla 3v3                                                        -"<<endl;
            cout<<"--------------------------------------------------------------------------"<<endl;
            //validacion de la entrada del usuario
            int op1;
            double x;
            cin>>x;

            while(cin.fail()||modf(x, &intpart)!=0||x<1||x>3){
                cin.clear();
                cin.ignore(123, '\n');
                cout<<"ha ingresado un valor incorrecto, por favor vuelva a ingresar una opcion:"<<endl;
                cin>>x;
            }
            op1=(int)x;
            switch(op1){
                case 1:
                    /*en caso de que el usuario desee realizar una batalla 1v1, el sistema le pedira que escoja un pokemon para el jugador 1
                    y luego para el jugador 2, dandole a escoger de una serie de numeros. si el usuario intenta escoger el mismo pokemon para
                    ambos jugadores le dira que no es posible.*/
                    system("cls");
                    //impresion de las opciones disponibles
                    cout<<"--------------------------------------------------------------------------"<<endl;
                    cout<<"Elija el pokemon para el jugador 1:"<<endl;
                    for(int i=0; i<_pokedex.size(); i++){
                        cout<<i+1<<"- "<<_pokedex[i].getNombre()<<" HP: "<<_pokedex[i].getTotalHP()<<" ATK: "<<_pokedex[i].getAtaque()<<" SPD: "<<_pokedex[i].getVelocidad()<<endl;
                    }
                    cout<<"--------------------------------------------------------------------------"<<endl;
                    //validacion de la entrada del usuario
                    int op2;
                    double z;
                    cin>>z;
                    while(cin.fail()||modf(z, &intpart)!=0||z<1||z>_pokedex.size()){
                        cin.clear();
                        cin.ignore(123, '\n');
                        cout<<"ha ingresado un valor incorrecto, por favor vuelva a ingresar una opcion:"<<endl;
                        cin>>z;
                    }
                    op2=(int)z;
                    //impresion de las opciones disponibles
                    cout<<"--------------------------------------------------------------------------"<<endl;
                    cout<<"Elija el pokemon para el jugador 2:"<<endl;
                    for(int i=0; i<_pokedex.size(); i++){
                        if(i!=op2-1){
                            cout<<i+1<<"- "<<_pokedex[i].getNombre()<<" HP: "<<_pokedex[i].getTotalHP()<<" ATK: "<<_pokedex[i].getAtaque()<<" SPD: "<<_pokedex[i].getVelocidad()<<endl;
                        }
                    }
                    cout<<"--------------------------------------------------------------------------"<<endl;
                    //validacion de la entrada del usuario
                    int op3;
                    double a;
                    cin>>a;
                    while(cin.fail()||modf(a, &intpart)!=0||a<1||a>_pokedex.size()||a==op2){
                        cin.clear();
                        cin.ignore(123, '\n');
                        cout<<"ha ingresado un valor incorrecto o el pokemon ya ha sido elegido, por favor vuelva a ingresar una opcion:"<<endl;
                        cin>>a;
                    }
                    op3=(int)a;
                    //inicio de la batalla con los pokemon seleccionados por el usuario, siendo pasados directamente desde el vector pokedex.
                    iniciarBatalla(_pokedex[op2-1],_pokedex[op3-1]);
                    break;
                case 2:
                    //en caso de que el usuario escoja una batalla 2v2, el sistema pedira los primeros dos pokemon de cada equipo, no admitira repetidos.
                    system("cls");
                    //impresion de las opciones
                    cout<<"--------------------------------------------------------------------------"<<endl;
                    cout<<"Elija el primer pokemon para el equipo 1:"<<endl;
                     for(int i=0; i<_pokedex.size(); i++){
                        cout<<i+1<<"- "<<_pokedex[i].getNombre()<<" HP: "<<_pokedex[i].getTotalHP()<<" ATK: "<<_pokedex[i].getAtaque()<<" SPD: "<<_pokedex[i].getVelocidad()<<endl;
                    }
                    cout<<"--------------------------------------------------------------------------"<<endl;
                    //validacion de la entrada del usuario
                    double q, w;
                    int op4, op5;
                    cin>>q;
                    while(cin.fail()||modf(q, &intpart)!=0||q<1||q>_pokedex.size()){
                        cin.clear();
                        cin.ignore(123, '\n');
                        cout<<"ha ingresado un valor incorrecto, por favor vuelva a ingresar una opcion:"<<endl;
                        cin>>q;
                    }
                    op4=(int)q;
                    //adicion del pokemon seleccionado al vector del equipo 1
                    team1.push_back(_pokedex[op4-1]);
                    //impresion de las opciones
                    cout<<"--------------------------------------------------------------------------"<<endl;
                    cout<<"Elija el segundo pokemon para el equipo 1: "<<endl;
                    for(int i=0; i<_pokedex.size(); i++){
                        if(i!=op4-1){
                            cout<<i+1<<"- "<<_pokedex[i].getNombre()<<" HP: "<<_pokedex[i].getTotalHP()<<" ATK: "<<_pokedex[i].getAtaque()<<" SPD: "<<_pokedex[i].getVelocidad()<<endl;
                        }
                    }
                    cout<<"--------------------------------------------------------------------------"<<endl;
                    //validacion de la entrada del usuario, con validacion extra para rechazar repetidos.
                    cin>>w;
                    while(cin.fail()||modf(w, &intpart)!=0||w<1||w>_pokedex.size()||w==q){
                        cin.clear();
                        cin.ignore(123, '\n');
                        cout<<"ha ingresado un valor incorrecto o el pokemon ya ha sido elegido, por favor vuelva a ingresar una opcion:"<<endl;
                        cin>>w;
                    }
                    op5=(int)w;
                    //adicion del pokemon seleccionado al vector del equipo 1
                    team1.push_back(_pokedex[op5-1]);
                    //en este punto el programa empieza a hacer lo mismo pero para los pokemon del equipo 2.
                    cout<<"--------------------------------------------------------------------------"<<endl;
                    cout<<"Elija el primer pokemon para el equipo 2: "<<endl;
                    for(int i=0; i<_pokedex.size(); i++){
                        if(i!=op4-1&&i!=op5-1){
                            cout<<i+1<<"- "<<_pokedex[i].getNombre()<<" HP: "<<_pokedex[i].getTotalHP()<<" ATK: "<<_pokedex[i].getAtaque()<<" SPD: "<<_pokedex[i].getVelocidad()<<endl;
                        }
                    }
                    cout<<"--------------------------------------------------------------------------"<<endl;
                    double e;
                    int op6;
                    cin>>e;

                    while(cin.fail()||modf(e, &intpart)!=0||e<1||e>_pokedex.size()||e==q||e==w){
                        cin.clear();
                        cin.ignore(123, '\n');
                        cout<<"ha ingresado un valor incorrecto o el pokemon ya ha sido elegido, por favor vuelva a ingresar una opcion:"<<endl;
                        cin>>e;
                    }
                    op6=(int)e;
                    team2.push_back(_pokedex[op6-1]);
                    double r;
                    int op7;
                    cout<<"--------------------------------------------------------------------------"<<endl;
                    cout<<"Elija el segundo pokemon para el equipo 2:"<<endl;
                    for(int i=0; i<_pokedex.size(); i++){
                        if(i!=op4-1&&i!=op5-1&&i!=op6-1){
                            cout<<i+1<<"- "<<_pokedex[i].getNombre()<<" HP: "<<_pokedex[i].getTotalHP()<<" ATK: "<<_pokedex[i].getAtaque()<<" SPD: "<<_pokedex[i].getVelocidad()<<endl;
                        }
                    }
                    cout<<"--------------------------------------------------------------------------"<<endl;
                    cin>>r;

                    while(cin.fail()||modf(r, &intpart)!=0||r<1||r>_pokedex.size()||r==q||r==w||r==e){
                        cin.clear();
                        cin.ignore(123, '\n');
                        cout<<"ha ingresado un valor incorrecto o el pokemon ya ha sido elegido, por favor vuelva a ingresar una opcion:"<<endl;
                        cin>>r;
                    }
                    op7=(int)r;
                    team2.push_back(_pokedex[op7-1]);
                    iniciarBatalla(team1, team2);
                    break;
                case 3:
                    //en caso de que el usuario elija la opcion 3v3, pedira los 3 pokemon de cada equipo, no admitira repetidos.
                    //la manera en que hace esto es exactamente igual a los dos anteriores cases.
                    system("cls");
                    cout<<"--------------------------------------------------------------------------"<<endl;
                    cout<<"Elija el primer pokemon para el equipo 1:"<<endl;
                     for(int i=0; i<_pokedex.size(); i++){
                        cout<<i+1<<"- "<<_pokedex[i].getNombre()<<" HP: "<<_pokedex[i].getTotalHP()<<" ATK: "<<_pokedex[i].getAtaque()<<" SPD: "<<_pokedex[i].getVelocidad()<<endl;
                    }
                    cout<<"--------------------------------------------------------------------------"<<endl;
                    double t,y,u,i,o,p;
                    int op8, op9,op10,op11,op12,op13;
                    cin>>t;

                    while(cin.fail()||modf(t, &intpart)!=0||t<1||t>_pokedex.size()){
                        cin.clear();
                        cin.ignore(123, '\n');
                        cout<<"ha ingresado un valor incorrecto, por favor vuelva a ingresar una opcion:"<<endl;
                        cin>>t;
                    }
                    op8=(int)t;
                    team1.push_back(_pokedex[op8-1]);
                    cout<<"--------------------------------------------------------------------------"<<endl;
                    cout<<"Elija el segundo pokemon para el equipo 1: "<<endl;
                    for(int i=0; i<_pokedex.size(); i++){
                        if(i!=op8-1){
                            cout<<i+1<<"- "<<_pokedex[i].getNombre()<<" HP: "<<_pokedex[i].getTotalHP()<<" ATK: "<<_pokedex[i].getAtaque()<<" SPD: "<<_pokedex[i].getVelocidad()<<endl;
                        }
                    }
                    cout<<"--------------------------------------------------------------------------"<<endl;
                    cin>>y;
                    while(cin.fail()||modf(y, &intpart)!=0||y<1||y>_pokedex.size()||y==t){
                        cin.clear();
                        cin.ignore(123, '\n');
                        cout<<"ha ingresado un valor incorrecto o el pokemon ya ha sido elegido, por favor vuelva a ingresar una opcion:"<<endl;
                        cin>>y;
                    }
                    op9=(int)y;
                    team1.push_back(_pokedex[op9-1]);
                    cout<<"--------------------------------------------------------------------------"<<endl;
                    cout<<"Elija el tercer pokemon para el equipo 1: "<<endl;
                    for(int i=0; i<_pokedex.size(); i++){
                        if(i!=op9-1&&i!=op8-1){
                            cout<<i+1<<"- "<<_pokedex[i].getNombre()<<" HP: "<<_pokedex[i].getTotalHP()<<" ATK: "<<_pokedex[i].getAtaque()<<" SPD: "<<_pokedex[i].getVelocidad()<<endl;
                        }
                    }
                    cout<<"--------------------------------------------------------------------------"<<endl;
                    cin>>u;

                    while(cin.fail()||modf(u, &intpart)!=0||u<1||u>_pokedex.size()||u==y||u==t){
                        cin.clear();
                        cin.ignore(123, '\n');
                        cout<<"ha ingresado un valor incorrecto o el pokemon ya ha sido elegido, por favor vuelva a ingresar una opcion:"<<endl;
                        cin>>u;
                    }
                    op10=(int)u;
                    team1.push_back(_pokedex[op10-1]);
                    cout<<"--------------------------------------------------------------------------"<<endl;
                    cout<<"Elija el primer pokemon para el equipo 2: "<<endl;
                    for(int i=0; i<_pokedex.size(); i++){
                        if(i!=op9-1&&i!=op10-1&&i!=op8-1){
                            cout<<i+1<<"- "<<_pokedex[i].getNombre()<<" HP: "<<_pokedex[i].getTotalHP()<<" ATK: "<<_pokedex[i].getAtaque()<<" SPD: "<<_pokedex[i].getVelocidad()<<endl;
                        }
                    }
                    cout<<"--------------------------------------------------------------------------"<<endl;
                    cin>>i;
                    while(cin.fail()||modf(i, &intpart)!=0||i<1||i>_pokedex.size()||i==t||i==y||i==u){
                        cin.clear();
                        cin.ignore(123, '\n');
                        cout<<"ha ingresado un valor incorrecto o el pokemon ya ha sido elegido, por favor vuelva a ingresar una opcion:"<<endl;
                        cin>>i;
                    }
                    op11=(int)i;
                    team2.push_back(_pokedex[op11-1]);
                    cout<<"--------------------------------------------------------------------------"<<endl;
                    cout<<"Elija el segundo pokemon para el equipo 2:"<<endl;
                    for(int i=0; i<_pokedex.size(); i++){
                        if(i!=op8-1&&i!=op9-1&&i!=op10-1&&i!=op11-1){
                            cout<<i+1<<"- "<<_pokedex[i].getNombre()<<" HP: "<<_pokedex[i].getTotalHP()<<" ATK: "<<_pokedex[i].getAtaque()<<" SPD: "<<_pokedex[i].getVelocidad()<<endl;
                        }
                    }
                    cout<<"--------------------------------------------------------------------------"<<endl;
                    cin>>o;

                    while(cin.fail()||modf(o, &intpart)!=0||o<1||o>_pokedex.size()||o==t||o==y||o==u||o==i){
                        cin.clear();
                        cin.ignore(123, '\n');
                        cout<<"ha ingresado un valor incorrecto o el pokemon ya ha sido elegido, por favor vuelva a ingresar una opcion:"<<endl;
                        cin>>o;
                    }
                    op12=(int)o;
                    team2.push_back(_pokedex[op12-1]);
                    cout<<"--------------------------------------------------------------------------"<<endl;
                    cout<<"Elija el tercer pokemon para el equipo 2:"<<endl;
                    for(int i=0; i<_pokedex.size(); i++){
                        if(i!=op8-1&&i!=op9-1&&i!=op10-1&&i!=op11-1&&i!=op12-1){
                            cout<<i+1<<"- "<<_pokedex[i].getNombre()<<" HP: "<<_pokedex[i].getTotalHP()<<" ATK: "<<_pokedex[i].getAtaque()<<" SPD: "<<_pokedex[i].getVelocidad()<<endl;
                        }
                    }
                    cout<<"--------------------------------------------------------------------------"<<endl;
                    cin>>p;

                    while(cin.fail()||modf(p, &intpart)!=0||o<1||o>_pokedex.size()||p==t||p==y||p==u||p==i||p==o){
                        cin.clear();
                        cin.ignore(123, '\n');
                        cout<<"ha ingresado un valor incorrecto o el pokemon ya ha sido elegido, por favor vuelva a ingresar una opcion:"<<endl;
                        cin>>p;
                    }
                    op13=(int)p;
                    team2.push_back(_pokedex[op13-1]);
                    iniciarBatalla(team1,team2);
                    break;
                default:
                    cout << "Ha ingresado un valor invalido"<< endl;
                    break;
            }
        //break del caso 1 del menu principal
        break;
        case 2:
            //caso 2 usado para cerrar el programa
            exit(0);
            break;
        default:
            cout<<"ha ingresado un valor invalido"<<endl;
            break;
    }
        //confirmacion si el usuario desea realizar otra accion
        cout<<"--------------------------------------------------------------------------"<<endl;
        cout << "¿Desea hacer otra batalla pokemon?"<<endl;
        cout<< "1- Si || Cualquier otra tecla - No"<<endl;
        cin>>confirmacion;
        //limpieza de la pantalla
        system("cls");
    }

}
