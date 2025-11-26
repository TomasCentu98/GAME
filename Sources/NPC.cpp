#include "../Includes/NPC.h"
#include "HEROE.h"
#include <cstring>

NPC::NPC() :
    _textura("IMG/cirujano.png"),
    _sprite(_textura)
{
    _vida = 100;
    _fuerza = 10;

    _sprite.setOrigin({
        _sprite.getTexture().getSize().x / 2.f,
        _sprite.getTexture().getSize().y / 2.f
    });
}

void NPC::setVida (int vida){
    _vida = vida;
};

void NPC::setFuerza (int fuerza){
    _fuerza = fuerza;
};

int NPC::getVida(){
    return _vida;
};

int NPC::getFuerza(){
    return _fuerza;
};

void NPC::setNombre(const char *nombre){
    strcpy(_nombre, nombre);
};

char* NPC::getNombre(){
    return _nombre;
};

void NPC::setDialogo(const char *dialogo){
    strcpy(_dialogo, dialogo);
};

char* NPC::getDialogo(){
    return _dialogo;
};

void NPC::recibirGolpe(int cantGolpe) {
    if(_estaDefendido) {
        _vida -= cantGolpe - defensa();
        _estaDefendido = false;
    } else {
    _vida -= cantGolpe;
    }
}

int NPC::calcularGolpe(int fuerza) {
    return (rand() % _fuerza) + 5;
}

void NPC::golpear(HEROE &heroe) {
    int golpe = calcularGolpe(_fuerza);
    heroe.recibirGolpe(golpe);
    heroe.setDR(golpe);
}

int NPC::defensa() {
    int defendido = (rand() % (_fuerza - 4)) + 5;
    return defendido;
}

sf::Vector2f NPC::getVelocidad() {
    return _velocidad;
}

void NPC::setVelocidad(float x, float y) {
    _velocidad.x = x;
    _velocidad.y = y;
}

void NPC::setDirrecionMov(bool derecha) {
    _moviendoDerecha = derecha;
}

bool NPC::getDireccionMov() {
    return _moviendoDerecha;
}

bool NPC::getDefensa() {
    return _estaDefendido;
}

void NPC::setDefensa(bool defensa){
    _estaDefendido = defensa;
}

// DATOS PARA VIDEO

void NPC::setSprite(const char *txt) {
    _textura.loadFromFile(txt);
    _sprite.setTexture(_textura, true);
    _sprite.setTextureRect({{0,0},{32,32}});
}

void NPC::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(_sprite, states);
}

void NPC::posicionar(float x, float y) {
    _sprite.setPosition({x , y});
}

sf::Sprite NPC::getSprite() {
    return _sprite;
}

bool NPC::estaColisionando(sf::Vector2f areaObj) {
    if(_sprite.getGlobalBounds().contains(areaObj)) return true;
    return false;
}

