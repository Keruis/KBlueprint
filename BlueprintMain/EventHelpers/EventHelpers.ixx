export module EventHelpers;

export namespace Blueprint::EventHelpers {
    void wheelEvent(double zoomStep,
                    double blurStep,
                    int rollerWheel,
                    double& targetZoomLevel,
                    double& targetBlurLevel,
                    double& zoomLevel,
                    double& blurLevel,
                    double& velocity
                    ) noexcept ;

    void smoothZoom(bool& isDashing,
                    double& velocity,
                    double& targetZoomLevel,
                    double& targetBlurLevel,
                    double& zoomLevel,
                    double& blurLevel
                    ) noexcept ;
}
