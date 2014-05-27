#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "game.h"

#include <QMainWindow>

class QGraphicsScene;
class QGraphicsView;
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Game m_game;
    QGraphicsScene* m_scene;
    QGraphicsView* m_view;
};

#endif // MAINWINDOW_H
