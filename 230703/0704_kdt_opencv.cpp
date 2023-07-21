
#include <iostream>
#include <vector>
#include <opencv2/opencv.hpp>

struct Point {
    cv::Point2f coordinates;
    int label;

    Point(const cv::Point2f& coords, int lbl) : coordinates(coords), label(lbl) {}
};

// KD树节点
struct KDNode {
    Point point;
    KDNode* left;
    KDNode* right;

    KDNode(const Point& pt) : point(pt), left(nullptr), right(nullptr) {}
};

// KD树类
class KDTree {
private:
    KDNode* root;

public:
    KDTree() : root(nullptr) {}

    void buildTree(std::vector<Point>& points) {
        root = buildSubtree(points, 0);
    }

    KDNode* buildSubtree(std::vector<Point>& points, int depth) {
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

    // 可视化KD树
    void visualizeTree(cv::Mat& image, KDNode* node, int depth, const cv::Point2f& minPoint, const cv::Point2f& maxPoint) {
        if (node == nullptr)
            return;

        int k = node->point.coordinates.size();
        int axis = depth % k;
        float splitValue = node->point.coordinates[axis];

        cv::Point2f lineStart, lineEnd;
        if (axis == 0) {
            lineStart = cv::Point2f(splitValue, minPoint.y);
            lineEnd = cv::Point2f(splitValue, maxPoint.y);
        } else {
            lineStart = cv::Point2f(minPoint.x, splitValue);
            lineEnd = cv::Point2f(maxPoint.x, splitValue);
        }
        cv::line(image, lineStart, lineEnd, cv::Scalar(0, 255, 0), 1);

        visualizeTree(image, node->left, depth + 1, minPoint, maxPoint);
        visualizeTree(image, node->right, depth + 1, minPoint, maxPoint);
    }

    void visualize(cv::Mat& image) {
        cv::Point2f minPoint(0, 0);
        cv::Point2f maxPoint(image.cols, image.rows);
        visualizeTree(image, root, 0, minPoint, maxPoint);
    }

    // K最近邻搜索
    void searchKNearestNeighbors(KDNode* node, const cv::Point2f& query, std::vector<KDNode*>& nearestNodes, int depth, int k) {
        if (node == nullptr)
            return;

        nearestNodes.push_back(node);
        std::sort(nearestNodes.begin(), nearestNodes.end(), [&query](const KDNode* a, const KDNode* b) {
            double distA = calculateDistance(a->point.coordinates, query);
            double distB = calculateDistance(b->point.coordinates, query);
            return distA < distB;
        });

        if (nearestNodes.size() > k)
            nearestNodes.pop_back();

        int axis = depth % node->point.coordinates.size();
        if (query[axis] < node->point.coordinates[axis])
            searchKNearestNeighbors(node->left, query, nearestNodes, depth + 1, k);
        else
            searchKNearestNeighbors(node->right, query, nearestNodes, depth + 1, k);

        double currentBestDistance = calculateDistance(nearestNodes.back()->point.coordinates, query);
        double axisDistance = std::abs(query[axis] - node->point.coordinates[axis]);

        if (nearestNodes.size() < k || axisDistance < currentBestDistance) {
            if (query[axis] < node->point.coordinates[axis])
                searchKNearestNeighbors(node->right, query, nearestNodes, depth + 1, k);
            else
                searchKNearestNeighbors(node->left, query, nearestNodes, depth + 1, k);
        }
    }

    std::vector<int> predict(const cv::Point2f& query, int k) {
        std::vector<KDNode*> nearestNodes;
        nearestNodes.reserve(k);
        searchKNearestNeighbors(root, query, nearestNodes, 0, k);

        std::map<int, int> labelCounts;
        for (const auto& node : nearestNodes) {
            labelCounts[node->point.label]++;
        }

        std::vector<int> predictedLabels;
        for (const auto& pair : labelCounts) {
            predictedLabels.push_back(pair.first);
        }

        return predictedLabels;
    }

    static double calculateDistance(const cv::Point2f& a, const cv::Point2f& b) {
        double distance = 0.0;
        distance += std::pow(a.x - b.x, 2);
        distance += std::pow(a.y - b.y, 2);
        return std::sqrt(distance);
    }
};

int main() {
    int numSamples = 100;  // 样本数量
    int numFeatures = 2;   // 特征数量
    int numClasses = 2;    // 类别数量
    double minX = 0.0;     // X 坐标最小值
    double maxX = 10.0;    // X 坐标最大值
    double minY = 0.0;     // Y 坐标最小值
    double maxY = 10.0;    // Y 坐标最大值

    // 生成随机数据集
    std::vector<Point> dataset;
    for (int i = 0; i < numSamples; ++i) {
        double x = minX + static_cast<double>(std::rand()) / (static_cast<double>(RAND_MAX / (maxX - minX)));
        double y = minY + static_cast<double>(std::rand()) / (static_cast<double>(RAND_MAX / (maxY - minY)));
        int label = std::rand() % numClasses;
        dataset.push_back(Point(cv::Point2f(x, y), label));
    }

    // 构建KD树
    KDTree kdTree;
    kdTree.buildTree(dataset);

    // 创建用于可视化的图像
    cv::Mat image(500, 500, CV_8UC3, cv::Scalar(255, 255, 255));

    // 可视化KD树
    kdTree.visualize(image);

    // 可视化查询点及其K最近邻点
    cv::Point2f queryPoint(5, 5);
    std::vector<KDNode*> nearestNodes;
    kdTree.searchKNearestNeighbors(kdTree.getRoot(), queryPoint, nearestNodes, 0, 3);

    cv::circle(image, queryPoint, 5, cv::Scalar(255, 0, 0), -1);
    for (const auto& node : nearestNodes) {
        cv::circle(image, node->point.coordinates, 5, cv::Scalar(0, 0, 255), -1);
        cv::line(image, queryPoint, node->point.coordinates, cv::Scalar(0, 0, 255), 1);
    }

    // 显示图像
    cv::imshow("KD-Tree Visualization", image);
    cv::waitKey(0);

    return 0;
}