void NPC::actualizar(MAPA &mapaActual, int width, int heigth, sf::Clock &relojito) {
    _velocidad = {0, 0};

    const int frameWidth = 32;
    const int frameHeight = 32;
    int fila = 0;

    sf::Vector2 personajePos = {
        _sprite.getGlobalBounds().getCenter().x,
        _sprite.getGlobalBounds().getCenter().y
    };

    // BORDE PANTALLA IZQUIERDA
    if(personajePos.x < _sprite.getOrigin().x) {
        _sprite.setPosition({_sprite.getOrigin().x, _sprite.getPosition().y});
    }
    // BORDE PANTALLA ARRIBA
    if(personajePos.y < _sprite.getOrigin().y) {
        _sprite.setPosition({_sprite.getPosition().x, _sprite.getOrigin().y});
    }
    // BORDE PANTALLA ABAJO
    if(personajePos.y > heigth - _sprite.getOrigin().y) {
        _sprite.setPosition({_sprite.getPosition().x , heigth - _sprite.getOrigin().y});
    }
    // BORDE PANTALLA DERECHA
    if(personajePos.x > width - _sprite.getOrigin().x) {
        _sprite.setPosition({width - _sprite.getOrigin().x , _sprite.getPosition().y});
    }

    // TECLAS DE MOVIMIENTO
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) {
       _velocidad.y = -3;
       fila = 3;
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) {
        _velocidad.x = -3;
        fila = 1;
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) {
       _velocidad.y = 3;
       fila = 0;
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
        _velocidad.x = 3;
        fila = 2;
    }

    const int azulejoSize = 32 ;
    const int cantAzulejosX = width / azulejoSize;

    sf::Vector2f azulejoPos = {personajePos.x + _velocidad.x, personajePos.y + _velocidad.y};
    int azulejoX = azulejoPos.x / azulejoSize;
    int azulejoY = azulejoPos.y  / azulejoSize;

    if(_velocidad.x !=0 || _velocidad.y !=0){
        if(relojito.getElapsedTime().asSeconds() >= _frameTime){
            _currentFrame = (_currentFrame + 1) % 3;
            relojito.restart();
        }
    }

    _sprite.setTextureRect({{frameWidth * _currentFrame, frameHeight * fila},{frameWidth, frameHeight}});

    // verificar si el azulejo destino es sólido por posicion
    //                     x , y , cant -> 0 + 1 * 25 -> azulejos[25] = true
    if(mapaActual.esCaminable(azulejoX, azulejoY, cantAzulejosX))
    {
        _sprite.move(_velocidad); // mover solo si no es sólido
    }
}

void NPC::patrullar(int posIzq, int posDer) {
    float nuevaPosX;
    float posY = _sprite.getPosition().y;
    const int frameWidth = 32;
    const int frameHeight = 32;

    if (_relojEnemigo.getElapsedTime().asSeconds() >= _frameTime)
    {
        _currentFrame = (_currentFrame + 1) % 3;
        _relojEnemigo.restart();
    }

    if (getDireccionMov())
    {
        setVelocidad(2,0);
        nuevaPosX = _sprite.getPosition().x + getVelocidad().x;

        if (_sprite.getPosition().x >= posDer) setDirrecionMov(false);

        _sprite.setTextureRect({{frameWidth * _currentFrame, 0},{frameWidth, frameHeight}});
    }
    else
    {
        setVelocidad(-2,0);
        nuevaPosX = _sprite.getPosition().x + getVelocidad().x;

        if (_sprite.getPosition().x <= posIzq) setDirrecionMov(true);

        _sprite.setTextureRect({{frameWidth * _currentFrame, 32},{frameWidth, frameHeight}});
    }

    posicionar(nuevaPosX, posY);
}

void NPC::animacionIdle(std::string img){

    _textura.loadFromFile(img);
    _sprite.setTexture(_textura);

    if(relojAnimacion.getElapsedTime().asSeconds()>tiempoAnimacion){
      _sprite.setTextureRect({{0,0},{64,64}});
    }

    if(relojAnimacion.getElapsedTime().asSeconds()>tiempoAnimacion*2){
      _sprite.setTextureRect({{64,0},{64,64}});
      relojAnimacion.restart();
    }
}

void NPC::animacionGolpe(std::string img){

    _textura.loadFromFile(img);
    _sprite.setTexture(_textura);
    float tiempo = relojGolpe.getElapsedTime().asSeconds();

    if (tiempo < tiempoAnimacion) {
        _sprite.setTextureRect({{0,0},{64,64}});
    }
    else if (tiempo < tiempoAnimacion * 2) {
        _sprite.setTextureRect({{64,0},{64,64}});
    }
    else {
        _sprite.setTextureRect({{128,0},{64,64}});
    }

    if (tiempo >= 1.5) relojGolpe.restart();
}

void NPC::setRango(bool esJefe) { _esJefe = esJefe; }
bool NPC::getRango() { return _esJefe; }
