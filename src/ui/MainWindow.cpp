#include "MainWindow.h"
#include "DocumentCanvas.h"

#include <QAction>
#include <QApplication>
#include <QFileDialog>
#include <QFileInfo>
#include <QKeySequence>
#include <QLabel>
#include <QMenu>
#include <QMenuBar>
#include <QMessageBox>
#include <QStatusBar>
#include <QStyle>
#include <QToolBar>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      m_canvas(new DocumentCanvas(this))
{
    setCentralWidget(m_canvas);
    resize(1180, 780);
    setMinimumSize(820, 560);

    createActions();
    createMenus();
    createToolBar();
    createStatusBar();
    updateWindowTitle();
}

void MainWindow::createActions()
{
    m_openAction = new QAction(
        style()->standardIcon(QStyle::SP_DialogOpenButton),
        tr("Open PDF"),
        this
    );
    m_openAction->setShortcut(QKeySequence::Open);
    connect(m_openAction, &QAction::triggered, this, &MainWindow::openPdf);

    m_closeAction = new QAction(tr("Close Document"), this);
    m_closeAction->setShortcut(QKeySequence::Close);
    m_closeAction->setEnabled(false);
    connect(m_closeAction, &QAction::triggered, this, &MainWindow::closeDocument);

    m_saveAction = new QAction(
        style()->standardIcon(QStyle::SP_DialogSaveButton),
        tr("Save"),
        this
    );
    m_saveAction->setShortcut(QKeySequence::Save);
    m_saveAction->setEnabled(false);
    m_saveAction->setToolTip(tr("Saving arrives after PDF document integration"));

    m_previousPageAction = new QAction(tr("Previous"), this);
    m_previousPageAction->setShortcut(QKeySequence(Qt::Key_PageUp));
    m_previousPageAction->setEnabled(false);

    m_nextPageAction = new QAction(tr("Next"), this);
    m_nextPageAction->setShortcut(QKeySequence(Qt::Key_PageDown));
    m_nextPageAction->setEnabled(false);

    m_zoomOutAction = new QAction(tr("Zoom Out"), this);
    m_zoomOutAction->setShortcut(QKeySequence::ZoomOut);
    m_zoomOutAction->setEnabled(false);

    m_zoomInAction = new QAction(tr("Zoom In"), this);
    m_zoomInAction->setShortcut(QKeySequence::ZoomIn);
    m_zoomInAction->setEnabled(false);

    m_fitPageAction = new QAction(tr("Fit Page"), this);
    m_fitPageAction->setCheckable(true);
    m_fitPageAction->setChecked(true);
    m_fitPageAction->setEnabled(false);

    m_twoPageAction = new QAction(tr("Two Page"), this);
    m_twoPageAction->setCheckable(true);
    m_twoPageAction->setEnabled(false);
}

void MainWindow::createMenus()
{
    QMenu *fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(m_openAction);
    fileMenu->addAction(m_saveAction);
    fileMenu->addSeparator();
    fileMenu->addAction(m_closeAction);
    fileMenu->addSeparator();

    QAction *exitAction = fileMenu->addAction(tr("Exit"));
    exitAction->setShortcut(QKeySequence::Quit);
    connect(exitAction, &QAction::triggered, qApp, &QApplication::quit);

    QMenu *viewMenu = menuBar()->addMenu(tr("&View"));
    viewMenu->addAction(m_zoomOutAction);
    viewMenu->addAction(m_zoomInAction);
    viewMenu->addSeparator();
    viewMenu->addAction(m_fitPageAction);
    viewMenu->addAction(m_twoPageAction);

    QMenu *helpMenu = menuBar()->addMenu(tr("&Help"));
    QAction *aboutAction = helpMenu->addAction(tr("About PDF Reader"));
    connect(aboutAction, &QAction::triggered, this, &MainWindow::showAbout);
}

void MainWindow::createToolBar()
{
    QToolBar *toolbar = addToolBar(tr("Main Toolbar"));
    toolbar->setObjectName(QStringLiteral("MainToolbar"));
    toolbar->setMovable(false);
    toolbar->setFloatable(false);
    toolbar->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);

    toolbar->addAction(m_openAction);
    toolbar->addAction(m_saveAction);
    toolbar->addSeparator();
    toolbar->addAction(m_previousPageAction);
    toolbar->addAction(m_nextPageAction);
    toolbar->addSeparator();
    toolbar->addAction(m_zoomOutAction);
    toolbar->addAction(m_zoomInAction);
    toolbar->addAction(m_fitPageAction);
    toolbar->addSeparator();
    toolbar->addAction(m_twoPageAction);
}

void MainWindow::createStatusBar()
{
    m_documentStatus = new QLabel(tr("No document open"), this);
    statusBar()->addWidget(m_documentStatus, 1);

    QLabel *versionLabel = new QLabel(
        tr("PDFReader %1").arg(QApplication::applicationVersion()),
        this
    );
    statusBar()->addPermanentWidget(versionLabel);
}

void MainWindow::openPdf()
{
    const QString filePath = QFileDialog::getOpenFileName(
        this,
        tr("Open PDF"),
        QString(),
        tr("PDF Documents (*.pdf);;All Files (*.*)")
    );

    if (filePath.isEmpty()) {
        return;
    }

    m_currentFilePath = filePath;
    m_canvas->setOpenedFile(filePath);
    m_closeAction->setEnabled(true);

    const QFileInfo info(filePath);
    m_documentStatus->setText(
        tr("Selected: %1").arg(info.fileName())
    );

    updateWindowTitle();
}

void MainWindow::closeDocument()
{
    m_currentFilePath.clear();
    m_canvas->clearDocument();
    m_closeAction->setEnabled(false);
    m_documentStatus->setText(tr("No document open"));
    updateWindowTitle();
}

void MainWindow::showAbout()
{
    QMessageBox::about(
        this,
        tr("About PDF Reader"),
        tr(
            "PDF Reader %1\n\n"
            "Phase 1 establishes the native Qt/C++ Windows application shell, "
            "CMake project, document viewport, and automated GitHub Windows build.\n\n"
            "PDFium rendering is added in Phase 2."
        ).arg(QApplication::applicationVersion())
    );
}

void MainWindow::updateWindowTitle()
{
    if (m_currentFilePath.isEmpty()) {
        setWindowTitle(tr("PDF Reader"));
        return;
    }

    setWindowTitle(
        tr("%1 - PDF Reader").arg(QFileInfo(m_currentFilePath).fileName())
    );
}
