#ifndef LINK_DATA_H
#define LINK_DATA_H

#include <string>

#ifndef Q_MOC_RUN
#define BOOST_SYSTEM_NO_DEPRECATED
#include <boost/date_time/gregorian/gregorian.hpp>
#endif // Q_MOC_RUN

namespace Chain
{
    class Link_Data
    {
    public:
        explicit Link_Data(boost::gregorian::date const& day, bool did_stuff = false);

        boost::gregorian::date const& date() const;
        std::string date_string() const;

        bool did_stuff() const;
        void set_did_stuff(bool state);
    private:
        boost::gregorian::date m_date;
        bool m_did_stuff;
    };

} // namespace Chain

inline
Chain::Link_Data::Link_Data(boost::gregorian::date const& date, bool did_stuff):
    m_date(date),
    m_did_stuff(did_stuff)
{
}

inline
boost::gregorian::date const& Chain::Link_Data::date() const
{
    return m_date;
}

inline
std::string Chain::Link_Data::date_string() const
{
    return boost::gregorian::to_iso_extended_string(m_date);
}

inline
bool Chain::Link_Data::did_stuff() const
{
    return m_did_stuff;
}

inline
void Chain::Link_Data::set_did_stuff(bool state)
{
    m_did_stuff = state;
}


#endif // LINK_DATA_H
