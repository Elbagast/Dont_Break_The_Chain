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
        // Special 6
        //============================================================
        Chain_Data(QString const& title,
                   QString const& description,
                   QColor colour,
                   QDate start_date = QDate::currentDate());

        Chain_Data(QString const& title,
                   QString const& description,
                   QColor colour,
                   QDate start_date,
                   QList<bool> const& data);

        // Implicit default destructor
        //~Chain_Data() = default;

        // Implicit default copy
        //Chain_Data(Chain_Data const& other) = default;
        //Chain_Data& operator=(Chain_Data const& other) = default;

        // Implicit default move
        //Chain_Data(Chain_Data && other) = default;
        //Chain_Data& operator=(Chain_Data && other) = default;

        // Interface
        //============================================================
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

        int day_count() const;
        int week_count() const;

        int weekdays_before_start() const;
        int weekdays_after_end() const;

        int first_day_weekday() const;
        int last_day_weekday() const;

    private:
        // Helpers
        //============================================================
        // Convert a week number (in regard to the data) and weekday into an index in m_chain
        int index_from(int week, int weekday) const;

        // Data Members
        //============================================================
        QString m_title;
        QString m_description;
        QColor m_colour;
        QDate m_start_date;
        QList<bool> m_chain;
    };

} // namespace Chain


#endif // CHAIN_DATA_H
