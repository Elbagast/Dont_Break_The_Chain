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

    class Main_Window :
            public QMainWindow
    {
        Q_OBJECT

    public:
        // Supplied file where the chains are/will be stored
        explicit Main_Window(QString const& chain_filepath, QWidget* parent = nullptr);
        ~Main_Window() override;

        void add_chain(QString const& title,
                       QString const& description,
                       QColor colour,
                       QDate start_date = QDate::currentDate(),
                       QList<bool> const& data = QList<bool>());

        void save_all() const;
        void load_all();

    private slots:
        void action_slot_New_Chain();
        void action_slot_Exit();

    private:
        std::unique_ptr<Ui::Main_Window> m_ui;
        QString m_filepath;
        QUptr<QWidget> m_scrollarea_contents_widget;
        QUptr<QVBoxLayout> m_scrollarea_contents_layout;
        std::vector<QUptr<Chain_Widget>> m_chain_widgets;
    };

} // namespace Chain

#endif // MAIN_WINDOW_H
