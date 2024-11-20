#include <iostream>


const int dx[] = { -1, 1, 0, 0 };
const int dy[] = { 0, 0, -1, 1 };

void labelComponents(int** image, int m, int n) {
    int label = 1; //Label for connected component
    int** visited = new int*[m];
    for (int i = 0; i < m; i++) {
        visited[i] = new int[n];
        for (int j = 0; j < n; j++) {
            visited[i][j] = 0;
        }
    }
    
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (image[i][j] == 1 && visited[i][j] == 0) {
                label++;

                int* queueX = new int[m * n];//Queue for x coordinate
                int* queueY = new int[m * n];//Queue for y coordinate
                int front = 0;
                int rear = 0;

                queueX[rear] = i;//Add x coordinate to queue
                queueY[rear] = j;//Add y coordinate to queue
                rear++;

                while (front < rear) {
                    int x = queueX[front];//Get x coordinate from queue
                    int y = queueY[front];//Get y coordinate from queue
                    front++;

                    if (image[x][y] == 1) {
                        image[x][y] = label;
                        visited[x][y] = 1;

                        for (int k = 0; k < 4; k++) {
                            int newX = x + dx[k];
                            int newY = y + dy[k];
                            //Check new coordinates if they are valid and not visited
                            if (newX >= 0 && newX < m && newY >= 0 && newY < n && image[newX][newY] == 1) {
                                queueX[rear] = newX;
                                queueY[rear] = newY;
                                rear++;
                            }
                        }
                    }
                }

                delete[] queueX;
                delete[] queueY;
            }
        }
    }

    for (int i = 0; i < m; i++) {
        delete[] visited[i];
    }
    delete[] visited;
}

int main() {
    //Image size
    int m = 7;
    int n = 7;

    //Create image
    int** image = new int*[m];
    for (int i = 0; i < m; i++) {
        image[i] = new int[n];
        for (int j = 0; j < n; j++) {
            image[i][j] = 0;
        }
    }
    //Input binary image
    int binaryImage[7][7] = {
            {0, 0, 1, 0, 0, 0, 0},
            {0, 0, 1, 1, 0, 0, 0},
            {0, 0, 0, 0, 1, 0, 0},
            {0, 0, 0, 1, 1, 0, 0},
            {0, 1, 0, 0, 1, 0, 1},
            {1, 1, 1, 0, 0, 0, 1},
            {1, 1, 1, 0, 0, 1, 1,}
    };
    //Copy binary image to image
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            image[i][j] = binaryImage[i][j];
        }
    }

    labelComponents(image, m, n);
    //Output labeled image
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            std::cout << image[i][j] << " ";
        }
        std::cout << std::endl;
    }
    //Delete image
    for (int i = 0; i < m; i++) {
        delete[] image[i];
    }
    delete[] image;

    return 0;
}
