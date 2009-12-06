/*
 * The main display window for nesT.
 */

#include <fstream>
#include <iostream>
#include <stdexcept>
#include <vector>
#include <QApplication>
#include <QKeySequence>
#include <QFileDialog>
#include <QMessageBox>
#include <QDir>
#include <toast/assert.hpp>
#include "nest_shared.hpp"
#include "mainwindow.hpp"
#include "sprite.hpp"

#include <iostream>

MainWindow::MainWindow(QWidget *parent, renderer *the_renderer)
	: QMainWindow(parent)
{
	TOAST_ASSERT_NOT_NULL(the_renderer);
	m_renderer = the_renderer;

    //TODO: Break these menus out into separate methods or objects so that we don't end up with a
    //      giant evil constructor of ultimate doom!

	// Add File Menu
	m_fileMenu = menuBar()->addMenu(tr("&File"));

	m_openAction = new QAction(tr("&Open..."), this);
	m_openAction->setShortcuts(QKeySequence::Open);
	m_openAction->setStatusTip(tr("Open a new ROM"));
	connect(m_openAction, SIGNAL(triggered()), this, SLOT(selectRom()));

	m_exitAction = new QAction(tr("E&xit"), this);
	m_exitAction->setStatusTip(tr("Exit nesT"));
	connect(m_exitAction, SIGNAL(triggered()), QApplication::instance(), SLOT(quit()));
	
	m_fileMenu->addAction(m_openAction);
	m_fileMenu->addAction(m_exitAction);

	// Add Tools Menu
	m_toolsMenu = menuBar()->addMenu(tr("&Tools"));
	
	m_drawspritesAction = new QAction(tr("&Draw Sprites"), this);
	m_drawspritesAction->setStatusTip(tr("Display the ROM's sprites"));
	connect(m_drawspritesAction, SIGNAL(triggered()), this, SLOT(drawSprites()));

	m_toolsMenu->addAction(m_drawspritesAction);

	// Set up other stuff
	m_canvas = new RomCanvas(this, the_renderer);
	setCentralWidget(m_canvas);
	m_canvas->show();

	m_canvas->displayText(tr("Hello, world!"));
	m_romDir = QDir::homePath();

	m_rom = NULL;
}

MainWindow::~MainWindow()
{
	// child widgets' destructors are automatically called by the parent widget's destructor.  
  	// In our case the QActions and QMenus are deleted by the QMainWindow destructor

	delete m_rom;
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
			if(m_rom != NULL)
				delete m_rom;

			m_rom = new rom(file);
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

/* Draws all sprites inside a ROM's character memory.  Some ROMs do not use character memory and
 * just load stuff manually from program memory (like Final Fantasy).  We don't support that just
 * yet here.
 */
void MainWindow::drawSprites()
{
	if(m_rom != NULL)
	{
		std::vector<sprite*> sprites = m_rom->construct_sprites();
		std::vector<uint8_t> indices = {0x0F, 0x05, 0x0A, 0x02};  // black, red, green, blue
		sprite_attribute attr;
		nes_master_palette masterpalette;
		nes_color_palette  colorpalette(&masterpalette, &indices);
		render_context context = {&attr, &colorpalette};
		auto sprite_itr = sprites.begin();
		
		attr.x_pos = 0;
		attr.y_pos = 0;

		m_renderer->set_resolution(768, 720);
		m_renderer->update();

		for(; sprite_itr < sprites.end(); ++sprite_itr)
		{
			m_renderer->render((*sprite_itr)->data(), &context);

			attr.x_pos += 8;    // value is 8-bit, so it'll wrap around naturally
			
			if(0 == attr.x_pos)
				attr.y_pos += 8;
		}
	}
	else
	{
		m_canvas->displayText(tr("You need to open a ROM first!"));
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
	emit resized();
	QMainWindow::resizeEvent(event);
}
