#include <opencv2/opencv.hpp>
#include <iostream>
#include <chrono>
#include <sstream>
#include <iomanip>
#include <ctime>
#include <vector>

/* ========= STYLE ========= */
static cv::Scalar HUD_WHITE(245,245,245);
static cv::Scalar HUD_DIM(200,200,200);
static cv::Scalar HUD_ACCENT(0,255,255);

void drawTelemetryHUD(cv::Mat& frame) {
    int w = frame.cols;
    int h = frame.rows;

    /* ===== LEFT METRIC STACK ===== */
    int x = 40;
    int y = 120;
    int dy = 90;

    auto drawMetric = [&](std::string value,
                          std::string unit,
                          int ypos) {

        cv::putText(frame, value,
                    {x, ypos},
                    cv::FONT_HERSHEY_COMPLEX,
                    2.2,
                    HUD_WHITE,
                    4,
                    cv::LINE_AA);

        cv::putText(frame, unit,
                    {x, ypos + 32},
                    cv::FONT_HERSHEY_SIMPLEX,
                    0.7,
                    HUD_DIM,
                    2,
                    cv::LINE_AA);

        cv::line(frame,
                 {x, ypos + 42},
                 {x + 120, ypos + 42},
                 HUD_DIM,
                 1);
    };

    drawMetric("43",  "MPH",     y);
    drawMetric("70",  "KM/H",    y += dy);
    drawMetric("210", "W",       y += dy);
    drawMetric("116", "RPM",     y += dy);

    cv::putText(frame,
                "-7.0%",
                {x, y + dy},
                cv::FONT_HERSHEY_SIMPLEX,
                1.0,
                HUD_WHITE,
                2,
                cv::LINE_AA);

    cv::putText(frame,
                "GRADIENT",
                {x, y + dy + 28},
                cv::FONT_HERSHEY_SIMPLEX,
                0.6,
                HUD_DIM,
                1,
                cv::LINE_AA);

    /* ===== BOTTOM ELEVATION PROFILE ===== */
    int by = h - 80;
    std::vector<cv::Point> profile;

    for (int i = 0; i < w; i += 40) {
        int py = by - (std::rand() % 30);
        profile.emplace_back(i, py);
    }

    for (size_t i = 1; i < profile.size(); i++) {
        cv::line(frame, profile[i - 1], profile[i],
                 HUD_WHITE, 2);
    }

    cv::putText(frame,
                "1643 m   5389 ft",
                {40, h - 30},
                cv::FONT_HERSHEY_SIMPLEX,
                0.6,
                HUD_DIM,
                1,
                cv::LINE_AA);

    /* ===== TOP-RIGHT MINI MAP ===== */
    int mapRadius = 80;
    cv::Point mapCenter(w - 120, 120);

    // subtle circle outline
    cv::circle(frame,
               mapCenter,
               mapRadius,
               HUD_DIM,
               2,
               cv::LINE_AA);

    // route trace (local-relative path)
    std::vector<cv::Point> route = {
        {0, -60},
        {15, -30},
        {-10, 0},
        {20, 30},
        {-5, 55}
    };

    for (size_t i = 1; i < route.size(); i++) {
        cv::line(frame,
                 mapCenter + route[i - 1],
                 mapCenter + route[i],
                 HUD_WHITE,
                 2,
                 cv::LINE_AA);
    }

    // current position
    cv::circle(frame,
               mapCenter + route.back(),
               6,
               HUD_ACCENT,
               -1,
               cv::LINE_AA);
}

std::string makeFilename() {
    auto t = std::time(nullptr);
    std::stringstream ss;
    ss << "zaire_ar_"
       << std::put_time(std::localtime(&t), "%Y%m%d_%H%M%S")
       << ".jpg";
    return ss.str();
}

int main(int argc, char** argv) {
    int cam = (argc > 1) ? std::atoi(argv[1]) : 0;

    cv::VideoCapture cap(cam);
    if (!cap.isOpened()) {
        std::cerr << "Camera open failed\n";
        return -1;
    }

    cap.set(cv::CAP_PROP_FRAME_WIDTH, 1920);
    cap.set(cv::CAP_PROP_FRAME_HEIGHT, 1080);

    cv::Mat frame;
    cap >> frame;

    if (frame.empty()) {
        std::cerr << "Empty frame\n";
        return -1;
    }

    drawTelemetryHUD(frame);

    std::string out = makeFilename();
    cv::imwrite(out, frame, {cv::IMWRITE_JPEG_QUALITY, 95});

    std::cout << "✓ Saved AR telemetry capture: " << out << std::endl;
    return 0;
}
