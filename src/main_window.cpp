/*
 * I'll add something here...maybe.
 */

#include <fstream>
#include <stdexcept>
#include <QApplication>
#include <QKeySequence>
#include <QFileDialog>
#include <QMessageBox>
#include <QDir>
#include "main_window.hpp"
#include "rom.hpp"

#include <iostream>

main_window::main_window(QWidget *parent)
	: QMainWindow(parent)
{
	// Add File Menu
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

	canvas = new rom_canvas(this);
	setCentralWidget(canvas);
	canvas->show();

	rom_dir = QDir::homePath();
}

main_window::~main_window()
{
	// child widgets' destructors are automatically called by the parent widget's destructor.  
  	// In our case the QActions and QMenus are deleted by the QMainWindow destructor
}

/* A slot that allows a user to select a rom using the File Open dialog. */
void main_window::select_rom()
{
	// TODO: Support for opening compressed files
	QString filepath = QFileDialog::getOpenFileName(this, tr("Select ROM"), rom_dir,
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
			show_error(tr("Could not open ROM"), error);
		}
		// File dialogs that don't remember where you last were are annoying =)
		rom_dir = filepath;
	}
}

/* Display an information box with the given title and message.  The box will have an OK button on
 * it.
 */
void main_window::show_message(const QString& title, const QString& message)
{
	QMessageBox::information(this, title, message, QMessageBox::Ok, QMessageBox::Ok);
}

/* Display a dialog box that asks the user a yes/no question.  The box will have Yes and No buttons
 * on it.  Return True if the user clicked Yes and False otherwise.
 */ 
bool main_window::ask_question(const QString& title, const QString& question)
{
	QMessageBox::StandardButton button;
	button = QMessageBox::question(this, title, question, QMessageBox::Yes | QMessageBox::No,
								   QMessageBox::No);
	return QMessageBox::Yes == button;
}

/* Display an error message to the user with the given title and message.  The box will have an OK
 * button on it.
 */
void main_window::show_error(const QString& title, const QString& error)
{
	QMessageBox::critical(this, title, error, QMessageBox::Ok, QMessageBox::Ok);
}
