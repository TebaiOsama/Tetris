#include "Tableau.h"
#include "Fenetre.h"

#include <QCoreApplication>
#include <QGridLayout>
#include <QLabel>
#include <QLCDNumber>
#include <QPushButton>

Fenetre::Fenetre(QWidget *parent): QWidget(parent), tableau(new Tableau)
{

    LabelPieceSuiv = new QLabel;
    LabelPieceSuiv->setFrameStyle(QFrame::Box | QFrame::Raised);
    LabelPieceSuiv->setAlignment(Qt::AlignCenter);
    tableau->setLabelPieceSuiv(LabelPieceSuiv);
//! [1]
    ptsLcd = new QLCDNumber(5);
    ptsLcd->setSegmentStyle(QLCDNumber::Filled);
//! [1]
    //levelLcd = new QLCDNumber(2);
    //levelLcd->setSegmentStyle(QLCDNumber::Filled);
    //linesLcd = new QLCDNumber(5);
    //linesLcd->setSegmentStyle(QLCDNumber::Filled);

//! [2]
    buttonStart = new QPushButton(tr("&Commencer"));
    buttonStart->setFocusPolicy(Qt::NoFocus);
    buttonQuit = new QPushButton(tr("&Arreter"));
    buttonQuit->setFocusPolicy(Qt::NoFocus);
    buttonPause = new QPushButton(tr("&Pause"));
//! [2] //! [3]
    buttonPause->setFocusPolicy(Qt::NoFocus);
//! [3] //! [4]

    connect(buttonStart, &QPushButton::clicked, tableau, &Tableau::start);
//! [4] //! [5]
    connect(buttonQuit , &QPushButton::clicked, qApp, &QCoreApplication::quit);
    connect(buttonPause, &QPushButton::clicked, tableau, &Tableau::pause);
#if __cplusplus >= 201402L
    connect(board, &TetrixBoard::scoreChanged,
            scoreLcd, qOverload<int>(&QLCDNumber::display));
    connect(board, &TetrixBoard::levelChanged,
            //levelLcd, qOverload<int>(&QLCDNumber::display));
    connect(board, &TetrixBoard::linesRemovedChanged,
            linesLcd, qOverload<int>(&QLCDNumber::display));
#else
    connect(tableau, &Tableau::chmntScore,
            ptsLcd, QOverload<int>::of(&QLCDNumber::display));
    //connect(board, &TetrixBoard::levelChanged,
            //levelLcd, QOverload<int>::of(&QLCDNumber::display));
    //connect(board, &TetrixBoard::linesRemovedChanged,
            //linesLcd, QOverload<int>::of(&QLCDNumber::display));
#endif
//! [5]

//! [6]
    QGridLayout *layout = new QGridLayout;
    layout->addWidget(creationLabel(tr("Prochaine piece")), 0, 0);
    layout->addWidget(LabelPieceSuiv, 1, 0);
    //layout->addWidget(createLabel(tr("LEVEL")), 2, 0);
    //layout->addWidget(levelLcd, 3, 0);
    layout->addWidget(buttonStart, 4, 0);
    layout->addWidget(tableau, 0, 1, 6, 1);
    layout->addWidget(creationLabel(tr("Points")), 0, 2);
    layout->addWidget(ptsLcd, 1, 2);
    //layout->addWidget(createLabel(tr("Lignes enlevés")), 2, 2);
    //layout->addWidget(linesLcd, 3, 2);
    layout->addWidget(buttonQuit, 5, 2);
    layout->addWidget(buttonPause, 5, 0);
    setLayout(layout);

    setWindowTitle(tr("Tetris"));
    resize(550, 370);
}
//! [6]

//! [7]
QLabel *Fenetre::creationLabel(const QString &text)
{
    QLabel *label = new QLabel(text);
    label->setAlignment(Qt::AlignHCenter | Qt::AlignBottom);
    return label;
}
//! [7]
