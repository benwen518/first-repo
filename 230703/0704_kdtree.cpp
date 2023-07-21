#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <map>
#include <random>

// struct Point {
//     std::vector<double> coordinates;
//     int label;

//     Point(const std::vector<double>& coords, int lbl) : coordinates(coords), label(lbl) {}
// };
struct Point {
    std::vector<double> coordinates;
    int label;

    Point(const std::vector<double>& coords, int lbl)
        : coordinates(coords), label(lbl) {}
};

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

class KDNode {
public:
    Point point;
    KDNode* left;
    KDNode* right;

    KDNode(const Point& pt) : point(pt), left(nullptr), right(nullptr) {}
};

class KDTree {
private:
    KDNode* root;

public:
    KDTree() : root(nullptr) {}

    void buildTree(std::vector<Point>& points) {
        root = buildSubtree(points, 0);
    }

    KDNode* buildSubtree(std::vector<Point> points, int depth) {
        if (points.empty())
            return nullptr;

        int k = points[0].coordinates.size();
        int axis = depth % k;

        std::sort(points.begin(), points.end(), [axis](const Point& a, const Point& b) {
            return a.coordinates[axis] < b.coordinates[axis];
        });

        int medianIndex = points.size() / 2;
        KDNode* node = new KDNode(points[medianIndex]);
        points.erase(points.begin() + medianIndex);

        node->left = buildSubtree(std::vector<Point>(points.begin(), points.begin() + medianIndex), depth + 1);
        node->right = buildSubtree(std::vector<Point>(points.begin() + medianIndex, points.end()), depth + 1);

        return node;
    }

    void searchKNearestNeighbors(KDNode* node, const Point& query, std::vector<KDNode*>& nearestNodes, int depth, int k) {
    if (node == nullptr)
        return;

    nearestNodes.push_back(node);
    std::sort(nearestNodes.begin(), nearestNodes.end(), [&query](const KDNode* a, const KDNode* b) {
        double distA = calculateDistance(a->point, query);
        double distB = calculateDistance(b->point, query);
        return distA < distB;
    });

    if (nearestNodes.size() > k)
        nearestNodes.pop_back();

    int axis = depth % node->point.coordinates.size();
    if (query.coordinates[axis] < node->point.coordinates[axis])
        searchKNearestNeighbors(node->left, query, nearestNodes, depth + 1, k);
    else
        searchKNearestNeighbors(node->right, query, nearestNodes, depth + 1, k);

    double currentBestDistance = calculateDistance(nearestNodes.back()->point, query);
    double axisDistance = std::abs(query.coordinates[axis] - node->point.coordinates[axis]);

    if (nearestNodes.size() < k || axisDistance < currentBestDistance) {
        if (query.coordinates[axis] < node->point.coordinates[axis])
            searchKNearestNeighbors(node->right, query, nearestNodes, depth + 1, k);
        else
            searchKNearestNeighbors(node->left, query, nearestNodes, depth + 1, k);
    }
}


    int predict(const Point& query, int k) {
        std::vector<KDNode*> nearestNodes;
        nearestNodes.reserve(k);
        searchKNearestNeighbors(root, query, nearestNodes, 0, k);

        std::map<int, int> labelCounts;
        for (const auto& node : nearestNodes) {
            labelCounts[node->point.label]++;
        }

        int maxCount = 0;
        int predictedLabel = -1;

        for (const auto& pair : labelCounts) {
            if (pair.second > maxCount) {
                maxCount = pair.second;
                predictedLabel = pair.first;
            }
        }

        return predictedLabel;
    }

    static double calculateDistance(const Point& a, const Point& b) {
        double distance = 0.0;
        for (size_t i = 0; i < a.coordinates.size(); ++i) {
            double diff = a.coordinates[i] - b.coordinates[i];
            distance += diff * diff;
        }
        return std::sqrt(distance);
    }
};

int main() {
    int numSamples = 100;   // 样本数量
    int numFeatures = 2;    // 特征数量
    int numClasses = 2;     // 类别数量
    double minX = 0.0;      // X 坐标最小值
    double maxX = 10.0;     // X 坐标最大值
    double minY = 0.0;      // Y 坐标最小值
    double maxY = 10.0;     // Y 坐标最大值
    int k = 3;              // K值

    // 生成随机数据集
    std::vector<Point> dataset = generateRandomDataset(numSamples, numFeatures, numClasses, minX, maxX, minY, maxY);

    // 划分训练集和测试集
    int numTrainingSamples = numSamples * 0.8;  // 80% 数据作为训练集
    std::vector<Point> trainingSet(dataset.begin(), dataset.begin() + numTrainingSamples);
    std::vector<Point> testSet(dataset.begin() + numTrainingSamples, dataset.end());

    // 构建 KD Tree
    KDTree kdTree;
    kdTree.buildTree(trainingSet);

    // 预测并计算准确率
    int numCorrect = 0;
    for (const auto& testPoint : testSet) {
        int predictedLabel = kdTree.predict(testPoint, k);
        std::cout << "Coordinates: ";
        for (const auto& coord : testPoint.coordinates) {
            std::cout << coord << " ";
        }
        std::cout << "| True Label: " << testPoint.label;
        std::cout << " | Predicted Label: " << predictedLabel << std::endl;
        if (predictedLabel == testPoint.label) {
            numCorrect++;
        }
    }

    double accuracy = static_cast<double>(numCorrect) / testSet.size();
    std::cout << "Accuracy: " << accuracy << std::endl;

    return 0;
}
