#include "HEROE.h"
#include "MAPA.h"
#include "MAPA_PELEA.h"
#include "PANTALLA.h"
#include "MANAGER.h"
#include <SFML/Audio.hpp>
#include <cstring>

PANTALLA::PANTALLA() {}

// INICIO DE JUEGO
void PANTALLA::gameLoop(HEROE &enlace, sf::RenderWindow &window) {
    sf::Music MusicaJuego;
    MusicaJuego.openFromFile("Musica/Mundo.ogg");
    MusicaJuego.play();
    MusicaJuego.setLooping(true);
    MusicaJuego.setVolume(3);

    // MAPA
    MAPA mapa(_ANCHO, _LARGO);
    sf::Clock relojito;
    sf::Clock relojitoEnemigo;
    enlace.posicionar(561 , 432);

    NPC vagabundo;
    vagabundo.setSprite("IMG/cirujano.png");
    vagabundo.setNombre("charly");
    vagabundo.posicionar(250, 200);

    sf::RectangleShape arbol({32.f, 64.f});
    sf::Texture textArbol("IMG/Arbolito.png");
    arbol.setTexture(&textArbol);
    arbol.setPosition({260.f, 150.f});

    NPC eneg1pan1;
    eneg1pan1.setSprite("IMG/goblin.png");
    eneg1pan1.setNombre("pepeASD");

    NPC eneg2pan1;
    eneg2pan1.setSprite("IMG/goblin.png");
    eneg2pan1.setNombre("pepeZXC");

    NPC eneg1pan2;
    eneg1pan2.setSprite("IMG/goblin.png");
    eneg1pan2.setNombre("pepeRWER");

    NPC eneg2pan2;
    eneg2pan2.setSprite("IMG/goblin.png");
    eneg2pan2.setNombre("pepeTRFS");

    NPC jefe;
    jefe.setSprite("IMG/DragFrente2.png");
    jefe.setNombre("pepeCAQSD");

    bool tuto = true;
    bool enemigosCreadosPan1 = false;
    bool enemigosCreadosPan2 = false;
    bool enemigosCreadosPan3 = false;

    while (window.isOpen() && enlace.vivo) {

        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>()) window.close();
        }

        // MOVIMIENTO DE JUGADOR
        enlace.actualizar(mapa, _ANCHO, _LARGO, relojito);

        if (!enlace.getBatallando())
        {
            if (!enlace.estaColisionando(eneg1pan1.getSprite().getPosition()))
                eneg1pan1.patrullar(300, 500, relojitoEnemigo);

            if (enlace.estaColisionando(eneg1pan1.getSprite().getPosition()))
            {
                if(eneg1pan1.getVida() > 0) cortinaInicio(window);
                MusicaJuego.stop();
                pelea(eneg1pan1, enlace, window);
                MusicaJuego.play();
            }

            if (!enlace.estaColisionando(eneg2pan1.getSprite().getPosition()))
                eneg2pan1.patrullar(250, 500, relojitoEnemigo);

            if (enlace.estaColisionando(eneg2pan1.getSprite().getPosition()))
            {
                if(eneg2pan1.getVida() > 0) cortinaInicio(window);
                MusicaJuego.stop();
                pelea(eneg2pan1, enlace, window);
                MusicaJuego.play();
            }

            if (!enlace.estaColisionando(eneg1pan2.getSprite().getPosition()))
                eneg1pan2.patrullar(250, 600, relojitoEnemigo);

            if (enlace.estaColisionando(eneg1pan2.getSprite().getPosition()))
            {
                if(eneg1pan2.getVida() > 0) cortinaInicio(window);
                MusicaJuego.stop();
                pelea(eneg1pan2, enlace, window);
                MusicaJuego.play();
            }

            if (!enlace.estaColisionando(eneg2pan2.getSprite().getPosition()))
                eneg2pan2.patrullar(250, 700, relojitoEnemigo);

            if (enlace.estaColisionando(eneg2pan2.getSprite().getPosition()))
            {
                if(eneg2pan2.getVida() > 0) cortinaInicio(window);
                MusicaJuego.stop();
                pelea(eneg2pan2, enlace, window);
                MusicaJuego.play();
            }
        }

        // CONTROLA EL PASO DE MAPAS
        mapa.chequeoPasoDeMapa(enlace);



        window.clear(sf::Color::Black);
        if(!enlace.vivo){
            break;
        }
        window.draw(mapa);


        if (tuto) {
            window.draw(vagabundo);
            window.draw(arbol);

            if (enlace.estaColisionando(vagabundo.getSprite().getPosition())) {
                tutorial(window, enlace, mapa);
            }
        }

        window.draw(enlace);

        // PARA REEUBICAR ENEMIGOS AL CAMBIAR MAPA
        if(mapa.getMapaActual() == 1 && !enemigosCreadosPan1)
        {
            vagabundo.posicionar(-32,-32);
            arbol.setPosition({-32,-32});
            jefe.posicionar(-32,-32);
            eneg1pan2.posicionar(-32,-32);
            eneg2pan2.posicionar(-32,-32);
            eneg1pan1.posicionar(255, 432);
            eneg2pan1.posicionar(465 , 114);
            //
            enemigosCreadosPan1 = true;
            enemigosCreadosPan2 = false;
            enemigosCreadosPan3 = false;
        }
        if(mapa.getMapaActual() == 2 && !enemigosCreadosPan2)
        {
            jefe.posicionar(-32,-32);
            eneg1pan2.posicionar(200, 432);
            eneg2pan2.posicionar(465 , 150);
            eneg1pan1.posicionar(-32,-32);
            eneg2pan1.posicionar(-32,-32);
            //
            enemigosCreadosPan1 = false;
            enemigosCreadosPan2 = true;
            enemigosCreadosPan3 = false;
        }
        if(mapa.getMapaActual() == 3 && !enemigosCreadosPan3)
        {
            jefe.posicionar(300,300);
            eneg1pan2.posicionar(-32,-32);
            eneg2pan2.posicionar(-32,-32);
            eneg1pan1.posicionar(-32,-32);
            eneg2pan1.posicionar(-32,-32);
            //
            enemigosCreadosPan1 = false;
            enemigosCreadosPan2 = false;
            enemigosCreadosPan3 = true;
        }

        if (eneg1pan1.getVida() <= 0) eneg1pan1.posicionar(-32,-32);
        if (eneg2pan1.getVida() <= 0) eneg2pan1.posicionar(-32,-32);
        if (eneg1pan2.getVida() <= 0) eneg1pan2.posicionar(-32,-32);
        if (eneg2pan2.getVida() <= 0) eneg2pan2.posicionar(-32,-32);

        if(mapa.getMapaActual() != 0)
        {
            // muestra solo enemigos "vivos"
            if (eneg1pan1.getVida() > 0) window.draw(eneg1pan1);
            if (eneg2pan1.getVida() > 0) window.draw(eneg2pan1);
            if (eneg1pan2.getVida() > 0) window.draw(eneg1pan2);
            if (eneg2pan2.getVida() > 0) window.draw(eneg2pan2);
            if (jefe.getVida() > 0) window.draw(jefe);
        }


        window.display();
    }
}

