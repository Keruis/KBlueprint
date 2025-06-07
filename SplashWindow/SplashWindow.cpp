#include "SplashWindow.h"
#include <QLabel>
#include <QVBoxLayout>
#include <QScreen>

SplashWindow::SplashWindow(QWidget* parent)
        : QWidget(parent)
{

}

SplashWindow::~SplashWindow() {

}

void SplashWindow::Initialize() noexcept {
    qDebug() << "Initialize called!";

    setupWindowProperties();

    m_imageLabel = new QLabel(this);
    m_imageLabel->setAttribute(Qt::WA_TranslucentBackground);
    m_imageLabel->setStyleSheet("background: transparent;");
    m_imageLabel->setVisible(false);

    m_container_K = new QWidget(this);
    m_container_ERUIS = new QWidget(this);

    // 创建标签
    m_label_K = new QLabel("K", m_container_K);
    m_label_ERUIS = new QLabel("eruis", m_container_ERUIS);

    // 设置标签样式
    for (auto label : {m_label_K, m_label_ERUIS}) {
        label->setStyleSheet(R"(
        QLabel {
            color: white;
            font-size: 320px;
            font-weight: bold;
        }
    )");
        label->adjustSize();
    }

    // 设置容器大小与标签一致
    m_container_K->setFixedSize(m_label_K->size());
    m_container_ERUIS->setFixedSize(m_label_ERUIS->size());

    // 添加模糊效果到标签
    m_blur_K = new QGraphicsBlurEffect(this);
    m_blur_K->setBlurRadius(10);
    m_label_K->setGraphicsEffect(m_blur_K);

    m_blur_ERUIS = new QGraphicsBlurEffect(this);
    m_blur_ERUIS->setBlurRadius(10);
    m_label_ERUIS->setGraphicsEffect(m_blur_ERUIS);

    // 添加透明效果到容器
    m_opacity_K = new QGraphicsOpacityEffect(this);
    m_opacity_K->setOpacity(0.0);
    m_container_K->setGraphicsEffect(m_opacity_K);

    m_opacity_ERUIS = new QGraphicsOpacityEffect(this);
    m_opacity_ERUIS->setOpacity(0.0);
    m_container_ERUIS->setGraphicsEffect(m_opacity_ERUIS);

    // 设置初始位置
    int y = (height() - m_label_K->height()) / 2;
    m_container_K->move(0, y - 50);
    m_container_ERUIS->move(getHorizontalOffsetForCentering(m_label_ERUIS->rect(), 2) + m_label_K->width() - 50, this->height() - m_label_ERUIS->height() - 50);
}

void SplashWindow::StartAnimation() noexcept {
    qDebug() << "StartAnimation called.";

    QPropertyAnimation* kposAnim = new QPropertyAnimation(m_container_K, "pos", this);
    kposAnim->setDuration(2600);
    kposAnim->setStartValue(m_container_K->pos());
    kposAnim->setEndValue(QPoint(getHorizontalOffsetForCentering(m_label_ERUIS->rect(), 2) - 50, m_container_K->y()));
    kposAnim->setEasingCurve(QEasingCurve::OutElastic);

    QPropertyAnimation* eruisPosAnim = new QPropertyAnimation(m_container_ERUIS, "pos", this);
    eruisPosAnim->setDuration(700);
    eruisPosAnim->setStartValue(m_container_ERUIS->pos());
    eruisPosAnim->setEndValue(QPoint(getHorizontalOffsetForCentering(m_label_ERUIS->rect(), 2) + m_label_K->width() - 50, m_container_K->y()));
    eruisPosAnim->setEasingCurve(QEasingCurve::OutBounce);

    QVariantAnimation* blurAnim = new QVariantAnimation(this);
    blurAnim->setDuration(2000);
    blurAnim->setStartValue(20.0);
    blurAnim->setEndValue(0.0);
    blurAnim->setEasingCurve(QEasingCurve::OutCubic);
    connect(blurAnim, &QVariantAnimation::valueChanged, this, [=, this](const QVariant &value) {
        double v = value.toDouble();
        m_blur_K->setBlurRadius(v);
        m_blur_ERUIS->setBlurRadius(v);
    });

    QPropertyAnimation* opacityAnimK = new QPropertyAnimation(m_opacity_K, "opacity", this);
    opacityAnimK->setDuration(1400);
    opacityAnimK->setStartValue(0.0);
    opacityAnimK->setEndValue(1.0);
    opacityAnimK->setEasingCurve(QEasingCurve::OutCubic);

    QPropertyAnimation* opacityAnimERUIS = new QPropertyAnimation(m_opacity_ERUIS, "opacity", this);
    opacityAnimERUIS->setDuration(1400);
    opacityAnimERUIS->setStartValue(0.0);
    opacityAnimERUIS->setEndValue(1.0);
    opacityAnimERUIS->setEasingCurve(QEasingCurve::OutCubic);

    QParallelAnimationGroup* group = new QParallelAnimationGroup(this);
    group->addAnimation(kposAnim);
    group->addAnimation(eruisPosAnim);
    group->addAnimation(blurAnim);
    group->addAnimation(opacityAnimK);
    group->addAnimation(opacityAnimERUIS);

    connect(opacityAnimERUIS, &QPropertyAnimation::valueChanged, this, [this](const QVariant &value) {
        if (value.toDouble() >= 1.0) {
            static bool triggered = false;
            if (!triggered) {
                triggered = true;
                AnimateDotExpansion();
            }
        }
    });

    connect(group, &QParallelAnimationGroup::finished, this, [this]() {
        qDebug() << "Animation finished.";
        update();
        QTimer::singleShot(1000, this, [this]() {
            emit animationFinished();
            ClearDot();
        });
    });

    group->start(QAbstractAnimation::DeleteWhenStopped);
}

