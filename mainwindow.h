#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class ContactBookWindow;
class AnalysisWindow;


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onExitButtonClicked();
    void onSelectPersonButtonClicked();
    void onCompareButtonClicked();


private:
    Ui::MainWindow *ui;
    ContactBookWindow *contactBookWindow;
    AnalysisWindow *analysisWindow;

    void setupConnections();
};
#endif // MAINWINDOW_H
