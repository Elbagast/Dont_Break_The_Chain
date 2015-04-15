#include "chain_data.h"


Chain::Chain_Data::Chain_Data(std::string const& title, std::string const& description, boost::gregorian::date const& start_date):
    m_title(title),
    m_description(description),
    m_links()
{
    append_links_until_today(start_date);
}

Chain::Chain_Data::~Chain_Data() = default;

std::string const& Chain::Chain_Data::title() const
{
    return m_title;
}

std::string const& Chain::Chain_Data::description() const
{
    return m_description;
}

boost::gregorian::date const& Chain::Chain_Data::start_date() const
{
    assert(!m_links.empty());
    return m_links.front().date();
}

boost::gregorian::date const& Chain::Chain_Data::end_date() const
{
    assert(!m_links.empty());
    return m_links.back().date();
}

std::vector<Chain::Link_Data>& Chain::Chain_Data::links()
{
    return m_links;
}

std::vector<Chain::Link_Data> const& Chain::Chain_Data::links() const
{
    return m_links;
}

void Chain::Chain_Data::set_title(std::string const& value)
{
    m_title = value;
}

void Chain::Chain_Data::set_description(std::string const& value)
{
    m_description = value;
}

void Chain::Chain_Data::append_links_until_today(boost::gregorian::date const& start)
{
    boost::gregorian::date end{boost::gregorian::day_clock::local_day() + boost::gregorian::days(1)};
    for (boost::gregorian::day_iterator iter{start}; *iter != end; ++iter)
    {
        m_links.emplace_back(*iter);
    }
}

void Chain::Chain_Data::append_links_until_today()
{
    boost::gregorian::date start{end_date() + boost::gregorian::days(1)};
    append_links_until_today(start);
}

Chain::Link_Data& Chain::Chain_Data::link(int week, int weekday)
{
    return m_links.at(index_from(week, weekday));
}

Chain::Link_Data const& Chain::Chain_Data::link(int week, int weekday) const
{
    return m_links.at(index_from(week, weekday));
}

int Chain::Chain_Data::day_count() const
{
    return m_links.size();
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
    return weekday(start_date());
}

int Chain::Chain_Data::weekdays_after_end() const
{
    return 6 - weekday(end_date());
}

int Chain::Chain_Data::first_day_weekday() const
{
    return weekday(start_date());
}

int Chain::Chain_Data::last_day_weekday() const
{
    return weekday(end_date());
}

int Chain::Chain_Data::weekday(boost::gregorian::date const& date)
{
    switch(date.day_of_week())
    {
    case boost::gregorian::Monday:      return 0;
    case boost::gregorian::Tuesday:     return 1;
    case boost::gregorian::Wednesday:   return 2;
    case boost::gregorian::Thursday:    return 3;
    case boost::gregorian::Friday:      return 4;
    case boost::gregorian::Saturday:    return 5;
    case boost::gregorian::Sunday:      return 6;
    default:                            return 0;
    }
}

int Chain::Chain_Data::index_from(int week, int weekday) const
{
    assert(week >= 0);
    assert(week < week_count());
    assert(weekday >= 0);
    assert(weekday < 7);
    return week * 7 + weekday - weekdays_before_start();
}
