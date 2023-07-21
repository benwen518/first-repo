// #include <iostream>
// #include <vector>
// #include <cmath>
// #include <algorithm>
// #include <map>

// struct Point {
//     std::vector<double> coordinates;
//     int label;

//     Point(const std::vector<double>& coords, int lbl) : coordinates(coords), label(lbl) {}
// };

// struct KDNode {
//     Point point;
//     int splitDim;
//     KDNode* left;
//     KDNode* right;

//     KDNode(const Point& p, int split) : point(p), splitDim(split), left(nullptr), right(nullptr) {}
// };

// class KNNClassifier {
// private:
//     int k;
//     KDNode* root;

// public:
//     KNNClassifier(int kValue) : k(kValue), root(nullptr) {}

//     void fit(const std::vector<Point>& trainingSet) {
//         root = buildKDTree(trainingSet);
//     }

//     int predict(const Point& testPoint) {
//         std::vector<KDNode*> nearestNodes;
//         searchKNearestNeighbors(root, testPoint, nearestNodes);

//         std::map<int, int> labelCounts;
//         for (const auto& node : nearestNodes) {
//             int label = node->point.label;
//             labelCounts[label]++;
//         }

//         int maxCount = 0;
//         int predictedLabel = -1;
//         for (const auto& pair : labelCounts) {
//             if (pair.second > maxCount) {
//                 maxCount = pair.second;
//                 predictedLabel = pair.first;
//             }
//         }

//         return predictedLabel;
//     }

// private:
//     KDNode* buildKDTree(const std::vector<Point>& points, int depth = 0) {
//         if (points.empty())
//             return nullptr;

//         int k = points[0].coordinates.size(); // 样本点的维度

//         // 选择切分维度
//         int splitDim = depth % k;

//         // 按切分维度的值进行排序
//         std::vector<Point> sortedPoints(points);
//         std::sort(sortedPoints.begin(), sortedPoints.end(),
//                   [splitDim](const Point& a, const Point& b) {
//                       return a.coordinates[splitDim] < b.coordinates[splitDim];
//                   });

//         // 选择中位数作为切分值
//         int median = sortedPoints.size() / 2;

//         KDNode* node = new KDNode(sortedPoints[median], splitDim);
//         node->left = buildKDTree(std::vector<Point>(sortedPoints.begin(), sortedPoints.begin() + median), depth + 1);
//         node->right = buildKDTree(std::vector<Point>(sortedPoints.begin() + median + 1, sortedPoints.end()), depth + 1);

//         return node;
//     }

//     void searchKNearestNeighbors(KDNode* node, const Point& query, std::vector<KDNode*>& nearestNodes,
//                                  int depth = 0) {
//         if (node == nullptr)
//             return;

//         int k = query.coordinates.size();
//         int splitDim = depth % k;

//         double distance = calculateDistance(node->point, query);
//         insertNearestNeighbor(node, distance, nearestNodes, k);

//         double axisDistance = query.coordinates[splitDim] - node->point.coordinates[splitDim];
//         if (axisDistance <= 0)
//             searchKNearestNeighbors(node->left, query, nearestNodes, depth + 1);
//         if (axisDistance >= 0)
//             searchKNearestNeighbors(node->right, query, nearestNodes, depth + 1);

//         if (std::abs(axisDistance) < nearestNodes.back()->point.coordinates[splitDim])
//             searchKNearestNeighbors(axisDistance <= 0 ? node->right : node->left, query, nearestNodes, depth + 1);
//     }

//     double calculateDistance(const Point& p1, const Point& p2) {
//         double distance = 0.0;
//         for (size_t i = 0; i < p1.coordinates.size(); ++i)
//             distance += std::pow(p1.coordinates[i] - p2.coordinates[i], 2);
//         return std::sqrt(distance);
//     }

//     void insertNearestNeighbor(KDNode* node, double distance, std::vector<KDNode*>& nearestNodes, size_t k) {
//         if (nearestNodes.size() < k) {
//             nearestNodes.push_back(node);
//             std::sort(nearestNodes.begin(), nearestNodes.end(),
//                       [](const KDNode* a, const KDNode* b) {
//                           return a->point.label < b->point.label;
//                       });
//         } else if (distance < calculateDistance(nearestNodes.back()->point, node->point)) {
//             nearestNodes.pop_back();
//             nearestNodes.push_back(node);
//             std::sort(nearestNodes.begin(), nearestNodes.end(),
//                       [](const KDNode* a, const KDNode* b) {
//                           return a->point.label < b->point.label;
//                       });
//         }
//     }
// };