void PANTALLA::menu(sf::RenderWindow &window, HEROE &enlace) {

    sf::Texture tex("IMG/menu.png");
    sf::Sprite image(tex);
    sf::Music musicamenu("Musica/Menu.ogg");
    musicamenu.play();
    musicamenu.setLooping(true);
    musicamenu.setVolume(60);

    // BOTONES
    sf::RectangleShape botonJugar( {160.f , 40.f} );
        botonJugar.setFillColor(sf::Color::Transparent);
        botonJugar.setPosition( {350.f , 410.f} );
    sf::RectangleShape botonCreditos( {160.f , 40.f} );
        botonCreditos.setFillColor(sf::Color::Transparent);
        botonCreditos.setPosition( {350.f , 459.f} );
    sf::RectangleShape botonSalir( {160.f , 40.f} );
        botonSalir.setFillColor(sf::Color::Transparent);
        botonSalir.setPosition( {350.f , 505.f} );

    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>()) window.close();
        }
        window.clear();
        if(reset==false){
            window.draw(image);
            window.draw(botonJugar);
            window.draw(botonCreditos);
            window.draw(botonSalir);
                    }

        if(reset==true && !enlace.vivo){
                reset = false;
                musicamenu.stop();
                enlace.resetear();
                gameLoop(enlace, window);
        }
        if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
        {
            sf::Vector2i mousePos = sf::Mouse::getPosition(window);

            if(botonJugar.getGlobalBounds().contains({(float) mousePos.x ,  (float) mousePos.y}))
            {
                musicamenu.stop();
                gameLoop(enlace, window);
            }
            if(botonCreditos.getGlobalBounds().contains({(float) mousePos.x ,  (float) mousePos.y}))
                creditos(window);
            if(botonSalir.getGlobalBounds().contains({(float) mousePos.x ,  (float) mousePos.y}))
                exit(1);
        }


        window.display();
    }
}

