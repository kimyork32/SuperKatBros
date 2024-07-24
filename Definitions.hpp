#ifndef DEFINITIONS_H
#define DEFINITIONS_H

const int windowSizeAncho = 1152; 
const int windowSizeAlto = 864;


const int numRows = 20;
const int numCols = 80;

const int cellSize = 70;


const float GRAVITY = 4500.0f;
const float JUMP_FORCE = -8000.0f;
const float MAX_JUMP_TIME = 1.2f;
const float MASS = 6.00f;
const float velocidadX = 320.0f;

// ESPECIFICACIONES DEL MAPA
const unsigned int numFilasSpriteMapa = 9;
const unsigned int numColumnasSpriteMapa = 20;
const unsigned int cantBloquesMapaSprite = numFilasSpriteMapa * numColumnasSpriteMapa;


// RANGO DE BLOQUES SIMPLES - BLOQUES ESPECIALES - ITEMS - ENEMIGO
const unsigned int rangeBloqueBegin = 1;
const unsigned int rangeBloqueEnd = cantBloquesMapaSprite;

const unsigned int rangeBloqueEspecialBegin = rangeBloqueEnd + 1;
const unsigned int rangeBloqueEspecialEnd = rangeBloqueEspecialBegin + 3 - 1;

const unsigned int rangeItemBegin = rangeBloqueEspecialEnd + 1;
const unsigned int rangeItemEnd= rangeItemBegin + 4 - 1;

const unsigned int rangeEnemigoBegin = rangeItemEnd + 1;
const unsigned int rangeEnemigoEnd = rangeEnemigoBegin + 5 - 1;

// VALORES

// Bloques destruibles
const unsigned int valBloqueDestruible = rangeBloqueEspecialBegin + 0;
const unsigned int valBloqueMoneda = rangeBloqueEspecialBegin + 1;
const unsigned int valBloqueItem = rangeBloqueEspecialBegin + 2;


// Items
const unsigned int valItemAji = rangeItemBegin + 0;
const unsigned int valItemCatnip = rangeItemBegin + 1;
const unsigned int valItemMoneda = rangeItemBegin + 2;
const unsigned int valItemPollo = rangeItemBegin + 3;


// Enemigos
const unsigned int valEnemigoRata = rangeEnemigoBegin + 0;			// 57
const unsigned int valEnemigoErizo = rangeEnemigoBegin + 1;			// 58
const unsigned int valEnemigoSerpiente = rangeEnemigoBegin + 2;		// 59
const unsigned int valEnemigoPezGlobo = rangeEnemigoBegin + 3;		// 60
const unsigned int valEnemigoAguila = rangeEnemigoBegin + 4;			// 61





#endif // !DEFINITIONS_H