// // int main() {
// //     std::vector<Point> trainingSet = {
// //         Point({1, 2}, 0),
// //         Point({2, 3}, 0),
// //         Point({4, 5}, 1),
// //         Point({3, 2}, 1),
// //         Point({2, 1}, 0)
// //     };

// //     KNNClassifier knn(3);
// //     knn.fit(trainingSet);

// //     Point testPoint({3, 4}, 0);
// //     int predictedLabel = knn.predict(testPoint);

// //     std::cout << "Predicted label: " << predictedLabel << std::endl;

// //     return 0;
// // }

// // int main() {
// //     std::vector<Point> trainingSet = {
// //         Point({1, 2}, 0),
// //         Point({2, 3}, 0),
// //         Point({4, 5}, 1),
// //         Point({3, 2}, 1),
// //         Point({2, 1}, 0)
// //     };

// //     std::vector<Point> testSet = {
// //         Point({1, 1}, 0),
// //         Point({4, 4}, 1),
// //         Point({3, 3}, 0),
// //         Point({2, 2}, 1),
// //     };

// //     KNNClassifier knn(3);
// //     knn.fit(trainingSet);

// //     int correctCount = 0;
// //     for (const auto& point : testSet) {
// //         int predictedLabel = knn.predict(point);
// //         if (predictedLabel == point.label)
// //             correctCount++;
// //     }

// //     double accuracy = static_cast<double>(correctCount) / testSet.size() * 100.0;

// //     std::cout << "Accuracy: " << accuracy << "%" << std::endl;

// //     return 0;
// // }

// int main() {
//     std::vector<Point> trainingSet = {
//         Point({1, 2}, 0),
//         Point({2, 3}, 0),
//         Point({4, 5}, 1),
//         Point({3, 2}, 1),
//         Point({2, 1}, 0),
//         Point({5, 5}, 1),
//         Point({1, 5}, 1),
//         Point({4, 1}, 0)
//     };

//     std::vector<Point> testSet = {
//         Point({1, 1}, 0),
//         Point({4, 4}, 1),
//         Point({3, 3}, 0),
//         Point({2, 2}, 1),
//         Point({3, 4}, 0),
//         Point({5, 1}, 0),
//         Point({1, 4}, 1),
//         Point({4, 3}, 1)
//     };

//     KNNClassifier knn(3);
//     knn.fit(trainingSet);

//     int correctCount = 0;
//     for (const auto& point : testSet) {
//         int predictedLabel = knn.predict(point);
//         if (predictedLabel == point.label)
//             correctCount++;
//     }

//     double accuracy = static_cast<double>(correctCount) / testSet.size() * 100.0;

//     std::cout << "Accuracy: " << accuracy << "%" << std::endl;

//     return 0;
// }
//old有结果
////////
// new
// #include <iostream>
// #include <vector>
// #include <cmath>
// #include <algorithm>
// #include <map>

// struct Point {
//     std::vector<double> coordinates;
//     int label;

//     Point(const std::vector<double>& coords, int lbl) : coordinates(coords), label(lbl) {}
// };

// class KDNode {
// public:
//     Point point;
//     KDNode* left;
//     KDNode* right;

//     KDNode(const Point& pt) : point(pt), left(nullptr), right(nullptr) {}
// };

// class KDTree {
// private:
//     KDNode* root;

// public:
//     KDTree() : root(nullptr) {}

//     void buildTree(std::vector<Point>& points) {
//         root = buildSubtree(points, 0);
//     }

//     KDNode* buildSubtree(std::vector<Point> points, int depth) {
//         if (points.empty())
//             return nullptr;

//         int k = points[0].coordinates.size();
//         int axis = depth % k;

//         std::sort(points.begin(), points.end(), [axis](const Point& a, const Point& b) {
//             return a.coordinates[axis] < b.coordinates[axis];
//         });

