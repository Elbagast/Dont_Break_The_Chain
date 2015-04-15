#ifndef CHAIN_DATA_H
#define CHAIN_DATA_H

#include <vector>
#include "link_data.h"

namespace Chain
{
    class Chain_Data
    {
    public:
        // By default a chain starts today
        Chain_Data(std::string const& title, std::string const& description, boost::gregorian::date const& start_date = boost::gregorian::day_clock::local_day());
        ~Chain_Data();

        std::string const& title() const;
        std::string const& description() const;
        boost::gregorian::date const& start_date() const;
        boost::gregorian::date const& end_date() const;

        std::vector<Link_Data>& links();
        std::vector<Link_Data> const& links() const;

        void set_title(std::string const& value);
        void set_description(std::string const& value);

        // add links with dates between the last date stored and this day to the end of m_links
        void append_links_until_today(boost::gregorian::date const& start);
        void append_links_until_today();

        Link_Data& link(int week, int weekday);
        Link_Data const& link(int week, int weekday) const;

        int day_count() const;
        int week_count() const;

        int weekdays_before_start() const;
        int weekdays_after_end() const;

        int first_day_weekday() const;
        int last_day_weekday() const;

        static
        int weekday(boost::gregorian::date const& date);

    private:
        int index_from(int week, int weekday) const;

        std::string m_title;
        std::string m_description;
        std::vector<Link_Data> m_links;
    };

} // namespace Chain


#endif // CHAIN_DATA_H
