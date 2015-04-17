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
        // Supplied dir path is where chain files will be loaded and saved
        explicit Main_Window(QString const& dir_path, QWidget* parent = nullptr);
        ~Main_Window() override;

        void add_chain(QString const& title, QString const& description, QColor colour, QDate start_date = QDate::currentDate());
        void load_chain(QString const& file_path);

    private slots:
        void action_slot_New_Chain();
        void action_slot_Exit();

    private:
        std::unique_ptr<Ui::Main_Window> m_ui;

        QString m_dir_path;
        QUptr<QWidget> m_scrollarea_contents_widget;
        QUptr<QVBoxLayout> m_scrollarea_contents_layout;
        std::vector<QUptr<Chain_Widget>> m_chain_widgets;
    };

} // namespace Chain

#endif // MAIN_WINDOW_H
