#include "HEROE.h"
#include "MAPA.h"
#include "MAPA_PELEA.h"
#include "PANTALLA.h"
#include "MANAGER.h"
#include "NPC_aux.h"
#include <SFML/Audio.hpp>
#include <cstring>
#include <iostream>

PANTALLA::PANTALLA() {}

// INICIO DE JUEGO
void PANTALLA::gameLoop(HEROE &enlace, sf::RenderWindow &window) {
    sf::Music MusicaJuego;
    MusicaJuego.openFromFile("Musica/Mundo.ogg");
    MusicaJuego.play();
    MusicaJuego.setLooping(true);
    MusicaJuego.setVolume(3);

    MAPA mapa(_ANCHO, _LARGO);
    sf::Clock relojito;
    enlace.posicionar(561 , 432);

    NPC vagabundo;
    vagabundo.setSprite("IMG/cirujano.png");
    vagabundo.setNombre("charly");
    vagabundo.posicionar(250, 200);

    sf::RectangleShape arbol({32.f, 64.f});
    sf::Texture textArbol("IMG/Arbolito.png");
    arbol.setTexture(&textArbol);
    arbol.setPosition({260.f, 150.f});

    NPC eneg1pan1 = leerEnemigo();

    NPC eneg2pan1 = leerEnemigo();

    NPC eneg1pan2 = leerEnemigo();

    NPC eneg2pan2 = leerEnemigo();

    FILE *archivo = fopen("enemigos.dat", "rb");
    if(archivo==nullptr) return;

    NPC jefe;
    NPC_aux jefeAux;

    if (fread(&jefeAux, sizeof(NPC_aux), 1, archivo)) {
        jefe.setNombre(jefeAux.getNombre());
        jefe.setDialogo(jefeAux.getDialogo());
        jefe.setVida(jefeAux.getVida());
        jefe.setFuerza(jefeAux.getFuerza());
        jefe.setSprite("IMG/DragFrente2.png");
    }

    fclose(archivo);

    bool tuto = true;
    bool salirDelJuego = false;
    bool enemigosCreadosPan1 = false;
    bool enemigosCreadosPan2 = false;
    bool enemigosCreadosPan3 = false;

    while (window.isOpen() && enlace.vivo) {

        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>()) window.close();

            if (const auto* keyEvent = event->getIf<sf::Event::KeyPressed>()) {
                if (keyEvent->scancode == sf::Keyboard::Scancode::Escape) {
                    if (pausa(window)) {
                        salirDelJuego = true;
                    }
                }
            }
        }

        if (salirDelJuego) break;

        // MOVIMIENTO DE JUGADOR
        enlace.actualizar(mapa, _ANCHO, _LARGO, relojito);

        if (!enlace.getBatallando())
        {
            // ENEMIGO 1 PANTALLA 1
            if (!enlace.estaColisionando(eneg1pan1.getSprite().getPosition()))
                eneg1pan1.patrullar(300, 500);

            if (enlace.estaColisionando(eneg1pan1.getSprite().getPosition()))
            {
                if(eneg1pan1.getVida() > 0) cortinaInicio(window);
                MusicaJuego.stop();
                pelea(eneg1pan1, enlace, window);
                MusicaJuego.play();
            }

            // ENEMIGO 2 PANTALLA 1
            if (!enlace.estaColisionando(eneg2pan1.getSprite().getPosition()))
                eneg2pan1.patrullar(250, 500);

            if (enlace.estaColisionando(eneg2pan1.getSprite().getPosition()))
            {
                if(eneg2pan1.getVida() > 0) cortinaInicio(window);
                MusicaJuego.stop();
                pelea(eneg2pan1, enlace, window);
                MusicaJuego.play();
            }

            // ENEMIGO 1 PANTALLA 2
            if (!enlace.estaColisionando(eneg1pan2.getSprite().getPosition()))
                eneg1pan2.patrullar(250, 600);

            if (enlace.estaColisionando(eneg1pan2.getSprite().getPosition()))
            {
                if(eneg1pan2.getVida() > 0) cortinaInicio(window);
                MusicaJuego.stop();
                pelea(eneg1pan2, enlace, window);
                MusicaJuego.play();
            }

            // ENEMIGO 2 PANTALLA 2
            if (!enlace.estaColisionando(eneg2pan2.getSprite().getPosition()))
                eneg2pan2.patrullar(250, 700);

            if (enlace.estaColisionando(eneg2pan2.getSprite().getPosition()))
            {
                if(eneg2pan2.getVida() > 0) cortinaInicio(window);
                MusicaJuego.stop();
                pelea(eneg2pan2, enlace, window);
                MusicaJuego.play();
            }

            // JEFE PANTALLA 3
            if (enlace.estaColisionando(jefe.getSprite().getPosition()))
            {
                if(jefe.getVida() > 0) cortinaInicio(window);
                MusicaJuego.stop();
                pelea(jefe, enlace, window);
            }
        }

        // CONTROLA EL PASO DE MAPAS
        mapa.chequeoPasoDeMapa(enlace);

        window.clear(sf::Color::Black);

        // si moriste, termina el juego
        if(!enlace.vivo) break;

        window.draw(mapa);

        // tutorial, si te vas del mapa, se cierra
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
            // validaciones para mover sprites
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
            // validaciones para mover sprites
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
            // validaciones para mover sprites
            enemigosCreadosPan1 = false;
            enemigosCreadosPan2 = false;
            enemigosCreadosPan3 = true;
        }

        // si los enemigos estan muertos, se van fuera de camara
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

        if (jefe.getVida() < 0) enlace.juegoFinalizado = true;

        if (enlace.juegoFinalizado) break;

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

    sf::RectangleShape estadisticas( {80.f , 100.f} );
        sf::Texture texturaEstadisticas("IMG/estadisticas.png");
        estadisticas.setTexture(&texturaEstadisticas);
        estadisticas.setPosition( {50.f , 450.f} );

    sf::Font fuenteEstadisticas("MAPAS/fuentePelea.ttf");
    sf::Text textoEstadisticas(fuenteEstadisticas);
        textoEstadisticas.setString("Estadisticas");
        textoEstadisticas.setCharacterSize(12);
        textoEstadisticas.setFillColor(sf::Color::White);
        textoEstadisticas.setPosition( {45.f , 430.f} );

    sf::Clock tiempoDeJuego;

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
            window.draw(estadisticas);
        }

        if(reset==true && !enlace.vivo){
            reset = false;
            musicamenu.stop();
            enlace.resetear();
            tiempoDeJuego.restart();
            gameLoop(enlace, window);
            musicamenu.play();
        }

        if (enlace.juegoFinalizado) {
            ESTADISTICAS est;
            est.setM(enlace.getM());
            est.setDR(enlace.getDR());
            est.setD(enlace.getD());
            est.setDEF(enlace.getDEF());
            est.setVID(enlace.getVID());
            est.setT(tiempoDeJuego.restart().asSeconds());

            est.generarPuntaje();

            est.setNombre(enlace.getNombre());

            guardarEstadisticas(est);
            enlace.juegoFinalizado = false;
        }

        sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
        if (estadisticas.getGlobalBounds().contains(mousePos)) {
            window.draw(textoEstadisticas);
        }

        if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
        {
            sf::Vector2i mousePos = sf::Mouse::getPosition(window);
            sf::Vector2f worldPos = window.mapPixelToCoords(mousePos);

            if(botonJugar.getGlobalBounds().contains(worldPos))
            {
                musicamenu.stop();
                pedirNombre(window, enlace);
                tiempoDeJuego.restart();
                gameLoop(enlace, window);
                musicamenu.play();
            }
            if(botonCreditos.getGlobalBounds().contains(worldPos))
                creditos(window);
            if(botonSalir.getGlobalBounds().contains(worldPos))
                exit(1);

            if(estadisticas.getGlobalBounds().contains(worldPos)) {
                mostrarEstadisticas(window, enlace, tiempoDeJuego.restart().asSeconds());
            }
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
    enlace.setSprite("IMG/EnlaceIdleBatalla.png");
    const sf::Vector2f posR = rival.getSprite().getPosition();
    rival.setSprite("IMG/GoblinIdle.png");

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
    sf::Clock relojGolpe;
    bool animacionGolpeando = false;
    while (rival.getVida() > 0) {

        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>()) window.close();
        }

        if (!window.isOpen()) break;
        if (enlace.getVida() <= 0) break;


        rival.animacionIdle("IMG/GoblinPelea.png");

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

            window.draw(mapita.getTxt());



        if (turnoH)
        {

            if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
            {
                if (!botonApretado)
                {
                    sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
                    botonApretado = true;

                    if (mapita.getRectangles()[4].getGlobalBounds().contains({mousePos.x , mousePos.y}))
                    {

                        animacionGolpeando = true;
                        relojGolpe.restart();
                        mapita.setTexto(" PEGANDO ");


                    }

                    if (mapita.getRectangles()[5].getGlobalBounds().contains({mousePos.x , mousePos.y}))
                    {
                        mapita.setTexto(" DEFENDIENDO ");
                        enlace.setDefensa(true);
                        enlace.setDEF(1);
                        defensaE.play(); // sonido defenza
                        turnoH = false;
                    }
                    if (mapita.getRectangles()[6].getGlobalBounds().contains({mousePos.x , mousePos.y}))
                    {
                        mapita.setTexto(" CURANDO ");
                        enlace.curar();
                        enlace.setVID(1);
                        enlace.setM(20);
                        curacionE.play(); // sonido curacion
                        turnoH = false;
                    }
                    if (mapita.getRectangles()[7].getGlobalBounds().contains({mousePos.x , mousePos.y}))
                    {
                        mapita.setTexto(" PIU PIU ");
                        enlace.hechizo(rival);
                        enlace.setM(30);
                        hechizoE.play(); // sonido hechizo
                        turnoH = false;
                    }
                } else {botonApretado = false;}
            }
            if(animacionGolpeando==true){
                enlace.animacionGolpe(relojGolpe);
                if(relojGolpe.getElapsedTime().asSeconds()>=1.5){
                    enlace.golpear(rival);
                    animacionGolpeando=false;
                    turnoH=false;
                    ataqueE.play();
                }
            }
            else{enlace.animacionIdle("IMG/EnlaceIdle.png");}
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
                ataqueG.play(); // sonido ataque
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
    window.draw(enlace);
    window.draw(rival);
    window.display();

    }
    if (enlace.getVida()<=0){
            MusicaPelea.stop();
            enlace.vivo = false;
            cortinaInicio(window);
            gameOver(window, enlace);
            enlace.setSprite("IMG/Enlace.png");
            rival.setSprite("IMG/Goblin.png");
            return;
    }

    cortinaInicio(window);

    enlace.setVida(100.f);
    enlace.setMana(100);
    enlace.victoria();
    enlace.setBatallando(false);
    enlace.posicionar(posEnlace.x, posEnlace.y);
    enlace.setSprite("IMG/Enlace.png");
    rival.posicionar(posR.x, posR.y);
    rival.setSprite("IMG/Goblin.png");
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
    if(!textura.loadFromFile("IMG/gameover.png")) return;
    sf::Sprite gameoverpant(textura);

    sf::SoundBuffer *musiquitaGO = new sf::SoundBuffer("Musica/GameOver.ogg");
    sf::Sound GameOverMusica (*musiquitaGO);
    GameOverMusica.play();

    sf::RectangleShape botonContinuar;
    botonContinuar.setSize({240 , 80});
    botonContinuar.setFillColor(sf::Color::Transparent);
    botonContinuar.setPosition({305 , 345});

    sf::RectangleShape botonSalir;
    botonSalir.setSize({240 , 60});
    botonSalir.setFillColor(sf::Color::Transparent);
    botonSalir.setPosition({305 , 445});

    while(window.isOpen()){

        while (const std::optional event = window.pollEvent())
        {
        if (event->is<sf::Event::Closed>()) window.close();
        }

        window.clear();
        window.draw(gameoverpant);
        window.draw(botonContinuar);
        window.draw(botonSalir);

        if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {

            sf::Vector2i pixelPos = sf::Mouse::getPosition(window);
            sf::Vector2f worldPos = window.mapPixelToCoords(pixelPos);

            if(botonContinuar.getGlobalBounds().contains(worldPos)) {
                reset = true;
                break;
            }

            if(botonSalir.getGlobalBounds().contains(worldPos)) {
                menu(window, enlace);
            }
        }

        window.display();
    }
    delete musiquitaGO;
}

