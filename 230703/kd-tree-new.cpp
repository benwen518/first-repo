#include <iostream>
#include <vector>
#include <random>
#include <cmath>
#include <algorithm>
#include <ctime> // 添加头文件

struct Point {
    std::vector<double> coordinates;
    int label;

    Point(const std::vector<double>& coords, int lbl)
        : coordinates(coords), label(lbl) {}
};

double calculateDistance(const Point& p1, const Point& p2) {
    double sum = 0.0;
    for (size_t i = 0; i < p1.coordinates.size(); ++i) {
        double diff = p1.coordinates[i] - p2.coordinates[i];
        sum += diff * diff;
    }
    return std::sqrt(sum);
}

int knnPredict(const std::vector<Point>& dataset, const Point& query, int k) {
    std::vector<std::pair<double, int>> distancesWithLabels;

    for (const auto& point : dataset) {
        double distance = calculateDistance(point, query);
        distancesWithLabels.push_back(std::make_pair(distance, point.label));
    }

    std::sort(distancesWithLabels.begin(), distancesWithLabels.end());

    std::vector<int> labelCounts(dataset.size(), 0);
    for (int i = 0; i < k; ++i) {
        int label = distancesWithLabels[i].second;
        labelCounts[label]++;
    }

    int maxCount = 0;
    int predictedLabel = -1;
    for (size_t i = 0; i < labelCounts.size(); ++i) {
        if (labelCounts[i] > maxCount) {
            maxCount = labelCounts[i];
            predictedLabel = static_cast<int>(i);
        }
    }

    return predictedLabel;
}

std::vector<Point> generateRandomDataset(int numSamples, int numFeatures, int numClasses, double minX, double maxX, double minY, double maxY) {
    std::vector<Point> dataset;

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<double> distX(minX, maxX);
    std::uniform_real_distribution<double> distY(minY, maxY);
    std::uniform_int_distribution<int> distLabel(0, numClasses - 1);

    for (int i = 0; i < numSamples; ++i) {
        std::vector<double> coords(numFeatures);
        for (int j = 0; j < numFeatures; ++j) {
            coords[j] = distX(gen);
        }
        int label = distLabel(gen);
        dataset.push_back(Point(coords, label));
    }

    return dataset;
}

int main() {
    int numSamples = 100;   // 样本数量
    int numFeatures = 2;    // 特征数量
    int numClasses = 2;     // 类别数量
    double minX = 0.0;      // X 坐标最小值
    double maxX = 10.0;     // X 坐标最大值
    double minY = 0.0;      // Y 坐标最小值
    double maxY = 10.0;     // Y 坐标最大值
    int k = 5;              // KNN 算法中的 k 值

    std::srand(std::time(nullptr)); // 设置随机数种子

    // 生成随机训练数据集
    std::vector<Point> dataset = generateRandomDataset(numSamples, numFeatures, numClasses, minX, maxX, minY, maxY);

    // 生成随机测试数据集
    std::vector<Point> testset = generateRandomDataset(numSamples, numFeatures, numClasses, minX, maxX, minY, maxY);

    int correctCount = 0;
    for (const auto& point : testset) {
        int predictedLabel = knnPredict(dataset, point, k);
        std::cout << "Coordinates: ";
        for (const auto& coord : point.coordinates) {
            std::cout << coord << " ";
        }
        std::cout << "| Predicted label: " << predictedLabel << ", Correct label: " << point.label << std::endl;
        if (predictedLabel == point.label)
            correctCount++;
    }

    double accuracy = static_cast<double>(correctCount) / testset.size() * 100.0;
    std::cout << "Accuracy: " << accuracy << "%" << std::endl;

    return 0;
}

