#ifndef PIECE_H
#define PIECE_H

enum Formes { Vide, Z, S, Ligne, T, Carre, L, Linvers };


class Piece
{
private:
    //setteurs privés
    void setX(int index, int x);
    void setY(int index, int y);

    Formes m_forme; //nom de la forme d'une piece
    int coords[4][2]; //coordonnés de chaque bloque d'une piece

public:
    Piece(); //constructeur

    void setFormeRandom(); //choisi un forme aleatoire
    void setForme(Formes forme); //setteur de la forme

    Formes forme() const { return m_forme; }
    int getX(int index) const;
    int getY(int index) const;
    //min et max des coordonnes d'une piece
    int minX();
    int maxX();
    int minY();
    int maxY();

    Piece rotationPiece(); //fonction qui tourne la piece


};


#endif