void PANTALLA::mostrarEstadisticas(sf::RenderWindow &window, HEROE &enlace, float tiempoDeJuego) {

    sf::RectangleShape fondo({800 , 576});
    sf::Texture textura("IMG/fondoEstadisticas.png");
    fondo.setTexture(&textura);

    sf::Font fuente("MAPAS/fuentePelea.ttf");
    sf::Text texto(fuente, "Presione ESC para volver...");
    texto.setPosition({200.f , 500.f});
    texto.setCharacterSize(24);

    FILE* file = fopen("estadisticas.dat", "rb");
    if (file == nullptr) return;

    fseek(file, 0, SEEK_END); // al final
    int tamanoArchivo = ftell(file);
    fseek(file, 0, SEEK_SET); // al principio

    const int cantidadElementos = tamanoArchivo / sizeof(ESTADISTICAS);
    ESTADISTICAS *buffer = new ESTADISTICAS[cantidadElementos];

    sf::Text** textosEstadisticas = new sf::Text*[cantidadElementos];

    for (int elemento=0; elemento < cantidadElementos; elemento++) {
        fread(&buffer[elemento], sizeof(ESTADISTICAS), 1, file);
        std::string txt = buffer[elemento].getNombre();
        std::string txt2 = "   //    " + std::to_string(buffer[elemento].getTotal()) + "pts.";
        textosEstadisticas[elemento] = new sf::Text(fuente, txt + txt2);
        textosEstadisticas[elemento]->setFillColor(sf::Color::White);
        textosEstadisticas[elemento]->setPosition( {200.f , 200.f + 25 * elemento} );
    }

    fclose(file);

    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>()) window.close();
        }

        window.clear();
        window.draw(fondo);

        for (int elemento=0; elemento < cantidadElementos; elemento++) {
            window.draw(*textosEstadisticas[elemento]);
        }

        window.draw(texto);

        window.display();

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape)) break;
    }

    for (int i = 0; i < cantidadElementos; ++i) {
        delete textosEstadisticas[i];
    }
    delete[] buffer;
    delete[] textosEstadisticas;
}

