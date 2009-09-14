/*
 * The main display window for nesT.
 */

#include <QMainWindow>
#include <QMenuBar>
#include <QAction>
#include <QMenu>

class main_window : public QMainWindow
{
	Q_OBJECT

public:
	main_window(QWidget *parent = 0);
	virtual ~main_window();

protected:
	QAction *open_action;
	QAction *exit_action;
	QMenu   *file_menu;

protected slots:
	void select_rom();

private:
	// nothing for now
};
