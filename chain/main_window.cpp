#include "main_window.h"
#include "ui_main_window.h"

#include "chain_widget.h"
#include "new_chain_dialog.h"

#include <QVBoxLayout>
#include <QDate>

Chain::Main_Window::Main_Window(QWidget* parent) :
    QMainWindow(parent),
    m_ui(std::make_unique<Ui::Main_Window>()),
    m_scrollarea_contents_widget(make_quptr<QWidget>()),
    m_scrollarea_contents_layout(make_quptr<QVBoxLayout>()),
    m_chain_widgets()
{
    m_ui->setupUi(this);
    this->setWindowTitle("Don't Break the Chain");

    m_ui->scrollArea->setWidget(m_scrollarea_contents_widget.get());
    m_scrollarea_contents_widget->setLayout(m_scrollarea_contents_layout.get());
    m_scrollarea_contents_layout->addStretch(1);

    QObject::connect(m_ui->action_New_Chain, &QAction::triggered,
                     this, &Main_Window::action_slot_New_Chain);
    QObject::connect(m_ui->action_Exit, &QAction::triggered,
                     this, &Main_Window::action_slot_Exit);

    //add_chain("Test", "Stuff goes in here don't you know.", 2015,4,1);
    //add_chain("Half Life 3", "Blah blah blah Mr Freeman.", 2015,4,13);
}

Chain::Main_Window::~Main_Window() = default;

void Chain::Main_Window::add_chain(std::string const& title, std::string const& description, int year, int month, int day)
{
    add_chain(title, description, boost::gregorian::date(year, month, day));
}

void Chain::Main_Window::add_chain(std::string const& title, std::string const& description, boost::gregorian::date const& start_date)
{
    m_chain_widgets.push_back(make_quptr<Chain_Widget>(title, description, start_date, this));
    m_scrollarea_contents_layout->insertWidget(m_scrollarea_contents_layout->count() - 1, m_chain_widgets.back().get());
}

void Chain::Main_Window::action_slot_New_Chain()
{
    New_Chain_Dialog dialog{this};

    if (dialog.exec() == QDialog::Accepted)
    {
        QDate const& date = dialog.date();
        add_chain(dialog.title().toStdString(), dialog.description().toStdString(), date.year(), date.month(), date.day());
    }
}

void Chain::Main_Window::action_slot_Exit()
{
    this->close();
}