void PANTALLA::pedirNombre(sf::RenderWindow &window, HEROE &enlace) {

    sf::Font fuente("MAPAS/fuentePelea.ttf");
    sf::Text texto(fuente, "Ingrese nombre heroico");
    texto.setPosition({250.f , 200.f});

    sf::Text enter(fuente, "Enter para finalizar...", 24);
    enter.setPosition({250.f , 500.f});

    sf::Texture textura("IMG/fondoPelea.png");
    sf::RectangleShape fondo( {800.f , 576.f});
    fondo.setTexture(&textura);

    std::string buffer = "";
    bool escribiendo = false;

    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>()) window.close();

            if (const auto* textEntered = event->getIf<sf::Event::TextEntered>())
            {
                if (textEntered->unicode < 128) {
                    escribiendo = true;
                    buffer += (char)textEntered->unicode;
                }
            }
        }

        window.clear();
        window.draw(fondo);
        window.draw(texto);
        window.draw(enter);

        if(escribiendo) texto.setString(buffer);

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Enter)) {
            enlace.setNombre(buffer.c_str());
            break;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Backspace)) {
            if (!buffer.empty()) buffer.pop_back();
            if (buffer.empty()) {
                texto.setString("Ingrese nombre heroico");
                escribiendo = false;
            }
        }

        window.display();
    }
}

