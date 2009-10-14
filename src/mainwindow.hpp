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

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	explicit MainWindow(QWidget *parent = 0);
	virtual ~MainWindow();

	virtual void showMessage(const QString& title, const QString& message);
	virtual bool askQuestion(const QString& title, const QString& question);
	virtual void showError(const QString& title, const QString& error);

protected:
	QAction *m_openAction;
	QAction *m_exitAction;
	QMenu   *m_fileMenu;

	QString  m_romDir;

	RomCanvas *m_canvas;

	virtual void resizeEvent(QResizeEvent *event);

protected slots:
	virtual void selectRom();

signals:
	void resized();

private:
	// nothing for now
};

#endif // INCLUDED_NEST_MAIN_WINDOW_HPP
