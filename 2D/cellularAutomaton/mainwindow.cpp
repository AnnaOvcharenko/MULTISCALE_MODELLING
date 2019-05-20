#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "grid.h"
#include <iostream>
#include <windows.h>
#include <thread>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->comboBox->addItem("Glider");
    ui->comboBox->addItem("Oscillator");
    ui->comboBox->addItem("Invariable");
    ui->comboBox->addItem("Random");
    ui->comboBox->addItem("From file");
    //ui->comboBox->addItem("Manual definition");

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *event)
{
              QPainter painter(this);
              int cellSize=10;


              if(isButtonDrawClicked)
              {
                 // Do the drawing here - as in your current draw() function                  
                  painter.setPen(QPen(Qt::black, 1, Qt::SolidLine));

                  //Paint grid itself:
                   painter.fillRect(110,30,grid.numberOfCellsX*cellSize,grid.numberOfCellsY*cellSize, QBrush(Qt::white));
                  //vertical
                  for (int i=0;i<=grid.numberOfCellsX;++i) {
                      //painter.setPen(QPen(Qt::black, 2, Qt::SolidLine));
                      painter.drawLine(110+cellSize*i, 30, 110+cellSize*i, 30+grid.numberOfCellsY*cellSize);
                  }
                  //horizontal
                  for (int i=0;i<=grid.numberOfCellsY;++i) {
                      //painter.setPen(QPen(Qt::black, 2, Qt::SolidLine));
                      painter.drawLine(110, 30+cellSize*i, 110+grid.numberOfCellsX*cellSize,30+cellSize*i );
                  }

                  //Fill cells with appropriate color(start set):
                  for (int step=0;step<grid.numberOfCellsY;++step) {
                      for (int i=0;i<grid.numberOfCellsX;++i) {

                           if(grid.currentGrid[i][step].getState())
                               painter.fillRect(110+cellSize*i,30+cellSize*step,cellSize,cellSize,  QBrush(Qt::black));
                      }
                  }

                  isButtonDrawClicked=false;

              }

              if(isButtonStartClicked){

                   painter.setPen(QPen(Qt::black, 1, Qt::SolidLine));

                  // while(true){

                       //Paint grid itself:
                        painter.fillRect(110,30,grid.numberOfCellsX*cellSize,grid.numberOfCellsY*cellSize, QBrush(Qt::white));
                       //vertical
                       for (int i=0;i<=grid.numberOfCellsX;++i) {
                           //painter.setPen(QPen(Qt::black, 2, Qt::SolidLine));
                           painter.drawLine(110+cellSize*i, 30, 110+cellSize*i, 30+grid.numberOfCellsY*cellSize);
                       }
                       //horizontal
                       for (int i=0;i<=grid.numberOfCellsY;++i) {
                           //painter.setPen(QPen(Qt::black, 2, Qt::SolidLine));
                           painter.drawLine(110, 30+cellSize*i, 110+grid.numberOfCellsX*cellSize,30+cellSize*i );
                       }
                            cout<<"paint main"<<endl;

                       //Fill cells with appropriate color(start set):
                       for (int step=0;step<grid.numberOfCellsY;++step) {
                           for (int i=0;i<grid.numberOfCellsX;++i) {

                                if(grid.currentGrid[i][step].getState())
                                    painter.fillRect(110+cellSize*i,30+cellSize*step,cellSize,cellSize,  QBrush(Qt::black));


                           }
                       }


                  isButtonStartClicked=false;
              }

              QWidget::paintEvent(event); // call the base class so everything else is drawn OK
}

void MainWindow::on_drawButton_clicked()
{
    int numberOfCellsX=stoi((ui->numberOfCellsXBox->text()).toStdString());
    int numberOfCellsY=stoi((ui->numberOfCellsYBox->text()).toStdString());
   // int rule = stoi((ui->ruleBox->text()).toStdString());

    grid = Grid(numberOfCellsX, numberOfCellsY);

    if(ui->comboBox->currentText()=="Glider"){
        grid.setGlider();
    }
    else if (ui->comboBox->currentText()=="Oscillator") {
        grid.setOscillator();
    }
    else if (ui->comboBox->currentText()=="Invariable") {
        grid.setInvariable();
    }
    else if (ui->comboBox->currentText()=="Random") {
        grid.setRandom();
    }
    else if (ui->comboBox->currentText()=="From file") {
        grid.readFromFile("E:\\AGH\\Modelowanie\\2D\\cellularAutomaton\\data.txt");
    }
    else if (ui->comboBox->currentText()=="Manual definition") {
        grid.killThemAll();
    }


    //grid.readFromFile("E:\\AGH\\Modelowanie\\2D\\cellularAutomaton\\data.txt");
    //grid.Generate();

    isButtonDrawClicked = true;
    update();
}

void MainWindow::thr(MainWindow* m){
    while(!m->isButtonStopClicked){
        m->isButtonStartClicked=true;
        m->grid.Generate();
        m->update();
        Sleep(100);

    }
}

void MainWindow::on_startButton_clicked()
{

   isButtonStopClicked=false;
   std::thread *first=new std::thread(thr,this);


}

void MainWindow::on_stopButton_clicked()
{
    isButtonStopClicked=true;
}
