import numpy as np

XtX = np.array([
    [5, 15, 10, 12, 7],
    [15, 55, 37, 39, 24],
    [10, 37, 30, 23, 17],
    [12, 39, 23, 34, 14],
    [7, 24, 17, 14, 15]
])
Xty = np.array([[168], [572], [391], [413], [265]])
beta = np.linalg.inv(XtX) @ Xty
print(beta)