#include "HEROE.h"
#include "MAPA.h"
#include "MAPA_PELEA.h"
#include "PANTALLA.h"

PANTALLA::PANTALLA() {}

// INICIO DE JUEGO
void PANTALLA::gameLoop(HEROE &enlace, sf::RenderWindow &window) {

    // MAPA
    MAPA mapa(_ANCHO, _LARGO);

    enlace.posicionar(561 , 432);

    // CAMBIAR POR RECTANGLE SHAPE Y CREAR DENTRO DE EVENTO
    NPC eneg1pan1;
    eneg1pan1.setSprite("IMG/link.png");

    NPC eneg2pan1;
    eneg2pan1.setSprite("IMG/link.png");

    NPC eneg1pan2;
    eneg1pan2.setSprite("IMG/link.png");

    NPC eneg2pan2;
    eneg2pan2.setSprite("IMG/link.png");

    NPC gefe;
    gefe.setSprite("IMG/link.png");

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
            {
                eneg1pan1.patrullar(250, 562);
                if (enlace.estaColisionando(eneg1pan1.getSprite().getPosition()))
                    pelea(eneg1pan1, enlace, window);
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
            gefe.posicionar(-32,-32);
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
            gefe.posicionar(-32,-32);
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
            gefe.posicionar(300,300);
            eneg1pan2.posicionar(-32,-32);
            eneg2pan2.posicionar(-32,-32);
            eneg1pan1.posicionar(-32,-32);
            eneg2pan1.posicionar(-32,-32);
            //
            enemigosCreadosPan1 = false;
            enemigosCreadosPan2 = false;
            enemigosCreadosPan3 = true;
        }

        // muestra solo enemigos "vivos"
        if (eneg1pan1.getVida() > 0) window.draw(eneg1pan1);
        if (eneg2pan1.getVida() > 0) window.draw(eneg2pan1);
        if (eneg1pan2.getVida() > 0) window.draw(eneg1pan2);
        if (eneg2pan2.getVida() > 0) window.draw(eneg2pan2);
        if (gefe.getVida() > 0) window.draw(gefe);

        window.display();
    }
}

void PANTALLA::menu(sf::RenderWindow &window) {

    sf::Texture tex("IMG/menu.png");
    sf::Sprite image(tex);

    // BOTONES
    sf::RectangleShape botonJugar( {160.f , 40.f} );
        botonJugar.setOutlineThickness(2.5);
        botonJugar.setOutlineColor(sf::Color::Black);
        botonJugar.setFillColor(sf::Color::Transparent);
        botonJugar.setPosition( {350.f , 410.f} );
    sf::RectangleShape botonCreditos( {160.f , 40.f} );
        botonCreditos.setOutlineThickness(2.5);
        botonCreditos.setOutlineColor(sf::Color::Black);
        botonCreditos.setFillColor(sf::Color::Transparent);
        botonCreditos.setPosition( {350.f , 459.f} );
    sf::RectangleShape botonSalir( {160.f , 40.f} );
        botonSalir.setOutlineThickness(2.5);
        botonSalir.setOutlineColor(sf::Color::Black);
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
                HEROE *enlace = new HEROE();
                enlace->setSprite("IMG/link.png");
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
    // toma las posiciones para devolverlos al terminar
    const sf::Vector2f posEnlace = enlace.getSprite().getPosition();
    const sf::Vector2f posR = rival.getSprite().getPosition();

    // posiciona las entidades al centro de pantalla
    enlace.setBatallando(true);
    enlace.posicionar(250.f, 250.f);
    rival.posicionar(450.f, 250.f);

    // datos para turnos
    bool turnoH = true;
    bool turnoE = false;
    bool botonApretado = false;
    sf::Clock relojTurno;
    sf::Time tiempoEspera = sf::seconds(0.5f);
    bool esperando = false;

    // crea escena de pelea
    MAPA_PELEA mapita;
        mapita.setTextureFondo("IMG/fondoPelea.png");
        mapita.setTextureHud("IMG/HUD_batalla.png");
        mapita.iniciar();

    //  toma los valores "maximos" de vida y mana
    const std::string vidaMaxH = std::to_string(enlace.getVida());
    const std::string manaMax = std::to_string(enlace.getMana());
    const std::string vidaMaxEneg = std::to_string(rival.getVida());

    while (rival.getVida() > 0) {

        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>()) window.close();
        }

        if (!window.isOpen()) break;
        if (enlace.getVida() <= 0) break;

        // texto de la vida del enemigo
        std::string textVE = "Goblin: \n" + std::to_string(rival.getVida()) + " | " + vidaMaxEneg;
        mapita._vidaEnemigo.setString(textVE);

        // texto de datos del jugador
        std::string text1 = "Enlace: \n" + std::to_string(enlace.getVida())
                            + " | " + vidaMaxH
                            + "\n" + std::to_string(enlace.getMana()) + " | " + manaMax;
        std::string textHeroe = text1 ;
        mapita._vidaHeroe.setString(textHeroe);

        // "IA" del enemigo
        const int decisionRival = (rand() % 2) + 1;

        window.clear(sf::Color::Black);

        if (turnoH && !esperando)
        {
            if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
            {
                if (!botonApretado )
                {
                    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                    botonApretado = true;

                    if (mapita.getRectangles()[4].getGlobalBounds().contains({(float)mousePos.x , (float)mousePos.y}))
                    {
                        mapita._textoExplicativo.setString(" PEGANDO ");
                        enlace.golpear(rival);
                    }
                    if (mapita.getRectangles()[5].getGlobalBounds().contains({(float)mousePos.x , (float)mousePos.y}))
                    {
                        mapita._textoExplicativo.setString(" DEFENDIENDO ");
                        enlace.setDefensa(true);
                    }
                    if (mapita.getRectangles()[6].getGlobalBounds().contains({(float)mousePos.x , (float)mousePos.y}))
                    {
                        mapita._textoExplicativo.setString(" CURANDO ");
                        enlace.curar();
                    }
                    if (mapita.getRectangles()[7].getGlobalBounds().contains({(float)mousePos.x , (float)mousePos.y}))
                    {
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

        // dibuja el fondo y la interfaz
        for (auto cuadro : mapita.getRectangles())
        {
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

float PANTALLA::getAncho() {
    return _ANCHO;
}

float PANTALLA::getLargo() {
    return _LARGO;
}

PANTALLA::~PANTALLA() {}
