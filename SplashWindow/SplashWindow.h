#ifndef BLUEPRINT_SPLASHWINDOW_H
#define BLUEPRINT_SPLASHWINDOW_H

#include <QWidget>
#include <QTimer>
#include <QPropertyAnimation>
#include <QLabel>
#include <QVBoxLayout>
#include <QApplication>
#include <QScreen>
#include <QGraphicsBlurEffect>
#include <QParallelAnimationGroup>

class SplashWindow : public QWidget {
    Q_OBJECT

public:
    explicit SplashWindow(QWidget* parent = nullptr) ;
    ~SplashWindow() ;

    void Initialize() noexcept ;

    void StartAnimation() noexcept ;

protected:
    void showEvent(QShowEvent* event) override ;
    void paintEvent(QPaintEvent* event) override ;

private:
    void setupWindowProperties() noexcept ;
    int getHorizontalOffsetForCentering(const QRect &rect, int divisor) noexcept;

signals:
    void animationFinished();

private:
    QWidget* m_container_K;
    QWidget* m_container_ERUIS;

    QLabel* m_label_K;
    QLabel* m_label_ERUIS;

    QGraphicsOpacityEffect* m_opacity_K;
    QGraphicsOpacityEffect* m_opacity_ERUIS;

    QGraphicsBlurEffect* m_blur_K;
    QGraphicsBlurEffect* m_blur_ERUIS;
};


#endif //BLUEPRINT_SPLASHWINDOW_H
