import numpy as np
from numpy import int64

def bilinear_interp_vectorized(a: np.ndarray, b: np.ndarray) -> np.ndarray:
    """
        This is the vectorized implementation of bilinear interpolation.
        - a is a ND array with shape [N, H1, W1, C], dtype = int64
        - b is a ND array with shape [N, H2, W2, 2], dtype = float64
        - return a ND array with shape [N, H2, W2, C], dtype = int64
    """
    # get axis size from ndarray shape
    N, H1, W1, C = a.shape
    N1, H2, W2, _ = b.shape
    assert N == N1

    # TODO: Implement vectorized bilinear interpolation
    res = np.empty((N, H2, W2, C), dtype=int64)

    padding = np.empty((N, H2, W2, 2))
    padding[:, :, :, :] = b

    xy = np.array(np.meshgrid(np.arange(H2), np.arange(W2)), dtype=np.float32)
    x = xy[0].flatten().astype(np.int)
    y = xy[1].flatten().astype(np.int)

    index = padding[:, x, y, :]
    clip_index = np.floor(index).astype(np.int)

    clip_index = clip_index.reshape((-1, 2))
    index = index.reshape((-1, 2))
    a = a.reshape((-1, C))

    _xy = index - clip_index
    n = np.array(np.meshgrid(np.arange(W2*H2), np.arange(N)), dtype=np.int32)
    n = n[1].flatten().astype(np.int)

    result = (1-_xy[:, 0, None]) * (1-_xy[:, 1, None]) * a[clip_index[:, 0]*W1 + clip_index[:, 1] + n[:]*W1*H1, :] + \
             _xy[:, 0, None] * (1 - _xy[:, 1, None]) * a[(clip_index[:, 0]+1)*W1 + clip_index[:, 1] + n[:]*W1*H1, :] + \
             (1-_xy[:, 0, None]) * _xy[:, 1, None] * a[clip_index[:, 0]*W1 + (clip_index[:, 1]+1) + n[:]*W1*H1, :] + \
             _xy[:, 0, None] * _xy[:, 1, None] * a[(clip_index[:, 0]+1)*W1 + (clip_index[:, 1]+1) + n[:]*W1*H1, :]

    res[:, :, :, :] = result.reshape((N1, W2, H2, -1)).transpose(0, 2, 1, 3)
    return res



