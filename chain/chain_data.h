#ifndef CHAIN_DATA_H
#define CHAIN_DATA_H

#include <QString>
#include <QColor>
#include <QDate> // QDate contains only an integer so pass by value
#include <QList>

namespace Chain
{
    /*
    Chain_Data
    ====================================================================================================
    Data class that contains everything needed to represent a chain.
    */
    class Chain_Data
    {
    public:
        // By default a chain starts today
        Chain_Data(QString const& title, QString const& description, QColor colour, QDate start_date = QDate::currentDate());

        QString const& title() const;
        QString const& description() const;

        QColor colour() const;

        QDate start_date() const;
        QDate end_date() const;

        QList<bool>& chain();
        QList<bool> const& chain() const;

        bool link(int index) const;
        bool link(int week, int weekday) const;
        //bool link(QDate date) const;

        QDate link_date(int index) const;
        QDate link_date(int week, int weekday) const;

        void set_title(QString const& value);
        void set_description(QString const& value);

        void set_colour(QColor colour);
        void set_colour(int red, int green, int blue);

        void set_link(int index, bool state);
        void set_link(int week, int weekday, bool state);
        //void set_link(QDate date, bool state);

        // add links with dates between the last date stored and this day to the end of m_links
        void append_links_until_today(QDate start);
        void append_links_until_today();

        int day_count() const;
        int week_count() const;

        int weekdays_before_start() const;
        int weekdays_after_end() const;

        int first_day_weekday() const;
        int last_day_weekday() const;

    private:
        int index_from(int week, int weekday) const;

        QString m_title;
        QString m_description;
        QColor m_colour;
        QDate m_start_date;
        QList<bool> m_chain;
    };

} // namespace Chain


#endif // CHAIN_DATA_H
