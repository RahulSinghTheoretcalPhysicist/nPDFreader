#pragma once

#include <QMainWindow>
#include <QString>

class QAction;
class QLabel;
class DocumentCanvas;

class MainWindow final : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);

private slots:
    void openPdf();
    void closeDocument();
    void showAbout();

private:
    void createActions();
    void createMenus();
    void createToolBar();
    void createStatusBar();
    void updateWindowTitle();

    DocumentCanvas *m_canvas = nullptr;
    QLabel *m_documentStatus = nullptr;

    QAction *m_openAction = nullptr;
    QAction *m_closeAction = nullptr;
    QAction *m_saveAction = nullptr;
    QAction *m_previousPageAction = nullptr;
    QAction *m_nextPageAction = nullptr;
    QAction *m_zoomOutAction = nullptr;
    QAction *m_zoomInAction = nullptr;
    QAction *m_fitPageAction = nullptr;
    QAction *m_twoPageAction = nullptr;

    QString m_currentFilePath;
};