bool PANTALLA::pausa(sf::RenderWindow &window) {

    sf::Font fuente("MAPAS/fuentePelea.ttf");

    sf::Text textoPausa(fuente, "PAUSA", 50);
    textoPausa.setPosition({350 , 200});

    sf::RectangleShape fondo;
    fondo.setSize({800 , 576});
    fondo.setFillColor(sf::Color(30,50,30,150));

    sf::RectangleShape continuar;
    continuar.setSize({240 , 70});
    continuar.setFillColor(sf::Color::Transparent);
    continuar.setPosition({305 , 345});
    continuar.setOutlineThickness(2);
    continuar.setOutlineColor(sf::Color::White);
    sf::Text textoContinuar(fuente, "CONTINUAR - ESCAPE", 20);
    textoContinuar.setPosition({320 , 360});

    sf::RectangleShape salir;
    salir.setSize({240 , 60});
    salir.setFillColor(sf::Color::Transparent);
    salir.setPosition({305 , 445});
    salir.setOutlineThickness(2);
    salir.setOutlineColor(sf::Color::Red);
    sf::Text textoSalir(fuente, "SALIR - ENTER", 24);
    textoSalir.setPosition({335 , 460});
    textoSalir.setFillColor(sf::Color::Red);

    while(window.isOpen()){

        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>()) window.close();

            if (const auto* keyEvent = event->getIf<sf::Event::KeyPressed>()) {
                if (keyEvent->scancode == sf::Keyboard::Scancode::Escape) {
                    return false;
                }
            }

            if (const auto* keyEvent = event->getIf<sf::Event::KeyPressed>()) {
                if (keyEvent->scancode == sf::Keyboard::Scancode::Enter) {
                    return true;
                }
            }
        }

        window.clear();
        window.draw(fondo);
        window.draw(textoPausa);
        window.draw(continuar);
        window.draw(textoContinuar);
        window.draw(salir);
        window.draw(textoSalir);
        window.display();
    }
}

PANTALLA::~PANTALLA() {}
