#include "Tableau.h"

#include <QtGui>

Q_DECLARE_METATYPE(QPainter*)

Tableau::Tableau(QWidget *parent): QFrame(parent){

    isStarted = false;
    isPaused = false;
    setFrameStyle(QFrame::Panel | QFrame::Sunken);
    setFocusPolicy(Qt::StrongFocus);
    effacerTableau();

    pieceSucc.setFormeRandom();
}

void Tableau::setLabelPieceSuiv(QLabel *label){
    labelPieceSuiv = label;
}

QSize Tableau::sizeHint() const{
    return QSize(LARGEUR * 15 + frameWidth() * 2, HAUTEUR * 15 + frameWidth() * 2);
}

QSize Tableau::minimumSizeHint() const{
    return QSize(LARGEUR * 5 + frameWidth() * 2, HAUTEUR * 5 + frameWidth() * 2);
}

void Tableau::start(){
    if (isPaused)
        return;

    isStarted = true;
    isEnAttente = false;
    lignesSupp = 0;
    piecesTot = 0;
    pts = 0;
    effacerTableau();


    emit chmntScore(pts);

    newPiece();
    timer.start(TempsMax(), this);
}

void Tableau::pause(){
    if (!isStarted)
        return;


    if (!isPaused) {
        timer.stop();
    } else {
        timer.start(TempsMax(), this);
    }
    update();
}

void Tableau::paintEvent(QPaintEvent *event){
    QFrame::paintEvent(event);

    QPainter painter(this);
    QRect rect = contentsRect();
    int boardTop = rect.bottom() - HAUTEUR*HauteurFenetre();

    for (int i = 0; i < HAUTEUR; ++i) {
        for (int j = 0; j < LARGEUR; ++j) {
            Formes shape = formeDe(j, HAUTEUR - i - 1);
            if (shape != Vide)
                dessiner(painter, rect.left() + j * LargeurFenetre(), boardTop + i * HauteurFenetre(), shape);
        }
    }
    if (pieceCurr.forme() != Vide) {
        for (int i = 0; i < 4; ++i) {
            int x = curX + pieceCurr.getX(i);
            int y = curY - pieceCurr.getY(i);
            dessiner(painter, rect.left() + x * LargeurFenetre(), boardTop + (HAUTEUR - y - 1) * HauteurFenetre(), pieceCurr.forme());
        }
    }
}

void Tableau::keyPressEvent(QKeyEvent *event){
    if (!isStarted || isPaused || pieceCurr.forme() == Vide) {
        QFrame::keyPressEvent(event);
        return;
    }
    switch (event->key()) {
    case Qt::Key_Left:
        deplace(pieceCurr, curX - 1, curY);
        break;
    case Qt::Key_Right:
        deplace(pieceCurr, curX + 1, curY);
        break;
    case Qt::Key_Down:
        descenteRapide();
        break;
    case Qt::Key_Up:
        deplace(pieceCurr.rotationPiece(), curX, curY);
        break;
    case Qt::Key_Space:
        descenteInst();
        break;
    default:
        QFrame::keyPressEvent(event);
    }
}

void Tableau::timerEvent(QTimerEvent *event){
    if (event->timerId() == timer.timerId()) {
        if (isEnAttente) {
            isEnAttente = false;
            newPiece();
            timer.start(TempsMax(), this);
        } else {
            descenteRapide();
        }
    } else {
        QFrame::timerEvent(event);
    }
}

void Tableau::effacerTableau(){
    for (int i = 0; i < HAUTEUR * LARGEUR; i++)
        board[i] = Vide;
}

void Tableau::descenteInst(){
    int hauteur = 0;
    int newY = curY;
    while (newY > 0) {
        if (!deplace(pieceCurr, curX, newY - 1))
            break;
        newY--;
        hauteur++;
    }
    descente(hauteur);
}

void Tableau::descenteRapide(){
    if (!deplace(pieceCurr, curX, curY - 1))
        descente(0);
}

