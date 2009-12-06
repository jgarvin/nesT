/*
 * The main display window for nesT.
 */

#ifndef INCLUDED_NEST_MAIN_WINDOW_HPP
#define INCLUDED_NEST_MAIN_WINDOW_HPP

#include <QMainWindow>
#include <QMenuBar>
#include <QAction>
#include <QMenu>
#include <QResizeEvent>
#include <QString>
#include "romcanvas.hpp"
#include "renderer.hpp"
#include "rom.hpp"


class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	MainWindow(QWidget *parent, renderer *the_renderer);
	virtual ~MainWindow();

	virtual void showMessage(const QString& title, const QString& message);
	virtual bool askQuestion(const QString& title, const QString& question);
	virtual void showError(const QString& title, const QString& error);

protected:
	// File menu
	QMenu   *m_fileMenu;
	QAction *m_openAction;
	QAction *m_exitAction;

	// Tools menu
	QMenu   *m_toolsMenu;
	QAction *m_drawspritesAction;

	// Other stuff
	QString  m_romDir;
	RomCanvas *m_canvas;
	renderer *m_renderer;

	rom *m_rom;

	virtual void resizeEvent(QResizeEvent *event);

protected slots:
	virtual void selectRom();
	virtual void drawSprites();

signals:
	void resized();

private:
	// nothing for now
};

#endif // INCLUDED_NEST_MAIN_WINDOW_HPP
