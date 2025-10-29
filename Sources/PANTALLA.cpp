#include "HEROE.h"
#include "MAPA.h"
#include "MAPA_PELEA.h"
#include "PANTALLA.h"
#include <SFML/Audio.hpp>
PANTALLA::PANTALLA() {}

// INICIO DE JUEGO
void PANTALLA::gameLoop(HEROE &enlace, sf::RenderWindow &window) {
    sf::Music MusicaJuego;
    MusicaJuego.openFromFile("Musica/Mundo.ogg");
    MusicaJuego.play();
    MusicaJuego.setLooping(true);
    MusicaJuego.setVolume(80);

    // MAPA
    MAPA mapa(_ANCHO, _LARGO);

    enlace.posicionar(561 , 432);

    NPC eneg1pan1;
    eneg1pan1.setSprite("IMG/GoblinDer2.png");
    eneg1pan1.setNombre("pepeASD");

    NPC eneg2pan1;
    eneg2pan1.setSprite("IMG/GoblinDer2.png");
    eneg2pan1.setNombre("pepeZXC");

    NPC eneg1pan2;
    eneg1pan2.setSprite("IMG/GoblinDer2.png");
    eneg1pan2.setNombre("pepeRWER");

    NPC eneg2pan2;
    eneg2pan2.setSprite("IMG/GoblinDer2.png");
    eneg2pan2.setNombre("pepeTRFS");

    NPC jefe;
    jefe.setSprite("IMG/DragFrente2.png");
    jefe.setNombre("pepeCAQSD");

    bool enemigosCreadosPan1 = false;
    bool enemigosCreadosPan2 = false;
    bool enemigosCreadosPan3 = false;

    while (window.isOpen()) {

        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>()) window.close();
        }

        // MOVIMIENTO DE JUGADOR
        enlace.actualizar(mapa, _ANCHO, _LARGO);

        if (!enlace.getBatallando())
        {
            if (!enlace.estaColisionando(eneg1pan1.getSprite().getPosition()))
                eneg1pan1.patrullar(300, 500);

            if (enlace.estaColisionando(eneg1pan1.getSprite().getPosition()))
            {
                if(eneg1pan1.getVida() > 0) cortinaInicio(window);
                MusicaJuego.stop();
                pelea(eneg1pan1, enlace, window);
                MusicaJuego.play();
            }

            if (!enlace.estaColisionando(eneg2pan1.getSprite().getPosition()))
                eneg2pan1.patrullar(250, 500);

            if (enlace.estaColisionando(eneg2pan1.getSprite().getPosition()))
            {
                if(eneg2pan1.getVida() > 0) cortinaInicio(window);
                MusicaJuego.stop();
                pelea(eneg2pan1, enlace, window);
                MusicaJuego.play();
            }

            if (!enlace.estaColisionando(eneg1pan2.getSprite().getPosition()))
                eneg1pan2.patrullar(250, 600);

            if (enlace.estaColisionando(eneg1pan2.getSprite().getPosition()))
            {
                if(eneg1pan2.getVida() > 0) cortinaInicio(window);
                MusicaJuego.stop();
                pelea(eneg1pan2, enlace, window);
                MusicaJuego.play();
            }

            if (!enlace.estaColisionando(eneg2pan2.getSprite().getPosition()))
                eneg2pan2.patrullar(250, 700);

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

        window.draw(mapa);
        window.draw(enlace);

        // PARA REEUBICAR ENEMIGOS AL CAMBIAR MAPA
        if(mapa.getMapaActual() == 1 && !enemigosCreadosPan1)
        {
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

void PANTALLA::menu(sf::RenderWindow &window) {

    sf::Texture tex("IMG/menu.png");
    sf::Sprite image(tex);
    sf::Music musicamenu("Musica/Menu.ogg");
    musicamenu.play();
    musicamenu.setLooping(true);

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

        if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
        {
            sf::Vector2i mousePos = sf::Mouse::getPosition(window);

            if(botonJugar.getGlobalBounds().contains({(float) mousePos.x ,  (float) mousePos.y}))
            {
                musicamenu.stop();
                HEROE *enlace = new HEROE();
                enlace->setSprite("IMG/EnlaceFrente.png");
                enlace->setNombre("Enlace");
                enlace->setDialogo("hola");
                gameLoop(*enlace, window);
                delete enlace;
            }
            if(botonCreditos.getGlobalBounds().contains({(float) mousePos.x ,  (float) mousePos.y}))
                creditos(window);
            if(botonSalir.getGlobalBounds().contains({(float) mousePos.x ,  (float) mousePos.y}))
                exit(1);
        }

        window.clear();

        window.draw(image);
            window.draw(botonJugar);
            window.draw(botonCreditos);
            window.draw(botonSalir);

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

    sf::Music MusicaPelea;
    MusicaPelea.openFromFile("Musica/Pelea.ogg");
    MusicaPelea.play();
    MusicaPelea.setLooping(true);
    MusicaPelea.setVolume(25);

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
    rival.getSprite().setScale({-1.f, 1.f});

    // LATA
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
        mapita._vidaEnemigo.setString(textVE);

        // texto de datos del jugador
        std::string text1 = nombreHeroe + ": \n" + std::to_string(enlace.getVida())
                            + " | " + vidaMaxH
                            + "\n" + std::to_string(enlace.getMana()) + " | " + manaMax;
        std::string textHeroe = text1 ;
        mapita._vidaHeroe.setString(textHeroe);

        // "IA" del enemigo
        const int decisionRival = (rand() % 2) + 1;

        window.clear(sf::Color::Black);

        // dibuja el fondo y la interfaz
        for (auto cuadro : mapita.getRectangles())
        {
            window.draw(cuadro);
        }
            window.draw(mapita._vidaEnemigo);
            window.draw(mapita._vidaHeroe);
            window.draw(lata);
            window.draw(enlace);
            window.draw(rival);
            window.draw(mapita._textoExplicativo);

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
                        mapita._textoExplicativo.setString(" PEGANDO ");
                        enlace.golpear(rival);
                        ataqueE.play();
                        turnoH = false;
                    }
                    if (mapita.getRectangles()[5].getGlobalBounds().contains({(float)mousePos.x , (float)mousePos.y}))
                    {
                        mapita._textoExplicativo.setString(" DEFENDIENDO ");
                        enlace.setDefensa(true);
                        defensaE.play();
                        turnoH = false;
                    }
                    if (mapita.getRectangles()[6].getGlobalBounds().contains({(float)mousePos.x , (float)mousePos.y}))
                    {
                        mapita._textoExplicativo.setString(" CURANDO ");
                        enlace.curar();
                        curacionE.play();
                        turnoH = false;
                    }
                    if (mapita.getRectangles()[7].getGlobalBounds().contains({(float)mousePos.x , (float)mousePos.y}))
                    {
                        mapita._textoExplicativo.setString(" PIU PIU ");
                        enlace.hechizo(rival);
                        hechizoE.play();
                        turnoH = false;
                    }
                } else {botonApretado = false;}
            }
        }

        if(!turnoH && !enter) {
            if (!turnoHecho) {
                std::string text = mapita._textoExplicativo.getString() + '\n' + "Presione enter para terminar turno...";
                mapita._textoExplicativo.setString(text);
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
                mapita._textoExplicativo.setString(" ENEMIGO PEGANDO ");
                rival.golpear(enlace);
                ataqueG.play();
                turnoE = false;
                turnoH = true;
            } else {
                mapita._textoExplicativo.setString(" ENEMIGO DEFENDIDO ");
                rival.setDefensa(true);
                turnoE = false;
                turnoH = true;
            }

            enter = false;
        }
    }

    cortinaFin(window);

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

void PANTALLA::cortinaFin(sf::RenderWindow &window) {

    sf::RectangleShape cortina(sf::Vector2f({(float)_ANCHO,(float) _LARGO}));
    cortina.setFillColor(sf::Color::White);
    float duracion = 0.25;

    sf::Clock relojito;

    while (relojito.getElapsedTime().asSeconds() > duracion) {

        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>()) window.close();
        }

        float transparencia = 255 - (relojito.getElapsedTime().asSeconds() / duracion) * 255;
        float colorcito = 255 - (relojito.getElapsedTime().asSeconds() / duracion);
        cortina.setFillColor(sf::Color(colorcito,colorcito,colorcito,transparencia));

        window.clear();

        window.draw(cortina);

        window.display();
    }
}


PANTALLA::~PANTALLA() {}
