/*
 * The main display window for nesT.
 */

#ifndef INCLUDED_NEST_MAIN_WINDOW_HPP
#define INCLUDED_NEST_MAIN_WINDOW_HPP

#include <QMainWindow>
#include <QMenuBar>
#include <QAction>
#include <QMenu>
#include <QString>

class main_window : public QMainWindow
{
	Q_OBJECT

public:
	main_window(QWidget *parent = 0);
	virtual ~main_window();

	virtual void show_message(const QString& title, const QString& message);
	virtual bool ask_question(const QString& title, const QString& question);
	virtual void show_error(const QString& title, const QString& error);

protected:
	QAction *open_action;
	QAction *exit_action;
	QMenu   *file_menu;

	QString  rom_dir;

protected slots:
	virtual void select_rom();

private:
	// nothing for now
};

#endif // INCLUDED_NEST_MAIN_WINDOW_HPP
