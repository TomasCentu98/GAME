#include "../Includes/MANAGER.h"
#include "../Includes/PANTALLA.h"
#include "MAPA_PELEA.h"
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <cstring>
using namespace std;

void app() {

   PANTALLA pantalla;

   pantalla.gameLoop();

}

// lee un .txt y copia la lista de numeros que tenga dentro
std::vector<int> copiarDeArchivo(const std::string& nombreArchivo) {
    std::ifstream archivo(nombreArchivo);
    std::vector<int> listaCopiada;
    int numero;

    if (!archivo.is_open()) {
        return listaCopiada;
    }

    while (archivo >> numero) {
        listaCopiada.push_back(numero);
    }

    archivo.close();
    return listaCopiada;

}

void patrullar(ENEMIGO &obj, sf::Vector2f posIzq, sf::Vector2f posDer) {
    int nuevaPosX;
    int posY = obj.getSprite().getPosition().y;

    if (obj.getDireccionMov()) {
        obj.setVelocidad(2,0);
        nuevaPosX = obj.getSprite().getPosition().x + obj.getVelocidad().x;
        if (obj.getSprite().getPosition().x >= posDer.x) {
            obj.setDirrecionMov(false);
        }
    } else {
        obj.setVelocidad(-2,0);
        nuevaPosX = obj.getSprite().getPosition().x + obj.getVelocidad().x;
        if (obj.getSprite().getPosition().x <= posIzq.x) {
            obj.setDirrecionMov(true);
        }
    }

    obj.posicionar(nuevaPosX, posY);
}

void eventoBatalla(ENEMIGO &rival, HEROE &enlace, sf::RenderWindow& window){

    const sf::Vector2f posEnlace = enlace.getSprite().getPosition();
    const sf::Vector2f posR = rival.getSprite().getPosition();
    enlace.setBatallando(true);
    enlace.posicionar(250.f, 250.f);
    rival.posicionar(450.f, 250.f);

    bool turnoH = true;
    bool turnoE = false;
    bool botonApretado = false;
    sf::Clock relojTurno;
    sf::Time tiempoEspera = sf::seconds(0.5f);
    bool esperando = false;


    MAPA_PELEA mapita;
        mapita.setTextureFondo("IMG/fondoPelea.png");
        mapita.setTextureHud("IMG/HUD_batalla.png");
        mapita.iniciar();

    const std::string vidaMaxH = std::to_string((int)enlace.getVida());
    const std::string manaMax = std::to_string(enlace.getMana());
    const std::string vidaMaxEneg = std::to_string((int)rival.getVida());

    while (rival.getVida() > 0) {

        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>()) window.close();
        }

        if (!window.isOpen()) break;
        if (enlace.getVida() <= 0) break;

        std::string textVE = "Goblin: \n" + std::to_string((int)rival.getVida()) + " | " + vidaMaxEneg;
        mapita._vidaEnemigo.setString(textVE);

        std::string text1 = "Enlace: \n" + std::to_string((int)enlace.getVida()) + " | " + vidaMaxH;
        std::string text2 = "\n" + std::to_string(enlace.getMana()) + " | " + manaMax;
        std::string textHeroe = text1 + text2;
        mapita._vidaHeroe.setString(textHeroe);

        const int decisionRival = (rand() % 2) + 1;

        window.clear(sf::Color::Black);

        if (turnoH && !esperando) {
            if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
                if (!botonApretado ) {
                    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                    botonApretado = true;

                    if (mapita.getRectangles()[4].getGlobalBounds().contains({(float)mousePos.x , (float)mousePos.y})) {
                        mapita._textoExplicativo.setString(" PEGANDO ");
                        enlace.golpear(rival);
                    }
                    if (mapita.getRectangles()[5].getGlobalBounds().contains({(float)mousePos.x , (float)mousePos.y})) {
                        mapita._textoExplicativo.setString(" DEFENDIENDO ");
                        enlace.setDefensa(true);
                    }
                    if (mapita.getRectangles()[6].getGlobalBounds().contains({(float)mousePos.x , (float)mousePos.y})) {
                        mapita._textoExplicativo.setString(" CURANDO ");
                        enlace.curar();
                    }
                    if (mapita.getRectangles()[7].getGlobalBounds().contains({(float)mousePos.x , (float)mousePos.y})) {
                        mapita._textoExplicativo.setString(" PIU PIU ");
                        enlace.hechizo(rival);
                    }

                    relojTurno.restart();
                    esperando = true;
                } else {botonApretado = false;}
            }
        }

        if (turnoH && esperando && relojTurno.getElapsedTime() >= tiempoEspera) {
            turnoH = false;
            turnoE = true;
            esperando = false;
        }

        if (turnoE && !esperando) {
            if (decisionRival == 1) {
                mapita._textoExplicativo.setString(" ENEMIGO PEGANDO ");
                rival.golpear(enlace);
            } else {
                mapita._textoExplicativo.setString(" ENEMIGO DEFENDIDO ");
                rival.setDefensa(true);
            }

            relojTurno.restart();
            esperando = true;
            turnoE = false;
        }

        if (!turnoE && esperando && relojTurno.getElapsedTime() >= tiempoEspera) {
            turnoH = true;
            turnoE = false;
            esperando = false;
        }

        for (auto cuadro : mapita.getRectangles()) {
            window.draw(cuadro);
        }

        window.draw(mapita._vidaEnemigo);
        window.draw(mapita._vidaHeroe);
        window.draw(enlace);
        window.draw(rival);
        window.draw(mapita._textoExplicativo);

        window.display();

    }

    enlace.setVida(100.f);
    enlace.setMana(100);
    enlace.setBatallando(false);
    enlace.posicionar(posEnlace.x, posEnlace.y);
    rival.posicionar(posR.x, posR.y);
}


std::string generarDialogo(int numero){
    FILE *dialogo;


    int dialogoRandom = (rand()%3)+1;

    if(numero==0)dialogo = fopen("DialogosEnemigo.txt","rb");
    if(numero==1)dialogo = fopen("DialogosHeroe.txt","rb");
    if(dialogo==nullptr){
        exit(1);
    }
    char prueba[200]={};
    int contador=1;

    while(fgets(prueba,sizeof(prueba),dialogo)){
        if(contador==dialogoRandom){
            break;
        }
        contador++;
        memset(prueba, '\0', sizeof (prueba));
    };

    fclose(dialogo);
    std::string texto(prueba);
    return texto;
};

/*std::string generarDialogoHeroe(){

};
*/
