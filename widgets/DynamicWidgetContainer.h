#ifndef BLUEPRINT_DYNAMICWIDGETCONTAINER_H
#define BLUEPRINT_DYNAMICWIDGETCONTAINER_H

#include <QWidget>
#include <QMap>
#include <QString>
#include <QVBoxLayout>
#include "PlaceholderPage.h"

class DynamicWidgetContainer : public QWidget {
Q_OBJECT

public:
    explicit DynamicWidgetContainer(QWidget* parent = nullptr);
    ~DynamicWidgetContainer();

    void AddPage(const QString& name, QWidget* widget) noexcept;
    void ShowPage(const QString& name) noexcept;
    void SetDefaultPage(QWidget* widget) noexcept;
    QWidget* CurrentPage() const noexcept;
    QWidget* GetPage(const QString& name) const;

private:
    QWidget* m_current = nullptr;
    QWidget* m_default = nullptr;
    QMap<QString, QWidget*> m_pages;
    QVBoxLayout* m_layout = nullptr;
};

#endif // BLUEPRINT_DYNAMICWIDGETCONTAINER_H