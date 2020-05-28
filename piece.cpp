#include "Piece.h"

#include <QtCore>


Piece::Piece(){
    setForme(Vide);
}

void Piece::setX(int index, int x) {
    coords[index][0] = x;
}
void Piece::setY(int index, int y) {
    coords[index][1] = y;
}

int Piece::getX(int index) const {
    return coords[index][0];
}

int Piece::getY(int index) const {
    return coords[index][1];
}

void Piece::setForme(Formes forme){

    enum Formes { Vide, Z, S, Ligne, T, Carre, L, Linvers };

    if(forme == 0){
        int grille[4][2] = { { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }};
        for(int i=0; i<4; i++){
            for(int j = 0;j<2; j++)
                coords[i][j] = grille[i][j];
        }
    }
    else if(forme == 1){
        int grille[4][2] = { { 0, -1 },  { 0, 0 },   { -1, 0 },  { -1, 1 }};
        for(int i=0; i<4; i++){
            for(int j = 0;j<2; j++)
                coords[i][j] = grille[i][j];
        }

    }
    else if(forme == 2){
        int grille[4][2] = { { 0, -1 },  { 0, 0 },   { 1, 0 },   { 1, 1 }};
        for(int i=0; i<4; i++){
            for(int j = 0;j<2; j++)
                coords[i][j] = grille[i][j];
        }

    }
    else if(forme == 3){
        int grille[4][2] = { { 0, -1 },  { 0, 0 },   { 0, 1 },   { 0, 2 }};
        for(int i=0; i<4; i++){
            for(int j = 0;j<2; j++)
                coords[i][j] = grille[i][j];
        }
        //rotation random
    }
    else if(forme == 4){
        int grille[4][2] = { { -1, 0 },  { 0, 0 },   { 1, 0 },   { 0, 1 }};
        for(int i=0; i<4; i++){
            for(int j = 0;j<2; j++)
                coords[i][j] = grille[i][j];
        }

    }
    else if(forme == 5){
        int grille[4][2] = { { 0, 0 },   { 1, 0 },   { 0, 1 },   { 1, 1 }};
        for(int i=0; i<4; i++){
            for(int j = 0;j<2; j++)
                coords[i][j] = grille[i][j];
        }

    }
    else if(forme == 6){
        int grille[4][2] = { { -1, -1 }, { 0, -1 },  { 0, 0 },   { 0, 1 }};
        for(int i=0; i<4; i++){
            for(int j = 0;j<2; j++)
                coords[i][j] = grille[i][j];
        }

    }
    else if(forme == 7){
        int grille[4][2] = { { 1, -1 },  { 0, -1 },  { 0, 0 },   { 0, 1 }};
        for(int i=0; i<4; i++){
            for(int j = 0;j<2; j++)
                coords[i][j] = grille[i][j];
        }

    }

    m_forme = forme;

}

int Piece::minX(){
    int min = coords[0][0];
    for (int i = 1; i < 4; i++)
        min>coords[i][0]?min=coords[i][0]:min;
    return min;
}

int Piece::maxX(){
    int max = coords[0][0];
    for (int i = 1; i < 4; i++)
        max<coords[i][0]?max=coords[i][0]:max;
    return max;
}

int Piece::minY(){
    int min = coords[0][1];
    for (int i = 1; i < 4; i++)
        min>coords[i][1]?min=coords[i][1]:min;
    return min;
}

int Piece::maxY(){
    int max = coords[0][1];
    for (int i = 1; i < 4; i++)
        max<coords[i][1]?max=coords[i][1]:max;
    return max;
}


Piece Piece::rotationPiece(){
    if (m_forme == Carre)
        return *this;

    Piece resultat;
    resultat.m_forme = m_forme;
    for (int i = 0; i < 4; ++i) {
        resultat.setX(i, -getY(i));
        resultat.setY(i, getX(i));
    }

    return resultat;
}

void Piece::setFormeRandom(){
    setForme(Formes((rand() % 7)+1));//on choisit une forme randomique

}