//         int medianIndex = points.size() / 2;
//         KDNode* node = new KDNode(points[medianIndex]);
//         points.erase(points.begin() + medianIndex);

//         node->left = buildSubtree(std::vector<Point>(points.begin(), points.begin() + medianIndex), depth + 1);
//         node->right = buildSubtree(std::vector<Point>(points.begin() + medianIndex, points.end()), depth + 1);

//         return node;
//     }

//     void searchKNearestNeighbors(KDNode* node, const Point& query, std::vector<KDNode*>& nearestNodes, int depth) {
//         if (node == nullptr)
//             return;

//         int k = query.coordinates.size();
//         int axis = depth % k;

//         KDNode* searchNode;
//         KDNode* otherNode;

//         if (query.coordinates[axis] < node->point.coordinates[axis]) {
//             searchNode = node->left;
//             otherNode = node->right;
//         } else {
//             searchNode = node->right;
//             otherNode = node->left;
//         }

//         searchKNearestNeighbors(searchNode, query, nearestNodes, depth + 1);

//         if (nearestNodes.size() < nearestNodes.capacity()) {
//             nearestNodes.push_back(node);
//             std::sort(nearestNodes.begin(), nearestNodes.end(), [query](const KDNode* a, const KDNode* b) {
//                 return calculateDistance(a->point, query) < calculateDistance(b->point, query);
//             });
//         } else if (std::abs(node->point.coordinates[axis] - query.coordinates[axis]) < calculateDistance(nearestNodes.back()->point, query)) {
//             nearestNodes.push_back(node);
//             std::sort(nearestNodes.begin(), nearestNodes.end(), [query](const KDNode* a, const KDNode* b) {
//                 return calculateDistance(a->point, query) < calculateDistance(b->point, query);
//             });
//             nearestNodes.pop_back();
//         }

//         if (std::pow(query.coordinates[axis] - node->point.coordinates[axis], 2) < calculateDistance(nearestNodes.back()->point, query)) {
//             searchKNearestNeighbors(otherNode, query, nearestNodes, depth + 1);
//         }
//     }

//     int predict(const Point& query, int k) {
//         std::vector<KDNode*> nearestNodes;
//         nearestNodes.reserve(k);
//         searchKNearestNeighbors(root, query, nearestNodes, 0);

//         std::map<int, int> labelCounts;
//         for (const auto& node : nearestNodes) {
//             labelCounts[node->point.label]++;
//         }

//         int maxCount = 0;
//         int predictedLabel = -1;

//         for (const auto& pair : labelCounts) {
//             if (pair.second > maxCount) {
//                 maxCount = pair.second;
//                 predictedLabel = pair.first;
//             }
//         }

//         return predictedLabel;
//     }

//     static double calculateDistance(const Point& a, const Point& b) {
//         double distance = 0.0;
//         for (size_t i = 0; i < a.coordinates.size(); ++i) {
//             distance += std::pow(a.coordinates[i] - b.coordinates[i], 2);
//         }
//         return std::sqrt(distance);
//     }
// };

// int main() {
//     std::vector<Point> trainingSet = {
//         Point({1, 2}, 0),
//         Point({2, 3}, 0),
//         Point({4, 5}, 1),
//         Point({3, 2}, 1),
//         Point({2, 1}, 0),
//         Point({5, 5}, 1),
//         Point({1, 5}, 1),
//         Point({4, 1}, 0)
//     };

//     std::vector<Point> testSet = {
//         Point({1, 1}, 0),
//         Point({4, 4}, 1),
//         Point({3, 3}, 0),
//         Point({2, 2}, 1),
//         Point({3, 4}, 0),
//         Point({5, 1}, 0),
//         Point({1, 4}, 1),
//         Point({4, 3}, 1)
//     };

//     KDTree kdTree;
//     kdTree.buildTree(trainingSet);

//     int correctCount = 0;
//     for (const auto& point : testSet) {
//         int predictedLabel = kdTree.predict(point, 3);
//         if (predictedLabel == point.label)
//             correctCount++;
//     }

//     double accuracy = static_cast<double>(correctCount) / testSet.size() * 100.0;

//     std::cout << "Accuracy: " << accuracy << "%" << std::endl;

//     return 0;
// }

