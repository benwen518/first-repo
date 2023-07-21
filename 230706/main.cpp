#include <Python.h>

int main() {
    // 初始化Python解释器
    Py_Initialize();

    // 调用Python代码
    PyRun_SimpleString(R"(
        import pandas as pd
        import matplotlib as mpl
        import matplotlib.pyplot as plt
        from mpl_toolkits.mplot3d import Axes3D

        data = pd.read_csv('your_file.csv', header=None)
        xs = data.iloc[:, 0]
        ys = data.iloc[:, 1]
        zs = data.iloc[:, 2]
        categories = data.iloc[:, 3]

        cmap = mpl.cm.get_cmap('viridis')

        fig = plt.figure()
        ax = Axes3D(fig)

        sc = ax.scatter(xs, ys, zs, c=categories, cmap=cmap)

        cbar = fig.colorbar(sc)

        ax.set_xlabel('X label')
        ax.set_ylabel('Y label')
        ax.set_zlabel('Z label')

        plt.show()
    )");

    // 清理Python解释器
    Py_Finalize();

    return 0;
}
