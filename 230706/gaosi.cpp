#include <iostream>
#include <vector>
#include <random>
#include <cmath>
#include <algorithm>
#include <numeric>
#include <map>

// 高斯分布生成函数
std::vector<std::vector<double>> generateGaussianData(int samples, const std::vector<double>& mean, const std::vector<std::vector<double>>& cov) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::normal_distribution<double> dist(0.0, 1.0);

    int dimensions = mean.size();
    std::vector<std::vector<double>> data(samples, std::vector<double>(dimensions));

    for (int i = 0; i < samples; ++i) {
        for (int j = 0; j < dimensions; ++j) {
            double sum = 0.0;
            for (int k = 0; k < dimensions; ++k) {
                sum += cov[j][k] * dist(gen);
            }
            data[i][j] = mean[j] + sum;
        }
    }

    return data;
}

// KNN算法分类函数
std::vector<int> knnClassification(const std::vector<std::vector<double>>& data, const std::vector<int>& labels, const std::vector<std::vector<double>>& newData, int k) {
    int numSamples = data.size();
    int numFeatures = data[0].size();
    int numNewSamples = newData.size();

    std::vector<int> predictions(numNewSamples);

    for (int i = 0; i < numNewSamples; ++i) {
        std::vector<std::pair<double, int>> distances;

        for (int j = 0; j < numSamples; ++j) {
            double distance = 0.0;
            for (int f = 0; f < numFeatures; ++f) {
                distance += std::pow(data[j][f] - newData[i][f], 2);
            }
            distances.emplace_back(std::sqrt(distance), labels[j]);
        }

        std::sort(distances.begin(), distances.end());

        std::map<int, int> labelCount;
        for (int j = 0; j < k; ++j) {
            int label = distances[j].second;
            labelCount[label]++;
        }

        int maxCount = 0;
        int predictedLabel = -1;
        for (const auto& pair : labelCount) {
            if (pair.second > maxCount) {
                maxCount = pair.second;
                predictedLabel = pair.first;
            }
        }

        predictions[i] = predictedLabel;
    }

    return predictions;
}

// 交叉熵函数
double crossEntropy(const std::vector<int>& trueLabels, const std::vector<int>& predictedLabels) {
    int numSamples = trueLabels.size();
    double sum = 0.0;

    for (int i = 0; i < numSamples; ++i) {
        double prob = (trueLabels[i] == predictedLabels[i]) ? 1.0 : 0.0;
        sum += std::log(prob);
    }

    return -sum / numSamples;
}

int main() {
    // 设置随机种子，以保证结果可重复性
    std::srand(42);

    // 定义高斯分布1的均值和协方差矩阵
    std::vector<double> mean1{ 0.0, 0.0 };
    std::vector<std::vector<double>> cov1{ { 1.0, 0.0 }, { 0.0, 1.0 } };
    int samples1 = 100;

    // 定义高斯分布2的均值和协方差矩阵
    std::vector<double> mean2{ 3.0, 3.0 };
    std::vector<std::vector<double>> cov2{ { 1.0, 0.0 }, { 0.0, 1.0 } };
    int samples2 = 100;

    // 生成高斯分布1的数据集
    std::vector<std::vector<double>> data1 = generateGaussianData(samples1, mean1, cov1);
    std::vector<int> labels1(samples1, 0);

    // 生成高斯分布2的数据集
    std::vector<std::vector<double>> data2 = generateGaussianData(samples2, mean2, cov2);
    std::vector<int> labels2(samples2, 1);

    // 合并数据集和标签
    std::vector<std::vector<double>> data;
    data.reserve(samples1 + samples2);
    data.insert(data.end(), data1.begin(), data1.end());
    data.insert(data.end(), data2.begin(), data2.end());

    std::vector<int> labels;
    labels.reserve(samples1 + samples2);
    labels.insert(labels.end(), labels1.begin(), labels1.end());
    labels.insert(labels.end(), labels2.begin(), labels2.end());

    // 创建KNN分类器
    int k = 3;

    // 生成新样本
    std::vector<std::vector<double>> newSamples{ { 1.0, 1.0 }, { 2.0, 2.0 } };

    // 使用KNN算法进行分类预测
    std::vector<int> predictions = knnClassification(data, labels, newSamples, k);

    // 打印真实值和预测值
    std::cout << "真实值: ";
    for (const auto& label : labels) {
        std::cout << label << " ";
    }
    std::cout << std::endl;

    std::cout << "预测值: ";
    for (const auto& prediction : predictions) {
        std::cout << prediction << " ";
    }
    std::cout << std::endl;

    // 计算准确率
    int numCorrect = 0;
    for (int i = 0; i < labels.size(); ++i) {
        if (labels[i] == predictions[i]) {
            numCorrect++;
        }
    }
    double accuracy = static_cast<double>(numCorrect) / labels.size();
    std::cout << "准确率: " << accuracy << std::endl;

    // 计算交叉熵
    double entropy = crossEntropy(labels, predictions);
    std::cout << "交叉熵: " << entropy << std::endl;

    // 输出详细坐标
    std::cout << "详细坐标:" << std::endl;
    for (int i = 0; i < data.size(); ++i) {
        std::cout << data[i][0] << " " << data[i][1] << " " << labels[i] << std::endl;
    }

    return 0;
}