void PANTALLA::creditos(sf::RenderWindow &window) {

    sf::Texture tex("IMG/Creditos.png");
    sf::Sprite image(tex);

    sf::Font fuente("MAPAS/fuentePelea.ttf");
    sf::Text texto(fuente, "Presione ESC para volver...");
    texto.setPosition({200.f , 450.f});
    texto.setCharacterSize(24);

    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>()) window.close();
        }

        if (!window.isOpen()) break;

        window.clear();

        window.draw(image);
        window.draw(texto);

        window.display();

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape)) break;
    }
}

void PANTALLA::pelea(NPC &rival, HEROE &enlace, sf::RenderWindow &window) {

    // MUSICA DE FONDO
    sf::Music MusicaPelea;
    MusicaPelea.openFromFile("Musica/Pelea.ogg");
    MusicaPelea.play();
    MusicaPelea.setLooping(true);
    MusicaPelea.setVolume(5);

    // EFECTOS DE SONIDO
    sf::SoundBuffer ataqueEnlace;
    ataqueEnlace.loadFromFile("Efectos/Golpe.ogg");
    sf::Sound ataqueE(ataqueEnlace);

    sf::SoundBuffer defensaEnlace;
    defensaEnlace.loadFromFile("Efectos/Bloqueo.ogg");
    sf::Sound defensaE(defensaEnlace);

    sf::SoundBuffer hechizoEnlace;
    hechizoEnlace.loadFromFile("Efectos/Lata.ogg");
    sf::Sound hechizoE(hechizoEnlace);

    sf::SoundBuffer curacionEnlace;
    curacionEnlace.loadFromFile("Efectos/Curacion.ogg");
    sf::Sound curacionE(curacionEnlace);

    sf::SoundBuffer ataqueGoblin;
    ataqueGoblin.loadFromFile("Efectos/Herida.ogg");
    sf::Sound ataqueG(ataqueGoblin);

    // toma las posiciones para devolverlos al terminar
    const sf::Vector2f posEnlace = enlace.getSprite().getPosition();
    const sf::Vector2f posR = rival.getSprite().getPosition();

    // posiciona las entidades al centro de pantalla
    enlace.setBatallando(true);
    enlace.posicionar(250.f, 250.f);
    rival.posicionar(450.f, 250.f);

    // LATA DE HECHIZO
    sf::RectangleShape lata({40.f, 40.f});
    sf::Texture lataTexture("IMG/lata.png");
    lata.setTexture(&lataTexture);
    lata.setPosition({30.f , 30.f});

    // datos para turnos
    bool turnoH = true;
    bool turnoE = false;
    bool botonApretado = false;
    bool turnoHecho = false;
    bool enter = false;

    // crea escena de pelea
    MAPA_PELEA mapita;
        mapita.setTextureFondo("IMG/fondoPelea.png");
        mapita.setTextureHud("IMG/HUD_batalla.png");
        mapita.iniciar();

    //  toma los valores "maximos" de vida y mana
    std::string vidaMaxH = std::to_string(enlace.getVida());
    std::string manaMax = std::to_string(enlace.getMana());
    std::string vidaMaxEneg = std::to_string(rival.getVida());
    std::string nombreEnemigo = rival.getNombre();
    std::string nombreHeroe = enlace.getNombre();

    while (rival.getVida() > 0) {

        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>()) window.close();
        }

        if (!window.isOpen()) break;
        if (enlace.getVida() <= 0) break;

        // texto de la vida del enemigo
        std::string textVE = nombreEnemigo + ": \n" + std::to_string(rival.getVida()) + " | " + vidaMaxEneg;
        mapita.setVidaEnemigo(textVE);

        // texto de datos del jugador
        std::string manacito = std::to_string(enlace.getMana());
        if (enlace.getMana() <= 0) manacito = '0';

        std::string textHeroe = nombreHeroe + ": \n" + std::to_string(enlace.getVida())
                            + " | " + vidaMaxH
                            + "\n" + manacito + " | " + manaMax;
        mapita.setVidaHeroe(textHeroe);

        // "IA" del enemigo
        const int decisionRival = (rand() % 2) + 1;

        window.clear(sf::Color::Black);

        // dibuja el fondo y la interfaz
        for (int cuadro=0; cuadro < 8; cuadro++)
        {
            window.draw(mapita.getRectangles()[cuadro]);
        }
            window.draw(mapita.getE());
            window.draw(mapita.getH());
            //window.draw(lata);
            window.draw(enlace);
            window.draw(rival);
            window.draw(mapita.getTxt());

        window.display();

        if (turnoH)
        {
            if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
            {
                if (!botonApretado)
                {
                    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                    botonApretado = true;

                    if (mapita.getRectangles()[4].getGlobalBounds().contains({(float)mousePos.x , (float)mousePos.y}))
                    {
                        mapita.setTexto(" PEGANDO ");
                        enlace.golpear(rival);
                        ataqueE.play();
                        turnoH = false;
                    }
                    if (mapita.getRectangles()[5].getGlobalBounds().contains({(float)mousePos.x , (float)mousePos.y}))
                    {
                        mapita.setTexto(" DEFENDIENDO ");
                        enlace.setDefensa(true);
                        defensaE.play();
                        turnoH = false;
                    }
                    if (mapita.getRectangles()[6].getGlobalBounds().contains({(float)mousePos.x , (float)mousePos.y}))
                    {
                        mapita.setTexto(" CURANDO ");
                        enlace.curar();
                        curacionE.play();
                        turnoH = false;
                    }
                    if (mapita.getRectangles()[7].getGlobalBounds().contains({(float)mousePos.x , (float)mousePos.y}))
                    {
                        mapita.setTexto(" PIU PIU ");
                        enlace.hechizo(rival);
                        hechizoE.play();
                        turnoH = false;
                    }
                } else {botonApretado = false;}
            }
        }

        if(!turnoH && !enter) {
            if (!turnoHecho) {
                std::string text = mapita.getTexto() + '\n' + "Presione enter para terminar turno...";
                mapita.setTexto(text);
                turnoHecho = true;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Enter)) {
                enter = true;
                turnoE = true;
                turnoHecho = false;
            }
        }

        if (turnoE && enter) {
            if (decisionRival == 1) {
                mapita.setTexto(" ENEMIGO PEGANDO ");
                rival.golpear(enlace);
                ataqueG.play();
                turnoE = false;
                turnoH = true;
            } else {
                mapita.setTexto(" ENEMIGO DEFENDIDO ");
                rival.setDefensa(true);
                turnoE = false;
                turnoH = true;
            }

            enter = false;


        }

    }

    if(enlace.getVida()<=0){
            MusicaPelea.stop();
            enlace.vivo = false;
            gameOver(window, enlace);
            return;
        }

    cortinaInicio(window);

    enlace.setVida(100.f);
    enlace.setMana(100);
    enlace.setBatallando(false);
    enlace.posicionar(posEnlace.x, posEnlace.y);
    rival.posicionar(posR.x, posR.y);
    MusicaPelea.stop();
}