////第三次测试代码应当100 但结果75
// #include <iostream>
// #include <vector>
// #include <cmath>
// #include <algorithm>
// #include <map>

// struct Point {
//     std::vector<double> coordinates;
//     int label;

//     Point(const std::vector<double>& coords, int lbl) : coordinates(coords), label(lbl) {}
// };

// class KDNode {
// public:
//     Point point;
//     KDNode* left;
//     KDNode* right;

//     KDNode(const Point& pt) : point(pt), left(nullptr), right(nullptr) {}
// };

// class KDTree {
// private:
//     KDNode* root;

// public:
//     KDTree() : root(nullptr) {}

//     void buildTree(std::vector<Point>& points) {
//         root = buildSubtree(points, 0);
//     }

//     KDNode* buildSubtree(std::vector<Point> points, int depth) {
//         if (points.empty())
//             return nullptr;

//         int k = points[0].coordinates.size();
//         int axis = depth % k;

//         std::sort(points.begin(), points.end(), [axis](const Point& a, const Point& b) {
//             return a.coordinates[axis] < b.coordinates[axis];
//         });

//         int medianIndex = points.size() / 2;
//         KDNode* node = new KDNode(points[medianIndex]);
//         points.erase(points.begin() + medianIndex);

//         node->left = buildSubtree(std::vector<Point>(points.begin(), points.begin() + medianIndex), depth + 1);
//         node->right = buildSubtree(std::vector<Point>(points.begin() + medianIndex, points.end()), depth + 1);

//         return node;
//     }

//     void searchKNearestNeighbors(KDNode* node, const Point& query, std::vector<KDNode*>& nearestNodes, int depth, int k) {
//         if (node == nullptr)
//             return;

//         nearestNodes.push_back(node);
//         std::sort(nearestNodes.begin(), nearestNodes.end(), [&query](const KDNode* a, const KDNode* b) {
//             double distA = calculateDistance(a->point, query);
//             double distB = calculateDistance(b->point, query);
//             return distA < distB;
//         });

//         if (nearestNodes.size() > k)
//             nearestNodes.pop_back();

//         int axis = depth % node->point.coordinates.size();
//         if (query.coordinates[axis] < node->point.coordinates[axis])
//             searchKNearestNeighbors(node->left, query, nearestNodes, depth + 1, k);
//         else
//             searchKNearestNeighbors(node->right, query, nearestNodes, depth + 1, k);
//     }

//     int predict(const Point& query, int k) {
//         std::vector<KDNode*> nearestNodes;
//         nearestNodes.reserve(k);
//         searchKNearestNeighbors(root, query, nearestNodes, 0, k);

//         std::map<int, int> labelCounts;
//         for (const auto& node : nearestNodes) {
//             labelCounts[node->point.label]++;
//         }

//         int maxCount = 0;
//         int predictedLabel = -1;

//         for (const auto& pair : labelCounts) {
//             if (pair.second > maxCount) {
//                 maxCount = pair.second;
//                 predictedLabel = pair.first;
//             }
//         }

//         return predictedLabel;
//     }

//     static double calculateDistance(const Point& a, const Point& b) {
//         double distance = 0.0;
//         for (size_t i = 0; i < a.coordinates.size(); ++i) {
//             double diff = a.coordinates[i] - b.coordinates[i];
//             distance += diff * diff;
//         }
//         return std::sqrt(distance);
//     }
// };

// int main() {
//     // 创建数据集
//     std::vector<Point> dataset;
//     dataset.push_back(Point({2.0, 3.0}, 0));
//     dataset.push_back(Point({5.0, 4.0}, 0));
//     dataset.push_back(Point({9.0, 6.0}, 1));
//     dataset.push_back(Point({4.0, 7.0}, 1));
//     dataset.push_back(Point({8.0, 1.0}, 0));
//     dataset.push_back(Point({7.0, 2.0}, 1));

//     // 创建 KD 树
//     KDTree kdTree;
//     kdTree.buildTree(dataset);

//     // 测试数据集
//     std::vector<Point> testset;
//     testset.push_back(Point({3.0, 2.0}, 0));   // 正确类别：0
//     testset.push_back(Point({6.0, 5.0}, 1));   // 正确类别：1
//     testset.push_back(Point({1.0, 5.0}, 0));   // 正确类别：0
//     testset.push_back(Point({9.0, 4.0}, 1));   // 正确类别：1

