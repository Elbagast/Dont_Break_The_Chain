#include "main_window.h"
#include "ui_main_window.h"

#include "chain_widget.h"
#include "new_chain_dialog.h"

#include <QVBoxLayout>
#include <QDate>
#include <QDir>

Chain::Main_Window::Main_Window(QString const& dir_path, QWidget* parent) :
    QMainWindow(parent),
    m_ui(std::make_unique<Ui::Main_Window>()),
    m_dir_path(dir_path),
    m_scrollarea_contents_widget(make_quptr<QWidget>()),
    m_scrollarea_contents_layout(make_quptr<QVBoxLayout>()),
    m_chain_widgets()
{
    m_ui->setupUi(this);
    this->setWindowTitle("Don't Break the Chain");

    // Configure the scroll widget contents
    m_ui->scrollArea->setWidget(m_scrollarea_contents_widget.get());
    m_scrollarea_contents_widget->setLayout(m_scrollarea_contents_layout.get());
    m_scrollarea_contents_layout->addStretch(1);

    // Connect the menu actions
    QObject::connect(m_ui->action_New_Chain, &QAction::triggered,
                     this, &Main_Window::action_slot_New_Chain);
    QObject::connect(m_ui->action_Exit, &QAction::triggered,
                     this, &Main_Window::action_slot_Exit);

    // Scan the directory for .chain files and load them
    QDir chain_dir{m_dir_path};

    // Make a filter for files we care about: "*.chain" or whatever the extension is
    QString name_filter{"*"};
    name_filter.append(Chain_Data::file_extension());

    // Get all the entries in the dir that are files with the .chain extension
    QStringList file_names = chain_dir.entryList({name_filter}, QDir::Files);

    // Load each chain file
    for (QString const& file_name : file_names)
    {
        load_chain(chain_dir.filePath(file_name));
    }
}

Chain::Main_Window::~Main_Window()
{
    for (auto const& widget : m_chain_widgets)
    {
        widget->save();
    }
}

void Chain::Main_Window::add_chain(QString const& title, QString const& description, QColor colour, QDate start_date)
{
    m_chain_widgets.push_back(make_quptr<Chain_Widget>(m_dir_path, title, description, colour, start_date, this));
    m_scrollarea_contents_layout->insertWidget(m_scrollarea_contents_layout->count() - 1, m_chain_widgets.back().get());
}

void Chain::Main_Window::load_chain(QString const& file_path)
{
    m_chain_widgets.push_back(make_quptr<Chain_Widget>(file_path));
    m_scrollarea_contents_layout->insertWidget(m_scrollarea_contents_layout->count() - 1, m_chain_widgets.back().get());
}

void Chain::Main_Window::action_slot_New_Chain()
{
    New_Chain_Dialog dialog{this};

    if (dialog.exec() == QDialog::Accepted && dialog.has_valid_selections())
    {
        QDate date = dialog.date();
        add_chain(dialog.title(), dialog.description(), dialog.colour(), date);
    }
}

void Chain::Main_Window::action_slot_Exit()
{
    this->close();
}
