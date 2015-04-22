#include "main_window.h"
#include "ui_main_window.h"

#include "chain_widget.h"
#include "new_chain_dialog.h"

#include <QVBoxLayout>
#include <QDate>
#include <QDir>
#include <QFile>
#include <QTextStream>
#include <QXmlStreamWriter>
#include <QXmlStreamReader>
#include <QDebug>

Chain::Main_Window::Main_Window(QString const& filepath, QWidget* parent) :
    QMainWindow(parent),
    m_ui(std::make_unique<Ui::Main_Window>()),
    m_filepath(filepath),
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

    // load chains from the file at m_chain_filepath
    load_all();
}

Chain::Main_Window::~Main_Window()
{
    // save chains to the file at m_chain_filepath
    save_all();
}

void Chain::Main_Window::add_chain(QString const& title,
                                   QString const& description,
                                   QColor colour,
                                   QDate start_date,
                                   QList<bool> const& data)
{
    m_chain_widgets.push_back(make_quptr<Chain_Widget>(title, description, colour, start_date, data, this));
    m_scrollarea_contents_layout->insertWidget(m_scrollarea_contents_layout->count() - 1, m_chain_widgets.back().get());
}


void Chain::Main_Window::save_all() const
{
    //qDebug() << "Save: " << m_filepath;
    QFile file{m_filepath};

    if (file.open(QFile::WriteOnly | QFile::Truncate | QFile::Text))
    {
        //qDebug() << "File opened";

        //QTextStream out_stream(&file);

        //qDebug() << static_cast<QFile*>(out_stream.device())->fileName();
        QXmlStreamWriter xml_stream{&file};
        xml_stream.setAutoFormatting(true);
        xml_stream.writeStartDocument();

        // start the element that contains all the chains
        xml_stream.writeStartElement("all_chains");

        // for each chain, write a chain element
        for (auto const& widget : m_chain_widgets)
        {
            // start the element that contains this chain
            xml_stream.writeStartElement("chain");

            xml_stream.writeTextElement("title", widget->data().title());
            xml_stream.writeTextElement("description", widget->data().description());
            xml_stream.writeTextElement("colour", widget->data().colour().name());
            xml_stream.writeTextElement("start_date", widget->data().start_date().toString());

            QString data_string{};
            for (bool link : widget->data().chain())
            {
                data_string.push_back(link ? '1' : '0');
            }
            xml_stream.writeTextElement("data", data_string);

            // end the element that contains this chain
            xml_stream.writeEndElement();
        }

        // end the element that contains all the chains
        xml_stream.writeEndElement();

        xml_stream.writeEndDocument();

        file.close();
    }
}

void Chain::Main_Window::load_all()
{
    //qDebug() << "Load: " << m_filepath;
    QFile file{m_filepath};
    //assert(file.exists());
    if (file.exists() && file.open(QFile::ReadOnly | QFile::Text))
    {
        //qDebug() << "File opened";
        QXmlStreamReader xml_stream{&file};

        // while not at end or error
        while (!xml_stream.atEnd() && !xml_stream.hasError())
        {
            // read the next token
            xml_stream.readNext();
            //qDebug() << "XML: " << xml_stream.name().toString();

            // if the token is for chains
            if (xml_stream.name().toString() == "all_chains")
            {
                //qDebug() << "Now inside 'all_chains'";
                xml_stream.readNext();
                //qDebug() << "XML: " << xml_stream.name().toString();

                // while there are chain elements
                while (xml_stream.readNextStartElement() && xml_stream.name().toString() == "chain")
                {
                    //qDebug() << "Now inside 'chain'";
                    // variables to parse into
                    QString title{};
                    QString description{};
                    QColor colour{};
                    QDate start_date{};
                    QList<bool> data{};

                    // inside "chain", read its Elements
                    while (xml_stream.readNextStartElement())
                    {
                        //qDebug() << "XML: " << xml_stream.name().toString();
                        if (xml_stream.name().toString() == "title")
                        {
                            //qDebug() << "parse title";
                            title = xml_stream.readElementText();
                        }
                        else if (xml_stream.name().toString() == "description")
                        {
                            //qDebug() << "parse description";
                            description = xml_stream.readElementText();
                        }
                        else if (xml_stream.name().toString() == "colour")
                        {
                            //qDebug() << "parse colour";
                            colour = xml_stream.readElementText();
                        }
                        else if (xml_stream.name().toString() == "start_date")
                        {
                            //qDebug() << "parse start_date";
                            start_date = QDate::fromString(xml_stream.readElementText());
                        }
                        else if (xml_stream.name().toString() == "data")
                        {
                            //qDebug() << "parse data";
                            auto data_string = xml_stream.readElementText();
                            for (auto character : data_string)
                            {
                                if (character == '0')
                                {
                                    data.push_back(false);
                                }
                                else if (character == '1')
                                {
                                    data.push_back(true);
                                }
                                else
                                {
                                    //assert(0);
                                }
                            }
                        }
                    }
                    // build the chain widget
                    add_chain(title, description, colour, start_date, data);
                    // or break?

                }
                // else break?
            }
            // else break?
        }
        if (xml_stream.hasError())
        {
            // dummy for now
        }

        file.close();
    }
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
