/*
 * I'll add something here...maybe.
 */

#include <QKeySequence>
#include "main_window.hpp"

main_window::main_window(QWidget *parent)
	: QMainWindow(parent)
{
	open_action = new QAction(tr("&Open..."), this);
	open_action->setShortcuts(QKeySequence::Open);
	open_action->setStatusTip(tr("Open a new ROM"));
	connect(open_action, SIGNAL(triggered()), this, SLOT(open()));

	file_menu = menuBar()->addMenu(tr("&File"));
	file_menu->addAction(open_action);
}

main_window::~main_window()
{
	delete file_menu;
	delete open_action;
}
