/*
 * The main display window for nesT.
 */

#include <fstream>
#include <iostream>
#include <stdexcept>
#include <QApplication>
#include <QKeySequence>
#include <QFileDialog>
#include <QMessageBox>
#include <QDir>
#include "MainWindow.hpp"
#include "rom.hpp"

//#include <iostream>

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
{
	// Add File Menu
	m_openAction = new QAction(tr("&Open..."), this);
	m_openAction->setShortcuts(QKeySequence::Open);
	m_openAction->setStatusTip(tr("Open a new ROM"));
	connect(m_openAction, SIGNAL(triggered()), this, SLOT(selectRom()));

	m_exitAction = new QAction(tr("E&xit"), this);
	m_exitAction->setStatusTip(tr("Exit nesT"));
	connect(m_exitAction, SIGNAL(triggered()), QApplication::instance(), SLOT(quit()));
	
	m_fileMenu = menuBar()->addMenu(tr("&File"));
	m_fileMenu->addAction(m_openAction);
	m_fileMenu->addAction(m_exitAction);

	m_canvas = new RomCanvas(this);
	setCentralWidget(m_canvas);
	m_canvas->show();

	m_canvas->displayText(tr("Hello, world! Blah, blah, blah..."), 0);
	m_romDir = QDir::homePath();
}

MainWindow::~MainWindow()
{
	// child widgets' destructors are automatically called by the parent widget's destructor.  
  	// In our case the QActions and QMenus are deleted by the QMainWindow destructor
}

/* A slot that allows a user to select a rom using the File Open dialog. */
void MainWindow::selectRom()
{
	// TODO: Support for opening compressed files
	QString filepath = QFileDialog::getOpenFileName(this, tr("Select ROM"), m_romDir,
													tr("NES ROMs (*.nes)"), NULL, NULL);

	if(!filepath.isNull())
	{
		std::ifstream file(filepath.toAscii().constData());

		try
		{
			rom rom(file);
		}
		catch(std::runtime_error e)
		{
			QString error = tr("Exception occurred when trying to open ") + filepath + ":\n\n " +
				e.what() + "\n\n" + tr("The rom file might be corrupt.");
			showError(tr("Could not open ROM"), error);
		}
		// File dialogs that don't remember where you last were are annoying =)
		m_romDir = filepath;
	}
}

/* Display an information box with the given title and message.  The box will have an OK button on
 * it.
 */
void MainWindow::showMessage(const QString& title, const QString& message)
{
	QMessageBox::information(this, title, message, QMessageBox::Ok, QMessageBox::Ok);
}

/* Display a dialog box that asks the user a yes/no question.  The box will have Yes and No buttons
 * on it.  Return True if the user clicked Yes and False otherwise.
 */ 
bool MainWindow::askQuestion(const QString& title, const QString& question)
{
	QMessageBox::StandardButton button;
	button = QMessageBox::question(this, title, question, QMessageBox::Yes | QMessageBox::No,
								   QMessageBox::No);
	return QMessageBox::Yes == button;
}

/* Display an error message to the user with the given title and message.  The box will have an OK
 * button on it.
 */
void MainWindow::showError(const QString& title, const QString& error)
{
	QMessageBox::critical(this, title, error, QMessageBox::Ok, QMessageBox::Ok);
}

/* What to do when the window is resized by a QT Resize Event.  For now, we're just moving the
 * message box.
 */
void MainWindow::resizeEvent(QResizeEvent *event)
{
	m_canvas->displayText(tr("Hello, world! Blah, blah, blah..."), 0);
	
	emit resized();
	QMainWindow::resizeEvent(event);
}
