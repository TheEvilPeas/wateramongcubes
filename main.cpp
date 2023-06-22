#include <QApplication>
#include <QWidget>
#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QMessageBox>
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#include <QTextEdit>

using namespace std;

//объявление сокрощенных названий для типов
typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

//инициализация константных массивов для обхода вокруг клетки в dfs
const int fx[4] = {0, 0, 1, -1};
const int fy[4] = {1, -1, 0, 0};

//инциализация переменных
int rowsMatrix, colsMatrix; // количество строк и столбцов
ll sumWater; // временная переменная для подсчета суммы объема воды
int matrixInput[101][101]; // получаемая матрица
bool matrixVisited[101][101]; //матрица значений, которые были посещены
priority_queue<pair<int, pii>, vector<pair<int, pii>>, greater<pair<int, pii>>> pq; //рабочая переменная

// Функция для проверки, является ли клетка с координатами (x, y) допустимой
bool valid(int x, int y, int L) {
    if (x >= 0 && x < rowsMatrix && y >= 0 && y < colsMatrix && !matrixVisited[x][y] && matrixInput[x][y] <= L)
        return true;
    else
        return false;
}

// Функция для обхода клеток и подсчета объема воды
void DepthFirstSearch(int ux, int uy, int L) {
    matrixVisited[ux][uy] = true;

    for (int i = 0; i < 4; i++) {
        int vx = ux + fx[i];
        int vy = uy + fy[i];
        if (valid(vx, vy, L)) {
            sumWater += (ll)(L - matrixInput[vx][vy]);
            DepthFirstSearch(vx, vy, L);
        } else if (matrixInput[vx][vy] > L && !matrixVisited[vx][vy]) {
            pq.push({matrixInput[vx][vy], {vx, vy}});
        }
    }
}

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    QWidget window;
    QGridLayout *layout = new QGridLayout(&window);

    QLabel *labelSize = new QLabel("Размер матрицы:", &window);
    QLineEdit *lineEditSize = new QLineEdit(&window);

    QLabel *labelMatrix = new QLabel("Матрица:", &window);
    QTextEdit *textEditMatrix = new QTextEdit(&window);

    QPushButton *buttonSolve = new QPushButton("Решить", &window);

    layout->addWidget(labelSize, 0, 0);
    layout->addWidget(lineEditSize, 0, 1);
    layout->addWidget(labelMatrix, 1, 0);
    layout->addWidget(textEditMatrix, 1, 1);
    layout->addWidget(buttonSolve, 2, 0, 1, 2);

    QObject::connect(buttonSolve, &QPushButton::clicked, [&]() {
        QString sizeText = lineEditSize->text();
        QStringList sizeList = sizeText.split(" ");
        if (sizeList.size() != 2) {
            QMessageBox::critical(&window, "Ошибка", "Некорректный размер матрицы");
            return;
        }

        rowsMatrix = sizeList[0].toInt();
        colsMatrix = sizeList[1].toInt();

        QString matrixText = textEditMatrix->toPlainText();
        QStringList matrixList = matrixText.split("\n");
        if (matrixList.size() != rowsMatrix) {
            QMessageBox::critical(&window, "Ошибка", "Некорректная матрица");
            return;
        }

        for (int i = 0; i < rowsMatrix; i++) {
            QStringList rowList = matrixList[i].split(" ");
            if (rowList.size() != colsMatrix) {
                QMessageBox::critical(&window, "Ошибка", "Некорректная матрица");
                return;
            }

            for (int j = 0; j < colsMatrix; j++) {
                matrixInput[i][j] = rowList[j].toInt();
                if (i == 0 || i == rowsMatrix - 1 || j == 0 || j == colsMatrix - 1)
                    pq.push({matrixInput[i][j], {i, j}});
            }
        }

        ll ans = 0;
        while (!pq.empty()) {
            auto x = pq.top();
            pq.pop();
            sumWater = 0;
            int i, j, val;
            val = x.first;
            i = x.second.first;
            j = x.second.second;
            if (!matrixVisited[i][j]) {
                DepthFirstSearch(i, j, val);
            }
            ans += sumWater;
        }

        QMessageBox::information(&window, "Результат", "Результат работы: " + QString::number(ans));

        memset(matrixVisited, false, sizeof(matrixVisited));
    });

    window.setLayout(layout);
    window.show();

    return app.exec();
}
