#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <QMainWindow>
#include "quptr.h"
#include "chain_widget.h"

class QWidget;
class QVBoxLayout;

namespace Ui
{
    class Main_Window;
}

namespace Chain
{
    class Chain_Widget;

    class Main_Window :
            public QMainWindow
    {
        Q_OBJECT

    public:
        explicit Main_Window(QWidget* parent = nullptr);
        ~Main_Window() override;

        void add_chain(std::string const& title, std::string const& description, int year, int month, int day);
        void add_chain(std::string const& title, std::string const& description, boost::gregorian::date const& start_date = boost::gregorian::day_clock::local_day());

    private slots:
        void action_slot_New_Chain();
        void action_slot_Exit();

    private:
        std::unique_ptr<Ui::Main_Window> m_ui;

        QUptr<QWidget> m_scrollarea_contents_widget;
        QUptr<QVBoxLayout> m_scrollarea_contents_layout;
        std::vector<QUptr<Chain_Widget>> m_chain_widgets;
    };

} // namespace Chain

#endif // MAIN_WINDOW_H
