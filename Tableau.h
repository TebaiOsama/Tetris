#ifndef TABLEAU_H
#define TABLEAU_H

#include <QTimer>
#include <QFrame>
#include <QPointer>
#include <QLabel>

#include "Piece.h"

#define HAUTEUR 22
#define LARGEUR 10

class Tableau : public QFrame{
    Q_OBJECT

public:
    Tableau(QWidget *parent = nullptr);
    void setLabelPieceSuiv(QLabel *label);

    QSize sizeHint() const override;
    QSize minimumSizeHint() const override;

public slots:
    void start();
    void pause();

signals:
    void chmntScore(int score);

protected:
    void paintEvent(QPaintEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;
    void timerEvent(QTimerEvent *event) override;

private:

    Formes &formeDe(int x, int y) { return board[(y * LARGEUR) + x]; }
    int TempsMax() { return 1000; } //ajouter difficulter
    int LargeurFenetre() { return contentsRect().width() / LARGEUR; }
    int HauteurFenetre() { return contentsRect().height() / HAUTEUR; }
    void effacerTableau();
    void descenteInst();
    void descenteRapide();
    void descente(int haut);
    void effacerLignes();
    void newPiece();
    void pieceSuiv();
    bool deplace(const Piece &newPiece, int newX, int newY); //renvoie true si on peut deplacer la piece
    void dessiner(QPainter &painter, int x, int y, Formes forme);

    QBasicTimer timer;
    QPointer<QLabel> labelPieceSuiv;
    bool isStarted;
    bool isPaused;
    bool isEnAttente;
    Piece pieceCurr; //piece currante
    Piece pieceSucc; //piece suivante
    //coords actuelles
    int curX;
    int curY;
    int lignesSupp;
    int piecesTot;
    int pts;
    int niveau;
    Formes board[LARGEUR * HAUTEUR];
};

#endif
