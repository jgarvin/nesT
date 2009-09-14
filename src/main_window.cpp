/*
 * I'll add something here...maybe.
 */

#include <QApplication>
#include <QKeySequence>
#include <QFileDialog>
#include <QMessageBox>
#include <QString>
#include <QDir>
#include "main_window.hpp"

main_window::main_window(QWidget *parent)
	: QMainWindow(parent)
{
	open_action = new QAction(tr("&Open..."), this);
	open_action->setShortcuts(QKeySequence::Open);
	open_action->setStatusTip(tr("Open a new ROM"));
	connect(open_action, SIGNAL(triggered()), this, SLOT(select_rom()));

	exit_action = new QAction(tr("E&xit"), this);
	exit_action->setStatusTip(tr("Exit nesT"));
	connect(exit_action, SIGNAL(triggered()), QApplication::instance(), SLOT(quit()));

	file_menu = menuBar()->addMenu(tr("&File"));
	file_menu->addAction(open_action);
	file_menu->addAction(exit_action);
}

main_window::~main_window()
{
	delete file_menu;
	delete open_action;
	delete exit_action;
}

/* A slot that allows a user to select a rom using the File Open dialog. */
void main_window::select_rom()
{
	// TODO:  Support for compressed files (zip, 7z, tar.gz, etc.)
	QString filepath = QFileDialog::getOpenFileName(this, tr("Select ROM"), QDir::homePath(),
													tr("NES ROMs (*.nes)"), NULL, NULL);
	QString message;

	if (filepath.isNull())
		message = tr("No games for you today?  How sad.");
	else
		message = tr("You want to play ") + filepath + tr("?  Good choice!");
		
	QMessageBox::information(this, tr("Test Box"), message, QMessageBox::Ok, QMessageBox::Ok);
} 