void Tableau::descente(int hauteur){
    for (int i = 0; i < 4; ++i) {
        int x = curX + pieceCurr.getX(i);
        int y = curY - pieceCurr.getY(i);
        formeDe(x, y) = pieceCurr.forme();
    }

    piecesTot++;
    /*
    if (piecesTot % 25 == 0) {
        ++niveau;
        timer.start(TempsMax(), this);
    }
*/
    pts += hauteur + 7;
    emit chmntScore(pts);
    effacerLignes();

    if (!isEnAttente)
        newPiece();
}

void Tableau::effacerLignes(){
    int numFullLines = 0;

    for (int i = HAUTEUR - 1; i >= 0; --i) {
        bool lineIsFull = true;

        for (int j = 0; j < LARGEUR; ++j) {
            if (formeDe(j, i) == Vide) {
                lineIsFull = false;
                break;
            }
        }

        if (lineIsFull) {
            ++numFullLines;
            for (int k = i; k < HAUTEUR - 1; ++k) {
                for (int j = 0; j < LARGEUR; ++j)
                    formeDe(j, k) = formeDe(j, k + 1);
            }
            for (int j = 0; j < LARGEUR; ++j)
                formeDe(j, HAUTEUR - 1) = Vide;
        }
    }
    if (numFullLines > 0) {
        lignesSupp += numFullLines;
        pts += 10 * numFullLines;
        emit chmntScore(pts);

        timer.start(500, this);
        isEnAttente = true;
        pieceCurr.setForme(Vide);
        update();
    }
}

void Tableau::newPiece(){
    pieceCurr = pieceSucc;
    pieceSucc.setFormeRandom();
    pieceSuiv();
    curX = LARGEUR / 2 + 1;
    curY = HAUTEUR - 1 + pieceCurr.minY();

    if (!deplace(pieceCurr, curX, curY)) {
        pieceCurr.setForme(Vide);
        timer.stop();
        isStarted = false;
        //message de defaite
    }
}

void Tableau::pieceSuiv(){
    if (!labelPieceSuiv)
        return;

    int dx = pieceSucc.maxX() - pieceSucc.minX() + 1;
    int dy = pieceSucc.maxY() - pieceSucc.minY() + 1;

    QPixmap pixmap(dx * LargeurFenetre(), dy * HauteurFenetre());
    QPainter painter(&pixmap);
    painter.fillRect(pixmap.rect(), labelPieceSuiv->palette().window());

    for (int i = 0; i < 4; ++i) {
        int x = pieceSucc.getX(i) - pieceSucc.minX();
        int y = pieceSucc.getY(i) - pieceSucc.minY();
        dessiner(painter, x * LargeurFenetre(), y * HauteurFenetre(),
                   pieceSucc.forme());
    }
    labelPieceSuiv->setPixmap(pixmap);
}

bool Tableau::deplace(const Piece &newPiece, int newX, int newY){
    for (int i = 0; i < 4; ++i) {
        int x = newX + newPiece.getX(i);
        int y = newY - newPiece.getY(i);
        if (x < 0 || x >= LARGEUR || y < 0 || y >= HAUTEUR)
            return false;
        if (formeDe(x, y) != Vide)
            return false;
    }
    pieceCurr = newPiece;
    curX = newX;
    curY = newY;
    update();
    return true;
}

void Tableau::dessiner(QPainter &painter, int x, int y, Formes forme){
    QRgb colorTable[8] = { 0x000000, 0x0000ff, 0xff0000, 0x7a7a7a, 0x00ffff, 0xffd700, 0x4b0082, 0xDAAA00};

    QColor color = colorTable[int(forme)];
    painter.fillRect(x + 1, y + 1, LargeurFenetre() - 2, HauteurFenetre() - 2, color);

    painter.setPen(color.lighter());
    painter.drawLine(x, y + HauteurFenetre() - 1, x, y);
    painter.drawLine(x, y, x + LargeurFenetre() - 1, y);

    painter.setPen(color.darker());
    painter.drawLine(x + 1, y + HauteurFenetre() - 1, x + LargeurFenetre() - 1, y + HauteurFenetre() - 1);
    painter.drawLine(x + LargeurFenetre() - 1, y + HauteurFenetre() - 1, x + LargeurFenetre() - 1, y + 1);
}