//     int correctCount = 0;
//     for (const auto& point : testset) {
//         int predictedLabel = kdTree.predict(point, 3);
//         std::cout << "Predicted label: " << predictedLabel << ", Correct label: " << point.label << std::endl;
//         if (predictedLabel == point.label)
//             correctCount++;
//     }

//     double accuracy = static_cast<double>(correctCount) / testset.size() * 100.0;
//     std::cout << "Accuracy: " << accuracy << "%" << std::endl;

//     return 0;
// }

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

    // 生成随机数据集
    std::vector<Point> dataset = generateRandomDataset(numSamples, numFeatures, numClasses, minX, maxX, minY, maxY);

    // 输出数据集
    for (const auto& point : dataset) {
        std::cout << "Coordinates: ";
        for (const auto& coord : point.coordinates) {
            std::cout << coord << " ";
        }
        std::cout << "| Label: " << point.label << std::endl;
    }
    
    
    return 0;
}
// int main() {
//     // 创建数据集
//     std::vector<Point> dataset;
//     dataset.push_back(Point({2.0, 3.0}, 0));
//     dataset.push_back(Point({5.0, 4.0}, 0));
//     dataset.push_back(Point({9.0, 6.0}, 1));
//     dataset.push_back(Point({4.0, 7.0}, 1));
//     dataset.push_back(Point({8.0, 1.0}, 0));
//     dataset.push_back(Point({7.0, 2.0}, 1));

//     // 创建 KD 树
//     KDTree kdTree;
//     kdTree.buildTree(dataset);

//     // 测试数据集
//     std::vector<Point> testset;
//     testset.push_back(Point({3.0, 2.0}, 0));   // 正确类别：0
//     testset.push_back(Point({6.0, 5.0}, 1));   // 正确类别：1
//     testset.push_back(Point({1.0, 5.0}, 0));   // 正确类别：0
//     testset.push_back(Point({9.0, 4.0}, 1));   // 正确类别：1

//     int correctCount = 0;
//     for (const auto& point : testset) {
//         int predictedLabel = kdTree.predict(point, 3);
//         std::cout << "Predicted label: " << predictedLabel << ", Correct label: " << point.label << std::endl;
//         if (predictedLabel == point.label)
//             correctCount++;
//     }

//     double accuracy = static_cast<double>(correctCount) / testset.size() * 100.0;
//     std::cout << "Accuracy: " << accuracy << "%" << std::endl;

//     return 0;
// }

// int main() {
//     // 创建数据集
//     std::vector<Point> dataset;
//     dataset.push_back(Point({2.0, 3.0}, 0));
//     dataset.push_back(Point({5.0, 4.0}, 0));
//     dataset.push_back(Point({9.0, 6.0}, 1));
//     dataset.push_back(Point({4.0, 7.0}, 1));
//     dataset.push_back(Point({8.0, 1.0}, 0));
//     dataset.push_back(Point({7.0, 2.0}, 1));

//     // 创建 KD 树
//     KDTree kdTree;
//     kdTree.buildTree(dataset);

//     // 测试数据集
//     std::vector<Point> testset;
//     testset.push_back(Point({3.0, 2.0}, 0));   // 正确类别：0
//     testset.push_back(Point({6.0, 5.0}, 1));   // 正确类别：1
//     testset.push_back(Point({1.0, 5.0}, 0));   // 正确类别：0
//     testset.push_back(Point({9.0, 4.0}, 1));   // 正确类别：1
//     testset.push_back(Point({6.0, 1.0}, 0));   // 正确类别：0
//     testset.push_back(Point({4.0, 5.0}, 1));   // 正确类别：1

//     int correctCount = 0;
//     for (const auto& point : testset) {
//         int predictedLabel = kdTree.predict(point, 11);
//         std::cout << "Predicted label: " << predictedLabel << ", Correct label: " << point.label << std::endl;
//         if (predictedLabel == point.label)
//             correctCount++;
//     }

//     double accuracy = static_cast<double>(correctCount) / testset.size() * 100.0;
//     std::cout << "Accuracy: " << accuracy << "%" << std::endl;

//     return 0;
// }

//可用
