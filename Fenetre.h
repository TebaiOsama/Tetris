#ifndef TETRIXWINDOW_H
#define TETRIXWINDOW_H

#include <QWidget>

QT_BEGIN_NAMESPACE
class QLCDNumber;
class QLabel;
class QPushButton;
QT_END_NAMESPACE

#include "Tableau.h"
//! [0]
class Fenetre : public QWidget
{
    Q_OBJECT

public:
    Fenetre(QWidget *parent = nullptr);

private:
    QLabel *creationLabel(const QString &text);

    Tableau *tableau;
    QLabel *LabelPieceSuiv;
    QLCDNumber *ptsLcd;
    //QLCDNumber *levelLcd;
    QLCDNumber *linesLcd;
    QPushButton *buttonStart;
    QPushButton *buttonQuit;
    QPushButton *buttonPause;
};
//! [0]

#endif
