#include "../Includes/NPC.h"
#include "../Includes/PANTALLA.h"

NPC::NPC() :
    _textura("IMG/link.png"),
    _sprite(_textura)
{
    _vida = 100.f;
    _fuerza = 5.f;

    _sprite.setOrigin({
        _sprite.getTexture().getSize().x / 2.f,
        _sprite.getTexture().getSize().y / 2.f
    });
}

void NPC::setVida (float vida){
    _vida = vida;
};

void NPC::setFuerza (float fuerza){
    _fuerza = fuerza;
};

float NPC::getVida(){
    return _vida;
};

float NPC::getFuerza(){
    return _fuerza;
};

void NPC::setNombre(std::string nombre){
    _nombre = nombre.data();
};

std::string NPC::getNombre(){
    std::string nombre(_nombre);
    return nombre;
};

void NPC::setDialogo(std::string dialogo){
    _dialogo = dialogo.data();
};

std::string NPC::getDialogo(){
    std::string dialogo(_dialogo);
    return dialogo;
};

void NPC::recibirGolpe(float contGolpe) {
    // CAMBIAR EN ENEMIGOS Y HEROE
}

float NPC::calcularGolpe(float fuerza) {
    return (rand() % (int)_fuerza) + 5;
}


int NPC::defensa() {
    int defendido = (rand() % 8) + 1;
    return defendido;
}

bool NPC::getDefensa() {
    return _estaDefendido;
};

void NPC::setDefensa(bool defensa){
    _estaDefendido = defensa;
}

// DATOS PARA VIDEO

void NPC::setSprite(std::string txt) {
    _textura.loadFromFile(txt),
    _sprite.setTexture(_textura, true);
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

void NPC::actualizar(MAPA &mapaActual, int width, int heigth) {
    _velocidad = {0, 0};

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
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) {
        _velocidad.x = -3;
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) {
       _velocidad.y = 3;
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
        _velocidad.x = 3;
    }

    // DIRECCION DE SPRITE AL CAMINAR
    if (_velocidad.x < 0) {
        _sprite.setScale({-1.f, 1.f});
    } else if (_velocidad.x > 0) {
        _sprite.setScale({1.f,1.f});
    }

    const int azulejoSize = 32 ;
    const int cantAzulejosX = width / azulejoSize;

    sf::Vector2f azulejoPos = {personajePos.x + _velocidad.x, personajePos.y + _velocidad.y};
    int azulejoX = azulejoPos.x / azulejoSize;
    int azulejoY = azulejoPos.y  / azulejoSize;

    // verificar si el azulejo destino es sólido por posicion
    //                     x , y , cant -> 0 + 1 * 25 -> azulejos[25]
    if(mapaActual.esCaminable(azulejoX, azulejoY, cantAzulejosX))
    {
        _sprite.move(_velocidad); // mover solo si no es sólido
    }
}