unsigned int PANTALLA::getAncho() {
    return _ANCHO;
}

unsigned int PANTALLA::getLargo() {
    return _LARGO;
}

void PANTALLA::cortinaInicio(sf::RenderWindow &window) {

    sf::RectangleShape cortina(sf::Vector2f({(float) _ANCHO,(float) _LARGO}));
    cortina.setFillColor(sf::Color::White);
    float duracion = 0.25;

    sf::Clock relojito;

    while (relojito.getElapsedTime().asSeconds() < duracion) {

        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>()) window.close();
        }

        float transparencia = (relojito.getElapsedTime().asSeconds() / duracion) * 255;
        float colorcito = 255 - (relojito.getElapsedTime().asSeconds() / duracion);
        cortina.setFillColor(sf::Color(colorcito,colorcito,colorcito,transparencia));

        window.clear();

        window.draw(cortina);

        window.display();
    }
}

void PANTALLA::tutorial(sf::RenderWindow &window, HEROE &enlace, MAPA &mapa) {

    sf::Font fuente("MAPAS/fuente.ttf");
    sf::Texture texture("IMG/HUD_batalla.png");
    int dialogo = 0;

    // cuadro de texto que aparece
    sf::RectangleShape cuadroTexto({650.f , 100.f});
    cuadroTexto.setPosition({100.f , 350.f});
    cuadroTexto.setFillColor(sf::Color::Black);
    cuadroTexto.setOutlineThickness(1);

    // muestra la interfaz de ataque para mostrarla de ejemplo
    sf::RectangleShape imgInterfaz({150.f, 200.f});
    imgInterfaz.setTexture(&texture);
    imgInterfaz.setPosition({350.f, 130.f});

    sf::Text texto(fuente, "texto piola");
    texto.setCharacterSize(16);
    texto.setString(dialogosTuto(dialogo));
    texto.setPosition({110.f, 360.f});
    texto.setFillColor(sf::Color::White);

    // para mostrar al vagabundo del tuto y su arbolito
    NPC vagabundo;
    vagabundo.setSprite("IMG/cirujano.png");
    vagabundo.setNombre("charly");
    vagabundo.posicionar(250, 200);

    sf::RectangleShape arbol({32.f, 64.f});
    sf::Texture textArbol("IMG/Arbolito.png");
    arbol.setTexture(&textArbol);
    arbol.setPosition({260.f, 150.f});

    // verificaciones para avanzar dialogo
    bool avanzar = false;
    bool botonApretado = false;
    bool finDialogo = false;

    while(window.isOpen()) {

        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>()) window.close();
        }

        window.clear();
        window.draw(mapa);
        window.draw(cuadroTexto);
        window.draw(vagabundo);
        window.draw(arbol);
        window.draw(enlace);

        if (dialogo >= 4 && dialogo <= 8) window.draw(imgInterfaz);

        if (!avanzar) {
            if (!finDialogo) {
                std::string txt = texto.getString() + '\n' + "Enter >>>";
                texto.setString(txt);
                finDialogo = true;
            }

            if (!botonApretado && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Enter)) {
                dialogo++;
                texto.setString(dialogosTuto(dialogo));
                botonApretado = true;
                finDialogo = false;
            }

            if (botonApretado && !sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Enter)) {
                botonApretado = false;
            }

        }

        // que corte en el ultimo dialogo
        if (dialogo == 10) break;

        window.draw(texto);


        window.display();
    }

    // al finalizar los textos mueve un poco al PJ
    // para no volver a empezar el bucle
    enlace.posicionar(250, 220);
}

void PANTALLA::gameOver(sf::RenderWindow &window, HEROE &enlace){

    sf::Texture textura;
    if(!textura.loadFromFile("IMG/gameover.png")){
        return;
    }
    sf::Sprite gameoverpant(textura);

    while(window.isOpen()){
        while (const std::optional event = window.pollEvent())
        {
        if (event->is<sf::Event::Closed>()) window.close();
        }

        window.clear();
        window.draw(gameoverpant);

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space)){
                reset=true;
                break;
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape)){
            menu(window, enlace);
        }
        window.display();
    }


}


PANTALLA::~PANTALLA() {}
