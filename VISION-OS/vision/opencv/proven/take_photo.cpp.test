#include <opencv2/opencv.hpp>
#include <iostream>
#include <chrono>
#include <random>
#include <sstream>
#include <iomanip>

int main(int argc, char** argv) {
    // Camera device index (usually 0 for first camera)
    int cameraIndex = 0;
    if (argc > 1) {
        cameraIndex = std::atoi(argv[1]);
    }
    
    std::cout << "Opening camera " << cameraIndex << "..." << std::endl;
    
    // Open the camera
    cv::VideoCapture cap(cameraIndex);
    
    // Check if camera opened successfully
    if (!cap.isOpened()) {
        std::cerr << "ERROR: Could not open camera!" << std::endl;
        std::cerr << "Try: ls /dev/video* to see available cameras" << std::endl;
        return -1;
    }
    
    // Get camera properties
    int width = cap.get(cv::CAP_PROP_FRAME_WIDTH);
    int height = cap.get(cv::CAP_PROP_FRAME_HEIGHT);
    std::cout << "Camera opened: " << width << "x" << height << std::endl;
    
    // Optional: Set resolution (uncomment if needed)
    // cap.set(cv::CAP_PROP_FRAME_WIDTH, 640);
    // cap.set(cv::CAP_PROP_FRAME_HEIGHT, 480);
    
    cv::Mat frame;
    
    std::cout << "Warming up camera..." << std::endl;
    // Let camera warm up - capture and discard a few frames
    for (int i = 0; i < 5; i++) {
        cap >> frame;
    }
    
    std::cout << "Capturing image..." << std::endl;
    
    // Capture one frame
    cap >> frame;
    
    // Check if frame is valid
    if (frame.empty()) {
        std::cerr << "ERROR: Captured empty frame!" << std::endl;
        return -1;
    }
    
    // Generate filename with timestamp and random number
    auto now = std::chrono::system_clock::now();
    auto now_time_t = std::chrono::system_clock::to_time_t(now);
    auto now_ms = std::chrono::duration_cast<std::chrono::milliseconds>(
        now.time_since_epoch()) % 1000;
    
    // Generate random number (0-9999)
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 9999);
    int random_num = dis(gen);
    
    // Format: YYYYMMDD_HHMMSS_RNDM.jpg
    std::stringstream ss;
    ss << std::put_time(std::localtime(&now_time_t), "%Y%m%d_%H%M%S")
       << "_" << std::setw(4) << std::setfill('0') << random_num << ".jpg";
    std::string filename = ss.str();
    
    bool success = cv::imwrite(filename, frame);
    
    if (success) {
        std::cout << "Image saved successfully: " << filename << std::endl;
        std::cout << "Image size: " << frame.cols << "x" << frame.rows << std::endl;
    } else {
        std::cerr << "ERROR: Failed to save image!" << std::endl;
        return -1;
    }
    
    // Release camera
    cap.release();
    
    return 0;
}
