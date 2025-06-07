#include "DynamicWidgetContainer.h"

DynamicWidgetContainer::DynamicWidgetContainer(QWidget* parent)
        : QWidget(parent)
{
    m_layout = new QVBoxLayout(this);
    m_layout->setContentsMargins(0, 0, 0, 0);
    m_layout->setSpacing(0);
    SetDefaultPage(new PlaceholderPage());
}

DynamicWidgetContainer::~DynamicWidgetContainer() {}

void DynamicWidgetContainer::AddPage(const QString& name, QWidget* widget) noexcept {
    if (!m_pages.contains(name)) {
        widget->setParent(this);
        widget->hide();
        m_layout->addWidget(widget);
        m_pages.insert(name, widget);
    }
}

void DynamicWidgetContainer::ShowPage(const QString& name) noexcept {
    QWidget* target = m_pages.value(name, nullptr);

    if (m_current)
        m_current->hide();

    if (target) {
        m_current = target;
        m_current->show();
    } else if (m_default) {
        m_current = m_default;
        m_current->show();
    } else {
        m_current = nullptr;
    }
}

void DynamicWidgetContainer::SetDefaultPage(QWidget* widget) noexcept {
    if (m_default) m_default->hide();

    m_default = widget;

    if (m_default) {
        m_default->setParent(this);
        m_default->hide(); // 默认先不显示
        m_layout->addWidget(m_default);
    }
}

QWidget* DynamicWidgetContainer::CurrentPage() const noexcept {
    return m_current;
}

QWidget* DynamicWidgetContainer::GetPage(const QString& name) const {
    return m_pages.value(name, nullptr);
}