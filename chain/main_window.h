#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <QMainWindow>
#include <memory>
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

    /*
    Main_Window
    ====================================================================================================
    The base of the application. On construction it reads a supplied file (if it exists) and constructs
    chains based on it. On destruction it saves all open chains to that file, overwriting anything in
    it.
    */
    class Main_Window :
            public QMainWindow
    {
        Q_OBJECT

    public:
        // Special 6
        //============================================================
        explicit Main_Window(QString const& chain_filepath, QWidget* parent = nullptr);
        ~Main_Window() override;

        // No copying
        Main_Window(Main_Window const& other) = delete;
        Main_Window& operator=(Main_Window const& other) = delete;

        // Implicit default move
        //Main_Window(Main_Window && other) = default;
        //Main_Window& operator=(Main_Window && other) = default;

        // Interface
        //============================================================
        // Create a new chain based on these inputs
        void add_chain(QString const& title,
                       QString const& description,
                       QColor colour,
                       QDate start_date = QDate::currentDate(),
                       QList<bool> const& data = QList<bool>());

    private slots:
        // Action slots
        //============================================================
        void action_slot_New_Chain();
        void action_slot_Exit();

    private:
        // Helpers
        //============================================================
        void save_all() const;
        void load_all();

        // Data Members
        //============================================================
        std::unique_ptr<Ui::Main_Window> m_ui;
        QString m_filepath;
        QUptr<QWidget> m_scrollarea_contents_widget;
        QUptr<QVBoxLayout> m_scrollarea_contents_layout;
        std::vector<QUptr<Chain_Widget>> m_chain_widgets;
    };

} // namespace Chain

#endif // MAIN_WINDOW_H