void SplashWindow::HideLabels() {
    m_container_K->hide();
    m_container_ERUIS->hide();
}

void SplashWindow::setupWindowProperties() noexcept {
    QRect screenGeometry = QGuiApplication::primaryScreen()->geometry();
    this->setFixedSize(screenGeometry.size());
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::SplashScreen | Qt::WindowStaysOnTopHint);
    this->setAttribute(Qt::WA_TranslucentBackground);
}

int SplashWindow::getHorizontalOffsetForCentering(const QRect &rect, int divisor) noexcept {
    QRect screenGeometry = QGuiApplication::primaryScreen()->geometry();
    return (screenGeometry.width() - rect.width()) / divisor;
}

void SplashWindow::showEvent(QShowEvent *event) {
    QWidget::showEvent(event);
    StartAnimation();
}

void SplashWindow::paintEvent(QPaintEvent *event) {
    QWidget::paintEvent(event);

    if (!m_showIDot) return;

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setPen(Qt::NoPen);
    painter.setBrush(Qt::white);

    QFont font;
    font.setPointSize(320);
    font.setBold(true);
    painter.setFont(font);

    QFontMetricsF metrics(font);
    QString text = "eruis";
    int indexOfI = text.indexOf('i');
    if (indexOfI == -1) return;

    qreal xOffset = 0;
    for (int i = 0; i < indexOfI; ++i) {
        xOffset += metrics.horizontalAdvance(text[i]);
    }

    qreal iWidth = metrics.horizontalAdvance('i');

    QPoint labelPos = m_container_ERUIS->pos() + m_label_ERUIS->pos();
    qreal baselineY = labelPos.y() + metrics.ascent();

    QPointF dotCenter(
            labelPos.x() + xOffset - iWidth,
            baselineY - metrics.ascent() * 0.73
    );

    painter.drawEllipse(dotCenter, m_dotRadius, m_dotRadius);
}

void SplashWindow::AnimateDotExpansion() {
    m_showIDot = true;

    if (m_dotExpansionAnim) {
        m_dotExpansionAnim->stop();
        delete m_dotExpansionAnim;
    }

    m_dotExpansionAnim = new QVariantAnimation(this);
    m_dotExpansionAnim->setDuration(1000);
    m_dotExpansionAnim->setStartValue(10.0);
    m_dotExpansionAnim->setEndValue(std::max(width(), height()) * 1.2);
    m_dotExpansionAnim->setEasingCurve(QEasingCurve::OutCubic);

    connect(m_dotExpansionAnim, &QVariantAnimation::valueChanged, this, [this](const QVariant &value) {
        m_dotRadius = value.toDouble();
        update();  // 触发 repaint
    });

    connect(m_dotExpansionAnim, &QVariantAnimation::finished, this, [this]() {
        qDebug() << "Dot expansion finished.";
    });

    QTimer::singleShot(500, this, [this]() {
        QPixmap pixmap(":/SplashWindow/ys.png");
        if (!pixmap.isNull()) {
            HideLabels();
            m_imageLabel->setPixmap(pixmap);
            m_imageLabel->setScaledContents(true);
            m_imageLabel->setFixedSize(pixmap.size());
            m_imageLabel->move(
                    (width() - pixmap.width()) / 2,
                    (height() - pixmap.height()) / 2
            );
            m_imageLabel->setVisible(true);

            // 👇 淡入动画放这里！
            auto opacityEffect = new QGraphicsOpacityEffect(this);
            m_imageLabel->setGraphicsEffect(opacityEffect);

            auto fadeIn = new QPropertyAnimation(opacityEffect, "opacity");
            fadeIn->setDuration(1000);
            fadeIn->setStartValue(0.0);
            fadeIn->setEndValue(1.0);
            fadeIn->setEasingCurve(QEasingCurve::OutCubic);
            fadeIn->start(QAbstractAnimation::DeleteWhenStopped);

        } else {
            qDebug() << "Failed to load image!";
        }
    });

    m_dotExpansionAnim->start();
}

void SplashWindow::ClearDot() {
    m_showIDot = false;
    m_dotRadius = 10.0;

    if (m_dotExpansionAnim) {
        m_dotExpansionAnim->stop();
        delete m_dotExpansionAnim;
        m_dotExpansionAnim = nullptr;
    }

    update();  // 清空后重绘
}