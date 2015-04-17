#include "chain_data.h"
#include <cassert>
#include <QFile>
#include <QTextStream>
//#include <QDebug>

QString const Chain::Chain_Data::s_file_extension = QString(".chain");

Chain::Chain_Data::Chain_Data(QString const& dir_path, QString const& title, QString const& description, QColor colour, QDate start_date):
    m_filepath(),
    m_title(title),
    m_description(description),
    m_colour(colour),
    m_start_date(start_date),
    m_chain()
{
    m_filepath = dir_path;
    m_filepath.append("/");
    m_filepath.append(m_title);
    m_filepath.append(file_extension());
    append_links_until_today(start_date);
}

Chain::Chain_Data::Chain_Data(QString const& dir_path, QString const& filepath):
    m_filepath(),
    m_title(),
    m_description(),
    m_colour(),
    m_start_date(),
    m_chain()
{
    m_filepath = dir_path;
    m_filepath.append("/");
    m_filepath.append(filepath);
    load();
    append_links_until_today();
}

void Chain::Chain_Data::save() const
{
    //qDebug() << "Save: " << m_filepath;
    QFile file{m_filepath};

    if (file.open(QFile::WriteOnly | QFile::Truncate | QFile::Text))
    {
        //qDebug() << "File opened";

        QTextStream out_stream(&file);

        //qDebug() << static_cast<QFile*>(out_stream.device())->fileName();

        out_stream << m_title;
        endl(out_stream);

        out_stream << m_description;
        endl(out_stream);

        out_stream << m_colour.name();
        endl(out_stream);

        out_stream << m_start_date.toString();
        endl(out_stream);

        for (bool link : m_chain)
        {
            out_stream << link;// << ' ';
        }
        endl(out_stream);

        out_stream.flush();

        file.close();
    }
}

void Chain::Chain_Data::load()
{
    //qDebug() << "Load: " << m_filepath;
    QFile file{m_filepath};
    assert(file.exists());
    if (file.open(QFile::ReadOnly | QFile::Text))
    {
        //qDebug() << "File opened";

        QTextStream in_stream(&file);

        m_title = in_stream.readLine();

        m_description = in_stream.readLine();

        m_colour = in_stream.readLine();

        m_start_date = QDate::fromString(in_stream.readLine());

        QString chain = in_stream.readLine();
        assert(!chain.isEmpty());
        for (int index = 0, end = chain.size(); index != end; ++index)
        {
            //qDebug() << "index: " << index << " = " << chain[index];
            if (chain[index] == '0')
            {
                m_chain.push_back(false);
            }
            else if (chain[index] == '1')
            {
                m_chain.push_back(true);
            }
            else
            {
                assert(0);
            }
        }




        file.close();
    }
}

QString const& Chain::Chain_Data::title() const
{
    return m_title;
}

QString const& Chain::Chain_Data::description() const
{
    return m_description;
}

QColor Chain::Chain_Data::colour() const
{
    return m_colour;
}

QDate Chain::Chain_Data::start_date() const
{
    return m_start_date;
}

QDate Chain::Chain_Data::end_date() const
{
    return m_start_date.addDays(m_chain.size() - 1);
}

QList<bool>& Chain::Chain_Data::chain()
{
    return m_chain;
}

QList<bool> const& Chain::Chain_Data::chain() const
{
    return m_chain;
}

bool Chain::Chain_Data::link(int index) const
{
    return m_chain.at(index);
}

bool Chain::Chain_Data::link(int week, int weekday) const
{
     return m_chain.at(index_from(week, weekday));
}

//bool Chain::Chain_Data::link(QDate date) const
//{
//
//}

QDate Chain::Chain_Data::link_date(int index) const
{
    return start_date().addDays(index);
}

QDate Chain::Chain_Data::link_date(int week, int weekday) const
{
    return start_date().addDays(index_from(week, weekday));
}


void Chain::Chain_Data::set_title(QString const& value)
{
    m_title = value;
}

void Chain::Chain_Data::set_description(QString const& value)
{
    m_description = value;
}

void Chain::Chain_Data::set_colour(QColor colour)
{
    m_colour = colour;
}

void Chain::Chain_Data::set_colour(int red, int green, int blue)
{
    m_colour = QColor(red, green, blue);
}

void Chain::Chain_Data::set_link(int index, bool state)
{
    m_chain[index] = state;
}

void Chain::Chain_Data::set_link(int week, int weekday, bool state)
{
    m_chain[index_from(week, weekday)] = state;
}

//void Chain::Chain_Data::set_link(QDate date, bool state)
//{
//
//}

void Chain::Chain_Data::append_links_until_today(QDate start)
{
    // end point is 1 passed today
    QDate end_day = QDate::currentDate().addDays(1);
    // start is a copy already
    for (auto begin = start.toJulianDay(), end = end_day.toJulianDay(); begin != end; ++begin)
    {
        m_chain.push_back(false);
    }
}

void Chain::Chain_Data::append_links_until_today()
{
    // Start after the end of currently stored data
    QDate start = end_date().addDays(1);
    append_links_until_today(start);
}

int Chain::Chain_Data::day_count() const
{
    return m_chain.size();
}

int Chain::Chain_Data::week_count() const
{
    // The number of days the chain spans
    int days = day_count();
    // Add days to make this into a factor of 7
    days += weekdays_before_start();
    days += weekdays_after_end();
    return days / 7;
}

int Chain::Chain_Data::weekdays_before_start() const
{
    // QDate week days are 1 = Mon ... 7 = Sun
    return start_date().dayOfWeek() - 1;
}

int Chain::Chain_Data::weekdays_after_end() const
{
    return 7 - start_date().dayOfWeek();
}

int Chain::Chain_Data::first_day_weekday() const
{
    return start_date().dayOfWeek();
}

int Chain::Chain_Data::last_day_weekday() const
{
    return end_date().dayOfWeek();
}

int Chain::Chain_Data::index_from(int week, int weekday) const
{
    return week * 7 + (weekday -1) - weekdays_before_start();
}

QString const& Chain::Chain_Data::file_extension()
{
    return s_file_extension;
}
