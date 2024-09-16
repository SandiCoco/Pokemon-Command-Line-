/*Edwin Daniel Lizama Garcia LG20012
  Diego Paolo Morales Lopez ML20011
  Carlos Efrain Rodriguez Saravia RS20047
  Roberto Hernan Lainez Trejo LT20007*/
#include <iostream>
#include "Pokemon.h"
#include <vector>

using namespace pocketMonsters; 
using namespace std;

int main(int argc, char const *argv[])
{   
    StrAtaque araniaso,placaje,golpeCabeza, burbujas,bombaAgua,latigocepa,tormentaHojas,energyBall,ascuas,
    lanzaLlamas, golpeHielo,
    tumbaRocas, 
    tierraViva,bofeton,
    golpeTrueno;
    //Creamos los ataques y les asignamos su nombre, poder y el tipo 0(agua),1(hierva),2(fuego),3(hielo)
    //4(roca),5(tierra),6(electrico),7(Normal)
    burbujas.nombre="burbujas"; burbujas.poder=30; burbujas.tipo='0';
    bombaAgua.nombre="Bomba de agua"; bombaAgua.poder=40; bombaAgua.tipo='0';

    tormentaHojas.nombre="Tormenta de hojas"; tormentaHojas.poder=50; tormentaHojas.tipo='1';
    latigocepa.nombre="Latigo cepa"; latigocepa.poder=20; latigocepa.tipo='1';
    energyBall.nombre="Energibola"; energyBall.poder=35; energyBall.tipo='1';

    ascuas.nombre="ascuas"; ascuas.poder=30; ascuas.tipo='2';
    lanzaLlamas.nombre="Lanzallamas"; lanzaLlamas.poder=40; lanzaLlamas.tipo='2';

    golpeHielo.nombre="Golpe hielo"; golpeHielo.poder=45; golpeHielo.tipo='3';

    tumbaRocas.nombre="Tumba rocas"; tumbaRocas.poder=40; tumbaRocas.tipo='4';
    
    tierraViva.nombre="Tierra viva"; tierraViva.poder=50; tierraViva.tipo='5';
    bofeton.nombre="Bofeton de lodo"; bofeton.poder=25; bofeton.tipo='5';

    golpeTrueno.nombre="Golpe trueno"; golpeTrueno.poder=45; golpeTrueno.tipo='6';

    placaje.nombre="placaje";  placaje.poder=25;  placaje.tipo='7';
    golpeCabeza.nombre="Golpe cabeza"; golpeCabeza.poder=40; golpeCabeza.tipo='7';
    araniaso.nombre="Araniaso"; araniaso.poder=40; araniaso.tipo='7';
    
    //creacion de los diferentes sets de stats que son usados en los pokemon
    stats stpkm1, stpkm2, stpkm3, stpkm4, stpkm5,stpkm6;
    stpkm1.ATK=30;  stpkm1.SPD=100; stpkm1.HP=150;
    stpkm2.ATK=40;  stpkm2.SPD=90;  stpkm2.HP=160;
    stpkm3.ATK=45;  stpkm3.SPD=50;  stpkm3.HP=200; 
    stpkm4.ATK=35;  stpkm4.SPD=70;  stpkm4.HP=180;
    stpkm5.ATK=60;  stpkm5.SPD=70;  stpkm5.HP=100;
    stpkm6.ATK=50;  stpkm6.SPD=75;  stpkm6.HP=120;

    //creacion de diferentes vectores que contienen los ataques de cada pokemon
    ataque atks, atks2, atks3,atks4,atks5,atks6,atks7,atks8,atks9;
    atks.push_back(placaje);   atks.push_back(ascuas);       atks.push_back(golpeTrueno);    atks.push_back(tumbaRocas);
    atks2.push_back(burbujas); atks2.push_back(placaje);     atks2.push_back(golpeHielo);    atks2.push_back(golpeCabeza);
    atks3.push_back(placaje);  atks3.push_back(latigocepa);  atks3.push_back(bofeton);       atks3.push_back(tormentaHojas);
    atks4.push_back(placaje);  atks4.push_back(lanzaLlamas); atks4.push_back(ascuas);        atks4.push_back(golpeCabeza);
    atks5.push_back(burbujas); atks5.push_back(placaje);     atks5.push_back(bombaAgua);     atks5.push_back(golpeHielo);
    atks6.push_back(placaje);  atks6.push_back(latigocepa);  atks6.push_back(tormentaHojas); atks6.push_back(tumbaRocas);
    atks7.push_back(placaje);  atks7.push_back(burbujas);    atks7.push_back(bombaAgua);     atks7.push_back(tierraViva);
    atks8.push_back(placaje);  atks8.push_back(golpeCabeza); atks8.push_back(energyBall);    atks8.push_back(tormentaHojas);
    atks9.push_back(araniaso); atks9.push_back(ascuas);      atks9.push_back(lanzaLlamas);   atks9.push_back(tumbaRocas);

    //creacion de los objetos de la clase fuego, agua y hierva respectivamente para los pokemon. cada uno recibe ataques, nombre y stats
    Fuego Charmander (atks, "Charmander", stpkm2 );
    Fuego cyndaquill (atks4, "Cyndaquil", stpkm1);
    Fuego torchic    (atks9,"Torchic",stpkm4);
    Agua squirtle    (atks2, "Squirtle", stpkm1);
    Agua mudkip      (atks7,"Mudkip",stpkm2);
    Agua totodile    (atks5,"Totodile",stpkm5);
    Hierva bulbasaur (atks3, "Bulbasaur", stpkm3);
    Hierva treecko   (atks8,"Treecko",stpkm6);
    Hierva chikorita (atks6,"Chikorita",stpkm6);
    

    //creacion de un objeto de la clase simulador
    Simulador sim;
    //creacion de la pokedex, usando push_back() para meter todos los pokemon creados en un solo vector
    pkmnTeam pokedex;
    pokedex.push_back(Charmander);
    pokedex.push_back(cyndaquill);
    pokedex.push_back(torchic);
    pokedex.push_back(squirtle);
    pokedex.push_back(totodile);
    pokedex.push_back(mudkip);
    pokedex.push_back(bulbasaur);
    pokedex.push_back(chikorita);
    pokedex.push_back(treecko);

    system("cls");
    //uso de la funcion mostrarMenu() de la clase simulador, recibiendo el vector pokedex que contiene todos los pokemon como parametro.
    sim.mostrarMenu(pokedex);

    
    return 0;
} 
